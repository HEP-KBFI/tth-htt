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
            Int_t pdgId,
            Int_t status,
            Int_t statusFlags);
  GenLepton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId,
            Int_t charge,
            Int_t status,
            Int_t statusFlags);
  GenLepton(const math::PtEtaPhiMLorentzVector & p4,
            Int_t pdgId,
            Int_t status,
            Int_t statusFlags);

  virtual ~GenLepton() {}

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  virtual bool
  is_electron() const;

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  virtual bool
  is_muon() const;
};

std::ostream &
operator<<(std::ostream & stream,
           const GenLepton & lepton);

#endif // tthAnalysis_HiggsToTauTau_GenLepton_h
