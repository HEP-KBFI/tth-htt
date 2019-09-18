#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
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
#include "tthAnalysis/HiggsToTauTau/interface/hltPathWriter.h" // hltPathWriter
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityWriter.h" // ObjectMultiplicityWriter
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017, kLoose, kFakeable, kTight
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // k*_central
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType(), kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h" // branchEntryBaseType
#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h" // copyBranches_singleType, copyBranches_vectorType
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h"
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet
#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles
#include <FWCore/Utilities/interface/Parse.h> // edm::tokenize()

#include <TChain.h> // TChain
#include <TBenchmark.h> // TBenchmark

#include <regex> // std::regex_match(), std::regex, std::smatch

typedef std::vector<std::string> vstring;

template <typename GenParticleType>
std::vector<GenParticle>
convert_to_GenParticle(const std::vector<GenParticleType> & genOtherObjects)
{
  std::vector<GenParticle> genParticles;
  std::transform(
    genOtherObjects.cbegin(), genOtherObjects.cend(), std::back_inserter(genParticles),
    [](const GenParticleType & genOtherObject) -> const GenParticle
    {
      return static_cast<GenParticle>(genOtherObject);
    }
  );
  return genParticles;
}

/**
 * @brief Produce Ntuple containing preselected events,
 *        drop branches not needed for ttH, H->tautau analysis,
 *        and add flag indicating for which events the MEM computation is to be run
 *       (the latter is necessary in order to split MEM computation into jobs that each perform ~50 MEM integrations)
 */
