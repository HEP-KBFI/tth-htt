#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h

/** \class RecoSubjetAK12
 *
 * Class to access information for subjets of jets reconstructed by the anti-kT algorithm with R=1.2 (AK12),
 * used for reconstruction of boosted W bosons (produced in hadronic top decays with resolved b-jets)
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase

class RecoSubjetAK12
  : public RecoJetBase
{
public:
  RecoSubjetAK12() = default;
  RecoSubjetAK12(const GenJet & particle,
		 Double_t charge,
		 Double_t pullEta,
		 Double_t pullPhi,
		 Double_t pullMag,
		 Int_t idx);

  virtual ~RecoSubjetAK12();

 /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t charge() const;
  Double_t pullEta() const;
  Double_t pullPhi() const;
  Double_t pullMag() const;

protected:
  Double_t charge_;
  Double_t pullEta_;
  Double_t pullPhi_;
  Double_t pullMag_;
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetAK12 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h

