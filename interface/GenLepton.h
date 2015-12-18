#ifndef GENLEPTON_H
#define GENLEPTON_H

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

class GenLepton
{
public:
  GenLepton() = default;
  GenLepton(Int_t _pdg_id,
            Double_t _pt,
            Double_t _eta,
            Double_t _phi,
            Double_t _mass);

  Int_t pdg_id;  ///< PDG id of the lepton (signed)
  Double_t pt;   ///< pT of the lepton
  Double_t eta;  ///< eta of the lepton
  Double_t phi;  ///< phi of the lepton
  Double_t mass; ///< mass of the lepton

  math::PtEtaPhiMLorentzVector p4; ///< 4-momentum constructed from the pT, eta, phi and mass
};

#endif // GENLEPTON_H
