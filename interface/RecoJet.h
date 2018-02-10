#ifndef tthAnalysis_HiggsToTauTau_RecoJet_h
#define tthAnalysis_HiggsToTauTau_RecoJet_h

/** \class RecoJet
 *
 * Class to access information for "resolved" jets, 
 * reconstructed by anti-kT algorithm with dR=0.4
 *
 * \author Christian Veelken, Tallin
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
          Double_t jecUncertTotal,
          Double_t BtagCSV,
          Double_t BtagWeight,
          Double_t QGDiscr,
          Int_t heppyFlavour,
          Int_t idx);

  virtual ~RecoJet();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t jecUncertTotal() const;
  Double_t BtagCSV() const;
  Double_t BtagWeight() const;
  Double_t QGDiscr() const;
  Int_t heppyFlavour() const;

  friend class RecoJetReader;
  friend class RecoJetWriter;

protected:
  Double_t jecUncertTotal_; ///< 1 sigma jet energy correction
  Double_t BtagCSV_;      ///< CSV b-tagging discriminator value
  Double_t BtagWeight_;   ///< weight for data/MC correction of b-tagging efficiency and mistag rate
  Double_t QGDiscr_;      ///< quark/gluon discriminator
  Int_t heppyFlavour_;    ///< Jet heppy flavour

  //---------------------------------------------------------
  // CV: needed by RecoJetWriter
  std::map<int, Double_t> BtagWeight_systematics_; 
  //---------------------------------------------------------
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h

