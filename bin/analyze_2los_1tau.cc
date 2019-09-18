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
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
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
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2los_1tau.h" // EvtHistManager_2los_1tau
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_semi_boosted
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleanerSubJets.h" // RecoJetCollectionCleanerAK8SubJets

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

enum { kFR_disabled, kFR_2lepton, kFR_3L, kFR_1tau };

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied
const int hadTauSelection_veto_antiElectron = -1; // Karl: needs to match anti-electron discriminator applied in 2l+2tau category
const int hadTauSelection_veto_antiMuon = -1; // Karl: needs to match anti-muon discriminator applied in 2l+2tau category

double comp_mvaOutput_Hj_tagger(const RecoJet* jet,
                                const std::vector<const RecoLepton*>& leptons,
                                std::map<std::string, double>& mvaInputs_Hj_tagger,
                                TMVAInterface& mva_Hj_tagger,
                                const EventInfo & eventInfo)
{
  double dRmin_lepton = -1.;
  double dRmax_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
        lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(jet->eta(), jet->phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) dRmin_lepton = dR;
    if ( dRmax_lepton == -1. || dR > dRmax_lepton ) dRmax_lepton = dR;
  }

  mvaInputs_Hj_tagger["Jet_lepdrmin"] = dRmin_lepton;
  mvaInputs_Hj_tagger["max(Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags,0.)"] = std::max(0., jet->BtagCSV());
  mvaInputs_Hj_tagger["max(Jet_qg,0.)"] = std::max(0., jet->QGDiscr());
  mvaInputs_Hj_tagger["Jet_lepdrmax"] = dRmax_lepton;
  mvaInputs_Hj_tagger["Jet_pt"] = jet->pt();

  check_mvaInputs(mvaInputs_Hj_tagger, eventInfo);

  double mvaOutput_Hj_tagger = mva_Hj_tagger(mvaInputs_Hj_tagger);
  return mvaOutput_Hj_tagger;
}

