#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateHistManagers.h"

#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getTrigMatching_string, matchesTrigObj
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"         // get_era

#include <TString.h> // Form

denominatorHistManagers::denominatorHistManagers(
  const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
  const std::string& hadTauSelection_denominator, const std::string& trigMatching_denominator, 
  double minAbsEta, double maxAbsEta, int decayMode, const std::string& central_or_shift)
  : process_(process)
  , era_string_(era_string)
  , era_(get_era(era_string))
  , isMC_(isMC)
  , chargeSelection_(chargeSelection)
  , hadTauSelection_denominator_(hadTauSelection_denominator)
  , minAbsEta_(minAbsEta)
  , maxAbsEta_(maxAbsEta)
  , decayMode_(decayMode)
  , central_or_shift_(central_or_shift)
  , jetHistManager_(0)
  , jetHistManager_genHadTau_(0)
  , jetHistManager_genLepton_(0)
  , jetHistManager_genJet_(0)
  , hadTauHistManager_(0)
  , hadTauHistManager_genHadTau_(0)
  , hadTauHistManager_genLepton_(0)
  , hadTauHistManager_genJet_(0)
  , fakeableHadTauSelector_(0)
  , evtHistManager_(0)
{
  trigMatching_denominator_ = getTrigMatchingOption(trigMatching_denominator);
  std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
  subdir_ = Form("jetToTauFakeRate_%s_%s/denominator/%s", chargeSelection_.data(), trigMatching_denominator.data(), etaBin.data());
  if ( decayMode != -1 ) subdir_.append(Form("_dm%i", decayMode));
  fakeableHadTauSelector_ = new RecoHadTauSelectorFakeable(era_);
  fakeableHadTauSelector_->set(hadTauSelection_denominator);
}

denominatorHistManagers::~denominatorHistManagers()
{
  delete jetHistManager_;
  delete jetHistManager_genHadTau_;
  delete jetHistManager_genLepton_;
  delete jetHistManager_genJet_;
  delete hadTauHistManager_;
  delete hadTauHistManager_genHadTau_;
  delete hadTauHistManager_genLepton_;
  delete hadTauHistManager_genJet_;
  delete fakeableHadTauSelector_;
  delete evtHistManager_;
}

