#ifndef tthAnalysis_HiggsToTauTau_RecoJetAK8_h
#define tthAnalysis_HiggsToTauTau_RecoJetAK8_h

/** \class RecoJetAK8
 *
 * Class to access information for jets reconstructed by the anti-kT algorithm with R=1.2 (AK8),
 * used for reconstruction of boosted W bosons (produced in hadronic top decays with resolved b-jets)
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK8.h" // RecoSubjetAK8

#include <memory> // std::shared_ptr

class RecoJetAK8
  : public RecoJetBase
{
public:
  RecoJetAK8() = default;
  RecoJetAK8(const GenJet & particle,
	      Double_t msoftdrop,
	      const RecoSubjetAK8* subJet1,
	      const RecoSubjetAK8* subJet2,
	      Double_t tau1,
	      Double_t tau2,
	      Double_t tau3,
	      Double_t tau4,
	      Int_t jetId,
	      Int_t idx);

  virtual ~RecoJetAK8();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t msoftdrop() const;
  const RecoSubjetAK8* subJet1() const;
  const RecoSubjetAK8* subJet2() const;
  Double_t tau1() const;
  Double_t tau2() const;
  Double_t tau3() const;
  Double_t tau4() const;
  Int_t jetId() const;

protected: 
  Double_t msoftdrop_;
  std::shared_ptr<const RecoSubjetAK8> subJet1_;
  std::shared_ptr<const RecoSubjetAK8> subJet2_;
  Double_t tau1_;
  Double_t tau2_;
  Double_t tau3_;
  Double_t tau4_;
  Int_t jetId_;   ///< jet ID, as explained in https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetAK8 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJetAK8_h
