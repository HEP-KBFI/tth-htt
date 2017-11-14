#ifndef tthAnalysis_HiggsToTauTau_RecoHadTau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTau_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#include <ostream> // ostream

class RecoHadTau : public Particle
{
 public:
  RecoHadTau() = default;
  RecoHadTau(Double_t pt,
	     Double_t eta,
	     Double_t phi,
	     Double_t mass,
	     Int_t charge,
	     Double_t dxy,
	     Double_t dz,
	     Int_t decayMode,
       Bool_t decayModeFinding,
       Bool_t decayModeFindingNew,
	     Int_t id_mva_dR03,
	     Double_t raw_mva_dR03,
	     Int_t id_mva_dR05,
	     Double_t raw_mva_dR05,
	     Int_t id_cut_dR03,
	     Double_t raw_cut_dR03,
	     Int_t id_cut_dR05,
	     Int_t antiElectron,
	     Int_t antiMuon);

  virtual ~RecoHadTau();

  /**
   * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
   */
  void set_isLoose() const { isLoose_ = true; }
  void set_isFakeable() const { isFakeable_ = true; }
  void set_isTight() const { isTight_ = true; }

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton* genLepton, bool isOwner = false) { genLepton_ = genLepton; genLepton_isOwner_ = isOwner; }
  void set_genHadTau(const GenHadTau* genHadTau, bool isOwner = false) { genHadTau_ = genHadTau; genHadTau_isOwner_ = isOwner; }
  void set_genJet(const GenJet* genJet, bool isOwner = false) { genJet_ = genJet; genJet_isOwner_ = isOwner; }

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Int_t charge() const { return charge_; }
  Double_t dxy() const { return dxy_; }
  Double_t dz() const { return dz_; }
  Int_t decayMode() const { return decayMode_; }
  Bool_t decayModeFinding() const { return decayModeFinding_; }
  Bool_t decayModeFindingNew() const { return decayModeFindingNew_; }
  Int_t id_mva_dR03() const { return id_mva_dR03_; }
  Double_t raw_mva_dR03() const { return raw_mva_dR03_; }
  Int_t id_mva_dR05() const { return id_mva_dR05_; }
  Double_t raw_mva_dR05() const { return raw_mva_dR05_; }
  Int_t id_cut_dR03() const { return id_cut_dR03_; }
  Double_t raw_cut_dR03() const { return raw_cut_dR03_; }
  Int_t id_cut_dR05() const { return id_cut_dR05_; }
  Int_t antiElectron() const { return antiElectron_; }
  Int_t antiMuon() const { return antiMuon_; }

  const GenLepton* genLepton() const { return genLepton_; }
  const GenHadTau* genHadTau() const { return genHadTau_; }
  const GenJet* genJet() const { return genJet_; }

  bool isLoose() const { return isLoose_; }
  bool isFakeable() const { return isFakeable_; }
  bool isTight() const { return isTight_; }

 protected:
  Int_t charge_;
  Double_t dxy_;              ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz_;               ///< d_{z}, distance on the z axis w.r.t PV
  Int_t decayMode_;           ///< tau decay mode (5x(nof charged pions - 1) - (nof neutral pions))
  Bool_t decayModeFinding_;    ///< decayModeFinding discriminator
  Bool_t decayModeFindingNew_; ///< new decayModeFinding discriminator
  Int_t id_mva_dR03_;         ///< MVA-based tau id computed with dR=0.3 isolation cone
  Double_t raw_mva_dR03_;     ///< raw output of MVA-based tau id computed with dR=0.3 isolation cone
  Int_t id_mva_dR05_;         ///< MVA-based tau id computed with dR=0.5 isolation cone
  Double_t raw_mva_dR05_;     ///< raw output of MVA-based tau id computed with dR=0.5 isolation cone
  Int_t id_cut_dR03_;         ///< cut-based tau id computed with dR=0.3 isolation cone
  Double_t raw_cut_dR03_;     ///< raw isolation pT-sum of cut-based tau id computed with dR=0.3 isolation cone
  Int_t id_cut_dR05_;         ///< cut-based tau id computed with dR=0.5 isolation cone
  Int_t antiElectron_;        ///< discriminator against electrons
  Int_t antiMuon_;            ///< discriminator against muons

//--- matching to generator level particles
  const GenLepton* genLepton_;
  bool genLepton_isOwner_;
  const GenHadTau* genHadTau_;
  bool genHadTau_isOwner_;
  const GenJet* genJet_;
  bool genJet_isOwner_;

//--- flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
  mutable bool isLoose_;
  mutable bool isFakeable_;
  mutable bool isTight_;
};

std::ostream& operator<<(std::ostream& stream, const RecoHadTau& hadTau);

#endif // tthAnalysis_HiggsToTauTau_RecoHadTau_h

