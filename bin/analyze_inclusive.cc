#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // comp_*()
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs()
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtag*
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorForward.h" // RecoJetSelectorForward
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherConePt(), mergeLeptonCollections()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // k*_central
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths(), hltPaths_isTriggered()
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader

#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_semi_boosted
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions_Hj_and_Hjj_taggers.h" // comp_mvaOutput_Hj_tagger()

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleanerSubJets.h" // RecoJetCollectionCleanerAK8SubJets

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet
#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <TBenchmark.h> // TBenchmark
#include <TError.h> // gErrorAbortLevel, kError

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <numeric> // std::accumulate()

typedef std::vector<std::string> vstring;

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Run sync Ntuple in inclusive mode
 */
int
main(int argc,
     char * argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_inclusive>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_inclusive");

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException("analyze_inclusive")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  }

  const std::vector<std::string> mvaInputVariables_TensorFlow_3l_ttH_tH_3cat_v8 = {
    "avg_dr_jet", "ptmiss", "mbb_medium",
    "jet1_pt", "jet2_pt", "jet3_pt", "jet4_pt",
    "max_lep_eta",
    "lep1_mT", "lep1_conept", "lep2_mT", "lep2_conept", "lep3_mT", "lep3_conept",
    "jetForward1_pt", "res-HTT_CSVsort4rd", "HadTop_pt_CSVsort4rd",
    "nJet", "nJetForward", "nBJetLoose",
    "nBJetMedium", "nElectron", "sum_lep_charge"
  };
  const std::vector<std::string> classes_TensorFlow_3l_ttH_tH_3cat = {
    "predictions_ttH",  "predictions_rest", "predictions_tH"
  };
  const std::string mvaFileName_TensorFlow_3l_ttH_tH_3cat_v8 =
    "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_sync/test_model_3l_ttH_tH_3cat_nottZ_no4mom_noSemi_noStand_v8.pb"
  ;
  const TensorFlowInterface mva_3l_ttH_tH_3cat_v8_TF(
    mvaFileName_TensorFlow_3l_ttH_tH_3cat_v8,
    mvaInputVariables_TensorFlow_3l_ttH_tH_3cat_v8,
    classes_TensorFlow_3l_ttH_tH_3cat
  );

  const std::string mvaFileName_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4 =
    "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_sync/test_model_2lss_ttH_tH_4cat_onlyTHQ_notEnrich_v4.pb"
  ;
  const std::vector<std::string> mvaInputVariables_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4 = {
    "avg_dr_jet", "ptmiss", "mbb_medium",
    "jet1_pt", "jet2_pt", "jet3_pt", "jet4_pt", "max_lep_eta",
    "lep1_mT", "lep1_conept", "lep1_min_dr_jet",
    "lep2_mT", "lep2_conept", "lep2_min_dr_jet",
    "nJetForward", "jetForward1_pt", "jetForward1_eta_abs",
    "res-HTT_CSVsort4rd", "HadTop_pt_CSVsort4rd",
    "nJet", "nBJetLoose", "nBJetMedium", "nElectron", "sum_lep_charge", "mvaOutput_Hj_tagger"
  };
  // the order also matters
  const std::vector<std::string> classes_TensorFlow_2lss_ttH_tH_4cat = {
    "predictions_ttH", "predictions_ttW", "predictions_rest", "predictions_tH"
  };
  const TensorFlowInterface mva_2lss_ttH_tH_4cat_onlyTHQ_v4(
    mvaFileName_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4,
    mvaInputVariables_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4,
    classes_TensorFlow_2lss_ttH_tH_4cat
  );

  const std::string mvaFileName_Hj_tagger = "tthAnalysis/HiggsToTauTau/data/Hj_deepcsv_BDTG_2017.weights.xml";
  std::vector<std::string> mvaInputVariables_Hj_tagger = {
    "Jet25_lepdrmin", "max(Jet25_bDiscriminator,0.)",
    "max(Jet25_qg,0.)", "Jet25_lepdrmax", "Jet25_pt"
  };
  const TMVAInterface mva_Hj_tagger(mvaFileName_Hj_tagger, mvaInputVariables_Hj_tagger);

  //--- initialize hadronic top tagger BDT
  HadTopTagger hadTopTagger;
  HadTopTagger_semi_boosted_AK8 hadTopTagger_semi_boosted_fromAK8;

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_inclusive");

  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string process_string = cfg_analyze.getParameter<std::string>("process");

  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
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
  vstring triggerNames_3e = cfg_analyze.getParameter<vstring>("triggers_3e");
  std::vector<hltPath*> triggers_3e = create_hltPaths(triggerNames_3e);
  bool use_triggers_3e = cfg_analyze.getParameter<bool>("use_triggers_3e");
  vstring triggerNames_2e1mu = cfg_analyze.getParameter<vstring>("triggers_2e1mu");
  std::vector<hltPath*> triggers_2e1mu = create_hltPaths(triggerNames_2e1mu);
  bool use_triggers_2e1mu = cfg_analyze.getParameter<bool>("use_triggers_2e1mu");
  vstring triggerNames_1e2mu = cfg_analyze.getParameter<vstring>("triggers_1e2mu");
  std::vector<hltPath*> triggers_1e2mu = create_hltPaths(triggerNames_1e2mu);
  bool use_triggers_1e2mu = cfg_analyze.getParameter<bool>("use_triggers_1e2mu");
  vstring triggerNames_3mu = cfg_analyze.getParameter<vstring>("triggers_3mu");
  std::vector<hltPath*> triggers_3mu = create_hltPaths(triggerNames_3mu);
  bool use_triggers_3mu = cfg_analyze.getParameter<bool>("use_triggers_3mu");
  vstring triggerNames_1mu1tau = cfg_analyze.getParameter<vstring>("triggers_1mu1tau");
  std::vector<hltPath*> triggers_1mu1tau = create_hltPaths(triggerNames_1mu1tau);
  bool use_triggers_1mu1tau = cfg_analyze.getParameter<bool>("use_triggers_1mu1tau");
  vstring triggerNames_1e1tau = cfg_analyze.getParameter<vstring>("triggers_1e1tau");
  std::vector<hltPath*> triggers_1e1tau = create_hltPaths(triggerNames_1e1tau);
  bool use_triggers_1e1tau = cfg_analyze.getParameter<bool>("use_triggers_1e1tau");
  vstring triggerNames_2tau = cfg_analyze.getParameter<vstring>("triggers_2tau");
  std::vector<hltPath*> triggers_2tau = create_hltPaths(triggerNames_2tau);

  const bool apply_offline_e_trigger_cuts_1e      = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  const bool apply_offline_e_trigger_cuts_2e      = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  const bool apply_offline_e_trigger_cuts_1mu     = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  const bool apply_offline_e_trigger_cuts_2mu     = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  const bool apply_offline_e_trigger_cuts_1e1mu   = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");
  const bool apply_offline_e_trigger_cuts_3e      = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3e");
  const bool apply_offline_e_trigger_cuts_2e1mu   = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e1mu");
  const bool apply_offline_e_trigger_cuts_1e2mu   = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e2mu");
  const bool apply_offline_e_trigger_cuts_3mu     = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3mu");
  const bool apply_offline_e_trigger_cuts_1mu1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu1tau");
  const bool apply_offline_e_trigger_cuts_1e1tau  = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1tau");

  const std::string hadTauSelection_tauIdWP = cfg_analyze.getParameter<std::string>("hadTauSelection_tauIdWP");
  const std::string hadTauAk8Clean_tauIdWP  = cfg_analyze.getParameter<std::string>("hadTauAk8Clean_tauIdWP");
  const std::string central_or_shift        = cfg_analyze.getParameter<std::string>("central_or_shift");

  const bool isMC               = cfg_analyze.getParameter<bool>("isMC");
  const bool useNonNominal      = cfg_analyze.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet = useNonNominal || ! isMC;

  const bool redoGenMatching    = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");
  const bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  const bool readGenObjects     = isMC && ! redoGenMatching;

  checkOptionValidity(central_or_shift, isMC);
  const int jetBtagSF_option = getBTagWeight_option   (central_or_shift);

  const int met_option       = useNonNominal_jetmet ? kJetMET_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option     = useNonNominal_jetmet ? kJetMET_central_nonNominal : getJet_option(central_or_shift, isMC);
  const int hadTauPt_option  = useNonNominal_jetmet ? kHadTauPt_uncorrected      : getHadTauPt_option(central_or_shift);

  const bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");

  const std::string branchName_electrons  = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons      = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus    = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  const std::string branchName_jets       = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met        = cfg_analyze.getParameter<std::string>("branchName_met");
  const std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  const std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  const std::string branchName_genJets    = cfg_analyze.getParameter<std::string>("branchName_genJets");

  const std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  const std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  const std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  const std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  const std::string branchName_jetsAK8      = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  const std::string branchName_subjetsAK8   = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");

  const std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << '\n';
  RunLumiEventSelector * run_lumi_eventSelector = nullptr;
  if(! selEventsFileName_input.empty())
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << '\n';
  const unsigned reportEvery = inputFiles.reportAfter();

  TTreeWrapper * const inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s).\n";

