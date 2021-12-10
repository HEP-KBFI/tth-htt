/** \executable prepareDatacards
 *
 * Prepare datacards for ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
cfg_prepareDatacards
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

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // compIntegral(), getTArraDfromVector(), histogramEntryType_private()
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin(), getPtBin()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

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

  double square(double x)
  {
    return x*x;
  }
  template<typename T>
  T* copyHistogram(TDirectory* dir_input, const std::string& process, const std::string& histogramName_input,
		     const std::string& histogramName_output, double sf, double xMin, double xMax, int rebin, const std::string& central_or_shift,
		     bool enableException, bool setEmptySystematicFromCentral = true)
  {
    //std::cout << "<copyHistogram>:" << std::endl;
    //std::cout << " dir_input = " << dir_input->GetName() << std::endl;
    //std::cout << " process = " << process << std::endl;
    //std::cout << " histogramName_input = " << histogramName_input << std::endl;
    //std::cout << " histogramName_output = " << histogramName_output << std::endl;
    //std::cout << " central_or_shift = " << central_or_shift << std::endl;
    //std::cout << " enableException = " << enableException << std::endl;

    std::string histogramName_input_full = "";
    if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramName_input_full.append(central_or_shift);
    if( histogramName_input_full != "" ) histogramName_input_full.append("_");
    histogramName_input_full.append(histogramName_input);
    std::cout<< "histogramName_input_full: " << histogramName_input_full << std::endl;

    T* histogram_input = dynamic_cast<T*>(dir_input->Get(histogramName_input_full.data()));
    if ( !histogram_input ) {
      if ( enableException )
	throw cms::Exception("copyHistogram")
	  << "Failed to find histogram = '" << histogramName_input_full << "' in directory = '" << dir_input->GetName() << "' !!\n";
      return 0;
    }
    std::cout << " integral(" << process << ") = " << histogram_input->Integral() << std::endl;

    // special treatment for the case that systematic variation has zero events, but central value > 0
    bool isSystematicFromCentral = false;
    if ( setEmptySystematicFromCentral && !(central_or_shift == "" || central_or_shift == "central") && histogram_input->GetEntries() == 0 ) {
      T* histogram_central = dynamic_cast<T*>(dir_input->Get(histogramName_input.data()));
      if ( histogram_central->GetEntries() > 0 ) {
	histogram_input = histogram_central;
	isSystematicFromCentral = true;
      }
    }

    TArrayD histogramBinning_xaxisinput = getBinning_axis(histogram_input->GetXaxis());
    int numBins_xinput = histogramBinning_xaxisinput.GetSize() - 1;
    const TAxis* xAxis_input = histogram_input->GetXaxis();

    TArrayD histogramBinning_yaxisinput;
    int numBins_yinput(-1);
    const TAxis* yAxis_input(NULL);
    bool isHistogram2d = ( histogram_input->GetDimension() == 2 ) ? true : false;
    if ( isHistogram2d )
    {
      histogramBinning_yaxisinput = getBinning_axis(histogram_input->GetYaxis());
      numBins_yinput = histogramBinning_yaxisinput.GetSize() - 1;
      yAxis_input = histogram_input->GetYaxis();
    }

    // std::string histogramName_output_full = std::string("x").append("_").append(process);
    std::string histogramName_output_full = process;
    if ( !(central_or_shift == "" || central_or_shift == "central") ) histogramName_output_full.append("_").append(central_or_shift);
    if ( histogramName_output != "" ) histogramName_output_full.append("_").append(histogramName_output);

    TArrayD histogramBinning_xoutput = getBinning_axis(histogram_input->GetXaxis(), xMin, xMax);
    int numBins_xoutput = histogramBinning_xoutput.GetSize() - 1;
    TArrayD histogramBinning_youtput;
    int numBins_youtput(0);
    if ( isHistogram2d )
    {
      histogramBinning_youtput = getBinning_axis(histogram_input->GetYaxis());
      numBins_youtput = histogramBinning_youtput.GetSize() - 1;
    }

    T* histogram_output(NULL);
    if ( !isHistogram2d )
    {
      TH1* histogram_1d = new TH1F(histogramName_output_full.data(), histogramName_output_full.data(), numBins_xoutput, histogramBinning_xoutput.GetArray());
      histogram_output = dynamic_cast<T*>(histogram_1d);
    }
    else
    {
      TH2* histogram_2d = new TH2F(histogramName_output_full.data(), histogramName_output_full.data(), numBins_xoutput, histogramBinning_xoutput.GetArray(), numBins_youtput, histogramBinning_youtput.GetArray());
      histogram_output = dynamic_cast<T*>(histogram_2d);
    }

    if ( !histogram_output->GetSumw2N() ) histogram_output->Sumw2();
    const TAxis* xAxis_output = histogram_output->GetXaxis();
    const TAxis* yAxis_output(NULL);
    if ( isHistogram2d )
    yAxis_output = histogram_output->GetYaxis();

    double binContent_output_underflow = 0.;
    double binErr2_output_underflow = 0.;
    double binContent_output_overflow = 0.;
    double binErr2_output_overflow = 0.;
    for ( int idxBin_xinput = 0; idxBin_xinput <= (numBins_xinput + 1); ++idxBin_xinput ) {
      for ( int idxBin_yinput = 0; idxBin_yinput <= (numBins_yinput + 1); ++idxBin_yinput ) {
        double binContent_input, binError_input;
        if ( isSystematicFromCentral ) {
          if (isHistogram2d)
          {
            binContent_input = 0.1*sf*histogram_input->GetBinContent(idxBin_xinput, idxBin_yinput);
            binError_input = sf*histogram_input->GetBinError(idxBin_xinput, idxBin_yinput);
            binError_input = TMath::Sqrt(binError_input*binError_input + binContent_input*binContent_input);
          }
          else
          {
            assert(idxBin_yinput == 0);
            binContent_input = 0.1*sf*histogram_input->GetBinContent(idxBin_xinput);
            binError_input = sf*histogram_input->GetBinError(idxBin_xinput);
            binError_input = TMath::Sqrt(binError_input*binError_input + binContent_input*binContent_input);
          }
        }
        else
        {
          if ( !isHistogram2d )
          {
            assert(idxBin_yinput == 0);
            binContent_input = sf*histogram_input->GetBinContent(idxBin_xinput);
            binError_input = sf*histogram_input->GetBinError(idxBin_xinput);
          }
          else
          {
            binContent_input = sf*histogram_input->GetBinContent(idxBin_xinput, idxBin_yinput);
            binError_input = sf*histogram_input->GetBinError(idxBin_xinput, idxBin_yinput);
          }
        }
        if ( !isHistogram2d ) {
          assert(idxBin_yinput == 0);
          if ( idxBin_xinput >= 1 && idxBin_xinput <= numBins_xinput ) {
            double binCenter_input = xAxis_input->GetBinCenter(idxBin_xinput);
            if ( !((xMin == -1. || binCenter_input > xMin) && (xMax == -1. || binCenter_input < xMax)) ) continue;
            int idxBin_output = xAxis_output->FindBin(binCenter_input);
            if ( idxBin_output >= 1 && idxBin_output <= numBins_xoutput ) {
              histogram_output->SetBinContent(idxBin_output, binContent_input);
              histogram_output->SetBinError(idxBin_output, binError_input);
            } else if ( idxBin_output == 0 ) { // "regular" bin of input histogram, which corresponds to underflow bin of output histogram
              binContent_output_underflow += binContent_input;
              binErr2_output_underflow += square(binError_input);
            } else if ( idxBin_output == (numBins_xinput + 1) ) { // "regular" bin of input histogram, which corresponds to overflow bin of output histogram
              binContent_output_overflow += binContent_input;
              binErr2_output_overflow += square(binError_input);
            } else assert(0);
          } else if ( idxBin_xinput == 0 ) { // underflow bin of input histogram, which corresponds to underflow bin of output histogram
            binContent_output_underflow += binContent_input;
            binErr2_output_underflow += square(binError_input);
          } else if ( idxBin_xinput == (numBins_xinput + 1) ) { // overflow bin of input histogram, which corresponds to overflow bin of output histogram
            binContent_output_overflow += binContent_input;
            binErr2_output_overflow += square(binError_input);
          } else assert(0);
        }
        else {
          double binCenter_xinput = xAxis_input->GetBinCenter(idxBin_xinput);
          double binCenter_yinput = yAxis_input->GetBinCenter(idxBin_yinput);
          int idxBin_xoutput = xAxis_output->FindBin(binCenter_xinput);
          int idxBin_youtput = yAxis_output->FindBin(binCenter_yinput);
          if ( idxBin_xoutput >= 1 && idxBin_xoutput <= numBins_xoutput && idxBin_youtput >= 1 && idxBin_youtput <= numBins_youtput) {
            histogram_output->SetBinContent(idxBin_xinput, idxBin_yinput, binContent_input);
            histogram_output->SetBinError(idxBin_xinput, idxBin_yinput, binError_input);
          }
          else if (idxBin_xoutput == 0 || idxBin_xoutput == (numBins_xoutput+1) || idxBin_youtput == 0 || idxBin_youtput == (numBins_youtput+1)) {
            continue;
            }
          else {
            assert(0);
          }
        }
      }
    }
    // CV: set underflow and overflow bins to zero
    //histogram_output->SetBinContent(0, binContent_output_underflow);
    //histogram_output->SetBinError(0, TMath::Sqrt(binErr2_output_underflow));
    //histogram_output->SetBinContent(numBins_output + 1, binContent_output_overflow);
    //histogram_output->SetBinError(numBins_output + 1, TMath::Sqrt(binErr2_output_overflow));
    if ( isHistogram2d ) {
      histogram_output->SetBinContent(0, 0, 0.);
      histogram_output->SetBinError(0, 0, 0.);
      histogram_output->SetBinContent(numBins_xoutput + 1, numBins_youtput + 1, 0.);
      histogram_output->SetBinError(numBins_xoutput + 1, numBins_youtput + 1, 0.);
    }
    else {
      histogram_output->SetBinContent(0, 0.);
      histogram_output->SetBinError(0, 0.);
      histogram_output->SetBinContent(numBins_xoutput + 1, 0.);
      histogram_output->SetBinError(numBins_xoutput + 1, 0.);
    }

    if ( rebin > 1 ) {
      if ( (numBins_xoutput % rebin) != 0 )
	throw cms::Exception("copyHistogram")
	  << "Failed to rebin histogram = '" << histogramName_input_full << "':"
	  << " numBins_input = " << numBins_xinput << ", numBins_xoutput = " << numBins_xoutput << " (xMin = " << xMin << ", xMax = " << xMax << "), rebin = " << rebin << " !!\n";
      histogram_output->Rebin(rebin);
    }

    return dynamic_cast<T*>(histogram_output);
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
  TPRegexp* fakes = new TPRegexp("data_fakes");

  std::vector<categoryType> categories;
  edm::VParameterSet cfg_categories = cfg_prepareDatacards.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfg_categories.begin();
	cfgCategory != cfg_categories.end(); ++cfgCategory ) {
    categories.push_back(categoryType(*cfgCategory));
  }

  std::string histogramToFit = cfg_prepareDatacards.getParameter<std::string>("histogramToFit");
  double histogramToFit_xMin = ( cfg_prepareDatacards.exists("histogramToFit_xMin") ) ? cfg_prepareDatacards.getParameter<double>("histogramToFit_xMin") : -1.;
  double histogramToFit_xMax = ( cfg_prepareDatacards.exists("histogramToFit_xMax") ) ? cfg_prepareDatacards.getParameter<double>("histogramToFit_xMax") : -1.;
  bool histogramToFit_makeBinContentsPositive = cfg_prepareDatacards.getParameter<bool>("histogramToFit_makeBinContentsPositive");
  vstring central_or_shifts = cfg_prepareDatacards.getParameter<vstring>("sysShifts");
  // CV: check if central value needs to be added
  bool containsCentralValue = false;
  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
    if ( (*central_or_shift) == "central" || (*central_or_shift) == "" ) containsCentralValue = true;
  }
  if ( !containsCentralValue ) {
    central_or_shifts.push_back("");
  }
  int histogramToFit_rebin = cfg_prepareDatacards.getParameter<int>("histogramToFit_rebin");
  bool apply_automatic_rebinning = cfg_prepareDatacards.getParameter<bool>("apply_automatic_rebinning");
  double minEvents_automatic_rebinning = cfg_prepareDatacards.getParameter<double>("minEvents_automatic_rebinning");
  bool quantile_rebinning_in_fakes = cfg_prepareDatacards.getParameter<bool>("quantile_rebinning_in_fakes");
  int nbin_quantile_rebinning = cfg_prepareDatacards.getParameter<int>("nbin_quantile_rebinning");
  bool apply_quantile_rebinning = nbin_quantile_rebinning > 0;
  bool is2d_histogram = cfg_prepareDatacards.getParameter<bool>("is2d_histogram");
  if(quantile_rebinning_in_fakes && ! apply_quantile_rebinning)
  {
    throw cmsException(__func__, __LINE__)
      << "It doesn't make any sense to require quantile rebinning in fakes if you haven't provided "
         "the number of bins"
    ;
  }
  const vdouble explicitBinning = cfg_prepareDatacards.getParameter<vdouble>("explicit_binning");

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
    std::vector<histogramEntryType_private*>histogramsToRebin;
    std::vector<histogramEntryType_private*>histogramsRebinned;
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
        bool isMatched_signal = compMatch(subdir->GetName(), *signal);
        if ( isMatched_signal ) {
          std::cout << " matches signal = " << (*signal)->GetPattern() << std::endl;
          isSignal = true;
        } else {
          std::cout << " does not match signal = " << (*signal)->GetPattern() << std::endl;
        }
      }
      if ( isToCopy ) {
        for(const std::string & central_or_shift: central_or_shifts)
        {
          std::cout << "histogramToFit = " << histogramToFit << ", central_or_shift = " << central_or_shift << '\n';
          const bool is_central = central_or_shift.empty()  || central_or_shift == "central";
          TFileDirectory* subdir_output = &fs;
          subdir_output->cd();
          //Make subdirectory if given
          bool makeSubDir = cfg_prepareDatacards.getParameter<bool>("makeSubDir");
          if ( makeSubDir == true && category->output_.length() > 0 ){
            TDirectory* subsubdir_output = createSubdirectory_recursively(fs, category->output_);
            subsubdir_output->cd();
          }
          double sf = ( isSignal ) ? sf_signal : 1.;
          TH1* histogram(NULL);
          TH2* histogram_2d(NULL);
          if ( is2d_histogram )
          {
            histogram_2d = copyHistogram<TH2>(
                   subdir, subdir->GetName(), histogramToFit, "",
                   sf, histogramToFit_xMin, histogramToFit_xMax, histogramToFit_rebin, central_or_shift, is_central);
            delete histogram;
            continue;
          }
          else
          {
          histogram = copyHistogram<TH1>(
                 subdir, subdir->GetName(), histogramToFit, "",
                 sf, histogramToFit_xMin, histogramToFit_xMax, histogramToFit_rebin, central_or_shift, is_central);
          delete histogram_2d;
          }
          if ( !histogram ) continue;
          bool isData = compMatch(subdir->GetName(), data);
          bool isFakes = compMatch(subdir->GetName(), fakes);
          if(! (isData || isSignal) && is_central && ((quantile_rebinning_in_fakes && isFakes) || ! quantile_rebinning_in_fakes))
          {
            std::cout << "adding background = '" << subdir->GetName() << "'" << std::endl;
            if   ( !histogramBackgroundSum ) histogramBackgroundSum = (TH1*)histogram->Clone(Form("%s_BackgroundSum", category->input_.data()));
            else                             histogramBackgroundSum->Add(histogram);
          }
          histogramEntryType_private* histogramEntry = new histogramEntryType_private(histogram, isData);
          histogramsToRebin.push_back(histogramEntry);
        }
      }
    }
    if (is2d_histogram) {
      delete histogramBackgroundSum;
      continue;
    }
    if(! explicitBinning.empty() && ! apply_automatic_rebinning && ! apply_quantile_rebinning)
    {
      TDirectory* subsubdir_output = createSubdirectory_recursively(fs, Form("%s/rebinned", category->output_.c_str()));
      subsubdir_output->cd();
      // rebin histograms as the user requested
      TArrayD histogramBinning = getTArrayDfromVector(explicitBinning);
      for ( std::vector<histogramEntryType_private*>::iterator histogram = histogramsToRebin.begin();
            histogram != histogramsToRebin.end(); ++histogram ) {
	histogramEntryType_private* histogramEntry = new histogramEntryType_private(
          getRebinnedHistogram1d((TH1*)(*histogram)->histogram_, 4, histogramBinning), (bool)(*histogram)->isData_
        );
	histogramsRebinned.push_back(histogramEntry);
      }
    }
    if ( apply_automatic_rebinning &&(!apply_quantile_rebinning) && explicitBinning.empty()) {
      TDirectory* subsubdir_output = createSubdirectory_recursively(fs, Form("%s/rebinned", category->output_.c_str()));
      subsubdir_output->cd();
      // rebin histograms to avoid bins with zero background
      assert(histogramBackgroundSum);
      TArrayD histogramBinning = getRebinnedBinning(histogramBackgroundSum, minEvents_automatic_rebinning);
      for ( std::vector<histogramEntryType_private*>::iterator histogram = histogramsToRebin.begin();
            histogram != histogramsToRebin.end(); ++histogram ) {
        histogramEntryType_private* histogramEntry = new histogramEntryType_private(
          getRebinnedHistogram1d((TH1*)(*histogram)->histogram_, 4, histogramBinning), (bool)(*histogram)->isData_
                   );
        histogramsRebinned.push_back(histogramEntry);
      }
    }
    if ( apply_quantile_rebinning && (!apply_automatic_rebinning) && explicitBinning.empty()) {
      TDirectory* subsubdir_output = createSubdirectory_recursively(fs, Form("%s/rebinned", category->output_.c_str()));
      subsubdir_output->cd();
      assert(histogramBackgroundSum);
      const Int_t nq = nbin_quantile_rebinning;
      Double_t xq[nq];  // position where to compute the quantiles in [0,1]
      Double_t yq[nq];  // array to contain the quantiles
      for (Int_t i=0;i<nq;i++) xq[i] = Float_t(i+1)/nq;
      histogramBackgroundSum->GetQuantiles(nq,yq,xq);
      std::cout << "............ quantile binning ............" << std::endl;
      for (Int_t i=0;i<nq;i++)std::cout<<yq[i]<<std::endl;
      TArrayD histogramBinning(nq+1);
      histogramBinning[0] = 0;
      for (Int_t i=0;i<nq;i++) histogramBinning[i+1] = yq[i];
      for ( std::vector<histogramEntryType_private*>::iterator histogram = histogramsToRebin.begin();
	    histogram != histogramsToRebin.end(); ++histogram ) {
	histogramEntryType_private* histogramEntry = new histogramEntryType_private(
          getRebinnedHistogram1d((TH1*)(*histogram)->histogram_, 4, histogramBinning), (bool)(*histogram)->isData_
        );
	histogramsRebinned.push_back(histogramEntry);
      }
    }
    if ( histogramToFit_makeBinContentsPositive ) {
      for ( std::vector<histogramEntryType_private*>::iterator histogram = histogramsToRebin.begin();
	    histogram != histogramsToRebin.end(); ++histogram ) {
	makeBinContentsPositive((TH1*)(*histogram)->histogram_, (bool)(*histogram)->isData_, true);
      }
      for ( std::vector<histogramEntryType_private*>::iterator histogram = histogramsRebinned.begin();
	    histogram != histogramsRebinned.end(); ++histogram ) {
	makeBinContentsPositive((TH1*)(*histogram)->histogram_, (bool)(*histogram)->isData_, true);
      }
    }

    delete histogramBackgroundSum;
  }

  delete inputFile;

  clock.Show("prepareDatacards");

  return EXIT_SUCCESS;
}
