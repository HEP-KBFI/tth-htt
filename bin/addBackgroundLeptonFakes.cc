/** \executable addBackgroundLeptonFakes
 *
 * Compute shape templates and normalization for fake lepton background in 2lss_1tau and 2os_1tau channels.
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

  std::cout << "<addBackgroundLeptonFakes>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgroundLeptonFakes");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addBackgroundLeptonFakes") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddBackgroundLeptonFakes = cfg.getParameter<edm::ParameterSet>("addBackgroundLeptonFakes");
  
  std::vector<categoryEntryType*> categories;
  edm::VParameterSet cfgCategories = cfgAddBackgroundLeptonFakes.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
  }

  std::string processData = cfgAddBackgroundLeptonFakes.getParameter<std::string>("processData");
  std::string processLeptonFakes = cfgAddBackgroundLeptonFakes.getParameter<std::string>("processLeptonFakes");
  vstring processesToSubtract = cfgAddBackgroundLeptonFakes.getParameter<vstring>("processesToSubtract");

  bool disable_makeBinContentsPositive_forTailFit = cfgAddBackgroundLeptonFakes.getParameter<bool>("disable_makeBinContentsPositive_forTailFit");

  vstring central_or_shifts = cfgAddBackgroundLeptonFakes.getParameter<vstring>("sysShifts");
  bool contains_central_value = false;
  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
    if ( (*central_or_shift) == "" || (*central_or_shift) == "central" ) contains_central_value = true;
  }
  if ( !contains_central_value ) central_or_shifts.push_back(""); // CV: add central value

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addBackgroundLeptonFakes") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
  
  for ( std::vector<categoryEntryType*>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    std::cout << "processing category: signal = " << (*category)->signal_ << ", sideband = " << (*category)->sideband_ << std::endl;

    const TDirectory* dir_sideband = getDirectory(inputFile, (*category)->sideband_, true);
    assert(dir_sideband); 	

    std::vector<const TDirectory*> subdirs_sideband_level1 = getSubdirectories(dir_sideband);
    for ( std::vector<const TDirectory*>::iterator subdir_sideband_level1 = subdirs_sideband_level1.begin();
	  subdir_sideband_level1 != subdirs_sideband_level1.end(); ++subdir_sideband_level1 ) {
      std::vector<const TDirectory*> subdirs_sideband_level2 = getSubdirectories(*subdir_sideband_level1);
      for ( std::vector<const TDirectory*>::iterator subdir_sideband_level2 = subdirs_sideband_level2.begin();
	    subdir_sideband_level2 != subdirs_sideband_level2.end(); ++subdir_sideband_level2 ) {
	std::cout << " processing directory = " << Form("%s/%s", (*subdir_sideband_level1)->GetName(), (*subdir_sideband_level2)->GetName()) << std::endl;

        const TDirectory* dirData = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(*subdir_sideband_level2))->Get(processData.data()));
        if ( !dirData ) {
	  std::cout << "Failed to find subdirectory = " << processData << " within directory = " << (*subdir_sideband_level2)->GetName() << " --> skipping !!\n";
	  continue;
	}
        std::set<std::string> histograms;
        TList* list = dirData->GetListOfKeys();
        TIter next(list);
        TKey* key = 0;
	while ( (key = dynamic_cast<TKey*>(next())) ) {
	  TObject* object = key->ReadObj();
	  TH1* histogram = dynamic_cast<TH1*>(object);
	  if ( !histogram ) continue;
	  TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", processData.data()), "");
	  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
		central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
	    if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
	      histogramName = histogramName.ReplaceAll(Form("%s_", central_or_shift->data()), "");
	    }
	  }
	  if ( histogramName.Contains("CMS_") ) continue;
	  if ( histogramName.Contains("cutFlow") ) continue;
	  if ( histograms.find(histogramName.Data()) == histograms.end() ) {
	    std::cout << "adding histogram = " << histogramName.Data() << std::endl;
	    histograms.insert(histogramName.Data());
	  }
	}
	
	for ( std::set<std::string>::const_iterator histogram = histograms.begin();
	      histogram != histograms.end(); ++histogram ) {
	  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
		central_or_shift != central_or_shifts.end(); ++central_or_shift ) {

	    int verbosity = ( histogram->find("EventCounter") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	    //int verbosity = ( histogram->find("EventCounter") != std::string::npos ) ? 1 : 0;

	    TH1* histogramData = getHistogram(*subdir_sideband_level2, processData, *histogram, *central_or_shift, false);
	    if ( !histogramData ) {
	      histogramData = getHistogram(*subdir_sideband_level2, processData, *histogram, "central", true);
	    }
	    if ( verbosity ) {
	      std::cout << " integral(data_obs) = " << histogramData->Integral() << std::endl;
	    }
	    
	    std::vector<TH1*> histogramsToSubtract;
	    for ( vstring::const_iterator processToSubtract = processesToSubtract.begin();
		  processToSubtract != processesToSubtract.end(); ++processToSubtract ) {
	      TH1* histogramToSubtract = getHistogram(*subdir_sideband_level2, *processToSubtract, *histogram, *central_or_shift, false);
	      if ( !histogramToSubtract ) histogramToSubtract = getHistogram(*subdir_sideband_level2, *processToSubtract, *histogram, "central", true);
	      if ( verbosity ) {
		std::cout << " integral(" << (*processToSubtract) << ") = " << histogramToSubtract->Integral() << std::endl;
	      }
	      histogramsToSubtract.push_back(histogramToSubtract);
	    }
	    
	    std::string subdirName_output = Form("%s/%s/%s/%s", (*category)->signal_.data(), (*subdir_sideband_level1)->GetName(), (*subdir_sideband_level2)->GetName(), processLeptonFakes.data());
	    TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
	    subdir_output->cd();

	    std::string histogramNameLeptonFakes;
	    if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramNameLeptonFakes.append(*central_or_shift);
	    if ( histogramNameLeptonFakes.length() > 0 ) histogramNameLeptonFakes.append("_");
	    histogramNameLeptonFakes.append(*histogram);
	    TH1* histogramLeptonFakes = subtractHistograms(histogramNameLeptonFakes, histogramData, histogramsToSubtract, verbosity);
	    if ( verbosity ) {
	      std::cout << " integral(Fakes) = " << histogramLeptonFakes->Integral() << std::endl;
	    }

            if(!disable_makeBinContentsPositive_forTailFit){ makeBinContentsPositive(histogramLeptonFakes, false, verbosity); } // Treating histogramLeptonFakes as MC background	  

          }
	}
      }
    }
  }
  
  //---------------------------------------------------------------------------------------------------
  // CV: Add (dummy) histograms for number of analyzed and processed events
  //     This is needed to avoid run-time errors/warnings when executing python/commands/get_events_count.py (called by python/sbatch-node.template.hadd.sh)
  fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  //---------------------------------------------------------------------------------------------------

  delete inputFile;

  clock.Show("addBackgroundLeptonFakes");

  return EXIT_SUCCESS;
}
