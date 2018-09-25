#include "tthAnalysis/HiggsToTauTau/interface/Plotter.h"

#include <TH1.h>
#include <THStack.h>
#include <TMath.h>
#include <TString.h> // Form
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TF1.h>
#include <TStyle.h>

typedef std::vector<std::string> vstring;
typedef std::pair<double, double> pdouble;

Plotter::Plotter(const TFile* inputFile, const edm::ParameterSet& cfg)
  : PlotterPluginBase(inputFile, cfg)
  , histogramManager_(nullptr)
{
  edm::VParameterSet cfgCategories = cfg.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories_.push_back(category);
    categoryNames_.push_back(category->name_);
  }

  processData_ = cfg.getParameter<std::string>("processData");
  processesBackground_ = cfg.getParameter<vstring>("processesBackground");
  processSignal_ = cfg.getParameter<std::string>("processSignal");

  edm::VParameterSet cfgDistributions = cfg.getParameter<edm::VParameterSet>("distributions");
  distributions_ = readDistributions(cfgDistributions);

  applyRebinning_ = cfg.getParameter<bool>("applyRebinning");
  apply_fixed_rebinning_ = cfg.getParameter<int>("apply_fixed_rebinning");
  apply_automatic_rebinning_ = cfg.getParameter<bool>("apply_automatic_rebinning");
  minEvents_automatic_rebinning_ = cfg.getParameter<double>("minEvents_automatic_rebinning");
  applyAutoBlinding_ = cfg.getParameter<bool>("applyAutoBlinding");
  divideByBinWidth_ = cfg.getParameter<bool>("divideByBinWidth");

  edm::ParameterSet cfgNuisanceParameters = cfg.getParameter<edm::ParameterSet>("nuisanceParameters");
  histogramManager_ = new HistogramManager(processesBackground_, processSignal_, categoryNames_, cfgNuisanceParameters);
  showUncertainty_ = cfg.getParameter<bool>("showUncertainty");

  std::string labelOnTop_string = cfg.getParameter<std::string>("labelOnTop");
  double intLumiData = cfg.getParameter<double>("intLumiData");
  labelOnTop_ = Form(labelOnTop_string.data(), intLumiData);
  
  outputFileName_ = cfg.getParameter<std::string>("outputFileName");
}

Plotter::~Plotter()
{
  for ( std::vector<categoryEntryType*>::iterator it = categories_.begin();
	it != categories_.end(); ++it ) {
    delete (*it);
  }

  for ( std::vector<plotEntryType*>::iterator it = distributions_.begin();
	it != distributions_.end(); ++it ) {
    delete (*it);
  }

  delete histogramManager_;
}

