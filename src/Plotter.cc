#include "tthAnalysis/HiggsToTauTau/interface/Plotter.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

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

Plotter::Plotter(const TFile * inputFile,
                 const edm::ParameterSet & cfg)
  : PlotterPluginBase(inputFile, cfg)
  , processData_(cfg.getParameter<std::string>("processData"))
  , processesBackground_(cfg.getParameter<vstring>("processesBackground"))
  , processSignal_(cfg.getParameter<std::string>("processSignal"))
  , applyRebinning_(cfg.getParameter<bool>("applyRebinning"))
  , apply_fixed_rebinning_(cfg.getParameter<int>("apply_fixed_rebinning"))
  , apply_automatic_rebinning_(cfg.getParameter<bool>("apply_automatic_rebinning"))
  , minEvents_automatic_rebinning_(cfg.getParameter<double>("minEvents_automatic_rebinning"))
  , applyAutoBlinding_(cfg.getParameter<bool>("applyAutoBlinding"))
  , divideByBinWidth_(cfg.getParameter<bool>("divideByBinWidth"))
  , histogramManager_(nullptr)
  , showUncertainty_(cfg.getParameter<bool>("showUncertainty"))
  , legendTextSize_(cfg.getParameter<double>("legendTextSize"))
  , legendPosX_(cfg.getParameter<double>("legendPosX"))
  , legendPosY_(cfg.getParameter<double>("legendPosY"))
  , legendSizeX_(cfg.getParameter<double>("legendSizeX"))
  , legendSizeY_(cfg.getParameter<double>("legendSizeY"))
  , outputFileName_(cfg.getParameter<std::string>("outputFileName"))
{
  const edm::VParameterSet cfgCategories = cfg.getParameter<edm::VParameterSet>("categories");
  for(const edm::ParameterSet & cfgCategory: cfgCategories)
  {
    categoryEntryType * category = new categoryEntryType(cfgCategory);
    categories_.push_back(category);
    categoryNames_.push_back(category->name_);
  }

  const edm::VParameterSet cfgDistributions = cfg.getParameter<edm::VParameterSet>("distributions");
  distributions_ = readDistributions(cfgDistributions);

  const edm::ParameterSet cfgNuisanceParameters = cfg.getParameter<edm::ParameterSet>("nuisanceParameters");
  histogramManager_ = new HistogramManager(processesBackground_, processSignal_, categoryNames_, cfgNuisanceParameters);

  const std::string labelOnTop_string = cfg.getParameter<std::string>("labelOnTop");
  const double intLumiData = cfg.getParameter<double>("intLumiData");
  labelOnTop_ = Form(labelOnTop_string.data(), intLumiData);
}

Plotter::~Plotter()
{
  for(categoryEntryType * it: categories_)
  {
    delete it;
  }
  for(plotEntryType * it: distributions_)
  {
    delete it;
  }
  delete histogramManager_;
}

namespace
{
  std::vector<histogramEntryType *>
  getHistogramsBackground_clone(std::vector<histogramEntryType *> & histogramsBackground)
  {
    std::vector<histogramEntryType*> histogramsBackground_clone;
    for(histogramEntryType * histogramBackground_entry: histogramsBackground)
    {
      const std::string histogramNameBackground = Form("%s_", histogramBackground_entry->histogram_->GetName() );
      TH1 * histogramBackground = static_cast<TH1 *>(histogramBackground_entry->histogram_->Clone(histogramNameBackground.data()));
      const std::string & process = histogramBackground_entry->process_;
      histogramsBackground_clone.push_back(new histogramEntryType(process, histogramBackground));
    }
    return histogramsBackground_clone ;
  }

  std::vector<histogramEntryType *>
  getHistogramsBackground_rebin(std::vector<histogramEntryType *> & histogramsBackground,
                                int rebin)
  {
    std::vector<histogramEntryType*> histogramsBackground_rebin;
    for(histogramEntryType * histogramBackground_entry: histogramsBackground)
    {
      TH1 * histogramBackground = static_cast<TH1 *>(histogramBackground_entry->histogram_);
      histogramBackground->Rebin(rebin);
      const std::string & process = histogramBackground_entry->process_;
      histogramsBackground_rebin.push_back(new histogramEntryType(process, histogramBackground));
    }
    return histogramsBackground_rebin ;
  }