//--- prepare sync Ntuple
  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const std::string syncNtuple_tree = syncNtuple_cfg.getParameter<std::string>("tree");
  const std::string syncNtuple_output = syncNtuple_cfg.getParameter<std::string>("output");
  if(syncNtuple_tree.empty() || syncNtuple_output.empty())
  {
    throw cmsException("analyze_inclusive", __LINE__)
      << "Need to specify both analyze_inclusive.syncNtuple.tree and "
         "analyze_inclusive.syncNtuple.output in order to run this program";
  }
  SyncNtupleManager * const snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
  snm->initializeBranches();
  snm->initializeHLTBranches({
    triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu,
    triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu,
    triggers_1mu1tau, triggers_1e1tau, triggers_2tau
  });

//--- declare event-level variables
  EventInfo eventInfo(isMC);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({
    triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu,
    triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu,
    triggers_1mu1tau, triggers_1e1tau, triggers_2tau
  });
  inputTree -> registerReader(&hltPathReader_instance);

//--- declare particle collections
  RecoMuonReader * const muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree->registerReader(muonReader);
  const RecoMuonCollectionGenMatcher muonGenMatcher;
  const RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  const RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  const RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);

  RecoElectronReader * const electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree->registerReader(electronReader);
  const RecoElectronCollectionGenMatcher electronGenMatcher;
  const RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  const RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  const RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);

  RecoHadTauReader * const hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree->registerReader(hadTauReader);
  const RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  const RecoHadTauCollectionCleaner hadTauCleaner(0.3, isDEBUG);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_tauIdWP);
  fakeableHadTauSelector.set_min_antiElectron(-1);
  fakeableHadTauSelector.set_min_antiMuon(-1);

  // X: it is used just for cleaning of AK8 jets, that is used only in channels using Medium WP tau as the tight tau
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauAk8Clean_tauIdWP);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader * const jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree->registerReader(jetReader);
  const RecoJetCollectionGenMatcher jetGenMatcher;
  const RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  const RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  const RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  const RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  const RecoJetCollectionCleaner jetCleaner_large8(0.8, isDEBUG);
  const RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);
  const RecoJetCollectionSelectorForward jetSelectorForward(era, -1, isDEBUG);

  RecoJetReaderAK8 * const jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  const RecoJetCollectionSelectorAK8 jetSelectorAK8(era);
  const RecoJetCollectionCleanerAK8 jetCleanerAK8(0.8, isDEBUG); // [*]
  const RecoJetCollectionCleanerAK8SubJets jetCleanerAK8SubJets(0.4, isDEBUG); // [*]
  // [*] to clean against leptons and hadronic taus

