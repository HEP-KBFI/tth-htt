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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // comp_mindr_lep*_jet(), comp_lep*_conePt(), comp_*()
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // LUMI_*, EVT_*, RUN_*, MET_*_*
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorCutBased.h" // RecoMuonCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtag*
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_*
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager

#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h

#include <iostream> // std::cout

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton, kFR_3L };

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_SUCCESS;
  }
  std::cout << "<" << argv[0] << ">:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("syncNtuple");

  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string outputTreeName = cfg_analyze.getParameter<std::string>("outputTreeName");
  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const bool debug = cfg_analyze.getParameter<bool>("debug");

//--- declare data-taking period
  const int era = [&era_string, &argv]() -> int
  {
    if     (era_string == "2015") return kEra_2015;
    else if(era_string == "2016") return kEra_2016;
    else
      throw cms::Exception(argv[0])
        << "Invalid configuration parameter 'era' = " << era_string << '\n';
  }();
  
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("sync_ntuples") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  const int jetPt_option = RecoJetReader::kJetPt_central;

  const vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  const std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  const vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  const std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  const vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  const std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  const vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  const std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  const vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  const std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);

  const std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_input = "  << selEventsFileName_input  << '\n'
            << "selEventsFileName_output = " << selEventsFileName_output << '\n';

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  /*int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"                                                     ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" || hadTauSelection_part1 == "Fakeable_mcClosure" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"                                                     ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_2lss_1tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";*/
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  
  
  

  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << '\n';
  const unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  const std::string outputFileName = outputFile.file();

  TChain* inputTree = new TChain(treeName.data());
  for(const std::string & inputFileName: inputFiles.files())
  {
    std::cout << "input Tree: adding file = " << inputFileName << '\n';
    inputTree -> AddFile(inputFileName.c_str());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception(argv[0]) << "Failed to identify input Tree !!\n";
  }
  
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);

  std::cout << "input Tree contains " << inputTree->GetEntries() << " Entries in "
            << inputTree->GetListOfFiles()->GetEntries() << " files.\n";

