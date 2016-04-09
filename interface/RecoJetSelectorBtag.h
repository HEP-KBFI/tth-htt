#ifndef tthAnalysis_HiggsToTauTau_RecoJetSelectorBtag_h
#define tthAnalysis_HiggsToTauTau_RecoJetSelectorBtag_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoJetSelectorBtag
{
 public:
  RecoJetSelectorBtag();
  ~RecoJetSelectorBtag() {}

  /**
   * @brief Check if jet given as function argument passes pT and eta cuts (pT > 25 GeV and |eta| < 2.4, cf. Section 3.1 of AN-2015/321)
   * @return True if jet passes selection; false otherwise
   */
  bool operator()(const RecoJet& jet) const;

 protected: 
  Double_t min_pt_;      ///< lower cut threshold on pT
  Double_t max_absEta_;  ///< upper cut threshold on absolute value of eta
  Double_t min_BtagCSV_; ///< lower cut threshold on CSV b-tagging discriminator value
};

class RecoJetSelectorBtagLoose 
  : public RecoJetSelectorBtag
{
 public:
  RecoJetSelectorBtagLoose()
  {
    min_BtagCSV_ = 0.460; // CSV loose WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X#Supported_Algorithms_and_Operati
  }
};

class RecoJetSelectorBtagMedium 
  : public RecoJetSelectorBtag
{
 public:
  RecoJetSelectorBtagMedium()
  {
    min_BtagCSV_ = 0.800; // CSV medium WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X#Supported_Algorithms_and_Operati
  }
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetSelectorBtag_h

