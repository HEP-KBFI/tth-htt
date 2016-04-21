
/** \executable prepareDatacards
 *
 * Prepare datacards for ttH, H->tautau analysis
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
#include <TArrayD.h>
#include <TBenchmark.h>
#include <TMath.h>
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
  void copyHistogram(TDirectory* dir_input, const std::string& process, const std::string& histogramName_input, 
		     const std::string& histogramName_output, double sf, double setBinsToZeroBelow, int rebin, const std::string& central_or_shift, bool enableException)
  {
    //std::cout << "<copyHistogram>:" << std::endl;
    //std::cout << " dir_input = " << dir_input->GetName() << std::endl;
    //std::cout << " process = " << process << std::endl;
    //std::cout << " histogramName_input = " << histogramName_input << std::endl;
    //std::cout << " histogramName_output = " << histogramName_output << std::endl;
    //std::cout << " central_or_shift = " << central_or_shift << std::endl;
    //std::cout << " enableException = " << enableException << std::endl;
    std::string histogramName_input_full = process;
    if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramName_input_full.append("_").append(central_or_shift);
    histogramName_input_full.append("_").append(histogramName_input);
    TH1* histogram_input = dynamic_cast<TH1*>(dir_input->Get(histogramName_input_full.data()));
    if ( !histogram_input ) {
      if ( enableException ) 
	throw cms::Exception("copyHistogram")
	  << "Failed to find histogram = " << histogramName_input_full << " in directory = " << dir_input->GetName() << " !!\n";
      return;
    }   
    std::cout << " integral(" << process << ") = " << histogram_input->Integral() << std::endl;
    std::string histogramName_output_full = process;
    if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramName_output_full.append("_").append(central_or_shift);
    if ( histogramName_output != "" ) histogramName_output_full.append("_").append(histogramName_output);
    TArrayD histogramBinning = getBinning(histogram_input);
    int numBins = histogramBinning.GetSize() - 1;
    TH1* histogram_output = new TH1F(histogramName_output_full.data(), histogramName_output_full.data(), numBins, histogramBinning.GetArray());
    if ( !histogram_output->GetSumw2N() ) histogram_output->Sumw2();
    for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
      double binContent = sf*histogram_input->GetBinContent(iBin);
      histogram_output->SetBinContent(iBin, binContent);
      double binError = sf*histogram_input->GetBinError(iBin);
      histogram_output->SetBinError(iBin, binError);
      // CV: set underflow, overflow and all bins below given threshold (use 50 GeV for SVfit mass) to zero
      double binCenter = histogram_input->GetBinCenter(iBin);
      if ( iBin == 0 || binCenter < setBinsToZeroBelow || iBin == (numBins + 1) ) {
	histogram_output->SetBinContent(iBin, 0.);
	histogram_output->SetBinError(iBin, 0.);
      }
      if ( rebin > 1 ) {
	histogram_output->Rebin(rebin);
      }
    }
  }
    
  std::string getSubdirNameOutput(const std::string& category) 
  {
    std::string subdirName_output = Form("tauTau_%s", category.data());
    return subdirName_output;
  }

  struct categoryType
  {
    categoryType(const edm::ParameterSet& cfg)
    {
      input_ = cfg.getParameter<std::string>("input");
      output_ = cfg.getParameter<std::string>("output");
    }
    ~categoryType() {}
    std::string input_;
    std::string output_;
  };
}

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  std::cout << "<prepareDatacards>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("prepareDatacards");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("prepareDatacards") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_prepareDatacards = cfg.getParameter<edm::ParameterSet>("prepareDatacards");
  
  vstring processesToCopy_string = cfg_prepareDatacards.getParameter<vstring>("processesToCopy");
  std::vector<TPRegexp*> processesToCopy;
  for ( vstring::const_iterator processToCopy_string = processesToCopy_string.begin();
	processToCopy_string != processesToCopy_string.end(); ++processToCopy_string ) {
    TPRegexp* processToCopy = new TPRegexp(processToCopy_string->data());
    processesToCopy.push_back(processToCopy);
  }
  
  double sf_signal = cfg_prepareDatacards.getParameter<double>("sf_signal");
  vstring signals_string = cfg_prepareDatacards.getParameter<vstring>("signals");
  std::vector<TPRegexp*> signals;
  for ( vstring::const_iterator signal_string = signals_string.begin();
	signal_string != signals_string.end(); ++signal_string ) {
    TPRegexp* signal = new TPRegexp(signal_string->data());
    signals.push_back(signal);
  }

  std::vector<categoryType> categories;
  edm::VParameterSet cfg_categories = cfg_prepareDatacards.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfg_categories.begin();
	cfgCategory != cfg_categories.end(); ++cfgCategory ) {
    categories.push_back(categoryType(*cfgCategory));
  }
  
  std::string histogramToFit = cfg_prepareDatacards.getParameter<std::string>("histogramToFit");
  int histogramToFit_rebin = cfg_prepareDatacards.getParameter<int>("histogramToFit_rebin");

  double setBinsToZeroBelow = cfg_prepareDatacards.getParameter<double>("setBinsToZeroBelow");

  vstring central_or_shifts = cfg_prepareDatacards.getParameter<vstring>("sysShifts");
  central_or_shifts.push_back(""); // CV: add central value

  std::vector<TH1*> histogramsForDatacards;

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("prepareDatacards") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  for ( std::vector<categoryType>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
      std::cout << "processing category = " << category->input_ << std::endl;
      
      TDirectory* dir = getDirectory(inputFile, category->input_, true);
      assert(dir);
      
      // copy histograms that do not require modifications
      std::cout << "copying histograms that do not require modifications" << std::endl;
      TList* list = dir->GetListOfKeys();
      TIter next(list);
      TKey* key = 0;
      while ( (key = dynamic_cast<TKey*>(next())) ) {
	TObject* object = key->ReadObj();
	TDirectory* subdir = dynamic_cast<TDirectory*>(object);
	if ( !subdir ) continue;
	bool isToCopy = false;
	for ( std::vector<TPRegexp*>::iterator processToCopy = processesToCopy.begin();
	      processToCopy != processesToCopy.end(); ++processToCopy ) {
	  if ( (*processToCopy)->Match(subdir->GetName()) ) isToCopy = true;
	}
	bool isSignal = false;
	for ( std::vector<TPRegexp*>::iterator signal = signals.begin();
	      signal != signals.end(); ++signal ) {
	  if ( (*signal)->Match(subdir->GetName()) ) isSignal = true;
	}
	if ( isToCopy ) {
	  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
		central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
	    std::cout << "histogramToFit = " << histogramToFit << ", central_or_shift = " << (*central_or_shift) << std::endl;
	    
	    std::string subdirName_output = getSubdirNameOutput(category->output_);
	    TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
	    subdir_output->cd();
	    double sf = ( isSignal ) ? sf_signal : 1.;
	    copyHistogram(
	      subdir, subdir->GetName(), histogramToFit, "", 
	      sf, setBinsToZeroBelow, histogramToFit_rebin, *central_or_shift, (*central_or_shift) == "" || (*central_or_shift) == "central");	      
	  }
	}
      }
  }
  
  delete inputFile;

  clock.Show("prepareDatacards");

  return 0;
}
