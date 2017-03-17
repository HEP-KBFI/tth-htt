
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
#include <TBranch.h> // TBranch
#include <TLeaf.h> // TLeaf
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TMatrixD.h> // TMatrixD

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_3l_1tau.h" // CutFlowTableHistManager_3l_1tau
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h"

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

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
 
/**
 * @brief Produce Ntuple containing preselected events,
 *        drop branches not needed for ttH, H->tautau analysis,
 *        and add flag indicating for which events the MEM computation is to be run
 *       (the latter is necessary in order to split MEM computation into jobs that each perform ~50 MEM integrations)
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<produceNtuple_3l_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("produceNtuple_3l_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("produceNtuple_3l_1tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_produceNtuple = cfg.getParameter<edm::ParameterSet>("produceNtuple_3l_1tau");

  std::string treeName = cfg_produceNtuple.getParameter<std::string>("treeName");

  std::string era_string = cfg_produceNtuple.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("produceNtuple_3l_1tau") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  std::string leptonSelection_string = cfg_produceNtuple.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("produceNtuple_3l_1tau") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";
  int minNumLeptons = cfg_produceNtuple.getParameter<int>("minNumLeptons");

   TString hadTauSelection_string = cfg_produceNtuple.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"    ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"    ) hadTauSelection = kTight;
   else throw cms::Exception("produceNtuple_3l_1tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;
  int minNumHadTaus = cfg_produceNtuple.getParameter<int>("minNumHadTaus");

  int minNumJets = cfg_produceNtuple.getParameter<int>("minNumJets");

  bool use_HIP_mitigation_bTag = cfg_produceNtuple.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  int minNumBJets_loose = cfg_produceNtuple.getParameter<int>("minNumBJets_loose");
  int minNumBJets_medium = cfg_produceNtuple.getParameter<int>("minNumBJets_medium");
  
  bool isMC = cfg_produceNtuple.getParameter<bool>("isMC"); 

  std::string selEventsFileName_input = cfg_produceNtuple.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    run_lumi_eventSelector = makeRunLumiEventSelector(selEventsFileName_input);
  }

  std::string selEventsFileName_addMEM = cfg_produceNtuple.getParameter<std::string>("selEventsFileName_addMEM");
  std::cout << "selEventsFileName_addMEM = " << selEventsFileName_addMEM << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector_addMEM = 0;
  if ( selEventsFileName_addMEM != "" ) {
    run_lumi_eventSelector = makeRunLumiEventSelector(selEventsFileName_addMEM);
  }

  vstring outputCommands_string = cfg_produceNtuple.getParameter<vstring>("outputCommands");
  std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);

  vstring copy_histograms = cfg_produceNtuple.getParameter<vstring>("copy_histograms");

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
    throw cms::Exception("produceNtuple_3l_1tau") 
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

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  // CV: lower thresholds on hadronic taus by 2 GeV 
  //     with respect to thresholds applied on analysis level (in analyze_3l_1tau.cc)
  preselHadTauSelector.set_min_pt(18.); 
  fakeableHadTauSelector.set_min_pt(18.);
  tightHadTauSelector.set_min_pt(18.);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, "nJet", "Jet");
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  // CV: apply jet pT cut on JEC upward shift, to make sure pT cut is loose enough
  //     to allow systematic uncertainty on JEC to be estimated on analysis level 
  jetReader->setJetPt_central_or_shift(RecoJetReader::kJetPt_central); 
  jetReader->read_BtagWeight_systematics(isMC);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, "met");
  metReader->setBranchAddresses(inputTree);  

  std::string outputTreeName = treeName;
  std::string outputDirName = "";
  if ( outputTreeName.find_last_of("/") != std::string::npos ) {
    size_t pos = outputTreeName.find_last_of("/");
    outputTreeName = std::string(outputTreeName, pos + 1);
    outputDirName = std::string(outputTreeName, 0, pos);
  }
  if ( outputDirName != "" ) {
    TDirectory* dir = createSubdirectory_recursively(fs, outputDirName.data());
    dir->cd();
  } else {
    fs.cd();
  }
  TTree* outputTree = new TTree(outputTreeName.data(), outputTreeName.data());

  outputTree->Branch("run", &run, "run/i");
  outputTree->Branch("lumi", &lumi, "lumi/i");
  outputTree->Branch("evt", &event, "evt/l");

  std::string branchName_muons = "Muon";
  RecoMuonWriter* muonWriter = new RecoMuonWriter(era, Form("n%s", branchName_muons.data()), branchName_muons);
  muonWriter->setBranches(outputTree);
  std::cout << "writing RecoMuon objects to branch = '" << branchName_muons << "'" << std::endl;

  std::string branchName_electrons = "Electron";
  RecoElectronWriter* electronWriter = new RecoElectronWriter(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronWriter->setBranches(outputTree);
  std::cout << "writing RecoElectron objects to branch = '" << branchName_electrons << "'" << std::endl;

  std::string branchName_hadTaus = "HadTau";
  RecoHadTauWriter* hadTauWriter = new RecoHadTauWriter(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauWriter->setBranches(outputTree);
  std::cout << "writing RecoHadTau objects to branch = '" << branchName_hadTaus << "'" << std::endl;

  std::string branchName_jets = "Jet";
  RecoJetWriter* jetWriter = new RecoJetWriter(era, Form("n%s", branchName_jets.data()), branchName_jets);
  jetWriter->setBranches(outputTree);
  std::cout << "writing RecoJet objects to branch = '" << branchName_jets << "'" << std::endl;

  std::string branchName_met = "met";
  RecoMEtWriter* metWriter = new RecoMEtWriter(era, branchName_met);
  metWriter->setBranches(outputTree);
  std::cout << "writing RecoMEt object to branch = '" << branchName_met << "'" << std::endl;

  std::map<std::string, bool> isBranchToKeep = getBranchesToKeep(inputTree, outputCommands); // key = branchName
  std::map<std::string, branchEntryBaseType*> branchesToKeep; // key = branchName
  copyBranches_singleType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  copyBranches_vectorType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  
  std::cout << "keeping branches:" << std::endl;
  for ( std::map<std::string, branchEntryBaseType*>::const_iterator branchEntry = branchesToKeep.begin();
        branchEntry != branchesToKeep.end(); ++branchEntry ) {
    std::cout << " " << branchEntry->second->outputBranchName_ << " (type = " << branchEntry->second->outputBranchType_string_ << ")" << std::endl;
  }

  std::cout << "adding branches:" << std::endl;
  // CV: request MEM computation for this event 
  //    (value stored in 'maxPermutations_addMEM_3l_1tau' branch specifies maximum number of permutations for which the MEM computation is run;
  //     in case the actual number of permutations exceeds the value stored in the branch, addMEM_3l_1tau.cc will print a warning
  //     and skip the remaining permutations, in order not to exceed the computing time limits.)
  Int_t maxPermutations_addMEM_3l_1tau = 0;
  std::cout << " maxPermutations_addMEM_3l_1tau (type = I)" << std::endl;
  outputTree->Branch("maxPermutations_addMEM_3l_1tau", &maxPermutations_addMEM_3l_1tau, "maxPermutations_addMEM_3l_1tau/I");

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  cutFlowTableType cutFlowTable;
  //CutFlowTableHistManager_3l_1tau* cutFlowHistManager = new CutFlowTableHistManager_3l_1tau(makeHistManager_cfg("produceNtuple_3l_1tau",
  //  "cutFlow", "central"));
  //cutFlowHistManager->bookHistograms(fs);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {

    inputTree->GetEntry(idxEntry);

    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event
		<< " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    
    cutFlowTable.update("read from file");
    //cutFlowHistManager->fillHistograms("read from file");

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event << std::endl;
      if ( inputTree->GetFile() ) std::cout << "input File = " << inputTree->GetFile()->GetName() << std::endl;
    }

    bool passesAddMEM = run_lumi_eventSelector_addMEM && (*run_lumi_eventSelector_addMEM)(run, lumi, event);
    //std::cout << "passesAddMEM = " << passesAddMEM << std::endl;

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
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, fakeableMuons);
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
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons);
    std::vector<const RecoJet*> selJets;
    for ( std::vector<const RecoJet*>::const_iterator cleanedJet = cleanedJets.begin();
	  cleanedJet != cleanedJets.end(); ++cleanedJet ) {
      double cleanedJet_pt = (*cleanedJet)->pt();
      double cleanedJet_pt_JECUp = cleanedJet_pt*((*cleanedJet)->corr_JECUp()/(*cleanedJet)->corr());
      double cleanedJet_pt_JECDown = cleanedJet_pt*((*cleanedJet)->corr_JECDown()/(*cleanedJet)->corr());
      double cleanedJet_absEta = (*cleanedJet)->absEta();
      double min_pT = jetSelector.get_min_pt();
      double max_absEta = jetSelector.get_max_absEta();
      if ( (cleanedJet_pt >= min_pT || cleanedJet_pt_JECUp >= min_pT || cleanedJet_pt_JECDown >= min_pT ) && cleanedJet_absEta < max_absEta ) {
	selJets.push_back(*cleanedJet);
      }
    }
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

    RecoMEt met = metReader->read();

//--- apply preselection    
    std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons);
    if ( !((int)selLeptons.size() >= minNumLeptons) && !passesAddMEM ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selLeptons selection." << std::endl;
	std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons);
	std::cout << " (#preselLeptons = " << preselLeptons.size() << ")" << std::endl;
	for ( size_t idxPreselLepton = 0; idxPreselLepton < preselLeptons.size(); ++idxPreselLepton ) {
	  std::cout << "preselLepton #" << idxPreselLepton << ":" << std::endl;
	  std::cout << (*preselLeptons[idxPreselLepton]);
	}
	std::cout << " (#selLeptons = " << selLeptons.size() << ")" << std::endl;
	for ( size_t idxSelLepton = 0; idxSelLepton < selLeptons.size(); ++idxSelLepton ) {
	  std::cout << "selLepton #" << idxSelLepton << ":" << std::endl;
	  std::cout << (*selLeptons[idxSelLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i sel leptons", minNumLeptons));
    //cutFlowHistManager->fillHistograms(Form(">= %i sel leptons", minNumLeptons));

    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];
    // CV: lower thresholds on leading and subleading lepton by 2 GeV 
    //     with respect to thresholds applied on analysis level (in analyze_3l_1tau.cc)
    double minPt_lead = -1.;
    if      ( era == kEra_2015 ) minPt_lead = 18.; 
    else if ( era == kEra_2016 ) minPt_lead = 23.;
    else assert(0);
    double minPt_sublead = selLepton_sublead->is_electron() ? 13. : 8.;
    if ( !(selLepton_lead->pt() > minPt_lead && selLepton_sublead->pt() > minPt_sublead) && !passesAddMEM ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 23 GeV && sublead lepton pT > 13(e)/8(mu) GeV");
    //cutFlowHistManager->fillHistograms("lead lepton pT > 23 GeV && sublead lepton pT > 13(e)/8(mu) GeV");

    if ( !((int)selHadTaus.size() >= minNumHadTaus) && !passesAddMEM ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selHadTaus selection." << std::endl;
	std::cout << " (#selHadTaus = " << selHadTaus.size() << ")" << std::endl;
	std::cout << " (#preselHadTaus = " << preselHadTaus.size() << ")" << std::endl;
	for ( size_t idxPreselHadTau = 0; idxPreselHadTau < preselHadTaus.size(); ++idxPreselHadTau ) {
	  std::cout << "preselHadTau #" << idxPreselHadTau << ":" << std::endl;
	  std::cout << (*preselHadTaus[idxPreselHadTau]);
	}
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i sel hadTau", minNumHadTaus));
    //cutFlowHistManager->fillHistograms(Form(">= %i sel hadTau", minNumHadTaus));

    // apply requirement on jets 
    if ( !((int)selJets.size() >= minNumJets) && !passesAddMEM ) {
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
    cutFlowTable.update(Form(">= %i jets", minNumJets));
    //cutFlowHistManager->fillHistograms(Form(">= %i jets", minNumJets));
    if ( !((int)selBJets_loose.size() >= minNumBJets_loose || (int)selBJets_medium.size() >= minNumBJets_medium) && !passesAddMEM ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
	for ( size_t idxSelJet = 0; idxSelJet < selJets.size(); ++idxSelJet ) {
	  std::cout << "selJet #" << idxSelJet << ":" << std::endl;
	  std::cout << (*selJets[idxSelJet]);
	}
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ")" << std::endl;
	for ( size_t idxSelBJet_loose = 0; idxSelBJet_loose < selBJets_loose.size(); ++idxSelBJet_loose ) {
	  std::cout << "selBJet_loose #" << idxSelBJet_loose << ":" << std::endl;
	  std::cout << (*selBJets_loose[idxSelBJet_loose]);
	}
	std::cout << " (#selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
	for ( size_t idxSelBJet_medium = 0; idxSelBJet_medium < selBJets_medium.size(); ++idxSelBJet_medium ) {
	  std::cout << "selBJet_medium #" << idxSelBJet_medium << ":" << std::endl;
	  std::cout << (*selBJets_medium[idxSelBJet_medium]);
	}
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i loose b-jets || %i medium b-jet", minNumBJets_loose, minNumBJets_medium));
    //cutFlowHistManager->fillHistograms(Form(">= %i loose b-jets || %i medium b-jet", minNumBJets_loose, minNumBJets_medium));

//--- check if MEM needs to be computed for this event
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    bool failsZbosonMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = fakeableLeptons.begin();
	  lepton1 != fakeableLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != fakeableLeptons.end(); ++lepton2 ) {
	//std::cout << "lepton1: pT = " << (*lepton1)->pt() << ", eta = " << (*lepton1)->eta() << ", phi = " << (*lepton1)->phi() << ", pdgId = " << (*lepton1)->pdgId() << std::endl;
	//std::cout << "lepton2: pT = " << (*lepton2)->pt() << ", eta = " << (*lepton2)->eta() << ", phi = " << (*lepton2)->phi() << ", pdgId = " << (*lepton2)->pdgId() << std::endl;
	if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // pair of same flavor leptons of opposite charge
	  double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	  //std::cout << "mass = " << mass << std::endl;
	  if ( std::fabs(mass - z_mass) < z_window ) {
	    //std::cout << "--> setting failsZbosonMassVeto = true !!" << std::endl;
	    failsZbosonMassVeto = true;
	  }
	}
      }
    }
    //std::cout << "selBJets_loose.size() = " << selBJets_loose.size() << ", selBJets_medium.size() = " << selBJets_medium.size() << "," 
    //	        << " failsZbosonMassVeto = " << failsZbosonMassVeto << std::endl;
    bool passesPreselection = (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) && !failsZbosonMassVeto;
    if ( (passesPreselection || passesAddMEM) && selLeptons.size() >= 3 && selHadTaus.size() >= 1 ) {
      maxPermutations_addMEM_3l_1tau = TMath::Nint((1./6)*selLeptons.size()*(selLeptons.size() - 1)*(selLeptons.size() - 2)*selHadTaus.size());
    } else {
      maxPermutations_addMEM_3l_1tau = -1;
    }
    
    muonWriter->write(preselMuons);
    electronWriter->write(preselElectrons);
    hadTauWriter->write(preselHadTaus);
    jetWriter->write(jet_ptrs);
    metWriter->write(met);

    //std::cout << "copying branches:" << std::endl;
    for ( std::map<std::string, branchEntryBaseType*>::const_iterator branchEntry = branchesToKeep.begin();
          branchEntry != branchesToKeep.end(); ++branchEntry ) {
      //std::cout << branchEntry->second->outputBranchName_ << std::endl;
      branchEntry->second->copyBranch();
    }

    outputTree->Fill();

    ++selectedEntries;
  }
												
  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << std::endl;

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  std::cout << "output Tree:" << std::endl;
  outputTree->Print();
  //outputTree->Scan("*", "", "", 20, 0);

  delete run_lumi_eventSelector;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;

  delete muonWriter;
  delete electronWriter;
  delete hadTauWriter;
  delete jetWriter;
  delete metWriter;

//--- copy histograms keeping track of number of processed events from input files to output file
  std::cout << "copying histograms:" << std::endl;
  delete inputTree;
  std::map<std::string, TH1*> histograms;
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    TFile* inputFile = new TFile(inputFileName->data());
    if ( !inputFile ) 
      throw cms::Exception("produceNtuple_3l_1tau") 
	<< "Failed to open input File = '" << (*inputFileName) << "' !!\n";
    
    for ( vstring::const_iterator histogramName = copy_histograms.begin();
	  histogramName != copy_histograms.end(); ++histogramName ) {
      if ( inputFiles.files().size() > 1 ) {
	std::cout << " " << (*histogramName) << " from input File = '" << (*inputFileName) << "'" << std::endl;
      } else { 
	std::cout << " " << (*histogramName) << std::endl;
      }
      TH1* histogram_input = dynamic_cast<TH1*>(inputFile->Get(histogramName->data()));
      if ( !histogram_input ) continue;

      TH1* histogram_output = histograms[*histogramName];
      if ( histogram_output ) {
	histogram_output->Add(histogram_input);
      } else {
	if      ( dynamic_cast<TH1F*>(histogram_input) ) histogram_output = fs.make<TH1F>(*(dynamic_cast<TH1F*>(histogram_input)));
	else if ( dynamic_cast<TH1D*>(histogram_input) ) histogram_output = fs.make<TH1D>(*(dynamic_cast<TH1D*>(histogram_input)));
	assert(histogram_output);
	histograms[*histogramName] = histogram_output;
      }
    }
    delete inputFile;
  }
												
  //delete cutFlowHistManager;											

  clock.Show("produceNtuple_3l_1tau");

  return EXIT_SUCCESS;
}

