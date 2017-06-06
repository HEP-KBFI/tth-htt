#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TEfficiency.h>
#include <TError.h> // gErrorAbortLevel, kError

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
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
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L

#include <iostream> // std::cerr, std::fixed
#include <cstring> // std::strncpm
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

enum { kFR_disabled, kFR_2lepton, kFR_3L, kFR_1tau };

const std::string hadTauSelection = "dR03mvaTight";
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Produce histograms for the charge flip background.
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
  std::cout << "<analyze_charge_flip>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_charge_flip");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_charge_flip")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_charge_flip");
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_charge_flip") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  //bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  //bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  //bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");
  
  enum { kLoose, kFakeable, kTight };
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection");
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("analyze_charge_flip")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::string central_or_shift_label = central_or_shift == "central" ? "" : "_"+central_or_shift;
  std::string central_or_shift_label_st = central_or_shift == "central" ? "" : central_or_shift+"_";
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");

  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;


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
  
  TString central_or_shift_tstring = central_or_shift.data();
  if ( isMC && central_or_shift != "central" ) {
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_charge_flip")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_thu_shape") ) {
      if      ( central_or_shift_tstring.EndsWith("x1Down") ) lheScale_option = kLHE_scale_xDown;
      else if ( central_or_shift_tstring.EndsWith("x1Up")   ) lheScale_option = kLHE_scale_xUp;
      else if ( central_or_shift_tstring.EndsWith("y1Down") ) lheScale_option = kLHE_scale_yDown;
      else if ( central_or_shift_tstring.EndsWith("y1Up")   ) lheScale_option = kLHE_scale_yUp;
      else assert(0);
    } else if (!central_or_shift_tstring.BeginsWith("CMS_ttHl_electronE")) throw cms::Exception("analyze_charge_flip")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
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

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

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

  TChain* inputTree = new TChain(treeName.data());
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }

  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("analyze_charge_flip")
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

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_2e);

  PUWEIGHT_TYPE pileupWeight;
  GENWEIGHT_TYPE genWeight = 1.;
  
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

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep", "nGenLepFromTau", "GenLepFromTau");
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
  std::string charge_and_leptonSelectionSS = Form("%s_%s", "SS", leptonSelection_string.data());
  std::string charge_and_leptonSelectionOS = Form("%s_%s", "OS", leptonSelection_string.data());
  ElectronHistManager preselElectronHistManagerSS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionSS.data()), central_or_shift.data()));
  preselElectronHistManagerSS.bookHistograms(fs);
  ElectronHistManager preselElectronHistManagerOS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionOS.data()), central_or_shift.data()));
  preselElectronHistManagerOS.bookHistograms(fs);

  vstring categories_etapt = {  //B-barrel, E-endcap, L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT > 50)
    "BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"
  };
  vstring categories_charge = {
    "SS", "OS"
  };
  std::map<std::string, std::map<std::string, std::map<std::string, TH1D*>>> histos;
  std::map<std::string, std::map<std::string, std::map<std::string, TH1D*>>> histos_2gen;
  std::map<std::string, std::map<std::string, std::map<std::string, TH1D*>>> histos_2gen_rec;
  
  for ( vstring::const_iterator which = categories_charge.begin(); 	which != categories_charge.end(); ++which ) {
    TFileDirectory subDir = fs.mkdir( which->data() );
    //TFileDirectory subDir2 = subDir.mkdir(process_string);
    TFileDirectory subD1 = fs.mkdir("gen");
    TFileDirectory subD = subD1.mkdir(which->data());

    TFileDirectory subD1r = fs.mkdir("gen_rec");
    TFileDirectory subDr = subD1r.mkdir(which->data());

    for ( vstring::const_iterator category = categories_etapt.begin(); 	category != categories_etapt.end(); ++category ) {
      TFileDirectory subDir1_5 = subDir.mkdir(category->data());
      TFileDirectory subDir2 = subDir1_5.mkdir(process_string.data());
      TFileDirectory subD2 = subD.mkdir(category->data());
      TFileDirectory subD2r = subDr.mkdir(category->data());
      
      histos[which->data()][*category][process_string] = subDir2.make<TH1D>( Form("%smass_ll", central_or_shift_label_st.data()), "m_{ll}", 60,  60., 120. );
      histos[which->data()][*category][process_string]->Sumw2();
      if (std::strncmp(process_string.data(), "DY", 2) == 0 && !central_or_shift_tstring.BeginsWith("CMS_ttHl_electronER")){
          TFileDirectory subDirFake = subDir1_5.mkdir("DY_fake");
          histos[which->data()][*category]["DY_fake"] = subDirFake.make<TH1D>( Form("%smass_ll", central_or_shift_label_st.data()) , "m_{ll}", 60,  60., 120. );
          histos[which->data()][*category]["DY_fake"]->Sumw2();
          if (central_or_shift == "central") {
            histos_2gen[which->data()][*category][process_string] = subD2.make<TH1D>( Form("%smass_ll", central_or_shift_label_st.data()), "m_{ll}", 60,  60., 120. );
            histos_2gen[which->data()][*category][process_string]->Sumw2();
            histos_2gen_rec[which->data()][*category][process_string] = subD2r.make<TH1D>( Form("%smass_ll", central_or_shift_label_st.data()), "m_{ll}", 60,  60., 120. );
            histos_2gen_rec[which->data()][*category][process_string]->Sumw2();
          }
      }      
    }
  }
  vstring categories_charge_gen = {
    "ID", "MisID"
  };

  TFileDirectory subDir_fails = fs.mkdir( Form("failed_cuts") );
  TH1I* fail_counter = subDir_fails.make<TH1I>( process_string.data(), "Rejected events", 11,  0, 11 );
  const char *rejcs[11] = {"Trigger", "Trig_2e1e", "2e", "0mu", "2e_trig", "2e_sel", "2e_sel_trig", "0mu_sel", "pT_el", "tight_charge", "m_ll"};
  for (int i=1;i<=11;i++) fail_counter->GetXaxis()->SetBinLabel(i,rejcs[i-1]); 


  vstring categories_etapt_gen = {  //B-barrel, E-endcap, L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT > 50)
    "BL", "BM", "BH", "EL", "EM", "EH"
  };

  Double_t bins_eta[3] = {0, 1.479, 2.5};
  Double_t bins_pt[4] = {10, 25, 50, 1000};

  TEfficiency* gen_eff;
  TEfficiency* gen_eff_rec;
  TH2D* transfer_matrix;
  TH2D* transfer_matrix_flip;
  TH2D* transfer_matrix_noflip;
  std::map<std::string, TH2D*> histos_gen;
  if (isMC && central_or_shift == "central"){
    TFileDirectory subD = fs.mkdir("gen_ratio");
    TFileDirectory subD2 = subD.mkdir( process_string );
    for ( vstring::const_iterator which = categories_charge_gen.begin(); 	which != categories_charge_gen.end(); ++which ) {
      //TFileDirectory subDir = fs.mkdir( which->data() );
      histos_gen[which->data()] = subD2.make<TH2D>( Form("pt_eta_%s", which->data()), "pt_eta", 3,  bins_pt, 2, bins_eta );
      histos_gen[which->data()]->Sumw2();
    }
    gen_eff = subD.make<TEfficiency>(Form("pt_eta_%s", process_string.data()),"pt_eta;pT;#eta;charge_misID", 3,  bins_pt, 2, bins_eta);
    gen_eff->SetUseWeightedEvents();
    gen_eff->SetStatisticOption(TEfficiency::kFNormal);
    gen_eff_rec = subD.make<TEfficiency>(Form("pt_eta_%s_rec", process_string.data()),"pt_eta;pT;#eta;charge_misID", 3,  bins_pt, 2, bins_eta);
    gen_eff_rec->SetUseWeightedEvents();
    gen_eff_rec->SetStatisticOption(TEfficiency::kFNormal);
    transfer_matrix = subD.make<TH2D>(Form("transfer_matrix"),"transfer_matrix", 6, 0, 6, 6, 0, 6);
    transfer_matrix_flip = subD.make<TH2D>(Form("transfer_matrix_flip"),"transfer_matrix_flip", 6, 0, 6, 6, 0, 6);
    transfer_matrix_noflip = subD.make<TH2D>(Form("transfer_matrix_noflip"),"transfer_matrix_noflip", 6, 0, 6, 6, 0, 6);
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/unbiased/genEvt", charge_and_leptonSelectionSS.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/genEvt", charge_and_leptonSelectionSS.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/lheInfo", charge_and_leptonSelectionSS.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    inputTree->GetEntry(idxEntry);
    
    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;

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
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e) || (isMC && !apply_trigger_bits);
    
    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    if ( !(selTrigger_1e || selTrigger_2e) ) {
        if ( run_lumi_eventSelector ) {
	        std::cout << "event FAILS trigger selection." << std::endl; 
	        std::cout << " (selTrigger_1e = " << isTriggered_1e 
			  << ", selTrigger_2e = " << isTriggered_2e << ")" << std::endl;
        }
        if (central_or_shift == "central") fail_counter->Fill("Trigger", 1);
        continue;
    }
    
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && isTriggered_2e ) {
	      if ( run_lumi_eventSelector ) {
	        std::cout << "event FAILS trigger selection." << std::endl; 
	        std::cout << " (selTrigger_1e = " << selTrigger_1e 
		          << ", isTriggered_2e = " << isTriggered_2e << ")" << std::endl;
	      }
        if (central_or_shift == "central") fail_counter->Fill("Trig_2e1e", 1);
	      continue; 
      }
  }

    if ( /*(selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)   ||
	       (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||*/
	       (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
	       /*(selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||*/
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
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);

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
    	int abs_pdgId = std::abs(genLepton->pdgId());
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
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    
    // require exactly two preselected electrons
    if ( !(preselElectrons.size() == 2) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS 2 presel Electrons selection" << std::endl; 
	      std::cout << " #preselElectrons = " << preselElectrons.size() 
		        << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("2e", 1);
      continue;
    }
    //const RecoLepton* preselLepton_lead = preselLeptons[0];
    //int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId());
    //const RecoLepton* preselLepton_sublead = preselLeptons[1];
    //int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId());
    
    // require exactly zero preselected muons
    if ( !(preselMuons.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS 0 presel Muons selection" << std::endl; 
	      std::cout << " (#preselMuons = " << preselMuons.size() 
           << ")" << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("0mu", 1);
      continue;
    }
    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	      std::cout << " (#preselElectrons = " << preselElectrons.size() 
		        << ", selTrigger_1e = " << selTrigger_1e 
		        << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("2e_trig", 1);
      continue;
    }

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
	evtWeight *= (*jet)->BtagWeight();
      }
    }    

