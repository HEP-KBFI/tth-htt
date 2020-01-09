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
#include <TH2F.h> // TH2
#include <TROOT.h> // TROOT

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
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
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorForward.h" // RecoJetSelectorForward
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleanerSubJets.h" // RecoJetCollectionCleanerAK8SubJets
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
#include "tthAnalysis/HiggsToTauTau/interface/GenMatchInterface.h" // GenMatchInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h" // Data_to_MC_CorrectionInterface_0l_2tau_trigger
#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h" // DYMCReweighting
#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h" // DYMCNormScaleFactors
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_semi_boosted
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet tags
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h" // ClassicSVfit
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h" // classic_svFit::MeasuredTauLepton
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/mT2_2particle.h" // mT2_2particle::comp_mT
#include "tthAnalysis/HiggsToTauTau/interface/mT2_3particle.h" // mT2_3particle::comp_mT
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface.h" // HHWeightInterface

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()
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
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_2tau };

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

//--- stop ROOT from keeping track of all histograms
  TH1::AddDirectory(false);

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
  std::cout << "process_string " << process_string <<"\n";
  const bool isMC_tH = process_string == "tHq" || process_string == "tHW";
  const bool isMC_VH = process_string == "VH";
  const bool isMC_H  = process_string == "ggH" || process_string == "qqH" || process_string == "TTWH" || process_string == "TTZH";
  const bool isMC_HH = process_string == "HH";
  const bool isMC_signal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  const bool isSignal = isMC_signal || isMC_tH || isMC_VH || isMC_HH || isMC_H ;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_2tau = cfg_analyze.getParameter<vstring>("triggers_2tau");
  std::vector<hltPath*> triggers_2tau = create_hltPaths(triggerNames_2tau);
  bool use_triggers_2tau = cfg_analyze.getParameter<bool>("use_triggers_2tau");

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;
  const TauID tauId = TauID_PyMap.at(hadTauSelection_part2.substr(0, 7));
  int tauLevel = get_tau_id_wp_int(hadTauSelection_part2);

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau(true);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  GenMatchInterface genMatchInterface(2, apply_hadTauGenMatching);

  enum { kOS, kSS };
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  else throw cms::Exception("analyze_0l_2tau")
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift_main = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::vector<std::string> central_or_shifts_local = cfg_analyze.getParameter<std::vector<std::string>>("central_or_shifts_local");
  const bool do_tree = false; //(isSignal || process_string == "TTZ" || process_string == "TT" || process_string == "DY" ) && !(central_or_shifts_local.size() > 1);
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  const vstring categories_evt = cfg_analyze.getParameter<vstring>("evtCategories");
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_DYMCReweighting = cfg_analyze.getParameter<bool>("apply_DYMCReweighting");
  bool apply_DYMCNormScaleFactors = cfg_analyze.getParameter<bool>("apply_DYMCNormScaleFactors");
  bool apply_topPtReweighting = cfg_analyze.getParameter<bool>("apply_topPtReweighting");
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

  std::cout
    << "central_or_shift = "    << central_or_shift_main << "\n"
       " -> hadTauPt_option = " << hadTauPt_option       << "\n"
       " -> met_option      = " << met_option            << "\n"
       " -> jetPt_option    = " << jetPt_option          << '\n'
  ;

  DYMCReweighting * dyReweighting = nullptr;
  if(apply_DYMCReweighting)
  {
    dyReweighting = new DYMCReweighting(era);
  }
  DYMCNormScaleFactors * dyNormScaleFactors = nullptr;
  if(apply_DYMCNormScaleFactors)
  {
    dyNormScaleFactors = new DYMCNormScaleFactors(era);
  }

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
    default: throw cmsException("analyze_0l_2tau", __LINE__) << "Invalid era = " << era;
  }
  Data_to_MC_CorrectionInterface_0l_2tau_trigger * dataToMCcorrectionInterface_0l_2tau_trigger = nullptr;
  if(isMC)
  {
    dataToMCcorrectionInterface_0l_2tau_trigger = new Data_to_MC_CorrectionInterface_0l_2tau_trigger(cfg_dataToMCcorrectionInterface);
  }

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
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  edm::ParameterSet cfg_EvtYieldHistManager = cfg_analyze.getParameter<edm::ParameterSet>("cfgEvtYieldHistManager");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");
  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  std::string branchName_genTauLeptons = cfg_analyze.getParameter<std::string>("branchName_genTauLeptons");
  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  bool redoGenMatching = cfg_analyze.exists("redoGenMatching") ? cfg_analyze.getParameter<bool>("redoGenMatching") : true;
  bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

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
  EventInfo eventInfo(isMC, isSignal, isMC_HH, apply_topPtReweighting);
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

  hltPathReader hltPathReader_instance(triggers_2tau);
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
  fakeableElectronSelector.disable_offline_e_trigger_cuts();
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  tightElectronSelector.disable_offline_e_trigger_cuts();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose looseHadTauSelector(era, -1, isDEBUG);
  looseHadTauSelector.set_if_looser(hadTauSelection_part2);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauSelection_part2);
  switch(hadTauSelection)
  {
    case kFakeable: tauLevel = std::min(tauLevel, get_tau_id_wp_int(fakeableHadTauSelector.getSelector().get())); break;
    case kTight:    tauLevel = std::min(tauLevel, get_tau_id_wp_int(tightHadTauSelector.getSelector().get()));    break;
    default: assert(0);
  }

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics((central_or_shifts_local.size() > 1 || central_or_shift_main != "central") && isMC);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionCleaner jetCleaner_large8(0.8, isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);
  const RecoJetCollectionSelectorForward jetSelectorForward(era, -1, isDEBUG);

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);
  RecoJetCollectionCleanerAK8 jetCleanerAK8(0.8, isDEBUG); //to clean against leptons and hadronic taus
  RecoJetCollectionCleanerAK8SubJets jetCleanerAK8SubJets(0.4, isDEBUG); //to clean against leptons and hadronic taus

  GenParticleReader* genTauLeptonReader = nullptr;
  if ( isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors)) {
    genTauLeptonReader = new GenParticleReader(branchName_genTauLeptons);
    inputTree->registerReader(genTauLeptonReader);
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

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

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
      genPhotonReader = new GenPhotonReader(branchName_genPhotons);
      inputTree -> registerReader(genPhotonReader);
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

  //--- initialize hadronic top tagger BDT
  HadTopTagger* hadTopTagger = new HadTopTagger();
  HadTopTagger_semi_boosted_AK8* hadTopTagger_semi_boosted_fromAK8 = new HadTopTagger_semi_boosted_AK8();

  //--- initialize BDTs
  std::string mvaFileName_0l_2tau_deeptauLoose_2 = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/0l_2tau_DeepTauLoose_7.xml";
  std::vector<std::string> mvaInputVariables_0l_2tau_deeptau_4 = {
    "dr_taus", "mTauTauVis", "mTauTau", "cosThetaS_hadTau",
    "tau1_pt", "tau2_pt",
    "mbb_loose", "avg_dr_jet", "mindr_tau1_jet", "mindr_tau2_jet", "met_LD",
    "mT_tau1", "mT_tau2",
    "res_HTT", "max_Lep_eta"
  };
  TMVAInterface mva_xgb_Legacy(
    mvaFileName_0l_2tau_deeptauLoose_2,
    mvaInputVariables_0l_2tau_deeptau_4
  );
  mva_xgb_Legacy.enableBDTTransform();

  std::string mvaFileName_XGB_Updated = "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/0l_2tau_XGB_Updated_evtLevelSUM_TTH_20Var.xml";
  std::vector<std::string> mvaInputVariables_XGB_Updated = {
    "mindr_tau1_jet", "mindr_tau2_jet",
    "avg_dr_jet", "ptmiss", "tau1_pt", "tau2_pt", "tau1_eta", "tau2_eta",
    "dr_taus", "mT_tau1", "mT_tau2", "mTauTauVis", "mTauTau", "nJet",
    "nBJetLoose", "nBJetMedium",
    "res-HTT_CSVsort4rd_2", "res-HTT_CSVsort4rd", "HadTop_pt_CSVsort4rd_2", "HadTop_pt_CSVsort4rd"
  };
  TMVAInterface mva_XGB_Updated(mvaFileName_XGB_Updated, mvaInputVariables_XGB_Updated);
  mva_XGB_Updated.enableBDTTransform();
  std::map<std::string, double> mvaInputs_XGB_Updated;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;

//--- declare histograms
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    HadTauHistManager* leadHadTau_;
    HadTauHistManager* subleadHadTau_;
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
    MVAInputVarHistManager* mvaInputVariables_ttbar_unweight_;
    std::map<std::string, EvtHistManager_0l_2tau*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_0l_2tau*>> evt_in_decayModes_;
    std::map<std::string, std::map<std::string, std::map<int, EvtHistManager_0l_2tau*>>> evt_in_decayModes_scan_;
    std::map<std::string, EvtHistManager_0l_2tau*> evt_in_categories_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
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

      int idxHadTau = genMatchDefinition->getIdx();

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
        selHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/leadHadTau", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
        selHistManager->leadHadTau_->bookHistograms(fs);
        selHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/subleadHadTau", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
        selHistManager->subleadHadTau_->bookHistograms(fs);
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
        selHistManager->mvaInputVariables_ttbar_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/mvaInputs_ttbar", histogramDir.data()), era_string, central_or_shift));
        selHistManager->mvaInputVariables_ttbar_->bookHistograms(fs, mvaInputVariables_0l_2tau_deeptau_4);
	selHistManager->mvaInputVariables_ttbar_unweight_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
	  Form("%s/sel/mvaInputs_ttbar_unweight", histogramDir.data()), era_string, central_or_shift));
        selHistManager->mvaInputVariables_ttbar_unweight_->bookHistograms(fs, mvaInputVariables_0l_2tau_deeptau_4);
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
        selHistManager->evt_[evt_cat_str] = new EvtHistManager_0l_2tau(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
        ));
	      selHistManager->evt_[evt_cat_str]->bookHistograms(fs);

      }

      if(isSignal)
      {
        const vstring decayModes_evt = get_key_list_hist(eventInfo, isMC_HH, isMC_VH);

        for(const std::string & decayMode: decayModes_evt)
        {
          if(( isMC_tH || isMC_H ) && (decayMode == "hzg" || decayMode == "hmm" ))
          {
            continue;
          }
          std::string decayMode_and_genMatch = get_prefix(process_string, isMC_tH,  isMC_HH, isMC_H, isMC_VH);
          decayMode_and_genMatch += decayMode;
	        decayMode_and_genMatch += genMatchDefinition->getName();

          for(const std::string & evt_cat_str: evt_cat_strs)
          {
            if(skipBooking && evt_cat_str != default_cat_str)
            {
              continue;
            }
            const std::string process_string_new = evt_cat_str == default_cat_str  ?
              process_string :
              process_string + "_" + evt_cat_str
            ;
            const std::string decayMode_and_genMatchName = boost::replace_all_copy(
              decayMode_and_genMatch, process_string, process_string_new
            );

            selHistManager->evt_in_decayModes_[evt_cat_str][decayMode] = new EvtHistManager_0l_2tau(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
            ));
	    selHistManager->evt_in_decayModes_[evt_cat_str][decayMode]->bookHistograms(fs);

          }
        }
      }
      for(const std::string & category: categories_evt)
      {
        if(category == "0l_2tau")
        {
          // 0l_2tau subdirectory already created for the inclusive case
          continue;
        }
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("0l_2tau", category.data());
        selHistManager->evt_in_categories_[category] = new EvtHistManager_0l_2tau(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/evt", histogramDir_category.Data()), era_string, central_or_shift));
        selHistManager->evt_in_categories_[category]->bookHistograms(fs);

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
        selHistManager->weights_->bookHistograms(fs,
          { "genWeight", "pileupWeight", "data_to_MC_correction", "triggerWeight", "hadTauEff", "fakeRate" });
      }
      selHistManagers[central_or_shift][idxHadTau] = selHistManager;
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
  if(selectBDT || do_tree)
  {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string, central_or_shift_main)
    );
    for(const std::string & evt_cat_str: evt_cat_strs)
    {
      bdt_filler->register_variable<float_type>(evt_cat_str);
    }
    bdt_filler -> register_variable<float_type>(
      "mindr_tau1_jet", "mindr_tau2_jet",
      "avg_dr_jet", "ptmiss", "htmiss",
      "tau1_mva", "tau2_mva",
      "tau1_pt", "tau2_pt",
      "tau1_eta", "tau2_eta",
      "tau1_phi", "tau2_phi",
      "dr_taus", "mT_tau1", "mT_tau2", //"Pzeta", "PzetaVis",
      "mTauTauVis", "mTauTau",
      "res-HTT_CSVsort4rd", "res-HTT_CSVsort4rd_2",
      "HadTop_pt_CSVsort4rd", "HadTop_pt_CSVsort4rd_2",
      "genTopPt_CSVsort4rd", "genTopPt_CSVsort4rd_2",
      "HTT_semi_boosted_fromAK8", "genTopPt_semi_boosted_fromAK8", "HadTop_pt_semi_boosted_fromAK8",
      "minDR_AK8_lep",
      "minDR_AK8subjets_lep",
      "lumiScale", "genWeight", "evtWeight",
      "cosThetaS_hadTau",
      "massL", "pZetaComb",
      "min_Deta_mostfwdJet_jet", "min_Deta_leadfwdJet_jet",
      "met_LD", "jet1_pt", "jet1_eta",
      "jet1_pt", "jet1_eta", "jet1_phi", //"jet1_E",
      "jet2_pt", "jet2_eta", "jet2_phi", //"jet2_E",
      "jet3_pt", "jet3_eta", "jet3_phi", //"jet3_E",
      "jet4_pt", "jet4_eta", "jet4_phi", //"jet4_E",
      "mostFwdJet_eta", "mostFwdJet_pt", "mostFwdJet_phi", "mostFwdJet_E",
      "leadFwdJet_eta", "leadFwdJet_pt", "leadFwdJet_phi", "leadFwdJet_E",
      "mT2_W", "mT2_top_2particle", "mT2_top_3particle",
      "mbb_loose", "mbb_medium",
      "lumiScale", "genWeight",
      "selHadTau_lead_deepTauIDe",  "selHadTau_lead_deepTauIDmu", "selHadTau_lead_deepTauIDjet",
      "selHadTau_sublead_deepTauIDe", "selHadTau_sublead_deepTauIDmu", "selHadTau_sublead_deepTauIDjet",
      "selHadTau_lead_deepTauRawe", "selHadTau_lead_deepTauRawmu", "selHadTau_lead_deepTauRawjet",
      "selHadTau_sublead_deepTauRawe", "selHadTau_sublead_deepTauRawmu", "selHadTau_sublead_deepTauRawjet"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium",
      "N_jetAK8", "cleanedJets_fromAK8",
      "hadtruth", "hadtruth_2",
      "bWj1Wj2_isGenMatched_CSVsort4rd", "bWj1Wj2_isGenMatched_CSVsort4rd_2",
      "hadtruth_semi_boosted_fromAK8",
      "bWj1Wj2_isGenMatched_semi_boosted_fromAK8",
      "resolved_and_semi_AK8",
      "nJetForward",
      //
      "selHadTau_lead_genHadTau", "selHadTau_sublead_genHadTau",
      "selHadTau_lead_genLepton", "selHadTau_sublead_genLepton",
      "selHadTau_lead_antiMuon", "selHadTau_lead_antiElectron",
      "selHadTau_sublead_antiMuon", "selHadTau_sublead_antiElectron",
      "selHadTau_lead_decayMode", "selHadTau_lead_idDecayMode",
      "selHadTau_sublead_decayMode", "selHadTau_sublead_idDecayMode",
      //
      "selHadTau_lead_genHadTau_status", "selHadTau_sublead_genHadTau_status",
      "selHadTau_lead_genLepton_status", "selHadTau_sublead_genLepton_status",
      "selHadTau_lead_genJet", "selHadTau_sublead_genJet",
      "selHadTau_lead_genAny", "selHadTau_sublead_genAny",
      "selHadTau_lead_genPartFlav", "selHadTau_sublead_genPartFlav",
      "tau1_mva_id", "tau2_mva_id"
      //"passesTight_hadTau_lead", "passesTight_hadTau_sublead"
    );
    bdt_filler -> bookTree(fs);
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
    ">= 2 fakeable taus",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet",
    ">= 2 sel taus",
    "no tight leptons",
    "HLT filter matching",
    ">= 4 jets",
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
    EvtWeightRecorder evtWeightRecorder(central_or_shifts_local, central_or_shift_main, isMC);
    cutFlowTable.update("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));

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
      if(objectMultiplicity.getNRecoHadTau(tauId, tauLevel) < 2 ||
         objectMultiplicity.getNRecoLepton(kTight)          > 0  )
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

    std::vector<GenParticle> genTauLeptons;
    if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
    {
      genTauLeptons = genTauLeptonReader->read();
    }

    if(isMC)
    {
      if(apply_genWeight)         evtWeightRecorder.record_genWeight(boost::math::sign(eventInfo.genWeight));
      if(apply_DYMCReweighting)   evtWeightRecorder.record_dy_rwgt(dyReweighting, genTauLeptons);
      if(eventWeightManager)      evtWeightRecorder.record_auxWeight(eventWeightManager);
      if(l1PreFiringWeightReader) evtWeightRecorder.record_l1PrefireWeight(l1PreFiringWeightReader);
      if(apply_topPtReweighting)  evtWeightRecorder.record_toppt_rwgt(eventInfo.topPtRwgtSF);
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

    bool isTriggered_2tau = hltPaths_isTriggered(triggers_2tau, triggerWhiteList, eventInfo, isMC, isDEBUG);

    bool selTrigger_2tau = use_triggers_2tau && isTriggered_2tau;
    if ( !selTrigger_2tau ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
        std::cout << " (selTrigger_2tau = " << selTrigger_2tau << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("trigger", evtWeightRecorder.get(central_or_shift_main));
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

    const std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    const std::vector<const RecoLepton*> preselLeptonsUncleaned = mergeLeptonCollections(preselElectronsUncleaned, preselMuons, isHigherConePt);
    const std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    const std::vector<const RecoLepton*> tightLeptons = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau*> looseHadTaus = looseHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(looseHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    const std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 2);
    const std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    const std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("looseHadTaus",    looseHadTaus);
      printCollection("fakeableHadTaus", fakeableHadTaus);
      printCollection("tightHadTaus",    tightHadTaus);
      printCollection("selHadTaus",      selHadTaus);
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableLeptons, looseHadTaus) :
      jetCleaner       (jet_ptrs, fakeableLeptons, looseHadTaus)
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

//--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    const std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    const std::vector<const RecoJetAK8*> jet_ptrsAK8raw1 = convert_to_ptrs(jetsAK8);
    const std::vector<const RecoJetAK8*> jet_ptrsAK8raw = jetSelectorAK8(jet_ptrsAK8raw1, isHigherPt);;
    const std::vector<const RecoJetAK8*> jet_ptrsAK8 = jetCleanerAK8SubJets(jet_ptrsAK8raw, fakeableMuons, fakeableElectrons, selHadTaus);
    const std::vector<const RecoJet*> cleanedJets_fromAK8 = jetCleaner_large8(selJets, jet_ptrsAK8);

//--- build collections of generator level particles (after some cuts are applied, to save computing time)
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
    // require presence of at least two hadronic taus passing fakeable preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing fakeable preselection criteria contains significant contamination from jets)
    if ( !(fakeableHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 fakeable taus", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 fakeable taus", evtWeightRecorder.get(central_or_shift_main));

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 jets", evtWeightRecorder.get(central_or_shift_main));
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( isDEBUG )
      {  std::cout << "event " << eventInfo.str() << " FAILS >= 2 loose b-jets || 1 medium b-jet ." << std::endl;
      std::cout << "selBJets_loose.size() = " << selBJets_loose.size() << "selBJets_medium.size() = " << selBJets_medium.size() << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift_main));

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, looseHadTaus, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 2) ) {
      if ( isDEBUG ) std::cout << "event " << eventInfo.str() << " FAILS selHadTaus.size() >= 2; selHadTaus.size() = " << selHadTaus.size() << std::endl;
      continue;
    }
    cutFlowTable.update(">= 2 sel taus", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 sel taus", evtWeightRecorder.get(central_or_shift_main));
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);

    if(isMC)
    {
      if(apply_DYMCNormScaleFactors)
      {
        evtWeightRecorder.record_dy_norm(
          dyNormScaleFactors, genTauLeptons, selJets.size(), selBJets_loose.size(), selBJets_medium.size()
        );
      }
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);

      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(),
        selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta());

      dataToMCcorrectionInterface_0l_2tau_trigger->setHadTaus(
        selHadTau_lead->pt(),    selHadTau_lead->eta(),    selHadTau_lead->phi(),    selHadTau_lead->decayMode(),
        selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->phi(), selHadTau_sublead->decayMode()
      );
      dataToMCcorrectionInterface_0l_2tau_trigger->setTriggerBits(isTriggered_2tau);

