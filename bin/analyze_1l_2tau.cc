
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
#include <TRandom3.h> // TRandom3

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 1l_2tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_2tau.h" // EvtHistManager_1l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_1l_2tau.h" // CutFlowTableHistManager_1l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_2tau_trigger.h" // Data_to_MC_CorrectionInterface_1l_2tau_trigger
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

#define EPS 1E-2

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { k1e_btight, k1e_bloose, k1mu_btight, k1mu_bloose };
enum { kFR_disabled, kFR_3L, kFR_2tau };

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
 * @brief Produce datacard and control plots for 1l_2tau category.
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

  std::cout << "<analyze_1l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_1l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_1l_2tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_1l_2tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1e1tau = cfg_analyze.getParameter<vstring>("triggers_1e1tau");
  std::vector<hltPath*> triggers_1e1tau = create_hltPaths(triggerNames_1e1tau);
  bool use_triggers_1e1tau = cfg_analyze.getParameter<bool>("use_triggers_1e1tau");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_1mu1tau = cfg_analyze.getParameter<vstring>("triggers_1mu1tau");
  std::vector<hltPath*> triggers_1mu1tau = create_hltPaths(triggerNames_1mu1tau);
  bool use_triggers_1mu1tau = cfg_analyze.getParameter<bool>("use_triggers_1mu1tau");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1e1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1tau");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_1mu1tau = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu1tau");

  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_1lepton(apply_leptonGenMatching);
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
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
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
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 

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
    else throw cms::Exception("analyze_1l_2tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      if ( isMC ) jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      else cms::Exception("analyze_1l_2tau")
	<< "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      if ( isMC ) {
	jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
	if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
	else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
	else assert(0);
      } else cms::Exception("analyze_1l_2tau")
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
      } else cms::Exception("analyze_1l_2tau")
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
      } else cms::Exception("analyze_1l_2tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( !(central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") || 
		  central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt")) ) {
      throw cms::Exception("analyze_1l_2tau")
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
  //cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", false);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);
  Data_to_MC_CorrectionInterface_1l_2tau_trigger* dataToMCcorrectionInterface_1l_2tau_trigger = new Data_to_MC_CorrectionInterface_1l_2tau_trigger(cfg_dataToMCcorrectionInterface);
  
  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "3L"       ) applyFakeRateWeights = kFR_3L;
  else if ( applyFakeRateWeights_string == "2tau"     ) applyFakeRateWeights = kFR_2tau;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  
  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L || applyFakeRateWeights == kFR_2tau ) {
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

  const bool selectBDT = [&cfg_analyze]() -> bool
  {
    if(cfg_analyze.exists("selectBDT"))
      return cfg_analyze.getParameter<bool>("selectBDT");
    return false;
  }();

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
    throw cms::Exception("analyze_1l_2tau") 
      << "Failed to identify input Tree !!\n";
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
  hltPaths_setBranchAddresses(inputTree, triggers_1e1tau);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu1tau);

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
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(std::min(hadTauSelection_antiElectron_lead, hadTauSelection_antiElectron_sublead));
  preselHadTauSelector.set_min_antiMuon(std::min(hadTauSelection_antiMuon_lead, hadTauSelection_antiMuon_sublead));
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_lead(era, 0);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector_lead.set(hadTauSelection_part2);
  fakeableHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  fakeableHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_sublead(era, 1);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector_sublead.set(hadTauSelection_part2);
  fakeableHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  fakeableHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_lead(era, 0);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_lead.set(hadTauSelection_part2);
  tightHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  tightHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_sublead(era, 1);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_sublead.set(hadTauSelection_part2);
  tightHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  tightHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);

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

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
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
  }

