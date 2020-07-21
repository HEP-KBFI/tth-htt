
/** \executable copyHistograms_recursively
 *
 * Copy histograms within TDirectories specified in python configuration to new ROOT file.
 * The purpose of this executable is to split the hadd stage1 ROOT files into multiple ROOT files,
 * with one ROOT file per event category, in order to reduce the memory consumption of the subsequent hadd stage1_5 and hadd stage2 jobs.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()

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
  void processSubdirectory_recursively(TFileDirectory& fs, const TDirectory* dir_input, const std::string& dirName)
  {
    std::cout << "<processSubdirectory_recursively>:" << std::endl;
    std::cout << " processing input directory = " << dirName << std::endl;
          
    TDirectory* dir_output = createSubdirectory_recursively(fs, dirName);
    dir_output->cd();

    // process all histograms in current directory
    TList* list = dir_input->GetListOfKeys();
    TIter next(list);
    TKey* key = 0;
    while ( (key = dynamic_cast<TKey*>(next())) ) {
      TObject* object = key->ReadObj();
      TH1* histogram_input = dynamic_cast<TH1*>(object);
      if ( histogram_input ) {
	std::string histogramName_output = histogram_input->GetName();
	addHistograms(histogramName_output, { histogram_input });
      }
    }

    // recursively process all subdirectories
    std::vector<const TDirectory*> subdirs_input = getSubdirectories(dir_input);
    for ( std::vector<const TDirectory*>::iterator subdir_input = subdirs_input.begin();
          subdir_input != subdirs_input.end(); ++subdir_input ) {
      processSubdirectory_recursively(fs, *subdir_input, dirName + "/" + (*subdir_input)->GetName());
    }
    for(const TDirectory* subdir_input: subdirs_input)
    {
      delete subdir_input;
      subdir_input = 0;
    }
  }
}

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("copyHistograms_recursively") 
      << "Failed to load histogram = '" << histogramName << "' from file = " << inputFile->GetName() << " !!\n";
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<copyHistograms_recursively>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("copyHistograms_recursively");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("copyHistograms_recursively") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgCopyHistograms = cfg.getParameter<edm::ParameterSet>("copyHistograms");

  vstring categories = cfgCopyHistograms.getParameter<vstring>("categories");
  if ( !(categories.size() >= 1) )
    throw cms::Exception("copyHistograms_recursively") 
      << "Configuration parameter 'categories' must not be empty !!\n";
  
  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("copyHistograms_recursively") 
      << "Exactly one input file expected !!\n";
  std::string inputFileName = inputFiles.files().front();
  std::cout << "opening input file = '" << inputFileName << "'" << std::endl;
  TFile* inputFile = new TFile(inputFileName.data());
  if ( !inputFile ) throw cms::Exception("copyHistograms_recursively") 
    << "Failed to open input file = '" << inputFileName << "' !!\n";
  std::cout << " done." << std::endl;

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  for ( vstring::const_iterator category = categories.begin();
        category != categories.end(); ++category ) {
    
    TDirectory* dir = getDirectory(inputFile, *category, true);
    assert(dir);

    std::cout << "processing category = " << (*category) << std::endl;

    processSubdirectory_recursively(fs, dir, *category);
  }

  //---------------------------------------------------------------------------------------------------
  // CV: Add (dummy) histograms for number of analyzed and processed events
  //     This is needed to avoid run-time errors/warnings when executing python/commands/get_events_count.py (called by python/sbatch-node.template.hadd.sh)
  TH1* histogram_analyzedEntries_input = loadHistogram(inputFile, "analyzedEntries");
  TH1* histogram_analyzedEntries_output = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  histogram_analyzedEntries_output->SetBinContent(1, histogram_analyzedEntries_input->GetBinContent(1));
  histogram_analyzedEntries_output->SetBinError(1, histogram_analyzedEntries_input->GetBinError(1));
  TH1* histogram_selectedEntries_input = loadHistogram(inputFile, "selectedEntries");
  TH1* histogram_selectedEntries_output = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  histogram_selectedEntries_output->SetBinContent(1, histogram_selectedEntries_input->GetBinContent(1));
  histogram_selectedEntries_output->SetBinError(1, histogram_selectedEntries_input->GetBinError(1));
  //---------------------------------------------------------------------------------------------------

  std::cout << "closing input file = '" << inputFile->GetName() << "'" << std::endl;
  delete inputFile;
  std::cout << " done." << std::endl;

  clock.Show("copyHistograms_recursively");

  std::cout << "returning exit code = " << EXIT_SUCCESS << " (EXIT_SUCCESS)." << std::endl;
  return EXIT_SUCCESS;
}