//--- apply data/MC corrections for trigger efficiency
      evtWeightRecorder.record_tauTriggerEff(dataToMCcorrectionInterface_0l_2tau_trigger);

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      evtWeightRecorder.record_hadTauID_and_Iso(dataToMCcorrectionInterface);
      evtWeightRecorder.record_eToTauFakeRate(dataToMCcorrectionInterface);
      evtWeightRecorder.record_muToTauFakeRate(dataToMCcorrectionInterface);
    }

    // veto events that contain leptons passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptons.size() <= 0) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection." << std::endl;
        printCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("no tight leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("no tight leptons", evtWeightRecorder.get(central_or_shift_main));

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
    cutFlowTable.update("HLT filter matching", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeightRecorder.get(central_or_shift_main));

    if(! selectBDT && applyFakeRateWeights == kFR_2tau)
    {
      assert(jetToTauFakeRateInterface);
      evtWeightRecorder.record_jetToTau_FR_lead(jetToTauFakeRateInterface, selHadTau_lead);
      evtWeightRecorder.record_jetToTau_FR_sublead(jetToTauFakeRateInterface, selHadTau_sublead);
      bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTausFull);
      bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTausFull);
      evtWeightRecorder.compute_FR_2tau(passesTight_hadTau_lead, passesTight_hadTau_sublead);
    }

    double mTauTauVis = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();

    // apply requirement on jets (incl. b-tagged jets) on level of final event selection
    if ( !(selJets.size() >= 4) ) continue;
    cutFlowTable.update(">= 4 jets", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 4 jets", evtWeightRecorder.get(central_or_shift_main));

    if(run_lumi_eventSelector || isDEBUG)
    {
      std::cout << "event " << eventInfo.str()
      << "\n selJets.size() = " << selJets.size()
      << "\n selBJets_medium.size() = " << selBJets_medium.size()
      << "\n selBJets_loose.size() = "<< selBJets_loose.size()
      << "\n selJetsForward.size()" << selJetsForward.size()
      << std::endl;
      printCollection("selJetsForward", selJetsForward);
      printCollection("selBJets_medium", selBJets_medium);
      printCollection("selBJets_loose", selBJets_loose);
    }

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsUncleaned);
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));

    if ( !(selHadTau_lead->pt() > minPt_hadTau_lead && selHadTau_lead->absEta() < 2.1) ) {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS lead tau pt eta; selHadTau_lead->pt()  " << selHadTau_lead->pt()  << "abs(eta)" << selHadTau_lead->absEta()  << " \n";
      }
      continue;
    }
    cutFlowTable.update(Form("lead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_lead), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(Form("lead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_lead), evtWeightRecorder.get(central_or_shift_main));

    if ( !(selHadTau_sublead->pt() > minPt_hadTau_sublead && selHadTau_sublead->absEta() < 2.1) ) {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS sublead tau pt eta; selHadTau_sublead->pt()  " << selHadTau_sublead->pt()  << "abs(eta)" << selHadTau_sublead->absEta()  << " \n";
      }
      continue;
    }
    cutFlowTable.update(Form("sublead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_sublead), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(Form("sublead hadTau pT > %.0f GeV && abs(eta) < 2.1", minPt_hadTau_sublead), evtWeightRecorder.get(central_or_shift_main));

    bool isCharge_SS = selHadTau_lead->charge()*selHadTau_sublead->charge() > 0;
    bool isCharge_OS = selHadTau_lead->charge()*selHadTau_sublead->charge() < 0;
    if(hadTauChargeSelection == kOS && isCharge_SS)
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS OS tau-pair selection\n";
      }
      continue;
    }
    if ( hadTauChargeSelection == kSS && isCharge_OS )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS SS tau-pair selection\n";
      }
      continue;
    }
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("tau-pair OS/SS charge", evtWeightRecorder.get(central_or_shift_main));

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

    //--- compute output of hadronic top tagger BDT
    // it returns the gen-triplets organized in top/anti-top
    bool calculate_matching = isMC && selectBDT && !applyAdditionalEvtWeight; // DY has not matching info
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
    //double HadTop_eta_CSVsort4rd = 0.;
    double genTopPt_CSVsort4rd = 0.;
    double b_pt_1 = 0.1;
    double Wj1_pt_1 = 0.1;
    double Wj2_pt_1 = 0.1;
    double max_mvaOutput_HTT_CSVsort4rd_2 = 0.;
    bool max_truth_HTT_CSVsort4rd_2 = false;
    double HadTop_pt_CSVsort4rd_2 = 0.;
    double genTopPt_CSVsort4rd_2 = 0.;

    bool hadtruth = false;
    bool hadtruth_2 = false;
    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet ) {
      //btag_iterator++;
      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1 ) {
       if ( &(*selWJet1) == &(*selBJet) ) continue;
       for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selJets.begin(); selWJet2 != selJets.end(); ++selWJet2 ) {
    if ( &(*selWJet2) == &(*selBJet) ) continue;
    if ( &(*selWJet2) == &(*selWJet1) ) continue;
    bool isGenMatched = false;
    double genTopPt_teste = 0.;
    const std::map<int, double> bdtResult = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti );
    // genTopPt_teste is filled with the result of gen-matching
    if ( isGenMatched ) hadtruth = true;
    // save genpt of all options
    double HadTop_pt = ((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).pt();

    if ( bdtResult.at(kXGB_CSVsort4rd) > max_mvaOutput_HTT_CSVsort4rd ) {
      max_truth_HTT_CSVsort4rd = isGenMatched;
      max_mvaOutput_HTT_CSVsort4rd = bdtResult.at(kXGB_CSVsort4rd);
      HadTop_pt_CSVsort4rd = HadTop_pt;
      genTopPt_CSVsort4rd = genTopPt_teste;
      //HadTop_eta_CSVsort4rd = std::fabs(((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).eta());
      Wj1_pt_1 = (*selWJet1)->pt();
      Wj2_pt_1 = (*selWJet2)->pt();
      b_pt_1   = (*selBJet)->pt();
    }

    }
      }
    }
    ///--- the second res-HTT
    if ( selJets.size() > 5 ){
    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin(); selBJet != selJets.end(); ++selBJet ) {
      if (b_pt_1 == (*selBJet)->pt() || Wj1_pt_1 == (*selBJet)->pt() || Wj2_pt_1 == (*selBJet)->pt()) continue;
      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selJets.begin(); selWJet1 != selJets.end(); ++selWJet1 ) {
       if ( &(*selWJet1) == &(*selBJet) ) continue;
       if (b_pt_1 == (*selWJet1)->pt() || Wj1_pt_1 == (*selWJet1)->pt() || Wj2_pt_1 == (*selWJet1)->pt()) continue;
       for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1; selWJet2 != selJets.end(); ++selWJet2 ) {
    if (b_pt_1 == (*selWJet2)->pt() || Wj1_pt_1 == (*selWJet2)->pt() || Wj2_pt_1 == (*selWJet2)->pt()) continue;
    if ( &(*selWJet2) == &(*selBJet) ) continue;
    if ( &(*selWJet2) == &(*selWJet1) ) continue;
    bool isGenMatched = false;
    double genTopPt_teste = 0.;
    const std::map<int, double> bdtResult = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti );
    // genTopPt_teste is filled with the result of gen-matching
    if ( isGenMatched ) hadtruth_2 = true;
    // save genpt of all options
    double HadTop_pt = ((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).pt();

    if ( bdtResult.at(kXGB_CSVsort4rd) > max_mvaOutput_HTT_CSVsort4rd_2 ) {
      max_truth_HTT_CSVsort4rd_2 = isGenMatched;
      max_mvaOutput_HTT_CSVsort4rd_2 = bdtResult.at(kXGB_CSVsort4rd);
      HadTop_pt_CSVsort4rd_2 = HadTop_pt;
      genTopPt_CSVsort4rd_2 = genTopPt_teste;
    }
    }
        }
      } // close loop on jetS
    } // close if 6 jets
    if (isDEBUG) std::cout<< max_mvaOutput_HTT_CSVsort4rd_2 << " " << max_mvaOutput_HTT_CSVsort4rd << std::endl;

    // compute overlaps semi-boosted resolved / semi-boosted and boosted / ...
    bool resolved_and_semi_AK8 = false;

    // -- semi-boosted hTT -- AK8
    double HTT_semi_boosted_fromAK8 = 0.;
    bool bWj1Wj2_isGenMatched_semi_boosted_fromAK8 = false;
    double genTopPt_semi_boosted_fromAK8 = 0.;
    double HadTop_pt_semi_boosted_fromAK8 = 0.;
    bool hadtruth_semi_boosted_fromAK8 = false;
    double minDR_AK8_lep = -1.;
    double minDR_AK8subjets_lep = -1.;
    for ( std::vector<const RecoJet*>::const_iterator selBJet = cleanedJets_fromAK8.begin(); selBJet != cleanedJets_fromAK8.end(); ++selBJet )  {
    for ( std::vector<const RecoJetAK8*>::const_iterator jetIter = jet_ptrsAK8.begin();
          jetIter != jet_ptrsAK8.end(); ++jetIter ) {

        bool isGenMatched = false;
        double genTopPt_teste = 0.;
        double HadTop_pt = ((*jetIter)->p4() + (*selBJet)->p4()).pt();
        const std::map<int, double> bdtResult = (*hadTopTagger_semi_boosted_fromAK8)(**jetIter, **selBJet, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti);
        if (isGenMatched) {hadtruth_semi_boosted_fromAK8 = true;}

        if ( bdtResult.at(kXGB_semi_boosted_AK8_no_kinFit) > HTT_semi_boosted_fromAK8 ) {
          bWj1Wj2_isGenMatched_semi_boosted_fromAK8 = isGenMatched;
          HTT_semi_boosted_fromAK8 = bdtResult.at(kXGB_semi_boosted_AK8_no_kinFit);
          HadTop_pt_semi_boosted_fromAK8 = HadTop_pt;
          genTopPt_semi_boosted_fromAK8 = genTopPt_teste;
          minDR_AK8_lep = std::min(
            deltaR(selHadTau_lead->p4(), (*jetIter)->p4()),
            deltaR(selHadTau_sublead->p4(), (*jetIter)->p4())
          );

          minDR_AK8subjets_lep =
          std::min(
          std::min(
            deltaR(selHadTau_lead->p4(), (*jetIter)->subJet1()->p4()),
            deltaR(selHadTau_sublead->p4(), (*jetIter)->subJet1()->p4())
          ),
          std::min(
            deltaR(selHadTau_lead->p4(), (*jetIter)->subJet2()->p4()),
            deltaR(selHadTau_sublead->p4(), (*jetIter)->subJet2()->p4())
          )
         );
        }

      }
    }
    if (genTopPt_CSVsort4rd == genTopPt_semi_boosted_fromAK8)  resolved_and_semi_AK8 = true;

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
    //double mTauTau = -1.; // CV: temporarily comment-out the following line, to make code compile with "old" and "new" version of ClassicSVfit
    double mTauTau   = ( svFitAlgo.isValidSolution() ) ? static_cast<classic_svFit::HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass() : -1.;
    double mT_tau1   = comp_MT_met(selHadTau_lead, met.pt(), met.phi());
    double mT_tau2   = comp_MT_met(selHadTau_sublead, met.pt(), met.phi());
    //double pZeta     = comp_pZeta(selHadTau_lead -> p4(), selHadTau_sublead -> p4(), met.p4().px(), met.p4().py());
    //double pZetaVis  = comp_pZetaVis(selHadTau_lead -> p4(), selHadTau_sublead -> p4());
    double pZetaComb = comp_pZetaComb(selHadTau_lead -> p4(), selHadTau_sublead -> p4(), met.p4().px(), met.p4().py());

    //compute di-b-jet mass
    const double mbb             = selBJets_medium.size() > 1 ? (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1.;
    const double mbb_loose       = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
    //const double pt_HHvis_loose        = selBJets_loose.size() > 1 ? (selHadTau_lead->p4()+selHadTau_sublead->p4()+selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).pt() : -1.;
    //const double pt_HHvis_medium        = selBJets_medium.size() > 1 ? (selHadTau_lead->p4()+selHadTau_sublead->p4()+selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).pt() : -1.;

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
    const double mindr_tau1_jet  = std::min(10., comp_mindr_jet(*selHadTau_lead, selJets));
    const double mindr_tau2_jet  = std::min(10., comp_mindr_jet(*selHadTau_sublead, selJets));
    const double cosThetaS_hadTau = comp_cosThetaStar(selHadTau_lead->p4(), selHadTau_sublead->p4());


    const std::map<std::string, double> mvaInputs_ttbar = {
      {"max_Lep_eta",      std::max({selHadTau_lead->absEta(), selHadTau_sublead->absEta()})},
      {"res_HTT",          max_mvaOutput_HTT_CSVsort4rd},
      //{"HadTop_pt",        HadTop_pt_CSVsort4rd},
      //{"HadTop_pt_2",      HadTop_pt_CSVsort4rd_2},
      {"dr_taus",          deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4())},
      {"tau1_pt",          selHadTau_lead -> pt()},
      {"tau2_pt",          selHadTau_sublead -> pt()},
      {"avg_dr_jet",       comp_avg_dr_jet(selJets)},
      {"mTauTauVis",       mTauTauVis},
      {"mTauTau",          mTauTau},
      {"cosThetaS_hadTau", cosThetaS_hadTau },
      {"mbb_loose",        mbb_loose},
      {"met_LD",           met_LD},
      //{"nBJetLoose",        selBJets_loose.size()},
      //{"nJet",		selJets.size()},
      {"mindr_tau1_jet",   TMath::Min(10., comp_mindr_jet(*selHadTau_lead, selJets))},
      {"mindr_tau2_jet",   TMath::Min(10., comp_mindr_jet(*selHadTau_sublead, selJets))},
      {"mT_tau1",          comp_MT_met(selHadTau_lead, met.pt(), met.phi())},
      {"mT_tau2",          comp_MT_met(selHadTau_sublead, met.pt(), met.phi())}
      };
    double mva_0l_2tau_deeptauLoose_2 = mva_xgb_Legacy(mvaInputs_ttbar);

    // mvaInputs_XGB_Updated
    mvaInputs_XGB_Updated["mindr_tau1_jet"] = TMath::Min(10., comp_mindr_jet(*selHadTau_lead, selJets));
    mvaInputs_XGB_Updated["mindr_tau2_jet"] = TMath::Min(10., comp_mindr_jet(*selHadTau_sublead, selJets));
    mvaInputs_XGB_Updated["avg_dr_jet"] = comp_avg_dr_jet(selJets);
    mvaInputs_XGB_Updated["ptmiss"] = met.pt();
    mvaInputs_XGB_Updated["tau1_pt"] = selHadTau_lead->pt();
    mvaInputs_XGB_Updated["tau2_pt"] = selHadTau_sublead->pt();
    mvaInputs_XGB_Updated["tau1_eta"] = selHadTau_lead->absEta();
    mvaInputs_XGB_Updated["tau2_eta"] = selHadTau_sublead->absEta();
    mvaInputs_XGB_Updated["dr_taus"] = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_XGB_Updated["mT_tau1"] = comp_MT_met(selHadTau_lead, met.pt(), met.phi());
    mvaInputs_XGB_Updated["mT_tau2"] = comp_MT_met(selHadTau_sublead, met.pt(), met.phi());
    mvaInputs_XGB_Updated["mTauTauVis"] = mTauTauVis;
    mvaInputs_XGB_Updated["mTauTau"] = mTauTau;
    mvaInputs_XGB_Updated["nJet"] = selJets.size();
    mvaInputs_XGB_Updated["nBJetLoose"] = selBJets_loose.size();
    mvaInputs_XGB_Updated["nBJetMedium"] = selBJets_medium.size();
    mvaInputs_XGB_Updated["res-HTT_CSVsort4rd_2"] = max_mvaOutput_HTT_CSVsort4rd_2;
    mvaInputs_XGB_Updated["res-HTT_CSVsort4rd"] = max_mvaOutput_HTT_CSVsort4rd;
    mvaInputs_XGB_Updated["HadTop_pt_CSVsort4rd_2"] = HadTop_pt_CSVsort4rd_2;
    mvaInputs_XGB_Updated["HadTop_pt_CSVsort4rd"] = HadTop_pt_CSVsort4rd;
    double mva_Updated = mva_XGB_Updated(mvaInputs_XGB_Updated);

