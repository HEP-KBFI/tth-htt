#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"

#include <TMath.h> // TMath::Pi()

JetHistManager::JetHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , idx_(cfg.getParameter<int>("idx"))
{}

void
JetHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_pt_           = book1D(dir, "pt",           "pt",            40,  0.,  200.);
  histogram_eta_          = book1D(dir, "eta",          "eta",          100, -5.0,  +5.0);
  histogram_phi_          = book1D(dir, "phi",          "phi",           36, -TMath::Pi(), +TMath::Pi());
  histogram_mass_         = book1D(dir, "mass",         "mass",          40,  0.,    2.);
  histogram_BtagCSV_      = book1D(dir, "BtagCSV",      "BtagCSV",       40,  0.,    1.);
  histogram_abs_genPdgId_ = book1D(dir, "abs_genPdgId", "abs_genPdgId",  22, -0.5, +21.5);
}

void
JetHistManager::fillHistograms(const RecoJet & jet,
                               double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,      jet.pt(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,     jet.eta(),     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,     jet.phi(),     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mass_,    jet.mass(),    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_BtagCSV_, jet.BtagCSV(), evtWeight, evtWeightErr);

  int abs_genPdgId = 0;
  if     (jet.genLepton()) abs_genPdgId = std::abs(jet.genLepton()->pdgId()); // generator level match to electron or muon
  else if(jet.genHadTau()) abs_genPdgId = 15; // generator level match to hadronic tau decay
  else if(jet.genJet()   ) abs_genPdgId = 21; // generator level match to jet; fill histogram with pdgId of gluon
  else                     abs_genPdgId = 0;  // no match to any generator level particle (reconstructed jet most likely due to pileup)
  fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);
}

void
JetHistManager::fillHistograms(const std::vector<const RecoJet *> & jet_ptrs,
                               double evtWeight)
{
  const int numJets = jet_ptrs.size();
  for(int idxJet = 0; idxJet < numJets; ++idxJet)
  {
    const RecoJet * jet = jet_ptrs[idxJet];
    if(idx_ >= 0 && idxJet != idx_)
    {
      continue;
    }
    fillHistograms(*jet, evtWeight);
  }
}
