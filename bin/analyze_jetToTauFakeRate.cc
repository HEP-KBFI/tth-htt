#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TError.h> // gErrorAbortLevel, kError
#include <TROOT.h> // TROOT

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2los_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // RecoElectronSelectorTight, RecoMuonSelectorTight, RecoHadTauSelectorLoose, RecoHadTauSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRate.h" // EvtHistManager_jetToTauFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;
typedef std::vector<int> vint;

/**
 * @brief Auxiliary class for filling histograms for denominator
 */
struct denominatorHistManagers
{
  denominatorHistManagers(
    const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection_denominator, double minAbsEta, double maxAbsEta, int decayMode, const std::string& central_or_shift)
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
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    subdir_ = Form("jetToTauFakeRate_%s/denominator/%s", chargeSelection_.data(), etaBin.data());
    if ( decayMode != -1 ) subdir_.append(Form("_dm%i", decayMode));
    fakeableHadTauSelector_ = new RecoHadTauSelectorFakeable(era_);
    fakeableHadTauSelector_->set(hadTauSelection_denominator);
  }
  ~denominatorHistManagers()
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
  void bookHistograms(TFileDirectory& dir)
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
  void fillHistograms(const RecoJet& jet, const RecoHadTau& hadTau, double evtWeight)
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
  std::string process_;
  std::string era_string_;
  int era_;
  bool isMC_;
  std::string chargeSelection_;
  std::string hadTauSelection_denominator_;
  double minAbsEta_;
  double maxAbsEta_;
  int decayMode_; // set to -1 to select all hadronic taus
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
  EvtHistManager_jetToTauFakeRate* evtHistManager_;
};

/**
 * @brief Auxiliary class for applying hadronic tau selection and filling histograms for numerator
 */
struct numeratorSelector_and_HistManagers : public denominatorHistManagers
{
  numeratorSelector_and_HistManagers(
    const std::string& process, const std::string& era_string, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection_denominator, const std::string& hadTauSelection_numerator, double minAbsEta, double maxAbsEta, int decayMode, const std::string& central_or_shift)
    : denominatorHistManagers(process, era_string, isMC, chargeSelection, hadTauSelection_denominator, minAbsEta, maxAbsEta, decayMode, central_or_shift),
      hadTauSelection_numerator_(hadTauSelection_numerator),
      tightHadTauSelector_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);    
    subdir_ = Form("jetToTauFakeRate_%s/numerator/%s/%s", chargeSelection_.data(), hadTauSelection_numerator_.data(), etaBin.data());
    if ( decayMode != -1 ) subdir_.append(Form("_dm%i", decayMode));
    tightHadTauSelector_ = new RecoHadTauSelectorTight(era_);
    tightHadTauSelector_->set(hadTauSelection_numerator);
  }
  ~numeratorSelector_and_HistManagers()
  {
    delete tightHadTauSelector_;
  }
  void bookHistograms(TFileDirectory& dir)
  {
    denominatorHistManagers::bookHistograms(dir);
  }
  void fillHistograms(const RecoJet& jet, const RecoHadTau& hadTau, double evtWeight)
  {
    denominatorHistManagers::fillHistograms(jet, hadTau, evtWeight);   
  }
  std::string hadTauSelection_numerator_;
  RecoHadTauSelectorTight* tightHadTauSelector_;
};

