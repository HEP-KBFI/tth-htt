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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
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
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_2lss_1tau.h" // MEMOutputReader_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorCutBased.h" // RecoMuonCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h" // EvtHistManager_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton, kFR_3L, kFR_1tau };

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
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
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2017" ) era = kEra_2017;
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

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
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";

  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  std::cout << "leptonSelection_string = " << leptonSelection_string << std::endl;
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_2lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;
  bool apply_leptonGenMatching_ttZ_workaround = cfg_analyze.getParameter<bool>("apply_leptonGenMatching_ttZ_workaround");
  std::cout << "apply_leptonGenMatching_ttZ_workaround = " << apply_leptonGenMatching_ttZ_workaround << std::endl;

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
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_1tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS" ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS" ) chargeSumSelection = kSS;
  else throw cms::Exception("analyze_2lss_1tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId");
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool apply_lepton_and_hadTauCharge_cut = cfg_analyze.getParameter<bool>("apply_lepton_and_hadTauCharge_cut");
  std::cout << "apply_lepton_and_hadTauCharge_cut = " << apply_lepton_and_hadTauCharge_cut << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits");
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");

  bool isDEBUG = ( cfg_analyze.exists("isDEBUG") ) ? cfg_analyze.getParameter<bool>("isDEBUG") : false;
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  int jetPt_option = RecoJetReader::kJetPt_central;
  int jetToLeptonFakeRate_option = kFRl_central;
  int met_option = RecoMEtReader::kMEt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  int lheScale_option = kLHE_scale_central;
  int jetBtagSF_option = kBtag_central;
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_2lss_1tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      if ( isMC ) jetBtagSF_option = getBTagWeight_option(central_or_shift);
      else throw cms::Exception("analyze_2lss_1tau")
        << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      if ( isMC ) {
        jetBtagSF_option = getBTagWeight_option(central_or_shift);
        if      ( shiftUp_or_Down == "Up"   ) {
          jetPt_option = RecoJetReader::kJetPt_jecUp;
          met_option = RecoMEtReader::kMEt_shifted_JetEnUp;
        } else if ( shiftUp_or_Down == "Down" ) {
          jetPt_option = RecoJetReader::kJetPt_jecDown;
          met_option = RecoMEtReader::kMEt_shifted_JetEnDown;
        } else assert(0);
      } else throw cms::Exception("analyze_2lss_1tau")
          << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JER") ) {
      if ( central_or_shift_tstring.EndsWith("Up") ) met_option = RecoMEtReader::kMEt_shifted_JetResUp;
      else if ( central_or_shift_tstring.EndsWith("Down") ) met_option = RecoMEtReader::kMEt_shifted_JetResDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_UnclusteredEn") ) {
      if ( central_or_shift_tstring.EndsWith("Up") ) met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnUp;
      else if ( central_or_shift_tstring.EndsWith("Down") ) met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRe_shape") ||
                central_or_shift_tstring.BeginsWith("CMS_ttHl_FRm_shape") ) {
      if      ( central_or_shift_tstring.EndsWith("e_shape_ptUp")           ) jetToLeptonFakeRate_option = kFRe_shape_ptUp;
      else if ( central_or_shift_tstring.EndsWith("e_shape_ptDown")         ) jetToLeptonFakeRate_option = kFRe_shape_ptDown;
      else if ( central_or_shift_tstring.EndsWith("e_shape_etaUp")          ) jetToLeptonFakeRate_option = kFRe_shape_etaUp;
      else if ( central_or_shift_tstring.EndsWith("e_shape_etaDown")        ) jetToLeptonFakeRate_option = kFRe_shape_etaDown;
      else if ( central_or_shift_tstring.EndsWith("e_shape_eta_barrelUp")   ) jetToLeptonFakeRate_option = kFRe_shape_eta_barrelUp;
      else if ( central_or_shift_tstring.EndsWith("e_shape_eta_barrelDown") ) jetToLeptonFakeRate_option = kFRe_shape_eta_barrelDown;
      else if ( central_or_shift_tstring.EndsWith("m_shape_ptUp")           ) jetToLeptonFakeRate_option = kFRm_shape_ptUp;
      else if ( central_or_shift_tstring.EndsWith("m_shape_ptDown")         ) jetToLeptonFakeRate_option = kFRm_shape_ptDown;
      else if ( central_or_shift_tstring.EndsWith("m_shape_etaUp")          ) jetToLeptonFakeRate_option = kFRm_shape_etaUp;
      else if ( central_or_shift_tstring.EndsWith("m_shape_etaDown")        ) jetToLeptonFakeRate_option = kFRm_shape_etaDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if ( isMC ) {
        if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
        else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
        else assert(0);
      } else throw cms::Exception("analyze_2lss_1tau")
          << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRjt") ) {
      if      ( central_or_shift_tstring.EndsWith("normUp")    ) jetToTauFakeRate_option = kFRjt_normUp;
      else if ( central_or_shift_tstring.EndsWith("normDown")  ) jetToTauFakeRate_option = kFRjt_normDown;
      else if ( central_or_shift_tstring.EndsWith("shapeUp")   ) jetToTauFakeRate_option = kFRjt_shapeUp;
      else if ( central_or_shift_tstring.EndsWith("shapeDown") ) jetToTauFakeRate_option = kFRjt_shapeDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_thu_shape") ) {
      if ( isMC ) {
        if      ( central_or_shift_tstring.EndsWith("x1Down") ) lheScale_option = kLHE_scale_xDown;
        else if ( central_or_shift_tstring.EndsWith("x1Up")   ) lheScale_option = kLHE_scale_xUp;
        else if ( central_or_shift_tstring.EndsWith("y1Down") ) lheScale_option = kLHE_scale_yDown;
        else if ( central_or_shift_tstring.EndsWith("y1Up")   ) lheScale_option = kLHE_scale_yUp;
        else assert(0);
      } else throw cms::Exception("analyze_2lss_1tau")
          << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( !(central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") ||
                  central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt")) ) {
      throw cms::Exception("analyze_2lss_1tau")
        << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    }
  }

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

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
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L || applyFakeRateWeights == kFR_1tau || apply_hadTauFakeRateSF ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }
  std::cout << "Applying jetToTauFakeRate fake rate weights = " << applyFakeRateWeights_string << " (" << applyFakeRateWeights << ")\n";

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");
  std::string branchName_memOutput = cfg_analyze.getParameter<std::string>("branchName_memOutput");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  std::string branchName_genLeptons2 = cfg_analyze.getParameter<std::string>("branchName_genLeptons2");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;

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
  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const std::string syncNtuple_tree = syncNtuple_cfg.getParameter<std::string>("tree");
  const std::string syncNtuple_output = syncNtuple_cfg.getParameter<std::string>("output");
  if(! syncNtuple_tree.empty() && ! syncNtuple_output.empty())
  {
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
    snm->initializeBranches();
    snm->initializeHLTBranches({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
  }

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  for ( const std::vector<hltPath*> hltPaths: { triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu } ) {
    inputTree -> registerReader(hltPaths);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  muonReader->set_HIP_mitigation(use_HIP_mitigation_mediumMuonId);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorCutBased cutBasedMuonSelector(era); // needed for sync
  RecoMuonCollectionSelectorMVABased mvaBasedMuonSelector(era); // needed for sync
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorCutBased cutBasedElectronSelector(era); // needed for sync
  RecoElectronCollectionSelectorMVABased mvaBasedElectronSelector(era); // needed for sync
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauSelectorTight tightHadTauFilter(era);
  tightHadTauFilter.set("dR03mvaMedium");
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

//--- declare likelihoods for signal/background hypotheses, obtained by matrix element method
  MEMOutputReader_2lss_1tau* memReader = 0;
  if ( branchName_memOutput != "" ) {
    memReader = new MEMOutputReader_2lss_1tau(Form("n%s", branchName_memOutput.data()), branchName_memOutput);
    inputTree -> registerReader(memReader);
  }

  // declaring bin mappings
  std::string inputFileName_mem_mapping = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_MEM_mapping_likelihood.root";
  TFile* inputFile_mem_mapping = openFile(LocalFileInPath(inputFileName_mem_mapping));
  TH2* mem_mapping = loadTH2(inputFile_mem_mapping, "hTargetBinning");

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
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
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader();
    inputTree -> registerReader(lheInfoReader);
  }

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);

  if ( isMC ) {
          inputTree -> registerReader(genTopQuarkReader);
          inputTree -> registerReader(genBJetReader);
          inputTree -> registerReader(genWBosonReader);
          inputTree -> registerReader(genWJetReader);
  }

  double evtWeightSum=0; // to devbug
  //--- initialize hadronic top tagger BDT
  //std::string mvaFileName_hadTopTagger = "tthAnalysis/HiggsToTauTau/data/hadTopTagger_BDTG_2017Oct10_opt2.xml";
  std::string mvaFileName_hadTopTaggerWithKinFit = "tthAnalysis/HiggsToTauTau/data/all_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_1000_deph_3_lr_0o01_CSV_sort_withKinFit.pkl";
  std::string mvaFileName_hadTopTaggerNoKinFit = "tthAnalysis/HiggsToTauTau/data/all_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_1000_deph_3_lr_0o01_CSV_sort.pkl";
  std::string mvaFileName_hadTopTagger = "tthAnalysis/HiggsToTauTau/data/all_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_1000_deph_3_lr_0o01_CSV_sort.pkl";
  std::string mvaFileName_hadTopTagger_tmva = "tthAnalysis/HiggsToTauTau/data/1l_2tau_HadTopTagger_BDT.weights.xml";
  HadTopTagger* hadTopTagger = new HadTopTagger(
          mvaFileName_hadTopTaggerWithKinFit,
          mvaFileName_hadTopTaggerNoKinFit,
          mvaFileName_hadTopTagger_tmva);

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
  // the same vector will be used to XGB training

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

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

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
    EvtHistManager_2lss_1tau* evt_;
  };
  typedef std::map<int, preselHistManagerType*> int_to_preselHistManagerMap;
  std::map<int, int_to_preselHistManagerMap> preselHistManagers;
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    ElectronHistManager* leadElectron_;
    ElectronHistManager* subleadElectron_;
    MuonHistManager* muons_;
    MuonHistManager* leadMuon_;
    MuonHistManager* subleadMuon_;
    HadTauHistManager* hadTaus_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MVAInputVarHistManager* mvaInputVariables_2lss_;
    MVAInputVarHistManager* mvaInputVariables_2lss_1tau_;
    EvtHistManager_2lss_1tau* evt_;
    std::map<std::string, EvtHistManager_2lss_1tau*> evt_in_decayModes_;
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

      preselHistManagerType* preselHistManager = new preselHistManagerType();
      preselHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/presel/electrons", histogramDir.data()), central_or_shift));
      preselHistManager->electrons_->bookHistograms(fs);
      preselHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
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
      preselHistManager->evt_ = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_and_genMatch,
        Form("%s/presel/evt", histogramDir.data()), era_string, central_or_shift));
      preselHistManager->evt_->bookHistograms(fs);
      preselHistManagers[idxLepton][idxHadTau] = preselHistManager;

      selHistManagerType* selHistManager = new selHistManagerType();
      //selHistManager->evt_->LoadMaps(nstart, ntarget);
      selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
      selHistManager->electrons_->bookHistograms(fs);
      selHistManager->leadElectron_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadElectron", histogramDir.data()), central_or_shift, 0));
      selHistManager->leadElectron_->bookHistograms(fs);
      selHistManager->subleadElectron_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadElectron", histogramDir.data()), central_or_shift, 1));
      selHistManager->subleadElectron_->bookHistograms(fs);
      selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/muons", histogramDir.data()), central_or_shift));
      selHistManager->muons_->bookHistograms(fs);
      selHistManager->leadMuon_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadMuon", histogramDir.data()), central_or_shift, 0));
      selHistManager->leadMuon_->bookHistograms(fs);
      selHistManager->subleadMuon_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadMuon", histogramDir.data()), central_or_shift, 1));
      selHistManager->subleadMuon_->bookHistograms(fs);
      selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
      selHistManager->hadTaus_->bookHistograms(fs);
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
      selHistManager->mvaInputVariables_2lss_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/mvaInputs_2lss", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_2lss_->bookHistograms(fs, mvaInputVariables_2lss);
      selHistManager->mvaInputVariables_2lss_1tau_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/mvaInputs_2lss_1tau", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_2lss_1tau_->bookHistograms(fs, mvaInputVariables_2lss_1tau);
      selHistManager->evt_ = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
      selHistManager->evt_->bookHistograms(fs);

      const vstring decayModes_evt = eventInfo.getDecayModes();
      if(isSignal)
      {
        for(const std::string & decayMode_evt: decayModes_evt)
        {
          std::string decayMode_and_genMatch = decayMode_evt;
          if(apply_leptonGenMatching)                            decayMode_and_genMatch += leptonGenMatch_definition -> name_;
          if(apply_leptonGenMatching && apply_hadTauGenMatching) decayMode_and_genMatch += "&";
          if(apply_hadTauGenMatching)                            decayMode_and_genMatch += hadTauGenMatch_definition -> name_;

          selHistManager -> evt_in_decayModes_[decayMode_evt] = new EvtHistManager_2lss_1tau(makeHistManager_cfg(
            decayMode_and_genMatch,
            Form("%s/sel/evt", histogramDir.data()),
            era_string,
            central_or_shift
          ));
          selHistManager -> evt_in_decayModes_[decayMode_evt] -> bookHistograms(fs);
        }
      }
      selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/weights", histogramDir.data()), central_or_shift));
      selHistManager->weights_->bookHistograms(fs, { "genWeight", "pileupWeight", "triggerWeight", "data_to_MC_correction", "fakeRate" });
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
  }

  std::cout << "Book BDT filling" << std::endl;
  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;

  NtupleFillerBDT<float, int>* bdt_filler_gen = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler_gen)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler_gen)>::type::int_type   int_type;

  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), central_or_shift)
    );
    bdt_filler->register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_tth_mva", "mindr_lep1_jet",
      "mindr_lep2_jet", "mT_lep1",  "MT_met_lep1", "dr_lep1_tau",
      "lep2_pt", "lep2_conePt", "lep2_eta", "max_lep_eta", "avg_dr_lep",
      "lep2_tth_mva", "mT_lep2", "dr_lep2_tau",
      "mindr_tau_jet", "avg_dr_jet",  "nJet25_Recl", "ptmiss", "htmiss",
      "tau_mva", "tau_pt", "tau_eta", "dr_leps",
      "mTauTauVis1", "mTauTauVis2",
      "memOutput_isValid",   "memOutput_errorFlag",  "memOutput_LR",  "memOutput_tt_LR", "memOutput_ttZ_LR",
      "memOutput_tt_LR",  "memOutput_ttZ_LR", "memOutput_ttZ_Zll_LR",
      "log_memOutput_ttH",  "log_memOutput_ttZ",  "log_memOutput_ttZ_Zll", "log_memOutput_tt",
      "lep1_genLepPt", "lep2_genLepPt",
      "tau_genTauPt",  "lep1_frWeight", "lep2_frWeight",   "tau_frWeight",
      "mvaOutput_2lss_ttV",  "mvaOutput_2lss_ttbar", "mvaDiscr_2lss",
      "mvaOutput_Hj_tagger", "mvaOutput_Hjj_tagger",
      "fittedHadTop_pt", "fittedHadTop_eta", "unfittedHadTop_pt",
      "unfittedHadTop_eta","fitHTptoHTpt" , "fitHTptoHTmass",
      "dr_lep1_HTfitted", "dr_lep2_HTfitted", "dr_tau_HTfitted", "mass_lep1_HTfitted", "mass_lep2_HTfitted",  "dr_lep1_HTunfitted", "dr_lep2_HTunfitted", "dr_tau_HTunfitted",
      "mvaOutput_2lss_1tau_ttbar", "mvaOutput_2lss_1tau_ttV", "mvaDiscr_2lss_1tau", "oldVar_from20_to_12", "oldVar_from20_to_7",
      "mvaOutput_2lss_1tau_ttV_wMEM", "mvaOutput_2lss_1tau_ttbar_wMEM",
      "lumiScale", "genWeight", "evtWeight",
      "mvaOutput_hadTopTaggerWithKinFit", "mvaOutput_hadTopTagger",
      "bWj1Wj2_isGenMatched", "bWj1Wj2_isGenMatchedWithKinFit",
      "HadTop_pt", "HadTop_eta","ncombo","genTopPt","min(met_pt,400)","hadtruth",
      "mbb","ptbb", "mbb_loose","ptbb_loose"
      // lep1_isTight, lep2_isTight, nBJetLoose, nBJetMedium, nJet, tau_isTight
    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "nLep","nTau",
      "lep1_isTight", "lep2_isTight", "tau_isTight","failsTightChargeCut",
      "run","evt","lumi"
    );
    bdt_filler->bookTree(fs);
    ///////////////////////////////////////
    bdt_filler_gen = new std::remove_pointer<decltype(bdt_filler_gen)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntupleGen", histogramDir.data()), central_or_shift)
    );
    bdt_filler_gen -> register_variable<float_type>(
      "genPtTop",  "genPtTopB",  "genPtTopW",  "genPtTopWj1",  "genPtTopWj2",
      "genEtaTop",  "genEtaTopB",  "genEtaTopW",  "genEtaTopWj1",  "genEtaTopWj2",
      "genPhiTopB",  "genPhiTopWj1",  "genPhiTopWj2",
      "genMTopB",  "genMTopWj1",  "genMTopWj2",
      "genPtAntiTop",  "genPtAntiTopB",  "genPtAntiTopW",  "genPtAntiTopWj1",  "genPtAntiTopWj2",
      "genEtaAntiTop",  "genEtaAntiTopB",  "genEtaAntiTopW",  "genEtaAntiTopWj1",  "genEtaAntiTopWj2",
      "genPhiAntiTopB",  "genPhiAntiTopWj1",  "genPhiAntiTopWj2",
      "genMAntiTopB",  "genMAntiTopWj1",  "genMAntiTopWj2"
    );
    bdt_filler_gen -> register_variable<int_type>(
      "gencount","gencountHad","passtrigger","run","evt","lumi"
    );
    bdt_filler_gen -> bookTree(fs);

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
    ">= 2 presel leptons",
    "presel lepton trigger match",
    ">= 2 jets",
    ">= 2 loose b-jets || 1 medium b-jet (1)",
    ">= 1 sel tau (1)",
    ">= 2 sel leptons",
    "<= 2 tight leptons",
    "sel lepton trigger match",
    ">= 3 jets",
    ">= 2 loose b-jets || 1 medium b-jet (2)",
    ">= 1 sel tau (2)",
    "m(ll) > 12 GeV",
    "lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV",
    "tight lepton charge",
    "sel lepton-pair OS/SS charge",
    "sel lepton+tau charge",
    "Z-boson mass veto",
    "met LD > 0.2",
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

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
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
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;

    //--- build collections of generator level particles
    //std::cout << "built gen variable" << std::endl;
    std::vector<GenParticle> genTopQuarks;
    std::vector<GenParticle> genBJets;
    std::vector<GenParticle> genWBosons;
    std::vector<GenParticle> genWJets;
    int gencount = 0;
    int gencountHad = 0;
    double genPtTop = -1;
    double genPtTopB = -1;
    double genPtTopW = -1;
    double genPtTopWj1 = -1;
    double genPtTopWj2 = -1;
    double genEtaTop = -100;
    double genEtaTopB = -100;
    double genEtaTopW = -100;
    double genEtaTopWj1 = -100;
    double genEtaTopWj2 = -100;
    double genPhiTopB = -100;
    double genPhiTopWj1 = -100;
    double genPhiTopWj2 = -100;
    double genMTopB = -100;
    double genMTopWj1 = -100;
    double genMTopWj2 = -100;

    double genPtAntiTop = -1;
    double genPtAntiTopB = -1;
    double genPtAntiTopW = -1;
    double genPtAntiTopWj1 = -1;
    double genPtAntiTopWj2 = -1;
    double genEtaAntiTop = -1;
    double genEtaAntiTopB = -1;
    double genEtaAntiTopW = -1;
    double genEtaAntiTopWj1 = -1;
    double genEtaAntiTopWj2 = -1;
    double genPhiAntiTopB = -100;
    double genPhiAntiTopWj1 = -100;
    double genPhiAntiTopWj2 = -100;
    double genMAntiTopB = -100;
    double genMAntiTopWj1 = -100;
    double genMAntiTopWj2 = -100;

    if ( isMC ) {
      genTopQuarks = genTopQuarkReader->read();
      genBJets = genBJetReader->read();
      genWBosons = genWBosonReader->read();
      genWJets = genWJetReader->read();
      std::map<int, double> genMatchingTopVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenTop);
      std::map<int, double> genMatchingAntiTopVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop);
      genPtTop = genMatchingTopVar[kGenPtTop];
      genPtTopB = genMatchingTopVar[kGenPtTopB];
      genPtTopW = genMatchingTopVar[kGenPtTopW];
      genPtTopWj1 = genMatchingTopVar[kGenPtTopWj1];
      genPtTopWj2 = genMatchingTopVar[kGenPtTopWj2];
      genEtaTop = genMatchingTopVar[kGenEtaTop];
      genEtaTopB = genMatchingTopVar[kGenEtaTopB];
      genEtaTopW = genMatchingTopVar[kGenEtaTopW];
      genEtaTopWj1 = genMatchingTopVar[kGenEtaTopWj1];
      genEtaTopWj2 = genMatchingTopVar[kGenEtaTopWj2];
      genPhiTopB = genMatchingTopVar[kGenPhiTopB];
      genPhiTopWj1 = genMatchingTopVar[kGenPhiTopWj1];
      genPhiTopWj2 = genMatchingTopVar[kGenPhiTopWj2];
      genMTopB = genMatchingTopVar[kGenMTopB];
      genMTopWj1 = genMatchingTopVar[kGenMTopWj1];
      genMTopWj2 = genMatchingTopVar[kGenMTopWj2];

      genPtAntiTop = genMatchingAntiTopVar[kGenPtTop];
      genPtAntiTopB = genMatchingAntiTopVar[kGenPtTopB];
      genPtAntiTopW = genMatchingAntiTopVar[kGenPtTopW];
      genPtAntiTopWj1 = genMatchingAntiTopVar[kGenPtTopWj1];
      genPtAntiTopWj2 = genMatchingAntiTopVar[kGenPtTopWj2];
      genEtaAntiTop = genMatchingAntiTopVar[kGenEtaTop];
      genEtaAntiTopB = genMatchingAntiTopVar[kGenEtaTopB];
      genEtaAntiTopW = genMatchingAntiTopVar[kGenEtaTopW];
      genEtaAntiTopWj1 = genMatchingAntiTopVar[kGenEtaTopWj1];
      genEtaAntiTopWj2 = genMatchingAntiTopVar[kGenEtaTopWj2];
      genPhiAntiTopB = genMatchingAntiTopVar[kGenPhiTopB];
      genPhiAntiTopWj1 = genMatchingAntiTopVar[kGenPhiTopWj1];
      genPhiAntiTopWj2 = genMatchingAntiTopVar[kGenPhiTopWj2];
      genMAntiTopB = genMatchingAntiTopVar[kGenMTopB];
      genMAntiTopWj1 = genMatchingAntiTopVar[kGenMTopWj1];
      genMAntiTopWj2 = genMatchingAntiTopVar[kGenMTopWj2];
      if (genPtTop>0 && genPtAntiTop>0) gencount = 2;
      else if (genPtTop>0 || genPtAntiTop>0) gencount = 1;
      if (genMTopWj1>0 && genMAntiTopWj1>0) gencountHad = 2;
      else if (genMTopWj1>0 || genMAntiTopWj1>0) gencountHad = 1;
    }
    if ( bdt_filler_gen ) {
      bdt_filler_gen -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("genPtTop",        genPtTop)
          ("genPtTopB",       genPtTopB)
          ("genPtTopW",       genPtTopW)
          ("genPtTopWj1",     genPtTopWj1)
          ("genPtTopWj2",     genPtTopWj2)
          ("genEtaTop",       genEtaTop)
          ("genEtaTopB",      genEtaTopB)
          ("genEtaTopW",      genEtaTopW)
          ("genEtaTopWj1",    genEtaTopWj1)
          ("genEtaTopWj2",    genEtaTopWj2)
          ("genPhiTopB",      genPhiTopB)
          ("genPhiTopWj1",    genPhiTopWj1)
          ("genPhiTopWj2",    genPhiTopWj2)
          ("genMTopB",        genMTopB)
          ("genMTopWj1",      genMTopWj1)
          ("genMTopWj2",      genMTopWj2)
          ("genPtAntiTop",    genPtAntiTop)
          ("genPtAntiTopB",   genPtAntiTopB)
          ("genPtAntiTopW",   genPtAntiTopW)
          ("genPtAntiTopWj1", genPtAntiTopWj1)
          ("genPtAntiTopWj2", genPtAntiTopWj2)
          ("genEtaAntiTop",   genEtaAntiTop)
          ("genEtaAntiTopB",  genEtaAntiTopB)
          ("genEtaAntiTopW",  genEtaAntiTopW)
          ("genEtaAntiTopWj1", genEtaAntiTopWj1)
          ("genEtaAntiTopWj2", genEtaAntiTopWj2)
          ("genPhiAntiTopB",   genPhiAntiTopB)
          ("genPhiAntiTopWj1", genPhiAntiTopWj1)
          ("genPhiAntiTopWj2", genPhiAntiTopWj2)
          ("genMAntiTopB",     genMAntiTopB)
          ("genMAntiTopWj1",   genMAntiTopWj1)
          ("genMAntiTopWj2",   genMAntiTopWj2)
          ("gencount",         gencount)
          ("gencountHad",      gencountHad)
          ("passtrigger",      (selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu))
          ("run", eventInfo.run)
          ("lumi", eventInfo.lumi)
          ("evt", eventInfo.event)
        .fill();
    }

    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS trigger selection." << std::endl;
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
      if ( selTrigger_1e && (isTriggered_2e || isTriggered_1mu || isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1e = " << selTrigger_1e
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_1mu = " << isTriggered_1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e && (isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_2e = " << selTrigger_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1mu = " << selTrigger_1mu
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1e1mu && isTriggered_2mu ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS trigger selection." << std::endl;
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
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::sort(preselMuons.begin(), preselMuons.end(), isHigherPt);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::sort(fakeableMuons.begin(), fakeableMuons.end(), isHigherConePt);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::sort(tightMuons.begin(), tightMuons.end(), isHigherPt);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else if ( leptonSelection == kTight    ) selMuons = tightMuons;
    else assert(0);
    if ( isDEBUG ) {
      for ( size_t idxPreselMuon = 0; idxPreselMuon < preselMuons.size(); ++idxPreselMuon ) {
        std::cout << "preselMuon #" << idxPreselMuon << ":" << std::endl;
        std::cout << (*preselMuons[idxPreselMuon]);
      }
      for ( size_t idxSelMuon = 0; idxSelMuon < selMuons.size(); ++idxSelMuon ) {
        std::cout << "selMuon #" << idxSelMuon << ":" << std::endl;
        std::cout << (*selMuons[idxSelMuon]);
      }
    }

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::sort(preselElectrons.begin(), preselElectrons.end(), isHigherPt);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::sort(fakeableElectrons.begin(), fakeableElectrons.end(), isHigherConePt);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::sort(tightElectrons.begin(), tightElectrons.end(), isHigherPt);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else if ( leptonSelection == kTight    ) selElectrons = tightElectrons;
    else assert(0);
    if ( isDEBUG ) {
      for ( size_t idxPreselElectron = 0; idxPreselElectron < preselElectrons.size(); ++idxPreselElectron ) {
        std::cout << "preselElectron #" << idxPreselElectron << ":" << std::endl;
        std::cout << (*preselElectrons[idxPreselElectron]);
      }
      for ( size_t idxSelElectron = 0; idxSelElectron < selElectrons.size(); ++idxSelElectron ) {
        std::cout << "selElectron #" << idxSelElectron << ":" << std::endl;
        std::cout << (*selElectrons[idxSelElectron]);
      }
    }

    std::vector<const RecoLepton*> selLeptons;
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::sort(cleanedHadTaus.begin(), cleanedHadTaus.end(), isHigherPt);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);
    if ( isDEBUG ) {
      for ( size_t idxPreselHadTau = 0; idxPreselHadTau < preselHadTaus.size(); ++idxPreselHadTau ) {
        std::cout << "preselHadTau #" << idxPreselHadTau << ":" << std::endl;
        std::cout << (*preselHadTaus[idxPreselHadTau]);
      }
      for ( size_t idxSelHadTau = 0; idxSelHadTau < selHadTaus.size(); ++idxSelHadTau ) {
        std::cout << "selHadTau #" << idxSelHadTau << ":" << std::endl;
        std::cout << (*selHadTaus[idxSelHadTau]);
      }
    }
    selHadTaus = pickFirstNobjects(selHadTaus, 1);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    if ( isDEBUG ) {
      if ( run_lumi_eventSelector ) {
        std::cout << " (#uncleanedJets = " << jet_ptrs.size() << ")" << std::endl;
        for ( size_t idxJet = 0; idxJet < jet_ptrs.size(); ++idxJet ) {
          std::cout << "uncleanedJet #" << idxJet << ":" << std::endl;
          std::cout << (*jet_ptrs[idxJet]);
        }
      }
    }
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableElectrons, tightElectrons, fakeableMuons, tightMuons, fakeableHadTaus);
    std::sort(cleanedJets.begin(), cleanedJets.end(), isHigherPt);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

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
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherConePt);
    // require at least two leptons passing loose preselection criteria
    if ( !(preselLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS preselLeptons selection." << std::endl;
        printCollection("preselLeptons", preselLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons");
    cutFlowHistManager->fillHistograms(">= 2 presel leptons", lumiScale);
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    if ( apply_leptonGenMatching_ttZ_workaround ) idxPreselLepton_genMatch = kGen_2l0j;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 2 &&                            (selTrigger_2e    || selTrigger_1e                  )) ||
           (preselElectrons.size() >= 1 && preselMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
           (                               preselMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl;
        std::cout << " (#preselElectrons = " << preselElectrons.size()
                  << ", #preselMuons = " << preselMuons.size()
                  << ", selTrigger_2mu = " << selTrigger_2mu
                  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
                  << ", selTrigger_2e = " << selTrigger_2e
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("presel lepton trigger match");
    cutFlowHistManager->fillHistograms("presel lepton trigger match", lumiScale);

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on preselection level
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selJets selection (1)." << std::endl;
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets");
    cutFlowHistManager->fillHistograms(">= 2 jets", lumiScale);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selBJets selection (1)." << std::endl;
        printCollection("selJets", selJets);
        printCollection("selBJets_loose", selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", lumiScale);

    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selHadTaus selection." << std::endl;
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau (1)");
    cutFlowHistManager->fillHistograms(">= 1 sel tau (1)", lumiScale);
    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined1);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

    double mTauTauVis1_presel = (preselLepton_lead->p4() + selHadTau->p4()).mass();
    double mTauTauVis2_presel = (preselLepton_sublead->p4() + selHadTau->p4()).mass();

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselLepton_genMatch][idxSelHadTau_genMatch];
    assert(preselHistManager != 0);

    preselHistManager->electrons_->fillHistograms(preselElectrons, 1.);
    preselHistManager->muons_->fillHistograms(preselMuons, 1.);
    preselHistManager->hadTaus_->fillHistograms(selHadTaus, 1.);
    preselHistManager->jets_->fillHistograms(selJets, 1.);
    preselHistManager->BJets_loose_->fillHistograms(selBJets_loose, 1.);
    preselHistManager->BJets_medium_->fillHistograms(selBJets_medium, 1.);
    preselHistManager->met_->fillHistograms(met, mht_p4, met_LD, 1.);
    preselHistManager->evt_->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(),
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      1.0, // evtWeight is first to be sure of not being loosing counting
      -1., -1., -1., -1., -1., -1., -1., -1., -1., -1., -1.,
      mTauTauVis1_presel, mTauTauVis2_presel,
      -1., -1.
    );

//--- apply final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selLeptons selection." << std::endl;
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
    if ( apply_leptonGenMatching_ttZ_workaround ) idxSelLepton_genMatch = kGen_2l0j;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined2);

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    double btagWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= boost::math::sign(eventInfo.genWeight);
      if ( isMC_tH ) evtWeight *= eventInfo.genWeight_tH;
      evtWeight *= eventInfo.pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {
        if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
        else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
        else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
        else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
            jet != selJets.end(); ++jet ) {
        btagWeight *= (*jet)->BtagWeight();
      }
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

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
        triggerWeight = dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
        if ( isDEBUG ) {
          std::cout << "triggerWeight = " << triggerWeight << std::endl;
        }
        evtWeight *= triggerWeight;
      }

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
      if ( leptonSelection == kFakeable ) {
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
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

    double weight_fakeRate = 1.;
    if ( !selectBDT ) {
      if ( applyFakeRateWeights == kFR_3L ) {
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
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta()); // selHadTau->pt()>0 ?  : 0.0;
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTaus);
  //td::cout << "prob_fake_hadTau = " << prob_fake_hadTau << std::endl;
  weight_fakeRate = getWeight_3L(
          prob_fake_lepton_lead, passesTight_lepton_lead,
          prob_fake_lepton_sublead, passesTight_lepton_sublead,
          prob_fake_hadTau, passesTight_hadTau);
        if ( isDEBUG ) {
          std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
        }
        evtWeight *= weight_fakeRate;
      } else if ( applyFakeRateWeights == kFR_2lepton) {
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
        if ( isDEBUG ) {
          std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
        }
        evtWeight *= weight_fakeRate;
      } else if ( applyFakeRateWeights == kFR_1tau) {
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        weight_fakeRate = prob_fake_hadTau;
        if ( isDEBUG ) {
          std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
        }
        evtWeight *= weight_fakeRate;
      }
      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight && !(selHadTau->genHadTau() || selHadTau->genLepton())) {
        double weight_data_to_MC_correction_hadTau = jetToTauFakeRateInterface->getSF_lead(selHadTau->pt(), selHadTau->absEta());
        if ( isDEBUG ) {
          std::cout << "weight_data_to_MC_correction_hadTau = " << weight_data_to_MC_correction_hadTau << std::endl;
        }
        evtWeight *= weight_data_to_MC_correction_hadTau;
      }
    } // end if !selectBDT
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }
    // require exactly two leptons passing tight selection criteria, to avoid overlap with other channels
    std::vector<const RecoLepton*> tightLeptons;
    tightLeptons.reserve(tightElectrons.size() + tightMuons.size());
    tightLeptons.insert(tightLeptons.end(), tightElectrons.begin(), tightElectrons.end());
    tightLeptons.insert(tightLeptons.end(), tightMuons.begin(), tightMuons.end());
    std::sort(tightLeptons.begin(), tightLeptons.end(), isHigherPt);
    if ( !(tightLeptons.size() <= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS tightLeptons selection." << std::endl;
        printCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("<= 2 tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("<= 2 tight leptons", evtWeight);
    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((selElectrons.size() >= 2 &&                         (selTrigger_2e    || selTrigger_1e                  )) ||
           (selElectrons.size() >= 1 && selMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
           (                            selMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl;
        std::cout << " (#selElectrons = " << preselElectrons.size()
                  << ", #selMuons = " << preselMuons.size()
                  << ", selTrigger_2mu = " << selTrigger_2mu
                  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
                  << ", selTrigger_2e = " << selTrigger_2e
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton trigger match", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton trigger match", evtWeight);
    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 3) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selJets selection (2)." << std::endl;
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(">= 3 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 3 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selBJets selection (2)." << std::endl;
        printCollection("selJets", selJets);
        printCollection("selBJets_loose", selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);

    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selHadTaus selection." << std::endl;
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau (2)", evtWeight);
    cutFlowHistManager->fillHistograms(">= 1 sel tau (2)", evtWeight);

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
        std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    double minPt_lead = -1.;
    if ( era == kEra_2017 ) minPt_lead = 25.; // CV: increase minimum lepton pT cut to 25 GeV to keep-up with higher trigger thresholds in 2016 data
    else assert(0);
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt() > minPt_lead && selLepton_sublead->pt() > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS lepton pT selection." << std::endl;
        std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
                  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);
    cutFlowHistManager->fillHistograms("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool failsTightChargeCut = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton = selLeptons.begin();
          lepton != selLeptons.end(); ++lepton ) {
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
        std::cout << "event FAILS tight lepton charge requirement." << std::endl;
      }
      //if (!selectBDT)
      continue;
    }
    cutFlowTable.update("tight lepton charge", evtWeight);
    cutFlowHistManager->fillHistograms("tight lepton charge", evtWeight);

    bool isLeptonCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isLeptonCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
    if ( leptonChargeSelection == kOS && isLeptonCharge_SS ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kSS && isLeptonCharge_OS ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = SS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kOS ) {
      double prob_chargeMisId_lead = prob_chargeMisId(getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta());
      double prob_chargeMisId_sublead = prob_chargeMisId(getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta());

      if ( apply_lepton_and_hadTauCharge_cut ) {
        if ( chargeSumSelection == kOS ) {
          // CV: apply charge misidentification probability to lepton of same charge as hadronic tau
          //    (if the lepton of charge opposite to the charge of the hadronic tau "flips",
          //     the event has sum of charges equal to three and fails "lepton+tau charge" cut)
          if ( selLepton_lead->charge()*selHadTau->charge()    > 0 ) evtWeight *= prob_chargeMisId_lead;
          if ( selLepton_sublead->charge()*selHadTau->charge() > 0 ) evtWeight *= prob_chargeMisId_sublead;
        } else if ( chargeSumSelection == kSS ) {
          // CV: apply charge misidentification probability to lepton of opposite charge as hadronic tau
          //    (if the lepton of same charge as the hadronic tau "flips",
          //     the event has sum of charges equal to one and fails "lepton+tau charge" cut)
          if ( selLepton_lead->charge()*selHadTau->charge()    < 0 ) evtWeight *= prob_chargeMisId_lead;
          if ( selLepton_sublead->charge()*selHadTau->charge() < 0 ) evtWeight *= prob_chargeMisId_sublead;
        } else assert(0);
      } else {
        evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);
      }
    }
    cutFlowTable.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton-pair OS/SS charge", evtWeight);

    if ( apply_lepton_and_hadTauCharge_cut ) {
      if ( !((chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) == 1) ||
             (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) != 1)) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS lepton+tau charge selection." << std::endl;
          std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                    << ", subleading selLepton charge = " << selLepton_sublead->charge()
                    << ", selHadTau charge = " << selHadTau->charge() << ")" << std::endl;
        }
        continue;
      }
      cutFlowTable.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
      cutFlowHistManager->fillHistograms("sel lepton+tau charge", evtWeight);
    }

    bool failsZbosonMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = fakeableLeptons.begin();
          lepton1 != fakeableLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
            lepton2 != fakeableLeptons.end(); ++lepton2 ) {
        double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
        if ( (*lepton1)->is_electron() && (*lepton2)->is_electron() && std::fabs(mass - z_mass) < z_window ) {
          failsZbosonMassVeto = true;
        }
      }
    }
    if ( failsZbosonMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS Z-boson veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeight);
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeight);
    if ( !(fakeableMuons.size() >= 1 || met_LD >= 0.2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS MET LD selection." << std::endl;
        std::cout << " (LD = " << met_LD << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("met LD > 0.2", evtWeight);
    cutFlowHistManager->fillHistograms("met LD > 0.2", evtWeight);

    if ( leptonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( (tightMuons.size() + tightElectrons.size()) >= 2 && tightHadTaus.size() >= 1 ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS tightElectrons+tightMuons selection." << std::endl;
          std::cout << " (#tightElectrons = " << tightElectrons.size() << ", #tightMuons = " << tightMuons.size() << ", #tightHadTaus = " << tightHadTaus.size() << ")" << std::endl;
        }
        continue; // CV: avoid overlap with signal region
      }
      cutFlowTable.update("signal region veto", evtWeight);
      cutFlowHistManager->fillHistograms("signal region veto", evtWeight);
    }

    double mTauTauVis1_sel = (selLepton_lead->p4() + selHadTau->p4()).mass();
    double mTauTauVis2_sel = (selLepton_sublead->p4() + selHadTau->p4()).mass();


    //--- compute variables BDTs used to discriminate ttH vs. ttV and ttH vs. ttba -- they will be used more than once -- Xanda

    double mindr_lep1_jet=TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    double mindr_lep2_jet=TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets));
    //double max_lep_eta=TMath::Max(std::abs(selLepton_lead -> eta()), std::abs(selLepton_sublead -> eta()));
    //double tau_pt=selHadTau -> pt();
    //double ptmiss=met.pt();
    //double dr_leps=deltaR(selLepton_lead -> p4(), selLepton_sublead -> p4());
    //double mT_lep1=comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi());
    //double mT_lep2=comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi());
    //double dr_lep1_tau=deltaR(selLepton_lead -> p4(), selHadTau -> p4());
    //double dr_lep2_tau=deltaR(selLepton_sublead -> p4(), selHadTau -> p4());
    double avg_dr_jet=comp_avg_dr_jet(selJets);
    double nJet25_Recl=comp_n_jet25_recl(selJets);
    double lep1_conePt=comp_lep1_conePt(*selLepton_lead);
    double lep2_conePt=comp_lep2_conePt(*selLepton_sublead);
    double minMET400=std::min(met.pt(), (Double_t)400.);
    double mindr_tau_jet = comp_mindr_hadTau1_jet(*selHadTau, selJets);

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    in 2lss_1tau category of ttH multilepton analysis
    mvaInputs_2lss["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(selLepton_lead->eta()), std::fabs(selLepton_sublead->eta()));
    mvaInputs_2lss["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->p4(), met.pt(), met.phi());
    mvaInputs_2lss["nJet25_Recl"]                = nJet25_Recl;
    mvaInputs_2lss["mindr_lep1_jet"]             = mindr_lep1_jet;
    mvaInputs_2lss["mindr_lep2_jet"]             = mindr_lep2_jet;
    mvaInputs_2lss["LepGood_conePt[iF_Recl[0]]"] = lep1_conePt;
    mvaInputs_2lss["LepGood_conePt[iF_Recl[1]]"] = lep2_conePt;
    mvaInputs_2lss["min(met_pt,400)"]            = minMET400;
    mvaInputs_2lss["avg_dr_jet"]                 = avg_dr_jet;
    check_mvaInputs(mvaInputs_2lss, eventInfo);
    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs_2lss);
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs_2lss);
    //std::cout << "mvaOutput_2lss_ttbar = " << mvaOutput_2lss_ttbar << std::endl;

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
    //std::cout << "mvaDiscr_2lss = " << mvaDiscr_2lss << std::endl;
    //std::cout << std::endl;
    MEMOutput_2lss_1tau memOutput_2lss_1tau_matched;
    if ( memReader ) {
      std::vector<MEMOutput_2lss_1tau> memOutputs_2lss_1tau = memReader->read();
      for ( std::vector<MEMOutput_2lss_1tau>::const_iterator memOutput_2lss_1tau = memOutputs_2lss_1tau.begin();
            memOutput_2lss_1tau != memOutputs_2lss_1tau.end(); ++memOutput_2lss_1tau ) {
        const double selLepton_lead_dR = deltaR(
          selLepton_lead->eta(), selLepton_lead->phi(),
          memOutput_2lss_1tau->leadLepton_eta_, memOutput_2lss_1tau->leadLepton_phi_);
        if ( selLepton_lead_dR > 1.e-2 ) continue;
        const double selLepton_sublead_dR = deltaR(
          selLepton_sublead->eta(), selLepton_sublead->phi(),
          memOutput_2lss_1tau->subleadLepton_eta_, memOutput_2lss_1tau->subleadLepton_phi_);
        if ( selLepton_sublead_dR > 1.e-2 ) continue;
        const double selHadTau_dR = deltaR(
          selHadTau->eta(), selHadTau->phi(),
          memOutput_2lss_1tau->hadTau_eta_, memOutput_2lss_1tau->hadTau_phi_);
        if ( selHadTau_dR > 1.e-2 ) continue;
        memOutput_2lss_1tau_matched = (*memOutput_2lss_1tau);
        break;
      }
      if ( !memOutput_2lss_1tau_matched.is_initialized() ) {
        std::cout << "Warning in " << eventInfo << '\n'
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
                      << "\t\tlead lepton eta = " << memOutputs_2lss_1tau[mem_idx].leadLepton_eta_
                      << "; phi = "               << memOutputs_2lss_1tau[mem_idx].leadLepton_phi_ << '\n'
                      << "\t\tsublead lepton eta = " << memOutputs_2lss_1tau[mem_idx].subleadLepton_eta_
                      << "; phi = "                  << memOutputs_2lss_1tau[mem_idx].subleadLepton_phi_ << '\n'
                      << "\t\thadronic tau eta = " << memOutputs_2lss_1tau[mem_idx].hadTau_eta_
                      << "; phi = "                << memOutputs_2lss_1tau[mem_idx].hadTau_phi_ << '\n';
          }
        } else {
          std::cout << "Event contains no MEM objects whatsoever !!\n";
        }
      }
    }
    double memOutput_LR = ( memOutput_2lss_1tau_matched.isValid() ) ? memOutput_2lss_1tau_matched.LR() : -1.;
    double memOutput_ttZ_LR = ( memOutput_2lss_1tau_matched.isValid_ttZ_LR() ) ? memOutput_2lss_1tau_matched.ttZ_LR() : -1.;
    double memOutput_ttbar_LR = ( memOutput_2lss_1tau_matched.isValid_ttbar_LR()  ) ? memOutput_2lss_1tau_matched.LR() : -1.;

    Double_t memDiscr = getSF_from_TH2(mem_mapping, memOutput_ttbar_LR, memOutput_ttZ_LR)+ 1;

    //--- compute output of hadronic top tagger BDT
    //TH2* histogram_mva_hadTopTagger = fs.make<TH2D>("mva_hadTopTagger", "mva_hadTopTagger", 200, -1., +1., 200, -1., +1.);
    //double max_mvaOutput_hadTopTagger = -1.;
    double max_mvaOutput_hadTopTaggerWithKinFit = -1.;
    double max_mvaOutput_hadTopTagger = -1.;
    bool max_truth_hadTopTagger = false;
    bool max_truth_hadTopTaggerWithKinFit = false;
    bool hadtruth = false;
    int ncombo=0;
    double genTopPt=-10;
    double positionJet1=-1;
    double positionJet2=-1;
    double positionJet3=-1;

    Particle::LorentzVector unfittedHadTopP4, fittedHadTopP4;
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
                if ( genWJets.size() >= 2 && genBJets.size() >= 1 && genTopQuarks.size() >= 1 && genWBosons.size() >= 1 ){
              double genTopPtProbeTop=-10;
              double genTopPtProbeAntiTop=-10;
            std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(**selBJet, **selWJet1, **selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenTop, genTopPtProbeTop);
            std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(**selBJet, **selWJet1, **selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop, genTopPtProbeAntiTop);
              if ( genMatchingTop[kGenMatchedTriplet]     ) genTopPt = genTopPtProbeTop;
              if ( genMatchingAntiTop[kGenMatchedTriplet] ) genTopPt = genTopPtProbeAntiTop;
              isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
              if ( isGenMatched ) hadtruth = true;
                }
              }
        if ( bdtResult.at(kXGB_with_kinFit) > max_mvaOutput_hadTopTaggerWithKinFit ) { // hadTopTaggerWithKinFit
                max_truth_hadTopTaggerWithKinFit = isGenMatched;
          max_mvaOutput_hadTopTaggerWithKinFit = bdtResult.at(kXGB_with_kinFit);
                fittedHadTopP4 = hadTopTagger->kinFit()->fittedTop();
                unfittedHadTopP4 = (*selBJet)->p4() + (*selWJet1)->p4() + (*selWJet2)->p4();
            positionJet1 = (*selBJet)->pt();
            positionJet2 = (*selWJet1)->pt();
            positionJet3 = (*selWJet2)->pt();
              }
        if ( bdtResult.at(kXGB_no_kinFit) > max_mvaOutput_hadTopTagger ) { // hadTopTaggerNoKinFit
                max_truth_hadTopTagger = isGenMatched;
          max_mvaOutput_hadTopTagger = bdtResult.at(kXGB_with_kinFit);
              }
        //fillWithOverFlow2d(histogram_mva_hadTopTagger, bdtResult.at(kXGB_with_kinFit), bdtResult.at(kTMVA_with_kinFitnFit), 1.);
        // to test if XML converted file is equal to plain pkl rearing -- do not erase the example
            }
          }
    }

    std::map<std::string, double> mvaInputs_Hj_tagger;
    double mvaOutput_Hj_tagger = -1.;
    for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin();
          selJet != selJets.end(); ++selJet ) {
      if ((*selJet)->pt()==positionJet1 || (*selJet)->pt()==positionJet2 || (*selJet)->pt()==positionJet3) continue;
      double mvaOutput = comp_mvaOutput_Hj_tagger(
        *selJet, fakeableLeptons,
        mvaInputs_Hj_tagger, mva_Hj_tagger,
        eventInfo);
      if ( mvaOutput > mvaOutput_Hj_tagger ) mvaOutput_Hj_tagger = mvaOutput;
    }

    std::map<std::string, double> mvaInputs_Hjj_tagger;
    double mvaOutput_Hjj_tagger = -1.;
    for ( std::vector<const RecoJet*>::const_iterator selJet1 = selJets.begin();
          selJet1 != selJets.end(); ++selJet1 ) {
      if ((*selJet1)->pt()==positionJet1 || (*selJet1)->pt()==positionJet2 || (*selJet1)->pt()==positionJet3) continue;
      for ( std::vector<const RecoJet*>::const_iterator selJet2 = selJet1 + 1;
            selJet2 != selJets.end(); ++selJet2 ) {
        if ((*selJet2)->pt()==positionJet1 || (*selJet2)->pt()==positionJet2 || (*selJet2)->pt()==positionJet3) continue;
        double mvaOutput = comp_mvaOutput_Hjj_tagger(
          *selJet1, *selJet2, selJets, fakeableLeptons,
          mvaInputs_Hjj_tagger, mva_Hjj_tagger,
          mvaInputs_Hj_tagger, mva_Hj_tagger,
      eventInfo);
        if ( mvaOutput > mvaOutput_Hjj_tagger ) mvaOutput_Hjj_tagger = mvaOutput;
      }
    }

    //--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar trained by Arun for 2lss_1tau category
    mvaInputs_2lss_1tau["avg_dr_jet"]           = comp_avg_dr_jet(selJets);
    mvaInputs_2lss_1tau["dr_leps"]              = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    mvaInputs_2lss_1tau["dr_lep1_tau"]          = deltaR(selLepton_lead->p4(), selHadTau->p4());
    mvaInputs_2lss_1tau["lep1_conePt"]          = selLepton_lead->cone_pt();
    mvaInputs_2lss_1tau["lep2_conePt"]          = selLepton_sublead->cone_pt();
    mvaInputs_2lss_1tau["mindr_lep1_jet"]       = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    mvaInputs_2lss_1tau["mindr_lep2_jet"]       = TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets));
    mvaInputs_2lss_1tau["mT_lep1"]              = comp_MT_met_lep1(selLepton_lead->p4(), met.pt(), met.phi());
    mvaInputs_2lss_1tau["mTauTauVis1"]          = mTauTauVis1_sel;
    mvaInputs_2lss_1tau["mTauTauVis2"]          = mTauTauVis2_sel;
    mvaInputs_2lss_1tau["nJet"]                 = selJets.size();
    mvaInputs_2lss_1tau["tau_pt"]               = selHadTau->pt();
    mvaInputs_2lss_1tau["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = TMath::Max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    check_mvaInputs(mvaInputs_2lss_1tau, eventInfo);
    double mvaOutput_2lss_1tau_ttV = mva_2lss_1tau_ttV(mvaInputs_2lss_1tau);
    double mvaOutput_2lss_1tau_ttbar = mva_2lss_1tau_ttbar(mvaInputs_2lss_1tau);
    Double_t mvaDiscr_2lss_1tau = getSF_from_TH2(mva_mapping_2lss_1tau, mvaOutput_2lss_1tau_ttbar, mvaOutput_2lss_1tau_ttV) + 1.;
    //////////////////////////////////////

    mvaInputs_2lss_1tau_wMEM = mvaInputs_2lss_1tau;
    mvaInputs_2lss_1tau_wMEM["memOutput_LR"] = memOutput_LR;

    double mvaOutput_2lss_1tau_ttV_wMEM = mva_2lss_1tau_ttV_wMEM(mvaInputs_2lss_1tau_wMEM);
    double mvaOutput_2lss_1tau_ttbar_wMEM = mva_2lss_1tau_ttbar_wMEM(mvaInputs_2lss_1tau_wMEM);
    Double_t mvaDiscr_2lss_1tau_wMEM = getSF_from_TH2(mva_mapping_2lss_1tau_wMEM, mvaOutput_2lss_1tau_ttbar_wMEM, mvaOutput_2lss_1tau_ttV_wMEM) + 1.;

//--- fill histograms with events passing final selection
    evtWeightSum=evtWeightSum+evtWeight;
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
    selHistManager->mvaInputVariables_2lss_->fillHistograms(mvaInputs_2lss, evtWeight);
    selHistManager->mvaInputVariables_2lss_1tau_->fillHistograms(mvaInputs_2lss_1tau, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(),
      selMuons.size(),
      selHadTaus.size(),
      selJets.size(),
      selBJets_loose.size(),
      selBJets_medium.size(),
      evtWeight,
      //
      mvaOutput_2lss_ttV,
      mvaOutput_2lss_ttbar,
      mvaDiscr_2lss,
      mvaOutput_2lss_1tau_ttV,
      mvaOutput_2lss_1tau_ttbar,
      mvaDiscr_2lss_1tau,
      mvaOutput_2lss_1tau_ttV_wMEM,
      mvaOutput_2lss_1tau_ttbar_wMEM,
      mvaDiscr_2lss_1tau_wMEM,
      mvaOutput_Hj_tagger,
      mvaOutput_Hjj_tagger,
      mTauTauVis1_sel,
      mTauTauVis2_sel,
      memOutput_LR, //memOutput_2lss_1tau_matched.is_initialized() ? &memOutput_2lss_1tau_matched : nullptr,
      memDiscr
    );
    if ( isSignal ) {
      const std::string decayModeStr = eventInfo.getDecayModeString();
      if(! decayModeStr.empty())
      {
        selHistManager->evt_in_decayModes_[decayModeStr]->fillHistograms(
          selElectrons.size(),
          selMuons.size(),
          selHadTaus.size(),
          selJets.size(),
          selBJets_loose.size(),
          selBJets_medium.size(),
          evtWeight,
          mvaOutput_2lss_ttV,
          mvaOutput_2lss_ttbar,
          mvaDiscr_2lss,
          mvaOutput_2lss_1tau_ttV,
          mvaOutput_2lss_1tau_ttbar,
          mvaDiscr_2lss_1tau,
          mvaOutput_2lss_1tau_ttV_wMEM,
          mvaOutput_2lss_1tau_ttbar_wMEM,
          mvaDiscr_2lss_1tau_wMEM,
          mvaOutput_Hj_tagger,
          mvaOutput_Hjj_tagger,
          mTauTauVis1_sel,
          mTauTauVis2_sel,
          memOutput_LR, //memOutput_2lss_1tau_matched.is_initialized() ? &memOutput_2lss_1tau_matched : nullptr,
          memDiscr
        );
    }
    }
    selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

    double tau_fake_prob=1.;
    double prob_fake_lepton_lead = 1.;
    double prob_fake_lepton_sublead = 1.;

    double memOutput_type=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.type() : -100.;
    double memOutput_ttH=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttH()     : -100.;
    double memOutput_tt=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_tt()      : -100.;
    double memOutput_ttZ=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttZ()     : -100.;
    double memOutput_ttZ_Zll=memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.weight_ttZ_Zll() : -100.;

    if ( bdt_filler ) {
      //FR weights for bdt ntuple
      if(leptonFakeRateInterface) {
        if      ( std::abs(selLepton_lead->pdgId()) == 11 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->cone_pt(), selLepton_lead->absEta());
        else if ( std::abs(selLepton_lead->pdgId()) == 13 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->cone_pt(), selLepton_lead->absEta());

        if      ( std::abs(selLepton_sublead->pdgId()) == 11 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
        else if ( std::abs(selLepton_sublead->pdgId()) == 13 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
      }

        if(jetToTauFakeRateInterface) {
          tau_fake_prob= jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        }

      double lep1_genLepPt=( selLepton_lead->genLepton() != 0 ) ? selLepton_lead->genLepton()->pt() : 0.;
      double lep2_genLepPt=( selLepton_sublead->genLepton() != 0 ) ? selLepton_sublead->genLepton()->pt() : 0.;
      double tau_genTauPt=( selHadTau->genHadTau() != 0 ) ? selHadTau->genHadTau()->pt() : 0.;

      if ( mindr_lep2_jet < 0.3 || mindr_lep1_jet < 0.3 ) {
        std::cout <<leptonSelection_string <<" (#tightElectrons = " << tightElectrons.size() <<"("<<fakeableElectrons.size() <<"), #tightMuons = " << tightMuons.size() <<"("<<fakeableMuons.size() <<")" << std::endl;
      };
      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("lep1_pt",                selLepton_lead -> pt())
          ("lep1_conePt",            comp_lep1_conePt(*selLepton_lead))
          ("lep1_eta",               std::abs(selLepton_lead -> eta()))
          ("lep1_tth_mva",           selLepton_lead -> mvaRawTTH())
          ("mindr_lep1_jet",         TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets)) )
          ("mindr_lep2_jet",         TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets)) )
          ("mT_lep1",                comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi()))
          ("MT_met_lep1",            comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi()))
          ("dr_lep1_tau",            deltaR(selLepton_lead -> p4(), selHadTau -> p4()))
          ("lep2_pt",                selLepton_sublead -> pt())
          ("lep2_conePt",            comp_lep1_conePt(*selLepton_sublead))
          ("lep2_eta",               std::abs(selLepton_sublead -> eta()))
          ("max_lep_eta",            TMath::Max(std::abs(selLepton_lead -> eta()), std::abs(selLepton_sublead -> eta())))
          ("avg_dr_lep",             1.0) // comp_avg_dr_jet(selLeptons))
          ("lep2_tth_mva",           selLepton_sublead -> mvaRawTTH())
          ("mT_lep2",                comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi()))
          ("dr_lep2_tau",            deltaR(selLepton_sublead -> p4(), selHadTau -> p4()))
          ("mindr_tau_jet",          TMath::Min(10., mindr_tau_jet))
          ("avg_dr_jet",             comp_avg_dr_jet(selJets))
          ("nJet25_Recl",            comp_n_jet25_recl(selJets))
          ("ptmiss",                 met.pt())
          ("htmiss",                 mht_p4.pt())
          ("tau_mva",                selHadTau -> raw_mva_dR03())
          ("tau_pt",                 selHadTau -> pt())
          ("tau_eta",                std::abs(selHadTau -> eta()))
          ("dr_leps",                deltaR(selLepton_lead -> p4(), selLepton_sublead -> p4()))
          ("mTauTauVis1",            mTauTauVis1_sel)
          ("mTauTauVis2",            mTauTauVis2_sel)
          ("memOutput_isValid",      memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.isValid()        : -100.)
          ("memOutput_errorFlag",    memOutput_2lss_1tau_matched.is_initialized() ? memOutput_2lss_1tau_matched.errorFlag()      : -100.)
          ("memOutput_LR",           memOutput_LR)
          ("memOutput_tt_LR",        memOutput_ttbar_LR)
          ("memOutput_ttZ_LR",       memOutput_ttZ_LR)
          ("memOutput_tt_LR",        memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 1.e-15*memOutput_tt)) : (memOutput_ttH/(memOutput_ttH + 1.e-12*memOutput_tt)))
          ("memOutput_ttZ_LR",       memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 0.5*memOutput_ttZ)) : (memOutput_ttH/(memOutput_ttH + 0.05*memOutput_ttZ)))
          ("memOutput_ttZ_Zll_LR",   memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 1.0*memOutput_ttZ_Zll)) : (memOutput_ttH/(memOutput_ttH + 0.1*memOutput_ttZ_Zll)))
          ("log_memOutput_ttH",       TMath::Log(TMath::Max(1.e-30, memOutput_ttH)))
          ("log_memOutput_ttZ",       TMath::Log(TMath::Max(1.e-30, memOutput_ttZ)))
          ("log_memOutput_ttZ_Zll",   TMath::Log(TMath::Max(1.e-30, memOutput_ttZ_Zll)))
          ("log_memOutput_tt",        TMath::Log(TMath::Max(1.e-30, memOutput_tt)))
          ("lep1_genLepPt",          lep1_genLepPt)
          ("lep2_genLepPt",          lep2_genLepPt)
          ("tau_genTauPt",           tau_genTauPt)
          ("lep1_frWeight",          lep1_genLepPt > 0 ? 1.0 : prob_fake_lepton_lead)
          ("lep2_frWeight",          lep2_genLepPt > 0 ? 1.0 : prob_fake_lepton_sublead)
          ("tau_frWeight",           tau_genTauPt > 0 ? 1.0 : tau_fake_prob)
          ("mvaOutput_2lss_ttV",     mvaOutput_2lss_ttV)
          ("mvaOutput_2lss_ttbar",   mvaOutput_2lss_ttbar)
          ("mvaDiscr_2lss",          mvaDiscr_2lss)
          ("mvaOutput_Hj_tagger",    mvaOutput_Hj_tagger)
          ("mvaOutput_Hjj_tagger",   mvaOutput_Hjj_tagger)
          ("fittedHadTop_pt",        fittedHadTopP4.pt())
          ("fittedHadTop_eta",       std::abs(fittedHadTopP4.eta()))
          ("unfittedHadTop_pt",      unfittedHadTopP4.pt())
          ("unfittedHadTop_eta",     std::abs(unfittedHadTopP4.eta()))
          ("fitHTptoHTpt",           fittedHadTopP4.pt()/unfittedHadTopP4.pt())
          ("fitHTptoHTmass",           fittedHadTopP4.mass()/unfittedHadTopP4.mass())
          ("dr_lep1_HTfitted",        deltaR(selLepton_lead -> p4(), fittedHadTopP4) )
          ("dr_lep2_HTfitted",        deltaR(selLepton_sublead -> p4(), fittedHadTopP4) )
          ("dr_tau_HTfitted",         deltaR(selHadTau -> p4(), fittedHadTopP4))
          ("mass_lep1_HTfitted",        (selLepton_lead -> p4() + fittedHadTopP4).mass() )
          ("mass_lep2_HTfitted",        (selLepton_sublead -> p4() + fittedHadTopP4).mass() )
          ("dr_lep1_HTunfitted",        deltaR(selLepton_lead -> p4(), unfittedHadTopP4) )
          ("dr_lep2_HTunfitted",        deltaR(selLepton_sublead -> p4(), unfittedHadTopP4) )
          ("dr_tau_HTunfitted",         deltaR(selHadTau -> p4(), unfittedHadTopP4))
          ("mvaOutput_2lss_1tau_ttbar", mvaOutput_2lss_1tau_ttbar)
          ("mvaOutput_2lss_1tau_ttV",   mvaOutput_2lss_1tau_ttV)
          ("mvaDiscr_2lss_1tau",        mvaDiscr_2lss_1tau)
          ("oldVar_from20_to_12",       1.0)
          ("oldVar_from20_to_7",        1.0)
          ("mvaOutput_2lss_1tau_ttV_wMEM", mvaOutput_2lss_1tau_ttV_wMEM)
          ("mvaOutput_2lss_1tau_ttbar_wMEM", mvaOutput_2lss_1tau_ttbar_wMEM)
          ("lumiScale",              lumiScale)
          ("genWeight",              eventInfo.genWeight)
          ("evtWeight",              evtWeight)
          ("nJet",                   selJets.size())
          ("nLep",                   selLeptons.size())
          ("nTau",                   selHadTaus.size())
          ("nBJetLoose",             selBJets_loose.size())
          ("nBJetMedium",            selBJets_medium.size())
          ("lep1_isTight",           int(selLepton_lead -> isTight()))
          ("lep2_isTight",           int(selLepton_sublead -> isTight()))
          ("tau_isTight",            int(tightHadTauFilter(*selHadTau)))
          ("mvaOutput_hadTopTaggerWithKinFit", max_mvaOutput_hadTopTaggerWithKinFit)
          ("mvaOutput_hadTopTagger", max_mvaOutput_hadTopTagger)
          ("bWj1Wj2_isGenMatched",   max_truth_hadTopTagger)
          ("bWj1Wj2_isGenMatchedWithKinFit",   max_truth_hadTopTaggerWithKinFit)
          ("HadTop_pt",              fittedHadTopP4.pt())
          ("HadTop_eta",             std::abs(fittedHadTopP4.eta()))
          ("ncombo", ncombo)
          ("genTopPt", genTopPt)
          ("min(met_pt,400)",            std::min(met.pt(), (Double_t)400.))
          ("hadtruth",               hadtruth)
          ("mbb",       selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : -1000  )
          ("ptbb",       selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).pt() : -1000  )
          ("mbb_loose",       selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1000  )
          ("ptbb_loose",       selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).pt() : -1000  )
          ("failsTightChargeCut",          failsTightChargeCut)
          ("run", eventInfo.run)
          ("lumi", eventInfo.lumi)
          ("evt", eventInfo.event)
        .fill()
      ;
    }

    if(snm)
    {
      const std::vector<const RecoMuon *> cutBasedMuons = cutBasedMuonSelector(preselMuons);
      const std::vector<const RecoMuon *> mvaBasedMuons = mvaBasedMuonSelector(preselMuons);
      const std::vector<const RecoElectron *> cutBasedElectrons = cutBasedElectronSelector(preselElectrons);
      const std::vector<const RecoElectron *> mvaBasedElectrons = mvaBasedElectronSelector(preselElectrons);

      const double ht          = compHT(preselLeptons, preselHadTaus, selJets);
      const double MT_met_lep0 = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
      const double dR_l0tau    = deltaR(selLepton_lead->p4(),    selHadTau->p4());
      const double dR_l1tau    = deltaR(selLepton_sublead->p4(), selHadTau->p4());
      const double dR_leps     = deltaR(selLepton_lead->p4(),    selLepton_sublead->p4());
      const double max_dr_jet  = comp_max_dr_jet(selJets);

      const bool isGenMatched =
        selLepton_lead->isGenMatched()    &&
        selLepton_sublead->isGenMatched() &&
        selHadTau->isGenMatched()
      ;

      snm->read(eventInfo);
      snm->read(preselMuons,     fakeableMuons,     cutBasedMuons,     mvaBasedMuons);
      snm->read(preselElectrons, fakeableElectrons, cutBasedElectrons, mvaBasedElectrons);
      snm->read(selHadTaus);
      snm->read(selJets);

      snm->read({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
      snm->read(isGenMatched);

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);

      snm->read(lep1_conePt,                            FloatVariableType::lep0_conept);
      snm->read(lep2_conePt,                            FloatVariableType::lep1_conept);
      snm->read(mindr_lep1_jet,                         FloatVariableType::mindr_lep0_jet);
      snm->read(mindr_lep2_jet,                         FloatVariableType::mindr_lep1_jet);
      // mindr_lep2_jet not filled
      snm->read(mindr_tau_jet,                          FloatVariableType::mindr_tau_jet);
      snm->read(MT_met_lep0,                            FloatVariableType::MT_met_lep0);
      snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
      snm->read(mvaOutput_2lss_ttV,                     FloatVariableType::MVA_2lss_ttV);
      snm->read(mvaOutput_2lss_ttbar,                   FloatVariableType::MVA_2lss_ttbar);
      // tt_deltaR not filled
      snm->read(selBJets_medium.size(),                 FloatVariableType::ntags);
      snm->read(selBJets_loose.size(),                  FloatVariableType::ntags_loose);
      // tt_mvis not filled
      // tt_pt not filled
      snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
      snm->read(ht,                                     FloatVariableType::HT);
      // MVA_1l2tau_ttbar not filled
      // MVA_1l2tau_ttbar_v2 not filled
      // MVA_1l2tau_ttZ_v2 not filled
      // MVA_1l2tau_2Dbin_v2 not filled
      snm->read(mTauTauVis2_sel,                        FloatVariableType::mvis_l1tau);
      snm->read(dR_l0tau,                               FloatVariableType::dR_l0tau);
      snm->read(dR_l1tau,                               FloatVariableType::dR_l1tau);
      // dR_l2tau not filled
      // MT_met_lep2 not filled
      // MVA_3l1tau_ttbar not filled
      // MVA_3l1tau_ttV not filled
      // MVA_3l1tau_2Dbin not filled

      snm->read(weight_fakeRate,                        FloatVariableType::FR_weight);
      snm->read(triggerWeight,                          FloatVariableType::triggerSF_weight);
      snm->read(leptonSF_weight,                        FloatVariableType::leptonSF_weight);
      snm->read(tauSF_weight,                           FloatVariableType::tauSF_weight);
      snm->read(btagWeight,                             FloatVariableType::bTagSF_weight);
      snm->read(eventInfo.pileupWeight,                 FloatVariableType::PU_weight);
      snm->read(boost::math::sign(eventInfo.genWeight), FloatVariableType::MC_weight);

      snm->read(memOutput_ttH,                          FloatVariableType::Integral_ttH);
      snm->read(memOutput_ttZ,                          FloatVariableType::Integral_ttZ);
      snm->read(memOutput_ttZ_Zll,                      FloatVariableType::Integral_ttZ_Zll);
      snm->read(memOutput_tt,                           FloatVariableType::Integral_ttbar);
      snm->read(memOutput_type,                         FloatVariableType::integration_type);
      snm->read(memOutput_LR,                           FloatVariableType::MEM_LR);
      snm->read(dR_leps,                                FloatVariableType::dR_leps);
      snm->read(mTauTauVis1_sel,                        FloatVariableType::mvis_l0tau);
      snm->read(mvaOutput_2lss_1tau_ttbar,              FloatVariableType::MVA_2lSS1tau_noMEM_ttbar);
      snm->read(mvaOutput_2lss_1tau_ttV,                FloatVariableType::MVA_2lSS1tau_noMEM_ttV);
      snm->read(mvaDiscr_2lss_1tau,                     FloatVariableType::MVA_2lSS1tau_noMEM_2Dbin);
      snm->read(mvaOutput_2lss_1tau_ttbar_wMEM,         FloatVariableType::MVA_2lSS1tau_MEM_ttbar);
      snm->read(mvaOutput_2lss_1tau_ttV_wMEM,           FloatVariableType::MVA_2lSS1tau_MEM_ttV);
      snm->read(mvaDiscr_2lss_1tau_wMEM,                FloatVariableType::MVA_2lSS1tau_MEM_2Dbin);

      snm->read(eventInfo.genWeight,                    FloatVariableType::genWeight);

      snm->fill();
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

      const TH1* histogram_EventCounter = selHistManagers[idxLepton][idxHadTau]->evt_->getHistogram_EventCounter();
      std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries() << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
    }
  }
  std::cout << std::endl;
  std::cout << "Sum of weights "<< evtWeightSum << std::endl;

  delete dataToMCcorrectionInterface;

  delete leptonFakeRateInterface;
  delete jetToTauFakeRateInterface;

  delete run_lumi_eventSelector;

  delete inputFile_mva_mapping_2lss_1tau;
  delete inputFile_mva_mapping_2lss_1tau_wMEM;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete memReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete hadTopTagger;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete cutFlowHistManager;

  delete inputTree;
  delete snm;

  clock.Show("analyze_2lss_1tau");

  return EXIT_SUCCESS;
}