/**
 * @brief Produce datacard and control plots for 2los_1tau categories.
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

  std::cout << "<analyze_2los_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_2los_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_2los_1tau")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_2los_1tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tH = process_string == "tHq" || process_string == "tHW";
  const bool isMC_VH = process_string == "VH" || process_string == "ggH" || process_string == "qqH";
  const bool isMC_signal = process_string == "signal" || process_string == "signal_ctcvcp";
  const bool isSignal = isMC_signal || isMC_tH || isMC_VH;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

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

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_2lepton(apply_leptonGenMatching);
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
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_1tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_l1PreFireWeight = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
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
  const vstring syncNtuple_genMatch = syncNtuple_cfg.getParameter<vstring>("genMatch");
  const bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
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
  const int jetToLeptonFakeRate_option        = getJetToLeptonFR_option       (central_or_shift);
  const int jetToTauFakeRate_option           = getJetToTauFR_option          (central_or_shift);
  const int lheScale_option                   = getLHEscale_option            (central_or_shift);
  const int jetBtagSF_option                  = getBTagWeight_option          (central_or_shift);
  const PUsys puSys_option                    = getPUsys_option               (central_or_shift);
  const L1PreFiringWeightSys l1PreFire_option = getL1PreFiringWeightSys_option(central_or_shift);

  const int met_option      = useNonNominal_jetmet ? kJetMET_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option    = useNonNominal_jetmet ? kJetMET_central_nonNominal : getJet_option(central_or_shift, isMC);
  const int hadTauPt_option = useNonNominal_jetmet ? kHadTauPt_uncorrected      : getHadTauPt_option(central_or_shift);

  std::cout
    << "central_or_shift = "               << central_or_shift             << "\n"
       " -> jetToLeptonFakeRate_option = " << jetToLeptonFakeRate_option   << "\n"
       " -> hadTauPt_option            = " << hadTauPt_option              << "\n"
       " -> jetToTauFakeRate_option    = " << jetToTauFakeRate_option      << "\n"
       " -> lheScale_option            = " << lheScale_option              << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option             << "\n"
       " -> met_option                 = " << met_option                   << "\n"
       " -> jetPt_option               = " << jetPt_option                 << "\n"
       " -> l1PreFire_option           = " << as_integer(l1PreFire_option) << '\n'
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
    default: throw cmsException("analyze_2los_1tau", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else if ( applyFakeRateWeights_string == "3L"       ) applyFakeRateWeights = kFR_3L;
  else if ( applyFakeRateWeights_string == "1tau"     ) applyFakeRateWeights = kFR_1tau;
  else throw cms::Exception("analyze_2los_1tau")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L || applyFakeRateWeights == kFR_1tau || apply_hadTauFakeRateSF ) {
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

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  std::string branchName_hadTauGenMatch   = cfg_analyze.getParameter<std::string>("branchName_hadTauGenMatch");
  std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");

  const bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

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
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
    snm->initializeBranches();
    snm->initializeHLTBranches({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
  }

//--- declare event-level variables
  EventInfo eventInfo(isMC, isSignal);
  const std::string default_cat_str = "default";
  std::vector<std::string> evt_cat_strs = { default_cat_str };
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isMC_signal) && ! tHweights.empty())
  {
    eventInfo.loadWeight_tH(tHweights);
    const std::vector<std::string> evt_cat_tH_strs = eventInfo.getWeight_tH_str();
    evt_cat_strs.insert(evt_cat_strs.end(), evt_cat_tH_strs.begin(), evt_cat_tH_strs.end());
  }
  EventInfoReader eventInfoReader(&eventInfo, puSys_option);
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
    l1PreFiringWeightReader = new L1PreFiringWeightReader(era, l1PreFire_option);
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
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauSelectorTight tightHadTauFilter(era);
  tightHadTauFilter.set(hadTauSelection_part2);
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);
  switch(hadTauSelection)
  {
    case kFakeable: tauLevel = std::min(tauLevel, get_tau_id_wp_int(fakeableHadTauSelector.getSelector().get())); break;
    case kTight:    tauLevel = std::min(tauLevel, get_tau_id_wp_int(tightHadTauSelector.getSelector().get()));    break;
    default: assert(0);
  }

  // Karl: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 2l+2tau category
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
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionCleaner jetCleaner_large8(0.8, isDEBUG);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  const RecoJetCollectionSelectorForward jetSelectorForward(era, -1, isDEBUG);

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);
  RecoJetCollectionCleanerAK8SubJets jetCleanerAK8SubJets(0.4, isDEBUG); //to clean against leptons and hadronic taus

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

  //--- initialize hadronic top tagger BDT
  HadTopTagger* hadTopTagger = new HadTopTagger();
  HadTopTagger_semi_boosted_AK8* hadTopTagger_semi_boosted_fromAK8 = new HadTopTagger_semi_boosted_AK8();

  std::string mvaFileName_Hj_tagger = "tthAnalysis/HiggsToTauTau/data/Hj_csv_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_Hj_tagger;
  mvaInputVariables_Hj_tagger.push_back("Jet_lepdrmin");
  mvaInputVariables_Hj_tagger.push_back("max(Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags,0.)");
  mvaInputVariables_Hj_tagger.push_back("max(Jet_qg,0.)");
  mvaInputVariables_Hj_tagger.push_back("Jet_lepdrmax");
  mvaInputVariables_Hj_tagger.push_back("Jet_pt");
  TMVAInterface mva_Hj_tagger(mvaFileName_Hj_tagger, mvaInputVariables_Hj_tagger);

  std::string mvaFileName_Hjj_tagger = "tthAnalysis/HiggsToTauTau/data/Hjj_csv_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_Hjj_tagger;
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_minlepmass");
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_sumbdt");
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_dr");
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_minjdr");
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_mass");
  mvaInputVariables_Hjj_tagger.push_back("bdtJetPair_minjOvermaxjdr");
  TMVAInterface mva_Hjj_tagger(mvaFileName_Hjj_tagger, mvaInputVariables_Hjj_tagger);

  std::string mvaFileNameEvt = "tthAnalysis/HiggsToTauTau/data/2los_1tau_XGB_HTT_evtLevelSUM_TTH_19Var.pkl";
  std::vector<std::string> mvaInputVariables_2los_1tau_SUM;
  mvaInputVariables_2los_1tau_SUM.push_back("avg_dr_jet");
  mvaInputVariables_2los_1tau_SUM.push_back("dr_lep1_tau_os");
  mvaInputVariables_2los_1tau_SUM.push_back("dr_lep2_tau_ss");
  mvaInputVariables_2los_1tau_SUM.push_back("dr_leps");
  mvaInputVariables_2los_1tau_SUM.push_back("lep2_conePt");
  mvaInputVariables_2los_1tau_SUM.push_back("mT_lep1");
  mvaInputVariables_2los_1tau_SUM.push_back("mT_lep2");
  mvaInputVariables_2los_1tau_SUM.push_back("mTauTauVis");
  mvaInputVariables_2los_1tau_SUM.push_back("tau_pt");
  mvaInputVariables_2los_1tau_SUM.push_back("tau_eta");
  mvaInputVariables_2los_1tau_SUM.push_back("min_lep_eta");
  mvaInputVariables_2los_1tau_SUM.push_back("mindr_lep1_jet");
  mvaInputVariables_2los_1tau_SUM.push_back("mindr_lep2_jet");
  mvaInputVariables_2los_1tau_SUM.push_back("mindr_tau_jet");
  mvaInputVariables_2los_1tau_SUM.push_back("mbb_loose");
  mvaInputVariables_2los_1tau_SUM.push_back("nJet");
  mvaInputVariables_2los_1tau_SUM.push_back("mvaOutput_hadTopTaggerWithKinFit");
  mvaInputVariables_2los_1tau_SUM.push_back("HadTop_eta");
  mvaInputVariables_2los_1tau_SUM.push_back("HadTop_pt");
  XGBInterface mva_2los_1tau_SUM(mvaFileNameEvt, mvaInputVariables_2los_1tau_SUM);

  std::string mvaFileName_XGB_Updated = "tthAnalysis/HiggsToTauTau/data/evtLevel_Sep2018/2los_1tau_XGB_Updated_evtLevelSUM_TTH_18Var.pkl";
  std::vector<std::string> mvaInputVariables_XGB_Updated = {
    "tau_pt", "res-HTT_CSVsort4rd", "avg_dr_jet",
    "tau_eta", "mindr_tau_jet", "HadTop_pt_CSVsort4rd",
    "dr_leps", "mbb_loose", "mTauTauVis",
    "mindr_lep1_jet", "nJet", "dr_lep1_tau_os",
    "mindr_lep2_jet", "mT_lep2", "dr_lep2_tau_ss",
    "lep2_conePt", "min_lep_eta_abs", "ptmiss"
  };
  XGBInterface mva_XGB_Updated(mvaFileName_XGB_Updated, mvaInputVariables_XGB_Updated);
  std::map<std::string, double> mvaInputs_XGB_Updated;

  std::string mvaFileName_XGB_Boosted_AK8 = "tthAnalysis/HiggsToTauTau/data/evtLevel_Sep2018/2los_1tau_XGB_Boosted_AK8_evtLevelSUM_TTH_22Var.pkl";
  std::vector<std::string> mvaInputVariables_XGB_Boosted_AK8 = {
    "tau_pt", "res-HTT_CSVsort4rd", "avg_dr_jet",
    "tau_eta", "mindr_tau_jet", "HadTop_pt_CSVsort4rd",
    "dr_leps", "mbb_loose", "mTauTauVis",
    "mindr_lep1_jet", "nJet", "dr_lep1_tau_os",
    "mindr_lep2_jet", "mT_lep2", "dr_lep2_tau_ss",
    "lep2_conePt", "min_lep_eta_abs", "ptmiss",
    "resolved_and_boosted", "HTT_semi_boosted_fromAK8", "minDR_AK8_lep", "HTT_boosted"
  };
  XGBInterface mva_XGB_Boosted_AK8(mvaFileName_XGB_Boosted_AK8, mvaInputVariables_XGB_Boosted_AK8);
  std::map<std::string, double> mvaInputs_XGB_Boosted_AK8;

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
        genMatchToMuonReader -> readGenPartFlav(false);
        inputTree -> registerReader(genMatchToMuonReader);

        genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
        genMatchToElectronReader -> readGenPartFlav(false);
        inputTree -> registerReader(genMatchToElectronReader);

        genMatchToHadTauReader = new GenParticleReader(branchName_hadTauGenMatch);
        genMatchToHadTauReader -> readGenPartFlav(false);
        inputTree -> registerReader(genMatchToHadTauReader);

        genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
        genMatchToJetReader -> readGenPartFlav(false);
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
    inputTree->registerReader(genQuarkFromTopReader);
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

  std::string mvaFileName_2los_1tau_ttV = "tthAnalysis/HiggsToTauTau/data/evtLevel_deprecated/2los_1tau_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2los_1tau_ttV;
  mvaInputVariables_2los_1tau_ttV.push_back("lep1_conePt");
  mvaInputVariables_2los_1tau_ttV.push_back("lep2_conePt");
  mvaInputVariables_2los_1tau_ttV.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2los_1tau_ttV.push_back("mT_lep1");
  mvaInputVariables_2los_1tau_ttV.push_back("dr_leps");
  mvaInputVariables_2los_1tau_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2los_1tau_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2los_1tau_ttV.push_back("dr_lep_tau_os");
  mvaInputVariables_2los_1tau_ttV.push_back("dr_lep_tau_ss");
  mvaInputVariables_2los_1tau_ttV.push_back("TMath::Abs(tau_eta)");
  mvaInputVariables_2los_1tau_ttV.push_back("mindr_tau_jet");
  mvaInputVariables_2los_1tau_ttV.push_back("TMath::Min(ptmiss,500)");
  mvaInputVariables_2los_1tau_ttV.push_back("mTauTauVis");
  TMVAInterface mva_2los_1tau_ttV(mvaFileName_2los_1tau_ttV, mvaInputVariables_2los_1tau_ttV);

  std::string mvaFileName_2los_1tau_ttbar = "tthAnalysis/HiggsToTauTau/data/evtLevel_deprecated/2los_1tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2los_1tau_ttbar;
  mvaInputVariables_2los_1tau_ttbar.push_back("lep1_conePt");
  mvaInputVariables_2los_1tau_ttbar.push_back("lep2_conePt");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Abs(lep1_eta)");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Abs(lep2_eta)");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2los_1tau_ttbar.push_back("mT_lep1");
  mvaInputVariables_2los_1tau_ttbar.push_back("mT_lep2");
  mvaInputVariables_2los_1tau_ttbar.push_back("dr_leps");
  mvaInputVariables_2los_1tau_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2los_1tau_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2los_1tau_ttbar.push_back("dr_lep_tau_os");
  mvaInputVariables_2los_1tau_ttbar.push_back("dr_lep_tau_ss");
  mvaInputVariables_2los_1tau_ttbar.push_back("tau_pt");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Abs(tau_eta)");
  mvaInputVariables_2los_1tau_ttbar.push_back("mindr_tau_jet");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Min(ptmiss,500)");
  mvaInputVariables_2los_1tau_ttbar.push_back("TMath::Min(htmiss,500)");
  mvaInputVariables_2los_1tau_ttbar.push_back("mTauTauVis");
  mvaInputVariables_2los_1tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2los_1tau_ttbar.push_back("nJet");
  mvaInputVariables_2los_1tau_ttbar.push_back("nBJetLoose");
  mvaInputVariables_2los_1tau_ttbar.push_back("nBJetMedium");
  mvaInputVariables_2los_1tau_ttbar.push_back("lep1_charge*tau_charge");
  TMVAInterface mva_2los_1tau_ttbar(mvaFileName_2los_1tau_ttbar, mvaInputVariables_2los_1tau_ttbar);

//-- BDT trained by Kartik
  std::string mvaFileName_2los_1tau_evtLevelSUM_TTH_19Var = "tthAnalysis/HiggsToTauTau/data/2los_1tau_XGB_HTT_evtLevelSUM_TTH_19Var.pkl";
  std::vector<std::string> mvaInputs2los_1tau_evtLevelSUM_TTH_19VarSort =  {
    "avg_dr_jet", "dr_lep1_tau_os", "dr_lep2_tau_ss", "dr_leps", "lep2_conePt", "mT_lep1", "mT_lep2",
  "mTauTauVis", "tau_pt", "tau_eta", "min_lep_eta", "mindr_lep1_jet", "mindr_lep2_jet", "mindr_tau_jet",
  "mbb_loose", "nJet", "res-HTT_2016", "HadTop_eta", "HadTop_pt"
  };
  XGBInterface mva_xgb_2los_1tau_evtLevelSUM_TTH_19Var(
    mvaFileName_2los_1tau_evtLevelSUM_TTH_19Var, mvaInputs2los_1tau_evtLevelSUM_TTH_19VarSort
  );

  ///for ttH vs ttbar --BDT
  std::string mvaFileName_2los_1tau_evtLevelTT_TTH_20Var = "tthAnalysis/HiggsToTauTau/data/2los_1tau_XGB_HTT_evtLevelTT_TTH_20Var.pkl";
  std::vector<std::string> mvaInputs2los_1tau_evtLevelTT_TTH_20VarSort =  {
   "avg_dr_jet","dr_lep1_tau_os", "dr_lep2_tau_ss", "dr_leps", "lep1_conePt", "lep2_conePt", "mT_lep1", "mT_lep2",
    "mTauTauVis", "tau_pt", "tau_eta", "min_lep_eta", "mindr_lep1_jet", "mindr_lep2_jet", "mindr_tau_jet", "mbb_loose",
    "nJet", "res-HTT_2016", "HadTop_eta", "HadTop_pt"
  };
  XGBInterface mva_xgb_2los_1tau_evtLevelTT_TTH_20Var(
    mvaFileName_2los_1tau_evtLevelTT_TTH_20Var, mvaInputs2los_1tau_evtLevelTT_TTH_20VarSort
  );



  std::vector<std::string> mvaInputVariables_2los_1tau = get_mvaInputVariables(
    mvaInputs2los_1tau_evtLevelSUM_TTH_19VarSort, mvaInputVariables_2los_1tau_ttbar
  ); // those two are the only one important
  std::map<std::string, double> mvaInputs_2los_1tau;

  std::string inputFileName_mva_mapping_2los_1tau = "tthAnalysis/HiggsToTauTau/data/evtLevel_deprecated/2los_1tau_BDT_mapping.root";
  TFile* inputFile_mva_mapping_2los_1tau = openFile(LocalFileInPath(inputFileName_mva_mapping_2los_1tau));
  TH2* mva_mapping_2los_1tau = loadTH2(inputFile_mva_mapping_2los_1tau, "hTargetBinning");

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;

//--- declare histograms
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    std::map<std::string, ElectronHistManager*> electrons_in_categories_;
    ElectronHistManager* leadElectron_;
    std::map<std::string, ElectronHistManager*> leadElectron_in_categories_;
    ElectronHistManager* subleadElectron_;
    std::map<std::string, ElectronHistManager*> subleadElectron_in_categories_;
    MuonHistManager* muons_;
    std::map<std::string, MuonHistManager*> muons_in_categories_;
    MuonHistManager* leadMuon_;
    std::map<std::string, MuonHistManager*> leadMuon_in_categories_;
    MuonHistManager* subleadMuon_;
    std::map<std::string, MuonHistManager*> subleadMuon_in_categories_;
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
    MVAInputVarHistManager* mvaInputVariables_2los_1tau_;
    std::map<std::string, EvtHistManager_2los_1tau*> evt_;
    std::map<std::string, std::map<std::string, EvtHistManager_2los_1tau*>> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_2los_1tau*> evt_in_categories_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };

  typedef std::map<int, selHistManagerType*> int_to_selHistManagerMap;
  std::map<int, int_to_selHistManagerMap> selHistManagers;
  for ( std::vector<leptonGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

      int idxLepton = leptonGenMatch_definition->idx_;
      int idxHadTau = hadTauGenMatch_definition->idx_;

      selHistManagerType* selHistManager = new selHistManagerType();
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
      selHistManager->mvaInputVariables_2los_1tau_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/mvaInputs_2los_1tau", histogramDir.data()), era_string, central_or_shift));
      selHistManager->mvaInputVariables_2los_1tau_->bookHistograms(fs, mvaInputVariables_2los_1tau);

      for(const std::string & evt_cat_str: evt_cat_strs)
      {
        std::string proc0 = process_string;
        if ( process_string == "signal") proc0 = "ttH";
        if ( process_string == "signal_ctcvcp" ) proc0 = "ttH_ctcvcp";
        const std::string process_string_new = evt_cat_str == default_cat_str ?
          proc0 :
          proc0 + evt_cat_str
        ;
        const std::string process_and_genMatchName = boost::replace_all_copy(
          process_and_genMatch, process_string, process_string_new
        );

        selHistManager->evt_[evt_cat_str] = new EvtHistManager_2los_1tau(makeHistManager_cfg(
          process_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
        ));
        selHistManager->evt_[evt_cat_str]->bookHistograms(fs);
      }

      const vstring decayModes_evt = eventInfo.getDecayModes();
      if(isSignal)
      {
        for(const std::string & decayMode_evt: decayModes_evt)
        {

          if ( ( isMC_tH || isMC_VH ) && ( decayMode_evt == "hzg" || decayMode_evt == "hmm" ) ) continue;
          std::string decayMode_and_genMatch;
          if ( isMC_tH || isMC_VH ) {
            decayMode_and_genMatch = process_string;
            decayMode_and_genMatch += "_";
          }
          else decayMode_and_genMatch = "ttH_";
          decayMode_and_genMatch += decayMode_evt;

          if(apply_leptonGenMatching)                            decayMode_and_genMatch += leptonGenMatch_definition -> name_;
          if(apply_leptonGenMatching && apply_hadTauGenMatching) decayMode_and_genMatch += "&";
          if(apply_hadTauGenMatching)                            decayMode_and_genMatch += hadTauGenMatch_definition -> name_;

          for(const std::string & evt_cat_str: evt_cat_strs)
          {
            const std::string process_string_new = evt_cat_str == default_cat_str ?
              process_string:
              process_string + "_" + evt_cat_str
            ;
            const std::string decayMode_and_genMatchName = boost::replace_all_copy(
              decayMode_and_genMatch, process_string, process_string_new
            );

            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] = new EvtHistManager_2los_1tau(makeHistManager_cfg(
              decayMode_and_genMatchName, Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift
            ));
            selHistManager -> evt_in_decayModes_[evt_cat_str][decayMode_evt] -> bookHistograms(fs);
          }
        }
      }
      edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/evtYield", histogramDir.data()), era_string, central_or_shift);
      cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
      cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
      selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
      selHistManager->evtYield_->bookHistograms(fs);
      selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/weights", histogramDir.data()), era_string, central_or_shift));
      selHistManager->weights_->bookHistograms(fs, { "genWeight", "pileupWeight", "triggerWeight", "data_to_MC_correction", "fakeRate" });
      selHistManagers[idxLepton][idxHadTau] = selHistManager;
    }
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string,
      Form("%s/unbiased/genEvt", histogramDir.data()),  era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string,
      Form("%s/sel/genEvt", histogramDir.data()),era_string, central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string,
      Form("%s/sel/lheInfo", histogramDir.data()),era_string, central_or_shift));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string,central_or_shift)
    );
    bdt_filler->register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_tth_mva", "mindr_lep1_jet", "mT_lep1", "dr_lep1_tau_os",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_tth_mva", "mindr_lep2_jet", "mT_lep2", "dr_lep2_tau_ss",
      "mindr_tau_jet", "avg_dr_jet", "ptmiss",  "htmiss", "tau_mva", "tau_pt", "tau_eta",
      "dr_leps", "mTauTauVis", "genWeight", "evtWeight",
      "lep1_genLepPt", "lep2_genLepPt",
      "tau_genTauPt",
      "lep1_fake_prob", "lep2_fake_prob", "tau_fake_prob","dr_leps",
      "max_lep_eta", "min_lep_eta",
      "mbb", "ptbb", "b1_pt", "b2_pt", "drbb", "detabb",
      "mbb_loose", "ptbb_loose", "b1_loose_pt", "b2_loose_pt", "drbb_loose", "detabb_loose",
      "res-HTT_CSVsort4rd", "HadTop_pt_CSVsort4rd", "genTopPt_CSVsort4rd",
      "HTT_semi_boosted_fromAK8", "genTopPt_semi_boosted_fromAK8", "HadTop_pt_semi_boosted_fromAK8",
      "W_pt_semi_boosted_fromAK8", "b_pt_semi_boosted_fromAK8",
      "minDR_AK8_lep", "minDR_AK8subjets_lep"

    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "lep1_isTight", "lep1_charge",
      "lep2_isTight", "lep2_charge", "tau_isTight",
      "tau_charge", "lep1_tau_charge", "nLep",  "nTau",
      "hadtruth", "bWj1Wj2_isGenMatched_CSVsort4rd",

      "hadtruth_semi_boosted_fromAK8",
      "N_jetAK8", "cleanedJets_fromAK8",
      "bWj1Wj2_isGenMatched_semi_boosted_fromAK8",
      "resolved_and_semi_AK8"

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
    process_string, Form("%s/sel/cutFlow", histogramDir.data()), era_string,central_or_shift
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "object multiplicity",
    "trigger",
    ">= 2 presel leptons",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet",
    ">= 1 sel tau",
    ">= 2 sel leptons",
    "<= 2 tight leptons",
    "HLT filter matching",
    ">= 3 jets",
    "<= 1 veto taus",
    "m(ll) > 12 GeV",
    "lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV",
    "tight lepton charge",
    "sel lepton-pair OS charge",
    "Z-boson mass veto",
    "met LD > 30 GeV",
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

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
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
    cutFlowTable.update("object multiplicity");
    cutFlowHistManager->fillHistograms("object multiplicity", lumiScale);

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

    double evtWeight_inclusive = 1.;
    double evtWeight_tH_nom = 1.;
    if(isMC)
    {
      if(apply_genWeight)         evtWeight_inclusive *= boost::math::sign(eventInfo.genWeight);
      if(eventWeightManager)      evtWeight_inclusive *= eventWeightManager->getWeight();
      if(l1PreFiringWeightReader) evtWeight_inclusive *= l1PreFiringWeightReader->getWeight();
      lheInfoReader->read();
      evtWeight_inclusive *= lheInfoReader->getWeight_scale(lheScale_option);
      evtWeight_inclusive *= eventInfo.pileupWeight;

      evtWeight_tH_nom = eventInfo.genWeight_tH();
      evtWeight_inclusive *= evtWeight_tH_nom;

      evtWeight_inclusive *= lumiScale;
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu);

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
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);

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
      const std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
      selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);
    }

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

    // Karl: veto events containing more than one tau passing the VTight WP, to avoid overlap with the 2l+2tau category
    const std::vector<const RecoHadTau*> vetoHadTaus = vetoHadTauSelector(cleanedHadTaus, isHigherPt);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableLeptonsFull, fakeableHadTausFull) :
      jetCleaner       (jet_ptrs, fakeableLeptonsFull, fakeableHadTausFull)
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
    std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    std::vector<const RecoJetAK8*> jet_ptrsAK8raw = convert_to_ptrs(jetsAK8);
    std::vector<const RecoJetAK8*> jet_ptrsAK8;
    std::vector<const RecoJetAK8*> cleanedJetsAK8 = jetCleanerAK8SubJets(jet_ptrsAK8raw, selMuons, selElectrons, selHadTaus);
    jet_ptrsAK8 = jetSelectorAK8(cleanedJetsAK8, isHigherPt);
    //std::cout << "after load ak8"  << std::endl;
//--- cleaned RecoJet collection from AK8 as well
    std::vector<const RecoJet*> cleanedJets_fromAK8;
    cleanedJets_fromAK8 = jetCleaner_large8(selJets, jet_ptrsAK8);

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
    cutFlowTable.update(">= 2 presel leptons");
    cutFlowHistManager->fillHistograms(">= 2 presel leptons", lumiScale);
    const RecoLepton* preselLepton_lead = preselLeptonsFull[0];
    const RecoLepton* preselLepton_sublead = preselLeptonsFull[1];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on preselection level
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selJets selection (1)." << std::endl;
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets");
    cutFlowHistManager->fillHistograms(">= 2 jets", lumiScale);

    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selBJets selection (1)." << std::endl;
        printCollection("selJets", selJets);
        printCollection("selBJets_loose", selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet", lumiScale);

    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selHadTaus selection." << std::endl;
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau");
    cutFlowHistManager->fillHistograms(">= 1 sel tau", lumiScale);

    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined1);

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    const Particle::LorentzVector mht_p4 = compMHT(fakeableLeptonsFull, fakeableHadTausFull, selJets);
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    // require exactly two leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
        printCollection("selLeptons", selLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 2 sel leptons", 1.);
    cutFlowHistManager->fillHistograms(">= 2 sel leptons", 1.);
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined2);

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
    double leptonSF_weight = 1.;
    double tauSF_weight = 1.;
    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
        selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta());

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

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);
      dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());
      tauSF_weight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      tauSF_weight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      tauSF_weight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      weight_data_to_MC_correction *= tauSF_weight;
      if ( isDEBUG ) {
        std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }

      evtWeight *= weight_data_to_MC_correction;
    }

    bool passesTight_hadTau = isMatched(*selHadTau, tightHadTausFull);
    bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
    bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);

    double weight_fakeRate = 1.;
    double prob_fake_lepton_lead = 1.;
    double prob_fake_lepton_sublead = 1.;
    if(leptonFakeRateInterface) {
      const int selLepton_lead_absPdgId    = std::abs(selLepton_lead->pdgId());
      switch(selLepton_lead_absPdgId)
      {
        case 11: prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(
                                           selLepton_lead->cone_pt(), selLepton_lead->absEta()
                                         );
                                         break;
        case 13: prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(
                                           selLepton_lead->cone_pt(), selLepton_lead->absEta()
                                         );
                                         break;
        default: assert(0);
      }
      const int selLepton_sublead_absPdgId = std::abs(selLepton_sublead->pdgId());
      switch(selLepton_sublead_absPdgId)
      {
        case 11: prob_fake_lepton_lead = prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(
                   selLepton_sublead->cone_pt(), selLepton_sublead->absEta()
                 );
                 break;
        case 13: prob_fake_lepton_lead = prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(
                   selLepton_sublead->cone_pt(), selLepton_sublead->absEta()
                 );
                 break;
        default: assert(0);
      }
    }

    double prob_fake_hadTau = 1.;
    if(jetToTauFakeRateInterface) prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());

    if ( applyFakeRateWeights == kFR_3L ) weight_fakeRate = getWeight_3L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead,
        prob_fake_hadTau, passesTight_hadTau);
    else if ( applyFakeRateWeights == kFR_2lepton) weight_fakeRate = getWeight_2L(
          prob_fake_lepton_lead, passesTight_lepton_lead,
          prob_fake_lepton_sublead, passesTight_lepton_sublead);
    else if ( applyFakeRateWeights == kFR_1tau) weight_fakeRate = prob_fake_hadTau;
    if ( !selectBDT ) evtWeight *= weight_fakeRate;

      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight && !(selHadTau->genHadTau() || selHadTau->genLepton()) ) {
        double weight_data_to_MC_correction_hadTau = jetToTauFakeRateInterface->getSF_lead(selHadTau->pt(), selHadTau->absEta());
        if ( isDEBUG ) {
          std::cout << "weight_data_to_MC_correction_hadTau = " << weight_data_to_MC_correction_hadTau << std::endl;
        }
        tauSF_weight *= weight_data_to_MC_correction_hadTau;
        evtWeight *= weight_data_to_MC_correction_hadTau;
      }

    // require exactly two leptons passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptonsFull.size() <= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection.\n";
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 2 tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("<= 2 tight leptons", evtWeight);

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
    cutFlowTable.update("HLT filter matching", evtWeight);
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeight);

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS selJets selection (2)." << std::endl;
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(">= 3 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 3 jets", evtWeight);

    // veto events containing more than one tau passing the Medium WP, to avoid overlap with the 2l+2tau category
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

    const bool failsLowMassVeto = isfailsLowMassVeto(preselLeptonsFullUncleaned);
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

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
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);
    cutFlowHistManager->fillHistograms("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    if ( selLepton_lead->charge()*selLepton_sublead->charge() > 0 ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton-pair OS charge", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton-pair OS charge", evtWeight);

    bool failsZbosonMassVeto = isfailsZbosonMassVeto(preselLeptonsFull);
    if ( failsZbosonMassVeto ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS Z-boson veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeight);
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeight);

    if ( ((selLepton_lead->is_electron() && selLepton_sublead->is_electron()) ||
          (selLepton_lead->is_muon()     && selLepton_sublead->is_muon())      ) && met_LD < 30. ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS MET LD selection.\n"
                     " (LD = " << met_LD << ")\n"
        ;
      }
      continue;
    }
    cutFlowTable.update("met LD > 30 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("met LD > 30 GeV", evtWeight);

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
    cutFlowTable.update("signal region veto", evtWeight);
    cutFlowHistManager->fillHistograms("signal region veto", evtWeight);

    const RecoLepton* selLepton_OS = 0;
    const RecoLepton* selLepton_SS = 0;
    if ( selLepton_lead->charge()*selHadTau->charge() < 0. ) {
      selLepton_OS = selLepton_lead;
      selLepton_SS = selLepton_sublead;
    } else if ( selLepton_sublead->charge()*selHadTau->charge() < 0. ) {
      selLepton_OS = selLepton_sublead;
      selLepton_SS = selLepton_lead;
    }
    double mTauTauVis_sel = ( selLepton_OS ) ? (selLepton_OS->p4() + selHadTau->p4()).mass() : -1.;

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss_1tau category of ttH multilepton analysis
    mvaInputs_2lss["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(selLepton_lead->eta()), std::fabs(selLepton_sublead->eta()));
    mvaInputs_2lss["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
    mvaInputs_2lss["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs_2lss["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    mvaInputs_2lss["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    mvaInputs_2lss["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*selLepton_lead);
    mvaInputs_2lss["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*selLepton_sublead);
    mvaInputs_2lss["min(met_pt,400)"]            = std::min(met.pt(), (Double_t)400.);
    mvaInputs_2lss["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);

    check_mvaInputs(mvaInputs_2lss, eventInfo);
    //for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_2lss.begin();
    //            mvaInput != mvaInputs_2lss.end(); ++mvaInput ) {
    //  std::cout << " " << mvaInput->first << " = " << mvaInput->second << std::endl;
    //}

    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs_2lss);
    //std::cout << "mvaOutput_2lss_ttV = " << mvaOutput_2lss_ttV << std::endl;
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs_2lss);
    //std::cout << "mvaOutput_2lss_ttbar = " << mvaOutput_2lss_ttbar << std::endl;

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
    bool resolved_and_semi_AK8 = false;
    double max_mvaOutput_HTT_CSVsort4rd = 0.;
    bool max_truth_HTT_CSVsort4rd = false;
    double HadTop_pt_CSVsort4rd = 0.;
    double HadTop_eta_CSVsort4rd = 0.;
    double genTopPt_CSVsort4rd = 0.;
    double b_pt_CSVsort4rd_1 = 0.1;
    double Wj1_pt_CSVsort4rd_1 = 0.1;
    double Wj2_pt_CSVsort4rd_1 = 0.1;
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
      HadTop_eta_CSVsort4rd = std::fabs(((*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4()).eta());
      Wj1_pt_CSVsort4rd_1 = (*selWJet1)->pt();
      Wj2_pt_CSVsort4rd_1 = (*selWJet2)->pt();
      b_pt_CSVsort4rd_1   = (*selBJet)->pt();
    }

    }
      }
    }

// -- semi-boosted hTT -- AK8
    double HTT_semi_boosted_fromAK8 = 0.;
    bool bWj1Wj2_isGenMatched_semi_boosted_fromAK8 = false;
    double genTopPt_semi_boosted_fromAK8 = 0.;
    double HadTop_pt_semi_boosted_fromAK8 = 0.;
    double W_pt_semi_boosted_fromAK8 = 0.;
    double b_pt_semi_boosted_fromAK8 = 0.;

    bool hadtruth_semi_boosted_fromAK8 = false;
    double minDR_AK8_lep = -1.;
    double minDR_AK8subjets_lep = -1.;
    for ( std::vector<const RecoJet*>::const_iterator selBJet = cleanedJets_fromAK8.begin(); selBJet != cleanedJets_fromAK8.end(); ++selBJet )  { // cleanedJets.size()
    for ( std::vector<const RecoJetAK8*>::const_iterator jetIter = jet_ptrsAK8.begin();
          jetIter != jet_ptrsAK8.end(); ++jetIter ) {
        if ( !((*jetIter)->subJet1() && (*jetIter)->subJet2()) ) continue;
        bool isGenMatched = false;
        double genTopPt_teste = 0.;
        double HadTop_pt = ((*jetIter)->p4() + (*selBJet)->p4()).pt();
        //bool fatjet_isGenMatched = false;
        const std::map<int, double> bdtResult = (*hadTopTagger_semi_boosted_fromAK8)(**jetIter, **selBJet, calculate_matching, isGenMatched, genTopPt_teste, genVar, genVarAnti);
        if (isGenMatched) {hadtruth_semi_boosted_fromAK8 = true;}

        if ( bdtResult.at(kXGB_semi_boosted_AK8_no_kinFit) > HTT_semi_boosted_fromAK8 ) {
          bWj1Wj2_isGenMatched_semi_boosted_fromAK8 = isGenMatched;
          HTT_semi_boosted_fromAK8 = bdtResult.at(kXGB_semi_boosted_AK8_no_kinFit);
          HadTop_pt_semi_boosted_fromAK8 = HadTop_pt;
          genTopPt_semi_boosted_fromAK8 = genTopPt_teste;
          minDR_AK8_lep = std::min(
            deltaR(selLepton_lead->p4(), (*jetIter)->p4()),
            deltaR(selLepton_sublead->p4(), (*jetIter)->p4())
          );
          b_pt_semi_boosted_fromAK8 = (*selBJet)->pt() ;
          W_pt_semi_boosted_fromAK8 = (*jetIter)->pt() ;
          minDR_AK8subjets_lep =
          std::min(
          std::min(
            deltaR(selLepton_lead->p4(), (*jetIter)->subJet1()->p4()),
            deltaR(selLepton_sublead->p4(), (*jetIter)->subJet1()->p4())
          ),
          std::min(
            deltaR(selLepton_lead->p4(), (*jetIter)->subJet2()->p4()),
            deltaR(selLepton_sublead->p4(), (*jetIter)->subJet2()->p4())
          )
         );
        }

      }
    }

    if (genTopPt_CSVsort4rd == genTopPt_semi_boosted_fromAK8)  resolved_and_semi_AK8 = true;

    //std::map<std::string, double> mvaOutput_Hj_tagger;
    std::map<std::string, double> mvaInputs_Hj_tagger;
    double mvaOutput_Hj_tagger = 0.;
    for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin();
          selJet != selJets.end(); ++selJet ) {
      if ((*selJet)->pt()==Wj1_pt_CSVsort4rd_1 || (*selJet)->pt()==Wj2_pt_CSVsort4rd_1 || (*selJet)->pt()==b_pt_CSVsort4rd_1) continue;
      double mvaOutput = comp_mvaOutput_Hj_tagger(
        *selJet, fakeableLeptons, mvaInputs_Hj_tagger, mva_Hj_tagger,
        eventInfo);
      if ( mvaOutput > mvaOutput_Hj_tagger ) mvaOutput_Hj_tagger = mvaOutput;
    }

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Kartik for 2los_1tau category
    const std::map<std::string, double>  mvaInputVariables_2los_1tau_evtLevelSUM_TTH_19Var = {
      { "avg_dr_jet",     comp_avg_dr_jet(selJets) },
      { "dr_lep1_tau_os", deltaR(selLepton_OS -> p4(), selHadTau -> p4())  },
      { "dr_lep2_tau_ss", deltaR(selLepton_SS -> p4(), selHadTau -> p4())  },
      { "dr_leps",        deltaR(selLepton_OS -> p4(), selLepton_SS -> p4()) },
      { "lep2_conePt",    selLepton_sublead->cone_pt()  },
      { "mT_lep1",        comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi())         },
      { "mT_lep2",        comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi())         },
      { "mTauTauVis",    mTauTauVis_sel },
      { "tau_pt",         selHadTau -> pt()   },
      { "tau_eta",        selHadTau -> absEta() },
      { "min_lep_eta",    TMath::Min(selLepton_sublead -> eta(), selLepton_lead -> eta()) },
      { "mindr_lep1_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets))},
      { "mindr_lep2_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets))},
      { "mindr_tau_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)) },
      { "mbb_loose",     selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1.   },
      { "nJet",          selJets.size()     },
      { "res-HTT_2016",  max_mvaOutput_HTT_CSVsort4rd },
      { "HadTop_eta",   std::abs(HadTop_eta_CSVsort4rd) },
      { "HadTop_pt",    HadTop_pt_CSVsort4rd },
    };
    const double mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var = mva_xgb_2los_1tau_evtLevelSUM_TTH_19Var(mvaInputVariables_2los_1tau_evtLevelSUM_TTH_19Var);

   ///--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Kartik for 2los_1tau category
    const std::map<std::string, double>  mvaInputVariables_2los_1tau_evtLevelTT_TTH_20Var = {
      { "avg_dr_jet",     comp_avg_dr_jet(selJets) },
      { "dr_lep1_tau_os", deltaR(selLepton_OS -> p4(), selHadTau -> p4())  },
      { "dr_lep2_tau_ss", deltaR(selLepton_SS -> p4(), selHadTau -> p4())  },
      { "dr_leps",        deltaR(selLepton_OS -> p4(), selLepton_SS -> p4()) },
      { "lep1_conePt",    selLepton_lead->cone_pt()  },//comp_lep1_conePt(*selLepton_lead))
      { "lep2_conePt",    selLepton_sublead->cone_pt()  },
      { "mT_lep1",        comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi())         },
      { "mT_lep2",        comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi())         },
      { "mTauTauVis",    mTauTauVis_sel },
      { "tau_pt",         selHadTau -> pt()   },
      { "tau_eta",        selHadTau -> absEta() },
      { "min_lep_eta",    TMath::Min(selLepton_sublead -> eta(), selLepton_lead -> eta()) },
      { "mindr_lep1_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets))},
      { "mindr_lep2_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets))},
      { "mindr_tau_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)) },
      { "mbb_loose",     selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1.   },
      { "nJet",          selJets.size()     },
      { "res-HTT_2016",  max_mvaOutput_HTT_CSVsort4rd },
      { "HadTop_eta",   std::abs(HadTop_eta_CSVsort4rd) },
      { "HadTop_pt",    HadTop_pt_CSVsort4rd },
    };
    const double mvaOutput_2los_1tau_evtLevelTT_TTH_20Var = mva_xgb_2los_1tau_evtLevelTT_TTH_20Var(mvaInputVariables_2los_1tau_evtLevelTT_TTH_20Var);


    const std::map<std::string, double>  mvaInputVariables_mva_XGB_Updated = {
      { "tau_pt",         selHadTau -> pt()   },
      { "res-HTT_CSVsort4rd",  max_mvaOutput_HTT_CSVsort4rd },
      { "avg_dr_jet",     comp_avg_dr_jet(selJets) },
      { "tau_eta",        selHadTau -> absEta() },
      { "mindr_tau_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)) },
      { "HadTop_pt_CSVsort4rd",    HadTop_pt_CSVsort4rd },
      { "dr_leps",        deltaR(selLepton_OS -> p4(), selLepton_SS -> p4()) },
      { "mbb_loose",     selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1.   },
      { "mTauTauVis",    mTauTauVis_sel },
      { "mindr_lep1_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets))},
      { "nJet",          selJets.size()     },
      { "dr_lep1_tau_os", deltaR(selLepton_OS -> p4(), selHadTau -> p4())  },
      { "mindr_lep2_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets))},
      { "mT_lep2",        comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi())         },
      { "dr_lep2_tau_ss", deltaR(selLepton_SS -> p4(), selHadTau -> p4())  },
      { "lep2_conePt",    selLepton_sublead->cone_pt()  },
      { "min_lep_eta_abs",    TMath::Min(selLepton_sublead -> absEta(), selLepton_lead -> absEta()) },
      {"ptmiss", met.pt()}
    };
    const double mvaOutput_XGB_Updated = mva_XGB_Updated(mvaInputVariables_mva_XGB_Updated);

    const std::map<std::string, double>  mvaInputVariables_mva_XGB_Boosted_AK8 = {
      { "tau_pt",         selHadTau -> pt()   },
      { "res-HTT_CSVsort4rd",  max_mvaOutput_HTT_CSVsort4rd },
      { "avg_dr_jet",     comp_avg_dr_jet(selJets) },
      { "tau_eta",        selHadTau -> absEta() },
      { "mindr_tau_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)) },
      { "HadTop_pt_CSVsort4rd",    HadTop_pt_CSVsort4rd },
      { "dr_leps",        deltaR(selLepton_OS -> p4(), selLepton_SS -> p4()) },
      { "mbb_loose",     selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1.   },
      { "mTauTauVis",    mTauTauVis_sel },
      { "mindr_lep1_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets))},
      { "nJet",          selJets.size()     },
      { "dr_lep1_tau_os", deltaR(selLepton_OS -> p4(), selHadTau -> p4())  },
      { "mindr_lep2_jet", TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets))},
      { "mT_lep2",        comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi())         },
      { "dr_lep2_tau_ss", deltaR(selLepton_SS -> p4(), selHadTau -> p4())  },
      { "lep2_conePt",    selLepton_sublead->cone_pt()  },
      { "min_lep_eta_abs",    TMath::Min(selLepton_sublead -> absEta(), selLepton_lead -> absEta()) },
      {"ptmiss", met.pt()},
      {"resolved_and_boosted", 1.0},
      {"HTT_semi_boosted_fromAK8", HTT_semi_boosted_fromAK8},
      {"minDR_AK8_lep", minDR_AK8_lep},
      {"HTT_boosted", 1.0}
    };
    const double mvaOutput_XGB_Boosted_AK8 = mva_XGB_Boosted_AK8(mvaInputVariables_mva_XGB_Boosted_AK8);

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Arun for 2los_1tau category
    mvaInputs_2los_1tau["lep1_conePt"]            = selLepton_lead->cone_pt();
    mvaInputs_2los_1tau["lep2_conePt"]            = selLepton_sublead->cone_pt();
    mvaInputs_2los_1tau["TMath::Abs(lep1_eta)"]   = selLepton_lead->absEta();
    mvaInputs_2los_1tau["TMath::Abs(lep2_eta)"]   = selLepton_sublead->absEta();
    mvaInputs_2los_1tau["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = TMath::Max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    mvaInputs_2los_1tau["mT_lep1"]                = comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi());
    mvaInputs_2los_1tau["mT_lep2"]                = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
    mvaInputs_2los_1tau["dr_leps"]                = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    mvaInputs_2los_1tau["mindr_lep1_jet"]         = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    mvaInputs_2los_1tau["mindr_lep2_jet"]         = TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets));
    mvaInputs_2los_1tau["dr_lep_tau_os"]          = ( selLepton_OS ) ? deltaR(selLepton_OS->p4(), selHadTau->p4()) : 10.;
    mvaInputs_2los_1tau["dr_lep_tau_ss"]          = ( selLepton_SS ) ? deltaR(selLepton_SS->p4(), selHadTau->p4()) : 10.;
    mvaInputs_2los_1tau["tau_pt"]                 = selHadTau->pt();
    mvaInputs_2los_1tau["TMath::Abs(tau_eta)"]    = selHadTau->absEta();
    mvaInputs_2los_1tau["mindr_tau_jet"]          = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets));
    mvaInputs_2los_1tau["TMath::Min(ptmiss,500)"] = TMath::Min(500., met.pt());
    mvaInputs_2los_1tau["TMath::Min(htmiss,500)"] = TMath::Min(500., mht_p4.pt());
    mvaInputs_2los_1tau["mTauTauVis"]             = mTauTauVis_sel;
    mvaInputs_2los_1tau["avg_dr_jet"]             = comp_avg_dr_jet(selJets);
    mvaInputs_2los_1tau["nJet"]                   = selJets.size();
    mvaInputs_2los_1tau["nBJetLoose"]             = selBJets_loose.size();
    mvaInputs_2los_1tau["nBJetMedium"]            = selBJets_medium.size();
    mvaInputs_2los_1tau["lep1_charge*tau_charge"] = selLepton_lead->charge()*selHadTau->charge();

    check_mvaInputs(mvaInputs_2los_1tau, eventInfo);

    double mvaOutput_2los_1tau_ttV = mva_2los_1tau_ttV(mvaInputs_2los_1tau);
    double mvaOutput_2los_1tau_ttbar = mva_2los_1tau_ttbar(mvaInputs_2los_1tau);
    Double_t mvaDiscr_2los_1tau = getSF_from_TH2(mva_mapping_2los_1tau, mvaOutput_2los_1tau_ttbar, mvaOutput_2los_1tau_ttV) + 1.;

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
    selHistManager->mvaInputVariables_2lss_->fillHistograms(mvaInputs_2lss, evtWeight);
    selHistManager->mvaInputVariables_2los_1tau_->fillHistograms(mvaInputs_2los_1tau, evtWeight);

    std::map<std::string, double> tH_weight_map;
    for(const std::string & evt_cat_str: evt_cat_strs)
    {
      const std::string evt_cat_str_query = evt_cat_str == default_cat_str ? get_tH_SM_str() : evt_cat_str;
      tH_weight_map[evt_cat_str] = isMC_tH ?
        evtWeight / evtWeight_tH_nom * eventInfo.genWeight_tH(evt_cat_str_query):
        evtWeight
      ;
    }
    for(const auto & kv: tH_weight_map)
    {
      selHistManager->evt_[kv.first]->fillHistograms(
        selElectrons.size(), selMuons.size(), selHadTaus.size(),
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, mvaOutput_2los_1tau_ttV, mvaOutput_2los_1tau_ttbar, mvaDiscr_2los_1tau,
        mTauTauVis_sel,
        mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var,mvaOutput_2los_1tau_evtLevelTT_TTH_20Var,
        mvaOutput_XGB_Updated, mvaOutput_XGB_Boosted_AK8,
        kv.second
      );
    }
    if(isSignal)
    {
      const std::string decayModeStr = eventInfo.getDecayModeString();
      if ( ( isMC_tH || isMC_VH ) && ( decayModeStr == "hzg" || decayModeStr == "hmm" ) ) continue;
      if(! decayModeStr.empty())
      {
        for(const auto & kv: tH_weight_map)
        {
          selHistManager -> evt_in_decayModes_[kv.first][decayModeStr] -> fillHistograms(
            selElectrons.size(),
            selMuons.size(),
            selHadTaus.size(),
            selJets.size(),
            selBJets_loose.size(),
            selBJets_medium.size(),
            mvaOutput_2lss_ttV,
            mvaOutput_2lss_ttbar,
            mvaDiscr_2lss,
            mvaOutput_2los_1tau_ttV,
            mvaOutput_2los_1tau_ttbar,
            mvaDiscr_2los_1tau,
            mTauTauVis_sel,
            mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var,
            mvaOutput_2los_1tau_evtLevelTT_TTH_20Var,
            mvaOutput_XGB_Updated, mvaOutput_XGB_Boosted_AK8,
            kv.second
          );
        }
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

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.str() << '\n';
    }

    const bool isGenMatched = isMC &&
      contains(syncNtuple_genMatch, selLepton_genMatch.name_ + "&" + selHadTau_genMatch.name_)
    ;

    if ( bdt_filler ) {
      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("lep1_pt",              selLepton_lead -> pt())
          ("lep1_conePt",          comp_lep1_conePt(*selLepton_lead))
          ("lep1_eta",             selLepton_lead -> eta())
          ("lep1_tth_mva",         selLepton_lead -> mvaRawTTH())
          ("mindr_lep1_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets)))
          ("max_lep_eta",          TMath::Max(selLepton_sublead -> eta(), selLepton_lead -> eta()))
          ("min_lep_eta",          TMath::Min(selLepton_sublead -> eta(), selLepton_lead -> eta()))
          ("mT_lep1",              comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi()))
          ("dr_lep1_tau_os",       deltaR(selLepton_OS -> p4(), selHadTau -> p4()))
          ("dr_leps",              deltaR(selLepton_OS -> p4(), selLepton_SS -> p4()))
          ("lep2_pt",              selLepton_sublead -> pt())
          ("lep2_conePt",          comp_lep1_conePt(*selLepton_sublead))
          ("lep2_eta",             selLepton_sublead -> eta())
          ("lep2_tth_mva",         selLepton_sublead -> mvaRawTTH())
          ("mindr_lep2_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets)))
          ("mT_lep2",              comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi()))
          ("dr_lep2_tau_ss",       deltaR(selLepton_SS -> p4(), selHadTau -> p4()))
          ("mindr_tau_jet",        TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)))
          ("avg_dr_jet",           comp_avg_dr_jet(selJets))
          ("ptmiss",               met.pt())
          ("htmiss",               mht_p4.pt())
          ("tau_mva",              selHadTau -> raw_mva())
          ("tau_pt",               selHadTau -> pt())
          ("tau_eta",              selHadTau -> eta())
          ("hadtruth",               hadtruth)
          ("bWj1Wj2_isGenMatched_CSVsort4rd",              max_truth_HTT_CSVsort4rd)
          ("res-HTT_CSVsort4rd",   max_mvaOutput_HTT_CSVsort4rd)
          ("HadTop_pt_CSVsort4rd", HadTop_pt_CSVsort4rd)
          ("genTopPt_CSVsort4rd",  genTopPt_CSVsort4rd)
          ("dr_leps",              deltaR(selLepton_lead -> p4(), selLepton_sublead -> p4()))
          ("mTauTauVis" ,          mTauTauVis_sel)
          ("lep1_genLepPt",        ( selLepton_lead->genLepton() != 0 ) ? selLepton_lead->genLepton()->pt() : 0.)
          ("lep2_genLepPt",        ( selLepton_sublead->genLepton() != 0 ) ? selLepton_sublead->genLepton()->pt() : 0.)
          ("tau_genTauPt",         ( selHadTau->genHadTau() != 0 ) ? selHadTau->genHadTau()->pt() : 0.)
          ("lep1_fake_prob",       ( selLepton_lead->genLepton() != 0 ) ? 1.0 : prob_fake_lepton_lead )
          ("lep2_fake_prob",       ( selLepton_sublead->genLepton() != 0 ) ? 1.0 : prob_fake_lepton_sublead)
          ("tau_fake_prob",        ( selHadTau->genHadTau() != 0 || selHadTau->genLepton() != 0 ) ? 1.0 : prob_fake_hadTau )
          ("genWeight",            eventInfo.genWeight)
          ("evtWeight",            evtWeight)
          ("nJet",                 selJets.size())
          ("nBJetLoose",           selBJets_loose.size())
          ("nBJetMedium",          selBJets_medium.size())
          ("nLep",                 selLeptons.size())
          ("nTau",                 selHadTaus.size())
          ("lep1_isTight",         int(selLepton_lead -> isTight()))
          ("lep1_charge",          selLepton_lead -> charge())
          ("lep1_tau_charge",      selLepton_lead -> charge()+selHadTau -> charge())
          ("lep2_isTight",         int(selLepton_sublead -> isTight()))
          ("lep2_charge",          selLepton_sublead -> charge())
          ("tau_isTight",          int(tightHadTauFilter(*selHadTau)))
          ("tau_charge",           selHadTau -> charge())
          ("mbb",                  selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : -1.  )
          ("ptbb",                 selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).pt() : -1.  )
          ("b1_pt",                selBJets_medium.size()>0 ?  selBJets_medium[0]->pt() : -1. )
          ("b2_pt",                selBJets_medium.size()>1 ?  selBJets_medium[1]->pt() : -1. )
          ("drbb",                 selBJets_medium.size()>1 ? deltaR(selBJets_medium[0]->p4(), selBJets_medium[1]->p4()) : -1. )
          ("detabb",               selBJets_medium.size()>1 ? TMath::Abs(selBJets_medium[0]->eta() - selBJets_medium[1]->eta()) : -1. )
          ("mbb_loose",            selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1.  )
          ("ptbb_loose",           selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).pt() : -1.  )
          ("b1_loose_pt",          selBJets_loose.size()>0 ?  selBJets_loose[0]->pt() : -1. )
          ("b2_loose_pt",          selBJets_loose.size()>1 ?  selBJets_loose[1]->pt() : -1. )
          ("drbb_loose",           selBJets_loose.size()>1 ? deltaR(selBJets_loose[0]->p4(), selBJets_loose[1]->p4()) : -1. )
          ("detabb_loose",         selBJets_loose.size()>1 ? TMath::Abs(selBJets_loose[0]->eta() - selBJets_loose[1]->eta()) : -1. )

          ("HTT_semi_boosted_fromAK8",                     HTT_semi_boosted_fromAK8)
          ("bWj1Wj2_isGenMatched_semi_boosted_fromAK8",    bWj1Wj2_isGenMatched_semi_boosted_fromAK8)
          ("genTopPt_semi_boosted_fromAK8",            genTopPt_semi_boosted_fromAK8)
          ("HadTop_pt_semi_boosted_fromAK8",           HadTop_pt_semi_boosted_fromAK8)

          ("N_jetAK8",     jet_ptrsAK8.size())
          ("W_pt_semi_boosted_fromAK8",           W_pt_semi_boosted_fromAK8)
          ("b_pt_semi_boosted_fromAK8",           b_pt_semi_boosted_fromAK8)
          ("minDR_AK8_lep",                minDR_AK8_lep)
          ("resolved_and_semi_AK8",     resolved_and_semi_AK8)

          ("hadtruth_semi_boosted_fromAK8", hadtruth_semi_boosted_fromAK8)
          ("cleanedJets_fromAK8",       cleanedJets_fromAK8.size())
          ("minDR_AK8subjets_lep",         minDR_AK8subjets_lep)
        .fill()
      ;
    }

    if(snm)
    {
      const double dr_lep1_tau1    = deltaR(selLepton_lead->p4(), selHadTau->p4());
      const double dr_lep2_tau1    = deltaR(selLepton_sublead->p4(), selHadTau->p4());
      const double max_dr_jet      = comp_max_dr_jet(selJets);
      const double mbb_loose       = selBJets_loose.size() > 1 ? (selBJets_loose[0]->p4() + selBJets_loose[1]->p4()).mass() : -1.;
      const double avr_dr_lep_tau  = (dr_lep1_tau1 + dr_lep2_tau1) / 2;
      const double max_dr_lep_tau  = std::max(dr_lep2_tau1, dr_lep1_tau1);
      const double min_dr_lep_tau  = std::min(dr_lep2_tau1, dr_lep1_tau1);
      const double mindr_lep1_jet  = comp_mindr_lep1_jet(*selLepton_lead, selJets);
      const double mindr_lep2_jet  = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
      const double min_dr_lep_jet  = std::min(mindr_lep1_jet, mindr_lep2_jet);
      const double mindr_tau_jet   = comp_mindr_hadTau1_jet(*selHadTau, selJets);
      const double avg_dr_jet      = comp_avg_dr_jet(selJets);
      const double dr_leps         = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
      const double max_lep_eta     = std::max(selLepton_lead->absEta(), selLepton_sublead->absEta());
      const double mT_lep1         = comp_MT_met_lep1(*selLepton_lead,    met.pt(), met.phi());
      const double mT_lep2         = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
      const double mTauTauVis1_sel = (selLepton_lead->p4() + selHadTau->p4()).mass();
      const double mTauTauVis2_sel = (selLepton_sublead->p4() + selHadTau->p4()).mass();
      const double mbb             = selBJets_medium.size() > 1 ?  (selBJets_medium[0]->p4() + selBJets_medium[1]->p4()).mass() : -1000;
      const int nLightJet          = selJets.size() - selBJets_loose.size() + selJetsForward.size();

      snm->read(eventInfo);
      snm->read(selLeptons);
      snm->read(preselMuons,     fakeableMuons,     tightMuons);
      snm->read(preselElectrons, fakeableElectrons, tightElectrons);
      snm->read(fakeableHadTaus);
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
      snm->read(max_mvaOutput_HTT_CSVsort4rd,           FloatVariableType::HTT);
      snm->read(HadTop_pt_CSVsort4rd,                   FloatVariableType::HadTop_pt);
      snm->read(mvaOutput_Hj_tagger,                    FloatVariableType::Hj_tagger);

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

      // mvaOutput_3l_ttV not filled
      // mvaOutput_3l_ttbar not filled
      // mvaOutput_plainKin_SUM_M not filled
      // mvaOutput_plainKin_1B_M not filled

      snm->read(weight_fakeRate,                        FloatVariableType::FR_weight);
      snm->read(triggerWeight,                          FloatVariableType::triggerSF_weight);
      snm->read(leptonSF_weight,                        FloatVariableType::leptonSF_weight);
      snm->read(tauSF_weight,                           FloatVariableType::tauSF_weight);
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

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  std::cout << "sel. Entries by gen. matching:" << std::endl;
  for ( std::vector<leptonGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

      int idxLepton = leptonGenMatch_definition->idx_;
      int idxHadTau = hadTauGenMatch_definition->idx_;

      const TH1* histogram_EventCounter = selHistManagers[idxLepton][idxHadTau]->evt_[default_cat_str]->getHistogram_EventCounter();
      std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries() << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
    }
  }
  std::cout << std::endl;

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
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete l1PreFiringWeightReader;
  delete cutFlowHistManager;
  delete eventWeightManager;

  delete inputTree;
  delete snm;

  clock.Show("analyze_2los_1tau");

  return EXIT_SUCCESS;
}
