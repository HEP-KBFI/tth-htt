#ifndef HADRONICTAU_H
#define HADRONICTAU_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class HadronicTau
  : public GenParticle
{
public:
  HadronicTau() = default;
  HadronicTau(Double_t _pt,
              Double_t _eta,
              Double_t _phi,
              Double_t _mass,
              Int_t    _decmode,
              Int_t    _id_mva,
              Int_t    _anti_e,
              Int_t    _anti_mu);

  Double_t pt;
  Double_t eta;
  Double_t phi;
  Double_t mass;
  Int_t decmode;
  Int_t id_mva;
  Int_t anti_e;
  Int_t anti_mu;
};

#endif // HADRONICTAU_H

