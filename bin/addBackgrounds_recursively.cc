
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
  void processSubdirectory_recursively(TFileDirectory& fs, const TDirectory* dir, const std::string& dirName, const vstring& processes_input, const std::string& process_output, const vstring& histogramsToCopy, const vstring& central_or_shifts)
  {
    std::cout << "<processSubdirectory_recursively>:" << std::endl;
    std::cout << " dir = '" << dirName << "'" << std::endl;
    
    // check if directory given as function argument contains subdirectories for input processes
    bool allProcessesExist = true;
    for ( vstring::const_iterator process_input = processes_input.begin();
	  process_input != processes_input.end(); ++process_input ) {
      const TDirectory* subdir_input = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(process_input->data()));
      if ( !subdir_input ) allProcessesExist = false;
    }
    // std::cout << "allProcessesExist = " << allProcessesExist << std::endl;
    if ( allProcessesExist ) {
      std::cout << "processing directory = " << dirName << std::endl;

      // get list of histograms to be added
      std::string the_process_input = processes_input.front();
      const TDirectory* the_subdir_input = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(the_process_input.data()));      
      assert(the_subdir_input);
      // the_subdir_input->ls();
      
      std::set<std::string> histograms;
      TList* list = the_subdir_input->GetListOfKeys();
      TIter next(list);
      TKey* key = 0;
      while ( (key = dynamic_cast<TKey*>(next())) ) {
	TObject* object = key->ReadObj();
	TH1* histogram = dynamic_cast<TH1*>(object);
	if ( !histogram ) continue;
	TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", the_process_input.data()), "");
	for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	      central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
	  if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
	    histogramName = histogramName.ReplaceAll(Form("%s_", central_or_shift->data()), "");
	  }
	}
	if ( histogramName.Contains("CMS_") ) continue;
	bool isHistogramToCopy = false;
	if ( histogramsToCopy.size() > 0 ) {
	  for ( vstring::const_iterator histogramToCopy = histogramsToCopy.begin();
		histogramToCopy != histogramsToCopy.end(); ++histogramToCopy ) {
	    if ( (*histogramToCopy) == histogramName.Data() ) isHistogramToCopy = true;
	  }
	} else {
	  isHistogramToCopy = true;
	}
	if ( !isHistogramToCopy ) continue;
	if ( histograms.find(histogramName.Data()) == histograms.end() ) {
	  std::cout << "adding histogram = " << histogramName.Data() << std::endl;
	  histograms.insert(histogramName.Data());
	}
      }
      
      // add histograms
      for ( std::set<std::string>::const_iterator histogram = histograms.begin();
	    histogram != histograms.end(); ++histogram ) {
	std::cout << "histogram = " << (*histogram) << std::endl;
	for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	      central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
	  
	  int verbosity = ( histogram->find("EventCounter") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	  
	  std::vector<TH1*> histograms_input;
	  for ( vstring::const_iterator process_input = processes_input.begin();
		process_input != processes_input.end(); ++process_input ) {
	    bool enableException = ( (*central_or_shift) == "" || (*central_or_shift) == "central" ) ? true : false;
	    TH1* histogram_input = getHistogram(dir, *process_input, *histogram, *central_or_shift, enableException);
	    if ( !histogram_input ) histogram_input = getHistogram(dir, *process_input, *histogram, "", true);
	    histograms_input.push_back(histogram_input);
	  }

	  std::string subdirName_output = Form("%s/%s", dirName.data(), process_output.data());
	  std::cout << "creating subdirectory = '" << subdirName_output << "'" << std::endl;
	  TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
	  subdir_output->cd();
	  	  
	  std::string histogramName_output;
	  if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramName_output.append(*central_or_shift);
	  if ( histogramName_output.length() > 0 ) histogramName_output.append("_");
	  histogramName_output.append(*histogram);
	  std::cout << "histogram = " << (*histogram) << ", central_or_shift = " << (*central_or_shift) << ": histogramName_output = " << histogramName_output << std::endl;
	  addHistograms(histogramName_output, histograms_input, verbosity);
	}
      }
    }

    // recursively process all subdirectories
    std::vector<const TDirectory*> subdirs = getSubdirectories(dir);
    for ( std::vector<const TDirectory*>::iterator subdir = subdirs.begin();
	  subdir != subdirs.end(); ++subdir ) {
      processSubdirectory_recursively(fs, *subdir, dirName + "/" + (*subdir)->GetName(), processes_input, process_output, histogramsToCopy, central_or_shifts);
    }
    for(const TDirectory* subdir: subdirs)
    {
      delete subdir;
      subdir = 0;
    }
  }
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

  std::cout << "<addBackgrounds_recursively>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgrounds_recursively");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addBackgrounds_recursively") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddBackgrounds = cfg.getParameter<edm::ParameterSet>("addBackgrounds");

  vstring categories = cfgAddBackgrounds.getParameter<vstring>("categories");
  
  vstring processes_input = cfgAddBackgrounds.getParameter<vstring>("processes_input");
  std::string process_output = cfgAddBackgrounds.getParameter<std::string>("process_output");

  vstring histogramsToCopy = cfgAddBackgrounds.getParameter<vstring>("histogramsToCopy");
  std::cout<< "histogramsToCopy = " << format_vstring(histogramsToCopy) << std::endl;

  vstring central_or_shifts = cfgAddBackgrounds.getParameter<vstring>("sysShifts");
  central_or_shifts.push_back(""); // CV: add central value
  
  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addBackgrounds_recursively") 
      << "Exactly one input file expected !!\n";
  std::string inputFileName = inputFiles.files().front();
  std::cout << "opening input file = '" << inputFileName << "'" << std::endl;
  TFile* inputFile = new TFile(inputFileName.data());
  if ( !inputFile ) throw cms::Exception("addBackgrounds_recursively") 
    << "Failed to open input file = '" << inputFileName << "' !!\n";
  std::cout << " done." << std::endl;

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  if ( categories.size() == 0 ) categories = getSubdirectoryNames(inputFile);

  for ( vstring::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    
    TDirectory* dir = getDirectory(inputFile, *category, true);
    assert(dir);

    std::cout << "processing category = " << (*category) << std::endl;
	
    processSubdirectory_recursively(fs, dir, *category, processes_input, process_output, histogramsToCopy, central_or_shifts);
  }

  //---------------------------------------------------------------------------------------------------
  // CV: Add (dummy) histograms for number of analyzed and processed events
  //     This is needed to avoid run-time errors/warnings when executing python/commands/get_events_count.py (called by python/sbatch-node.template.hadd.sh)
  fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  //---------------------------------------------------------------------------------------------------

  std::cout << "closing input file = '" << inputFile->GetName() << "'" << std::endl;
  delete inputFile;
  std::cout << " done." << std::endl;

  clock.Show("addBackgrounds_recursively");

  std::cout << "returning exit code = " << EXIT_SUCCESS << " (EXIT_SUCCESS)." << std::endl;
  return EXIT_SUCCESS;
}