//--- initialize BDTs used to discriminate ttH vs. ttbar trained by Matthias for 1l_2tau category
  std::string mvaFileName_1l_2tau_ttbar;
  if ( hadTauSelection_part2 == "dR03mvaVVTight" ) mvaFileName_1l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttbar_vvTight.weights.xml";
  else mvaFileName_1l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttbar_vTight.weights.xml";
  std::vector<std::string> mvaInputVariables_1l_2tau_ttbar;
  mvaInputVariables_1l_2tau_ttbar.push_back("ht");
  mvaInputVariables_1l_2tau_ttbar.push_back("tt_deltaR");
  mvaInputVariables_1l_2tau_ttbar.push_back("tt_visiblemass");
  mvaInputVariables_1l_2tau_ttbar.push_back("tau1_pt");
  mvaInputVariables_1l_2tau_ttbar.push_back("tau2_pt");
  mvaInputVariables_1l_2tau_ttbar.push_back("jet_deltaRavg");
  mvaInputVariables_1l_2tau_ttbar.push_back("njets_inclusive");
  mvaInputVariables_1l_2tau_ttbar.push_back("ntags_loose");
  TMVAInterface mva_1l_2tau_ttbar(mvaFileName_1l_2tau_ttbar, mvaInputVariables_1l_2tau_ttbar);

  std::map<std::string, double> mvaInputs_ttbar;

  std::string mvaFileName_1l_2tau_ttV;
  if ( hadTauSelection_part2 == "dR03mvaVVTight" ) mvaFileName_1l_2tau_ttV = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttV_vvTight.weights.xml";
  else mvaFileName_1l_2tau_ttV = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttV_vTight.weights.xml";
  std::vector<std::string> mvaInputVariables_1l_2tau_ttV;
  mvaInputVariables_1l_2tau_ttV.push_back("ht");
  mvaInputVariables_1l_2tau_ttV.push_back("tt_deltaR");
  mvaInputVariables_1l_2tau_ttV.push_back("tt_visiblemass");
  mvaInputVariables_1l_2tau_ttV.push_back("tt_sumpt");
  mvaInputVariables_1l_2tau_ttV.push_back("jet_deltaRmax");
  mvaInputVariables_1l_2tau_ttV.push_back("jet_deltaRavg");
  mvaInputVariables_1l_2tau_ttV.push_back("njets_inclusive");
  TMVAInterface mva_1l_2tau_ttV(mvaFileName_1l_2tau_ttV, mvaInputVariables_1l_2tau_ttV);

  std::map<std::string, double> mvaInputs_ttV;

  std::string inputFileName_mva_mapping_1l_2tau;
  if ( hadTauSelection_part2 == "dR03mvaVVTight" ) inputFileName_mva_mapping_1l_2tau = "tthAnalysis/HiggsToTauTau/data/1l_2tau_BDT_mapping_vvTight.root";
  else mvaFileName_1l_2tau_ttV = inputFileName_mva_mapping_1l_2tau = "tthAnalysis/HiggsToTauTau/data/1l_2tau_BDT_mapping_vTight.root";
  TFile* inputFile_mva_mapping_1l_2tau = openFile(LocalFileInPath(inputFileName_mva_mapping_1l_2tau));
  TH2* mva_mapping_1l_2tau = loadTH2(inputFile_mva_mapping_1l_2tau, "hTargetBinning");
  
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
    EvtHistManager_1l_2tau* evt_;
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
    MVAInputVarHistManager* mvaInputVariables_ttbar_;
    MVAInputVarHistManager* mvaInputVariables_ttV_;
    EvtHistManager_1l_2tau* evt_;
    std::map<std::string, EvtHistManager_1l_2tau*> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_1l_2tau*> evt_in_categories_;
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
      preselHistManager->evt_ = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/presel/evt", histogramDir.data()), central_or_shift));
      preselHistManager->evt_->bookHistograms(fs);
      preselHistManagers[idxLepton][idxHadTau] = preselHistManager;

      selHistManagerType* selHistManager = new selHistManagerType();
      selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
      selHistManager->electrons_->bookHistograms(fs);
      vstring categories_e = { 
	"1e_2tau_bloose", "1e_2tau_btight"
      };
      std::map<std::string, ElectronHistManager*> selElectronHistManager_category; // key = category
      for ( vstring::const_iterator category = categories_e.begin();
	    category != categories_e.end(); ++category ) {
	TString histogramDir_category = histogramDir.data();
	histogramDir_category.ReplaceAll("1l_2tau", category->data());
	selHistManager->electrons_in_categories_[*category] = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
          Form("%s/sel/electrons", histogramDir_category.Data()), central_or_shift));
	selHistManager->electrons_in_categories_[*category]->bookHistograms(fs);
      }
      selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/muons", histogramDir.data()), central_or_shift));
      selHistManager->muons_->bookHistograms(fs);
      vstring categories_mu = { 
	"1mu_2tau_bloose", "1mu_2tau_btight"
      };
      for ( vstring::const_iterator category = categories_mu.begin();
	    category != categories_mu.end(); ++category ) {
	TString histogramDir_category = histogramDir.data();
	histogramDir_category.ReplaceAll("1l_2tau", category->data());
	selHistManager->muons_in_categories_[*category] = new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
          Form("%s/sel/muons", histogramDir_category.Data()), central_or_shift));
	selHistManager->muons_in_categories_[*category]->bookHistograms(fs);
      }
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
	"1e_2tau_bloose", "1e_2tau_btight",
	"1mu_2tau_bloose", "1mu_2tau_btight"
      };
      for ( vstring::const_iterator category = categories_tau.begin();
	    category != categories_tau.end(); ++category ) {
	TString histogramDir_category = histogramDir.data();
	histogramDir_category.ReplaceAll("1l_2tau", category->data());
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
      selHistManager->mvaInputVariables_ttbar_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/mvaInputs_ttbar", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_ttbar_->bookHistograms(fs, mvaInputVariables_1l_2tau_ttbar);
      selHistManager->mvaInputVariables_ttV_ = new MVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/mvaInputs_ttV", histogramDir.data()), central_or_shift));
      selHistManager->mvaInputVariables_ttV_->bookHistograms(fs, mvaInputVariables_1l_2tau_ttV);
      selHistManager->evt_ = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evt", histogramDir.data()), central_or_shift));
      selHistManager->evt_->bookHistograms(fs);      
      vstring decayModes_evt;
      decayModes_evt.reserve(decayMode_idString.size());
      boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes_evt));
      if ( isSignal ) {
	for ( vstring::const_iterator decayMode = decayModes_evt.begin();
	      decayMode != decayModes_evt.end(); ++decayMode) {

	  std::string decayMode_and_genMatch = (*decayMode);
	  if ( apply_leptonGenMatching ) decayMode_and_genMatch += leptonGenMatch_definition->name_;
	  if ( apply_leptonGenMatching && apply_hadTauGenMatching ) decayMode_and_genMatch += "&";
	  if ( apply_hadTauGenMatching ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;

	  selHistManager->evt_in_decayModes_[*decayMode] = new EvtHistManager_1l_2tau(makeHistManager_cfg(decayMode_and_genMatch,
            Form("%s/sel/evt", histogramDir.data()), central_or_shift));
	  selHistManager->evt_in_decayModes_[*decayMode]->bookHistograms(fs);
	}
      }
      vstring categories_evt = { 
	"1e_2tau_bloose", "1e_2tau_btight", 
	"1mu_2tau_bloose", "1mu_2tau_btight"
      };
      for ( vstring::const_iterator category = categories_evt.begin();
	    category != categories_evt.end(); ++category ) {
	TString histogramDir_category = histogramDir.data();
	histogramDir_category.ReplaceAll("1l_2tau", category->data());
	selHistManager->evt_in_categories_[*category] = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
          Form("%s/sel/evt", histogramDir_category.Data()), central_or_shift));
	selHistManager->evt_in_categories_[*category]->bookHistograms(fs);
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
      "lep_pt", "lep_eta", "lep_tth_mva", "mindr_lep_jet", "mindr_tau1_jet", "mindr_tau2_jet",
      "avg_dr_jet", "ptmiss", "mT_lep", "htmiss", "tau1_mva", "tau2_mva", "tau1_pt", "tau2_pt",
      "tau1_eta", "tau2_eta", "dr_taus", "dr_lep_tau_os", "dr_lep_tau_ss", "mTauTauVis",
      "lumiScale", "genWeight", "evtWeight"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium"
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
  CutFlowTableHistManager_1l_2tau* cutFlowHistManager = new CutFlowTableHistManager_1l_2tau(makeHistManager_cfg(process_string, 
    Form("%s/sel/cutFlow", histogramDir.data()), central_or_shift));
  cutFlowHistManager->bookHistograms(fs);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    inputTree->GetEntry(idxEntry);

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
    }

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }
    
    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1tau = hltPaths_isTriggered(triggers_1e1tau) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu1tau = hltPaths_isTriggered(triggers_1mu1tau) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1e1tau = use_triggers_1e1tau && isTriggered_1e1tau;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1mu1tau = use_triggers_1mu1tau && isTriggered_1mu1tau;
    if ( !(selTrigger_1e || selTrigger_1e1tau || selTrigger_1mu|| selTrigger_1mu1tau) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl; 
	std::cout << " (selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1e1tau = " << selTrigger_1e1tau 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau << ")" << std::endl;
      }
      continue;
    }
    
