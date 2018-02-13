#ifndef tthAnalysis_HiggsToTauTau_RecoJetAK12_h
#define tthAnalysis_HiggsToTauTau_RecoJetAK12_h

/** \class RecoJetAK12
 *
 * Class to access information for jets reconstructed by the anti-kT algorithm with R=1.2 (AK12),
 * used for reconstruction of boosted W bosons (produced in hadronic top decays with resolved b-jets)
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK12.h" // RecoSubjetAK12

class RecoJetAK12
  : public RecoJetBase
{
public:
  RecoJetAK12() = default;
  RecoJetAK12(const GenJet & particle,
	      Double_t charge,
	      Double_t pullEta,
	      Double_t pullPhi,
	      Double_t pullMag,
	      Double_t QjetVolatility,
	      Double_t msoftdrop,
	      const RecoSubjetAK12* subJet1,
	      const RecoSubjetAK12* subJet2,
	      Double_t tau1,
	      Double_t tau2,
	      Double_t tau3,
	      Double_t tau4,
	      Int_t idx);

  virtual ~RecoJetAK12();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t charge() const;
  Double_t pullEta() const;
  Double_t pullPhi() const;
  Double_t pullMag() const;
  Double_t QjetVolatility() const;
  Double_t msoftdrop() const;
  const RecoSubjetAK12* subJet1() const;
  const RecoSubjetAK12* subJet2() const;
  Double_t tau1() const;
  Double_t tau2() const;
  Double_t tau3() const;
  Double_t tau4() const;

protected:
  Double_t charge_;
  Double_t pullEta_;
  Double_t pullPhi_;
  Double_t pullMag_;
  Double_t QjetVolatility_;
  Double_t msoftdrop_;
  const RecoSubjetAK12* subJet1_;
  const RecoSubjetAK12* subJet2_;
  Double_t tau1_;
  Double_t tau2_;
  Double_t tau3_;
  Double_t tau4_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetAK12 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJetAK12_h

