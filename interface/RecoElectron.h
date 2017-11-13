#ifndef tthAnalysis_HiggsToTauTau_RecoElectron_h
#define tthAnalysis_HiggsToTauTau_RecoElectron_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

#include <ostream>

class RecoElectron
  : public RecoLepton
{
 public:
  RecoElectron() = default;
  RecoElectron(Double_t pt,
	       Double_t eta,
	       Double_t phi,
	       Double_t mass,
	       Int_t pdgId,
	       Double_t dxy,
	       Double_t dz,
	       Double_t relIso,
	       Double_t chargedHadRelIso03,
         Double_t miniRelIsoCharged,
	       Double_t sip3d,
	       Double_t mvaRawTTH,
	       Double_t jetPtRatio,
	       Double_t jetBtagCSV,
	       Int_t passesTightCharge,
	       Int_t charge,
	       Double_t mvaRawPOG_GP,
	       Double_t mvaRawPOG_HZZ,
	       Double_t sigmaEtaEta,
	       Double_t HoE,
	       Double_t deltaEta,
	       Double_t deltaPhi,
	       Double_t OoEminusOoP,
	       Int_t nLostHits,
	       Int_t passesConversionVeto);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t mvaRawPOG_GP() const { return mvaRawPOG_GP_; }
  Double_t mvaRawPOG_HZZ() const { return mvaRawPOG_HZZ_; }
  Double_t sigmaEtaEta() const { return sigmaEtaEta_; }
  Double_t HoE() const { return HoE_; }
  Double_t deltaEta() const { return deltaEta_; }
  Double_t deltaPhi() const { return deltaPhi_; }
  Double_t OoEminusOoP() const { return OoEminusOoP_; }
  Int_t nLostHits() const { return nLostHits_; }
  Int_t passesConversionVeto() const { return passesConversionVeto_; }

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool
  is_electron() const { return true; }

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool
  is_muon() const { return false; }

//--- observables specific to electrons
  Double_t mvaRawPOG_GP_;         ///< raw output value of EGamma POG electron id MVA, General Purpose (pt>10)
  Double_t mvaRawPOG_HZZ_;         ///< raw output value of EGamma POG electron id MVA, HZZ(pt < 10)
  Double_t sigmaEtaEta_;       ///< second shower moment in eta-direction
  Double_t HoE_;               ///< ratio of energy deposits in hadronic/electromagnetic section of calorimeter
  Double_t deltaEta_;          ///< difference in eta between impact position of track and electron cluster
  Double_t deltaPhi_;          ///< difference in phi between impact position of track and electron cluster
  Double_t OoEminusOoP_;       ///< difference between calorimeter energy and track momentum (1/E - 1/P)
  Int_t nLostHits_;            ///< number of operational tracker layers between interaction point and innermost hit on track
  Int_t passesConversionVeto_; ///< Flag indicating if electron passes (1) or fails (0) photon conversion veto
};

std::ostream& operator<<(std::ostream& stream, const RecoElectron& electron);

#endif // tthAnalysis_HiggsToTauTau_RecoElectron_h
