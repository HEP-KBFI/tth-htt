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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2l_2tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
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
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2l_2tau.h" // EvtHistManager_2l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_2l_2tau.h" // CutFlowTableHistManager_2l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_3lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_3tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort(), std::find()
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <array> // std::array<>
#include <tuple> // std::tuple<>, std::get<>(), std::make_tuple()

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_2lepton, kFR_4L, kFR_2tau };

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

void comp_cosThetaS(const Particle::LorentzVector& hadTauP4_lead, const Particle::LorentzVector& hadTauP4_sublead,
		    double& cosThetaS_hadTau
      )
{
  TLorentzVector hadTauP4tlv_lead;
  hadTauP4tlv_lead.SetPtEtaPhiM(hadTauP4_lead.pt(), hadTauP4_lead.eta(), hadTauP4_lead.phi(), hadTauP4_lead.mass());
  TLorentzVector hadTauP4tlv_sublead;
  hadTauP4tlv_sublead.SetPtEtaPhiM(hadTauP4_sublead.pt(), hadTauP4_sublead.eta(), hadTauP4_sublead.phi(), hadTauP4_sublead.mass());
  TLorentzVector diTauP4 = hadTauP4tlv_lead + hadTauP4tlv_sublead;
  TLorentzVector hadTauBoost = hadTauP4tlv_lead;
  cosThetaS_hadTau = std::abs(hadTauBoost.CosTheta());
}