namespace
{
  std::vector<histogramEntryType*> getHistogramsBackground_clone(std::vector<histogramEntryType*>& histogramsBackground)
  {
    std::vector<histogramEntryType*> histogramsBackground_clone;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
          histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      std::string histogramNameBackground = Form("%s_", (*histogramBackground_entry)->histogram_->GetName() );
      TH1* histogramBackground = (TH1*)(*histogramBackground_entry)->histogram_->Clone(histogramNameBackground.data());
      const std::string& process = (*histogramBackground_entry)->process_;
      histogramsBackground_clone.push_back(new histogramEntryType(process, histogramBackground));
    }
    return histogramsBackground_clone ;
  }

  std::vector<histogramEntryType*> getHistogramsBackground_rebin(std::vector<histogramEntryType*>& histogramsBackground, int rebin)
  {
    std::vector<histogramEntryType*> histogramsBackground_rebin;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
          histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      TH1* histogramBackground = (TH1*)(*histogramBackground_entry)->histogram_;
      histogramBackground->Rebin(rebin);
      const std::string& process = (*histogramBackground_entry)->process_;
      histogramsBackground_rebin.push_back(new histogramEntryType(process, histogramBackground));
    }
    return histogramsBackground_rebin ;
  }

  std::vector<pdouble> getBlindedRanges(TH1* histogramData, std::vector<histogramEntryType*>& histogramsBackground, TH1* histogramSignal)
  {
    std::vector<pdouble> range;
    TH1* histogramBackgroundSum = 0;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
          histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      TH1* histogramBackground = (*histogramBackground_entry)->histogram_;
      checkCompatibleBinning(histogramSignal, histogramBackground);
      if(!histogramBackgroundSum) histogramBackgroundSum = (TH1*) histogramBackground->Clone("histogramBackgroundSum");
      histogramBackgroundSum->Add(histogramBackground);
    }
    int numBins = histogramData->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double x = histogramData->GetBinCenter(iBin);
      double w = histogramData->GetBinWidth(iBin);
      double s = histogramSignal->GetBinContent(iBin);
      double b = histogramBackgroundSum->GetBinContent(iBin);
      if((s/sqrt(b+pow(0.09*b, 2))) >= 0.5){
	double xmin = x - 0.5*w;
	double xmax = x + 0.5*w;
	range.push_back(pdouble(xmin, xmax));
      }
    }
    return range;
  }
  
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
      //      std::cout << "BinCenter = " << x << ": isBlinded = " << isBlinded << std::endl;
      if ( isBlinded ) {
	blindedHistogram->SetBinContent(iBin, -10.);
	blindedHistogram->SetBinError(iBin, 0.);
      }
    }
    //std::cout << "histogram: name = " << histogram->GetName() << ", integral = " << histogram->Integral() << std::endl;
    //std::cout << "histogram(blinded): name = " << blindedHistogram->GetName() << ", integral = " << blindedHistogram->Integral() << std::endl;
    return blindedHistogram;
  }
}

