
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
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss category
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
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorForward.h" // RecoJetSelectorForward
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_ttWctrl.h" // EvtHistManager_ttWctrl
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonChargeFlipGenMatch_definitions_2lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton };

/**
 * @brief Produce datacard and control plots for ttWctrl categories.
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

  std::cout << "<analyze_ttWctrl>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_ttWctrl");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_ttWctrl")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_ttWctrl");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tHq = process_string == "tHq";
  const bool isMC_tHW = process_string == "tHW";
  const bool isMC_tH = isMC_tHq || isMC_tHW;
  const bool isMC_VH = process_string == "VH";
  const bool isMC_HH = process_string == "HH";
  const bool isMC_signal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  const bool isSignal = isMC_signal || isMC_tH || isMC_VH;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS };
  std::string leptonChargeSelection_string = cfg_analyze.getParameter<std::string>("leptonChargeSelection");
  int leptonChargeSelection = -1;
  if      ( leptonChargeSelection_string == "OS" ) leptonChargeSelection = kOS;
  else if ( leptonChargeSelection_string == "SS" ) leptonChargeSelection = kSS;
  else throw cms::Exception("analyze_2lss")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonChargeFlipGenMatchEntry> leptonGenMatch_definitions = getLeptonChargeFlipGenMatch_definitions_2lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection_veto").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift_main = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::vector<std::string> central_or_shifts_local = cfg_analyze.getParameter<std::vector<std::string>>("central_or_shifts_local");
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_l1PreFireWeight = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  const bool useNonNominal = cfg_analyze.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet = useNonNominal || ! isMC;

  if(! central_or_shifts_local.empty())
  {
    assert(central_or_shift_main == "central");
    assert(std::find(central_or_shifts_local.cbegin(), central_or_shifts_local.cend(), "central") != central_or_shifts_local.cend());
  }
  else
  {
    central_or_shifts_local = { central_or_shift_main };
  }

  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const std::string syncNtuple_tree = syncNtuple_cfg.getParameter<std::string>("tree");
  const std::string syncNtuple_output = syncNtuple_cfg.getParameter<std::string>("output");
  const vstring syncNtuple_genMatch = syncNtuple_cfg.getParameter<vstring>("genMatch");
  const bool do_sync = ! syncNtuple_tree.empty() && ! syncNtuple_output.empty();

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift_main);
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  checkOptionValidity(central_or_shift_main, isMC);
  const int met_option      = useNonNominal_jetmet ? kJetMET_central_nonNominal : getMET_option(central_or_shift_main, isMC);
  const int jetPt_option    = useNonNominal_jetmet ? kJetMET_central_nonNominal : getJet_option(central_or_shift_main, isMC);
  const int hadTauPt_option = useNonNominal_jetmet ? kHadTauPt_uncorrected      : getHadTauPt_option(central_or_shift_main);

  std::cout
    << "central_or_shift = "    << central_or_shift_main << "\n"
       " -> hadTauPt_option = " << hadTauPt_option       << "\n"
       " -> met_option      = " << met_option            << "\n"
       " -> jetPt_option    = " << jetPt_option          << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_ttWctrl", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else throw cms::Exception("analyze_ttWctrl")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  std::cout << "Applying fake rate weights = " << applyFakeRateWeights_string << " (" << applyFakeRateWeights << ")\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
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

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

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
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree, SyncGenMatchCharge::kLepton);
    snm->initializeBranches();
    snm->initializeHLTBranches({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
  }

//--- declare event-level variables
  EventInfo eventInfo(isMC, isSignal, isMC_HH);
  const std::string default_cat_str = "default";
  std::vector<std::string> evt_cat_strs = { default_cat_str };
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isMC_signal) && ! tHweights.empty())
  {
    eventInfo.set_central_or_shift(central_or_shift_main);
    eventInfo.loadWeight_tH(tHweights);
    const std::vector<std::string> evt_cat_tH_strs = eventInfo.getWeight_tH_str();
    evt_cat_strs.insert(evt_cat_strs.end(), evt_cat_tH_strs.begin(), evt_cat_tH_strs.end());
  }
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  ObjectMultiplicity objectMultiplicity;
  ObjectMultiplicityReader objectMultiplicityReader(&objectMultiplicity);
  if(useObjectMultiplicity)
  {
    inputTree -> registerReader(&objectMultiplicityReader);
  }
  const int minLeptonSelection = std::min(electronSelection, muonSelection);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
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
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose looseHadTauSelector(era, -1, isDEBUG);
  looseHadTauSelector.set_if_looser(hadTauSelection_part2);
  RecoHadTauCollectionSelectorLoose hadTauSelector(era);
  hadTauSelector.set(hadTauSelection_part2);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics((central_or_shifts_local.size() > 1 || central_or_shift_main != "central") && isMC);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  const RecoJetCollectionSelectorForward jetSelectorForward(era, -1, isDEBUG);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

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
      inputTree -> registerReader(genLeptonReader);
      genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
      inputTree -> registerReader(genHadTauReader);
      genJetReader = new GenJetReader(branchName_genJets);
      inputTree -> registerReader(genJetReader);

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
    inputTree -> registerReader(lheInfoReader);
  }

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss category of ttH multilepton analysis
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

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
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
    std::map<std::string, EvtHistManager_ttWctrl*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_ttWctrl*>> evt_in_decayModes_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };

  std::map<std::string, GenEvtHistManager*> genEvtHistManager_beforeCuts;
  std::map<std::string, GenEvtHistManager*> genEvtHistManager_afterCuts;
  std::map<std::string, LHEInfoHistManager*> lheInfoHistManager;
  std::map<std::string, std::map<int, selHistManagerType*>> selHistManagers;
  for(const std::string & central_or_shift: central_or_shifts_local)
  {
    const bool skipBooking = central_or_shift != central_or_shift_main;
    for(const leptonChargeFlipGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
    {
      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition.name_;

      int idxLepton = leptonGenMatch_definition.idx_;

      selHistManagerType* selHistManager = new selHistManagerType();
      if(! skipBooking)
      {
        selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/electrons", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->electrons_->bookHistograms(fs);
        selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/muons", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->muons_->bookHistograms(fs);
        selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/hadTaus", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->hadTaus_->bookHistograms(fs);
        selHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/jets", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->jets_->bookHistograms(fs);
        selHistManager->leadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/leadJet", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
        selHistManager->leadJet_->bookHistograms(fs);
        selHistManager->subleadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/subleadJet", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
        selHistManager->subleadJet_->bookHistograms(fs);
        selHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/BJets_loose", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->BJets_loose_->bookHistograms(fs);
        selHistManager->leadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/leadBJet_loose", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
        selHistManager->leadBJet_loose_->bookHistograms(fs);
        selHistManager->subleadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/subleadBJet_loose", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
        selHistManager->subleadBJet_loose_->bookHistograms(fs);
        selHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/BJets_medium", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
        selHistManager->BJets_medium_->bookHistograms(fs);
        selHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/met", histogramDir.data()), era_string, central_or_shift));
        selHistManager->met_->bookHistograms(fs);
        selHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/metFilters", histogramDir.data()), era_string, central_or_shift));
        selHistManager->metFilters_->bookHistograms(fs);
        selHistManager->mvaInputVariables_2lss_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/mvaInputs_2lss", histogramDir.data()), era_string, central_or_shift));
        selHistManager->mvaInputVariables_2lss_->bookHistograms(fs, mvaInputVariables_2lss);
      }

      for(const std::string & evt_cat_str: evt_cat_strs)
      {
        if(skipBooking && evt_cat_str != default_cat_str)
        {
          continue;
        }
        const std::string process_string_new = evt_cat_str == default_cat_str ?
          process_string + "_" :
          process_string + "_" + evt_cat_str + "_"
        ;
        const std::string process_and_genMatchName = boost::replace_all_copy(
          process_and_genMatch, process_string, process_string_new
        );

        selHistManager->evt_[evt_cat_str] = new EvtHistManager_ttWctrl(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
        ));
        selHistManager->evt_[evt_cat_str]->bookHistograms(fs);
      }

      const vstring decayModes_evt = eventInfo.getDecayModes();
      if(isSignal)
      {
        for(const std::string & decayMode_evt: decayModes_evt)
        {
          std::string decayMode_and_genMatch = decayMode_evt;
          if(apply_leptonGenMatching)
          {
            decayMode_and_genMatch += leptonGenMatch_definition.name_;
          }

          for(const std::string & evt_cat_str: evt_cat_strs)
          {
            if(skipBooking && evt_cat_str != default_cat_str)
            {
              continue;
            }
            const std::string process_string_new = evt_cat_str == default_cat_str ?
              process_string:
              process_string + "_" + evt_cat_str
            ;
            const std::string decayMode_and_genMatchName = boost::replace_all_copy(
              decayMode_and_genMatch, process_string, process_string_new
            );

            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] = new EvtHistManager_ttWctrl(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
            ));
            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> bookHistograms(fs);
          }
        }
      }
      if(! skipBooking)
      {
        edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/evtYield", histogramDir.data()), era_string, central_or_shift);
        cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
        cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
        selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
        selHistManager->evtYield_->bookHistograms(fs);
        selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/weights", histogramDir.data()), era_string, central_or_shift));
        selHistManager->weights_->bookHistograms(fs, { "genWeight", "pileupWeight", "triggerWeight", "data_to_MC_correction", "fakeRate" });
      }
      selHistManagers[central_or_shift][idxLepton] = selHistManager;
    }

    if(isMC && ! skipBooking)
    {
      genEvtHistManager_beforeCuts[central_or_shift] = new GenEvtHistManager(makeHistManager_cfg(process_string,
        Form("%s/unbiased/genEvt", histogramDir.data()), era_string, central_or_shift));
      genEvtHistManager_beforeCuts[central_or_shift]->bookHistograms(fs);
      genEvtHistManager_afterCuts[central_or_shift] = new GenEvtHistManager(makeHistManager_cfg(process_string,
        Form("%s/sel/genEvt", histogramDir.data()), era_string, central_or_shift));
      genEvtHistManager_afterCuts[central_or_shift]->bookHistograms(fs);
      lheInfoHistManager[central_or_shift] = new LHEInfoHistManager(makeHistManager_cfg(process_string,
        Form("%s/sel/lheInfo", histogramDir.data()), era_string, central_or_shift));
      lheInfoHistManager[central_or_shift]->bookHistograms(fs);

      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts[central_or_shift]->bookHistograms(fs, eventWeightManager);
        genEvtHistManager_afterCuts[central_or_shift]->bookHistograms(fs, eventWeightManager);
      }
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
    EvtWeightRecorder evtWeightRecorder(central_or_shifts_local, central_or_shift_main, isMC);
    cutFlowTable.update("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(minLeptonSelection) < 2 ||
         objectMultiplicity.getNRecoLepton(kTight)             > 2  )
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }
    cutFlowTable.update("object multiplicity", evtWeightRecorder.get(central_or_shift_main));

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
      for(const std::string & central_or_shift: central_or_shifts_local)
      {
        if(central_or_shift != central_or_shift_main)
        {
          continue;
        }
        genEvtHistManager_beforeCuts[central_or_shift]->fillHistograms(
          genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
        );
        if(eventWeightManager)
        {
          genEvtHistManager_beforeCuts[central_or_shift]->fillHistograms(
            eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift)
          );
        }
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, isDEBUG);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e, isDEBUG);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu, isDEBUG);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu, isDEBUG);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu, isDEBUG);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	std::cout << " (selTrigger_1e = " << selTrigger_1e
		  << ", selTrigger_2e = " << selTrigger_2e
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_2mu = " << selTrigger_2mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }

//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_2mu || isTriggered_1e1mu) ) {
	if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1e = " << selTrigger_1e
		    << ", isTriggered_1mu = " << isTriggered_1mu
		    << ", isTriggered_2mu = " << isTriggered_2mu
		    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_1e && isTriggered_2e && era != kEra_2018 ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1e = " << selTrigger_1e
                    << ", isTriggered_2e = " << isTriggered_2e << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e && (isTriggered_2mu || isTriggered_1e1mu) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_2e = " << selTrigger_2e
		    << ", isTriggered_2mu = " << isTriggered_2mu
		    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_2mu || isTriggered_1e1mu) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1mu = " << selTrigger_1mu
		    << ", isTriggered_2e = " << isTriggered_2e
		    << ", isTriggered_2mu = " << isTriggered_2mu
		    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_1e1mu && isTriggered_2mu ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1e1mu = " << selTrigger_1e1mu
		    << ", isTriggered_2mu = " << isTriggered_2mu << ")" << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift_main));

    if ( (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)   ||
	 (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
	 (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
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
    const std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons, isHigherConePt);
    const std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons, isHigherConePt);
    const std::vector<const RecoMuon*> tightMuons = tightMuonSelector(fakeableMuons, isHigherConePt);
    if(isDEBUG ) // || run_lumi_eventSelector Xanda
    {
      printCollection("preselMuons",   preselMuons);
      printCollection("fakeableMuons", fakeableMuons);
      printCollection("tightMuons",    tightMuons);
    }

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    const std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons, isHigherConePt);
    const std::vector<const RecoElectron*> preselElectronsUncleaned = preselElectronSelector(electron_ptrs, isHigherConePt);
    const std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons, isHigherConePt);
    const std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(fakeableElectrons, isHigherConePt);
    if(isDEBUG ) // || run_lumi_eventSelector Xanda
    {
      printCollection("preselElectrons",   preselElectrons);
      printCollection("preselElectronsUncleaned", preselElectronsUncleaned);
      printCollection("fakeableElectrons", fakeableElectrons);
      printCollection("tightElectrons",    tightElectrons);
    }

    const std::vector<const RecoLepton*> preselLeptonsFull = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    const std::vector<const RecoLepton*> preselLeptonsFullUncleaned = mergeLeptonCollections(preselElectronsUncleaned, preselMuons, isHigherConePt);
    const std::vector<const RecoLepton*> fakeableLeptonsFull = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    const std::vector<const RecoLepton*> tightLeptonsFull = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    const std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 2);
    const std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 2);
    const std::vector<const RecoLepton*> tightLeptons = getIntersection(fakeableLeptons, tightLeptonsFull, isHigherConePt);

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
      const std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
      selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);
    }

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau *> looseHadTaus = looseHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(looseHadTaus, isHigherPt);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableLeptonsFull, looseHadTaus) :
      jetCleaner       (jet_ptrs, fakeableLeptonsFull, looseHadTaus)
    ;
    const std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    const std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    const std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);
    const std::vector<const RecoJet *> selJetsForward = jetSelectorForward(cleanedJets, isHigherPt);

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

        hadTauGenMatcher.addGenLeptonMatchByIndex(selHadTaus, hadTauGenMatch, GenParticleType::kGenAnyLepton);
        hadTauGenMatcher.addGenHadTauMatch       (selHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch          (selHadTaus, genJets);

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

        hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons);
        hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch   (selHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets, genJets);
      }
    }

//--- apply preselection
    // require two or more leptons passing loose preselection criteria
    if ( !(preselLeptonsFull.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS preselLeptons selection." << std::endl;
  //printCollection("preselLeptons", preselLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons", evtWeightRecorder.get(central_or_shift_main));
    const RecoLepton* preselLepton_lead = preselLeptonsFull[0];
    const RecoLepton* preselLepton_sublead = preselLeptonsFull[1];
    const leptonChargeFlipGenMatchEntry& preselLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selJets selection (1)." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets", evtWeightRecorder.get(central_or_shift_main));
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selBJets selection (1)." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift_main));

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptonsFull, looseHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    // require two or more leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
	std::cout << " (#selLeptons = " << selLeptons.size() << ")" << std::endl;
	for ( size_t idxSelLepton = 0; idxSelLepton < selLeptons.size(); ++idxSelLepton ) {
	  std::cout << "selLepton #" << idxSelLepton << ":" << std::endl;
	  std::cout << (*selLeptons[idxSelLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 sel leptons", evtWeightRecorder.get(central_or_shift_main));
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const leptonChargeFlipGenMatchEntry& selLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined2);

    if(isMC)
    {
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
        selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta()
      );

//--- apply data/MC corrections for trigger efficiency
      evtWeightRecorder.record_leptonTriggerEff(dataToMCcorrectionInterface);

//--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria
      evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose());

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if(electronSelection == kFakeable && muonSelection == kFakeable)
      {
        evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose());
      }
      else if(electronSelection >= kFakeable && muonSelection >= kFakeable)
      {
        // apply loose-to-tight lepton ID SFs if either of the following is true:
        // 1) both electron and muon selections are tight -> corresponds to SR
        // 2) electron selection is relaxed to fakeable and muon selection is kept as tight -> corresponds to MC closure w/ relaxed e selection
        // 3) muon selection is relaxed to fakeable and electron selection is kept as tight -> corresponds to MC closure w/ relaxed mu selection
        // we allow (2) and (3) so that the MC closure regions would more compatible w/ the SR (1) in comparison
        evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge());
      }
    }

    if(applyFakeRateWeights == kFR_2lepton)
    {
      bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
      bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
      evtWeightRecorder.record_jetToLepton_FR_lead(leptonFakeRateInterface, selLepton_lead);
      evtWeightRecorder.record_jetToLepton_FR_sublead(leptonFakeRateInterface, selLepton_sublead);

      evtWeightRecorder.compute_FR_2l(passesTight_lepton_lead, passesTight_lepton_sublead);
    }

    if ( !(tightLeptonsFull.size() <= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection." << std::endl;
  //printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 2 tight leptons", evtWeightRecorder.get(central_or_shift_main));

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,    selTrigger_1e    },
        { hltPathsE::trigger_1mu,   selTrigger_1mu   },
        { hltPathsE::trigger_2e,    selTrigger_2e    },
        { hltPathsE::trigger_2mu,   selTrigger_2mu   },
        { hltPathsE::trigger_1e1mu, selTrigger_1e1mu },
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
    cutFlowTable.update("HLT filter matching", evtWeightRecorder.get(central_or_shift_main));

    // apply requirement on jets (incl. b-tagged jets) on level of final event selection
    //std::cout << "event " << eventInfo.str() << " selJets selection (2) -- " << selJets.size() << std::endl;
    //printCollection("selJets", selJets);
    if ( !(selJets.size() == 3) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selJets selection (2) -- " << selJets.size() << std::endl;
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update("= 3 jets", evtWeightRecorder.get(central_or_shift_main));

    if ( selHadTaus.size() > 0 ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selHadTaus veto." << std::endl;
	printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update("sel tau veto", evtWeightRecorder.get(central_or_shift_main));

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsFullUncleaned);
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));

    const double minPt_lead = 25.;
    const double minPt_sublead = 15.;
     // CV: according to Giovanni, the pT cuts should be applied on cone_pt
    //    (combined efficiency of single lepton and double lepton triggers assumed to be high,
    //     even if one or two leptons and fakes and hence cone_pt may be significantly smaller than lepton_pt,
    //     on which pT cuts are applied on trigger level)
    if ( !(selLepton_lead->cone_pt() > minPt_lead && selLepton_sublead->cone_pt() > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV", evtWeightRecorder.get(central_or_shift_main));

    bool failsTightChargeCut = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton = fakeableLeptons.begin();
    lepton != fakeableLeptons.end(); ++lepton ) {
      if ( (*lepton)->is_electron() ) {
	const RecoElectron* electron = dynamic_cast<const RecoElectron*>(*lepton);
	assert(electron);
	if ( electron->tightCharge() < 2 ) failsTightChargeCut = true;
      }
      if ( (*lepton)->is_muon() ) {
	const RecoMuon* muon = dynamic_cast<const RecoMuon*>(*lepton);
	assert(muon);
	if ( muon->tightCharge() < 2 ) failsTightChargeCut = true;
      }
    }
    if ( failsTightChargeCut ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS tight lepton charge requirement." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("tight lepton charge", evtWeightRecorder.get(central_or_shift_main));

    const bool isLeptonCharge_SS = selLepton_lead->charge() * selLepton_sublead->charge() > 0;
    const bool isLeptonCharge_OS = selLepton_lead->charge() * selLepton_sublead->charge() < 0;
    if(leptonChargeSelection == kOS && isLeptonCharge_SS)
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection.\n"
                     " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge()
                  << ", leptonChargeSelection = OS)\n"
        ;
      }
      continue;
    }
    if(leptonChargeSelection == kSS && isLeptonCharge_OS)
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection.\n"
                     " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge()
                  << ", leptonChargeSelection = SS)\n"
        ;
      }
      continue;
    }
    if(leptonChargeSelection == kOS)
    {
      const double prob_chargeMisId_lead = prob_chargeMisId(
        era, getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta()
      );
      const double prob_chargeMisId_sublead = prob_chargeMisId(
        era, getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta()
      );
      const double prob_chargeMisId_sum = (prob_chargeMisId_lead + prob_chargeMisId_sublead);

      // Karl: reject the event, if the applied probability of charge misidentification is 0;
      //       note that this can happen only if both selected leptons are muons (their misId prob is 0).
      if(prob_chargeMisId_sum == 0.)
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS charge flip selection\n"
                       "(leading lepton charge (pdgId) = " << selLepton_lead->charge() << " (" << selLepton_lead->pdgId()
                    << ") => misId prob = " << prob_chargeMisId_lead << "; "
                       "subleading lepton charge (pdgId) = " << selLepton_sublead->charge() << " (" << selLepton_sublead->pdgId()
                    << ") => misId prob = " << prob_chargeMisId_sublead << ")\n"
          ;
        }
        continue;
      }
      evtWeightRecorder.record_chargeMisIdProb(prob_chargeMisId_sum);
    }
    cutFlowTable.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeightRecorder.get(central_or_shift_main));

    const bool failsZbosonMassVeto = isfailsZbosonMassVeto(preselLeptonsFull) || (
        selLepton_lead->is_electron() &&
        selLepton_sublead->is_electron() &&
        isfailsZbosonMassVeto({ selLepton_lead, selLepton_sublead }, true)
      )
    ;
    if ( failsZbosonMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS Z-boson veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeightRecorder.get(central_or_shift_main));

    if ( !(selLepton_lead->is_muon() || selLepton_sublead->is_muon() || met_LD >= 30.) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS MET LD selection.\n"
	  " (LD = " << met_LD << ")\n"
	;
      }
      continue;
    }
    cutFlowTable.update("met LD > 30 GeV", evtWeightRecorder.get(central_or_shift_main));

    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS MEt filters." << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeightRecorder.get(central_or_shift_main));

    bool failsSignalRegionVeto = false;
    if ( isMCClosure_e || isMCClosure_m ) {
      bool applySignalRegionVeto = (isMCClosure_e && countFakeElectrons(selLeptons) >= 1) || (isMCClosure_m && countFakeMuons(selLeptons) >= 1);
      if ( applySignalRegionVeto && tightLeptons.size() >= 2 ) failsSignalRegionVeto = true;
    } else if ( electronSelection == kFakeable || muonSelection == kFakeable ) {
      if ( tightLeptons.size() >= 2 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
	             "# tight leptons = " << tightLeptons.size() << " >= 2\n"
        ;
	//printCollection("tightLeptons", tightLeptons);
      }
      continue; // CV: avoid overlap with signal region
    }
    cutFlowTable.update("signal region veto", evtWeightRecorder.get(central_or_shift_main));

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss category of ttH multilepton analysis
    const int nJet25_Recl = comp_n_jet25_recl(selJets);

    const double mindr_lep1_jet = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    const double mindr_lep2_jet = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    const double max_lep_eta    = std::max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    const double mT_lep1        = comp_MT_met_lep1(*selLepton_lead,    met.pt(), met.phi());
    const double avg_dr_jet     = comp_avg_dr_jet(selJets);
    const double lep1_conePt    = comp_lep1_conePt(*selLepton_lead);
    const double lep2_conePt    = comp_lep2_conePt(*selLepton_sublead);
    const double minMET400      = std::min(met.pt(), 400.);

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
    if      ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.4 ) mvaDiscr_2lss = 7.;
    else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.1 ) mvaDiscr_2lss = 6.;
    else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV <= +0.1 ) mvaDiscr_2lss = 5.;
    else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV >  +0.3 ) mvaDiscr_2lss = 4.;
    else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV <= +0.3 ) mvaDiscr_2lss = 3.;
    else if ( mvaOutput_2lss_ttbar > -0.2                               ) mvaDiscr_2lss = 2.;
    else                                                                  mvaDiscr_2lss = 1.;

    for(const std::string & central_or_shift: central_or_shifts_local)
    {
      const bool skipFilling = central_or_shift != central_or_shift_main;
      selHistManagerType* selHistManager = selHistManagers[central_or_shift][idxSelLepton_genMatch];
      assert(selHistManager != 0);
      const double evtWeight = evtWeightRecorder.get(central_or_shift);
      if(! skipFilling)
      {
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
      }

      const std::string central_or_shift_tH = eventInfo.has_central_or_shift(central_or_shift) ? central_or_shift : central_or_shift_main;
      const double evtWeight_tH_nom = evtWeightRecorder.get_nom_tH_weight(central_or_shift_tH);
      std::map<std::string, double> tH_weight_map;
      for(const std::string & evt_cat_str: evt_cat_strs)
      {
        if(skipFilling && evt_cat_str != default_cat_str)
        {
          continue;
        }
        const std::string evt_cat_str_query = evt_cat_str == default_cat_str ? get_tH_SM_str() : evt_cat_str;
        tH_weight_map[evt_cat_str] = isMC_tH ?
          evtWeight / evtWeight_tH_nom * eventInfo.genWeight_tH(central_or_shift_tH, evt_cat_str_query):
          evtWeight
        ;
      }
      for(const auto & kv: tH_weight_map)
      {
        selHistManager->evt_[kv.first]->fillHistograms(
          selElectrons.size(), selMuons.size(), selHadTaus.size(),
          selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
          mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss,
          selLepton_lead->cone_pt() + selLepton_sublead->cone_pt(), kv.second
        );
      }
      if(isSignal)
      {
        const std::string decayModeStr = eventInfo.getDecayModeString();
        if(! decayModeStr.empty())
        {
          for(const auto & kv: tH_weight_map)
          {
            selHistManager->evt_in_decayModes_[kv.first][decayModeStr]->fillHistograms(
              selElectrons.size(), selMuons.size(), selHadTaus.size(),
              selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
              mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss,
              selLepton_lead->cone_pt() + selLepton_sublead->cone_pt(), kv.second
            );
          }
        }
      }
      if(! skipFilling)
      {
        selHistManager->evtYield_->fillHistograms(eventInfo, evtWeight);
        selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
        selHistManager->weights_->fillHistograms("pileupWeight", evtWeightRecorder.get_puWeight(central_or_shift));
        selHistManager->weights_->fillHistograms("triggerWeight", evtWeightRecorder.get_sf_triggerEff(central_or_shift));
        selHistManager->weights_->fillHistograms("data_to_MC_correction", evtWeightRecorder.get_data_to_MC_correction(central_or_shift));
        selHistManager->weights_->fillHistograms("fakeRate", evtWeightRecorder.get_FR(central_or_shift));
      }

      if(isMC && ! skipFilling)
      {
        genEvtHistManager_afterCuts[central_or_shift]->fillHistograms(
          genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
        );
        lheInfoHistManager[central_or_shift]->fillHistograms(*lheInfoReader, evtWeight);
        if(eventWeightManager)
        {
          genEvtHistManager_afterCuts[central_or_shift]->fillHistograms(
            eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift)
          );
        }
      }
    }

    (*selEventsFile) << eventInfo.str() << '\n';

    if(snm)
    {
      const bool isGenMatched = isMC &&
        contains(syncNtuple_genMatch, selLepton_genMatch.name_)
      ;

      const double dr_leps        = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
      const double mT_lep2        = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
      const double max_dr_jet     = comp_max_dr_jet(selJets);
      const double mbb            = selBJets_medium.size() > 1 ?  (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1000;
      const double mbb_loose      = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1000;
      const double min_dr_lep_jet = std::min(mindr_lep1_jet, mindr_lep2_jet);
      const int nLightJet         = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(looseHadTaus);
      snm->read(selJets);

      snm->read({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
      snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size(), nLightJet);

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);

      snm->read(mindr_lep1_jet,                         FloatVariableType::mindr_lep1_jet);
      snm->read(mindr_lep2_jet,                         FloatVariableType::mindr_lep2_jet);
      // mindr_lep3_jet not filled
      // mindr_lep4_jet not filled

      // mindr_tau_jet not filled
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

      //snm->read(mvaOutput_2lss_ttV,                     FloatVariableType::mvaOutput_2lss_ttV);
      //snm->read(mvaOutput_2lss_ttbar,                   FloatVariableType::mvaOutput_2lss_tt);
      // mvaOutput_2lss_1tau_plainKin_tt not filled
      // mvaOutput_2lss_1tau_plainKin_ttV not filled
      // mvaOutput_2lss_1tau_plainKin_1B_M not filled
      // mvaOutput_2lss_1tau_plainKin_SUM_M not filled
      // mvaOutput_2lss_1tau_HTT_SUM_M not filled
      // mvaOutput_2lss_1tau_HTTMEM_SUM_M not filled

      // mvaOutput_3l_ttV not filled
      // mvaOutput_3l_ttbar not filled
      // mvaOutput_plainKin_SUM_M not filled
      // mvaOutput_plainKin_1B_M not filled

      // weight_fakeRate not filled
      // triggerWeight not filled
      // leptonSF_weight not filled
      // tauSF_weight not filled
      snm->read(evtWeightRecorder.get_btag(central_or_shift_main),           FloatVariableType::bTagSF_weight);
      snm->read(evtWeightRecorder.get_puWeight(central_or_shift_main),       FloatVariableType::PU_weight);
      snm->read(evtWeightRecorder.get_genWeight(),                           FloatVariableType::MC_weight);

      // memOutput_ttH not filled
      // memOutput_ttZ not filled
      // memOutput_ttZ_Zll not filled
      // memOutput_tt not filled
      // memOutput_type not filled
      // memOutput_LR not filled

      snm->read(eventInfo.genWeight,                    FloatVariableType::genWeight);

      if(isGenMatched)
      {
        snm->fill();
      }
      else
      {
        snm->resetBranches();
      }
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeightRecorder.get(central_or_shift_main);
    histogram_selectedEntries->Fill(0.);
    if(isDEBUG)
    {
      std::cout << evtWeightRecorder << '\n';
    }
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

  for(auto & kv: genEvtHistManager_beforeCuts)
  {
    delete kv.second;
  }
  for(auto & kv: genEvtHistManager_afterCuts)
  {
    delete kv.second;
  }
  for(auto & kv: lheInfoHistManager)
  {
    delete kv.second;
  }
  delete l1PreFiringWeightReader;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;

  clock.Show("analyze_ttWctrl");

  return EXIT_SUCCESS;
}
