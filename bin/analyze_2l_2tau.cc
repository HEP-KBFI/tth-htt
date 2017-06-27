
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
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
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
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerUnits.h" // ...
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerMEM.h" // NtupleFillerMEM
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

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

#define EPS 1E-2

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_2lepton, kFR_4L, kFR_2tau };


const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString = {
  { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
  { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
  { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
};

//const int hadTauSelection_antiElectron_lead = 1; // vLoose
//const int hadTauSelection_antiMuon_lead = 1; // Loose 
//const int hadTauSelection_antiElectron_sublead = 2; // Loose
//const int hadTauSelection_antiMuon_sublead = 1; // Loose
const int hadTauSelection_antiElectron_lead = -1; // not applied
const int hadTauSelection_antiMuon_lead = -1; // not applied 
const int hadTauSelection_antiElectron_sublead = -1; // not applied
const int hadTauSelection_antiMuon_sublead = -1; // not applied

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

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

  int minNumJets = cfg_analyze.getParameter<int>("minNumJets");
  std::cout << "minNumJets = " << minNumJets << std::endl;
    
  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
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
      else cms::Exception("analyze_2l_2tau")
	<< "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      if ( isMC ) {
	jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
	if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
	else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
	else assert(0);
      } else cms::Exception("analyze_2l_2tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
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
      } else cms::Exception("analyze_2l_2tau")
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
      } else cms::Exception("analyze_2l_2tau")
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
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_lead", hadTauSelection_antiElectron_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_lead", hadTauSelection_antiMuon_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_sublead", hadTauSelection_antiElectron_sublead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_sublead", hadTauSelection_antiMuon_sublead);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

  ///////////////////////////// not sure yet which weights are needed
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
  if ( applyFakeRateWeights == kFR_4L || applyFakeRateWeights == kFR_2tau || apply_hadTauFakeRateSF ) {
									  
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
  std::string branchName_memOutput = cfg_analyze.getParameter<std::string>("branchName_memOutput");

  std::string branchName_genLeptons1 = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  std::string branchName_genLeptons2 = cfg_analyze.getParameter<std::string>("branchName_genLeptons2");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  
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
  
  std::string selEventsTFileName = cfg_analyze.getParameter<std::string>("selEventsTFileName");
  const bool writeSelEventsFile = selEventsTFileName != "";

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TChain* inputTree = new TChain(treeName.data());
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("analyze_2l_2tau") 
      << "Failed to identify input Tree !!\n";
  }
  
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);
  
//--- create output root file from selected events if needed
  NtupleFillerMEM mem;
  if ( writeSelEventsFile ) {
    mem.use2016(era == kEra_2016);
    mem.isSignal(isSignal);
    mem.setFileName(selEventsTFileName);
  }

  std::cout << "input Tree contains " << inputTree->GetEntries() << " Entries in " << inputTree->GetListOfFiles()->GetEntries() << " files." << std::endl;

//--- declare event-level variables
  RUN_TYPE run;
  inputTree->SetBranchAddress(RUN_KEY, &run);
  LUMI_TYPE lumi;
  inputTree->SetBranchAddress(LUMI_KEY, &lumi);
  EVT_TYPE event;
  inputTree->SetBranchAddress(EVT_KEY, &event);
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode;
  if ( isSignal ) {
    inputTree->SetBranchAddress(GENHIGGSDECAYMODE_KEY, &genHiggsDecayMode);
  }

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_2e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_2mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

  GENWEIGHT_TYPE genWeight = 1.;
  PUWEIGHT_TYPE pileupWeight = 1.;
  if ( isMC ) {
    inputTree->SetBranchAddress(GENWEIGHT_KEY, &genWeight);
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons);
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, run_lumi_eventSelector != 0);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, run_lumi_eventSelector != 0);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
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
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met);
  metReader->setBranchAddresses(inputTree);  

