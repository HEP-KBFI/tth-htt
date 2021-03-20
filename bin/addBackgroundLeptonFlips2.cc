
/** \executable addBackgroundLeptonFlips
 *
 * Compute shape templates and normalization for background due to charge misidentification in 2lss_1tau channel.
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

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h" // getSubdirectories

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
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
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {	
      signal_ = cfg.getParameter<std::string>("signal");
      sideband_ = cfg.getParameter<std::string>("sideband");
    }
    ~categoryEntryType() {}
    std::string signal_;
    std::string sideband_;
  };
  
  void processSubdirectory_recursively(TFileDirectory& fs, 
                                       const TDirectory* dir, const std::string& dirName, 
                                       const std::string& processData, const std::string& processLeptonFlips, const vstring& processesToSubtract,
                                       const vstring& central_or_shifts,
                                       bool makeBinContentsPositive_dir,
                                       int depth_recursion, int max_depth_recursion,
                                       bool isDEBUG = false)
  {
    if ( isDEBUG )
    {
      std::cout << "<processSubdirectory_recursively>:" << std::endl;
      std::cout << " dir = '" << dirName << "'" << std::endl;
    }

    // check if directory given as function argument contains subdirectories for input processes
    vstring processes_input;
    processes_input.push_back(processData);
    processes_input.insert(processes_input.end(), processesToSubtract.begin(), processesToSubtract.end());
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
      const TDirectory* subdirData = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(processData.data()));      
      assert(subdirData);
      //subdirData->ls();
      
      std::set<std::string> histogramNames;
      TList* list = subdirData->GetListOfKeys();
      TIter next(list);
      TKey* key = 0;
      while ( (key = dynamic_cast<TKey*>(next())) ) {
        TObject* object = key->ReadObj();
        TH1* histogram = dynamic_cast<TH1*>(object);
        if ( !histogram ) continue;
        TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", processData.data()), "");
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
          int verbosity = ( histogramName.find("EventCounter") != std::string::npos && (central_or_shift == "" || central_or_shift == "central") ) ? 1 : 0;
	  //int verbosity = ( histogramName.find("EventCounter") != std::string::npos ) ? 1 : 0;
          //if ( histogramName.find("sumXY") != std::string::npos ) verbosity = 1;

	  TH1* histogramData = getHistogram(dir, processData, histogramName, central_or_shift, false);
	  if ( !histogramData ) 
          {
	    histogramData = getHistogram(dir, processData, histogramName, "central", true);
	  }
	  if ( verbosity )
          {
            double integral = compIntegral(histogramData, false, false);
            double integralErr = compIntegralErr(histogramData, false, false);
	    std::cout << " integral(data_obs) = " << integral << " +/- " << integralErr << std::endl;
	  }
	    
	  std::vector<TH1*> histogramsToSubtract;
	  for ( auto processToSubtract: processesToSubtract )
          {
	    TH1* histogramToSubtract = getHistogram(dir, processToSubtract, histogramName, central_or_shift, false);
	    if ( !histogramToSubtract ) 
            {
              histogramToSubtract = getHistogram(dir, processToSubtract, histogramName, "central", true);
            }
	    if ( verbosity )
            {
              double integral = compIntegral(histogramToSubtract, false, false);
              double integralErr = compIntegralErr(histogramToSubtract, false, false);
              std::cout << " integral(" << processToSubtract << ") = " << integral << " +/- " << integralErr << std::endl;
	    }
            histogramsToSubtract.push_back(histogramToSubtract);
          }
	    
          std::string subdirName_output = Form("%s/%s", dirName.data(), processLeptonFlips.data());
          if ( isDEBUG )
          {
            std::cout << "creating subdirectory = '" << subdirName_output << "'" << std::endl;
          }
          TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
          subdir_output->cd();

          std::string histogramNameLeptonFlips;
          if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramNameLeptonFlips.append(central_or_shift);
          if ( histogramNameLeptonFlips.length() > 0 ) histogramNameLeptonFlips.append("_");
          histogramNameLeptonFlips.append(histogramName);
          TH1* histogramLeptonFlips = subtractHistograms(histogramNameLeptonFlips, histogramData, histogramsToSubtract, verbosity);
          if ( verbosity )
          {
            double integral = compIntegral(histogramLeptonFlips, false, false);
            double integralErr = compIntegralErr(histogramLeptonFlips, false, false);
	    std::cout << " integral(Flips) = " << integral << " +/- " << integralErr << std::endl;
          }

          if( makeBinContentsPositive_dir )
          {
            makeBinContentsPositive(histogramLeptonFlips, false, verbosity); // Treating histogramLeptonFlips as MC background
          }
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
        bool makeBinContentsPositive_subdir = makeBinContentsPositive_dir;
        if ( std::string((*subdir)->GetName()).find("mvaInputVarCorrelation") != std::string::npos ) 
        {
          makeBinContentsPositive_subdir = false;
        }
        processSubdirectory_recursively(
          fs, *subdir, dirName + "/" + (*subdir)->GetName(), 
          processData, processLeptonFlips, processesToSubtract, 
          central_or_shifts, 
          makeBinContentsPositive_subdir,
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

  std::cout << "<addBackgroundLeptonFlips2>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgroundLeptonFlips2");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addBackgroundLeptonFlips") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addBackgroundLeptonFlips = cfg.getParameter<edm::ParameterSet>("addBackgroundLeptonFlips");
  
  std::vector<categoryEntryType*> categories;
  edm::VParameterSet cfgCategories = cfg_addBackgroundLeptonFlips.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
  }

  std::string processData = cfg_addBackgroundLeptonFlips.getParameter<std::string>("processData");
  std::string processLeptonFlips = cfg_addBackgroundLeptonFlips.getParameter<std::string>("processLeptonFlips");
  vstring processesToSubtract = cfg_addBackgroundLeptonFlips.getParameter<vstring>("processesToSubtract");

  const bool makeBinContentsPositive_forTailFit = ( cfg_addBackgroundLeptonFlips.exists("makeBinContentsPositive_forTailFit") ) ? 
    cfg_addBackgroundLeptonFlips.getParameter<bool>("makeBinContentsPositive_forTailFit") : false;

  vstring central_or_shifts = cfg_addBackgroundLeptonFlips.getParameter<vstring>("sysShifts");
  bool contains_central_value = false;
  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
    if ( (*central_or_shift) == "" || (*central_or_shift) == "central" ) contains_central_value = true;
  }
  if ( !contains_central_value ) central_or_shifts.push_back(""); // CV: add central value
  
  int max_depth_recursion = cfg_addBackgroundLeptonFlips.exists("max_depth_recursion") ? cfg_addBackgroundLeptonFlips.getParameter<int>("max_depth_recursion") : -1;
  //int max_depth_recursion = cfg_addBackgroundLeptonFlips.getParameter<int>("max_depth_recursion");

  bool isDEBUG = cfg_addBackgroundLeptonFlips.exists("isDEBUG") ? cfg_addBackgroundLeptonFlips.getParameter<bool>("isDEBUG") : false;
  //bool isDEBUG = cfg_addBackgroundLeptonFlips.getParameter<bool>("isDEBUG");

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addBackgroundLeptonFlips") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
  
   for ( auto category: categories )
  {
    std::cout << "processing category: signal = " << category->signal_ << ", sideband = " << category->sideband_ << std::endl;

    const TDirectory* dir_sideband = getDirectory(inputFile, category->sideband_, true);
    assert(dir_sideband); 	

    processSubdirectory_recursively(
      fs, dir_sideband, category->signal_,
      processData, processLeptonFlips, processesToSubtract,
      central_or_shifts,
      makeBinContentsPositive_forTailFit,
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

  delete inputFile;

  clock.Show("addBackgroundLeptonFlips2");

  return EXIT_SUCCESS;
}
