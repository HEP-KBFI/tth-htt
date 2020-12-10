
/** \executable addBackgrounds
 *
 * Add "background" contributions of different MC samples.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h" // getSubdirectories, getSubdirectoryNames
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

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
                                       const TDirectory* dir, const std::string& dirName, 
                                       const vstring& processes_input, const std::string& process_output, 
                                       const vstring& central_or_shifts,
                                       int depth_recursion, int max_depth_recursion,
                                       bool isDEBUG = false)
  {
    if ( isDEBUG )
    {
      std::cout << "<processSubdirectory_recursively>:" << std::endl;
      std::cout << " dir = '" << dirName << "'" << std::endl;
    }

    // check if directory given as function argument contains subdirectories for input processes
    bool allProcessesExist = true;
    for ( auto process_input: processes_input )
    {
      const TDirectory* subdir_input = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(process_input.data()));
      if ( !subdir_input ) 
      {
        allProcessesExist = false;
      }
    }
    if ( allProcessesExist ) 
    {
      if ( isDEBUG )
      {
        std::cout << "processing directory = " << dirName << std::endl;
      }

      // get list of histograms to be added
      std::string the_process_input = processes_input.front();
      const TDirectory* the_subdir_input = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(the_process_input.data()));      
      assert(the_subdir_input);
      //the_subdir_input->ls();
      
      std::set<std::string> histogramNames;
      TList* list = the_subdir_input->GetListOfKeys();
      TIter next(list);
      TKey* key = 0;
      while ( (key = dynamic_cast<TKey*>(next())) ) {
        TObject* object = key->ReadObj();
        TH1* histogram = dynamic_cast<TH1*>(object);
        if ( !histogram ) continue;
        TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", the_process_input.data()), "");
        for ( auto central_or_shift: central_or_shifts )
        {
	  if ( !(central_or_shift == "" || central_or_shift == "central") ) 
          {
	    histogramName = histogramName.ReplaceAll(Form("%s_", central_or_shift.data()), "");
	  }
	}
	if ( histogramName.Contains("CMS_") ) continue;
	if ( histogramName.Contains("cutFlow") ) continue;
	if ( histogramNames.find(histogramName.Data()) == histogramNames.end() ) 
        {
          if ( isDEBUG )
          {
	    std::cout << "adding histogram = " << histogramName.Data() << std::endl;
          }
	  histogramNames.insert(histogramName.Data());
	}
      }
      
      // add histograms
      for ( auto histogramName: histogramNames )
      {
        for ( auto central_or_shift: central_or_shifts )
        {
          std::vector<TH1*> histograms_input;
          for ( auto process_input: processes_input ) 
          {
            bool enableException = ( central_or_shift == "" || central_or_shift == "central" ) ? true : false;
            TH1* histogram_input = getHistogram(dir, process_input, histogramName, central_or_shift, enableException);
            if ( !histogram_input ) 
            {
              histogram_input = getHistogram(dir, process_input, histogramName, "", true);
            }
            if ( std::find(histograms_input.begin(), histograms_input.end(), histogram_input) != histograms_input.end() )
            {
              throw cmsException(__func__, __LINE__)
                << "Attempting to add the same histogram twice: " << histogram_input->GetName() << " from " << process_input << " !!\n";
            }
if ( histogramName == "jpaCategory" && histogram_input->GetNbinsX() != 15 ) 
{
  std::cout << "histogramName = " << histogramName << " for process_input = " << process_input << " has the wrong binning --> skipping !!" << std::endl;
  continue;
}
            histograms_input.push_back(histogram_input);
          }

          std::string subdirName_output = Form("%s/%s", dirName.data(), process_output.data());
          if ( isDEBUG )
          {
            std::cout << "creating subdirectory = '" << subdirName_output << "'" << std::endl;
          }
          TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
          subdir_output->cd();

          std::string histogramName_output;
          if ( !(central_or_shift == "" || central_or_shift == "central") )
          {
            histogramName_output.append(central_or_shift);
          }
          if ( histogramName_output.length() > 0 )
          {
            histogramName_output.append("_");
          }
          histogramName_output.append(histogramName);
          if ( isDEBUG )
          {
            std::cout << "creating histogram = '" << histogramName_output << "'" << std::endl;
          }
          addHistograms(histogramName_output, histograms_input);
        }
      }
    }

    // recursively process all subdirectories
    std::vector<const TDirectory*> subdirs = getSubdirectories(dir);
    bool stopRecursion = ( max_depth_recursion != -1 && depth_recursion >= max_depth_recursion ) ? true : false;
    if ( !stopRecursion )
    {
      for ( std::vector<const TDirectory*>::iterator subdir = subdirs.begin();
            subdir != subdirs.end(); ++subdir ) {
        processSubdirectory_recursively(
          fs, *subdir, dirName + "/" + (*subdir)->GetName(), 
          processes_input, process_output, 
          central_or_shifts,
          depth_recursion + 1, max_depth_recursion,
          isDEBUG
        );
      }
    }
    else
    {
      if ( isDEBUG )
      {
        std::cout << "aborting recursion, because maximum-recursion-depth = " << max_depth_recursion << " has been reached." << std::endl;
      }
    }
    for ( const TDirectory* subdir: subdirs )
    {
      delete subdir;
      subdir = nullptr;
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

  std::cout << "<addBackgrounds2>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgrounds2");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cmsException(__func__, __LINE__)
      << "No ParameterSet 'process' found in configuration file = " << argv[1];

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addBackgrounds = cfg.getParameter<edm::ParameterSet>("addBackgrounds");

  vstring categories = cfg_addBackgrounds.getParameter<vstring>("categories");

  vstring processes_input = cfg_addBackgrounds.getParameter<vstring>("processes_input");
  std::string process_output = cfg_addBackgrounds.getParameter<std::string>("process_output");

  vstring central_or_shifts = cfg_addBackgrounds.getParameter<vstring>("sysShifts");
  bool contains_central = false;
  for ( auto central_or_shift: central_or_shifts )
  {
    if ( central_or_shift == "" || central_or_shift == "central" ) 
    {
      contains_central = true;
      break;
    }
  }
  if ( !contains_central ) 
  {
    central_or_shifts.push_back(""); // CV: add central value
  }

  int max_depth_recursion = cfg_addBackgrounds.exists("max_depth_recursion") ? cfg_addBackgrounds.getParameter<int>("max_depth_recursion") : -1;
  //int max_depth_recursion = cfg_addBackgrounds.getParameter<int>("max_depth_recursion");

  bool isDEBUG = cfg_addBackgrounds.exists("isDEBUG") ? cfg_addBackgrounds.getParameter<bool>("isDEBUG") : false;
  //bool isDEBUG = cfg_addBackgrounds.getParameter<bool>("isDEBUG");

  fwlite::InputSource inputFiles(cfg);
  if ( !(inputFiles.files().size() == 1) )
    throw cmsException(__func__, __LINE__) << "Exactly one input file expected";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  if ( categories.size() == 0 ) categories = getSubdirectoryNames(inputFile);

  for ( const std::string & category: categories )
  {
    std::cout << "processing category = " << category << std::endl;

    TDirectory* dir = getDirectory(inputFile, category, true);
    assert(dir);

    processSubdirectory_recursively(
      fs, dir, category, 
      processes_input, process_output, 
      central_or_shifts, 
      1, max_depth_recursion,
      isDEBUG
    );
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

  clock.Show("addBackgrounds2");

  std::cout << "returning exit code = " << EXIT_SUCCESS << " (EXIT_SUCCESS)." << std::endl;
  return EXIT_SUCCESS;
}