void Plotter::makePlots()
{
  for ( std::vector<categoryEntryType*>::iterator category = categories_.begin();
	category != categories_.end(); ++category ) {
    std::cout << "processing category = " << (*category)->name_ << std::endl;
    
    TDirectory* dir = getDirectory(inputFile_, (*category)->name_, true);
    assert(dir);
    
    for ( std::vector<plotEntryType*>::iterator distribution = distributions_.begin();
	  distribution != distributions_.end(); ++distribution ) {
      
      TH1* histogramData = 0;
      if ( processData_ != "" ) {
	histogramData = getHistogram_wrapper(dir, processData_, (*distribution)->histogramName_, "central", true);
      }

      histogramManager_->setDirectory(dir);
      histogramManager_->setCategory((*category)->name_);
      histogramManager_->setHistogram((*distribution)->histogramName_);
      histogramManager_->update();

      TH1* histogramBackgroundSum = 0;
      std::vector<histogramEntryType*> histogramsBackground;
      for ( vstring::const_iterator processBackground = processesBackground_.begin();
	    processBackground != processesBackground_.end(); ++processBackground ) {
	TH1* histogramBackground = histogramManager_->getHistogramPrefit(*processBackground, true);
	histogramsBackground.push_back(new histogramEntryType(*processBackground, histogramBackground));
	if   ( !histogramBackgroundSum ) histogramBackgroundSum = (TH1*)histogramBackground->Clone(Form("%s_BackgroundSum", (*category)->name_.data()));
	else                             histogramBackgroundSum->Add(histogramBackground);
      }

      TH1* histogramSignal = histogramManager_->getHistogramPrefit(processSignal_, true);

      std::vector<pdouble> keepBlinded = getBlindedRanges(histogramData, histogramsBackground, histogramSignal);
      TH1* histogramData_blinded = 0;
      if ( processData_ != "" ) {
	if ( keepBlinded.size() >= 1 && applyAutoBlinding_ ) histogramData_blinded = blindHistogram(histogramData, keepBlinded);
	else{
	  std::string histogramNameData_blinded = Form("%s_blinded", histogramData->GetName());
	  histogramData_blinded = (TH1*)histogramData->Clone(histogramNameData_blinded.data());
	}
      }

      TH1* histogramUncertainty = 0;
      if ( showUncertainty_ ) {
        histogramUncertainty = histogramManager_->getHistogramUncertainty();
      }

      std::string histogramNameData_rebinned = Form("%s_rebinned", histogramData->GetName());
      TH1* histogramData_rebinned = (TH1*)histogramData->Clone(histogramNameData_rebinned.data());
      std::vector<histogramEntryType*> histogramsBackground_rebinned = getHistogramsBackground_clone(histogramsBackground);
      std::string histogramNameSignal_rebinned = Form("%s_rebinned_fixed", histogramSignal->GetName()); 
      TH1* histogramSignal_rebinned = (TH1*)histogramSignal->Clone(histogramNameSignal_rebinned.data());
      std::string histogramNameBackgroundSum_rebinned = Form("%s_rebinned",histogramBackgroundSum->GetName());
      TH1* histogramBackgroundSum_rebinned = (TH1*)histogramBackgroundSum->Clone(histogramNameBackgroundSum_rebinned.data());
      TH1* histogramData_blinded_rebinned = 0;
      TH1* histogramUncertainty_rebinned = 0;
      int apply_fixed_rebinning = 1;
      if ( applyRebinning_ ) {
	//if ( apply_fixed_rebinning_ > 1 && !apply_automatic_rebinning_ ) {
	if ( apply_fixed_rebinning_ ){
	  TArrayD histogramBinning_output = getBinning(histogramData_rebinned);
	  int numBins_output = histogramBinning_output.GetSize() - 1;
	  if ( numBins_output < 10 ) {
	    apply_fixed_rebinning = 1;
	  } else if ( numBins_output <= 20 ) {
	    if ( (numBins_output % 2) == 0 ) apply_fixed_rebinning = 2;
	    else apply_fixed_rebinning = 1;
	  } else if ( numBins_output <= 40 ) {
	    if ( (numBins_output % 3) == 0) apply_fixed_rebinning = 3;
	    else if ( (numBins_output % 2) == 0) apply_fixed_rebinning = 2;
	    else apply_fixed_rebinning = 1;
	  } else {
	    if ( (numBins_output % 5) == 0) apply_fixed_rebinning = 5;
	    else if ( (numBins_output % 4) == 0) apply_fixed_rebinning = 4;
	    else if ( (numBins_output % 3) == 0) apply_fixed_rebinning = 3;
	    else if ( (numBins_output % 2) == 0) apply_fixed_rebinning = 2;
	    else apply_fixed_rebinning = 1;
	  }
	  histogramData_rebinned->Rebin(apply_fixed_rebinning);
	  histogramSignal_rebinned->Rebin(apply_fixed_rebinning);
	  getHistogramsBackground_rebin(histogramsBackground_rebinned, apply_fixed_rebinning);
	  histogramBackgroundSum_rebinned->Rebin(apply_fixed_rebinning); 
	}

	TH1* histogramData_tmp = 0;
	std::vector<histogramEntryType*> histogramsBackground_tmp;
	TH1* histogramSignal_tmp = 0;
	if ( apply_automatic_rebinning_ ) {
	  TArrayD histogramBinning;
	  if ( (*distribution)->hasExplicitBinning() ){
	    histogramBinning = getTArraDfromVector((*distribution)->explicitBinning_);
	  } else {
	    histogramBinning = getRebinnedBinning(histogramBackgroundSum_rebinned, minEvents_automatic_rebinning_);
	  }
	  histogramData_tmp = getRebinnedHistogram1d(histogramData_rebinned, 4, histogramBinning, true);
	  histogramSignal_tmp = getRebinnedHistogram1d(histogramSignal_rebinned, 4, histogramBinning, true);
	  for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground_rebinned.begin(); 
		histogramBackground_entry != histogramsBackground_rebinned.end(); ++histogramBackground_entry ) {
	    TH1* histogramBackground = (*histogramBackground_entry)->histogram_;
	    const std::string& process = (*histogramBackground_entry)->process_;
	    TH1* histogramBackground_tmp = getRebinnedHistogram1d(histogramBackground, 4, histogramBinning, true);
	    histogramsBackground_tmp.push_back(new histogramEntryType(process, histogramBackground_tmp));
	  }
	  histogramData_rebinned = histogramData_tmp;
	  histogramsBackground_rebinned = histogramsBackground_tmp;
	  histogramSignal_rebinned = histogramSignal_tmp;
	}

	std::vector<pdouble> keepBlinded = getBlindedRanges(histogramData_rebinned, histogramsBackground_rebinned, histogramSignal_rebinned);
	if ( processData_ != "" ) {
	  if ( keepBlinded.size() >= 1 && applyAutoBlinding_ ) histogramData_blinded_rebinned = blindHistogram(histogramData_rebinned, keepBlinded);
	  else histogramData_blinded_rebinned = (TH1*)histogramData_rebinned->Clone("rebinned_data");
	}

	if ( showUncertainty_ ) {
	  histogramUncertainty_rebinned = histogramManager_->getHistogramUncertainty();
	}
      }

      vstring extraLabels;
      if ( (*category)->label_ != "" ) extraLabels.push_back((*category)->label_);
      double extraLabelsSizeX = 0.12;

      size_t idx = outputFileName_.find(".");
      std::string outputFileName_plot(outputFileName_, 0, idx);
      outputFileName_plot.append(Form("_%s", (*distribution)->outputFileName_.data()));
      if ( idx != std::string::npos ) outputFileName_plot.append(std::string(outputFileName_, idx));
	  
      makePlot(
        800, 900, 
	histogramData, histogramData_blinded, 
	histogramsBackground, 
	histogramSignal, 
	histogramUncertainty, 
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop_,  
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(), 
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot, 
	false, 
	divideByBinWidth_);
      makePlot(
        800, 900, 
	histogramData, histogramData_blinded, 
	histogramsBackground, 
	histogramSignal, 
	histogramUncertainty, 
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop_,  
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(), 
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot, 
	false, 
	divideByBinWidth_);

      if ( applyRebinning_ ){
	makePlot(
          800, 900, 
	  histogramData_rebinned, histogramData_blinded_rebinned, 
	  histogramsBackground_rebinned, 
	  histogramSignal_rebinned, 
	  histogramUncertainty_rebinned, 
	  (*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	  labelOnTop_,	
	  extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(), 
	  (*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	  true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	  outputFileName_plot, 
	  true, 
	  divideByBinWidth_);
	makePlot(
          800, 900, 
	  histogramData_rebinned, histogramData_blinded_rebinned,
	  histogramsBackground_rebinned, 
	  histogramSignal_rebinned, 
	  histogramUncertainty_rebinned, 
	  (*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	  labelOnTop_, 
	  extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(), 
	  (*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	  false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	  outputFileName_plot, 
	  true, 
	  divideByBinWidth_);
      }
      delete histogramData;
      delete histogramSignal;
      delete histogramBackgroundSum;
      histogramsBackground.clear();
      delete histogramData_blinded;
      delete histogramUncertainty;
      delete histogramData_rebinned;
      delete histogramSignal_rebinned;
      delete histogramBackgroundSum_rebinned;
      delete histogramData_blinded_rebinned;
      histogramsBackground_rebinned.clear();
      delete histogramUncertainty_rebinned;
      for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin(); 
	    histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
        delete (*histogramBackground_entry)->histogram_;
      }
      for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground_rebinned.begin();
	    histogramBackground_entry != histogramsBackground_rebinned.end(); ++histogramBackground_entry ) {
	delete (*histogramBackground_entry)->histogram_;
      }
    }
  }
}
