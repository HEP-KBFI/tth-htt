#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TError.h> // gErrorAbortLevel, kError

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l_1tau.h" // MEMOutput_3l_1tau
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
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
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l_1tau.h" // MEMInterface_3l_1tau
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_3l_1tau.h" // MEMOutputWriter_3l_1tau
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoWriter.h" // EventInfoWriter
#include "tthAnalysis/HiggsToTauTau/interface/MEMPermutationWriter.h" // MEMPermutationWriter::get_maxPermutations_addMEM_pattern()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // selectObjects(), get_selection(), get_era(), kLoose, kFakeable, kTight
#include "tthAnalysis/HiggsToTauTau/interface/memAuxFunctions.h" // get_memObjectBranchName(), get_memPermutationBranchName()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // k*_central
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively()
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h" // copyBranches_singleType(), copyBranches_vectorType()
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h" // branchEntryBaseType

#include <boost/algorithm/string/predicate.hpp> // boost::algorithm::starts_with(), boost::algorithm::ends_with()

#include <iostream> // std::cerr, std::fixed
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <assert.h> // assert

typedef std::vector<std::string> vstring;

/**
 * @brief Compute MEM for events passing preselection in 3l_1tau channel of ttH, H->tautau analysis
 */
int main(int argc,
         char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<addMEM_3l_1tau>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if(!edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
    throw cms::Exception(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  const edm::ParameterSet cfg        = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_addMEM = cfg.getParameter<edm::ParameterSet>("addMEM_3l_1tau");
  const vstring central_or_shifts           = cfg_addMEM.getParameter<vstring>("central_or_shift");
  const std::string treeName                = cfg_addMEM.getParameter<std::string>("treeName");
  const std::string selEventsFileName_input = cfg_addMEM.getParameter<std::string>("selEventsFileName_input");
  const bool isMC                           = cfg_addMEM.getParameter<bool>("isMC");
  const bool isDEBUG                        = cfg_addMEM.getParameter<bool>("isDEBUG");
  const bool dryRun                         = cfg_addMEM.getParameter<bool>("dryRun");
  const bool copy_all_branches              = cfg_addMEM.getParameter<bool>("copy_all_branches");
  const bool readGenObjects                 = cfg_addMEM.getParameter<bool>("readGenObjects");
  const bool useNonNominal                  = cfg_addMEM.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet           = useNonNominal || ! isMC;

  const std::string branchName_electrons = cfg_addMEM.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_addMEM.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus   = cfg_addMEM.getParameter<std::string>("branchName_hadTaus");
  const std::string branchName_jets      = cfg_addMEM.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_addMEM.getParameter<std::string>("branchName_met");
  const vstring copy_histograms          = cfg_addMEM.getParameter<vstring>("copy_histograms");

  const std::string era_string = cfg_addMEM.getParameter<std::string>("era");
  const int era = get_era(era_string);

  const std::string leptonSelection_string = cfg_addMEM.getParameter<std::string>("leptonSelection");
  const int leptonSelection = get_selection(leptonSelection_string);

  TString hadTauSelection_string = cfg_addMEM.getParameter<std::string>("hadTauSelection");
  TObjArray * hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts -> GetEntries());
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  const std::string hadTauSelection_part2 = hadTauSelection_parts -> GetEntries() == 2   ?
    (dynamic_cast<TObjString *>(hadTauSelection_parts -> At(1))) -> GetString().Data()   :
    ""
  ;
  delete hadTauSelection_parts;

  std::cout << "selEventsFileName_input = " << selEventsFileName_input << '\n';
  RunLumiEventSelector* run_lumi_eventSelector = nullptr;
  if( selEventsFileName_input != "")
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents        = inputFiles.maxEvents();
  const int skipEvents       = cfg.getParameter<edm::ParameterSet>("fwliteInput").getParameter<unsigned>("skipEvents");
  const unsigned reportEvery = inputFiles.reportAfter();
  std::cout << " maxEvents = " << maxEvents << "\n skipEvents = " << skipEvents << '\n';

  const fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TChain* inputTree = new TChain(treeName.data());
  for(const std::string & inputFileName: inputFiles.files())
  {
    std::cout << "input Tree: adding file = " << inputFileName << '\n';
    inputTree->AddFile(inputFileName.data());
  }
  if(inputTree->GetListOfFiles()->GetEntries() < 1)
  {
    throw cms::Exception(argv[0]) << "Failed to identify input Tree !!\n";
  }
  
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);
  std::cout << "input Tree contains " << inputTree->GetEntries()
            << " Entries in "         << inputTree->GetListOfFiles()->GetEntries() << " files.\n";
  
//--- declare event-level variables
  EventInfo eventInfo(false, false, false);
  EventInfoReader eventInfoReader(&eventInfo);
  eventInfoReader.setBranchAddresses(inputTree);

  const std::string branchName_maxPermutations_addMEM = get_memPermutationBranchName(
    "3l_1tau", leptonSelection_string, hadTauSelection_part1, hadTauSelection_part2
  );

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  muonReader->setBranchAddresses(inputTree);
  const RecoMuonCollectionSelectorLoose    preselMuonSelector  (era);
  const RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  const RecoMuonCollectionSelectorTight    tightMuonSelector   (era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  electronReader->readUncorrected(useNonNominal);
  electronReader->setBranchAddresses(inputTree);
  const RecoElectronCollectionCleaner electronCleaner(0.05);
  const RecoElectronCollectionSelectorLoose    preselElectronSelector  (era);
  const RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  const RecoElectronCollectionSelectorTight    tightElectronSelector   (era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(kHadTauPt_central);
  hadTauReader->setBranchAddresses(inputTree);
  const RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose    preselHadTauSelector  (era);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  RecoHadTauCollectionSelectorTight    tightHadTauSelector   (era);
  preselHadTauSelector.set_if_looser(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(-1);
  preselHadTauSelector.set_min_antiMuon(-1);
  fakeableHadTauSelector.set_if_looser(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(-1);
  fakeableHadTauSelector.set_min_antiMuon(-1);
  tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(-1);
  tightHadTauSelector.set_min_antiMuon(-1);
  // CV: lower thresholds on hadronic taus by 2 GeV
  //     with respect to thresholds applied on analysis level (in analyze_2lss_1tau.cc)
  preselHadTauSelector.set_min_pt(18.);
  fakeableHadTauSelector.set_min_pt(18.);
  tightHadTauSelector.set_min_pt(18.);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  // CV: apply jet pT cut on JEC upward shift, to make sure pT cut is loose enough
  //     to allow systematic uncertainty on JEC to be estimated on analysis level
  jetReader->setPtMass_central_or_shift(useNonNominal_jetmet ? kJet_central_nonNominal : kJet_central);
  jetReader->read_ptMass_systematics(isMC);
  jetReader->read_BtagWeight_systematics(isMC);
  jetReader->setBranchAddresses(inputTree);
  const RecoJetCollectionCleaner jetCleaner(0.4);
  const RecoJetCollectionSelector jetSelector(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(useNonNominal_jetmet ? kMEt_central_nonNominal : kMEt_central);
  metReader->read_ptPhi_systematics(isMC);
  metReader->setBranchAddresses(inputTree);

  std::string outputTreeName = treeName;
  std::string outputDirName = "";
  if(outputTreeName.find_last_of("/") != std::string::npos)
  {
    std::size_t pos = outputTreeName.find_last_of("/");
    outputTreeName = std::string(outputTreeName, pos + 1);
    outputDirName  = std::string(outputTreeName, 0, pos);
  }
  if(! outputDirName.empty())
  {
    TDirectory* dir = createSubdirectory_recursively(fs, outputDirName.data());
    dir->cd();
  }
  else
  {
    fs.cd();
  }
  TTree* outputTree = new TTree(outputTreeName.data(), outputTreeName.data());

  RecoMuonWriter *     muonWriter      = nullptr;
  RecoElectronWriter * electronWriter  = nullptr;
  RecoHadTauWriter *   hadTauWriter    = nullptr;
  RecoJetWriter *      jetWriter       = nullptr;
  RecoMEtWriter *      metWriter       = nullptr;
  EventInfoWriter *    eventInfoWriter = nullptr;

  std::map<std::string, branchEntryBaseType*> branchesToKeep;
  if(copy_all_branches)
  {
    eventInfoWriter = new EventInfoWriter(eventInfo.is_signal(), eventInfo.is_mc(), eventInfo.is_mc_th());
    eventInfoWriter->setBranches(outputTree);

    muonWriter = new RecoMuonWriter(era, Form("n%s", branchName_muons.data()), branchName_muons);
    muonWriter->setBranches(outputTree);
    electronWriter = new RecoElectronWriter(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
    electronWriter->writeUncorrected(useNonNominal);
    electronWriter->setBranches(outputTree);
    hadTauWriter = new RecoHadTauWriter(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
    hadTauWriter->setBranches(outputTree);
    jetWriter = new RecoJetWriter(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
    jetWriter->setPtMass_central_or_shift(useNonNominal_jetmet ? kJet_central_nonNominal : kJet_central);
    jetWriter->write_ptMass_systematics(isMC);
    jetWriter->write_BtagWeight_systematics(isMC);
    jetWriter->setBranches(outputTree);
    metWriter = new RecoMEtWriter(era, isMC, branchName_met);
    metWriter->setPtPhi_central_or_shift(useNonNominal_jetmet ? kMEt_central_nonNominal : kMEt_central);
    metWriter->write_ptPhi_systematics(isMC);
    metWriter->setBranches(outputTree);

    vstring outputCommands_string = {
      "keep *",
      Form("drop %s", eventInfoWriter->getBranchName_run().data()),
      Form("drop %s", eventInfoWriter->getBranchName_lumi().data()),
      Form("drop %s", eventInfoWriter->getBranchName_event().data()),
      Form("drop n%s*", branchName_muons.data()),
      Form("drop %s_*", branchName_muons.data()),
      Form("drop n%s*", branchName_electrons.data()),
      Form("drop %s_*", branchName_electrons.data()),
      Form("drop n%s*", branchName_hadTaus.data()),
      Form("drop %s_*", branchName_hadTaus.data()),
      Form("drop n%s*", branchName_jets.data()),
      Form("drop %s_*", branchName_jets.data()),
      Form("drop *%s*", branchName_met.data()),
    };
    std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);
    std::map<std::string, bool>     isBranchToKeep = getBranchesToKeep(inputTree, outputCommands);
    copyBranches_singleType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
    copyBranches_vectorType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  }

  if(! branchesToKeep.count(branchName_maxPermutations_addMEM))
  {
    throw cmsException(__func__, __LINE__)
      << "No such branch: " << branchName_maxPermutations_addMEM;
  }

  const std::string branchName_memOutput = get_memObjectBranchName(
    "3l_1tau", leptonSelection_string, hadTauSelection_part1.data(), hadTauSelection_part2.data()
  );
  std::map<std::string, MEMOutputWriter_3l_1tau *> memWriter;
  for(const std::string & central_or_shift: central_or_shifts)
  {
    const std::string branchName_memOutput_cos(Form("%s_%s", branchName_memOutput.data(), central_or_shift.data()));
    memWriter[central_or_shift] = new MEMOutputWriter_3l_1tau(
      Form("n%s", branchName_memOutput_cos.data()), branchName_memOutput_cos
    );
    memWriter[central_or_shift]->setBranches(outputTree);
    std::cout << "writing MEMOutput_2lss_1tau objects for systematic " << central_or_shift
              << " to branch = '" << branchName_memOutput_cos << "'\n";
  }

  MEMInterface_3l_1tau memInterface_3l_1tau;

  const int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  cutFlowTableType cutFlowTable;
  for(int idxEntry = skipEvents; idxEntry < numEntries && (maxEvents == -1 || idxEntry < (skipEvents + maxEvents)); ++idxEntry)
  {

    if(run_lumi_eventSelector && run_lumi_eventSelector -> areWeDone())
    {
      break;
    }

    inputTree->GetEntry(idxEntry);

    if(idxEntry >= 0 && (idxEntry % reportEvery) == 0)
    {
      std::cout << "processing Entry " << idxEntry << ": " << eventInfo
                << " (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;

    cutFlowTable.update("read from file");

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection");

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon *> cleanedMuons  = muon_ptrs;
    const std::vector<const RecoMuon *> preselMuons   = preselMuonSelector  (cleanedMuons);
    const std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons);
    const std::vector<const RecoMuon *> tightMuons    = tightMuonSelector   (preselMuons);
    const std::vector<const RecoMuon *> selMuons      = selectObjects(
      leptonSelection, preselMuons, fakeableMuons, tightMuons
    );
    if(isDEBUG)
    {
      printCollection("selMuons", selMuons);
    }

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron *> electron_ptrs     = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron *> cleanedElectrons  = electronCleaner(electron_ptrs, fakeableMuons);
    const std::vector<const RecoElectron *> preselElectrons   = preselElectronSelector(cleanedElectrons);
    const std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    const std::vector<const RecoElectron *> tightElectrons    = tightElectronSelector(preselElectrons);
    const std::vector<const RecoElectron *> selElectrons      = selectObjects(
      leptonSelection, preselElectrons, fakeableElectrons, tightElectrons
    );
    if(isDEBUG)
    {
      printCollection("selElectrons", selElectrons);
    }

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau *> hadTau_ptrs     = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau *> cleanedHadTaus  = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau *> preselHadTaus   = preselHadTauSelector(cleanedHadTaus);
    const std::vector<const RecoHadTau *> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    const std::vector<const RecoHadTau *> tightHadTaus    = tightHadTauSelector(cleanedHadTaus);
    const std::vector<const RecoHadTau *> selHadTaus      = selectObjects(
      hadTauSelection, preselHadTaus, fakeableHadTaus, tightHadTaus
    );
    if(isDEBUG)
    {
      printCollection("selHadTaus", selHadTaus);
    }
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);

    const RecoMEt met = metReader->read();

    std::map<std::string, std::vector<MEMOutput_3l_1tau>> memOutputs_3l_1tau;
    for(const std::string & central_or_shift: central_or_shifts)
    {
      memOutputs_3l_1tau[central_or_shift] = {};
    }

//--- fill the branches here since because we want to re-use the readers
//--- however, the readers obtain pointers to gen level objects and pass them to the reco objects
//--- thus, if we try to re-read the objects, these pointers will be overwritten and become invalid
//--- therefore, we have to write the reco objects before re-reading new stuff
    if(copy_all_branches)
    {
      eventInfoWriter->write(eventInfo);
      muonWriter->write(preselMuons);
      electronWriter->write(preselElectrons);
      hadTauWriter->write(preselHadTaus); // save central
      jetWriter->write(jet_ptrs); // save central
      metWriter->write(met); // save central

      for(const auto & branchEntry: branchesToKeep)
      {
        branchEntry.second->copyBranch();
      }
    } // copy_all_branches

//--- compute MEM values
    const Int_t maxPermutations_addMEM_3l_1tau = branchesToKeep.at(branchName_maxPermutations_addMEM)->getValue_int();
    if(isDEBUG)
    {
      std::cout << "Found " << maxPermutations_addMEM_3l_1tau << " possible combination(s) to compute MEM\n";
    }
    if(maxPermutations_addMEM_3l_1tau >= 1)
    {
      const std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons);
      for(std::size_t selLepton_lead_idx = 0; selLepton_lead_idx < selLeptons.size(); ++selLepton_lead_idx)
      {
        const RecoLepton * selLepton_lead = selLeptons[selLepton_lead_idx];
        for(std::size_t selLepton_sublead_idx = selLepton_lead_idx + 1; selLepton_sublead_idx < selLeptons.size(); ++selLepton_sublead_idx)
        {
          const RecoLepton * selLepton_sublead = selLeptons[selLepton_sublead_idx];
          for(std::size_t selLepton_third_idx = selLepton_sublead_idx + 1; selLepton_third_idx < selLeptons.size(); ++selLepton_third_idx)
          {
            const RecoLepton * selLepton_third = selLeptons[selLepton_third_idx];
            for(const std::string central_or_shift: central_or_shifts)
            {
              checkOptionValidity(central_or_shift, isMC);
              const int jetPt_option    = getJet_option     (central_or_shift, isMC);
              const int hadTauPt_option = getHadTauPt_option(central_or_shift);
              const int met_option      = getMET_option     (central_or_shift, isMC);

              if(jetPt_option    == kJet_central      &&
                 hadTauPt_option == kHadTauPt_central &&
                 met_option      == kMEt_central      &&
                 central_or_shift != "central")
              {
                std::cout << "Skipping systematics: " << central_or_shift << '\n';
                continue;
              }

              jetReader   ->setPtMass_central_or_shift  (jetPt_option);
              hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
              metReader   ->setMEt_central_or_shift     (met_option);

//--- build the jet and tau collections specifically for MEM evaluation
              const std::vector<RecoHadTau> hadTaus_mem = hadTauReader->read();
              const std::vector<const RecoHadTau *> hadTau_ptrs_mem     = convert_to_ptrs(hadTaus_mem);
              const std::vector<const RecoHadTau *> cleanedHadTaus_mem  = hadTauCleaner(hadTau_ptrs_mem, preselMuons, preselElectrons);
              const std::vector<const RecoHadTau *> preselHadTaus_mem   = preselHadTauSelector(cleanedHadTaus_mem);
              const std::vector<const RecoHadTau *> fakeableHadTaus_mem = fakeableHadTauSelector(cleanedHadTaus_mem);
              const std::vector<const RecoHadTau *> tightHadTaus_mem    = tightHadTauSelector(cleanedHadTaus_mem);
              const std::vector<const RecoHadTau *> selHadTaus_mem      = selectObjects(
                hadTauSelection, preselHadTaus_mem, fakeableHadTaus_mem, tightHadTaus_mem
              );
              if(isDEBUG)
              {
                printCollection(central_or_shift + " selHadTaus", selHadTaus_mem);
              }

              const std::vector<RecoJet> jets_mem = jetReader->read();
              const std::vector<const RecoJet *> jet_ptrs_mem = convert_to_ptrs(jets_mem);
              const std::vector<const RecoJet *> selJets_mem  = jetSelector(jet_ptrs_mem);

              const RecoMEt met_mem = metReader->read();

              int idxPermutation = -1;

              for (const RecoHadTau * selHadTau: selHadTaus_mem)
              {
                const std::vector<const RecoLepton*> selLeptons_forCleaning = { selLepton_lead, selLepton_sublead, selLepton_third };
                const std::vector<const RecoHadTau *> selHadTaus_forCleaning = { selHadTau };
                const std::vector<const RecoJet *> selJets_mem_cleaned = jetCleaner(
                  selJets_mem, selLeptons_forCleaning, selHadTaus_forCleaning
                );
                if(selJets_mem_cleaned.size() >= 2)
                {
                  ++idxPermutation;
                  if(idxPermutation < maxPermutations_addMEM_3l_1tau)
                  {
                    std::cout << "computing MEM for " << eventInfo
                              << " (idxPermutation = " << idxPermutation << "):\n"
                                 "inputs:\n"
                              << " leading lepton:     " << *(static_cast<const GenLepton *>(selLepton_lead))
                              << " subleading lepton:  " << *(static_cast<const GenLepton *>(selLepton_sublead))
                              << " third lepton:      " << *(static_cast<const GenLepton *>(selLepton_third))
                              << " hadTau (charge = :"   << selHadTau -> charge() << ") "
                                                         << *(static_cast<const Particle *>(selHadTau))
                              << " MET:"                << met_mem << '\n';
                    printCollection("cleaned MEM jets", selJets_mem_cleaned);

                    MEMOutput_3l_1tau memOutput_3l_1tau;
                    if(dryRun)
                    {
                      memOutput_3l_1tau.fillInputs(selLepton_lead, selLepton_sublead, selLepton_third, selHadTau);
                    }
                    else
                    {
                      memOutput_3l_1tau = memInterface_3l_1tau(
                        selLepton_lead, selLepton_sublead, selLepton_third, selHadTau,
                        met_mem, selJets_mem_cleaned
                      );
                    }
                    memOutput_3l_1tau.eventInfo_ = eventInfo;
                    std::cout << "output: (" << central_or_shift << "): " << memOutput_3l_1tau;
                    memOutputs_3l_1tau[central_or_shift].push_back(memOutput_3l_1tau);
                  } // idxPermutation < maxPermutations_addMEM_3l_1tau
                  else if(idxPermutation == maxPermutations_addMEM_3l_1tau) // CV: print warning only once per event
                  {
                    std::cout << "Warning in " << eventInfo << ":\n"
                                 "Number of permutations exceeds 'maxPermutations_addMEM_3l_1tau' = "
                              << maxPermutations_addMEM_3l_1tau << " --> skipping MEM computation after "
                              << maxPermutations_addMEM_3l_1tau << " permutations !!\n";
                  }
                } // selJets_mem_cleaned.size() >= 2
              } // selHadTau

              if(isDEBUG)
              {
                std::cout << "#memOutputs_2lss_1tau = " << memOutputs_3l_1tau[central_or_shift].size() << '\n';
              }
            } // central_or_shift
          } // selLepton_third_idx
        } // selLepton_sublead_idx
      } // selLepton_lead_idx
    } // maxPermutations_addMEM_3l_1tau >= 1

    for(const std::string & central_or_shift: central_or_shifts)
    {
      memWriter[central_or_shift]->write(memOutputs_3l_1tau[central_or_shift]);
    }

    outputTree->Fill();
    ++selectedEntries;
  } // idxEntry

  std::cout << "num. Entries = "  << numEntries      << "\n"
               " analyzed = "     << analyzedEntries << "\n"
               " selected = "     << selectedEntries << "\n"
               "cut-flow table\n" << cutFlowTable    << "\n"
               "output Tree:\n";
  if(isDEBUG)
  {
    outputTree->Print();
  }

  delete run_lumi_eventSelector;
  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;

  for(auto & kv: memWriter)
  {
    if(kv.second)
    {
      delete kv.second;
      kv.second = nullptr;
    }
  }

  delete inputTree;

//--- copy histograms keeping track of number of processed events from input files to output file
  std::cout << "copying histograms:\n";
  std::map<std::string, TH1*> histograms;
  for(const std::string & inputFileName: inputFiles.files())
  {
    TFile* inputFile = new TFile(inputFileName.data());
    if(! inputFile || inputFile -> IsZombie())
    {
      throw cms::Exception(argv[0]) << "Failed to open input File = '" << inputFileName << "' !!\n";
    }

    for(const std::string & histogramName: copy_histograms)
    {
      if(inputFiles.files().size() > 1)
      {
        std::cout << ' ' << histogramName << " from input File = '" << inputFileName << "'\n";
      }
      else
      {
        std::cout << ' ' << histogramName << '\n';
      }
      TH1* histogram_input = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
      if(! histogram_input)
      {
        continue;
      }

      TH1* histogram_output = histograms[histogramName];
      if(histogram_output)
      {
        histogram_output->Add(histogram_input);
      }
      else
      {
        if     (dynamic_cast<TH1F*>(histogram_input))
        {
          histogram_output = fs.make<TH1F>(*(dynamic_cast<TH1F*>(histogram_input)));
        }
        else if(dynamic_cast<TH1D*>(histogram_input))
        {
          histogram_output = fs.make<TH1D>(*(dynamic_cast<TH1D*>(histogram_input)));
        }
        assert(histogram_output);
        histograms[histogramName] = histogram_output;
      } // ! histogram_output
    } // histogramName
    delete inputFile;
  } // inputFileName

  clock.Show("addMEM_3l_1tau");

  return EXIT_SUCCESS;
}
