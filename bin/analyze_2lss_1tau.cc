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
#include <TMatrixD.h> // TMatrixD
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::
#include <TH2.h> // TH2
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
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions_Hj_and_Hjj_taggers.h" // comp_mvaOutput_Hj_tagger, comp_mvaOutput_Hjj_tagger
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_2lss_1tau.h" // MEMOutputReader_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h" // EvtHistManager_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet tags
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/GenMatchInterface.h" // GenMatchInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface.h" // HHWeightInterface
#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"

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

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton, kFR_3L, kFR_1tau };

/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
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

  std::cout << "<analyze_2lss_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_2lss_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_2lss_1tau")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_2lss_1tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tH = process_string == "tHq" || process_string == "tHW";
  const bool isMC_VH = process_string == "VH";
  const bool isMC_WZ = process_string == "WZ";
  const bool isMC_H  = process_string == "ggH" || process_string == "qqH" || process_string == "TTWH" || process_string == "TTZH";
  const bool isMC_HH = process_string == "HH";
  const bool isMC_signal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  const bool isSignal = isMC_signal || isMC_tH || isMC_VH || isMC_HH || isMC_H;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);
  const unsigned int skipEvery = cfg_analyze.getParameter<unsigned int>("skipEvery");

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e, "triggers_1e");
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e, "triggers_2e");
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu, "triggers_1mu");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu, "triggers_2mu");
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu, "triggers_1e1mu");
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
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonChargeFlipGenMatchEntry> leptonGenMatch_definitions = getLeptonChargeFlipGenMatch_definitions_2lepton(true);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;
  const TauID tauId = TauID_PyMap.at(hadTauSelection_part2.substr(0, 7));
  int tauLevel = get_tau_id_wp_int(hadTauSelection_part2);
  std::string hadTauSelection_veto = cfg_analyze.getParameter<std::string>("hadTauSelection_veto");

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_1tau(true);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  GenMatchInterface genMatchInterface(2, apply_leptonGenMatching, true, 1, apply_hadTauGenMatching);

  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS" ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS" ) chargeSumSelection = kSS;
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

  bool apply_lepton_and_hadTauCharge_cut = cfg_analyze.getParameter<bool>("apply_lepton_and_hadTauCharge_cut");
  std::cout << "apply_lepton_and_hadTauCharge_cut = " << apply_lepton_and_hadTauCharge_cut << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift_main = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::vector<std::string> central_or_shifts_local = cfg_analyze.getParameter<std::vector<std::string>>("central_or_shifts_local");
  const bool do_tree = (isSignal || isMC_WZ || process_string == "TTW" || process_string == "TTZ" || process_string == "TT") && !(central_or_shifts_local.size() > 1);

  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_l1PreFireWeight = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");
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

  edm::ParameterSet triggerWhiteList;
  if(! isMC)
  {
    triggerWhiteList = cfg_analyze.getParameter<edm::ParameterSet>("triggerWhiteList");
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
    default: throw cmsException("analyze_2lss_1tau", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else if ( applyFakeRateWeights_string == "3L"       ) applyFakeRateWeights = kFR_3L;
  else if ( applyFakeRateWeights_string == "1tau"     ) applyFakeRateWeights = kFR_1tau;
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  std::cout << "Applying fake rate weights = " << applyFakeRateWeights_string << " (" << applyFakeRateWeights << ")\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L || applyFakeRateWeights == kFR_1tau || apply_hadTauFakeRateSF ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight);
  }
  std::cout << "Applying jetToTauFakeRate fake rate weights = " << applyFakeRateWeights_string << " (" << applyFakeRateWeights << ")\n";

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

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  bool ignoreMEMerrors = cfg_analyze.getParameter<bool>("ignoreMEMerrors");

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
    const std::vector<std::string> evt_cat_tH_strs = eventInfo.getWeight_tH_str(central_or_shift_main);
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
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauSelection_part2);
  RecoHadTauSelectorTight tightHadTauFilter(era, -1, isDEBUG);
  tightHadTauFilter.set(hadTauSelection_part2);
  switch(hadTauSelection)
  {
    case kFakeable: tauLevel = std::min(tauLevel, get_tau_id_wp_int(fakeableHadTauSelector.getSelector().get())); break;
    case kTight:    tauLevel = std::min(tauLevel, get_tau_id_wp_int(tightHadTauSelector.getSelector().get()));    break;
    default: assert(0);
  }

  // CV: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 2l+2tau category
  RecoHadTauCollectionSelectorLoose vetoHadTauSelector(era, -1, isDEBUG);
  vetoHadTauSelector.set(hadTauSelection_veto);

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
  MEMOutputReader_2lss_1tau* memReader = 0;
  if ( branchName_memOutput != "" ) {
    memReader = new MEMOutputReader_2lss_1tau(Form("n%s", branchName_memOutput.data()), branchName_memOutput);
    inputTree -> registerReader(memReader);
  }

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

  //--- initialize hadronic top tagger BDT
  HadTopTagger* hadTopTagger = new HadTopTagger();

