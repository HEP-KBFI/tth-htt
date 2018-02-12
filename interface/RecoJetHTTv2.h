#ifndef tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h

/** \class RecoJetHTTv2
 *
 * Class to access information for jets reconstructed by hep-top-tagger (HTTv2) algorithm,
 * used for reconstruction of boosted hadronic tops
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h" // RecoSubjetHTTv2

class RecoJetHTTv2
  : public RecoJetBase
{
public:
  RecoJetHTTv2() = default;
  RecoJetHTTv2(const GenJet & particle,
	       Double_t area,
	       const RecoSubjetHTTv2* subJet1,
	       const RecoSubjetHTTv2* subJet2,
	       const RecoSubjetHTTv2* subJet3,
	       Double_t fRec,
	       Double_t Ropt,
	       Double_t RoptCalc,
	       Double_t ptForRoptCalc,
	       Int_t idx);

  virtual ~RecoJetHTTv2();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t area() const;
  const RecoSubjetHTTv2* subJet1() const;
  const RecoSubjetHTTv2* subJet2() const;
  const RecoSubjetHTTv2* subJet3() const;
  Double_t fRec() const;
  Double_t Ropt() const;
  Double_t RoptCalc() const;
  Double_t ptForRoptCalc() const;

protected:
  Double_t area_;
  const RecoSubjetHTTv2* subJet1_;
  const RecoSubjetHTTv2* subJet2_;
  const RecoSubjetHTTv2* subJet3_;
  Double_t fRec_;
  Double_t Ropt_;
  Double_t RoptCalc_;
  Double_t ptForRoptCalc_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetHTTv2 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h

