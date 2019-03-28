#ifndef tthAnalysis_HiggsToTauTau_RecoHadTau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTau_h

#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

#include <memory> // std::shared_ptr<>

// forward declarations
class GenLepton;
class GenJet;

class RecoHadTau
  : public GenHadTau
{
public:
  RecoHadTau() = default;
  RecoHadTau(const GenHadTau & particle,
             Double_t dxy,
             Double_t dz,
             Int_t decayMode,
             Bool_t decayModeFinding,
             Bool_t decayModeFindingNew,
             Int_t id_mva_dR03,
             Double_t raw_mva_dR03,
             Int_t id_mva_dR05,
             Double_t raw_mva_dR05,
             Int_t antiElectron,
             Int_t antiMuon,
             UInt_t filterBits,
             Int_t genMatchIdx);

  virtual ~RecoHadTau();

  /**
   * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
   */
  void set_isLoose() const;
  void set_isFakeable() const;
  void set_isTight() const;

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton * genLepton);
  void set_genHadTau(const GenHadTau * genHadTau);
  void set_genJet(const GenJet * genJet);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t dxy() const;
  Double_t dz() const;
  Int_t decayMode() const;
  Bool_t decayModeFinding() const;
  Bool_t decayModeFindingNew() const;
  Int_t id_mva_dR03() const;
  Double_t raw_mva_dR03() const;
  Int_t id_mva_dR05() const;
  Double_t raw_mva_dR05() const;
  Int_t antiElectron() const;
  Int_t antiMuon() const;
  UInt_t filterBits() const;
  Int_t genMatchIdx() const;

  const GenLepton * genLepton() const;
  const GenHadTau * genHadTau() const;
  const GenJet * genJet() const;

  bool isGenMatched() const;
  bool hasAnyGenMatch() const;

  bool isLoose() const;
  bool isFakeable() const;
  bool isTight() const;

protected:
  Int_t charge_;
  Double_t dxy_;               ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz_;                ///< d_{z}, distance on the z axis w.r.t PV
  Int_t decayMode_;            ///< tau decay mode (5x(nof charged pions - 1) - (nof neutral pions))
  Bool_t decayModeFinding_;    ///< decayModeFinding discriminator
  Bool_t decayModeFindingNew_; ///< new decayModeFinding discriminator
  Int_t id_mva_dR03_;          ///< MVA-based tau id computed with dR=0.3 isolation cone
  Double_t raw_mva_dR03_;      ///< raw output of MVA-based tau id computed with dR=0.3 isolation cone
  Int_t id_mva_dR05_;          ///< MVA-based tau id computed with dR=0.5 isolation cone
  Double_t raw_mva_dR05_;      ///< raw output of MVA-based tau id computed with dR=0.5 isolation cone
  Int_t antiElectron_;         ///< discriminator against electrons
  Int_t antiMuon_;             ///< discriminator against muons
  UInt_t filterBits_;          ///< bitmask of matching with trigger objects
  Int_t genMatchIdx_;          ///< index to matched gen particle

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
           const RecoHadTau & hadTau);

#endif // tthAnalysis_HiggsToTauTau_RecoHadTau_h