  std::vector<pdouble>
  getBlindedRanges(TH1 * histogramData,
                   std::vector<histogramEntryType *> & histogramsBackground,
                   TH1 * histogramSignal)
  {
    std::vector<pdouble> range;
    TH1* histogramBackgroundSum = nullptr;
    for(histogramEntryType * histogramBackground_entry: histogramsBackground)
    {
      TH1 * histogramBackground = histogramBackground_entry->histogram_;

      if     (histogramData         ) checkCompatibleBinning(histogramData, histogramBackground);
      else if(histogramSignal       ) checkCompatibleBinning(histogramSignal, histogramBackground);
      else if(histogramBackgroundSum) checkCompatibleBinning(histogramBackgroundSum, histogramBackground);

      if(!histogramBackgroundSum)
      {
        histogramBackgroundSum = static_cast<TH1 *>(histogramBackground->Clone("histogramBackgroundSum"));
      }
      histogramBackgroundSum->Add(histogramBackground);
    }

    const int numBins = histogramData->GetNbinsX();
    for(int iBin = 1; iBin <= numBins; ++iBin)
    {
      TH1 * histogramRef = nullptr;
      if     (histogramData  ) histogramRef = histogramData;
      else if(histogramSignal) histogramRef = histogramSignal;
      else                     histogramRef = histogramBackgroundSum;
      assert(histogramRef);

      const double x = histogramRef->GetBinCenter(iBin);
      const double w = histogramRef->GetBinWidth(iBin);
      const double s = ( histogramSignal ) ? histogramSignal->GetBinContent(iBin) : 0.;
      const double b = histogramBackgroundSum->GetBinContent(iBin);
      if((s / std::sqrt(b + std::pow(0.09 * b, 2))) >= 0.5)
      {
        const double xmin = x - 0.5 * w;
        const double xmax = x + 0.5 * w;
        range.push_back(pdouble(xmin, xmax));
      }
    }
    return range;
  }

  TH1 *
  blindHistogram(TH1 * histogram,
                 const std::vector<pdouble> & keepBlinded)
  {
    const std::string blindedHistogramName = Form("%s_blinded", histogram->GetName());
    TH1 * blindedHistogram = static_cast<TH1 *>(histogram->Clone(blindedHistogramName.data()));
    if(! blindedHistogram->GetSumw2N())
    {
      blindedHistogram->Sumw2();
    }
    const int numBins = histogram->GetNbinsX();
    for(int iBin = 1; iBin <= numBins; ++iBin)
    {
      const double x = histogram->GetBinCenter(iBin);
      bool isBlinded = false;
      for(pdouble keepBlinded_it: keepBlinded)
      {
        if(x >= keepBlinded_it.first && x <= keepBlinded_it.second)
        {
          isBlinded = true;
          break;
        }
      }
      if(isBlinded)
      {
        blindedHistogram->SetBinContent(iBin, -10.);
        blindedHistogram->SetBinError(iBin, 0.);
      }
    }
    return blindedHistogram;
  }
}

