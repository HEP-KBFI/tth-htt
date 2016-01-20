#ifndef RECOJET_H
#define RECOJET_H

#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

class RecoJet
  : public GenJet
{
public:
  RecoJet() = default;
  RecoJet(Double_t _pt,
          Double_t _eta,
          Double_t _phi,
          Double_t _mass,
          Double_t _csv,
          Int_t _idx);

  Double_t csv;  ///< CSV of the jet
  Int_t idx;     ///< its index in the ntuple
};

#endif // RECOJET_H