int
main(int argc,
     char ** argv)
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<produceNtuple>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("produceNtuple");

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException("produceNtuple", __LINE__)
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << "";
  }

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_produceNtuple = cfg.getParameter<edm::ParameterSet>("produceNtuple");
  const std::string treeName = cfg_produceNtuple.getParameter<std::string>("treeName");
  const int basketSize = cfg_produceNtuple.getParameter<int>("basketSize");
  const int cacheSize = cfg_produceNtuple.getParameter<int>("cacheSize");

  const std::string era_string = cfg_produceNtuple.getParameter<std::string>("era");
  const int era = get_era(era_string);

  const std::string leptonSelection_string = cfg_produceNtuple.getParameter<std::string>("leptonSelection");
  const int leptonSelection = get_selection(leptonSelection_string);
  const std::string hadTauSelection_tauIDwp = cfg_produceNtuple.getParameter<std::string>("hadTauWP");

  const std::string branchName_electrons  = cfg_produceNtuple.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons      = cfg_produceNtuple.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus    = cfg_produceNtuple.getParameter<std::string>("branchName_hadTaus");
  const std::string branchName_jets       = cfg_produceNtuple.getParameter<std::string>("branchName_jets");
  const std::string branchName_met        = cfg_produceNtuple.getParameter<std::string>("branchName_met");
  const std::string branchName_genLeptons = cfg_produceNtuple.getParameter<std::string>("branchName_genLeptons");
  const std::string branchName_genHadTaus = cfg_produceNtuple.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genPhotons = cfg_produceNtuple.getParameter<std::string>("branchName_genPhotons");
  const std::string branchName_genJets    = cfg_produceNtuple.getParameter<std::string>("branchName_genJets");

  const std::string branchName_muonGenMatch     = cfg_produceNtuple.getParameter<std::string>("branchName_muonGenMatch");
  const std::string branchName_electronGenMatch = cfg_produceNtuple.getParameter<std::string>("branchName_electronGenMatch");
  const std::string branchName_hadTauGenMatch   = cfg_produceNtuple.getParameter<std::string>("branchName_hadTauGenMatch");
  const std::string branchName_jetGenMatch      = cfg_produceNtuple.getParameter<std::string>("branchName_jetGenMatch");

  const vstring branchNames_triggers       = cfg_produceNtuple.getParameter<vstring>("branchNames_triggers");
  const vstring branchNames_triggersFilter = cfg_produceNtuple.getParameter<vstring>("branchNames_triggersFilter");

  const int minNumLeptons             = cfg_produceNtuple.getParameter<int>("minNumLeptons");
  const int minNumHadTaus             = cfg_produceNtuple.getParameter<int>("minNumHadTaus");
  const int minNumLeptons_and_HadTaus = cfg_produceNtuple.getParameter<int>("minNumLeptons_and_HadTaus");
  const int minNumJets                = cfg_produceNtuple.getParameter<int>("minNumJets");
  const int minNumBJets_loose         = cfg_produceNtuple.getParameter<int>("minNumBJets_loose");
  const int minNumBJets_medium        = cfg_produceNtuple.getParameter<int>("minNumBJets_medium");
  const int maxNumBJets_loose         = cfg_produceNtuple.getParameter<int>("maxNumBJets_loose");
  const int maxNumBJets_medium        = cfg_produceNtuple.getParameter<int>("maxNumBJets_medium");
  const bool applyJetEtaCut           = cfg_produceNtuple.getParameter<bool>("applyJetEtaCut");

  const bool isMC                    = cfg_produceNtuple.getParameter<bool>("isMC");
  const bool redoGenMatching         = cfg_produceNtuple.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex      = cfg_produceNtuple.getParameter<bool>("genMatchingByIndex");
  const bool isDEBUG                 = cfg_produceNtuple.getParameter<bool>("isDEBUG");
  const bool useNonNominal           = cfg_produceNtuple.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet    = useNonNominal || ! isMC;
  const bool readGenObjects          = isMC && ! redoGenMatching;

  const std::string selEventsFileName_input = cfg_produceNtuple.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << '\n';
  RunLumiEventSelector * const run_lumi_eventSelector = selEventsFileName_input.empty() ?
    nullptr                                                                             :
    new RunLumiEventSelector(selEventsFileName_input)
  ;

  const vstring copy_histograms = cfg_produceNtuple.getParameter<vstring>("copy_histograms");
  const vstring drop_branches = cfg_produceNtuple.getParameter<vstring>("drop_branches");

  std::vector<std::regex> copy_histograms_regex;
  std::transform(
    copy_histograms.begin(), copy_histograms.end(), std::back_inserter(copy_histograms_regex),
    [](const std::string & copy_histogram_regex) -> std::regex { return std::regex(copy_histogram_regex); }
  );

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << '\n';
  const unsigned reportEvery = inputFiles.reportAfter();

  const fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout
    << "For the input trees, setting the basket size to " << basketSize << "b "
       "and cache size to " << cacheSize << "b\n"
  ;
  inputTree->setBasketSize(basketSize);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo;
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  // There are four distinct scenarios:
  // 1) no event-level preselection by HLT paths is applied -> branchNames_triggersFilter is empty
  //    1.a) data: branchNames_triggers contains all HLT paths that a given PD must include
  //               All HLT paths are explicitly copied from input to output. There may be some missing "required"
  //               HLT paths that do not belong to a given PD or even to data -- they're never recreated but just
  //               excluded at the analysis level.
  //    1.b) MC: branchNames_triggers is empty
  //             All HLT paths are implicitly copied from input to output. Some HLT paths may be missing in MC -- they're
  //             never recreated but just excluded at the analysis level.
  // 2) event-level preselection by HLT paths is applied -> branchNames_triggersFilter is not empty
  //    2.a) data: branchNames_triggers contains all HLT paths that a given PD must include
  //               All HLT paths are explicitly copied from input to output, which means that we can access their values
  //               at the same time. So, by filtering these HLT paths by their name we can make the decision by taking
  //               the logical OR of filtered HLT paths. Even if some HLT paths are missing from the input Ntuple,
  //               then this works in favor to us: we just consider the paths to be not triggered.
  //    2.b) MC: branchNames_triggers is empty
  //             Now, this is a bit complicated: we don't explicitly copy the HLT paths from input to output but we do it
  //             implicitly. This means that if we want to read the value of the HLT paths from the input file, we need
  //             to exclude them from implicit copy procedure. However, this means that any missing branches will be
  //             recreated.
  assert(isMC != (! branchNames_triggers.empty()));
  const bool filterByTrigger = ! branchNames_triggersFilter.empty();
  std::vector<std::string> triggerBranches_explicitCopy;
  std::vector<hltPath *> triggers;
  std::vector<hltPath *> triggersToFilter;
  if(! isMC)
  {
    // copy all branches explicitly in data (1.a, 2.a)
    triggerBranches_explicitCopy = branchNames_triggers;
  }
  else if(filterByTrigger)
  {
    // copy only these branches explicitly that we filter in MC (2.b)
    triggerBranches_explicitCopy = branchNames_triggersFilter;
  }
  // 1.b: nothing to explicitly copy
  triggers = create_hltPaths(triggerBranches_explicitCopy, "triggers");
  triggersToFilter = filter_hltPaths(triggers, branchNames_triggersFilter);
  if(filterByTrigger)
  {
    std::cout << "Applying preselection by requiring each event to pass logical OR of the following HLT paths:\n";
    for(const std::string & branchName_triggersFilter: branchNames_triggersFilter)
    {
      std::cout << "  " << branchName_triggersFilter << '\n';
    }
  }

  hltPathReader hltPathReader_instance(triggers);
  inputTree -> registerReader(&hltPathReader_instance);

