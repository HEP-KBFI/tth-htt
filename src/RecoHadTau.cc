#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau, GenParticle

RecoHadTau::RecoHadTau(Double_t pt,
		       Double_t eta,
		       Double_t phi,
		       Double_t mass,
		       Int_t pdgId,
		       Double_t dz,
		       Int_t decayModeFinding,
		       Int_t id_mva_dR03,
		       Int_t id_mva_dR05,
		       Int_t id_cut_dR03,
		       Int_t id_cut_dR05,
		       Int_t antiElectron,
		       Int_t antiMuon)
  : GenParticle(pt, eta, phi, mass)
  , pdgId_(pdgId)
  , dz_(dz)
  , decayModeFinding_(decayModeFinding)
  , id_mva_dR03_(id_mva_dR03)
  , id_mva_dR05_(id_mva_dR05)
  , id_cut_dR03_(id_cut_dR03)
  , id_cut_dR05_(id_cut_dR05)
  , antiElectron_(antiElectron)
  , antiMuon_(antiMuon)
{}