//--- Rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 1mu, 1e
// CV: This logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets.
//     The mu+tau and e+tau need to have the lowest priority, as not all e+tau trigger paths exists in the VHbb Ntuples of the SingleElectron and SingleMuon datasets!!
    if ( !isMC && !isDEBUG ) {
      bool isTriggered_SingleElectron = isTriggered_1e;
      bool isTriggered_SingleMuon = isTriggered_1mu;
      //bool isTriggered_Tau = isTriggered_1e1tau || isTriggered_1mu1tau;

      bool selTrigger_SingleElectron = selTrigger_1e;
      //bool selTrigger_SingleMuon = selTrigger_1mu;
      bool selTrigger_Tau = selTrigger_1e1tau || selTrigger_1mu1tau;
      
      if ( selTrigger_SingleElectron && isTriggered_SingleMuon ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl; 
	  std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
		    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon << ")" << std::endl;
	}
	continue; 
      }
      if ( selTrigger_Tau && (isTriggered_SingleMuon || isTriggered_SingleElectron) ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl; 
	  std::cout << " (selTrigger_Tau = " << selTrigger_Tau
		    << ", isTriggered_SingleMuon = " << isTriggered_SingleMuon
		    << ", isTriggered_SingleElectron = " << isTriggered_SingleElectron << ")" << std::endl;
	}
	continue; 
      }
    }
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);

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
    std::vector<const RecoHadTau*> fakeableHadTaus_lead = fakeableHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_sublead = hadTauCleaner(fakeableHadTauSelector_sublead(preselHadTaus), fakeableHadTaus_lead);
    assert(fakeableHadTaus_lead.size() <= 1 && fakeableHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> fakeableHadTaus;
    if ( fakeableHadTaus_lead.size()    >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_lead[0]);
    if ( fakeableHadTaus_sublead.size() >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_sublead[0]);
    std::vector<const RecoHadTau*> tightHadTaus_lead = tightHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus_sublead = hadTauCleaner(tightHadTauSelector_sublead(preselHadTaus), tightHadTaus_lead);
    assert(tightHadTaus_lead.size() <= 1 && tightHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> tightHadTaus;
    if ( tightHadTaus_lead.size()    >= 1 ) tightHadTaus.push_back(tightHadTaus_lead[0]);
    if ( tightHadTaus_sublead.size() >= 1 ) tightHadTaus.push_back(tightHadTaus_sublead[0]);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);
    selHadTaus = pickFirstNobjects(selHadTaus, 2);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);    

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
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
    // require exactly one lepton passing loose preselection criteria
    if ( !(preselLeptons.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 presel lepton");
    cutFlowHistManager->fillHistograms(">= 1 presel lepton", lumiScale);
    const RecoLepton* preselLepton = preselLeptons[0];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    if ( apply_leptonGenMatching_ttZ_workaround ) idxPreselLepton_genMatch = kGen_1l0j;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined1);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 1 && (selTrigger_1e  || selTrigger_1e1tau )) ||
	   (preselMuons.size()     >= 1 && (selTrigger_1mu || selTrigger_1mu1tau))) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", #preselMuons = " << preselMuons.size() 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1e1tau = " << selTrigger_1e1tau << ")" << std::endl;
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
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets");
    cutFlowHistManager->fillHistograms(">= 2 jets", lumiScale);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", lumiScale);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselLepton_genMatch][idxPreselHadTau_genMatch];
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
    preselHistManager->evt_->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1., -1.,	-1.,					
      mTauTauVis_presel, 1.);

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    if ( !(selLeptons.size() >= 1) ) continue;
    cutFlowTable.update(">= 1 sel lepton", lumiScale);
    cutFlowHistManager->fillHistograms(">= 1 sel lepton", lumiScale);
    const RecoLepton* selLepton = selLeptons[0];
    int selLepton_type = getLeptonType(selLepton->pdgId());
    const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    if ( apply_leptonGenMatching_ttZ_workaround ) idxSelLepton_genMatch = kGen_1l0j;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined1);

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
      double btagWeight = 1.;
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

    // require exactly one lepton passing tight selection criteria, to avoid overlap with other channels
    std::vector<const RecoLepton*> tightLeptons;    
    tightLeptons.reserve(tightElectrons.size() + tightMuons.size());
    tightLeptons.insert(tightLeptons.end(), tightElectrons.begin(), tightElectrons.end());
    tightLeptons.insert(tightLeptons.end(), tightMuons.begin(), tightMuons.end());
    std::sort(tightLeptons.begin(), tightLeptons.end(), isHigherPt);
    if ( !(tightLeptons.size() <= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS tightLeptons selection." << std::endl;
	printLeptonCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("<= 1 tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("<= 1 tight leptons", evtWeight);

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((selElectrons.size() >= 1 && (selTrigger_1e  || selTrigger_1e1tau )) ||
	   (selMuons.size()     >= 1 && (selTrigger_1mu || selTrigger_1mu1tau))) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl; 
	std::cout << " (#selElectrons = " << selElectrons.size() 
		  << ", #selMuons = " << selMuons.size() 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1mu1tau = " << selTrigger_1mu1tau 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1e1tau = " << selTrigger_1e1tau << ")" << std::endl;
      }
      continue;
    } 
    cutFlowTable.update("sel lepton trigger match", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton trigger match", evtWeight);

    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    cutFlowHistManager->fillHistograms(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined2);

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    double weight_leptonEff = 1.;
    double weight_hadTauEff = 1.;
    if ( isMC ) {
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);

      dataToMCcorrectionInterface->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(),
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta());

      dataToMCcorrectionInterface_1l_2tau_trigger->setLeptons(selLepton_type, selLepton->pt(), selLepton->eta());
      dataToMCcorrectionInterface_1l_2tau_trigger->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->decayMode(),
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->decayMode());
      dataToMCcorrectionInterface_1l_2tau_trigger->setTriggerBits(isTriggered_1e, isTriggered_1e1tau, isTriggered_1mu, isTriggered_1mu1tau);

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
	triggerWeight = dataToMCcorrectionInterface_1l_2tau_trigger->getWeight_triggerEff();
	if ( isDEBUG ) {
	  std::cout << "triggerWeight = " << triggerWeight << std::endl;
	}
	evtWeight *= triggerWeight;
      }

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface_1l_2tau_trigger->getSF_triggerEff();
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
      sf_leptonEff *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();
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
      weight_data_to_MC_correction *= sf_hadTauEff;
      if ( isDEBUG ) {
	std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }
      evtWeight *= weight_data_to_MC_correction;
    }       
    
    double weight_fakeRate = 1.;
    if ( applyFakeRateWeights == kFR_3L ) {
      double prob_fake_lepton = 1.;
      if      ( std::abs(selLepton->pdgId()) == 11 ) prob_fake_lepton = leptonFakeRateInterface->getWeight_e(selLepton->cone_pt(), selLepton->absEta());
      else if ( std::abs(selLepton->pdgId()) == 13 ) prob_fake_lepton = leptonFakeRateInterface->getWeight_mu(selLepton->cone_pt(), selLepton->absEta());
      else assert(0);
      bool passesTight_lepton = isMatched(*selLepton, tightElectrons) || isMatched(*selLepton, tightMuons);
      double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTaus);
      double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTaus);
      weight_fakeRate = getWeight_3L(
        prob_fake_lepton, passesTight_lepton, 
	prob_fake_hadTau_lead, passesTight_hadTau_lead, 
	prob_fake_hadTau_sublead, passesTight_hadTau_sublead); 
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

    double mTauTauVis = (selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 3 jets", evtWeight);
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
	std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    double minPt = selLepton->is_electron() ? 25. : 20.;
    if ( !(selLepton->pt() > minPt) ) continue;
    cutFlowTable.update("sel lepton pT > 25(e)/20(mu) GeV", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton pT > 25(e)/20(mu) GeV", evtWeight);

    if ( !(selLepton->absEta() < 2.1) ) continue;
    cutFlowTable.update("sel lepton abs(eta) < 2.1", evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton abs(eta) < 2.1", evtWeight);

    if ( !(selHadTau_lead->pt() > 30.) ) continue;
    cutFlowTable.update("sel hadTau pT > 30 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("sel hadTau pT > 30 GeV", evtWeight);

    bool isCharge_SS = selHadTau_lead->charge()*selHadTau_sublead->charge() > 0;
    bool isCharge_OS = selHadTau_lead->charge()*selHadTau_sublead->charge() < 0;
    if ( hadTauChargeSelection == kOS && isCharge_SS ) continue;
    if ( hadTauChargeSelection == kSS && isCharge_OS ) continue;
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("tau-pair OS/SS charge", evtWeight);
    const RecoHadTau* selHadTau_OS = 0;
    const RecoHadTau* selHadTau_SS = 0;
    if ( hadTauChargeSelection == kOS ) {
      if ( selHadTau_lead->charge()*selLepton->charge() < 0 ) selHadTau_OS = selHadTau_lead;
      else selHadTau_OS = selHadTau_sublead;
    } 
    if ( hadTauChargeSelection == kSS ) {
      static TRandom3 rnd;
      if ( rnd.Rndm() >= 0.5 ) selHadTau_OS = selHadTau_lead;
      else selHadTau_OS = selHadTau_sublead;
    } 
    if      ( selHadTau_OS == selHadTau_lead    ) selHadTau_SS = selHadTau_sublead;
    else if ( selHadTau_OS == selHadTau_sublead ) selHadTau_SS = selHadTau_lead;
    assert(selHadTau_OS && selHadTau_SS);

    if ( std::abs(selLepton->charge() + selHadTau_lead->charge()+ selHadTau_sublead->charge()) != 1 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	std::cout << " (selLepton charge = " << selLepton->charge() 
		  << ", leading selHadTau charge = " << selHadTau_lead->charge() 
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lepton+tau charge", evtWeight);
    cutFlowHistManager->fillHistograms("lepton+tau charge", evtWeight);

    if ( leptonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( tightLeptons.size() >= 1 && tightHadTaus_lead.size() >= 1 && tightHadTaus_sublead.size() >= 1 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
      cutFlowHistManager->fillHistograms("signal region veto", evtWeight);
    }
    
//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Matthias for 1l_2tau category
    mvaInputs_ttbar["ht"]              = compHT(fakeableLeptons, selHadTaus, selJets);
    mvaInputs_ttbar["tt_deltaR"]       = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_ttbar["tt_visiblemass"]  = mTauTauVis;
    mvaInputs_ttbar["tau1_pt"]         = selHadTau_lead->pt();
    mvaInputs_ttbar["tau2_pt"]         = selHadTau_sublead->pt();
    mvaInputs_ttbar["jet_deltaRavg"]   = comp_avg_dr_jet(selJets);
    mvaInputs_ttbar["njets_inclusive"] = selJets.size();
    mvaInputs_ttbar["ntags_loose"]     = selBJets_loose.size();

    check_mvaInputs(mvaInputs_ttbar, run, lumi, event);

    double mvaOutput_1l_2tau_ttbar = mva_1l_2tau_ttbar(mvaInputs_ttbar);

    mvaInputs_ttV["ht"]                = compHT(fakeableLeptons, selHadTaus, selJets);
    mvaInputs_ttV["tt_deltaR"]         = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    mvaInputs_ttV["tt_visiblemass"]    = mTauTauVis;
    mvaInputs_ttV["tt_sumpt"]          = selHadTau_lead->pt() + selHadTau_sublead->pt();
    mvaInputs_ttV["jet_deltaRmax"]     = comp_max_dr_jet(selJets);
    mvaInputs_ttV["jet_deltaRavg"]     = comp_avg_dr_jet(selJets);
    mvaInputs_ttV["njets_inclusive"]   = selJets.size();

    check_mvaInputs(mvaInputs_ttV, run, lumi, event);

    double mvaOutput_1l_2tau_ttV = mva_1l_2tau_ttV(mvaInputs_ttV);

    Double_t mvaDiscr_1l_2tau = 0.5*(getSF_from_TH2(mva_mapping_1l_2tau, mvaOutput_1l_2tau_ttbar, mvaOutput_1l_2tau_ttV) + 1.);

//--- fill histograms with events passing final selection 
    selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch][idxSelHadTau_genMatch];
    assert(selHistManager != 0);
    selHistManager->electrons_->fillHistograms(selElectrons, evtWeight);
    selHistManager->muons_->fillHistograms(selMuons, evtWeight);
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
    selHistManager->mvaInputVariables_ttbar_->fillHistograms(mvaInputs_ttbar, evtWeight);
    selHistManager->mvaInputVariables_ttV_->fillHistograms(mvaInputs_ttV, evtWeight);
    selHistManager->evt_->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_1l_2tau_ttbar, mvaOutput_1l_2tau_ttV, mvaDiscr_1l_2tau,
      mTauTauVis, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selHistManager->evt_in_decayModes_[kv.first]->fillHistograms(
            preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	    mvaOutput_1l_2tau_ttbar, mvaOutput_1l_2tau_ttV, mvaDiscr_1l_2tau,
	    mTauTauVis, evtWeight);
          break;
        }
      }
    }
    selHistManager->weights_->fillHistograms("genWeight", genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", pileupWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("leptonEff", weight_leptonEff);
    selHistManager->weights_->fillHistograms("hadTauEff", weight_hadTauEff);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    std::string category;
    if      ( selElectrons.size() >= 1 && selBJets_medium.size() >= 1 ) category = "1e_2tau_btight"; 
    else if ( selElectrons.size() >= 1                                ) category = "1e_2tau_bloose";  
    else if ( selMuons.size()     >= 1 && selBJets_medium.size() >= 1 ) category = "1mu_2tau_btight"; 
    else if ( selMuons.size()     >= 1                                ) category = "1mu_2tau_bloose"; 
    else assert(0);

    if ( selHistManager->electrons_in_categories_.find(category) != selHistManager->electrons_in_categories_.end() ) {
      selHistManager->electrons_in_categories_[category]->fillHistograms(selElectrons, evtWeight);
    }
    if ( selHistManager->muons_in_categories_.find(category) != selHistManager->muons_in_categories_.end() ) {
      selHistManager->muons_in_categories_[category]->fillHistograms(selMuons, evtWeight);
    }
    selHistManager->hadTaus_in_categories_[category]->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
    selHistManager->leadHadTau_in_categories_[category]->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_in_categories_[category]->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->evt_in_categories_[category]->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_1l_2tau_ttbar, mvaOutput_1l_2tau_ttV, mvaDiscr_1l_2tau,
      mTauTauVis, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    if ( selEventsFile ) {
      (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;
    }

    if(bdt_filler)
    {
      bdt_filler -> operator()({ run, lumi, event })
          ("lep_pt",         selLepton -> pt())
          ("lep_eta",        selLepton -> eta())
          ("lep_tth_mva",    selLepton -> mvaRawTTH())
          ("mindr_lep_jet",  TMath::Min(10., comp_mindr_lep1_jet(*selLepton, selJets)))
          ("mindr_tau1_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets)))
          ("mindr_tau2_jet", TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets)))
          ("avg_dr_jet",     comp_avg_dr_jet(selJets))
          ("ptmiss",         met.pt())
          ("mT_lep",         comp_MT_met_lep1(*selLepton, met.pt(), met.phi()))
          ("htmiss",         mht_p4.pt())
          ("tau1_mva",       selHadTau_lead -> raw_mva_dR03())
          ("tau2_mva",       selHadTau_sublead -> raw_mva_dR03())
          ("tau1_pt",        selHadTau_lead -> pt())
          ("tau2_pt",        selHadTau_sublead -> pt())
          ("tau1_eta",       selHadTau_lead -> eta())
          ("tau2_eta",       selHadTau_sublead -> eta())
          ("dr_taus",        deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4()))
	  ("dr_lep_tau_os",  deltaR(selLepton->p4(), selHadTau_OS->p4()))  
          ("dr_lep_tau_ss",  deltaR(selLepton->p4(), selHadTau_SS->p4()))
          ("mTauTauVis",     mTauTauVis)
          ("lumiScale",      lumiScale)
          ("genWeight",      genWeight)
          ("evtWeight",      evtWeight)
          ("nJet",           selJets.size())
          ("nBJetLoose",     selBJets_loose.size())
          ("nBJetMedium",    selBJets_medium.size())
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
  delete bdt_filler;

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
  hltPaths_delete(triggers_1e1tau);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1mu1tau);

  clock.Show("analyze_1l_2tau");

  return EXIT_SUCCESS;
}

