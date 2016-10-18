#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoJetSelectorBtag
{
 public:
  RecoJetSelectorBtag(int era, int index, bool debug);
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
  RecoJetSelectorBtagLoose(int era, int index = -1, bool debug = false)
    : RecoJetSelectorBtag(era, index, debug) 
  {
    if      ( era_ == kEra_2015 ) min_BtagCSV_ = 0.460; // CSV loose WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X#Supported_Algorithms_and_Operati
    else if ( era_ == kEra_2016 ) min_BtagCSV_ = 0.460; // CSV loose WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80X#Supported_Algorithms_and_Operati
    else assert(0);
  }
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagLoose> RecoJetCollectionSelectorBtagLoose;

class RecoJetSelectorBtagMedium 
  : public RecoJetSelectorBtag
{
 public:
  RecoJetSelectorBtagMedium(int era, int index = -1, bool debug = false)
    : RecoJetSelectorBtag(era, index, debug)
  {
    if      ( era_ == kEra_2015 ) min_BtagCSV_ = 0.800; // CSV medium WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X#Supported_Algorithms_and_Operati
    else if ( era_ == kEra_2016 ) min_BtagCSV_ = 0.800; // CSV medium WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80X#Supported_Algorithms_and_Operati
    else assert(0);
  }
};

typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagMedium> RecoJetCollectionSelectorBtagMedium;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorBtag_h

