#ifndef tthAnalysis_HiggsToTauTau_GenLepton_h
#define tthAnalysis_HiggsToTauTau_GenLepton_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenLepton
  : public GenParticle
{
public:
  GenLepton() = default;
  GenLepton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId);
  GenLepton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId,
            Int_t charge);
  GenLepton(const math::PtEtaPhiMLorentzVector & p4,
            Int_t pdgId);

  virtual ~GenLepton() {}
};

std::ostream &
operator<<(std::ostream & stream,
           const GenLepton & lepton);

#endif // tthAnalysis_HiggsToTauTau_GenLepton_h
