#ifndef tthAnalysis_HiggsToTauTau_RecoElectron_h
#define tthAnalysis_HiggsToTauTau_RecoElectron_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

class RecoElectron
  : public RecoLepton
{
public:
  RecoElectron() = default;
  RecoElectron(const RecoLepton & lepton,
               Double_t mvaRawPOG_GP,
               Double_t mvaRawPOG_HZZ,
               Double_t sigmaEtaEta,
               Double_t HoE,
               Double_t deltaEta,
               Double_t deltaPhi,
               Double_t OoEminusOoP,
               Int_t nLostHits,
               Bool_t passesConversionVeto);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t mvaRawPOG_GP() const;
  Double_t mvaRawPOG_HZZ() const;
  Double_t sigmaEtaEta() const;
  Double_t HoE() const;
  Double_t deltaEta() const;
  Double_t deltaPhi() const;
  Double_t OoEminusOoP() const;
  Int_t nLostHits() const;
  Bool_t passesConversionVeto() const;

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool is_electron() const override;

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool is_muon() const override;

//--- observables specific to electrons
  Double_t mvaRawPOG_GP_;       ///< raw output value of EGamma POG electron id MVA, General Purpose (pt>10)
  Double_t mvaRawPOG_HZZ_;      ///< raw output value of EGamma POG electron id MVA, HZZ(pt < 10)
  Double_t sigmaEtaEta_;        ///< second shower moment in eta-direction
  Double_t HoE_;                ///< ratio of energy deposits in hadronic/electromagnetic section of calorimeter
  Double_t deltaEta_;           ///< difference in eta between impact position of track and electron cluster
  Double_t deltaPhi_;           ///< difference in phi between impact position of track and electron cluster
  Double_t OoEminusOoP_;        ///< difference between calorimeter energy and track momentum (1/E - 1/P)
  Int_t nLostHits_;             ///< number of operational tracker layers between interaction point and innermost hit on track
  Bool_t passesConversionVeto_; ///< Flag indicating if electron passes (true) or fails (false) photon conversion veto
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoElectron & electron);

#endif // tthAnalysis_HiggsToTauTau_RecoElectron_h
