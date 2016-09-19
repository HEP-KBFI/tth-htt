
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
#include <TMatrixD.h> // TMatrixD

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 0l_3tau category
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_3tau.h" // EvtHistManager_0l_3tau
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_3tau, getHadTauGenMatch
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
#include "tthAnalysis/HiggsToTauTau/interface/hadTauTriggerTurnOnCurves.h" // effHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"

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

enum { k0l_btight, k0l_bloose };

const int hadTauSelection_antiElectron_lead = 1; // vLoose
const int hadTauSelection_antiMuon_lead = 1; // Loose 
const int hadTauSelection_antiElectron_sublead = 2; // Loose
const int hadTauSelection_antiMuon_sublead = 1; // Loose 
const int hadTauSelection_antiElectron_third = 2; // Loose
const int hadTauSelection_antiMuon_third = 1; // Loose

int getHadTau_genPdgId(const RecoHadTau* hadTau)
{
  int hadTau_genPdgId = -1;
  if      ( hadTau->genHadTau_ ) hadTau_genPdgId = 15;
  else if ( hadTau->genLepton_ ) hadTau_genPdgId = std::abs(hadTau->genLepton_->pdgId_);
  return hadTau_genPdgId;
}

/**
 * @brief Produce datacard and control plots for 0l_3tau category.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<analyze_0l_3tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_0l_3tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_0l_3tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_0l_3tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames = cfg_analyze.getParameter<vstring>("triggers");
  //std::vector<hltPath*> triggers = create_hltPaths(triggerNames);

  enum { kLoose, kFakeable, kTight };
  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"                                                     ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" || hadTauSelection_part1 == "Fakeable_mcClosure" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"                                                     ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;
  
  std::string hadTauGenMatchSelection_string = cfg_analyze.getParameter<std::string>("hadTauGenMatch");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_3tau();
  int hadTauGenMatchSelection = getHadTauGenMatch_int(hadTauGenMatch_definitions, hadTauGenMatchSelection_string);
  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  if ( hadTauGenMatchSelection_string != "all" && !apply_hadTauGenMatching ) {
    throw cms::Exception("analyze_0l_3tau") 
      << "Invalid combination of Configuration parameters 'hadTauGenMatch' = " << hadTauGenMatchSelection_string << ", 'apply_hadTauGenMatching' = " << apply_hadTauGenMatching << " !!\n";
  }

  vdouble hadTauEtaBins_lead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_lead"); // CV: eta bins in which jet->tau fake-rates are determined
  vdouble hadTauEtaBins_sublead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_sublead");

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  int lheScale_option = kLHE_scale_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_0l_3tau")
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
      throw cms::Exception("analyze_0l_3tau")
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
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_third", hadTauSelection_antiElectron_third);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_third", hadTauSelection_antiMuon_third);
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
    throw cms::Exception("analyze_0l_3tau") 
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

  //hltPaths_setBranchAddresses(inputTree, triggers);

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

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector;

  RecoHadTauReader* hadTauReader = new RecoHadTauReader("nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector;
  preselHadTauSelector.set_min_pt(20.);
  preselHadTauSelector.set_min_antiElectron(1);
  preselHadTauSelector.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_lead;
  fakeableHadTauSelector_lead.set_min_pt(40.);
  fakeableHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  fakeableHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_sublead;
  fakeableHadTauSelector_sublead.set_min_pt(40.);
  fakeableHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  fakeableHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_third;
  fakeableHadTauSelector_third.set_min_pt(20.);
  fakeableHadTauSelector_third.set_min_antiElectron(hadTauSelection_antiElectron_third);
  fakeableHadTauSelector_third.set_min_antiMuon(hadTauSelection_antiMuon_third);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_lead;
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_lead.set(hadTauSelection_part2);
  tightHadTauSelector_lead.set_min_pt(40.);
  tightHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  tightHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_sublead;
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_sublead.set(hadTauSelection_part2);
  tightHadTauSelector_sublead.set_min_pt(40.);
  tightHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  tightHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_third;
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_third.set(hadTauSelection_part2);
  tightHadTauSelector_third.set_min_pt(20.);
  tightHadTauSelector_third.set_min_antiElectron(hadTauSelection_antiElectron_third);
  tightHadTauSelector_third.set_min_antiMuon(hadTauSelection_antiMuon_third);

  RecoJetReader* jetReader = new RecoJetReader("nJet", "Jet");
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

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/hadTaus", hadTauSelection_part1.data()), central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_lead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/leadHadTau", hadTauSelection_part1.data()), central_or_shift));
  preselHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/subleadHadTau", hadTauSelection_part1.data()), central_or_shift));
  preselHadTauHistManager_sublead.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_third(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/thirdHadTau", hadTauSelection_part1.data()), central_or_shift));
  preselHadTauHistManager_third.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/jets", hadTauSelection_part1.data()), central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/BJets_loose", hadTauSelection_part1.data()), central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/BJets_medium", hadTauSelection_part1.data()), central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/met", hadTauSelection_part1.data()), central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  EvtHistManager_0l_3tau preselEvtHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/presel/evt", hadTauSelection_part1.data()), central_or_shift));
  preselEvtHistManager.bookHistograms(fs);

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/hadTaus", hadTauSelection_part1.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_lead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/leadHadTau", hadTauSelection_part1.data()), central_or_shift, 0));
  selHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/subleadHadTau", hadTauSelection_part1.data()), central_or_shift, 1));
  selHadTauHistManager_sublead.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_third(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/thirdHadTau", hadTauSelection_part1.data()), central_or_shift, 1));
  selHadTauHistManager_third.bookHistograms(fs);
  vstring categories_tau = {
    "0l_3tau_bloose", "0l_3tau_btight"
  };
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_lead_category; // key = category
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_sublead_category; // key = category
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_third_category; // key = category
  for ( vstring::const_iterator category = categories_tau.begin();
	category != categories_tau.end(); ++category ) {
    HadTauHistManager* selHadTauHistManager_lead = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/leadHadTau", category->data(), hadTauSelection_part1.data()), central_or_shift));
    selHadTauHistManager_lead->bookHistograms(fs);
    selHadTauHistManager_lead_category[*category] = selHadTauHistManager_lead;
    HadTauHistManager* selHadTauHistManager_sublead = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/subleadHadTau", category->data(), hadTauSelection_part1.data()), central_or_shift));
    selHadTauHistManager_sublead->bookHistograms(fs);
    selHadTauHistManager_sublead_category[*category] = selHadTauHistManager_sublead;
    HadTauHistManager* selHadTauHistManager_third = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/thirdHadTau", category->data(), hadTauSelection_part1.data()), central_or_shift));
    selHadTauHistManager_third->bookHistograms(fs);
    selHadTauHistManager_third_category[*category] = selHadTauHistManager_third;
  }
  edm::ParameterSet cfg_selHadTauFakeRateHistManager = makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/hadTauFakeRates", hadTauSelection_part1.data()), central_or_shift);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_lead", hadTauEtaBins_lead);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_sublead", hadTauEtaBins_sublead);
  HadTauFakeRateHistManager selHadTauFakeRateHistManager(cfg_selHadTauFakeRateHistManager);
  selHadTauFakeRateHistManager.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/jets", hadTauSelection_part1.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/leadJet", hadTauSelection_part1.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/subleadJet", hadTauSelection_part1.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/BJets_loose", hadTauSelection_part1.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/leadBJet_loose", hadTauSelection_part1.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/subleadBJet_loose", hadTauSelection_part1.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/BJets_medium", hadTauSelection_part1.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/met", hadTauSelection_part1.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  EvtHistManager_0l_3tau selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("0l_3tau_%s/sel/evt", hadTauSelection_part1.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  std::map<std::string, EvtHistManager_0l_3tau*> selEvtHistManager_decayMode; // key = decay mode
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
      EvtHistManager_0l_3tau* selEvtHistManager_ptr = new EvtHistManager_0l_3tau(makeHistManager_cfg(decayMode->data(),
        Form("0l_3tau_%s/sel/evt", hadTauSelection_part1.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManager_decayMode[*decayMode] = selEvtHistManager_ptr;
    }
  }
  std::map<int, EvtHistManager_0l_3tau*> selEvtHistManagers_genMatch; // key = { kGen_3t0e0m0j, kGen_2t1e0m0j, kGen_2t_0e1m0j, kGen_2t_0e0m1j,... }
  if ( isMC && !apply_hadTauGenMatching ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
	hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {
      if ( hadTauGenMatch_definition->idx_ == kGen_All3 || hadTauGenMatch_definition->idx_ == kGen_Undefined3 ) continue;
      std::string process_and_genMatch = process_string + hadTauGenMatch_definition->name_;
      EvtHistManager_0l_3tau* selEvtHistManager_ptr = new EvtHistManager_0l_3tau(makeHistManager_cfg(process_and_genMatch, 
        Form("0l_3tau_%s/sel/evt", hadTauSelection_part1.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManagers_genMatch[hadTauGenMatch_definition->idx_] = selEvtHistManager_ptr;
    }
  }
  vstring categories_evt = { 
    "0l_3tau_bloose", "0l_3tau_btight"
  };
  std::map<std::string, EvtHistManager_0l_3tau*> selEvtHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_evt.begin();
	category != categories_evt.end(); ++category ) {
    EvtHistManager_0l_3tau* selEvtHistManager = new EvtHistManager_0l_3tau(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/evt", category->data(), hadTauSelection_part1.data()), central_or_shift));
    selEvtHistManager->bookHistograms(fs);
    selEvtHistManager_category[*category] = selEvtHistManager;
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("0l_3tau_%s/unbiased/genEvt", hadTauSelection_part1.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("0l_3tau_%s/sel/genEvt", hadTauSelection_part1.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("0l_3tau_%s/sel/lheInfo", hadTauSelection_part1.data()), central_or_shift));
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

    if ( apply_trigger_bits ) {
      //bool isTriggered = hltPaths_isTriggered(triggers);
      //if ( !isTriggered ) continue;
      cutFlowTable.update("trigger");
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(muon_ptrs);
    
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(electron_ptrs);
    
    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(hadTau_ptrs);
    std::vector<const RecoHadTau*> fakeableHadTaus_lead = fakeableHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTausToClean;
    if ( fakeableHadTaus_lead.size() >= 1 ) fakeableHadTausToClean.push_back(fakeableHadTaus_lead[0]);
    std::vector<const RecoHadTau*> fakeableHadTaus_sublead = hadTauCleaner(fakeableHadTauSelector_sublead(preselHadTaus), fakeableHadTausToClean);
    if ( fakeableHadTaus_sublead.size() >= 1 ) fakeableHadTausToClean.push_back(fakeableHadTaus_sublead[0]);
    std::vector<const RecoHadTau*> fakeableHadTaus_third = hadTauCleaner(fakeableHadTauSelector_third(preselHadTaus), fakeableHadTausToClean);
    std::vector<const RecoHadTau*> fakeableHadTaus;
    if ( fakeableHadTaus_lead.size()    >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_lead[0]);
    if ( fakeableHadTaus_sublead.size() >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_sublead[0]);
    if ( fakeableHadTaus_third.size()   >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_third[0]);
    std::vector<const RecoHadTau*> tightHadTaus_lead = tightHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTausToClean;
    if ( tightHadTaus_lead.size() >= 1 ) tightHadTausToClean.push_back(tightHadTaus_lead[0]);
    std::vector<const RecoHadTau*> tightHadTaus_sublead = hadTauCleaner(tightHadTauSelector_sublead(preselHadTaus), tightHadTausToClean);
    if ( tightHadTaus_sublead.size() >= 1 ) tightHadTausToClean.push_back(tightHadTaus_sublead[0]);
    std::vector<const RecoHadTau*> tightHadTaus_third = hadTauCleaner(tightHadTauSelector_third(preselHadTaus), tightHadTausToClean);
    std::vector<const RecoHadTau*> tightHadTaus;
    if ( tightHadTaus_lead.size()    >= 1 ) tightHadTaus.push_back(tightHadTaus_lead[0]);
    if ( tightHadTaus_sublead.size() >= 1 ) tightHadTaus.push_back(tightHadTaus_sublead[0]);
    if ( tightHadTaus_third.size()   >= 1 ) tightHadTaus.push_back(tightHadTaus_third[0]);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selHadTaus);
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
    // require exactly zero lepton passing loose preselection criteria
    if ( !(preselLeptons.size() == 0) ) continue;
    cutFlowTable.update("0 presel leptons");

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    std::sort(preselHadTaus.begin(), preselHadTaus.end(), isHigherPt);
    if ( !(preselHadTaus.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 presel taus");
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    const RecoHadTau* preselHadTau_third = preselHadTaus[2];
    int preselHadTau_chargeSum = preselHadTau_lead->charge_ + preselHadTau_sublead->charge_ + preselHadTau_third->charge_;
    const RecoHadTau* preselHadTau1_SS = 0;
    const RecoHadTau* preselHadTau2_SS = 0;
    const RecoHadTau* preselHadTau_OS  = 0;
    for ( int idxPreselHadTau = 0; idxPreselHadTau < 3; ++idxPreselHadTau ) {
      const RecoHadTau* preselHadTau = preselHadTaus[idxPreselHadTau];
      if ( preselHadTau->charge_*preselHadTau_chargeSum > 0 ) {
	if      ( !preselHadTau1_SS ) preselHadTau1_SS = preselHadTau;
	else if ( !preselHadTau2_SS ) preselHadTau2_SS = preselHadTau;
      } else {
	if ( !preselHadTau_OS ) preselHadTau_OS = preselHadTau;
      }
    }
    double mTauTauVis1_presel = ( preselHadTau1_SS && preselHadTau_OS ) ? (preselHadTau1_SS->p4_ + preselHadTau_OS->p4_).mass() : -1.;
    double mTauTauVis2_presel = ( preselHadTau2_SS && preselHadTau_OS ) ? (preselHadTau2_SS->p4_ + preselHadTau_OS->p4_).mass() : -1.;

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

//--- fill histograms with events passing preselection
    preselHadTauHistManager.fillHistograms(preselHadTaus, evtWeight);
    preselHadTauHistManager_lead.fillHistograms({ preselHadTau_lead }, evtWeight);
    preselHadTauHistManager_sublead.fillHistograms({ preselHadTau_sublead }, evtWeight);
    preselHadTauHistManager_third.fillHistograms({ preselHadTau_third }, evtWeight);
    preselJetHistManager.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    preselMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    preselEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mTauTauVis1_presel, mTauTauVis2_presel, evtWeight);

//--- apply final event selection 
    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const RecoHadTau* selHadTau_third = selHadTaus[2];

    const hadTauGenMatchEntry& hadTauGenMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead, selHadTau_third);
    assert(!(hadTauGenMatch.idx_ == kGen_Undefined3 || hadTauGenMatch.idx_ == kGen_All3));

    if ( hadTauGenMatchSelection != kGen_All3 ) {
      if ( hadTauGenMatch.idx_ != hadTauGenMatchSelection ) continue;
      cutFlowTable.update("tau gen match", evtWeight);
    }
        
    int selHadTau_chargeSum = selHadTau_lead->charge_ + selHadTau_sublead->charge_ + selHadTau_third->charge_;
    const RecoHadTau* selHadTau1_SS = 0;
    const RecoHadTau* selHadTau2_SS = 0;
    const RecoHadTau* selHadTau_OS  = 0;
    for ( int idxSelHadTau = 0; idxSelHadTau < 3; ++idxSelHadTau ) {
      const RecoHadTau* selHadTau = selHadTaus[idxSelHadTau];
      if ( selHadTau->charge_*selHadTau_chargeSum > 0 ) {
	if      ( !selHadTau1_SS ) selHadTau1_SS = selHadTau;
	else if ( !selHadTau2_SS ) selHadTau2_SS = selHadTau;
      } else {
	if ( !selHadTau_OS ) selHadTau_OS = selHadTau;
      }
    }
    double mTauTauVis1 = ( selHadTau1_SS && selHadTau_OS ) ? (selHadTau1_SS->p4_ + selHadTau_OS->p4_).mass() : -1.;
    double mTauTauVis2 = ( selHadTau2_SS && selHadTau_OS ) ? (selHadTau2_SS->p4_ + selHadTau_OS->p4_).mass() : -1.;
    
    if ( isMC ) {
//--- weight simulated events by efficiency to pass HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg trigger
//   (triggers not simulated in Spring16 MC samples)
      evtWeight *= effHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg(
        selHadTau_lead->pt_, selHadTau_lead->eta_, 
	selHadTau_sublead->pt_, selHadTau_sublead->eta_);

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
      int selHadTau_third_genPdgId = getHadTau_genPdgId(selHadTau_third);
      dataToMCcorrectionInterface->setHadTaus(
	selHadTau_lead_genPdgId, selHadTau_lead->pt_, selHadTau_lead->eta_,
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt_, selHadTau_sublead->eta_,
	selHadTau_third_genPdgId, selHadTau_third->pt_, selHadTau_third->eta_);
      evtWeight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      evtWeight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      evtWeight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();  
    }   
   
    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 4) ) continue;
    cutFlowTable.update(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
 
    if ( !(std::abs(selHadTau_chargeSum) == 1) ) continue;
    cutFlowTable.update("sel tau charge", evtWeight);

    if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus.size() >= 3 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
    }

    if ( applyJetToTauFakeRateWeight ) {
      assert(jetToTauFakeRateInterface);
      
      double prob_fake_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt_, selHadTau_lead->absEta_);
      double prob_fake_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt_, selHadTau_sublead->absEta_);
      double prob_fake_third = jetToTauFakeRateInterface->getWeight_third(selHadTau_third->pt_, selHadTau_third->absEta_);
      
      bool passesTight_lead = isMatched(*selHadTau_lead, tightHadTaus);
      bool passesTight_sublead = isMatched(*selHadTau_sublead, tightHadTaus);
      bool passesTight_third = isMatched(*selHadTau_third, tightHadTaus);

      double p1 = prob_fake_lead/(1. - prob_fake_lead);
      double p2 = prob_fake_sublead/(1. - prob_fake_sublead);
      double p3 = prob_fake_third/(1. - prob_fake_third);
      double evtWeight_tight_to_loose = 0.;
      if      ( !passesTight_lead &&  passesTight_sublead &&  passesTight_third ) evtWeight_tight_to_loose =  p1;
      else if (  passesTight_lead && !passesTight_sublead &&  passesTight_third ) evtWeight_tight_to_loose =  p2;
      else if (  passesTight_lead &&  passesTight_sublead && !passesTight_third ) evtWeight_tight_to_loose =  p3;
      else if ( !passesTight_lead && !passesTight_sublead &&  passesTight_third ) evtWeight_tight_to_loose = -p1*p2;
      else if ( !passesTight_lead &&  passesTight_sublead && !passesTight_third ) evtWeight_tight_to_loose = -p1*p3;
      else if (  passesTight_lead && !passesTight_sublead && !passesTight_third ) evtWeight_tight_to_loose = -p2*p3;
      else if ( !passesTight_lead && !passesTight_sublead && !passesTight_third ) evtWeight_tight_to_loose =  p1*p2*p3;
      evtWeight *= evtWeight_tight_to_loose;
    }
    
//--- fill histograms with events passing final selection 
    selHadTauHistManager_lead.fillHistograms({ selHadTau_lead }, evtWeight);
    selHadTauHistManager_sublead.fillHistograms({ selHadTau_sublead }, evtWeight);
    selHadTauHistManager_third.fillHistograms({ selHadTau_third }, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    selHadTauFakeRateHistManager.fillHistograms(selHadTau_lead, selHadTau_sublead, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mTauTauVis1, mTauTauVis2, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selEvtHistManager_decayMode[kv.first]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	    mTauTauVis1, mTauTauVis2, evtWeight);
          break;
        }
      }
    }
    if ( isMC && !apply_hadTauGenMatching ) {
      EvtHistManager_0l_3tau* selEvtHistManager_genMatch = selEvtHistManagers_genMatch[hadTauGenMatch.idx_];
      assert(selEvtHistManager_genMatch);
      selEvtHistManager_genMatch->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	mTauTauVis1, mTauTauVis2, evtWeight);
    }

    int category = -1;
    if ( selBJets_medium.size() >= 1 ) category = k0l_btight;
    else category = k0l_bloose;

    if ( category == k0l_btight ) {
      selHadTauHistManager_lead_category["0l_3tau_btight"]->fillHistograms({ selHadTau_lead }, evtWeight);
      selHadTauHistManager_sublead_category["0l_3tau_btight"]->fillHistograms({ selHadTau_sublead }, evtWeight);
      selHadTauHistManager_third_category["0l_3tau_btight"]->fillHistograms({ selHadTau_third }, evtWeight);
      selEvtHistManager_category["0l_3tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mTauTauVis1, mTauTauVis2, evtWeight);
    } else if ( category == k0l_bloose ) {
      selHadTauHistManager_lead_category["0l_3tau_bloose"]->fillHistograms({ selHadTau_lead }, evtWeight);
      selHadTauHistManager_sublead_category["0l_3tau_bloose"]->fillHistograms({ selHadTau_sublead }, evtWeight);
      selHadTauHistManager_third_category["0l_3tau_bloose"]->fillHistograms({ selHadTau_third }, evtWeight);
      selEvtHistManager_category["0l_3tau_bloose"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mTauTauVis1, mTauTauVis2, evtWeight);
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

  //hltPaths_delete(triggers);

  clock.Show("analyze_0l_3tau");

  return EXIT_SUCCESS;
}

