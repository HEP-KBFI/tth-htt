
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
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h" // EvtHistManager_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/EvtTreeManager_2lss_1tau.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
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

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose

//-------------------------------------------------------------------------------
// !!! FOR SYNCHRONIZATION ONLY
const int hadTauSelection_antiElectron = -1; // disabled
const int hadTauSelection_antiMuon = -1; // disabled
//     ONLY FOR SYNCHRONIZATION !!!
//-------------------------------------------------------------------------------
 
/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<produceTTHMVATrainingNtuple_2lss_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("produceTTHMVATrainingNtuple_2lss_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("produceTTHMVATrainingNtuple_2lss_1tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
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
  else throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau") 
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";

  enum { kLoose, kFakeable, kTight };
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection");
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  std::string hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection");

  std::vector<TFile*> inputFilesToClose;

  TH2* lutFakeRate_e = 0;
  TH2* lutFakeRate_mu = 0;
  if ( leptonSelection == kFakeable ) {
    edm::ParameterSet cfg_leptonFakeRate = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateLooseToTightWeight");
    std::string inputFileName = cfg_leptonFakeRate.getParameter<std::string>("inputFileName");
    std::string histogramName_e = cfg_leptonFakeRate.getParameter<std::string>("histogramName_e");
    std::string histogramName_mu = cfg_leptonFakeRate.getParameter<std::string>("histogramName_mu");
    TFile* inputFile = openFile(edm::FileInPath(inputFileName));
    lutFakeRate_e = loadTH2(inputFile, histogramName_e);
    lutFakeRate_mu = loadTH2(inputFile, histogramName_mu);
    inputFilesToClose.push_back(inputFile);
  }

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if      ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HF")       ) jet_btagWeight_branch = "Jet_bTagWeightHF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats1") ) jet_btagWeight_branch = "Jet_bTagWeightHFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats2") ) jet_btagWeight_branch = "Jet_bTagWeightHFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LF")       ) jet_btagWeight_branch = "Jet_bTagWeightLF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats1") ) jet_btagWeight_branch = "Jet_bTagWeightLFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats2") ) jet_btagWeight_branch = "Jet_bTagWeightLFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr1")    ) jet_btagWeight_branch = "Jet_bTagWeightcErr1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr2")    ) jet_btagWeight_branch = "Jet_bTagWeightcErr2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = "Jet_bTagWeightJES" + shiftUp_or_Down;
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
      else assert(0);
    } else throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  }

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  
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
    throw cms::Exception("produceTTHMVATrainingNtuple_2lss_1tau") 
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
  hltPaths_setBranchAddresses(inputTree, triggers_2e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_2mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

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
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, run_lumi_eventSelector != 0);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, run_lumi_eventSelector != 0);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorTight hadTauSelector(era);
  hadTauSelector.set(hadTauSelection_string);
  hadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  hadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  
  RecoJetReader* jetReader = new RecoJetReader(era, "nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep", "nGenLepFromTau", "GenLepFromTau");
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader("nGenJet", "GenJet");
    genJetReader->setBranchAddresses(inputTree);
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
  TMVAInterface mva_2lss_ttV(mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttbar;
  mvaInputVariables_2lss_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttbar.push_back("min(met_pt,400)");
  mvaInputVariables_2lss_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_ttbar.push_back("MT_met_lep1");
  TMVAInterface mva_2lss_ttbar(mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::map<std::string, double> mvaInputs;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  std::string charge_and_leptonSelection = Form("%s_%s", leptonChargeSelection_string.data(), leptonSelection_string.data());
  ElectronHistManager preselElectronHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/electrons", charge_and_leptonSelection.data()), central_or_shift));
  preselElectronHistManager.bookHistograms(fs);
  MuonHistManager preselMuonHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/muons", charge_and_leptonSelection.data()), central_or_shift));
  preselMuonHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/hadTaus", charge_and_leptonSelection.data()), central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/jets", charge_and_leptonSelection.data()), central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/BJets_loose", charge_and_leptonSelection.data()), central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/BJets_medium", charge_and_leptonSelection.data()), central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/met", charge_and_leptonSelection.data()), central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  EvtHistManager_2lss_1tau preselEvtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/evt", charge_and_leptonSelection.data()), central_or_shift));
  preselEvtHistManager.bookHistograms(fs);

  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/electrons", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);
  vstring categories_e = { 
    "2epp_1tau_bloose", "2epp_1tau_btight", "2emm_1tau_bloose", "2emm_1tau_btight", 
    "1e1mupp_1tau_bloose", "1e1mupp_1tau_btight", "1e1mumm_1tau_bloose", "1e1mumm_1tau_btight" };
  std::map<std::string, std::map<std::string, ElectronHistManager*>> selElectronHistManager_category; // key = category, "leadElectron"/"subleadElectron"/"electron"
  for ( vstring::const_iterator category = categories_e.begin();
	category != categories_e.end(); ++category ) {
    if ( category->find("2epp") != std::string::npos || category->find("2emm") != std::string::npos ) {
      ElectronHistManager* selElectronHistManager_lead = new ElectronHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/leadElectron", category->data(), charge_and_leptonSelection.data()), central_or_shift, 0));
      selElectronHistManager_lead->bookHistograms(fs);
      selElectronHistManager_category[*category]["leadElectron"] = selElectronHistManager_lead;
      ElectronHistManager* selElectronHistManager_sublead = new ElectronHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/subleadElectron", category->data(), charge_and_leptonSelection.data()), central_or_shift, 1));
      selElectronHistManager_sublead->bookHistograms(fs);
      selElectronHistManager_category[*category]["subleadElectron"] = selElectronHistManager_sublead;
    }
    if ( category->find("1e1mupp") != std::string::npos || category->find("1e1mumm") != std::string::npos ) {
      ElectronHistManager* selElectronHistManager = new ElectronHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/electron", category->data(), charge_and_leptonSelection.data()), central_or_shift));
      selElectronHistManager->bookHistograms(fs);
      selElectronHistManager_category[*category]["electron"] = selElectronHistManager;
    }
  }

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/muons", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);
  vstring categories_mu = { 
    "1e1mupp_1tau_bloose", "1e1mupp_1tau_btight", "1e1mumm_1tau_bloose", "1e1mumm_1tau_btight",
    "2mupp_1tau_bloose", "2mupp_1tau_btight", "2mumm_1tau_bloose", "2mumm_1tau_btight" 
  };
  std::map<std::string, std::map<std::string, MuonHistManager*>> selMuonHistManager_category; // key = category, "leadMuon"/"subleadMuon"/"muon"
  for ( vstring::const_iterator category = categories_mu.begin();
	category != categories_mu.end(); ++category ) {
    if ( category->find("1e1mupp") != std::string::npos || category->find("1e1mumm") != std::string::npos ) {
      MuonHistManager* selMuonHistManager = new MuonHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/muon", category->data(), charge_and_leptonSelection.data()), central_or_shift));
      selMuonHistManager->bookHistograms(fs);
      selMuonHistManager_category[*category]["muon"] = selMuonHistManager;
    }
    if ( category->find("2mupp") != std::string::npos || category->find("2mumm") != std::string::npos ) {
      MuonHistManager* selMuonHistManager_lead = new MuonHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/leadMuon", category->data(), charge_and_leptonSelection.data()), central_or_shift, 0));
      selMuonHistManager_lead->bookHistograms(fs);
      selMuonHistManager_category[*category]["leadMuon"] = selMuonHistManager_lead;
      MuonHistManager* selMuonHistManager_sublead = new MuonHistManager(makeHistManager_cfg(process_string, 
	Form("%s_%s/sel/subleadMuon", category->data(), charge_and_leptonSelection.data()), central_or_shift, 1));
      selMuonHistManager_sublead->bookHistograms(fs);
      selMuonHistManager_category[*category]["subleadMuon"] = selMuonHistManager_sublead;
    }
  }

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/hadTaus", charge_and_leptonSelection.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/jets", charge_and_leptonSelection.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/leadJet", charge_and_leptonSelection.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/subleadJet", charge_and_leptonSelection.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/BJets_loose", charge_and_leptonSelection.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/leadBJet_loose", charge_and_leptonSelection.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/subleadBJet_loose", charge_and_leptonSelection.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/BJets_medium", charge_and_leptonSelection.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/met", charge_and_leptonSelection.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  EvtHistManager_2lss_1tau selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  std::map<std::string, EvtHistManager_2lss_1tau*> selEvtHistManager_decayMode; // key = decay mode
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
      EvtHistManager_2lss_1tau* selEvtHistManager_ptr = new EvtHistManager_2lss_1tau(makeHistManager_cfg(decayMode->data(),
        Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManager_decayMode[*decayMode] = selEvtHistManager_ptr;
    }
  }
  EvtHistManager_2lss_1tau* selEvtHistManager_genHadTau = 0;
  EvtHistManager_2lss_1tau* selEvtHistManager_genLepton = 0;
  EvtHistManager_2lss_1tau* selEvtHistManager_genJet = 0;
  if ( isMC ) {
    std::string process_and_genMatchedHadTau = process_string + "t";
    selEvtHistManager_genHadTau = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_and_genMatchedHadTau, 
      Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
    selEvtHistManager_genHadTau->bookHistograms(fs);
    std::string process_and_genMatchedLepton = process_string + "l";
    selEvtHistManager_genLepton = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_and_genMatchedLepton, 
      Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
    selEvtHistManager_genLepton->bookHistograms(fs);
    std::string process_and_genMatchedJet = process_string + "j";
    selEvtHistManager_genJet = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_and_genMatchedJet, 
      Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
    selEvtHistManager_genJet->bookHistograms(fs);
  }
  vstring categories_evt = { 
    "2epp_1tau_bloose", "2epp_1tau_btight", "2emm_1tau_bloose", "2emm_1tau_btight",
    "1e1mupp_1tau_bloose", "1e1mupp_1tau_btight", "1e1mumm_1tau_bloose", "1e1mumm_1tau_btight",
    "2mupp_1tau_bloose", "2mupp_1tau_btight", "2mumm_1tau_bloose", "2mumm_1tau_btight" 
  };
  std::map<std::string, EvtHistManager_2lss_1tau*> selEvtHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_evt.begin();
	category != categories_evt.end(); ++category ) {
    EvtHistManager_2lss_1tau* selEvtHistManager_ptr = new EvtHistManager_2lss_1tau(makeHistManager_cfg(process_string,
      Form("%s_%s/sel/evt", category->data(), charge_and_leptonSelection.data()), central_or_shift));
    selEvtHistManager_ptr->bookHistograms(fs);
    selEvtHistManager_category[*category] = selEvtHistManager_ptr;
  }

  GenEvtHistManager genEvtHistManager_beforeCuts(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/unbiased/genEvt", charge_and_leptonSelection.data()), central_or_shift));
  genEvtHistManager_beforeCuts.bookHistograms(fs);
  GenEvtHistManager genEvtHistManager_afterCuts(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/genEvt", charge_and_leptonSelection.data()), central_or_shift));
  genEvtHistManager_afterCuts.bookHistograms(fs);
  
  EvtTreeManager_2lss_1tau selEvtTreeManager(makeHistManager_cfg(process_string,  
    Form("2lss_1tau_%s/sel/evtntuple", charge_and_leptonSelection.data()), central_or_shift));
  selEvtTreeManager.bookTree(fs);

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
      genEvtHistManager_beforeCuts.fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
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
    if ( !isMC ) {
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
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else if ( leptonSelection == kTight    ) selMuons = tightMuons;
    else assert(0);
    //for ( size_t idxPreselMuon = 0; idxPreselMuon < preselMuons.size(); ++idxPreselMuon ) {
    //  std::cout << "preselMuon #" << idxPreselMuon << ":" << std::endl;
    //  std::cout << (*preselMuons[idxPreselMuon]);
    //}
    
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
    //for ( size_t idxPreselElectron = 0; idxPreselElectron < preselElectrons.size(); ++idxPreselElectron ) {
    //  std::cout << "preselElectron #" << idxPreselElectron << ":" << std::endl;
    //  std::cout << (*preselElectrons[idxPreselElectron]);
    //}

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    
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

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.3);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.3);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.5);

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
    // require exactly two leptons passing loose preselection criteria to avoid overlap with 3l category
    if ( !(preselLeptons.size() == 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS preselLeptons selection." << std::endl;
	std::cout << " (#preselLeptons = " << preselLeptons.size() << ")" << std::endl;
	for ( size_t idxPreselLepton = 0; idxPreselLepton < preselLeptons.size(); ++idxPreselLepton ) {
	  std::cout << "preselLepton #" << idxPreselLepton << ":" << std::endl;
	  std::cout << (*preselLeptons[idxPreselLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update("2 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId_);
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId_);

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

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on preselection level
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets");
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selHadTaus selection." << std::endl;
	std::cout << " (#selHadTaus = " << selHadTaus.size() << ")" << std::endl;
	for ( size_t idxSelHadTau = 0; idxSelHadTau < selHadTaus.size(); ++idxSelHadTau ) {
	  std::cout << "selHadTau #" << idxSelHadTau << ":" << std::endl;
	  std::cout << (*selHadTaus[idxSelHadTau]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau (1)");
    const RecoHadTau* selHadTau = selHadTaus[0];

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

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      evtWeight *= pileupWeight;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	evtWeight *= (*jet)->BtagWeight_;
      }
    }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria
    if ( isMC ) {
      evtWeight *= sf_triggerEff(2,
        preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      evtWeight *= sf_leptonID_and_Iso_loose(2,
        preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
    }

    double evtWeight_pp = evtWeight;
    double evtWeight_mm = evtWeight;
    if ( leptonChargeSelection == kOS ) {
      double prob_chargeMisId_lead = prob_chargeMisId(getLeptonType(preselLepton_lead->pdgId_), preselLepton_lead->pt_, preselLepton_lead->eta_);
      double prob_chargeMisId_sublead = prob_chargeMisId(getLeptonType(preselLepton_sublead->pdgId_), preselLepton_sublead->pt_, preselLepton_sublead->eta_);

      evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);

      if ( preselLepton_lead->charge_ < 0 && preselLepton_sublead->charge_ > 0 ) {
	evtWeight_pp *= prob_chargeMisId_lead;
	evtWeight_mm *= prob_chargeMisId_sublead;
      }
      if ( preselLepton_lead->charge_ > 0 && preselLepton_sublead->charge_ < 0 ) {
	evtWeight_pp *= prob_chargeMisId_sublead;
	evtWeight_mm *= prob_chargeMisId_lead;
      }
    } 

    const RecoLepton* preselLepton1_OS = 0;
    const RecoLepton* preselLepton2_OS = 0;
    if ( preselLepton_lead->charge_*selHadTau->charge_ < 0. ) {
      preselLepton1_OS = preselLepton_lead;
    } 
    if ( preselLepton_sublead->charge_*selHadTau->charge_ < 0. ) {
      if ( !preselLepton1_OS ) preselLepton1_OS = preselLepton_sublead;
      else preselLepton2_OS = preselLepton_sublead;
    }
    double mTauTauVis1_presel = ( preselLepton1_OS ) ? (preselLepton1_OS->p4_ + selHadTau->p4_).mass() : -1.;
    double mTauTauVis2_presel = ( preselLepton2_OS ) ? (preselLepton2_OS->p4_ + selHadTau->p4_).mass() : -1.;

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    mvaInputs["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(preselLepton_lead->eta_), std::fabs(preselLepton_sublead->eta_));
    mvaInputs["MT_met_lep1"]                = comp_MT_met_lep1(*preselLepton_lead, met_pt, met_phi);
    mvaInputs["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*preselLepton_lead, selJets);
    mvaInputs["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*preselLepton_sublead, selJets);
    mvaInputs["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*preselLepton_lead);
    mvaInputs["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*preselLepton_sublead);
    mvaInputs["min(met_pt,400)"]            = std::min(met_pt, (Float_t)400.);
    mvaInputs["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);

    int index = 1;
    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
	  mvaInput != mvaInputs.end(); ++mvaInput ) {
      if ( TMath::IsNaN(mvaInput->second) ) {
	std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << ":" << std::endl; 
	std::cout << " mvaInput #" << index << " ('" << mvaInput->first << "') = " << mvaInput->second << " --> setting mvaInput value to zero !!" << std::endl; 
	mvaInputs[mvaInput->first] = 0.;
	++index;
      }
    }

    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs);
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table X of AN-2015/321
    Double_t mvaDiscr_2lss = -1;
    if      ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 6.;
    else if ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 5.;
    else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 4.;
    else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 3.;
    else if (                                mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 2.;
    else                                                                  mvaDiscr_2lss = 1.;

//--- fill histograms with events passing preselection
    preselMuonHistManager.fillHistograms(preselMuons, evtWeight);
    preselElectronHistManager.fillHistograms(preselElectrons, evtWeight);
    preselHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    preselJetHistManager.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    preselMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    preselEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1.,
      mTauTauVis1_presel, mTauTauVis2_presel, evtWeight);

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
	std::cout << " (#selLeptons = " << selLeptons.size() << ")" << std::endl;
	for ( size_t idxSelLepton = 0; idxSelLepton < selLeptons.size(); ++idxSelLepton ) {
	  std::cout << "selLepton #" << idxSelLepton << ":" << std::endl;
	  std::cout << (*selLeptons[idxSelLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update("2 sel leptons", evtWeight);
    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

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

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 4) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
	for ( size_t idxSelJet = 0; idxSelJet < selJets.size(); ++idxSelJet ) {
	  std::cout << "selJet #" << idxSelJet << ":" << std::endl;
	  std::cout << (*selJets[idxSelJet]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
	for ( size_t idxSelBJet_loose = 0; idxSelBJet_loose < selBJets_loose.size(); ++idxSelBJet_loose ) {
	  std::cout << "selJet #" << idxSelBJet_loose << ":" << std::endl;
	  std::cout << (*selJets[idxSelBJet_loose]);
	}
	for ( size_t idxSelBJet_medium = 0; idxSelBJet_medium < selBJets_medium.size(); ++idxSelBJet_medium ) {
	  std::cout << "selJet #" << idxSelBJet_medium << ":" << std::endl;
	  std::cout << (*selJets[idxSelBJet_medium]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
    if ( !(selHadTaus.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selHadTaus selection." << std::endl;
	std::cout << " (#selHadTaus = " << selHadTaus.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 1 sel tau (2)", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = selLeptons.begin();
	  lepton1 != selLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != selLeptons.end(); ++lepton2 ) {
	if ( ((*lepton1)->p4_ + (*lepton2)->p4_).mass() < 12. ) {
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

    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt_ > minPt_lead && selLepton_sublead->pt_ > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selLepton_lead->pt_ << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selLepton_sublead->pt_ << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 20 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool isCharge_SS = selLepton_lead->charge_*selLepton_sublead->charge_ > 0;
    bool isCharge_OS = selLepton_lead->charge_*selLepton_sublead->charge_ < 0;
    if ( leptonChargeSelection == kOS && isCharge_SS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge_ 
		  << ", subleading selLepton charge = " << selLepton_sublead->charge_ << ", leptonChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kSS && isCharge_OS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge_ 
		  << ", subleading selLepton charge = " << selLepton_sublead->charge_ << ", leptonChargeSelection = SS)" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(Form("lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeight);

    if ( std::abs(selLepton_lead->charge_ + selLepton_sublead->charge_ + selHadTau->charge_) != 1 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge_ 
		  << ", subleading selLepton charge = " << selLepton_sublead->charge_ 
		  << ", selHadTau charge = " << selHadTau->charge_ << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lepton+tau charge");

    bool failsZbosonMassVeto = false;
    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton1 = selLeptons.begin();
	    lepton1 != selLeptons.end(); ++lepton1 ) {
	for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	      lepton2 != selLeptons.end(); ++lepton2 ) {
	  if ( std::fabs(((*lepton1)->p4_ + (*lepton2)->p4_).mass() - z_mass) < z_window ) {
	    failsZbosonMassVeto = true;
	  }
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

    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      if ( met_LD < 0.2 ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS MET LD selection." << std::endl;
	  std::cout << " (LD = " << met_LD << ")" << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("met LD > 0.2", evtWeight);

    if ( leptonSelection == kFakeable ) {
      if ( (tightMuons.size() + tightElectrons.size()) >= 2 ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS tightElectrons+tightMuons selection." << std::endl;
	  std::cout << " (#tightElectrons = " << tightElectrons.size() << ", #tightMuons = " << tightMuons.size() << ")" << std::endl;
	}
	continue; // CV: avoid overlap with signal region
      }
    }
    cutFlowTable.update("signal region veto", evtWeight);

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
    if ( isMC ) {
      double sf_tight_to_loose = 1.;
      if ( leptonSelection == kFakeable ) {
	sf_tight_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(2,
          preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
          preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      } else if ( leptonSelection == kTight ) {
	sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(2,
          preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	  preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      }
      evtWeight *= sf_tight_to_loose;
      evtWeight_pp *= sf_tight_to_loose;
      evtWeight_mm *= sf_tight_to_loose;
    }

    if ( leptonSelection == kFakeable ) {
      TH2* lutFakeRate_lead = 0;
      if      ( std::abs(selLepton_lead->pdgId_) == 11 ) lutFakeRate_lead = lutFakeRate_e;
      else if ( std::abs(selLepton_lead->pdgId_) == 13 ) lutFakeRate_lead = lutFakeRate_mu;
      assert(lutFakeRate_lead);
      double prob_fake_lead = getSF_from_TH2(lutFakeRate_lead, selLepton_lead->pt_, selLepton_lead->eta_);

      TH2* lutFakeRate_sublead = 0;
      if      ( std::abs(selLepton_sublead->pdgId_) == 11 ) lutFakeRate_sublead = lutFakeRate_e;
      else if ( std::abs(selLepton_sublead->pdgId_) == 13 ) lutFakeRate_sublead = lutFakeRate_mu;
      assert(lutFakeRate_sublead);
      double prob_fake_sublead = getSF_from_TH2(lutFakeRate_sublead, selLepton_sublead->pt_, selLepton_sublead->eta_);

      bool passesTight_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
      bool passesTight_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);

      double p1 = prob_fake_lead/(1. - prob_fake_lead);
      double p2 = prob_fake_sublead/(1. - prob_fake_sublead);
      double evtWeight_tight_to_loose = 0.;
      if      ( !passesTight_lead &&  passesTight_sublead ) evtWeight_tight_to_loose =  p1;
      else if (  passesTight_lead && !passesTight_sublead ) evtWeight_tight_to_loose =  p2;
      else if ( !passesTight_lead && !passesTight_sublead ) evtWeight_tight_to_loose = -p1*p2;
      evtWeight *= evtWeight_tight_to_loose;
      evtWeight_pp *= evtWeight_tight_to_loose;
      evtWeight_mm *= evtWeight_tight_to_loose;
    }

//--- fill histograms with events passing final selection 
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selEvtHistManager.fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
      mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1.,
      mTauTauVis1_presel, mTauTauVis2_presel, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selEvtHistManager_decayMode[kv.first]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
            mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1.,
            mTauTauVis1_presel, mTauTauVis2_presel, evtWeight);
          break;
        }
      }
    }
    if ( isMC ) {
      EvtHistManager_2lss_1tau* selEvtHistManager_genMatch = 0;
      if      ( selHadTau_lead->genHadTau_                               ) selEvtHistManager_genMatch = selEvtHistManager_genHadTau;
      else if ( selHadTau_lead->genHadTau_ || selHadTau_lead->genLepton_ ) selEvtHistManager_genMatch = selEvtHistManager_genLepton;
      else                                                                 selEvtHistManager_genMatch = selEvtHistManager_genJet;
      assert(selEvtHistManager_genMatch);
      selEvtHistManager_genMatch->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
	mTauTauVis1_presel, mTauTauVis2_presel, evtWeight);
    }

    if ( isMC ) {
      genEvtHistManager_afterCuts.fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }
    
    bool isCharge_pp = selLepton_lead->pdgId_ < 0 && selLepton_sublead->pdgId_ < 0;
    bool isCharge_mm = selLepton_lead->pdgId_ > 0 && selLepton_sublead->pdgId_ > 0;

    bool isCategory_2epp_btight = selElectrons.size() == 2 && (isCharge_pp || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_2epp_bloose = selElectrons.size() == 2 && (isCharge_pp || leptonChargeSelection == kOS);
    bool isCategory_2emm_btight = selElectrons.size() == 2 && (isCharge_mm || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_2emm_bloose = selElectrons.size() == 2 && (isCharge_mm || leptonChargeSelection == kOS);
    bool isCategory_1e1mupp_btight = selElectrons.size() == 1 && selMuons.size() == 1 && (isCharge_pp || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_1e1mupp_bloose = selElectrons.size() == 1 && selMuons.size() == 1 && (isCharge_pp || leptonChargeSelection == kOS);
    bool isCategory_1e1mumm_btight = selElectrons.size() == 1 && selMuons.size() == 1 && (isCharge_mm || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_1e1mumm_bloose = selElectrons.size() == 1 && selMuons.size() == 1 && (isCharge_mm || leptonChargeSelection == kOS);
    bool isCategory_2mupp_btight = selMuons.size() == 2 && (isCharge_pp || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_2mupp_bloose = selMuons.size() == 2 && (isCharge_pp || leptonChargeSelection == kOS);
    bool isCategory_2mumm_btight = selMuons.size() == 2 && (isCharge_mm || leptonChargeSelection == kOS) && selBJets_medium.size() >= 1;
    bool isCategory_2mumm_bloose = selMuons.size() == 2 && (isCharge_mm || leptonChargeSelection == kOS);

    if ( isCategory_2epp_btight ) {
      selElectronHistManager_category["2epp_1tau_btight"]["leadElectron"]->fillHistograms(selElectrons, evtWeight_pp);
      selElectronHistManager_category["2epp_1tau_btight"]["subleadElectron"]->fillHistograms(selElectrons, evtWeight_pp);
      selEvtHistManager_category["2epp_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_2epp_bloose ) {
      selElectronHistManager_category["2epp_1tau_bloose"]["leadElectron"]->fillHistograms(selElectrons, evtWeight_pp);
      selElectronHistManager_category["2epp_1tau_bloose"]["subleadElectron"]->fillHistograms(selElectrons, evtWeight_pp);
      selEvtHistManager_category["2epp_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_2emm_btight ) {
      selElectronHistManager_category["2emm_1tau_btight"]["leadElectron"]->fillHistograms(selElectrons, evtWeight_mm);
      selElectronHistManager_category["2emm_1tau_btight"]["subleadElectron"]->fillHistograms(selElectrons, evtWeight_mm);
      selEvtHistManager_category["2emm_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 
    if ( isCategory_2emm_bloose ) {
      selElectronHistManager_category["2emm_1tau_bloose"]["leadElectron"]->fillHistograms(selElectrons, evtWeight_mm);
      selElectronHistManager_category["2emm_1tau_bloose"]["subleadElectron"]->fillHistograms(selElectrons, evtWeight_mm);
      selEvtHistManager_category["2emm_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 
    if ( isCategory_1e1mupp_btight ) {
      selElectronHistManager_category["1e1mupp_1tau_btight"]["electron"]->fillHistograms(selElectrons, evtWeight_pp);
      selMuonHistManager_category["1e1mupp_1tau_btight"]["muon"]->fillHistograms(selMuons, evtWeight_pp);
      selEvtHistManager_category["1e1mupp_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_1e1mupp_bloose ) {
      selElectronHistManager_category["1e1mupp_1tau_bloose"]["electron"]->fillHistograms(selElectrons, evtWeight_pp);
      selMuonHistManager_category["1e1mupp_1tau_bloose"]["muon"]->fillHistograms(selMuons, evtWeight_pp);
      selEvtHistManager_category["1e1mupp_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_1e1mumm_btight ) {
      selElectronHistManager_category["1e1mumm_1tau_btight"]["electron"]->fillHistograms(selElectrons, evtWeight_mm);
      selMuonHistManager_category["1e1mumm_1tau_btight"]["muon"]->fillHistograms(selMuons, evtWeight_mm);
      selEvtHistManager_category["1e1mumm_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
	selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 
    if ( isCategory_1e1mumm_bloose ) {
      selElectronHistManager_category["1e1mumm_1tau_bloose"]["electron"]->fillHistograms(selElectrons, evtWeight_mm);
      selMuonHistManager_category["1e1mumm_1tau_bloose"]["muon"]->fillHistograms(selMuons, evtWeight_mm);
      selEvtHistManager_category["1e1mumm_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 
    if ( isCategory_2mupp_btight ) {
      selMuonHistManager_category["2mupp_1tau_btight"]["leadMuon"]->fillHistograms(selMuons, evtWeight_pp);
      selMuonHistManager_category["2mupp_1tau_btight"]["subleadMuon"]->fillHistograms(selMuons, evtWeight_pp);
      selEvtHistManager_category["2mupp_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(),
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_2mupp_bloose ) {
      selMuonHistManager_category["2mupp_1tau_bloose"]["leadMuon"]->fillHistograms(selMuons, evtWeight_pp);
      selMuonHistManager_category["2mupp_1tau_bloose"]["subleadMuon"]->fillHistograms(selMuons, evtWeight_pp);
      selEvtHistManager_category["2mupp_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_pp);
    } 
    if ( isCategory_2mumm_btight ) {
      selMuonHistManager_category["2mumm_1tau_btight"]["leadMuon"]->fillHistograms(selMuons, evtWeight_mm);
      selMuonHistManager_category["2mumm_1tau_btight"]["subleadMuon"]->fillHistograms(selMuons, evtWeight_mm);
      selEvtHistManager_category["2mumm_1tau_btight"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 
    if ( isCategory_2mumm_bloose ) {
      selMuonHistManager_category["2mumm_1tau_bloose"]["leadMuon"]->fillHistograms(selMuons, evtWeight_mm);
      selMuonHistManager_category["2mumm_1tau_bloose"]["subleadMuon"]->fillHistograms(selMuons, evtWeight_mm);
      selEvtHistManager_category["2mumm_1tau_bloose"]->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, -1., -1., 
        mTauTauVis1_presel, mTauTauVis2_presel, evtWeight_mm);
    } 


    //---Fill Trees for MVA training 
    float mindr_tau_jet = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets)); 
    float mindr_lep1_jet  = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));  
    float mindr_lep2_jet  = TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets)); 
    float mT_lep1 = comp_MT_met_lep1(*selLepton_lead, met_pt, met_phi); 
    float mT_lep2 = comp_MT_met_lep1(*selLepton_sublead, met_pt, met_phi); 
    float avg_dr_jet = comp_avg_dr_jet(selJets); 
    float dr_leps = deltaR(selLepton_lead->p4_, selLepton_sublead->p4_); 
    float dr_lep1_tau = deltaR(selLepton_lead->p4_, selHadTau_lead->p4_); 
    float dr_lep2_tau = deltaR(selLepton_sublead->p4_, selHadTau_lead->p4_); 
    float lep1_conePt = comp_lep1_conePt(*selLepton_lead);  
    float lep2_conePt = comp_lep2_conePt(*selLepton_sublead);  
    selEvtTreeManager.fillTree(selLepton_lead->pt_, selLepton_sublead->pt_, lep1_conePt, lep2_conePt, selLepton_lead->eta_, selLepton_sublead->eta_, 
                               selLepton_lead->mvaRawTTH_, selLepton_sublead->mvaRawTTH_, selJets.size(), selBJets_loose.size(),  
                               selBJets_medium.size(), mindr_lep1_jet, mindr_lep2_jet, mindr_tau_jet, avg_dr_jet, float(met_p4.pt()),  
                               mT_lep1, mT_lep2, float(mht_p4.pt()), selHadTau_lead->raw_mva_dR03_, selHadTau_lead->pt_, selHadTau_lead->eta_, 
                               dr_leps, dr_lep1_tau, dr_lep2_tau, mTauTauVis1_presel, mTauTauVis2_presel);
    
    (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

  for ( std::vector<TFile*>::iterator inputFile = inputFilesToClose.begin();
	inputFile != inputFilesToClose.end(); ++inputFile ) {
    delete (*inputFile);
  }  

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  clock.Show("produceTTHMVATrainingNtuple_2lss_1tau");

  return EXIT_SUCCESS;
}

