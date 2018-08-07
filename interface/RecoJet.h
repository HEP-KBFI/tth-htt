#ifndef tthAnalysis_HiggsToTauTau_RecoJet_h
#define tthAnalysis_HiggsToTauTau_RecoJet_h

/** \class RecoJet
 *
 * Class to access information for "resolved" jets, 
 * reconstructed by anti-kT algorithm with dR=0.4
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase

#include <map> // std::map<,>

class RecoJet
  : public RecoJetBase
{
public:
  RecoJet() = default;
  RecoJet(const GenJet & particle,
          Double_t charge,
          Double_t BtagCSV,
          Double_t BtagWeight,
          Double_t QGDiscr,
          Double_t pullEta,
          Double_t pullPhi,
          Double_t pullMag,
          Int_t jetId,
          Int_t idx);

  virtual ~RecoJet();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t charge() const;
  Double_t BtagCSV() const;
  Double_t BtagWeight() const;
  Double_t QGDiscr() const;
  Double_t pullEta() const;
  Double_t pullPhi() const;
  Double_t pullMag() const;
  Int_t jetId() const;

  Double_t maxPt() const;

  friend class RecoJetReader;
  friend class RecoJetWriter;

protected:
  Double_t charge_;     ///< jet charge, computed according to JME-13-006
  Double_t BtagCSV_;    ///< CSV b-tagging discriminator value
  Double_t BtagWeight_; ///< weight for data/MC correction of b-tagging efficiency and mistag rate
  Double_t QGDiscr_;    ///< quark/gluon discriminator
  Double_t pullEta_;    ///< eta component of pull vector, computed according to arXiv:1001.5027
  Double_t pullPhi_;    ///< phi component of pull vector, computed according to arXiv:1001.5027
  Double_t pullMag_;    ///< magnitude of pull vector, computed according to arXiv:1001.5027
  Int_t jetId_;         ///< jet ID, as explained in https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017

  //---------------------------------------------------------
  // CV: needed by RecoJetWriter
  std::map<int, Double_t> BtagWeight_systematics_;
  std::map<int, Double_t> pt_systematics_;
  std::map<int, Double_t> mass_systematics_;
  //---------------------------------------------------------
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h

