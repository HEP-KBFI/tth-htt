#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet, GenParticle

GenJet::GenJet(Double_t pt,
               Double_t eta,
               Double_t phi,
               Double_t mass)
  : GenParticle(pt, eta, phi, mass)
{}