//--- apply final event selection
    std::vector<const RecoLepton*> selLeptons;
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly two electrons passing selection criteria of final event selection
    if ( selElectrons.size() != 2 ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS selElectrons selection." << std::endl;
	      std::cout << " (#selElectrons = " << selElectrons.size() << ")" << std::endl;
	      for ( size_t idxSelElectron = 0; idxSelElectron < selElectrons.size(); ++idxSelElectron ) {
	        std::cout << "selElectron #" << idxSelElectron << ":" << std::endl;
	        std::cout << (*selElectrons[idxSelElectron]);
	      }
        for ( size_t idxPreSelElectron = 0; idxPreSelElectron < preselElectrons.size(); ++idxPreSelElectron ) {
	        std::cout << "preselElectron #" << idxPreSelElectron << ":" << std::endl;
	        std::cout << (*preselElectrons[idxPreSelElectron]);
	      }
      }
      if (central_or_shift == "central") fail_counter->Fill("2e_sel", 1);
      continue;
    }
    
    if ( selElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS trigger selection for given selElectron multiplicity." << std::endl; 
	      std::cout << " (#selElectrons = " << selElectrons.size() 
		        << ", selTrigger_1e = " << selTrigger_1e 
		        << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("2e_sel_trig", 1);
      continue;
    }

    if ( selMuons.size() != 0) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS selection for selMuon = 0." << std::endl; 
	      std::cout << " (#selMuons = " << selMuons.size() << ")" << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("0mu_sel", 1);
      continue;
    }

    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    // require that trigger paths match event category (with event category based on selLeptons);
    /*if ( selElectrons.size() == 2 &&                         !(selTrigger_1e  || selTrigger_2e)                       ) continue;
    if ( selElectrons.size() == 1 && selMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) continue;
    */

    // Determine event category
    std::string stEta;
    std::string stLeadPt;
    std::string stSubPt;

    Double_t etaL0 = std::fabs(selLepton_lead->eta());
    Double_t etaL1 = std::fabs(selLepton_sublead->eta());
    
    double pt0, pt1;
    //std::cout << "Before " << selLepton_lead->pt() << ", " << selLepton_sublead->pt() << "   " << central_or_shift << std::endl;
    pt0 = selLepton_lead->pt();
    pt1 = selLepton_sublead->pt();
    if (central_or_shift == "CMS_ttHl_electronESBarrelUp") {
      if (etaL0 < 1.479) pt0 *= 1.01;
      if (etaL1 < 1.479) pt1 *= 1.01;
    }
    else if (central_or_shift == "CMS_ttHl_electronESBarrelDown"){
      if (etaL0 < 1.479) pt0 *= 0.99;
      if (etaL1 < 1.479) pt1 *= 0.99;
    }
    else if (central_or_shift == "CMS_ttHl_electronESEndcapUp") {
      if (etaL0 >= 1.479) pt0 *= 1.025;
      if (etaL1 >= 1.479) pt1 *= 1.025;
    }
    else if (central_or_shift == "CMS_ttHl_electronESEndcapDown") {
      if (etaL0 >= 1.479) pt0 *= 0.975;
      if (etaL1 >= 1.479) pt1 *= 0.975;
    }
    //std::cout << "After: " << pt0 << ", " << pt1 << std::endl;
    
    if(pt1 > pt0){ //Lepton pt order changed due to systematic
      double temp = pt1;
      pt1 = pt0;
      pt0 = temp;
      temp = etaL1;
      etaL1 = etaL0;
      etaL0 = temp;
    }
    
    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(pt0 > minPt_lead && pt1 > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS lepton pT selection." << std::endl;
	      std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
		        << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      fail_counter->Fill("pT_el", 1);
      continue;
    }
    
    
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
    //cutFlowTable.update("tight lepton charge", evtWeight);
    fail_counter->Fill("tight_charge", 1);
    
      
    bool isCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;

    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());

    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(), 
	selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta());

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      /*if ( !apply_trigger_bits ) {
	evtWeight *= dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
      }*/

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria      
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      double weight_data_to_MC_correction_tight = 1.;
    
      if ( leptonSelection == kFakeable ) {
	      weight_data_to_MC_correction_tight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
        weight_data_to_MC_correction_tight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }
      evtWeight *= weight_data_to_MC_correction_tight;
    
    
    //--- apply data/MC corrections for hadronic tau identification efficiency 
    //    and for e->tau and mu->tau misidentification rates
      if ( selHadTaus.size() >= 1)  {
        const RecoHadTau* selHadTau = selHadTaus[0];
        int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);
        dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());
        evtWeight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
        evtWeight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
        evtWeight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      
      double weight_fakeRate = 1.;
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
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTaus);
        weight_fakeRate = getWeight_3L(
          prob_fake_lepton_lead, passesTight_lepton_lead, 
	  prob_fake_lepton_sublead, passesTight_lepton_sublead, 
	  prob_fake_hadTau, passesTight_hadTau);
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
        evtWeight *= weight_fakeRate;
      } else if ( applyFakeRateWeights == kFR_1tau) {
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        weight_fakeRate = prob_fake_hadTau;
        evtWeight *= weight_fakeRate;
      }

      // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
      if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight && !(selHadTau->genHadTau() || selHadTau->genLepton()) ) {
        double weight_data_to_MC_correction_tau = jetToTauFakeRateInterface->getSF_lead(selHadTau->pt(), selHadTau->absEta());
        evtWeight *= weight_data_to_MC_correction_tau;
      }
    }    
  }

