#include "tthAnalysis/HiggsToTauTau/interface/TriggerHistManager.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"

#include <cassert> // assert()

TriggerHistManager::TriggerHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  central_or_shiftOptions_["hltPathCounter"] = { "central" };
}

TriggerHistManager::~TriggerHistManager()
{
  for(auto & it: hltPathMap_)
  {
    delete it.second;
  }
}

void 
TriggerHistManager::add_hltPaths(const std::vector<hltPath *> & hltPaths)
{
  double next_binCenter = hltPathMap_.size();
  for(hltPath * hltPath: hltPaths)
  {
    hltPathMap_[hltPath->getBranchName()] = new hltPathEntry(hltPath->getBranchName(), next_binCenter);
    next_binCenter += 1.;
  }
}

void
TriggerHistManager::bookHistograms(TFileDirectory & dir)
{
  if(hltPathMap_.empty())
  {
    throw cmsException(this, __func__, __LINE__) << "No HLT paths defined";
  }

  histogram_hltPathCounter_ = book1D(dir, "hltPathCounter", "hltPathCounter", hltPathMap_.size(), -0.5, hltPathMap_.size() - 0.5);

  TAxis * const xAxis = histogram_hltPathCounter_->GetXaxis();
  for(const auto & hltPath: hltPathMap_)
  {
    const int idxBin =  xAxis->FindBin(hltPath.second->binCenter_);
    assert(idxBin >= 1 && idxBin <= xAxis->GetNbins());
    xAxis->SetBinLabel(idxBin, hltPath.second->branchName_.data());
  }
}

void
TriggerHistManager::fillHistograms(const std::vector<hltPath*>& hltPaths,
                                   double evtWeight)
{
  const double evtWeightErr = 0.;

  for(hltPath * hltPath: hltPaths)
  {
    const bool passes = hltPath->getValue();
    if(passes)
    {
      const auto hltPathMap_iter = hltPathMap_.find(hltPath->getBranchName());
      assert(hltPathMap_iter != hltPathMap_.end());
      fill(histogram_hltPathCounter_, hltPathMap_iter->second->binCenter_, evtWeight, evtWeightErr);
    }
  }
}
