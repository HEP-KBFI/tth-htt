#ifndef tthAnalysis_HiggsToTauTau_RecoMuon_h
#define tthAnalysis_HiggsToTauTau_RecoMuon_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

class RecoMuon
  : public RecoLepton
{
public:
  RecoMuon() = default;
  RecoMuon(const RecoLepton & lepton,
           Bool_t passesLooseIdPOG,
           Bool_t passesMediumIdPOG,
           Float_t segmentCompatibility,
           Float_t ptErr,
           Float_t pt_corrected,
           Float_t pt_sys_uncert);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Bool_t
  passesLooseIdPOG() const;

  Bool_t
  passesMediumIdPOG() const;

  Float_t
  segmentCompatibility() const;

  Float_t
  ptErr() const;

  Float_t
  dpt_div_pt() const;

  Float_t
  pt_corrected() const;

  Float_t
  pt_sys_uncert() const;

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

  Double_t
  cone_pt() const override;

  const Particle::LorentzVector &
  cone_p4() const override;

//--- observables specific to muons
  Bool_t passesLooseIdPOG_;      ///< flag indicating if muon passes (true) or fails (false) loose PFMuon id
  Bool_t passesMediumIdPOG_;     ///< flag indicating if muon passes (true) or fails (false) medium PFMuon id
  Float_t segmentCompatibility_; ///< muon segment compatibility
  Float_t ptErr_;                ///< pT error of the muon track
  Float_t pt_corrected_;         ///< Rochester-corrected muon momentum
  Float_t pt_sys_uncert_;        ///< associated systematic uncertainty to Rochester correction
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoMuon & muon);

#endif // tthAnalysis_HiggsToTauTau_RecoMuon_h
