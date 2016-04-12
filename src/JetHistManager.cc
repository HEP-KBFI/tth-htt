#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

JetHistManager::JetHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  idx_ = cfg.getParameter<int>("idx");
}

void JetHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_pt_ = book1D(dir, "pt", "pt", 40, 0., 200.);
  histogram_eta_ = book1D(dir, "eta", "eta", 46, -2.3, +2.3);
  histogram_phi_ = book1D(dir, "phi", "phi", 36, -TMath::Pi(), +TMath::Pi());
  histogram_mass_ = book1D(dir, "mass", "mass", 40, 0., 2.);

  histogram_BtagCSV_ = book1D(dir, "BtagCSV", "BtagCSV", 40, 0., 1.);
  
  histogram_abs_genPdgId_ = book1D(dir, "abs_genPdgId", "abs_genPdgId", 22, -0.5, +21.5);
}

void JetHistManager::fillHistograms(const std::vector<const RecoJet*>& jet_ptrs, double evtWeight)
{
  double evtWeightErr = 0.;
  
  size_t numJets = jet_ptrs.size();
  for ( size_t idxJet = 0; idxJet < numJets; ++idxJet ) {
    const RecoJet* jet = jet_ptrs[idxJet];

    if ( idx_ >= 0 && (int)idxJet != idx_ ) continue;

    fillWithOverFlow(histogram_pt_, jet->pt_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_eta_, jet->eta_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_phi_, jet->phi_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mass_, jet->mass_, evtWeight, evtWeightErr);

    fillWithOverFlow(histogram_BtagCSV_, jet->BtagCSV_, evtWeight, evtWeightErr);
  
    int abs_genPdgId = 0;
    if      ( jet->genLepton_ ) abs_genPdgId = std::abs(jet->genLepton_->pdgId_); // generator level match to electron or muon
    else if ( jet->genHadTau_ ) abs_genPdgId = 15;                                // generator level match to hadronic tau decay 
    else if ( jet->genJet_    ) abs_genPdgId = 21;                                // generator level match to jet; fill histogram with pdgId of gluon
    else                        abs_genPdgId = 0;                                 // no match to any generator level particle (reconstructed jet most likely due to pileup)
    fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);
  }
}
