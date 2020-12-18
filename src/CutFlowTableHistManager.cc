#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <cassert> // assert()

CutFlowTableHistManager::CutFlowTableHistManager(const edm::ParameterSet & cfg,
                                                 const std::vector<std::string> & cuts)
  : HistManagerBase(cfg)
  , histogram_cutFlow_(nullptr)
  , cuts_(cuts)
{
  central_or_shiftOptions_["cutFlow"] = { "*" };
}

void
CutFlowTableHistManager::bookHistograms(TFileDirectory & dir)
{
  const int numCuts = cuts_.size();
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis * const xAxis = histogram_cutFlow_->GetXaxis();

  for(int i = 1; i <= numCuts; ++i)
  {
    xAxis->SetBinLabel(i, cuts_.at(i - 1).data());
  }
}

void
CutFlowTableHistManager::fillHistograms(const std::string & cut,
                                        double evtWeight)
{
  assert(histogram_cutFlow_);
  const double evtWeightErr = 0.;
  const TAxis * const xAxis = histogram_cutFlow_->GetXaxis();
  const int idxBin = const_cast<TAxis *>(xAxis)->FindBin(cut.data());

  if(idxBin >= 1 && idxBin <= xAxis->GetNbins())
  {
    const double binCenter = xAxis->GetBinCenter(idxBin);
    fill(histogram_cutFlow_, binCenter, evtWeight, evtWeightErr);
  }
  else
  {
    throw cmsException(this, __func__) << "Cut = '" << cut << "' not defined";
  }
}