//--- initialize BDTs used to discriminate ttH vs. ttV and tt
  std::string mvaFileName_HTT_SUM_M ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/2lss_1tau_XGB_HTT_evtLevelSUM_TTH_M_18Var.xml";
  std::vector<std::string> mvaInputVariables_HTT_SUMSort = {
    "avg_dr_jet", "dr_lep1_tau", "dr_lep2_tau", "dr_leps", "lep2_conePt",
    "mT_lep1", "mT_lep2", "mTauTauVis2", "max_lep_eta",
    "mbb", "mindr_lep1_jet", "mindr_lep2_jet", "mindr_tau_jet",
    "nJet", "ptmiss", "tau_pt",
    "HTT", "HadTop_pt"
  };
  TMVAInterface mva_2lss_1tau_HTT_SUM_M(mvaFileName_HTT_SUM_M, mvaInputVariables_HTT_SUMSort);
  mva_2lss_1tau_HTT_SUM_M.enableBDTTransform();

  std::vector<std::string> mvaInputVariables_TensorFlow = {
    "lep1_conePt", "lep1_eta", "lep1_phi", "mT_lep1", "mindr_lep1_jet",
    "lep2_conePt", "lep2_eta", "lep2_phi", "mT_lep2", "mindr_lep2_jet",
    "tau1_pt", "tau1_eta", "tau1_phi", "mindr_tau_jet",
    "avg_dr_jet", "mbb_loose", "min_dr_Lep", "mTauTauVis1", "mTauTauVis2",
    "res_HTT", "HadTop_pt", "massL3",
    "min_Deta_leadfwdJet_jet", "leadFwdJet_eta", "leadFwdJet_pt", "met_LD",
    "jet1_pt", "jet1_eta", "jet1_phi",
    "jet2_pt", "jet2_eta", "jet2_phi",
    "jet3_pt", "jet3_eta", "jet3_phi",
    "nJet", "nBJetLoose", "nBJetMedium", "nJetForward", "nElectron", "sum_Lep_charge"
  };

  std::vector<std::string> classes_NN = {"predictions_ttH",  "predictions_rest", "predictions_tH"};
  std::string mvaFileName_NN = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/2lss_1tau_DNN_legacy.pb";
  TensorFlowInterface mva_NN(
    mvaFileName_NN,
    mvaInputVariables_TensorFlow,
    classes_NN
  );

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

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
    std::map<std::string, EvtHistManager_2lss_1tau*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_2lss_1tau*>> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_2lss_1tau*> evt_in_categories_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };

  const std::map<std::string, std::vector<double>> categories_NN = {
    {"output_NN_ttH",   {0.0, 0.49, 0.57, 0.64, 0.74, 0.85, 1.0}},
    {"output_NN_tH",    {0.0, 0.49, 0.57, 0.70, 1.0}},
    {"output_NN_rest",  {0.0, 0.50, 0.56, 0.62, 0.71, 1.0}}
  };

  std::map<std::string, std::map<int, selHistManagerType*>> selHistManagers;
  std::map<std::string, GenEvtHistManager*> genEvtHistManager_beforeCuts;
  std::map<std::string, GenEvtHistManager*> genEvtHistManager_afterCuts;
  std::map<std::string, LHEInfoHistManager*> lheInfoHistManager;
  for(const std::string & central_or_shift: central_or_shifts_local)
  {
    const bool skipBooking = central_or_shift != central_or_shift_main;
    std::vector<const GenMatchEntry*> genMatchDefinitions = genMatchInterface.getGenMatchDefinitions();
    for (const GenMatchEntry * genMatchDefinition : genMatchDefinitions)
    {
      std::string process_and_genMatch = process_string;
      process_and_genMatch += genMatchDefinition->getName();

      int idxLepton_and_HadTau = genMatchDefinition->getIdx();

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
        selHistManager->mvaInputVariables_2lss_->bookHistograms(fs, mvaInputVariables_TensorFlow);
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

        selHistManager->evt_[evt_cat_str] = new EvtHistManager_2lss_1tau(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift,
          skipBooking ? "minimalHistograms" : "allHistograms"
        ));
        selHistManager->evt_[evt_cat_str]->bookCategories(
          fs,
          categories_NN
        );
        selHistManager->evt_[evt_cat_str]->bookHistograms(fs);
      }

      if(isSignal)
      {
        const vstring decayModes_evt = get_key_list_hist(eventInfo, isMC_HH, isMC_VH);
        for(const std::string & decayMode_evt: decayModes_evt)
        {
          if ( ( isMC_tH || isMC_H ) && ( decayMode_evt == "hzg" || decayMode_evt == "hmm" ) ) continue;
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

            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] = new EvtHistManager_2lss_1tau(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift,
              skipBooking ? "minimalHistograms" : "allHistograms"
            ));
            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> bookCategories(
              fs,
              categories_NN
            );
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
      selHistManagers[central_or_shift][idxLepton_and_HadTau] = selHistManager;
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

  std::cout << "Book BDT filling" << std::endl;
  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;

  if ( selectBDT || do_tree ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string, central_or_shift_main)
    );
    bdt_filler->register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta",  "lep1_phi", "lep1_tth_mva", "mindr_lep1_jet",
      "mindr_lep2_jet", "mT_lep1",  "MT_met_lep1", "dr_lep1_tau",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_phi", "max_lep_eta", "avg_dr_lep",
      "lep2_tth_mva", "mT_lep2", "dr_lep2_tau",
      "mindr_tau_jet", "avg_dr_jet",  "nJet25_Recl", "ptmiss", "htmiss",
      "tau1_mva", "tau1_pt", "tau1_eta", "tau1_phi", "mT_tau1", "dr_leps",
      "mTauTauVis1", "mTauTauVis2",
      "memOutput_isValid",   "memOutput_errorFlag",  "memOutput_LR",
      //"memOutput_tt_LR", "memOutput_ttZ_LR",
      //"memOutput_tt_LR",  "memOutput_ttZ_LR", "memOutput_ttZ_Zll_LR",
      //"log_memOutput_ttH",  "log_memOutput_ttZ",  "log_memOutput_ttZ_Zll", "log_memOutput_tt",
      "lep1_genLepPt", "lep2_genLepPt",
      "tau_genTauPt",
      //"lep1_fake_prob", "lep2_fake_prob",  "tau_fake_prob",
      //"tau_fake_test",
      "genWeight", "evtWeight",
      "mbb_loose", "mbb_medium",
      "dr_Lep_lss", "dr_Lep_los1", "dr_Lep_los2", "eta_LepLep_los1", "eta_LepLep_los2", "eta_LepLep_los",
      "res_HTT", "HadTop_pt", "genTopPt_CSVsort4rd",
      "min_Deta_mostfwdJet_jet", "min_Deta_leadfwdJet_jet",
      "met_LD",
      "jet1_pt", "jet1_eta", "jet1_phi", "jet1_E",
      "jet2_pt", "jet2_eta", "jet2_phi", "jet2_E",
      "jet3_pt", "jet3_eta", "jet3_phi", "jet3_E",
      "jet4_pt", "jet4_eta", "jet4_phi", "jet4_E",
      "mostFwdJet_eta", "mostFwdJet_pt", "mostFwdJet_phi", "mostFwdJet_E",
      "leadFwdJet_eta", "leadFwdJet_pt", "leadFwdJet_phi", "leadFwdJet_E",
      "massL", "massL3", "massLT",
      "selHadTau_lead_deepTauIDe",  "selHadTau_lead_deepTauIDmu", "selHadTau_lead_deepTauIDjet",
      "selHadTau_lead_deepTauRawe", "selHadTau_lead_deepTauRawmu", "selHadTau_lead_deepTauRawjet"
    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "nLep","nTau",
      "lep1_isTight", "lep2_isTight", "tau_isTight", "failsTightChargeCut",
      "nElectron", "sum_Lep_charge",
      "hadtruth", "bWj1Wj2_isGenMatched_CSVsort4rd",
      "nJetForward",
      "tau1_mva_id",
      "selHadTau_lead_genHadTau", "selHadTau_lead_genLepton",
      "selHadTau_lead_decayMode", "selHadTau_lead_idDecayMode"
    );
    bdt_filler->bookTree(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  std::map<std::string, int> selectedEntries_byGenMatchType;             // key = process_and_genMatch
  std::map<std::string, std::map<std::string, double>> selectedEntries_weighted_byGenMatchType; // keys = central_or_shift, process_and_genMatch
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
    ">= 2 presel leptons",
    ">= 1 sel tau",
    ">= 2 sel leptons",
    "<= 2 tight leptons",
    "HLT filter matching",
    "Hadronic selection",
    "<= 1 veto taus",
    "m(ll) > 12 GeV",
    "lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV",
    "tight lepton charge",
    "sel lepton-pair OS/SS charge",
    "sel lepton+tau charge",
    "Z-boson mass veto",
    "met LD > 30 GeV",
    "MEt filters",
    "sel lepton-pair gen=rec charge match",
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
      if(objectMultiplicity.getNRecoLepton(minLeptonSelection) < 2 ||
         objectMultiplicity.getNRecoLepton(kTight)             > 2 ||
         objectMultiplicity.getNRecoHadTau(tauId, tauLevel)    < 1  )
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

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, triggerWhiteList, eventInfo, isMC, isDEBUG);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e, triggerWhiteList, eventInfo, isMC, isDEBUG);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu, triggerWhiteList, eventInfo, isMC, isDEBUG);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu, triggerWhiteList, eventInfo, isMC, isDEBUG);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu, triggerWhiteList, eventInfo, isMC, isDEBUG);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;

    //--- build collections of generator level particles
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
    if ( !isMC && !isDEBUG ) {
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
    cutFlowHistManager->fillHistograms("trigger", evtWeightRecorder.get(central_or_shift_main));

    if ( (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)   ||
         (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
         (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
         (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
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
    }
    const std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
    if(!(electronSelection == muonSelection)) selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau*> looseHadTaus = looseHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(looseHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    const std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 1);
    const std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    const std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("looseHadTaus",    looseHadTaus);
      printCollection("fakeableHadTaus", fakeableHadTaus);
      printCollection("tightHadTaus",    tightHadTaus);
    }

    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("selMuons", selMuons);
      printCollection("selElectrons", selElectrons);
      printCollection("selLeptons", selLeptons);
      printCollection("selHadTaus", selHadTaus);
    }

    // CV: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 2l+2tau category
    const std::vector<const RecoHadTau*> vetoHadTaus = vetoHadTauSelector(cleanedHadTaus, isHigherPt);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, selectBDT ? selHadTaus : looseHadTaus) :
      jetCleaner       (jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, selectBDT ? selHadTaus : looseHadTaus)
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

        hadTauGenMatcher.addGenLeptonMatchByIndex(cleanedHadTaus, hadTauGenMatch, GenParticleType::kGenAnyLepton);
        hadTauGenMatcher.addGenHadTauMatch       (cleanedHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch          (cleanedHadTaus, genJets);

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

        hadTauGenMatcher.addGenLeptonMatch(cleanedHadTaus, genLeptons);
        hadTauGenMatcher.addGenHadTauMatch(cleanedHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch   (cleanedHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets, genJets);
      }
    }

//--- apply preselection
    // require at least two leptons passing loose preselection criteria
    if ( !(preselLeptonsFull.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS preselLeptons selection." << std::endl;
        printCollection("preselLeptons", preselLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 presel leptons", evtWeightRecorder.get(central_or_shift_main));

    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selHadTaus selection." << std::endl;
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 1 sel tau", evtWeightRecorder.get(central_or_shift_main));

    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau);

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptonsFull, looseHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
        printCollection("selLeptons", selLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 2 sel leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 sel leptons", evtWeightRecorder.get(central_or_shift_main));
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const leptonChargeFlipGenMatchEntry& selLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead);

    if(isMC)
    {
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->cone_pt(), selLepton_lead->eta(),
        selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->cone_pt(), selLepton_sublead->eta()
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
        evtWeightRecorder.record_leptonIDSF(dataToMCcorrectionInterface, false);
      }

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      dataToMCcorrectionInterface->setHadTaus(getHadTau_genPdgId(selHadTau), selHadTau->pt(), selHadTau->eta());
      evtWeightRecorder.record_hadTauID_and_Iso(dataToMCcorrectionInterface);
      evtWeightRecorder.record_eToTauFakeRate(dataToMCcorrectionInterface);
      evtWeightRecorder.record_muToTauFakeRate(dataToMCcorrectionInterface);
    }

    bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
    bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
    bool passesTight_hadTau = isMatched(*selHadTau, tightHadTausFull);

    if(leptonFakeRateInterface)
    {
      evtWeightRecorder.record_jetToLepton_FR_lead(leptonFakeRateInterface, selLepton_lead);
      evtWeightRecorder.record_jetToLepton_FR_sublead(leptonFakeRateInterface, selLepton_sublead);
    }
    if(jetToTauFakeRateInterface)
    {
      evtWeightRecorder.record_jetToTau_FR_lead(jetToTauFakeRateInterface, selHadTau);
    }

    if(! selectBDT)
    {
      if(applyFakeRateWeights == kFR_3L)
      {
        evtWeightRecorder.compute_FR_2l1tau(passesTight_lepton_lead, passesTight_lepton_sublead, passesTight_hadTau);
      }
      else if(applyFakeRateWeights == kFR_2lepton)
      {
        evtWeightRecorder.compute_FR_2l(passesTight_lepton_lead, passesTight_lepton_sublead);
      }
      else if (applyFakeRateWeights == kFR_1tau)
      {
        evtWeightRecorder.compute_FR_1tau();
      }
      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if(isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight && !(selHadTau->genHadTau() || selHadTau->genLepton()))
      {
        evtWeightRecorder.record_jetToTau_SF_lead(jetToTauFakeRateInterface, selHadTau);
      }
    }

    // require exactly two leptons passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptonsFull.size() <= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection.\n";
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 2 tight leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("<= 2 tight leptons", evtWeightRecorder.get(central_or_shift_main));

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
      if(! hltFilter(trigger_bits, fakeableLeptons, fakeableHadTaus))
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

    const bool ttH_like = (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) && (selJets.size() >= 3);
    const bool tH_like = (selBJets_medium.size() >= 1 && ((selJets.size() - selBJets_loose.size()) + selJetsForward.size()) >= 1);
    const bool is_tH_like_and_not_ttH_like = tH_like && ! ttH_like;

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    const bool passEvents = ttH_like || tH_like;
    if(! passEvents)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS Hadronic selection.\n";
        printCollection("selJets", selJets);
        printCollection("selBJets_loose", selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update("Hadronic selection", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("Hadronic selection", evtWeightRecorder.get(central_or_shift_main));

    // veto events containing more than one tau passing the Medium WP, to avoid overlap with the 2l+2tau category
    // we want to keep all cuts consistent in SR and fake CR, to obtain a consistent estimate of the fake background
    if ( !(vetoHadTaus.size() <= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS vetoHadTaus selection." << std::endl;
        printCollection("vetoHadTaus", vetoHadTaus);
      }
      continue;
    }
    cutFlowTable.update("<= 1 veto taus", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("<= 1 veto taus", evtWeightRecorder.get(central_or_shift_main));

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
    const double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->cone_pt() > minPt_lead && selLepton_sublead->cone_pt() > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS lepton pT selection." << std::endl;
        std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
                  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeightRecorder.get(central_or_shift_main));

    bool failsTightChargeCut = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton = fakeableLeptons.begin();
          lepton != fakeableLeptons.end(); ++lepton ) {
      if ( (*lepton)->is_electron() ) {
        const RecoElectron* electron = dynamic_cast<const RecoElectron*>(*lepton);
        assert(electron);
        if ( electron->tightCharge() < 2 )
        {
          failsTightChargeCut = true;
          break;
        }
      }
      else if ( (*lepton)->is_muon() ) {
        const RecoMuon* muon = dynamic_cast<const RecoMuon*>(*lepton);
        assert(muon);
        if ( muon->tightCharge() < 2 )
        {
          failsTightChargeCut = true;
          break;
        }
      }
    }
    if ( failsTightChargeCut ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tight lepton charge requirement." << std::endl;
      }
      //if (!selectBDT)
      continue;
    }
    cutFlowTable.update("tight lepton charge", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("tight lepton charge", evtWeightRecorder.get(central_or_shift_main));

    bool isLeptonCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isLeptonCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
    if ( leptonChargeSelection == kOS && isLeptonCharge_SS ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kSS && isLeptonCharge_OS ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = SS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kOS ) {
      double prob_chargeMisId_lead = prob_chargeMisId(era, getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta());
      double prob_chargeMisId_sublead = prob_chargeMisId(era, getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta());

      double prob_chargeMisId_applied = 1.;
      if ( apply_lepton_and_hadTauCharge_cut ) {
        if ( chargeSumSelection == kOS ) {
          // CV: apply charge misidentification probability to lepton of same charge as hadronic tau
          //    (if the lepton of charge opposite to the charge of the hadronic tau "flips",
          //     the event has sum of charges equal to three and fails "lepton+tau charge" cut)
          if ( selLepton_lead->charge()*selHadTau->charge()    > 0 ) prob_chargeMisId_applied *= prob_chargeMisId_lead;
          if ( selLepton_sublead->charge()*selHadTau->charge() > 0 ) prob_chargeMisId_applied *= prob_chargeMisId_sublead;
        } else if ( chargeSumSelection == kSS ) {
          // CV: apply charge misidentification probability to lepton of opposite charge as hadronic tau
          //    (if the lepton of same charge as the hadronic tau "flips",
          //     the event has sum of charges equal to one and fails "lepton+tau charge" cut)
          if ( selLepton_lead->charge()*selHadTau->charge()    < 0 ) prob_chargeMisId_applied *= prob_chargeMisId_lead;
          if ( selLepton_sublead->charge()*selHadTau->charge() < 0 ) prob_chargeMisId_applied *= prob_chargeMisId_sublead;
        } else assert(0);
      } else {
        prob_chargeMisId_applied *= (prob_chargeMisId_lead + prob_chargeMisId_sublead);
      }
      // Karl: reject the event, if the applied probability of charge misidentification is 0. This can happen only if
      //       1) both selected leptons are muons (their misId prob is 0).
      //       2) one lepton is a muon and the other is an electron, and the muon has the same sign as the selected tau.
      if(prob_chargeMisId_applied == 0.)
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS charge flip selection\n"
                       "(leading lepton charge (pdgId) = " << selLepton_lead->charge() << " (" << selLepton_lead->pdgId()
                    << ") => misId prob = " << prob_chargeMisId_lead << "; "
                       "subleading lepton charge (pdgId) = " << selLepton_sublead->charge() << " (" << selLepton_sublead->pdgId()
                    << ") => misId prob = " << prob_chargeMisId_sublead << "); "
                       "tau charge = " << selHadTau->charge() << ")\n"
          ;
        }
        continue;
      }
      evtWeightRecorder.record_chargeMisIdProb(prob_chargeMisId_applied);
    }
    cutFlowTable.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("sel lepton-pair OS/SS charge", evtWeightRecorder.get(central_or_shift_main));

    if ( apply_lepton_and_hadTauCharge_cut ) {
      if ( !((chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) == 1) ||
             (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) != 1)) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS lepton+tau charge selection." << std::endl;
          std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                    << ", subleading selLepton charge = " << selLepton_sublead->charge()
                    << ", selHadTau charge = " << selHadTau->charge() << ")" << std::endl;
        }
        continue;
      }
      cutFlowTable.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeightRecorder.get(central_or_shift_main));
      cutFlowHistManager->fillHistograms("sel lepton+tau charge", evtWeightRecorder.get(central_or_shift_main));
    }

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
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeightRecorder.get(central_or_shift_main));
    if ( !(selLepton_lead->is_muon() || selLepton_sublead->is_muon() || met_LD >= 30.) ) {
      if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS MET LD selection." << std::endl;
          std::cout << " (LD = " << met_LD << ")\n"
        ;
      }
      continue;
    }
    cutFlowTable.update("met LD > 30 GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("met LD > 30 GeV", evtWeightRecorder.get(central_or_shift_main));

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

    if (isMC) {
      if((selLepton_lead->genLepton() && selLepton_lead->charge() != selLepton_lead->genLepton()->charge()) ||
         (selLepton_sublead->genLepton() && selLepton_sublead->charge() != selLepton_sublead->genLepton()->charge())){
        if(run_lumi_eventSelector)
          {
	    std::cout << "event " << eventInfo.str() << " FAILS lepton-par gen=rec charge matching\n"
              "(leading lepton charge = " << selLepton_lead->charge() << " genlepton charge = " << selLepton_lead->genLepton()->charge()<< "; "
              "subleading lepton charge = " << selLepton_sublead->charge() << " genlepton charge = " << selLepton_sublead->genLepton()->charge()<< "\n"
              ;
          }
        continue;
      }
    }
    cutFlowTable.update("sel lepton-pair gen=rec charge match", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("sel lepton-pair gen=rec charge match", evtWeightRecorder.get(central_or_shift_main));


    bool failsSignalRegionVeto = false;
    if ( isMCClosure_e || isMCClosure_m || isMCClosure_t ) {
      bool applySignalRegionVeto_lepton = (isMCClosure_e && countFakeElectrons(selLeptons) >= 1) || (isMCClosure_m && countFakeMuons(selLeptons) >= 1);
      bool applySignalRegionVeto_hadTau = isMCClosure_t && countFakeHadTaus(selHadTaus) >= 1;
      if ( applySignalRegionVeto_lepton && tightLeptons.size() >= 2 ) failsSignalRegionVeto = true;
      if ( applySignalRegionVeto_hadTau && tightHadTaus.size() >= 1 ) failsSignalRegionVeto = true;
    } else if ( electronSelection == kFakeable || muonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( tightLeptons.size() >= 2 && tightHadTaus.size() >= 1 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
	             "# tight leptons = " << tightLeptons.size() << " >= 2 and "
                     "# tight taus = " << tightHadTaus.size() << " >= 1\n"
        ;
	printCollection("tightLeptons", tightLeptons);
	printCollection("tightHadTaus", tightHadTaus);
      }
      continue; // CV: avoid overlap with signal region
    }
    cutFlowTable.update("signal region veto", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("signal region veto", evtWeightRecorder.get(central_or_shift_main));

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

    if(isDEBUG || run_lumi_eventSelector)
    {
      std::cout << "Event weights:\n" << evtWeightRecorder << '\n';
    }

    MEMOutput_2lss_1tau memOutput_2lss_1tau_matched;
    if(memReader)
    {
      const std::vector<MEMOutput_2lss_1tau> memOutputs_2lss_1tau = memReader->read();
      for(const MEMOutput_2lss_1tau & memOutput_2lss_1tau: memOutputs_2lss_1tau)
      {
        const double selLepton_lead_dR = deltaR(
          selLepton_lead->eta(),               selLepton_lead->phi(),
          memOutput_2lss_1tau.leadLepton_eta_, memOutput_2lss_1tau.leadLepton_phi_
        );
        if(selLepton_lead_dR > 1.e-2)
        {
          continue;
        }
        const double selLepton_sublead_dR = deltaR(
          selLepton_sublead->eta(),               selLepton_sublead->phi(),
          memOutput_2lss_1tau.subleadLepton_eta_, memOutput_2lss_1tau.subleadLepton_phi_
        );
        if(selLepton_sublead_dR > 1.e-2)
        {
          continue;
        }
        const double selHadTau_dR = deltaR(
          selHadTau->eta(), selHadTau->phi(),
          memOutput_2lss_1tau.hadTau_eta_, memOutput_2lss_1tau.hadTau_phi_
        );
        if(selHadTau_dR > 1.e-2)
        {
          continue;
        }
        memOutput_2lss_1tau_matched = memOutput_2lss_1tau;
        break;
      }
      if(! memOutput_2lss_1tau_matched.is_initialized())
      {
        std::cout << "Warning in " << eventInfo << '\n'
                  << "No MEMOutput_2lss_1tau object found for:\n"
                  << "\tselLepton_lead: pT = " << selLepton_lead->pt()
                  << ", eta = "                << selLepton_lead->eta()
                  << ", phi = "                << selLepton_lead->phi()
                  << ", pdgId = "              << selLepton_lead->pdgId() << "\n"
                     "\tselLepton_sublead: pT = " << selLepton_sublead->pt()
                  << ", eta = "                   << selLepton_sublead->eta()
                  << ", phi = "                   << selLepton_sublead->phi()
                  << ", pdgId = "                 << selLepton_sublead->pdgId() << "\n"
                     "\tselHadTau: pT = " << selHadTau->pt()
                  << ", eta = "           << selHadTau->eta()
                  << ", phi = "           << selHadTau->phi() << "\n"
                     "ttH-like = " << ttH_like << " "
                     "tH-like = "  << tH_like  << "\n"
                     "Number of MEM objects read: " << memOutputs_2lss_1tau.size() << '\n'
        ;
        bool memSkipError = false;
        if(! memOutputs_2lss_1tau.empty())
        {
          for(unsigned mem_idx = 0; mem_idx < memOutputs_2lss_1tau.size(); ++mem_idx)
          {
            std::cout << "\t#" << mem_idx << " mem object;\n"
                      << "\t\tlead lepton eta = "    << memOutputs_2lss_1tau[mem_idx].leadLepton_eta_
                      << "; phi = "                  << memOutputs_2lss_1tau[mem_idx].leadLepton_phi_ << "\n"
                         "\t\tsublead lepton eta = " << memOutputs_2lss_1tau[mem_idx].subleadLepton_eta_
                      << "; phi = "                  << memOutputs_2lss_1tau[mem_idx].subleadLepton_phi_ << "\n"
                         "\t\thadronic tau eta = "   << memOutputs_2lss_1tau[mem_idx].hadTau_eta_
                      << "; phi = "                  << memOutputs_2lss_1tau[mem_idx].hadTau_phi_ << "\n"
                      << "error flag = "             << memOutputs_2lss_1tau[mem_idx].errorFlag() << '\n'
            ;
            if(memOutputs_2lss_1tau[mem_idx].errorFlag() == ADDMEM_2LSS1TAU_ERROR_SKIPPED)
            {
              std::cout << "MEM computation was skipped for event " << eventInfo.str() << '\n';
            }
            else if(memOutputs_2lss_1tau[mem_idx].errorFlag() == ADDMEM_2LSS1TAU_ERROR_SKIPPED_NOPERM)
            {
              std::cout
                << "MEM computation was skipped for event " << eventInfo.str() << " AND "
                   "there were not enough MEM permutations in the first place\n"
              ;
            }
            else if(memOutputs_2lss_1tau[mem_idx].errorFlag() == ADDMEM_2LSS1TAU_ERROR_JETMULTIPLICITY)
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
                  << "MEM not available because the event is tH-like or the objects have changed "
                     "changed wrt the objects used in MEM computation due to systematics\n"
                ;
              }
            }
            else if(memOutputs_2lss_1tau[mem_idx].errorFlag() == ADDMEM_2LSS1TAU_ERROR_NOPERM)
            {
              std::cout
                << "MEM computation was skipped for event " << eventInfo.str() << " because not enough permutations found\n"
              ;
            }
            else if(memOutputs_2lss_1tau[mem_idx].errorFlag() == ADDMEM_2LSS1TAU_ERROR_MATRIXINVERSION)
            {
              memSkipError = true;
              std::cout << "MEM computation failed because MET covariance matrix was not invertible\n";
            }
            else
            {
              std::cout << "Failed with MEM error: " << memOutput_2lss_1tau_matched.errorFlag() << '\n';
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
          throw cmsException(argv[0], __LINE__) << "No valid MEM output was found";
        }
      }
    }
    const std::map<MEMsys, double> memOutput_LR = memOutput_2lss_1tau_matched.get_LR_map();

    //--- compute output of hadronic top tagger BDT
    // it returns the gen-triplets organized in top/anti-top
    bool calculate_matching = false; //isMC && selectBDT && !applyAdditionalEvtWeight; // DY has not matching info
    std::map<int, Particle::LorentzVector> genVar;
    std::map<int, Particle::LorentzVector> genVarAnti;
    if (calculate_matching) {
      genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop);
      genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop);
    }

    // resolved HTT
    double max_mvaOutput_HTT_CSVsort4rd = 0.;
    bool max_truth_HTT_CSVsort4rd = false;
    double HadTop_pt_CSVsort4rd = 0.;
    double genTopPt_CSVsort4rd = 0.;
    bool hadtruth = false;
    for(std::vector<const RecoJet *>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet)
    {
      for(std::vector<const RecoJet *>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1)
      {
        if(&(*selWJet1) == &(*selBJet))
        {
          continue;
        }
        for(std::vector<const RecoJet *>::const_iterator selWJet2 = selJets.begin(); selWJet2 != selJets.end(); ++selWJet2)
        {
          if(&(*selWJet2) == &(*selBJet))
          {
            continue;
          }
          if(&(*selWJet2) == &(*selWJet1))
          {
            continue;
          }
          bool isGenMatched = false;
          double genTopPt_teste = 0.;
          const std::map<int, double> bdtResult = (*hadTopTagger)(
            **selBJet, **selWJet1, **selWJet2, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti
          );
          // genTopPt_teste is filled with the result of gen-matching
          if(isGenMatched)
          {
            hadtruth = true;
          }
          // save genpt of all options
          const double HadTop_pt = ((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).pt();

          if(bdtResult.at(kXGB_CSVsort4rd) > max_mvaOutput_HTT_CSVsort4rd)
          {
            max_truth_HTT_CSVsort4rd = isGenMatched;
            max_mvaOutput_HTT_CSVsort4rd = bdtResult.at(kXGB_CSVsort4rd);
            HadTop_pt_CSVsort4rd = HadTop_pt;
            genTopPt_CSVsort4rd = genTopPt_teste;
          }
        }
      }
    }

//--- compute variables BDTs used to discriminate ttH vs. ttV and ttH vs. ttba -- they will be used more than once -- Xanda
    const int nJet25_Recl = comp_n_jet25_recl(selJets);

    const double mindr_lep1_jet  = comp_mindr_jet(*selLepton_lead, selJets);
    const double mindr_lep2_jet  = comp_mindr_jet(*selLepton_sublead, selJets);
    const double max_lep_eta     = std::max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    const double tau_pt          = selHadTau->pt();
    const double ptmiss          = met.pt();
    const double dr_leps         = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    const double mT_lep1         = comp_MT_met(selLepton_lead,    met.pt(), met.phi());
    const double mT_lep2         = comp_MT_met(selLepton_sublead, met.pt(), met.phi());
    const double dr_lep1_tau     = deltaR(selLepton_lead->p4(),    selHadTau->p4());
    const double dr_lep2_tau     = deltaR(selLepton_sublead->p4(), selHadTau->p4());
    const double avg_dr_jet      = comp_avg_dr_jet(selJets);
    const double lep1_conePt     = comp_lep_conePt(*selLepton_lead);
    const double lep2_conePt     = comp_lep_conePt(*selLepton_sublead);
    const double mindr_tau_jet   = comp_mindr_jet(*selHadTau, selJets);
    const double mbb             = selBJets_medium.size() > 1 ?  (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1000;
    const double mTauTauVis1_sel = (selLepton_lead->cone_p4() + selHadTau->p4()).mass();
    const double mTauTauVis2_sel = (selLepton_sublead->cone_p4() + selHadTau->p4()).mass();
    const double HTT             = max_mvaOutput_HTT_CSVsort4rd;
    const double HadTop_pt       = HadTop_pt_CSVsort4rd;
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
      dr_los1 = deltaR(selHadTau -> p4(), selLepton_lead -> p4());
      dr_los2 = deltaR(selHadTau  -> p4(), selLepton_sublead -> p4());
      eta_los1 = std::abs(selHadTau -> eta() - selLepton_lead -> eta());
      eta_los2 = std::abs(selHadTau  -> eta() - selLepton_sublead -> eta());
    } else {
      dr_lss  = deltaR(selHadTau -> p4(), selLepton_lead -> p4());
      dr_los1 = deltaR(selLepton_sublead -> p4(), selHadTau -> p4());
      dr_los2 = deltaR(selLepton_sublead  -> p4(), selLepton_lead -> p4());
      eta_los1 = std::abs(selLepton_sublead -> eta() - selHadTau -> eta());
      eta_los2 = std::abs(selLepton_sublead  -> eta() - selLepton_lead -> eta());
    }
    double eta_los = 0.;
    if (dr_los1 < dr_los2) eta_los = eta_los1;
    else eta_los = eta_los2;

//--- compute output of BDTs used to discriminate ttH vs. ttV and  tt trained with XGB
    const std::map<std::string, double> mvaInputVariables_HTT_SUM = {
      { "avg_dr_jet",     avg_dr_jet          },
      { "dr_lep1_tau",    dr_lep1_tau         },
      { "dr_lep2_tau",    dr_lep2_tau         },
      { "dr_leps",        dr_leps             },
      { "lep2_conePt",    lep2_conePt         },
      { "mT_lep1",        mT_lep1             },
      { "mT_lep2",        mT_lep2             },
      { "mTauTauVis2",    mTauTauVis2_sel     },
      { "max_lep_eta",    max_lep_eta         },
      { "mbb",            mbb                 },
      { "mindr_lep1_jet", mindr_lep1_jet      },
      { "mindr_lep2_jet", mindr_lep2_jet      },
      { "mindr_tau_jet",  mindr_tau_jet       },
      { "nJet",           nJet25_Recl         },
      { "ptmiss",         ptmiss              },
      { "tau_pt",         tau_pt              },
      { "HTT",            HTT                 },
      { "HadTop_pt",      HadTop_pt           },
    };
    const double mvaOutput_2lss_1tau_HTT_SUM_M = mva_2lss_1tau_HTT_SUM_M(mvaInputVariables_HTT_SUM);

    /*
    "lep1_conePt", "lep1_eta", "lep1_phi", "mT_lep1", "mindr_lep1_jet",
    "lep2_conePt", "lep2_eta", "lep2_phi", "mT_lep2", "mindr_lep2_jet",
    "tau1_pt", "tau1_eta", "tau1_phi", "mindr_tau_jet",
    "avg_dr_jet", "mbb_loose", "min_dr_Lep", "mTauTauVis1", "mTauTauVis2",
    "res_HTT", "HadTop_pt", "massL3",
    "min_Deta_leadfwdJet_jet", "leadFwdJet_eta", "leadFwdJet_pt", "met_LD",
    "jet1_pt", "jet1_eta", "jet1_phi",
    "jet2_pt", "jet2_eta", "jet2_phi",
    "jet3_pt", "jet3_eta", "jet3_phi",
    "nJet", "nBJetLoose", "nBJetMedium", "nJetForward", "nElectron", "sum_Lep_charge"
    */
    std::map<std::string, double> mvaInputVariables_NN = {
      {"lep1_conePt",     lep1_conePt},
      {"lep1_eta",        selLepton_lead -> eta()},
      {"lep1_phi",        selLepton_lead -> phi()},
      {"mT_lep1",         mT_lep1}, //
      {"mindr_lep1_jet",  mindr_lep1_jet},
      {"lep2_conePt",     lep2_conePt},
      {"lep2_eta",        selLepton_sublead -> eta()},
      {"lep2_phi",        selLepton_sublead -> phi()},
      {"mT_lep2",         mT_lep2}, //
      {"mindr_lep2_jet",  mindr_lep2_jet},
      {"tau1_pt",         selHadTau -> pt()},
      {"tau1_eta",        selHadTau -> eta()},
      {"tau1_phi",        selHadTau -> phi()},
      {"mindr_tau_jet",   std::min(10., mindr_tau_jet)},
      {"avg_dr_jet",      avg_dr_jet},
      {"met_LD",          met_LD},
      {"mbb_loose",       selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : 0},
      {"min_dr_Lep",      std::min( {dr_lep1_tau, dr_lep2_tau, dr_leps})},
      //{"eta_LepLep_los",  eta_los},
      {"mTauTauVis1",     mTauTauVis1_sel},
      {"mTauTauVis2",     mTauTauVis2_sel},
      {"leadFwdJet_eta",  selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : 0.},
      {"leadFwdJet_pt",   selJetsForward.size() > 0 ? selJetsForward[0] -> pt()     : 0.},
      {"min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet},
      {"jet1_pt",         selJets[0]->pt()},
      {"jet1_eta",        selJets[0]->eta()},
      {"jet1_phi",        selJets[0]->phi()},
      {"jet2_pt",         selJets.size() > 1 ?  selJets[1]->pt()  : 0.},
      {"jet2_eta",        selJets.size() > 1 ?  selJets[1]->eta() : 0.},
      {"jet2_phi",        selJets.size() > 1 ?  selJets[1]->phi() : 0.},
      {"jet3_pt",         selJets.size() > 2 ?  selJets[2]->pt()  : 0.},
      {"jet3_eta",        selJets.size() > 2 ?  selJets[2]->eta() : 0.},
      {"jet3_phi",        selJets.size() > 2 ?  selJets[2]->phi() : 0.},
      {"sum_Lep_charge",  selLepton_lead -> charge() + selLepton_sublead -> charge() + selHadTau->charge()},
      {"HadTop_pt",       HadTop_pt_CSVsort4rd},
      {"res_HTT",         max_mvaOutput_HTT_CSVsort4rd},
      {"massL3",          comp_massL3(selLepton_lead, selLepton_sublead, selHadTau, met.pt(), met.phi())},
      {"nJet",            selJets.size()},
      {"nBJetLoose",      selBJets_loose.size()},
      {"nBJetMedium",     selBJets_medium.size()},
      {"nJetForward",     selJetsForward.size()},
      {"nElectron",       selElectrons.size()}
      };
    std::map<std::string, double> mvaOutput_NN_TF = mva_NN(mvaInputVariables_NN);
    if ( isDebugTF ) {
      std::cout << "variables ";
      for (auto elem : mvaInputVariables_NN) std::cout << elem.first << " " << elem.second << "\n";
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "result sig_1p2_rest_1_th_1p2 ";
      for (auto elem : classes_NN ) std::cout << elem << " = " << mvaOutput_NN_TF[elem] <<" ";
      std::cout << std::endl;
    }

    std::string category_NN_TF = "output_NN_";
    double output_NN = -10.0;
    if (ttH_like || tH_like) {
      if (
        mvaOutput_NN_TF["predictions_ttH"] >= mvaOutput_NN_TF["predictions_rest"] &&\
        mvaOutput_NN_TF["predictions_ttH"] >= mvaOutput_NN_TF["predictions_tH"]
      ) {
        category_NN_TF += "ttH";
        output_NN = mvaOutput_NN_TF["predictions_ttH"];
        }
      if (
        mvaOutput_NN_TF["predictions_tH"] >  mvaOutput_NN_TF["predictions_ttH"] &&\
        mvaOutput_NN_TF["predictions_tH"] >= mvaOutput_NN_TF["predictions_rest"]
      ) {
        category_NN_TF += "tH";
        output_NN = mvaOutput_NN_TF["predictions_tH"];
        }
      if (
        mvaOutput_NN_TF["predictions_rest"] > mvaOutput_NN_TF["predictions_ttH"] &&\
        mvaOutput_NN_TF["predictions_rest"] > mvaOutput_NN_TF["predictions_tH"]
      ) {
        category_NN_TF += "rest";
        output_NN = mvaOutput_NN_TF["predictions_rest"];
        }
    } else assert(0);

//--- retrieve gen-matching flags
    std::vector<const GenMatchEntry*> genMatches = genMatchInterface.getGenMatch(selLeptons, selHadTaus);

//--- fill histograms with events passing final selection
    std::map<std::string, double> tH_weight_map;
    for(const std::string & central_or_shift: central_or_shifts_local)
    {
      const double evtWeight = evtWeightRecorder.get(central_or_shift);
      const bool skipFilling = central_or_shift != central_or_shift_main;
      for (const GenMatchEntry* genMatch : genMatches)
      {
        selHistManagerType* selHistManager = selHistManagers[central_or_shift][genMatch->getIdx()];
        assert(selHistManager);
        const MEMsys mem_option = getMEMsys_option(central_or_shift);
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
          selHistManager->mvaInputVariables_2lss_->fillHistograms(mvaInputVariables_NN, evtWeight);
        }

        const std::string central_or_shift_tH = eventInfo.has_central_or_shift(central_or_shift) ? central_or_shift : central_or_shift_main;
        const double evtWeight_tH_nom = evtWeightRecorder.get_nom_tH_weight(central_or_shift_tH);
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

          EvtHistManager_2lss_1tau* selHistManager_evt = selHistManager->evt_[kv.first];
          if ( selHistManager_evt )
          {
          selHistManager_evt->fillHistograms(
            selElectrons.size(),
            selMuons.size(),
      	    selHadTaus.size(),
      	    selJets.size(),
      	    selBJets_loose.size(),
      	    selBJets_medium.size(),
      	    kv.second,
      	    mvaOutput_2lss_1tau_HTT_SUM_M,
      	    mTauTauVis1_sel,
      	    mTauTauVis2_sel,
            memOutput_LR.at(mem_option),
            category_NN_TF,
            output_NN
         );
         }
        }
        if ( isSignal ) {
          std::string decayModeStr = get_key_hist(eventInfo, genWBosons, isMC_HH, isMC_VH);
          if ( ( isMC_tH || isMC_H ) && ( decayModeStr == "hzg" || decayModeStr == "hmm" ) ) continue;
          if(! decayModeStr.empty())
          {
            for(const auto & kv: tH_weight_map)
            {
              EvtHistManager_2lss_1tau* selHistManager_evt_category_decayModes = selHistManager->evt_in_decayModes_[kv.first][decayModeStr];
              if ( selHistManager_evt_category_decayModes )
              {
              selHistManager_evt_category_decayModes->fillHistograms(
                selElectrons.size(),
                selMuons.size(),
                selHadTaus.size(),
                selJets.size(),
                selBJets_loose.size(),
                selBJets_medium.size(),
                kv.second,
                mvaOutput_2lss_1tau_HTT_SUM_M,
                mTauTauVis1_sel,
                mTauTauVis2_sel,
                memOutput_LR.at(mem_option),
                category_NN_TF,
                output_NN
              );
             }
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

    double memOutput_type=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.type() : -100.;
    double memOutput_ttH=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttH()     : -100.;
    double memOutput_tt=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_tt()      : -100.;
    double memOutput_ttZ=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttZ()     : -100.;
    double memOutput_ttZ_Zll=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttZ_Zll() : -100.;

    bool isGenMatched = false;
    if ( isMC )
    {
      for (const GenMatchEntry* genMatch : genMatches)
      {
	if ( genMatch->getName() == "" ) isGenMatched = true; // non-fake
      }
    }

    if ( bdt_filler ) {

      double lep1_genLepPt=( selLepton_lead->genLepton() != 0 ) ? selLepton_lead->genLepton()->pt() : 0.;
      double lep2_genLepPt=( selLepton_sublead->genLepton() != 0 ) ? selLepton_sublead->genLepton()->pt() : 0.;
      double tau_genTauPt=( selHadTau->genHadTau() != 0 ) ? selHadTau->genHadTau()->pt() : 0.;

      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("lep1_pt",                        selLepton_lead->pt())
          ("lep1_conePt",                    lep1_conePt)
          ("lep1_eta",                       selLepton_lead->absEta())
          ("lep1_phi",                       selLepton_lead->phi())
          ("lep1_tth_mva",                   selLepton_lead->mvaRawTTH())
          ("mindr_lep1_jet",                 std::min(10., mindr_lep1_jet) )
          ("mindr_lep2_jet",                 std::min(10., mindr_lep2_jet) )
          ("mT_lep1",                        mT_lep1)
          ("MT_met_lep1",                    comp_MT_met(selLepton_lead, met.pt(), met.phi()))
          ("dr_lep1_tau",                    dr_lep1_tau)
          ("lep2_pt",                        selLepton_sublead->pt())
          ("lep2_conePt",                    lep2_conePt)
          ("lep2_eta",                       selLepton_sublead->absEta())
          ("lep2_phi",                       selLepton_sublead->phi())
          ("max_lep_eta",                    max_lep_eta)
          ("avg_dr_lep",                     1.0) // dr_leps??
          ("lep2_tth_mva",                   selLepton_sublead->mvaRawTTH())
          ("mT_lep2",                        mT_lep2)
          ("dr_lep2_tau",                    dr_lep2_tau)
          ("mindr_tau_jet",                  std::min(10., mindr_tau_jet))
          ("avg_dr_jet",                     avg_dr_jet)
          ("nJet25_Recl",                    nJet25_Recl)
          ("ptmiss",                         ptmiss)
          ("htmiss",                         mht_p4.pt())
          ("tau1_mva",                        selHadTau->raw_mva())
          ("tau1_pt",                         selHadTau->pt())
          ("tau1_eta",                        selHadTau->absEta())
          ("tau1_phi",                        selHadTau->phi())
          ("mT_tau1",                        comp_MT_met(selHadTau,    met.pt(), met.phi()))
          ("dr_leps",                        dr_leps)
          ("mTauTauVis1",                    mTauTauVis1_sel)
          ("mTauTauVis2",                    mTauTauVis2_sel)
          ("memOutput_isValid",              memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.isValid()   : -100.)
          ("memOutput_errorFlag",            memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.errorFlag() : -100.)
          ("memOutput_LR",                   memOutput_LR.at(mem_option_main))
          ("lep1_genLepPt",                  lep1_genLepPt)
          ("lep2_genLepPt",                  lep2_genLepPt)
          ("tau_genTauPt",                   tau_genTauPt)
          //("lep1_fake_prob",                 selLepton_lead->genLepton() ? 1.0 : evtWeightRecorder.get_jetToLepton_FR_lead(central_or_shift_main))
          //("lep2_fake_prob",                 selLepton_sublead->genLepton()? 1.0 : evtWeightRecorder.get_jetToLepton_FR_sublead(central_or_shift_main))
          //("tau_fake_prob",                  selHadTau->genHadTau() || selHadTau->genLepton() ? 1.0 : evtWeightRecorder.get_jetToTau_FR_lead(central_or_shift_main))
          //("tau_fake_test",                  selHadTau->genHadTau() ? 1.0 : evtWeightRecorder.get_jetToTau_FR_lead(central_or_shift_main))

          ("hadtruth",               hadtruth)
          ("bWj1Wj2_isGenMatched_CSVsort4rd",              max_truth_HTT_CSVsort4rd)
          ("res_HTT",                 max_mvaOutput_HTT_CSVsort4rd)
          ("HadTop_pt",            HadTop_pt_CSVsort4rd)
          ("genTopPt_CSVsort4rd",             genTopPt_CSVsort4rd)

          ("genWeight",                      eventInfo.genWeight)
          ("evtWeight",                      evtWeightRecorder.get(central_or_shift_main))
          ("nJet",                           nJet25_Recl)
          ("nLep",                           selLeptons.size())
          ("nTau",                           selHadTaus.size())
          ("nBJetLoose",                     selBJets_loose.size())
          ("nBJetMedium",                    selBJets_medium.size())
          ("lep1_isTight",                   static_cast<int>(selLepton_lead->isTight()))
          ("lep2_isTight",                   static_cast<int>(selLepton_sublead->isTight()))
          ("tau_isTight",                    static_cast<int>(tightHadTauFilter(*selHadTau)))
          ("hadtruth",                       hadtruth)
          ("mbb_loose",                      selBJets_loose.size()  > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1000)
          ("failsTightChargeCut",            failsTightChargeCut)

          ("dr_Lep_lss",              dr_lss)
          ("dr_Lep_los1",             dr_los1)
          ("dr_Lep_los2",             dr_los2)
          ("eta_LepLep_los1",            eta_los1)
          ("eta_LepLep_los2",            eta_los2)
          ("eta_LepLep_los",             eta_los) // for min dr section 4.1 of arXiv:1404.1278
          ("mbb_medium",     selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : 0 )
          ("nElectron",      selElectrons.size())
          ("sum_Lep_charge", selLepton_lead -> charge() + selLepton_sublead -> charge() + selHadTau->charge())
          ("massL",          selLeptons.size() > 1 ? comp_massL2(selLeptons[0], selLeptons[1], met.pt(), met.phi())  : 0.)
          ("min_Deta_mostfwdJet_jet", min_Deta_mostfwdJet_jet)
          ("min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet)
          ("met_LD",    met_LD)
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
          ("mostFwdJet_eta",      selJetsForward.size() > 0 ? std::abs(mostFwdJet.Eta()) : -1000)
          ("mostFwdJet_pt",       selJetsForward.size() > 0 ? mostFwdJet.pt() : -1000)
          ("mostFwdJet_phi",      selJetsForward.size() > 0 ? mostFwdJet.phi() : -1000)
          ("mostFwdJet_E",        selJetsForward.size() > 0 ? mostFwdJet.energy() : -1000)
          ("leadFwdJet_eta",      selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : -1000)
          ("leadFwdJet_pt",       selJetsForward.size() > 0 ? selJetsForward[0] -> pt() : -1000)
          ("leadFwdJet_phi",      selJetsForward.size() > 0 ? selJetsForward[0] -> phi() : -1000)
          ("leadFwdJet_E",        selJetsForward.size() > 0 ? selJetsForward[0] -> p4().energy() : -1000)
          ("nJetForward",          selJetsForward.size())
          ("selHadTau_lead_deepTauRawe", selHadTau -> raw_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_lead_deepTauRawmu", selHadTau -> raw_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_lead_deepTauRawjet", selHadTau -> raw_mva(TauID::DeepTau2017v2VSjet))
          ("selHadTau_lead_deepTauIDe", selHadTau -> id_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_lead_deepTauIDmu", selHadTau -> id_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_lead_deepTauIDjet", selHadTau -> id_mva(TauID::DeepTau2017v2VSjet))
          ("selHadTau_lead_genHadTau", selHadTau->genHadTau() ? 1 : 0)
          ("selHadTau_lead_genLepton", selHadTau->genLepton() ? 1 : 0)
          ("selHadTau_lead_decayMode", selHadTau ->  decayMode())
          ("selHadTau_lead_idDecayMode", selHadTau ->  idDecayMode())
          ("tau1_mva_id",                     selHadTau->id_mva(TauID::MVAoldDMdR032017v2))
          ("massLT",          selLeptons.size() > 1 ? comp_massL2(selLeptons[0], selLeptons[1], met.pt(), met.phi())  : 0.)
          ("massL3",          selLeptons.size() > 1 ? comp_massL3(selLeptons[0], selLeptons[1], selHadTau, met.pt(), met.phi())  : 0.)

        .fill()
      ;
    }

    if(snm)
    {
      const double dr_lep1_tau1   = deltaR(selLepton_lead->p4(), selHadTau->p4());
      const double dr_lep2_tau1   = deltaR(selLepton_sublead->p4(), selHadTau->p4());
      const double max_dr_jet     = comp_max_dr_jet(selJets);
      const double mbb_loose      = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
      const double avr_dr_lep_tau = (dr_lep1_tau1 + dr_lep2_tau1) / 2;
      const double max_dr_lep_tau = std::max(dr_lep2_tau1, dr_lep1_tau1);
      const double min_dr_lep_tau = std::min(dr_lep2_tau1, dr_lep1_tau1);
      const double min_dr_lep_jet = std::min(mindr_lep1_jet, mindr_lep2_jet);
      const int nLightJet         = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(looseHadTaus);
      snm->read(selJets);

      snm->read({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
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
      // mindr_lep3_jet not filled
      // mindr_lep4_jet not filled

      snm->read(mvaOutput_NN_TF["predictions_ttH"],  FloatVariableType::mvaOutput_2lss_1tau_ttH);
      snm->read(mvaOutput_NN_TF["predictions_tH"],   FloatVariableType::mvaOutput_2lss_1tau_tH);
      snm->read(mvaOutput_NN_TF["predictions_rest"], FloatVariableType::mvaOutput_2lss_1tau_rest);

      snm->read(mindr_tau_jet,                          FloatVariableType::mindr_tau1_jet);
      // mindr_tau2_jet not filled

      snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
      snm->read(avr_dr_lep_tau,                         FloatVariableType::avr_dr_lep_tau);
      snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
      snm->read(max_dr_lep_tau,                         FloatVariableType::max_dr_lep_tau);
      snm->read(mindr_tau_jet,                          FloatVariableType::min_dr_tau_jet); // 1 tau
      snm->read(min_dr_lep_tau,                         FloatVariableType::min_dr_lep_tau);
      snm->read(min_dr_lep_jet,                         FloatVariableType::min_dr_lep_jet);

      snm->read(dr_leps,                                FloatVariableType::dr_leps);
      // dr_taus not filled

      // dr_lep_tau_ss not filled
      snm->read(dr_lep1_tau1,                           FloatVariableType::dr_lep1_tau1);
      // dr_lep1_tau2 not filled
      snm->read(dr_lep2_tau1,                           FloatVariableType::dr_lep2_tau1);
      // dr_lep3_tau1 not filled
      // dr_lep2_tau2 not filled

      snm->read(max_lep_eta,                            FloatVariableType::max_lep_eta);

      snm->read(mT_lep1,                                FloatVariableType::mT_met_lep1);
      snm->read(mT_lep2,                                FloatVariableType::mT_met_lep2);
      // mT_met_lep3 not filled
      // mT_met_lep4 not filled

      // mTauTauVis not filled
      snm->read(mTauTauVis1_sel,                        FloatVariableType::mvis_l1tau);
      snm->read(mTauTauVis2_sel,                        FloatVariableType::mvis_l2tau);

      snm->read(mbb,                                    FloatVariableType::mbb);
      snm->read(mbb_loose,                              FloatVariableType::mbb_loose);

      // cosThetaS_hadTau not filled
      snm->read(HTT,                                    FloatVariableType::HTT);
      snm->read(HadTop_pt,                              FloatVariableType::HadTop_pt);
      //snm->read(mvaOutput_Hj_tagger,                    FloatVariableType::Hj_tagger);

      // mvaOutput_plainKin_ttV not filled
      // mvaOutput_plainKin_tt not filled
      // mvaOutput_plainKin_1B_VT not filled
      // mvaOutput_HTT_SUM_VT not filled

      // mvaOutput_plainKin_SUM_VT not filled
      // mvaOutput_3l_ttV not filled
      // mvaOutput_3l_ttbar not filled
      // mvaOutput_plainKin_SUM_M not filled
      // mvaOutput_plainKin_1B_M not filled

      snm->read(evtWeightRecorder.get_FR(central_or_shift_main),             FloatVariableType::FR_weight);
      snm->read(evtWeightRecorder.get_sf_triggerEff(central_or_shift_main),  FloatVariableType::triggerSF_weight);
      snm->read(evtWeightRecorder.get_leptonSF(),                            FloatVariableType::leptonSF_weight);
      snm->read(evtWeightRecorder.get_tauSF(central_or_shift_main),          FloatVariableType::tauSF_weight);
      snm->read(evtWeightRecorder.get_btag(central_or_shift_main),           FloatVariableType::bTagSF_weight);
      snm->read(evtWeightRecorder.get_puWeight(central_or_shift_main),       FloatVariableType::PU_weight);
      snm->read(evtWeightRecorder.get_genWeight(),                           FloatVariableType::MC_weight);

      snm->read(memOutput_ttH,                          FloatVariableType::Integral_ttH);
      // Integral_tHq not filled
      // Integral_ttW not filled
      snm->read(memOutput_ttZ,                          FloatVariableType::Integral_ttZ);
      snm->read(memOutput_ttZ_Zll,                      FloatVariableType::Integral_ttZ_Zll);
      snm->read(memOutput_tt,                           FloatVariableType::Integral_ttbar);
      snm->read(memOutput_type,                         FloatVariableType::integration_type);
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
    process_and_genMatch += "&";
    process_and_genMatch += selHadTau_genMatch.name_;
    ++selectedEntries_byGenMatchType[process_and_genMatch];
    for(const std::string & central_or_shift: central_or_shifts_local)
    {
      selectedEntries_weighted_byGenMatchType[central_or_shift][process_and_genMatch] += evtWeightRecorder.get(central_or_shift);
    }
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
    for(const leptonChargeFlipGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
    {
      for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
      {
        std::string process_and_genMatch = process_string;
        process_and_genMatch += leptonGenMatch_definition.name_;
        process_and_genMatch += "&";
        process_and_genMatch += hadTauGenMatch_definition.name_;
        std::cout << " " << process_and_genMatch << " = " << selectedEntries_byGenMatchType[process_and_genMatch]
                  << " (weighted = " << selectedEntries_weighted_byGenMatchType[central_or_shift][process_and_genMatch] << ")\n";
      }
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
  delete jetToTauFakeRateInterface;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete metFilterReader;
  delete memReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;

  delete hadTopTagger;

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

  delete inputTree;
  delete snm;

  clock.Show("analyze_2lss_1tau");

  return EXIT_SUCCESS;
}
