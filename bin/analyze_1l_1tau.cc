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
#include <TRandom3.h> // TRandom3
#include <TH2.h> // TH2
#include <TLorentzVector.h> // TLorentzVector
#include <TROOT.h> // TROOT

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 1l_1tau category
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_1tau.h" // EvtHistManager_1l_1tau
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/GenMatchInterface.h" // GenMatchInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_1L, getWeight_2L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_1tau_trigger.h" // Data_to_MC_CorrectionInterface_1l_1tau_trigger
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
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManagerWrapper.h" // SyncNtupleManagerWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncGenMatchCharge
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface.h" // HHWeightInterface

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h" // ClassicSVfit
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h" // classic_svFit::MeasuredTauLepton
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/mT2_2particle.h" // mT2_2particle::comp_mT
#include "tthAnalysis/HiggsToTauTau/interface/mT2_3particle.h" // mT2_3particle::comp_mT

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

#include <Python.h>

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { k1e_btight, k1e_bloose, k1mu_btight, k1mu_bloose };
enum { kFR_disabled, kFR_2L, kFR_1tau };

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied
const int hadTauSelection_veto_antiElectron = -1; // CV: needs to match anti-electron discriminator applied in 1l+1tau category
const int hadTauSelection_veto_antiMuon = -1; // CV: needs to match anti-muon discriminator applied in 1l+1tau category

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

double comp_cosThetaS(const Particle::LorentzVector& hadTauP4_lead, const Particle::LorentzVector& hadTauP4_sublead)
{
  TLorentzVector hadTauP4tlv_lead;
  hadTauP4tlv_lead.SetPtEtaPhiM(hadTauP4_lead.pt(), hadTauP4_lead.eta(), hadTauP4_lead.phi(), hadTauP4_lead.mass());
  TLorentzVector hadTauP4tlv_sublead;
  hadTauP4tlv_sublead.SetPtEtaPhiM(hadTauP4_sublead.pt(), hadTauP4_sublead.eta(), hadTauP4_sublead.phi(), hadTauP4_sublead.mass());
  TLorentzVector diTauP4 = hadTauP4tlv_lead + hadTauP4tlv_sublead;
  TLorentzVector hadTauBoost = hadTauP4tlv_lead;
  hadTauBoost.Boost(-diTauP4.BoostVector());
  return std::fabs(hadTauBoost.CosTheta());
}

