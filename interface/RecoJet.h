#ifndef RECOJET_H
#define RECOJET_H

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

class RecoJet
{
public:
  RecoJet() = default;
  RecoJet(Double_t _pt,
          Double_t _eta,
          Double_t _phi,
          Double_t _csv,
          Double_t _mass,
          Int_t _idx);

  Double_t pt;   ///< pT of the jet
  Double_t eta;  ///< eta of the jet
  Double_t phi;  ///< phi of the jet
  Double_t csv;  ///< CSV of the jet
  Double_t mass; ///< mass of the jet
  Int_t idx;     ///< its index in the ntuple

  math::PtEtaPhiMLorentzVector p4; ///< 4-momentum constructed from pT, eta, phi and mass
};

#endif // RECOJET_H