/**
 * @brief Produce datacard and control plots for 2l_2tau category.
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

  std::cout << "<analyze_2l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_2l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_2l_2tau")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_2l_2tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_2l_2tau")
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

  enum { kOS, kSS, kDisabled };
  std::string leptonChargeSelection_string = cfg_analyze.getParameter<std::string>("leptonChargeSelection");
  int leptonChargeSelection = -1;
  if      ( leptonChargeSelection_string == "OS"       ) leptonChargeSelection = kOS;
  else if ( leptonChargeSelection_string == "SS"       ) leptonChargeSelection = kSS;
  else if ( leptonChargeSelection_string == "disabled" ) leptonChargeSelection = kDisabled;
  else throw cms::Exception("analyze_2l_2tau")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS"       ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS"       ) hadTauChargeSelection = kSS;
  else if ( hadTauChargeSelection_string == "disabled" ) hadTauChargeSelection = kDisabled;
  else throw cms::Exception("analyze_2l_2tau")
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("analyze_2l_2tau")
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
  else throw cms::Exception("analyze_2l_2tau")
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS"       ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS"       ) chargeSumSelection = kSS;
  else if ( chargeSumSelection_string == "disabled" ) chargeSumSelection = kDisabled;
  else throw cms::Exception("analyze_2l_2tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";

  int minNumJets = cfg_analyze.getParameter<int>("minNumJets");
  std::cout << "minNumJets = " << minNumJets << std::endl;

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId");
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits");
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");

  bool isDEBUG = ( cfg_analyze.exists("isDEBUG") ) ? cfg_analyze.getParameter<bool>("isDEBUG") : false;
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }

  int jetPt_option = RecoJetReader::kJetPt_central;
  int jetToLeptonFakeRate_option = kFRl_central;
  int met_option = RecoMEtReader::kMEt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  int lheScale_option = kLHE_scale_central;
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_2l_2tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      if ( isMC ) jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      else throw cms::Exception("analyze_2l_2tau")
	<< "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      if ( isMC ) {
	jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
	if      ( shiftUp_or_Down == "Up"   ) {
	  jetPt_option = RecoJetReader::kJetPt_jecUp;
	  met_option = RecoMEtReader::kMEt_shifted_JetEnUp;
	} else if ( shiftUp_or_Down == "Down" ) {
	  jetPt_option = RecoJetReader::kJetPt_jecDown;
	  met_option = RecoMEtReader::kMEt_shifted_JetEnDown;
	} else assert(0);
      } else throw cms::Exception("analyze_2l_2tau")
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
      } else throw cms::Exception("analyze_2l_2tau")
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
      } else throw cms::Exception("analyze_2l_2tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( !(central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") ||
		  central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt")) ) {
      throw cms::Exception("analyze_2l_2tau")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    }
  }

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else if ( applyFakeRateWeights_string == "4L"       ) applyFakeRateWeights = kFR_4L;
  else if ( applyFakeRateWeights_string == "2tau"     ) applyFakeRateWeights = kFR_2tau;
  else throw cms::Exception("analyze_2l_2tau")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_4L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_4L || applyFakeRateWeights == kFR_2tau ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons1 = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  std::string branchName_genLeptons2 = cfg_analyze.getParameter<std::string>("branchName_genLeptons2");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
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

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper* inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s)." << std::endl;

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  std::vector<hltPath*> hltPaths;
  hltPaths.insert(hltPaths.end(), triggers_1e.begin(), triggers_1e.end());
  hltPaths.insert(hltPaths.end(), triggers_2e.begin(), triggers_2e.end());
  hltPaths.insert(hltPaths.end(), triggers_1mu.begin(), triggers_1mu.end());
  hltPaths.insert(hltPaths.end(), triggers_2mu.begin(), triggers_2mu.end());
  hltPaths.insert(hltPaths.end(), triggers_1e1mu.begin(), triggers_1e1mu.end());
  for ( std::vector<hltPath*>::iterator hltPath = hltPaths.begin();
	hltPath != hltPaths.end(); ++hltPath ) {
    inputTree->registerReader(*hltPath);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons, readGenObjects);
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, run_lumi_eventSelector != 0);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, run_lumi_eventSelector != 0);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree->registerReader(hadTauReader);
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
  tightHadTauFilter.set("dR03mvaVTight");
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets, readGenObjects);
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if(! readGenObjects)
    {
      if ( branchName_genLeptons1 != "" || branchName_genLeptons2 != "" ) {
        genLeptonReader = new GenLeptonReader(Form("n%s", branchName_genLeptons1.data()), branchName_genLeptons1, Form("n%s", branchName_genLeptons2.data()), branchName_genLeptons2);
        inputTree->registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(Form("n%s", branchName_genHadTaus.data()), branchName_genHadTaus);
        inputTree->registerReader(genHadTauReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(Form("n%s", branchName_genJets.data()), branchName_genJets);
        inputTree->registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader();
    inputTree->registerReader(lheInfoReader);
  }

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    trained by Arun for 2l_2tau category
  std::string mvaFileName_2l_2tau_ttV = "tthAnalysis/HiggsToTauTau/data/2l_2tau_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_2tau_ttV;
  mvaInputVariables_2l_2tau_ttV.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2l_2tau_ttV.push_back("nJet");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("avg_dr_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("lep2_conePt");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep1_tau1");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep1_tau2");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep2_tau1");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep2_tau2");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_tau1_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_tau2_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("mT_lep2");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_leps");
  mvaInputVariables_2l_2tau_ttV.push_back("tau1_pt");
  mvaInputVariables_2l_2tau_ttV.push_back("TMath::Abs(tau1_eta)");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_taus");
  mvaInputVariables_2l_2tau_ttV.push_back("mTauTauVis");
  mvaInputVariables_2l_2tau_ttV.push_back("hadTauPairCharge");
  mvaInputVariables_2l_2tau_ttV.push_back("nBJetLoose");
  TMVAInterface mva_2l_2tau_ttV(mvaFileName_2l_2tau_ttV, mvaInputVariables_2l_2tau_ttV);

  std::string mvaFileName_2l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/2l_2tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_2tau_ttbar;
  mvaInputVariables_2l_2tau_ttbar.push_back("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))");
  mvaInputVariables_2l_2tau_ttbar.push_back("nJet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep1_tau1");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep1_tau2");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep2_tau1");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep2_tau2");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_tau1_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_tau2_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mT_lep1");
  mvaInputVariables_2l_2tau_ttbar.push_back("mT_lep2");
  mvaInputVariables_2l_2tau_ttbar.push_back("tau1_pt");
  mvaInputVariables_2l_2tau_ttbar.push_back("tau2_pt");
  mvaInputVariables_2l_2tau_ttbar.push_back("TMath::Abs(tau1_eta)");
  mvaInputVariables_2l_2tau_ttbar.push_back("TMath::Abs(tau2_eta)");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_taus");
  mvaInputVariables_2l_2tau_ttbar.push_back("mTauTauVis");
  mvaInputVariables_2l_2tau_ttbar.push_back("leptonPairCharge");
  mvaInputVariables_2l_2tau_ttbar.push_back("hadTauPairCharge");
  mvaInputVariables_2l_2tau_ttbar.push_back("nBJetLoose");
  mvaInputVariables_2l_2tau_ttbar.push_back("nBJetMedium");
  TMVAInterface mva_2l_2tau_ttbar(mvaFileName_2l_2tau_ttbar, mvaInputVariables_2l_2tau_ttbar);

  std::vector<std::string> mvaInputVariables_2l_2tau = get_mvaInputVariables(mvaInputVariables_2l_2tau_ttV, mvaInputVariables_2l_2tau_ttbar);
  std::map<std::string, double> mvaInputs_2l_2tau;

  std::string inputFileNam_mva_mapping_2l_2tau = "tthAnalysis/HiggsToTauTau/data/2l_2tau_BDT_mapping.root";
  TFile* inputFile_mva_mapping_2l_2tau = openFile(LocalFileInPath(inputFileNam_mva_mapping_2l_2tau));
  TH2* mva_mapping_2l_2tau = loadTH2(inputFile_mva_mapping_2l_2tau, "hTargetBinning");

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;

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
    EvtHistManager_2l_2tau* evt_;
  };
  typedef std::map<int, preselHistManagerType*> int_to_preselHistManagerMap;
  std::map<int, int_to_preselHistManagerMap> preselHistManagers;
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
    MVAInputVarHistManager* mvaInputVariables_2l_2tau_;
    EvtHistManager_2l_2tau* evt_;
    std::map<std::string, EvtHistManager_2l_2tau*> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_2l_2tau*> evt_in_categories_;
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
      preselHistManager->evt_ = new EvtHistManager_2l_2tau(makeHistManager_cfg(process_and_genMatch,
        Form("%s/presel/evt", histogramDir.data()), era_string, central_or_shift));
      preselHistManager->evt_->bookHistograms(fs);
      preselHistManagers[idxLepton][idxHadTau] = preselHistManager;

      selHistManagerType* selHistManager = new selHistManagerType();
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
      selHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadHadTau", histogramDir.data()), central_or_shift));
      selHistManager->leadHadTau_->bookHistograms(fs);
      selHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadHadTau", histogramDir.data()), central_or_shift));
      selHistManager->subleadHadTau_->bookHistograms(fs);
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
      selHistManager->mvaInputVariables_2l_2tau_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/mvaInputs_2l_2tau", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_2l_2tau_->bookHistograms(fs, mvaInputVariables_2l_2tau);
      selHistManager->evt_ = new EvtHistManager_2l_2tau(makeHistManager_cfg(process_and_genMatch,
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

          selHistManager -> evt_in_decayModes_[decayMode_evt] = new EvtHistManager_2l_2tau(makeHistManager_cfg(
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

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), central_or_shift)
    );
    bdt_filler -> register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_tth_mva", "mindr_lep1_jet", "mT_lep1", "dr_lep1_tau1", "dr_lep1_tau2",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_tth_mva", "mindr_lep2_jet", "mT_lep2", "dr_lep2_tau1", "dr_lep2_tau2",
      "mindr_tau1_jet", "mindr_tau2_jet", "avg_dr_jet", "ptmiss",  "htmiss", "tau1_mva", "tau1_pt", "tau1_eta", "tau2_mva", "tau2_pt", "tau2_eta", "dr_leps", "dr_taus",
      "mTauTauVis", "cosThetaS_hadTau", "cosThetaS_GenTau",
      "leptonPairCharge", "hadTauPairCharge", "lumiScale", "genWeight", "evtWeight",
      "lep1_genLepPt", "lep2_genLepPt", "tau1_genTauPt", "tau2_genTauPt",
      "lep1_fake_prob", "lep2_fake_prob", "tau1_fake_prob", "tau2_fake_prob",
      "tau1_fake_test", "tau2_fake_test", "weight_fakeRate", "weights_dataToMC",
      "hadTau1Charge","hadTau2Charge",
      "pT_LT1",  "pT_LT2",  "mass_LT1",  "mass_LT2",
      "pT_LT1_m",  "pT_LT2_m",  "mass_LT1_m",  "mass_LT2_m",
      "mbb_loose","mbb_medium"
      //"mvaOutput_2l_ttV", "mvaOutput_2l_ttbar", "mvaDiscr_2l"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "is_OS" //, "lep1_isTight", "lep2_isTight", "tau1_isTight", "tau2_isTight"
    );
    bdt_filler -> bookTree(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  CutFlowTableHistManager_2l_2tau* cutFlowHistManager = new CutFlowTableHistManager_2l_2tau(makeHistManager_cfg(process_string,
    Form("%s/sel/cutFlow", histogramDir.data()), central_or_shift));
  cutFlowHistManager->bookHistograms(fs);
  while ( inputTree->hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())) ) {
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

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry #" << inputTree->getCumulativeMaxEventCount() << ": " << eventInfo << std::endl;
      if ( inputTree -> isOpen() ) {
	std::cout << "input File = " << inputTree->getCurrentFileName() << std::endl;
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
      if ( isDEBUG ) {
	printGenLeptonCollection("genLeptons", genLeptons);
	printGenHadTauCollection("genHadTaus", genHadTaus);
	printGenJetCollection("genJets", genJets);
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

    if ( (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
	 (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
	 (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ||
	 (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
	 (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)  ) {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      tightElectronSelector.enable_offline_e_trigger_cuts();
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    //std::cout<<"start cleaning"<<std::endl;
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else if ( leptonSelection == kTight    ) selMuons = tightMuons;
    else assert(0);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else if ( leptonSelection == kTight    ) selElectrons = tightElectrons;
    else assert(0);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(preselHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);
    selHadTaus = pickFirstNobjects(selHadTaus, 2);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus, selElectrons, selMuons);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

//--- build collections of generator level particles (after some cuts are applied, to save computing time)
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

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.2);

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
    // require exactly two leptons passing loose preselection criteria
    if ( !(preselLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS preselLeptons selection." << std::endl;
	printLeptonCollection("preselLeptons", preselLeptons);
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

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    std::sort(preselHadTaus.begin(), preselHadTaus.end(), isHigherPt);
    if ( !(preselHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 presel taus");
    cutFlowHistManager->fillHistograms(">= 2 presel taus", lumiScale);
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    const hadTauGenMatchEntry& preselHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, preselHadTau_lead, preselHadTau_sublead);
    int idxPreselHadTau_genMatch = preselHadTau_genMatch.idx_;
    assert(idxPreselHadTau_genMatch != kGen_HadTauUndefined2);

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !((int)selJets.size() >= minNumJets) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	printJetCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (1)", minNumJets));
    cutFlowHistManager->fillHistograms(">= N jets (1)", lumiScale);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	printJetCollection("selJets", selJets);
	printJetCollection("selBJets_loose", selBJets_loose);
	printJetCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", lumiScale);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

    double mTauTauVis_presel = (preselHadTau_lead->p4() + preselHadTau_sublead->p4()).mass();

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselLepton_genMatch][idxPreselHadTau_genMatch];
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
      -1., -1., -1.,
      mTauTauVis_presel, preselLepton_lead->charge() + preselLepton_sublead->charge(), preselHadTau_lead->charge() + preselHadTau_sublead->charge(),
      1.);

//--- apply final event selection
    std::vector<const RecoLepton*> selLeptons;
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly two leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selLeptons selection." << std::endl;
	printLeptonCollection("selLeptons", selLeptons);
	//printLeptonCollection("preselLeptons", preselLeptons);
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
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= sgn(eventInfo.genWeight);
      if ( isMC_tH ) evtWeight *= eventInfo.genWeight_tH;
      evtWeight *= eventInfo.pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      double btagWeight = 1.;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	btagWeight *= (*jet)->BtagWeight();
      }
      evtWeight *= btagWeight;
      if ( isDEBUG ) {
	std::cout << "lumiScale = " << lumiScale << std::endl;
	if ( apply_genWeight ) std::cout << "genWeight = " << sgn(eventInfo.genWeight) << std::endl;
	std::cout << "pileupWeight = " << eventInfo.pileupWeight << std::endl;
	std::cout << "btagWeight = " << btagWeight << std::endl;
      }
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
	printLeptonCollection("tightLeptons", tightLeptons);
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

    if ( !(selHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined2);

    double mTauTauVis = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
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
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if ( leptonSelection == kFakeable ) {
	weight_data_to_MC_correction = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
        weight_data_to_MC_correction = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->decayMode(),
        selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->decayMode());
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      if ( isDEBUG ) {
	std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }

      evtWeight *= weight_data_to_MC_correction;
    }

    bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
    bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTaus);
    bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
    bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTaus);

    double weight_fakeRate = 1.;
    double prob_fake_lepton_lead = 1.;
    double prob_fake_lepton_sublead = 1.;
    if(leptonFakeRateInterface) {
        if      ( std::abs(selLepton_lead->pdgId()) == 11 )
          {prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->cone_pt(), selLepton_lead->absEta());}
        else if ( std::abs(selLepton_lead->pdgId()) == 13 )
          {prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->cone_pt(), selLepton_lead->absEta());}
        else assert(0);
        if      ( std::abs(selLepton_sublead->pdgId()) == 11 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());}
        else if ( std::abs(selLepton_sublead->pdgId()) == 13 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());}
        else assert(0);
    }

    double prob_fake_hadTau_lead = 1.;
    double prob_fake_hadTau_sublead = 1.;
    if(jetToTauFakeRateInterface) {
    prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
    prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
    }

    if ( applyFakeRateWeights == kFR_4L )  {
      weight_fakeRate = getWeight_4L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead,
        prob_fake_hadTau_lead, passesTight_hadTau_lead,
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );
    } else if ( applyFakeRateWeights == kFR_2lepton)  {
      weight_fakeRate = getWeight_2L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead
      );
    } else if ( applyFakeRateWeights == kFR_2tau) {
      weight_fakeRate = getWeight_2L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead,
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );
    }

	// CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
	double weight_data_to_MC_correction_hadTau_lead = 1.;
	double weight_data_to_MC_correction_hadTau_sublead = 1.;
	if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight ) {
	if ( !(selHadTau_lead->genHadTau() || selHadTau_lead->genLepton()) ) {
	  weight_data_to_MC_correction_hadTau_lead = jetToTauFakeRateInterface->getSF_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
	}
	if ( !(selHadTau_sublead->genHadTau() || selHadTau_sublead->genLepton()) ) {
	  weight_data_to_MC_correction_hadTau_sublead = jetToTauFakeRateInterface->getSF_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
	}
	if ( isDEBUG ) {
	  std::cout << "weight_data_to_MC_correction_hadTau:"
		    << " lead = " << weight_data_to_MC_correction_hadTau_lead << ","
		    << " sublead = " << weight_data_to_MC_correction_hadTau_sublead << std::endl;
	}
      evtWeight *= (weight_data_to_MC_correction_hadTau_lead*weight_data_to_MC_correction_hadTau_sublead);
      }
	if ( !selectBDT ) evtWeight *= weight_fakeRate;

    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !((int)selJets.size() >= minNumJets) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	printJetCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (2)", minNumJets), evtWeight);
    cutFlowHistManager->fillHistograms(">= N jets (2)", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1)) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	printJetCollection("selJets", selJets);
	printJetCollection("selBJets_loose", selBJets_loose);
	printJetCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
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
	std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    double minPt_lead = -1.;
    if      ( era == kEra_2015 ) minPt_lead = 20.;
    else if ( era == kEra_2016 ) minPt_lead = 25.; // CV: increase minimum lepton pT cut to 25 GeV to keep-up with higher trigger thresholds in 2016 data
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
    if ( leptonChargeSelection != kDisabled ) {
      cutFlowTable.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeight);
    }
    cutFlowHistManager->fillHistograms("sel lepton-pair OS/SS charge", evtWeight);

    bool isCharge_hadTau_SS = selHadTau_lead->charge()*selHadTau_sublead->charge() > 0;
    bool isCharge_hadTau_OS = selHadTau_lead->charge()*selHadTau_sublead->charge() < 0;
    if ( hadTauChargeSelection == kOS && isCharge_hadTau_SS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS hadTau charge selection." << std::endl;
	std::cout << " (leading selHadTau charge = " << selHadTau_lead->charge()
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ", hadTauChargeSelection = SS)" << std::endl;
      }
      continue;
    }
    if ( hadTauChargeSelection == kSS && isCharge_hadTau_OS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS hadTau charge selection." << std::endl;
	std::cout << " (leading selHadTau charge = " << selHadTau_lead->charge()
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ", hadTauChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( hadTauChargeSelection != kDisabled ) {
      cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);
    }
    cutFlowHistManager->fillHistograms("tau-pair OS/SS charge", evtWeight);

    if ( (chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) != 0) ||
	 (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) == 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
		  << ", subleading selLepton charge = " << selLepton_sublead->charge()
		  << ", leading selHadTau charge = " << selHadTau_lead->charge()
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton+tau charge", evtWeight);

    bool isSameFlavor_OS = false;
    double massSameFlavor_OS = -1.;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = fakeableLeptons.begin();
	  lepton1 != fakeableLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != fakeableLeptons.end(); ++lepton2 ) {
	if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // pair of same flavor leptons of opposite charge
	  isSameFlavor_OS = true;
	  double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	  if ( std::fabs(mass - z_mass) < std::fabs(massSameFlavor_OS - z_mass) ) massSameFlavor_OS = mass;
	}
      }
    }

    bool failsZbosonMassVeto = isSameFlavor_OS && std::fabs(massSameFlavor_OS - z_mass) < z_window;
    if ( failsZbosonMassVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS Z-boson veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeight);
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeight);

    double met_LD_cut = 0.;
    if      ( selJets.size() >= 4 ) met_LD_cut = -1.; // MET LD cut not applied
    else if ( isSameFlavor_OS     ) met_LD_cut =  0.3;
    else                            met_LD_cut =  0.2;
    if ( met_LD_cut > 0 && met_LD < met_LD_cut ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS MET LD selection." << std::endl;
	std::cout << " (met_LD = " << met_LD << ", met_LD_cut = " << met_LD_cut << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("met LD", evtWeight);
    cutFlowHistManager->fillHistograms("met LD", evtWeight);

    if ( leptonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( (tightMuons.size() + tightElectrons.size()) >= 2 && tightHadTaus.size() >= 2 ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS tightElectrons+tightMuons selection." << std::endl;
	  std::cout << " (#tightElectrons = " << tightElectrons.size() << ", #tightMuons = " << tightMuons.size() << ", #tightHadTaus = " << tightHadTaus.size() << ")" << std::endl;
	}
	continue; // CV: avoid overlap with signal region
      }
      cutFlowTable.update("signal region veto", evtWeight);
      cutFlowHistManager->fillHistograms("signal region veto", evtWeight);
    }

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar
//    trained by Arun for 2l_2tau category
    mvaInputs_2l_2tau["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = TMath::Max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    mvaInputs_2l_2tau["nJet"] = selJets.size();
    mvaInputs_2l_2tau["mindr_lep1_jet"] = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    mvaInputs_2l_2tau["mindr_lep2_jet"] = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets));
    mvaInputs_2l_2tau["avg_dr_jet"] = comp_avg_dr_jet(selJets);
    mvaInputs_2l_2tau["lep2_conePt"] = comp_lep2_conePt(*selLepton_sublead);
    mvaInputs_2l_2tau["dr_lep1_tau1"] = deltaR(selLepton_lead->p4(), selHadTau_lead->p4());
    mvaInputs_2l_2tau["dr_lep1_tau2"] = deltaR(selLepton_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_2l_2tau["dr_lep2_tau1"] = deltaR(selLepton_sublead->p4(), selHadTau_lead->p4());
    mvaInputs_2l_2tau["dr_lep2_tau2"] = deltaR(selLepton_sublead->p4(), selHadTau_sublead->p4());
    mvaInputs_2l_2tau["mindr_tau1_jet"] = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets));
    mvaInputs_2l_2tau["mindr_tau2_jet"] = TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets));
    mvaInputs_2l_2tau["mT_lep1"] = comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi());
    mvaInputs_2l_2tau["mT_lep2"] = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
    mvaInputs_2l_2tau["dr_leps"] = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    mvaInputs_2l_2tau["tau1_pt"] = selHadTau_lead->pt();
    mvaInputs_2l_2tau["tau2_pt"] = selHadTau_sublead->pt();
    mvaInputs_2l_2tau["TMath::Abs(tau1_eta)"] = selHadTau_lead->absEta();
    mvaInputs_2l_2tau["TMath::Abs(tau2_eta)"] = selHadTau_sublead->absEta();
    mvaInputs_2l_2tau["dr_taus"] = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_2l_2tau["mTauTauVis"] = mTauTauVis;
    mvaInputs_2l_2tau["leptonPairCharge"] = selLepton_lead->charge() + selLepton_sublead->charge();
    mvaInputs_2l_2tau["hadTauPairCharge"] = selHadTau_lead->charge() + selHadTau_sublead->charge();
    mvaInputs_2l_2tau["nBJetLoose"] = selBJets_loose.size();
    mvaInputs_2l_2tau["nBJetMedium"] = selBJets_medium.size();

    check_mvaInputs(mvaInputs_2l_2tau, eventInfo);

    double mvaOutput_2l_2tau_ttV = mva_2l_2tau_ttV(mvaInputs_2l_2tau);
    double mvaOutput_2l_2tau_ttbar = mva_2l_2tau_ttbar(mvaInputs_2l_2tau);

    Double_t mvaDiscr_2l_2tau = getSF_from_TH2(mva_mapping_2l_2tau, mvaOutput_2l_2tau_ttbar, mvaOutput_2l_2tau_ttV) + 1.;

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
    selHistManager->mvaInputVariables_2l_2tau_->fillHistograms(mvaInputs_2l_2tau, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(), selMuons.size(), selHadTaus.size(),
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_2l_2tau_ttV, mvaOutput_2l_2tau_ttbar, mvaDiscr_2l_2tau,
      mTauTauVis, selLepton_lead->charge() + selLepton_sublead->charge(), selHadTau_lead->charge() + selHadTau_sublead->charge(),
      evtWeight);
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
	  mvaOutput_2l_2tau_ttV,
	  mvaOutput_2l_2tau_ttbar,
	  mvaDiscr_2l_2tau,
          mTauTauVis,
          selLepton_lead->charge() + selLepton_sublead->charge(),
          selHadTau_lead->charge() + selHadTau_sublead->charge(),
          evtWeight
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

    if ( bdt_filler ) {

      double lep1_genLepPt =  (selLepton_lead->genLepton() != 0)  ? selLepton_lead->genLepton()->pt() : 0. ;
      double lep2_genLepPt = (selLepton_sublead->genLepton() != 0)  ? selLepton_sublead->genLepton()->pt() : 0. ;
      double tau1_genTauPt =  (selHadTau_lead->genHadTau() != 0)  ? selHadTau_lead->genHadTau()->pt() : 0. ;
      double tau2_genTauPt = (selHadTau_sublead->genHadTau() != 0) ? selHadTau_sublead->genHadTau()->pt() : 0. ;
      //std::cout<<"pts "<<lep1_genLepPt <<" "<<lep2_genLepPt<<" "<<tau1_genTauPt <<" "<<tau2_genTauPt<<std::endl;

      int is_OS=1;
      if (abs(selLepton_lead->charge() -selLepton_sublead->charge() ) < 0.1) is_OS=0;

      std::cout<<"calculate pt balance"<<std::endl;
      double ptLLeadTLead=abs((selLepton_lead->p4()+selHadTau_lead -> p4()).pt() - (selLepton_sublead->p4()+selHadTau_sublead -> p4()).pt());
      double ptLLeadTSLead=abs((selLepton_lead->p4()+selHadTau_sublead -> p4()).pt() - (selLepton_sublead->p4()+selHadTau_lead -> p4()).pt());
      double pT_LT1 = -1;
      double pT_LT2 = -1;
      double pT_LT1_dumb = -1;
      double pT_LT2_dumb = -1;
      double mass_LT1 = -1;
      double mass_LT2 = -1;
      if (ptLLeadTLead > ptLLeadTSLead) {
        pT_LT1_dumb=(selLepton_lead->p4()+selHadTau_sublead -> p4()).pt();
        pT_LT2_dumb=(selLepton_sublead->p4()+selHadTau_lead -> p4()).pt();
      } else if (ptLLeadTLead < ptLLeadTSLead) {
        pT_LT1_dumb=(selLepton_lead->p4()+selHadTau_lead -> p4()).pt();
        pT_LT2_dumb=(selLepton_sublead->p4()+selHadTau_sublead -> p4()).pt();
      }
      // order by by pt
      if (pT_LT1_dumb>pT_LT2_dumb){
        pT_LT1=pT_LT1_dumb;
        pT_LT2=pT_LT2_dumb;
        mass_LT1=(selLepton_lead->p4()+selHadTau_sublead -> p4()).M();
        mass_LT2=(selLepton_sublead->p4()+selHadTau_lead -> p4()).M();
      } else {
        pT_LT2=pT_LT1_dumb;
        pT_LT1=pT_LT2_dumb;
        mass_LT2=(selLepton_lead->p4()+selHadTau_sublead -> p4()).M();
        mass_LT1=(selLepton_sublead->p4()+selHadTau_lead -> p4()).M();
      }

      std::cout<<"calculate mass balance"<<std::endl;
      double massLLeadTLead=abs((selLepton_lead->p4()+selHadTau_lead -> p4()).M() - (selLepton_sublead->p4()+selHadTau_sublead -> p4()).M());
      double massLLeadTSLead=abs((selLepton_lead->p4()+selHadTau_sublead -> p4()).M() - (selLepton_sublead->p4()+selHadTau_lead -> p4()).M());
      double pT_LT1_m = -1;
      double pT_LT2_m = -1;
      double pT_LT1_m_dumb = -1;
      double pT_LT2_m_dumb = -1;
      double mass_LT1_m = -1;
      double mass_LT2_m = -1;
      if (massLLeadTLead > massLLeadTSLead) {
        pT_LT1_m_dumb=(selLepton_lead->p4()+selHadTau_sublead -> p4()).pt();
        pT_LT2_m_dumb=(selLepton_sublead->p4()+selHadTau_lead -> p4()).pt();
      } else if (massLLeadTLead < massLLeadTSLead) {
        pT_LT1_m_dumb=(selLepton_lead->p4()+selHadTau_lead -> p4()).pt();
        pT_LT2_m_dumb=(selLepton_sublead->p4()+selHadTau_sublead -> p4()).pt();
      }
      // order by by pt
      if (pT_LT1_m_dumb>pT_LT2_m_dumb){
        pT_LT1_m=pT_LT1_m_dumb;
        pT_LT2_m=pT_LT2_m_dumb;
        mass_LT1_m=(selLepton_lead->p4()+selHadTau_sublead -> p4()).M();
        mass_LT2_m=(selLepton_sublead->p4()+selHadTau_lead -> p4()).M();
      } else {
        pT_LT2_m=pT_LT1_m_dumb;
        pT_LT1_m=pT_LT2_m_dumb;
        mass_LT2_m=(selLepton_lead->p4()+selHadTau_sublead -> p4()).M();
        mass_LT1_m=(selLepton_sublead->p4()+selHadTau_lead -> p4()).M();
      }

      double cosThetaS_hadTau=-100;
      comp_cosThetaS(selHadTau_lead->p4(), selHadTau_sublead->p4(), cosThetaS_hadTau);

      double cosThetaS_GenTau=-4;
      if (selHadTau_lead->genHadTau() != 0 && selHadTau_sublead->genHadTau() != 0)  comp_cosThetaS(selHadTau_lead->p4(), selHadTau_sublead->p4(), cosThetaS_GenTau);

      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
          ("lep1_pt",              selLepton_lead -> pt())
          ("lep1_conePt",          comp_lep1_conePt(*selLepton_lead))
          ("lep1_eta",             selLepton_lead -> eta())
          ("lep1_tth_mva",         selLepton_lead -> mvaRawTTH())
          ("mindr_lep1_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets)))
          ("mT_lep1",              comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi()))
          ("dr_lep1_tau1",         deltaR(selLepton_lead -> p4(), selHadTau_lead -> p4()))
          ("dr_lep1_tau2",         deltaR(selLepton_lead -> p4(), selHadTau_sublead -> p4()))
          ("lep2_pt",              selLepton_sublead -> pt())
          ("lep2_conePt",          comp_lep2_conePt(*selLepton_sublead))
          ("lep2_eta",             selLepton_sublead -> eta())
          ("lep2_tth_mva",         selLepton_sublead -> mvaRawTTH())
          ("mindr_lep2_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets)))
          ("mT_lep2",              comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi()))
          ("dr_lep2_tau1",         deltaR(selLepton_sublead -> p4(), selHadTau_lead -> p4()))
          ("dr_lep2_tau2",         deltaR(selLepton_sublead -> p4(), selHadTau_sublead -> p4()))
          ("mindr_tau1_jet",       TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets)))
          ("mindr_tau2_jet",       TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets)))
          ("avg_dr_jet",           comp_avg_dr_jet(selJets))
          ("ptmiss",               met.pt())
          ("htmiss",               mht_p4.pt())
          ("tau1_mva",             selHadTau_lead -> raw_mva_dR03())
          ("tau2_mva",             selHadTau_sublead -> raw_mva_dR03())
          ("tau1_pt",              selHadTau_lead -> pt())
          ("tau2_pt",              selHadTau_sublead -> pt())
          ("tau1_eta",             selHadTau_lead -> eta())
          ("tau2_eta",             selHadTau_sublead -> eta())
          ("dr_taus",              deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4()))
          ("dr_leps",              deltaR(selLepton_lead -> p4(), selLepton_sublead -> p4()))
          ("mTauTauVis",           mTauTauVis)
          ("cosThetaS_hadTau",     cosThetaS_hadTau)
          ("cosThetaS_GenTau",      cosThetaS_GenTau)
          ("leptonPairCharge",     selLepton_lead->charge() + selLepton_sublead->charge())
          ("hadTauPairCharge",     selHadTau_lead->charge() + selHadTau_sublead->charge())
          ("hadTau1Charge",     selHadTau_lead->charge() )
          ("hadTau2Charge",     selHadTau_sublead->charge())
          ("lep1_genLepPt",       lep1_genLepPt)
          ("lep2_genLepPt",       lep2_genLepPt)
          ("tau1_genTauPt",       tau1_genTauPt)
          ("tau2_genTauPt",       tau2_genTauPt)
          ("lep1_fake_prob", ( selLepton_lead->genLepton() != 0 ) ? 1.0 : prob_fake_lepton_lead )
          ("lep2_fake_prob", ( selLepton_sublead->genLepton() != 0 ) ? 1.0 : prob_fake_lepton_sublead)
          ("tau1_fake_prob", ( selHadTau_lead->genHadTau() != 0 || selHadTau_lead->genLepton() != 0 ) ? 1.0 : prob_fake_hadTau_lead )
          ("tau2_fake_prob", ( selHadTau_sublead->genHadTau() != 0 || selHadTau_sublead->genLepton() != 0 ) ? 1.0 : prob_fake_hadTau_sublead )
          //  treat leptons that are reconstructed as hadronic taus as non-fakes (for hadronic taus, the fake rates refer to jet->tau fakes).
          ("tau1_fake_test", ( selHadTau_lead->genHadTau() != 0 ) ? 1.0 : prob_fake_hadTau_lead )
          ("tau2_fake_test", ( selHadTau_sublead->genHadTau() != 0 ) ? 1.0 : prob_fake_hadTau_sublead )
          ("weight_fakeRate", weight_fakeRate)
          ("weights_dataToMC", (weight_data_to_MC_correction_hadTau_lead*weight_data_to_MC_correction_hadTau_sublead))
          ("pT_LT1", pT_LT1)
          ("pT_LT2", pT_LT2)
          ("mass_LT1", mass_LT1)
          ("mass_LT2", mass_LT2)
          ("pT_LT1_m", pT_LT1_m)
          ("pT_LT2_m", pT_LT2_m)
          ("mass_LT1_m", mass_LT1_m)
          ("mass_LT2_m", mass_LT2_m)
          ("mbb_loose",           selBJets_loose.size()>1 ?  (selBJets_loose[0]->p4()+selBJets_loose[1]->p4()).mass() : -1000 )
          ("mbb_medium",          selBJets_medium.size()>1 ?  (selBJets_medium[0]->p4()+selBJets_medium[1]->p4()).mass() : -1000 )
          ("lumiScale",            lumiScale)
          ("genWeight",            eventInfo.genWeight)
          ("evtWeight",            evtWeight)
          ("nJet",                 selJets.size())
          ("nBJetLoose",           selBJets_loose.size())
          ("nBJetMedium",          selBJets_medium.size())
          ("is_OS",                is_OS)
        .fill()
      ;
    }
    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
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
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete cutFlowHistManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;

  clock.Show("analyze_2l_2tau");

  return EXIT_SUCCESS;
}
