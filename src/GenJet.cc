#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet, GenParticle

GenJet::GenJet(Double_t _pt,
               Double_t _eta,
               Double_t _phi,
               Double_t _mass)
  : GenParticle(_pt, _eta, _phi, _mass)
{}