//--- fill histograms with events passing final selection
//--- Calclulate mass of lepton system
    math::PtEtaPhiMLorentzVector p4 =
      math::PtEtaPhiMLorentzVector(pt0, preselElectrons[0]->eta(), preselElectrons[0]->phi(), preselElectrons[0]->mass()) +
      math::PtEtaPhiMLorentzVector(pt1, preselElectrons[1]->eta(), preselElectrons[1]->phi(), preselElectrons[1]->mass());
    Double_t mass_ll = p4.M();
    //Adjust central value
    mass_ll *= 1.02;
    if (mass_ll < 60 || mass_ll > 120) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS dilepton mass selection." << std::endl;
	      std::cout << " (dilepton mass = " << mass_ll << ")" << std::endl;
      }
      if (central_or_shift == "central") fail_counter->Fill("m_ll", 1);
      continue;
    }
    if (pt0 >= 10 && pt0 < 25) stLeadPt = "L";
    else if (pt0 >= 25 && pt0 < 50) stLeadPt = "M";
    else if (pt0 > 50) stLeadPt = "H";
    if (pt1 >= 10 && pt1 < 25) stSubPt = "L";
    else if (pt1 >= 25 && pt1 < 50) stSubPt = "M";
    else if (pt1 > 50) stSubPt = "H";
    //else assert(0);

    if (etaL0 < 1.479 && etaL1 < 1.479) stEta = "BB";
    else if (etaL0 >= 1.479 && etaL1 >= 1.479) stEta = "EE";
    else if (etaL0 < etaL1) stEta = "BE";
    else
    {
      if (std::strncmp(stLeadPt.data(), stSubPt.data(), 1) == 0) stEta = "BE";       //Symmetric case
      else stEta = "EB";
    }
    //std::cout << stEta << " "<< stLeadPt  <<" " << stSubPt << " " << pt0 << " " << pt1 << " " << etaL0 << " " << etaL1 << std::endl;
  
    std::string category = Form("%s_%s%s", stEta.data(), stLeadPt.data(), stSubPt.data());

    std::string charge_cat = ( isCharge_SS ) ? "SS" : "OS";
    if (std::strncmp(process_string.data(), "DY", 2) == 0){    //Split DY
      const GenLepton *gp0 = preselElectrons[0]->genLepton();
      const GenLepton *gp1 = preselElectrons[1]->genLepton();
      //std::cout << gp0 << " " << gp1 << " " << abs(preselElectrons[0]->pdgId()) << " " << abs(gp0->pdgId()) << " " << abs(preselElectrons[1]->pdgId()) << " " << abs(gp1->pdgId()) << std::endl;
      if (gp0 != 0 && gp1 != 0 && abs(preselElectrons[0]->pdgId()) == abs(gp0->pdgId()) && abs(preselElectrons[1]->pdgId()) == abs(gp1->pdgId())) {
        math::PtEtaPhiMLorentzVector p4_gen =
            math::PtEtaPhiMLorentzVector(gp0->pt(), gp0->eta(), gp0->phi(), gp0->mass()) +
            math::PtEtaPhiMLorentzVector(gp1->pt(), gp1->eta(), gp1->phi(), gp1->mass());
        Double_t mass_ll_gen = p4_gen.M();
        
        //Adjust central value to better match data shape
        if (central_or_shift == "central" || central_or_shift == "")
          mass_ll = mass_ll + 0.25 * (mass_ll - mass_ll_gen);
        else if (central_or_shift == "CMS_ttHl_electronERDown")   
          mass_ll = mass_ll - 0.25 * (mass_ll - mass_ll_gen);
        else if (central_or_shift == "CMS_ttHl_electronERUp")
          mass_ll = mass_ll + 0.25 * (mass_ll - mass_ll_gen);
        //std::cout << "After:  " << mass_ll << std::endl;
        histos[charge_cat][category.data()]["DY"]->Fill(mass_ll, evtWeight);
        histos[charge_cat]["total"]["DY"]->Fill(mass_ll, evtWeight);
      }
      else if (!central_or_shift_tstring.BeginsWith("CMS_ttHl_electronER")){
        histos[charge_cat][category.data()]["DY_fake"]->Fill(mass_ll, evtWeight);
        histos[charge_cat]["total"]["DY_fake"]->Fill(mass_ll, evtWeight);        
      }
    }
    else {//Otherwise
      histos[charge_cat][category.data()][process_string]->Fill(mass_ll, evtWeight);
      histos[charge_cat]["total"][process_string]->Fill(mass_ll, evtWeight);
    }    

    if (isMC && central_or_shift == "central" && std::strncmp(process_string.data(), "DY", 2) == 0 &&
      preselElectrons[0]->genLepton() != 0 && preselElectrons[1]->genLepton() != 0)
    {
      for (int i = 0; i < 2; i++)
      {
        const GenLepton *gp = preselElectrons[i]->genLepton();
        #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        gen_eff->FillWeighted(preselElectrons[i]->charge() != gp->charge(), evtWeight, gp->pt(), std::fabs(gp->eta()));
        gen_eff_rec->FillWeighted(preselElectrons[i]->charge() != gp->charge(), evtWeight, preselElectrons[i]->pt(), std::fabs(preselElectrons[i]->eta()));
        
        int transfer_bin = 0, rec_bin = 0;
        if (std::fabs(gp->eta()) > 1.479) transfer_bin += 3;
        if (gp->pt() >= 15 && gp->pt() < 25) transfer_bin += 1;
        else if (gp->pt() >= 25 && gp->pt() < 50) transfer_bin += 2;
        else if (gp->pt() > 50) transfer_bin += 3;        
        else transfer_bin = 0;
        if (std::fabs(preselElectrons[i]->eta()) > 1.479) rec_bin += 3;
        if (preselElectrons[i]->pt() >= 15 && preselElectrons[i]->pt() < 25) rec_bin += 1;
        else if (preselElectrons[i]->pt() >= 25 && preselElectrons[i]->pt() < 50) rec_bin += 2;
        else if (preselElectrons[i]->pt() > 50) rec_bin += 3;
        else rec_bin = 0;
        transfer_matrix->Fill(transfer_bin, rec_bin, evtWeight);
        if (preselElectrons[i]->charge() != gp->charge())
          transfer_matrix_flip->Fill(transfer_bin, rec_bin, evtWeight);
        else
          transfer_matrix_noflip->Fill(transfer_bin, rec_bin, evtWeight);
        //if (preselElectrons[i]->charge() == gp->charge())
        //{
          histos_gen["ID"]->Fill(gp->pt(), std::fabs(gp->eta()), evtWeight);
        //}
        if (preselElectrons[i]->charge() != gp->charge())
        {
          histos_gen["MisID"]->Fill(gp->pt(), std::fabs(gp->eta()),evtWeight);
        }
        //else assert(0);
      }
      const GenLepton *gen0 = preselElectrons[0]->genLepton();
      const GenLepton *gen1 = preselElectrons[1]->genLepton();
      const GenLepton *gp0;
      const GenLepton *gp1;
      if (gen1->pt() > gen0->pt()){        
        gp0 = gen1;
        gp1 = gen0;
      }
      else {
        gp0 = gen0;
        gp1 = gen1;
      }
      std::string stEtaGen;
      std::string stLeadPtGen;
      std::string stSubPtGen;
      assert(gp0->pt() >= gp1->pt());
      if (gp0->pt() >= 10 && gp0->pt() < 25) stLeadPtGen = "L";
      else if (gp0->pt() >= 25 && gp0->pt() < 50) stLeadPtGen = "M";
      else if (gp0->pt() > 50) stLeadPtGen = "H";
      if (gp1->pt() >= 10 && gp1->pt() < 25) stSubPtGen = "L";
      else if (gp1->pt() >= 25 && gp1->pt() < 50) stSubPtGen = "M";
      else if (gp1->pt() > 50) stSubPtGen = "H";
      else{
        std::cout << "PT<10 " << gp0->pt() << " " << gp1->pt() << std::endl; 
        stSubPtGen = "L";
        //assert(0);
      }

      Double_t etaL0Gen = std::fabs(gp0->eta());
      Double_t etaL1Gen = std::fabs(gp1->eta());
      if (etaL0Gen < 1.479 && etaL1Gen < 1.479) stEtaGen = "BB";
      else if (etaL0Gen > 1.479 && etaL1Gen > 1.479) stEtaGen = "EE";
      else if (etaL0Gen < etaL1Gen) stEtaGen = "BE";
      else
      {
        if (std::strncmp(stLeadPtGen.data(), stSubPtGen.data(), 1) == 0) stEtaGen = "BE";       //Symmetric case
        else stEtaGen = "EB";
      }
      std::string categoryGen = Form("%s_%s%s", stEtaGen.data(), stLeadPtGen.data(), stSubPtGen.data());
      std::string charge_catGen = ( isCharge_SS ) ? "SS" : "OS";
      histos_2gen[charge_catGen][categoryGen.data()][process_string]->Fill(mass_ll, evtWeight);
      histos_2gen[charge_catGen]["total"][process_string]->Fill(mass_ll, evtWeight);
      histos_2gen_rec[charge_catGen][category.data()][process_string]->Fill(mass_ll, evtWeight);
      histos_2gen_rec[charge_catGen]["total"][process_string]->Fill(mass_ll, evtWeight);
    }
    if (isCharge_SS)
      preselElectronHistManagerSS.fillHistograms(preselElectrons, evtWeight);
    else if (isCharge_OS)
      preselElectronHistManagerOS.fillHistograms(preselElectrons, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;
    (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }


  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

  delete dataToMCcorrectionInterface;

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
  hltPaths_delete(triggers_2e);

  clock.Show("analyze_charge_flip");

  return EXIT_SUCCESS;
}
