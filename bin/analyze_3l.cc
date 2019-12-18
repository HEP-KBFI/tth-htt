#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TError.h> // gErrorAbortLevel, kError
#include <TROOT.h> // TROOT

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 3l category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_3l.h" // MEMOutputReader_3l
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_3l.h" // EvtHistManager_3l
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_3lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/GenMatchInterface.h" // GenMatchInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet tags
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface.h" // HHWeightInterface

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/predicate.hpp> // boost::starts_with()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <array> // std::array<>
#include <tuple> // std::tuple<>, std::get<>(), std::make_tuple()

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_3lepton };

/**
 * @brief Produce datacard and control plots for 3l categories.
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

  std::cout << "<analyze_3l>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_3l");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_3l")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_3l");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tH = process_string == "tHq" || process_string == "tHW";
  const bool isMC_VH = process_string == "VH";
  const bool isMC_H  = process_string == "ggH" || process_string == "qqH" || process_string == "TTWH" || process_string == "TTZH";
  const bool isMC_HH = process_string == "HH";
  const bool isMC_signal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  const bool isSignal = isMC_signal || isMC_tH || isMC_VH || isMC_HH || isMC_H;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);
  const bool isControlRegion = cfg_analyze.getParameter<bool>("isControlRegion");
  const unsigned int skipEvery = cfg_analyze.getParameter<unsigned int>("skipEvery");

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
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_3lepton(true);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  GenMatchInterface genMatchInterface(3, apply_leptonGenMatching, false);

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  enum { kOS, kSS };
  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS" ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS" ) chargeSumSelection = kSS;
  else throw cms::Exception("analyze_3l")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

  int minNumJets = cfg_analyze.getParameter<int>("minNumJets");
  std::cout << "minNumJets = " << minNumJets << std::endl;

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
  const bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
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

  const MEMsys mem_option_main = getMEMsys_option(central_or_shift_main);
  assert(mem_option_main == MEMsys::nominal);

  std::cout
    << "central_or_shift    = " << central_or_shift_main       << "\n"
       " -> hadTauPt_option = " << hadTauPt_option             << "\n"
       " -> met_option      = " << met_option                  << "\n"
       " -> jetPt_option    = " << jetPt_option                << "\n"
       " -> MEMsys option   = " << as_integer(mem_option_main) << '\n'
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
    default: throw cmsException("analyze_3l", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "3lepton"  ) applyFakeRateWeights = kFR_3lepton;
  else throw cms::Exception("analyze_3l")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3lepton) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  edm::ParameterSet cfg_EvtYieldHistManager = cfg_analyze.getParameter<edm::ParameterSet>("cfgEvtYieldHistManager");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");
  std::string branchName_memOutput = cfg_analyze.getParameter<std::string>("branchName_memOutput");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  const bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

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
    snm->initializeHLTBranches({
      triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu,
      triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu
    });
  }

//--- declare event-level variables
  EventInfo eventInfo(isMC, isSignal, isMC_HH);
  const std::string default_cat_str = "default";
  std::vector<std::string> evt_cat_strs = { default_cat_str };

  //--- HH scan

  const edm::ParameterSet hhWeight_cfg = cfg_analyze.getParameterSet("hhWeight_cfg");
  const bool apply_HH_rwgt = isMC_HH && hhWeight_cfg.getParameter<bool>("apply_rwgt");
  const HHWeightInterface * HHWeight_calc = nullptr;
  if(apply_HH_rwgt)
  {
    HHWeight_calc = new HHWeightInterface(hhWeight_cfg);
    evt_cat_strs = HHWeight_calc->get_scan_strs();
  }
  const size_t Nscan = evt_cat_strs.size();
  std::cout << "Number of points being scanned = " << Nscan << '\n';

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

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu, triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu });
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
  RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3, isDEBUG);
  RecoHadTauCollectionSelectorLoose looseHadTauSelector(era, -1, isDEBUG);
  looseHadTauSelector.set_if_looser(hadTauSelection_part2);
  RecoHadTauCollectionSelectorLoose tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauSelection_part2);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics((central_or_shifts_local.size() > 1 || central_or_shift_main != "central") && isMC);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);
  const RecoJetCollectionSelectorForward jetSelectorForward(era, -1, isDEBUG);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

//--- declare likelihoods for signal/background hypotheses, obtained by matrix element method
  MEMOutputReader_3l* memReader = 0;
  if ( branchName_memOutput != "" ) {
    memReader = new MEMOutputReader_3l(Form("n%s", branchName_memOutput.data()), branchName_memOutput);
    inputTree -> registerReader(memReader);
  }

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
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  if ( isMC ) {
	  inputTree -> registerReader(genWBosonReader);
  }

HadTopTagger* hadTopTagger = new HadTopTagger();
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


  std::vector<std::string> mvaInputVariables_TensorFlow_3l_ttH_tH_3cat_v8 = {
    "avg_dr_jet", "ptmiss", "mbb_medium",
    "jet1_pt", "jet2_pt", "jet3_pt", "jet4_pt",
    "max_Lep_eta",
    "mT_lep1", "lep1_conePt", "mT_lep2", "lep2_conePt", "mT_lep3", "lep3_conePt",
    "leadFwdJet_pt", "res_HTT", "HadTop_pt",
    "nJet", "nJetForward", "nBJetLoose",
    "nBJetMedium", "nElectron", "sum_Lep_charge"
  };
  std::map<std::string, double> mvaInputs_3l_ttH_tH_3cat_v8_TF;
  std::vector<std::string> classes_TensorFlow_3l_ttH_tH_3cat = {"predictions_ttH",  "predictions_rest", "predictions_tH"};
  std::string mvaFileName_TensorFlow_3l_ttH_tH_3cat_v8 = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_sync/test_model_3l_ttH_tH_3cat_nottZ_no4mom_noSemi_noStand_v8.pb";
  TensorFlowInterface mva_3l_ttH_tH_3cat_v8_TF(
    mvaFileName_TensorFlow_3l_ttH_tH_3cat_v8,
    mvaInputVariables_TensorFlow_3l_ttH_tH_3cat_v8,
    classes_TensorFlow_3l_ttH_tH_3cat
  );
  // Legacy
  std::vector<std::string> mvaInputVariables_legacy_opt = {
    "lep1_conePt", "lep1_eta", "lep1_phi",
    "lep2_conePt", "lep2_eta", "lep2_phi",
    "lep3_conePt", "lep3_eta", "lep3_phi",
    "mindr_lep1_jet", "mindr_lep2_jet", "mindr_lep3_jet", "min_dr_Lep",
    "avg_dr_jet", "met_LD", "mbb_loose",
    "leadFwdJet_eta", "leadFwdJet_pt", "min_Deta_leadfwdJet_jet",
    "jet1_pt", "jet1_eta", "jet1_phi",
    "jet2_pt", "jet2_eta", "jet2_phi",
    "jet3_pt", "jet3_eta", "jet3_phi",
    "sum_Lep_charge", "HadTop_pt", "res_HTT",
    "nJet", "nBJetLoose", "nBJetMedium", "nJetForward", "nElectron", "has_SFOS"
  };
  std::string mvaFileName_TensorFlow_3l_ttH_tH_sig_2_rest_2_th_2_withWZ = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/3l_0tau/test_sig_2_rest_2_th_2_withWZ_2.pb";
  TensorFlowInterface mva_3l_sig_2_rest_2_th_2_withWZ_TF(
    mvaFileName_TensorFlow_3l_ttH_tH_sig_2_rest_2_th_2_withWZ,
    mvaInputVariables_legacy_opt,
    classes_TensorFlow_3l_ttH_tH_3cat
  );
  std::string mvaFileName_TensorFlow_3l_ttH_tH_sig_2p5_rest_2_th_2p5_withWZ = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/3l_0tau/test_sig_2p5_rest_2_th_2p5_withWZ_2.pb";
  TensorFlowInterface mva_3l_sig_2p5_rest_2_th_2p5_withWZ_TF(
    mvaFileName_TensorFlow_3l_ttH_tH_sig_2p5_rest_2_th_2p5_withWZ,
    mvaInputVariables_legacy_opt,
    classes_TensorFlow_3l_ttH_tH_3cat
  );
  std::string mvaFileName_TensorFlow_3l_ttH_tH_sig_2_rest_2p5_th_2_withWZ_2 = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/3l_0tau/test_sig_2_rest_2p5_th_2_withWZ_2.pb";
  TensorFlowInterface mva_3l_sig_2_rest_2p5_th_2_withWZ_TF(
    mvaFileName_TensorFlow_3l_ttH_tH_sig_2_rest_2p5_th_2_withWZ_2,
    mvaInputVariables_legacy_opt,
    classes_TensorFlow_3l_ttH_tH_3cat
  );

  std::vector<std::string> mvaInputVariables_3l = get_mvaInputVariables(mvaInputVariables_legacy_opt, mvaInputVariables_legacy_opt);
  std::map<std::string, double> mvaInputs_3l;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  bool ignoreMEMerrors = cfg_analyze.getParameter<bool>("ignoreMEMerrors");

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
    MVAInputVarHistManager* mvaInputVariables_3l_;
    std::map<std::string, EvtHistManager_3l*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_3l*>> evt_in_decayModes_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };

  const std::map<std::string, std::vector<double>> categories_TensorFlow_3l_ttH_tH_3cat_v8 = {
    {"output_NN_3l_ttH_tH_3cat_v8_ttH_bl",  {}},
    {"output_NN_3l_ttH_tH_3cat_v8_ttH_bt",  {}},
    {"output_NN_3l_ttH_tH_3cat_v8_tH_bl",   {}},
    {"output_NN_3l_ttH_tH_3cat_v8_tH_bt",   {}},
    {"output_NN_3l_ttH_tH_3cat_v8_rest_bl", {}},
    {"output_NN_3l_ttH_tH_3cat_v8_rest_bt", {}},
    {"output_NN_3l_ttH_tH_3cat_v8_cr",      {}}
  };

  const std::map<std::string, std::vector<double>> categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ = {
    {"output_NN_sig_2_rest_2_th_2_withWZ_ttH_bl",      {0.0, 0.45, 0.51, 0.57, 0.66, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_ttH_bt",      {0.0, 0.51, 0.60, 0.70, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_tH_bl",       {0.0, 0.43, 0.47, 0.50, 0.55, 0.61, 0.71, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_tH_bt",       {0.0, 0.46, 0.58, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_eee",    {0, 1}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_eem_bl", {0.0, 0.48, 0.52, 0.59, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_eem_bt", {0, 1}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_emm_bl", {0.0, 0.47, 0.53, 0.58, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_emm_bt", {0, 1}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_mmm_bl", {0.0, 0.50, 0.58, 1.0}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_rest_mmm_bt", {0, 1}},
    {"output_NN_sig_2_rest_2_th_2_withWZ_cr",          {0, 1}}
  };
  /*
  ttH_bl, 5, [0.0, 0.45, 0.51, 0.57, 0.66, 1.0]
  ttH_bt, 4, [0.0, 0.51, 0.60, 0.70, 1.0]
  tHq_bl, 7, [0.0, 0.43, 0.47, 0.50, 0.55, 0.61, 0.71, 1.0]
  tHq_bt,  3,  [0.0, 0.46, 0.58, 1.0]
  BKG_eee,  1,  [0, 1]
  BKG_eem_bl,  4,  [0.0, 0.48, 0.52, 0.59, 1.0]
  BKG_eem_bt,  1,  [0, 1]
  BKG_emm_bl,  4,  [0.0, 0.47, 0.53, 0.58, 1.0]
  BKG_emm_bt,  1, [0, 1]
  BKG_mmm_bl,  3,  [0.0, 0.50, 0.58, 1.0]
  BKG_mmm_bt,  1,  [0, 1]
  */


  const std::map<std::string, std::vector<double>> categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ = {
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_ttH_bl",      {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_ttH_bt",      {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_tH_bl",       {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_tH_bt",       {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eee_bl", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eee_bt", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eem_bl", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eem_bt", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_emm_bl", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_emm_bt", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_mmm_bl", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_mmm_bt", {}},
    {"output_NN_sig_2p5_rest_2_th_2p5_withWZ_cr",          {}}
  };

  const std::map<std::string, std::vector<double>> categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ = {
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_ttH_bl",      {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_ttH_bt",      {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_tH_bl",       {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_tH_bt",       {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eee_bl", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eee_bt", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eem_bl", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eem_bt", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_emm_bl", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_emm_bt", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_mmm_bl", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_rest_mmm_bt", {}},
    {"output_NN_sig_2_rest_2p5_th_2_withWZ_cr",          {}}
  };

  vstring ctrl_categories = { "other" };
  for(int nele_ctrl = 0; nele_ctrl < 4; ++nele_ctrl)
  {
    for(int nbjets_ctrl = 0; nbjets_ctrl < 3; ++nbjets_ctrl)
    {
      for(int njets_ctrl = std::min(2, nbjets_ctrl + 1); njets_ctrl < std::min(nbjets_ctrl + 5, 6); ++njets_ctrl)
      {
        int nmu_ctrl = 3 - nele_ctrl;
        const std::string ele_ctrl_str(nele_ctrl, 'e');
        const std::string mu_ctrl_str(nmu_ctrl, 'm');
        const std::string ctrl_category = Form("b%d_j%d_%s%s", nbjets_ctrl, njets_ctrl, ele_ctrl_str.data(), mu_ctrl_str.data());
        ctrl_categories.push_back(ctrl_category);
      }
    }
  }

  std::map<std::string, GenEvtHistManager*> genEvtHistManager_beforeCuts;
  std::map<std::string, GenEvtHistManager*> genEvtHistManager_afterCuts;
  std::map<std::string, LHEInfoHistManager*> lheInfoHistManager;
  std::map<std::string, std::map<int, selHistManagerType*>> selHistManagers;
  for(const std::string & central_or_shift: central_or_shifts_local)
  {
    const bool skipBooking = central_or_shift != central_or_shift_main;
    std::vector<const GenMatchEntry*> genMatchDefinitions = genMatchInterface.getGenMatchDefinitions();
    for (const GenMatchEntry * genMatchDefinition : genMatchDefinitions)
    {
      std::string process_and_genMatch = process_string;
      process_and_genMatch += genMatchDefinition->getName();

      int idxLepton = genMatchDefinition->getIdx();

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
        selHistManager->mvaInputVariables_3l_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/mvaInputs_3l", histogramDir.data()), era_string, central_or_shift));
        selHistManager->mvaInputVariables_3l_->bookHistograms(fs, mvaInputVariables_3l);
      }

      for(const std::string & evt_cat_str: evt_cat_strs)
      {
        if(skipBooking && evt_cat_str != default_cat_str)
        {
          continue;
        }
        const std::string process_string_new = evt_cat_str == default_cat_str ?
          process_string :
          process_string + evt_cat_str
        ;
        const std::string process_and_genMatchName = boost::replace_all_copy(
          process_and_genMatch, process_string, process_string_new
        );

        selHistManager->evt_[evt_cat_str] = new EvtHistManager_3l(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
        ));
        selHistManager->evt_[evt_cat_str]->bookCategories(
          fs,
          categories_TensorFlow_3l_ttH_tH_3cat_v8,
          categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ,
          categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ,
          categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ
        );
        if(isControlRegion)
        {
          selHistManager->evt_[evt_cat_str]->setCRcategories(fs, ctrl_categories);
        }
        selHistManager->evt_[evt_cat_str]->bookHistograms(fs);
      }

      if(isSignal)
      {
        const vstring decayModes_evt = get_key_list_hist(eventInfo, isMC_HH, isMC_VH);
        for(const std::string & decayMode_evt: decayModes_evt)
        {
          if((isMC_tH || isMC_VH ) && (decayMode_evt == "hzg" || decayMode_evt == "hmm"))
          {
            continue;
          }
          std::string decayMode_and_genMatch = get_prefix(process_string, isMC_tH,  isMC_HH, isMC_H, isMC_VH);
          decayMode_and_genMatch += decayMode_evt;
	  decayMode_and_genMatch += genMatchDefinition->getName();

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

            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] = new EvtHistManager_3l(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
            ));
            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> bookCategories(
              fs,
              categories_TensorFlow_3l_ttH_tH_3cat_v8,
              categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ,
              categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ,
              categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ
            );
            if(isControlRegion)
            {
              selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> setCRcategories(fs, ctrl_categories);
            }
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

  NtupleFillerBDT<float, int> * bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string, central_or_shift_main)
    );
    bdt_filler -> register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_phi", "lep1_tth_mva", "mindr_lep1_jet", "mT_lep1",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_phi", "lep2_tth_mva", "mindr_lep2_jet", "mT_lep2",
      "lep3_pt", "lep3_conePt", "lep3_eta", "lep3_phi", "lep3_tth_mva", "mindr_lep3_jet", "mT_lep3",
      "avg_dr_jet", "ptmiss",  "htmiss", "met_LD",
      "dr_leps",
      "lumiScale", "genWeight", "evtWeight",
      "memOutput_isValid", "memOutput_errorFlag", "memOutput_ttH", "memOutput_tHq", "memOutput_ttW", "memOutput_ttZ", "memOutput_tt", "memOutput_LR",
      "lep1_genLepPt", "lep2_genLepPt", "lep3_genLepPt",
      "lep1_fake_prob", "lep2_fake_prob", "lep3_fake_prob",
      "lep1_frWeight", "lep2_frWeight", "lep3_frWeight",
      "mvaOutput_3l_ttV", "mvaOutput_3l_ttbar", "mvaDiscr_3l",
      "mbb_loose", "mbb_medium",
      "dr_Lep_lss", "dr_Lep_los1", "dr_Lep_los2", "eta_LepLep_los1", "eta_LepLep_los2", "eta_LepLep_los",
      "mostFwdJet_eta", "mostFwdJet_pt", "mostFwdJet_phi", "mostFwdJet_E",
      "leadFwdJet_eta", "leadFwdJet_pt", "leadFwdJet_phi", "leadFwdJet_E",
      "min_dr_Lep", "max_dr_Lep",
      "jet1_pt", "jet1_eta", "jet1_phi", "jet1_E",
      "jet2_pt", "jet2_eta", "jet2_phi", "jet2_E",
      "jet3_pt", "jet3_eta", "jet3_phi", "jet3_E",
      "jet4_pt", "jet4_eta", "jet4_phi", "jet4_E",
      "sum_Lep_charge", "HadTop_pt", "res_HTT", "max_Lep_eta",
      "massL", "massL_FO", "massL3", "massLT", "min_Deta_mostfwdJet_jet", "min_Deta_leadfwdJet_jet"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "lep1_isTight", "lep2_isTight", "lep3_isTight", "hadtruth",
      "nElectron", "has_SFOS", "nJetForward"
    );
    bdt_filler -> bookTree(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  std::map<std::string, int> selectedEntries_byGenMatchType;             // key = process_and_genMatch
  std::map<std::string, double> selectedEntries_weighted_byGenMatchType; // key = process_and_genMatch
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  const edm::ParameterSet cutFlowTableCfg = makeHistManager_cfg(
    process_string, Form("%s/sel/cutFlow", histogramDir.data()), era_string, central_or_shift_main
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "object multiplicity",
    "trigger",
    ">= 3 presel leptons",
    "Hadronic selection",
    "3 sel leptons",
    "<= 3 tight leptons",
    "HLT filter matching",
    "sel tau veto",
    "m(ll) > 12 GeV",
    "lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV && third lepton pT > 10 GeV",
    "sel lepton charge",
    "Z-boson mass veto",
    "H->ZZ*->4l veto",
    "met LD",
    "MEt filters",
    "signal region veto",
  };
  CutFlowTableHistManager * cutFlowHistManager = new CutFlowTableHistManager(cutFlowTableCfg, cuts);
  cutFlowHistManager->bookHistograms(fs);

  bool isDebugTF = false;
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
    if(skipEvery > 1)
    {
      if(selectBDT)
      {
        if(eventInfo.event % skipEvery == 0)
        {
          // skip every N-th event when running in BDT mode
          continue;
        }
        else
        {
          // rescale event weight by N / (N - 1)
          evtWeightRecorder.record_rescaling(skipEvery / (skipEvery - 1.));
        }
      }
      else
      {
        if(eventInfo.event % skipEvery != 0)
        {
          // we enter here (N-1) times -> select every N-th event when running the analysis regularly
          continue;
        }
        else
        {
          // rescale event weight by N
          evtWeightRecorder.record_rescaling(skipEvery);
        }
      }
    }

    cutFlowTable.update("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(minLeptonSelection) < 3 ||
         objectMultiplicity.getNRecoLepton(kTight)             > 3  )
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }
    cutFlowTable.update("object multiplicity", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("object multiplicity", evtWeightRecorder.get(central_or_shift_main));

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
    std::vector<GenParticle> genWBosons;
    if ( isMC ) {
      genWBosons = genWBosonReader->read();
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
      bool selTrigger_MuonEG = selTrigger_1e1mu || selTrigger_2e1mu || selTrigger_1e2mu;
      if ( selTrigger_SingleElectron && (isTriggered_SingleMuon || isTriggered_DoubleMuon || isTriggered_MuonEG) ) {
	if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
		    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon
		    << ", isTriggered_DoubleMuon = " << isTriggered_DoubleMuon
		    << ", isTriggered_MuonEG = " << isTriggered_MuonEG << ")" << std::endl;
	}
	continue;
      }
      if ( selTrigger_SingleElectron && isTriggered_DoubleEG && era != kEra_2018 ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
                    << ", isTriggered_DoubleEG = " << isTriggered_DoubleEG << ")" << std::endl;
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
    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("trigger", evtWeightRecorder.get(central_or_shift_main));

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
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    const std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons, isHigherConePt);
    const std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons, isHigherConePt);
    const std::vector<const RecoMuon*> tightMuons = tightMuonSelector(fakeableMuons, isHigherConePt);
    if(isDEBUG || run_lumi_eventSelector)
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
    if(isDEBUG || run_lumi_eventSelector)
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

    const std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 3);
    const std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 3);
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

    }
    std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
    if(!(electronSelection == muonSelection)) selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau*> looseHadTaus = looseHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> selHadTaus = tightHadTauSelector(looseHadTaus, isHigherPt);

    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("selMuons", selMuons);
      printCollection("selElectrons", selElectrons);
      printCollection("selLeptons", selLeptons);
      printCollection("selHadTaus", selHadTaus);
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, looseHadTaus) :
      jetCleaner       (jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, looseHadTaus)
    ;
    const std::vector<const RecoJet*> selJets = jetSelector(cleanedJets, isHigherPt);
    const std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets, isHigherPt);
    const std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);
    const std::vector<const RecoJet *> selJetsForward = jetSelectorForward(cleanedJets, isHigherPt);

    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("uncleanedJets", jet_ptrs);
      printCollection("selJets",       selJets);
    }

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
    // require exactly three leptons passing loose preselection criteria to avoid overlap with 4l category
    if ( !(preselLeptonsFull.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS preselLeptons selection." << std::endl;
        printCollection("preselLeptons", preselLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update(">= 3 presel leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 3 presel leptons", evtWeightRecorder.get(central_or_shift_main));

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on preselection level
    const bool tH_like  = (selBJets_medium.size() >= 1 && ((selJets.size() - selBJets_loose.size()) + selJetsForward.size()) >= 1);
    const bool ttH_like = (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) && selJets.size() >= 2;
    const bool passEvents = ttH_like || tH_like;
    if((! passEvents && ! isControlRegion) || (isControlRegion && selJets.empty()))
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS selBJets selection\n";
        printCollection("selJets", selJets);
        printCollection("selBJets_loose", selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update("Hadronic selection", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("Hadronic selection", evtWeightRecorder.get(central_or_shift_main));

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptonsFull, looseHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    // require exactly three leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
        printCollection("selLeptons", selLeptons);
        printCollection("preselLeptons", preselLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 3 sel leptons", 1.);
    cutFlowHistManager->fillHistograms(">= 3 sel leptons", 1.);
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const RecoLepton* selLepton_third = selLeptons[2];
    int selLepton_third_type = getLeptonType(selLepton_third->pdgId());
    const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead, selLepton_third);

    if(isMC)
    {
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
	selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta(),
        selLepton_third_type, selLepton_third->pt(), selLepton_third->eta()
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
        evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge());
      }
    }

    if(! selectBDT)
    {
      if(applyFakeRateWeights == kFR_3lepton)
      {
        bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
        bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
        bool passesTight_lepton_third = isMatched(*selLepton_third, tightElectrons) || isMatched(*selLepton_third, tightMuons);
        evtWeightRecorder.record_jetToLepton_FR_lead(leptonFakeRateInterface, selLepton_lead);
        evtWeightRecorder.record_jetToLepton_FR_sublead(leptonFakeRateInterface, selLepton_sublead);
        evtWeightRecorder.record_jetToLepton_FR_third(leptonFakeRateInterface, selLepton_third);
        evtWeightRecorder.compute_FR_3l(passesTight_lepton_lead, passesTight_lepton_sublead, passesTight_lepton_third);
      }
    }

    // require exactly three leptons passing tight selection criteria, to avoid overlap with 4l channel
    if ( !(tightLeptonsFull.size() <= 3) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection.\n";
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 3 tight leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("<= 3 tight leptons", evtWeightRecorder.get(central_or_shift_main));

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
    cutFlowTable.update("HLT filter matching", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeightRecorder.get(central_or_shift_main));
    if ( selHadTaus.size() > 0 ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selHadTaus veto." << std::endl;
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update("sel tau veto", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("sel tau veto", evtWeightRecorder.get(central_or_shift_main));

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsFullUncleaned);
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));

    const double minPt_lead = 25.;
    const double minPt_sublead = 15.;
    const double minPt_third = 10.;
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
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV && third lepton pT > 10 GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV && third lepton pT > 10 GeV", evtWeightRecorder.get(central_or_shift_main));

    int sumLeptonCharge = selLepton_lead->charge() + selLepton_sublead->charge() + selLepton_third->charge();
    bool isCharge_SS = std::abs(sumLeptonCharge) >  1;
    bool isCharge_OS = std::abs(sumLeptonCharge) <= 1;
    if ( chargeSumSelection == kOS && isCharge_SS ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
		  << ", subleading selLepton charge = " << selLepton_sublead->charge()
		  << ", third selLepton charge = " << selLepton_third->charge() << ", chargeSumSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( chargeSumSelection == kSS && isCharge_OS ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
		  << ", subleading selLepton charge = " << selLepton_sublead->charge()
		  << ", third selLepton charge = " << selLepton_third->charge() << ", chargeSumSelection = SS)" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton charge", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("sel lepton charge", evtWeightRecorder.get(central_or_shift_main));

    bool failsZbosonMassVeto = isfailsZbosonMassVeto(preselLeptonsFull);
    if((failsZbosonMassVeto != isControlRegion))
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS Z-boson veto\n";
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeightRecorder.get(central_or_shift_main));

    const bool failsHtoZZVeto = isfailsHtoZZVeto(preselLeptonsFull);
    if(failsHtoZZVeto)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS H->ZZ*->4l veto.\n";
      }
      continue;
    }
    cutFlowTable.update("H->ZZ*->4l veto", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("H->ZZ*->4l veto", evtWeightRecorder.get(central_or_shift_main));

    const bool isSameFlavor_OS_FO = isSFOS(fakeableLeptons);
    bool is_tH_like_and_not_ttH_like = tH_like && !ttH_like;
    double met_LD_cut = 0.;
    //if (tH_like && !do_sync) met_LD_cut = -1.;
    if      ( selJets.size() >= 4 ) met_LD_cut = -1.; // MET LD cut not applied
    else if ( isSameFlavor_OS_FO     ) met_LD_cut = 45.;
    else                            met_LD_cut = 30.;
    if ( met_LD_cut > 0 && met_LD < met_LD_cut ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS MET LD selection." << std::endl;
        std::cout << " (met_LD = " << met_LD << ", met_LD_cut = " << met_LD_cut << ")" << std::endl;
      }

      if ( !tH_like ) continue; // MET LD cut not applied if tH_like
      else is_tH_like_and_not_ttH_like = true;

    }
    cutFlowTable.update("met LD", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("met LD", evtWeightRecorder.get(central_or_shift_main));

    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
	if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS MEt filters." << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("MEt filters", evtWeightRecorder.get(central_or_shift_main));

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
    cutFlowTable.update("signal region veto", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("signal region veto", evtWeightRecorder.get(central_or_shift_main));
    if(isDEBUG)
    {
      std::cout << "event " << eventInfo.str() << " evtweight: " << evtWeightRecorder << '\n';
    }

    std::vector<double> WeightBM; // weights to do histograms for BMs
    std::map<std::string, double> Weight_ktScan; // weights to do histograms for BMs
    double HHWeight = 1.0; // X: for the SM point -- the point explicited on this code

    if(apply_HH_rwgt)
    {
      assert(HHWeight_calc);
      WeightBM = HHWeight_calc->getJHEPWeight(eventInfo.gen_mHH, eventInfo.gen_cosThetaStar, isDEBUG);
      Weight_ktScan = HHWeight_calc->getScanWeight(eventInfo.gen_mHH, eventInfo.gen_cosThetaStar, isDEBUG);
      HHWeight = WeightBM[0];
      evtWeightRecorder.record_bm(HHWeight); // SM by default

      if(isDEBUG)
      {
        std::cout << "mhh = " << eventInfo.gen_mHH          << " : "
          "cost "             << eventInfo.gen_cosThetaStar << " : "
          "weight = "         << HHWeight                   << '\n'
          ;
        std::cout << "Calculated " << Weight_ktScan.size() << " scan weights\n";
        for(std::size_t bm_list = 0; bm_list < Weight_ktScan.size(); ++bm_list)
        {
          std::cout << "line = " << bm_list << " " << evt_cat_strs[bm_list] << "; Weight = " <<  Weight_ktScan[evt_cat_strs[bm_list]] << '\n';
        }
        std::cout << '\n';
      }
    }

    MEMOutput_3l memOutput_3l_matched;
    if(memReader)
    {
      const std::vector<MEMOutput_3l> memOutputs_3l = memReader->read();
      for(const MEMOutput_3l & memOutput_3l: memOutputs_3l)
      {
        const double selLepton_lead_dR = deltaR(
          selLepton_lead -> eta(),            selLepton_lead -> phi(),
          memOutput_3l.leadLepton_eta_, memOutput_3l.leadLepton_phi_
        );
        if(selLepton_lead_dR > 1.e-2)
          continue;
        const double selLepton_sublead_dR = deltaR(
          selLepton_sublead -> eta(),            selLepton_sublead -> phi(),
          memOutput_3l.subleadLepton_eta_, memOutput_3l.subleadLepton_phi_
        );
        if(selLepton_sublead_dR > 1.e-2)
          continue;
        const double selLepton_third_dR = deltaR(
          selLepton_third -> eta(),            selLepton_third -> phi(),
          memOutput_3l.thirdLepton_eta_, memOutput_3l.thirdLepton_phi_
        );
        if(selLepton_third_dR > 1.e-2)
          continue;
        memOutput_3l_matched = memOutput_3l;
        break;
      }
      if(! memOutput_3l_matched.is_initialized())
      {
        std::cout << "Warning in " << eventInfo << '\n';
        std::cout << "No MEMOutput_3l object found for:" << '\n'
                  << "\tselLepton_lead: pT = " << selLepton_lead -> pt()
                  << ", eta = "                << selLepton_lead -> eta()
                  << ", phi = "                << selLepton_lead -> phi()
                  << ", pdgId = "              << selLepton_lead -> pdgId() << "\n"
                     "\tselLepton_sublead: pT = " << selLepton_sublead -> pt()
                  << ", eta = "                   << selLepton_sublead -> eta()
                  << ", phi = "                   << selLepton_sublead -> phi()
                  << ", pdgId = "                 << selLepton_sublead -> pdgId() << "\n"
                     "\tselLepton_third: pT = " << selLepton_third -> pt()
                  << ", eta = "                 << selLepton_third -> eta()
                  << ", phi = "                 << selLepton_third -> phi()
                  << ", pdgId = "               << selLepton_third -> pdgId() << "\n"
                     "ttH-like = " << ttH_like << " "
                     "tH-like = "  << tH_like  << '\n'
        ;
        bool memSkipError = false;
        if(! memOutputs_3l.empty())
        {
          for(unsigned mem_idx = 0; mem_idx < memOutputs_3l.size(); ++mem_idx)
          {
            std::cout << "\t#" << mem_idx << " mem object;\n"
                      << "\t\tlead lepton eta = " << memOutputs_3l[mem_idx].leadLepton_eta_
                      << "; phi = "               << memOutputs_3l[mem_idx].leadLepton_phi_ << "\n"
                         "\t\tsublead lepton eta = " << memOutputs_3l[mem_idx].subleadLepton_eta_
                      << "; phi = "                  << memOutputs_3l[mem_idx].subleadLepton_phi_ << "\n"
                         "\t\tthird lepton eta = " << memOutputs_3l[mem_idx].thirdLepton_eta_
                      << "; phi = "                << memOutputs_3l[mem_idx].thirdLepton_phi_ << '\n'
            ;
            if(memOutputs_3l[mem_idx].errorFlag() == ADDMEM_3L_ERROR_SKIPPED)
            {
              std::cout << "MEM computation was skipped for event " << eventInfo.str() << '\n';
            }
            else if(memOutputs_3l[mem_idx].errorFlag() == ADDMEM_3L_ERROR_SKIPPED_NOPERM)
            {
              std::cout
                << "MEM computation was skipped for event " << eventInfo.str() << " AND "
                   "there were not enough MEM permutations in the first place\n"
                << memOutput_3l_matched.is_initialized() << " " << memOutput_3l_matched.weight_ttH() << "\n"
              ;
            }
            else if(memOutputs_3l[mem_idx].errorFlag() == ADDMEM_3L_ERROR_JETMULTIPLICITY ||
                    memOutputs_3l[mem_idx].errorFlag() == ADDMEM_3L_ERROR_BJETMULTIPLICITY )
            {
              if(ttH_like && branchName_memOutput.find(central_or_shift_main) != std::string::npos)
              {
                std::cout
                  << "MEM did not find enough jets in event " << eventInfo.str() << " and for systematics "
                  << central_or_shift_main << " although there are " << selJets.size() << " jets selected in the event\n"
                ;
              }
              else
              {
                memSkipError = true;
                std::cout
                  << "MEM not available because the event is tH-like or the thresholds is jet selection have "
                     "changed wrt the thresholds used in MEM computation\n"
                ;
              }
            }
            else if(memOutputs_3l[mem_idx].errorFlag() == ADDMEM_3L_ERROR_NOPERM)
            {
              std::cout
                << "MEM computation was skipped for event " << eventInfo.str() << " because not enough permutations found\n"
              ;
            }
            else
            {
              std::cout << "Failed with MEM error: " << memOutput_3l_matched.errorFlag()  << '\n';
            }
          }
        }
        else
        {
          std::cout << "Event " << eventInfo.str() << " contains no MEM objects whatsoever\n";
          memSkipError = tH_like;
        }
        if(! ignoreMEMerrors && ! memSkipError)
        {
          throw cmsException(argv[0], __LINE__) << "No valid MEM output was found: "
          << " run number: " << eventInfo.run
          << " | lumi number: " << eventInfo.lumi
          << " | event number: " << eventInfo.event;
        }
      }
    }

    const std::map<MEMsys, double> memOutput_LR = memOutput_3l_matched.get_LR_map();
    const double memOutput_ttH = memOutput_3l_matched.isValid() ? memOutput_3l_matched.weight_ttH() : -100.;
    const double memOutput_tHq = memOutput_3l_matched.isValid() ? memOutput_3l_matched.weight_tHq() : -100.;
    const double memOutput_ttW = memOutput_3l_matched.isValid() ? memOutput_3l_matched.weight_ttW() : -100.;
    const double memOutput_ttZ = memOutput_3l_matched.isValid() ? memOutput_3l_matched.weight_ttZ() : -100.;
    const double memOutput_tt  = memOutput_3l_matched.isValid() ? memOutput_3l_matched.weight_tt()  : -100.;

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 3l category of ttH multilepton analysis
    const double lep1_conePt = comp_lep1_conePt(*selLepton_lead);
    const double lep2_conePt = comp_lep2_conePt(*selLepton_sublead);
    const double lep3_conePt = comp_lep3_conePt(*selLepton_third);
    const double mindr_lep1_jet = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    const double mindr_lep2_jet = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    const double mindr_lep3_jet = comp_mindr_lep3_jet(*selLepton_third, selJets);
    const double avg_dr_jet = comp_avg_dr_jet(selJets);
    const double max_lep12_eta = std::max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    mvaInputs_3l["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = max_lep12_eta;
    mvaInputs_3l["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
    mvaInputs_3l["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs_3l["mindr_lep1_jet"]             = mindr_lep1_jet;
    mvaInputs_3l["mindr_lep2_jet"]             = mindr_lep2_jet;
    mvaInputs_3l["LepGood_conePt[iF_Recl[0]]"] = lep1_conePt;
    mvaInputs_3l["LepGood_conePt[iF_Recl[2]]"] = lep3_conePt;
    mvaInputs_3l["avg_dr_jet"]                 = avg_dr_jet;
    mvaInputs_3l["mhtJet25_Recl"]              = mht_p4.pt();

    check_mvaInputs(mvaInputs_3l, eventInfo);

    double mvaOutput_3l_ttV = mva_3l_ttV(mvaInputs_3l);
    double mvaOutput_3l_ttbar = mva_3l_ttbar(mvaInputs_3l);

    //--- compute output of hadronic top tagger BDT
    // it returns the gen-triplets organized in top/anti-top
    bool calculate_matching = false;//isMC && selectBDT && !applyAdditionalEvtWeight; // DY has not matching info
    std::map<int, Particle::LorentzVector> genVar;
    std::map<int, Particle::LorentzVector> genVarAnti;
    /*
    if (calculate_matching) {
      genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop);
      genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop);
    }*/

    // resolved HTT
    double max_mvaOutput_HTT_CSVsort4rd = 0.;
    //bool max_truth_HTT_CSVsort4rd = false;
    double HadTop_pt_CSVsort4rd = 0.;
    //double genTopPt_CSVsort4rd = 0.;
    bool hadtruth = false;
    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet ) {
      //btag_iterator++;
      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1 ) {
       if ( &(*selWJet1) == &(*selBJet) ) continue;
       for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1; selWJet2 != selJets.end(); ++selWJet2 ) {
    if ( &(*selWJet2) == &(*selBJet) ) continue;
    if ( &(*selWJet2) == &(*selWJet1) ) continue;
    bool isGenMatched = false;
    double genTopPt_teste = 0.;
    const std::map<int, double> bdtResult = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti, isDebugTF );
    // genTopPt_teste is filled with the result of gen-matching
    if ( isGenMatched ) hadtruth = true;
    // save genpt of all options
    double HadTop_pt = ((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).pt();

    if ( bdtResult.at(kXGB_CSVsort4rd) > max_mvaOutput_HTT_CSVsort4rd ) {
      //max_truth_HTT_CSVsort4rd = isGenMatched;
      max_mvaOutput_HTT_CSVsort4rd = bdtResult.at(kXGB_CSVsort4rd);
      HadTop_pt_CSVsort4rd = HadTop_pt;
      //genTopPt_CSVsort4rd = genTopPt_teste;
    }

    }
      }
    }

    const double mT_lep1           = comp_MT_met_lep1(selLepton_lead->p4(), met.pt(), met.phi());
    const double mT_lep2           = comp_MT_met_lep2(selLepton_sublead->p4(), met.pt(), met.phi());
    const double mT_lep3           = comp_MT_met_lep3(selLepton_third->p4(), met.pt(), met.phi());
    const double max_dr_jet        = comp_max_dr_jet(selJets);
    const double mbb               = selBJets_medium.size() > 1 ? (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : 0.;
    const double mbb_loose         = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
    const double min_dr_lep_jet    = std::min({ mindr_lep1_jet, mindr_lep2_jet, mindr_lep3_jet });
    const double dr_leps           = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    const double max_lep_eta       = std::max({ selLepton_lead->absEta(), selLepton_sublead->absEta(), selLepton_third->absEta() });
    const double min_dr_lep    = std::min({
      deltaR(selLepton_lead->p4(), selLepton_sublead->p4()),
      deltaR(selLepton_lead->p4(), selLepton_third->p4()),
      deltaR(selLepton_third->p4(), selLepton_sublead->p4())
    });
    const double max_dr_lep    = std::max({
      deltaR(selLepton_lead->p4(), selLepton_sublead->p4()),
      deltaR(selLepton_lead->p4(), selLepton_third->p4()),
      deltaR(selLepton_third->p4(), selLepton_sublead->p4())
    });
    bool hasSFOS = isSFOS(selLeptons);
    double min_Deta_mostfwdJet_jet = 0;
    double min_Deta_leadfwdJet_jet = 0;
    // take the highest eta selJetsForward
    Particle::LorentzVector mostFwdJet = HighestEtaFwdJet(selJetsForward);
    if (selJetsForward.size() > 0 && selJets.size() > 0)
    {
      min_Deta_mostfwdJet_jet = min_Deta_fwdJet_jet(mostFwdJet, selJets);
      Particle::LorentzVector leadFwdJet = selJetsForward[0]-> p4();
      min_Deta_leadfwdJet_jet = min_Deta_fwdJet_jet(leadFwdJet, selJets);
    }

    double dr_lss  = 0.;
    double dr_los1 = 0.;
    double dr_los2 = 0.;
    double eta_los1 = 0.;
    double eta_los2 = 0.;
    // it does not assume mis-charge identification
    if (selLepton_lead->charge()*selLepton_sublead->charge() > 0){
      dr_lss  = deltaR(selLepton_sublead -> p4(), selLepton_lead -> p4());
      dr_los1 = deltaR(selLepton_third -> p4(), selLepton_lead -> p4());
      dr_los2 = deltaR(selLepton_third  -> p4(), selLepton_sublead -> p4());
      eta_los1 = std::abs(selLepton_third -> eta() - selLepton_lead -> eta());
      eta_los2 = std::abs(selLepton_third  -> eta() - selLepton_sublead -> eta());
    } else {
      dr_lss  = deltaR(selLepton_third -> p4(), selLepton_lead -> p4());
      dr_los1 = deltaR(selLepton_sublead -> p4(), selLepton_third -> p4());
      dr_los2 = deltaR(selLepton_sublead  -> p4(), selLepton_lead -> p4());
      eta_los1 = std::abs(selLepton_sublead -> eta() - selLepton_third -> eta());
      eta_los2 = std::abs(selLepton_sublead  -> eta() - selLepton_lead -> eta());
    }
    double eta_los = 0.;
    if (dr_los1 < dr_los2) eta_los = eta_los1;
    else eta_los = eta_los2;

    mvaInputs_3l_ttH_tH_3cat_v8_TF["avg_dr_jet"]                 = avg_dr_jet;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["ptmiss"] = met.pt();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["mbb_medium"] = mbb;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["jet1_pt"] = selJets.size() > 0 ? selJets[0]->pt() : 0;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["jet2_pt"] = selJets.size() > 1 ? selJets[1]->pt() : 0;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["jet3_pt"] = selJets.size() > 2 ? selJets[2]->pt() : 0;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["jet4_pt"] = selJets.size() > 3 ? selJets[3]->pt() : 0;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["max_Lep_eta"] = max_lep_eta;
    //mvaInputs_3l_ttH_tH_3cat_v8_TF["lep_min_dr_jet"] = lep_min_dr_jet;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["mT_lep1"] = mT_lep1;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["lep1_conePt"] = lep1_conePt;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["mT_lep2"] = mT_lep2;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["lep2_conePt"] = lep2_conePt;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["mT_lep3"] = mT_lep3;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["lep3_conePt"] = lep3_conePt;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["leadFwdJet_pt"] = selJetsForward.size() > 0 ? selJetsForward[0]->pt() : 0;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["res_HTT"] = max_mvaOutput_HTT_CSVsort4rd;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["HadTop_pt"] = HadTop_pt_CSVsort4rd;
    mvaInputs_3l_ttH_tH_3cat_v8_TF["nJet"] = selJets.size();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["nJetForward"] = selJetsForward.size();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["nBJetLoose"] = selBJets_loose.size();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["nBJetMedium"] = selBJets_medium.size();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["nElectron"] = selElectrons.size();
    mvaInputs_3l_ttH_tH_3cat_v8_TF["sum_Lep_charge"] = sumLeptonCharge;
    //mvaInputs_3l_ttH_tH_3cat_v8_TF["mvaOutput_Hj_tagger"] = Hj_tagger_fromCSVsort4th;
    std::map<std::string, double> mvaOutput_3l_ttH_tH_3cat_v8_TF = mva_3l_ttH_tH_3cat_v8_TF(mvaInputs_3l_ttH_tH_3cat_v8_TF);
    if ( isDebugTF ) {
      std::cout << "result v8 ";
      for (auto elem : classes_TensorFlow_3l_ttH_tH_3cat ) std::cout << elem << " = " << mvaOutput_3l_ttH_tH_3cat_v8_TF[elem] <<" ";
      std::cout << std::endl;
    }

    std::string category = "output_NN_3l_ttH_tH_3cat_v8_";
    double output_NN_3l_ttH_tH_3cat_v8 = -10.0;
    if (passEvents) {

      if (
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"] >= mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"] &&\
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"] >= mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"]
      ) {
        category += "ttH";
        output_NN_3l_ttH_tH_3cat_v8 = mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"];
      }
      if (
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"] >  mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"] &&\
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"] >= mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"]
      ) {
        category += "tH";
        output_NN_3l_ttH_tH_3cat_v8 = mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"];
        }
      if (
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"] > mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"] &&\
        mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"] > mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"]
      ) {
        category += "rest";
        output_NN_3l_ttH_tH_3cat_v8 = mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"];
        }

      if (selBJets_medium.size() >= 2) category += "_bt";
      else category += "_bl";

    }
    else if(isControlRegion)
    {
      category += "cr";
    }
    else assert(0);

    /*
    "lep1_conePt", "lep1_eta", "lep1_phi",
    "lep2_conePt", "lep2_eta", "lep2_phi",
    "lep3_conePt", "lep3_eta", "lep3_phi",
    "mindr_lep1_jet", "mindr_lep2_jet", "mindr_lep3_jet", "min_dr_Lep",
    "avg_dr_jet", "met_LD", "mbb_loose",
    "leadFwdJet_eta", "leadFwdJet_pt", "min_Deta_leadfwdJet_jet",
    "jet1_pt", "jet1_eta", "jet1_phi",
    "jet2_pt", "jet2_eta", "jet2_phi",
    "jet3_pt", "jet3_eta", "jet3_phi",
    "sum_Lep_charge", "HadTop_pt", "res_HTT",
    "nJet", "nBJetLoose", "nBJetMedium", "nJetForward", "nElectron", "has_SFOS"
    */
    std::map<std::string, double> mvaInputVariables_NN = {
      {"lep1_conePt",     lep1_conePt},
      {"lep1_eta",        selLepton_lead -> absEta()},
      {"lep1_phi",        selLepton_lead -> phi()},
      {"mindr_lep1_jet",  mindr_lep1_jet},
      {"lep2_conePt",     lep2_conePt},
      {"lep2_eta",        selLepton_sublead -> absEta()},
      {"lep2_phi",        selLepton_sublead -> phi()},
      {"mindr_lep2_jet",  mindr_lep2_jet},
      {"lep3_conePt",     lep3_conePt},
      {"lep3_eta",        selLepton_third -> absEta()},
      {"lep3_phi",        selLepton_third -> phi()},
      {"mindr_lep3_jet",  mindr_lep3_jet},
      {"avg_dr_jet",      avg_dr_jet},
      {"met_LD",          met_LD},
      {"mbb_loose",       selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : 0},
      {"min_dr_Lep",      min_dr_lep},
      {"leadFwdJet_eta",  selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : 0.},
      {"leadFwdJet_pt",   selJetsForward.size() > 0 ? selJetsForward[0] -> pt()     : 0.},
      {"min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet},
      {"jet1_pt",         selJets[0]->pt()},
      {"jet1_eta",        selJets[0]->absEta()},
      {"jet1_phi",        selJets[0]->phi()},
      {"jet2_pt",         selJets.size() > 1 ?  selJets[1]->pt()  : 0.},
      {"jet2_eta",        selJets.size() > 1 ?  selJets[1]->absEta() : 0.},
      {"jet2_phi",        selJets.size() > 1 ?  selJets[1]->phi() : 0.},
      {"jet3_pt",         selJets.size() > 2 ?  selJets[2]->pt()  : 0.},
      {"jet3_eta",        selJets.size() > 2 ?  selJets[2]->absEta() : 0.},
      {"jet3_phi",        selJets.size() > 2 ?  selJets[2]->phi() : 0.},
      {"sum_Lep_charge",  selLepton_lead -> charge() + selLepton_sublead -> charge() + selLepton_third->charge()},
      {"HadTop_pt",       HadTop_pt_CSVsort4rd},
      {"res_HTT",         max_mvaOutput_HTT_CSVsort4rd},
      {"nJet",            selJets.size()},
      {"nBJetLoose",      selBJets_loose.size()},
      {"nBJetMedium",     selBJets_medium.size()},
      {"nJetForward",     selJetsForward.size()},
      {"nElectron",       selElectrons.size()},
      {"has_SFOS",        hasSFOS}
      };
      std::map<std::string, double> mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF = mva_3l_sig_2_rest_2p5_th_2_withWZ_TF(mvaInputVariables_NN);
      std::map<std::string, double> mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF = mva_3l_sig_2p5_rest_2_th_2p5_withWZ_TF(mvaInputVariables_NN);
      std::map<std::string, double> mvaOutput_sig_2_rest_2_th_2_withWZ_TF = mva_3l_sig_2_rest_2_th_2_withWZ_TF(mvaInputVariables_NN);
      if ( isDebugTF ) {
        std::cout << "variables ";
        for (auto elem : mvaInputVariables_NN) std::cout << elem.first << " " << elem.second << "\n";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "result mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF ";
        for (auto elem : classes_TensorFlow_3l_ttH_tH_3cat ) std::cout << elem << " = " << mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF[elem] <<" ";
        std::cout << std::endl;
        std::cout << "result mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF ";
        for (auto elem : classes_TensorFlow_3l_ttH_tH_3cat ) std::cout << elem << " = " << mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF[elem] <<" ";
        std::cout << std::endl;
        std::cout << "result  mvaOutput_sig_2_rest_2_th_2_withWZ_TF ";
        for (auto elem : classes_TensorFlow_3l_ttH_tH_3cat ) std::cout << elem << " = " << mvaOutput_sig_2_rest_2_th_2_withWZ_TF[elem] <<" ";
        std::cout << std::endl;
      }

    std::string category_sig_2_rest_2_th_2_withWZ = "output_NN_sig_2_rest_2_th_2_withWZ_";
    double output_NN_sig_2_rest_2_th_2_withWZ = -10.0;
    if (passEvents) {

      if (
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_rest"] &&\
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_tH"]
      ) {
        category_sig_2_rest_2_th_2_withWZ += "ttH";
        output_NN_sig_2_rest_2_th_2_withWZ = mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_ttH"];
      }
      if (
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_tH"] >  mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_ttH"] &&\
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_tH"] >= mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_rest"]
      ) {
        category_sig_2_rest_2_th_2_withWZ += "tH";
        output_NN_sig_2_rest_2_th_2_withWZ = mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_tH"];
        }
      if (
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_rest"] > mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_ttH"] &&\
        mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_rest"] > mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_tH"]
      ) {
        category_sig_2_rest_2_th_2_withWZ += "rest";
        output_NN_sig_2_rest_2_th_2_withWZ = mvaOutput_sig_2_rest_2_th_2_withWZ_TF["predictions_rest"];
        if ( selElectrons.size() == 3) category_sig_2_rest_2_th_2_withWZ += "_eee";
        if ( selElectrons.size() == 2) category_sig_2_rest_2_th_2_withWZ += "_eem";
        if ( selElectrons.size() == 1) category_sig_2_rest_2_th_2_withWZ += "_emm";
        if ( selElectrons.size() == 0) category_sig_2_rest_2_th_2_withWZ += "_mmm";
        }

      if ( category_sig_2_rest_2_th_2_withWZ.find("_eee") == std::string::npos)
      {
        if (selBJets_medium.size() >= 2) category_sig_2_rest_2_th_2_withWZ += "_bt";
        else category_sig_2_rest_2_th_2_withWZ += "_bl";
      }

    }
    else if(isControlRegion)
    {
      category_sig_2_rest_2_th_2_withWZ += "cr";
    }
    else assert(0);

  std::string category_sig_2_rest_2p5_th_2_withWZ = "output_NN_sig_2_rest_2p5_th_2_withWZ_";
  double output_NN_sig_2_rest_2p5_th_2_withWZ = -10.0;
  if (passEvents) {

    if (
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_rest"] &&\
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_tH"]
    ) {
      category_sig_2_rest_2p5_th_2_withWZ += "ttH";
      output_NN_sig_2_rest_2p5_th_2_withWZ = mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_ttH"];
    }
    if (
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_tH"] >  mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_ttH"] &&\
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_tH"] >= mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_rest"]
    ) {
      category_sig_2_rest_2p5_th_2_withWZ += "tH";
      output_NN_sig_2_rest_2p5_th_2_withWZ = mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_tH"];
      }
    if (
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_rest"] > mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_ttH"] &&\
      mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_rest"] > mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_tH"]
    ) {
      category_sig_2_rest_2p5_th_2_withWZ += "rest";
      output_NN_sig_2_rest_2p5_th_2_withWZ = mvaOutput_sig_2_rest_2p5_th_2_withWZ_TF["predictions_rest"];
      if ( selElectrons.size() == 3) category_sig_2_rest_2p5_th_2_withWZ += "_eee";
      if ( selElectrons.size() == 2) category_sig_2_rest_2p5_th_2_withWZ += "_eem";
      if ( selElectrons.size() == 1) category_sig_2_rest_2p5_th_2_withWZ += "_emm";
      if ( selElectrons.size() == 0) category_sig_2_rest_2p5_th_2_withWZ += "_mmm";
      }

    if (selBJets_medium.size() >= 2) category_sig_2_rest_2p5_th_2_withWZ += "_bt";
    else category_sig_2_rest_2p5_th_2_withWZ += "_bl";

  }
  else if(isControlRegion)
  {
    category_sig_2_rest_2p5_th_2_withWZ += "cr";
  }
  else assert(0);

  std::string category_sig_2p5_rest_2_th_2p5_withWZ = "output_NN_sig_2p5_rest_2_th_2p5_withWZ_";
  double output_NN_sig_2p5_rest_2_th_2p5_withWZ = -10.0;
  if (passEvents) {

    if (
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_rest"] &&\
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_ttH"] >= mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_tH"]
    ) {
      category_sig_2p5_rest_2_th_2p5_withWZ += "ttH";
      output_NN_sig_2p5_rest_2_th_2p5_withWZ = mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_ttH"];
    }
    if (
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_tH"] >  mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_ttH"] &&\
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_tH"] >= mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_rest"]
    ) {
      category_sig_2p5_rest_2_th_2p5_withWZ += "tH";
      output_NN_sig_2p5_rest_2_th_2p5_withWZ = mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_tH"];
      }
    if (
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_rest"] > mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_ttH"] &&\
      mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_rest"] > mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_tH"]
    ) {
      category_sig_2p5_rest_2_th_2p5_withWZ += "rest";
      output_NN_sig_2p5_rest_2_th_2p5_withWZ = mvaOutput_sig_2p5_rest_2_th_2p5_withWZ_TF["predictions_rest"];
      if ( selElectrons.size() == 3) category_sig_2p5_rest_2_th_2p5_withWZ += "_eee";
      if ( selElectrons.size() == 2) category_sig_2p5_rest_2_th_2p5_withWZ += "_eem";
      if ( selElectrons.size() == 1) category_sig_2p5_rest_2_th_2p5_withWZ += "_emm";
      if ( selElectrons.size() == 0) category_sig_2p5_rest_2_th_2p5_withWZ += "_mmm";
      }

    if (selBJets_medium.size() >= 2) category_sig_2p5_rest_2_th_2p5_withWZ += "_bt";
    else category_sig_2p5_rest_2_th_2p5_withWZ += "_bl";

  }
  else if(isControlRegion)
  {
    category_sig_2p5_rest_2_th_2p5_withWZ += "cr";
  }
  else assert(0);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 (10) of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_3l = -1;
    if      ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 5.;
    else if ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 4.;
    else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 3.;
    else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 2.;
    else                                                                mvaDiscr_3l = 1.;

