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

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l.h" // MEMInterface_3l
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_3l.h" // MEMOutputWriter_3l
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter
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
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <boost/algorithm/string/predicate.hpp> // boost::algorithm::starts_with(), boost::algorithm::ends_with()

#include <iostream> // std::cerr, std::fixed
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <assert.h> // assert

typedef std::vector<std::string> vstring;

/**
 * @brief Compute MEM for events passing preselection in 3l channel of ttH, H->tautau analysis
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

  std::cout << "<addMEM_3l>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if(!edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
    throw cms::Exception(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  const edm::ParameterSet cfg        = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_addMEM = cfg.getParameter<edm::ParameterSet>("addMEM_3l");
  const vstring central_or_shifts           = cfg_addMEM.getParameter<vstring>("central_or_shift");
  const std::string treeName                = cfg_addMEM.getParameter<std::string>("treeName");
  const std::string selEventsFileName_input = cfg_addMEM.getParameter<std::string>("selEventsFileName_input");
  const bool isMC                           = cfg_addMEM.getParameter<bool>("isMC");
  const bool isDEBUG                        = cfg_addMEM.getParameter<bool>("isDEBUG");
  const bool dryRun                         = cfg_addMEM.getParameter<bool>("dryRun");
  const bool copy_all_branches              = cfg_addMEM.getParameter<bool>("copy_all_branches");
  const bool readGenObjects                 = cfg_addMEM.getParameter<bool>("readGenObjects");
  const bool jetCleaningByIndex             = cfg_addMEM.getParameter<bool>("jetCleaningByIndex");
  const bool useNonNominal                  = cfg_addMEM.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet           = useNonNominal || ! isMC;

  const std::string branchName_electrons = cfg_addMEM.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_addMEM.getParameter<std::string>("branchName_muons");
  const std::string branchName_jets      = cfg_addMEM.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_addMEM.getParameter<std::string>("branchName_met");
  const vstring copy_histograms          = cfg_addMEM.getParameter<vstring>("copy_histograms");

  const std::string era_string = cfg_addMEM.getParameter<std::string>("era");
  const int era = get_era(era_string);

  const std::string leptonSelection_string = cfg_addMEM.getParameter<std::string>("leptonSelection");
  const int leptonSelection = get_selection(leptonSelection_string);

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
  EventInfo eventInfo;
  EventInfoReader eventInfoReader(&eventInfo);
  eventInfoReader.setBranchAddresses(inputTree);

  const std::string branchName_maxPermutations_addMEM = get_memPermutationBranchName(
    "3l", leptonSelection_string
  );

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  muonReader->setBranchAddresses(inputTree);
  const RecoMuonCollectionSelectorLoose    preselMuonSelector  (era);
  const RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  const RecoMuonCollectionSelectorTight    tightMuonSelector   (era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  electronReader->setBranchAddresses(inputTree);
  const RecoElectronCollectionCleaner electronCleaner(0.3);
  const RecoElectronCollectionSelectorLoose    preselElectronSelector  (era);
  const RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  const RecoElectronCollectionSelectorTight    tightElectronSelector   (era);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  // CV: apply jet pT cut on JEC upward shift, to make sure pT cut is loose enough
  //     to allow systematic uncertainty on JEC to be estimated on analysis level
  jetReader->setPtMass_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
  jetReader->read_ptMass_systematics(isMC);
  jetReader->setBranchAddresses(inputTree);
  const RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  const RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  const RecoJetCollectionSelector jetSelector(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
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
  RecoJetWriter *      jetWriter       = nullptr;
  RecoMEtWriter *      metWriter       = nullptr;
  EventInfoWriter *    eventInfoWriter = nullptr;

  std::map<std::string, branchEntryBaseType*> branchesToKeep;
  if(copy_all_branches)
  {
    eventInfoWriter = new EventInfoWriter(eventInfo.is_signal(), eventInfo.is_mc());
    eventInfoWriter->setBranches(outputTree);

    muonWriter = new RecoMuonWriter(era, isMC, Form("n%s", branchName_muons.data()), branchName_muons);
    muonWriter->setBranches(outputTree);
    electronWriter = new RecoElectronWriter(era, isMC, Form("n%s", branchName_electrons.data()), branchName_electrons);
    electronWriter->writeUncorrected(useNonNominal);
    electronWriter->setBranches(outputTree);
    jetWriter = new RecoJetWriter(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
    jetWriter->setPtMass_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
    jetWriter->setBranches(outputTree);
    metWriter = new RecoMEtWriter(era, isMC, branchName_met);
    metWriter->setPtPhi_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
    metWriter->write_ptPhi_systematics(isMC);
    metWriter->setBranches(outputTree);

    vstring outputCommands_string = {
      "keep *",
      Form("drop %s", eventInfoWriter->getBranchName_run().data()),
      Form("drop %s", eventInfoWriter->getBranchName_lumi().data()),
      Form("drop %s", eventInfoWriter->getBranchName_event().data()),
      Form("drop %s", eventInfoWriter->getBranchName_PV_ndof().data()),
      Form("drop n%s", branchName_muons.data()),
      Form("drop n%s_*", branchName_muons.data()),
      Form("drop %s_*", branchName_muons.data()),
      Form("drop n%s", branchName_electrons.data()),
      Form("drop n%s_*", branchName_electrons.data()),
      Form("drop %s_*", branchName_electrons.data()),
      Form("drop n%s", branchName_jets.data()),
      Form("drop n%s_*", branchName_jets.data()),
      Form("drop %s_*", branchName_jets.data()),
      Form("drop %s_*", branchName_met.data())
    };
    std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);
    std::map<std::string, bool> isBranchToKeep = getBranchesToKeep(inputTree, outputCommands);
    copyBranches_singleType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
    copyBranches_vectorType(inputTree, outputTree, isBranchToKeep, branchesToKeep);
  }

  if(! branchesToKeep.count(branchName_maxPermutations_addMEM))
  {
    throw cmsException(__func__, __LINE__)
      << "No such branch: " << branchName_maxPermutations_addMEM;
  }

  const std::string branchName_memOutput = get_memObjectBranchName(
    "3l", leptonSelection_string
  );
  std::map<std::string, MEMOutputWriter_3l *> memWriter;
  for(const std::string & central_or_shift: central_or_shifts)
  {
    const std::string branchName_memOutput_cos(Form("%s_%s", branchName_memOutput.data(), central_or_shift.data()));
    memWriter[central_or_shift] = new MEMOutputWriter_3l(
      Form("n%s", branchName_memOutput_cos.data()), branchName_memOutput_cos
    );
    memWriter[central_or_shift]->setBranches(outputTree);
    std::cout << "writing MEMOutput_3l objects for systematic " << central_or_shift
              << " to branch = '" << branchName_memOutput_cos << "'\n";
  }

  LocalFileInPath memConfigFileName("tthAnalysis/HiggsToTauTau/data/addMEM_3l.cfg");
  MEMInterface_3l memInterface_3l(memConfigFileName.fullPath());

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
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);

    const RecoMEt met = metReader->read();

    std::map<std::string, std::vector<MEMOutput_3l>> memOutputs_3l;
    for(const std::string & central_or_shift: central_or_shifts)
    {
      memOutputs_3l[central_or_shift] = {};
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
      jetWriter->write(jet_ptrs); // save central
      metWriter->write(met); // save central

      for(const auto & branchEntry: branchesToKeep)
      {
        branchEntry.second->copyBranch();
      }
    } // copy_all_branches

//--- compute MEM values
    const Int_t maxPermutations_addMEM_3l = branchesToKeep.at(branchName_maxPermutations_addMEM)->getValue_int();
    if(isDEBUG)
    {
      std::cout << "Found " << maxPermutations_addMEM_3l << " possible combination(s) to compute MEM\n";
    }
    if(maxPermutations_addMEM_3l >= 1)
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
            for(const std::string & central_or_shift: central_or_shifts)
            {
              checkOptionValidity(central_or_shift, isMC);
              const int jetPt_option    = getJet_option     (central_or_shift, isMC);
              const int met_option      = getMET_option     (central_or_shift, isMC);

              if(jetPt_option    == kJetMET_central      &&
                 met_option      == kJetMET_central      &&
                 central_or_shift != "central")
              {
                std::cout << "Skipping systematics: " << central_or_shift << '\n';
                continue;
              }

              jetReader   ->setPtMass_central_or_shift  (jetPt_option);
              metReader   ->setMEt_central_or_shift     (met_option);

//--- build the jet collections specifically for MEM evaluation
              const std::vector<RecoJet> jets_mem = jetReader->read();
              const std::vector<const RecoJet *> jet_ptrs_mem = convert_to_ptrs(jets_mem);
              const std::vector<const RecoJet *> selJets_mem  = jetSelector(jet_ptrs_mem);

              const RecoMEt met_mem = metReader->read();

              int idxPermutation = -1;

              const std::vector<const RecoLepton*> selLeptons_forCleaning = { selLepton_lead, selLepton_sublead, selLepton_third };
              const std::vector<const RecoJet *> selJets_mem_cleaned = jetCleaningByIndex ?
                jetCleanerByIndex(selJets_mem, selLeptons_forCleaning) :
                jetCleaner       (selJets_mem, selLeptons_forCleaning)
              ;
              if(selJets_mem_cleaned.size() >= 2)
              {
                ++idxPermutation;
                if(idxPermutation < maxPermutations_addMEM_3l)
                {
                  if(isDEBUG)
                  {
                    std::cout << "computing MEM for " << eventInfo
                              << " (idxPermutation = " << idxPermutation << "):\n"
                                 "inputs:\n"
                              << " leading lepton:    " << *(static_cast<const ChargedParticle *>(selLepton_lead))
                              << " subleading lepton: " << *(static_cast<const ChargedParticle *>(selLepton_sublead))
                              << " third lepton:      " << *(static_cast<const ChargedParticle *>(selLepton_third))
                              << " MET:"                << met_mem << '\n';
                    printCollection("cleaned MEM jets", selJets_mem_cleaned);
                  }

                  MEMOutput_3l memOutput_3l;
                  if(dryRun)
                  {
                    memOutput_3l.fillInputs(selLepton_lead, selLepton_sublead, selLepton_third);
                  }
                  else
                  {
                    memOutput_3l = memInterface_3l(
                      selLepton_lead, selLepton_sublead, selLepton_third,
                      met_mem, selJets_mem_cleaned
                    );
                  }
                  memOutput_3l.eventInfo_ = eventInfo;
                  std::cout << "output: (" << central_or_shift << "): " << memOutput_3l;
                  memOutputs_3l[central_or_shift].push_back(memOutput_3l);
                } // idxPermutation < maxPermutations_addMEM_3l
                else if(idxPermutation == maxPermutations_addMEM_3l) // CV: print warning only once per event
                {
                  std::cout << "Warning in " << eventInfo << ":\n"
                               "Number of permutations exceeds 'maxPermutations_addMEM_3l' = "
                            << maxPermutations_addMEM_3l << " --> skipping MEM computation after "
                            << maxPermutations_addMEM_3l << " permutations !!\n";
                }
              } // selJets_mem_cleaned.size() >= 2

                if(isDEBUG)
              {
                std::cout << "#memOutputs_3l = " << memOutputs_3l[central_or_shift].size() << '\n';
              }
            } // central_or_shift
          } // selLepton_third_idx
        } // selLepton_sublead_idx
      } // selLepton_lead_idx
    } // maxPermutations_addMEM_3l >= 1

    for(const std::string & central_or_shift: central_or_shifts)
    {
      memWriter[central_or_shift]->write(memOutputs_3l[central_or_shift]);
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

  clock.Show("addMEM_3l");

  return EXIT_SUCCESS;
}
