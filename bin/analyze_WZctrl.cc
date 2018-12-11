
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
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
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
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
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_WZctrl.h" // EvtHistManager_WZctrl
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_3lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_3lepton };

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Produce datacard and control plots for WZctrl categories.
 */
int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_WZctrl>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_WZctrl");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_WZctrl")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_WZctrl");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  // single lepton triggers
  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e, "triggers_1e");
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu, "triggers_1mu");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  // double lepton triggers
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e, "triggers_2e");
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu, "triggers_1e1mu");
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu, "triggers_2mu");
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  // triple lepton triggers
  vstring triggerNames_3e = cfg_analyze.getParameter<vstring>("triggers_3e");
  std::vector<hltPath*> triggers_3e = create_hltPaths(triggerNames_3e, "triggers_3e");
  bool use_triggers_3e = cfg_analyze.getParameter<bool>("use_triggers_3e");
  vstring triggerNames_2e1mu = cfg_analyze.getParameter<vstring>("triggers_2e1mu");
  std::vector<hltPath*> triggers_2e1mu = create_hltPaths(triggerNames_2e1mu, "triggers_2e1mu");
  bool use_triggers_2e1mu = cfg_analyze.getParameter<bool>("use_triggers_2e1mu");
  vstring triggerNames_1e2mu = cfg_analyze.getParameter<vstring>("triggers_1e2mu");
  std::vector<hltPath*> triggers_1e2mu = create_hltPaths(triggerNames_1e2mu, "triggers_1e2mu");
  bool use_triggers_1e2mu = cfg_analyze.getParameter<bool>("use_triggers_1e2mu");
  vstring triggerNames_3mu = cfg_analyze.getParameter<vstring>("triggers_3mu");
  std::vector<hltPath*> triggers_3mu = create_hltPaths(triggerNames_3mu, "triggers_3mu");
  bool use_triggers_3mu = cfg_analyze.getParameter<bool>("use_triggers_3mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_3e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3e");
  bool apply_offline_e_trigger_cuts_2e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e1mu");
  bool apply_offline_e_trigger_cuts_1e2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e2mu");
  bool apply_offline_e_trigger_cuts_3mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3mu");

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_3lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection_veto").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  int minNumJets = cfg_analyze.getParameter<int>("minNumJets");
  std::cout << "minNumJets = " << minNumJets << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tHq" || process_string == "tHW" ) ? true : false;
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  const bool useNonNominal = cfg_analyze.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet = useNonNominal || ! isMC;

  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const std::string syncNtuple_tree = syncNtuple_cfg.getParameter<std::string>("tree");
  const std::string syncNtuple_output = syncNtuple_cfg.getParameter<std::string>("output");
  const bool sync_requireGenMatching = syncNtuple_cfg.getParameter<bool>("requireGenMatching");
  const bool do_sync = ! syncNtuple_tree.empty() && ! syncNtuple_output.empty();

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  checkOptionValidity(central_or_shift, isMC);
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  const int hadTauPt_option            = getHadTauPt_option     (central_or_shift);
  const int lheScale_option            = getLHEscale_option     (central_or_shift);
  const int jetBtagSF_option           = getBTagWeight_option   (central_or_shift);
  const PUsys puSys_option             = getPUsys_option        (central_or_shift);

  const int met_option   = useNonNominal_jetmet ? kMEt_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option = useNonNominal_jetmet ? kJet_central_nonNominal : getJet_option(central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> jetToLeptonFakeRate_option = " << jetToLeptonFakeRate_option << "\n"
       " -> hadTauPt_option            = " << hadTauPt_option            << "\n"
       " -> lheScale_option            = " << lheScale_option            << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option           << "\n"
       " -> met_option                 = " << met_option                 << "\n"
       " -> jetPt_option               = " << jetPt_option               << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_WZctrl", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "3lepton"  ) applyFakeRateWeights = kFR_3lepton;
  else throw cms::Exception("analyze_WZctrl")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3lepton) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  edm::ParameterSet cfg_EvtYieldHistManager = cfg_analyze.getParameter<edm::ParameterSet>("cfgEvtYieldHistManager");

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- prepare sync Ntuple
  SyncNtupleManager * snm = nullptr;
  if(do_sync)
  {
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
    snm->initializeBranches();
    snm->initializeHLTBranches({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu,
                                 triggers_1e1mu, triggers_1e2mu, triggers_2e1mu,
                                 triggers_3e, triggers_3mu });
  }

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, false);
  EventInfoReader eventInfoReader(&eventInfo, puSys_option);
  inputTree -> registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu, triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu });
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight hadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) hadTauSelector.set(hadTauSelection_part2);
  hadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  hadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenPhotonReader* genPhotonReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if ( !readGenObjects ) {
      if ( branchName_genLeptons != "" ) {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree -> registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree -> registerReader(genHadTauReader);
      }
      if ( branchName_genPhotons != "" ) {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree -> registerReader(genPhotonReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss_1tau category of ttH multilepton analysis
  std::string mvaFileName_2lss_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttV;
  mvaInputVariables_2lss_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttV.push_back("MT_met_lep1");
  mvaInputVariables_2lss_ttV.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[1]]");
  TMVAInterface mva_2lss_ttV(mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttbar;
  mvaInputVariables_2lss_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttbar.push_back("min(met_pt,400)");
  mvaInputVariables_2lss_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_ttbar.push_back("MT_met_lep1");
  TMVAInterface mva_2lss_ttbar(mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_2lss = get_mvaInputVariables(mvaInputVariables_2lss_ttV, mvaInputVariables_2lss_ttbar);

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 3l category of ttH multilepton analysis
  std::string mvaFileName_3l_ttV = "tthAnalysis/HiggsToTauTau/data/3l_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_3l_ttV;
  mvaInputVariables_3l_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_3l_ttV.push_back("MT_met_lep1");
  mvaInputVariables_3l_ttV.push_back("nJet25_Recl");
  mvaInputVariables_3l_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_3l_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_3l_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  mvaInputVariables_3l_ttV.push_back("LepGood_conePt[iF_Recl[2]]");
  TMVAInterface mva_3l_ttV(mvaFileName_3l_ttV, mvaInputVariables_3l_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_3l_ttbar = "tthAnalysis/HiggsToTauTau/data/3l_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_3l_ttbar;
  mvaInputVariables_3l_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_3l_ttbar.push_back("MT_met_lep1");
  mvaInputVariables_3l_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_3l_ttbar.push_back("mhtJet25_Recl");
  mvaInputVariables_3l_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_3l_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_3l_ttbar.push_back("mindr_lep2_jet");
  TMVAInterface mva_3l_ttbar(mvaFileName_3l_ttbar, mvaInputVariables_3l_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_3l = get_mvaInputVariables(mvaInputVariables_3l_ttV, mvaInputVariables_3l_ttbar);
  std::map<std::string, double> mvaInputs_3l;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
   struct preselHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    JetHistManager* jets_;
    JetHistManager* BJets_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    EvtHistManager_WZctrl* evt_;
    EvtYieldHistManager* evtYield_;
  };
  std::map<int, preselHistManagerType*> preselHistManagers;
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    MVAInputVarHistManager* mvaInputVariables_2lss_;
    MVAInputVarHistManager* mvaInputVariables_3l_;
    EvtHistManager_WZctrl* evt_;
    std::map<std::string, EvtHistManager_WZctrl*> evt_in_decayModes_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };
  std::map<int, selHistManagerType*> selHistManagers;

  for ( std::vector<leptonGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
	leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {

    std::string process_and_genMatch = process_string;
    if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;

    int idxLepton = leptonGenMatch_definition->idx_;

    preselHistManagerType* preselHistManager = new preselHistManagerType();
    preselHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/electrons", histogramDir.data()), central_or_shift));
    preselHistManager->electrons_->bookHistograms(fs);
    preselHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/muons", histogramDir.data()), central_or_shift));
    preselHistManager->muons_->bookHistograms(fs);
    preselHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/hadTaus", histogramDir.data()), central_or_shift));
    preselHistManager->hadTaus_->bookHistograms(fs);
    preselHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/jets", histogramDir.data()), central_or_shift));
    preselHistManager->jets_->bookHistograms(fs);
    preselHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/BJets_loose", histogramDir.data()), central_or_shift));
    preselHistManager->BJets_loose_->bookHistograms(fs);
    preselHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/BJets_medium", histogramDir.data()), central_or_shift));
    preselHistManager->BJets_medium_->bookHistograms(fs);
    preselHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/met", histogramDir.data()), central_or_shift));
    preselHistManager->met_->bookHistograms(fs);
    preselHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/metFilters", histogramDir.data()), central_or_shift));
    preselHistManager->metFilters_->bookHistograms(fs);
    preselHistManager->evt_ = new EvtHistManager_WZctrl(makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/evt", histogramDir.data()), era_string, central_or_shift));
    preselHistManager->evt_->bookHistograms(fs);
    edm::ParameterSet cfg_EvtYieldHistManager_presel = makeHistManager_cfg(process_and_genMatch,
      Form("%s/presel/evtYield", histogramDir.data()), central_or_shift);
    cfg_EvtYieldHistManager_presel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
    cfg_EvtYieldHistManager_presel.addParameter<bool>("isMC", isMC);
    preselHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_presel);
    preselHistManager->evtYield_->bookHistograms(fs);
    preselHistManagers[idxLepton] = preselHistManager;

    selHistManagerType* selHistManager = new selHistManagerType();
    selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
    selHistManager->electrons_->bookHistograms(fs);
    selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/muons", histogramDir.data()), central_or_shift));
    selHistManager->muons_->bookHistograms(fs);
    selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
    selHistManager->hadTaus_->bookHistograms(fs);
    selHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/jets", histogramDir.data()), central_or_shift));
    selHistManager->jets_->bookHistograms(fs);
    selHistManager->leadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/leadJet", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadJet_->bookHistograms(fs);
    selHistManager->subleadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/subleadJet", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadJet_->bookHistograms(fs);
    selHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/BJets_loose", histogramDir.data()), central_or_shift));
    selHistManager->BJets_loose_->bookHistograms(fs);
    selHistManager->leadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/leadBJet_loose", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadBJet_loose_->bookHistograms(fs);
    selHistManager->subleadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/subleadBJet_loose", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadBJet_loose_->bookHistograms(fs);
    selHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/BJets_medium", histogramDir.data()), central_or_shift));
    selHistManager->BJets_medium_->bookHistograms(fs);
    selHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/met", histogramDir.data()), central_or_shift));
    selHistManager->met_->bookHistograms(fs);
    selHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/metFilters", histogramDir.data()), central_or_shift));
    selHistManager->metFilters_->bookHistograms(fs);
    selHistManager->mvaInputVariables_2lss_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/mvaInputs_2lss", histogramDir.data()), central_or_shift));
    selHistManager->mvaInputVariables_2lss_->bookHistograms(fs, mvaInputVariables_2lss);
    selHistManager->mvaInputVariables_3l_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/mvaInputs_3l", histogramDir.data()), central_or_shift));
    selHistManager->mvaInputVariables_3l_->bookHistograms(fs, mvaInputVariables_3l);
    selHistManager->evt_ = new EvtHistManager_WZctrl(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
    selHistManager->evt_->bookHistograms(fs);
    const vstring decayModes_evt = eventInfo.getDecayModes();
    if ( isSignal ) {
      for ( const std::string & decayMode_evt: decayModes_evt ) {
	std::string decayMode_and_genMatch = decayMode_evt;
	if ( apply_leptonGenMatching ) decayMode_and_genMatch += leptonGenMatch_definition->name_;

	selHistManager->evt_in_decayModes_[decayMode_evt] = new EvtHistManager_WZctrl(makeHistManager_cfg(decayMode_and_genMatch,
          Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
	selHistManager->evt_in_decayModes_[decayMode_evt]->bookHistograms(fs);
      }
    }
    edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/evtYield", histogramDir.data()), central_or_shift);
    cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
    cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
    selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
    selHistManager->evtYield_->bookHistograms(fs);
    selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
      Form("%s/sel/weights", histogramDir.data()), central_or_shift));
    selHistManager->weights_->bookHistograms(fs, { "genWeight", "pileupWeight", "triggerWeight", "data_to_MC_correction", "fakeRate" });
    selHistManagers[idxLepton] = selHistManager;
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string,
      Form("%s/unbiased/genEvt", histogramDir.data()), era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string,
      Form("%s/sel/genEvt", histogramDir.data()), era_string, central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string,
      Form("%s/sel/lheInfo", histogramDir.data()), era_string, central_or_shift));
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
  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection");

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

    double evtWeight_inclusive = 1.;
    if(isMC)
    {
      if(apply_genWeight)    evtWeight_inclusive *= boost::math::sign(eventInfo.genWeight);
      if(isMC_tH)            evtWeight_inclusive *= eventInfo.genWeight_tH;
      if(eventWeightManager) evtWeight_inclusive *= eventWeightManager->getWeight();
      lheInfoReader->read();
      evtWeight_inclusive *= lheInfoReader->getWeight_scale(lheScale_option);
      evtWeight_inclusive *= eventInfo.pileupWeight;
      evtWeight_inclusive *= lumiScale;
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, isDEBUG);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu, isDEBUG);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e, isDEBUG);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu, isDEBUG);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu, isDEBUG);
    bool isTriggered_3e = hltPaths_isTriggered(triggers_3e, isDEBUG);
    bool isTriggered_2e1mu = hltPaths_isTriggered(triggers_2e1mu, isDEBUG);
    bool isTriggered_1e2mu = hltPaths_isTriggered(triggers_1e2mu, isDEBUG);
    bool isTriggered_3mu = hltPaths_isTriggered(triggers_3mu, isDEBUG);
    if ( isDEBUG ) {
      std::cout << "isTriggered:"
		<< " 1e = " << isTriggered_1e << ","
		<< " 1mu = " << isTriggered_1mu << ","
		<< " 2e = " << isTriggered_2e << ","
		<< " 1e1mu = " << isTriggered_1e1mu << ","
		<< " 2mu = " << isTriggered_2mu << ","
		<< " 3e = " << isTriggered_3e << ","
		<< " 2e1mu = " << isTriggered_2e1mu << ","
		<< " 1e2mu = " << isTriggered_1e2mu << ","
		<< " 3mu = " << isTriggered_3mu << std::endl;
    }

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_3e = use_triggers_3e && isTriggered_3e;
    bool selTrigger_2e1mu = use_triggers_2e1mu && isTriggered_2e1mu;
    bool selTrigger_1e2mu = use_triggers_1e2mu && isTriggered_1e2mu;
    bool selTrigger_3mu = use_triggers_3mu && isTriggered_3mu;
    if ( !(selTrigger_1e || selTrigger_1mu   ||
	   selTrigger_2e || selTrigger_1e1mu || selTrigger_2mu   ||
	   selTrigger_3e || selTrigger_2e1mu || selTrigger_1e2mu || selTrigger_3mu) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	std::cout << " (selTrigger_3mu = " << selTrigger_3mu
		  << ", selTrigger_1e2mu = " << selTrigger_1e2mu
		  << ", selTrigger_2e1mu = " << selTrigger_2e1mu
		  << ", selTrigger_3e = " << selTrigger_3e
		  << ", selTrigger_2mu = " << selTrigger_2mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2e = " << selTrigger_2e
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }

//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the triggers are ranked by primary dataset (PD).
//    The ranking of the PDs is as follows: DoubleMuon, MuonEG, DoubleEG, SingleMuon, SingleElectron
// CV: see https://cmssdt.cern.ch/lxr/source/HLTrigger/Configuration/python/HLT_GRun_cff.py?v=CMSSW_8_0_24 for association of triggers paths to PD
//     this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC && !isDEBUG ) {

      //bool isTriggered_SingleElectron = isTriggered_1e;
      bool isTriggered_SingleMuon = isTriggered_1mu;
      bool isTriggered_DoubleEG = isTriggered_2e || isTriggered_3e;
      bool isTriggered_DoubleMuon = isTriggered_2mu || isTriggered_3mu;
      bool isTriggered_MuonEG = isTriggered_1e1mu || isTriggered_2e1mu || isTriggered_1e2mu;

      bool selTrigger_SingleElectron = selTrigger_1e;
      bool selTrigger_SingleMuon = selTrigger_1mu;
      bool selTrigger_DoubleEG = selTrigger_2e || selTrigger_3e;
      //bool selTrigger_DoubleMuon = selTrigger_2mu || selTrigger_3mu;
      bool selTrigger_MuonEG = selTrigger_1e1mu || selTrigger_2e1mu || selTrigger_1e2mu;
      if ( selTrigger_SingleElectron && (isTriggered_DoubleEG || isTriggered_SingleMuon || isTriggered_DoubleMuon || isTriggered_MuonEG) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
		    << ", isTriggered_DoubleEG = " << isTriggered_DoubleEG
		    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon
		    << ", isTriggered_DoubleMuon = " << isTriggered_DoubleMuon
		    << ", isTriggered_MuonEG = " << isTriggered_MuonEG << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_DoubleEG && (isTriggered_DoubleMuon || isTriggered_MuonEG) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_DoubleEG = " << selTrigger_DoubleEG
		    << ", isTriggered_DoubleMuon = " << isTriggered_DoubleMuon
		    << ", isTriggered_MuonEG = " << isTriggered_MuonEG << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_SingleMuon && (isTriggered_DoubleEG || isTriggered_DoubleMuon || isTriggered_MuonEG) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_SingleMuon = " << selTrigger_SingleMuon
		    << ", isTriggered_DoubleEG = " << isTriggered_DoubleEG
		    << ", isTriggered_DoubleMuon = " << isTriggered_DoubleMuon
		    << ", isTriggered_MuonEG = " << isTriggered_MuonEG << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_MuonEG && isTriggered_DoubleMuon ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_MuonEG = " << selTrigger_MuonEG
		    << ", isTriggered_DoubleMuon = " << isTriggered_DoubleMuon << ")" << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("trigger");

    if ( (selTrigger_3mu   && !apply_offline_e_trigger_cuts_3mu)   ||
	 (selTrigger_2e1mu && !apply_offline_e_trigger_cuts_2e1mu) ||
	 (selTrigger_1e2mu && !apply_offline_e_trigger_cuts_1e2mu) ||
	 (selTrigger_3e    && !apply_offline_e_trigger_cuts_3e)    ||
	 (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)   ||
	 (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
	 (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
	 (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
	 (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ) {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
      tightElectronSelector.enable_offline_e_trigger_cuts();
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons, isHigherConePt);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons, isHigherConePt);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(fakeableMuons, isHigherConePt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselMuons",   preselMuons);
      printCollection("fakeableMuons", fakeableMuons);
      printCollection("tightMuons",    tightMuons);
    }

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons, isHigherConePt);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons, isHigherConePt);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(fakeableElectrons, isHigherConePt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselElectrons",   preselElectrons);
      printCollection("fakeableElectrons", fakeableElectrons);
      printCollection("tightElectrons",    tightElectrons);
    }

    std::vector<const RecoLepton*> preselLeptonsFull = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    std::vector<const RecoLepton*> fakeableLeptonsFull = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    std::vector<const RecoLepton*> tightLeptonsFull = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 3);
    std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 3);
    std::vector<const RecoLepton*> tightLeptons = getIntersection(fakeableLeptons, tightLeptonsFull, isHigherConePt);

    std::vector<const RecoLepton*> selLeptons;
    std::vector<const RecoMuon*> selMuons;
    std::vector<const RecoElectron*> selElectrons;
    if(electronSelection == muonSelection)
    {
      // for SR, flip region and fake CR
      // doesn't matter if we supply electronSelection or muonSelection here
      selLeptons = selectObjects(muonSelection, preselLeptons, fakeableLeptons, tightLeptons);
      selMuons = getIntersection(preselMuons, selLeptons, isHigherConePt);
      selElectrons = getIntersection(preselElectrons, selLeptons, isHigherConePt);
    }
    else
    {
      // for MC closure
      // make sure that neither electron nor muon selections are loose
      assert(electronSelection != kLoose && muonSelection != kLoose);
      selMuons = selectObjects(muonSelection, preselMuons, fakeableMuons, tightMuons);
      selElectrons = selectObjects(electronSelection, preselElectrons, fakeableElectrons, tightElectrons);
      std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
      selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);
    }

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus, isHigherPt);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);

    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("selMuons", selMuons);
      printCollection("selElectrons", selElectrons);
      printCollection("selLeptons", selLeptons);
      printCollection("selHadTaus", selHadTaus);
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableLeptonsFull, fakeableHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if ( isMC && redoGenMatching && !fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    if ( !(preselLeptonsFull.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS preselLeptons selection." << std::endl;
  printCollection("preselLeptons", preselLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update(">= 3 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptonsFull[0];
    const RecoLepton* preselLepton_sublead = preselLeptonsFull[1];
    const RecoLepton* preselLepton_third = preselLeptonsFull[2];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead, preselLepton_third);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined3);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 3 &&                            (selTrigger_3e    || selTrigger_2e  || selTrigger_1e                                      )) ||
	   (preselElectrons.size() >= 2 && preselMuons.size() >= 1 && (selTrigger_2e1mu || selTrigger_2e  || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (preselElectrons.size() >= 1 && preselMuons.size() >= 2 && (selTrigger_1e2mu || selTrigger_2mu || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                               preselMuons.size() >= 3 && (selTrigger_3mu   || selTrigger_2mu || selTrigger_1mu                                     ))) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection for given preselLepton multiplicity." << std::endl;
	std::cout << " (#preselElectrons = " << preselElectrons.size()
		  << ", #preselMuons = " << preselMuons.size()
		  << ", selTrigger_3mu = " << selTrigger_3mu
		  << ", selTrigger_1e2mu = " << selTrigger_1e2mu
		  << ", selTrigger_2e1mu = " << selTrigger_2e1mu
		  << ", selTrigger_3e = " << selTrigger_3e
		  << ", selTrigger_2mu = " << selTrigger_2mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2e = " << selTrigger_2e
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("presel lepton trigger match");

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !((int)selJets.size() >= minNumJets) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selJets selection." << std::endl;
	printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (1)", minNumJets));
    if ( !(selBJets_medium.size() == 0 && selBJets_loose.size() < 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS selBJets selection." << std::endl;
	printCollection("selJets", selJets);
	printCollection("selBJets_loose", selBJets_loose);
	printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update("No medium b-jets (1)");

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, {}, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselLepton_genMatch];
    assert(preselHistManager != 0);
    preselHistManager->electrons_->fillHistograms(preselElectrons, 1.);
    preselHistManager->muons_->fillHistograms(preselMuons, 1.);
    preselHistManager->hadTaus_->fillHistograms(selHadTaus, 1.);
    preselHistManager->jets_->fillHistograms(selJets, 1.);
    preselHistManager->BJets_loose_->fillHistograms(selBJets_loose, 1.);
    preselHistManager->BJets_medium_->fillHistograms(selBJets_medium, 1.);
    preselHistManager->met_->fillHistograms(met, mht_p4, met_LD, 1.);
    preselHistManager->metFilters_->fillHistograms(metFilters, 1.);
    preselHistManager->evt_->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(),
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1., -1., -1., -1., -1., -1.,
      -1., -1., 0., 1.);
    preselHistManager->evtYield_->fillHistograms(eventInfo, 1.);

//--- apply final event selection
    // require exactly two leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
	printCollection("selLeptons", selLeptons);
	//printCollection("preselLeptons", preselLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 3 sel leptons", 1.);
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const RecoLepton* selLepton_third = selLeptons[2];
    int selLepton_third_type = getLeptonType(selLepton_third->pdgId());
    const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead, selLepton_third);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined3);

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    double btagWeight = 1.;
    double triggerWeight = 1.;
    double leptonSF_weight = 1.;
    if ( isMC ) {
      evtWeight *= evtWeight_inclusive;
      btagWeight = get_BtagWeight(selJets);
      evtWeight *= btagWeight;
      if ( isDEBUG ) {
	std::cout << "lumiScale = " << lumiScale << std::endl;
	if ( apply_genWeight ) std::cout << "genWeight = " << boost::math::sign(eventInfo.genWeight) << std::endl;
	std::cout << "pileupWeight = " << eventInfo.pileupWeight << std::endl;
	std::cout << "btagWeight = " << btagWeight << std::endl;
      }
    }

    double weight_data_to_MC_correction = 1.;
    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
	selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta(),
        selLepton_third_type, selLepton_third->pt(), selLepton_third->eta());

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      if ( isDEBUG ) {
	std::cout << "sf_triggerEff = " << sf_triggerEff << std::endl;
      }
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

//--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria
      leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if ( electronSelection == kFakeable && muonSelection == kFakeable ) {
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( electronSelection >= kFakeable && muonSelection >= kFakeable ) {
        // apply loose-to-tight lepton ID SFs if either of the following is true:
        // 1) both electron and muon selections are tight -> corresponds to SR
        // 2) electron selection is relaxed to fakeable and muon selection is kept as tight -> corresponds to MC closure w/ relaxed e selection
        // 3) muon selection is relaxed to fakeable and electron selection is kept as tight -> corresponds to MC closure w/ relaxed mu selection
        // we allow (2) and (3) so that the MC closure regions would more compatible w/ the SR (1) in comparison
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();
      }
      weight_data_to_MC_correction *= leptonSF_weight;

      evtWeight *= weight_data_to_MC_correction;
    }

    double weight_fakeRate = 1.;
    if ( applyFakeRateWeights == kFR_3lepton ) {
      double prob_fake_lepton_lead = 1.;
      if      ( std::abs(selLepton_lead->pdgId()) == 11 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->cone_pt(), selLepton_lead->absEta());
      else if ( std::abs(selLepton_lead->pdgId()) == 13 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->cone_pt(), selLepton_lead->absEta());
      else assert(0);
      bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
      double prob_fake_lepton_sublead = 1.;
      if      ( std::abs(selLepton_sublead->pdgId()) == 11 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
      else if ( std::abs(selLepton_sublead->pdgId()) == 13 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
      else assert(0);
      bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
      double prob_fake_lepton_third = 1.;
      if      ( std::abs(selLepton_third->pdgId()) == 11 ) prob_fake_lepton_third = leptonFakeRateInterface->getWeight_e(selLepton_third->cone_pt(), selLepton_third->absEta());
      else if ( std::abs(selLepton_third->pdgId()) == 13 ) prob_fake_lepton_third = leptonFakeRateInterface->getWeight_mu(selLepton_third->cone_pt(), selLepton_third->absEta());
      else assert(0);
      bool passesTight_lepton_third = isMatched(*selLepton_third, tightElectrons) || isMatched(*selLepton_third, tightMuons);
      weight_fakeRate = getWeight_3L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
	prob_fake_lepton_sublead, passesTight_lepton_sublead,
	prob_fake_lepton_third, passesTight_lepton_third);
      if ( isDEBUG ) {
	std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
      }
      evtWeight *= weight_fakeRate;
    }
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }

    // require that trigger paths match event category (with event category based on fakeableLeptons)
    if ( !((fakeableElectrons.size() >= 3 &&                              (selTrigger_3e    || selTrigger_2e  || selTrigger_1e                                      )) ||
	   (fakeableElectrons.size() >= 2 && fakeableMuons.size() >= 1 && (selTrigger_2e1mu || selTrigger_2e  || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 2 && (selTrigger_1e2mu || selTrigger_2mu || selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                                 fakeableMuons.size() >= 3 && (selTrigger_3mu   || selTrigger_2mu || selTrigger_1mu                                     ))) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection for given fakeableLepton multiplicity." << std::endl;
	std::cout << " (#fakeableElectrons = " << fakeableElectrons.size()
		  << ", #fakeableMuons = " << fakeableMuons.size()
		  << ", selTrigger_3mu = " << selTrigger_3mu
		  << ", selTrigger_1e2mu = " << selTrigger_1e2mu
		  << ", selTrigger_2e1mu = " << selTrigger_2e1mu
		  << ", selTrigger_3e = " << selTrigger_3e
		  << ", selTrigger_2mu = " << selTrigger_2mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2e = " << selTrigger_2e
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("fakeable lepton trigger match", evtWeight);

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,    selTrigger_1e    },
        { hltPathsE::trigger_1mu,   selTrigger_1mu   },
        { hltPathsE::trigger_2e,    selTrigger_2e    },
        { hltPathsE::trigger_2mu,   selTrigger_2mu   },
        { hltPathsE::trigger_1e1mu, selTrigger_1e1mu },
        { hltPathsE::trigger_1e2mu, selTrigger_1e2mu },
        { hltPathsE::trigger_2e1mu, selTrigger_2e1mu },
        { hltPathsE::trigger_3e,    selTrigger_3e    },
        { hltPathsE::trigger_3mu,   selTrigger_3mu   },
      };
      if(! hltFilter(trigger_bits, fakeableLeptons, {}))
      {
        if(run_lumi_eventSelector || isDEBUG)
        {
          std::cout << "event " << eventInfo.str() << " FAILS HLT filter matching\n";
        }
        continue;
      }
    }
    cutFlowTable.update("HLT filter matching", evtWeight);

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !((int)selJets.size() >= minNumJets) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selJets selection." << std::endl;
	printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (2)", minNumJets), evtWeight);
    if ( !(selBJets_medium.size() == 0)) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS selBJets selection." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("No medium b-jets (2)", evtWeight);

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
    lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
      lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
	double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	if ( mass < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);

    const double minPt_lead = 25.;
    const double minPt_sublead = 15.;
    double minPt_third = -1.;
    switch(era)
    {
      case kEra_2016: minPt_third = 15.; break; // AN2017_029_v5:371
      case kEra_2017: minPt_third = 10.; break;
      case kEra_2018: throw cmsException("analyze_3l", __LINE__) << "Implement me!";
      default:        throw cmsException("analyze_3l", __LINE__) << "Invalid era = " << era;
    }
    assert(minPt_third > 0.);
    // CV: according to Giovanni, the pT cuts should be applied on cone_pt
    //    (combined efficiency of single lepton, double lepton, and triple lepton triggers assumed to be high,
    //     even if one or two leptons and fakes and hence cone_pt may be significantly smaller than lepton_pt,
    //     on which pT cuts are applied on trigger level)
    if ( !(selLepton_lead->cone_pt() > minPt_lead && selLepton_sublead->cone_pt() > minPt_sublead && selLepton_third->cone_pt() > minPt_third) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead
		  << ", third selLepton pT = " << selLepton_third->pt() << ", minPt_third = " << minPt_third << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV && third lepton pT > 15 GeV", evtWeight);

    int sumLeptonCharge = selLepton_lead->charge() + selLepton_sublead->charge() + selLepton_third->charge();
    if ( std::abs(sumLeptonCharge) > 1 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
		  << ", subleading selLepton charge = " << selLepton_sublead->charge()
		  << ", third selLepton charge = " << selLepton_third->charge() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton charge", evtWeight);

    bool isSFOS = false;
    double massSFOS = -1.;
    const RecoLepton* selLepton_extra = 0;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
    lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
      lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
	if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // pair of same flavor leptons of opposite charge
	  isSFOS = true;
	  double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	  if ( std::fabs(mass - z_mass) < std::fabs(massSFOS - z_mass) ) {
	    massSFOS = mass;
	    if      ( !((*lepton1) == selLepton_lead    || (*lepton2) == selLepton_lead)    ) selLepton_extra = selLepton_lead;
	    else if ( !((*lepton1) == selLepton_sublead || (*lepton2) == selLepton_sublead) ) selLepton_extra = selLepton_sublead;
	    else if ( !((*lepton1) == selLepton_third   || (*lepton2) == selLepton_third)   ) selLepton_extra = selLepton_third;
	  }
	}
      }
    }

    bool passesZbosonMassCut = isSFOS && std::fabs(massSFOS - z_mass) < z_window;
    if ( !passesZbosonMassCut ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS Z-boson mass cut. isSFOS = "<< isSFOS << ";  max(std::fabs(massSFOS - z_mass)) = " << std::fabs(massSFOS - z_mass) << "; z_mass = " << z_mass << "; z_window = " << z_window << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass cut", evtWeight);

    double met_LD_cut = 0.;
    if      ( selJets.size() >= 4 ) met_LD_cut = -1.; // MET LD cut not applied
    else if ( isSFOS              ) met_LD_cut = 45.;
    else                            met_LD_cut = 30.;
    if ( met_LD_cut > 0 && met_LD < met_LD_cut ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS MET LD selection." << std::endl;
	std::cout << " (met_LD = " << met_LD << ", met_LD_cut = " << met_LD_cut << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("met LD", evtWeight);

    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event " << eventInfo.str() << " FAILS MEt filters." << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeight);

    if ( selHadTaus.size() > 0 ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selHadTaus veto." << std::endl;
  //printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update("sel tau veto");

    bool failsSignalRegionVeto = false;
    if ( isMCClosure_e || isMCClosure_m ) {
      bool applySignalRegionVeto = (isMCClosure_e && countFakeElectrons(selLeptons) >= 1) || (isMCClosure_m && countFakeMuons(selLeptons) >= 1);
      if ( applySignalRegionVeto && tightLeptons.size() >= 3 ) failsSignalRegionVeto = true;
    } else if ( electronSelection == kFakeable || muonSelection == kFakeable ) {
      if ( tightLeptons.size() >= 3 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
	             "# tight leptons = " << tightLeptons.size() << " >= 3\n"
        ;
	printCollection("tightLeptons", tightLeptons);
      }
      continue; // CV: avoid overlap with signal region
    }
    cutFlowTable.update("signal region veto", evtWeight);

    double mT = ( selLepton_extra ) ? comp_MT_met_lep1(*selLepton_extra, met.pt(), met.phi()) : -1.;

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss category of ttH multilepton analysis
    const int nJet25_Recl = comp_n_jet25_recl(selJets);

    const double mindr_lep1_jet = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    const double mindr_lep2_jet = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    const double max_lep_eta    = std::max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    const double mT_lep1        = comp_MT_met_lep1(*selLepton_lead,    met.pt(), met.phi());
    const double MT_met_lep1    = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
    const double avg_dr_jet     = comp_avg_dr_jet(selJets);
    const double lep1_conePt    = comp_lep1_conePt(*selLepton_lead);
    const double lep2_conePt    = comp_lep2_conePt(*selLepton_sublead);
    const double lep3_conePt    = selLepton_third ? comp_lep3_conePt(*selLepton_third) : -1.;
    const double minMET400      = std::min(met.pt(), 400.);

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss_1tau category of ttH multilepton analysis
    std::map<std::string, double> mvaInputs_2lss = {
      { "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", max_lep_eta                   },
      { "MT_met_lep1",                                                    mT_lep1                       },
      { "nJet25_Recl",                                                    nJet25_Recl                   },
      { "mindr_lep1_jet",                                                 std::min(10., mindr_lep1_jet) },
      { "mindr_lep2_jet",                                                 std::min(10., mindr_lep2_jet) },
      { "LepGood_conePt[iF_Recl[0]]",                                     lep1_conePt                   },
      { "LepGood_conePt[iF_Recl[1]]",                                     lep2_conePt                   },
      { "min(met_pt,400)",                                                minMET400                     },
      { "avg_dr_jet",                                                     avg_dr_jet                    },
    };

    check_mvaInputs(mvaInputs_2lss, eventInfo);

    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs_2lss);
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs_2lss);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 () of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_2lss = -1;
    if(era == kEra_2016 || era == kEra_2017)
    {
      if      ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.4 ) mvaDiscr_2lss = 7.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.1 ) mvaDiscr_2lss = 6.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV <= +0.1 ) mvaDiscr_2lss = 5.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV >  +0.3 ) mvaDiscr_2lss = 4.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV <= +0.3 ) mvaDiscr_2lss = 3.;
      else if ( mvaOutput_2lss_ttbar > -0.2                               ) mvaDiscr_2lss = 2.;
      else                                                                  mvaDiscr_2lss = 1.;
    } else assert(0);

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 3l category of ttH multilepton analysis
    double mvaOutput_3l_ttV = -1.;
    double mvaOutput_3l_ttbar = -1.;
    if(selLepton_third)
    {
      mvaInputs_3l = std::map<std::string, double>({
        { "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", max_lep_eta    },
        { "MT_met_lep1",                                                    MT_met_lep1    },
        { "nJet25_Recl",                                                    nJet25_Recl    },
        { "mindr_lep1_jet",                                                 mindr_lep1_jet },
        { "mindr_lep2_jet",                                                 mindr_lep2_jet },
        { "LepGood_conePt[iF_Recl[0]]",                                     lep1_conePt    },
        { "LepGood_conePt[iF_Recl[2]]",                                     lep3_conePt    },
        { "avg_dr_jet",                                                     avg_dr_jet     },
        { "mhtJet25_Recl",                                                  mht_p4.pt()    },
      });
      check_mvaInputs(mvaInputs_3l, eventInfo);

      mvaOutput_3l_ttV = mva_3l_ttV(mvaInputs_3l);
      mvaOutput_3l_ttbar = mva_3l_ttbar(mvaInputs_3l);
    }

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 (10) of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_3l = -1;
    if(era == kEra_2016 || era == kEra_2017)
    {
      if      ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 5.;
      else if ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 4.;
      else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 3.;
      else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 2.;
      else                                                                mvaDiscr_3l = 1.;
    } else assert(0);

    selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch];
    assert(selHistManager != 0);
    selHistManager->electrons_->fillHistograms(selElectrons, evtWeight);
    selHistManager->muons_->fillHistograms(selMuons, evtWeight);
    selHistManager->hadTaus_->fillHistograms(selHadTaus, evtWeight);
    selHistManager->jets_->fillHistograms(selJets, evtWeight);
    selHistManager->leadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->subleadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->BJets_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->leadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->subleadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->BJets_medium_->fillHistograms(selBJets_medium, evtWeight);
    selHistManager->met_->fillHistograms(met, mht_p4, met_LD, evtWeight);
    selHistManager->metFilters_->fillHistograms(metFilters, evtWeight);
    selHistManager->mvaInputVariables_2lss_->fillHistograms(mvaInputs_2lss, evtWeight);
    selHistManager->mvaInputVariables_3l_->fillHistograms(mvaInputs_3l, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(), selMuons.size(), selHadTaus.size(),
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss,
      mvaOutput_3l_ttV, mvaOutput_3l_ttbar, mvaDiscr_3l,
      massSFOS, mT, sumLeptonCharge, evtWeight);
    if ( isSignal ) {
      const std::string decayModeStr = eventInfo.getDecayModeString();
      if(! decayModeStr.empty())
      {
        selHistManager->evt_in_decayModes_[decayModeStr]->fillHistograms(
          selElectrons.size(), selMuons.size(), selHadTaus.size(),
          selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
          mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss,
          mvaOutput_3l_ttV, mvaOutput_3l_ttbar, mvaDiscr_3l,
          massSFOS, mT, sumLeptonCharge, evtWeight);
      }
    }
    selHistManager->evtYield_->fillHistograms(eventInfo, evtWeight);
    selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    (*selEventsFile) << eventInfo.run << ":" << eventInfo.lumi << ":" << eventInfo.event << std::endl;

    if(snm)
    {
      const bool isGenMatched = isMC &&
        ((apply_leptonGenMatching && selLepton_genMatch.numGenMatchedLeptons_ == 3) || ! apply_leptonGenMatching)
      ;

      const double dr_leps        = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
      const double mT_lep2        = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
      const double max_dr_jet     = comp_max_dr_jet(selJets);
      const double mbb            = selBJets_medium.size() > 1 ?  (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1000;
      const double mbb_loose      = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1000;
      const double min_dr_lep_jet = std::min(mindr_lep1_jet, mindr_lep2_jet);
      const double mindr_lep3_jet = selLepton_third ? comp_mindr_lep3_jet(*selLepton_sublead, selJets) : -1.;

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(selJets);

      snm->read({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu,
                  triggers_1e1mu, triggers_1e2mu, triggers_2e1mu,
                  triggers_3e, triggers_3mu });
      snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size());

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);

      snm->read(mindr_lep1_jet,                         FloatVariableType::mindr_lep1_jet);
      snm->read(mindr_lep2_jet,                         FloatVariableType::mindr_lep2_jet);
      snm->read(mindr_lep3_jet,                         FloatVariableType::mindr_lep3_jet);
      // mindr_lep4_jet not filled

      // mindr_tau1_jet not filled
      // mindr_tau2_jet not filled

      snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
      // avr_dr_lep_tau not filled
      snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
      // max_dr_lep_tau not filled
      // min_dr_tau_jet not filled
      // min_dr_lep_tau not filled
      snm->read(min_dr_lep_jet,                         FloatVariableType::min_dr_lep_jet);

      snm->read(dr_leps,                                FloatVariableType::dr_leps);
      // dr_taus not filled

      // dr_lep_tau_ss not filled
      // dr_lep1_tau1 not filled
      // dr_lep1_tau2 not filled
      // dr_lep2_tau1 not filled
      // dr_lep3_tau1 not filled
      // dr_lep2_tau2 not filled

      snm->read(max_lep_eta,                            FloatVariableType::max_lep_eta);

      snm->read(mT_lep1,                                FloatVariableType::mT_met_lep1);
      snm->read(mT_lep2,                                FloatVariableType::mT_met_lep2);
      // mT_met_lep3 not filled
      // mT_met_lep4 not filled

      // mTauTauVis not filled
      // mvis_l1tau not filled
      // mvis_l2tau not filled

      snm->read(mbb,                                    FloatVariableType::mbb);
      snm->read(mbb_loose,                              FloatVariableType::mbb_loose);

      // cosThetaS_hadTau not filled
      // HTT not filled
      // HadTop_pt not filled
      // mvaOutput_Hj_tagger not filled

      // mvaOutput_plainKin_ttV not filled
      // mvaOutput_plainKin_tt not filled
      // mvaOutput_plainKin_1B_VT not filled
      // mvaOutput_HTT_SUM_VT not filled

      // mvaOutput_plainKin_SUM_VT not filled

      snm->read(mvaOutput_2lss_ttV,                     FloatVariableType::mvaOutput_2lss_ttV);
      snm->read(mvaOutput_2lss_ttbar,                   FloatVariableType::mvaOutput_2lss_tt);
      // mvaOutput_2lss_1tau_plainKin_tt not filled
      // mvaOutput_2lss_1tau_plainKin_ttV not filled
      // mvaOutput_2lss_1tau_plainKin_1B_M not filled
      // mvaOutput_2lss_1tau_plainKin_SUM_M not filled
      // mvaOutput_2lss_1tau_HTT_SUM_M not filled
      // mvaOutput_2lss_1tau_HTTMEM_SUM_M not filled

      snm->read(mvaOutput_3l_ttV,                       FloatVariableType::mvaOutput_3l_ttV);
      snm->read(mvaOutput_3l_ttbar,                     FloatVariableType::mvaOutput_3l_ttbar);
      // mvaOutput_plainKin_SUM_M not filled
      // mvaOutput_plainKin_1B_M not filled

      // weight_fakeRate not filled
      // triggerWeight not filled
      // leptonSF_weight not filled
      // tauSF_weight not filled
      snm->read(btagWeight,                             FloatVariableType::bTagSF_weight);
      snm->read(eventInfo.pileupWeight,                 FloatVariableType::PU_weight);
      snm->read(boost::math::sign(eventInfo.genWeight), FloatVariableType::MC_weight);

      // memOutput_ttH not filled
      // memOutput_ttZ not filled
      // memOutput_ttZ_Zll not filled
      // memOutput_tt not filled
      // memOutput_type not filled
      // memOutput_LR not filled

      snm->read(eventInfo.genWeight,                    FloatVariableType::genWeight);

      if((sync_requireGenMatching && isGenMatched) || ! sync_requireGenMatching)
      {
        snm->fill();
      }
      else
      {
        snm->reset();
      }
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  if(snm)
  {
    snm->write();
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete run_lumi_eventSelector;

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
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1e1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_3e);
  hltPaths_delete(triggers_2e1mu);
  hltPaths_delete(triggers_1e2mu);
  hltPaths_delete(triggers_3mu);

  delete inputTree;

  clock.Show("analyze_WZctrl");

  return EXIT_SUCCESS;
}
