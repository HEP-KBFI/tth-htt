
/** \executable addBackgrounds_recursively
 *
 * Add "background" contributions of different MC samples.
 * Works for arbitrary "depth" of TDirectory structure in which histograms are stored within ROOT file.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h" // getSubdirectories, getSubdirectoryNames
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TPRegexp.h"
#include "TDirectory.h"
#include "TList.h"
#include "TKey.h"
#include "TObject.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  void processSubdirectory_recursively(TFileDirectory& fs, 
				       const TDirectory* dir_input, const std::string& dirName, 
				       std::map<std::string, TDirectory*>& dirs_output, std::map<std::string, TH1*>& histograms_output,
				       int verbosity)
  {
    std::cout << "processing directory = '" << dirName << "'" << std::endl;
    
    // create output directory
    std::string key_dirs_output = dirName;
    TDirectory* dir_output = dirs_output[key_dirs_output];
    if ( dir_output ) {
      dir_output->cd();
    } else {
      //dir_output = createSubdirectory_recursively(fs, dirName, ( verbosity >= 1 ) ? true : false);
      dir_output = createSubdirectory_recursively(fs, dirName);
      assert(dir_output);
      dirs_output[key_dirs_output] = dir_output;
      dir_output->cd();
    }
    
    // process histograms within current input directory
    TList* keys_dir_input = dir_input->GetListOfKeys();
    TIter next(keys_dir_input);
    TKey* key_dir_input = 0;
    while ( (key_dir_input = dynamic_cast<TKey*>(next())) ) {
      TObject* object = key_dir_input->ReadObj();
      TH1* histogram_input = dynamic_cast<TH1*>(object);
      if ( !histogram_input ) continue;
      std::string histogramName = histogram_input->GetName();
      std::string key_histograms_output = Form("%s/%s", dirName.data(), histogramName.data());
      TH1* histogram_output = histograms_output[key_histograms_output];
      if ( histogram_output ) {
	// add input histogram to existing output histogram
	//checkCompatibleBinning(histogram_input, histogram_output);
	//std::cout << "adding histogram = '" << histogramName << "'" << std::endl;
	histogram_output->Add(histogram_input);
      } else {
	// create output histogram
	//std::cout << "creating histogram = '" << histogramName << "'" << std::endl;
	histogram_output = static_cast<TH1*>(histogram_input->Clone(histogramName.data()));
	histogram_output->Reset();
	if ( !histogram_output->GetSumw2N() ) {
	  histogram_output->Sumw2();
	}
	histogram_output->Add(histogram_input);
	histograms_output[key_histograms_output] = histogram_output;
      }
    }

    // process all subdirectories within current input directory (recursively)
    std::vector<const TDirectory*> subdirs_input = getSubdirectories(dir_input);
    for ( std::vector<const TDirectory*>::iterator subdir_input = subdirs_input.begin();
          subdir_input != subdirs_input.end(); ++subdir_input ) {
      std::string subdirName = Form("%s/%s", dirName.data(), (*subdir_input)->GetName());
      processSubdirectory_recursively(
        fs, 
        *subdir_input, subdirName, 
	dirs_output, histograms_output,
	verbosity);
    }
  }
}

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 3 ) {
    std::cout << "Usage: " << argv[0] 
	      << " [-v [verbosity]]"
	      << " targetfile source1 [source2 source3 ...]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<my_hadd>:" << std::endl;

  std::vector<std::string> inputFileNames;
  std::string outputFileName;
  int verbosity = 1;
  int idx_arg = 1;
  while ( idx_arg < argc ) {
    std::string arg = argv[idx_arg];
    if ( arg == "-v" ) {
      if ( (idx_arg + 1) < argc ) {
	verbosity = atoi(argv[idx_arg + 1]);
	idx_arg += 2;
      } else {
	throw cms::Exception("my_hadd") 
	  << "Command-line option '-v' must be followed by verbosity level !!\n";
      }
      continue;
    }
    if ( outputFileName == "" ) {
      outputFileName = argv[idx_arg];      
    } else {
      inputFileNames.push_back(argv[idx_arg]);
    }
    idx_arg += 1;
  }
  if ( inputFileNames.size() == 0 ) {
    throw cms::Exception("my_hadd") 
      << "No input files given !!\n";
  }
  if ( outputFileName == "" ) {
    throw cms::Exception("my_hadd") 
      << "No output file given !!\n";
  }

  std::cout << "inputFileNames = " << format_vstring(inputFileNames) << std::endl;
  std::cout << "outputFileName = '" << outputFileName << "'" << std::endl;
  std::cout << "verbosity = " << verbosity << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("my_hadd");

  fwlite::TFileService fs = fwlite::TFileService(outputFileName.data());

  std::map<std::string, TDirectory*> dirs_output; // key = dirName
  std::map<std::string, TH1*> histograms_output; // key = dirName + "/" + histogramName

  for ( std::vector<std::string>::const_iterator inputFileName = inputFileNames.begin();
	inputFileName != inputFileNames.end(); ++inputFileName ) {
    std::cout << "opening input file = '" << (*inputFileName) << "'" << std::endl;
    TFile* inputFile = new TFile(inputFileName->data());
    if ( !inputFile ) {
      throw cms::Exception("my_hadd") 
	<< "Failed to open input file = '" << (*inputFileName) << "' !!\n";
    }
    std::cout << " done." << std::endl;

    std::string inputFile_directory = "";
    processSubdirectory_recursively(
      fs, 
      inputFile, inputFile_directory, 
      dirs_output, histograms_output,
      verbosity);

    std::cout << "closing input file = '" << (*inputFileName) << "'" << std::endl;
    delete inputFile;
    std::cout << " done." << std::endl;
  }

  clock.Show("my_hadd");

  std::cout << "returning exit code = " << EXIT_SUCCESS << " (EXIT_SUCCESS)." << std::endl;
  return EXIT_SUCCESS;
}
