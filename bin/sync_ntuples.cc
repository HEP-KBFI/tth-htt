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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorCutBased.h" // RecoMuonCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtag*
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_*
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_2tau_trigger.h"
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cout
#include <fstream> // std::ofstream

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton, kFR_3L, kFR_2tau, kFR_4L, kFR_3lepton, kFR_1tau };

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied
const bool apply_trigger_bits = false;

/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_SUCCESS;
  }
  std::cout << "<" << argv[0] << ">:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("syncNtuple");

  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string outputTreeName = cfg_analyze.getParameter<std::string>("outputTreeName");
  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const bool debug = cfg_analyze.getParameter<bool>("debug");

//--- declare data-taking period
  const int era = [&era_string, &argv]() -> int
  {
    if(era_string == "2017") return kEra_2017;
    else
      throw cms::Exception(argv[0])
        << "Invalid configuration parameter 'era' = " << era_string << '\n';
  }();
  
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("sync_ntuples") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  std::string jet_btagWeight_branch;
  bool isMC = true; //cfg_analyze.getParameter<bool>("isMC");
  if ( isMC ) {
    if ( era == kEra_2017 ) jet_btagWeight_branch = "Jet_btagSF_csvv2";
    else assert(0);
  }

  const int jetPt_option = RecoJetReader::kJetPt_central;
  //int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  //int lheScale_option = kLHE_scale_central;

  double lumiScale = cfg_analyze.getParameter<double>("lumiScale");

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  //bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  //bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  //bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  //bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  //bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");
  vstring triggerNames_1e1tau = cfg_analyze.getParameter<vstring>("triggers_1e1tau");
  std::vector<hltPath*> triggers_1e1tau = create_hltPaths(triggerNames_1e1tau);
  //bool use_triggers_1e1tau = cfg_analyze.getParameter<bool>("use_triggers_1e1tau");
  vstring triggerNames_1mu1tau = cfg_analyze.getParameter<vstring>("triggers_1mu1tau");
  std::vector<hltPath*> triggers_1mu1tau = create_hltPaths(triggerNames_1mu1tau);
  //bool use_triggers_1mu1tau = cfg_analyze.getParameter<bool>("use_triggers_1mu1tau");

  // triple lepton triggers
  vstring triggerNames_3e = cfg_analyze.getParameter<vstring>("triggers_3e");
  std::vector<hltPath*> triggers_3e = create_hltPaths(triggerNames_3e);
  //bool use_triggers_3e = cfg_analyze.getParameter<bool>("use_triggers_3e");
  vstring triggerNames_2e1mu = cfg_analyze.getParameter<vstring>("triggers_2e1mu");
  std::vector<hltPath*> triggers_2e1mu = create_hltPaths(triggerNames_2e1mu);
  //bool use_triggers_2e1mu = cfg_analyze.getParameter<bool>("use_triggers_2e1mu");
  vstring triggerNames_1e2mu = cfg_analyze.getParameter<vstring>("triggers_1e2mu");
  std::vector<hltPath*> triggers_1e2mu = create_hltPaths(triggerNames_1e2mu);
  //bool use_triggers_1e2mu = cfg_analyze.getParameter<bool>("use_triggers_1e2mu");
  vstring triggerNames_3mu = cfg_analyze.getParameter<vstring>("triggers_3mu");
  std::vector<hltPath*> triggers_3mu = create_hltPaths(triggerNames_3mu);
  //bool use_triggers_3mu = cfg_analyze.getParameter<bool>("use_triggers_3mu");

  /*bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_3e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3e");
  bool apply_offline_e_trigger_cuts_2e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e1mu");
  bool apply_offline_e_trigger_cuts_1e2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e2mu");
  bool apply_offline_e_trigger_cuts_3mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3mu");*/

  const std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_input = "  << selEventsFileName_input  << '\n'
            << "selEventsFileName_output = " << selEventsFileName_output << '\n';

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"                                                     ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" || hadTauSelection_part1 == "Fakeable_mcClosure" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"                                                     ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_2lss_1tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  
  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_1tau(apply_hadTauGenMatching);

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << '\n';
  const unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  const std::string outputFileName = outputFile.file();

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(false, isMC, false);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  for(const std::vector<hltPath*> hltPaths: {
       triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu, triggers_1e1tau, triggers_1mu1tau,
       triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu
     })
  {
    inputTree -> registerReader(hltPaths);
  }
  
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, "MET");
  metReader->setMEt_central_or_shift(RecoMEtReader::kMEt_central);
  inputTree -> registerReader(metReader);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "Muon", false);
  muonReader->set_HIP_mitigation(use_HIP_mitigation_mediumMuonId);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorCutBased cutBasedSelector(era); // KE: not needed in 2016 sync, but keep it
  RecoMuonCollectionSelectorMVABased mvaBasedSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, run_lumi_eventSelector != 0);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "Electron", false);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05); // NB! in analysis we have 0.3
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, debug);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorCutBased cutBasedElectronSelector(era); // KE: not needed in 2016 sync, but keep it
  RecoElectronCollectionSelectorMVABased mvaBasedElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, run_lumi_eventSelector != 0);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "Tau", false);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.4); // NB! in analysis we have 0.3
  RecoHadTauCollectionSelectorLoose hadTauSelector(era); // KE: Tight -> Loose
  hadTauSelector.set("dR03mvaLoose");

  /*if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);*/
  //fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  //fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");
  //std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::string central_or_shift = "central";
  
  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);
  Data_to_MC_CorrectionInterface_1l_2tau_trigger* dataToMCcorrectionInterface_1l_2tau_trigger = new Data_to_MC_CorrectionInterface_1l_2tau_trigger(cfg_dataToMCcorrectionInterface);  
  
  int applyFakeRateWeights = kFR_3L;
  
  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }
  
  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, "Jet", false);
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4); // NB! in analysis we *had* 0.5
  RecoJetCollectionSelector jetSelector(era);  

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("GenLep");
    inputTree -> registerReader(genLeptonReader);
    genHadTauReader = new GenHadTauReader("GenVisTau");
    inputTree -> registerReader(genHadTauReader);
    genJetReader = new GenJetReader("GenJet");
    inputTree -> registerReader(genJetReader);
    lheInfoReader = new LHEInfoReader();
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
  TMVAInterface mva_2lss_ttV(mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, 
    { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttbar;
  mvaInputVariables_2lss_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttbar.push_back("min(met_pt,400)");
  mvaInputVariables_2lss_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_ttbar.push_back("MT_met_lep1");
  TMVAInterface mva_2lss_ttbar(mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, 
    { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_2lss = get_mvaInputVariables(mvaInputVariables_2lss_ttV, mvaInputVariables_2lss_ttbar);
  std::map<std::string, double> mvaInputs_2lss;

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    trained by Arun for 2lss_1tau category 
  std::string mvaFileName_2lss_1tau_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttV;
  mvaInputVariables_2lss_1tau_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttV.push_back("lep1_conePt");
  mvaInputVariables_2lss_1tau_ttV.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttV.push_back("mT_lep1");
  mvaInputVariables_2lss_1tau_ttV.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttV.push_back("mTauTauVis1");
  mvaInputVariables_2lss_1tau_ttV.push_back("mTauTauVis2");
  TMVAInterface mva_2lss_1tau_ttV(mvaFileName_2lss_1tau_ttV, mvaInputVariables_2lss_1tau_ttV);

  std::string mvaFileName_2lss_1tau_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttbar;
  mvaInputVariables_2lss_1tau_ttbar.push_back("nJet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttbar.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttbar.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttbar.push_back("tau_pt");
  mvaInputVariables_2lss_1tau_ttbar.push_back("dr_lep1_tau");
  TMVAInterface mva_2lss_1tau_ttbar(mvaFileName_2lss_1tau_ttbar, mvaInputVariables_2lss_1tau_ttbar);
  
  std::vector<std::string> mvaInputVariables_2lss_1tau = get_mvaInputVariables(mvaInputVariables_2lss_1tau_ttV, mvaInputVariables_2lss_1tau_ttbar);
  std::map<std::string, double> mvaInputs_2lss_1tau;

  std::string inputFileName_mva_mapping_2lss_1tau = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_BDT_mapping_likelihood.root";
  TFile* inputFile_mva_mapping_2lss_1tau = openFile(LocalFileInPath(inputFileName_mva_mapping_2lss_1tau));
  TH2* mva_mapping_2lss_1tau = loadTH2(inputFile_mva_mapping_2lss_1tau, "hTargetBinning");

  /*
  std::string mvaFileName_2lss_1tau_ttV_wMEM = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttV_BDTGwMEM.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttV_wMEM;
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("lep1_conePt");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("mT_lep1");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("mTauTauVis1");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("mTauTauVis2");
  mvaInputVariables_2lss_1tau_ttV_wMEM.push_back("memOutput_LR");
  TMVAInterface mva_2lss_1tau_ttV_wMEM(mvaFileName_2lss_1tau_ttV_wMEM, mvaInputVariables_2lss_1tau_ttV_wMEM);

  std::string mvaFileName_2lss_1tau_ttbar_wMEM = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttbar_BDTGwMEM.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttbar_wMEM;
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("nJet");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("tau_pt");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("dr_lep1_tau");
  mvaInputVariables_2lss_1tau_ttbar_wMEM.push_back("memOutput_LR");
  TMVAInterface mva_2lss_1tau_ttbar_wMEM(mvaFileName_2lss_1tau_ttbar_wMEM, mvaInputVariables_2lss_1tau_ttbar_wMEM);

  std::vector<std::string> mvaInputVariables_2lss_1tau_wMEM = get_mvaInputVariables(mvaInputVariables_2lss_1tau_ttV_wMEM, mvaInputVariables_2lss_1tau_ttbar_wMEM);
  std::map<std::string, double> mvaInputs_2lss_1tau_wMEM;

  std::string inputFileName_mva_mapping_2lss_1tau_wMEM = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_BDTwMEM_mapping_likelihood.root";
  TFile* inputFile_mva_mapping_2lss_1tau_wMEM = openFile(LocalFileInPath(inputFileName_mva_mapping_2lss_1tau_wMEM));
  TH2* mva_mapping_2lss_1tau_wMEM = loadTH2(inputFile_mva_mapping_2lss_1tau_wMEM, "hTargetBinning");

  std::string mvaFileName_2lss_1tau_ttV_wMEMsepLR = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttV_BDTGwMEMsepLR.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttV_wMEMsepLR;
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("lep1_conePt");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("mT_lep1");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("mTauTauVis1");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("mTauTauVis2");
  mvaInputVariables_2lss_1tau_ttV_wMEMsepLR.push_back("memOutput_ttZ_LR");
  TMVAInterface mva_2lss_1tau_ttV_wMEMsepLR(mvaFileName_2lss_1tau_ttV_wMEMsepLR, mvaInputVariables_2lss_1tau_ttV_wMEMsepLR);

  std::string mvaFileName_2lss_1tau_ttbar_wMEMsepLR = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttbar_BDTGwMEMsepLR.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR;
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("nJet");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("lep2_conePt");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("tau_pt");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("dr_lep1_tau");
  mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR.push_back("memOutput_tt_LR");
  TMVAInterface mva_2lss_1tau_ttbar_wMEMsepLR(mvaFileName_2lss_1tau_ttbar_wMEMsepLR, mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR);

  std::vector<std::string> mvaInputVariables_2lss_1tau_wMEMsepLR = get_mvaInputVariables(mvaInputVariables_2lss_1tau_ttV_wMEMsepLR, mvaInputVariables_2lss_1tau_ttbar_wMEMsepLR);
  std::map<std::string, double> mvaInputs_2lss_1tau_wMEMsepLR;

  std::string inputFileName_mva_mapping_2lss_1tau_wMEMsepLR = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_BDTwMEMsepLR_mapping_likelihood.root";
  TFile* inputFile_mva_mapping_2lss_1tau_wMEMsepLR = openFile(LocalFileInPath(inputFileName_mva_mapping_2lss_1tau_wMEMsepLR));
  TH2* mva_mapping_2lss_1tau_wMEMsepLR = loadTH2(inputFile_mva_mapping_2lss_1tau_wMEMsepLR, "hTargetBinning");
  */

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

  SyncNtupleManager snm(outputFileName, outputTreeName);
  snm.initializeBranches();
  snm.initializeHLTBranches({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});

  int analyzedEntries = 0;
  int selectedEntries = 0;

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

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    snm.readRunLumiEvent(eventInfo.run, eventInfo.lumi, eventInfo.event);

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( true/*isMC*/ ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
    	    genLepton != genLeptons.end(); ++genLepton ) {
	      int abs_pdgId = std::abs(genLepton->pdgId());
	      if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	      else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }


//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
// CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> cutBasedMuons = cutBasedSelector(preselMuons);
    std::vector<const RecoMuon*> mvaBasedMuons = mvaBasedSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons = preselMuons;
    std::sort(preselMuons.begin(), preselMuons.end(), isHigherConePt);
    snm.read(preselMuons, fakeableMuons, cutBasedMuons, mvaBasedMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> cutBasedElectrons = cutBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> mvaBasedElectrons = mvaBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons = preselElectrons;
    std::sort(preselElectrons.begin(), preselElectrons.end(), isHigherConePt);
    snm.read(preselElectrons, fakeableElectrons, cutBasedElectrons, mvaBasedElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::sort(selHadTaus.begin(), selHadTaus.end(), isHigherPt);
    snm.read(selHadTaus);
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = [&]()
    {
      if(era == kEra_2017)
        return jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
      else
        throw cms::Exception(argv[0]) << "Invalid era = " << era;
    }();
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::sort(selJets.begin(), selJets.end(), isHigherPt);
    snm.read(selJets);

    RecoMEt met = metReader->read();


    if ( true/*isMC*/ ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- collect preselected leptons
    std::vector<const RecoLepton *> preselLeptons;
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherConePt);

//--- collect fakeable leptons
    std::vector<const RecoLepton *> fakeableLeptons;
    fakeableLeptons.reserve(fakeableElectrons.size() + fakeableMuons.size());
    fakeableLeptons.insert(fakeableLeptons.end(), fakeableElectrons.begin(), fakeableElectrons.end());
    fakeableLeptons.insert(fakeableLeptons.end(), fakeableMuons.begin(),     fakeableMuons.end());
    std::sort(fakeableLeptons.begin(), fakeableLeptons.end(), isHigherConePt);
    
    const RecoLepton * const lepton_lead = [&]()
    {
      if(era == kEra_2017 && fakeableLeptons.size() > 0)
        return fakeableLeptons[0];
      return static_cast<const RecoLepton * const>(0);
    }();
    const RecoLepton * const lepton_sublead = [&]()
    {
      if(era == kEra_2017 && fakeableLeptons.size() > 1)
        return fakeableLeptons[1];
      return static_cast<const RecoLepton * const>(0);
    }();
    const RecoLepton * const lepton3 = [&]()
    {
      if(era == kEra_2017 && fakeableLeptons.size() > 2)
        return fakeableLeptons[2];
      return static_cast<const RecoLepton * const>(0);
    }();
    
    int lepton_lead_type = -1;
    double lepton_lead_pt = 0.;
    double lepton_lead_eta = 0.; 
        
    if(lepton_lead != 0){
      lepton_lead_type = getLeptonType(lepton_lead->pdgId());
      lepton_lead_pt = lepton_lead->pt();;
      lepton_lead_eta = lepton_lead->eta(); 
    }
    
    int lepton_sublead_type = -1;
    double lepton_sublead_pt = 0.;
    double lepton_sublead_eta = 0.; 
    
    if (lepton_sublead != 0){
      lepton_sublead_type = getLeptonType(lepton_sublead->pdgId());
      lepton_sublead_pt = lepton_sublead->pt();
      lepton_sublead_eta = lepton_sublead->eta();
    }
    
    int lepton3_type = -1;
    double lepton3_pt = 0.;
    double lepton3_eta = 0.;
    
    if (lepton3 != 0){
      lepton3_type = getLeptonType(lepton3->pdgId());
      lepton3_pt = lepton3->pt();
      lepton3_eta = lepton3->eta();
    }

    dataToMCcorrectionInterface->setLeptons(
	      lepton_lead_type, lepton_lead_pt, lepton_lead_eta, 
    	  lepton_sublead_type, lepton_sublead_pt, lepton_sublead_eta,
    	  lepton3_type, lepton3_pt, lepton3_eta
    );
    
    double weight_btag = 1.;
    if( isMC){
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	          jet != selJets.end(); ++jet ) {
	      weight_btag *= (*jet)->BtagWeight();
	      
      }
    }
    
    int tau_lead_type = -1;
    double tau_lead_pt = 0.;
    double tau_lead_eta = 0.; 
    int tau_sublead_type = -1;
    double tau_sublead_pt = 0.;
    double tau_sublead_eta = 0.; 
    int tau_3_type = -1;
    double tau_3_pt = 0.;
    double tau_3_eta = 0.; 
    
    if(selHadTaus.size() > 2){      
      tau_3_type = getHadTau_genPdgId(selHadTaus[2]);
      tau_3_pt = selHadTaus[2]->pt();;
      tau_3_eta = selHadTaus[2]->eta(); 
    }if(selHadTaus.size() > 1){
      tau_sublead_type = getHadTau_genPdgId(selHadTaus[1]);
      tau_sublead_pt = selHadTaus[1]->pt();;
      tau_sublead_eta = selHadTaus[1]->eta(); 
    }
    if(selHadTaus.size() > 0){
      tau_lead_type = getHadTau_genPdgId(selHadTaus[0]);
      tau_lead_pt = selHadTaus[0]->pt();;
      tau_lead_eta = selHadTaus[0]->eta(); 
    }
    
    dataToMCcorrectionInterface->setHadTaus(tau_lead_type, tau_lead_pt, tau_lead_eta,
        tau_sublead_type, tau_sublead_pt, tau_sublead_eta,
        tau_3_type, tau_3_pt, tau_3_eta
    );

    
    
//--- compute MHT and linear MET discriminant (met_LD)
    LV mht_p4(0,0,0,0);
    for(const RecoJet * & jet: selJets)             mht_p4 += jet -> p4();
    for(const RecoLepton * & lepton: preselLeptons) mht_p4 += lepton -> p4();
    for(const RecoHadTau * & hadTau: selHadTaus)    mht_p4 += hadTau -> p4();
    const Double_t met_LD = met_coef*met.p4().pt() + mht_coef*mht_p4.pt();

    snm.read(met.pt(),      FloatVariableType::PFMET);
    snm.read(0.,     FloatVariableType::PFMETphi);
    snm.read(mht_p4.pt(), FloatVariableType::MHT);
    snm.read(met_LD,      FloatVariableType::metLD);
    snm.read({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});

    double mTauTauVis1_sel = -99;
    double mTauTauVis2_sel = -99;
    if(lepton_lead != 0 && selHadTaus.size()>0)
      mTauTauVis1_sel = (lepton_lead->p4() + selHadTaus[0]->p4()).mass();
    if(lepton_sublead != 0 && selHadTaus.size()>0)
      mTauTauVis2_sel = (lepton_sublead->p4() + selHadTaus[0]->p4()).mass();

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    std::cout << lepton_lead << " " << lepton_sublead << std::endl;
    if(lepton_sublead !=0){
      mvaInputs_2lss["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(lepton_lead->eta()), std::fabs(lepton_sublead->eta()));
      mvaInputs_2lss["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*lepton_sublead, selJets);
      mvaInputs_2lss["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*lepton_sublead);
      std::cout << "asi" <<std::endl;
    }
    if(lepton_lead !=0){
      mvaInputs_2lss["MT_met_lep1"]                = comp_MT_met_lep1(lepton_lead->cone_p4(), met.pt(), met.phi());
      mvaInputs_2lss["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*lepton_lead, selJets);
      mvaInputs_2lss["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*lepton_lead);
    }  
    mvaInputs_2lss["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs_2lss["min(met_pt,400)"]            = std::min((Double_t)met.pt(), 400.);
    mvaInputs_2lss["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);
    
    check_mvaInputs(mvaInputs_2lss, eventInfo.run, eventInfo.lumi, eventInfo.event);
    //for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_2lss.begin();
    //	    mvaInput != mvaInputs_2lss.end(); ++mvaInput ) {
    //  std::cout << " " << mvaInput->first << " = " << mvaInput->second << std::endl;
    //}
    
    double mvaOutput_2lss_ttV = -99;
    double mvaOutput_2lss_ttbar = -99;
    if (lepton_sublead !=0){
      mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs_2lss);
      //std::cout << "mvaOutput_2lss_ttV = " << mvaOutput_2lss_ttV << std::endl;
      mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs_2lss);
      //std::cout << "mvaOutput_2lss_ttbar = " << mvaOutput_2lss_ttbar << std::endl;
    }

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 () of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_2lss = -1;
    if ( era == kEra_2017 ) {
      if      ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.4 ) mvaDiscr_2lss = 7.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.1 ) mvaDiscr_2lss = 6.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV <= +0.1 ) mvaDiscr_2lss = 5.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV >  +0.3 ) mvaDiscr_2lss = 4.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV <= +0.3 ) mvaDiscr_2lss = 3.;
      else if ( mvaOutput_2lss_ttbar > -0.2                               ) mvaDiscr_2lss = 2.;
      else                                                                  mvaDiscr_2lss = 1.;
    } else assert(0);
    std::cout << "mvaDiscr_2lss = " << mvaDiscr_2lss << std::endl;
    //std::cout << std::endl;

    /*MEMOutput_2lss_1tau memOutput_2lss_1tau_matched;
    if ( memReader ) {
      std::vector<MEMOutput_2lss_1tau> memOutputs_2lss_1tau = memReader->read();
      for ( std::vector<MEMOutput_2lss_1tau>::const_iterator memOutput_2lss_1tau = memOutputs_2lss_1tau.begin();
	    memOutput_2lss_1tau != memOutputs_2lss_1tau.end(); ++memOutput_2lss_1tau ) {
        const double selLepton_lead_dR = deltaR(
          selLepton_lead->eta(), selLepton_lead->phi(), 
	  memOutput_2lss_1tau->leadLepton_eta(), memOutput_2lss_1tau->leadLepton_phi());
        if ( selLepton_lead_dR > 1.e-2 ) continue;
        const double selLepton_sublead_dR = deltaR(
          selLepton_sublead->eta(), selLepton_sublead->phi(), 
	  memOutput_2lss_1tau->subleadLepton_eta(), memOutput_2lss_1tau->subleadLepton_phi());
        if ( selLepton_sublead_dR > 1.e-2 ) continue;
        const double selHadTau_dR = deltaR(
          selHadTau->eta(), selHadTau->phi(),
          memOutput_2lss_1tau->hadTau_eta(), memOutput_2lss_1tau->hadTau_phi());
        if ( selHadTau_dR > 1.e-2 ) continue;
        memOutput_2lss_1tau_matched = (*memOutput_2lss_1tau);
        break;
      }
      if ( !memOutput_2lss_1tau_matched.is_initialized() ) {
        std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << '\n'
                  << "No MEMOutput_2lss_1tau object found for:\n"
                  << "\tselLepton_lead: pT = " << selLepton_lead->pt()
                  << ", eta = "                << selLepton_lead->eta()
                  << ", phi = "                << selLepton_lead->phi()
                  << ", pdgId = "              << selLepton_lead->pdgId() << '\n'
                  << "\tselLepton_sublead: pT = " << selLepton_sublead->pt()
                  << ", eta = "                   << selLepton_sublead->eta()
                  << ", phi = "                   << selLepton_sublead->phi()
                  << ", pdgId = "                 << selLepton_sublead->pdgId() << '\n'
                  << "\tselHadTau: pT = " << selHadTau->pt()
                  << ", eta = "           << selHadTau->eta()
                  << ", phi = "           << selHadTau->phi() << '\n'
                  << "Number of MEM objects read: " << memOutputs_2lss_1tau.size() << '\n';
        if ( memOutputs_2lss_1tau.size() ) {
          for ( unsigned mem_idx = 0; mem_idx < memOutputs_2lss_1tau.size(); ++mem_idx ) {
            std::cout << "\t#" << mem_idx << " mem object;\n"
                      << "\t\tlead lepton eta = " << memOutputs_2lss_1tau[mem_idx].leadLepton_eta()
                      << "; phi = "               << memOutputs_2lss_1tau[mem_idx].leadLepton_phi() << '\n'
                      << "\t\tsublead lepton eta = " << memOutputs_2lss_1tau[mem_idx].subleadLepton_eta()
                      << "; phi = "                  << memOutputs_2lss_1tau[mem_idx].subleadLepton_phi() << '\n'
                      << "\t\thadronic tau eta = " << memOutputs_2lss_1tau[mem_idx].hadTau_eta()
                      << "; phi = "                << memOutputs_2lss_1tau[mem_idx].hadTau_phi() << '\n';
	  }
	} else {
	  std::cout << "Event contains no MEM objects whatsoever !!\n";
	}
      }
    }

    double memOutput_LR = ( memOutput_2lss_1tau_matched.isValid() && !memOutput_2lss_1tau_matched.errorFlag() ) ? memOutput_2lss_1tau_matched.LR() : -1.;
    double memOutput_ttZ_LR = ( memOutput_2lss_1tau_matched.isValid_ttZ_LR() && !memOutput_2lss_1tau_matched.errorFlag_ttZ_LR() ) ? memOutput_2lss_1tau_matched.ttZ_LR() : -1.;
    double memOutput_ttbar_LR = ( memOutput_2lss_1tau_matched.isValid_ttbar_LR() && !memOutput_2lss_1tau_matched.errorFlag_ttbar_LR() ) ? memOutput_2lss_1tau_matched.LR() : -1.;

    Double_t memDiscr = getSF_from_TH2(mem_mapping, memOutput_ttbar_LR, memOutput_ttZ_LR);*/

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar trained by Arun for 2lss_1tau category
    mvaInputs_2lss_1tau["avg_dr_jet"]                                            = comp_avg_dr_jet(selJets);
    //mvaInputs_2lss_1tau["dr_lep2_tau"]                                           = deltaR(selLepton_sublead->p4(), selHadTau->p4());
    //mvaInputs_2lss_1tau["htmiss"]                                                = mht_p4.pt();
    //mvaInputs_2lss_1tau["lep1_pt"]                                               = selLepton_lead->pt();
    //mvaInputs_2lss_1tau["lep2_pt"]                                               = selLepton_sublead->pt();    
    //mvaInputs_2lss_1tau["mindr_tau_jet" ]                                        = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets));
    //mvaInputs_2lss_1tau["mT_lep2"]                                               = comp_MT_met_lep2(selLepton_sublead->p4(), met.pt(), met.phi());
    mvaInputs_2lss_1tau["mTauTauVis1"]                                           = mTauTauVis1_sel;
    mvaInputs_2lss_1tau["mTauTauVis2"]                                           = mTauTauVis2_sel;
    mvaInputs_2lss_1tau["nJet"]                                                  = selJets.size();
    //mvaInputs_2lss_1tau["ptmiss"]                                                = met.pt();
    //mvaInputs_2lss_1tau["TMath::Abs(lep1_eta)"]                                  = selLepton_lead->absEta();
    //mvaInputs_2lss_1tau["TMath::Abs(lep2_eta)"]                                  = selLepton_sublead->absEta();
    //mvaInputs_2lss_1tau["TMath::Abs(tau_eta)"]                                   = selHadTau->absEta();
    if(lepton_sublead !=0){    
      mvaInputs_2lss_1tau["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = TMath::Max(lepton_lead->absEta(), lepton_sublead->absEta());
      mvaInputs_2lss_1tau["dr_leps"]                                               = deltaR(lepton_lead->p4(), lepton_sublead->p4());
      mvaInputs_2lss_1tau["lep2_conePt"]                                           = lepton_sublead->cone_pt();
      mvaInputs_2lss_1tau["mindr_lep2_jet"]                                        = TMath::Min(10., comp_mindr_lep2_jet(*lepton_sublead, selJets));
    }
    if(lepton_lead !=0){
      mvaInputs_2lss_1tau["lep1_conePt"]                                           = lepton_lead->cone_pt();
      if(selHadTaus.size() > 0)
        mvaInputs_2lss_1tau["dr_lep1_tau"]                                           = deltaR(lepton_lead->p4(), selHadTaus[0]->p4());
      mvaInputs_2lss_1tau["mindr_lep1_jet"]                                        = TMath::Min(10., comp_mindr_lep1_jet(*lepton_lead, selJets));
      mvaInputs_2lss_1tau["mT_lep1"]                                               = comp_MT_met_lep1(lepton_lead->p4(), met.pt(), met.phi());
    }
    if(selHadTaus.size() > 0)
      mvaInputs_2lss_1tau["tau_pt"]                                                = selHadTaus[0]->pt();
    

    Double_t mvaDiscr_2lss_1tau = -1.;
    if (lepton_sublead !=0){
      check_mvaInputs(mvaInputs_2lss_1tau, eventInfo.run, eventInfo.lumi, eventInfo.event);
      //for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_2lss.begin();
      //	    mvaInput != mvaInputs_2lss.end(); ++mvaInput ) {
      //  std::cout << " " << mvaInput->first << " = " << mvaInput->second << std::endl;
      //}

      double mvaOutput_2lss_1tau_ttV = mva_2lss_1tau_ttV(mvaInputs_2lss_1tau);
      double mvaOutput_2lss_1tau_ttbar = mva_2lss_1tau_ttbar(mvaInputs_2lss_1tau);     
      mvaDiscr_2lss_1tau = getSF_from_TH2(mva_mapping_2lss_1tau, mvaOutput_2lss_1tau_ttbar, mvaOutput_2lss_1tau_ttV) + 1.;
    }
    std::cout << "mvaDiscr_2lss_1tau = " << mvaDiscr_2lss_1tau << std::endl;

    //mvaInputs_2lss_1tau_wMEM = mvaInputs_2lss_1tau;
    //mvaInputs_2lss_1tau_wMEM["memOutput_LR"] = memOutput_LR;
    
    //double mvaOutput_2lss_1tau_ttV_wMEM = mva_2lss_1tau_ttV_wMEM(mvaInputs_2lss_1tau_wMEM);
    //double mvaOutput_2lss_1tau_ttbar_wMEM = mva_2lss_1tau_ttbar_wMEM(mvaInputs_2lss_1tau_wMEM); 
    //Double_t mvaDiscr_2lss_1tau_wMEM = getSF_from_TH2(mva_mapping_2lss_1tau_wMEM, mvaOutput_2lss_1tau_ttbar_wMEM, mvaOutput_2lss_1tau_ttV_wMEM) + 1.;

    /*mvaInputs_2lss_1tau_wMEMsepLR = mvaInputs_2lss_1tau;
    mvaInputs_2lss_1tau_wMEMsepLR["memOutput_ttZ_LR"] = memOutput_ttZ_LR;
    mvaInputs_2lss_1tau_wMEMsepLR["memOutput_tt_LR"] = memOutput_ttbar_LR;

    double mvaOutput_2lss_1tau_ttV_wMEMsepLR = mva_2lss_1tau_ttV_wMEMsepLR(mvaInputs_2lss_1tau_wMEMsepLR);
    double mvaOutput_2lss_1tau_ttbar_wMEMsepLR = mva_2lss_1tau_ttbar_wMEMsepLR(mvaInputs_2lss_1tau_wMEMsepLR); 
    Double_t mvaDiscr_2lss_1tau_wMEMsepLR = getSF_from_TH2(mva_mapping_2lss_1tau_wMEMsepLR, mvaOutput_2lss_1tau_ttbar_wMEMsepLR, mvaOutput_2lss_1tau_ttV_wMEMsepLR) + 1.;
    */
    
    snm.read(mvaInputs_2lss_1tau);
    mvaInputs_2lss_1tau.clear();
    
    //selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch][idxSelHadTau_genMatch];
    //assert(selHistManager != 0);
    
    /*double evtWeight_pp = evtWeight;
    double evtWeight_mm = evtWeight;
    if ( leptonChargeSelection == kOS ) {
      double prob_chargeMisId_lead = prob_chargeMisId(getLeptonType(preselLepton_lead->pdgId()), preselLepton_lead->pt(), preselLepton_lead->eta());
      double prob_chargeMisId_sublead = prob_chargeMisId(getLeptonType(preselLepton_sublead->pdgId()), preselLepton_sublead->pt(), preselLepton_sublead->eta());

      evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);

      if ( preselLepton_lead->charge() < 0 && preselLepton_sublead->charge() > 0 ) {
	evtWeight_pp *= prob_chargeMisId_lead;
	evtWeight_mm *= prob_chargeMisId_sublead;
      }
      if ( preselLepton_lead->charge() > 0 && preselLepton_sublead->charge() < 0 ) {
	evtWeight_pp *= prob_chargeMisId_sublead;
	evtWeight_mm *= prob_chargeMisId_lead;
      }
    }*/
    
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherConePt);
    const RecoLepton* selLepton_lead = nullptr;
    const RecoLepton* selLepton_sublead = nullptr;
    const RecoLepton* selLepton_third = nullptr;
    if (selLeptons.size() > 0){
      selLepton_lead = selLeptons[0];
      if (selLeptons.size() > 1)
        selLepton_sublead = selLeptons[1];
      if (selLeptons.size() > 2)
        selLepton_third = selLeptons[2];
    }
    double weight_fakeRate = 1.;
    //dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      
    if ( applyFakeRateWeights == kFR_3L and selLeptons.size() > 1) {
      double prob_fake_lepton_lead = 1.;
      if      ( std::abs(selLepton_lead->pdgId()) == 11 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->pt(), selLepton_lead->absEta());
      else if ( std::abs(selLepton_lead->pdgId()) == 13 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->pt(), selLepton_lead->absEta());
      else if (selLeptons.size() == 0) prob_fake_lepton_lead = 1.;
      else assert(0);
      bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
      double prob_fake_lepton_sublead = 1.;
      
      if      ( std::abs(selLepton_sublead->pdgId()) == 11 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->pt(), selLepton_sublead->absEta());
      else if ( std::abs(selLepton_sublead->pdgId()) == 13 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->pt(), selLepton_sublead->absEta());
      else if (selLeptons.size() == 1) prob_fake_lepton_sublead = 1.;
      else assert(0);
      
      bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
      if(selHadTaus.size() > 0){
        const RecoHadTau* selHadTau = selHadTaus[0];
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTaus);
        weight_fakeRate = getWeight_3L(
          prob_fake_lepton_lead, passesTight_lepton_lead, 
          prob_fake_lepton_sublead, passesTight_lepton_sublead, 
          prob_fake_hadTau, passesTight_hadTau);
      }
    }
    else if ( applyFakeRateWeights == kFR_2tau && selHadTaus.size() > 1) {
      double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(tau_lead_pt, tau_lead_eta);
      bool passesTight_hadTau_lead = isMatched(*selHadTaus[0], tightHadTaus);
      double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(tau_sublead_pt, tau_sublead_eta);
      bool passesTight_hadTau_sublead = isMatched(*selHadTaus[1], tightHadTaus);
      weight_fakeRate = getWeight_2L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead, 
      	prob_fake_hadTau_sublead, passesTight_hadTau_sublead);
    }
    else if ( applyFakeRateWeights == kFR_2lepton) {
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
      weight_fakeRate = getWeight_2L(
        prob_fake_lepton_lead, passesTight_lepton_lead, 
      	prob_fake_lepton_sublead, passesTight_lepton_sublead);
    } 
    else if ( applyFakeRateWeights == kFR_4L && selLeptons.size() > 2 && selHadTaus.size() > 0) {
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
      double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTaus[0]->pt(), selHadTaus[0]->absEta());
      bool passesTight_hadTau = isMatched(*selHadTaus[1], tightHadTaus);
      weight_fakeRate = getWeight_4L(
          prob_fake_lepton_lead, passesTight_lepton_lead, 
	        prob_fake_lepton_sublead, passesTight_lepton_sublead, 
	        prob_fake_lepton_third, passesTight_lepton_third, 
	        prob_fake_hadTau, passesTight_hadTau);      
    } else if ( applyFakeRateWeights == kFR_3lepton ) {
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
      /*if ( isDEBUG ) {
	      std::cout << "leading lepton: cone_pT = " << selLepton_lead->cone_pt() << ", absEta = " << selLepton_lead->absEta() << ", pdgId = " << selLepton_lead->pdgId() << ","
		        << " p = " << prob_fake_lepton_lead << ", passesTight = " << passesTight_lepton_lead << std::endl;
	      std::cout << "subleading lepton: cone_pT = " << selLepton_sublead->cone_pt() << ", absEta = " << selLepton_sublead->absEta() << ", pdgId = " << selLepton_sublead->pdgId() << ","
		        << " p = " << prob_fake_lepton_sublead << ", passesTight = " << passesTight_lepton_sublead << std::endl;
	      std::cout << "third lepton: cone_pT = " << selLepton_third->cone_pt() << ", absEta = " << selLepton_third->absEta() << ", pdgId = " << selLepton_third->pdgId() << ","
		        << " p = " << prob_fake_lepton_third << ", passesTight = " << passesTight_lepton_third << std::endl;
	      std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
      } */     
    } else if ( applyFakeRateWeights == kFR_1tau && selHadTaus.size() > 0) {
      double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTaus[0]->pt(), selHadTaus[0]->absEta());
      weight_fakeRate = prob_fake_hadTau;      
    }
    
    
    double triggerSF_weight = 1.;
    

    if(lepton_sublead == 0 && selHadTaus.size() > 1){
      bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
      bool isTriggered_1e1tau = hltPaths_isTriggered(triggers_1e1tau) || (isMC && !apply_trigger_bits);
      bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
      bool isTriggered_1mu1tau = hltPaths_isTriggered(triggers_1mu1tau) || (isMC && !apply_trigger_bits);
      
      dataToMCcorrectionInterface_1l_2tau_trigger->setLeptons(lepton_lead_type, lepton_lead_pt, lepton_lead_eta);
      dataToMCcorrectionInterface_1l_2tau_trigger->setHadTaus(
        selHadTaus[0]->pt(), selHadTaus[0]->eta(), selHadTaus[0]->phi(),
        selHadTaus[1]->pt(), selHadTaus[1]->eta(), selHadTaus[1]->phi());
      dataToMCcorrectionInterface_1l_2tau_trigger->setTriggerBits(isTriggered_1e, isTriggered_1e1tau, isTriggered_1mu, isTriggered_1mu1tau);
      triggerSF_weight *= dataToMCcorrectionInterface_1l_2tau_trigger->getSF_triggerEff();
    }
    else
      triggerSF_weight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      
    double leptonSF_weight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();
    //std::cout << "lepton_ID_and_Iso_Loose" << dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose() << std::endl;
    //leptonSF_weight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
    //std::cout << "etotauFR" << dataToMCcorrectionInterface->getSF_eToTauFakeRate() << std::endl;
    //leptonSF_weight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
    //std::cout << "mutotauFR" << dataToMCcorrectionInterface->getSF_muToTauFakeRate() << std::endl;
    //leptonSF_weight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
    //std::cout << "hadtauIDIso" << dataToMCcorrectionInterface->getSF_hadTauID_and_Iso() << std::endl;
    //double hadTauSF_weight = dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();

    
    //--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
    //    to also pass the tight identification and isolation criteria
    if ( isMC ) {
      if ( leptonSelection == kFakeable ) {
	        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
	        //std::cout << "fakeable_to_loose" << dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose() << std::endl;
      } else if ( leptonSelection == kTight ) {
          if (lepton3 != 0 || lepton_sublead == 0 )
            leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();
          else
            leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
          //std::cout << "fakeable_to_tight" << dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge() << std::endl;
      }
    }
    
    
    double hadTauSF_weight = dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
    hadTauSF_weight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
    hadTauSF_weight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
    if ( isMC && selHadTaus.size() > 0 && apply_hadTauFakeRateSF && hadTauSelection == kTight && !(selHadTaus[0]->genHadTau() || selHadTaus[0]->genLepton()) ) {
      hadTauSF_weight *= jetToTauFakeRateInterface->getSF_lead(selHadTaus[0]->pt(), selHadTaus[0]->absEta());
    }
    //double MC_weight = pileupWeight * triggerSF_weight * leptonSF_weight * weight_btag * hadTauSF_weight * genWeight;

    snm.read(boost::math::sign(eventInfo.genWeight),   FloatVariableType::MC_weight);
    snm.read(weight_fakeRate,   FloatVariableType::FR_weight);
    snm.read(triggerSF_weight,   FloatVariableType::triggerSF_weight);
    snm.read(leptonSF_weight,   FloatVariableType::leptonSF_weight);
    snm.read(weight_btag,   FloatVariableType::bTagSF_weight);
    snm.read(eventInfo.pileupWeight,   FloatVariableType::PU_weight);
    snm.read(hadTauSF_weight,   FloatVariableType::hadTauSF_weight);
    snm.read(lumiScale,   FloatVariableType::lumiScale);
    //snm.read(genWeight,   FloatVariableType::genWeight);
    snm.fill();
    
    (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    ++selectedEntries;    
  }
  snm.write();
  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << '\n';

  delete run_lumi_eventSelector;
  delete selEventsFile;
  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);
  hltPaths_delete(triggers_1e1tau);
  hltPaths_delete(triggers_1mu1tau);
  hltPaths_delete(triggers_3e);
  hltPaths_delete(triggers_2e1mu);
  hltPaths_delete(triggers_1e2mu);
  hltPaths_delete(triggers_3mu);

  delete inputTree;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
}
