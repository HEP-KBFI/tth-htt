
#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/ParameterSet/interface/FileInPath.h" // edm::FileInPath
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 1l_2tau category
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
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
#include "tthAnalysis/HiggsToTauTau/interface/HadTauFakeRateHistManager.h" // HadTauFakeRateHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_2tau.h" // EvtHistManager_1l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_3tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType

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

const int hadTauSelection_antiElectron_lead = 1; // vLoose
const int hadTauSelection_antiMuon_lead = 1; // Loose 
const int hadTauSelection_antiElectron_sublead = 2; // Loose
const int hadTauSelection_antiMuon_sublead = 1; // Loose

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

int getHadTau_genPdgId(const RecoHadTau* hadTau)
{
  int hadTau_genPdgId = -1;
  if      ( hadTau->genHadTau_ ) hadTau_genPdgId = 15;
  else if ( hadTau->genLepton_ ) hadTau_genPdgId = std::abs(hadTau->genLepton_->pdgId_);
  return hadTau_genPdgId;
}

/**
 * @brief Produce datacard and control plots for 1l_2tau category.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
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
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");

  enum { kOS, kSS };
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  enum { kLoose, kFakeable, kTight };
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

  std::string hadTauGenMatchSelection_string = cfg_analyze.getParameter<std::string>("hadTauGenMatch");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau();
  int hadTauGenMatchSelection = getHadTauGenMatch_int(hadTauGenMatch_definitions, hadTauGenMatchSelection_string);
  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  if ( hadTauGenMatchSelection_string != "all" && !apply_hadTauGenMatching ) {
    throw cms::Exception("analyze_1l_2tau") 
      << "Invalid combination of Configuration parameters 'hadTauGenMatch' = " << hadTauGenMatchSelection_string << ", 'apply_hadTauGenMatching' = " << apply_hadTauGenMatching << " !!\n";
  }
  std::string process_and_genMatch = process_string;
  if ( hadTauGenMatchSelection_string != "all" && apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatchSelection_string;

  vdouble hadTauEtaBins_lead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_lead"); // CV: eta bins in which jet->tau fake-rates are determined
  vdouble hadTauEtaBins_sublead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_sublead");

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 

  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  int lheScale_option = kLHE_scale_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_1l_2tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRjt") ) {
      if      ( central_or_shift_tstring.EndsWith("normUp")    ) jetToTauFakeRate_option = kFRjt_normUp;
      else if ( central_or_shift_tstring.EndsWith("normDown")  ) jetToTauFakeRate_option = kFRjt_normDown;
      else if ( central_or_shift_tstring.EndsWith("shapeUp")   ) jetToTauFakeRate_option = kFRjt_shapeUp;
      else if ( central_or_shift_tstring.EndsWith("shapeDown") ) jetToTauFakeRate_option = kFRjt_shapeDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_thu_shape") ) {
      if      ( central_or_shift_tstring.EndsWith("x1Down") ) lheScale_option = kLHE_scale_xDown;
      else if ( central_or_shift_tstring.EndsWith("x1Up")   ) lheScale_option = kLHE_scale_xUp;
      else if ( central_or_shift_tstring.EndsWith("y1Down") ) lheScale_option = kLHE_scale_yDown;
      else if ( central_or_shift_tstring.EndsWith("y1Up")   ) lheScale_option = kLHE_scale_yUp;
      else assert(0);
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
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);
  
  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  bool applyJetToTauFakeRateWeight = cfg_analyze.getParameter<bool>("applyJetToTauFakeRateWeight");
  if ( applyJetToTauFakeRateWeight ) {
    edm::ParameterSet cfg_jetToTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("jetToTauFakeRateWeight");
    cfg_jetToTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_jetToTauFakeRateWeight, jetToTauFakeRate_option);
  }
  
  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

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
  
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);

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
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);

  PUWEIGHT_TYPE pileupWeight;
  if ( isMC ) {
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }

  MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorTight tightMuonSelector(era);
  tightMuonSelector.disable_tightCharge_cut();

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector;
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  tightElectronSelector.disable_tightCharge_cut();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector;
  preselHadTauSelector.set_min_antiElectron(1);
  preselHadTauSelector.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_lead(0);
  fakeableHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  fakeableHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_sublead(1);
  fakeableHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  fakeableHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_lead(0);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_lead.set(hadTauSelection_part2);
  tightHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  tightHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_sublead(1);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_sublead.set(hadTauSelection_part2);
  tightHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  tightHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);

  RecoJetReader* jetReader = new RecoJetReader(era, "nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.5);
  RecoJetCollectionSelector jetSelector;  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep");
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader("nGenJet", "GenJet");
    genJetReader->setBranchAddresses(inputTree);
    lheInfoReader = new LHEInfoReader();
    lheInfoReader->setBranchAddresses(inputTree);
  }

//--- initialize BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
  std::string mvaFileName_1l_2tau_ttbar_TMVA = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_1l_2tau_ttbar_TMVA;
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("lep_pt");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("TMath::Abs(lep_eta)");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("lep_tth_mva");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("nJet");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("nBJetLoose");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("nBJetMedium");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("mindr_lep_jet");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("mindr_tau1_jet");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("mindr_tau2_jet");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("avg_dr_jet");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("ptmiss");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("mT_lep");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("htmiss");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("tau1_pt");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("tau2_pt");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("TMath::Abs(tau1_eta)");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("TMath::Abs(tau2_eta)");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("dr_lep_tau_os");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("dr_lep_tau_ss");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("dr_taus");
  mvaInputVariables_1l_2tau_ttbar_TMVA.push_back("mTauTauVis");
  TMVAInterface mva_1l_2tau_ttbar_TMVA(mvaFileName_1l_2tau_ttbar_TMVA, mvaInputVariables_1l_2tau_ttbar_TMVA, { "tau1_mva", "tau2_mva" });

  std::map<std::string, double> mvaInputs_TMVA;

  std::string mvaFileName_1l_2tau_ttbar_sklearn = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttbar_sklearn.weights.xml";
  std::vector<std::string> mvaInputVariables_1l_2tau_ttbar_sklearn;
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("nJet");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("mindr_lep_jet");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("avg_dr_jet");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("mT_lep");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("tau1_pt");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("tau2_pt");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("dr_lep_tau_os");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("dr_taus");
  mvaInputVariables_1l_2tau_ttbar_sklearn.push_back("mTauTauVis");
  TMVAInterface mva_1l_2tau_ttbar_sklearn(mvaFileName_1l_2tau_ttbar_sklearn, mvaInputVariables_1l_2tau_ttbar_sklearn);

  std::map<std::string, double> mvaInputs_sklearn;
  
//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  ElectronHistManager preselElectronHistManager(makeHistManager_cfg(process_and_genMatch,
    Form("%s/presel/electrons", histogramDir.data()), central_or_shift));
  preselElectronHistManager.bookHistograms(fs);
  MuonHistManager preselMuonHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/muons", histogramDir.data()), central_or_shift));
  preselMuonHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/hadTaus", histogramDir.data()), central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_lead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/leadHadTau", histogramDir.data()), central_or_shift));
  preselHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_sublead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/subleadHadTau", histogramDir.data()), central_or_shift));
  preselHadTauHistManager_sublead.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/jets", histogramDir.data()), central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/BJets_loose", histogramDir.data()), central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/BJets_medium", histogramDir.data()), central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/met", histogramDir.data()), central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  EvtHistManager_1l_2tau preselEvtHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/presel/evt", histogramDir.data()), central_or_shift));
  preselEvtHistManager.bookHistograms(fs);

  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);
  vstring categories_e = { 
    "1e_2tau_bloose", "1e_2tau_btight"
  };
  std::map<std::string, ElectronHistManager*> selElectronHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_e.begin();
	category != categories_e.end(); ++category ) {
    TString histogramDir_category = histogramDir.data();
    histogramDir_category.ReplaceAll("1l_2tau", category->data());
    ElectronHistManager* selElectronHistManager = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s_%s/sel/electron", category->data(), histogramDir_category.Data()), central_or_shift));
    selElectronHistManager->bookHistograms(fs);
    selElectronHistManager_category[*category] = selElectronHistManager;
  }

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/muons", histogramDir.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);
  vstring categories_mu = { 
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, MuonHistManager*> selMuonHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_mu.begin();
	category != categories_mu.end(); ++category ) {
    TString histogramDir_category = histogramDir.data();
    histogramDir_category.ReplaceAll("1l_2tau", category->data());
    MuonHistManager* selMuonHistManager = new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s_%s/sel/muon", category->data(), histogramDir_category.Data()), central_or_shift));
    selMuonHistManager->bookHistograms(fs);
    selMuonHistManager_category[*category] = selMuonHistManager;
  }

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_lead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/leadHadTau", histogramDir.data()), central_or_shift));
  selHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_sublead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/subleadHadTau", histogramDir.data()), central_or_shift));
  selHadTauHistManager_sublead.bookHistograms(fs);
  vstring categories_tau = {
    "1e_2tau_bloose", "1e_2tau_btight",
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_lead_category; // key = category
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_sublead_category; // key = category
  for ( vstring::const_iterator category = categories_tau.begin();
	category != categories_tau.end(); ++category ) {
    TString histogramDir_category = histogramDir.data();
    histogramDir_category.ReplaceAll("1l_2tau", category->data());
    HadTauHistManager* selHadTauHistManager_lead = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s_%s/sel/leadHadTau", category->data(), histogramDir_category.Data()), central_or_shift));
    selHadTauHistManager_lead->bookHistograms(fs);
    selHadTauHistManager_lead_category[*category] = selHadTauHistManager_lead;
    HadTauHistManager* selHadTauHistManager_sublead = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s_%s/sel/subleadHadTau", category->data(), histogramDir_category.Data()), central_or_shift));
    selHadTauHistManager_sublead->bookHistograms(fs);
    selHadTauHistManager_sublead_category[*category] = selHadTauHistManager_sublead;
  }
  edm::ParameterSet cfg_selHadTauFakeRateHistManager = makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/hadTauFakeRates", histogramDir.data()), central_or_shift);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_lead", hadTauEtaBins_lead);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_sublead", hadTauEtaBins_sublead);
  HadTauFakeRateHistManager selHadTauFakeRateHistManager(cfg_selHadTauFakeRateHistManager);
  selHadTauFakeRateHistManager.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/jets", histogramDir.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/leadJet", histogramDir.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/subleadJet", histogramDir.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/BJets_loose", histogramDir.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/leadBJet_loose", histogramDir.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/subleadBJet_loose", histogramDir.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/BJets_medium", histogramDir.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/met", histogramDir.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  MVAInputVarHistManager selMVAInputVarHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/mvaInputVariables", histogramDir.data()), central_or_shift));
  selMVAInputVarHistManager.bookHistograms(fs, mvaInputVariables_1l_2tau_ttbar_TMVA);

  EvtHistManager_1l_2tau selEvtHistManager(makeHistManager_cfg(process_and_genMatch, 
    Form("%s/sel/evt", histogramDir.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  std::map<std::string, EvtHistManager_1l_2tau*> selEvtHistManager_decayMode; // key = decay mode
  const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString = {
    { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
    { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
    { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
  };
  vstring decayModes_evt;
  decayModes_evt.reserve(decayMode_idString.size());
  boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes_evt));
  if ( isSignal ) {
    for ( vstring::const_iterator decayMode = decayModes_evt.begin();
          decayMode != decayModes_evt.end(); ++decayMode) {
      std::string decayMode_and_genMatch = *decayMode;
      if ( hadTauGenMatchSelection_string != "all" && apply_hadTauGenMatching ) decayMode_and_genMatch += hadTauGenMatchSelection_string;
      EvtHistManager_1l_2tau* selEvtHistManager_ptr = new EvtHistManager_1l_2tau(makeHistManager_cfg(decayMode_and_genMatch,
        Form("%s/sel/evt", histogramDir.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManager_decayMode[*decayMode] = selEvtHistManager_ptr;
    }
  }
  std::map<int, EvtHistManager_1l_2tau*> selEvtHistManagers_genMatch; // key = { kGen_2t0e0m0j, kGen_1t1e0m0j, kGen_1t_0e1m0j, kGen_1t_0e0m1j,... }
  if ( isMC && !apply_hadTauGenMatching ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
	hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {
      if ( hadTauGenMatch_definition->idx_ == kGen_All2 || hadTauGenMatch_definition->idx_ == kGen_Undefined2 ) continue;
      std::string process_and_genMatch = process_string + hadTauGenMatch_definition->name_;
      EvtHistManager_1l_2tau* selEvtHistManager_ptr = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evt", histogramDir.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManagers_genMatch[hadTauGenMatch_definition->idx_] = selEvtHistManager_ptr;
    }
  }
  vstring categories_evt = { 
    "1e_2tau_bloose", "1e_2tau_btight", 
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, EvtHistManager_1l_2tau*> selEvtHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_evt.begin();
	category != categories_evt.end(); ++category ) {
    TString histogramDir_category = histogramDir.data();
    histogramDir_category.ReplaceAll("1l_2tau", category->data());
    EvtHistManager_1l_2tau* selEvtHistManager = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
      Form("%s_%s/sel/evt", category->data(), histogramDir_category.Data()), central_or_shift));
    selEvtHistManager->bookHistograms(fs);
    selEvtHistManager_category[*category] = selEvtHistManager;
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
  
  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  cutFlowTableType cutFlowTable;
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    
    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");

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
	int abs_pdgId = std::abs(genLepton->pdgId_);
	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }
    
    bool isTriggered_1e = use_triggers_1e && (hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits));
    bool isTriggered_1mu = use_triggers_1mu && (hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits));
    if ( !(isTriggered_1e || isTriggered_1mu) ) continue;
    cutFlowTable.update("trigger");

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons);
    
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> selElectrons = tightElectronSelector(preselElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_lead = fakeableHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_sublead = hadTauCleaner(fakeableHadTauSelector_sublead(preselHadTaus), fakeableHadTaus_lead);
    assert(fakeableHadTaus_lead.size() <= 1 && fakeableHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> fakeableHadTaus;
    fakeableHadTaus.insert(fakeableHadTaus.end(), fakeableHadTaus_lead.begin(), fakeableHadTaus_lead.end());
    fakeableHadTaus.insert(fakeableHadTaus.end(), fakeableHadTaus_sublead.begin(), fakeableHadTaus_sublead.end());
    std::vector<const RecoHadTau*> tightHadTaus_lead = tightHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus_sublead = hadTauCleaner(tightHadTauSelector_sublead(preselHadTaus), tightHadTaus_lead);
    assert(tightHadTaus_lead.size() <= 1 && tightHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> tightHadTaus;
    tightHadTaus.insert(tightHadTaus.end(), tightHadTaus_lead.begin(), tightHadTaus_lead.end());
    tightHadTaus.insert(tightHadTaus.end(), tightHadTaus_sublead.begin(), tightHadTaus_sublead.end());
    std::vector<const RecoHadTau*> selHadTaus_lead;
    std::vector<const RecoHadTau*> selHadTaus_sublead;
    std::vector<const RecoHadTau*> selHadTaus;
    if ( hadTauSelection == kLoose ) {
      std::vector<const RecoHadTau*> preselHadTaus_lead;
      if ( preselHadTaus.size() >= 1 ) preselHadTaus_lead.push_back(preselHadTaus[0]);
      selHadTaus_lead = preselHadTaus_lead;
      std::vector<const RecoHadTau*> preselHadTaus_sublead;
      if ( preselHadTaus.size() >= 2 ) preselHadTaus_sublead.push_back(preselHadTaus[1]);
      selHadTaus_sublead = preselHadTaus_sublead;
      selHadTaus = preselHadTaus;
    } else if ( hadTauSelection == kFakeable ) {
      selHadTaus_lead = fakeableHadTaus_lead;
      selHadTaus_sublead = fakeableHadTaus_sublead;
      selHadTaus = fakeableHadTaus;
    } else if ( hadTauSelection == kTight ) {
      selHadTaus_lead = tightHadTaus_lead;
      selHadTaus_sublead = tightHadTaus_sublead;
      selHadTaus = tightHadTaus;
    } else assert(0);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selMuons, selElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);    

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if ( isMC && !fillGenEvtHistograms ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
    	    genLepton != genLeptons.end(); ++genLepton ) {
    	int abs_pdgId = std::abs(genLepton->pdgId_);
    	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
    	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }

//--- match reconstructed to generator level particles
    if ( isMC ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.3);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.3);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.5);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.3);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.3);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.5);

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.3);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.3);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.5);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.3);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.3);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.5);
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    // require exactly one lepton passing loose preselection criteria
    if ( !(preselLeptons.size() == 1) ) continue;
    cutFlowTable.update("1 presel lepton");
    const RecoLepton* preselLepton = preselLeptons[0];
    int preselLepton_type = getLeptonType(preselLepton->pdgId_);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( preselElectrons.size() == 1 && !isTriggered_1e  ) continue;
    if ( preselMuons.size()     == 1 && !isTriggered_1mu ) continue;
    cutFlowTable.update("presel lepton trigger match");

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    std::sort(preselHadTaus.begin(), preselHadTaus.end(), isHigherPt);
    if ( !(preselHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 presel taus");
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    double mTauTauVis_presel = (preselHadTau_lead->p4_ + preselHadTau_sublead->p4_).mass();

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets");
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");

//--- compute MHT and linear MET discriminant (met_LD)
    LV met_p4(met_pt, met_eta, met_phi, 0.);
    LV mht_p4(0,0,0,0);
    for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	  jet != selJets.end(); ++jet ) {
      mht_p4 += (*jet)->p4_;
    }
    for ( std::vector<const RecoLepton*>::const_iterator lepton = preselLeptons.begin();
	  lepton != preselLeptons.end(); ++lepton ) {
      mht_p4 += (*lepton)->p4_;
    }
    for ( std::vector<const RecoHadTau*>::const_iterator hadTau = selHadTaus.begin();
	  hadTau != selHadTaus.end(); ++hadTau ) {
      mht_p4 += (*hadTau)->p4_;
    }
    double met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();    

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      evtWeight *= pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {	
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	evtWeight *= (*jet)->BtagWeight_;
      }
    }

    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(preselLepton_type, preselLepton->pt_, preselLepton->eta_);

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
	evtWeight *= dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
      }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria      
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();
    }    

//--- fill histograms with events passing preselection
    preselMuonHistManager.fillHistograms(preselMuons, evtWeight);
    preselElectronHistManager.fillHistograms(preselElectrons, evtWeight);
    preselHadTauHistManager.fillHistograms(preselHadTaus, evtWeight);
    preselHadTauHistManager_lead.fillHistograms(preselHadTaus, evtWeight);
    preselHadTauHistManager_sublead.fillHistograms(preselHadTaus, evtWeight);
    preselJetHistManager.fillHistograms(selJets, evtWeight);
    preselBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    preselBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    preselMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    preselEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1., -1.,					
      mTauTauVis_presel, evtWeight);

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly one lepton passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() == 1) ) continue;
    cutFlowTable.update("1 sel lepton", evtWeight);
    const RecoLepton* selLepton = selLeptons[0];

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( selElectrons.size() == 1 && !isTriggered_1e  ) continue;
    if ( selMuons.size()     == 1 && !isTriggered_1mu ) continue;
    cutFlowTable.update("sel lepton trigger match", evtWeight);

    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus_lead.size() >= 1 && selHadTaus_sublead.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus_lead[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus_sublead[0];

    const hadTauGenMatchEntry& hadTauGenMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    assert(!(hadTauGenMatch.idx_ == kGen_Undefined2 || hadTauGenMatch.idx_ == kGen_All2));

    if ( hadTauGenMatchSelection != kGen_All2 ) {
      if ( hadTauGenMatch.idx_ != hadTauGenMatchSelection ) continue;
      cutFlowTable.update("tau gen match", evtWeight);
    }
    
    double mTauTauVis = (selHadTau_lead->p4_ + selHadTau_sublead->p4_).mass();

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 4) ) continue;
    cutFlowTable.update(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
 
    double minPt = 20.;
    if ( !(selLepton->pt_ > minPt) ) continue;
    cutFlowTable.update("sel lepton pT > 20 GeV", evtWeight);

    bool isCharge_SS = selHadTau_lead->charge_*selHadTau_sublead->charge_ > 0;
    bool isCharge_OS = selHadTau_lead->charge_*selHadTau_sublead->charge_ < 0;
    if ( hadTauChargeSelection == kOS && isCharge_SS ) continue;
    if ( hadTauChargeSelection == kSS && isCharge_OS ) continue;
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);

    if ( std::abs(selLepton->charge_ + selHadTau_lead->charge_+ selHadTau_sublead->charge_) != 1 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	std::cout << " (selLepton charge = " << selLepton->charge_ 
		  << ", leading selHadTau charge = " << selHadTau_lead->charge_ 
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge_ << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lepton+tau charge");

    if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus_lead.size() >= 1 && tightHadTaus_sublead.size() >= 1 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
    }

    if ( isMC ) {
//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt_, selHadTau_lead->eta_,
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt_, selHadTau_sublead->eta_);
      evtWeight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      evtWeight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      evtWeight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
    }    
    
    if ( applyJetToTauFakeRateWeight ) {
      assert(jetToTauFakeRateInterface);
      
      double prob_fake_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt_, selHadTau_lead->absEta_);
      double prob_fake_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt_, selHadTau_sublead->absEta_);
      
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
    
    const RecoHadTau* selHadTau_OS = 0;
    const RecoHadTau* selHadTau_SS = 0;
    if ( selLepton->charge_*selHadTau_lead->charge_ < 0. ) {
      selHadTau_OS = selHadTau_lead;
      selHadTau_SS = selHadTau_sublead;
    } else if ( selLepton->charge_*selHadTau_lead->charge_ < 0. ) {
      selHadTau_OS = selHadTau_sublead;
      selHadTau_SS = selHadTau_lead;
    }

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
    mvaInputs_TMVA["lep_pt"]               = selLepton->pt_;
    mvaInputs_TMVA["TMath::Abs(lep_eta)"]  = selLepton->absEta_;
    mvaInputs_TMVA["lep_tth_mva"]          = selLepton->mvaRawTTH_;
    mvaInputs_TMVA["nJet"]                 = selJets.size();
    mvaInputs_TMVA["nBJetLoose"]           = selBJets_loose.size();
    mvaInputs_TMVA["nBJetMedium"]          = selBJets_medium.size();
    mvaInputs_TMVA["mindr_lep_jet"]        = TMath::Min(10., comp_mindr_lep1_jet(*selLepton, selJets));
    mvaInputs_TMVA["mindr_tau1_jet"]       = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets));
    mvaInputs_TMVA["mindr_tau2_jet"]       = TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets));
    mvaInputs_TMVA["avg_dr_jet"]           = comp_avg_dr_jet(selJets);
    mvaInputs_TMVA["ptmiss"]               = met_pt;
    mvaInputs_TMVA["mT_lep"]               = comp_MT_met_lep1(*selLepton, met_pt, met_phi);
    mvaInputs_TMVA["htmiss"]               = mht_p4.pt();
    mvaInputs_TMVA["tau1_pt"]              = selHadTau_lead->pt_;
    mvaInputs_TMVA["tau2_pt"]              = selHadTau_sublead->pt_;
    mvaInputs_TMVA["TMath::Abs(tau1_eta)"] = selHadTau_lead->absEta_;
    mvaInputs_TMVA["TMath::Abs(tau2_eta)"] = selHadTau_sublead->absEta_;
    mvaInputs_TMVA["dr_lep_tau_os"]        = ( selHadTau_OS ) ? deltaR(selLepton->p4_, selHadTau_OS->p4_) : 10.;
    mvaInputs_TMVA["dr_lep_tau_ss"]        = ( selHadTau_SS ) ? deltaR(selLepton->p4_, selHadTau_SS->p4_) : 10.;
    mvaInputs_TMVA["dr_taus"]              = deltaR(selHadTau_lead->p4_, selHadTau_sublead->p4_);
    mvaInputs_TMVA["mTauTauVis"]           = mTauTauVis;

    int index = 1;
    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_TMVA.begin();
	  mvaInput != mvaInputs_TMVA.end(); ++mvaInput ) {
      if ( TMath::IsNaN(mvaInput->second) ) {
	std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << ":" << std::endl; 
	std::cout << " mvaInput #" << index << " ('" << mvaInput->first << "') = " << mvaInput->second << " --> setting mvaInput value to zero !!" << std::endl; 
	mvaInputs_TMVA[mvaInput->first] = 0.;
	++index;
      }
    }
    
    double mvaOutput_1l_2tau_ttbar_TMVA = mva_1l_2tau_ttbar_TMVA(mvaInputs_TMVA);

    mvaInputs_sklearn["nJet"]          = mvaInputs_TMVA["nJet"];
    mvaInputs_sklearn["mindr_lep_jet"] = mvaInputs_TMVA["mindr_lep_jet"];
    mvaInputs_sklearn["avg_dr_jet"]    = mvaInputs_TMVA["avg_dr_jet"];
    mvaInputs_sklearn["mT_lep"]        = mvaInputs_TMVA["mT_lep"];
    mvaInputs_sklearn["tau1_pt"]       = mvaInputs_TMVA["tau1_pt"];
    mvaInputs_sklearn["tau2_pt"]       = mvaInputs_TMVA["tau2_pt"];
    mvaInputs_sklearn["dr_lep_tau_os"] = mvaInputs_TMVA["dr_lep_tau_os"];
    mvaInputs_sklearn["dr_taus"]       = mvaInputs_TMVA["dr_taus"];
    mvaInputs_sklearn["mTauTauVis"]    = mvaInputs_TMVA["mTauTauVis"];
    
    double mvaOutput_1l_2tau_ttbar_sklearn = mva_1l_2tau_ttbar_sklearn(mvaInputs_sklearn);

//--- fill histograms with events passing final selection 
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager_lead.fillHistograms(selHadTaus_lead, evtWeight);
    selHadTauHistManager_sublead.fillHistograms(selHadTaus_sublead, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus_lead, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus_sublead, evtWeight);
    selHadTauFakeRateHistManager.fillHistograms(selHadTau_lead, selHadTau_sublead, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selMVAInputVarHistManager.fillHistograms(mvaInputs_TMVA, evtWeight);
    selEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
      mTauTauVis, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selEvtHistManager_decayMode[kv.first]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	    mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
	    mTauTauVis, evtWeight);
          break;
        }
      }
    }
    if ( isMC && !apply_hadTauGenMatching ) {
      EvtHistManager_1l_2tau* selEvtHistManager_genMatch = selEvtHistManagers_genMatch[hadTauGenMatch.idx_];
      assert(selEvtHistManager_genMatch);
      selEvtHistManager_genMatch->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
        mTauTauVis, evtWeight);
    }

    int category = -1;
    if      ( selElectrons.size() == 1 && selBJets_medium.size() >= 1 ) category = k1e_btight;
    else if ( selElectrons.size() == 1                                ) category = k1e_bloose;
    else if ( selMuons.size()     == 1 && selBJets_medium.size() >= 1 ) category = k1mu_btight;
    else if ( selMuons.size()     == 1                                ) category = k1mu_bloose;
    else assert(0);

    if ( category == k1e_btight ) {
      selElectronHistManager_category["1e_2tau_btight"]->fillHistograms(selElectrons, evtWeight);
      selHadTauHistManager_lead_category["1e_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1e_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1e_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
        mTauTauVis, evtWeight);
    } else if ( category == k1e_bloose ) {
      selElectronHistManager_category["1e_2tau_bloose"]->fillHistograms(selElectrons, evtWeight);
      selHadTauHistManager_lead_category["1e_2tau_bloose"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1e_2tau_bloose"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1e_2tau_bloose"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
        mTauTauVis, evtWeight);
    } else if ( category == k1mu_btight ) {
      selMuonHistManager_category["1mu_2tau_btight"]->fillHistograms(selMuons, evtWeight);
      selHadTauHistManager_lead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1mu_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
        mTauTauVis, evtWeight);
    } else if ( category == k1mu_bloose ) {
      selMuonHistManager_category["1mu_2tau_btight"]->fillHistograms(selMuons, evtWeight);
      selHadTauHistManager_lead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1mu_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar_TMVA, mvaOutput_1l_2tau_ttbar_sklearn,
        mTauTauVis, evtWeight);
    } 

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    (*selEventsFile) << run << ":" << lumi << ":" << event;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;
  std::cout << std::endl;

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete jetToTauFakeRateInterface;
  
  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);

  clock.Show("analyze_1l_2tau");

  return EXIT_SUCCESS;
}

