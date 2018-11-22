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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderHTTv2.h" // RecoJetReaderHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h" // JetHistManagerHTTv2
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
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_1L, getWeight_2L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_1tau_trigger.h" // Data_to_MC_CorrectionInterface_1l_1tau_trigger
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_boosted.h" // HadTopTagger_boosted
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_semi_boosted
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet tags
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h" // ClassicSVfit
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h" // classic_svFit::MeasuredTauLepton
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

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
  bool isSignal = ( process_string == "signal" ) ? true : false;

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
  double lep_mva_cut = cfg_analyze.getParameter<double>("lep_mva_cut"); // CV: used for tight lepton selection only

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonChargeFlipGenMatchEntry> leptonGenMatch_definitions = getLeptonChargeFlipGenMatch_definitions_1lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;
  std::string hadTauSelection_veto = cfg_analyze.getParameter<std::string>("hadTauSelection_veto");

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauChargeFlipGenMatchEntry> hadTauGenMatch_definitions = getHadTauChargeFlipGenMatch_definitions_1tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  enum { kOS, kSS, kDisabled };
  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS"       ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS"       ) chargeSumSelection = kSS;
  else if ( chargeSumSelection_string == "disabled" ) chargeSumSelection = kDisabled;
  else throw cms::Exception("analyze_1l_1tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

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
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");
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
  const int jetToTauFakeRate_option    = getJetToTauFR_option   (central_or_shift);
  const int lheScale_option            = getLHEscale_option     (central_or_shift);
  const int jetBtagSF_option           = getBTagWeight_option   (central_or_shift);
  const PUsys puSys_option             = getPUsys_option        (central_or_shift);

  const int met_option   = useNonNominal_jetmet ? kMEt_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option = useNonNominal_jetmet ? kJet_central_nonNominal : getJet_option(central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> jetToLeptonFakeRate_option = " << jetToLeptonFakeRate_option << "\n"
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
  //cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", false);
  //cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", true);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_1l_1tau", __LINE__) << "Invalid era = " << era;
  }
  Data_to_MC_CorrectionInterface_1l_1tau_trigger* dataToMCcorrectionInterface_1l_1tau_trigger = new Data_to_MC_CorrectionInterface_1l_1tau_trigger(cfg_dataToMCcorrectionInterface);

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
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2L || applyFakeRateWeights == kFR_1tau ) {
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
  std::string branchName_jetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_jetsHTTv2");
  std::string branchName_subjetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_subjetsHTTv2");
  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

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
  //std::cout << "selectBDT = " << selectBDT << std::endl;

  const double maxAbsEta_lepton = 2.1;
  double minPt_e = -1.;
  double minPt_mu = -1.;
  switch(era)
  {
    case kEra_2016: minPt_e = 25.; minPt_mu = 20.; break; // AN2016_372_v14:331
    case kEra_2017: minPt_e = 30.; minPt_mu = 25.; break;
    case kEra_2018: throw cmsException("analyze_1l_1tau", __LINE__) << "Implement me!";
    default:        throw cmsException("analyze_1l_1tau", __LINE__) << "Invalid era = " << era;
  }
  assert(minPt_e > 0. && minPt_mu > 0.);
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
  SyncNtupleManager * snm = nullptr;
  if(do_sync)
  {
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
    snm->initializeBranches();
    snm->initializeHLTBranches({ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau });
  }

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo, puSys_option);
  inputTree -> registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau });
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
  RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  tightElectronSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3, isDEBUG);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era, -1, isDEBUG);
  preselHadTauSelector.set_if_looser(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  // CV: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 1l+1tau category
  RecoHadTauCollectionSelectorTight vetoHadTauSelector(era, -1, isDEBUG);
  vetoHadTauSelector.set(hadTauSelection_veto);
  vetoHadTauSelector.set_min_antiElectron(hadTauSelection_veto_antiElectron);
  vetoHadTauSelector.set_min_antiMuon(hadTauSelection_veto_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleaner jetCleaner_large8(0.8, isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);

  RecoJetReaderHTTv2* jetReaderHTTv2 = new RecoJetReaderHTTv2(era, branchName_jetsHTTv2, branchName_subjetsHTTv2);
  inputTree -> registerReader(jetReaderHTTv2);
  RecoJetCollectionSelectorHTTv2 jetSelectorHTTv2(era);
  RecoJetCollectionCleanerHTTv2 jetCleanerHTTv2(1.5, isDEBUG); //to clean against leptons and hadronic taus
  RecoJetCollectionCleanerHTTv2SubJets jetCleanerHTTv2SubJets(0.4, isDEBUG); //to clean against leptons and hadronic taus

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);
  RecoJetCollectionCleanerAK8 jetCleanerAK8(0.8, isDEBUG); //to clean against leptons and hadronic taus
  RecoJetCollectionCleanerAK8SubJets jetCleanerAK8SubJets(0.4, isDEBUG); //to clean against leptons and hadronic taus

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
    if ( ! readGenObjects ) {
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
  HadTopTagger* hadTopTagger = new HadTopTagger();
  HadTopTagger_boosted* hadTopTagger_boosted = new HadTopTagger_boosted();
  HadTopTagger_semi_boosted_AK8* hadTopTagger_semi_boosted_fromAK8 = new HadTopTagger_semi_boosted_AK8();

//--- initialize eventlevel BDTs
/*
  std::string mvaFileName_plainKin_ttV ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/1l_1tau_XGB_plainKin_evtLevelTTV_TTH_13Var.xml";
  std::vector<std::string> mvaInputVariables_plainKin_ttVSort={
    "avg_dr_jet", "dr_taus", "ptmiss", "lep_conePt", "mT_lep",
    "mTauTauVis", "mindr_lep_jet", "mindr_tau1_jet",
    "dr_lep_tau_ss", "dr_lep_tau_sublead", "costS_tau", "tau1_pt", "tau2_pt"
  };
  TMVAInterface mva_plainKin_ttV(mvaFileName_plainKin_ttV, mvaInputVariables_plainKin_ttVSort);
  mva_plainKin_ttV.enableBDTTransform();

  std::string mvaFileName_plainKin_tt ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/1l_1tau_XGB_plainKin_evtLevelTT_TTH_13Var.xml";
  std::vector<std::string> mvaInputVariables_plainKin_ttSort={
    "avg_dr_jet", "dr_taus", "ptmiss", "mT_lep", "nJet",
    "mTauTauVis", "mindr_lep_jet", "mindr_tau1_jet", "mindr_tau2_jet",
    "dr_lep_tau_lead", "nBJetLoose", "tau1_pt", "tau2_pt"
  };
  TMVAInterface mva_plainKin_tt(mvaFileName_plainKin_tt, mvaInputVariables_plainKin_ttSort);
  mva_plainKin_tt.enableBDTTransform();

  // Joint 1B
  std::vector<std::string> mvaInputVariables_1BSort = {"BDTtt", "BDTttV"};
  std::string mvaFileName_plainKin_1B_VT ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/1l_1tau_XGB_JointBDT_plainKin_1B_VT.xml";
  TMVAInterface mva_2lss_plainKin_1B_VT(mvaFileName_plainKin_1B_VT, mvaInputVariables_1BSort);
  mva_2lss_plainKin_1B_VT.enableBDTTransform();

  // SUM-BDT
  std::string mvaFileName_HTT_sum_VT ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/1l_1tau_XGB_HTT_evtLevelSUM_TTH_VT_17Var.xml";
  std::vector<std::string> mvaInputVariables_HTT_sumSort={
    "avg_dr_jet", "dr_taus", "ptmiss", "lep_conePt", "mT_lep", "mTauTauVis", "mindr_lep_jet",
    "mindr_tau1_jet", "mindr_tau2_jet", "dr_lep_tau_ss", "dr_lep_tau_lead",
    "costS_tau", "nBJetLoose", "tau1_pt",
    "tau2_pt", "HTT", "HadTop_pt"
  };
  TMVAInterface mva_HTT_sum_VT(mvaFileName_HTT_sum_VT, mvaInputVariables_HTT_sumSort);
  mva_HTT_sum_VT.enableBDTTransform();

  // SUM-BDT
  std::string mvaFileName_plainKin_sum_VT ="tthAnalysis/HiggsToTauTau/data/evtLevel_2018March/1l_1tau_XGB_plainKin_evtLevelSUM_TTH_16Var.xml";
  std::vector<std::string> mvaInputVariables_plainKin_sumSort={
    "avg_dr_jet", "dr_taus", "ptmiss", "lep_conePt", "mT_lep", "mTauTauVis", "mindr_lep_jet",
    "mindr_tau1_jet", "mindr_tau2_jet", "nJet", "dr_lep_tau_ss", "dr_lep_tau_lead",
    "costS_tau", "nBJetLoose", "tau1_pt", "tau2_pt"
  };
  TMVAInterface mva_plainKin_sum_VT(mvaFileName_plainKin_sum_VT, mvaInputVariables_plainKin_sumSort);
  mva_plainKin_sum_VT.enableBDTTransform();
 */
//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;

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
    EvtHistManager_1l_1tau* evt_;
    EvtYieldHistManager* evtYield_;
  };
  typedef std::map<int, preselHistManagerType*> int_to_preselHistManagerMap;
  std::map<int, int_to_preselHistManagerMap> preselHistManagers;
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    std::map<std::string, ElectronHistManager*> electrons_in_categories_;
    MuonHistManager* muons_;
    std::map<std::string, MuonHistManager*> muons_in_categories_;
    HadTauHistManager* hadTaus_;
    std::map<std::string, HadTauHistManager*> hadTaus_in_categories_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    std::map<std::string, MEtHistManager*> met_in_categories_;
    MEtFilterHistManager* metFilters_;
    //MVAInputVarHistManager* mvaInputVariables_HTT_sum_;
    EvtHistManager_1l_1tau* evt_;
    std::map<std::string, EvtHistManager_1l_1tau*> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_1l_1tau*> evt_in_categories_;
    std::map<std::string, std::map<std::string, EvtHistManager_1l_1tau*>> evt_in_categories_and_decayModes_;
    EvtYieldHistManager* evtYield_;
    std::map<std::string, EvtYieldHistManager*> evtYield_in_categories_;
    WeightHistManager* weights_;
  };
  typedef std::map<int, selHistManagerType*> int_to_selHistManagerMap;
  std::map<int, int_to_selHistManagerMap> selHistManagers;
  for ( std::vector<leptonChargeFlipGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauChargeFlipGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching                            ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching                            ) process_and_genMatch += hadTauGenMatch_definition->name_;
      int idxLepton = leptonGenMatch_definition->idx_;
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
      preselHistManager->evt_ = new EvtHistManager_1l_1tau(makeHistManager_cfg(process_and_genMatch,
        Form("%s/presel/evt", histogramDir.data()), central_or_shift));
      preselHistManager->evt_->bookHistograms(fs);
      edm::ParameterSet cfg_EvtYieldHistManager_presel = makeHistManager_cfg(process_and_genMatch,
        Form("%s/presel/evtYield", histogramDir.data()), central_or_shift);
      cfg_EvtYieldHistManager_presel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
      cfg_EvtYieldHistManager_presel.addParameter<bool>("isMC", isMC);
      preselHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_presel);
      preselHistManager->evtYield_->bookHistograms(fs);
      preselHistManagers[idxLepton][idxHadTau] = preselHistManager;

      selHistManagerType* selHistManager = new selHistManagerType();
      selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
      selHistManager->electrons_->bookHistograms(fs);
      vstring categories_e = {
        "1e_1tau", "1e_1tau_SS", "1e_1tau_OS", "1e_1tau_OS_wChargeFlipWeights"
      };
      std::map<std::string, ElectronHistManager*> selElectronHistManager_category; // key = category
      for ( vstring::const_iterator category = categories_e.begin();
            category != categories_e.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
        selHistManager->electrons_in_categories_[*category] = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/electrons", histogramDir_category.Data()), central_or_shift));
        selHistManager->electrons_in_categories_[*category]->bookHistograms(fs);
      }
      selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/muons", histogramDir.data()), central_or_shift));
      selHistManager->muons_->bookHistograms(fs);
      vstring categories_mu = {
        "1mu_1tau", "1mu_1tau_SS", "1mu_1tau_OS", "1mu_1tau_OS_wChargeFlipWeights"
      };
      for ( vstring::const_iterator category = categories_mu.begin();
            category != categories_mu.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
        selHistManager->muons_in_categories_[*category] = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/muons", histogramDir_category.Data()), central_or_shift));
        selHistManager->muons_in_categories_[*category]->bookHistograms(fs);
      }
      selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
      selHistManager->hadTaus_->bookHistograms(fs);
      vstring categories_tau = {
	// CV: must *not* inclusive category, as histograms of same name already booked for selHistManager->hadTaus_ !!
	            "1l_1tau_SS",  "1l_1tau_OS",  "1l_1tau_OS_wChargeFlipWeights",
	"1e_1tau",  "1e_1tau_SS",  "1e_1tau_OS",  "1e_1tau_OS_wChargeFlipWeights",
	"1mu_1tau", "1mu_1tau_SS", "1mu_1tau_OS", "1mu_1tau_OS_wChargeFlipWeights"
      };
      for ( vstring::const_iterator category = categories_tau.begin();
            category != categories_tau.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
        selHistManager->hadTaus_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/hadTaus", histogramDir_category.Data()), central_or_shift));
        selHistManager->hadTaus_in_categories_[*category]->bookHistograms(fs);
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
      vstring categories_evt = {
	// CV: must *not* inclusive category, as histograms of same name already booked for selHistManager->evt_ !!
	            "1l_1tau_SS",  "1l_1tau_OS",  "1l_1tau_OS_wChargeFlipWeights",
	"1e_1tau",  "1e_1tau_SS",  "1e_1tau_OS",  "1e_1tau_OS_wChargeFlipWeights",
	"1mu_1tau", "1mu_1tau_SS", "1mu_1tau_OS", "1mu_1tau_OS_wChargeFlipWeights"
      };
      for ( vstring::const_iterator category = categories_evt.begin();
            category != categories_evt.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
	selHistManager->met_in_categories_[*category] = new MEtHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/met", histogramDir_category.Data()), central_or_shift));
        selHistManager->met_in_categories_[*category]->bookHistograms(fs);
      }
      selHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/metFilters", histogramDir.data()), central_or_shift));
      selHistManager->metFilters_->bookHistograms(fs);
      //selHistManager->mvaInputVariables_HTT_sum_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
      //  Form("%s/sel/mvaInputs_HTT_sum", histogramDir.data()), central_or_shift));
      //selHistManager->mvaInputVariables_HTT_sum_->bookHistograms(fs, mvaInputVariables_HTT_sumSort);
      selHistManager->evt_ = new EvtHistManager_1l_1tau(makeHistManager_cfg(process_and_genMatch,
       Form("%s/sel/evt", histogramDir.data()), central_or_shift));
      selHistManager->evt_->bookHistograms(fs);
      const vstring decayModes_evt = eventInfo.getDecayModes();
      if ( isSignal ) {
        for ( const std::string & decayMode_evt: decayModes_evt ) {
          std::string decayMode_and_genMatch = decayMode_evt;
          if ( apply_leptonGenMatching                            ) decayMode_and_genMatch += leptonGenMatch_definition->name_;
          if ( apply_leptonGenMatching && apply_hadTauGenMatching ) decayMode_and_genMatch += "&";
          if ( apply_hadTauGenMatching                            ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;
          selHistManager -> evt_in_decayModes_[decayMode_evt] = new EvtHistManager_1l_1tau(makeHistManager_cfg(decayMode_and_genMatch,
            Form("%s/sel/evt", histogramDir.data()), central_or_shift));
          selHistManager->evt_in_decayModes_[decayMode_evt]->bookHistograms(fs);
        }
      }
      for ( vstring::const_iterator category = categories_evt.begin();
            category != categories_evt.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
        selHistManager->evt_in_categories_[*category] = new EvtHistManager_1l_1tau(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/evt", histogramDir_category.Data()), central_or_shift));
        selHistManager->evt_in_categories_[*category]->bookHistograms(fs);
	if ( isSignal ) {
          for ( const std::string & decayMode_evt: decayModes_evt ) {
	    std::string decayMode_and_genMatch = decayMode_evt;
	    if ( apply_leptonGenMatching                            ) decayMode_and_genMatch += leptonGenMatch_definition->name_;
	    if ( apply_leptonGenMatching && apply_hadTauGenMatching ) decayMode_and_genMatch += "&";
	    if ( apply_hadTauGenMatching                            ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;
	    selHistManager->evt_in_categories_and_decayModes_[*category][decayMode_evt] = new EvtHistManager_1l_1tau(makeHistManager_cfg(decayMode_and_genMatch,
              Form("%s/sel/evt", histogramDir_category.Data()), central_or_shift));
            selHistManager->evt_in_categories_and_decayModes_[*category][decayMode_evt]->bookHistograms(fs);
	  }
	}
      }
      edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/evtYield", histogramDir.data()), central_or_shift);
      cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
      cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
      selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
      selHistManager->evtYield_->bookHistograms(fs);
      for ( vstring::const_iterator category = categories_evt.begin();
            category != categories_evt.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("1l_1tau", category->data());
	edm::ParameterSet cfg_EvtYieldHistManager_category = makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/evtYield", histogramDir_category.Data()), central_or_shift);
	cfg_EvtYieldHistManager_category.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
	cfg_EvtYieldHistManager_category.addParameter<bool>("isMC", isMC);
	selHistManager->evtYield_in_categories_[*category] = new EvtYieldHistManager(cfg_EvtYieldHistManager_category);
	selHistManager->evtYield_in_categories_[*category]->bookHistograms(fs);
      }
      selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/weights", histogramDir.data()), central_or_shift));
      selHistManager->weights_->bookHistograms(fs,
        { "genWeight", "pileupWeight", "data_to_MC_correction", "triggerWeight", "leptonEff", "hadTauEff", "fakeRate" });
      selHistManagers[idxLepton][idxHadTau] = selHistManager;
    }
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

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), central_or_shift)
    );
    bdt_filler->register_variable<float_type>(
      "lep_pt", "lep_conePt", "lep_eta", "lep_tth_mva", "mindr_lep_jet", "mindr_tau_jet", 
      "avg_dr_jet", "ptmiss", "mT_lep", "mT_tau", "htmiss", "tau_mva", "tau_pt",
      "tau_eta", "dr_lep_tau",
      "costS", "mTauTauVis", "mTauTau", "Pzeta", "PzetaVis", "PzetaComb", 
      "res-HTT_CSVsort4rd", "res-HTT_CSVsort4rd_2",
      "HadTop_pt_CSVsort4rd", "HadTop_pt_CSVsort4rd_2",
      "genTopPt_CSVsort4rd", "genTopPt_CSVsort4rd_2",
      "HTT_boosted", "genTopPt_boosted", "HadTop_pt_boosted",
      "HTT_semi_boosted_fromAK8", "genTopPt_semi_boosted_fromAK8", "HadTop_pt_semi_boosted_fromAK8",
      "minDR_HTTv2_lep", "minDR_AK8_lep",
      "minDR_HTTv2subjets_lep", "minDR_AK8subjets_lep",
      "lumiScale", "genWeight", "evtWeight", 
      "prob_fake_lepton", "prob_fake_hadTau"
    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium",
      "charge_lep_tau",
      "nHTTv2", "N_jetAK8", "cleanedJets_fromAK8",
      "hadtruth", "hadtruth_2",
      "bWj1Wj2_isGenMatched_CSVsort4rd", "bWj1Wj2_isGenMatched_CSVsort4rd_2",
      "hadtruth_boosted", "hadtruth_semi_boosted_fromAK8",
      "bWj1Wj2_isGenMatched_boosted", "bWj1Wj2_isGenMatched_semi_boosted_fromAK8",
      "resolved_and_semi_AK8", "boosted_and_semi_AK8", "resolved_and_boosted"      
    );
    bdt_filler->bookTree(fs);
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
    ">= 1 presel lepton",
    "presel lepton trigger match",
    ">= 1 presel tau",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet (1)",
    ">= 1 sel lepton",
    "<= 1 tight leptons",
    "fakeable lepton trigger match",
    ">= 1 sel tau",
    "<= 1 veto taus",
    "HLT filter matching",
    ">= 4 jets",
    ">= 2 loose b-jets || 1 medium b-jet (2)",
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

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection", lumiScale);
    cutFlowHistManager->fillHistograms("run:ls:event selection", lumiScale);

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if ( inputTree->isOpen() ) {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenHadTau> genHadTaus;
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
      bool isTriggered_SingleElectron = isTriggered_1e || isTriggered_1e1tau;
      bool isTriggered_SingleMuon = isTriggered_1mu || isTriggered_1mu1tau;
      //bool isTriggered_Tau = isTriggered_1e1tau || isTriggered_1mu1tau;

      bool selTrigger_SingleElectron = selTrigger_1e || selTrigger_1e1tau;
      //bool selTrigger_SingleMuon = selTrigger_1mu || selTrigger_1mu1tau;
      bool selTrigger_Tau = selTrigger_1e1tau || selTrigger_1mu1tau;

      if ( selTrigger_SingleElectron && isTriggered_SingleMuon ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
                    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon << ")" << std::endl;
        }
        continue;
      }
      
      if ( era == kEra_2016 ) {
	// CV: only needed for 2016 data-taking period,
	//     as mu+tau (e+tau) cross trigger is stored in the same primary dataset as the single muon (single electron) trigger
	//     in the 2017 (and presumably also in the) data-taking period
	if ( selTrigger_Tau && (isTriggered_SingleMuon || isTriggered_SingleElectron) ) {
	  if ( run_lumi_eventSelector ) {
	    std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
	    std::cout << " (selTrigger_Tau = " << selTrigger_Tau
		      << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon
		      << ", isTriggered_SingleElectron = " << isTriggered_SingleElectron << ")" << std::endl;
	  }
	  continue;
	}
      }
    }
    cutFlowTable.update("trigger", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms("trigger", evtWeight_inclusive);

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

    std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 1);
    std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 1);
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
    std::vector<const RecoHadTau*> preselHadTausFull = preselHadTauSelector(cleanedHadTaus, isHigherPt);
    std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(preselHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    std::vector<const RecoHadTau*> preselHadTaus = pickFirstNobjects(preselHadTausFull, 1);
    std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 1);
    std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, preselHadTaus, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselHadTaus",   preselHadTaus);
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
    std::vector<const RecoHadTau*> vetoHadTaus = vetoHadTauSelector(cleanedHadTaus, isHigherPt);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableLeptons, fakeableHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("uncleanedJets", jet_ptrs);
      printCollection("selJets",       selJets);
    }

