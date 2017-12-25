#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoJetSelectorBtag
{
 public:
  explicit RecoJetSelectorBtag(int era, int index, bool debug);
  ~RecoJetSelectorBtag() {}

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool operator()(const RecoJet& jet) const;

 protected: 
  int era_;
  bool debug_;
  Double_t min_pt_;      ///< lower cut threshold on pT
  Double_t max_absEta_;  ///< upper cut threshold on absolute value of eta
  Double_t min_BtagCSV_; ///< lower cut threshold on CSV b-tagging discriminator value    
};

class RecoJetSelectorBtagLoose 
  : public RecoJetSelectorBtag
{
 public:
  explicit RecoJetSelectorBtagLoose(int era, int index = -1, bool debug = false)
    : RecoJetSelectorBtag(era, index, debug) 
  {
    // NB! no btag CSVv2 WPs for 2017, yet!
    if ( era_ == kEra_2017 ) min_BtagCSV_ = 0.5426; // CSV loose WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    else assert(0);
  }
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagLoose> RecoJetCollectionSelectorBtagLoose;

class RecoJetSelectorBtagMedium 
  : public RecoJetSelectorBtag
{
 public:
  explicit RecoJetSelectorBtagMedium(int era, int index = -1, bool debug = false)
    : RecoJetSelectorBtag(era, index, debug)
  {
    // NB! no btag CSVv2 WPs for 2017, yet!
    if ( era_ == kEra_2017 ) min_BtagCSV_ = 0.8484; // CSV medium WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    else assert(0);
  }
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagMedium> RecoJetCollectionSelectorBtagMedium;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h

