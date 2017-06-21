#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau, GenParticleBase

GenHadTau::GenHadTau(Double_t pt,
		     Double_t eta,
		     Double_t phi,
		     Double_t mass,
		     Int_t charge)
  : Particle(pt, eta, phi, mass)
  , charge_(charge)
{}
