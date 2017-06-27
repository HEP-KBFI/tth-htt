#ifndef GENJET_H
#define GENJET_H

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle

class GenJet
  : public Particle
{
public:
  GenJet() = default;
  GenJet(Double_t _pt,
         Double_t _eta,
         Double_t _phi,
         Double_t _mass);
};

#endif // GENJET_H
