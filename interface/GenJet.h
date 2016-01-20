#ifndef GENJET_H
#define GENJET_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenJet
  : public GenParticle
{
public:
  GenJet() = default;
  GenJet(Double_t _pt,
         Double_t _eta,
         Double_t _phi,
         Double_t _mass);
};

#endif // GENJET_H
