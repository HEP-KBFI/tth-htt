#ifndef tthAnalysis_HiggsToTauTau_jetToTauFakeRateHistManagers_h
#define tthAnalysis_HiggsToTauTau_jetToTauFakeRateHistManagers_h

#include "CommonTools/Utils/interface/TFileDirectory.h" // TFileDirectory

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"                               // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h"                        // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"                            // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h"  // RecoHadTauSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h"     // RecoHadTauSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h"                     // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h"                             // TauFilterBit (enum)
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRateTTemu.h"  // EvtHistManager_jetToTauFakeRateTTemu
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRateDYmumu.h" // EvtHistManager_jetToTauFakeRateDYmumu

#include <vector> // std::vector
#include <string> // std::string

/**
 * @brief Auxiliary class for filling histograms for denominator
 */
struct denominatorHistManagers
{
  denominatorHistManagers(
    const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection_denominator, const std::string& trigMatching_denominator, 
    double minAbsEta, double maxAbsEta, int decayMode, const std::vector<int>& genJet_pdgIds, const std::string& central_or_shift);
  ~denominatorHistManagers();
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const RecoHadTau& hadTau, const RecoJet* jet, double evtWeight);
  std::string process_;
  std::string era_string_;
  Era era_;
  bool isMC_;
  std::string chargeSelection_;
  std::string hadTauSelection_denominator_;
  int trigMatching_denominator_;
  double minAbsEta_;
  double maxAbsEta_;
  int decayMode_;                  // value of -1 selects all hadronic taus
  std::vector<int> genJet_pdgIds_; // empty vector selects all hadronic taus
  std::string central_or_shift_;
  std::string subdir_;
  JetHistManager* jetHistManager_;
  JetHistManager* jetHistManager_genHadTau_;
  JetHistManager* jetHistManager_genLepton_;
  JetHistManager* jetHistManager_genJet_;
  HadTauHistManager* hadTauHistManager_;
  HadTauHistManager* hadTauHistManager_genHadTau_;
  HadTauHistManager* hadTauHistManager_genLepton_;
  HadTauHistManager* hadTauHistManager_genJet_;
  RecoHadTauSelectorFakeable* fakeableHadTauSelector_;
};

/**
 * @brief Auxiliary class for applying hadronic tau selection and filling histograms for numerator
 */
struct numeratorSelector_and_HistManagers : public denominatorHistManagers
{
  numeratorSelector_and_HistManagers(
    const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection_denominator, const std::string& trigMatching_denominator, const std::string& hadTauSelection_numerator, 
    double minAbsEta, double maxAbsEta, int decayMode, const std::vector<int>& genJet_pdgIds, const std::string& central_or_shift);
  ~numeratorSelector_and_HistManagers();
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const RecoHadTau& hadTau, const RecoJet* jet, double evtWeight);
  std::string hadTauSelection_numerator_;
  RecoHadTauSelectorTight* tightHadTauSelector_;
};

#endif // tthAnalysis_HiggsToTauTau_jetToTauFakeRateHistManagers_h
