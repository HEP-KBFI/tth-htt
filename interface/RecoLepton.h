#ifndef tthAnalysis_HiggsToTauTau_RecoLepton_h
#define tthAnalysis_HiggsToTauTau_RecoLepton_h

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#include <ostream>

class RecoLepton
  : public GenLepton
{
 public:
  RecoLepton() = default;
  RecoLepton(Double_t pt,
	     Double_t eta,
	     Double_t phi,
	     Double_t mass,
	     Int_t pdgId,
	     Double_t dxy,
	     Double_t dz,
	     Double_t relIso,
	     Double_t chargedHadRelIso03,
	     Double_t miniIsoCharged,
	     Double_t miniIsoNeutral,
	     Double_t sip3d,
	     Double_t mvaRawTTH,
	     Double_t jetNDauChargedMVASel,
	     Double_t jetPtRel,
	     Double_t jetPtRatio,
	     Double_t jetBtagCSV,
	     Int_t tightCharge,
	     Int_t charge);

  /**
   * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
   */
  void set_isLoose() const { isLoose_ = true; }
  void set_isFakeable() const { isFakeable_ = true; }
  void set_isTight() const { isTight_ = true; }

  /**
   * @brief Set "cone pT" for leptons that pass the "fakeable" lepton selection, but fail the "tight" lepton selection, 
   *        as described in lines 304-306 of AN-2016/211
   */
  void set_cone_pt(Double_t cone_pt)
  {
    cone_pt_ = cone_pt;
    cone_p4_ = Particle::LorentzVector(cone_pt, eta_, phi_, mass_);
  }

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton* genLepton) { genLepton_ = genLepton; }
  void set_genHadTau(const GenHadTau* genHadTau) { genHadTau_ = genHadTau; }
  void set_genJet(const GenJet* genJet) { genJet_ = genJet; }

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  virtual bool
  is_electron() const { return false; }

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  virtual bool
  is_muon() const { return false; }

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t lepton_pt() const { return pt_; }
  const Particle::LorentzVector& lepton_p4() const { return p4_; }

  // CV: use original lepton pT instead of mixing lepron pT and cone_pT, as discussed on slide 2 of 
  //     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
  virtual Double_t pt() const { return pt_; }
  virtual const Particle::LorentzVector& p4() const { return p4_; }

  Double_t dxy() const { return dxy_; }
  Double_t dz() const { return dz_; }
  Double_t relIso() const { return relIso_; }
  Double_t chargedHadRelIso03() const { return chargedHadRelIso03_; }
  Double_t miniIsoCharged() const { return miniIsoCharged_ / pt(); }
  Double_t miniIsoNeutral() const { return miniIsoNeutral_ / pt(); }
  Double_t sip3d() const { return sip3d_; }
  Double_t mvaRawTTH() const { return mvaRawTTH_; }
  Double_t jetNDauChargedMVASel() const { return jetNDauChargedMVASel_; }
  Double_t jetPtRel() const { return jetPtRel_; }
  Double_t jetPtRatio() const { return jetPtRatio_; }
  Double_t jetBtagCSV() const { return jetBtagCSV_; }
  Int_t tightCharge() const { return tightCharge_; }
  Int_t charge() const { return charge_; }
  Double_t cone_pt() const 
  { 
    if ( isFakeable_ && !isTight_ ) return cone_pt_;
    else return pt_;
  }
  const Particle::LorentzVector& cone_p4() const 
  { 
    if ( isFakeable_ && !isTight_ ) return cone_p4_;
    else return p4_;
  }
  
  const GenLepton* genLepton() const { return genLepton_; }
  const GenHadTau* genHadTau() const { return genHadTau_; }
  const GenJet* genJet() const { return genJet_; }

  bool isLoose() const { return isLoose_; }
  bool isFakeable() const { return isFakeable_; }
  bool isTight() const { return isTight_; }

 protected:
//--- common observables for electrons and muons
  Double_t dxy_;                        ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz_;                         ///< d_{z}, distance on the z axis w.r.t PV
  Double_t relIso_;                     ///< relative isolation
  Double_t chargedHadRelIso03_;
  Double_t miniIsoCharged_;             ///< absolute charged isolation
  Double_t miniIsoNeutral_;             ///< absolute neutral isolation (PU corrected)
  Double_t sip3d_;                      ///< significance of IP
  Double_t mvaRawTTH_;                  ///< raw output of lepton MVA of ttH multilepton analysis
  Double_t jetNDauChargedMVASel_;       ///< number of charged constituents in the closest jet
  Double_t jetPtRel_;                   ///< relative pT of the lepton wrt the closest jet
  Double_t jetPtRatio_;                 ///< ratio of lepton pT to pT of nearby jet
  Double_t jetBtagCSV_;                 ///< CSV b-tagging discriminator value of nearby jet
  Int_t tightCharge_;                   ///< Flag indicating if lepton passes (>= 2) or fails (< 2) tight charge requirement
  Int_t charge_;                        ///< lepton charge

  Double_t cone_pt_;
  Particle::LorentzVector cone_p4_;

//--- matching to generator level particles
  const GenLepton* genLepton_;
  const GenHadTau* genHadTau_;
  const GenJet* genJet_;

//--- flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
  mutable bool isLoose_;
  mutable bool isFakeable_;
  mutable bool isTight_;
};

std::ostream& operator<<(std::ostream& stream, const RecoLepton& lepton);

#endif // tthAnalysis_HiggsToTauTau_RecoLepton_h
