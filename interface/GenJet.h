#ifndef GENJET_H
#define GENJET_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenJet
  : public GenParticle
{
public:
  GenJet() = default;
  GenJet(Double_t pt,
         Double_t eta,
         Double_t phi,
         Double_t mass);

  virtual ~GenJet() {}
};

std::ostream &
operator<<(std::ostream & stream,
           const GenJet & genJet);

#endif // GENJET_H
