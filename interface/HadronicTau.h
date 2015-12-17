#ifndef HADRONICTAU_H
#define HADRONICTAU_H

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

class HadronicTau
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

  math::PtEtaPhiMLorentzVector p4;
};

#endif // HADRONICTAU_H

