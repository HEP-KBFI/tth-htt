#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"

GenLepton::GenLepton(Int_t _pdg_id,
                     Double_t _pt,
                     Double_t _eta,
                     Double_t _phi,
                     Double_t _mass)
  : pdg_id(_pdg_id)
  , pt(_pt)
  , eta(_eta)
  , phi(_phi)
  , mass(_mass)
{
  p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
}
