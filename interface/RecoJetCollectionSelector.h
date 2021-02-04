#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"                    // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"       // Era, pileupJetID

class RecoJetSelector
{
public:
  explicit RecoJetSelector(Era era,
                           int index = -1,
                           bool debug = false);
  ~RecoJetSelector() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);
  void set_min_jetId(int min_jetId);
  void set_pileupJetId(pileupJetID apply_pileupJetId);

  /**
   * @brief Get cut thresholds
   */
  double get_min_pt() const;
  double get_max_absEta() const;
  int get_min_jetId() const;
  pileupJetID get_pileupJetId() const;

  /**
   * @brief Check if jet given as function argument passes the selection cuts
   * @return True if jet passes selection; false otherwise
   */
  bool
  operator()(const RecoJet & jet) const;

protected:
  Era era_;
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
  Int_t min_jetId_;     ///< lower cut threshold on jet ID value
  pileupJetID apply_pileupJetId_;
  bool debug_;
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelector> RecoJetCollectionSelector;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelector_h