void
denominatorHistManagers::bookHistograms(TFileDirectory& dir)
{
  jetHistManager_ = new JetHistManager(makeHistManager_cfg(process_, 
    Form("%s/jets", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
  jetHistManager_->bookHistograms(dir);
  if ( isMC_ ) {
    std::string process_and_genMatchedHadTau = process_ + "t";
    jetHistManager_genHadTau_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, 
      Form("%s/jets", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    jetHistManager_genHadTau_->bookHistograms(dir);
    std::string process_and_genMatchedLepton = process_ + "l";
    jetHistManager_genLepton_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedLepton, 
      Form("%s/jets", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    jetHistManager_genLepton_->bookHistograms(dir);
    std::string process_and_genMatchedJet = process_ + "j";
    jetHistManager_genJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedJet, 
      Form("%s/jets", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    jetHistManager_genJet_->bookHistograms(dir);
  }
  hadTauHistManager_ = new HadTauHistManager(makeHistManager_cfg(process_, 
    Form("%s/hadTaus", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
  hadTauHistManager_->bookHistograms(dir);
  if ( isMC_ ) {
    std::string process_and_genMatchedHadTau = process_ + "t";
    hadTauHistManager_genHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, 
      Form("%s/hadTaus", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    hadTauHistManager_genHadTau_->bookHistograms(dir);
    std::string process_and_genMatchedLepton = process_ + "l";
    hadTauHistManager_genLepton_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedLepton, 
      Form("%s/hadTaus", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    hadTauHistManager_genLepton_->bookHistograms(dir);
    std::string process_and_genMatchedJet = process_ + "j";
    hadTauHistManager_genJet_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedJet, 
      Form("%s/hadTaus", subdir_.data()), era_string_, central_or_shift_, "minimalHistograms"));
    hadTauHistManager_genJet_->bookHistograms(dir);
  }
  evtHistManager_ = new EvtHistManager_jetToTauFakeRate(makeHistManager_cfg(process_, 
    Form("%s/evt", subdir_.data()), era_string_, central_or_shift_));
  evtHistManager_->bookHistograms(dir);
}

void 
denominatorHistManagers::fillHistograms(const RecoJet& jet, const std::vector<TrigObj>& triggerObjects, const RecoHadTau& hadTau, double evtWeight)
{
  if ( trigMatching_denominator_ == kFilterBit_notApplied || matchesTrigObj(jet, triggerObjects, trigMatching_denominator_) ) 
  {
    bool isSelected_decayMode = false;
    if ( decayMode_ ==  -1                                                           ) isSelected_decayMode = true;
    if ( decayMode_ ==   0 &&  hadTau.decayMode() ==  0                              ) isSelected_decayMode = true;
    if ( decayMode_ ==   1 && (hadTau.decayMode() ==  1 || hadTau.decayMode() ==  2) ) isSelected_decayMode = true;
    if ( decayMode_ ==   2 && (hadTau.decayMode() ==  1 || hadTau.decayMode() ==  2) ) isSelected_decayMode = true;
    if ( decayMode_ ==   5 && (hadTau.decayMode() ==  5 || hadTau.decayMode() ==  6) ) isSelected_decayMode = true;
    if ( decayMode_ ==   6 && (hadTau.decayMode() ==  5 || hadTau.decayMode() ==  6) ) isSelected_decayMode = true;
    if ( decayMode_ ==  10 &&  hadTau.decayMode() == 10                              ) isSelected_decayMode = true;
    if ( decayMode_ ==  11 &&  hadTau.decayMode() == 11                              ) isSelected_decayMode = true;
    if ( jet.absEta() > minAbsEta_ && jet.absEta() < maxAbsEta_ && isSelected_decayMode ) {
      jetHistManager_->fillHistograms(jet, evtWeight);
      if ( isMC_ ) {
        if      ( jet.genHadTau() ) jetHistManager_genHadTau_->fillHistograms(jet, evtWeight);
        else if ( jet.genLepton() ) jetHistManager_genLepton_->fillHistograms(jet, evtWeight);
        else                        jetHistManager_genJet_->fillHistograms(jet, evtWeight);
      }
    }
    if ( hadTau.absEta() > minAbsEta_ && hadTau.absEta() < maxAbsEta_ && isSelected_decayMode ) {
      hadTauHistManager_->fillHistograms(hadTau, evtWeight);
      if ( isMC_ ) {
        if      ( hadTau.genHadTau() ) hadTauHistManager_genHadTau_->fillHistograms(hadTau, evtWeight);
        else if ( hadTau.genLepton() ) hadTauHistManager_genLepton_->fillHistograms(hadTau, evtWeight);
        else                           hadTauHistManager_genJet_->fillHistograms(hadTau, evtWeight);
      }
    }
  }
}

numeratorSelector_and_HistManagers::numeratorSelector_and_HistManagers(
  const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
  const std::string& hadTauSelection_denominator, const std::string&  trigMatching_denominator, const std::string& hadTauSelection_numerator, 
  double minAbsEta, double maxAbsEta, int decayMode, const std::string& central_or_shift)
  : denominatorHistManagers(process, era_string, isMC, chargeSelection, hadTauSelection_denominator, trigMatching_denominator, minAbsEta, maxAbsEta, decayMode, central_or_shift),
    hadTauSelection_numerator_(hadTauSelection_numerator),
    tightHadTauSelector_(0)
{
  std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
  subdir_ = Form("jetToTauFakeRate_%s_%s/numerator/%s/%s", chargeSelection_.data(), trigMatching_denominator.data(), hadTauSelection_numerator_.data(), etaBin.data());
  if ( decayMode != -1 ) subdir_.append(Form("_dm%i", decayMode));
  tightHadTauSelector_ = new RecoHadTauSelectorTight(era_);
  tightHadTauSelector_->set(hadTauSelection_numerator);
}

numeratorSelector_and_HistManagers::~numeratorSelector_and_HistManagers()
{
  delete tightHadTauSelector_;
}
 
void 
numeratorSelector_and_HistManagers::bookHistograms(TFileDirectory& dir)
{
  denominatorHistManagers::bookHistograms(dir);
}
  
void 
numeratorSelector_and_HistManagers::fillHistograms(const RecoJet& jet, const std::vector<TrigObj>& triggerObjects, const RecoHadTau& hadTau, double evtWeight)
{
  denominatorHistManagers::fillHistograms(jet, triggerObjects, hadTau, evtWeight);   
}
