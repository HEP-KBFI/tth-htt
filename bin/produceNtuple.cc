
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
#include <TError.h> // gErrorAbortLevel, kError

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/MEMPermutationWriter.h" // MEMPermutationWriter
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoWriter.h" // EventInfoWriter
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, random_start
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // z_mass, z_window
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

#include <boost/algorithm/string/predicate.hpp> // boost::starts_with()

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

template <typename GenParticleType>
std::vector<GenParticle>
convert_to_GenParticle(const std::vector<GenParticleType>& genOtherObjects)
{
  std::vector<GenParticle> genParticles;
  for(const GenParticleType & genOtherObject: genOtherObjects)
  {
    const GenParticle p = static_cast<GenParticle>(genOtherObject);
    genParticles.push_back(p);
  }
  return genParticles;
}

/**
 * @brief Produce Ntuple containing preselected events,
 *        drop branches not needed for ttH, H->tautau analysis,
 *        and add flag indicating for which events the MEM computation is to be run
 *       (the latter is necessary in order to split MEM computation into jobs that each perform ~50 MEM integrations)
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

  std::cout << "<produceNtuple>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("produceNtuple");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("produceNtuple") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_produceNtuple = cfg.getParameter<edm::ParameterSet>("produceNtuple");

  std::string treeName = cfg_produceNtuple.getParameter<std::string>("treeName");

  std::string era_string = cfg_produceNtuple.getParameter<std::string>("era");
  int era = -1;
  if ( era_string == "2017" ) era = kEra_2017;
  else throw cms::Exception("produceNtuple") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  std::string leptonSelection_string = cfg_produceNtuple.getParameter<std::string>("leptonSelection").data();
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("produceNtuple") 
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
   else throw cms::Exception("produceNtuple") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  const std::string branchName_electrons_in   = cfg_produceNtuple.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons_in       = cfg_produceNtuple.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus_in     = cfg_produceNtuple.getParameter<std::string>("branchName_hadTaus");
  const std::string branchName_jets_in        = cfg_produceNtuple.getParameter<std::string>("branchName_jets");
  const std::string branchName_met_in         = cfg_produceNtuple.getParameter<std::string>("branchName_met");
  const std::string branchName_genLeptons1_in = cfg_produceNtuple.getParameter<std::string>("branchName_genLeptons1");
  const std::string branchName_genLeptons2_in = cfg_produceNtuple.getParameter<std::string>("branchName_genLeptons2");
  const std::string branchName_genHadTaus_in  = cfg_produceNtuple.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genJets_in     = cfg_produceNtuple.getParameter<std::string>("branchName_genJets");

  int minNumHadTaus = cfg_produceNtuple.getParameter<int>("minNumHadTaus");

  int minNumLeptons_and_HadTaus = cfg_produceNtuple.getParameter<int>("minNumLeptons_and_HadTaus");

  int minNumJets = cfg_produceNtuple.getParameter<int>("minNumJets");

  int minNumBJets_loose = cfg_produceNtuple.getParameter<int>("minNumBJets_loose");
  int minNumBJets_medium = cfg_produceNtuple.getParameter<int>("minNumBJets_medium");
  
  bool use_HIP_mitigation_mediumMuonId = cfg_produceNtuple.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;


  std::string process_string = cfg_produceNtuple.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  bool isMC = cfg_produceNtuple.getParameter<bool>("isMC");

  std::string selEventsFileName_input = cfg_produceNtuple.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    run_lumi_eventSelector = new RunLumiEventSelector(selEventsFileName_input);
  }

  vstring outputCommands_string = cfg_produceNtuple.getParameter<vstring>("outputCommands");
  std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);

  vstring copy_histograms = cfg_produceNtuple.getParameter<vstring>("copy_histograms");

  // CV: delay start by random time, to avoid that multiple analysis jobs
  //     open all Ntuples at the same time, causing high load on /hdfs file system,
  //     when running on batch
  //unsigned random_seed = cfg_produceNtuple.getParameter<unsigned>("random_seed");
  //random_start(random_seed);

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";
  
//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons_in.c_str()), branchName_muons_in);
  muonReader->set_HIP_mitigation(use_HIP_mitigation_mediumMuonId);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);
  
  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons_in.c_str()), branchName_electrons_in);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus_in.c_str()), branchName_hadTaus_in);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  std::cout << "Setting preselHadTauSelector\n";
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(-1);
  preselHadTauSelector.set_min_antiMuon(-1);
  std::cout << "Setting fakeableHadTauSelector\n";
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(-1);
  fakeableHadTauSelector.set_min_antiMuon(-1);
  std::cout << "Setting tightHadTauSelector\n";
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(-1);
  tightHadTauSelector.set_min_antiMuon(-1);
  // CV: lower thresholds on hadronic taus by 2 GeV 
  //     with respect to thresholds applied on analysis level 
  //     to allow for tau-ES uncertainties to be estimated
  preselHadTauSelector.set_min_pt(18.); 
  fakeableHadTauSelector.set_min_pt(18.);
  tightHadTauSelector.set_min_pt(18.);
  std::cout << hadTauSelection_part2 <<'\n';

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets_in.c_str()), branchName_jets_in);
  jetReader->setJetPt_central_or_shift(RecoJetReader::kJetPt_central); 
  jetReader->read_BtagWeight_systematics(isMC);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met_in);
  inputTree -> registerReader(metReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader(
                                            Form("n%s", branchName_genLeptons1_in.c_str()),      branchName_genLeptons1_in,
      ! branchName_genLeptons2_in.empty() ? Form("n%s", branchName_genLeptons2_in.c_str()) : "", branchName_genLeptons2_in
    );
    inputTree -> registerReader(genLeptonReader);
    genHadTauReader = new GenHadTauReader(Form("n%s", branchName_genHadTaus_in.c_str()), branchName_genHadTaus_in);
    inputTree -> registerReader(genHadTauReader);
    genJetReader = new GenJetReader(Form("n%s", branchName_genJets_in.c_str()), branchName_genJets_in);
    inputTree -> registerReader(genJetReader);
  }

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

  EventInfoWriter * eventInfoWriter = new EventInfoWriter(isSignal, isMC, isMC_tH);
  eventInfoWriter->setBranches(outputTree);

  std::string branchName_muons = branchName_muons_in;
  RecoMuonWriter* muonWriter = new RecoMuonWriter(era, Form("n%s", branchName_muons.data()), branchName_muons);
  muonWriter->setBranches(outputTree);
  std::cout << "writing RecoMuon objects to branch = '" << branchName_muons << "'" << std::endl;

  std::string branchName_electrons = branchName_electrons_in;
  RecoElectronWriter* electronWriter = new RecoElectronWriter(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronWriter->setBranches(outputTree);
  std::cout << "writing RecoElectron objects to branch = '" << branchName_electrons << "'" << std::endl;

  std::string branchName_hadTaus = branchName_hadTaus_in;
  RecoHadTauWriter* hadTauWriter = new RecoHadTauWriter(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauWriter->setBranches(outputTree);
  std::cout << "writing RecoHadTau objects to branch = '" << branchName_hadTaus << "'" << std::endl;

  std::string branchName_jets = branchName_jets_in;
  RecoJetWriter* jetWriter = new RecoJetWriter(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
  jetWriter->setBranches(outputTree);
  std::cout << "writing RecoJet objects to branch = '" << branchName_jets << "'" << std::endl;

  std::string branchName_met = branchName_met_in;
  RecoMEtWriter* metWriter = new RecoMEtWriter(era, branchName_met);
  metWriter->setBranches(outputTree);
  std::cout << "writing RecoMEt object to branch = '" << branchName_met << "'" << std::endl;

  GenParticleWriter* genLeptonWriter = 0;
  GenParticleWriter* genHadTauWriter = 0;
  GenParticleWriter* genJetWriter = 0;
  if ( isMC ) {
    std::string branchName_genLeptons = branchName_genLeptons1_in;
    genLeptonWriter = new GenParticleWriter(Form("n%s", branchName_genLeptons.data()), branchName_genLeptons);
    genLeptonWriter->setBranches(outputTree);
    std::cout << "writing GenLepton objects to branch = '" << branchName_genLeptons << "'" << std::endl;

    std::string branchName_genHadTaus = branchName_genHadTaus_in;
    genHadTauWriter = new GenParticleWriter(Form("n%s", branchName_genHadTaus.data()), branchName_genHadTaus);
    genHadTauWriter->setBranches(outputTree);
    std::cout << "writing GenHadTau objects to branch = '" << branchName_genHadTaus << "'" << std::endl;

    std::string branchName_genJets = branchName_genJets_in;
    genJetWriter = new GenParticleWriter(Form("n%s", branchName_genJets.data()), branchName_genJets);
    genJetWriter->setBranches(outputTree);
    std::cout << "writing GenJet objects to branch = '" << branchName_genJets << "'" << std::endl;
  }

  /* Disabling the functionality of keeping and dropping extra branches from the input file
   *
  std::map<std::string, bool> isBranchToKeep = getBranchesToKeep(inputTree, outputCommands); // key = branchName
  std::map<std::string, branchEntryBaseType*> branchesToKeep; // key = branchName
  copyBranches_singleType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  copyBranches_vectorType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  
  std::cout << "keeping branches:" << std::endl;
  for ( std::map<std::string, branchEntryBaseType*>::const_iterator branchEntry = branchesToKeep.begin();
        branchEntry != branchesToKeep.end(); ++branchEntry ) {
    std::cout << " " << branchEntry->second->outputBranchName_ << " (type = " << branchEntry->second->outputBranchType_string_ << ")" << std::endl;
  }
  */

  // define the writer class for the nof MEM permutations
  MEMPermutationWriter memPermutationWriter;
  memPermutationWriter
    .setLepSelection       (leptonSelection, kTight)
    .setHadTauSelection    (hadTauSelection, kTight)
    .setHadTauWorkingPoints(hadTauSelection_part2) // up until Tight
  ;
  // add conditions for computing the nof MEM permutations in 2lss1tau and 3l1tau channels
  // the arguments are: the name of the channel, minimum number of leptons, minimum number of hadronic taus
  memPermutationWriter
    .addCondition("2lss_1tau", 2, 1)
    .addCondition("3l_1tau",   3, 1)
  ;
  memPermutationWriter.setBranchNames(outputTree, era, true);

  int analyzedEntries = 0;
  int selectedEntries = 0;
  cutFlowTableType cutFlowTable;
  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    
    cutFlowTable.update("read from file");

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection");

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
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
    // Karl: do not clean w.r.t the taus b/c their definition changes across the analyses
    //       we are better off if we keep a bit more jets per event
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons);
    std::vector<const RecoJet*> selJets;
    for ( std::vector<const RecoJet*>::const_iterator cleanedJet = cleanedJets.begin();
          cleanedJet != cleanedJets.end(); ++cleanedJet ) {
      double cleanedJet_pt = (*cleanedJet)->pt();
      double cleanedJet_pt_JECUp = cleanedJet_pt*(1. + (*cleanedJet)->jecUncertTotal());
      double cleanedJet_pt_JECDown = cleanedJet_pt*(1. - (*cleanedJet)->jecUncertTotal());
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

//--- construct the merged lepton collections
    const std::vector<const RecoLepton*> preselLeptons   = mergeLeptonCollections(preselElectrons,   preselMuons);
    const std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    const std::vector<const RecoLepton*> tightLeptons    = mergeLeptonCollections(tightElectrons,    tightMuons);
    const std::vector<const RecoLepton*> selLeptons      = mergeLeptonCollections(selElectrons, selMuons);

//--- apply preselection
    if ( !((int)selLeptons.size() >= minNumLeptons) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selLeptons selection." << std::endl;
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

    if ( selLeptons.size() >= 1 ) {
      const RecoLepton* selLepton_lead = selLeptons[0];
      // CV: lower threshold on leading lepton by 2 GeV 
      //     with respect to thresholds applied on analysis level
      //     to allow for e-ES and mu-ES uncertainties to be estimated
      double minPt_lead = -1.;
      if ( era == kEra_2017 )
      {
        minPt_lead = selLepton_lead -> is_electron() ? 23. : 18.;
      }
      else
      {
        throw cms::Exception("produceNtuple") << "Unsupported era = " << era;
      }
      if ( !(selLepton_lead->pt() > minPt_lead) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event FAILS lepton pT selection." << std::endl;
          std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead << ")" << std::endl;
        }
        continue;
      }
      cutFlowTable.update(Form("lead lepton pT > %1.0f GeV", minPt_lead));
    }

    if ( !((int)selHadTaus.size() >= minNumHadTaus) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event FAILS selHadTaus selection." << std::endl;
        std::cout << " (#preselHadTaus = " << preselHadTaus.size() << ")" << std::endl;
        for ( size_t idxPreselHadTau = 0; idxPreselHadTau < preselHadTaus.size(); ++idxPreselHadTau ) {
          std::cout << "preselHadTau #" << idxPreselHadTau << ":" << std::endl;
          std::cout << (*preselHadTaus[idxPreselHadTau]);
        }
        std::cout << " (#selHadTaus = " << selHadTaus.size() << ")" << std::endl;
        for ( size_t idxSelHadTau = 0; idxSelHadTau < selHadTaus.size(); ++idxSelHadTau ) {
          std::cout << "selHadTau #" << idxSelHadTau << ":" << std::endl;
          std::cout << (*selHadTaus[idxSelHadTau]);
        }
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i sel hadTaus", minNumHadTaus));
    
    if ( !((int)(selLeptons.size() + selHadTaus.size()) >= minNumLeptons_and_HadTaus) ) {
      continue;
    }
    cutFlowTable.update(Form(">= %i sel leptons+hadTaus", minNumLeptons_and_HadTaus));

    // apply requirement on jets 
    if ( !((int)selJets.size() >= minNumJets) ) {
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

    // apply requirement on b-jets 
    if ( !((int)selBJets_loose.size() >= minNumBJets_loose || (int)selBJets_medium.size() >= minNumBJets_medium) ) {
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
    
//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC ) {
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

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

    memPermutationWriter.write(
      {{preselLeptons, fakeableLeptons, tightLeptons}}, {{selBJets_loose, selBJets_medium}}, cleanedHadTaus
    );

    eventInfoWriter->write(eventInfo);
    muonWriter->write(preselMuons);
    electronWriter->write(preselElectrons);
    hadTauWriter->write(fakeableHadTaus);
    jetWriter->write(selJets);
    metWriter->write(met);

    if ( isMC ) {
      genLeptonWriter->write(convert_to_GenParticle(genLeptons));
      genHadTauWriter->write(convert_to_GenParticle(genHadTaus));
      genJetWriter->write(convert_to_GenParticle(genJets));
    }

    //std::cout << "copying branches:" << std::endl;
    /*
    for ( std::map<std::string, branchEntryBaseType*>::const_iterator branchEntry = branchesToKeep.begin();
          branchEntry != branchesToKeep.end(); ++branchEntry ) {
      //std::cout << branchEntry->second->outputBranchName_ << std::endl;
      branchEntry->second->copyBranch();
    }
    */

    outputTree->Fill();

    ++selectedEntries;
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries
            << "cut-flow table" << std::endl;
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

  delete genLeptonWriter;
  delete genHadTauWriter;
  delete genJetWriter;

//--- copy histograms keeping track of number of processed events from input files to output file
  std::cout << "copying histograms:" << std::endl;
  delete inputTree;
  std::map<std::string, TH1*> histograms;
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
        inputFileName != inputFiles.files().end(); ++inputFileName ) {
    TFile* inputFile = new TFile(inputFileName->data());
    if ( !inputFile ) 
      throw cms::Exception("produceNtuple") 
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

  clock.Show("produceNtuple");

  return EXIT_SUCCESS;
}

