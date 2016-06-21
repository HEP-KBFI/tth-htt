#ifndef tthAnalysis_HiggsToTauTau_RecoJetSelector_h
#define tthAnalysis_HiggsToTauTau_RecoJetSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoJetSelector
{
 public:
  RecoJetSelector(bool debug = false);
  ~RecoJetSelector() {}

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool operator()(const RecoJet& jet) const;

 protected: 
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetSelector_h

