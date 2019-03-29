#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorForward_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorForward_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

class RecoJetSelectorForward
{
public:
  explicit RecoJetSelectorForward(int era,
                           int index = -1,
                           bool debug = false);
  ~RecoJetSelectorForward() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);
  void set_min_jetId(int min_jetId);

  /**
   * @brief Get cut thresholds
   */
  double get_min_pt() const;
  double get_max_absEta() const;
  double get_min_absEta() const;
  int get_min_jetId() const;

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool
  operator()(const RecoJet & jet) const;

protected:
  int era_;
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
  Double_t min_absEta_; ///< upper cut threshold on absolute value of eta
  Int_t min_jetId_;     ///< lower cut threshold on jet ID value
  bool debug_;
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorForward> RecoJetCollectionSelectorForward;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorForward_h