//--- declare particle collections
  RecoMuonReader * const muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree -> registerReader(muonReader);
  const RecoMuonCollectionGenMatcher muonGenMatcher;
  const RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  const RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  const RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);
  
  RecoElectronReader * const electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree -> registerReader(electronReader);
  const RecoElectronCollectionGenMatcher electronGenMatcher;
  const RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  const RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  const RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  const RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);

  double minPt_ele = -1.;
  double minPt_mu  = -1.;
  switch(era)
  {
    case kEra_2016:
    case kEra_2017:
    case kEra_2018: minPt_ele = 23.; minPt_mu = 18.; break;
    default:        throw cmsException("produceNtuple", __LINE__) << "Unsupported era = " << era;
  }

  RecoHadTauReader * const hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, isMC, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(kHadTauPt_uncorrected);
  inputTree -> registerReader(hadTauReader);
  const RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  const RecoHadTauCollectionCleaner hadTauCleaner(0.3, isDEBUG);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  fakeableHadTauSelector.disable_deeptau_lepton();
  fakeableHadTauSelector.set(hadTauSelection_tauIDwp);
  fakeableHadTauSelector.set_min_antiElectron(-1);
  fakeableHadTauSelector.set_min_antiMuon(-1);
  // CV: lower thresholds on hadronic taus by 2 GeV 
  //     with respect to thresholds applied on analysis level 
  //     to allow for tau-ES uncertainties to be estimated
  const double minPt_hadTau = 18.;
  fakeableHadTauSelector.set_min_pt(minPt_hadTau);

  // construct tau selectors that are needed for counting the multiplicities of taus passing each tau ID & WP
  std::map<TauID, std::map<int, RecoHadTauCollectionSelectorFakeable *>> multplicityHadTauSelectors;
  for(const auto & kv: TauID_PyMap)
  {
    multplicityHadTauSelectors[kv.second] = {};
    const int max_level = TauID_levels.at(kv.second);
    for(int level = 1; level <= max_level; ++level)
    {
      multplicityHadTauSelectors[kv.second][level] = new RecoHadTauCollectionSelectorFakeable(era, -1, isDEBUG);
      multplicityHadTauSelectors[kv.second][level]->disable_deeptau_lepton();
      multplicityHadTauSelectors[kv.second][level]->set(kv.first + TauID_level_strings.at(max_level).at(level - 1));
      multplicityHadTauSelectors[kv.second][level]->set_min_antiElectron(-1);
      multplicityHadTauSelectors[kv.second][level]->set_min_antiMuon(-1);
      multplicityHadTauSelectors[kv.second][level]->set_min_pt(minPt_hadTau);
    }
  }

  RecoJetReader * const jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
  jetReader->read_ptMass_systematics(isMC);
  inputTree -> registerReader(jetReader);
  const RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);

//--- save the default settings of jetSelector
  if(! applyJetEtaCut)
  {
    jetSelector.set_max_absEta(-1.);
  }
  const double min_jetSelector_pT     = jetSelector.get_min_pt();
  const double max_jetSelector_absEta = jetSelector.get_max_absEta();

//--- Disable pT cuts on the loose and medium b-tag selectors because we have to consider the effects
//    due to JECs: the jet pT may fluctuate up or down, and because of this the jet may fail pT requirement
//    depending on the choice of systematic uncertainties. The solution is to find maximum upwards
//    fluctuation in pT due to JEC and select only such cleaned jets that pass the pT cut in any systematic
//    setting. However, these jets that pass the pT cut due to JEC but otherwise wouldn't, would still be
//    cut out by the loose and medium b-tag selectors (they also employ the pT cut on top of b-tagging
//    requirements). The solution is to remove the pT cut in b-tagging selectors because the input jet
//    collection all already passes the pT cut in at least one choice of systematic uncertainties.
  jetSelectorBtagLoose.getSelector().set_min_pt(-1.);
  jetSelectorBtagLoose.getSelector().set_max_absEta(max_jetSelector_absEta);
  jetSelectorBtagMedium.getSelector().set_min_pt(-1.);
  jetSelectorBtagMedium.getSelector().set_max_absEta(max_jetSelector_absEta);

