#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TDirectory.h>
#include <TMath.h>
#include <TPRegexp.h>
#include <TObjString.h>
#include <TObjArray.h>

#include <iostream>
#include <assert.h>

typedef std::vector<std::string> vstring;
typedef std::pair<double, double> pdouble; 

histogramEntryType::histogramEntryType(const std::string& process, TH1* histogram)
  : process_(process),
    histogram_(histogram)
{}

plotEntryType::plotEntryType(const edm::ParameterSet& cfg)
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
HistogramManager::HistogramManager(const vstring& processesBackground, const std::string& processSignal, const vstring& categories, const edm::ParameterSet& cfg)
  : currentDir_(0),	
    isUpToDate_(false),
    histogram_uncertainty_(0)
{
  processes_ = processesBackground;
  processes_.push_back(processSignal);
  
  edm::ParameterSet cfgNormalization = cfg.getParameter<edm::ParameterSet>("normalization");
  for ( vstring::const_iterator process = processes_.begin();
	process != processes_.end(); ++process ) {
    for ( vstring::const_iterator category = categories.begin();
	  category != categories.end(); ++category ) {
      normEntryType processEntry;
      processEntry.process_ = (*process);
      processEntry.category_ = (*category);
      parseValue_and_Uncertainty(cfgNormalization.getParameter<std::string>(*process), processEntry.sf_, processEntry.sfErr_);
      normalizationValues_and_Uncertainties_[*process][*category] = processEntry;
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
HistogramManager::~HistogramManager()
{
  //for ( map_string_to_TH1::iterator it = histograms_postfit_.begin();
  //      it != histograms_postfit_.end(); ++it ) {
  //  delete it->second;
  //}
  //delete histogram_uncertainty_;
}

void HistogramManager::setDirectory(TDirectory* dir)
{
  currentDir_ = dir;
  isUpToDate_ = false;
}
void HistogramManager::setCategory(const std::string& category)
{
  currentCategory_ = category;
  isUpToDate_ = false;
}
void HistogramManager::setHistogram(const std::string& histogramName)
{
  currentHistogramName_ = histogramName;
  isUpToDate_ = false;
}

TH1* HistogramManager::getHistogramPrefit(const std::string& process, bool enableException)
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
TH1* HistogramManager::getHistogramPostfit(const std::string& process, bool enableException)
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
TH1* HistogramManager::getHistogramUncertainty()
{
  if ( !isUpToDate_ ) update();
  return histogram_uncertainty_;
}

void HistogramManager::getSF(const std::string& process, double& sf, double& sfErr)
{
  assert(normalizationValues_and_Uncertainties_.find(process) != normalizationValues_and_Uncertainties_.end());
  assert(normalizationValues_and_Uncertainties_[process].find(currentCategory_) != normalizationValues_and_Uncertainties_[process].end());
  sf = normalizationValues_and_Uncertainties_[process][currentCategory_].sf_;
  sfErr = normalizationValues_and_Uncertainties_[process][currentCategory_].sfErr_;
} 

void HistogramManager::update()
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
//-----------------------------------------------------------------------------

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

std::vector<plotEntryType*> readDistributions(const edm::VParameterSet& cfgDistributions)
{
  std::vector<plotEntryType*> distributions;
  for ( edm::VParameterSet::const_iterator cfgDistribution = cfgDistributions.begin();
	cfgDistribution != cfgDistributions.end(); ++cfgDistribution ) {
    TString histogramName = cfgDistribution->getParameter<std::string>("histogramName").data();
    TObjArray* histogramName_parts = histogramName.Tokenize("/");
    std::string histogramName_wrt_subdir;
    if ( histogramName_parts->GetEntries() >= 2 ) {
      TObjString* histogramName_part1 = dynamic_cast<TObjString*>(histogramName_parts->At(1));
      assert(histogramName_part1);
      histogramName_wrt_subdir.append(histogramName_part1->GetString().Data());
    }
    if ( histogramName_parts->GetEntries() >= 4 ) {
      TObjString* histogramName_part2 = dynamic_cast<TObjString*>(histogramName_parts->At(3));
      assert(histogramName_part2);
      if ( histogramName_wrt_subdir.length() > 0 ) histogramName_wrt_subdir.append("_");
      histogramName_wrt_subdir.append(histogramName_part2->GetString().Data());
    }
    edm::ParameterSet cfgDistribution_modified(*cfgDistribution);
    cfgDistribution_modified.addParameter<std::string>("outputFileName", histogramName_wrt_subdir);
    plotEntryType* distribution = new plotEntryType(cfgDistribution_modified);
    distributions.push_back(distribution);
  }
  return distributions;
}
