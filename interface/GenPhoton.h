#ifndef GENPHOTON_H
#define GENPHOTON_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#define _READ_GENERATOR_LEVEL_PHOTONS 0

class GenPhoton
  : public GenParticle
{
public:
  GenPhoton() = default;
  GenPhoton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId);

  virtual ~GenPhoton() {}
};

std::ostream &
operator<<(std::ostream & stream,
           const GenPhoton & genPhoton);

#endif // GENPHOTON_H