//--- declare event-level variables
  RUN_TYPE run;
  inputTree->SetBranchAddress(RUN_KEY, &run);
  LUMI_TYPE lumi;
  inputTree->SetBranchAddress(LUMI_KEY, &lumi);
  EVT_TYPE event;
  inputTree->SetBranchAddress(EVT_KEY, &event);

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_2e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_2mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

  MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorCutBased cutBasedSelector(era); // KE: not needed in 2016 sync, but keep it
  RecoMuonCollectionSelectorMVABased mvaBasedSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, run_lumi_eventSelector != 0);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionCleaner electronCleaner(0.05); // NB! in analysis we have 0.3
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, debug);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorCutBased cutBasedElectronSelector(era); // KE: not needed in 2016 sync, but keep it
  RecoElectronCollectionSelectorMVABased mvaBasedElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, run_lumi_eventSelector != 0);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionCleaner hadTauCleaner(0.4); // NB! in analysis we have 0.3
  RecoHadTauCollectionSelectorLoose hadTauSelector(era); // KE: Tight -> Loose
  hadTauSelector.set("dR03mvaLoose");


  /*hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);*/
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);


  std::string jet_btagWeight_branch;
  bool isMC = true; //cfg_analyze.getParameter<bool>("isMC");
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }
  //std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  std::string central_or_shift = "central";
  
  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);
  
  int applyFakeRateWeights = kFR_3L;
  
  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }
  
  int jetToTauFakeRate_option = kFRjt_central;
  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3L ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }
  
  
  
  PUWEIGHT_TYPE pileupWeight;
  GENWEIGHT_TYPE genWeight = 1.;
  
  if ( isMC ) {
    inputTree->SetBranchAddress(GENWEIGHT_KEY, &genWeight);
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }

  RecoJetReader* jetReader = new RecoJetReader(era, "nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionCleaner jetCleaner(0.4); // NB! in analysis we *had* 0.5
  RecoJetCollectionSelector jetSelector(era);  

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis
  const std::string mvaFileName_2lss_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_ttV_BDTG.weights.xml";
  const std::vector<std::string> mvaInputVariables_2lss_ttV =
  {
    "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",
    "MT_met_lep1",
    "nJet25_Recl",
    "mindr_lep1_jet",
    "mindr_lep2_jet",
    "LepGood_conePt[iF_Recl[0]]",
    "LepGood_conePt[iF_Recl[1]]"
  };
  const TMVAInterface mva_2lss_ttV(
    mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" }
  );

  const std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  const std::vector<std::string> mvaInputVariables_2lss_ttbar =
  {
    "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",
    "nJet25_Recl",
    "mindr_lep1_jet",
    "mindr_lep2_jet",
    "min(met_pt,400)",
    "avg_dr_jet",
    "MT_met_lep1"
  };
  const TMVAInterface mva_2lss_ttbar(
    mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" }
  );

  std::map<std::string, double> mvaInputs;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

  SyncNtupleManager snm(outputFileName, outputTreeName);
  snm.initializeBranches();
  snm.initializeHLTBranches({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});

  const int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;

  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;    
    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    snm.readRunLumiEvent(run, lumi, event);

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
// CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> cutBasedMuons = cutBasedSelector(preselMuons);
    std::vector<const RecoMuon*> mvaBasedMuons = mvaBasedSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons = preselMuons;
    std::sort(preselMuons.begin(), preselMuons.end(), isHigherPt);
    snm.read(preselMuons, fakeableMuons, cutBasedMuons, mvaBasedMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> cutBasedElectrons = cutBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> mvaBasedElectrons = mvaBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons = preselElectrons;
    std::sort(preselElectrons.begin(), preselElectrons.end(), isHigherPt);
    snm.read(preselElectrons, fakeableElectrons, cutBasedElectrons, mvaBasedElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::sort(selHadTaus.begin(), selHadTaus.end(), isHigherPt);
    snm.read(selHadTaus);
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = [&]()
    {
      if     (era == kEra_2015)
        return jetCleaner(jet_ptrs, selMuons, selElectrons, selHadTaus);
      else if(era == kEra_2016)
        return jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
      else
        throw cms::Exception(argv[0]) << "Invalid era = " << era;
    }();
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::sort(selJets.begin(), selJets.end(), isHigherPt);
    snm.read(selJets);

//--- collect preselected leptons
    std::vector<const RecoLepton *> preselLeptons;
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);

//--- collect fakeable leptons
    std::vector<const RecoLepton *> fakeableLeptons;
    fakeableLeptons.reserve(fakeableElectrons.size() + fakeableMuons.size());
    fakeableLeptons.insert(fakeableLeptons.end(), fakeableElectrons.begin(), fakeableElectrons.end());
    fakeableLeptons.insert(fakeableLeptons.end(), fakeableMuons.begin(),     fakeableMuons.end());
    std::sort(fakeableLeptons.begin(), fakeableLeptons.end(), isHigherPt);
    
    const RecoLepton * const lepton_lead = [&]()
    {
      if(era == kEra_2015 && preselLeptons.size() > 0)
        return preselLeptons[0];
      if(era == kEra_2016 && fakeableLeptons.size() > 0)
        return fakeableLeptons[0];
      return static_cast<const RecoLepton * const>(0);
    }();
    const RecoLepton * const lepton_sublead = [&]()
    {
      if(era == kEra_2015 && preselLeptons.size() > 1)
        return preselLeptons[1];
      if(era == kEra_2016 && fakeableLeptons.size() > 1)
        return fakeableLeptons[1];
      return static_cast<const RecoLepton * const>(0);
    }();
    
    int lepton_lead_type = -1;
    double lepton_lead_pt = 0.;
    double lepton_lead_eta = 0.; 
        
    if(lepton_lead != 0){
      lepton_lead_type = getLeptonType(lepton_lead->pdgId());
      lepton_lead_pt = lepton_lead->pt();;
      lepton_lead_eta = lepton_lead->eta(); 
    }
    
    int lepton_sublead_type = -1;
    double lepton_sublead_pt = 0.;
    double lepton_sublead_eta = 0.; 
    
    if (lepton_sublead != 0){
      lepton_sublead_type = getLeptonType(lepton_sublead->pdgId());
      lepton_sublead_pt = lepton_sublead->pt();
      lepton_sublead_eta = lepton_sublead->eta();
    }

    dataToMCcorrectionInterface->setLeptons(
	      lepton_lead_type, lepton_lead_pt, lepton_lead_eta, 
    	  lepton_sublead_type, lepton_sublead_pt, lepton_sublead_eta
    );
    
    double weight_btag = 1.;
    if( isMC){
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	          jet != selJets.end(); ++jet ) {
	      weight_btag *= (*jet)->BtagWeight();
      }
    }
//--- compute MHT and linear MET discriminant (met_LD)
    LV mht_p4(0,0,0,0);
    for(const RecoJet * & jet: selJets)             mht_p4 += jet -> p4();
    for(const RecoLepton * & lepton: preselLeptons) mht_p4 += lepton -> p4();
    for(const RecoHadTau * & hadTau: selHadTaus)    mht_p4 += hadTau -> p4();
    const LV met_p4(met_pt, met_eta, met_phi, 0.);
    const Double_t met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();

    snm.read(met_pt,      FloatVariableType::PFMET);
    snm.read(met_phi,     FloatVariableType::PFMETphi);
    snm.read(mht_p4.pt(), FloatVariableType::MHT);
    snm.read(met_LD,      FloatVariableType::metLD);
    snm.read({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});
//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    if(lepton_lead)
    {
      mvaInputs["MT_met_lep1"]                = comp_MT_met_lep1(*lepton_lead, met_pt, met_phi);
      mvaInputs["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*lepton_lead);
      mvaInputs["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*lepton_lead, selJets);
    }
    if(lepton_sublead)
    {
      mvaInputs["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*lepton_sublead);
      mvaInputs["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*lepton_sublead, selJets);
    }
    mvaInputs["nJet25_Recl"]     = comp_n_jet25_recl(selJets);
    mvaInputs["avg_dr_jet"]      = comp_avg_dr_jet(selJets);
    mvaInputs["min(met_pt,400)"] = std::min(met_pt, static_cast<Float_t>(400.));

    if(lepton_lead && lepton_sublead)
    {
      mvaInputs["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] =
        std::max(std::fabs(lepton_lead->eta()), std::fabs(lepton_sublead->eta()));
      if(selJets.size() > 1)
      {
        snm.read(mva_2lss_ttV(mvaInputs),   FloatVariableType::mvaOutput_ttV);
        snm.read(mva_2lss_ttbar(mvaInputs), FloatVariableType::mvaOutput_ttbar);
      }
    }
    snm.read(mvaInputs);
    mvaInputs.clear();
    
    //selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch][idxSelHadTau_genMatch];
    //assert(selHistManager != 0);
    
    /*double evtWeight_pp = evtWeight;
    double evtWeight_mm = evtWeight;
    if ( leptonChargeSelection == kOS ) {
      double prob_chargeMisId_lead = prob_chargeMisId(getLeptonType(preselLepton_lead->pdgId()), preselLepton_lead->pt(), preselLepton_lead->eta());
      double prob_chargeMisId_sublead = prob_chargeMisId(getLeptonType(preselLepton_sublead->pdgId()), preselLepton_sublead->pt(), preselLepton_sublead->eta());

      evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);

      if ( preselLepton_lead->charge() < 0 && preselLepton_sublead->charge() > 0 ) {
	evtWeight_pp *= prob_chargeMisId_lead;
	evtWeight_mm *= prob_chargeMisId_sublead;
      }
      if ( preselLepton_lead->charge() > 0 && preselLepton_sublead->charge() < 0 ) {
	evtWeight_pp *= prob_chargeMisId_sublead;
	evtWeight_mm *= prob_chargeMisId_lead;
      }
    }*/
    
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    const RecoLepton* selLepton_lead = nullptr;
    const RecoLepton* selLepton_sublead = nullptr;
    if (selLeptons.size() > 0){
      selLepton_lead = selLeptons[0];
      if (selLeptons.size() > 1)
        selLepton_sublead = selLeptons[1];
    }
    double weight_fakeRate = 1.;
    if ( applyFakeRateWeights == kFR_3L and selLeptons.size() > 1) {
      double prob_fake_lepton_lead = 1.;
      if      ( std::abs(selLepton_lead->pdgId()) == 11 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->pt(), selLepton_lead->absEta());
      else if ( std::abs(selLepton_lead->pdgId()) == 13 ) prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->pt(), selLepton_lead->absEta());
      else if (selLeptons.size() == 0) prob_fake_lepton_lead = 1.;
      else assert(0);
      bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
      double prob_fake_lepton_sublead = 1.;
      
      if      ( std::abs(selLepton_sublead->pdgId()) == 11 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->pt(), selLepton_sublead->absEta());
      else if ( std::abs(selLepton_sublead->pdgId()) == 13 ) prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->pt(), selLepton_sublead->absEta());
      else if (selLeptons.size() == 1) prob_fake_lepton_sublead = 1.;
      else assert(0);
      
      bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
      if(selHadTaus.size() > 0){
        const RecoHadTau* selHadTau = selHadTaus[0];
        double prob_fake_hadTau = jetToTauFakeRateInterface->getWeight_lead(selHadTau->pt(), selHadTau->absEta());
        bool passesTight_hadTau = isMatched(*selHadTau, tightHadTaus);
        weight_fakeRate = getWeight_3L(
          prob_fake_lepton_lead, passesTight_lepton_lead, 
          prob_fake_lepton_sublead, passesTight_lepton_sublead, 
          prob_fake_hadTau, passesTight_hadTau);
      }
      
      /*evtWeight *= weight_fakeRate;
      evtWeight_pp *= weight_fakeRate;
      evtWeight_mm *= weight_fakeRate;*/
    } 

    double triggerSF_weight = dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
    double leptonSF_weight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();
    //--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
    //    to also pass the tight identification and isolation criteria
    if ( isMC ) {
      if ( leptonSelection == kFakeable ) {
	        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
          leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }
    }
    double hadTauSF_weight = dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
    //double MC_weight = pileupWeight * triggerSF_weight * leptonSF_weight * weight_btag * hadTauSF_weight * genWeight;

    snm.read(genWeight,   FloatVariableType::MC_weight);
    snm.read(weight_fakeRate,   FloatVariableType::FR_weight);
    snm.read(triggerSF_weight,   FloatVariableType::triggerSF_weight);
    snm.read(leptonSF_weight,   FloatVariableType::leptonSF_weight);
    snm.read(weight_btag,   FloatVariableType::bTagSF_weight);
    snm.read(pileupWeight,   FloatVariableType::PU_weight);
    snm.read(hadTauSF_weight,   FloatVariableType::hadTauSF_weight);
    //snm.read(genWeight,   FloatVariableType::genWeight);
    snm.fill();
    
    (*selEventsFile) << run << ':' << lumi << ':' << event << '\n';
    ++selectedEntries;    
  }
  snm.write();
  std::cout << "num. Entries = " << numEntries << "\n analyzed = " << analyzedEntries << '\n'
            << "Wrote file = " << outputFileName << '\n';

  delete run_lumi_eventSelector;
  delete selEventsFile;
  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
}
