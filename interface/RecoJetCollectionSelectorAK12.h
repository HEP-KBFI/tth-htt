#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorAK12_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorAK12_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h" // RecoJetAK12

class RecoJetSelectorAK12
{
public:
  explicit RecoJetSelectorAK12(int era,
                           int index = -1,
                           bool debug = false);
  ~RecoJetSelectorAK12() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);
  void set_min_msoftdrop(double min_msoftdrop);

  /**
   * @brief Get cut thresholds
   */
  double get_min_pt() const;
  double get_max_absEta() const;
  double get_min_msoftdrop() const;

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool
  operator()(const RecoJetAK12 & jet) const;

protected:
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
  Double_t min_msoftdrop_;
  bool debug_;
};

typedef ParticleCollectionSelector<RecoJetAK12, RecoJetSelectorAK12> RecoJetCollectionSelectorAK12;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h
