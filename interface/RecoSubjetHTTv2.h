#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetHTTv2_h

/** \class RecoJet
 *
 * Class to access information for subjets of jets reconstructed by hep-top-tagger (HTTv2) algorithm,
 * used for reconstruction of boosted hadronic tops
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase

class RecoSubjetHTTv2
  : public RecoJetBase
{
public:
  RecoSubjetHTTv2() = default;
  RecoSubjetHTTv2(const GenJet & particle,
		  Bool_t IDPassed,
		  Double_t BtagCSV,
		  Double_t area,
		  Int_t idx);

  virtual ~RecoSubjetHTTv2();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Bool_t IDPassed() const;
  Double_t BtagCSV() const;
  Double_t area() const;

protected:
  Bool_t IDPassed_;
  Double_t BtagCSV_;
  Double_t area_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetHTTv2 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetHTTv2_h

