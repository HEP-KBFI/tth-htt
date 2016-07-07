#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

template <typename Tobj, typename Tsel>
class ParticleCollectionSelector
{
 public:
  ParticleCollectionSelector(int index = -1, bool debug = false) 
    : selIndex_(index)
    , selector_(index, debug)
  {}
  ~ParticleCollectionSelector() {}

  /**
   * @brief Select subset of particles passing selection, by applying selector specified as template parameter to each particle in collection passed as function argument
   * @return Collection of selected particles
   */
  std::vector<const Tobj*> operator()(const std::vector<const Tobj*>& particles) const
  {
    std::vector<const Tobj*> selParticles;
    int idx = 0;
    for ( typename std::vector<const Tobj*>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      if ( (idx == selIndex_ || selIndex_ == -1) && selector_(**particle) ) {
	selParticles.push_back(*particle);
      }
      ++idx;
    }
    return selParticles;
  }
  
 protected: 
  int selIndex_;
  Tsel selector_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorCutBased.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorMVABased.h"

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorLoose> RecoElectronCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorTight> RecoElectronCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorFakeable> RecoElectronCollectionSelectorFakeable;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorCutBased> RecoElectronCollectionSelectorCutBased;
typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorMVABased> RecoElectronCollectionSelectorMVABased;

template<>
class ParticleCollectionSelector<RecoElectron, RecoElectronSelectorTight>
{
 public:
  ParticleCollectionSelector(int index = -1, bool debug = false)
    : selIndex_(index)
    , selector_(index, debug)
  {}
  ~ParticleCollectionSelector() {}

  void enable_offline_e_trigger_cuts() { selector_.enable_offline_e_trigger_cuts(); }
  void disable_offline_e_trigger_cuts() { selector_.disable_offline_e_trigger_cuts(); }

  std::vector<const RecoElectron*> operator()(const std::vector<const RecoElectron*>& particles) const
  {
    std::vector<const RecoElectron*> selParticles;
    int idx = 0;
    for ( typename std::vector<const RecoElectron*>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      if ( (idx == selIndex_ || selIndex_ == -1) && selector_(**particle) ) {
	selParticles.push_back(*particle);
      }
      ++idx;
    }
    return selParticles;
  }

 protected: 
  int selIndex_;
  RecoElectronSelectorTight selector_;
};

template<>
class ParticleCollectionSelector<RecoElectron, RecoElectronSelectorFakeable>
{
 public:
  ParticleCollectionSelector(int index = -1, bool debug = false)
    : selIndex_(index)
    , selector_(index, debug)
  {}
  ~ParticleCollectionSelector() {}

  void enable_offline_e_trigger_cuts() { selector_.enable_offline_e_trigger_cuts(); }
  void disable_offline_e_trigger_cuts() { selector_.disable_offline_e_trigger_cuts(); }

  std::vector<const RecoElectron*> operator()(const std::vector<const RecoElectron*>& particles) const
  {
    std::vector<const RecoElectron*> selParticles;
    int idx = 0;
    for ( typename std::vector<const RecoElectron*>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      if ( (idx == selIndex_ || selIndex_ == -1) && selector_(**particle) ) {
	selParticles.push_back(*particle);
      }
      ++idx;
    }
    return selParticles;
  }
  
 protected: 
  int selIndex_;
  RecoElectronSelectorFakeable selector_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorCutBased.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorMVABased.h"

typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorLoose> RecoMuonCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorTight> RecoMuonCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorFakeable> RecoMuonCollectionSelectorFakeable;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorCutBased> RecoMuonCollectionSelectorCutBased;
typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorMVABased> RecoMuonCollectionSelectorMVABased;

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorLoose.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorLoose_1l_2tau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight_1l_2tau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorFakeable_1l_2tau.h"

typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorLoose> RecoHadTauCollectionSelectorLoose;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorLoose_1l_2tau> RecoHadTauCollectionSelectorLoose_1l_2tau;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorTight> RecoHadTauCollectionSelectorTight;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorTight_1l_2tau> RecoHadTauCollectionSelectorTight_1l_2tau;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorFakeable> RecoHadTauCollectionSelectorFakeable;
typedef ParticleCollectionSelector<RecoHadTau, RecoHadTauSelectorFakeable_1l_2tau> RecoHadTauCollectionSelectorFakeable_1l_2tau;


#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelector.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelectorBtag.h"

typedef ParticleCollectionSelector<RecoJet, RecoJetSelector> RecoJetCollectionSelector;
typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagLoose> RecoJetCollectionSelectorBtagLoose;
typedef ParticleCollectionSelector<RecoJet, RecoJetSelectorBtagMedium> RecoJetCollectionSelectorBtagMedium;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