//--- declare missing transverse energy
  RecoMEtReader * const metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
  metReader->read_ptPhi_systematics(isMC);
  inputTree -> registerReader(metReader);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  GenJetReader * genJetReader = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  GenParticleReader * genMatchToHadTauReader   = nullptr;
  GenParticleReader * genMatchToJetReader      = nullptr;

  if(isMC && ! readGenObjects)
  {
    genLeptonReader = new GenLeptonReader(branchName_genLeptons);
    inputTree -> registerReader(genLeptonReader);
    genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
    inputTree -> registerReader(genHadTauReader);
    genJetReader = new GenJetReader(branchName_genJets);
    genJetReader->read_partonFlavour();
    inputTree -> registerReader(genJetReader);

    if(genMatchingByIndex)
    {
      genMatchToMuonReader = new GenParticleReader(branchName_muonGenMatch);
      genMatchToMuonReader -> readGenPartFlav(true);
      inputTree -> registerReader(genMatchToMuonReader);

      genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
      genMatchToElectronReader -> readGenPartFlav(true);
      inputTree -> registerReader(genMatchToElectronReader);

      genMatchToHadTauReader = new GenParticleReader(branchName_hadTauGenMatch);
      genMatchToHadTauReader -> readGenPartFlav(true);
      inputTree -> registerReader(genMatchToHadTauReader);

      genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
      genMatchToJetReader -> readGenPartFlav(true);
      inputTree -> registerReader(genMatchToJetReader);
    }
    else
    {
      genPhotonReader = new GenPhotonReader(branchName_genPhotons);
      inputTree -> registerReader(genPhotonReader);
    }
  }

  std::string outputTreeName = treeName;
  std::string outputDirName = "";
  if(outputTreeName.find_last_of("/") != std::string::npos)
  {
    std::size_t pos = outputTreeName.find_last_of("/");
    outputTreeName = std::string(outputTreeName, pos + 1);
    outputDirName = std::string(outputTreeName, 0, pos);
  }
  if(! outputDirName.empty())
  {
    TDirectory * const dir = createSubdirectory_recursively(fs, outputDirName.data());
    dir->cd();
  }
  else
  {
    fs.cd();
  }
  TTree * const outputTree = new TTree(outputTreeName.data(), outputTreeName.data());

  EventInfoWriter eventInfoWriter;
  eventInfoWriter.setBranches(outputTree);

  ObjectMultiplicityWriter objectMultiplicityWriter(true);
  objectMultiplicityWriter.setBranches(outputTree);

  hltPathWriter hltPathWriter_instance(triggerBranches_explicitCopy);
  hltPathWriter_instance.setBranches(outputTree);

  RecoMuonWriter * const muonWriter = new RecoMuonWriter(era, isMC, branchName_muons);
  muonWriter->setBranches(outputTree);
  std::cout << "writing RecoMuon objects to branch = '" << branchName_muons << "'\n";

  RecoElectronWriter * const electronWriter = new RecoElectronWriter(era, isMC, branchName_electrons);
  electronWriter->writeUncorrected(false);
  electronWriter->setBranches(outputTree);
  std::cout << "writing RecoElectron objects to branch = '" << branchName_electrons << "'\n";

  RecoHadTauWriter * const hadTauWriter = new RecoHadTauWriter(era, isMC, branchName_hadTaus);
  hadTauWriter->setBranches(outputTree);
  std::cout << "writing RecoHadTau objects to branch = '" << branchName_hadTaus << "'\n";

  RecoJetWriter * const jetWriter = new RecoJetWriter(era, isMC, branchName_jets);
  jetWriter->setPtMass_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
  jetWriter->setBranches(outputTree);
  std::cout << "writing RecoJet objects to branch = '" << branchName_jets << "'\n";

  RecoMEtWriter * const metWriter = new RecoMEtWriter(era, isMC, branchName_met);
  metWriter->setPtPhi_central_or_shift(useNonNominal_jetmet ? kJetMET_central_nonNominal : kJetMET_central);
  metWriter->write_ptPhi_systematics(isMC);
  metWriter->setBranches(outputTree);
  std::cout << "writing RecoMEt object to branch = '" << branchName_met << "'\n";

  GenParticleWriter * genLeptonWriter = nullptr;
  GenParticleWriter * genHadTauWriter = nullptr;
  GenParticleWriter * genPhotonWriter = nullptr;
  GenParticleWriter * genJetWriter = nullptr;

  GenParticleWriter * genMatchToMuonWriter = nullptr;
  GenParticleWriter * genMatchToElectronWriter = nullptr;
  GenParticleWriter * genMatchToHadTauWriter = nullptr;
  GenParticleWriter * genMatchToJetWriter = nullptr;

  if(isMC && ! readGenObjects)
  {
    genLeptonWriter = new GenParticleWriter(branchName_genLeptons);
    genLeptonWriter->setBranches(outputTree);
    std::cout << "writing GenLepton objects to branch = '" << branchName_genLeptons << "'\n";

    genHadTauWriter = new GenParticleWriter(branchName_genHadTaus);
    genHadTauWriter->setBranches(outputTree);
    std::cout << "writing GenHadTau objects to branch = '" << branchName_genHadTaus << "'\n";

    genJetWriter = new GenParticleWriter(branchName_genJets);
    genJetWriter->setBranches(outputTree);
    std::cout << "writing GenJet objects to branch = '" << branchName_genJets << "'\n";

    if(genMatchingByIndex)
    {
      genMatchToMuonWriter = new GenParticleWriter(branchName_muonGenMatch);
      genMatchToMuonWriter->setBranches(outputTree);
      std::cout << "writing gen particles matched to muons to branch = '" << branchName_muonGenMatch << "'\n";

      genMatchToElectronWriter = new GenParticleWriter(branchName_electronGenMatch);
      genMatchToElectronWriter->setBranches(outputTree);
      std::cout << "writing gen particles matched to electrons to branch = '" << branchName_electronGenMatch << "'\n";

      genMatchToHadTauWriter = new GenParticleWriter(branchName_hadTauGenMatch);
      genMatchToHadTauWriter->setBranches(outputTree);
      std::cout << "writing gen particles matched to hadronic taus to branch = '" << branchName_hadTauGenMatch << "'\n";

      genMatchToJetWriter = new GenParticleWriter(branchName_jetGenMatch);
      genMatchToJetWriter->setBranches(outputTree);
      std::cout << "writing gen jets matched to jets to branch = '" << branchName_jetGenMatch << "'\n";
    }
    else
    {
      genPhotonWriter = new GenParticleWriter(branchName_genPhotons);
      genPhotonWriter->setBranches(outputTree);
      std::cout << "writing GenPhoton objects to branch = '" << branchName_genPhotons << "'\n";
    }
  }

  // define the writer class for the nof MEM permutations
  MEMPermutationWriter memPermutationWriter;
  memPermutationWriter
    .setLepSelection       (leptonSelection, kTight)
    .setHadTauSelection    (kFakeable,       kTight)
    .setHadTauWorkingPoints(hadTauSelection_tauIDwp)
  ;
  MEMPermutationWriter memPermutationWriter_tauLess;
  memPermutationWriter_tauLess
    .setLepSelection       (leptonSelection, kTight)
  ;
  MEMPermutationWriter memPermutationWriter_hh;
  memPermutationWriter_hh
    .setLepSelection       (leptonSelection, kTight)
  ;

  // add conditions for computing the nof MEM permutations in 2lss1tau and 3l1tau channels
  // the arguments are: the name of the channel, minimum number of leptons, minimum number of hadronic taus
  memPermutationWriter
    .addCondition("2lss_1tau", 2, 1)
    .addCondition("3l_1tau",   3, 1)
  ;
  memPermutationWriter_tauLess
    .addCondition("3l",        3, 0)
  ;
  memPermutationWriter_hh
    .addCondition("hh_bb2l",   2, 0)
    .addCondition("hh_bb1l",   1, 0)
  ;
  memPermutationWriter.setBranchNames(outputTree, era, true);
  memPermutationWriter_tauLess.setBranchNames(outputTree, era, true);
  memPermutationWriter_hh.setBranchNames(outputTree, era, true);

  std::vector<std::string> outputCommands_string = {
    "keep *",
    Form("drop %s", eventInfoWriter.getBranchName_run().data()),
    Form("drop %s", eventInfoWriter.getBranchName_lumi().data()),
    Form("drop %s", eventInfoWriter.getBranchName_event().data()),
    Form("drop %s", eventInfoWriter.getBranchName_PV_ndof().data()),
    Form("drop n%s*", branchName_muons.data()),
    Form("drop %s_*", branchName_muons.data()),
    Form("drop n%s*", branchName_electrons.data()),
    Form("drop %s_*", branchName_electrons.data()),
    Form("drop n%s*", branchName_hadTaus.data()),
    Form("drop %s_*", branchName_hadTaus.data()),
    Form("drop n%s*", branchName_jets.data()),
    Form("drop %s_*", branchName_jets.data()),
    Form("drop %s_*", branchName_met.data()),
    Form("drop maxPermutations_*"),
  };
  for(const std::string & drop_branch: drop_branches)
  {
    outputCommands_string.push_back(Form("drop %s", drop_branch.data()));
  }

  for(const std::string & branchName: triggerBranches_explicitCopy)
  {
    outputCommands_string.push_back(Form("drop %s", branchName.data()));
  }

  if(isMC && ! readGenObjects)
  {
    const std::vector<std::string> outputCommands_genParticles_string_invariant = {
      Form("drop n%s", branchName_genLeptons.data()),
      Form("drop %s_*", branchName_genLeptons.data()),
      Form("drop n%s", branchName_genHadTaus.data()),
      Form("drop %s_*", branchName_genHadTaus.data()),
      Form("drop n%s", branchName_genJets.data()),
      Form("drop %s_*", branchName_genJets.data()),
    };

    std::vector<std::string> outputCommands_genParticles_string;
    if(genMatchingByIndex)
    {
      outputCommands_genParticles_string = {
        Form("drop n%s", branchName_muonGenMatch.data()),
        Form("drop %s_*", branchName_muonGenMatch.data()),
        Form("drop n%s", branchName_electronGenMatch.data()),
        Form("drop %s_*", branchName_electronGenMatch.data()),
        Form("drop n%s", branchName_hadTauGenMatch.data()),
        Form("drop %s_*", branchName_hadTauGenMatch.data()),
        Form("drop n%s", branchName_jetGenMatch.data()),
        Form("drop %s_*", branchName_jetGenMatch.data()),
      };
    }
    else
    {
      outputCommands_genParticles_string = {
        Form("drop n%s", branchName_genPhotons.data()),
        Form("drop %s_*", branchName_genPhotons.data()),
        "keep *GenMatch*",
      };
    };
    std::copy(
      outputCommands_genParticles_string_invariant.begin(), outputCommands_genParticles_string_invariant.end(),
      std::back_inserter(outputCommands_genParticles_string)
    );
    std::copy(
      outputCommands_genParticles_string.begin(), outputCommands_genParticles_string.end(),
      std::back_inserter(outputCommands_string)
    );
  }
  else
  {
    outputCommands_string.push_back("keep *GenMatch*");
  }

  std::vector<outputCommandEntry> outputCommands = getOutputCommands(outputCommands_string);
  std::map<std::string, branchEntryBaseType *> branchesToKeep; // key = branchName
  bool branchesToKeep_isInitialized = false;

  int analyzedEntries = 0;
  int selectedEntries = 0;
  cutFlowTableType cutFlowTable;
  std::string currentFile;

  while(inputTree -> hasNextEvent(branchesToKeep_isInitialized) && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    // mark branches for copying (only done once per produceNtuple job, when processing first event)
    if(! branchesToKeep_isInitialized)
    {
      const std::map<std::string, bool> isBranchToKeep = getBranchesToKeep(inputTree -> getCurrentTree(), outputCommands); // key = branchName
      copyBranches_singleType(inputTree -> getCurrentTree(), outputTree, isBranchToKeep, branchesToKeep);
      copyBranches_vectorType(inputTree -> getCurrentTree(), outputTree, isBranchToKeep, branchesToKeep);
      if(isDEBUG)
      {
        std::cout << "keeping branches:\n";
        for( const auto & branchEntry: branchesToKeep)
        {
          std::cout << ' ' << branchEntry.second->outputBranchName_ << " (type ="
                       " " << branchEntry.second->outputBranchType_string_ << ")\n"
          ;
        }
      }
      branchesToKeep_isInitialized = true;

      // now that the inputTree is properly initialized, read the event
      if(! inputTree -> hasNextEvent(true))
      {
        break;
      }
    }

    // reinitialize addresses of all branches that are copied directly from input to output file
    // in case new input file has been opened
    if(inputTree->getCurrentFileName() != currentFile)
    {
      for(auto & branch: branchesToKeep)
      {
        branch.second->setInputTree(inputTree -> getCurrentTree());
      }
      currentFile = inputTree->getCurrentFileName();
    }

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

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection");

    if(isDEBUG)
    {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

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
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon *> cleanedMuons  = muon_ptrs;
    const std::vector<const RecoMuon *> preselMuons   = preselMuonSelector  (cleanedMuons, isHigherConePt);
    const std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons,  isHigherConePt);
    const std::vector<const RecoMuon *> tightMuons    = tightMuonSelector   (preselMuons,  isHigherConePt);
    const std::vector<const RecoMuon *> selMuons      = selectObjects(
      leptonSelection, preselMuons, fakeableMuons, tightMuons
    );

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron *> cleanedElectrons  = electronCleaner(electron_ptrs, preselMuons);

    const std::vector<const RecoElectron *> preselElectronsUncleaned = preselElectronSelector  (electron_ptrs,    isHigherConePt);
    const std::vector<const RecoElectron *> preselElectrons          = preselElectronSelector  (cleanedElectrons, isHigherConePt);
    const std::vector<const RecoElectron *> fakeableElectrons        = fakeableElectronSelector(preselElectrons,  isHigherConePt);
    const std::vector<const RecoElectron *> tightElectrons           = tightElectronSelector   (preselElectrons,  isHigherConePt);

    const std::vector<const RecoElectron *> selElectrons      = selectObjects(
      leptonSelection, preselElectrons, fakeableElectrons, tightElectrons
    );

    // always used cleaned electron collection in the cleaning of had tau collection to maintain consistency with the analysis
    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau *> hadTau_ptrs = convert_to_ptrs(hadTaus);
    const std::vector<const RecoHadTau *> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    const std::vector<const RecoHadTau *> fakeableHadTaus = fakeableHadTauSelector  (cleanedHadTaus, isHigherPt);
    const std::vector<const RecoHadTau *> & selHadTaus = fakeableHadTaus;

    ObjectMultiplicity objectMultiplicity;
    objectMultiplicity.setNRecoMuon    (preselMuons.size(),     fakeableMuons.size(),     tightMuons.size());
    objectMultiplicity.setNRecoElectron(preselElectrons.size(), fakeableElectrons.size(), tightElectrons.size());
    for(const auto & kv: TauID_PyMap)
    {
      const int max_level = TauID_levels.at(kv.second);
      for(int level = 1; level <= max_level; ++level)
      {
        const RecoHadTauCollectionSelectorFakeable & hadTauSelector = *multplicityHadTauSelectors.at(kv.second).at(level);
        const std::vector<const RecoHadTau *> multiplicityHadTaus = hadTauSelector(cleanedHadTaus, isHigherPt);
        objectMultiplicity.setNRecoHadTau(kv.second, level, multiplicityHadTaus.size());
      }
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    // Karl: do not clean w.r.t the taus b/c their definition changes across the analyses
    //       we are better off if we keep a bit more jets per event;
    //       we also decided to remove cleaning w.r.t fakeable leptons, b/c the jet cleaning
    //       has now become channel-dependent (i.e. we clean w.r.t the *selected* fakeable
    //       objects, not w.r.t the whole collection)
    std::vector<const RecoJet *> selJets;
    for(const RecoJet * cleanedJet: jet_ptrs)
    {
      // Karl: there are no JEC uncertainties for non-nominal (i.e. MET-adjusted) jet pT
      const double cleanedJet_pt_max = useNonNominal_jetmet ? cleanedJet->pt() : cleanedJet->maxPt();
      const double cleanedJet_absEta = cleanedJet->absEta();
      if(cleanedJet_pt_max >= min_jetSelector_pT && (
           ((cleanedJet_absEta < max_jetSelector_absEta) && max_jetSelector_absEta > 0.) ||
             max_jetSelector_absEta <= 0.
           )
         )
      {
        selJets.push_back(cleanedJet);
      }
    }

//--- sort the collection by their pT so that if we hit the limit of maximum number of objects
//--- in the Writer classes, we will drop the softer objects
    std::sort(selJets.begin(), selJets.end(), isHigherPt);
    const std::vector<const RecoJet *> selBJets_loose  = jetSelectorBtagLoose(selJets,  isHigherPt);
    const std::vector<const RecoJet *> selBJets_medium = jetSelectorBtagMedium(selJets, isHigherPt);

    RecoMEt met = metReader->read();

//--- construct the merged lepton collections
    const std::vector<const RecoLepton *> preselLeptons   = mergeLeptonCollections(preselElectrons,   preselMuons,   isHigherConePt);
    const std::vector<const RecoLepton *> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    const std::vector<const RecoLepton *> tightLeptons    = mergeLeptonCollections(tightElectrons,    tightMuons,    isHigherConePt);
    const std::vector<const RecoLepton *> selLeptons      = mergeLeptonCollections(selElectrons,      selMuons,      isHigherConePt);

//--- apply preselection
    if(filterByTrigger && ! hltPaths_isTriggered(triggersToFilter, isDEBUG))
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event FAILS trigger selection\n";
      }
      continue;
    }

    if(! (static_cast<int>(selLeptons.size()) >= minNumLeptons))
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event FAILS selLeptons selection.\n";
        printCollection("preselLeptons", preselLeptons);
        printCollection("selLeptons", selLeptons);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i sel leptons", minNumLeptons));

    if(minNumLeptons > 0 && selLeptons.size() >= 1)
    {
      const RecoLepton * const selLepton_lead = selLeptons[0];
      // CV: lower threshold on leading lepton by 2 GeV 
      //     with respect to thresholds applied on analysis level
      //     to allow for e-ES and mu-ES uncertainties to be estimated
      const double minPt_lead = selLepton_lead -> is_electron() ? minPt_ele : minPt_mu;
      if(! (selLepton_lead->cone_pt() > minPt_lead))
      {
        if(run_lumi_eventSelector || isDEBUG)
        {
          std::cout << "event FAILS lepton pT selection.\n"
                       "( leading selLepton "
                       "pT = "         << selLepton_lead->cone_pt() << ", "
                       "minPt_lead = " << minPt_lead << ")\n"
          ;
        }
        continue;
      }
      cutFlowTable.update(Form("lead lepton pT > %.1f (electron) / %.1f (muon) GeV", minPt_ele, minPt_mu));
    }

    if(! (static_cast<int>(selHadTaus.size()) >= minNumHadTaus))
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event FAILS selHadTaus selection\n";
        printCollection("fakeableHadTaus", fakeableHadTaus);
        printCollection("selHadTaus", selHadTaus);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i sel hadTaus", minNumHadTaus));

    if (! (static_cast<int>(selLeptons.size() + selHadTaus.size()) >= minNumLeptons_and_HadTaus))
    {
      continue;
    }
    cutFlowTable.update(Form(">= %i sel leptons+hadTaus", minNumLeptons_and_HadTaus));

    // apply requirement on jets 
    if(! (static_cast<int>(selJets.size()) >= minNumJets))
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event FAILS selJets selection\n";
        printCollection("selJets", selJets);
      }
      continue;
    }
    cutFlowTable.update(Form(">= %i jets", minNumJets));

    // apply requirement on b-jets 
    if(! (static_cast<int>(selBJets_loose.size())  >= minNumBJets_loose  ||
          static_cast<int>(selBJets_medium.size()) >= minNumBJets_medium ||
          ((maxNumBJets_loose >= 0  && static_cast<int>(selBJets_loose.size())  <= maxNumBJets_loose)  || maxNumBJets_loose < 0) ||
          ((maxNumBJets_medium >= 0 && static_cast<int>(selBJets_medium.size()) <= maxNumBJets_medium) || maxNumBJets_medium < 0)))
    {
      if(run_lumi_eventSelector || isDEBUG)
      {
        std::cout << "event FAILS selBJets selection\n";
        printCollection("selJets",         selJets);
        printCollection("selBJets_loose",  selBJets_loose);
        printCollection("selBJets_medium", selBJets_medium);
      }
      continue;
    }
    cutFlowTable.update(Form(
      ">= %i..%i loose b-jets || %i..%i medium b-jet",
      minNumBJets_loose, maxNumBJets_loose, minNumBJets_medium, maxNumBJets_medium
    ));

    if(isMC && ! readGenObjects)
    {
      const std::vector<GenLepton> genLeptons = genLeptonReader->read();
      const std::vector<GenHadTau> genHadTaus = genHadTauReader->read();
      const std::vector<GenJet>    genJets    = genJetReader->read();

      genLeptonWriter->write(convert_to_GenParticle(genLeptons));
      genHadTauWriter->write(convert_to_GenParticle(genHadTaus));
      genJetWriter   ->write(convert_to_GenParticle(genJets));

      if(genMatchingByIndex)
      {
        const std::vector<GenParticle> muonGenMatch     = genMatchToMuonReader->read();
        const std::vector<GenParticle> electronGenMatch = genMatchToElectronReader->read();
        const std::vector<GenParticle> hadTauGenMatch   = genMatchToHadTauReader->read();
        const std::vector<GenParticle> jetGenMatch      = genMatchToJetReader->read();

        genMatchToMuonWriter     -> write(muonGenMatch);
        genMatchToElectronWriter -> write(electronGenMatch);
        genMatchToHadTauWriter   -> write(hadTauGenMatch);
        genMatchToJetWriter      -> write(jetGenMatch);

        muonGenMatcher.addGenLeptonMatchByIndex(preselMuons, muonGenMatch, GenParticleType::kGenMuon);
        muonGenMatcher.addGenHadTauMatch       (preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch          (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatchByIndex(preselElectronsUncleaned, electronGenMatch, GenParticleType::kGenElectron);
        electronGenMatcher.addGenPhotonMatchByIndex(preselElectronsUncleaned, electronGenMatch);
        electronGenMatcher.addGenHadTauMatch       (preselElectronsUncleaned, genHadTaus);
        electronGenMatcher.addGenJetMatch          (preselElectronsUncleaned, genJets);

        hadTauGenMatcher.addGenLeptonMatchByIndex(selHadTaus, hadTauGenMatch, GenParticleType::kGenAnyLepton);
        hadTauGenMatcher.addGenHadTauMatch       (selHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch          (selHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch     (selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch     (selJets, genHadTaus);
        jetGenMatcher.addGenJetMatchByIndex (selJets, jetGenMatch);
      }
      else
      {
        const std::vector<GenPhoton> genPhotons = genPhotonReader->read();
        genPhotonWriter->write(convert_to_GenParticle(genPhotons));

        std::vector<GenLepton> genElectrons;
        std::vector<GenLepton> genMuons;

        for(const GenLepton & genLepton: genLeptons)
        {
          const int genLeptonType = getLeptonType(genLepton.pdgId());
          switch(genLeptonType)
          {
            case kElectron: genElectrons.push_back(genLepton); break;
            case kMuon:     genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }

        muonGenMatcher.addGenLeptonMatch(preselMuons, genMuons);
        muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch   (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatch(preselElectronsUncleaned, genElectrons);
        electronGenMatcher.addGenPhotonMatch(preselElectronsUncleaned, genPhotons);
        electronGenMatcher.addGenHadTauMatch(preselElectronsUncleaned, genHadTaus);
        electronGenMatcher.addGenJetMatch(preselElectronsUncleaned, genJets);

        hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons);
        hadTauGenMatcher.addGenHadTauMatch  (selHadTaus, genHadTaus);
        hadTauGenMatcher.addGenJetMatch  (selHadTaus, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets, genLeptons);
        jetGenMatcher.addGenHadTauMatch     (selJets, genHadTaus);
        jetGenMatcher.addGenJetMatch(selJets, genJets);
      }
    }

    memPermutationWriter.write(
      {{preselLeptons, fakeableLeptons, tightLeptons}}, {{selBJets_loose, selBJets_medium}}, cleanedHadTaus
    );
    memPermutationWriter_tauLess.write(
      {{preselLeptons, fakeableLeptons, tightLeptons}}, {{selBJets_loose, selBJets_medium}}, cleanedHadTaus
    );
    memPermutationWriter_hh.write(
      {{preselLeptons, fakeableLeptons, tightLeptons}}, {{selBJets_loose, selBJets_medium}}, cleanedHadTaus
    );

    eventInfoWriter.write(eventInfo);
    objectMultiplicityWriter.write(objectMultiplicity);
    hltPathWriter_instance.write(triggers);
    muonWriter->write(preselMuons);
    electronWriter->write(preselElectronsUncleaned);
    hadTauWriter->write(fakeableHadTaus);
    jetWriter->write(selJets);
    metWriter->write(met);

    for(const auto & branchEntry: branchesToKeep)
    {
      branchEntry.second->copyBranch();
    }

    outputTree->Fill();
    ++selectedEntries;
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << "\n\n"
            << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  if(isDEBUG)
  {
    std::cout << "output Tree:\n";
    outputTree->Print();
  }

  for(auto & kv: multplicityHadTauSelectors)
  {
    for(auto & kw: kv.second)
    {
      delete kw.second;
      kw.second = nullptr;
    }
  }

  delete run_lumi_eventSelector;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;

  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;

  delete muonWriter;
  delete electronWriter;
  delete hadTauWriter;
  delete jetWriter;
  delete metWriter;

  delete genLeptonWriter;
  delete genHadTauWriter;
  delete genPhotonWriter;
  delete genJetWriter;

  for(hltPath * trigger: triggers)
  {
    delete trigger;
  }

  for(auto & branches: branchesToKeep)
  {
    delete branches.second;
  }

//--- copy histograms keeping track of number of processed events from input files to output file
  std::cout << "copying histograms:\n";
  delete inputTree;
  std::smatch histogram_match;
  std::map<std::string, TH1 *> histograms;
  for(const std::string & inputFileName: inputFiles.files())
  {
    TFile * const inputFile = new TFile(inputFileName.data());
    if(! inputFile)
    {
      throw cmsException("produceNtuple", __LINE__)
        << "Failed to open input File = '" << inputFileName << '\''
      ;
    }
    TIter next(inputFile->GetListOfKeys());
    TKey * key = nullptr;
    while((key = static_cast<TKey *>(next())))
    {
      const std::string histogramName = key->GetName();
      bool is_match = false;
      for(const std::regex & copy_histogram_regex: copy_histograms_regex)
      {
        if(std::regex_match(histogramName, histogram_match, copy_histogram_regex))
        {
          is_match = true;
          break;
        }
      }
      if(! is_match)
      {
        continue;
      }

      if(inputFiles.files().size() > 1)
      {
        std::cout << ' ' << histogramName << " from input File = '" << inputFileName << "'\n";
      }
      else
      {
        std::cout << ' ' << histogramName << '\n';
      }
      TH1 * const histogram_input = dynamic_cast<TH1 *>(inputFile->Get(histogramName.data()));
      if(! histogram_input)
      {
        continue;
      }

      TH1 * histogram_output = histograms[histogramName];
      if(histogram_output)
      {
        histogram_output->Add(histogram_input);
      }
      else
      {
        if(dynamic_cast<TH1F *>(histogram_input))
        {
          histogram_output = fs.make<TH1F>(*(dynamic_cast<TH1F *>(histogram_input)));
        }
        else if(dynamic_cast<TH1D*>(histogram_input))
        {
          histogram_output = fs.make<TH1D>(*(dynamic_cast<TH1D *>(histogram_input)));
        }
        assert(histogram_output);
        histograms[histogramName] = histogram_output;
      }
    }
    delete inputFile;
  }

  clock.Show("produceNtuple");
  return EXIT_SUCCESS;
}
