#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoJetSelector
{
 public:
  RecoJetSelector(int era, int index = -1, bool debug = false);
  ~RecoJetSelector() {}

  /**
   * @brief Set cut thresholds
   */

  void set_min_pt(double min_pt) { min_pt_ = min_pt; }
  void set_max_absEta(double max_absEta) { max_absEta_ = max_absEta; }

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool operator()(const RecoJet& jet) const;

 protected: 
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelector> RecoJetCollectionSelector;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h

