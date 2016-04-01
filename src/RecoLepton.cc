#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton, GenLepton

RecoLepton::RecoLepton(Double_t _pt,
                       Double_t _eta,
                       Double_t _phi,
                       Double_t _mass,
                       Int_t _pdg_id,
                       Double_t _dxy,
                       Double_t _dz,
                       Double_t _rel_iso,
                       Double_t _sip3d,
                       Double_t _mva_tth,
		       Double_t _jetPtRatio,
                       Int_t _med_mu_id,
                       Int_t _ele_mva_id,
                       Int_t _lost_hits,
                       Int_t _loose_id,
                       Int_t _tight_charge,
                       Int_t _pass_conv_veto)

  : GenLepton(_pt, _eta, _phi, _mass, _pdg_id)
  , dxy(_dxy)
  , dz(_dz)
  , rel_iso(_rel_iso)
  , sip3d(_sip3d)
  , mva_tth(_mva_tth)
  , jetPtRatio(_jetPtRatio)
  , med_mu_id(_med_mu_id)
  , ele_mva_id(_ele_mva_id)
  , lost_hits(_lost_hits)
  , loose_id(_loose_id)
  , tight_charge(_tight_charge)
  , pass_conv_veto(_pass_conv_veto)
{}

bool
RecoLepton::is_electron() const
{
  return std::abs(pdg_id) == 11;
}

bool
RecoLepton::is_muon() const
{
  return std::abs(pdg_id) == 13;
}
