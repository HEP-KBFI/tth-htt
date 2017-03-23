
/** \executable addBackgrounds
 *
 * Add "background" contributions of different MC samples.
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
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  std::vector<TDirectory*> getSubdirectories(TDirectory* dir)
  {
    std::vector<TDirectory*> subdirectories;
    TList* list = dir->GetListOfKeys();
    TIter next(list);
    TKey* key = 0;
    while ( (key = dynamic_cast<TKey*>(next())) ) {
      TObject* object = key->ReadObj();
      TDirectory* subdirectory = dynamic_cast<TDirectory*>(object);
      if ( subdirectory ) subdirectories.push_back(subdirectory);
    }
    return subdirectories;
  }

  vstring getSubdirectoryNames(TDirectory* dir)
  {
    std::vector<TDirectory*> subdirectories = getSubdirectories(dir);
    vstring subdirectoryNames;
    for ( std::vector<TDirectory*>::const_iterator subdirectory = subdirectories.begin();
	  subdirectory != subdirectories.end(); ++subdirectory ) {
      subdirectoryNames.push_back((*subdirectory)->GetName());
    }
    return subdirectoryNames;
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

  std::cout << "<addBackgrounds>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgrounds");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addBackgrounds") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddBackgrounds = cfg.getParameter<edm::ParameterSet>("addBackgrounds");

  vstring categories = cfgAddBackgrounds.getParameter<vstring>("categories");
  
  vstring processes_input = cfgAddBackgrounds.getParameter<vstring>("processes_input");
  std::string process_output = cfgAddBackgrounds.getParameter<std::string>("process_output");

  vstring central_or_shifts = cfgAddBackgrounds.getParameter<vstring>("sysShifts");
  central_or_shifts.push_back(""); // CV: add central value
  
  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addBackgrounds") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  if ( categories.size() == 0 ) categories = getSubdirectoryNames(inputFile);

  for ( vstring::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    
    TDirectory* dir = getDirectory(inputFile, *category, true);
    assert(dir);

    std::cout << "processing category = " << (*category) << std::endl;
	
    std::vector<TDirectory*> subdirs_level1 = getSubdirectories(dir);
    for ( std::vector<TDirectory*>::iterator subdir_level1 = subdirs_level1.begin();
	  subdir_level1 != subdirs_level1.end(); ++subdir_level1 ) {

      std::vector<TDirectory*> subdirs_level2 = getSubdirectories(*subdir_level1);
      for ( std::vector<TDirectory*>::iterator subdir_level2 = subdirs_level2.begin();
	  subdir_level2 != subdirs_level2.end(); ++subdir_level2 ) {

	std::cout << " processing directory = " << Form("%s/%s", (*subdir_level1)->GetName(), (*subdir_level2)->GetName()) << std::endl;

	std::string the_process_input = processes_input.front();

        TDirectory* dir_input = dynamic_cast<TDirectory*>((*subdir_level2)->Get(the_process_input.data()));
        if ( !dir_input ) {
          if ( the_process_input.find("ttH_htt") != std::string::npos ||
               the_process_input.find("ttH_hww") != std::string::npos ||
               the_process_input.find("ttH_hzz") != std::string::npos ) {
            continue;
          } 
	  if ( std::string((*subdir_level2)->GetName()).find("genEvt")  != std::string::npos ||
	       std::string((*subdir_level2)->GetName()).find("lheInfo") != std::string::npos ||
	       std::string((*subdir_level2)->GetName()).find("cutFlow") != std::string::npos ) {
	    continue;
	  }
	  throw cms::Exception("addBackgrounds") 
	    << "Failed to find subdirectory = " << the_process_input << " within directory = " << (*subdir_level2)->GetName() << " !!\n";
	  //std::cerr << "Failed to find subdirectory = " << the_process_input << " within directory = " << (*subdir_level2)->GetName() << " --> skipping !!" << std::endl;
	  //continue;
        }
        std::set<std::string> histograms;
        TList* list = dir_input->GetListOfKeys();
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
	  if ( histograms.find(histogramName.Data()) == histograms.end() ) {
	    std::cout << "adding histogram = " << histogramName.Data() << std::endl;
	    histograms.insert(histogramName.Data());
	  }
	}
	
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
	      TH1* histogram_input = getHistogram(*subdir_level2, *process_input, *histogram, *central_or_shift, enableException);
              if ( !histogram_input ) histogram_input = getHistogram(*subdir_level2, *process_input, *histogram, "", true);
	      histograms_input.push_back(histogram_input);
	    }

	    std::string subdirName_output = Form("%s/%s/%s/%s", category->data(), (*subdir_level1)->GetName(), (*subdir_level2)->GetName(), process_output.data());
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
    }
  }
  
  delete inputFile;

  clock.Show("addBackgrounds");

  return 0;
}