//--- retrieve gen-matching flags
    std::vector<const GenMatchEntry*> genMatches = genMatchInterface.getGenMatch(selLeptons);

//--- fill histograms with events passing final selection
    std::string ctrl_category = "other";
    if(isControlRegion)
    {
      const int nbjets_ctrl = std::min(static_cast<int>(selBJets_medium.size()), 2);
      const int njets_ctrl = std::max(std::min(static_cast<int>(selJets.size()), std::min(nbjets_ctrl + 4, 5)), std::min(2, nbjets_ctrl + 1));
      const int nele_ctrl = std::count_if(
        selLeptons.cbegin(), selLeptons.cend(), [](const RecoLepton * const lepton) -> bool { return lepton->is_electron(); }
      );
      const int nmu_ctrl = std::count_if(
        selLeptons.cbegin(), selLeptons.cend(), [](const RecoLepton * const lepton) -> bool { return lepton->is_muon(); }
      );
      assert((nele_ctrl + nmu_ctrl) == 3);
      const std::string ele_ctrl_str(nele_ctrl, 'e');
      const std::string mu_ctrl_str(nmu_ctrl, 'm');
      ctrl_category = Form("b%d_j%d_%s%s", nbjets_ctrl, njets_ctrl, ele_ctrl_str.data(), mu_ctrl_str.data());
      if(std::find(ctrl_categories.cbegin(), ctrl_categories.cend(), ctrl_category) == ctrl_categories.cend())
      {
        throw cmsException("analyze_3l", __LINE__) << "Unexpected CR category: " << ctrl_category;
      }
    }
    for(const std::string & central_or_shift: central_or_shifts_local)
    {
      const double evtWeight = evtWeightRecorder.get(central_or_shift);
      const bool skipFilling = central_or_shift != central_or_shift_main;
      for (const GenMatchEntry* genMatch : genMatches)
      {
        selHistManagerType* selHistManager = selHistManagers[central_or_shift][genMatch->getIdx()];
        assert(selHistManager);
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
          selHistManager->mvaInputVariables_3l_->fillHistograms(mvaInputVariables_NN, evtWeight);
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
          if(isMC_tH)
          {
            const std::string evt_cat_str_query = evt_cat_str == default_cat_str ? get_tH_SM_str() : evt_cat_str;
            tH_weight_map[evt_cat_str] = evtWeight / evtWeight_tH_nom * eventInfo.genWeight_tH(central_or_shift_tH, evt_cat_str_query);
          }
          else if(apply_HH_rwgt)
          {
            tH_weight_map[evt_cat_str] = evtWeight * Weight_ktScan[evt_cat_str] / HHWeight;
          }
          else
          {
            tH_weight_map[evt_cat_str] = evtWeight;
          }
        }

        for(const auto & kv: tH_weight_map)
        {
          /*
          categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ,
          categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ,
          categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ
          */
          EvtHistManager_3l* selHistManager_evt = selHistManager->evt_[kv.first];
          if ( selHistManager_evt )
          {
            selHistManager_evt->fillHistograms(
            selElectrons.size(), selMuons.size(), selHadTaus.size(),
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
            ctrl_category,
            mvaOutput_3l_ttV, mvaOutput_3l_ttbar, mvaDiscr_3l,
            output_NN_3l_ttH_tH_3cat_v8, category,
            output_NN_sig_2_rest_2_th_2_withWZ, category_sig_2_rest_2_th_2_withWZ,
            output_NN_sig_2p5_rest_2_th_2p5_withWZ, category_sig_2p5_rest_2_th_2p5_withWZ,
            output_NN_sig_2_rest_2p5_th_2_withWZ, category_sig_2_rest_2p5_th_2_withWZ,
            memOutput_3l_matched.is_initialized() ? &memOutput_3l_matched : nullptr,
            kv.second
          );
          }
        }

        if(isSignal)
        {
          std::string decayModeStr = get_key_hist(eventInfo, genWBosons, isMC_HH, isMC_VH);
          if ( ( isMC_tH || isMC_H ) && ( decayModeStr == "hzg" || decayModeStr == "hmm" ) ) continue;
          if(! decayModeStr.empty())
          {
            for(const auto & kv: tH_weight_map)
            {
              EvtHistManager_3l* selHistManager_evt_decay = selHistManager->evt_in_decayModes_[kv.first][decayModeStr];
              if ( selHistManager_evt_decay )
              {
                selHistManager_evt_decay -> fillHistograms(
                selElectrons.size(),
                selMuons.size(),
                selHadTaus.size(),
                selJets.size(),
                selBJets_loose.size(),
                selBJets_medium.size(),
                ctrl_category,
                mvaOutput_3l_ttV,
                mvaOutput_3l_ttbar,
                mvaDiscr_3l,
                output_NN_3l_ttH_tH_3cat_v8, category,
                output_NN_sig_2_rest_2_th_2_withWZ, category_sig_2_rest_2_th_2_withWZ,
                output_NN_sig_2p5_rest_2_th_2p5_withWZ, category_sig_2p5_rest_2_th_2p5_withWZ,
                output_NN_sig_2_rest_2p5_th_2_withWZ, category_sig_2_rest_2p5_th_2_withWZ,
                memOutput_3l_matched.is_initialized() ? &memOutput_3l_matched : nullptr,
                kv.second
              );
              }
            }
            std::string decayMode_and_genMatch = decayModeStr;
            if ( apply_leptonGenMatching ) decayMode_and_genMatch += selLepton_genMatch.name_;
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

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.str() << '\n';
    }

    bool isGenMatched = false;
    if ( isMC )
    {
      for (const GenMatchEntry* genMatch : genMatches)
      {
	if ( genMatch->getName() == "" ) isGenMatched = true; // non-fake
      }
    }

    if ( bdt_filler ) {
      double lep1_genLepPt = ( selLepton_lead->genLepton()    ) ? selLepton_lead->genLepton()->pt()    : 0.;
      double lep2_genLepPt = ( selLepton_sublead->genLepton() ) ? selLepton_sublead->genLepton()->pt() : 0.;
      double lep3_genLepPt = ( selLepton_third->genLepton()   ) ? selLepton_third->genLepton()->pt()   : 0.;

      double prob_fake_lepton_lead = 1.0; // evtWeightRecorder.get_jetToLepton_FR_lead(central_or_shift_main);
      double prob_fake_lepton_sublead = 1.0; // = evtWeightRecorder.get_jetToLepton_FR_sublead(central_or_shift_main);
      double prob_fake_lepton_third = 1.0; // = evtWeightRecorder.get_jetToLepton_FR_third(central_or_shift_main);

      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("lep1_pt",             selLepton_lead -> pt())
          ("lep1_conePt",         lep1_conePt)
          ("lep1_eta",            selLepton_lead -> eta())
          ("lep1_phi",            selLepton_lead -> phi())
          ("lep1_tth_mva",        selLepton_lead -> mvaRawTTH())
          ("mindr_lep1_jet",      TMath::Min(10., mindr_lep1_jet))
          ("mT_lep1",             comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi()))
          ("lep2_pt",             selLepton_sublead -> pt())
          ("lep2_conePt",         lep2_conePt)
          ("lep2_eta",            selLepton_sublead -> eta())
          ("lep2_phi",            selLepton_sublead -> phi())
          ("lep2_tth_mva",        selLepton_sublead -> mvaRawTTH())
          ("mindr_lep2_jet",      TMath::Min(10., mindr_lep2_jet))
          ("mT_lep2",             comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi()))
          ("lep3_pt",             selLepton_third -> pt())
          ("lep3_conePt",         lep3_conePt)
          ("lep3_eta",            selLepton_third -> eta())
          ("lep3_phi",            selLepton_third -> phi())
          ("lep3_tth_mva",        selLepton_third -> mvaRawTTH())
          ("mindr_lep3_jet",      TMath::Min(10., mindr_lep3_jet))
          ("mT_lep3",             comp_MT_met_lep1(*selLepton_third, met.pt(), met.phi()))
          ("avg_dr_jet",          avg_dr_jet)
          ("ptmiss",              met.pt())
          ("htmiss",              mht_p4.pt())
          ("met_LD",              met_LD)
          ("dr_leps",             deltaR(selLepton_lead -> p4(), selLepton_sublead -> p4()))
          ("lep1_genLepPt",       (selLepton_lead->genLepton() != 0) ? selLepton_lead->genLepton()->pt() : 0.)
          ("lep2_genLepPt",       (selLepton_sublead->genLepton() != 0) ? selLepton_sublead->genLepton() ->pt() : 0.)
          ("lep3_genLepPt",       (selLepton_third->genLepton() != 0) ? selLepton_third->genLepton() ->pt() : 0.)
          ("lep1_frWeight",       lep1_genLepPt > 0 ? 1.0 : prob_fake_lepton_lead)
          ("lep2_frWeight",       lep2_genLepPt > 0 ? 1.0 : prob_fake_lepton_sublead)
          ("lep3_frWeight",       lep3_genLepPt > 0 ? 1.0 : prob_fake_lepton_third)
          ("lep1_fake_prob",      prob_fake_lepton_lead)
          ("lep2_fake_prob",      prob_fake_lepton_sublead)
          ("lep3_fake_prob",      prob_fake_lepton_third)
          ("mvaOutput_3l_ttV",    mvaOutput_3l_ttV)
          ("mvaOutput_3l_ttbar",  mvaOutput_3l_ttbar)
          ("mvaDiscr_3l",         mvaDiscr_3l)
	  ("memOutput_isValid",   memOutput_3l_matched.is_initialized() ? memOutput_3l_matched.isValid() : -1.)
	  ("memOutput_errorFlag", memOutput_3l_matched.is_initialized() ? memOutput_3l_matched.errorFlag() : -1.)
          ("memOutput_ttH",       memOutput_ttH)
          ("memOutput_tHq",       memOutput_tHq)
          ("memOutput_ttW",       memOutput_ttW)
          ("memOutput_ttZ",       memOutput_ttZ)
          ("memOutput_tt",        memOutput_tt)
          ("memOutput_LR",        memOutput_LR.at(mem_option_main))
          ("lumiScale",           evtWeightRecorder.get_lumiScale(central_or_shift_main))
          ("genWeight",           eventInfo.genWeight)
          ("evtWeight",           evtWeightRecorder.get(central_or_shift_main))
          ("mbb_loose",           selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1000 )
          ("mbb_medium",          selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : -1000 )
          ("nJet",                selJets.size())
          ("nBJetLoose",          selBJets_loose.size())
          ("nBJetMedium",         selBJets_medium.size())
          ("lep1_isTight",        int(selLepton_lead -> isTight()))
          ("lep2_isTight",        int(selLepton_sublead -> isTight()))
          ("lep3_isTight",        int(selLepton_third -> isTight()))
          ("dr_Lep_lss",              dr_lss)
          ("dr_Lep_los1",             dr_los1)
          ("dr_Lep_los2",             dr_los2)
          ("eta_LepLep_los1",            eta_los1)
          ("eta_LepLep_los2",            eta_los2)
          ("eta_LepLep_los",             eta_los) // for min dr section 4.1 of arXiv:1404.1278
          ("hadtruth",            hadtruth)
          ("mostFwdJet_eta",      selJetsForward.size() > 0 ? std::abs(mostFwdJet.Eta()) : -1000)
          ("mostFwdJet_pt",       selJetsForward.size() > 0 ? mostFwdJet.pt() : -1000)
          ("mostFwdJet_phi",      selJetsForward.size() > 0 ? mostFwdJet.phi() : -1000)
          ("mostFwdJet_E",        selJetsForward.size() > 0 ? mostFwdJet.energy() : -1000)
          ("leadFwdJet_eta",      selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : -1000)
          ("leadFwdJet_pt",       selJetsForward.size() > 0 ? selJetsForward[0] -> pt() : -1000)
          ("leadFwdJet_phi",      selJetsForward.size() > 0 ? selJetsForward[0] -> phi() : -1000)
          ("leadFwdJet_E",        selJetsForward.size() > 0 ? selJetsForward[0] -> p4().energy() : -1000)
          ("min_dr_Lep",          min_dr_lep)
          ("max_dr_Lep",          max_dr_lep)
          ("jet1_pt",   selJets.size() > 0 ? selJets[0]->pt() : -1000)
          ("jet1_eta",  selJets.size() > 0 ? selJets[0]->eta() : -1000)
          ("jet1_phi",  selJets.size() > 0 ? selJets[0]->phi() : -1000)
          ("jet1_E",    selJets.size() > 0 ? selJets[0]->p4().energy() : -1000)
          ("jet2_pt",   selJets.size() > 1 ? selJets[1]->pt() : -1000)
          ("jet2_eta",  selJets.size() > 1 ? selJets[1]->eta() : -1000)
          ("jet2_phi",  selJets.size() > 1 ? selJets[1]->phi() : -1000)
          ("jet2_E",    selJets.size() > 1 ? selJets[1]->p4().energy() : -1000)
          ("jet3_pt",   selJets.size() > 2 ? selJets[2]->pt() : -1000)
          ("jet3_eta",  selJets.size() > 2 ? selJets[2]->eta() : -1000)
          ("jet3_phi",  selJets.size() > 2 ? selJets[2]->phi() : -1000)
          ("jet3_E",    selJets.size() > 2 ? selJets[2]->p4().energy() : -1000)
          ("jet4_pt",   selJets.size() > 3 ? selJets[3]->pt() : -1000)
          ("jet4_eta",  selJets.size() > 3 ? selJets[3]->eta() : -1000)
          ("jet4_phi",  selJets.size() > 3 ? selJets[3]->phi() : -1000)
          ("jet4_E",    selJets.size() > 3 ? selJets[3]->p4().energy() : -1000)
          ("sum_Lep_charge", sumLeptonCharge)
          ("HadTop_pt",      HadTop_pt_CSVsort4rd)
          ("res_HTT",        max_mvaOutput_HTT_CSVsort4rd)
          ("max_Lep_eta",    max_lep_eta)
          ("massLT",          selLeptons.size() > 1 ? comp_MT_met_lep1(selLeptons[0]->p4() + selLeptons[1]->p4(), met.pt(), met.phi())  : 0.)
          ("massL3",          selLeptons.size() > 2 ? comp_MT_met_lep1(selLeptons[0]->p4() + selLeptons[1]->p4() + selLeptons[2]->p4(), met.pt(), met.phi())  : 0.)
          ("massL_FO",           massL(fakeableLeptons))
          ("massL",           massL(selLeptons))
          ("has_SFOS",       hasSFOS)
          ("min_Deta_mostfwdJet_jet", min_Deta_mostfwdJet_jet)
          ("min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet)
          ("nElectron",                      selElectrons.size())
          ("nJetForward",          selJetsForward.size())
        .fill()
      ;
    }

    if(snm)
    {
      const int nLightJet            = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(looseHadTaus);
      snm->read(selJets, false);
      snm->read(selJetsForward, true);

      snm->read({
        triggers_1e, triggers_1mu, triggers_2e, triggers_1e1mu, triggers_2mu,
        triggers_3e, triggers_2e1mu, triggers_1e2mu, triggers_3mu
      });
      snm->read(
        isGenMatched, selBJets_medium.size(), selBJets_loose.size(), nLightJet,
        SyncNtupleManager::placeholder_value, is_tH_like_and_not_ttH_like
      );

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
      snm->read(mT_lep3,                                FloatVariableType::mT_met_lep3);
      // mT_met_lep4 not filled
      snm->read(massL(fakeableLeptons),                 FloatVariableType::massL);

      // mTauTauVis not filled
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

      // mvaOutput_2lss_ttV not filled
      // mvaOutput_2lss_tt not filled
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

      snm->read(evtWeightRecorder.get_FR(central_or_shift_main),             FloatVariableType::FR_weight);
      snm->read(evtWeightRecorder.get_sf_triggerEff(central_or_shift_main),  FloatVariableType::triggerSF_weight);
      snm->read(evtWeightRecorder.get_leptonSF(),                            FloatVariableType::leptonSF_weight);
      // tauSF_weight not filled
      snm->read(evtWeightRecorder.get_btag(central_or_shift_main),           FloatVariableType::bTagSF_weight);
      snm->read(evtWeightRecorder.get_puWeight(central_or_shift_main),       FloatVariableType::PU_weight);
      snm->read(evtWeightRecorder.get_genWeight(),                           FloatVariableType::MC_weight);

      // mvaOutput_2lss_ttV not filled
      // mvaOutput_2lss_tt not filled
      // mvaOutput_2lss_1tau_plainKin_tt not filled
      // mvaOutput_2lss_1tau_plainKin_ttV not filled
      // mvaOutput_2lss_1tau_plainKin_1B_M not filled
      // mvaOutput_2lss_1tau_plainKin_SUM_M not filled
      // mvaOutput_2lss_1tau_HTT_SUM_M not filled
      // mvaOutput_2lss_1tau_HTTMEM_SUM_M not filled

      // mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH not filled
      // mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_tH not filled
      // mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW not filled
      // mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_rest not filled

      snm->read(mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_ttH"],  FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_ttH);
      snm->read(mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_tH"],   FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_tH);
      snm->read(mvaOutput_3l_ttH_tH_3cat_v8_TF["predictions_rest"], FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_rest);

      snm->read(memOutput_ttH,                          FloatVariableType::Integral_ttH);
      snm->read(memOutput_tHq,                          FloatVariableType::Integral_tHq);
      snm->read(memOutput_ttW,                          FloatVariableType::Integral_ttW);
      snm->read(memOutput_ttZ,                          FloatVariableType::Integral_ttZ);
      // Integral_ttZ_Zll not filled
      snm->read(memOutput_tt,                           FloatVariableType::Integral_ttbar);
      // integration_type not filled
      snm->read(memOutput_LR.at(MEMsys::nominal),       FloatVariableType::MEM_LR);
      snm->read(memOutput_LR.at(MEMsys::up),            FloatVariableType::MEM_LR_up);
      snm->read(memOutput_LR.at(MEMsys::down),          FloatVariableType::MEM_LR_down);

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
    std::string process_and_genMatch = process_string;
    process_and_genMatch += selLepton_genMatch.name_;
    ++selectedEntries_byGenMatchType[process_and_genMatch];
    selectedEntries_weighted_byGenMatchType[process_and_genMatch] += evtWeightRecorder.get(central_or_shift_main);
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

  std::cout << "sel. Entries by gen. matching:" << std::endl;
  for(const std::string & central_or_shift: central_or_shifts_local)
  {
    std::cout << "central_or_shift = " << central_or_shift << '\n';
    for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
    {
      std::string process_and_genMatch = process_string;
      process_and_genMatch += leptonGenMatch_definition.name_;
      std::cout << " " << process_and_genMatch << " = " << selectedEntries_byGenMatchType[process_and_genMatch]
		<< " (weighted = " << selectedEntries_weighted_byGenMatchType[process_and_genMatch] << ")" << std::endl;
    }
  }
  std::cout << std::endl;

//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete dataToMCcorrectionInterface;

  delete leptonFakeRateInterface;

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
  delete cutFlowHistManager;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;
  delete snm;

  clock.Show("analyze_3l");

  return EXIT_SUCCESS;
}