//--- build collections of jets reconstructed by hep-top-tagger (HTTv2) algorithm
    std::vector<RecoJetHTTv2> jetsHTTv2 = jetReaderHTTv2->read();
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2raw = convert_to_ptrs(jetsHTTv2);
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2rawSel = jetSelectorHTTv2(jet_ptrsHTTv2raw, isHigherPt);
    std::vector<const RecoJetHTTv2*> sel_HTTv2 = jetCleanerHTTv2SubJets(jet_ptrsHTTv2rawSel, fakeableMuons, fakeableElectrons, selHadTaus);

//--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    std::vector<const RecoJetAK8*> jet_ptrsAK8raw1 = convert_to_ptrs(jetsAK8);
    std::vector<const RecoJetAK8*> jet_ptrsAK8raw = jetSelectorAK8(jet_ptrsAK8raw1, isHigherPt);;
    std::vector<const RecoJetAK8*> jet_ptrsAK8 = jetCleanerAK8SubJets(jet_ptrsAK8raw, fakeableMuons, fakeableElectrons, selHadTaus);
    std::vector<const RecoJet*> cleanedJets_fromAK8;
    cleanedJets_fromAK8 = jetCleaner_large8(selJets, jet_ptrsAK8);

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

      hadTauGenMatcher.addGenLeptonMatch(preselHadTausFull, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTausFull, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTausFull, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    // require exactly one lepton passing loose preselection criteria
    if ( !(preselLeptonsFull.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 presel lepton", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms(">= 1 presel lepton", evtWeight_inclusive);
    const RecoLepton* preselLepton = preselLeptonsFull[0];
    const leptonChargeFlipGenMatchEntry& preselLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, preselLepton);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined1);
    //std::cout << "Selection applied" << std::endl;
    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 1 && (selTrigger_1e  || selTrigger_1e1tau )) ||
           (preselMuons.size()     >= 1 && (selTrigger_1mu || selTrigger_1mu1tau))) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection for given preselLepton multiplicity." << std::endl;
        std::cout << " (#preselElectrons = " << preselElectrons.size()
                  << ", #preselMuons = " << preselMuons.size()
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau
                  << ", selTrigger_1e = " << selTrigger_1e
                  << ", selTrigger_1e1tau = " << selTrigger_1e1tau << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("presel lepton trigger match", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms("presel lepton trigger match", evtWeight_inclusive);

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    if ( !(preselHadTausFull.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 presel tau", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms(">= 1 presel tau", evtWeight_inclusive);
    const RecoHadTau* preselHadTau = preselHadTausFull[0];
    const hadTauChargeFlipGenMatchEntry& preselHadTau_genMatch = getHadTauChargeFlipGenMatch(hadTauGenMatch_definitions, preselHadTau);
    int idxPreselHadTau_genMatch = preselHadTau_genMatch.idx_;
    assert(idxPreselHadTau_genMatch != kGen_HadTauUndefined1);

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms(">= 2 jets", evtWeight_inclusive);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", evtWeight_inclusive);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, fakeableHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselLepton_genMatch][idxPreselHadTau_genMatch];
    assert(preselHistManager != 0);
    preselHistManager->electrons_->fillHistograms(preselElectrons, 1.);
    preselHistManager->muons_->fillHistograms(preselMuons, 1.);
    preselHistManager->hadTaus_->fillHistograms(preselHadTausFull, 1.);
    preselHistManager->jets_->fillHistograms(selJets, 1.);
    preselHistManager->BJets_loose_->fillHistograms(selBJets_loose, 1.);
    preselHistManager->BJets_medium_->fillHistograms(selBJets_medium, 1.);
    preselHistManager->met_->fillHistograms(met, mht_p4, met_LD, 1.);
    preselHistManager->metFilters_->fillHistograms(metFilters, 1.);
    preselHistManager->evt_->fillHistograms(
      preselElectrons.size(),
      preselMuons.size(),
      selHadTaus.size(),
      selJets.size(),
      selBJets_loose.size(),
      selBJets_medium.size(),
      //-1., -1., -1., -1., -1.,
      (preselLepton->p4() + preselHadTau->p4()).mass(), -1., 
      -1., -1., -1., -1., -1.,
      -1., -1.,
      evtWeight_inclusive
    );
    preselHistManager->evtYield_->fillHistograms(eventInfo, evtWeight_inclusive);

//--- apply final event selection
    if ( !(selLeptons.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 sel lepton", evtWeight_inclusive);
    cutFlowHistManager->fillHistograms(">= 1 sel lepton", evtWeight_inclusive);
    const RecoLepton* selLepton = selLeptons[0];
    int selLepton_type = getLeptonType(selLepton->pdgId());
    const leptonChargeFlipGenMatchEntry& selLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, selLepton);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined1);

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//  (using the method "Event reweighting using scale factors calculated with a tag and probe method",
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
    // require exactly one lepton passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptonsFull.size() <= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection.\n";
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 1 tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("<= 1 tight leptons", evtWeight);

    // require that trigger paths match event category (with event category based on fakeableLeptons)
    if ( !((fakeableElectrons.size() >= 1 && (selTrigger_1e  || selTrigger_1e1tau )) ||
           (fakeableMuons.size()     >= 1 && (selTrigger_1mu || selTrigger_1mu1tau))) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection for given fakeableLepton multiplicity." << std::endl;
        std::cout << " (#fakeableElectrons = " << fakeableElectrons.size()
                  << ", #fakeableMuons = " << fakeableMuons.size()
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau
                  << ", selTrigger_1e = " << selTrigger_1e
                  << ", selTrigger_1e1tau = " << selTrigger_1e1tau << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("fakeable lepton trigger match", evtWeight);
    cutFlowHistManager->fillHistograms("fakeable lepton trigger match", evtWeight);

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
    cutFlowTable.update(">= 1 sel tau", evtWeight);
    cutFlowHistManager->fillHistograms(">= 1 sel tau", evtWeight);
    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauChargeFlipGenMatchEntry& selHadTau_genMatch = getHadTauChargeFlipGenMatch(hadTauGenMatch_definitions, selHadTau);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined1);

    // veto events containing more than one tau passing the Medium WP, to avoid overlap with the 1l+1tau category
    // we want to keep all cuts consistent in SR and fake CR, to obtain a consistent estimate of the fake background
    if ( !(vetoHadTaus.size() <= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS vetoHadTaus selection." << std::endl;
        printCollection("vetoHadTaus", vetoHadTaus);
      }
      continue;
    }
    cutFlowTable.update("<= 1 veto taus", evtWeight);
    cutFlowHistManager->fillHistograms("<= 1 veto taus", evtWeight);

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
    cutFlowTable.update("HLT filter matching", evtWeight);
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeight);

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    double weight_leptonEff = 1.;
    double weight_hadTauEff = 1.;
    double tauSF_weight = 1.;
    if ( isMC ) {
      int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);

      dataToMCcorrectionInterface->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());

      dataToMCcorrectionInterface_1l_1tau_trigger->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      if(era == kEra_2016)
      {
        dataToMCcorrectionInterface_1l_1tau_trigger->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta(), selHadTau->decayMode());
      }
      else if(era == kEra_2017)
      {
        dataToMCcorrectionInterface_1l_1tau_trigger->setHadTaus(selHadTau->pt(), selHadTau->eta(), selHadTau->phi());
      }
      else if(era == kEra_2018)
      {
        throw cmsException("analyze_1l_1tau", __LINE__) << "Implement me!";
      }
      else
      {
        throw cmsException("analyze_1l_1tau", __LINE__) << "Invalid era = " << era;
      }
      dataToMCcorrectionInterface_1l_1tau_trigger->setTriggerBits(isTriggered_1e, isTriggered_1e1tau, isTriggered_1mu, isTriggered_1mu1tau);

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface_1l_1tau_trigger->getSF_triggerEff();
      if ( isDEBUG ) {
        std::cout << "sf_triggerEff = " << sf_triggerEff << std::endl;
      }
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

      double sf_leptonEff = 1.;