/**
 * @brief Produce datacard and control plots for 2los_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- stop ROOT from keeping track of all histograms
  TH1::AddDirectory(false);

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_jetToTauFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_jetToTauFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_jetToTauFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_jetToTauFakeRate");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tHq = process_string == "tHq";
  const bool isMC_tHW = process_string == "tHW";
  const bool isMC_tH = isMC_tHq || isMC_tHW;
  const bool isSignal = process_string == "ttH" || process_string == "ttH_ctcvcp";

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  int chargeSelection = -1;
  if      ( chargeSelection_string == "OS" ) chargeSelection = kOS;
  else if ( chargeSelection_string == "SS" ) chargeSelection = kSS;
  else throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !!\n";

  double jet_minPt = cfg_analyze.getParameter<double>("jet_minPt");
  double jet_maxPt = cfg_analyze.getParameter<double>("jet_maxPt");
  double jet_minAbsEta = cfg_analyze.getParameter<double>("jet_minAbsEta");
  double jet_maxAbsEta = cfg_analyze.getParameter<double>("jet_maxAbsEta");

  std::string hadTau_selection_tight = cfg_analyze.getParameter<std::string>("hadTau_selection_tight");
  std::string hadTauSelection_denominator = cfg_analyze.getParameter<std::string>("hadTauSelection_denominator");
  vstring hadTauSelections_numerator = cfg_analyze.getParameter<vstring>("hadTauSelections_numerator");
  std::cout << "hadTauSelection:" << std::endl;
  std::cout << " denominator = " << hadTauSelection_denominator << std::endl;
  std::cout << " numerator = " << format_vstring(hadTauSelections_numerator) << std::endl;

  vdouble absEtaBins = cfg_analyze.getParameter<vdouble>("absEtaBins");
  if ( absEtaBins.size() < 2 ) throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins' !!\n";
  vint decayModes = cfg_analyze.getParameter<vint>("decayModes");
  if ( decayModes.size() < 1 ) throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'decayModes' !!\n";
  
  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_l1PreFireWeight = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift);
  }

  edm::ParameterSet triggerWhiteList;
  if(! isMC)
  {
    triggerWhiteList = cfg_analyze.getParameter<edm::ParameterSet>("triggerWhiteList");
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option          = getJet_option       (central_or_shift, isMC);
  const int hadTauPt_option       = getHadTauPt_option  (central_or_shift);
  const int met_option            = getMET_option       (central_or_shift, isMC);
  const TauIDSFsys tauIDSF_option = getTauIDSFsys_option(central_or_shift);

  std::cout
    << "central_or_shift = "     << central_or_shift           << "\n"
       " -> hadTauPt_option  = " << hadTauPt_option            << "\n"
       " -> met_option       = " << met_option                 << "\n"
       " -> jetPt_option     = " << jetPt_option               << "\n"
       " -> tauIDSF_option   = " << as_integer(tauIDSF_option) << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTau_selection_tight); // has no effect (will be overwritten)
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_jetToTauFakeRate", __LINE__) << "Invalid era = " << era;
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  edm::ParameterSet cfg_EvtYieldHistManager = cfg_analyze.getParameter<edm::ParameterSet>("cfgEvtYieldHistManager");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isMC);
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isSignal) && ! tHweights.empty())
  {
    eventInfo.set_central_or_shift(central_or_shift);
    eventInfo.loadWeight_tH(tHweights);
  }
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  ObjectMultiplicity objectMultiplicity;
  ObjectMultiplicityReader objectMultiplicityReader(&objectMultiplicity);
  if(useObjectMultiplicity)
  {
    inputTree -> registerReader(&objectMultiplicityReader);
  }

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_1mu, triggers_1e1mu });
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

  L1PreFiringWeightReader * l1PreFiringWeightReader = nullptr;
  if(apply_l1PreFireWeight)
  {
    l1PreFiringWeightReader = new L1PreFiringWeightReader(era);
    inputTree->registerReader(l1PreFiringWeightReader);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree->registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorFakeable preselHadTauSelector(era);
  preselHadTauSelector.set(hadTauSelection_denominator);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  tightHadTauSelector.set(hadTau_selection_tight);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics(central_or_shift != "central" && isMC);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  GenJetReader * genJetReader = nullptr;
  LHEInfoReader * lheInfoReader = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  GenParticleReader * genMatchToHadTauReader   = nullptr;
  GenParticleReader * genMatchToJetReader      = nullptr;
  if(isMC)
  {
    if(! readGenObjects)
    {
      genLeptonReader = new GenLeptonReader(branchName_genLeptons);
      inputTree->registerReader(genLeptonReader);
      genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
      inputTree->registerReader(genHadTauReader);
      genJetReader = new GenJetReader(branchName_genJets);
      inputTree->registerReader(genJetReader);

      if(genMatchingByIndex)
      {
        genMatchToMuonReader = new GenParticleReader(branchName_muonGenMatch);
        genMatchToMuonReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToMuonReader);

        genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
        genMatchToElectronReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToElectronReader);

        genMatchToHadTauReader = new GenParticleReader(branchName_hadTauGenMatch);
        genMatchToHadTauReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToHadTauReader);

        genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
        genMatchToJetReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToJetReader);
      }
      else
      {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree -> registerReader(genPhotonReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree->registerReader(lheInfoReader);
  }

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/electrons", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selElectronHistManager.bookHistograms(fs);

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/muons", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selMuonHistManager.bookHistograms(fs);

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genHadTau(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genHadTau", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selHadTauHistManager_genHadTau.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genElectron(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genElectron", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selHadTauHistManager_genElectron.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genMuon(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genMuon", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selHadTauHistManager_genMuon.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genJet(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genJet", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selHadTauHistManager_genJet.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/jets", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/leadJet", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms", 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/subleadJet", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms", 1));
  selJetHistManager_sublead.bookHistograms(fs);

  std::vector<denominatorHistManagers*> denominators;
  std::vector<numeratorSelector_and_HistManagers*> numerators;
  int numEtaBins = absEtaBins.size() - 1;
  for ( int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin ) {
    double minAbsEta = absEtaBins[idxEtaBin];
    double maxAbsEta = absEtaBins[idxEtaBin + 1];
    for ( vint::const_iterator decayMode = decayModes.begin();
          decayMode != decayModes.end(); ++decayMode ) {
      denominatorHistManagers* denominator = new denominatorHistManagers(
        process_string, era_string, isMC, chargeSelection_string, hadTauSelection_denominator, 
        minAbsEta, maxAbsEta, *decayMode, central_or_shift);
      denominator->bookHistograms(fs);
      denominators.push_back(denominator);

      for ( vstring::const_iterator hadTauSelection_numerator = hadTauSelections_numerator.begin();
            hadTauSelection_numerator != hadTauSelections_numerator.end(); ++hadTauSelection_numerator ) {
        numeratorSelector_and_HistManagers* numerator = new numeratorSelector_and_HistManagers(
          process_string, era_string, isMC, chargeSelection_string, hadTauSelection_denominator, *hadTauSelection_numerator,
          minAbsEta, maxAbsEta, *decayMode, central_or_shift);
        numerator->bookHistograms(fs);
        numerators.push_back(numerator);
      }
    }
  }

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/BJets_loose", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/leadBJet_loose", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms", 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/subleadBJet_loose", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms", 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/BJets_medium", chargeSelection_string.data()), era_string, central_or_shift, "minimalHistograms"));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/met", chargeSelection_string.data()), era_string, central_or_shift));
  selMEtHistManager.bookHistograms(fs);
  MEtFilterHistManager selMEtFilterHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/metFilters", chargeSelection_string.data()), era_string, central_or_shift));
  selMEtFilterHistManager.bookHistograms(fs);

  EvtHistManager_jetToTauFakeRate selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/evt", chargeSelection_string.data()), era_string, central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/evtYield", chargeSelection_string.data()), era_string, central_or_shift);
  cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
  cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
  EvtYieldHistManager selEvtYieldHistManager(cfg_EvtYieldHistManager_sel);
  selEvtYieldHistManager.bookHistograms(fs);

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/unbiased/genEvt", chargeSelection_string.data()), era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/sel/genEvt", chargeSelection_string.data()), era_string, central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/sel/lheInfo", chargeSelection_string.data()), era_string, central_or_shift));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  while(inputTree->hasNextEvent())
  {
    if(inputTree->canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree->getCurrentMaxEventIdx()
                << " or " << inputTree->getCurrentEventIdx() << " entry in #" << (inputTree->getProcessedFileCount() - 1)
                << " (" << eventInfo << ") file (" << selectedEntries << " entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(kTight)   != 2 ||
         objectMultiplicity.getNRecoElectron(kTight) != 1 ||
         objectMultiplicity.getNRecoMuon(kTight)     != 1  )
      {
        if(isDEBUG)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;

    std::vector<GenParticle> muonGenMatch;
    std::vector<GenParticle> electronGenMatch;
    std::vector<GenParticle> hadTauGenMatch;
    std::vector<GenParticle> jetGenMatch;
    if(isMC && fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToHadTauReader)   hadTauGenMatch = genMatchToHadTauReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }

    EvtWeightRecorder evtWeightRecorder({central_or_shift}, central_or_shift, isMC);
    if(isMC)
    {
      if(apply_genWeight)         evtWeightRecorder.record_genWeight(boost::math::sign(eventInfo.genWeight));
      if(eventWeightManager)      evtWeightRecorder.record_auxWeight(eventWeightManager);
      if(l1PreFiringWeightReader) evtWeightRecorder.record_l1PrefireWeight(l1PreFiringWeightReader);
      lheInfoReader->read();
      evtWeightRecorder.record_lheScaleWeight(lheInfoReader);
      evtWeightRecorder.record_puWeight(&eventInfo);
      evtWeightRecorder.record_nom_tH_weight(&eventInfo);
      evtWeightRecorder.record_lumiScale(lumiScale);

      genEvtHistManager_beforeCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(
          eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift)
        );
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, triggerWhiteList, eventInfo, isMC);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu, triggerWhiteList, eventInfo, isMC);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu, triggerWhiteList, eventInfo, isMC);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ) {
      continue;
    }
    
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 1e1mu, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_1e1mu) ) {
        continue;
      }
      if ( selTrigger_1mu && isTriggered_1e1mu ) {
        continue;
      }
    }
    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift));

    if ( (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
         (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
         (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ) {
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      tightElectronSelector.enable_offline_e_trigger_cuts();
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    const std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    const std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    const std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons);

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    const std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    const std::vector<const RecoElectron*> preselElectronsUncleaned = preselElectronSelector(electron_ptrs, isHigherConePt);
    const std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    const std::vector<const RecoElectron*> selElectrons = tightElectronSelector(preselElectrons);

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
//--- split hadronic tau candidates into different collections,
//    depending on whether they are genuine hadronic taus, e->tau fakes, mu->tau fakes, or jet->tau fakes
    std::vector<const RecoHadTau*> preselHadTaus_genHadTau;
    std::vector<const RecoHadTau*> preselHadTaus_genElectron;
    std::vector<const RecoHadTau*> preselHadTaus_genMuon;
    std::vector<const RecoHadTau*> preselHadTaus_genJet;

    for ( std::vector<const RecoHadTau*>::const_iterator hadTau = preselHadTaus.begin();
          hadTau != preselHadTaus.end(); ++hadTau ) {
      if      ( (*hadTau)->genHadTau()                                                    ) preselHadTaus_genHadTau.push_back(*hadTau);   // generator level match to hadronic tau decay 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 11 ) preselHadTaus_genElectron.push_back(*hadTau); // generator level match to electron 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 13 ) preselHadTaus_genMuon.push_back(*hadTau);     // generator level match to muon
      else                                                                                  preselHadTaus_genJet.push_back(*hadTau);      // generator level match to jet (or pileup)
    }
    const std::vector<const RecoHadTau*> selHadTaus = tightHadTauSelector(preselHadTaus);
    const std::vector<const RecoHadTau*> selHadTaus_genHadTau = tightHadTauSelector(preselHadTaus_genHadTau);
    const std::vector<const RecoHadTau*> selHadTaus_genElectron = tightHadTauSelector(preselHadTaus_genElectron);
    const std::vector<const RecoHadTau*> selHadTaus_genMuon = tightHadTauSelector(preselHadTaus_genMuon);
    const std::vector<const RecoHadTau*> selHadTaus_genJet = tightHadTauSelector(preselHadTaus_genJet);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableMuons, fakeableElectrons) :
      jetCleaner       (jet_ptrs, fakeableMuons, fakeableElectrons)
    ;
    const std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    const std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    const std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if(isMC && redoGenMatching && ! fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToHadTauReader)   hadTauGenMatch = genMatchToHadTauReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }

//--- match reconstructed to generator level particles
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        muonGenMatcher.addGenLeptonMatchByIndex(preselMuons, muonGenMatch, GenParticleType::kGenMuon);
        muonGenMatcher.addGenHadTauMatch       (preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch          (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatchByIndex(preselElectrons, electronGenMatch, GenParticleType::kGenElectron);
        electronGenMatcher.addGenPhotonMatchByIndex(preselElectrons, electronGenMatch);
        electronGenMatcher.addGenHadTauMatch       (preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch          (preselElectrons, genJets);

        hadTauGenMatcher.addGenLeptonMatchByIndex(preselHadTaus, hadTauGenMatch, GenParticleType::kGenAnyLepton);
        hadTauGenMatcher.addGenHadTauMatch       (preselHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch          (preselHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch    (selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch    (selJets, genHadTaus);
        jetGenMatcher.addGenJetMatchByIndex(selJets, jetGenMatch);
      }
      else
      {
        muonGenMatcher.addGenLeptonMatch(preselMuons, genMuons);
        muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch   (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatch(preselElectrons, genElectrons);
        electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons);
        electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch   (preselElectrons, genJets);

        hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons);
        hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch   (preselHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets, genJets);
      }
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons);
    std::vector<const RecoLepton*> preselLeptonsUncleaned = mergeLeptonCollections(preselElectronsUncleaned, preselMuons, isHigherConePt);
    // require two leptons passing loose preselection criteria 
    if ( !(preselLeptons.size() >= 2) ) {
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons", evtWeightRecorder.get(central_or_shift));
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId());
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId());

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 2 &&                             selTrigger_1e                                       ) ||
           (preselElectrons.size() >= 1 && preselMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
           (                               preselMuons.size() >= 2 &&  selTrigger_1mu                                      )) ) {
      continue;
    } 
    cutFlowTable.update("presel lepton trigger match", evtWeightRecorder.get(central_or_shift));
    
//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const std::vector<const RecoLepton *> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

    if(isMC)
    {
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      dataToMCcorrectionInterface->setLeptons(
        preselLepton_lead_type, preselLepton_lead->pt(), preselLepton_lead->cone_pt(), preselLepton_lead->eta(),
        preselLepton_sublead_type, preselLepton_sublead->pt(), preselLepton_sublead->cone_pt(), preselLepton_sublead->eta()
      );

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria
      evtWeightRecorder.record_leptonTriggerEff(dataToMCcorrectionInterface);

      evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose());

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      evtWeightRecorder.record_leptonIDSF(dataToMCcorrectionInterface);
    }

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons);
    // require exactly two leptons passing tight selection criteria to avoid overlap with 3l category
    if ( !(selLeptons.size() == 2) ) {
      continue;
    }
    cutFlowTable.update("2 sel leptons", evtWeightRecorder.get(central_or_shift));

    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    const RecoLepton* selLepton_e = 0;
    const RecoLepton* selLepton_mu = 0;
    if      ( selLepton_lead->is_electron()    ) selLepton_e  = selLepton_lead;
    else if ( selLepton_lead->is_muon()        ) selLepton_mu = selLepton_lead;
    if      ( selLepton_sublead->is_electron() ) selLepton_e  = selLepton_sublead;
    else if ( selLepton_sublead->is_muon()     ) selLepton_mu = selLepton_sublead;
    if ( !(selLepton_e && selLepton_mu) ) {
      continue;
    }
    cutFlowTable.update("1 sel electron + 1 sel muon", evtWeightRecorder.get(central_or_shift));

    double m_ll = (selLepton_lead->p4() + selLepton_sublead->p4()).mass();
    double m_bb = -1.;
    if ( selJets.size() >= 2 ) {
      std::vector<const RecoJet*> selJets_sortedByBtag = selJets;
      std::sort(selJets_sortedByBtag.begin(), selJets_sortedByBtag.end(), isHigherCSV);
      assert(selJets_sortedByBtag.size() >= 2);
      m_bb = (selJets_sortedByBtag[0]->p4() + selJets_sortedByBtag[1]->p4()).mass();
    }
    double mT_e = ( selLepton_e ) ? comp_MT_met(selLepton_e, met.pt(), met.phi()) : -1.;
    double mT_mu = ( selLepton_e ) ? comp_MT_met(selLepton_mu, met.pt(), met.phi()) : -1.;

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((fakeableElectrons.size() >= 2 &&                               selTrigger_1e                                       ) ||
           (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
           (                                 fakeableMuons.size() >= 2 &&  selTrigger_1mu                                      )) ) {
      continue;
    } 
    cutFlowTable.update("fakeable lepton trigger match", evtWeightRecorder.get(central_or_shift));

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,    selTrigger_1e    },
        { hltPathsE::trigger_1mu,   selTrigger_1mu   },
        { hltPathsE::trigger_1e1mu, selTrigger_1e1mu },
      };
      if(! hltFilter(trigger_bits, fakeableLeptons, {}))
      {
        continue;
      }
    }
    cutFlowTable.update("HLT filter matching", evtWeightRecorder.get(central_or_shift));

    // apply requirement on jets (incl. b-tagged jets) 
    if ( !(selJets.size() >= 2) ) {
      continue;
    }
    cutFlowTable.update(">= 2 jets", evtWeightRecorder.get(central_or_shift));
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift));

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsUncleaned);
    if(failsLowMassVeto)
    {
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift));

    const double minPt_lead = 25.;
    const double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt() > minPt_lead && selLepton_sublead->pt() > minPt_sublead) ) {
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeightRecorder.get(central_or_shift));

    bool isCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
    if ( chargeSelection == kOS && isCharge_SS ) {
      continue;
    }
    if ( chargeSelection == kSS && isCharge_OS ) {
      continue;
    }
    cutFlowTable.update(Form("lepton-pair %s charge", chargeSelection_string.data()), evtWeightRecorder.get(central_or_shift));

    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      if ( met_LD < 30. ) {
        continue;
      }
    }
    cutFlowTable.update("met LD > 30 GeV", evtWeightRecorder.get(central_or_shift));

    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
        continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeightRecorder.get(central_or_shift));

//--- fill histograms with events passing final selection 
    const double evtWeight = evtWeightRecorder.get(central_or_shift);
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    selHadTauHistManager_genHadTau.fillHistograms(selHadTaus_genHadTau, evtWeight);
    selHadTauHistManager_genElectron.fillHistograms(selHadTaus_genElectron, evtWeight);
    selHadTauHistManager_genMuon.fillHistograms(selHadTaus_genMuon, evtWeight);
    selHadTauHistManager_genJet.fillHistograms(selHadTaus_genJet, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met, mht_p4, met_LD, evtWeight);
    selMEtFilterHistManager.fillHistograms(metFilters, evtWeight);
    selEvtHistManager.fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
      m_ll, m_bb, mT_e, mT_mu, 
      evtWeight);
    selEvtYieldHistManager.fillHistograms(eventInfo, evtWeight);

//--- iterate over jets
    for ( std::vector<const RecoJet*>::const_iterator cleanedJet = cleanedJets.begin();
          cleanedJet != cleanedJets.end(); ++cleanedJet ) {
      if ( !((*cleanedJet)->pt() > jet_minPt && std::fabs((*cleanedJet)->eta()) > jet_minAbsEta  &&
             (*cleanedJet)->pt() < jet_maxPt && std::fabs((*cleanedJet)->eta()) < jet_maxAbsEta) ) continue;

      const RecoHadTau* preselHadTau_dRmatched = 0;
      double dRmin = 1.e+3;
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
            preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
        double dR = deltaR((*preselHadTau)->eta(), (*preselHadTau)->phi(), (*cleanedJet)->eta(), (*cleanedJet)->phi());
        if ( dR < dRmin || !preselHadTau_dRmatched ) {
          preselHadTau_dRmatched = (*preselHadTau);
          dRmin = dR;
        }
      }
      if ( !(preselHadTau_dRmatched && dRmin < 0.3) ) continue;

      std::vector<const RecoHadTau*> preselHadTau_ptrs;
      preselHadTau_ptrs.push_back(preselHadTau_dRmatched);
      std::vector<const RecoJet*> cleanedJets_wrtPreselHadTau = jetCleaner(selJets, preselHadTau_ptrs);
      std::vector<const RecoJet*> cleanedBJets_wrtPreselHadTau_loose = jetSelectorBtagLoose(cleanedJets_wrtPreselHadTau);
      std::vector<const RecoJet*> cleanedBJets_wrtPreselHadTau_medium = jetSelectorBtagMedium(cleanedJets_wrtPreselHadTau);    
      if ( !(cleanedBJets_wrtPreselHadTau_loose.size() >= 2 || cleanedBJets_wrtPreselHadTau_medium.size() >= 1) ) continue;

      for ( std::vector<denominatorHistManagers*>::iterator denominator = denominators.begin();
            denominator != denominators.end(); ++denominator ) {
        if ( !(*(*denominator)->fakeableHadTauSelector_)(*preselHadTau_dRmatched) ) continue;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
        double evtWeight_denominator = evtWeight;
        dataToMCcorrectionInterface->setHadTauSelection((*denominator)->fakeableHadTauSelector_->get());
        int preselHadTau_dRmatched_genPdgId = getHadTau_genPdgId(preselHadTau_dRmatched);
        dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt(), preselHadTau_dRmatched->eta());
        evtWeight_denominator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso(tauIDSF_option);

        (*denominator)->fillHistograms(**cleanedJet, *preselHadTau_dRmatched, evtWeight_denominator);
      }

      for ( std::vector<numeratorSelector_and_HistManagers*>::iterator numerator = numerators.begin();
            numerator != numerators.end(); ++numerator ) {
        if ( !(*(*numerator)->tightHadTauSelector_)(*preselHadTau_dRmatched) ) continue;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
        double evtWeight_numerator = evtWeight;
        dataToMCcorrectionInterface->setHadTauSelection((*numerator)->hadTauSelection_numerator_);
        int preselHadTau_dRmatched_genPdgId = getHadTau_genPdgId(preselHadTau_dRmatched);
        dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt(), preselHadTau_dRmatched->eta());
        evtWeight_numerator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso(tauIDSF_option);

        (*numerator)->fillHistograms(**cleanedJet, *preselHadTau_dRmatched, evtWeight_numerator);
      }
    }

    for ( std::vector<denominatorHistManagers*>::iterator denominator = denominators.begin();
          denominator != denominators.end(); ++denominator ) {
      int numHadTaus_denominator = 0;
      double evtWeight_denominator = evtWeight;
      dataToMCcorrectionInterface->setHadTauSelection((*denominator)->fakeableHadTauSelector_->get());
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
            preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
        if ( (*(*denominator)->fakeableHadTauSelector_)(**preselHadTau) ) ++numHadTaus_denominator;
        int preselHadTau_genPdgId = getHadTau_genPdgId(*preselHadTau);
        dataToMCcorrectionInterface->setHadTaus(preselHadTau_genPdgId, (*preselHadTau)->pt(), (*preselHadTau)->eta());
        evtWeight_denominator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso(tauIDSF_option);
      }
      (*denominator)->evtHistManager_->fillHistograms(selElectrons.size(), selMuons.size(), numHadTaus_denominator,
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        m_ll, m_bb, mT_e, mT_mu,
        evtWeight_denominator);
    }
    
    for ( std::vector<numeratorSelector_and_HistManagers*>::iterator numerator = numerators.begin();
          numerator != numerators.end(); ++numerator ) {
      int numHadTaus_numerator = 0;
      double evtWeight_numerator = evtWeight;
      dataToMCcorrectionInterface->setHadTauSelection((*numerator)->hadTauSelection_numerator_);
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
            preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
        if ( (*(*numerator)->tightHadTauSelector_)(**preselHadTau) ) ++numHadTaus_numerator;
        int preselHadTau_genPdgId = getHadTau_genPdgId(*preselHadTau);
        dataToMCcorrectionInterface->setHadTaus(preselHadTau_genPdgId, (*preselHadTau)->pt(), (*preselHadTau)->eta());
        evtWeight_numerator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso(tauIDSF_option);
      }
      (*numerator)->evtHistManager_->fillHistograms(selElectrons.size(), selMuons.size(), numHadTaus_numerator,
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        m_ll, m_bb, mT_e, mT_mu,
        evtWeight);
    }

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift));
      }
    }

    (*selEventsFile) << eventInfo.str() << '\n';

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
    if(isDEBUG)
    {
      std::cout << evtWeightRecorder << '\n';
    }
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in " << inputTree -> getProcessedFileCount() << " file(s) (out of " << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n";

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete dataToMCcorrectionInterface;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete metFilterReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete l1PreFiringWeightReader;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;

  clock.Show("analyze_jetToTauFakeRate");

  return EXIT_SUCCESS;
}

