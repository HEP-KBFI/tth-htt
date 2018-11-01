
/** \executable addSystDatacards
 *
 * Add specific shape systematics to the datacard,
 * e.g. CMS_ttHl_Clos_e_shapeUp/Down, CMS_ttHl_Clos_m_shapeUp/Down
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"

#include <TFile.h>
#include <TH1.h>
#include <TArrayD.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TPRegexp.h"
#include "TDirectory.h"
#include "TList.h"
#include "TKey.h"
#include "TObject.h"
#include "TString.h"

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  struct addSystType
  {
    addSystType(const edm::ParameterSet& cfg)
    {
      name_ = cfg.getParameter<std::string>("name");
      categories_ = cfg.getParameter<vstring>("categories");
      processes_ = cfg.getParameter<vstring>("processes");
      histogramsToFit_ = cfg.getParameter<vstring>("histogramsToFit");
      std::string inputFileName = cfg.getParameter<std::string>("inputFileName");
      LocalFileInPath inputFileName_fip(inputFileName);
      inputFileName_ = inputFileName_fip.fullPath();
      histogramName_ = cfg.getParameter<std::string>("histogramName");
    }
    ~addSystType() {}
    void print(std::ostream& stream) const
    {
      stream << "<addSystType>:" << std::endl;
      stream << " name = " << name_ << std::endl;
      stream << " categories = " << format_vstring(categories_) << std::endl;
      stream << " processes = " << format_vstring(processes_) << std::endl;
      stream << " histogramsToFit = " << format_vstring(histogramsToFit_) << std::endl;
      stream << " inputFileName = " << inputFileName_ << std::endl;
      stream << " histogramName = " << histogramName_ << std::endl;
    }
    std::string name_;
    vstring categories_;
    vstring processes_;
    vstring histogramsToFit_;
    std::string inputFileName_;
    std::string histogramName_;
  };

  bool isMatched(const vstring& names, const std::string& name_ref)
  {
    for ( vstring::const_iterator name = names.begin();
	  name != names.end(); ++name ) {
      if ( (*name) == name_ref ) return true;
    }
    return false;
  }

  TH1* copyHistogram(const TH1* histogram_input, const std::string& histogramName_output)
  {
    TH1* histogram_output = 0;
    const TAxis* xAxis = histogram_input->GetXaxis();
    if ( xAxis->GetXbins() ) histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXbins()->GetArray());
    else histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXmin(), xAxis->GetXmax());
    int numBins = xAxis->GetNbins();
    for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
      double binContent = histogram_input->GetBinContent(idxBin);
      histogram_output->SetBinContent(idxBin, binContent);
      double binError = histogram_input->GetBinError(idxBin);
      histogram_output->SetBinError(idxBin, binError);
    }
    return histogram_output;
  }

  double square(double x)
  {
    return x*x;
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

  std::cout << "<addSystDatacards>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addSystDatacards");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addSystDatacards") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addSystDatacards = cfg.getParameter<edm::ParameterSet>("addSystDatacards");
  
  std::string category = cfg_addSystDatacards.getParameter<std::string>("category");

  std::string histogramToFit = cfg_addSystDatacards.getParameter<std::string>("histogramToFit");

  std::vector<addSystType> addSystConfigs;
  edm::VParameterSet cfg_addSystConfigs = cfg_addSystDatacards.getParameter<edm::VParameterSet>("addSyst");
  for ( edm::VParameterSet::const_iterator cfgAddSystConfig = cfg_addSystConfigs.begin();
	cfgAddSystConfig != cfg_addSystConfigs.end(); ++cfgAddSystConfig ) {
    addSystConfigs.push_back(addSystType(*cfgAddSystConfig));
  }

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addSystDatacards") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
      
  // copy histograms that do not require modifications
  std::cout << "copying histograms that do not require modifications" << std::endl;
  TList* list1 = inputFile->GetListOfKeys();
  TIter next1(list1);
  TKey* key1 = 0;
  while ( (key1 = dynamic_cast<TKey*>(next1())) ) {
    TObject* object = key1->ReadObj();
    TH1* histogram_input = dynamic_cast<TH1*>(object);

    TFileDirectory* subdir_output = &fs;
    subdir_output->cd();
    
    copyHistogram(histogram_input, histogram_input->GetName());
  }

  // add histograms for specific shape systematics
  std::cout << "adding histograms for specific shape systematics" << std::endl;
  TList* list2 = inputFile->GetListOfKeys();
  TIter next2(list2);
  TKey* key2 = 0;
  while ( (key2 = dynamic_cast<TKey*>(next2())) ) {
    TObject* object = key2->ReadObj();
    TH1* histogram_input = dynamic_cast<TH1*>(object);
    //std::cout << "processing histogram = " << histogram_input->GetName() << std::endl;

    for ( std::vector<addSystType>::const_iterator addSystConfig = addSystConfigs.begin();
	  addSystConfig != addSystConfigs.end(); ++addSystConfig ) {

      //addSystConfig->print(std::cout);

      bool matchesCategory = isMatched(addSystConfig->categories_, category);
      //std::cout << "matchesCategory = " << matchesCategory << std::endl;
      if ( !matchesCategory ) continue;

      bool matchesHistogramToFit = isMatched(addSystConfig->histogramsToFit_, histogramToFit);
      //std::cout << "matchesHistogramToFit = " << matchesHistogramToFit << std::endl;
      if ( !matchesHistogramToFit ) continue;
      
      bool matchesProcess = false;
      for ( vstring::const_iterator process = addSystConfig->processes_.begin();
	    process != addSystConfig->processes_.end(); ++process ) {
	std::string histogramName_process = Form("x_%s", process->data());
	if ( histogramName_process == histogram_input->GetName() ) {
	  matchesProcess = true;
	  break;
	}
      }
      //std::cout << "matchesProcess = " << matchesProcess << std::endl;
      if ( !matchesProcess ) continue;
      
      TFile* inputFile_syst = new TFile(addSystConfig->inputFileName_.data());
      if ( !inputFile_syst ) 
	throw cms::Exception("addSystDatacards") 
	  << "Failed to open file = '" << addSystConfig->inputFileName_ << "' !!\n";
      
      TH1* histogram_syst = dynamic_cast<TH1*>(inputFile_syst->Get(addSystConfig->histogramName_.data()));
      if ( !histogram_syst ) 
	throw cms::Exception("addSystDatacards") 
	  << "Failed to load histogram = '" << addSystConfig->histogramName_ << "' from file = '" << addSystConfig->inputFileName_ << "' !!\n";
      
      TFileDirectory* subdir_output = &fs;
      subdir_output->cd();

      std::string histogramName_shiftUp = Form("%s_%sUp", histogram_input->GetName(), addSystConfig->name_.data());
      std::cout << "adding histogram = " << histogramName_shiftUp << std::endl;
      TH1* histogram_shiftUp = copyHistogram(histogram_input, histogramName_shiftUp.data());
      std::string histogramName_shiftDown = Form("%s_%sDown", histogram_input->GetName(), addSystConfig->name_.data());
      std::cout << "adding histogram = " << histogramName_shiftDown << std::endl;
      TH1* histogram_shiftDown = copyHistogram(histogram_input, histogramName_shiftDown.data());

      int numBins = histogram_input->GetNbinsX();
      for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
	double binContent_input = histogram_input->GetBinContent(idxBin);
	double binError_input = histogram_input->GetBinError(idxBin);

	double binContent_syst = histogram_syst->GetBinContent(idxBin);
	double binError_syst = histogram_syst->GetBinError(idxBin);

	double binContent_shiftUp = binContent_input + binContent_syst;
	histogram_shiftUp->SetBinContent(idxBin, binContent_shiftUp);
	double binError_shiftUp = TMath::Sqrt(square(binError_input) + square(binError_syst));
	histogram_shiftUp->SetBinError(idxBin, binError_shiftUp);

	double binContent_shiftDown = binContent_input - binContent_syst;
	histogram_shiftDown->SetBinContent(idxBin, binContent_shiftDown);
	double binError_shiftDown = binError_shiftUp;
	histogram_shiftDown->SetBinError(idxBin, binError_shiftDown);
      }

      makeBinContentsPositive(histogram_shiftUp, false, true);   // since we will be using this code only for MC 
      makeBinContentsPositive(histogram_shiftDown, false, true); // since we will be using this code only for MC 

      delete inputFile_syst;
    }
  }
  
  clock.Show("addSystDatacards");
  
  return 0;
}
