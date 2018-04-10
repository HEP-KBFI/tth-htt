#ifndef tthAnalysis_HiggsToTauTau_RecoElectron_h
#define tthAnalysis_HiggsToTauTau_RecoElectron_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

// EGamma POG WPs, defined in RecoEgamma/ElectronIdentification/python/Identification:
// mvaElectronID_Fall17_noIso_V1_cff.py (the default), mvaElectronID_Fall17_iso_V1_cff.py
enum class EGammaPOG { kWP80, kWP90, kWPL };

class RecoElectron
  : public RecoLepton
{
public:
  RecoElectron() = default;
  RecoElectron(const RecoLepton & lepton,
               Double_t eCorr,
               Double_t mvaRawPOG,
               Bool_t mvaRawPOG_WP80,
               Bool_t mvaRawPOG_WP90,
               Bool_t mvaRawPOG_WPL,
               Double_t sigmaEtaEta,
               Double_t HoE,
               Double_t deltaEta,
               Double_t deltaPhi,
               Double_t OoEminusOoP,
               Int_t nLostHits,
               Bool_t passesConversionVeto,
               Int_t cutbasedID_HLT);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t eCorr() const;
  Double_t mvaRawPOG() const;
  Bool_t mvaRawPOG_WP80() const;
  Bool_t mvaRawPOG_WP90() const;
  Bool_t mvaRawPOG_WPL() const;
  Bool_t mvaRawPOG_WP(EGammaPOG wp) const;
  Double_t sigmaEtaEta() const;
  Double_t HoE() const;
  Double_t deltaEta() const;
  Double_t deltaPhi() const;
  Double_t OoEminusOoP() const;
  Int_t nLostHits() const;
  Bool_t passesConversionVeto() const;
  Int_t cutbasedID_HLT() const;

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool
  is_electron() const override;

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool
  is_muon() const override;

  const static bool useNoIso = true;

//--- observables specific to electrons
  Double_t eCorr_;              ///< ratio of the calibrated energy/miniaod energy
  Double_t mvaRawPOG_;          ///< raw output value of EGamma POG electron id MVA (continuous range -1..+1)
  Bool_t mvaRawPOG_WP80_;       ///< ID of EGamma POG electron id MVA, corresponding to 80% efficiency WP (1 -- pass; 0 -- fail)
  Bool_t mvaRawPOG_WP90_;       ///< ID of EGamma POG electron id MVA, corresponding to 90% efficiency WP (1 -- pass; 0 -- fail)
  Bool_t mvaRawPOG_WPL_;        ///< ID of EGamma POG electron id MVA, corresponding to loose WP (1 -- pass; 0 -- fail)
  Double_t sigmaEtaEta_;        ///< second shower moment in eta-direction
  Double_t HoE_;                ///< ratio of energy deposits in hadronic/electromagnetic section of calorimeter
  Double_t deltaEta_;           ///< difference in eta between impact position of track and electron cluster
  Double_t deltaPhi_;           ///< difference in phi between impact position of track and electron cluster
  Double_t OoEminusOoP_;        ///< difference between calorimeter energy and track momentum (1/E - 1/P)
  Int_t nLostHits_;             ///< number of operational tracker layers between interaction point and innermost hit on track
  Bool_t passesConversionVeto_; ///< Flag indicating if electron passes (true) or fails (false) photon conversion veto
  Int_t cutbasedID_HLT_;        ///< Cut based HLT electron ID
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoElectron & electron);

#endif // tthAnalysis_HiggsToTauTau_RecoElectron_h