//--- declare missing transverse energy
  RecoMEtReader * const metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  GenJetReader * genJetReader = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  GenParticleReader * genMatchToHadTauReader   = nullptr;
  GenParticleReader * genMatchToJetReader      = nullptr;

  if(isMC && ! readGenObjects)
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

  int analyzedEntries = 0;
  int selectedEntries = 0;

  while(inputTree->hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree->canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree->getCurrentMaxEventIdx()
                << " or " << inputTree->getCurrentEventIdx() << " entry in #"
                << (inputTree->getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    //if (!( eventInfo.event == 126120 )) continue; 

    if(run_lumi_eventSelector && ! (*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree->getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree->isOpen())
      {
        std::cout << "input File = " << inputTree->getCurrentFileName() << '\n';
      }
    }

    snm->read(eventInfo);
    snm->read(eventInfo.pileupWeight,                 FloatVariableType::PU_weight);
    snm->read(eventInfo.genWeight,                    FloatVariableType::genWeight);
    snm->read(boost::math::sign(eventInfo.genWeight), FloatVariableType::MC_weight);

    const bool isTriggered_1e      = hltPaths_isTriggered(triggers_1e);
    const bool isTriggered_2e      = hltPaths_isTriggered(triggers_2e);
    const bool isTriggered_1mu     = hltPaths_isTriggered(triggers_1mu);
    const bool isTriggered_2mu     = hltPaths_isTriggered(triggers_2mu);
    const bool isTriggered_1e1mu   = hltPaths_isTriggered(triggers_1e1mu);
    const bool isTriggered_3e      = hltPaths_isTriggered(triggers_3e);
    const bool isTriggered_2e1mu   = hltPaths_isTriggered(triggers_2e1mu);
    const bool isTriggered_1e2mu   = hltPaths_isTriggered(triggers_1e2mu);
    const bool isTriggered_3mu     = hltPaths_isTriggered(triggers_3mu);
    const bool isTriggered_1mu1tau = hltPaths_isTriggered(triggers_1mu1tau);
    const bool isTriggered_1e1tau  = hltPaths_isTriggered(triggers_1e1tau);

    const bool selTrigger_1e      = use_triggers_1e      && isTriggered_1e;
    const bool selTrigger_2e      = use_triggers_2e      && isTriggered_2e;
    const bool selTrigger_1mu     = use_triggers_1mu     && isTriggered_1mu;
    const bool selTrigger_2mu     = use_triggers_2mu     && isTriggered_2mu;
    const bool selTrigger_1e1mu   = use_triggers_1e1mu   && isTriggered_1e1mu;
    const bool selTrigger_3e      = use_triggers_3e      && isTriggered_3e;
    const bool selTrigger_2e1mu   = use_triggers_2e1mu   && isTriggered_2e1mu;
    const bool selTrigger_1e2mu   = use_triggers_1e2mu   && isTriggered_1e2mu;
    const bool selTrigger_3mu     = use_triggers_3mu     && isTriggered_3mu;
    const bool selTrigger_1mu1tau = use_triggers_1mu1tau && isTriggered_1mu1tau;
    const bool selTrigger_1e1tau  = use_triggers_1e1tau  && isTriggered_1e1tau;

    snm->read({
      triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu,
      triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu,
      triggers_1mu1tau, triggers_1e1tau, triggers_2tau
    });

    if((selTrigger_2mu     && ! apply_offline_e_trigger_cuts_2mu)     ||
       (selTrigger_1mu     && ! apply_offline_e_trigger_cuts_1mu)     ||
       (selTrigger_2e      && ! apply_offline_e_trigger_cuts_2e)      ||
       (selTrigger_1e1mu   && ! apply_offline_e_trigger_cuts_1e1mu)   ||
       (selTrigger_1e      && ! apply_offline_e_trigger_cuts_1e)      ||
       (selTrigger_3e      && ! apply_offline_e_trigger_cuts_3e)      ||
       (selTrigger_2e1mu   && ! apply_offline_e_trigger_cuts_2e1mu)   ||
       (selTrigger_1e2mu   && ! apply_offline_e_trigger_cuts_1e2mu)   ||
       (selTrigger_3mu     && ! apply_offline_e_trigger_cuts_3mu)     ||
       (selTrigger_1mu1tau && ! apply_offline_e_trigger_cuts_1mu1tau) ||
       (selTrigger_1e1tau  && ! apply_offline_e_trigger_cuts_1e1tau)
      )
    {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
    }
    else
    {
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    const std::vector<const RecoMuon *> preselMuons   = preselMuonSelector  (cleanedMuons, isHigherConePt);
    const std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons,  isHigherConePt);
    const std::vector<const RecoMuon *> tightMuons    = tightMuonSelector   (preselMuons,  isHigherConePt);
    const std::vector<const RecoMuon *> selMuons = preselMuons;

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    const std::vector<const RecoElectron *> preselElectrons   = preselElectronSelector  (cleanedElectrons, isHigherConePt);
    const std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons,  isHigherConePt);
    const std::vector<const RecoElectron *> tightElectrons    = tightElectronSelector   (preselElectrons,  isHigherConePt);
    const std::vector<const RecoElectron *> selElectrons = preselElectrons;

    const std::vector<const RecoLepton *> preselLeptons   = mergeLeptonCollections(preselElectrons,   preselMuons,   isHigherConePt);
    const std::vector<const RecoLepton *> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    const std::vector<const RecoLepton *> selLeptons      = mergeLeptonCollections(selElectrons,      selMuons,      isHigherConePt);

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau *> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau *> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselLeptons);
    const std::vector<const RecoHadTau *> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau *> tightHadTaus = tightHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau *> selHadTaus = fakeableHadTaus;

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet *> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableLeptons, fakeableHadTaus)       :
      jetCleaner       (jet_ptrs, fakeableLeptons, fakeableHadTaus)
    ;
    const std::vector<const RecoJet *> selJets         = jetSelector          (cleanedJets, isHigherPt);
    const std::vector<const RecoJet *> selBJets_loose  = jetSelectorBtagLoose (cleanedJets, isHigherPt);
    const std::vector<const RecoJet *> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);
    const std::vector<const RecoJet *> selJetsForward  = jetSelectorForward   (cleanedJets, isHigherPt);

    if(isMC && ! readGenObjects)
    {
      const std::vector<GenLepton> genLeptons = genLeptonReader->read();;
      const std::vector<GenHadTau> genHadTaus = genHadTauReader->read();
      const std::vector<GenJet>    genJets    = genJetReader->read();

      if(genMatchingByIndex)
      {
        const std::vector<GenParticle> muonGenMatch     = genMatchToMuonReader->read();
        const std::vector<GenParticle> electronGenMatch = genMatchToElectronReader->read();
        const std::vector<GenParticle> hadTauGenMatch   = genMatchToHadTauReader->read();
        const std::vector<GenParticle> jetGenMatch      = genMatchToJetReader->read();

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
        const std::vector<GenPhoton> genPhotons = genPhotonReader->read();

        std::vector<GenLepton> genElectrons;
        std::vector<GenLepton> genMuons;

        for(const GenLepton & genLepton: genLeptons)
        {
          const int genLeptonType = getLeptonType(genLepton.pdgId());
          switch(genLeptonType)
          {
            case kElectron: genElectrons.push_back(genLepton); break;
            case kMuon:     genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }

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

    snm->read(preselMuons, fakeableMuons, tightMuons);
    snm->read(preselElectrons, fakeableElectrons, tightElectrons);
    snm->read(selLeptons);
    snm->read(selHadTaus);
    snm->read(selJets, false);
    snm->read(selJetsForward, true);

    const double avg_dr_jet = comp_avg_dr_jet(selJets);
    const double max_dr_jet = comp_max_dr_jet(selJets);
    const double mbb        = selBJets_medium.size() > 1 ? (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1.;
    const double mbb_loose  = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
    const double btagWeight = get_BtagWeight(selJets);
    const int nLightJet = selJets.size() - selBJets_loose.size() + selJetsForward.size();

    snm->read(avg_dr_jet, FloatVariableType::avg_dr_jet);
    snm->read(max_dr_jet, FloatVariableType::max_dr_jet);
    snm->read(btagWeight, FloatVariableType::bTagSF_weight);
    snm->read(mbb,        FloatVariableType::mbb);
    snm->read(mbb_loose,  FloatVariableType::mbb_loose);

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, fakeableHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

    snm->read(met.pt(),    FloatVariableType::PFMET);
    snm->read(met.phi(),   FloatVariableType::PFMETphi);
    snm->read(mht_p4.pt(), FloatVariableType::MHT);
    snm->read(met_LD,      FloatVariableType::metLD);

    double mvaOutput_Hj_tagger = 0.;
    if(! selJets.empty())
    {
      std::map<std::string, double> mvaInputs_Hj_tagger;
      mvaOutput_Hj_tagger = comp_mvaOutput_Hj_tagger(
        selJets[0], fakeableLeptons, mvaInputs_Hj_tagger, mva_Hj_tagger, eventInfo
      );
      snm->read(mvaOutput_Hj_tagger, FloatVariableType::Hj_tagger);
    }

    bool calculate_matching = false;
    bool isGenMatched = false;
    double genTopPt_teste = 0.;
    double HadTop_pt = 0.;
    double HTT = 0.;
    std::map<int, Particle::LorentzVector> genVar, genVarAnti;
    if(selJets.size() > 2)
    {
      const std::map<int, double> bdtResult = hadTopTagger(
        *selJets[0], *selJets[1], *selJets[2], calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti
      );
      HTT       = bdtResult.at(kXGB_CSVsort4rd);
      HadTop_pt = (selJets[0]->p4() + selJets[1]->p4() + selJets[2]->p4()).pt();
      snm->read(HTT,       FloatVariableType::HTT);
      snm->read(HadTop_pt, FloatVariableType::HadTop_pt);
    }

    //--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    const std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    const std::vector<const RecoJetAK8 *> jet_ptrsAK8raw1 = convert_to_ptrs(jetsAK8);
    const std::vector<const RecoJetAK8 *> jet_ptrsAK8raw = jetSelectorAK8(jet_ptrsAK8raw1, isHigherPt);
    const std::vector<const RecoJetAK8 *> jet_ptrsAK8 = jetCleanerAK8SubJets(jet_ptrsAK8raw, tightMuons, tightElectrons, tightHadTaus);
    const std::vector<const RecoJet *> cleanedJets_fromAK8 = jetCleaner_large8(selJets, jet_ptrsAK8);

    snm->read(jet_ptrsAK8);
    snm->read(false, selBJets_medium.size(), selBJets_loose.size(), nLightJet, cleanedJets_fromAK8.size());

    if(! jet_ptrsAK8.empty() && ! cleanedJets_fromAK8.empty())
    {
      const std::map<int, double> bdtResult_semi_boosted = hadTopTagger_semi_boosted_fromAK8(
        *jet_ptrsAK8[0], *cleanedJets_fromAK8[0], calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti
      );
      const double HadTop_pt_semi_boosted_fromAK8 = (jet_ptrsAK8[0] -> p4() + cleanedJets_fromAK8[0] -> p4()).pt();

      snm->read(bdtResult_semi_boosted.at(kXGB_semi_boosted_AK8_no_kinFit), FloatVariableType::HTT_semi_boosted_fromAK8);
      snm->read(HadTop_pt_semi_boosted_fromAK8,                             FloatVariableType::HadTop_pt_semi_boosted_fromAK8);
    }

    if(preselLeptons.size() > 1)
    {
      const double massL = comp_MT_met_lep1(preselLeptons[0]->p4() + preselLeptons[1]->p4(), met.pt(), met.phi());
      snm->read(massL, FloatVariableType::massL);
    }

    double lep1_conePt         = 0.;
    double lep2_conePt         = 0.;
    double sum_lep_charge_2lss = 0.;
    double sum_lep_charge_3l   = 0.;
    double mT_met_lep3         = 0.;
    double mindr_lep3_jet      = 0.;
    double lep3_conePt         = 0.;
    double max_lep_eta_2lss    = 0.;
    double max_lep_eta_3l      = 0.;
    double mT_met_lep1         = 0.;
    double mindr_lep1_jet      = 0.;
    double mindr_lep2_jet      = 0.;
    double mT_met_lep2         = 0.;

    if(! selLeptons.empty())
    {
      const RecoLepton * selLepton_lead = selLeptons[0];
      mindr_lep1_jet = comp_mindr_lep1_jet(*selLepton_lead, selJets);
      mT_met_lep1    = comp_MT_met_lep1(selLepton_lead->p4(), met.pt(), met.phi());
      double mTauTauVis1_sel  = ! selHadTaus.empty()      ?
        (selLepton_lead->p4() + selHadTaus.at(0)->p4()).mass() :
        snm->placeholder_value
      ;

      snm->read(mindr_lep1_jet,  FloatVariableType::mindr_lep1_jet);
      snm->read(mT_met_lep1,     FloatVariableType::mT_met_lep1);
      snm->read(mTauTauVis1_sel, FloatVariableType::mvis_l1tau);

      if(selLeptons.size() > 1)
      {
        const RecoLepton * selLepton_sublead = selLeptons[1];
        mindr_lep2_jet = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
        mT_met_lep2    = comp_MT_met_lep2(selLepton_sublead->p4(), met.pt(), met.phi());
        const double dR_leps        = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
        double mTauTauVis2_sel      = ! selHadTaus.empty()  ?
          (selLepton_sublead->p4() + selHadTaus.at(0)->p4()).mass() :
          snm->placeholder_value
        ;

        snm->read(mindr_lep2_jet,  FloatVariableType::mindr_lep2_jet);
        snm->read(mT_met_lep2,     FloatVariableType::mT_met_lep2);
        snm->read(dR_leps,         FloatVariableType::dr_leps);
        snm->read(mTauTauVis2_sel, FloatVariableType::mvis_l2tau);

        lep1_conePt = comp_lep1_conePt(*selLepton_lead);
        lep2_conePt = comp_lep2_conePt(*selLepton_sublead);
        sum_lep_charge_2lss = selLepton_lead->charge() + selLepton_sublead->charge();
        max_lep_eta_2lss = std::max(selLepton_lead -> absEta(), selLepton_sublead -> absEta());

        if(selLeptons.size() > 2)
        {
          const RecoLepton * selLepton_third = selLeptons[2];
          mT_met_lep3    = comp_MT_met_lep3(selLepton_third->p4(), met.pt(), met.phi());
          mindr_lep3_jet = comp_mindr_lep3_jet(*selLepton_third, selJets);

          snm->read(mT_met_lep3,    FloatVariableType::mT_met_lep3);
          snm->read(mindr_lep3_jet, FloatVariableType::mindr_lep3_jet);

          lep3_conePt = comp_lep3_conePt(*selLepton_third);
          sum_lep_charge_3l = selLepton_lead->charge() + selLepton_sublead->charge() + selLepton_third->charge();
          max_lep_eta_3l = std::max({ selLepton_lead->absEta(), selLepton_sublead->absEta(), selLepton_third->absEta() });
        }
      }
    }

    const std::map<std::string, double> mvaInputs_2lss_ttH_tH_4cat_onlyTHQ_v4_TF = {
      { "avg_dr_jet",           ! selJets.empty() ? avg_dr_jet : 0 },
      { "ptmiss",               met.pt() },
      { "mbb_medium",           mbb },
      { "max_dr_jet",           ! selJets.empty() ? max_dr_jet : 0 },
      { "jet1_pt",              ! selJets.empty() ? selJets[0]->pt() : 0 },
      { "jet2_pt",              selJets.size() > 1 ? selJets[1]->pt() : 0 },
      { "jet3_pt",              selJets.size() > 2 ? selJets[2]->pt() : 0 },
      { "jet4_pt",              selJets.size() > 3 ? selJets[3]->pt() : 0 },
      { "max_lep_eta",          max_lep_eta_2lss },
      { "lep1_mT",              mT_met_lep1 },
      { "lep1_conept",          lep1_conePt },
      { "lep1_min_dr_jet",      TMath::Min(10., mindr_lep1_jet) },
      { "lep2_mT",              mT_met_lep2 },
      { "lep2_conept",          lep2_conePt },
      { "lep2_min_dr_jet",      TMath::Min(10., mindr_lep2_jet) },
      { "nJetForward",          selJetsForward.size() },
      { "jetForward1_pt",       ! selJetsForward.empty() ?  selJetsForward[0]->pt() : 0 },
      { "jetForward1_eta_abs",  ! selJetsForward.empty() ?  selJetsForward[0]->absEta() : -1 },
      { "res-HTT_CSVsort4rd",   HTT },
      { "HadTop_pt_CSVsort4rd", HadTop_pt },
      { "nJet",                 selJets.size() },
      { "nBJetLoose",           selBJets_loose.size() },
      { "nBJetMedium",          selBJets_medium.size() },
      { "nElectron",            selElectrons.size() },
      { "sum_lep_charge",       sum_lep_charge_2lss },
      { "mvaOutput_Hj_tagger",  mvaOutput_Hj_tagger },
    };
    const std::map<std::string, double> mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4 =
      mva_2lss_ttH_tH_4cat_onlyTHQ_v4(mvaInputs_2lss_ttH_tH_4cat_onlyTHQ_v4_TF)
    ;

    snm->read(mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4.at("predictions_ttH"),  FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH);
    snm->read(mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4.at("predictions_tH"),   FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_tH);
    snm->read(mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4.at("predictions_ttW"),  FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW);
    snm->read(mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4.at("predictions_rest"), FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_rest);

    const std::map<std::string, double> mvaInputs_3l_ttH_tH_3cat_v8_TF = {
      { "avg_dr_jet",           ! selJets.empty() ? avg_dr_jet : 0 },
      { "ptmiss",               met.pt() },
      { "mbb_medium",           selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : 0 },
      { "jet1_pt",              ! selJets.empty() ? selJets[0]->pt() : 0 },
      { "jet2_pt",              selJets.size() > 1 ? selJets[1]->pt() : 0 },
      { "jet3_pt",              selJets.size() > 2 ?  selJets[2]->pt() : 0 },
      { "jet4_pt",              selJets.size() > 3 ?  selJets[3]->pt() : 0 },
      { "max_lep_eta",          max_lep_eta_3l },
      { "lep1_mT",              mT_met_lep1 },
      { "lep1_conept",          lep1_conePt },
      { "lep2_mT",              mT_met_lep2 },
      { "lep2_conept",          lep2_conePt },
      { "lep3_mT",              mT_met_lep3 },
      { "lep3_conept",          lep3_conePt },
      { "jetForward1_pt",       ! selJetsForward.empty() ? selJetsForward[0]->pt() : 0 },
      { "res-HTT_CSVsort4rd",   HTT },
      { "HadTop_pt_CSVsort4rd", HadTop_pt },
      { "nJet",                 selJets.size() },
      { "nJetForward",          selJetsForward.size() },
      { "nBJetLoose",           selBJets_loose.size() },
      { "nBJetMedium",          selBJets_medium.size() },
      { "nElectron",            selElectrons.size() },
      { "sum_lep_charge",       sum_lep_charge_3l },
    };
    const std::map<std::string, double> mvaOutput_3l_ttH_tH_3cat_v8 =
      mva_3l_ttH_tH_3cat_v8_TF(mvaInputs_3l_ttH_tH_3cat_v8_TF)
    ;

    snm->read(mvaOutput_3l_ttH_tH_3cat_v8.at("predictions_ttH"),  FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_ttH);
    snm->read(mvaOutput_3l_ttH_tH_3cat_v8.at("predictions_tH"),   FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_tH);
    snm->read(mvaOutput_3l_ttH_tH_3cat_v8.at("predictions_rest"), FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_rest);

    if(selLeptons.size() > 3)
    {
      const RecoLepton * selLepton_fourth = selLeptons[3];
      const double mT_met_lep4    = comp_MT_met_lep3(selLepton_fourth->p4(), met.pt(), met.phi());
      const double mindr_lep4_jet = comp_mindr_lep4_jet(*selLepton_fourth, selJets);

      snm->read(mT_met_lep4,    FloatVariableType::mT_met_lep4);
      snm->read(mindr_lep4_jet, FloatVariableType::mindr_lep4_jet);
    }

    if(! selHadTaus.empty())
    {
      const RecoHadTau * selHadTau = selHadTaus[0];

      const double mindr_tau_jet = comp_mindr_hadTau1_jet(*selHadTau, selJets);

      const double dR_l0tau = ! selLeptons.empty()      ?
        deltaR(selLeptons.at(0)->p4(), selHadTau->p4()) :
        snm->placeholder_value
      ;
      const double dR_l1tau = selLeptons.size() > 1     ?
        deltaR(selLeptons.at(1)->p4(), selHadTau->p4()) :
        snm->placeholder_value
      ;
      const double dR_l2tau = selLeptons.size() > 2     ?
        deltaR(selLeptons.at(2)->p4(), selHadTau->p4()) :
        snm->placeholder_value
      ;


      snm->read(mindr_tau_jet, FloatVariableType::mindr_tau1_jet);
      snm->read(dR_l0tau,      FloatVariableType::dr_lep1_tau1);
      snm->read(dR_l1tau,      FloatVariableType::dr_lep2_tau1);
      snm->read(dR_l2tau,      FloatVariableType::dr_lep3_tau1);
    }

    if(selHadTaus.size() > 1)
    {
      const RecoHadTau * selHadTau_lead    = selHadTaus[0];
      const RecoHadTau * selHadTau_sublead = selHadTaus[1];
      const double tt_deltaR      = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
      const double tt_mvis        = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();
      const double mindr_tau2_jet = comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets);

      snm->read(tt_deltaR,      FloatVariableType::dr_taus);
      snm->read(tt_mvis,        FloatVariableType::mTauTauVis);
      snm->read(mindr_tau2_jet, FloatVariableType::mindr_tau2_jet);
    }

    snm->fill();

    ++selectedEntries;
  }

  snm->write();

  std::cout << "max num. Entries = " << inputTree->getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree->getProcessedFileCount() << " file(s) (out of "
            << inputTree->getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << "\n\n";

  delete run_lumi_eventSelector;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete jetReaderAK8;
  delete metReader;

  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;

  delete genMatchToMuonReader;
  delete genMatchToElectronReader;
  delete genMatchToHadTauReader;
  delete genMatchToJetReader;

  delete inputTree;
  delete snm;

  clock.Show("analyze_inclusive");

  return EXIT_SUCCESS;
}
