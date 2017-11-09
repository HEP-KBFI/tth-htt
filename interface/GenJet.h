#ifndef GENJET_H
#define GENJET_H

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenJet : public Particle
{
 public:
  GenJet() = default;
  GenJet(Double_t _pt,
         Double_t _eta,
         Double_t _phi,
         Double_t _mass);

  virtual ~GenJet() {};

  operator GenParticle() const;  
};

#endif // GENJET_H
