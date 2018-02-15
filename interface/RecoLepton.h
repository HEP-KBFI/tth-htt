#ifndef tthAnalysis_HiggsToTauTau_RecoLepton_h
#define tthAnalysis_HiggsToTauTau_RecoLepton_h

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

// forward declarations
class GenHadTau;
class GenJet;

#include <memory> // std::shared_ptr

class RecoLepton
  : public GenLepton
{
public:
  RecoLepton() = default;
  RecoLepton(const GenLepton & lepton,
             Double_t dxy,
             Double_t dz,
             Double_t relIso,
             Double_t chargedHadRelIso03,
             Double_t miniIsoCharged,
             Double_t miniIsoNeutral,
             Double_t sip3d,
             Double_t mvaRawTTH,
             Double_t jetPtRatio,
             Double_t jetBtagCSV,
             Int_t tightCharge,
             Int_t charge);

  virtual ~RecoLepton();

  /**
   * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
   */
  void set_isLoose() const;
  void set_isFakeable() const;
  void set_isTight() const;

  /**
   * @brief Set "cone pT" for leptons that pass the "fakeable" lepton selection, but fail the "tight" lepton selection, 
   *        as described in lines 304-306 of AN-2016/211
   */
  void set_cone_pt(Double_t cone_pt);

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton * genLepton);
  void set_genHadTau(const GenHadTau * genHadTau);
  void set_genJet(const GenJet * genJet);

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

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t lepton_pt() const;
  const Particle::LorentzVector & lepton_p4() const;

  // CV: use original lepton pT instead of mixing lepton pT and cone_pT, as discussed on slide 2 of 
  //     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
  virtual Double_t pt() const;
  virtual const Particle::LorentzVector & p4() const;

  Double_t dxy() const;
  Double_t dz() const;
  Double_t relIso() const;
  Double_t chargedHadRelIso03() const;
  Double_t miniIsoCharged() const;
  Double_t miniIsoNeutral() const;
  Double_t sip3d() const;
  Double_t mvaRawTTH() const;
  Double_t jetPtRatio() const;
  Double_t jetBtagCSV() const;
  Int_t tightCharge() const;
  Int_t charge() const;
  Double_t cone_pt() const;
  const Particle::LorentzVector& cone_p4() const;
  
  const GenLepton * genLepton() const;
  const GenHadTau * genHadTau() const;
  const GenJet * genJet() const;

  bool isLoose() const;
  bool isFakeable() const;
  bool isTight() const;

protected:
//--- common observables for electrons and muons
  Double_t dxy_;                        ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz_;                         ///< d_{z}, distance on the z axis w.r.t PV
  Double_t relIso_;                     ///< relative mini-isolation
  Double_t chargedHadRelIso03_;         ///< PF relative isolation dR=0.3, charged component
  Double_t miniIsoCharged_;             ///< absolute charged mini-isolation
  Double_t miniIsoNeutral_;             ///< absolute neutral mini-isolation (PU corrected)
  Double_t sip3d_;                      ///< significance of IP
  Double_t mvaRawTTH_;                  ///< raw output of lepton MVA of ttH multilepton analysis
  Double_t jetPtRatio_;                 ///< ratio of lepton pT to pT of nearby jet
  Double_t jetBtagCSV_;                 ///< CSV b-tagging discriminator value of nearby jet
  Int_t tightCharge_;                   ///< Flag indicating if lepton passes (>= 2) or fails (< 2) tight charge requirement
  Int_t charge_;                        ///< lepton charge

  Double_t cone_pt_;
  Particle::LorentzVector cone_p4_;

//--- matching to generator level particles
  std::shared_ptr<const GenLepton> genLepton_;
  std::shared_ptr<const GenHadTau> genHadTau_;
  std::shared_ptr<const GenJet> genJet_;

//--- flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
  mutable bool isLoose_;
  mutable bool isFakeable_;
  mutable bool isTight_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoLepton & lepton);

#endif // tthAnalysis_HiggsToTauTau_RecoLepton_h
