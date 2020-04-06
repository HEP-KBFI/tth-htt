#ifndef tthAnalysis_HiggsToTauTau_GenLeptonCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_GenLeptonCollectionSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"                  // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"       // Era

class GenLeptonSelector
{
public:
  explicit GenLeptonSelector(Era era,
			     int index = -1,
			     bool debug = false);
  ~GenLeptonSelector() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt_muon(double min_pt_muon);
  void set_max_absEta_muon(double max_absEta_muon);
  void set_min_pt_electron(double min_pt_electron);
  void set_max_absEta_electron(double max_absEta_electron);

  /**
   * @brief Get cut thresholds
   */
  double get_min_pt_muon() const;
  double get_max_absEta_muon() const;
  double get_min_pt_electron() const;
  double get_max_absEta_electron() const;

  /**
   * @brief Check if generator-level lepton given as function argument passes pT and eta cuts (pT > 5 GeV and |eta| < 2.4 for muons, pT > 7 GeV and |eta| < 2.5 for electrons)
   * @return True if lepton passes selection; false otherwise
   */
  bool
  operator()(const GenLepton & lepton) const;

protected:
  Era era_;
  Double_t min_pt_muon_;         ///< lower cut threshold on pT for muons
  Double_t max_absEta_muon_;     ///< upper cut threshold on absolute value of eta for muons
  Double_t min_pt_electron_;     ///< lower cut threshold on pT for electrons
  Double_t max_absEta_electron_; ///< upper cut threshold on absolute value of eta for electrons
  bool debug_;
};

typedef ParticleCollectionSelector<GenLepton, GenLeptonSelector> GenLeptonCollectionSelector;

#endif // tthAnalysis_HiggsToTauTau_GenLeptonCollectionSelector_h

