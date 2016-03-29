#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton, GenParticle

GenLepton::GenLepton(Double_t _pt,
                     Double_t _eta,
                     Double_t _phi,
                     Double_t _mass,
                     Int_t _pdg_id)
  : GenParticle(_pt, _eta, _phi, _mass)
  , pdg_id(_pdg_id)
{}
