#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

#include <TMath.h> // TMath::Pi()

MEtHistManager::MEtHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void
MEtHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_met_pt_  = book1D(dir, "met_pt",  "met_pt",  40, 0., 200.);
  histogram_met_phi_ = book1D(dir, "met_phi", "met_phi", 36, -TMath::Pi(), +TMath::Pi());
  histogram_mht_pt_  = book1D(dir, "mht_pt",  "mht_pt",  40, 0., 200.);
  histogram_mht_phi_ = book1D(dir, "mht_phi", "mht_phi", 36, -TMath::Pi(), +TMath::Pi());

  histogram_mhtPt_vs_metPt_ = book2D(dir, "mhtPt_vs_metPt", "mht_vs_metPt", 40, 0., 200., 40, 0., 200.);

  histogram_met_LD_ = book1D(dir, "met_LD", "met_LD", 40, 0., 200.);
}

void
MEtHistManager::fillHistograms(const RecoMEt & met,
                               const Particle::LorentzVector & mht_p4,
                               double met_LD,
                               double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_met_pt_,  met.pt(),     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_met_phi_, met.phi(),    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mht_pt_,  mht_p4.pt(),  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mht_phi_, mht_p4.phi(), evtWeight, evtWeightErr);

  fillWithOverFlow2d(histogram_mhtPt_vs_metPt_, met.pt(), mht_p4.pt(), evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_met_LD_, met_LD, evtWeight, evtWeightErr);
}
