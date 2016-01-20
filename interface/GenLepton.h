#ifndef GENLEPTON_H
#define GENLEPTON_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenLepton
  : public GenParticle
{
public:
  GenLepton() = default;
  GenLepton(Double_t _pt,
            Double_t _eta,
            Double_t _phi,
            Double_t _mass,
            Int_t _pdg_id);

  Int_t pdg_id;  ///< PDG id of the lepton (signed)
};

#endif // GENLEPTON_H
