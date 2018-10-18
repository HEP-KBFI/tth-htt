#include "tthAnalysis/HiggsToTauTau/interface/TriggerHistManager.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()

#include <assert.h> // assert

TriggerHistManager::TriggerHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{}

TriggerHistManager::~TriggerHistManager()
{
  for ( std::map<std::string, hltPathEntry*>::const_iterator it = hltPathMap_.begin();
	it != hltPathMap_.end(); ++it ) {
    delete it->second;
  }
}

void 
TriggerHistManager::add_hltPaths(const std::vector<hltPath*>& hltPaths)
{
  double next_binCenter = hltPathMap_.size();
  for ( std::vector<hltPath*>::const_iterator hltPath = hltPaths.begin();
	hltPath != hltPaths.end(); ++hltPath ) {
    hltPathMap_[(*hltPath)->getBranchName()] = new hltPathEntry((*hltPath)->getBranchName(), next_binCenter);
    next_binCenter += 1.;
  }
}

void
TriggerHistManager::bookHistograms(TFileDirectory & dir)
{
  if ( hltPathMap_.size() == 0 ) 
    throw cms::Exception("TriggerHistManager::bookHistograms")
      << "No HLT paths defined !!\n";
  histogram_hltPathCounter_ = book1D(dir, "hltPathCounter", "hltPathCounter", hltPathMap_.size(), -0.5, hltPathMap_.size() - 0.5);
  TAxis* xAxis = histogram_hltPathCounter_->GetXaxis();
  for ( std::map<std::string, hltPathEntry*>::const_iterator hltPath = hltPathMap_.begin();
	hltPath != hltPathMap_.end(); ++hltPath ) {
    int idxBin =  xAxis->FindBin(hltPath->second->binCenter_);
    assert(idxBin >= 1 && idxBin <= xAxis->GetNbins());
    xAxis->SetBinLabel(idxBin, hltPath->second->branchName_.data());
  }
}

void
TriggerHistManager::fillHistograms(const std::vector<hltPath*>& hltPaths,
				   double evtWeight)
{
  const double evtWeightErr = 0.;

  for ( std::vector<hltPath*>::const_iterator hltPath = hltPaths.begin();
	hltPath != hltPaths.end(); ++hltPath ) {
    bool passes = (*hltPath)->getValue();
    if ( passes ) {
      std::map<std::string, hltPathEntry*>::const_iterator hltPathMap_iter = hltPathMap_.find((*hltPath)->getBranchName());
      assert(hltPathMap_iter != hltPathMap_.end());
      fill(histogram_hltPathCounter_, hltPathMap_iter->second->binCenter_, evtWeight, evtWeightErr);
    }
  }
}