//--- retrieve gen-matching flags
    std::vector<const GenMatchEntry*> genMatches = genMatchInterface.getGenMatch(selHadTaus);

//--- fill histograms with events passing final selection
    std::map<std::string, double> tH_weight_map;
    for(const std::string & central_or_shift: central_or_shifts_local)
    {
      const double evtWeight = evtWeightRecorder.get(central_or_shift);
      const double evtWeight_noDYNorm = evtWeight/evtWeightRecorder.get_dy_norm(central_or_shift);
      const bool skipFilling = central_or_shift != central_or_shift_main;
      for (const GenMatchEntry* genMatch : genMatches)
      {
        selHistManagerType* selHistManager = selHistManagers[central_or_shift][genMatch->getIdx()];
        assert(selHistManager);
        if(! skipFilling)
        {
          selHistManager->electrons_->fillHistograms(preselElectrons, evtWeight);
          selHistManager->muons_->fillHistograms(preselMuons, evtWeight);
          selHistManager->hadTaus_->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
          selHistManager->leadHadTau_->fillHistograms(selHadTaus, evtWeight);
          selHistManager->subleadHadTau_->fillHistograms(selHadTaus, evtWeight);
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
	  selHistManager->mvaInputVariables_ttbar_unweight_->fillHistograms(mvaInputs_ttbar, evtWeight_noDYNorm);
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
          EvtHistManager_0l_2tau* selHistManager_evt = selHistManager->evt_[kv.first];
          if ( selHistManager_evt )
          {
            selHistManager_evt->fillHistograms(
            preselElectrons.size(), preselMuons.size(), selHadTaus.size(),
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
            mva_0l_2tau_deeptauLoose_2,
            mva_Updated,
            mTauTauVis,
            mTauTau,
            kv.second
          );
          }
        }

        if ( isSignal ) {
          std::string decayModeStr = get_key_hist(eventInfo, genWBosons, isMC_HH, isMC_VH);
          if(! decayModeStr.empty() && !((isMC_tH || isMC_H) && ( decayModeStr == "hzg" || decayModeStr == "hmm" )))
          {
            for(const auto & kv: tH_weight_map)
            {
              EvtHistManager_0l_2tau* selHistManager_evt_category_decayModes = selHistManager->evt_in_decayModes_[kv.first][decayModeStr];
              if ( selHistManager_evt_category_decayModes )
              {
              selHistManager_evt_category_decayModes->fillHistograms(
                  preselElectrons.size(),
                  preselMuons.size(),
                  selHadTaus.size(),
                  selJets.size(),
                  selBJets_loose.size(),
                  selBJets_medium.size(),
                  mva_0l_2tau_deeptauLoose_2,
                  mva_Updated,
                  mTauTauVis,
                  mTauTau,
                  kv.second
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
          selHistManager->weights_->fillHistograms("data_to_MC_correction", evtWeightRecorder.get_data_to_MC_correction(central_or_shift));
          selHistManager->weights_->fillHistograms("triggerWeight", evtWeightRecorder.get_sf_triggerEff(central_or_shift));
          selHistManager->weights_->fillHistograms("hadTauEff", evtWeightRecorder.get_tauSF(central_or_shift));
          selHistManager->weights_->fillHistograms("fakeRate", evtWeightRecorder.get_FR(central_or_shift));
        }

        std::vector<std::string> categories;
        if   ( selBJets_medium.size() >= 2 ) categories.push_back("0l_2tau_2bM_2j");
        if   ( selBJets_medium.size() >= 1 ) categories.push_back("0l_2tau_1bM_2j");
        else                                 categories.push_back("0l_2tau_0bM_2j");
        for(const std::string & category: categories)
        {
          EvtHistManager_0l_2tau* selHistManager_evt_category = selHistManager->evt_in_categories_[category];
          if ( selHistManager_evt_category )
          {
          selHistManager_evt_category->fillHistograms(
            preselElectrons.size(), preselMuons.size(), selHadTaus.size(),
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
            mva_0l_2tau_deeptauLoose_2,
            mva_Updated,
            mTauTauVis,
            mTauTau,
            evtWeight
          );
          }
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

    if(bdt_filler)
    {
      //compute di-b-jet mass

      double mT2_top_3particle = -1.;
      double mT2_top_2particle = -1.;
      double mT2_W = -1.;
      const Particle::LorentzVector& selLeptonP4_lead = selHadTau_lead->p4();
      const Particle::LorentzVector& selLeptonP4_sublead = selHadTau_sublead->p4();
      //const RecoJetBase* selJet1_Hbb = selJets[0];
      //const RecoJetBase* selJet2_Hbb = selJets[1];

      if ( selJets.size() >= 2 ) {
        const Particle::LorentzVector& selJetP4_Hbb_lead = selJets[0]->p4();
        const Particle::LorentzVector& selJetP4_Hbb_sublead = selJets[1]->p4();
        mT2_2particle mT2Algo_2particle;
        const Particle::LorentzVector& metP4 = met.p4();
        mT2Algo_2particle(
          selLeptonP4_lead.px(), selLeptonP4_lead.py(), selLeptonP4_lead.mass(),
          selLeptonP4_sublead.px(), selLeptonP4_sublead.py(), selLeptonP4_sublead.mass(),
          metP4.px(), metP4.py(), 0.);
        mT2_W = mT2Algo_2particle.get_min_mT2();
      double cSumPx = selLeptonP4_lead.px() + selLeptonP4_sublead.px() + metP4.px();
      double cSumPy = selLeptonP4_lead.py() + selLeptonP4_sublead.py() + metP4.py();
      mT2Algo_2particle(
        selJetP4_Hbb_lead.px(), selJetP4_Hbb_lead.py(), selJetP4_Hbb_lead.mass(),
        selJetP4_Hbb_sublead.px(), selJetP4_Hbb_sublead.py(), selJetP4_Hbb_sublead.mass(),
        cSumPx, cSumPy, wBosonMass);
      mT2_top_2particle = mT2Algo_2particle.get_min_mT2();
      mT2_3particle mT2Algo_3particle;
      mT2Algo_3particle(
        selJetP4_Hbb_lead.px(), selJetP4_Hbb_lead.py(), selJetP4_Hbb_lead.mass(),
        selJetP4_Hbb_sublead.px(), selJetP4_Hbb_sublead.py(), selJetP4_Hbb_sublead.mass(),
        selLeptonP4_lead.px(), selLeptonP4_lead.py(), selLeptonP4_lead.mass(),
        selLeptonP4_sublead.px(), selLeptonP4_sublead.py(), selLeptonP4_sublead.mass(),
        metP4.px(), metP4.py(), 0.);
      double mT2_top_3particle_permutation1 = mT2Algo_3particle.get_min_mT2();
      mT2Algo_3particle(
        selJetP4_Hbb_lead.px(), selJetP4_Hbb_lead.py(), selJetP4_Hbb_lead.mass(),
        selJetP4_Hbb_sublead.px(), selJetP4_Hbb_sublead.py(), selJetP4_Hbb_sublead.mass(),
        selLeptonP4_sublead.px(), selLeptonP4_sublead.py(), selLeptonP4_sublead.mass(),
        selLeptonP4_lead.px(), selLeptonP4_lead.py(), selLeptonP4_lead.mass(),
        metP4.px(), metP4.py(), 0.);
      double mT2_top_3particle_permutation2 = mT2Algo_3particle.get_min_mT2();

      if ( mT2_top_3particle_permutation1 <= mT2_top_3particle_permutation2 ) {
        mT2_top_3particle = mT2_top_3particle_permutation1;
      } else {
        mT2_top_3particle = mT2_top_3particle_permutation2;
      }
    }

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

      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("mindr_tau1_jet", TMath::Min(10., comp_mindr_jet(*selHadTau_lead, selJets)))
          ("mindr_tau2_jet", TMath::Min(10., comp_mindr_jet(*selHadTau_sublead, selJets)))
          ("avg_dr_jet",     comp_avg_dr_jet(selJets))
          ("ptmiss",         met.pt())
          ("htmiss",         mht_p4.pt())
          ("tau1_mva",       selHadTau_lead -> raw_mva())
          ("tau2_mva",       selHadTau_sublead -> raw_mva())
          ("tau1_pt",        selHadTau_lead -> pt())
          ("tau2_pt",        selHadTau_sublead -> pt())
          ("tau1_phi",       selHadTau_lead -> phi())
          ("tau2_phi",       selHadTau_sublead -> phi())
          ("tau1_eta",       selHadTau_lead -> eta())
          ("tau2_eta",       selHadTau_sublead -> eta())
          ("dr_taus",        deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4()))
          ("mT_tau1",        mT_tau1)
          ("mT_tau2",        mT_tau2)
          ("mTauTauVis",     mTauTauVis)
          ("mTauTau",        mTauTau)
          ("lumiScale",      evtWeightRecorder.get_lumiScale(central_or_shift_main))
          ("genWeight",      eventInfo.genWeight)
          ("evtWeight",      evtWeightRecorder.get(central_or_shift_main))
          ("nJet",           selJets.size())
          ("nBJetLoose",     selBJets_loose.size())
          ("nBJetMedium",    selBJets_medium.size())
          ("hadtruth",               hadtruth)
          ("hadtruth_2",               hadtruth_2)
          ("res-HTT_CSVsort4rd",                 max_mvaOutput_HTT_CSVsort4rd)
          ("res-HTT_CSVsort4rd_2",                 max_mvaOutput_HTT_CSVsort4rd_2)
          ("bWj1Wj2_isGenMatched_CSVsort4rd",              max_truth_HTT_CSVsort4rd)
          ("bWj1Wj2_isGenMatched_CSVsort4rd_2",              max_truth_HTT_CSVsort4rd_2)
          ("HadTop_pt_CSVsort4rd",            HadTop_pt_CSVsort4rd)
          ("HadTop_pt_CSVsort4rd_2",            HadTop_pt_CSVsort4rd_2)
          ("genTopPt_CSVsort4rd",             genTopPt_CSVsort4rd)
          ("genTopPt_CSVsort4rd_2",             genTopPt_CSVsort4rd_2)
          ("resolved_and_semi_AK8",     resolved_and_semi_AK8)
          ("N_jetAK8",     jet_ptrsAK8.size())
          ("cleanedJets_fromAK8",       cleanedJets_fromAK8.size())
          ("minDR_AK8_lep",                minDR_AK8_lep)
          ("minDR_AK8subjets_lep",         minDR_AK8subjets_lep)
          ("HTT_semi_boosted_fromAK8",                     HTT_semi_boosted_fromAK8)
          ("bWj1Wj2_isGenMatched_semi_boosted_fromAK8",    bWj1Wj2_isGenMatched_semi_boosted_fromAK8)
          ("genTopPt_semi_boosted_fromAK8",            genTopPt_semi_boosted_fromAK8)
          ("HadTop_pt_semi_boosted_fromAK8",           HadTop_pt_semi_boosted_fromAK8)
          ("hadtruth_semi_boosted_fromAK8",          hadtruth_semi_boosted_fromAK8)

          ("nJetForward",         selJetsForward.size())
          ("mT2_W",                         mT2_W)
          ("mT2_top_2particle",             mT2_top_2particle)
          ("mT2_top_3particle",             mT2_top_3particle)
          ("pZetaComb",      pZetaComb)
          ("cosThetaS_hadTau", cosThetaS_hadTau )
          ("massL",           massL(fakeableLeptons))
          ("mbb_loose",       mbb_loose)
          ("mbb_medium",     mbb)
          ("met_LD",              met_LD)
          ("jet1_pt",   selJets.size() > 0 ? selJets[0]->pt() : -1000)
          ("jet1_eta",  selJets.size() > 0 ? selJets[0]->eta() : -1000)
          ("jet1_phi",  selJets.size() > 0 ? selJets[0]->phi() : -1000)
          //("jet1_E",    selJets.size() > 0 ? selJets[0]->p4().energy() : -1000)
          ("jet2_pt",   selJets.size() > 1 ? selJets[1]->pt() : -1000)
          ("jet2_eta",  selJets.size() > 1 ? selJets[1]->eta() : -1000)
          ("jet2_phi",  selJets.size() > 1 ? selJets[1]->phi() : -1000)
          //("jet2_E",    selJets.size() > 1 ? selJets[1]->p4().energy() : -1000)
          ("jet3_pt",   selJets.size() > 2 ? selJets[2]->pt() : -1000)
          ("jet3_eta",  selJets.size() > 2 ? selJets[2]->eta() : -1000)
          ("jet3_phi",  selJets.size() > 2 ? selJets[2]->phi() : -1000)
          //("jet3_E",    selJets.size() > 2 ? selJets[2]->p4().energy() : -1000)
          ("jet4_pt",   selJets.size() > 3 ? selJets[3]->pt() : -1000)
          ("jet4_eta",  selJets.size() > 3 ? selJets[3]->eta() : -1000)
          ("jet4_phi",  selJets.size() > 3 ? selJets[3]->phi() : -1000)
          //("jet4_E",    selJets.size() > 3 ? selJets[3]->p4().energy() : -1000)
          ("leadFwdJet_eta",      selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : -1000)
          ("leadFwdJet_pt",       selJetsForward.size() > 0 ? selJetsForward[0] -> pt() : -1000)
          ("leadFwdJet_phi",      selJetsForward.size() > 0 ? selJetsForward[0] -> phi() : -1000)
          ("leadFwdJet_E",        selJetsForward.size() > 0 ? selJetsForward[0] -> p4().energy() : -1000)
          ("nJetForward",         selJetsForward.size())
          ("mostFwdJet_eta",      selJetsForward.size() > 0 ? std::abs(mostFwdJet.Eta()) : -1000)
          ("mostFwdJet_pt",       selJetsForward.size() > 0 ? mostFwdJet.pt() : -1000)
          ("mostFwdJet_phi",      selJetsForward.size() > 0 ? mostFwdJet.phi() : -1000)
          ("mostFwdJet_E",        selJetsForward.size() > 0 ? mostFwdJet.energy() : -1000)
          ("min_Deta_mostfwdJet_jet", min_Deta_mostfwdJet_jet)
          ("min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet)
          // add mT2 and tau rau id
          ("selHadTau_lead_deepTauIDe", selHadTau_lead -> id_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_lead_deepTauIDmu", selHadTau_lead -> id_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_lead_deepTauIDjet", selHadTau_lead -> id_mva(TauID::DeepTau2017v2VSjet))
          ("selHadTau_sublead_deepTauIDe", selHadTau_sublead -> id_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_sublead_deepTauIDmu", selHadTau_sublead -> id_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_sublead_deepTauIDjet", selHadTau_sublead ->  id_mva(TauID::DeepTau2017v2VSjet))

          ("selHadTau_lead_deepTauRawe", selHadTau_lead -> raw_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_lead_deepTauRawmu", selHadTau_lead -> raw_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_lead_deepTauRawjet", selHadTau_lead -> raw_mva(TauID::DeepTau2017v2VSjet))
          ("selHadTau_sublead_deepTauRawe", selHadTau_sublead -> raw_mva(TauID::DeepTau2017v2VSe))
          ("selHadTau_sublead_deepTauRawmu", selHadTau_sublead -> raw_mva(TauID::DeepTau2017v2VSmu))
          ("selHadTau_sublead_deepTauRawjet", selHadTau_sublead -> raw_mva(TauID::DeepTau2017v2VSjet))

          ("selHadTau_lead_genHadTau", selHadTau_lead->genHadTau() ? 1 : 0 )
          ("selHadTau_sublead_genHadTau", selHadTau_sublead->genHadTau() ? 1 : 0)

          ("selHadTau_lead_genLepton", selHadTau_lead->genLepton() ? selHadTau_lead->genLepton()->pdgId()  : 0)
          ("selHadTau_sublead_genLepton", selHadTau_sublead->genLepton() ? selHadTau_sublead->genLepton()->pdgId()  : 0)

          ("selHadTau_lead_genHadTau_status", selHadTau_lead->genHadTau() ? selHadTau_lead->genHadTau()->status()  : 0 )
          ("selHadTau_sublead_genHadTau_status", selHadTau_sublead->genHadTau() ? selHadTau_sublead->genHadTau()->status()  : 0)

          ("selHadTau_lead_genLepton_status", selHadTau_lead->genLepton() ? selHadTau_lead->genLepton()->status()  : 0)
          ("selHadTau_sublead_genLepton_status", selHadTau_sublead->genLepton() ? selHadTau_sublead->genLepton()->status()  : 0)

          ("selHadTau_lead_genJet", selHadTau_lead->genJet() ? selHadTau_lead->genJet()->pdgId() : -1)
          ("selHadTau_sublead_genJet", selHadTau_sublead->genJet() ? selHadTau_sublead->genJet()->pdgId() : -1)

          ("selHadTau_lead_genAny", selHadTau_lead->hasAnyGenMatch() ? 1 : 0)
          ("selHadTau_sublead_genAny", selHadTau_sublead->hasAnyGenMatch() ? 1 : 0)

          ("selHadTau_lead_genPartFlav", selHadTau_lead->genPartFlav())
          ("selHadTau_sublead_genPartFlav", selHadTau_sublead->genPartFlav())

          ("selHadTau_lead_antiMuon", selHadTau_lead-> antiMuon())
          ("selHadTau_lead_antiElectron", selHadTau_lead-> antiElectron())
          ("selHadTau_sublead_antiMuon", selHadTau_sublead-> antiMuon())
          ("selHadTau_sublead_antiElectron", selHadTau_sublead-> antiElectron())

          ("selHadTau_lead_decayMode", selHadTau_lead ->  decayMode())
          ("selHadTau_lead_idDecayMode", selHadTau_lead ->  idDecayMode())
          ("selHadTau_sublead_decayMode", selHadTau_sublead ->  decayMode())
          ("selHadTau_sublead_idDecayMode", selHadTau_sublead ->  idDecayMode())

          ("tau1_mva_id",    selHadTau_lead -> id_mva(TauID::MVAoldDMdR032017v2))
          ("tau2_mva_id",    selHadTau_sublead -> id_mva(TauID::MVAoldDMdR032017v2))
          (tH_weight_map)
        .fill()
      ;

    }

    if(snm)
    {
      const double avg_dr_jet      = comp_avg_dr_jet(selJets);
      const double max_dr_jet      = comp_max_dr_jet(selJets);
      const double min_dr_tau_jet  = std::min(mindr_tau1_jet, mindr_tau2_jet);
      const double dr_taus         = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
      const int nLightJet          = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      snm->read(eventInfo);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(looseHadTaus);
      snm->read(selJets);

      snm->read({ triggers_2tau });
      snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size(), nLightJet);

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);
      snm->read(mva_0l_2tau_deeptauLoose_2,             FloatVariableType::mvaOutput_0l_2tau);

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
      snm->read(mTauTau,                                FloatVariableType::mTauTau);
      snm->read(pZetaComb,                              FloatVariableType::pZetaComb);
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

      snm->read(evtWeightRecorder.get_FR(central_or_shift_main),             FloatVariableType::FR_weight);
      snm->read(evtWeightRecorder.get_sf_triggerEff(central_or_shift_main),  FloatVariableType::triggerSF_weight);
      // weight_leptonEff not filled
      snm->read(evtWeightRecorder.get_tauSF(central_or_shift_main),          FloatVariableType::tauSF_weight);
      snm->read(evtWeightRecorder.get_btag(central_or_shift_main),           FloatVariableType::bTagSF_weight);
      snm->read(evtWeightRecorder.get_puWeight(central_or_shift_main),       FloatVariableType::PU_weight);
      snm->read(evtWeightRecorder.get_genWeight(),                           FloatVariableType::MC_weight);

      // Integral_ttH not filled
      // Integral_ttZ not filled
      // Integral_ttZ_Zll not filled
      // Integral_ttbar not filled
      // integration_type not filled
      // MEM_LR not filled

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
    for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
    {
      std::string process_and_genMatch = process_string;
      process_and_genMatch += hadTauGenMatch_definition.name_;
      std::cout << " " << process_and_genMatch << " = " << selectedEntries_byGenMatchType[process_and_genMatch]
                << " (weighted = " << selectedEntries_weighted_byGenMatchType[central_or_shift][process_and_genMatch] << ")\n";
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

  hltPaths_delete(triggers_2tau);

  delete inputTree;
  delete snm;

  //fmap->Close();

  clock.Show("analyze_0l_2tau");

  return EXIT_SUCCESS;
}
