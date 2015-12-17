#include "tthAnalysis/HiggsToTauTau/interface/HadronicTau.h"

HadronicTau::HadronicTau(Double_t _pt,
                         Double_t _eta,
                         Double_t _phi,
                         Double_t _mass,
                         Int_t    _decmode,
                         Int_t    _id_mva,
                         Int_t    _anti_e,
                         Int_t    _anti_mu)
  : pt(_pt)
  , eta(_eta)
  , phi(_phi)
  , mass(_mass)
  , decmode(_decmode)
  , id_mva(_id_mva)
  , anti_e(_anti_e)
  , anti_mu(_anti_mu)
{
  p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
}
