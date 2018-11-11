#ifndef tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h

/** \class RecoJetHTTv2
 *
 * Class to access information for jets reconstructed by hep-top-tagger (HTTv2) algorithm,
 * used for reconstruction of boosted hadronic tops
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h" // RecoSubjetHTTv2

#include <memory> // std::shared_ptr

class RecoJetHTTv2
  : public RecoJetBase
{
public:
  RecoJetHTTv2() = default;
  RecoJetHTTv2(const GenJet & particle,
               Double_t area,
               const RecoSubjetHTTv2 * subJet1,
               const RecoSubjetHTTv2 * subJet2,
               const RecoSubjetHTTv2 * subJet3,
               Double_t fRec,
               Double_t Ropt,
               Double_t RoptCalc,
               Double_t ptForRoptCalc,
               Double_t tau1,
               Double_t tau2,
               Double_t tau3,
               Int_t idx);

  virtual ~RecoJetHTTv2();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t area() const;
  const RecoSubjetHTTv2 * subJet1() const;
  const RecoSubjetHTTv2 * subJet2() const;
  const RecoSubjetHTTv2 * subJet3() const;
  Double_t fRec() const;
  Double_t Ropt() const;
  Double_t RoptCalc() const;
  Double_t ptForRoptCalc() const;
  Double_t tau1() const;
  Double_t tau2() const;
  Double_t tau3() const;

protected:
  Double_t area_;
  std::shared_ptr<const RecoSubjetHTTv2> subJet1_;
  std::shared_ptr<const RecoSubjetHTTv2> subJet2_;
  std::shared_ptr<const RecoSubjetHTTv2> subJet3_;
  Double_t fRec_;
  Double_t Ropt_;
  Double_t RoptCalc_;
  Double_t ptForRoptCalc_;
  Double_t tau1_;
  Double_t tau2_;
  Double_t tau3_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetHTTv2 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJetHTTv2_h