//--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria
      sf_leptonEff *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
       if ( electronSelection == kFakeable && muonSelection == kFakeable ) {
        sf_leptonEff *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( electronSelection >= kFakeable && muonSelection >= kFakeable ) {
        // apply loose-to-tight lepton ID SFs if either of the following is true:
        // 1) both electron and muon selections are tight -> corresponds to SR
        // 2) electron selection is relaxed to fakeable and muon selection is kept as tight -> corresponds to MC closure w/ relaxed e selection
        // 3) muon selection is relaxed to fakeable and electron selection is kept as tight -> corresponds to MC closure w/ relaxed mu selection
        // we allow (2) and (3) so that the MC closure regions would more compatible w/ the SR (1) in comparison
        sf_leptonEff *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();
      }
      if ( isDEBUG ) {
        std::cout << "sf_leptonEff = " << sf_leptonEff << std::endl;
      }
      weight_leptonEff *= sf_leptonEff;
      weight_data_to_MC_correction *= sf_leptonEff;

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

    double weight_fakeRate = 1.;
    double prob_fake_lepton = 1.;
    double prob_fake_hadTau = 1.;
    if ( !selectBDT ) {
      if ( applyFakeRateWeights == kFR_2L ) {
        if      ( std::abs(selLepton->pdgId()) == 11 ) prob_fake_lepton = leptonFakeRateInterface->getWeight_e(selLepton->cone_pt(), selLepton->absEta());
        else if ( std::abs(selLepton->pdgId()) == 13 ) prob_fake_lepton = leptonFakeRateInterface->getWeight_mu(selLepton->cone_pt(), selLepton->absEta());
        else assert(0);

        bool passesTight_lepton = isMatched(*selLepton, tightElectrons) || isMatched(*selLepton, tightMuons);
        prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTausFull);

        weight_fakeRate = getWeight_2L(
          prob_fake_lepton, passesTight_lepton,
          prob_fake_hadTau, passesTight_hadTau
        );

        if ( isDEBUG ) {
          std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
        }
        evtWeight *= weight_fakeRate;
      } else if ( applyFakeRateWeights == kFR_1tau) {
        prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTausFull);

        weight_fakeRate = getWeight_1L(
          prob_fake_hadTau, passesTight_hadTau
        );

        if ( isDEBUG ) {
          std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
        }
        evtWeight *= weight_fakeRate;
      }

      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight ) {
        double weight_data_to_MC_correction_hadTau = 1.;
        if ( !(selHadTau->genHadTau() || selHadTau->genLepton()) ) {
          weight_data_to_MC_correction_hadTau = jetToTauFakeRateInterface->getSF_lead(selHadTau->pt(), selHadTau->absEta());
        }

        if ( isDEBUG ) {
          std::cout << "weight_data_to_MC_correction_hadTau = " << weight_data_to_MC_correction_hadTau << std::endl;
        }
        tauSF_weight *= weight_data_to_MC_correction_hadTau;
        evtWeight *= weight_data_to_MC_correction_hadTau;
      }
    }
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
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
    cutFlowTable.update(">= 4 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) )
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS to have at least 2 loose or 1 medium jet(s)\n";
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);

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
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    const double minPt = selLepton->is_electron() ? minPt_e : minPt_mu;
    if ( !(selLepton->cone_pt() > minPt) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS minPt = " << minPt << " < cut on the selected lepton\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton pT > %.0f(e)/%.0f(mu) GeV", minPt_e, minPt_mu), evtWeight);
    cutFlowHistManager->fillHistograms(Form("sel lepton pT > %.0f(e)/%.0f(mu) GeV", minPt_e, minPt_mu), evtWeight);

    if ( !(selLepton->absEta() < maxAbsEta_lepton) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS maxAbsEta = " << maxAbsEta_lepton << " > cut on the selected lepton\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton abs(eta) < %.1f", maxAbsEta_lepton), evtWeight);
    cutFlowHistManager->fillHistograms(Form("sel lepton abs(eta) < %.1f", maxAbsEta_lepton), evtWeight);

    if ( !(selHadTau->pt() > minPt_hadTau) )
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event " << eventInfo.str() << " FAILS minPt = " << minPt_hadTau << " < cut on the selected tau\n";
      }
      continue;
    }
    cutFlowTable.update(Form("sel hadTau pT > %.0f GeV", minPt_hadTau), evtWeight);
    cutFlowHistManager->fillHistograms(Form("sel hadTau pT > %.0f GeV", minPt_hadTau), evtWeight);

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
    cutFlowTable.update(Form("lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("lepton+tau OS/SS charge", evtWeight);

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
    cutFlowTable.update("signal region veto", evtWeight);
    cutFlowHistManager->fillHistograms("signal region veto", evtWeight);

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
    //std::cout<< max_mvaOutput_HTT_CSVsort4rd_2 << " " << max_mvaOutput_HTT_CSVsort4rd << std::endl;

    // compute overlaps semi-boosted resolved / semi-boosted and boosted / ...
    bool resolved_and_semi_AK8 = false;
    bool boosted_and_semi_AK8 = false;
    bool resolved_and_boosted = false;

    //--- boosted hTT
    double HTT_boosted = 0.;
    bool bWj1Wj2_isGenMatched_boosted = false;
    double genTopPt_boosted = 0.;
    double HadTop_pt_boosted = 0.;
    bool hadtruth_boosted = false;
    double minDR_HTTv2_lep = -1.;
    double minDR_HTTv2subjets_lep = -1.;

    for ( std::vector<const RecoJetHTTv2*>::const_iterator jetIter = sel_HTTv2.begin();
    jetIter != sel_HTTv2.end(); ++jetIter ) {
    bool isGenMatched = false;
    double genTopPt_teste = 0.;
    const std::map<int, double> bdtResult = (*hadTopTagger_boosted)(**jetIter, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti);
    if (isGenMatched) {hadtruth_boosted = true;}

    if ( bdtResult.at(kXGB_boosted_no_kinFit) > HTT_boosted ) {
      bWj1Wj2_isGenMatched_boosted = isGenMatched;
      HTT_boosted = bdtResult.at(kXGB_boosted_no_kinFit);
      HadTop_pt_boosted = (*jetIter)->pt();
      genTopPt_boosted = genTopPt_teste;

      minDR_HTTv2_lep = std::min(
        deltaR(selLepton->p4(), (*jetIter)->p4()),
        deltaR(selHadTau->p4(), (*jetIter)->p4())
      );

      minDR_HTTv2subjets_lep =
      std::min(
      std::min(
      std::min(
        deltaR(selLepton->p4(), (*jetIter)->subJet1()->p4()),
        deltaR(selHadTau->p4(), (*jetIter)->subJet1()->p4())
      ),
      std::min(
        deltaR(selLepton->p4(), (*jetIter)->subJet2()->p4()),
        deltaR(selHadTau->p4(), (*jetIter)->subJet2()->p4())
      )
     ),
     std::min(
       deltaR(selLepton->p4(), (*jetIter)->subJet3()->p4()),
       deltaR(selHadTau->p4(), (*jetIter)->subJet3()->p4())
     )
     );

    }
    }
    if (genTopPt_CSVsort4rd == genTopPt_boosted) resolved_and_boosted = true;

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
    if (genTopPt_semi_boosted_fromAK8 == genTopPt_boosted)  boosted_and_semi_AK8 = true;

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
    const double tau_mva       = selHadTau->raw_mva_dR03();
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

/*
//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Matthias for 1l_1tau category
    const std::map<std::string, double> mvaInputsplainKin_ttV = {
      { "avg_dr_jet",         avg_dr_jet         },
      { "dr_taus",            dr_taus            },
      { "ptmiss",             ptmiss             },
      { "lep_conePt",         lep_conePt         },
      { "mT_lep",             mT_lep             },
      { "mTauTauVis",         mTauTauVis         },
      { "mindr_lep_jet",      mindr_lep_jet      },
      { "mindr_tau1_jet",     mindr_tau1_jet     },
      { "dr_lep_tau_ss",      dr_lep_tau_ss      },
      { "dr_lep_tau_sublead", dr_lep_tau_sublead },
      { "costS_tau",          costS_tau          },
      { "tau1_pt",            tau1_pt            },
      { "tau2_pt",            tau2_pt            },
    };
    const double mvaOutput_plainKin_ttV = mva_plainKin_ttV(mvaInputsplainKin_ttV);

    const std::map<std::string, double> mvaInputsplainKin_tt = {
      { "avg_dr_jet",     avg_dr_jet       },
      { "dr_taus",        dr_taus          },
      { "ptmiss",         ptmiss           },
      { "mT_lep",         mT_lep           },
      { "nJet",           nJet             },
      { "mTauTauVis",     mTauTauVis       },
      { "mindr_lep_jet",  mindr_lep_jet    },
      { "mindr_tau1_jet", mindr_tau1_jet   },
      { "mindr_tau2_jet", mindr_tau2_jet   },
      { "dr_lep_tau_lead", dr_lep_tau_lead },
      { "nBJetLoose",     nBJetLoose       },
      { "tau1_pt",        tau1_pt          },
      { "tau2_pt",        tau2_pt          },
    };
    const double mvaOutput_plainKin_tt = mva_plainKin_tt(mvaInputsplainKin_tt);

    const std::map<std::string, double> mvaInputVariables_plainKin_1B = {
      { "BDTtt",  mvaOutput_plainKin_ttV },
      { "BDTttV", mvaOutput_plainKin_tt },
    };
    const double mvaOutput_plainKin_1B_VT = mva_2lss_plainKin_1B_VT(mvaInputVariables_plainKin_1B);

    const std::map<std::string, double> mvaInputsHTT_sum = {
      { "avg_dr_jet",      avg_dr_jet      },
      { "dr_taus",         dr_taus         },
      { "ptmiss",          ptmiss          },
      { "lep_conePt",      lep_conePt      },
      { "mT_lep",          mT_lep          },
      { "mTauTauVis",      mTauTauVis      },
      { "mindr_lep_jet",   mindr_lep_jet   },
      { "mindr_tau1_jet",  mindr_tau1_jet  },
      { "mindr_tau2_jet",  mindr_tau2_jet  },
      { "dr_lep_tau_ss",   dr_lep_tau_ss   },
      { "dr_lep_tau_lead", dr_lep_tau_lead },
      { "costS_tau",       costS_tau       },
      { "nBJetLoose",      nBJetLoose      },
      { "tau1_pt",         tau1_pt         },
      { "tau2_pt",         tau2_pt         },
      { "HTT",             HTT             },
      { "HadTop_pt",       HadTop_pt       },
    };
    const double mvaOutput_HTT_SUM_VT = mva_HTT_sum_VT(mvaInputsHTT_sum);

    const std::map<std::string, double> mvaInputsplainKin_sum = {
      {"avg_dr_jet",      avg_dr_jet      },
      {"dr_taus",         dr_taus         },
      {"ptmiss",          ptmiss          },
      {"lep_conePt",      lep_conePt      },
      {"mT_lep",          mT_lep          },
      {"mTauTauVis",      mTauTauVis      },
      {"mindr_lep_jet",   mindr_lep_jet   },
      {"mindr_tau1_jet",  mindr_tau1_jet  },
      {"mindr_tau2_jet",  mindr_tau2_jet  },
      {"nJet",           nJet             },
      {"dr_lep_tau_ss",   dr_lep_tau_ss   },
      {"dr_lep_tau_lead", dr_lep_tau_lead },
      {"costS_tau",       costS_tau       },
      {"nBJetLoose",      nBJetLoose      },
      {"tau1_pt",         tau1_pt         },
      {"tau2_pt",         tau2_pt         },
    };
    const double mvaOutput_plainKin_SUM_VT = mva_plainKin_sum_VT(mvaInputsplainKin_sum);
 */

//--- fill histograms with events passing final selection
    selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch][idxSelHadTau_genMatch];
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
    //selHistManager->mvaInputVariables_HTT_sum_->fillHistograms(mvaInputsHTT_sum, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(),
      selMuons.size(),
      selHadTaus.size(),
      selJets.size(),
      selBJets_loose.size(),
      selBJets_medium.size(),
      //mvaOutput_plainKin_ttV,
      //mvaOutput_plainKin_tt,
      //mvaOutput_plainKin_1B_VT,
      //mvaOutput_HTT_SUM_VT,
      //mvaOutput_plainKin_SUM_VT,
      mTauTauVis, mTauTau,
      Pzeta, PzetaVis, PzetaComb, mT_lep, mT_tau,
      mbb, mbb_loose,
      evtWeight);
    if( isSignal ) {
      const std::string decayModeStr = eventInfo.getDecayModeString();
      if ( !decayModeStr.empty() ) {
        selHistManager->evt_in_decayModes_[decayModeStr]->fillHistograms(
          selElectrons.size(),
          selMuons.size(),
          selHadTaus.size(),
          selJets.size(),
          selBJets_loose.size(),
          selBJets_medium.size(),
          //mvaOutput_plainKin_ttV,
          //mvaOutput_plainKin_tt,
          //mvaOutput_plainKin_1B_VT,
          //mvaOutput_HTT_SUM_VT,
          //mvaOutput_plainKin_SUM_VT,
	  mTauTauVis, mTauTau,
	  Pzeta, PzetaVis, PzetaComb, mT_lep, mT_tau,
	  mbb, mbb_loose,
          evtWeight);
      }
    }
    selHistManager->evtYield_->fillHistograms(eventInfo, evtWeight);
    selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("leptonEff", weight_leptonEff);
    selHistManager->weights_->fillHistograms("hadTauEff", weight_hadTauEff);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    std::vector<std::string> categories;
    categories.push_back("1l_1tau");
    if ( isCharge_SS ) {
      categories.push_back("1l_1tau_SS");
    } else if ( isCharge_OS ) {
      categories.push_back("1l_1tau_OS");
      categories.push_back("1l_1tau_OS_wChargeFlipWeights");
    }
    if ( selElectrons.size() >= 1 ) {
      categories.push_back("1e_1tau");
      if ( isCharge_SS ) {
	categories.push_back("1e_1tau_SS");
      } else if ( isCharge_OS ) {
	categories.push_back("1e_1tau_OS");
	categories.push_back("1e_1tau_OS_wChargeFlipWeights");
      }
    } else if ( selMuons.size() >= 1 ) {
      categories.push_back("1mu_1tau");
      if ( isCharge_SS ) {
	categories.push_back("1mu_1tau_SS");
      } else if ( isCharge_OS ) {
	categories.push_back("1mu_1tau_OS");
	categories.push_back("1mu_1tau_OS_wChargeFlipWeights");
      }
    }
    for ( std::vector<std::string>::const_iterator category = categories.begin();
          category != categories.end(); ++category ) {
      double evtWeight_category = evtWeight;
      if ( category->find("_wChargeFlipWeights") != std::string::npos ) {
	double prob_chargeMisId_lepton = prob_chargeMisId(selLepton_type, selLepton->pt(), selLepton->eta());
	double prob_chargeMisId_tau = 0.01; // CV: not implemented yet; take "guessed" value for now
	evtWeight_category *= (prob_chargeMisId_lepton + prob_chargeMisId_tau);
      }
      if ( selHistManager->electrons_in_categories_.find(*category) != selHistManager->electrons_in_categories_.end() ) {
	selHistManager->electrons_in_categories_[*category]->fillHistograms(selElectrons, evtWeight_category);
      }
      if ( selHistManager->muons_in_categories_.find(*category) != selHistManager->muons_in_categories_.end() ) {
	selHistManager->muons_in_categories_[*category]->fillHistograms(selMuons, evtWeight_category);
      }
      if ( selHistManager->hadTaus_in_categories_.find(*category) != selHistManager->hadTaus_in_categories_.end() ) {
	selHistManager->hadTaus_in_categories_[*category]->fillHistograms(selHadTaus, evtWeight_category);
      }
      if ( selHistManager->met_in_categories_.find(*category) != selHistManager->met_in_categories_.end() ) {
        selHistManager->met_in_categories_[*category]->fillHistograms(met, mht_p4, met_LD, evtWeight_category);
      }
      if ( selHistManager->evt_in_categories_.find(*category) != selHistManager->evt_in_categories_.end() ) {
        selHistManager->evt_in_categories_[*category]->fillHistograms(
          selElectrons.size(),
          selMuons.size(),
          selHadTaus.size(),
          selJets.size(),
          selBJets_loose.size(),
          selBJets_medium.size(),
          //mvaOutput_plainKin_ttV,
          //mvaOutput_plainKin_tt,
          //mvaOutput_plainKin_1B_VT,
          //mvaOutput_HTT_SUM_VT,
          //mvaOutput_plainKin_SUM_VT,
	  mTauTauVis, mTauTau,
	  Pzeta, PzetaVis, PzetaComb, mT_lep, mT_tau,
	  mbb, mbb_loose,
          evtWeight_category);
      }
      if ( selHistManager->evt_in_categories_and_decayModes_.find(*category) != selHistManager->evt_in_categories_and_decayModes_.end() ) {
	if( isSignal ) {
	  const std::string decayModeStr = eventInfo.getDecayModeString();
	  if ( !decayModeStr.empty() ) {
	    selHistManager->evt_in_categories_and_decayModes_[*category][decayModeStr]->fillHistograms(
	      selElectrons.size(),
	      selMuons.size(),
	      selHadTaus.size(),
	      selJets.size(),
	      selBJets_loose.size(),
	      selBJets_medium.size(),
	      //mvaOutput_plainKin_ttV,
	      //mvaOutput_plainKin_tt,
	      //mvaOutput_plainKin_1B_VT,
	      //mvaOutput_HTT_SUM_VT,
	      //mvaOutput_plainKin_SUM_VT,
	      mTauTauVis, mTauTau,
	      Pzeta, PzetaVis, PzetaComb, mT_lep, mT_tau,
	      mbb, mbb_loose,
	      evtWeight_category);
	  }
	}
      }
      if ( selHistManager->evtYield_in_categories_.find(*category) != selHistManager->evtYield_in_categories_.end() ) {
	selHistManager->evtYield_in_categories_[*category]->fillHistograms(eventInfo, evtWeight_category);
      }
    }

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
      ((apply_leptonGenMatching && selLepton_genMatch.numGenMatchedJets_ == 0) || ! apply_leptonGenMatching) &&
      ((apply_hadTauGenMatching && selHadTau_genMatch.numGenMatchedJets_ == 0) || ! apply_hadTauGenMatching)
    ;

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
	  ("HTT_boosted",                               HTT_boosted)
	  ("genTopPt_boosted",                          genTopPt_boosted)
	  ("HadTop_pt_boosted",                         HadTop_pt_boosted)
	  ("HTT_semi_boosted_fromAK8",                  HTT_semi_boosted_fromAK8)
	  ("genTopPt_semi_boosted_fromAK8",             genTopPt_semi_boosted_fromAK8)
          ("HadTop_pt_semi_boosted_fromAK8",            HadTop_pt_semi_boosted_fromAK8)
	  ("minDR_HTTv2_lep",                           minDR_HTTv2_lep)
	  ("minDR_AK8_lep",                             minDR_AK8_lep)
	  ("minDR_HTTv2subjets_lep",                    minDR_HTTv2subjets_lep)
	  ("minDR_AK8subjets_lep",                      minDR_AK8subjets_lep)
	  ("lumiScale",                                 lumiScale)
	  ("genWeight",                                 eventInfo.genWeight)
	  ("evtWeight",                                 evtWeight)
          ("prob_fake_lepton",                          (selLepton->genLepton() != 0) ? 1. : prob_fake_lepton)
          ("prob_fake_hadTau",                          (selHadTau->genHadTau() != 0) ? 1. : prob_fake_hadTau)
	  ("nJet",                                      selJets.size())
	  ("nBJetLoose",                                selBJets_loose.size())
	  ("nBJetMedium",                               selBJets_medium.size())
	  ("charge_lep_tau",                            selLepton->charge() + selHadTau->charge()) 
	  ("nHTTv2",                                    sel_HTTv2.size())
	  ("N_jetAK8",                                  jet_ptrsAK8.size())
	  ("cleanedJets_fromAK8",                       cleanedJets_fromAK8.size())
	  ("hadtruth",                                  hadtruth)
	  ("hadtruth_2",                                hadtruth_2)
	  ("bWj1Wj2_isGenMatched_CSVsort4rd",           max_truth_HTT_CSVsort4rd)
	  ("bWj1Wj2_isGenMatched_CSVsort4rd_2",         max_truth_HTT_CSVsort4rd_2)
	  ("hadtruth_boosted",                          hadtruth_boosted)
	  ("hadtruth_semi_boosted_fromAK8",             hadtruth_semi_boosted_fromAK8)
	  ("bWj1Wj2_isGenMatched_boosted",              bWj1Wj2_isGenMatched_boosted)
	  ("bWj1Wj2_isGenMatched_semi_boosted_fromAK8", bWj1Wj2_isGenMatched_semi_boosted_fromAK8)
	  ("resolved_and_semi_AK8",                     resolved_and_semi_AK8)
	  ("boosted_and_semi_AK8",                      boosted_and_semi_AK8)
	  ("resolved_and_boosted",                      resolved_and_boosted)          
        .fill();
    }

    if(snm)
    {
      const double max_dr_jet = comp_max_dr_jet(selJets);

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(preselHadTausFull);
      snm->read(selJets);

      snm->read({ triggers_1e, triggers_1e1tau, triggers_1mu, triggers_1mu1tau });
      snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size());

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
      snm->read(mTauTauVis,                             FloatVariableType::mvis_l1tau);
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

      snm->read(weight_fakeRate,                        FloatVariableType::FR_weight);
      snm->read(triggerWeight,                          FloatVariableType::triggerSF_weight);
      snm->read(weight_leptonEff,                       FloatVariableType::leptonSF_weight);
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
  for ( std::vector<leptonChargeFlipGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauChargeFlipGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

      int idxLepton = leptonGenMatch_definition->idx_;
      int idxHadTau = hadTauGenMatch_definition->idx_;

      const TH1* histogram_EventCounter = selHistManagers[idxLepton][idxHadTau]->evt_->getHistogram_EventCounter();
      std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries() << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "countFat " << countFatTop << " " << countFatTopEntries << " " << countFatTopTruth << std::endl;

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

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete cutFlowHistManager;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1e1tau);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1mu1tau);

  delete inputTree;
  delete snm;

  clock.Show("analyze_1l_1tau");

  return EXIT_SUCCESS;
}
