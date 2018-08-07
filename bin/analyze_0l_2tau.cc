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
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
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
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_2tau.h" // EvtHistManager_0l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // get*_option()
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_2tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h" // Data_to_MC_CorrectionInterface_0l_2tau_trigger
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"

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
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_2tau };

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

/**
 * @brief Produce datacard and control plots for 0l_2tau category.
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

  std::cout << "<analyze_0l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_0l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_0l_2tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_0l_2tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_2tau = cfg_analyze.getParameter<vstring>("triggers_2tau");
  std::vector<hltPath*> triggers_2tau = create_hltPaths(triggerNames_2tau);
  bool use_triggers_2tau = cfg_analyze.getParameter<bool>("use_triggers_2tau");

  double lep_mva_cut = cfg_analyze.getParameter<double>("lep_mva_cut"); // CV: used for tight lepton selection only

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  enum { kOS, kSS };
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  else throw cms::Exception("analyze_0l_2tau") 
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

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
  const int hadTauPt_option         = getHadTauPt_option  (central_or_shift);
  const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
  const int lheScale_option         = getLHEscale_option  (central_or_shift);
  const int jetBtagSF_option        = getBTagWeight_option(central_or_shift);
  const PUsys puSys_option          = getPUsys_option     (central_or_shift);

  const int met_option   = useNonNominal_jetmet ? kMEt_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option = useNonNominal_jetmet ? kJet_central_nonNominal : getJet_option(central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> hadTauPt_option            = " << hadTauPt_option            << "\n"
       " -> jetToTauFakeRate_option    = " << jetToTauFakeRate_option    << "\n"
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
  if(era == kEra_2016)
  {
    const edm::ParameterSet cfg_triggerSF_2tau = cfg_analyze.getParameter<edm::ParameterSet>("triggerSF_2tau");
    cfg_dataToMCcorrectionInterface.addParameter<edm::ParameterSet>("triggerSF_2tau", cfg_triggerSF_2tau);
  }
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_0l_2tau", __LINE__) << "Invalid era = " << era;
  }
  Data_to_MC_CorrectionInterface_0l_2tau_trigger* dataToMCcorrectionInterface_0l_2tau_trigger = new Data_to_MC_CorrectionInterface_0l_2tau_trigger(cfg_dataToMCcorrectionInterface);
  
  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2tau"     ) applyFakeRateWeights = kFR_2tau;
  else throw cms::Exception("analyze_0l_2tau") 
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  
  bool selectBDT = cfg_analyze.getParameter<bool>("selectBDT");

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2tau ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
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

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  bool redoGenMatching = cfg_analyze.exists("redoGenMatching") ? cfg_analyze.getParameter<bool>("redoGenMatching") : true;

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfg_runLumiEventSelector;
    cfg_runLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfg_runLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfg_runLumiEventSelector);
  }
  
  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  const double minPt_hadTau_lead    = 40.;
  const double minPt_hadTau_sublead = 40.;

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
    snm->initializeHLTBranches({ triggers_2tau });
  }

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo, puSys_option);
  inputTree -> registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance(triggers_2tau);
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
  RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);
  tightMuonSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  electronReader->readUncorrected(useNonNominal);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  fakeableElectronSelector.disable_offline_e_trigger_cuts();
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  tightElectronSelector.disable_offline_e_trigger_cuts();
  tightElectronSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);
  GenParticleReader* genQuarkFromTopReader = new GenParticleReader(branchName_genQuarkFromTop);

  if ( isMC ) {
    inputTree -> registerReader(genTopQuarkReader);
    inputTree -> registerReader(genBJetReader);
    inputTree -> registerReader(genWBosonReader);
    inputTree -> registerReader(genWJetReader);
    inputTree -> registerReader(genQuarkFromTopReader);
  }

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

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

  //--- initialize hadronic top tagger BDT
  std::string mvaFileName_hadTopTaggerWithKinFit = "tthAnalysis/HiggsToTauTau/data/HadTopTagger_resolved_XGB_CSV_sort_withKinFit.xml";
  std::string mvaFileName_hadTopTaggerWithKinFitNew = "tthAnalysis/HiggsToTauTau/data/ttH_HadTopTagger_wBoost_XGB_ntrees_1500_deph_3_lr_0o01_CSV_sort_nvar9.pkl";
  std::string mvaFileName_hadTopTaggerNoKinFit = "tthAnalysis/HiggsToTauTau/data/ttH_HadTopTagger_wBoost_XGB_ntrees_1500_deph_3_lr_0o01_CSV_sort_nvar8.pkl";
  HadTopTagger* hadTopTagger = new HadTopTagger(mvaFileName_hadTopTaggerWithKinFit, mvaFileName_hadTopTaggerWithKinFitNew, mvaFileName_hadTopTaggerNoKinFit);

  //--- initialize BDTs used to discriminate ttH vs. ttbar trained by Arun for 0l_2tau category
  std::string mvaFileName_0l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/0l_2tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_0l_2tau_ttbar;
  mvaInputVariables_0l_2tau_ttbar.push_back("nJet");
  mvaInputVariables_0l_2tau_ttbar.push_back("nBJetLoose");
  mvaInputVariables_0l_2tau_ttbar.push_back("nBJetMedium");
  mvaInputVariables_0l_2tau_ttbar.push_back("mindr_tau1_jet");
  mvaInputVariables_0l_2tau_ttbar.push_back("mindr_tau2_jet");
  mvaInputVariables_0l_2tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_0l_2tau_ttbar.push_back("ptmiss");
  mvaInputVariables_0l_2tau_ttbar.push_back("mT_tau1");
  mvaInputVariables_0l_2tau_ttbar.push_back("mT_tau2");
  mvaInputVariables_0l_2tau_ttbar.push_back("htmiss");
  mvaInputVariables_0l_2tau_ttbar.push_back("tau1_pt");
  mvaInputVariables_0l_2tau_ttbar.push_back("tau2_pt");
  mvaInputVariables_0l_2tau_ttbar.push_back("TMath::Abs(tau1_eta)");
  mvaInputVariables_0l_2tau_ttbar.push_back("TMath::Abs(tau2_eta)");
  mvaInputVariables_0l_2tau_ttbar.push_back("dr_taus");
  mvaInputVariables_0l_2tau_ttbar.push_back("mTauTauVis");
  mvaInputVariables_0l_2tau_ttbar.push_back("mTauTau");
  TMVAInterface mva_0l_2tau_ttbar(mvaFileName_0l_2tau_ttbar, mvaInputVariables_0l_2tau_ttbar, { "tau1_mva", "tau2_mva" });  

  std::map<std::string, double> mvaInputs_ttbar;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;

//--- declare histograms
  struct preselHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    HadTauHistManager* leadHadTau_;
    HadTauHistManager* subleadHadTau_;
    JetHistManager* jets_;
    JetHistManager* BJets_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    EvtHistManager_0l_2tau* evt_;
    EvtYieldHistManager* evtYield_;
  };
  std::map<int, preselHistManagerType*> preselHistManagers;
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    std::map<std::string, HadTauHistManager*> hadTaus_in_categories_;
    HadTauHistManager* leadHadTau_;
    std::map<std::string, HadTauHistManager*> leadHadTau_in_categories_;
    HadTauHistManager* subleadHadTau_;
    std::map<std::string, HadTauHistManager*> subleadHadTau_in_categories_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    MVAInputVarHistManager* mvaInputVariables_ttbar_;
    //MVAInputVarHistManager* mvaInputVariables_ttV_;
    EvtHistManager_0l_2tau* evt_;    
    std::map<std::string, EvtHistManager_0l_2tau*> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_0l_2tau*> evt_in_categories_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };
  std::map<int, selHistManagerType*> selHistManagers;
  for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
        hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

    std::string process_and_genMatch = process_string;
    if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

    int idxHadTau = hadTauGenMatch_definition->idx_;
    
    preselHistManagerType* preselHistManager = new preselHistManagerType();
    preselHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/electrons", histogramDir.data()), central_or_shift));
    preselHistManager->electrons_->bookHistograms(fs);
    preselHistManager->muons_ =  new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/muons", histogramDir.data()), central_or_shift));
    preselHistManager->muons_->bookHistograms(fs);
    preselHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/hadTaus", histogramDir.data()), central_or_shift));
    preselHistManager->hadTaus_->bookHistograms(fs);
    preselHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/leadHadTau", histogramDir.data()), central_or_shift));
    preselHistManager->leadHadTau_->bookHistograms(fs);
    preselHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/subleadHadTau", histogramDir.data()), central_or_shift));
    preselHistManager->subleadHadTau_->bookHistograms(fs);
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
    preselHistManager->evt_ = new EvtHistManager_0l_2tau(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/evt", histogramDir.data()), central_or_shift));
    preselHistManager->evt_->bookHistograms(fs);
    edm::ParameterSet cfg_EvtYieldHistManager_presel = makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/evtYield", histogramDir.data()), central_or_shift);
    cfg_EvtYieldHistManager_presel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
    cfg_EvtYieldHistManager_presel.addParameter<bool>("isMC", isMC);
    preselHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_presel);
    preselHistManager->evtYield_->bookHistograms(fs);   
    preselHistManagers[idxHadTau] = preselHistManager;

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
    selHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/leadHadTau", histogramDir.data()), central_or_shift));
    selHistManager->leadHadTau_->bookHistograms(fs);
    selHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/subleadHadTau", histogramDir.data()), central_or_shift));
    selHistManager->subleadHadTau_->bookHistograms(fs);
    vstring categories_tau = {
      "0l_2tau_bloose", "0l_2tau_btight"
    };
    for ( vstring::const_iterator category = categories_tau.begin();
          category != categories_tau.end(); ++category ) {
      TString histogramDir_category = histogramDir.data();
      histogramDir_category.ReplaceAll("0l_2tau", category->data());
      selHistManager->hadTaus_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/hadTaus", histogramDir_category.Data()), central_or_shift));
      selHistManager->hadTaus_in_categories_[*category]->bookHistograms(fs);
      selHistManager->leadHadTau_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/leadHadTau", histogramDir_category.Data()), central_or_shift));
      selHistManager->leadHadTau_in_categories_[*category]->bookHistograms(fs);
      selHistManager->subleadHadTau_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/subleadHadTau", histogramDir_category.Data()), central_or_shift));
      selHistManager->subleadHadTau_in_categories_[*category]->bookHistograms(fs);
    }
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
    selHistManager->mvaInputVariables_ttbar_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/mvaInputs_ttbar", histogramDir.data()), central_or_shift));
    selHistManager->mvaInputVariables_ttbar_->bookHistograms(fs, mvaInputVariables_0l_2tau_ttbar);
    //selHistManager->mvaInputVariables_ttV_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
    //  Form("%s/sel/mvaInputs_ttV", histogramDir.data()), central_or_shift));
    //selHistManager->mvaInputVariables_ttV_->bookHistograms(fs, mvaInputVariables_0l_2tau_ttV);
    selHistManager->evt_ = new EvtHistManager_0l_2tau(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/evt", histogramDir.data()), central_or_shift));
    selHistManager->evt_->bookHistograms(fs);         
    const vstring decayModes_evt = eventInfo.getDecayModes();
    if ( isSignal ) {
      for ( vstring::const_iterator decayMode = decayModes_evt.begin();
            decayMode != decayModes_evt.end(); ++decayMode) {

        std::string decayMode_and_genMatch = (*decayMode);
        if ( apply_hadTauGenMatching ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;

        selHistManager->evt_in_decayModes_[*decayMode] = new EvtHistManager_0l_2tau(makeHistManager_cfg(decayMode_and_genMatch,
          Form("%s/sel/evt", histogramDir.data()), central_or_shift));
        selHistManager->evt_in_decayModes_[*decayMode]->bookHistograms(fs);
      }
    }
    vstring categories_evt = { 
      "0l_2tau_bloose", "0l_2tau_btight"
    };
    for ( vstring::const_iterator category = categories_evt.begin();
          category != categories_evt.end(); ++category ) {
      TString histogramDir_category = histogramDir.data();
      histogramDir_category.ReplaceAll("0l_2tau", category->data());
      selHistManager->evt_in_categories_[*category] = new EvtHistManager_0l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evt", histogramDir_category.Data()), central_or_shift));
      selHistManager->evt_in_categories_[*category]->bookHistograms(fs);
    }      
    edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/evtYield", histogramDir.data()), central_or_shift);
    cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
    cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
    selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
    selHistManager->evtYield_->bookHistograms(fs);   
    selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/weights", histogramDir.data()), central_or_shift));
    selHistManager->weights_->bookHistograms(fs, 
      { "genWeight", "pileupWeight", "data_to_MC_correction", "triggerWeight", "hadTauEff", "fakeRate" });
    selHistManagers[idxHadTau] = selHistManager;
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("%s/unbiased/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
     lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/lheInfo", histogramDir.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

  NtupleFillerBDT<float, int> * bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if(selectBDT)
  {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), central_or_shift)
    );
    bdt_filler -> register_variable<float_type>(
      "mindr_tau1_jet", "mindr_tau2_jet", 
      "avg_dr_jet", "ptmiss", "htmiss", "tau1_mva", "tau2_mva", "tau1_pt", "tau2_pt",
      "tau1_eta", "tau2_eta", "dr_taus", "mT_tau1", "mT_tau2", "mTauTauVis", "mTauTau",

      "HTT_wKinFit_top1", "HTT_wKinFitNew_top1", "HTT_noKinFit_top1", "dr_HadTop1_tau_lead_top1",
      "dr_HadTop1_tau_sublead_top1", "dr_HadTop1_tautau_top1", "HadTop1_pt_top1", "HadTop1_eta_top1",

      "HTT_wKinFit_top2", "HTT_wKinFitNew_top2", "HTT_noKinFit_top2", "dr_HadTop1_tau_lead_top2",
      "dr_HadTop1_tau_sublead_top2", "dr_HadTop1_tautau_top2", "HadTop1_pt_top2", "HadTop1_eta_top2",

      "lumiScale", "genWeight", "evtWeight"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium",
      "bWj1Wj2_isGenMatchedWithKinFit_top1", "bWj1Wj2_isGenMatchedWithKinFitNew_top1", "bWj1Wj2_isGenMatchedNoKinFit_top1",
      "bWj1Wj2_isGenMatchedWithKinFit_top2", "bWj1Wj2_isGenMatchedWithKinFitNew_top2", "bWj1Wj2_isGenMatchedNoKinFit_top2",
      "ncombo_top1", "hadtruth_top1", "ncombo_top2", "hadtruth_top2"
    );
    bdt_filler -> bookTree(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  const edm::ParameterSet cutFlowTableCfg = makeHistManager_cfg(
    process_string, Form("%s/sel/cutFlow", histogramDir.data()), central_or_shift
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "trigger",
    ">= 2 presel taus",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet (1)",
    ">= 2 sel taus",
    "no tight leptons",
    "HLT filter matching",
    ">= 4 jets",
    ">= 2 loose b-jets || 1 medium b-jet (2)",
    "m(ll) > 12 GeV",
    Form("lead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_lead),
    Form("sublead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_sublead),
    "tau-pair OS/SS charge",
    "MEt filters",
    "signal region veto",
  };
  CutFlowTableHistManager * cutFlowHistManager = new CutFlowTableHistManager(cutFlowTableCfg, cuts);
  cutFlowHistManager->bookHistograms(fs);
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

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo) ) continue;
    cutFlowTable.update("run:ls:event selection");
    cutFlowHistManager->fillHistograms("run:ls:event selection", lumiScale);

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

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
    
    std::vector<GenParticle> genTopQuarks;
    std::vector<GenParticle> genBJets;
    std::vector<GenParticle> genWBosons;
    std::vector<GenParticle> genWJets;
    std::vector<GenParticle> genQuarkFromTop;
    if ( isMC ) {
      genTopQuarks = genTopQuarkReader->read();
      genBJets = genBJetReader->read();
      genWBosons = genWBosonReader->read();
      genWJets = genWJetReader->read();
      genQuarkFromTop = genQuarkFromTopReader->read();
    }

    bool isTriggered_2tau = hltPaths_isTriggered(triggers_2tau, isDEBUG);

    bool selTrigger_2tau = use_triggers_2tau && isTriggered_2tau;
    if ( !selTrigger_2tau ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
        std::cout << " (selTrigger_2tau = " << selTrigger_2tau << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);
    
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

    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    std::vector<const RecoLepton*> tightLeptons = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTausFull = preselHadTauSelector(cleanedHadTaus, isHigherPt);
    std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(preselHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    std::vector<const RecoHadTau*> preselHadTaus = pickFirstNobjects(preselHadTausFull, 2);
    std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 2);
    std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, preselHadTaus, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselHadTaus",   preselHadTaus);
      printCollection("fakeableHadTaus", fakeableHadTaus);
      printCollection("tightHadTaus",    tightHadTaus);
      printCollection("selHadTaus",      selHadTaus);
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("uncleanedJets", jet_ptrs);
      printCollection("selJets",       selJets);
    }

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

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    if ( !(preselHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 presel taus");
    cutFlowHistManager->fillHistograms(">= 2 presel taus", lumiScale);
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    const hadTauGenMatchEntry& preselHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, preselHadTau_lead, preselHadTau_sublead);
    int idxPreselHadTau_genMatch = preselHadTau_genMatch.idx_;
    assert(idxPreselHadTau_genMatch != kGen_HadTauUndefined2);

    double mTauTauVis_presel = (preselHadTau_lead->p4() + preselHadTau_sublead->p4()).mass();

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets");
    cutFlowHistManager->fillHistograms(">= 2 jets", lumiScale);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", lumiScale);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    Particle::LorentzVector mht_p4 = compMHT({}, fakeableHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselHadTau_genMatch];
    assert(preselHistManager != 0);
    preselHistManager->electrons_->fillHistograms(preselElectrons, 1.);
    preselHistManager->muons_->fillHistograms(preselMuons, 1.);
    preselHistManager->hadTaus_->fillHistograms(preselHadTaus, 1.);
    preselHistManager->leadHadTau_->fillHistograms({ preselHadTau_lead }, 1.);
    preselHistManager->subleadHadTau_->fillHistograms({ preselHadTau_sublead }, 1.);
    preselHistManager->jets_->fillHistograms(selJets, 1.);
    preselHistManager->BJets_loose_->fillHistograms(selBJets_loose, 1.);
    preselHistManager->BJets_medium_->fillHistograms(selBJets_medium, 1.);
    preselHistManager->met_->fillHistograms(met, mht_p4, met_LD, 1.);
    preselHistManager->metFilters_->fillHistograms(metFilters, 1.);
    preselHistManager->evt_->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1., 
      mTauTauVis_presel, -1., 1.);
    preselHistManager->evtYield_->fillHistograms(eventInfo, 1.);

//--- apply final event selection 
    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 sel taus", lumiScale);
    cutFlowHistManager->fillHistograms(">= 2 sel taus", lumiScale);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined2);

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    double btagWeight = 1.;
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
    double triggerWeight = 1.;
    double weight_hadTauEff = 1.;
    double tauSF_weight = 1.;
    if ( isMC ) {
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);

      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(),
        selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta());

      if(era == kEra_2016)
      {
        dataToMCcorrectionInterface_0l_2tau_trigger->setHadTaus(
          selHadTau_lead_genPdgId,    selHadTau_lead->pt(),    selHadTau_lead->eta(),    selHadTau_lead->decayMode(),
          selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->decayMode()
        );
      }
      else if(era == kEra_2017)
      {
        dataToMCcorrectionInterface_0l_2tau_trigger->setHadTaus(
          selHadTau_lead->pt(),    selHadTau_lead->eta(),    selHadTau_lead->phi(),
          selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->phi()
        );
      }
      else if(era == kEra_2018)
      {
        throw cmsException("analyze_0l_2tau", __LINE__) << "Invalid era = " << era;
      }
      dataToMCcorrectionInterface_0l_2tau_trigger->setTriggerBits(isTriggered_2tau);

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface_0l_2tau_trigger->getSF_triggerEff();
      if ( isDEBUG ) {
        std::cout << "sf_triggerEff = " << sf_triggerEff << std::endl;
      }
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates     
      double sf_hadTauEff = 1.;
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      if ( isDEBUG ) { 
        std::cout << "sf_hadTauEff = " << sf_hadTauEff << std::endl;
      }
      weight_hadTauEff *= sf_hadTauEff;
      tauSF_weight *= weight_hadTauEff;
      weight_data_to_MC_correction *= sf_hadTauEff;
      if ( isDEBUG ) {
        std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }
      evtWeight *= weight_data_to_MC_correction;
    }       
    
    // veto events that contain leptons passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptons.size() <= 0) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection." << std::endl;
        printCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("no tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("no tight leptons", evtWeight);

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      if(! hltFilter({{ hltPathsE::trigger_2tau, selTrigger_2tau }}, {}, fakeableHadTaus))
      {
        if(run_lumi_eventSelector || isDEBUG)
        {
          std::cout << "event " << eventInfo.str() << " FAILS HLT filter matching\n";
        }
        continue;
      }
    }
    cutFlowTable.update("HLT filter matching", evtWeight);
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeight);

    double weight_fakeRate = 1.;
    if ( applyFakeRateWeights == kFR_2tau) {
      double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTausFull);
      double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTausFull);

      weight_fakeRate = getWeight_2L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead, 
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );

      if ( isDEBUG ) {
        std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
      }
      evtWeight *= weight_fakeRate;
    }    
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }

    double mTauTauVis = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 4) ) continue;
    cutFlowTable.update(">= 4 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
 
    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptons.begin();
      lepton1 != preselLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
        lepton2 != preselLeptons.end(); ++lepton2 ) {
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
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    if ( !(selHadTau_lead->pt() > minPt_hadTau_lead && selHadTau_lead->absEta() < 2.1) ) continue;
    cutFlowTable.update(Form("lead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_lead), evtWeight);
    cutFlowHistManager->fillHistograms(Form("lead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_lead), evtWeight);

    if ( !(selHadTau_sublead->pt() > minPt_hadTau_sublead && selHadTau_sublead->absEta() < 2.1) ) continue;
    cutFlowTable.update(Form("sublead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_sublead), evtWeight);
    cutFlowHistManager->fillHistograms(Form("sublead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_sublead), evtWeight);

    bool isCharge_SS = selHadTau_lead->charge()*selHadTau_sublead->charge() > 0;
    bool isCharge_OS = selHadTau_lead->charge()*selHadTau_sublead->charge() < 0;
    if ( hadTauChargeSelection == kOS && isCharge_SS )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS OS tau selection\n";
      }
      continue;
    }
    if ( hadTauChargeSelection == kSS && isCharge_OS )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS SS tau selection\n";
      }
      continue;
    }
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("tau-pair OS/SS charge", evtWeight);
    
    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS MEt filters." << std::endl;
        }
        continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeight);
    cutFlowHistManager->fillHistograms("MEt filters", evtWeight);
    
    bool failsSignalRegionVeto = false;
    if ( isMCClosure_t ) {
      bool applySignalRegionVeto = isMCClosure_t && countFakeHadTaus(selHadTaus) >= 1;
      if ( applySignalRegionVeto && tightHadTaus.size() >= 2 ) failsSignalRegionVeto = true;
    } else if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus.size() >= 2 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
                     "# tight taus = " << tightHadTaus.size() << " >= 2\n"
        ;
        printCollection("tightHadTaus", tightHadTaus);
      }
      continue; // CV: avoid overlap with signal region
    }
    cutFlowTable.update("signal region veto", evtWeight);
    cutFlowHistManager->fillHistograms("signal region veto", evtWeight);
    
    //--- compute output of hadronic top tagger BDT
    //double max_mvaOutput_hadTopTagger = -1.;
    double max_mvaOutput_hadTopTaggerWithKinFit = -1.;
    bool max_truth_hadTopTaggerWithKinFit = false;
    double max_mvaOutput_hadTopTaggerWithKinFitTop2 = -1.;
    bool max_truth_hadTopTaggerWithKinFitTop2 = false;

    double max_mvaOutput_hadTopTaggerWithKinFitNew = -1.;
    bool max_truth_hadTopTaggerWithKinFitNew = false;
    double max_mvaOutput_hadTopTaggerWithKinFitNewTop2 = -1.;
    bool max_truth_hadTopTaggerWithKinFitNewTop2 = false;

    double max_mvaOutput_hadTopTaggerNoKinFit = -1.;
    bool max_truth_hadTopTaggerNoKinFit = false;
    double max_mvaOutput_hadTopTaggerNoKinFitTop2 = -1.;
    bool max_truth_hadTopTaggerNoKinFitTop2 = false;

    bool hadtruth = false;
    bool hadtruth_top2 = false;
    int ncombo=0; int ncombo_top2 = 0;
    Particle::LorentzVector unfittedHadTopP4, fittedHadTopP4;
    Particle::LorentzVector unfittedHadTop2P4, fittedHadTop2P4;

    // it returns the gen-triplets organized in top/anti-top
    std::map<int, Particle::LorentzVector> genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop); // genWJets,
    std::map<int, Particle::LorentzVector> genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop); // genWJets,

    double selBJetTopPt = 0;
    double selWJet1TopPt = 0;
    double selWJet2TopPt = 0;
    ///////////////////////////////////////////////////////////////////////
    // resolved HTT
    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet ) {
      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1 ) {
        if ( &(*selWJet1) == &(*selBJet) ) continue;
        for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1; selWJet2 != selJets.end(); ++selWJet2 ) {
          if ( &(*selWJet2) == &(*selBJet) ) continue;
          if ( &(*selWJet2) == &(*selWJet1) ) continue;
          ncombo++;

          const std::map<int, double> bdtResult = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2);
          bool isGenMatched = false;

          if ( isMC && selectBDT ) {
            std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
              (*selBJet)->p4(), (*selWJet1)->p4(),  (*selWJet2)->p4(),
              genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
              kGenTop
            );

            std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
              (*selBJet)->p4(), (*selWJet1)->p4(),  (*selWJet2)->p4(),
              genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
              kGenAntiTop
            );

            isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
            if ( isGenMatched ) hadtruth = true;
          }

          if ( bdtResult.at(kXGB_with_kinFit) > max_mvaOutput_hadTopTaggerWithKinFit ) { // hadTopTaggerWithKinFit
            max_truth_hadTopTaggerWithKinFit = isGenMatched;
            max_mvaOutput_hadTopTaggerWithKinFit = bdtResult.at(kXGB_with_kinFit);
            fittedHadTopP4 = hadTopTagger->kinFit()->fittedTop();
            unfittedHadTopP4 = (*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4();
            selBJetTopPt = (*selBJet)->pt();
            selWJet1TopPt = (*selWJet1)->pt();
            selWJet2TopPt = (*selWJet2)->pt();
          }

          if ( bdtResult.at(kXGB_with_kinFitNew) > max_mvaOutput_hadTopTaggerWithKinFitNew ) { // hadTopTaggerWithKinFit
            max_truth_hadTopTaggerWithKinFitNew = isGenMatched;
            max_mvaOutput_hadTopTaggerWithKinFitNew = bdtResult.at(kXGB_with_kinFitNew);
          }
          
          if ( bdtResult.at(kXGB_no_kinFit) > max_mvaOutput_hadTopTaggerNoKinFit ) { // hadTopTaggerWithKinFit
            max_truth_hadTopTaggerNoKinFit = isGenMatched;
            max_mvaOutput_hadTopTaggerNoKinFit = bdtResult.at(kXGB_no_kinFit);
          }

        }
      }
    }
    // resolved 2nd Top
    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet ) {
      if(fabs((*selBJet)->pt() - selBJetTopPt) < 0.005 ||
         fabs((*selBJet)->pt() - selWJet1TopPt) < 0.005 ||
         fabs((*selBJet)->pt() - selWJet2TopPt) < 0.005) continue;

      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1 ) {
        if ( &(*selWJet1) == &(*selBJet) ) continue;

        if(fabs((*selWJet1)->pt() - selBJetTopPt) < 0.005 ||
           fabs((*selWJet1)->pt() - selWJet1TopPt) < 0.005 ||
           fabs((*selWJet1)->pt() - selWJet2TopPt) < 0.005) continue;

        for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1; selWJet2 != selJets.end(); ++selWJet2 ) {
          if ( &(*selWJet2) == &(*selBJet) ) continue;
          if ( &(*selWJet2) == &(*selWJet1) ) continue;

          if(fabs((*selWJet2)->pt() - selBJetTopPt) < 0.005 ||
             fabs((*selWJet2)->pt() - selWJet1TopPt) < 0.005 ||
             fabs((*selWJet2)->pt() - selWJet2TopPt) < 0.005) continue;
          ncombo_top2++;

          const std::map<int, double> bdtResult = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2);
          bool isGenMatched = false;

          if ( isMC && selectBDT ) {
            std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
              (*selBJet)->p4(), (*selWJet1)->p4(),  (*selWJet2)->p4(),
              genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
              kGenTop
            );

            std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
              (*selBJet)->p4(), (*selWJet1)->p4(),  (*selWJet2)->p4(),
              genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
              kGenAntiTop
            );

            isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
            if ( isGenMatched ) hadtruth_top2 = true;
          }
          if ( bdtResult.at(kXGB_with_kinFit) > max_mvaOutput_hadTopTaggerWithKinFitTop2 ) { // hadTopTaggerWithKinFit 
            max_truth_hadTopTaggerWithKinFitTop2 = isGenMatched;
            max_mvaOutput_hadTopTaggerWithKinFitTop2 = bdtResult.at(kXGB_with_kinFit);
            fittedHadTop2P4 = hadTopTagger->kinFit()->fittedTop();
            unfittedHadTop2P4 = (*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4();
          }

          if ( bdtResult.at(kXGB_with_kinFitNew) > max_mvaOutput_hadTopTaggerWithKinFitNewTop2 ) { // hadTopTaggerWithKinFit
            max_truth_hadTopTaggerWithKinFitNewTop2 = isGenMatched;
            max_mvaOutput_hadTopTaggerWithKinFitNewTop2 = bdtResult.at(kXGB_with_kinFitNew);
          }

          if ( bdtResult.at(kXGB_no_kinFit) > max_mvaOutput_hadTopTaggerNoKinFitTop2 ) { // hadTopTaggerWithKinFit
            max_truth_hadTopTaggerNoKinFitTop2 = isGenMatched;
            max_mvaOutput_hadTopTaggerNoKinFitTop2 = bdtResult.at(kXGB_no_kinFit);
          }

        }
      }
    }
//--- reconstruct mass of tau-pair using SVfit algorithm
//
//    NOTE: SVfit needs to be run after all event selection cuts are applied,
//          because the algorithm takes O(1 second per event) to run
//
    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
    classic_svFit::MeasuredTauLepton::kDecayType leg1Type = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    double leg1Mass = selHadTau_lead->mass();
    if ( leg1Mass < classic_svFit::chargedPionMass ) leg1Mass = classic_svFit::chargedPionMass;
    if ( leg1Mass > 1.5                            ) leg1Mass = 1.5;
    classic_svFit::MeasuredTauLepton::kDecayType leg2Type = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    double leg2Mass = selHadTau_sublead->mass();
    if ( leg2Mass < classic_svFit::chargedPionMass ) leg2Mass = classic_svFit::chargedPionMass;
    if ( leg2Mass > 1.5                            ) leg2Mass = 1.5;
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg1Type, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->phi(), leg1Mass));
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg2Type, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->phi(), leg2Mass));
    ClassicSVfit svFitAlgo;
    svFitAlgo.addLogM_dynamic(false);
    svFitAlgo.addLogM_fixed(true, 5.);
    svFitAlgo.integrate(measuredTauLeptons, met.p4().px(), met.p4().py(), met.cov());
    double mTauTau = -1.; // CV: temporarily comment-out the following line, to make code compile with "old" and "new" version of ClassicSVfit
    //double mTauTau = ( svFitAlgo.isValidSolution() ) ? static_cast<classic_svFit::HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass() : -1.;

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
    mvaInputs_ttbar["nJet"]                 = selJets.size();
    mvaInputs_ttbar["nBJetLoose"]           = selBJets_loose.size();
    mvaInputs_ttbar["nBJetMedium"]          = selBJets_medium.size();
    mvaInputs_ttbar["mindr_tau1_jet"]       = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets));
    mvaInputs_ttbar["mindr_tau2_jet"]       = TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets));
    mvaInputs_ttbar["avg_dr_jet"]           = comp_avg_dr_jet(selJets);
    mvaInputs_ttbar["ptmiss"]               = met.pt();
    mvaInputs_ttbar["mT_tau1"]              = comp_MT_met_hadTau1(*selHadTau_lead, met.pt(), met.phi());
    mvaInputs_ttbar["mT_tau2"]              = comp_MT_met_hadTau2(*selHadTau_sublead, met.pt(), met.phi());
    mvaInputs_ttbar["htmiss"]               = mht_p4.pt();
    mvaInputs_ttbar["tau1_pt"]              = selHadTau_lead->pt();
    mvaInputs_ttbar["tau2_pt"]              = selHadTau_sublead->pt();
    mvaInputs_ttbar["TMath::Abs(tau1_eta)"] = selHadTau_lead->absEta();
    mvaInputs_ttbar["TMath::Abs(tau2_eta)"] = selHadTau_sublead->absEta();
    mvaInputs_ttbar["dr_taus"]              = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_ttbar["mTauTauVis"]           = mTauTauVis;
    mvaInputs_ttbar["mTauTau"]              = mTauTau;

    check_mvaInputs(mvaInputs_ttbar, eventInfo);

    double mvaOutput_0l_2tau_ttbar = mva_0l_2tau_ttbar(mvaInputs_ttbar);    

//--- fill histograms with events passing final selection 
    selHistManagerType* selHistManager = selHistManagers[idxSelHadTau_genMatch];
    assert(selHistManager != 0);
    selHistManager->electrons_->fillHistograms(preselElectrons, evtWeight);
    selHistManager->muons_->fillHistograms(preselMuons, evtWeight);
    selHistManager->hadTaus_->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
    selHistManager->leadHadTau_->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->jets_->fillHistograms(selJets, evtWeight);
    selHistManager->leadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->subleadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->BJets_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->leadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->subleadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->BJets_medium_->fillHistograms(selBJets_medium, evtWeight);
    selHistManager->met_->fillHistograms(met, mht_p4, met_LD, evtWeight);
    selHistManager->metFilters_->fillHistograms(metFilters, evtWeight);
    selHistManager->mvaInputVariables_ttbar_->fillHistograms(mvaInputs_ttbar, evtWeight);
    //selHistManager->mvaInputVariables_ttV_->fillHistograms(mvaInputs_ttV, evtWeight);
    selHistManager->evt_->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_0l_2tau_ttbar, 
      mTauTauVis, mTauTau, evtWeight);
    if ( isSignal ) {
      const std::string decayModeStr = eventInfo.getDecayModeString();
      if(! decayModeStr.empty())
      {
        selHistManager->evt_in_decayModes_[decayModeStr]->fillHistograms(
          preselElectrons.size(),
          preselMuons.size(),
          selHadTaus.size(),
          selJets.size(),
          selBJets_loose.size(),
          selBJets_medium.size(),
          mvaOutput_0l_2tau_ttbar,
          mTauTauVis,
          mTauTau,
          evtWeight
        );
      }
    }
    selHistManager->evtYield_->fillHistograms(eventInfo, evtWeight);
    selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("hadTauEff", weight_hadTauEff);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    std::string category;
    if   ( selBJets_medium.size() >= 1 ) category = "0l_2tau_btight"; 
    else                                 category = "0l_2tau_bloose";  
    selHistManager->hadTaus_in_categories_[category]->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
    selHistManager->leadHadTau_in_categories_[category]->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_in_categories_[category]->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->evt_in_categories_[category]->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_0l_2tau_ttbar, 
      mTauTauVis, mTauTau, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

    const bool isGenMatched = isMC &&
      ((apply_hadTauGenMatching && selHadTau_genMatch.numGenMatchedJets_ == 0) || ! apply_hadTauGenMatching)
    ;

    if(bdt_filler)
    {
      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("mindr_tau1_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets)))
          ("mindr_tau2_jet", TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets)))
          ("avg_dr_jet",     comp_avg_dr_jet(selJets))
          ("ptmiss",         met.pt())
          ("htmiss",         mht_p4.pt())
          ("tau1_mva",       selHadTau_lead -> raw_mva_dR03())
          ("tau2_mva",       selHadTau_sublead -> raw_mva_dR03())
          ("tau1_pt",        selHadTau_lead -> pt())
          ("tau2_pt",        selHadTau_sublead -> pt())
          ("tau1_eta",       selHadTau_lead -> eta())
          ("tau2_eta",       selHadTau_sublead -> eta())
          ("dr_taus",        deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4()))
          ("mT_tau1",        comp_MT_met_hadTau1(*selHadTau_lead, met.pt(), met.phi()))
          ("mT_tau2",        comp_MT_met_hadTau2(*selHadTau_sublead, met.pt(), met.phi()))
          ("mTauTauVis",     mTauTauVis)
          ("mTauTau",        mTauTau)
          ("HTT_wKinFit_top1",                       max_mvaOutput_hadTopTaggerWithKinFit)
          ("HTT_wKinFitNew_top1",                    max_mvaOutput_hadTopTaggerWithKinFitNew)
          ("HTT_noKinFit_top1",                      max_mvaOutput_hadTopTaggerNoKinFit)
          ("dr_HadTop1_tau_lead_top1",               deltaR(unfittedHadTopP4, selHadTau_lead->p4()))
          ("dr_HadTop1_tau_sublead_top1",            deltaR(unfittedHadTopP4, selHadTau_sublead->p4()))
          ("dr_HadTop1_tautau_top1",                 deltaR(unfittedHadTopP4, selHadTau_lead->p4() + selHadTau_sublead->p4()))
          ("HadTop1_pt_top1",                        unfittedHadTopP4.pt())
          ("HadTop1_eta_top1",                       std::fabs(unfittedHadTopP4.eta()))
          ("HTT_wKinFit_top2",                       max_mvaOutput_hadTopTaggerWithKinFitTop2)
          ("HTT_wKinFitNew_top2",                    max_mvaOutput_hadTopTaggerWithKinFitNewTop2)
          ("HTT_noKinFit_top2",                      max_mvaOutput_hadTopTaggerNoKinFitTop2)
          ("dr_HadTop1_tau_lead_top2",               deltaR(unfittedHadTop2P4, selHadTau_lead->p4()))
          ("dr_HadTop1_tau_sublead_top2",            deltaR(unfittedHadTop2P4, selHadTau_sublead->p4()))
          ("dr_HadTop1_tautau_top2",                 deltaR(unfittedHadTop2P4, selHadTau_lead->p4() + selHadTau_sublead->p4()))
          ("HadTop1_pt_top2",                        unfittedHadTop2P4.pt())
          ("HadTop1_eta_top2",                       std::fabs(unfittedHadTop2P4.eta()))
          ("bWj1Wj2_isGenMatchedWithKinFit_top1",    max_truth_hadTopTaggerWithKinFit)
          ("bWj1Wj2_isGenMatchedWithKinFitNew_top1", max_truth_hadTopTaggerWithKinFitNew)
          ("bWj1Wj2_isGenMatchedNoKinFit_top1",      max_truth_hadTopTaggerNoKinFit)
          ("bWj1Wj2_isGenMatchedWithKinFit_top2",    max_truth_hadTopTaggerWithKinFitTop2)
          ("bWj1Wj2_isGenMatchedWithKinFitNew_top2", max_truth_hadTopTaggerWithKinFitNewTop2)
          ("bWj1Wj2_isGenMatchedNoKinFit_top2",      max_truth_hadTopTaggerNoKinFitTop2)
          ("ncombo_top1",                            ncombo)
          ("hadtruth_top1",                          hadtruth)
          ("ncombo_top2",                            ncombo_top2)
          ("hadtruth_top2",                          hadtruth_top2)
          ("lumiScale",      lumiScale)
          ("genWeight",      eventInfo.genWeight)
          ("evtWeight",      evtWeight)
          ("nJet",           selJets.size())
          ("nBJetLoose",     selBJets_loose.size())
          ("nBJetMedium",    selBJets_medium.size())
        .fill()
      ;
    }

    if(snm)
    {
      const double avg_dr_jet      = comp_avg_dr_jet(selJets);
      const double max_dr_jet      = comp_max_dr_jet(selJets);
      const double mbb             = selBJets_medium.size() > 1 ? (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1.;
      const double mbb_loose       = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
      const double mindr_tau1_jet  = std::min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets));
      const double mindr_tau2_jet  = std::min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets));
      const double min_dr_tau_jet  = std::min(mindr_tau1_jet, mindr_tau2_jet);
      const double dr_taus         = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());

      snm->read(eventInfo);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(preselHadTausFull);
      snm->read(selJets);

      snm->read({ triggers_2tau });
      snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size());

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);

      // mindr_lep_jet not filled
      // mindr_lep2_jet not filled
      // mindr_lep3_jet not filled
      // mindr_lep4_jet not filled

      snm->read(mindr_tau1_jet,                         FloatVariableType::mindr_tau1_jet);
      snm->read(mindr_tau2_jet,                         FloatVariableType::mindr_tau2_jet);

      snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
      // avr_dr_lep_tau not filled
      snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
      // max_dr_lep_tau not filled
      snm->read(min_dr_tau_jet,                         FloatVariableType::min_dr_tau_jet);
      // min_dr_lep_tau not filled
      // min_dr_lep_jet not filled

      // dr_leps not filled
      snm->read(dr_taus,                                FloatVariableType::dr_taus);

      // dr_lep_tau_ss not filled
      // dr_lep1_tau1 not filled
      // dr_lep1_tau2 not filled
      // dr_lep2_tau1 not filled
      // dr_lep3_tau1 not filled
      // dr_lep2_tau2 not filled

      // max_lep_eta not filled

      // mT_met_lep1 not filled
      // mT_met_lep2 not filled
      // mT_met_lep3 not filled
      // mT_met_lep4 not filled

      snm->read(mTauTauVis,                             FloatVariableType::mTauTauVis);
      // mvis_l1tau not filled
      // mvis_l2tau not filled

      snm->read(mbb,                                    FloatVariableType::mbb);
      snm->read(mbb_loose,                              FloatVariableType::mbb_loose);

      // cosThetaS_hadTau not filled
      // HTT not filled
      // HadTop_pt not filled
      // Hj_tagger not filled

      // mvaOutput_plainKin_ttV not filled
      // mvaOutput_plainKin_tt not filled
      // mvaOutput_plainKin_1B_VT not filled
      // mvaOutput_HTT_SUM_VT not filled
      // mvaOutput_plainKin_SUM_VT not filled

      // mvaOutput_plainKin_SUM_VT not filled

      // mvaOutput_2lss_ttV not filled
      // mvaOutput_2lss_tt not filled
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

      snm->read(weight_fakeRate,                        FloatVariableType::FR_weight);
      snm->read(triggerWeight,                          FloatVariableType::triggerSF_weight);
      // weight_leptonEff not filled
      snm->read(tauSF_weight,                           FloatVariableType::tauSF_weight);
      snm->read(btagWeight,                             FloatVariableType::bTagSF_weight);
      snm->read(eventInfo.pileupWeight,                 FloatVariableType::PU_weight);
      snm->read(boost::math::sign(eventInfo.genWeight), FloatVariableType::MC_weight);

      // Integral_ttH not filled
      // Integral_ttZ not filled
      // Integral_ttZ_Zll not filled
      // Integral_ttbar not filled
      // integration_type not filled
      // MEM_LR not filled

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

  std::cout << "sel. Entries by gen. matching:" << std::endl;
  for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
        hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

    std::string process_and_genMatch = process_string;
    if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

    int idxHadTau = hadTauGenMatch_definition->idx_;

    const TH1* histogram_EventCounter = selHistManagers[idxHadTau]->evt_->getHistogram_EventCounter();
    std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries()
              << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
  }
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete jetToTauFakeRateInterface;
  
  delete run_lumi_eventSelector;

  delete selEventsFile;
  delete bdt_filler;

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

  delete hadTopTagger;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete cutFlowHistManager;
  delete eventWeightManager;

  hltPaths_delete(triggers_2tau);

  delete inputTree;
  delete snm;

  clock.Show("analyze_0l_2tau");

  return EXIT_SUCCESS;
}
