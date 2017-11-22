/** \executable prepareDatacards
 *
 * Prepare datacards for ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
cfg_prepareDatacards 
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin 


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
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <assert.h>

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;


namespace
{
  std::vector<double> compBinning(TH1* histogram, double minEvents)
  {
    std::vector<double> histogramBinning;
    const TAxis* xAxis = histogram->GetXaxis();
    histogramBinning.push_back(xAxis->GetBinLowEdge(1));
    double sumEvents = 0.;
    int numBins = xAxis->GetNbins();
    for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
      sumEvents += histogram->GetBinContent(idxBin);
      if ( sumEvents >= minEvents ) {
	histogramBinning.push_back(xAxis->GetBinUpEdge(idxBin));
	sumEvents = 0.;
      }
    }
    if ( TMath::Abs(histogramBinning.back() - xAxis->GetBinUpEdge(numBins)) > 1.e-3 ) {
      if ( histogramBinning.size() >= 2 ) histogramBinning.back() = xAxis->GetBinUpEdge(numBins);
      else histogramBinning.push_back(xAxis->GetBinUpEdge(numBins));
    }
    assert(histogramBinning.size() >= 2);
    return histogramBinning;
  }
  
  TH1* rebinHistogram(const std::vector<double>& histogramBinning, const TH1* histogram)
  {
    TArrayF histogramBinning_array(histogramBinning.size());
    int idx = 0;
    for ( std::vector<double>::const_iterator binEdge = histogramBinning.begin();
	  binEdge != histogramBinning.end(); ++binEdge ) {
      histogramBinning_array[idx] = (*binEdge);
      ++idx;
    }
    std::string histogramName = Form("%s_rebinned", histogram->GetName());
    std::string histogramTitle = histogram->GetTitle();
    int numBins_rebinned = histogramBinning_array.GetSize() - 1;
    //std::cout << "numBins_rebinned = " << numBins_rebinned << std::endl;
    TH1* histogram_rebinned = new TH1D(histogramName.data(), histogramTitle.data(), numBins_rebinned, histogramBinning_array.GetArray());
    if ( !histogram_rebinned->GetSumw2N() ) histogram_rebinned->Sumw2();
    const TAxis* xAxis = histogram->GetXaxis();
    int numBins = xAxis->GetNbins();
    const TAxis* xAxis_rebinned = histogram_rebinned->GetXaxis();
    double binContentSum = 0.;
    double binError2Sum = 0.;
    int iBin_rebinned = 1;
    double binEdgeLow_rebinned = xAxis_rebinned->GetBinLowEdge(iBin_rebinned);
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double binCenter = xAxis->GetBinCenter(iBin);
      double binContent = histogram->GetBinContent(iBin);
      double binError = histogram->GetBinError(iBin);
      bool isNextBin_rebinned = false;
      if ( iBin == numBins ) {
	isNextBin_rebinned = true;
      } else {
	if ( iBin_rebinned < numBins_rebinned && binCenter > xAxis_rebinned->GetBinLowEdge(iBin_rebinned + 1) ) {
	  isNextBin_rebinned = true;
	}
      }
      if ( isNextBin_rebinned ) {
	double binWidth_rebinned = xAxis_rebinned->GetBinLowEdge(iBin_rebinned + 1) - binEdgeLow_rebinned;
	histogram_rebinned->SetBinContent(iBin_rebinned, binContentSum/binWidth_rebinned);
	histogram_rebinned->SetBinError(iBin_rebinned, TMath::Sqrt(binError2Sum)/binWidth_rebinned);
	binContentSum = 0.;
	binError2Sum = 0.;
	binEdgeLow_rebinned = xAxis_rebinned->GetBinLowEdge(iBin_rebinned + 1);
	++iBin_rebinned;
      }
      //std::cout << "binCenter = " << binCenter << ": iBin = " << iBin << ", iBin_rebinned = " << iBin_rebinned << std::endl;
      binContentSum += binContent;
      binError2Sum += (binError*binError);
    }
    return histogram_rebinned;
  } 

  TH1* copyHistogram(TDirectory* dir_input, const std::string& process, const std::string& histogramName_input, 
		     const std::string& histogramName_output, double sf, double setBinsToZeroBelow, int rebin, const std::string& central_or_shift, 
		     bool enableException, bool setEmptySystematicFromCentral = true)
  {
    std::cout << "<copyHistogram>:" << std::endl;
    std::cout << " dir_input = " << dir_input->GetName() << std::endl;
    std::cout << " process = " << process << std::endl;
    std::cout << " histogramName_input = " << histogramName_input << std::endl;
    std::cout << " histogramName_output = " << histogramName_output << std::endl;
    std::cout << " central_or_shift = " << central_or_shift << std::endl;
    std::cout << " enableException = " << enableException << std::endl;

    std::string histogramName_input_full = "";
    if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramName_input_full.append(central_or_shift);
    if( histogramName_input_full != "" ) histogramName_input_full.append("_");
    histogramName_input_full.append(histogramName_input);
    TH1* histogram_input = dynamic_cast<TH1*>(dir_input->Get(histogramName_input_full.data()));
    if ( !histogram_input ) {
      if ( enableException ) 
	throw cms::Exception("copyHistogram")
	  << "Failed to find histogram = " << histogramName_input_full << " in directory = " << dir_input->GetName() << " !!\n";
      return 0;
    }   
    std::cout << " integral(" << process << ") = " << histogram_input->Integral() << std::endl;
    // std::string histogramName_output_full = std::string("x").append("_").append(process); // DEF LINE
    std::string histogramName_output_full = process; // MY LINE
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
    }
    
    //If systematic variation has zero events, but central >0
    if ( setEmptySystematicFromCentral && !(central_or_shift == "" || central_or_shift == "central") && histogram_input->Integral() == 0 ) {
      TH1* histogram_central = dynamic_cast<TH1*>(dir_input->Get(histogramName_input.data()));
      if (histogram_central->GetEntries() > 0){
	for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
	  double binContent = 0.1*sf*histogram_central->GetBinContent(iBin);
	  histogram_output->SetBinContent(iBin, binContent);
	  double binError = sf*histogram_input->GetBinError(iBin);
	  binError = sqrt(binError*binError + binContent*binContent);
	  histogram_output->SetBinError(iBin, binError);
	  // CV: set underflow, overflow and all bins below given threshold (use 50 GeV for SVfit mass) to zero
	  double binCenter = histogram_input->GetBinCenter(iBin);
	  if ( iBin == 0 || binCenter < setBinsToZeroBelow || iBin == (numBins + 1) ) {
	    histogram_output->SetBinContent(iBin, 0.);
	    histogram_output->SetBinError(iBin, 0.);
	  }
	}
      }
    }
    
    if ( rebin > 1 ) {
      histogram_output->Rebin(rebin);
    }    

    return histogram_output;
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

  bool compMatch(const std::string& s, TPRegexp* pattern)
  {
    bool isMatched = false;
    if ( pattern->Match(s.data()) ) {
      TObjArray* matches = pattern->MatchS(s.data());
      int numMatches = matches->GetEntries();
      for ( int idxMatch = 0; idxMatch < numMatches; ++idxMatch ) {
	TObjString* s_matched = dynamic_cast<TObjString*>(matches->At(idxMatch));
	assert(s_matched); 
	if ( std::string(s_matched->GetString().Data()).size() == s.size() ) {
	  isMatched = true;
	  break;
	}
      }
      delete matches;
    }
    return isMatched;
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

  TPRegexp* data = new TPRegexp("data_obs");

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

  bool apply_automatic_rebinning = cfg_prepareDatacards.getParameter<bool>("apply_automatic_rebinning");
  double minEvents_automatic_rebinning = cfg_prepareDatacards.getParameter<double>("minEvents_automatic_rebinning");

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
    TH1* histogramBackgroundSum = 0;
    std::vector<TH1*> histogramsToRebin;
    while ( (key = dynamic_cast<TKey*>(next())) ) {
      TObject* object = key->ReadObj();
      TDirectory* subdir = dynamic_cast<TDirectory*>(object);
      if ( !subdir ) continue;
      std::cout << "subdir = " << subdir->GetName() << std::endl;
      bool isToCopy = false;
      for ( std::vector<TPRegexp*>::iterator processToCopy = processesToCopy.begin();
	    processToCopy != processesToCopy.end(); ++processToCopy ) {
	bool isMatched = compMatch(subdir->GetName(), *processToCopy);
	if ( isMatched ) {
	  std::cout << " matches processToCopy = " << (*processToCopy)->GetPattern() << std::endl;
	  isToCopy = true;
	} else {
	  std::cout << " does not match processToCopy = " << (*processToCopy)->GetPattern() << std::endl;
	}
      }
      bool isSignal = false;
      for ( std::vector<TPRegexp*>::iterator signal = signals.begin();
	    signal != signals.end(); ++signal ) {
	bool isMatched = compMatch(subdir->GetName(), *signal);
	if ( isMatched ) {
	  std::cout << " matches signal = " << (*signal)->GetPattern() << std::endl;
	  isSignal = true;
	} else {
	  std::cout << " does not match signal = " << (*signal)->GetPattern() << std::endl;
	}
      }
      if ( isToCopy || isSignal ) {
	for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	      central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
	  std::cout << "histogramToFit = " << histogramToFit << ", central_or_shift = " << (*central_or_shift) << std::endl;
	  
	  TFileDirectory* subdir_output = &fs;
	  subdir_output->cd();
	  //Make subdirectory if given
	  bool makeSubDir = cfg_prepareDatacards.getParameter<bool>("makeSubDir");
	  if ( makeSubDir == true && category->output_.length() > 0 ){
	    TDirectory* subsubdir_output = createSubdirectory_recursively(fs, category->output_);
	    subsubdir_output->cd();
	  }
	  double sf = ( isSignal ) ? sf_signal : 1.;
	  TH1* histogram = copyHistogram(
	    subdir, subdir->GetName(), histogramToFit, "", 
	    sf, setBinsToZeroBelow, histogramToFit_rebin, *central_or_shift, (*central_or_shift) == "" || (*central_or_shift) == "central");	  
	  if (!histogram) continue;
	  assert(histogram);
	  bool isData = compMatch(subdir->GetName(), data);
	  if ( !(isData || isSignal) ) {
	    if   ( !histogramBackgroundSum ) histogramBackgroundSum = (TH1*)histogram->Clone(Form("%s_BackgroundSum", category->input_.data()));
	    else                             histogramBackgroundSum->Add(histogram);  	    
	  }
	  histogramsToRebin.push_back(histogram);
	}
      }
    }

    if ( apply_automatic_rebinning ) {
      // rebin histograms to avoid bins with zero background
      assert(histogramBackgroundSum);
      std::vector<double> histogramBinning = compBinning(histogramBackgroundSum, minEvents_automatic_rebinning);
      for ( std::vector<TH1*>::iterator histogram = histogramsToRebin.begin();
	    histogram != histogramsToRebin.end(); ++histogram ) {
	rebinHistogram(histogramBinning, *histogram);
      }
    }

    delete histogramBackgroundSum;
  }
  
  delete inputFile;

  clock.Show("prepareDatacards");
  
  return EXIT_SUCCESS;
}
