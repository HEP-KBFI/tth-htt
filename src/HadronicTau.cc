#include "tthAnalysis/HiggsToTauTau/interface/HadronicTau.h" // HadronicTau, GenParticle

HadronicTau::HadronicTau(Double_t _pt,
                         Double_t _eta,
                         Double_t _phi,
                         Double_t _mass,
                         Int_t    _decmode,
                         Int_t    _id_mva_dR03,
			 Int_t    _id_mva_dR05,
			 Int_t    _id_cut_dR03,
			 Int_t    _id_cut_dR05,
                         Int_t    _anti_e,
                         Int_t    _anti_mu,
                         Int_t    _pdg_id)
  : GenParticle(_pt, _eta, _phi, _mass)
  , decmode(_decmode)
  , id_mva_dR03(_id_mva_dR03)
  , id_mva_dR05(_id_mva_dR05)
  , id_cut_dR03(_id_mva_dR03)
  , id_cut_dR05(_id_mva_dR05)
  , anti_e(_anti_e)
  , anti_mu(_anti_mu)
  , pdg_id(_pdg_id)
{}
