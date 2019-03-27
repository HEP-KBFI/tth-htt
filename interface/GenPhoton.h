#ifndef GENPHOTON_H
#define GENPHOTON_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenPhoton
  : public GenParticle
{
public:
  GenPhoton() = default;
  GenPhoton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId,
            Int_t status,
            Int_t statusFlags,
            UChar_t genPartFlav);
  GenPhoton(const GenParticle & genParticle);

  virtual ~GenPhoton() {}
};

std::ostream &
operator<<(std::ostream & stream,
           const GenPhoton & genPhoton);

#endif // GENPHOTON_H
