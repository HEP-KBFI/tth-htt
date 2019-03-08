#ifndef tthAnalysis_HiggsToTauTau_GenJetCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_GenJetCollectionSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

class GenJetSelector
{
public:
  explicit GenJetSelector(int era,
			  int index = -1,
			  bool debug = false);
  ~GenJetSelector() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);

  /**
   * @brief Get cut thresholds
   */
  double get_min_pt() const;
  double get_max_absEta() const;

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool
  operator()(const GenJet & jet) const;

protected:
  int era_;
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
  bool debug_;
};

typedef ParticleCollectionSelector<GenJet, GenJetSelector> GenJetCollectionSelector;

#endif // tthAnalysis_HiggsToTauTau_GenJetCollectionSelector_h