void
Plotter::makePlots()
{
  for(categoryEntryType * category: categories_)
  {
    std::cout << "processing category = " << category->name_ << '\n';
    
    TDirectory * dir = getDirectory(inputFile_, category->name_, true);
    assert(dir);

    for(plotEntryType * distribution: distributions_)
    {
      
      TH1 * histogramData = nullptr;
      if(! processData_.empty())
      {
        histogramData = getHistogram_wrapper(dir, processData_, distribution->histogramName_, "central", true);
      }

      histogramManager_->setDirectory(dir);
      histogramManager_->setCategory(category->name_);
      histogramManager_->setHistogram(distribution->histogramName_);
      histogramManager_->update();

      TH1 * histogramBackgroundSum = nullptr;
      std::vector<histogramEntryType *> histogramsBackground;
      for(const std::string & processBackground: processesBackground_)
      {
        TH1 * histogramBackground = histogramManager_->getHistogramPrefit(processBackground, true);
        histogramsBackground.push_back(new histogramEntryType(processBackground, histogramBackground));

        if(! histogramBackgroundSum)
        {
          histogramBackgroundSum = static_cast<TH1 *>(histogramBackground->Clone(Form("%s_BackgroundSum", category->name_.data())));
        }
        else
        {
          histogramBackgroundSum->Add(histogramBackground);
        }
      }

      TH1 * histogramSignal = nullptr;
      if(! processSignal_.empty())
      {
        histogramSignal = histogramManager_->getHistogramPrefit(processSignal_, true);
      }

      const std::vector<pdouble> keepBlinded = getBlindedRanges(histogramData, histogramsBackground, histogramSignal);
      TH1 * histogramData_blinded = nullptr;
      if(! processData_.empty())
      {
        if(keepBlinded.size() >= 1 && applyAutoBlinding_)
        {
          histogramData_blinded = blindHistogram(histogramData, keepBlinded);
        }
        else
        {
          const std::string histogramNameData_blinded = Form("%s_blinded", histogramData->GetName());
          histogramData_blinded = static_cast<TH1 *>(histogramData->Clone(histogramNameData_blinded.data()));
        }
      }

      TH1 * histogramUncertainty = nullptr;
      if(showUncertainty_)
      {
        histogramUncertainty = histogramManager_->getHistogramUncertainty();
      }

      vstring extraLabels;
      if(! category->label_.empty())
      {
        extraLabels.push_back(category->label_);
      }
      const double extraLabelsSizeX = 0.12;

      const std::size_t idx = outputFileName_.find(".");
      std::string outputFileName_plot(outputFileName_, 0, idx);
      outputFileName_plot.append(
        TString(Form("_%s_%s", category->name_.data(), distribution->outputFileName_.data())).ReplaceAll("/", "_")
      );
      if(idx != std::string::npos)
      {
        outputFileName_plot.append(std::string(outputFileName_, idx));
      }

      makePlot(
        800, 900,
        histogramData, histogramData_blinded,
        histogramsBackground,
        histogramSignal,
        histogramUncertainty,
        legendTextSize_, legendPosX_, legendPosY_, legendSizeX_, legendSizeY_,
        labelOnTop_,
        extraLabels, 0.055, 0.185, 0.915 - 0.055 * extraLabels.size(), extraLabelsSizeX, 0.055 * extraLabels.size(),
        distribution->xMin_, distribution->xMax_, distribution->xAxisTitle_, distribution->xAxisOffset_,
        true, distribution->yMin_, distribution->yMax_, distribution->yAxisTitle_, distribution->yAxisOffset_,
        outputFileName_plot,
        false,
        divideByBinWidth_
      );
      makePlot(
        800, 900,
        histogramData, histogramData_blinded,
        histogramsBackground,
        histogramSignal,
        histogramUncertainty,
        legendTextSize_, legendPosX_, legendPosY_, legendSizeX_, legendSizeY_,
        labelOnTop_,
        extraLabels, 0.055, 0.185, 0.915 - 0.055 * extraLabels.size(), extraLabelsSizeX, 0.055 * extraLabels.size(),
        distribution->xMin_, distribution->xMax_, distribution->xAxisTitle_, distribution->xAxisOffset_,
        false, distribution->yMin_, distribution->yMax_, distribution->yAxisTitle_, distribution->yAxisOffset_,
        outputFileName_plot,
        false,
        divideByBinWidth_
      );

      const std::string histogramNameData_rebinned = Form("%s_rebinned", histogramData->GetName());
      TH1 * histogramData_rebinned = (TH1*)histogramData->Clone(histogramNameData_rebinned.data());

      std::vector<histogramEntryType*> histogramsBackground_rebinned = getHistogramsBackground_clone(histogramsBackground);
      TH1 * histogramSignal_rebinned = nullptr;
      if(! processSignal_.empty())
      {
        const std::string histogramNameSignal_rebinned = Form("%s_rebinned_fixed", histogramSignal->GetName());
        histogramSignal_rebinned = (TH1*)histogramSignal->Clone(histogramNameSignal_rebinned.data());
      }

      const std::string histogramNameBackgroundSum_rebinned = Form("%s_rebinned",histogramBackgroundSum->GetName());
      TH1 * histogramBackgroundSum_rebinned = static_cast<TH1 *>(histogramBackgroundSum->Clone(histogramNameBackgroundSum_rebinned.data()));
      TH1 * histogramData_blinded_rebinned = nullptr;
      TH1 * histogramUncertainty_rebinned = nullptr;
      int apply_fixed_rebinning = 1;
      if(applyRebinning_)
      {
        if(showUncertainty_)
        {
          histogramUncertainty_rebinned = static_cast<TH1 *>(histogramUncertainty->Clone(Form("%s_rebinned", histogramUncertainty->GetName())));
        }

        if(apply_fixed_rebinning_)
        {
          const TArrayD histogramBinning_output = getBinning(histogramData_rebinned);
          const int numBins_output = histogramBinning_output.GetSize() - 1;
          if(numBins_output < 10)
          {
            apply_fixed_rebinning = 1;
          }
          else if(numBins_output <= 20)
          {
            apply_fixed_rebinning = numBins_output % 2 == 0 ? 2 : 1;
          }
          else if( numBins_output <= 40)
          {
            apply_fixed_rebinning = numBins_output % 3 == 0 ? 3 : (numBins_output % 2 == 0 ? 2 : 1);
          }
          else
          {
            if     (numBins_output % 5 == 0) apply_fixed_rebinning = 5;
            else if(numBins_output % 4 == 0) apply_fixed_rebinning = 4;
            else if(numBins_output % 3 == 0) apply_fixed_rebinning = 3;
            else if(numBins_output % 2 == 0) apply_fixed_rebinning = 2;
            else                             apply_fixed_rebinning = 1;
          }

          histogramData_rebinned->Rebin(apply_fixed_rebinning);
          if(histogramSignal_rebinned)
          {
            histogramSignal_rebinned->Rebin(apply_fixed_rebinning);
          }
          getHistogramsBackground_rebin(histogramsBackground_rebinned, apply_fixed_rebinning);
          histogramBackgroundSum_rebinned->Rebin(apply_fixed_rebinning);
          if(showUncertainty_)
          {
            histogramUncertainty_rebinned->Rebin(apply_fixed_rebinning);
          }
        }

        TH1 * histogramData_tmp = nullptr;
        std::vector<histogramEntryType*> histogramsBackground_tmp;
        TH1 * histogramSignal_tmp = nullptr;
        if(apply_automatic_rebinning_)
        {
          TArrayD histogramBinning;
          if(distribution->hasExplicitBinning())
          {
            histogramBinning = getTArraDfromVector(distribution->explicitBinning_);
          }
          else
          {
            histogramBinning = getRebinnedBinning(histogramBackgroundSum_rebinned, minEvents_automatic_rebinning_);
          }

          histogramData_tmp = getRebinnedHistogram1d(histogramData_rebinned, 4, histogramBinning, true);
          if(histogramSignal_rebinned)
          {
            histogramSignal_tmp = getRebinnedHistogram1d(histogramSignal_rebinned, 4, histogramBinning, true);
          }

          for(histogramEntryType * histogramBackground_entry: histogramsBackground_rebinned)
          {
            TH1 * histogramBackground = histogramBackground_entry->histogram_;
            const std::string& process = histogramBackground_entry->process_;
            TH1 * histogramBackground_tmp = getRebinnedHistogram1d(histogramBackground, 4, histogramBinning, true);
            histogramsBackground_tmp.push_back(new histogramEntryType(process, histogramBackground_tmp));
          }
          histogramData_rebinned = histogramData_tmp;
          histogramsBackground_rebinned = histogramsBackground_tmp;
          histogramSignal_rebinned = histogramSignal_tmp;
          if(showUncertainty_)
          {
            TH1 * histogramUncertainty_rebinned_tmp = getRebinnedHistogram1d(histogramUncertainty_rebinned, 4, histogramBinning, true);
            histogramUncertainty_rebinned = histogramUncertainty_rebinned_tmp;
          }
        }

        const std::vector<pdouble> keepBlinded_rebinned = getBlindedRanges(
          histogramData_rebinned, histogramsBackground_rebinned, histogramSignal_rebinned
        );
        if(! processData_.empty())
        {
          if(keepBlinded_rebinned.size() >= 1 && applyAutoBlinding_)
          {
            histogramData_blinded_rebinned = blindHistogram(histogramData_rebinned, keepBlinded_rebinned);
          }
          else
          {
            histogramData_blinded_rebinned = (TH1*)histogramData_rebinned->Clone("rebinned_data");
          }
        }

        makePlot(
          800, 900, 
          histogramData_rebinned, histogramData_blinded_rebinned,
          histogramsBackground_rebinned,
          histogramSignal_rebinned,
          histogramUncertainty_rebinned,
          legendTextSize_, legendPosX_, legendPosY_, legendSizeX_, legendSizeY_,
          labelOnTop_,
          extraLabels, 0.055, 0.185, 0.915 - 0.055 * extraLabels.size(), extraLabelsSizeX, 0.055 * extraLabels.size(),
          distribution->xMin_, distribution->xMax_, distribution->xAxisTitle_, distribution->xAxisOffset_,
          true, distribution->yMin_, distribution->yMax_, distribution->yAxisTitle_, distribution->yAxisOffset_,
          outputFileName_plot,
          true,
          divideByBinWidth_
        );
        makePlot(
          800, 900, 
          histogramData_rebinned, histogramData_blinded_rebinned,
          histogramsBackground_rebinned,
          histogramSignal_rebinned,
          histogramUncertainty_rebinned,
          legendTextSize_, legendPosX_, legendPosY_, legendSizeX_, legendSizeY_,
          labelOnTop_,
          extraLabels, 0.055, 0.185, 0.915 - 0.055 * extraLabels.size(), extraLabelsSizeX, 0.055 * extraLabels.size(),
          distribution->xMin_, distribution->xMax_, distribution->xAxisTitle_, distribution->xAxisOffset_,
          false, distribution->yMin_, distribution->yMax_, distribution->yAxisTitle_, distribution->yAxisOffset_,
          outputFileName_plot,
          true,
          divideByBinWidth_
        );
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
      for(histogramEntryType * histogramBackground_entry: histogramsBackground)
      {
        delete histogramBackground_entry->histogram_;
      }
      for(histogramEntryType * histogramBackground_entry: histogramsBackground_rebinned)
      {
        delete histogramBackground_entry->histogram_;
      }
    }
  }
}
