#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet, GenParticleBase

GenJet::GenJet(Double_t pt,
               Double_t eta,
               Double_t phi,
               Double_t mass)
  : Particle(pt, eta, phi, mass)
{}
