#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()

MEtFilterHistManager::MEtFilterHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  central_or_shiftOptions_["MEtFilterCounter"] = { "central" };
}

void
MEtFilterHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_MEtFilterCounter_ = book1D(dir, "MEtFilterCounter", "MEtFilterCounter", MEtFilterFlag::LAST, 1., MEtFilterFlag::LAST + 1);
  if(!histogram_MEtFilterCounter_) return;
  for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
  {
    histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(flag + 1, getMEtFilterFlagString(static_cast<MEtFilterFlag>(flag)));
  }
}

void
MEtFilterHistManager::fillHistograms(const MEtFilter & metFilter,
                                     double evtWeight)
{
  const double evtWeightErr = 0.;

  for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
  {
    if(! metFilter.getFlag(static_cast<MEtFilterFlag>(flag)))
    {
      // CV: fill histogram if filter has failed
      fill(histogram_MEtFilterCounter_, flag + 1, evtWeight, evtWeightErr);
    }
  }
}