/**
 * @brief Produce datacard and control plots for 1l_1tau category.
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

  std::cout << "<analyze_1l_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_1l_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_1l_1tau")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_1l_1tau");

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
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e, "triggers_1e");
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1e1tau = cfg_analyze.getParameter<vstring>("triggers_1e1tau");
  std::vector<hltPath*> triggers_1e1tau = create_hltPaths(triggerNames_1e1tau, "triggers_1e1tau");
  bool use_triggers_1e1tau = cfg_analyze.getParameter<bool>("use_triggers_1e1tau");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu, "triggers_1mu");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_1mu1tau = cfg_analyze.getParameter<vstring>("triggers_1mu1tau");
  std::vector<hltPath*> triggers_1mu1tau = create_hltPaths(triggerNames_1mu1tau, "triggers_1mu1tau");
  bool use_triggers_1mu1tau = cfg_analyze.getParameter<bool>("use_triggers_1mu1tau");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1e1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1tau");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_1mu1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu1tau");

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonChargeFlipGenMatchEntry> leptonGenMatch_definitions = getLeptonChargeFlipGenMatch_definitions_1lepton(true);
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
  std::vector<hadTauChargeFlipGenMatchEntry> hadTauGenMatch_definitions = getHadTauChargeFlipGenMatch_definitions_1tau(true);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  GenMatchInterface genMatchInterface(1, apply_leptonGenMatching, true, 1, apply_hadTauGenMatching, true);

  enum { kOS, kSS, kDisabled };
  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS"       ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS"       ) chargeSumSelection = kSS;
  else if ( chargeSumSelection_string == "disabled" ) chargeSumSelection = kDisabled;
  else throw cms::Exception("analyze_1l_1tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift_main = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::vector<std::string> central_or_shifts_local = cfg_analyze.getParameter<std::vector<std::string>>("central_or_shifts_local");
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

  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");

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
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_1l_1tau", __LINE__) << "Invalid era = " << era;
  }

  Data_to_MC_CorrectionInterface_1l_1tau_trigger * dataToMCcorrectionInterface_1l_1tau_trigger = nullptr;
  if(isMC)
  {
    dataToMCcorrectionInterface_1l_1tau_trigger = new Data_to_MC_CorrectionInterface_1l_1tau_trigger(cfg_dataToMCcorrectionInterface);
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2L"       ) applyFakeRateWeights = kFR_2L;
  else if ( applyFakeRateWeights_string == "1tau"     ) applyFakeRateWeights = kFR_1tau;
  else throw cms::Exception("analyze_1l_1tau")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2L || applyFakeRateWeights == kFR_1tau ) {
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

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
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

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;

  const double maxAbsEta_lepton = 2.1;
  const double minPt_e = 30.;
  const double minPt_mu = 25.;
  const double minPt_hadTau = 30.;

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- prepare sync Ntuple
  const std::vector<std::vector<hltPath *>> hltPaths{ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau };
  SyncNtupleManagerWrapper snmw(syncNtuple_cfg, hltPaths, SyncGenMatchCharge::kAll);

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
  const int minLeptonSelection = std::min(electronSelection, muonSelection);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau });
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
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  switch(hadTauSelection)
  {
    case kFakeable: tauLevel = std::min(tauLevel, get_tau_id_wp_int(fakeableHadTauSelector.getSelector().get())); break;
    case kTight:    tauLevel = std::min(tauLevel, get_tau_id_wp_int(tightHadTauSelector.getSelector().get()));    break;
    default: assert(0);
  }

  // CV: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 1l+1tau category
  RecoHadTauCollectionSelectorTight vetoHadTauSelector(era, -1, isDEBUG);
  vetoHadTauSelector.set(hadTauSelection_veto);
  vetoHadTauSelector.set_min_antiElectron(hadTauSelection_veto_antiElectron);
  vetoHadTauSelector.set_min_antiMuon(hadTauSelection_veto_antiMuon);

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
    if (! readGenObjects)
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

//--- initialize hadronic top tagger BDT
  HadTopTagger* hadTopTagger = new HadTopTagger();
  HadTopTagger_semi_boosted_AK8* hadTopTagger_semi_boosted_fromAK8 = new HadTopTagger_semi_boosted_AK8();

//--- initialize eventlevel BDTs
  std::vector<std::string> mvaInputVariables_1l_1tau_opt ={
    "lep_conePt", "avg_dr_jet",
    "mT_lep", "mT_tau",
    "tau_pt", "dr_lep_tau",
    "costS", "mTauTauVis", "mTauTau",
    "res_HTT", "res_HTT_2",
    "mbb_loose", "met_LD",
    "charge_lep_tau",
    "max_Lep_eta", "Lep_min_dr_jet"
  };
  std::string mvaFileName_1l_1tau_DeepTauMedium_6 = "tthAnalysis/HiggsToTauTau/data/NN_for_legacy_opt/1l_1tau_DeepTauLoose_6.xml";
  TMVAInterface mva_1l_1tau_Legacy_6(
    mvaFileName_1l_1tau_DeepTauMedium_6,
    mvaInputVariables_1l_1tau_opt
  );
  mva_1l_1tau_Legacy_6.enableBDTTransform();

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
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
    std::map<std::string, EvtHistManager_1l_1tau*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_1l_1tau*>> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_1l_1tau*> evt_in_categories_;
    std::map<std::string, std::map<std::string, std::map<std::string, EvtHistManager_1l_1tau*>>> evt_in_categories_and_decayModes_;
    EvtYieldHistManager* evtYield_;
    std::map<std::string, EvtYieldHistManager*> evtYield_in_categories_;
    WeightHistManager* weights_;
  };

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

        selHistManager->evt_[evt_cat_str] = new EvtHistManager_1l_1tau(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
        ));
        selHistManager->evt_[evt_cat_str]->bookHistograms(fs);
      }

      if(isSignal)
      {
        const vstring decayModes_evt = get_key_list_hist( eventInfo, isMC_HH, isMC_VH);
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

            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] = new EvtHistManager_1l_1tau(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
            ));
            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> bookHistograms(fs);
          }
        }
      }
      for(const std::string & category: categories_evt)
      {
        if(category == "1l_1tau")
        {
          // 1l_1tau subdirectory already created for the inclusive case
          continue;
        }
        selHistManager->evt_in_categories_and_decayModes_[category] = {};
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category.data());

        selHistManager->evt_in_categories_[category] = new EvtHistManager_1l_1tau(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/evt", histogramDir_category.Data()), era_string, central_or_shift));
        selHistManager->evt_in_categories_[category]->bookHistograms(fs);

        if ( isSignal ) {
          const vstring decayModes_evt = get_key_list_hist(eventInfo, isMC_HH, isMC_VH);

          for ( const std::string & decayMode_evt: decayModes_evt ) {

            if ( ( isMC_tH || isMC_H ) && ( decayMode_evt == "hzg" || decayMode_evt == "hmm" ) ) continue;
            selHistManager->evt_in_categories_and_decayModes_[category][decayMode_evt] = {};

            for(const std::string & evt_cat_str: evt_cat_strs)
            {
              if(skipBooking && evt_cat_str != default_cat_str)
              {
                continue;
              }

              std::string decayMode_and_genMatch = get_prefix(process_string, isMC_tH,  isMC_HH, isMC_H, isMC_VH);
              decayMode_and_genMatch += decayMode_evt;
              decayMode_and_genMatch += genMatchDefinition->getName();

              const std::string process_string_new = evt_cat_str == default_cat_str ?
                process_string:
                process_string + "_" + evt_cat_str
              ;
              const std::string decayMode_and_genMatchName = boost::replace_all_copy(
                decayMode_and_genMatch, process_string, process_string_new
              );

              selHistManager->evt_in_categories_and_decayModes_[category][decayMode_evt][evt_cat_str] = new EvtHistManager_1l_1tau(
                makeHistManager_cfg(decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir_category.Data()), era_string, central_or_shift)
              );
              selHistManager->evt_in_categories_and_decayModes_[category][decayMode_evt][evt_cat_str]->bookHistograms(fs);
            }
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

        for(const std::string & category: categories_evt)
        {
          if(category == "1l_1tau")
          {
            // 1l_1tau subdirectory already created for the inclusive case
            continue;
          }
          TString histogramDir_category = histogramDir.data();
          histogramDir_category.ReplaceAll("1l_1tau", category.data());
          edm::ParameterSet cfg_EvtYieldHistManager_category = makeHistManager_cfg(process_and_genMatch,
            Form("%s/sel/evtYield", histogramDir_category.Data()), era_string, central_or_shift);
          cfg_EvtYieldHistManager_category.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
          cfg_EvtYieldHistManager_category.addParameter<bool>("isMC", isMC);
          selHistManager->evtYield_in_categories_[category] = new EvtYieldHistManager(cfg_EvtYieldHistManager_category);
          selHistManager->evtYield_in_categories_[category]->bookHistograms(fs);
        }
        selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/weights", histogramDir.data()), era_string, central_or_shift));
        selHistManager->weights_->bookHistograms(fs,
          { "genWeight", "pileupWeight", "data_to_MC_correction", "triggerWeight", "leptonEff", "hadTauEff", "fakeRate" });
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

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string, central_or_shift_main)
    );
    bdt_filler->register_variable<float_type>(
      "lep_pt", "lep_conePt", "lep_eta", "lep_tth_mva", "mindr_lep_jet", "mindr_tau_jet",
      "avg_dr_jet", "ptmiss", "mT_lep", "mT_tau", "htmiss", "tau_mva", "tau_pt",
      "tau_eta", "dr_lep_tau",
      "costS", "mTauTauVis", "mTauTau", "Pzeta", "PzetaVis", "PzetaComb",
      "res-HTT_CSVsort4rd", "res-HTT_CSVsort4rd_2",
      "HadTop_pt_CSVsort4rd", "HadTop_pt_CSVsort4rd_2",
      "genTopPt_CSVsort4rd", "genTopPt_CSVsort4rd_2",
      "HTT_semi_boosted_fromAK8", "genTopPt_semi_boosted_fromAK8", "HadTop_pt_semi_boosted_fromAK8",
      "minDR_AK8_lep",
      "minDR_AK8subjets_lep",
      "lumiScale", "genWeight", "evtWeight",
      "prob_fake_lepton", "prob_fake_hadTau","mbb_medium","mbb_loose",
      "met_LD", "leadFwdJet_eta", "leadFwdJet_pt", "leadFwdJet_phi", "leadFwdJet_E",
      "massL",
      "min_Deta_leadfwdJet_jet",
      "jet1_pt", "jet1_eta", "jet1_phi", "jet1_E",
      "jet2_pt", "jet2_eta", "jet2_phi", "jet2_E",
      "jet3_pt", "jet3_eta", "jet3_phi", "jet3_E",
      "jet4_pt", "jet4_eta", "jet4_phi", "jet4_E",
      "selHadTau_lead_deepTauIDe",  "selHadTau_lead_deepTauIDmu", "selHadTau_lead_deepTauIDjet",
      "selHadTau_lead_deepTauRawe", "selHadTau_lead_deepTauRawmu", "selHadTau_lead_deepTauRawjet"
    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "nJetForward",
      "charge_lep_tau",
      "N_jetAK8", "cleanedJets_fromAK8",
      "hadtruth", "hadtruth_2",
      "bWj1Wj2_isGenMatched_CSVsort4rd", "bWj1Wj2_isGenMatched_CSVsort4rd_2",
      "hadtruth_semi_boosted_fromAK8",
      "bWj1Wj2_isGenMatched_semi_boosted_fromAK8",
      "resolved_and_semi_AK8",
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
    ">= 1 presel lepton",
    ">= 1 fakeable tau",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet",
    ">= 1 sel lepton",
    "<= 1 tight leptons",
    ">= 1 sel tau",
    "<= 1 veto taus",
    "HLT filter matching",
    ">= 4 jets",
    "m(ll) > 12 GeV",
    Form("sel lepton pT > %.0f(e)/%.0f(mu) GeV", minPt_e, minPt_mu),
    Form("sel lepton abs(eta) < %.1f", maxAbsEta_lepton),
    Form("sel hadTau pT > %.0f GeV", minPt_hadTau),
    Form("lepton+tau %s charge", chargeSumSelection_string.data()),
    "MEt filters",
    "signal region veto",
  };
  CutFlowTableHistManager * cutFlowHistManager = new CutFlowTableHistManager(cutFlowTableCfg, cuts);
  cutFlowHistManager->bookHistograms(fs);

  double countFatTopEntries = 0;
  double countFatTop = 0;
  double countFatTopTruth = 0;
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
    //if (analyzedEntries > 1000) break;

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    EvtWeightRecorder evtWeightRecorder(central_or_shifts_local, central_or_shift_main, isMC);
    cutFlowTable.update("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("run:ls:event selection", evtWeightRecorder.get(central_or_shift_main));

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if ( inputTree->isOpen() ) {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(minLeptonSelection) < 1 ||
         objectMultiplicity.getNRecoLepton(kTight)             > 1 ||
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
    std::vector<GenPhoton> genPhotons;
    std::vector<GenHadTau> genHadTaus;
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

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, isDEBUG);
    bool isTriggered_1e1tau = hltPaths_isTriggered(triggers_1e1tau, isDEBUG);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu, isDEBUG);
    bool isTriggered_1mu1tau = hltPaths_isTriggered(triggers_1mu1tau, isDEBUG);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1e1tau = use_triggers_1e1tau && isTriggered_1e1tau;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1mu1tau = use_triggers_1mu1tau && isTriggered_1mu1tau;

    if ( !(selTrigger_1e || selTrigger_1e1tau || selTrigger_1mu || selTrigger_1mu1tau) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
        std::cout << " (selTrigger_1e = " << selTrigger_1e
                  << ", selTrigger_1e1tau = " << selTrigger_1e1tau
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau << ")" << std::endl;
      }
      continue;
    }

//--- Rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 1mu || 1mu1tau, 1e || 1e1tau
// CV: This logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets.
//     The mu+tau (e+tau) cross trigger is stored in the same primary dataset as the single muon (single electron) trigger during the 2017 data-taking period!!
    if ( !isMC && !isDEBUG ) {
      bool isTriggered_SingleMuon = isTriggered_1mu || isTriggered_1mu1tau;
      bool selTrigger_SingleElectron = selTrigger_1e || selTrigger_1e1tau;

      if ( selTrigger_SingleElectron && isTriggered_SingleMuon ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
                    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon << ")" << std::endl;
        }
        continue;
      }
    }

    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("trigger", evtWeightRecorder.get(central_or_shift_main));

    if ( (selTrigger_1mu     && !apply_offline_e_trigger_cuts_1mu)     ||
         (selTrigger_1mu1tau && !apply_offline_e_trigger_cuts_1mu1tau) ||
         (selTrigger_1e      && !apply_offline_e_trigger_cuts_1e)      ||
         (selTrigger_1e1tau  && !apply_offline_e_trigger_cuts_1e1tau)  ) {
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

    const std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 1);
    const std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 1);
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
    const std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    const std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 1);
    const std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    const std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
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

    // CV: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 1l+1tau category
    const std::vector<const RecoHadTau*> vetoHadTaus = vetoHadTauSelector(cleanedHadTaus, isHigherPt);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, selectBDT ? selHadTaus : fakeableHadTausFull) :
      jetCleaner       (jet_ptrs, selectBDT ? selLeptons_full : fakeableLeptonsFull, selectBDT ? selHadTaus : fakeableHadTausFull)
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

        hadTauGenMatcher.addGenLeptonMatch(fakeableHadTaus, genLeptons);
        hadTauGenMatcher.addGenHadTauMatch(fakeableHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch   (fakeableHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets, genJets);
      }
    }

//--- apply preselection
    // require exactly one lepton passing loose preselection criteria
    if ( !(preselLeptonsFull.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 presel lepton", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 1 presel lepton", evtWeightRecorder.get(central_or_shift_main));

    // require presence of at least one hadronic tau passing fakeable preselection criteria
    // (do not veto events with more than one fakeable selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing fakeable preselection criteria contains significant contamination from jets)
    if ( !(fakeableHadTausFull.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 fakeable tau", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 1 fakeable tau", evtWeightRecorder.get(central_or_shift_main));

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 jets", evtWeightRecorder.get(central_or_shift_main));

    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet", evtWeightRecorder.get(central_or_shift_main));

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptonsFull, fakeableHadTausFull, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    if ( !(selLeptons.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 sel lepton", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 1 sel lepton", evtWeightRecorder.get(central_or_shift_main));

    const RecoLepton* selLepton = selLeptons[0];
    int selLepton_type = getLeptonType(selLepton->pdgId());
    const leptonChargeFlipGenMatchEntry& selLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, selLepton);

    // require exactly one lepton passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptonsFull.size() <= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection.\n";
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 1 tight leptons", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("<= 1 tight leptons", evtWeightRecorder.get(central_or_shift_main));

    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 1) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS because there aren't enough taus:\n";
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 1 sel tau", evtWeightRecorder.get(central_or_shift_main));
    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauChargeFlipGenMatchEntry& selHadTau_genMatch = getHadTauChargeFlipGenMatch(hadTauGenMatch_definitions, selHadTau);

    // veto events containing more than one tau passing the Medium WP, to avoid overlap with the 1l+1tau category
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

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,      selTrigger_1e      },
        { hltPathsE::trigger_1mu,     selTrigger_1mu     },
        { hltPathsE::trigger_1e1tau,  selTrigger_1e1tau  },
        { hltPathsE::trigger_1mu1tau, selTrigger_1mu1tau },
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

      int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);

      dataToMCcorrectionInterface->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());

      dataToMCcorrectionInterface_1l_1tau_trigger->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      dataToMCcorrectionInterface_1l_1tau_trigger->setHadTaus(selHadTau->pt(), selHadTau->eta(), selHadTau->phi(), selHadTau->decayMode());
      dataToMCcorrectionInterface_1l_1tau_trigger->setTriggerBits(isTriggered_1e, isTriggered_1e1tau, isTriggered_1mu, isTriggered_1mu1tau);

//--- apply data/MC corrections for trigger efficiency
      evtWeightRecorder.record_tauTriggerEff(dataToMCcorrectionInterface_1l_1tau_trigger);

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

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      evtWeightRecorder.record_hadTauID_and_Iso(dataToMCcorrectionInterface);
      evtWeightRecorder.record_eToTauFakeRate(dataToMCcorrectionInterface);
      evtWeightRecorder.record_muToTauFakeRate(dataToMCcorrectionInterface);
    }

    if(! selectBDT)
    {
      if(applyFakeRateWeights == kFR_2L)
      {
        evtWeightRecorder.record_jetToLepton_FR_lead(leptonFakeRateInterface, selLepton);
        evtWeightRecorder.record_jetToTau_FR_lead(jetToTauFakeRateInterface, selHadTau);

        const bool passesTight_lepton = isMatched(*selLepton, tightElectrons) || isMatched(*selLepton, tightMuons);
        const bool passesTight_hadTau = isMatched(*selHadTau, tightHadTausFull);

        evtWeightRecorder.compute_FR_1l1tau(passesTight_lepton, passesTight_hadTau);
      }
      else if( applyFakeRateWeights == kFR_1tau)
      {
        evtWeightRecorder.record_jetToTau_FR_lead(jetToTauFakeRateInterface, selHadTau);
        evtWeightRecorder.compute_FR_1tau();
      }

      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if(isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight)
      {
        if(! (selHadTau->genHadTau() || selHadTau->genLepton()))
        {
          evtWeightRecorder.record_jetToTau_SF_lead(jetToTauFakeRateInterface, selHadTau);
        }
      }
    }

    // apply requirement on jets (incl. b-tagged jets) on level of final event selection
    if ( !(selJets.size() >= 4) )
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS to have at least 4 jets \n";
      }
      continue;
    }
    cutFlowTable.update(">= 4 jets", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(">= 4 jets", evtWeightRecorder.get(central_or_shift_main));

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsFullUncleaned);
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeightRecorder.get(central_or_shift_main));

    const double minPt = selLepton->is_electron() ? minPt_e : minPt_mu;
    if ( !(selLepton->cone_pt() > minPt) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS minPt = " << minPt << " < cut on the selected lepton\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton pT > %.0f(e)/%.0f(mu) GeV", minPt_e, minPt_mu), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(Form("sel lepton pT > %.0f(e)/%.0f(mu) GeV", minPt_e, minPt_mu), evtWeightRecorder.get(central_or_shift_main));

    if ( !(selLepton->absEta() < maxAbsEta_lepton) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS maxAbsEta = " << maxAbsEta_lepton << " > cut on the selected lepton\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton abs(eta) < %.1f", maxAbsEta_lepton), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(Form("sel lepton abs(eta) < %.1f", maxAbsEta_lepton), evtWeightRecorder.get(central_or_shift_main));

    if ( !(selHadTau->pt() > minPt_hadTau) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS minPt = " << minPt_hadTau << " < cut on the selected tau\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel hadTau pT > %.0f GeV", minPt_hadTau), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms(Form("sel hadTau pT > %.0f GeV", minPt_hadTau), evtWeightRecorder.get(central_or_shift_main));

    bool isCharge_SS = selLepton->charge()*selHadTau->charge() > 0;
    bool isCharge_OS = selLepton->charge()*selHadTau->charge() < 0;
    if ( chargeSumSelection == kOS && isCharge_SS )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS OS lepton+tau selection." << std::endl;
      }
      continue;
    }
    if ( chargeSumSelection == kSS && isCharge_OS )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS SS lepton+tau selection." << std::endl;
      }
      continue;
    }
    cutFlowTable.update(Form("lepton+tau %s charge", chargeSumSelection_string.data()), evtWeightRecorder.get(central_or_shift_main));
    cutFlowHistManager->fillHistograms("lepton+tau OS/SS charge", evtWeightRecorder.get(central_or_shift_main));

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
    if ( isMCClosure_e || isMCClosure_m || isMCClosure_t ) {
      bool applySignalRegionVeto_lepton = (isMCClosure_e && countFakeElectrons(selLeptons) >= 1) || (isMCClosure_m && countFakeMuons(selLeptons) >= 1);
      bool applySignalRegionVeto_hadTau = isMCClosure_t && countFakeHadTaus(selHadTaus) >= 1;
      if ( applySignalRegionVeto_lepton && tightLeptons.size() >= 1 ) failsSignalRegionVeto = true;
      if ( applySignalRegionVeto_hadTau && tightHadTaus.size() >= 1 ) failsSignalRegionVeto = true;
    } else if ( electronSelection == kFakeable || muonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( tightLeptons.size() >= 1 && tightHadTaus.size() >= 1 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
	             "# tight leptons = " << tightLeptons.size() << " >= 1 and "
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
    std::map<std::string, double> Weight_ktScan; // weights to do histograms
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
       for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1; selWJet2 != selJets.end(); ++selWJet2 ) {
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
            deltaR(selLepton->p4(), (*jetIter)->p4()),
            deltaR(selHadTau->p4(), (*jetIter)->p4())
          );

          minDR_AK8subjets_lep =
          std::min(
          std::min(
            deltaR(selLepton->p4(), (*jetIter)->subJet1()->p4()),
            deltaR(selHadTau->p4(), (*jetIter)->subJet1()->p4())
          ),
          std::min(
            deltaR(selLepton->p4(), (*jetIter)->subJet2()->p4()),
            deltaR(selHadTau->p4(), (*jetIter)->subJet2()->p4())
          )
         );
        }

      }
    }
    if (genTopPt_CSVsort4rd == genTopPt_semi_boosted_fromAK8)  resolved_and_semi_AK8 = true;

//--- reconstruct mass of lepton+tau using SVfit algorithm
//
//    NOTE: SVfit needs to be run after all event selection cuts are applied,
//          because the algorithm takes O(1 second per event) to run
//
    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
    classic_svFit::MeasuredTauLepton::kDecayType leg1Type = classic_svFit::MeasuredTauLepton::kUndefinedDecayType;
    double leg1Mass = -1.;
    if ( selLepton_type == kElectron ) {
      leg1Type = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
      leg1Mass = classic_svFit::electronMass;
    } else if ( selLepton_type == kMuon ) {
      leg1Type = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
      leg1Mass = classic_svFit::muonMass;
    } else assert(0);
    classic_svFit::MeasuredTauLepton::kDecayType leg2Type = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    double leg2Mass = selHadTau->mass();
    if ( leg2Mass < classic_svFit::chargedPionMass ) leg2Mass = classic_svFit::chargedPionMass;
    if ( leg2Mass > 1.5                            ) leg2Mass = 1.5;
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg1Type, selLepton->pt(), selLepton->eta(), selLepton->phi(), leg1Mass));
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg2Type, selHadTau->pt(), selHadTau->eta(), selHadTau->phi(), leg2Mass));
    ClassicSVfit svFitAlgo;
    svFitAlgo.addLogM_dynamic(false);
    svFitAlgo.addLogM_fixed(true, 4.);
    svFitAlgo.integrate(measuredTauLeptons, met.p4().px(), met.p4().py(), met.cov());
    //double mTauTau = -1.; // CV: temporarily comment-out the following line, to make code compile with "old" and "new" version of ClassicSVfit
    double mTauTau = ( svFitAlgo.isValidSolution() ) ? static_cast<classic_svFit::HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass() : -1.;

//--- Declare the variables used as an input to the MVA/BDT in one place
//    so that there won't be any mismatches b/w the variables in the BDT Ntuple and
//    the variables used to evaluate the MVA/BDT scores.
//    Besides, we may want to use the said variables to fill sync Ntuple as well.
    const double lep_pt        = selLepton->pt();
    const double lep_conePt    = selLepton->cone_pt();
    const double lep_eta       = selLepton->absEta();
    const double lep_tth_mva   = selLepton->mvaRawTTH();
    const double mindr_lep_jet = std::min(10., comp_mindr_lep1_jet(*selLepton, selJets));
    const double mindr_tau_jet = std::min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets));
    const double avg_dr_jet    = comp_avg_dr_jet(selJets);;
    const double ptmiss        = met.pt();
    const double mT_lep        = comp_MT_met_lep1(*selLepton, met.pt(), met.phi());
    const double mT_tau        = comp_MT_met_hadTau1(*selHadTau, met.pt(), met.phi());
    const double htmiss        = mht_p4.pt();
    const double tau_mva       = selHadTau->raw_mva();
    const double tau_pt        = selHadTau->pt();
    const double tau_eta       = selHadTau->absEta();
    const double dr_lep_tau    = deltaR(selLepton->p4(), selHadTau->p4());
    const double costS         = comp_cosThetaS(selLepton->p4(), selHadTau->p4());
    const double mTauTauVis    = (selLepton->p4() + selHadTau->p4()).mass();
    const double Pzeta         = comp_pZeta(selLepton->p4(), selHadTau->p4(), met.p4().px(), met.p4().py());
    const double PzetaVis      = comp_pZetaVis(selLepton->p4(), selHadTau->p4());
    const double PzetaComb     = comp_pZetaComb(selLepton->p4(), selHadTau->p4(), met.p4().px(), met.p4().py());
    const double mbb           = ( selBJets_medium.size() >= 2 ) ? (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1.;
    const double mbb_loose     = ( selBJets_loose.size()  >= 2 ) ? (selBJets_loose[0]->p4()  + selBJets_loose[1]->p4()).mass()  : -1.;

    const std::map<std::string, double> mvaInputVariables_mva_XGB_1l_1tau_16_variables{
       {"mindr_lep_jet",    mindr_lep_jet},
       {"mindr_tau_jet",    mindr_tau_jet},
       {"avg_dr_jet",       avg_dr_jet},
       {"mT_lep",           mT_lep},
       {"mT_tau",           mT_tau},
       {"htmiss",           mht_p4.pt()},
       {"tau_pt",           selHadTau->pt()},
       {"tau_eta",          selHadTau->absEta()},
       {"dr_lep_tau",       dr_lep_tau},
       {"costS",            costS},
       {"mTauTauVis",       mTauTauVis},
       //{"PzetaComb",        comp_pZetaComb(selLepton->p4(), selHadTau->p4(), met.p4().px(), met.p4().py())},
       {"res-HTT_CSVsort4rd",  max_mvaOutput_HTT_CSVsort4rd},
       {"res-HTT_CSVsort4rd_2",  max_mvaOutput_HTT_CSVsort4rd_2},
       {"HadTop_pt_CSVsort4rd",  HadTop_pt_CSVsort4rd},
       {"nBJetMedium",       selBJets_medium.size()},
       //{"nBJetLoose",        selBJets_loose.size()},
       {"HadTop_pt_boosted", 1.0},
       {"mTauTau",		mTauTau},
       //{"nJet",		selJets.size()},
       {"lep_pt",		    lep_conePt},
       {"lep_conePt",		lep_conePt},
       {"charge_lep_tau",   selLepton->charge() + selHadTau->charge()},
       {"mbb_loose",	mbb_loose},
       {"res_HTT",    max_mvaOutput_HTT_CSVsort4rd},
       {"res_HTT_2",  max_mvaOutput_HTT_CSVsort4rd_2},
       {"met_LD",     met_LD},
       {"max_Lep_eta", std::max(selHadTau->absEta(), selLepton->absEta())},
       {"Lep_min_dr_jet", std::min(comp_mindr_lep1_jet(*selLepton, selJets), comp_mindr_hadTau1_jet(*selHadTau, selJets))},
    };
    const double mvaOutput_1l_1tau_DeepTauMedium_6 = mva_1l_1tau_Legacy_6(mvaInputVariables_mva_XGB_1l_1tau_16_variables);

    double min_Deta_leadfwdJet_jet = 0;
    if (selJetsForward.size() > 0 && selJets.size() > 0)
    {
      Particle::LorentzVector leadFwdJet = selJetsForward[0]-> p4();
      min_Deta_leadfwdJet_jet = min_Deta_fwdJet_jet(leadFwdJet, selJets);
    }

//--- retrieve gen-matching flags
    std::vector<const GenMatchEntry*> genMatches = genMatchInterface.getGenMatch(selLeptons, selHadTaus);

//--- fill histograms with events passing final selection
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
          EvtHistManager_1l_1tau* selHistManager_evt = selHistManager->evt_[kv.first];
          if ( selHistManager_evt )
          {
            selHistManager_evt->fillHistograms(
            selElectrons.size(),
            selMuons.size(),
            selHadTaus.size(),
            selJets.size(),
            selBJets_loose.size(),
            selBJets_medium.size(),
            mTauTauVis, mTauTau,
            mvaOutput_1l_1tau_DeepTauMedium_6,
            kv.second
          );
          }
        }
        if(isSignal)
        {
          std::string decayModeStr = get_key_hist(eventInfo, genWBosons, isMC_HH, isMC_VH);
          if(! decayModeStr.empty() && ! ((isMC_tH || isMC_H) && (decayModeStr == "hzg" || decayModeStr == "hmm" )))
          {
            for(const auto & kv: tH_weight_map)
            {
              EvtHistManager_1l_1tau* selHistManager_evt_decay = selHistManager->evt_in_decayModes_[kv.first][decayModeStr];
              if ( selHistManager_evt_decay )
              {
                selHistManager_evt_decay->fillHistograms(
                selElectrons.size(),
                selMuons.size(),
                selHadTaus.size(),
                selJets.size(),
                selBJets_loose.size(),
                selBJets_medium.size(),
                mTauTauVis, mTauTau,
                mvaOutput_1l_1tau_DeepTauMedium_6,
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
          selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
          selHistManager->weights_->fillHistograms("data_to_MC_correction", evtWeightRecorder.get_data_to_MC_correction(central_or_shift));
          selHistManager->weights_->fillHistograms("triggerWeight", evtWeightRecorder.get_sf_triggerEff(central_or_shift));
          selHistManager->weights_->fillHistograms("leptonEff", evtWeightRecorder.get_leptonSF());
          selHistManager->weights_->fillHistograms("hadTauEff", evtWeightRecorder.get_tauSF(central_or_shift));
          selHistManager->weights_->fillHistograms("fakeRate", evtWeightRecorder.get_FR(central_or_shift));
        }
        std::vector<std::string> categories = { "1l_1tau" };
        if(isCharge_SS)
        {
          categories.push_back("1l_1tau_SS");
        }
        else if(isCharge_OS)
        {
          categories.push_back("1l_1tau_OS");
          categories.push_back("1l_1tau_OS_wChargeFlipWeights");
        }

        if(selElectrons.size() >= 1)
        {
          categories.push_back("1e_1tau");
          if(isCharge_SS)
          {
            categories.push_back("1e_1tau_SS");
          }
          else if(isCharge_OS)
          {
            categories.push_back("1e_1tau_OS");
            categories.push_back("1e_1tau_OS_wChargeFlipWeights");
          }
        }
        else if(selMuons.size() >= 1)
        {
          categories.push_back("1mu_1tau");
          if(isCharge_SS)
          {
            categories.push_back("1mu_1tau_SS");
          }
          else if(isCharge_OS)
          {
            categories.push_back("1mu_1tau_OS");
            categories.push_back("1mu_1tau_OS_wChargeFlipWeights");
          }
        }
        for(const std::string & category: categories)
        {
          double evtWeight_category = evtWeight;
          double prob_chargeMisId_sum = 1.;
          if ( category.find("_wChargeFlipWeights") != std::string::npos ) {
            const double prob_chargeMisId_lepton = prob_chargeMisId(era, selLepton_type, selLepton->pt(), selLepton->eta());
            const double prob_chargeMisId_tau = 0.01; // CV: not implemented yet; take "guessed" value for now
            prob_chargeMisId_sum = prob_chargeMisId_lepton + prob_chargeMisId_tau;
          }
          evtWeight_category *= prob_chargeMisId_sum;
          if(selHistManager->evt_in_categories_.count(category))
          {
            selHistManager->evt_in_categories_[category]->fillHistograms(
              selElectrons.size(),
              selMuons.size(),
              selHadTaus.size(),
              selJets.size(),
              selBJets_loose.size(),
              selBJets_medium.size(),
              mTauTauVis, mTauTau,
              mvaOutput_1l_1tau_DeepTauMedium_6,
              evtWeight_category
            );
          }
          if(selHistManager->evt_in_categories_and_decayModes_.count(category))
          {
            if( isSignal ) {
              std::string decayModeStr = get_key_hist(eventInfo, genWBosons, isMC_HH, isMC_VH);
              if ( !decayModeStr.empty() && !((isMC_tH || isMC_H) && ( decayModeStr == "hzg" || decayModeStr == "hmm" )))
              {
                for(const auto & kv: tH_weight_map)
                {
                  EvtHistManager_1l_1tau* selHistManager_evt_category_decayModes = selHistManager->evt_in_categories_and_decayModes_[category][decayModeStr][kv.first];
                  if ( selHistManager_evt_category_decayModes )
                  {
                  selHistManager_evt_category_decayModes->fillHistograms(
                    selElectrons.size(),
                    selMuons.size(),
                    selHadTaus.size(),
                    selJets.size(),
                    selBJets_loose.size(),
                    selBJets_medium.size(),
                    mTauTauVis, mTauTau,
                    mvaOutput_1l_1tau_DeepTauMedium_6,
                    kv.second * prob_chargeMisId_sum
                  );
                }
                }
              }
            }
          }
          if ( selHistManager->evtYield_in_categories_.find(category) != selHistManager->evtYield_in_categories_.end() ) {
            selHistManager->evtYield_in_categories_[category]->fillHistograms(eventInfo, evtWeight_category);
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

    if ( bdt_filler ) {
      bdt_filler->operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
	  ("lep_pt",                                    lep_pt)
	  ("lep_conePt",                                lep_conePt)
	  ("lep_eta",                                   lep_eta)
	  ("lep_tth_mva",                               lep_tth_mva)
	  ("mindr_lep_jet",                             mindr_lep_jet)
	  ("mindr_tau_jet",                             mindr_tau_jet)
	  ("avg_dr_jet",                                avg_dr_jet)
	  ("ptmiss",                                    ptmiss)
    ("met_LD",                                    met_LD)
    ("massL",           massL(fakeableLeptons))
	  ("mT_lep",                                    mT_lep)
	  ("mT_tau",                                    mT_tau)
	  ("htmiss",                                    htmiss)
	  ("tau_mva",                                   tau_mva)
	  ("tau_pt",                                    tau_pt)
	  ("tau_eta",                                   tau_eta)
	  ("dr_lep_tau",                                dr_lep_tau)
	  ("costS",                                     costS)
	  ("mTauTauVis",                                mTauTauVis)
	  ("mTauTau",                                   mTauTau)
	  ("Pzeta",                                     Pzeta)
	  ("PzetaVis",                                  PzetaVis)
	  ("PzetaComb",                                 PzetaComb)
	  ("res-HTT_CSVsort4rd",                        max_mvaOutput_HTT_CSVsort4rd)
	  ("res-HTT_CSVsort4rd_2",                      max_mvaOutput_HTT_CSVsort4rd_2)
	  ("HadTop_pt_CSVsort4rd",                      HadTop_pt_CSVsort4rd)
          ("HadTop_pt_CSVsort4rd_2",                    HadTop_pt_CSVsort4rd_2)
	  ("genTopPt_CSVsort4rd",                       genTopPt_CSVsort4rd)
	  ("genTopPt_CSVsort4rd_2",                     genTopPt_CSVsort4rd_2)
	  ("HTT_semi_boosted_fromAK8",                  HTT_semi_boosted_fromAK8)
	  ("genTopPt_semi_boosted_fromAK8",             genTopPt_semi_boosted_fromAK8)
          ("HadTop_pt_semi_boosted_fromAK8",            HadTop_pt_semi_boosted_fromAK8)
	  ("minDR_AK8_lep",                             minDR_AK8_lep)
	  ("minDR_AK8subjets_lep",                      minDR_AK8subjets_lep)
          ("lumiScale",                                 evtWeightRecorder.get_lumiScale(central_or_shift_main))
	  ("genWeight",                                 eventInfo.genWeight)
          ("evtWeight",                                 evtWeightRecorder.get(central_or_shift_main))
          ("prob_fake_lepton",                    1.0)//      (selLepton->genLepton() != 0) ? 1. : evtWeightRecorder.get_jetToLepton_FR_lead(central_or_shift_main))
          ("prob_fake_hadTau",                    1.0)//      (selHadTau->genHadTau() != 0) ? 1. : evtWeightRecorder.get_jetToTau_FR_lead(central_or_shift_main))
	  ("nJet",                                      selJets.size())
	  ("nBJetLoose",                                selBJets_loose.size())
	  ("nBJetMedium",                               selBJets_medium.size())
	  ("charge_lep_tau",                            selLepton->charge() + selHadTau->charge())
	  ("N_jetAK8",                                  jet_ptrsAK8.size())
	  ("cleanedJets_fromAK8",                       cleanedJets_fromAK8.size())
	  ("hadtruth",                                  hadtruth)
	  ("hadtruth_2",                                hadtruth_2)
	  ("bWj1Wj2_isGenMatched_CSVsort4rd",           max_truth_HTT_CSVsort4rd)
	  ("bWj1Wj2_isGenMatched_CSVsort4rd_2",         max_truth_HTT_CSVsort4rd_2)
	  ("hadtruth_semi_boosted_fromAK8",             hadtruth_semi_boosted_fromAK8)
	  ("bWj1Wj2_isGenMatched_semi_boosted_fromAK8", bWj1Wj2_isGenMatched_semi_boosted_fromAK8)
	  ("resolved_and_semi_AK8",                     resolved_and_semi_AK8)
	  ("mbb_medium",					mbb)
	  ("mbb_loose",					mbb_loose)
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
    ("leadFwdJet_eta",      selJetsForward.size() > 0 ? selJetsForward[0] -> absEta() : -1000)
    ("leadFwdJet_pt",       selJetsForward.size() > 0 ? selJetsForward[0] -> pt() : -1000)
    ("leadFwdJet_phi",      selJetsForward.size() > 0 ? selJetsForward[0] -> phi() : -1000)
    ("leadFwdJet_E",        selJetsForward.size() > 0 ? selJetsForward[0] -> p4().energy() : -1000)
    ("nJetForward",         selJetsForward.size())
    ("min_Deta_leadfwdJet_jet", min_Deta_leadfwdJet_jet)

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
    .fill();
    }

    if(snmw)
    {
      const double max_dr_jet = comp_max_dr_jet(selJets);
      const int nLightJet     = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      for(auto & kv: snmw)
      {
	bool isGenMatched = false;
        if(isMC)
        {
          for (const GenMatchEntry * genMatch: genMatches)
          {
            if(snmw.isGenMatched(kv.first, genMatch->getName()))
            {
              isGenMatched = true;
            }
          }
        }

        SyncNtupleManager * snm = kv.second;

        snm->read(eventInfo);
        snm->read(selLeptons);
        snm->read(preselMuons,     fakeableMuons,     tightMuons);
        snm->read(preselElectrons, fakeableElectrons, tightElectrons);
        snm->read(fakeableHadTausFull);
        snm->read(selJets);

        snm->read({ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau });
        snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size(), nLightJet);

        snm->read(met.pt(),                               FloatVariableType::PFMET);
        snm->read(met.phi(),                              FloatVariableType::PFMETphi);
        snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
        snm->read(met_LD,                                 FloatVariableType::metLD);

        snm->read(mindr_lep_jet,                          FloatVariableType::mindr_lep1_jet);
        // mindr_lep2_jet not filled
        // mindr_lep3_jet not filled
        // mindr_lep4_jet not filled

        snm->read(mindr_tau_jet,                          FloatVariableType::mindr_tau1_jet);
        // mindr_tau2_jet not filled

        snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
        // avr_dr_lep_tau not filled
        snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
        // max_dr_lep_tau not filled
        // min_dr_tau_jet not filled
        // min_dr_lep_tau not filled
        // mindr_lep_jet not filled

        // dr_leps not filled
        // dr_taus not filled

        // dr_lep_tau_ss not filled
        snm->read(dr_lep_tau,                             FloatVariableType::dr_lep1_tau1);
        // dr_lep1_tau2 not filled
        // dr_lep2_tau1 not filled
        // dr_lep3_tau1 not filled
        // dr_lep2_tau2 not filled

        // max_lep_eta not filled

        snm->read(mT_lep,                                 FloatVariableType::mT_met_lep1);
        // mT_met_lep2 not filled
        // mT_met_lep3 not filled
        // mT_met_lep4 not filled

        snm->read(mTauTauVis,                             FloatVariableType::mTauTauVis);
        snm->read(mTauTau,                                FloatVariableType::mTauTau);
        // mvis_l2tau not filled

        snm->read(mbb,                                    FloatVariableType::mbb);
        snm->read(mbb_loose,                              FloatVariableType::mbb_loose);

        snm->read(costS,                                  FloatVariableType::cosThetaS_hadTau);
        snm->read(max_mvaOutput_HTT_CSVsort4rd,           FloatVariableType::HTT);
        snm->read(HadTop_pt_CSVsort4rd,                   FloatVariableType::HadTop_pt);
        // Hj_tagger not filled

        //snm->read(mvaOutput_plainKin_ttV,                 FloatVariableType::mvaOutput_plainKin_ttV);
        //snm->read(mvaOutput_plainKin_tt,                  FloatVariableType::mvaOutput_plainKin_tt);
        //snm->read(mvaOutput_plainKin_1B_VT,               FloatVariableType::mvaOutput_plainKin_1B_VT);
        //snm->read(mvaOutput_HTT_SUM_VT,                   FloatVariableType::mvaOutput_HTT_SUM_VT);
        //snm->read(mvaOutput_plainKin_SUM_VT,              FloatVariableType::mvaOutput_plainKin_SUM_VT);

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
        snm->read(evtWeightRecorder.get_leptonSF(),                            FloatVariableType::leptonSF_weight);
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
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeightRecorder.get(central_or_shift_main);
    std::string process_and_genMatch = process_string;
    process_and_genMatch += selLepton_genMatch.name_;
    process_and_genMatch += "&";
    process_and_genMatch += selHadTau_genMatch.name_;
    ++selectedEntries_byGenMatchType[process_and_genMatch];
    selectedEntries_weighted_byGenMatchType[process_and_genMatch] += evtWeightRecorder.get(central_or_shift_main);
    histogram_selectedEntries->Fill(0.);
  }

  if(snmw)
  {
    for(auto & kv: snmw)
    {
      kv.second->write();
    }
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
      for(const hadTauChargeFlipGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
      {
	std::string process_and_genMatch = process_string;
        process_and_genMatch += leptonGenMatch_definition.name_;
        process_and_genMatch += "&";
        process_and_genMatch += hadTauGenMatch_definition.name_;
        std::cout << " " << process_and_genMatch << " = " << selectedEntries_byGenMatchType[process_and_genMatch]
		  << " (weighted = " << selectedEntries_weighted_byGenMatchType[process_and_genMatch] << ")" << std::endl;
      }
    }
  }
  std::cout << std::endl;

  std::cout << "countFat " << countFatTop << " " << countFatTopEntries << " " << countFatTopTruth << std::endl;

//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete dataToMCcorrectionInterface;
  delete dataToMCcorrectionInterface_1l_1tau_trigger;

  delete leptonFakeRateInterface;
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

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1e1tau);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1mu1tau);

  delete inputTree;

  clock.Show("analyze_1l_1tau");

  return EXIT_SUCCESS;
}
