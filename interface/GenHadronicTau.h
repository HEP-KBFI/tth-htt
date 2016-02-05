#ifndef GENHADRONICTAU_H
#define GENHADRONICTAU_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenHadronicTau
  : public GenParticle
{
  GenHadronicTau() = default;
  GenHadronicTau(Double_t _pt,
                 Double_t _eta,
                 Double_t _phi,
                 Double_t _mass);
};

#endif // GENHADRONICTAU_H
