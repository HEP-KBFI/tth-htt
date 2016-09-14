#ifndef tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h
#define tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoMuonSelectorFakeable
{
 public:
  RecoMuonSelectorFakeable(int era, int index = -1, bool debug = false);
  ~RecoMuonSelectorFakeable() {}

  /**
   * @brief Check if muon given as function argument passes "fakeable" muon selection, defined in Table 12 of AN-2015/321
   * @return True if muon passes selection; false otherwise
   */
  bool operator()(const RecoMuon& muon) const;

 protected: 
  int era_;

  Double_t min_pt_;         ///< lower cut threshold on pT
  Double_t max_absEta_;     ///< upper cut threshold on absolute value of eta
  Double_t max_dxy_;        ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  Double_t max_dz_;         ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Double_t max_relIso_;     ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;      ///< upper cut threshold on significance of IP
  bool apply_looseIdPOG_;   ///< apply (True) or do not apply (False) loose PFMuon id selection
//-------------------------------------------------------------------------------
//--- define cuts that dependent on lepton MVA of ttH multilepton analysis 
//    format: muon fails / passes loose cut on lepton MVA value
  typedef std::vector<Double_t> vDouble_t;  
  vDouble_t binning_mvaTTH_;          ///< lepton MVA threshold
  vDouble_t min_jetPtRatio_;          ///< lower cut on ratio of lepton pT to pT of nearby jet
  vDouble_t max_jetBtagCSV_;          ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
//-------------------------------------------------------------------------------
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  bool apply_tightCharge_;  ///< apply (True) or do not apply (False) tight charge cut
};

class RecoMuonCollectionSelectorFakeable
{
 public:
  RecoMuonCollectionSelectorFakeable(int era, int index = -1, bool debug = false)
    : selIndex_(index)
    , selector_(era, index, debug)
  {}
  ~RecoMuonCollectionSelectorFakeable() {}

  std::vector<const RecoMuon*> operator()(const std::vector<const RecoMuon*>& muons) const
  {
    std::vector<const RecoMuon*> selMuons;
    int idx = 0;
    for ( typename std::vector<const RecoMuon*>::const_iterator muon = muons.begin();
	  muon != muons.end(); ++muon ) {
      if ( selector_(**muon) ) {
	if ( idx == selIndex_ || selIndex_ == -1 ) {
	  selMuons.push_back(*muon);
	}
	++idx;
      }
    }
    return selMuons;
  }
  
 protected: 
  int selIndex_;
  RecoMuonSelectorFakeable selector_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h

