#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

RecoJet::RecoJet(Double_t _pt,
                 Double_t _eta,
                 Double_t _phi,
                 Double_t _csv,
                 Double_t _mass,
                 Int_t _idx)
  : pt(_pt)
  , eta(_eta)
  , phi(_phi)
  , csv(_csv)
  , mass(_mass)
  , idx(_idx)
{
  p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
}
