
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
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" // MEMInterface_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_2lss_1tau.h" // MEMOutputWriter_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_2lss_1tau.h" // CutFlowTableHistManager_2lss_1tau
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

bool skipAddMEM = false;
//bool skipAddMEM = true;

/**
 * @brief Compute MEM for events passing preselection in 2lss_1tau channel of ttH, H->tautau analysis
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<addMEM_2lss_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addMEM_2lss_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addMEM_2lss_1tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addMEM = cfg.getParameter<edm::ParameterSet>("addMEM_2lss_1tau");

  std::string treeName = cfg_addMEM.getParameter<std::string>("treeName");

  std::string era_string = cfg_addMEM.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("addMEM_2lss_1tau") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  std::string leptonSelection_string = cfg_addMEM.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else throw cms::Exception("addMEM_2lss_1tau") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  TString hadTauSelection_string = cfg_addMEM.getParameter<std::string>("hadTauSelection").data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_string == "Loose"    ) hadTauSelection = kLoose;
  else if ( hadTauSelection_string == "Fakeable" ) hadTauSelection = kFakeable;
  else throw cms::Exception("addMEM_2lss_1tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";

  bool use_HIP_mitigation_bTag = cfg_addMEM.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  
  std::string branchName_electrons = cfg_addMEM.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_addMEM.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_addMEM.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_addMEM.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_addMEM.getParameter<std::string>("branchName_met");

  bool copy_all_branches = cfg_addMEM.getParameter<bool>("copy_all_branches");

  vstring copy_histograms = cfg_addMEM.getParameter<vstring>("copy_histograms");

  std::string selEventsFileName_input = cfg_addMEM.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  int skipEvents = cfg.getParameter<edm::ParameterSet>("fwliteInput").getParameter<unsigned>("skipEvents");
  std::cout << " skipEvents = " << skipEvents << std::endl;
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
    throw cms::Exception("addMEM_2lss_1tau") 
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

  Int_t maxPermutations_addMEM_2lss_1tau;
  inputTree->SetBranchAddress("maxPermutations_addMEM_2lss_1tau", &maxPermutations_addMEM_2lss_1tau);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons);
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  
  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  // CV: lower thresholds on hadronic taus by 2 GeV 
  //     with respect to thresholds applied on analysis level (in analyze_2lss_1tau.cc)
  preselHadTauSelector.set_min_pt(18.); 
  fakeableHadTauSelector.set_min_pt(18.);
  
  RecoJetReader* jetReader = new RecoJetReader(era, Form("n%s", branchName_jets.data()), branchName_jets);
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  // CV: apply jet pT cut on JEC upward shift, to make sure pT cut is loose enough
  //     to allow systematic uncertainty on JEC to be estimated on analysis level 
  jetReader->setJetPt_central_or_shift(RecoJetReader::kJetPt_central); 
  jetReader->read_BtagWeight_systematics(true);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met);
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

  RecoMuonWriter* muonWriter = 0;
  RecoElectronWriter* electronWriter = 0;
  RecoHadTauWriter* hadTauWriter = 0;
  RecoJetWriter* jetWriter = 0;
  RecoMEtWriter* metWriter = 0;

  std::map<std::string, branchEntryBaseType*> branchesToKeep;
  if ( copy_all_branches ) {
    outputTree->Branch("run", &run, "run/i");
    outputTree->Branch("lumi", &lumi, "lumi/i");
    outputTree->Branch("evt", &event, "evt/l");

    muonWriter = new RecoMuonWriter(era, Form("n%s", branchName_muons.data()), branchName_muons);
    muonWriter->setBranches(outputTree);
    electronWriter = new RecoElectronWriter(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
    electronWriter->setBranches(outputTree);
    hadTauWriter = new RecoHadTauWriter(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
    hadTauWriter->setBranches(outputTree);
    jetWriter = new RecoJetWriter(era, Form("n%s", branchName_jets.data()), branchName_jets);
    jetWriter->setBranches(outputTree);
    metWriter = new RecoMEtWriter(era, branchName_met);
    metWriter->setBranches(outputTree);
 
    vstring outputCommands_string;
    outputCommands_string.push_back("keep *");
    outputCommands_string.push_back("drop run");
    outputCommands_string.push_back("drop lumi");
    outputCommands_string.push_back("drop evt");
    outputCommands_string.push_back(Form("drop *%s*", branchName_muons.data()));
    outputCommands_string.push_back(Form("drop *%s*", branchName_electrons.data()));
    outputCommands_string.push_back(Form("drop *%s*", branchName_hadTaus.data()));
    outputCommands_string.push_back(Form("drop *%s*", branchName_jets.data()));
    outputCommands_string.push_back(Form("drop *%s*", branchName_met.data()));
    outputCommands_string.push_back("drop maxPermutations_addMEM_2lss_1tau");
    outputCommands_string.push_back("keep *metPuppi*");
    outputCommands_string.push_back("keep HLT_BIT_HLT_*");
    outputCommands_string.push_back("keep *l1*");
    outputCommands_string.push_back("keep *Gen*");
    std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);
    std::map<std::string, bool> isBranchToKeep = getBranchesToKeep(inputTree, outputCommands);
    copyBranches_singleType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
    copyBranches_vectorType(inputTree, outputTree, isBranchToKeep, branchesToKeep);

    outputTree->Branch("maxPermutations_addMEM_2lss_1tau", &maxPermutations_addMEM_2lss_1tau, "maxPermutations_addMEM_2lss_1tau/I");
  }

  std::string branchName_memOutput = "memObjects_2lss_1tau";
  MEMOutputWriter_2lss_1tau* memWriter = new MEMOutputWriter_2lss_1tau(Form("n%s", branchName_memOutput.data()), branchName_memOutput);
  memWriter->setBranches(outputTree);
  std::cout << "writing MEMOutput_2lss_1tau objects to branch = '" << branchName_memOutput << "'" << std::endl;

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  cutFlowTableType cutFlowTable;
  for ( int idxEntry = skipEvents; idxEntry < numEntries && (maxEvents == -1 || idxEntry < (skipEvents + maxEvents)); ++idxEntry ) {

    inputTree->GetEntry(idxEntry);

    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event
		<< " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    
    cutFlowTable.update("read from file");

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else assert(0);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, fakeableMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else assert(0);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else assert(0);
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> selJets = jetSelector(jet_ptrs);

    RecoMEt met = metReader->read();

//--- compute MEM values
    std::vector<MEMOutput_2lss_1tau> memOutputs_2lss_1tau;
    if ( maxPermutations_addMEM_2lss_1tau >= 1 ) {
      int idxPermutation = -1;
      std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons);
      for ( std::vector<const RecoLepton*>::const_iterator selLepton_lead = selLeptons.begin();
	    selLepton_lead != selLeptons.end(); ++selLepton_lead ) {
	for ( std::vector<const RecoLepton*>::const_iterator selLepton_sublead = selLepton_lead + 1;
	      selLepton_sublead != selLeptons.end(); ++selLepton_sublead ) {
	  for ( std::vector<const RecoHadTau*>::const_iterator selHadTau = selHadTaus.begin();
		selHadTau != selHadTaus.end(); ++selHadTau ) {
	    std::vector<const RecoLepton*> selLeptons_forCleaning;
	    selLeptons_forCleaning.push_back(*selLepton_lead);
	    selLeptons_forCleaning.push_back(*selLepton_sublead);
	    std::vector<const RecoHadTau*> selHadTaus_forCleaning;
	    selHadTaus_forCleaning.push_back(*selHadTau);
	    std::vector<const RecoJet*> selJets_cleaned = jetCleaner(selJets, selLeptons_forCleaning, selHadTaus_forCleaning);
	    if ( selJets_cleaned.size() >= 3 ) {
	      ++idxPermutation;
	      if ( idxPermutation < maxPermutations_addMEM_2lss_1tau ) {
		std::cout << "computing MEM for run = " << run << ", lumi = " << lumi << ", event = " << event 
			  << " (idxPermutation = " << idxPermutation << "):" << std::endl;
		std::cout << "inputs:" << std::endl; 
		std::cout << " leading lepton: pT = " << (*selLepton_lead)->pt() << ", eta = " << (*selLepton_lead)->eta() << "," 
			  << " phi = " << (*selLepton_lead)->phi() << ", pdgId = " << (*selLepton_lead)->pdgId() << std::endl;
		std::cout << " subleading lepton: pT = " << (*selLepton_sublead)->pt() << ", eta = " << (*selLepton_sublead)->eta() << "," 
			  << " phi = " << (*selLepton_sublead)->phi() << ", pdgId = " << (*selLepton_sublead)->pdgId() << std::endl;
		std::cout << " hadTau: pT = " << (*selHadTau)->pt() << ", eta = " << (*selHadTau)->eta() << "," 
			  << " phi = " << (*selHadTau)->phi() << ", decayMode = " << (*selHadTau)->decayMode() << ", mass = " << (*selHadTau)->mass() << std::endl;
		std::cout << " MET: pT = " << met.pt() << ", phi = " << met.phi() << std::endl;
		std::cout << " MET cov:" << std::endl;
		met.cov().Print();
		int idxJet = 0;
		for ( std::vector<const RecoJet*>::const_iterator selJet = selJets_cleaned.begin();
		      selJet != selJets_cleaned.end(); ++selJet ) {
		  std::cout << " jet #" << idxJet << ": pT = " << (*selJet)->pt() << ", eta = " << (*selJet)->eta() << "," 
			    << " phi = " << (*selJet)->phi() << ", mass = " << (*selJet)->mass() << ", CSV = " << (*selJet)->BtagCSV() << std::endl;
		  ++idxJet;
		}
		MEMOutput_2lss_1tau memOutput_2lss_1tau;
		if ( skipAddMEM ) {
		  memOutput_2lss_1tau.set_leadLepton_eta((*selLepton_lead)->eta());
		  memOutput_2lss_1tau.set_leadLepton_phi((*selLepton_lead)->phi());
		  memOutput_2lss_1tau.set_subleadLepton_eta((*selLepton_sublead)->eta());
		  memOutput_2lss_1tau.set_subleadLepton_phi((*selLepton_sublead)->phi());
		  memOutput_2lss_1tau.set_hadTau_eta((*selHadTau)->eta());
		  memOutput_2lss_1tau.set_hadTau_phi((*selHadTau)->phi());
		} else {
		  MEMInterface_2lss_1tau memInterface_2lss_1tau("ttH_Htautau_MEM_Analysis/MEM/small.py");
		  memOutput_2lss_1tau = memInterface_2lss_1tau(
	            *selLepton_lead, *selLepton_sublead, *selHadTau,
		    met,
		    selJets_cleaned);
		}
		memOutput_2lss_1tau.set_run(run);
		memOutput_2lss_1tau.set_lumi(lumi);
		memOutput_2lss_1tau.set_evt(event);
		std::cout << "output:" << std::endl; 
		std::cout << memOutput_2lss_1tau;
		memOutputs_2lss_1tau.push_back(memOutput_2lss_1tau);
	      } else if ( idxPermutation == maxPermutations_addMEM_2lss_1tau ) { // CV: print warning only once per event
	        std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << ":" << std::endl; 
	        std::cout << "Number of permutations exceeds 'maxPermutations_addMEM_2lss_1tau' = " << maxPermutations_addMEM_2lss_1tau 
	                  << " --> skipping MEM computation after " << maxPermutations_addMEM_2lss_1tau << " permutations !!\n";
	      }
	    }
	  }
	}
      }
    }
    
    memWriter->write(memOutputs_2lss_1tau);

    if ( copy_all_branches ) {
      muonWriter->write(preselMuons);
      electronWriter->write(preselElectrons);
      hadTauWriter->write(preselHadTaus);
      jetWriter->write(jet_ptrs);
      metWriter->write(met);

      for ( std::map<std::string, branchEntryBaseType*>::const_iterator branchEntry = branchesToKeep.begin();
	    branchEntry != branchesToKeep.end(); ++branchEntry ) {
	branchEntry->second->copyBranch();
      }
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

  delete memWriter;

//--- copy histograms keeping track of number of processed events from input files to output file
  std::cout << "copying histograms:" << std::endl;
  delete inputTree;
  std::map<std::string, TH1*> histograms;
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    TFile* inputFile = new TFile(inputFileName->data());
    if ( !inputFile ) 
      throw cms::Exception("addMEM_2lss_1tau") 
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

  clock.Show("addMEM_2lss_1tau");

  return EXIT_SUCCESS;
}

