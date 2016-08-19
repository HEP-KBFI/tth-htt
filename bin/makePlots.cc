
/** \executable makePlots
 *
 * Make control plots (prefit and postfit) for all channels of ttH, H->tautau analysis.
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
#include <THStack.h>
#include <TBenchmark.h>
#include <TMath.h>
#include "TPRegexp.h"
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TF1.h>
#include <TStyle.h>
#include <TROOT.h>

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;
typedef std::pair<double, double> pdouble; 

namespace
{
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {
      name_ = cfg.getParameter<std::string>("name");
      label_ = cfg.getParameter<std::string>("label");
    }
    ~categoryEntryType() {}
    std::string name_;
    std::string label_;
  };

  struct histogramEntryType
  {
    histogramEntryType(const std::string& process, TH1* histogram)
      : process_(process),
	histogram_(histogram)
    {}
    ~histogramEntryType() {}
    std::string process_;
    TH1* histogram_;
  };

  struct plotEntryType
  {
    plotEntryType(const edm::ParameterSet& cfg)
      : legendTextSize_(0.050),
	legendPosX_(0.700),
	legendPosY_(0.510),
	legendSizeX_(0.230),
	legendSizeY_(0.420)
    {
      histogramName_ = cfg.getParameter<std::string>("histogramName");
      outputFileName_ = ( cfg.exists("outputFileName") ) ?
	cfg.getParameter<std::string>("outputFileName") : histogramName_;
      xMin_ = ( cfg.exists("xMin") ) ? cfg.getParameter<double>("xMin") : -1.;
      xMax_ = ( cfg.exists("xMax") ) ? cfg.getParameter<double>("xMax") : -1.;
      xAxisTitle_ = cfg.getParameter<std::string>("xAxisTitle");
      xAxisOffset_ = ( cfg.exists("xAxisOffset") ) ? cfg.getParameter<double>("xAxisOffset") : 1.25;
      yMin_ = ( cfg.exists("yMin") ) ? cfg.getParameter<double>("yMin") : -1.;
      yMax_ = ( cfg.exists("yMax") ) ? cfg.getParameter<double>("yMax") : -1.;
      yAxisTitle_ = cfg.getParameter<std::string>("yAxisTitle");
      yAxisOffset_ = ( cfg.exists("yAxisOffset") ) ? cfg.getParameter<double>("yAxisOffset") : 1.15;
      if ( cfg.exists("keepBlinded") ) {
	vstring keepBlinded_string = cfg.getParameter<vstring>("keepBlinded");
	TPRegexp regexpParser_range("([0-9.e+/-]+):([0-9.e+/-]+)");
	for ( vstring::const_iterator keepBlinded_it = keepBlinded_string.begin();
	      keepBlinded_it != keepBlinded_string.end(); ++keepBlinded_it ) {
	  TObjArray* subStrings = regexpParser_range.MatchS(keepBlinded_it->data());
	  if ( subStrings->GetEntries() == 3 ) {
	    //std::cout << "substrings(1) = " << ((TObjString*)subStrings->At(1))->GetString() << std::endl;
	    double range_begin = ((TObjString*)subStrings->At(1))->GetString().Atof();
	    //std::cout << "substrings(2) = " << ((TObjString*)subStrings->At(2))->GetString() << std::endl;
	    double range_end = ((TObjString*)subStrings->At(2))->GetString().Atof();
	    keepBlinded_.push_back(pdouble(range_begin, range_end));
	  }
	}
      }      
    }
    ~plotEntryType() {}
    std::string histogramName_;
    std::string outputFileName_;
    double xMin_;
    double xMax_;
    std::string xAxisTitle_;
    double xAxisOffset_;
    double yMin_;
    double yMax_;
    std::string yAxisTitle_;
    double yAxisOffset_;
    std::vector<pdouble> keepBlinded_;
    double legendTextSize_;
    double legendPosX_;
    double legendPosY_;
    double legendSizeX_;
    double legendSizeY_; 
  };
  
  //-----------------------------------------------------------------------------
  void parseValue_and_Uncertainty(const std::string& valueErr_string, double& value, double& err)
  {
    //std::cout << "<parseValue_and_Uncertainty>:" << std::endl;
    //std::cout << " valueErr = " << valueErr_string << std::endl;
    TPRegexp regexpParser("([0-9.eE+-]+)\\s*\\+/-\\s*([0-9.eE+-]+)");
    TObjArray* subStrings = regexpParser.MatchS(valueErr_string.data());
    if ( subStrings->GetEntries() == 3 ) {
      value = ((TObjString*)subStrings->At(1))->GetString().Atof();
      //std::cout << " value = " << value << std::endl;
      err = ((TObjString*)subStrings->At(2))->GetString().Atof();
      //std::cout << " err = " << err << std::endl;
    } else throw cms::Exception("parseValue_and_Uncertainty") 
	<< "Failed to parse string = '" << valueErr_string << "' !!\n";    
  }
  TH1* getHistogram_wrapper(TDirectory* dir, const std::string& process, const std::string& histogramName, const std::string& central_or_shift, bool enableException)
  {
    std::string histogramName_full = TString(histogramName.data()).ReplaceAll("$PROCESS", process.data()).Data();
    size_t idx = histogramName_full.find_last_of("/");
    assert(idx < (histogramName_full.length() - 1));
    std::string subdirName = std::string(histogramName_full, 0, idx);
    std::string histogramName_wrt_subdir = std::string(histogramName_full, idx + 1);
    TH1* histogram = getHistogram(dir, subdirName, histogramName_wrt_subdir, central_or_shift, enableException);
    return histogram;
  }
  void printHistogram(const TH1* histogram)
  {
    std::cout << "<printHistogram>:" << std::endl;
    std::cout << "name = " << histogram->GetName() << std::endl;
    int numBins = histogram->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      std::cout << " bin #" << iBin << ": " << histogram->GetBinContent(iBin) << " +/- " << histogram->GetBinError(iBin) << std::endl;
    }
    std::cout << "integral = " << histogram->Integral() << std::endl;
  }
  double square(double x)
  {
    return (x*x);
  }
  struct HistogramManager
  {
    HistogramManager(const vstring& processesBackground, const std::string& processSignal, const std::vector<categoryEntryType*>& categories, const edm::ParameterSet& cfg)
      : currentDir_(0),	
	isUpToDate_(false),
	histogram_uncertainty_(0)
    {
      processes_ = processesBackground;
      processes_.push_back(processSignal);

      edm::ParameterSet cfgNormalization = cfg.getParameter<edm::ParameterSet>("normalization");
      for ( vstring::const_iterator process = processes_.begin();
	    process != processes_.end(); ++process ) {
	for ( std::vector<categoryEntryType*>::const_iterator category = categories.begin();
	      category != categories.end(); ++category ) {
	  normEntryType processEntry;
	  processEntry.process_ = (*process);
	  processEntry.category_ = ((*category)->name_);
	  parseValue_and_Uncertainty(cfgNormalization.getParameter<std::string>(*process), processEntry.sf_, processEntry.sfErr_);
	  normalizationValues_and_Uncertainties_[*process][(*category)->name_] = processEntry;
	}
      }

      edm::ParameterSet cfgShape = cfg.getParameter<edm::ParameterSet>("shape");
      sysShifts_ = cfgShape.getParameterNamesForType<std::string>();
      for ( vstring::const_iterator sysShift = sysShifts_.begin();
	    sysShift != sysShifts_.end(); ++sysShift ) {
	shapeEntryType sysShiftEntry;
	sysShiftEntry.sysShift_ = (*sysShift);
	parseValue_and_Uncertainty(cfgShape.getParameter<std::string>(*sysShift), sysShiftEntry.value_, sysShiftEntry.err_);
	shapeValues_and_Uncertainties_[*sysShift] = sysShiftEntry;
      }
    }
    ~HistogramManager()
    {
      //for ( map_string_to_TH1::iterator it = histograms_postfit_.begin();
      //      it != histograms_postfit_.end(); ++it ) {
      //  delete it->second;
      //}
      //delete histogram_uncertainty_;
    }

    void setDirectory(TDirectory* dir)
    {
      currentDir_ = dir;
      isUpToDate_ = false;
    }
    void setCategory(const std::string& category)
    {
      currentCategory_ = category;
      isUpToDate_ = false;
    }
    void setHistogram(const std::string& histogramName)
    {
      currentHistogramName_ = histogramName;
      isUpToDate_ = false;
    }

    TH1* getHistogramPrefit(const std::string& process, bool enableException)
    {
      if ( !isUpToDate_ ) update();
      TH1* histogram = 0;
      if ( histograms_prefit_.find(process) != histograms_prefit_.end() ) {
	histogram = histograms_prefit_[process];
      }
      if ( enableException && !histogram ) 
	throw cms::Exception("HistogramManager") 
	  << "Failed to find prefit histogram for process = " << process << " !!\n";    
      return histogram;
    }
    TH1* getHistogramPostfit(const std::string& process, bool enableException)
    {
      if ( !isUpToDate_ ) update();
      TH1* histogram = 0;
      if ( histograms_postfit_.find(process) != histograms_postfit_.end() ) {
	histogram = histograms_postfit_[process];
      }
      if ( enableException && !histogram ) 
	throw cms::Exception("HistogramManager") 
	  << "Failed to find postfit histogram for process = " << process << " !!\n";    
      return histogram;
    }
    TH1* getHistogramUncertainty()
    {
      if ( !isUpToDate_ ) update();
      return histogram_uncertainty_;
    }

    void getSF(const std::string& process, double& sf, double& sfErr)
    {
      assert(normalizationValues_and_Uncertainties_.find(process) != normalizationValues_and_Uncertainties_.end());
      assert(normalizationValues_and_Uncertainties_[process].find(currentCategory_) != normalizationValues_and_Uncertainties_[process].end());
      sf = normalizationValues_and_Uncertainties_[process][currentCategory_].sf_;
      sfErr = normalizationValues_and_Uncertainties_[process][currentCategory_].sfErr_;
    } 

    void update()
    {
      for ( vstring::const_iterator process = processes_.begin();
	    process != processes_.end(); ++process ) {
	std::cout << "process = " << (*process) << std::endl;

	TH1* histogram_prefit = getHistogram_wrapper(currentDir_, *process, currentHistogramName_, "central", true);
	histograms_prefit_[*process] = histogram_prefit;
	//printHistogram(histograms_prefit_[*process]);
	
	for ( vstring::const_iterator sysShift = sysShifts_.begin();
	      sysShift != sysShifts_.end(); ++sysShift ) {
	  std::string sysShiftUp = Form("%sUp", sysShift->data());
	  TH1* histogram_sysShiftUp = getHistogram_wrapper(currentDir_, *process, currentHistogramName_, sysShiftUp, false);
	  if ( histogram_sysShiftUp ) {
	    histograms_sysShifts_[*process][sysShiftUp] = histogram_sysShiftUp;
	  }
	  std::string sysShiftDown = Form("%sDown", sysShift->data());
	  TH1* histogram_sysShiftDown = getHistogram_wrapper(currentDir_, *process, currentHistogramName_, sysShiftDown, false);
	  if ( histogram_sysShiftDown ) {
	    histograms_sysShifts_[*process][sysShiftDown] = histogram_sysShiftDown;
	  }
	}
	
	std::string histogramName_postfit = Form("%s_postfit", histogram_prefit->GetName());
	TH1* histogram_postfit = (TH1*)histogram_prefit->Clone(histogramName_postfit.data());
	if ( !histogram_postfit->GetSumw2N() ) histogram_postfit->Sumw2();
	if ( normalizationValues_and_Uncertainties_.find(*process) != normalizationValues_and_Uncertainties_.end() ) {
	  double sf, sfErr;
	  getSF(*process, sf, sfErr);
	  std::cout << "--> scaling histogram = " << histogram_postfit->GetName() << " by factor = " << sf << std::endl;
	  histogram_postfit->Scale(sf);
	}
	for ( vstring::const_iterator sysShift = sysShifts_.begin();
	      sysShift != sysShifts_.end(); ++sysShift ) {
	  std::string sysShiftUp = Form("%sUp", sysShift->data());
	  std::string sysShiftDown = Form("%sDown", sysShift->data());
	  if ( histograms_sysShifts_[*process].find(sysShiftUp)   != histograms_sysShifts_[*process].end() &&
	       histograms_sysShifts_[*process].find(sysShiftDown) != histograms_sysShifts_[*process].end() ) {
	    double sysShift_value = shapeValues_and_Uncertainties_[*sysShift].value_;
	    TH1* histogram_sysShift = 0;
	    if ( sysShift_value > 0. ) histogram_sysShift = histograms_sysShifts_[*process][sysShiftUp];
	    else if ( sysShift_value < 0. ) histogram_sysShift = histograms_sysShifts_[*process][sysShiftDown];
	    if ( histogram_sysShift ) {
	      double absSysShift_value = TMath::Abs(sysShift_value);
	      TH1* histogram_prefit = histograms_prefit_[*process];
	      assert(histogram_prefit);
	      int numBins = histogram_postfit->GetNbinsX();
	      for ( int iBin = 1; iBin <= numBins; ++iBin ) {
		double binContent_central = histogram_prefit->GetBinContent(iBin);
		double binContent_sysShift = histogram_sysShift->GetBinContent(iBin);
		double binContent_postfit = histogram_postfit->GetBinContent(iBin);
		binContent_postfit *= (binContent_central + absSysShift_value*(binContent_sysShift - binContent_central));
		if ( binContent_postfit < 0. ) binContent_postfit = 0.;
		histogram_postfit->SetBinContent(iBin, binContent_postfit);
	      }
	    }
	  }
	}
	delete histograms_postfit_[*process];
	histograms_postfit_[*process] = histogram_postfit;
	//printHistogram(histograms_postfit_[*process]);
      }
	
      delete histogram_uncertainty_;
      std::string histogramName_uncertainty = Form("%s_uncertainty", currentHistogramName_.data());
      histogram_uncertainty_ = (TH1*)histograms_prefit_.begin()->second->Clone(histogramName_uncertainty.data());
      histogram_uncertainty_->Reset();
      if ( !histogram_uncertainty_->GetSumw2N() ) histogram_uncertainty_->Sumw2();
      int numBins = histogram_uncertainty_->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins; ++iBin ) {
	double binContent_uncertainty = 0.;
	double binErr2_uncertainty = 0.;
	for ( vstring::const_iterator process = processes_.begin();
	      process != processes_.end(); ++process ) {
	  TH1* histogram_prefit = histograms_prefit_[*process];
	  assert(histogram_prefit);
	  double binContent_prefit = histogram_prefit->GetBinContent(iBin);
	  TH1* histogram_postfit = histograms_postfit_[*process];
	  assert(histogram_postfit);
	  double binContent_postfit = histogram_postfit->GetBinContent(iBin);
	  double binErr_postfit = histogram_postfit->GetBinError(iBin);
	  binContent_uncertainty += binContent_postfit;
	  binErr2_uncertainty += square(binErr_postfit); // statistical uncertainty of background process in given bin
	  double sf, sfErr;
	  getSF(*process, sf, sfErr);
	  if ( sf > 0. ) {
	    binErr2_uncertainty += square(binContent_postfit*(sfErr/sf)); // systematic uncertainty on background normalization
	  }
	  for ( vstring::const_iterator sysShift = sysShifts_.begin();
		sysShift != sysShifts_.end(); ++sysShift ) {
	    double sysShift_value = shapeValues_and_Uncertainties_[*sysShift].value_;	    
	    TH1* histogram_sysShift = 0;
	    if ( sysShift_value > 0. ) {
	      std::string sysShiftUp = Form("%sUp", sysShift->data());
	      if ( histograms_sysShifts_[*process].find(sysShiftUp) != histograms_sysShifts_[*process].end() ) {
		histogram_sysShift = histograms_sysShifts_[*process][sysShiftUp];
	      }
	    } else if ( sysShift_value < 0. ) {
	      std::string sysShiftDown = Form("%sDown", sysShift->data());
	      if ( histograms_sysShifts_[*process].find(sysShiftDown) != histograms_sysShifts_[*process].end() ) {
		histogram_sysShift = histograms_sysShifts_[*process][sysShiftDown];
	      }
	    } 	    
	    if ( histogram_sysShift ) {
	      double sysShift_err = shapeValues_and_Uncertainties_[*sysShift].err_;
	      double binContent_sysShift = histogram_sysShift->GetBinContent(iBin);
	      if ( binContent_prefit > 0. ) {
		binErr2_uncertainty += square(binContent_postfit*sysShift_err*(binContent_sysShift - binContent_prefit)/binContent_prefit); // systematic uncertainty on background shape
	      } else if ( binContent_postfit > 0. ) {
		binErr2_uncertainty += square(sysShift_err*(binContent_sysShift - binContent_prefit));
	      }
	    }
	  }
	}
	histogram_uncertainty_->SetBinContent(iBin, binContent_uncertainty);
	assert(binErr2_uncertainty >= 0.);
	histogram_uncertainty_->SetBinError(iBin, TMath::Sqrt(binErr2_uncertainty));
      }
      
      isUpToDate_ = true;
    }

    vstring processes_;
    struct normEntryType
    {     
      std::string process_;
      std::string category_;
      double sf_;
      double sfErr_;
    };
    typedef std::map<std::string, normEntryType> stringToNormEntryTypeMap;
    std::map<std::string, stringToNormEntryTypeMap> normalizationValues_and_Uncertainties_; // keys = process, category

    vstring sysShifts_;
    struct shapeEntryType
    {     
      std::string sysShift_;
      double value_;
      double err_;
    };
    std::map<std::string, shapeEntryType> shapeValues_and_Uncertainties_; // key = sysShift

    TDirectory* currentDir_;

    std::string currentCategory_;

    std::string currentHistogramName_;

    bool isUpToDate_;

    typedef std::map<std::string, TH1*> map_string_to_TH1;
    map_string_to_TH1 histograms_prefit_;  // key = process
    map_string_to_TH1 histograms_postfit_; // key = process
    std::map<std::string, map_string_to_TH1> histograms_sysShifts_; // key = process, sysShift
    TH1* histogram_uncertainty_;
  };

  //-----------------------------------------------------------------------------

  TH1* blindHistogram(TH1* histogram, const std::vector<pdouble>& keepBlinded)
  {
    //std::cout << "<blindHistogram>:" << std::endl;
    std::string blindedHistogramName = Form("%s_blinded", histogram->GetName());
    TH1* blindedHistogram = (TH1*)histogram->Clone(blindedHistogramName.data());
    if ( !blindedHistogram->GetSumw2N() ) blindedHistogram->Sumw2();
    int numBins = histogram->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double x = histogram->GetBinCenter(iBin);
      bool isBlinded = false;
      for ( std::vector<pdouble>::const_iterator keepBlinded_it = keepBlinded.begin();
	    keepBlinded_it != keepBlinded.end(); ++keepBlinded_it ) {
	if ( x >= keepBlinded_it->first && x <= keepBlinded_it->second ) {
	  isBlinded = true;
	  break;
	}
      }
      //std::cout << "x = " << x << ": isBlinded = " << isBlinded << std::endl;
      if ( isBlinded ) {
	blindedHistogram->SetBinContent(iBin, -10.);
	blindedHistogram->SetBinError(iBin, 0.);
      }
    }
    //std::cout << "histogram: name = " << histogram->GetName() << ", integral = " << histogram->Integral() << std::endl;
    //std::cout << "histogram(blinded): name = " << blindedHistogram->GetName() << ", integral = " << blindedHistogram->Integral() << std::endl;
    return blindedHistogram;
  }

  TH1* divideHistogramByBinWidth(TH1* histogram)
  {
    std::string histogramDensityName = Form("%s_density", histogram->GetName());
    TH1* histogramDensity = (TH1*)histogram->Clone(histogramDensityName.data());
    TAxis* xAxis = histogram->GetXaxis();
    int numBins = xAxis->GetNbins();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double binContent = histogram->GetBinContent(iBin);
      double binError = histogram->GetBinError(iBin);
      double binWidth = xAxis->GetBinWidth(iBin);
      histogramDensity->SetBinContent(iBin, binContent/binWidth);
      histogramDensity->SetBinError(iBin, binError/binWidth);
    }
    return histogramDensity;
  }

  double compYmaxForClearance(TH1* histogram, double legendPosX, double legendPosY, double labelPosY, bool useLogScale, double numOrdersOfMagnitude)
  {
    TAxis* xAxis = histogram->GetXaxis();
    double xMin = xAxis->GetXmin();
    double xMax = xAxis->GetXmax();
    const double dX = 0.05;
    const double dY = 0.05;
    double x12 = xMin + (xMax - xMin)*legendPosX;
    //std::cout << "x12 = " << x12 << std::endl;
    double maxBinContent1 = 0.;
    double maxBinContent2 = 0.;
    int numBins = xAxis->GetNbins();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double binContent = histogram->GetBinContent(iBin);
      if ( xAxis->GetBinLowEdge(iBin) < (x12 + dX) ) {
	if ( binContent > maxBinContent1 ) maxBinContent1 = binContent;
      }
      if ( xAxis->GetBinUpEdge(iBin) > (x12 - dX) ) {
	if ( binContent > maxBinContent2 ) maxBinContent2 = binContent;
      }
    }
    double yMaxForClearance = 0.;
    if ( useLogScale ) {
      double maxBinContent = TMath::Max(maxBinContent1, maxBinContent2);
      double logYmaxForClearance1 = 0.;      
      if ( maxBinContent1 > 0. && maxBinContent > 0. ) {
	logYmaxForClearance1 = (TMath::Log(maxBinContent1) - (TMath::Log(maxBinContent) - numOrdersOfMagnitude*TMath::Log(10.)))/(labelPosY - dY);
	logYmaxForClearance1 += (TMath::Log(maxBinContent) - numOrdersOfMagnitude*TMath::Log(10.));
      }
      double logYmaxForClearance2 = 0.;    
      if ( maxBinContent2 > 0. && maxBinContent > 0. ) {
	logYmaxForClearance2 = (TMath::Log(maxBinContent2) - (TMath::Log(maxBinContent) - numOrdersOfMagnitude*TMath::Log(10.)))/(legendPosY - dY);
	logYmaxForClearance2 += (TMath::Log(maxBinContent) - numOrdersOfMagnitude*TMath::Log(10.));
      }
      double logYmaxForClearance = TMath::Max(logYmaxForClearance1, logYmaxForClearance2);
      yMaxForClearance = TMath::Exp(logYmaxForClearance);
      //std::cout << "log-scale: maxBinContent1 = " << maxBinContent1 << ", maxBinContent2 = " << maxBinContent2 << " --> setting yMaxForClearance = " << yMaxForClearance << std::endl;
    } else {
      yMaxForClearance = TMath::Max(maxBinContent1/(labelPosY - dY), maxBinContent2/(legendPosY - dY));
      //std::cout << "linear scale: maxBinContent1 = " << maxBinContent1 << ", maxBinContent2 = " << maxBinContent2 << " --> setting yMaxForClearance = " << yMaxForClearance << std::endl;
    }
    return yMaxForClearance;
  }

  void makePlot(double canvasSizeX, double canvasSizeY,
		TH1* histogramData, TH1* histogramData_blinded,
		std::vector<histogramEntryType*>& histogramsBackground, 	
		TH1* histogramSignal,
		TH1* histogramUncertainty,
		double legendTextSize, double legendPosX, double legendPosY, double legendSizeX, double legendSizeY, 
		const std::string& labelOnTop,
		std::vector<std::string>& extraLabels, double labelTextSize,
		double labelPosX, double labelPosY, double labelSizeX, double labelSizeY,
	        double xMin, double xMax, const std::string& xAxisTitle, double xAxisOffset,
		bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
		const std::string& outputFileName)
  {
    TH1* histogramData_density = 0;
    if ( histogramData ) {
      histogramData_density = divideHistogramByBinWidth(histogramData);      
    }

    TH1* histogramData_blinded_density = 0;
    if ( histogramData_blinded ) {
      if ( histogramData ) checkCompatibleBinning(histogramData_blinded, histogramData);
      histogramData_blinded_density = divideHistogramByBinWidth(histogramData_blinded);
    }

    std::vector<TH1*> histogramsBackground_density;
    TH1* histogramTTW = 0;
    TH1* histogramTTW_density = 0;
    TH1* histogramTTZ = 0;
    TH1* histogramTTZ_density = 0;
    TH1* histogramTT = 0;
    TH1* histogramTT_density = 0;
    TH1* histogramWZ = 0;
    TH1* histogramWZ_density = 0;
    TH1* histogramDiboson = 0;
    TH1* histogramDiboson_density = 0;
    TH1* histogramEWK = 0;
    TH1* histogramEWK_density = 0;
    TH1* histogramRares = 0;
    TH1* histogramRares_density = 0;
    TH1* histogramFakes = 0;
    TH1* histogramFakes_density = 0;
    TH1* histogramFlips = 0;
    TH1* histogramFlips_density = 0;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
	  histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      TH1* histogramBackground = (*histogramBackground_entry)->histogram_;
      const std::string& process = (*histogramBackground_entry)->process_;
      checkCompatibleBinning(histogramBackground, histogramData);
      TH1* histogramBackground_density = divideHistogramByBinWidth(histogramBackground); 
      if ( process.find("TTW") != std::string::npos ) {
	histogramTTW = histogramBackground;
	histogramTTW_density = histogramBackground_density;
      } else if ( process.find("TTZ") != std::string::npos ) {
	histogramTTZ = histogramBackground;
	histogramTTZ_density = histogramBackground_density;
      } else if ( process.find("TT") != std::string::npos ) {
	histogramTT = histogramBackground;
	histogramTT_density = histogramBackground_density;
      } else if ( process.find("EWK") != std::string::npos ) {
	histogramEWK = histogramBackground;
	histogramEWK_density = histogramBackground_density;
      } else if ( process.find("Diboson") != std::string::npos ) { 
	histogramDiboson = histogramBackground;
	histogramDiboson_density = histogramBackground_density;
      } else if ( process.find("WZ") != std::string::npos ) {
	histogramWZ = histogramBackground;
	histogramWZ_density = histogramBackground_density;
      } else if ( process.find("Rares") != std::string::npos ) {
	histogramRares = histogramBackground;
	histogramRares_density = histogramBackground_density;
      } else if ( process.find("Fakes") != std::string::npos || process.find("fakes") != std::string::npos ) {
	histogramFakes = histogramBackground;
	histogramFakes_density = histogramBackground_density;
      } else if ( process.find("Flips") != std::string::npos || process.find("flips") != std::string::npos ) {
	histogramFlips = histogramBackground;
	histogramFlips_density = histogramBackground_density;
      }
      histogramsBackground_density.push_back(histogramBackground_density);
    }

    TH1* histogramSignal_density = 0;
    if ( histogramSignal ) {
      if ( histogramSignal ) checkCompatibleBinning(histogramSignal, histogramData);
      histogramSignal_density = divideHistogramByBinWidth(histogramSignal); 
    }

    TH1* histogramSum_density = 0;
    std::vector<TH1*> histogramsSignal_and_Background_density = histogramsBackground_density;
    if ( histogramSignal_density ) histogramsSignal_and_Background_density.push_back(histogramSignal_density);
    for ( std::vector<TH1*>::iterator histogram_density = histogramsSignal_and_Background_density.begin();
	  histogram_density != histogramsSignal_and_Background_density.end(); ++histogram_density ) {
      if ( !histogramSum_density ) histogramSum_density = (TH1*)(*histogram_density)->Clone("histogramSum_density"); // CV: used for y-axis normalization only
      else histogramSum_density->Add(*histogram_density);
    }
    assert(histogramSum_density);

    TH1* histogramUncertainty_density = 0;
    if ( histogramUncertainty ) {
      if ( histogramData ) checkCompatibleBinning(histogramUncertainty, histogramData);
      histogramUncertainty_density = divideHistogramByBinWidth(histogramUncertainty);
    }

    TCanvas* canvas = new TCanvas("canvas", "", canvasSizeX, canvasSizeY);
    canvas->SetFillColor(10);
    canvas->SetFillStyle(4000);
    canvas->SetFillColor(10);
    canvas->SetTicky();
    canvas->SetBorderSize(2);
    canvas->SetLeftMargin(0.12);
    canvas->SetBottomMargin(0.12);

    TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
    topPad->SetFillColor(10);
    topPad->SetTopMargin(0.055);
    topPad->SetLeftMargin(0.15);
    topPad->SetBottomMargin(0.03);
    topPad->SetRightMargin(0.05);
    topPad->SetLogy(useLogScale);

    TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
    bottomPad->SetFillColor(10);
    bottomPad->SetTopMargin(0.02);
    bottomPad->SetLeftMargin(0.15);
    bottomPad->SetBottomMargin(0.31);
    bottomPad->SetRightMargin(0.05);
    bottomPad->SetLogy(false);

    canvas->cd();
    topPad->Draw();
    topPad->cd();

    TAxis* xAxis_top = 0;
    if ( histogramData_blinded_density ) xAxis_top = histogramData_blinded_density->GetXaxis();
    else xAxis_top = histogramSum_density->GetXaxis();
    if ( xMin >= 0. && xMax > xMin ) xAxis_top->SetRangeUser(xMin, xMax);
    xAxis_top->SetTitle(xAxisTitle.data());
    xAxis_top->SetTitleOffset(xAxisOffset);
    xAxis_top->SetLabelColor(10);
    xAxis_top->SetTitleColor(10);
    
    TAxis* yAxis_top = 0;
    if ( histogramData_blinded_density ) yAxis_top = histogramData_blinded_density->GetYaxis();
    else yAxis_top = histogramSum_density->GetYaxis();
    yAxis_top->SetTitle(yAxisTitle.data());
    yAxis_top->SetTitleOffset(yAxisOffset);
    yAxis_top->SetTitleSize(0.065);
    yAxis_top->SetLabelSize(0.05);
    yAxis_top->SetTickLength(0.04);  

    TLegend* legend = new TLegend(legendPosX, legendPosY, legendPosX + legendSizeX, legendPosY + legendSizeY, NULL, "brNDC");
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetFillColor(10);
    legend->SetTextSize(legendTextSize);

    if ( !(yMin >= 0. && yMax > yMin) ) {
      if ( useLogScale ) {
	const double numOrdersOfMagnitude = 4.5;
	if ( histogramData_density ) yMax = compYmaxForClearance(histogramData_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude);
	else yMax = 1.;
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSum_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude));
	yMin = TMath::Power(10., -numOrdersOfMagnitude)*TMath::Max(1., yMax);
      } else {
	if ( histogramData_density ) yMax = compYmaxForClearance(histogramData_density, legendPosX, legendPosY, labelPosY, false, -1.);
	else yMax = 1.;
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSum_density, legendPosX, legendPosY, labelPosY, false, -1.));
	yMin = 0.;
      }
    }
    //std::cout << "yMin = " << yMin << ", yMax = " << yMax << std::endl;

    if ( histogramData_blinded_density ) {
      histogramData_blinded_density->SetTitle("");
      histogramData_blinded_density->SetStats(false);
      histogramData_blinded_density->SetMaximum(yMax);
      histogramData_blinded_density->SetMinimum(yMin);
      histogramData_blinded_density->SetMarkerStyle(20);
      histogramData_blinded_density->SetMarkerSize(2);
      histogramData_blinded_density->SetMarkerColor(kBlack);
      histogramData_blinded_density->SetLineColor(kBlack);
      legend->AddEntry(histogramData_blinded_density, "observed", "p");
      histogramData_blinded_density->Draw("ep");
    }
        
    std::vector<TH1*> histogramsForStack_density;
    if ( histogramSignal_density ) {
      histogramSignal_density->SetFillColor(628); // red
      histogramsForStack_density.push_back(histogramSignal_density);
      legend->AddEntry(histogramSignal_density, "ttH", "f");
    }
    if ( histogramTTW_density ) {
      histogramTTW_density->SetFillColor(823); // dark green
      histogramsForStack_density.push_back(histogramTTW_density);
      legend->AddEntry(histogramTTW_density, "ttW", "f");
    }
    if ( histogramTTZ_density ) {
      histogramTTZ_density->SetFillColor(822); // light green
      histogramsForStack_density.push_back(histogramTTZ_density);
      legend->AddEntry(histogramTTZ_density, "ttZ", "f");
    }    
    if ( histogramTT_density ) {
      histogramTT_density->SetFillColor(16); // gray
      histogramsForStack_density.push_back(histogramTT_density);
      legend->AddEntry(histogramTT_density, "tt+jets", "f");
    }
    if ( histogramEWK_density ) {
      histogramEWK_density->SetFillColor(610); // purple
      histogramsForStack_density.push_back(histogramEWK_density);
      legend->AddEntry(histogramEWK_density, "EWK", "f");
    } else if ( histogramDiboson_density ) {
      histogramDiboson_density->SetFillColor(610);
      histogramsForStack_density.push_back(histogramDiboson_density);
      legend->AddEntry(histogramDiboson_density, "Diboson", "f");
    } else if ( histogramWZ_density ) {
      histogramWZ_density->SetFillColor(610);
      histogramsForStack_density.push_back(histogramWZ_density);
      legend->AddEntry(histogramWZ_density, "WZ", "f");
    }
    if ( histogramRares_density ) {
      histogramRares_density->SetFillColor(851); // light blue
      histogramsForStack_density.push_back(histogramRares_density);
      legend->AddEntry(histogramRares_density, "Rares", "f");
    }
    if ( histogramFakes_density ) {
      histogramFakes_density->SetFillColor(1);
      histogramFakes_density->SetFillStyle(3005); // stripes extending from top left to bottom right
      histogramsForStack_density.push_back(histogramFakes_density);
      legend->AddEntry(histogramFakes_density, "Fakes", "f");
    }
    if ( histogramFlips_density ) {
      histogramFlips_density->SetFillColor(1);
      histogramFlips_density->SetFillStyle(3006); // vertical stripes
      histogramsForStack_density.push_back(histogramFlips_density);
      legend->AddEntry(histogramFlips_density, "Flips", "f");
    }

    // CV: add histograms to THStack in "reverse" order, so that ttH signal is drawn on top
    THStack* histogramStack_density = new THStack("stack", "");
    for ( std::vector<TH1*>::reverse_iterator histogram_density = histogramsForStack_density.rbegin(); 
	  histogram_density != histogramsForStack_density.rend(); ++histogram_density ) {
      histogramStack_density->Add(*histogram_density);
    }
    if ( histogramData_blinded_density ) histogramStack_density->Draw("histsame");
    else histogramStack_density->Draw("hist");
    
    if ( histogramUncertainty_density ) {
      int numBins_top = histogramUncertainty_density->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins_top; ++iBin ) {
	double sumBinContents = 0.;
	if      ( histogramSignal_density  ) sumBinContents += histogramSignal_density->GetBinContent(iBin);
	if      ( histogramTTW_density     ) sumBinContents += histogramTTW_density->GetBinContent(iBin);
	if      ( histogramTTZ_density     ) sumBinContents += histogramTTZ_density->GetBinContent(iBin);
	if      ( histogramTT_density      ) sumBinContents += histogramTT_density->GetBinContent(iBin);
	if      ( histogramEWK_density     ) sumBinContents += histogramEWK_density->GetBinContent(iBin);
	else if ( histogramDiboson_density ) sumBinContents += histogramDiboson_density->GetBinContent(iBin);
	else if ( histogramWZ_density      ) sumBinContents += histogramWZ_density->GetBinContent(iBin);
	if      ( histogramRares_density   ) sumBinContents += histogramRares_density->GetBinContent(iBin);
	if      ( histogramFakes_density   ) sumBinContents += histogramFakes_density->GetBinContent(iBin);
	if      ( histogramFlips_density   ) sumBinContents += histogramFlips_density->GetBinContent(iBin);
	histogramUncertainty_density->SetBinContent(iBin, sumBinContents);
      }
      histogramUncertainty_density->SetFillColor(kBlack);
      histogramUncertainty_density->SetFillStyle(3344);    
      histogramUncertainty_density->Draw("e2same");
      legend->AddEntry(histogramUncertainty_density, "Uncertainty", "f");
    }
    
    if ( histogramData_blinded_density ) {
      histogramData_blinded_density->Draw("epsame");
      histogramData_blinded_density->Draw("axissame");
    }

    legend->Draw();

    TPaveText* labelOnTop_pave = 0;
    if ( labelOnTop != "" ) {
      labelOnTop_pave = new TPaveText(0.165, 0.95, 0.61, 1.00, "brNDC");
      labelOnTop_pave->AddText(labelOnTop.data());
      labelOnTop_pave->SetFillColor(10);
      labelOnTop_pave->SetBorderSize(0);
      labelOnTop_pave->SetTextColor(1);
      labelOnTop_pave->SetTextAlign(12);
      labelOnTop_pave->SetTextSize(0.045);
      labelOnTop_pave->Draw();
    }
    TPaveText* extraLabels_pave = 0;
    if ( extraLabels.size() > 0 ) {
      extraLabels_pave = new TPaveText(labelPosX, labelPosY, labelPosX + labelSizeX, labelPosY + labelSizeY, "brNDC");
      for ( std::vector<std::string>::const_iterator extraLabel = extraLabels.begin();
	    extraLabel != extraLabels.end(); ++extraLabel ) {
	extraLabels_pave->AddText(extraLabel->data());
      }
      extraLabels_pave->SetFillColor(10);
      extraLabels_pave->SetBorderSize(0);
      extraLabels_pave->SetTextColor(1);
      extraLabels_pave->SetTextAlign(12);
      extraLabels_pave->SetTextSize(labelTextSize);
      extraLabels_pave->Draw();
    }

    canvas->cd();
    bottomPad->Draw();
    bottomPad->cd();

    TH1* histogramSum = 0;
    TH1* histogramRatio = 0;
    TH1* histogramRatioUncertainty = 0;
    TF1* line = 0;
    if ( histogramData && histogramData_blinded ) {
      histogramSum = (TH1*)histogramData->Clone("histogramSum");
      histogramSum->Reset();
      if ( !histogramSum->GetSumw2N() ) histogramSum->Sumw2();
      if      ( histogramSignal  ) histogramSum->Add(histogramSignal);
      if      ( histogramTTW     ) histogramSum->Add(histogramTTW);
      if      ( histogramTTZ     ) histogramSum->Add(histogramTTZ);
      if      ( histogramTT      ) histogramSum->Add(histogramTT);
      if      ( histogramEWK     ) histogramSum->Add(histogramEWK);
      else if ( histogramDiboson ) histogramSum->Add(histogramDiboson);
      else if ( histogramWZ      ) histogramSum->Add(histogramWZ);
      if      ( histogramRares   ) histogramSum->Add(histogramRares);
      if      ( histogramFakes   ) histogramSum->Add(histogramFakes);
      if      ( histogramFlips   ) histogramSum->Add(histogramFlips);
      histogramRatio = (TH1*)histogramData->Clone("histogramRatio");
      histogramRatio->Reset();
      if ( !histogramRatio->GetSumw2N() ) histogramRatio->Sumw2();
      checkCompatibleBinning(histogramRatio, histogramSum);
      histogramRatio->Divide(histogramData, histogramSum);
      int numBins_bottom = histogramRatio->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins_bottom; ++iBin ) {
	double binContent = histogramRatio->GetBinContent(iBin);
	if ( histogramData_blinded && histogramData_blinded->GetBinContent(iBin) >= 0. ) histogramRatio->SetBinContent(iBin, binContent - 1.0);
	else histogramRatio->SetBinContent(iBin, -10.);
	//std::cout << " bin #" << iBin << " (x = " << histogramRatio->GetBinCenter(iBin) << "): ratio = " << histogramRatio->GetBinContent(iBin) << std::endl;
      }

      histogramRatio->SetTitle("");
      histogramRatio->SetStats(false);
      histogramRatio->SetMinimum(-0.50);
      histogramRatio->SetMaximum(+0.50);
      histogramRatio->SetMarkerStyle(histogramData_blinded_density->GetMarkerStyle());
      histogramRatio->SetMarkerSize(histogramData_blinded_density->GetMarkerSize());
      histogramRatio->SetMarkerColor(histogramData_blinded_density->GetMarkerColor());
      histogramRatio->SetLineColor(histogramData_blinded_density->GetLineColor());

      TAxis* xAxis_bottom = histogramRatio->GetXaxis();
      if ( xMin >= 0. && xMax > xMin ) xAxis_bottom->SetRangeUser(xMin, xMax);
      xAxis_bottom->SetTitle(xAxis_top->GetTitle());
      xAxis_bottom->SetLabelColor(1);
      xAxis_bottom->SetTitleColor(1);
      xAxis_bottom->SetTitleOffset(1.20);
      xAxis_bottom->SetTitleSize(0.12);
      xAxis_bottom->SetLabelOffset(0.02);
      xAxis_bottom->SetLabelSize(0.10);
      xAxis_bottom->SetTickLength(0.055);
      
      TAxis* yAxis_bottom = histogramRatio->GetYaxis();
      yAxis_bottom->SetTitle("#frac{Data - Simulation}{Simulation}");
      yAxis_bottom->SetTitleOffset(0.80);
      yAxis_bottom->SetNdivisions(505);
      yAxis_bottom->CenterTitle();
      yAxis_bottom->SetTitleSize(0.09);
      yAxis_bottom->SetLabelSize(0.10);
      yAxis_bottom->SetTickLength(0.04);  
      
      if ( histogramUncertainty ) {
	histogramRatioUncertainty = (TH1*)histogramUncertainty->Clone("histogramRatioUncertainty");
	if ( !histogramRatioUncertainty->GetSumw2N() ) histogramRatioUncertainty->Sumw2();
	checkCompatibleBinning(histogramRatioUncertainty, histogramSum);
	histogramRatioUncertainty->Divide(histogramSum);
	int numBins = histogramRatioUncertainty->GetNbinsX();
	for ( int iBin = 1; iBin <= numBins; ++iBin ) {
	  double binContent = histogramRatioUncertainty->GetBinContent(iBin);
	  histogramRatioUncertainty->SetBinContent(iBin, binContent - 1.0);
	}
	histogramRatioUncertainty->SetFillColor(histogramUncertainty_density->GetFillColor());
	//histogramRatioUncertainty->SetFillStyle(histogramUncertainty_density->GetFillStyle());    
	histogramRatioUncertainty->SetFillStyle(3644);    
      }
      histogramRatio->Draw("ep");

      line = new TF1("line","0", xAxis_bottom->GetXmin(), xAxis_bottom->GetXmax());
      line->SetLineStyle(3);
      line->SetLineWidth(1.5);
      line->SetLineColor(kBlack);
      line->Draw("same");
      
      if ( histogramRatioUncertainty ) {
	//printHistogram(histogramRatioUncertainty);
	histogramRatioUncertainty->Draw("e2same");
      }
      
      histogramRatio->Draw("epsame");
    }

    canvas->Update();
    size_t idx = outputFileName.find(".");
    std::string outputFileName_plot(outputFileName, 0, idx);
    if ( useLogScale ) outputFileName_plot.append("_log");
    else outputFileName_plot.append("_linear");
    if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
    canvas->Print(std::string(outputFileName_plot).append(".png").data());
    canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
    canvas->Print(std::string(outputFileName_plot).append(".root").data());

    delete histogramData_density;
    delete histogramData_blinded_density;
    delete histogramSignal_density;
    delete histogramTTW_density;
    delete histogramTTZ_density;
    delete histogramTT_density;
    delete histogramWZ_density;
    delete histogramDiboson_density;
    delete histogramEWK_density;
    delete histogramRares_density;
    delete histogramFakes_density;
    delete histogramFlips_density;
    delete histogramSum_density;
    delete histogramUncertainty_density;
    delete legend;
    delete labelOnTop_pave;
    delete extraLabels_pave;
    delete topPad;
    delete histogramSum;
    delete histogramRatio;
    delete histogramRatioUncertainty;
    delete line;
    delete bottomPad;    
    delete canvas;
  }
}

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  std::cout << "<makePlots>:" << std::endl;

  gROOT->SetBatch(true);

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("makePlots");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("makePlots") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgMakePlots = cfg.getParameter<edm::ParameterSet>("makePlots");

  std::vector<categoryEntryType*> categories;
  edm::VParameterSet cfgCategories = cfgMakePlots.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
  }

  std::string processData  = cfgMakePlots.getParameter<std::string>("processData");
  vstring processesBackground = cfgMakePlots.getParameter<vstring>("processesBackground");
  std::string processSignal = cfgMakePlots.getParameter<std::string>("processSignal");

  std::vector<plotEntryType*> distributions;
  edm::VParameterSet cfgDistributions = cfgMakePlots.getParameter<edm::VParameterSet>("distributions");
  for ( edm::VParameterSet::const_iterator cfgDistribution = cfgDistributions.begin();
	cfgDistribution != cfgDistributions.end(); ++cfgDistribution ) {
    std::string histogramName = cfgDistribution->getParameter<std::string>("histogramName");
    size_t idx = histogramName.find_last_of("/");
    std::string histogramName_wrt_subdir = ( idx < (histogramName.length() - 1) ) ?
      std::string(histogramName, idx + 1) : histogramName;
    edm::ParameterSet cfgDistribution_modified(*cfgDistribution);
    cfgDistribution_modified.addParameter<std::string>("outputFileName", histogramName_wrt_subdir);
    plotEntryType* distribution = new plotEntryType(cfgDistribution_modified);
    distributions.push_back(distribution);
  }

  edm::ParameterSet cfgNuisanceParameters = cfgMakePlots.getParameter<edm::ParameterSet>("nuisanceParameters");
  HistogramManager histogramManager(processesBackground, processSignal, categories, cfgNuisanceParameters);
  bool showUncertainty = cfgMakePlots.getParameter<bool>("showUncertainty");

  std::string labelOnTop_string = cfgMakePlots.getParameter<std::string>("labelOnTop");
  double intLumiData = cfgMakePlots.getParameter<double>("intLumiData");
  std::string labelOnTop = Form(labelOnTop_string.data(), intLumiData);
  
  std::string outputFileName = cfgMakePlots.getParameter<std::string>("outputFileName");

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("makePlots") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());
  
  for ( std::vector<categoryEntryType*>::iterator category = categories.begin();
	category != categories.end(); ++category ) {
    std::cout << "processing category = " << (*category)->name_ << std::endl;

    TDirectory* dir = getDirectory(inputFile, (*category)->name_, true);
    assert(dir);

    for ( std::vector<plotEntryType*>::iterator distribution = distributions.begin();
	  distribution != distributions.end(); ++distribution ) {

      TH1* histogramData = 0;
      TH1* histogramData_blinded = 0;
      if ( processData != "" ) {
	histogramData = getHistogram_wrapper(dir, processData, (*distribution)->histogramName_, "central", true);
	if ( (*distribution)->keepBlinded_.size() >= 1 ) histogramData_blinded = blindHistogram(histogramData, (*distribution)->keepBlinded_);
	else histogramData_blinded = histogramData; 
      }

      histogramManager.setDirectory(dir);
      histogramManager.setCategory((*category)->name_);
      histogramManager.setHistogram((*distribution)->histogramName_);
      histogramManager.update();

      std::vector<histogramEntryType*> histogramsBackground;
      for ( vstring::const_iterator processBackground = processesBackground.begin();
	    processBackground != processesBackground.end(); ++processBackground ) {
	TH1* histogramBackground = histogramManager.getHistogramPrefit(*processBackground, true);
	histogramsBackground.push_back(new histogramEntryType(*processBackground, histogramBackground));
      }
      
      TH1* histogramSignal = histogramManager.getHistogramPrefit(processSignal, true);
      
      TH1* histogramUncertainty = 0;
      if ( showUncertainty ) {
	histogramUncertainty = histogramManager.getHistogramUncertainty();
      }
            
      vstring extraLabels;
      if ( (*category)->label_ != "" ) extraLabels.push_back((*category)->label_);
      double extraLabelsSizeX = 0.12;

      size_t idx = outputFileName.find(".");
      std::string outputFileName_plot(outputFileName, 0, idx);
      outputFileName_plot.append(Form("_%s", (*distribution)->outputFileName_.data()));
      if ( idx != std::string::npos ) outputFileName_plot.append(std::string(outputFileName, idx));
	  
      makePlot(800, 900,
	       histogramData, histogramData_blinded,
	       histogramsBackground,
	       histogramSignal,
	       histogramUncertainty,
	       (*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	       labelOnTop,
	       extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	       (*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	       true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	       outputFileName_plot);
      makePlot(800, 900,
	       histogramData, histogramData_blinded,
	       histogramsBackground,
	       histogramSignal,
	       histogramUncertainty,
	       (*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	       labelOnTop,
	       extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	       (*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	       false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	       outputFileName_plot);

      if ( histogramData_blinded != histogramData ) delete histogramData_blinded;
    }
  }

  delete inputFile;
  
  for ( std::vector<categoryEntryType*>::iterator it = categories.begin();
	it != categories.end(); ++it ) {
    delete (*it);
  }
  for ( std::vector<plotEntryType*>::iterator it = distributions.begin();
	it != distributions.end(); ++it ) {
    delete (*it);
  }

  clock.Show("makePlots");

  return 0;
}

