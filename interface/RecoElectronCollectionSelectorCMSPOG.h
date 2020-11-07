#ifndef tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorCMSPOG_h
#define tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorCMSPOG_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"               // RecoElectron

enum class Era;

class RecoElectronSelectorCMSPOG
{
public:
  explicit
  RecoElectronSelectorCMSPOG(Era era,
                             int index = -1,
                             bool debug = false,
                             bool set_selection_flags = true);
  ~RecoElectronSelectorCMSPOG() {}

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
   * @brief Check if electron given as function argument passes "CMS POG" electron selection, defined in
   *        https://git.rwth-aachen.de/3pia/cms_analyses/bbww_dl/-/blob/33d3a9b255044a8655f2d47e43d5d3ca4350671c/recipes/selection.py#L189-195
   * @return True if electron passes selection; false otherwise
   */
  bool operator()(const RecoElectron & electron) const;

protected:
  bool set_selection_flags_;
  bool debug_;               ///< enable printout for debugging purposes
  const Era era_;

  Double_t min_pt_;          ///< lower cut threshold on reco::GSFElectron pT
  Double_t max_absEta_;      ///< upper cut threshold on absolute value of eta
};

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorCMSPOG> RecoElectronCollectionSelectorCMSPOG;

#endif // tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorCMSPOG_h
