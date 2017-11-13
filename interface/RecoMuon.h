#ifndef tthAnalysis_HiggsToTauTau_RecoMuon_h
#define tthAnalysis_HiggsToTauTau_RecoMuon_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

#include <ostream>

class RecoMuon
  : public RecoLepton
{
public:
  RecoMuon() = default;
  RecoMuon(Double_t pt,
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
           Bool_t passesLooseIdPOG,
           Bool_t passesMediumIdPOG,
           Float_t segmentCompatibility);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Bool_t passesLooseIdPOG() const { return passesLooseIdPOG_; }
  Bool_t passesMediumIdPOG() const { return passesMediumIdPOG_; }
  Float_t segmentCompatibility() const { return segmentCompatibility_; }

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool
  is_electron() const { return false; }

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool
  is_muon() const { return true; }

//--- observables specific to muons
  Bool_t passesLooseIdPOG_;       ///< flag indicating if muon passes (true) or fails (false) loose PFMuon id
  Bool_t passesMediumIdPOG_;      ///< flag indicating if muon passes (true) or fails (false) medium PFMuon id
  Float_t segmentCompatibility_; ///< muon segment compatibility
};

std::ostream& operator<<(std::ostream& stream, const RecoMuon& muon);

#endif // tthAnalysis_HiggsToTauTau_RecoMuon_h
