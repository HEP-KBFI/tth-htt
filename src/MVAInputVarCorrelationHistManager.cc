#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarCorrelationHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMath.h> // TMath::Pi()

#include <iostream> // std::cout, std::endl

MVAInputVarCorrelationHistManager::MVAInputVarCorrelationHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , histogram_sumX_(nullptr)
  , histogram_sumX2_(nullptr)
  , histogram_sumXY_(nullptr)
  , histogram_sumWeights_(nullptr)
{
  central_or_shiftOptions_["sumX"]       = { "central" };
  central_or_shiftOptions_["sumX2"]      = { "central" };
  central_or_shiftOptions_["sumXY"]      = { "central" };
  central_or_shiftOptions_["sumWeights"] = { "central" };
}

MVAInputVarCorrelationHistManager::~MVAInputVarCorrelationHistManager()
{}

namespace
{
  void setAxisLabels(TAxis* axis, const std::vector<std::string> & mvaInputVariables)
  {
    int idxBin = 1;
    for ( const auto & mvaInputVariable: mvaInputVariables )
    {
      axis->SetBinLabel(idxBin, mvaInputVariable.data());
      ++idxBin;
    }
  }
}

void
MVAInputVarCorrelationHistManager::bookHistograms(TFileDirectory & dir,
                                                  const std::vector<std::string> & mvaInputVariables)
{
  mvaInputVariables_ = mvaInputVariables;

  int numBins = mvaInputVariables_.size();

  histogram_sumX_  = book1D(dir, "sumX", "sumX", numBins, -0.5, numBins - 0.5);
  setAxisLabels(histogram_sumX_->GetXaxis(), mvaInputVariables_);

  histogram_sumX2_ = book1D(dir, "sumX2", "sumX2", numBins, -0.5, numBins - 0.5);
  setAxisLabels(histogram_sumX2_->GetXaxis(), mvaInputVariables_);

  histogram_sumXY_ = book2D(dir, "sumXY", "sumXY", numBins, -0.5, numBins - 0.5, numBins, -0.5, numBins - 0.5);
  setAxisLabels(histogram_sumXY_->GetXaxis(), mvaInputVariables_);
  setAxisLabels(histogram_sumXY_->GetYaxis(), mvaInputVariables_);

  histogram_sumWeights_ = book1D(dir, "sumWeights", "sumWeights", 1, -0.5, +0.5);
}

void
MVAInputVarCorrelationHistManager::fillHistograms(const std::map<std::string, double> & mvaInputs,
                                                  double evtWeight)
{
  assert(histogram_sumX_ && histogram_sumX2_ && histogram_sumXY_ && histogram_sumWeights_);
  double x = 0.;
  for ( const auto & mvaInputVariableX: mvaInputVariables_ )
  {
    std::map<std::string, double>::const_iterator mvaInputX = mvaInputs.find(mvaInputVariableX);
    assert(mvaInputX != mvaInputs.end());

    histogram_sumX_->Fill(x, evtWeight*mvaInputX->second);

    histogram_sumX2_->Fill(x, evtWeight*mvaInputX->second*mvaInputX->second);

    double y = 0.;
    for ( const auto & mvaInputVariableY: mvaInputVariables_ )
    {
      std::map<std::string, double>::const_iterator mvaInputY = mvaInputs.find(mvaInputVariableY);
      assert(mvaInputY != mvaInputs.end());

      histogram_sumXY_->Fill(x, y, evtWeight*mvaInputX->second*mvaInputY->second);

      y += 1.;
    }

    x += 1.;
  }

  histogram_sumWeights_->Fill(0., evtWeight);
}

std::vector<std::string>
getKeys(const std::map<std::string, double> & mvaInputs)
{
  std::vector<std::string> mvaInputVariables;
  for ( const auto & mvaInput: mvaInputs )
  {
    mvaInputVariables.push_back(mvaInput.first);
  }
  return mvaInputVariables;
}