//--- declare likelihoods for signal/background hypotheses, obtained by matrix element method
  MEMOutputReader_2l_2tau* memReader = 0;
  if ( branchName_memOutput != "" ) {
    memReader = new MEMOutputReader_2l_2tau(Form("n%s", branchName_memOutput.data()), branchName_memOutput);
    memReader->setBranchAddresses(inputTree); 
  }

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  GenParticleReader* genNuFromTauReader = 0;
  GenParticleReader* genTauReader = 0;
  GenParticleReader* genLepFromTopReader = 0;
  GenParticleReader* genBQuarkFromTopReader = 0;
  GenParticleReader* genNuFromTopReader = 0;
  GenParticleReader* genLepFromTauReader = 0;
  GenParticleReader* genTopReader = 0;
  GenParticleReader* genVbosonsReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader(Form("n%s", branchName_genLeptons1.data()), branchName_genLeptons1, Form("n%s", branchName_genLeptons2.data()), branchName_genLeptons2);
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader(Form("n%s", branchName_genHadTaus.data()), branchName_genHadTaus);
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader(Form("n%s", branchName_genJets.data()), branchName_genJets);
    genJetReader->setBranchAddresses(inputTree);
    lheInfoReader = new LHEInfoReader();
    lheInfoReader->setBranchAddresses(inputTree);
    if ( writeSelEventsFile && era == kEra_2016 ){
      genNuFromTauReader = new GenParticleReader("nGenNuFromTau", "GenNuFromTau");
      genNuFromTauReader->setBranchAddresses(inputTree);
      genTauReader = new GenParticleReader("nGenTaus", "GenTaus");
      genTauReader->setBranchAddresses(inputTree);
      genLepFromTopReader = new GenParticleReader("nGenLepFromTop", "GenLepFromTop");
      genLepFromTopReader->setBranchAddresses(inputTree);
      genBQuarkFromTopReader = new GenParticleReader("nGenBQuarkFromTop", "GenBQuarkFromTop");
      genBQuarkFromTopReader->setBranchAddresses(inputTree);
      genNuFromTopReader = new GenParticleReader("nGenNuFromTop", "GenNuFromTop");
      genNuFromTopReader->setBranchAddresses(inputTree);
      genLepFromTauReader = new GenParticleReader("nGenLepFromTau", "GenLepFromTau");
      genLepFromTauReader->setBranchAddresses(inputTree);
      genTopReader = new GenParticleReader("nGenTop", "GenTop");
      genTopReader->setBranchAddresses(inputTree);
      genVbosonsReader = new GenParticleReader("nGenVbosons", "GenVbosons");
      genVbosonsReader->setBranchAddresses(inputTree);
    }
  }

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2l category of ttH multilepton analysis
  std::string mvaFileName_2l_ttV = "tthAnalysis/HiggsToTauTau/data/2l_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_ttV;
  mvaInputVariables_2l_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2l_ttV.push_back("MT_met_lep1");
  mvaInputVariables_2l_ttV.push_back("nJet25_Recl");
  mvaInputVariables_2l_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2l_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  TMVAInterface mva_2l_ttV(mvaFileName_2l_ttV, mvaInputVariables_2l_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2l_ttbar = "tthAnalysis/HiggsToTauTau/data/2l_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_ttbar;
  mvaInputVariables_2l_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2l_ttbar.push_back("MT_met_lep1");
  mvaInputVariables_2l_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2l_ttbar.push_back("mhtJet25_Recl");
  mvaInputVariables_2l_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2l_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_ttbar.push_back("mindr_lep2_jet");
  TMVAInterface mva_2l_ttbar(mvaFileName_2l_ttbar, mvaInputVariables_2l_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_2l = get_mvaInputVariables(mvaInputVariables_2l_ttV, mvaInputVariables_2l_ttbar);
  std::map<std::string, double> mvaInputs_2l;

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    trained by Arun for 2l_2tau category 
  std::string mvaFileName_2l_2tau_ttV = "tthAnalysis/HiggsToTauTau/data/2l_2tau_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_2tau_ttV;
  mvaInputVariables_2l_2tau_ttV.push_back("nJet");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("lep1_conePt");
  mvaInputVariables_2l_2tau_ttV.push_back("lep2_conePt");
  mvaInputVariables_2l_2tau_ttV.push_back("mindr_tau_jet");
  mvaInputVariables_2l_2tau_ttV.push_back("tau_pt");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep1_tau");
  mvaInputVariables_2l_2tau_ttV.push_back("dr_lep2_tau");
  mvaInputVariables_2l_2tau_ttV.push_back("mTauTauVis");
  TMVAInterface mva_2l_2tau_ttV(mvaFileName_2l_2tau_ttV, mvaInputVariables_2l_2tau_ttV);

  std::string mvaFileName_2l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/2l_2tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2l_2tau_ttbar;
  mvaInputVariables_2l_2tau_ttbar.push_back("nJet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("mindr_tau_jet");
  mvaInputVariables_2l_2tau_ttbar.push_back("tau_pt");
  mvaInputVariables_2l_2tau_ttbar.push_back("TMath::Abs(tau_eta)");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep1_tau");
  mvaInputVariables_2l_2tau_ttbar.push_back("dr_lep2_tau");
  mvaInputVariables_2l_2tau_ttbar.push_back("mTauTauVis");
  TMVAInterface mva_2l_2tau_ttbar(mvaFileName_2l_2tau_ttbar, mvaInputVariables_2l_2tau_ttbar);

  std::vector<std::string> mvaInputVariables_2l_2tau = get_mvaInputVariables(mvaInputVariables_2l_2tau_ttV, mvaInputVariables_2l_2tau_ttbar);
  std::map<std::string, double> mvaInputs_2l_2tau;

  std::string inputFileNam_mva_mapping_2l_2tau = "tthAnalysis/HiggsToTauTau/data/2l_2tau_BDT_mapping.root";
  TFile* inputFile_mva_mapping_2l_2tau = openFile(LocalFileInPath(inputFileNam_mva_mapping_2l_2tau));
  TH2* mva_mapping_2l_2tau = loadTH2(inputFile_mva_mapping_2l_2tau, "hTargetBinning");

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
 std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
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
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MVAInputVarHistManager* mvaInputVariables_2l_;
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
      selHistManager->mvaInputVariables_2l_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/mvaInputs_2l", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_2l_->bookHistograms(fs, mvaInputVariables_2l);
      selHistManager->mvaInputVariables_2l_2tau_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/mvaInputs_2l_2tau", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_2l_2tau_->bookHistograms(fs, mvaInputVariables_2l_2tau);
      selHistManager->evt_ = new EvtHistManager_2l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
      selHistManager->evt_->bookHistograms(fs);
      vstring decayModes_evt;
      decayModes_evt.reserve(decayMode_idString.size());
      boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes_evt));
     if ( isSignal ) {
      for ( vstring::const_iterator decayMode = decayModes_evt.begin();
          decayMode != decayModes_evt.end(); ++decayMode) {
      std::string decayMode_and_genMatch = *decayMode;
	  if ( apply_leptonGenMatching ) decayMode_and_genMatch += leptonGenMatch_definition->name_;
	  if ( apply_leptonGenMatching && apply_hadTauGenMatching ) decayMode_and_genMatch += "&";
	  if ( apply_hadTauGenMatching ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;
	  
	  selHistManager->evt_in_decayModes_[*decayMode] = new EvtHistManager_2l_2tau(makeHistManager_cfg(decayMode_and_genMatch,
            Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
	  selHistManager->evt_in_decayModes_[*decayMode]->bookHistograms(fs);
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
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/unbiased/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
     lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/lheInfo", histogramDir.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
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
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_tth_mva", "mindr_lep1_jet", "mT_lep1", "dr_lep1_tau",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_tth_mva", "mindr_lep2_jet", "mT_lep2", "dr_lep2_tau",
      "mindr_tau_jet", "avg_dr_jet", "ptmiss",  "htmiss", "tau_mva", "tau_pt", "tau_eta", "dr_leps",
      "mTauTauVis1", "lumiScale", "genWeight", "evtWeight",
      //"memOutput_isValid", "memOutput_errorFlag", "memOutput_ttH", "memOutput_ttZ", "memOutput_LR",
      //"memOutput_ttH_Hww"
      "lep1_genLepPt", "lep2_genLepPt", "tau_genTauPt", 
      "lep1_fake_prob", "lep2_fake_prob", "tau_fake_prob",
      "mvaOutput_2l_ttV", "mvaOutput_2l_ttbar", "mvaDiscr_2l"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium", "lep1_isTight", "lep2_isTight", "tau_isTight"
    );
    bdt_filler -> bookTree(fs);
  }
  
  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  CutFlowTableHistManager_2l_2tau* cutFlowHistManager = new CutFlowTableHistManager_2l_2tau(makeHistManager_cfg(process_string, 
    Form("%s/sel/cutFlow", histogramDir.data()), central_or_shift));
  cutFlowHistManager->bookHistograms(fs);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);
    
    inputTree->GetEntry(idxEntry);

    if ( isDEBUG ) {
      std::cout << "event #" << idxEntry << ": run = " << run << ", lumi = " << lumi << ", event = " << event << std::endl;
    }

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");
    cutFlowHistManager->fillHistograms("run:ls:event selection", lumiScale);

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event << std::endl;
      if ( inputTree->GetFile() ) std::cout << "input File = " << inputTree->GetFile()->GetName() << std::endl;
    }

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
    	    genLepton != genLeptons.end(); ++genLepton ) {
	int abs_pdgId = std::abs(genLepton->pdgId());
	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
      if ( isDEBUG ) {
	 printGenLeptonCollection("genLeptons", genLeptons);
	 printGenHadTauCollection("genHadTaus", genHadTaus);
	 printGenJetCollection("genJets", genJets);
      }
    }
	
    std::vector<GenParticleExt> genNuFromTau;
    std::vector<GenParticleExt> genTau;
    std::vector<GenParticleExt> genLepFromTop;
    std::vector<GenParticleExt> genBQuarkFromTop;
    std::vector<GenParticleExt> genNuFromTop;
    std::vector<GenParticleExt> genLepFromTau;
    std::vector<GenParticleExt> genTop;
    std::vector<GenParticleExt> genVbosons;
    if ( isMC && writeSelEventsFile && era == kEra_2016 ) {
      genHadTaus = genHadTauReader->read();
      genNuFromTau = genNuFromTauReader->read();
      genTau = genTauReader->read();
      genLepFromTop = genLepFromTopReader->read();
      genBQuarkFromTop = genBQuarkFromTopReader->read();
      genNuFromTop = genNuFromTopReader->read();
      genLepFromTau = genLepFromTauReader->read();
      genTop = genTopReader->read();
      genVbosons = genVbosonsReader->read();
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
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
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
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selMuons, selElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);    

//--- build collections of generator level particles (after some cuts are applied, to save computing time)
    if ( isMC && !fillGenEvtHistograms ) {
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

//--- match reconstructed to generator level particles
    if ( isMC ) {
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
    cutFlowTable.update("2 presel lepton");
    cutFlowHistManager->fillHistograms(">= 2 presel leptons", lumiScale);
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    if ( apply_leptonGenMatching_ttZ_workaround ) idxPreselLepton_genMatch = kGen_2l0j;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);


    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      continue;
    }
    if ( preselMuons.size() == 2 && !(selTrigger_1mu || selTrigger_2mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselMuons = " << preselMuons.size() 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_2mu = " << selTrigger_2mu << ")" << std::endl;
      }
      continue;
    }
    if ( preselElectrons.size() == 1 && preselMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", #preselMuons = " << preselMuons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
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

    double mTauTauVis_presel = (preselHadTau_lead->p4() + preselHadTau_sublead->p4()).mass();

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !((int)selJets.size() >= minNumJets) ) { 
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	printJetCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (1)", minNumJets));
    cutFlowHistManager->fillHistograms(Form(">= %i jets (1)", minNumJets), lumiScale);
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
      -1., -1., -1., -1., -1., -1., 
      mTauTauVis1_presel,
      0, 1.);


//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly two leptons passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() == 2) ) {
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
      if ( apply_genWeight ) evtWeight *= sgn(genWeight);														 
      evtWeight *= pileupWeight;
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
	if ( apply_genWeight ) std::cout << "genWeight = " << sgn(genWeight) << std::endl;
	std::cout << "pileupWeight = " << pileupWeight << std::endl;
	std::cout << "btagWeight = " << btagWeight << std::endl;

  
      }

    }


    // require that trigger paths match event category (with event category based on selLeptons);
    if ( selElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl; 
	std::cout << " (#selElectrons = " << selElectrons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      continue;
    }
    if ( selMuons.size() == 2 && !(selTrigger_1mu || selTrigger_2mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl; 
	std::cout << " (#selMuons = " << selMuons.size() 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_2mu = " << selTrigger_2mu << ")" << std::endl;
      }
      continue;
    }
    if ( selElectrons.size() == 1 && selMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl; 
	std::cout << " (#selElectrons = " << selElectrons.size() 
		  << ", #selMuons = " << selMuons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton trigger match", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton trigger match", evtWeight);
    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];

    const hadTauGenMatchEntry& hadTauGenMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    assert(!(hadTauGenMatch.idx_ == kGen_HadTauUndefined2 || hadTauGenMatch.idx_ == kGen_HadTauAll2));

    if ( hadTauGenMatchSelection != kGen_HadTauAll2 ) {
      if ( hadTauGenMatch.idx_ != hadTauGenMatchSelection ) continue;
      cutFlowTable.update("tau gen match", evtWeight);
    }
    
    double mTauTauVis = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();
	
    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    if ( isMC ) {
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
	  
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(), 
	selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta());

      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(),
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta());

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
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      if ( isDEBUG ) {
	std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }

      evtWeight *= weight_data_to_MC_correction;
    }
	
    double weight_fakeRate = 1.;
    if ( !selectBDT ) {
      if ( applyFakeRateWeights == kFR_4L ) {
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
    double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
    bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTaus);
    double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
    bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTaus);
        weight_fakeRate = getWeight_4L(
          prob_fake_lepton_lead, passesTight_lepton_lead, 
	  prob_fake_lepton_sublead, passesTight_lepton_sublead, 
	  prob_fake_hadTau_lead, passesTight_hadTau_lead, 
	prob_fake_hadTau_sublead, passesTight_hadTau_sublead);
	}
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
      } else if ( applyFakeRateWeights == kFR_2tau) {
      double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTaus);
      double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTaus);
      weight_fakeRate = getWeight_2L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead, 
	prob_fake_hadTau_sublead, passesTight_hadTau_sublead);
	if ( isDEBUG ) {
	  std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
	}
	evtWeight *= weight_fakeRate;
    }
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }
	
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

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !((int)selJets.size() >= minNumJets) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	printJetCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets (2)", minNumJets), evtWeight);
    cutFlowHistManager->fillHistograms(Form(">= %i jets (2)", minNumJets), evtWeight);
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
    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selHadTaus selection." << std::endl;
	printHadTauCollection("selHadTaus", selHadTaus);
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
	  if ( selLepton_lead->charge()*selHadTau_lead->charge()    > 0 ) evtWeight *= prob_chargeMisId_lead;
	  if ( selLepton_sublead->charge()*selHadTau_lead->charge() > 0 ) evtWeight *= prob_chargeMisId_sublead;
	} else if ( chargeSumSelection == kSS ) {
	  // CV: apply charge misidentification probability to lepton of opposite charge as hadronic tau
	  //    (if the lepton of same charge as the hadronic tau "flips",
	  //     the event has sum of charges equal to one and fails "lepton+tau charge" cut)
	  if ( selLepton_lead->charge()*selHadTau_lead->charge()    < 0 ) evtWeight *= prob_chargeMisId_lead;
	  if ( selLepton_sublead->charge()*selHadTau_lead->charge() < 0 ) evtWeight *= prob_chargeMisId_sublead;
	} else assert(0);
      } else {
	evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);
      }      
    } 
    cutFlowTable.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton-pair OS/SS charge", evtWeight);
	
	if ( apply_lepton_and_hadTauCharge_cut ) {
      if ( !((chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) == 1) ||
	     (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) != 1)) ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	  std::cout << " (leading selLepton charge = " << selLepton_lead->charge() 
		    << ", subleading selLepton charge = " << selLepton_sublead->charge() 
		    << ", leading selHadTau charge = " << selHadTau_lead->charge()
			<< ", subleading selHadTau charge = " << selHadTau_sublead->charge() 	<< ")" << std::endl;
	}
	continue;
											   
      }
      cutFlowTable.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
      cutFlowHistManager->fillHistograms("sel lepton+tau charge", evtWeight);
    }
    
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
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);

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

    if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus.size() >= 2 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
    }

    if ( applyJetToTauFakeRateWeight ) {
      assert(jetToTauFakeRateInterface);
      
      double prob_fake_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      double prob_fake_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      
      bool passesTight_lead = isMatched(*selHadTau_lead, tightHadTaus);
      bool passesTight_sublead = isMatched(*selHadTau_sublead, tightHadTaus);

      double p1 = prob_fake_lead/(1. - prob_fake_lead);
      double p2 = prob_fake_sublead/(1. - prob_fake_sublead);
      double evtWeight_tight_to_loose = 0.;
      if      ( !passesTight_lead &&  passesTight_sublead ) evtWeight_tight_to_loose =  p1;
      else if (  passesTight_lead && !passesTight_sublead ) evtWeight_tight_to_loose =  p2;
      else if ( !passesTight_lead && !passesTight_sublead ) evtWeight_tight_to_loose = -p1*p2;
      evtWeight *= evtWeight_tight_to_loose;
    }
        
	//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2l category of ttH multilepton analysis 
    mvaInputs_2l["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(selLepton_lead->eta()), std::fabs(selLepton_sublead->eta()));
    mvaInputs_2l["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
    mvaInputs_2l["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs_2l["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    mvaInputs_2l["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    mvaInputs_2l["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*selLepton_lead);
    mvaInputs_2l["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);
    mvaInputs_2l["mhtJet25_Recl"]              = mht_p4.pt();

    check_mvaInputs(mvaInputs_2l, run, lumi, event);

    double mvaOutput_2l_ttV = mva_2l_ttV(mvaInputs_2l);
    double mvaOutput_2l_ttbar = mva_2l_ttbar(mvaInputs_2l);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 (10) of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_2l = -1;
    if ( era == kEra_2015 ) {
      if      ( mvaOutput_2l_ttbar >  +0.3 && mvaOutput_2l_ttV >  -0.1 ) mvaDiscr_2l = 3.;
      else if ( mvaOutput_2l_ttbar <= +0.3 && mvaOutput_2l_ttV <= -0.1 ) mvaDiscr_2l = 1.;
      else                                                               mvaDiscr_2l = 2.;
    } else if ( era == kEra_2016 ) {
      if      ( mvaOutput_2l_ttbar > +0.30 && mvaOutput_2l_ttV >  +0.25 ) mvaDiscr_2l = 5.;
      else if ( mvaOutput_2l_ttbar > +0.30 && mvaOutput_2l_ttV <= +0.25 ) mvaDiscr_2l = 4.;
      else if ( mvaOutput_2l_ttbar > -0.30 && mvaOutput_2l_ttV >  +0.25 ) mvaDiscr_2l = 3.;
      else if ( mvaOutput_2l_ttbar > -0.30 && mvaOutput_2l_ttV <= +0.25 ) mvaDiscr_2l = 2.;
      else                                                                mvaDiscr_2l = 1.;
    } else assert(0);
    
    mvaInputs_2l_2tau["avg_dr_jet"]           = comp_avg_dr_jet(selJets);
    mvaInputs_2l_2tau["dr_lep1_tau"]          = deltaR(selLepton_lead->p4(), selHadTau->p4());
    mvaInputs_2l_2tau["dr_lep2_tau"]          = deltaR(selLepton_sublead->p4(), selHadTau->p4());
    mvaInputs_2l_2tau["lep1_conePt"]          = comp_lep1_conePt(*selLepton_lead);
    mvaInputs_2l_2tau["lep2_conePt"]          = comp_lep2_conePt(*selLepton_sublead);
    mvaInputs_2l_2tau["mindr_lep1_jet"]       = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    mvaInputs_2l_2tau["mindr_lep2_jet"]       = TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets));
    mvaInputs_2l_2tau["mindr_tau_jet"]        = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets));
    mvaInputs_2l_2tau["nJet"]                 = selJets.size();
    mvaInputs_2l_2tau["tau_pt"]               = selHadTau->pt();
    mvaInputs_2l_2tau["TMath::Abs(tau_eta)"]  = selHadTau->absEta();

    check_mvaInputs(mvaInputs_2l_2tau, run, lumi, event);

    double mvaOutput_2l_2tau_ttV = mva_2l_2tau_ttV(mvaInputs_2l_2tau);
    double mvaOutput_2l_2tau_ttbar = mva_2l_2tau_ttbar(mvaInputs_2l_2tau);

    Double_t mvaDiscr_2l_2tau = getSF_from_TH2(mva_mapping_2l_2tau, mvaOutput_2l_2tau_ttbar, mvaOutput_2l_2tau_ttV) + 1.;
		
    MEMOutput_2l_2tau memOutput_2l_2tau_matched;
    if(memReader)
    {
      const std::vector<MEMOutput_2l_2tau> memOutputs_2l_2tau = memReader->read();
      for(const MEMOutput_2l_2tau & memOutput_2l_2tau: memOutputs_2l_2tau)
      {
        const double selLepton_lead_dR = deltaR(
          selLepton_lead -> eta(),            selLepton_lead -> phi(),
          memOutput_2l_2tau.leadLepton_eta(), memOutput_2l_2tau.leadLepton_phi()
        );
        if(selLepton_lead_dR > 1.e-2)
          continue;
        const double selLepton_sublead_dR = deltaR(
          selLepton_sublead -> eta(),            selLepton_sublead -> phi(),
          memOutput_2l_2tau.subleadLepton_eta(), memOutput_2l_2tau.subleadLepton_phi()
        );
        if(selLepton_sublead_dR > 1.e-2)
          continue;
        const double selHadTau_lead_dR = deltaR(
          selHadTau_lead -> eta(),             selHadTau_lead -> phi(),
          memOutput_2l_2tau.hadTau_lead_eta(), memOutput_2l_2tau.hadTau_lead_phi()
        );
        if(selHadTau_lead_dR > 1.e-2)
          continue;
        const double selHadTau_sublead_dR = deltaR(
          selHadTau_sublead -> eta(),             selHadTau_sublead -> phi(),
          memOutput_2l_2tau.hadTau_sublead_eta(), memOutput_2l_2tau.hadTau_sublead_phi()
        );
        if(selHadTau_sublead_dR > 1.e-2)
          continue;
        memOutput_2l_2tau_matched = memOutput_2l_2tau;
        break;
      }
      if(! memOutput_2l_2tau_matched.is_initialized())
      {
        std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << '\n';
        std::cout << "No MEMOutput_2l_2tau object found for:" << '\n'
                  << "\tselLepton_lead: pT = " << selLepton_lead -> pt()
                  << ", eta = "                << selLepton_lead -> eta()
                  << ", phi = "                << selLepton_lead -> phi()
                  << ", pdgId = "              << selLepton_lead -> pdgId() << '\n'
                  << "\tselLepton_sublead: pT = " << selLepton_sublead -> pt()
                  << ", eta = "                   << selLepton_sublead -> eta()
                  << ", phi = "                   << selLepton_sublead -> phi()
                  << ", pdgId = "                 << selLepton_sublead -> pdgId() << '\n'
                  << "\tselHadTau_lead: pT = " << selHadTau_lead -> pt()
                  << ", eta = "                << selHadTau_lead -> eta()
                  << ", phi = "                << selHadTau_lead -> phi() << '\n';
                  << "\tselHadTau_sublead: pT = " << selHadTau_sublead -> pt()
                  << ", eta = "                   << selHadTau_sublead -> eta()
                  << ", phi = "                   << selHadTau_sublead -> phi() << '\n';
      }
      if(memOutputs_2l_2tau.size())
      {
        for(unsigned mem_idx = 0; mem_idx < memOutputs_2l_2tau.size(); ++mem_idx)
          std::cout << "\t#" << mem_idx << " mem object;\n"
                    << "\t\tlead lepton eta = " << memOutputs_2l_2tau[mem_idx].leadLepton_eta()
                    << "; phi = "               << memOutputs_2l_2tau[mem_idx].leadLepton_phi() << '\n'
                    << "\t\tsublead lepton eta = " << memOutputs_2l_2tau[mem_idx].subleadLepton_eta()
                    << "; phi = "                  << memOutputs_2l_2tau[mem_idx].subleadLepton_phi() << '\n'
                    << "\t\thadronic tau_lead eta = " << memOutputs_2l_2tau[mem_idx].hadTau_lead_eta()
                    << "; phi = "                << memOutputs_2l_2tau[mem_idx].hadTau_lead_phi() << '\n';
                    << "\t\thadronic tau_sublead eta = " << memOutputs_2l_2tau[mem_idx].hadTau_sublead_eta()
                    << "; phi = "                << memOutputs_2l_2tau[mem_idx].hadTau_sublead_phi() << '\n';
      }
      else
        std::cout << "No MEM objects whatsoever\n";
    }
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
    selHistManager->mvaInputVariables_2l_->fillHistograms(mvaInputs_2l, evtWeight);
    selHistManager->mvaInputVariables_2l_2tau_->fillHistograms(mvaInputs_2l_2tau, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(), selMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
      mvaOutput_2l_ttV, mvaOutput_2l_ttbar, mvaDiscr_2l, mvaOutput_2l_2tau_ttV, mvaOutput_2l_2tau_ttbar, mvaDiscr_2l_2tau,  
      mTauTauVis1_sel,
      memOutput_2l_2tau_matched.is_initialized() ? &memOutput_2l_2tau_matched : nullptr, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selHistManager->evt_in_decayModes_[kv.first]->fillHistograms(
            selElectrons.size(), selMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
            mvaOutput_2l_ttV, mvaOutput_2l_ttbar, mvaDiscr_2l, mvaOutput_2l_2tau_ttV, mvaOutput_2l_2tau_ttbar, mvaDiscr_2l_2tau, 
            mTauTauVis1_sel, 
            memOutput_2l_2tau_matched.is_initialized() ? &memOutput_2l_2tau_matched : nullptr, evtWeight);
          break;
        }
      }
    }
    selHistManager->weights_->fillHistograms("genWeight", genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", pileupWeight);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);
						
	 

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    if ( selEventsFile ) {
      (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;
    }
	
  	//////////////////////////////

    if ( bdt_filler ) {
      //FR weights for bdt ntuple
      double prob_fake_lepton_lead = 1.;
      if      ( std::abs(selLepton_lead->pdgId()) == 11 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->cone_pt(), selLepton_lead->absEta());
      else if ( std::abs(selLepton_lead->pdgId()) == 13 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->cone_pt(), selLepton_lead->absEta());
      double prob_fake_lepton_sublead = 1.;
      if      ( std::abs(selLepton_sublead->pdgId()) == 11 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
      else if ( std::abs(selLepton_sublead->pdgId()) == 13 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());
      bdt_filler -> operator()({ run, lumi, event })
          ("lep1_pt",              selLepton_lead -> pt())
          ("lep1_conePt",          comp_lep1_conePt(*selLepton_lead))
          ("lep1_eta",             selLepton_lead -> eta())
          ("lep1_tth_mva",         selLepton_lead -> mvaRawTTH())
          ("mindr_lep1_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets)))
          ("mT_lep1",              comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi()))
          ("dr_lep1_tau",          deltaR(selLepton_lead -> p4(), selHadTau -> p4()))
          ("lep2_pt",              selLepton_sublead -> pt())
          ("lep2_conePt",          comp_lep1_conePt(*selLepton_sublead))
          ("lep2_eta",             selLepton_sublead -> eta())
          ("lep2_tth_mva",         selLepton_sublead -> mvaRawTTH())
          ("mindr_lep2_jet",       TMath::Min(10., comp_mindr_lep1_jet(*selLepton_sublead, selJets)))
          ("mT_lep2",              comp_MT_met_lep1(*selLepton_sublead, met.pt(), met.phi()))
          ("dr_lep2_tau",          deltaR(selLepton_sublead -> p4(), selHadTau -> p4()))
          ("mindr_tau_jet",        TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau, selJets)))
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
          ("mTauTauVis1",          mTauTauVis1_sel)
	      ("memOutput_isValid",    memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.isValid()        : -100.)
          ("memOutput_errorFlag",  memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.errorFlag()      : -100.)
          ("memOutput_type",       memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.type()           : -100.)
          ("memOutput_ttH",        memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.weight_ttH()     : -100.)
          ("memOutput_ttZ",        memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.weight_ttZ()     : -100.)
          ("memOutput_ttZ_Zll",    memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.weight_ttZ_Zll() : -100.)
          ("memOutput_tt",         memOutput_2l_2tau_matched.is_initialized() ? memOutput_2l_2tau_matched.weight_tt()      : -100.)
		  ("memOutput_LR",         memOutput_LR)
		  ("memOutput_tt_LR",      memOutput_ttbar_LR)
		  ("memOutput_ttZ_LR",     memOutput_ttZ_LR)
		  ("lep1_genLepPt",        ( selLepton_lead->genLepton() != 0 ) ? selLepton_lead->genLepton()->pt() : 0.)
		  ("lep2_genLepPt",        ( selLepton_sublead->genLepton() != 0 ) ? selLepton_sublead->genLepton()->pt() : 0.)
		  ("tau_genTauPt",         ( selHadTau->genHadTau() != 0 ) ? selHadTau->genHadTau()->pt() : 0.)
		  ("lep1_fake_prob",       prob_fake_lepton_lead)
		  ("lep2_fake_prob",       prob_fake_lepton_sublead)
		  ("mvaOutput_2l_ttV",     mvaOutput_2l_ttV)
		  ("mvaOutput_2l_ttbar",   mvaOutput_2l_ttbar)
		  ("mvaDiscr_2l",          mvaDiscr_2l)
          ("lumiScale",            lumiScale)
          ("genWeight",            genWeight)
          ("evtWeight",            evtWeight)
          ("nJet",                 selJets.size())
          ("nBJetLoose",           selBJets_loose.size())
          ("nBJetMedium",          selBJets_medium.size())
		  ("lep1_isTight",         int(selLepton_lead -> isTight()))
		  ("lep2_isTight",         int(selLepton_sublead -> isTight()))
		  ("tau_isTight",          int(tightHadTauFilter(*selHadTau)))
        .fill()
      ;
    }
    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
	histogram_selectedEntries->Fill(0.);									 
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;
  std::cout << std::endl;

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
  
  clock.Show("analyze_2l_2tau");

  return EXIT_SUCCESS;
}

