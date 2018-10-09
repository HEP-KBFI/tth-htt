#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

#include <TMath.h> // TMath::Pi()

HadTauHistManager::HadTauHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  idx_ = cfg.getParameter<int>("idx");
}

void HadTauHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_pt_        = book1D(dir, "pt",        "pt",        40,  0.,  200.);
  histogram_eta_       = book1D(dir, "eta",       "eta",       46, -2.3,  +2.3);
  histogram_phi_       = book1D(dir, "phi",       "phi",       36, -TMath::Pi(), +TMath::Pi());
  histogram_decayMode_ = book1D(dir, "decayMode", "decayMode", 12, -0.5, +11.5);
  histogram_mass_      = book1D(dir, "mass",      "mass",      40,  0.,    2.);
  histogram_charge_    = book1D(dir, "charge",    "charge",     3, -1.5,  +1.5);
  histogram_dz_        = book1D(dir, "dz",        "dz",        40, -0.2,  +0.2);
  histogram_dxy_       = book1D(dir, "dxy",       "dxy",       40, -0.1,  +0.1);

  histogram_decayModeFinding_ = book1D(dir, "decayModeFinding", "decayModeFinding", 2, -0.5, +1.5); 
  histogram_id_mva_dR03_      = book1D(dir, "id_mva_dR03",      "id_mva_dR03",      7, -0.5, +6.5);
  histogram_id_mva_dR05_      = book1D(dir, "id_mva_dR05",      "id_mva_dR05",      7, -0.5, +6.5);
  histogram_id_cut_dR03_      = book1D(dir, "id_cut_dR03",      "id_cut_dR03",      4, -0.5, +3.5);
  histogram_id_cut_dR05_      = book1D(dir, "id_cut_dR05",      "id_cut_dR05",      4, -0.5, +3.5);

  histogram_antiElectron_ = book1D(dir, "antiElectron", "antiElectron", 6, -0.5, +5.5);
  histogram_antiMuon_     = book1D(dir, "antiMuon",     "antiMuon",     3, -0.5, +2.5);

  histogram_abs_genPdgId_ = book1D(dir, "abs_genPdgId", "abs_genPdgId", 22, -0.5, +21.5);
}

void
HadTauHistManager::fillHistograms(const RecoHadTau & hadTau,
                                  double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,        hadTau.pt(),        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,       hadTau.eta(),       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,       hadTau.phi(),       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_decayMode_, hadTau.decayMode(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mass_,      hadTau.mass(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_charge_,    hadTau.charge(),    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_dz_,        hadTau.dz(),        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_dxy_,       hadTau.dxy(),       evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_decayModeFinding_, hadTau.decayModeFinding(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_id_mva_dR03_,      hadTau.id_mva_dR03(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_id_mva_dR05_,      hadTau.id_mva_dR05(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_id_cut_dR03_,      hadTau.id_cut_dR03(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_id_cut_dR05_,      hadTau.id_cut_dR05(),      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_antiElectron_,     hadTau.antiElectron(),     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_antiMuon_,         hadTau.antiMuon(),         evtWeight, evtWeightErr);

  int abs_genPdgId = 0;
  if     (hadTau.genHadTau()) abs_genPdgId = 15;                                    // generator level match to hadronic tau decay
  else if(hadTau.genLepton()) abs_genPdgId = std::abs(hadTau.genLepton()->pdgId()); // generator level match to electron or muon
  else if(hadTau.genJet()   ) abs_genPdgId = 21;                                    // generator level match to jet; fill histogram with pdgId of gluon
  else                        abs_genPdgId = 0;                                     // no match to any generator level particle
                                                                                    // (reconstructed tauh most likely due to pileup)
  fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);
}

void
HadTauHistManager::fillHistograms(const std::vector<const RecoHadTau *> & hadTau_ptrs,
                                  double evtWeight)
{
  const int numHadTaus = hadTau_ptrs.size();
  for(int idxHadTau = 0; idxHadTau < numHadTaus; ++idxHadTau)
  {
    const RecoHadTau * hadTau = hadTau_ptrs[idxHadTau];
    if(idx_ >= 0 && idxHadTau != idx_)
    {
      continue;
    }
    fillHistograms(*hadTau, evtWeight);
  }
}
