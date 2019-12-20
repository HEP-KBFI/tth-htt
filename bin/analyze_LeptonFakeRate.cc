#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenMEtReader.h" // GenMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelectorBtag/Loose
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector

#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h" // DYMCReweighting
#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h" // DYMCNormScaleFactors

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017, getBTagWeight_option()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // get*_option()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverflow
#include "tthAnalysis/HiggsToTauTau/interface/leptonFakeRateAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h" // hltPath_LeptonFakeRate, create_hltPaths_LeptonFakeRate(), hltPaths_LeptonFakeRate_delete()
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin(), getPtBin()
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon

#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles

#include <TRandom3.h> // TRandom3
#include <TBenchmark.h> // TBenchmark
#include <TH1.h> // TH1, TH1D
#include <TMath.h> // TMath::Pi()
#include <TROOT.h> // TROOT
#include <Math/Vector3D.h> // Needed for ROOT::Math::XYZVector

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/predicate.hpp> // boost::starts_with(), boost::ends_with()

#include <fstream> // std::ofstream

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

int
main(int argc,
     char ** argv)
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- stop ROOT from keeping track of all histograms
  TH1::AddDirectory(false);

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_LeptonFakeRate>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- initialize RNG
  TRandom3 rand(12345);

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1];
  }

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_LeptonFakeRate");
  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tHq = process_string == "tHq";
  const bool isMC_tHW = process_string == "tHW";
  const bool isMC_tH = isMC_tHq || isMC_tHW;
  const bool isSignal = process_string == "ttH" || process_string == "ttH_ctcvcp";

  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);
  const bool isMC    = cfg_analyze.getParameter<bool>("isMC");
  const bool hasLHE  = cfg_analyze.getParameter<bool>("hasLHE");
  const bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");

  const std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  const bool apply_genWeight            = cfg_analyze.getParameter<bool>("apply_genWeight");
  const bool apply_DYMCReweighting      = cfg_analyze.getParameter<bool>("apply_DYMCReweighting");
  const bool apply_DYMCNormScaleFactors = cfg_analyze.getParameter<bool>("apply_DYMCNormScaleFactors");
  const bool apply_l1PreFireWeight      = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  const bool fillGenEvtHistograms       = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  const bool jetCleaningByIndex         = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  const bool redoGenMatching            = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex         = cfg_analyze.getParameter<bool>("genMatchingByIndex");
  const bool readGenObjects             = isMC && ! redoGenMatching;
  const bool isDEBUG                    = cfg_analyze.getParameter<bool>("isDEBUG");
  const bool apply_met_filters          = cfg_analyze.getParameter<bool>("apply_met_filters");
  const double min_PV_ndof              = cfg_analyze.getParameter<double>("min_PV_ndof");
  
  const vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  const vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  const vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  const vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");

  const bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  const bool use_triggers_2e  = cfg_analyze.getParameter<bool>("use_triggers_2e");
  const bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  const bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");

  const edm::VParameterSet cfg_triggers_e = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_e;
  if(use_triggers_1e || use_triggers_2e)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_e)
    {
      const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
      const bool is_trigger_1e = cfg_trigger.getParameter<bool>("is_trigger_1e");
      const bool is_trigger_2e = cfg_trigger.getParameter<bool>("is_trigger_2e");
      assert(is_trigger_1e || is_trigger_2e);

      if(! ((is_trigger_1e && use_triggers_1e) ||(is_trigger_2e && use_triggers_2e)))
      {
        std::cout << "Skipping electron HLT path = '" << trigger_path << "'\n";
        continue;
      }

      if((is_trigger_1e && std::find(triggerNames_1e.begin(), triggerNames_1e.end(), trigger_path) == triggerNames_1e.end()) ||
         (is_trigger_2e && std::find(triggerNames_2e.begin(), triggerNames_2e.end(), trigger_path) == triggerNames_2e.end())  )
      {
        std::cout << "HLT path '" << trigger_path << "' is not in the list of available electron HLT paths\n";
        continue;
      }

      std::cout << "Selecting electron HLT path = '" << trigger_path << "'\n";
      const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
      triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end());
    }
  }

  const edm::VParameterSet cfg_triggers_mu = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_mu;
  if(use_triggers_1mu || use_triggers_2mu)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_mu)
    {
      const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
      const bool is_trigger_1mu = cfg_trigger.getParameter<bool>("is_trigger_1mu");
      const bool is_trigger_2mu = cfg_trigger.getParameter<bool>("is_trigger_2mu");
      assert(is_trigger_1mu || is_trigger_2mu);

      if(!((is_trigger_1mu && use_triggers_1mu) ||(is_trigger_2mu && use_triggers_2mu)))
      {
        std::cout << "Skipping muon HLT path = '" << trigger_path << "'\n";
        continue;
      }

      if((is_trigger_1mu && std::find(triggerNames_1mu.begin(), triggerNames_1mu.end(), trigger_path) == triggerNames_1mu.end()) ||
         (is_trigger_2mu && std::find(triggerNames_2mu.begin(), triggerNames_2mu.end(), trigger_path) == triggerNames_2mu.end())  )
      {
        std::cout << "HLT path '" << trigger_path << "' is not in the list of available muon HLT paths\n";
        continue;
      }

      std::cout << "Selecting muon HLT path = '" << trigger_path << "'\n";
      const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
      triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end());
    }
  }

  // sort HLT paths by reco pT thresholds in descending order (from higher pT threshold to lowest)
  std::sort(triggers_e.begin(),  triggers_e.end(),  isHigherMinRecoPt);
  std::sort(triggers_mu.begin(), triggers_mu.end(), isHigherMinRecoPt);

  const vdouble etaBins_e  = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  const vdouble ptBins_e   = cfg_analyze.getParameter<vdouble>("ptBins_e");
  const vdouble etaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  const vdouble ptBins_mu  = cfg_analyze.getParameter<vdouble>("ptBins_mu");

  const double minConePt_global_e  = cfg_analyze.getParameter<double>("minConePt_global_e");
  const double minConePt_global_mu = cfg_analyze.getParameter<double>("minConePt_global_mu");
  const double minRecoPt_global_e  = cfg_analyze.getParameter<double>("minRecoPt_global_e");
  const double minRecoPt_global_mu = cfg_analyze.getParameter<double>("minRecoPt_global_mu");

  const double lep_mva_cut_mu = cfg_analyze.getParameter<double>("lep_mva_cut_mu");
  const double lep_mva_cut_e  = cfg_analyze.getParameter<double>("lep_mva_cut_e");
  const double METScaleSyst   = cfg_analyze.getParameter<double>("METScaleSyst");

  
  const std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_jets      = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_analyze.getParameter<std::string>("branchName_met");
  const std::string branchName_genmet       = cfg_analyze.getParameter<std::string>("branchName_genmet");

  const std::string branchName_genTauLeptons = cfg_analyze.getParameter<std::string>("branchName_genTauLeptons");
  const std::string branchName_genLeptons    = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  const std::string branchName_genHadTaus    = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genPhotons    = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  const std::string branchName_genJets       = cfg_analyze.getParameter<std::string>("branchName_genJets");

  const std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  const std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  const std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  const edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  const MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);

  const std::string selEventsFileName_input = cfg_analyze.exists("selEventsFileName_input") ?
                                              cfg_analyze.getParameter<std::string>("selEventsFileName_input") : ""
  ;
  std::cout << "selEventsFileName_input = '" << selEventsFileName_input << "'\n";
  RunLumiEventSelector * run_lumi_eventSelector = nullptr;
  if(! selEventsFileName_input.empty())
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator",     ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  const bool writeTo_selEventsFileOut = ! selEventsFileName_output.empty();
  std::map<std::string, std::map<std::string, std::ofstream *>> outputFiles;
  for(const std::string & emu_str: { "e", "mu" })
  {
    for(const std::string & numden_str: { "num", "den" })
    {
      outputFiles[emu_str][numden_str] = writeTo_selEventsFileOut ?
        new std::ofstream(Form(selEventsFileName_output.data(), emu_str.data(), numden_str.data())) :
        nullptr
      ;
    }
  }

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift);
  }

  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option       = getJet_option(central_or_shift, isMC);
  const int met_option         = getMET_option(central_or_shift, isMC);
  const int hadTauPt_option    = getHadTauPt_option(central_or_shift);
  const METSyst metSyst_option = getMETsyst_option(central_or_shift);

  std::cout
    << "central_or_shift = "    << central_or_shift           << "\n"
       " -> met_option      = " << met_option                 << "\n"
       " -> metSyst_option  = " << as_integer(metSyst_option) << "\n"
       " -> jetPt_option    = " << jetPt_option               << "\n"
       " -> hadTauPt_option = " << hadTauPt_option            << '\n'
  ;

  DYMCReweighting * dyReweighting = nullptr;
  if(apply_DYMCReweighting)
  {
    dyReweighting = new DYMCReweighting(era);
  }
  DYMCNormScaleFactors * dyNormScaleFactors = nullptr;
  if(apply_DYMCNormScaleFactors)
  {
    dyNormScaleFactors = new DYMCNormScaleFactors(era);
  }

  fwlite::InputSource inputFiles(cfg);
  const int maxEvents        = inputFiles.maxEvents();
  const unsigned reportEvery = inputFiles.reportAfter();

  TTreeWrapper * inputTree = new TTreeWrapper(treeName, inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s).\n";

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

//--- declare event-level variables
  EventInfo eventInfo(isMC);
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isSignal) && ! tHweights.empty())
  {
    eventInfo.set_central_or_shift(central_or_shift);
    eventInfo.loadWeight_tH(tHweights);
  }
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  ObjectMultiplicity objectMultiplicity;
  ObjectMultiplicityReader objectMultiplicityReader(&objectMultiplicity);
  if(useObjectMultiplicity)
  {
    inputTree -> registerReader(&objectMultiplicityReader);
  }

  std::vector<hltPath_LeptonFakeRate *> triggers_all;
  triggers_all.insert(triggers_all.end(), triggers_e.begin(), triggers_e.end());
  triggers_all.insert(triggers_all.end(), triggers_mu.begin(), triggers_mu.end());

  std::vector<hltPath *> triggers;
  triggers.insert(triggers.end(), triggers_e.begin(), triggers_e.end());
  triggers.insert(triggers.end(), triggers_mu.begin(), triggers_mu.end());
  hltPathReader hltPathReader_instance(triggers);
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

  L1PreFiringWeightReader * l1PreFiringWeightReader = nullptr;
  if(apply_l1PreFireWeight)
  {
    l1PreFiringWeightReader = new L1PreFiringWeightReader(era);
    inputTree->registerReader(l1PreFiringWeightReader);
  }

//--- declare particle collections
  RecoMuonReader * muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);
  fakeableMuonSelector.getSelector().set_mvaTTH_wp(lep_mva_cut_mu);
  tightMuonSelector.getSelector().set_min_mvaTTH(lep_mva_cut_mu);

  RecoElectronReader * electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  fakeableElectronSelector.getSelector().set_mvaTTH_wp(lep_mva_cut_e);
  fakeableElectronSelector.enable_offline_e_trigger_cuts();
  tightElectronSelector.enable_offline_e_trigger_cuts();
  tightElectronSelector.getSelector().set_min_mvaTTH(lep_mva_cut_e);

  RecoJetReader * jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics(central_or_shift != "central" && isMC);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner_dR04(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7, isDEBUG); // Christian's suggestion
  RecoJetCollectionSelector jetSelector(era);
  jetSelector.getSelector().set_min_pt(30.);
  jetSelector.getSelector().set_max_absEta(2.4);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader * metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

//--- declare MET filter
  MEtFilter metFilter;
  MEtFilterReader * metFilterReader = new MEtFilterReader(&metFilter, era);
  inputTree->registerReader(metFilterReader);

// --- Setting up the Met Filter Hist Manager ----
  const edm::ParameterSet metFilterHistManagerCfg = makeHistManager_cfg(process_string, "LeptonFakeRate/met_filters", era_string, central_or_shift);
  MEtFilterHistManager * metFilterHistManager = new MEtFilterHistManager(metFilterHistManagerCfg);
  metFilterHistManager->bookHistograms(fs);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenJetReader * genJetReader       = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  LHEInfoReader * lheInfoReader     = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  GenParticleReader * genMatchToJetReader      = nullptr;
  GenMEtReader * genmetReader  = nullptr;

  if(isMC)
  {
    if(! readGenObjects)
    {
      genLeptonReader = new GenLeptonReader(branchName_genLeptons);
      inputTree->registerReader(genLeptonReader);
      genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
      inputTree->registerReader(genHadTauReader);
      genJetReader = new GenJetReader(branchName_genJets);
      inputTree->registerReader(genJetReader);

      if(genMatchingByIndex)
      {
        genMatchToMuonReader = new GenParticleReader(branchName_muonGenMatch);
        genMatchToMuonReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToMuonReader);

        genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
        genMatchToElectronReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToElectronReader);

        genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
        genMatchToJetReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToJetReader);
      }
      else
      {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree->registerReader(genPhotonReader);
      }
    }
    genmetReader = new GenMEtReader(era, isMC, branchName_genmet); 
    inputTree->registerReader(genmetReader);
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree->registerReader(lheInfoReader);
  }

  GenParticleReader * genTauLeptonReader = nullptr;
  if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
  {
    genTauLeptonReader = new GenParticleReader(branchName_genTauLeptons);
    inputTree->registerReader(genTauLeptonReader);
  }

  const auto get_num_den_hist_managers =
    [&process_string, isMC, &era_string, &central_or_shift](const std::string & dir,
                                                            int lepton_type,
                                                            double minAbsEta = -1.,
                                                            double maxAbsEta = -1.,
                                                            double minPt = -1.,
                                                            double maxPt = -1.,
                                                            const std::string & subdir_suffix = "")
    -> numerator_and_denominatorHistManagers * const
  {
    return new numerator_and_denominatorHistManagers(
      process_string, isMC, era_string, central_or_shift, Form("LeptonFakeRate/%s", dir.data()),
      lepton_type, minAbsEta, maxAbsEta, minPt, maxPt, subdir_suffix
    );
  };

//--- book histograms for electron numerator and denominator
  auto histograms_e_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/electrons_tight", kElectron);
  histograms_e_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/electrons_fakeable", kElectron);
  histograms_e_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/electrons_tight", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/electrons_fakeable", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_afterCuts;
  const int numEtaBins_e = etaBins_e.size() - 1;
  const int numPtBins_e  = ptBins_e.size()  - 1;

  for(int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e)
  {
    const double minAbsEta_e = std::abs(etaBins_e[idxEtaBin_e]);
    const double maxAbsEta_e = std::abs(etaBins_e[idxEtaBin_e + 1]);

    for(int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e)
    {
      const double minPt_e = ptBins_e[idxPtBin_e];
      const double maxPt_e = ptBins_e[idxPtBin_e + 1];

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_e_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_e_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_e_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_e_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book histograms for muon numerator and denominator
  auto histograms_mu_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/muons_tight", kMuon);
  histograms_mu_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/muons_fakeable", kMuon);
  histograms_mu_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/muons_tight", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/muons_fakeable", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_afterCuts;
  const int numEtaBins_mu = etaBins_mu.size() - 1;
  const int numPtBins_mu  = ptBins_mu.size()  - 1;

  for(int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu)
  {
    const double minAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu]);
    const double maxAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu + 1]);

    for(int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu)
    {
      const double minPt_mu = ptBins_mu[idxPtBin_mu];
      const double maxPt_mu = ptBins_mu[idxPtBin_mu + 1];

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book generator-level histograms for MC
  GenEvtHistManager * genEvtHistManager_beforeCuts = nullptr;
  GenEvtHistManager * genEvtHistManager_afterCuts  = nullptr;
  LHEInfoHistManager * lheInfoHistManager          = nullptr;
  if(isMC)
  {
    const auto getHistManagerCfg = [&process_string, &era_string, &central_or_shift](const std::string & dir)
      -> edm::ParameterSet
    {
      return makeHistManager_cfg(process_string, Form("LeptonFakeRate/%s", dir.data()), era_string, central_or_shift);
    };
    genEvtHistManager_beforeCuts = new GenEvtHistManager(getHistManagerCfg("gen_unbiased/genEvt"));
    genEvtHistManager_beforeCuts->bookHistograms(fs);

    genEvtHistManager_afterCuts = new GenEvtHistManager(getHistManagerCfg("gen_sel/genEvt"));
    genEvtHistManager_afterCuts->bookHistograms(fs);

    lheInfoHistManager = new LHEInfoHistManager(getHistManagerCfg("gen_sel/lheInfo"));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

//--- book additional event level histograms
  TH1 * histogram_met_pt  = fs.make<TH1D>("met_pt",  "met_pt",   40, 0., 200.);
  TH1 * histogram_met_phi = fs.make<TH1D>("met_phi", "met_phi",  36, -TMath::Pi(), +TMath::Pi());
  

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1 * histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1 * histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

  cutFlowTableType cutFlowTable_e(isDEBUG);
  initializeCutFlowTable(cutFlowTable_e, ">= 1 presel/Loose electron");
  if(apply_met_filters)
  {
    initializeCutFlowTable(cutFlowTable_e, "MEt filter");
  }
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_afterCuts);

  cutFlowTableType cutFlowTable_mu(isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu, ">= 1 presel/Loose muon");
  if(apply_met_filters)
  {
    initializeCutFlowTable(cutFlowTable_mu, "MEt filter");
  }
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, "mT_fix(muon, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_afterCuts);

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1) << " ("
                << eventInfo << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if(isDEBUG)
    {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(kLoose) != 1)
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }

    if(eventInfo.PV_ndof <= min_PV_ndof)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS PV ndof > " << min_PV_ndof << "cut \n";
      }
      continue;
    }

//--- build collections of generator level particles (before any cuts are applied,
//    to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;

    std::vector<GenParticle> muonGenMatch;
    std::vector<GenParticle> electronGenMatch;
    std::vector<GenParticle> jetGenMatch;
    if(isMC && fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }
  
//--- fill generator level histograms (before cuts)
    EvtWeightRecorder evtWeightRecorder({central_or_shift}, central_or_shift, isMC);
    std::vector<GenParticle> genTauLeptons;
    if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
    {
      genTauLeptons = genTauLeptonReader->read();
    }
    if(isMC)
    {
      if(apply_genWeight)         evtWeightRecorder.record_genWeight(boost::math::sign(eventInfo.genWeight));
      if(apply_DYMCReweighting)   evtWeightRecorder.record_dy_rwgt(dyReweighting, genTauLeptons);
      if(eventWeightManager)      evtWeightRecorder.record_auxWeight(eventWeightManager);
      if(l1PreFiringWeightReader) evtWeightRecorder.record_l1PrefireWeight(l1PreFiringWeightReader);
      lheInfoReader->read();
      evtWeightRecorder.record_lheScaleWeight(lheInfoReader);
      evtWeightRecorder.record_puWeight(&eventInfo);
      evtWeightRecorder.record_nom_tH_weight(&eventInfo);
      evtWeightRecorder.record_lumiScale(lumiScale);

      genEvtHistManager_beforeCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(
          eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift)
        );
      }
    }

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon *> preselMuons = preselMuonSelector(cleanedMuons); // Loose muons
    std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon *> tightMuons = tightMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron *> preselElectrons = preselElectronSelector(cleanedElectrons); // Loose electrons
    std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron *> tightElectrons = tightElectronSelector(preselElectrons);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet *> cleanedJets_dR04 = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableMuons, fakeableElectrons) :
      jetCleaner_dR04  (jet_ptrs, fakeableMuons, fakeableElectrons)
    ; // changed from presel to be in sync with the analysis channels
    std::vector<const RecoJet *> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);
    std::vector<const RecoJet *> selJets_dR04 = jetSelector(cleanedJets_dR04);
    std::vector<const RecoJet *> cleanedJets_dR07 = jetCleaner_dR07(jet_ptrs, fakeableMuons, fakeableElectrons); // changed from presel to be in sync with the analysis channels
    std::vector<const RecoJet *> selJets_dR07 = jetSelector(cleanedJets_dR07);

    const RecoMEt met = metReader->read();
    GenMEt genmet_tmp = GenMEt(0.,0.); // There is no MET Covariance stored in Ntuples
    if(isMC && (genmetReader != nullptr)){
      genmet_tmp = genmetReader->read();
    }

    const GenMEt genmet = genmet_tmp;    

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if(isMC && redoGenMatching && ! fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }
  
//--- match reconstructed to generator level particles
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        muonGenMatcher.addGenLeptonMatchByIndex(preselMuons, muonGenMatch, GenParticleType::kGenMuon);
        muonGenMatcher.addGenHadTauMatch       (preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch          (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatchByIndex(preselElectrons, electronGenMatch, GenParticleType::kGenElectron);
        electronGenMatcher.addGenPhotonMatchByIndex(preselElectrons, electronGenMatch);
        electronGenMatcher.addGenHadTauMatch       (preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch          (preselElectrons, genJets);

        jetGenMatcher.addGenLeptonMatch    (selJets_dR07, genLeptons);
        jetGenMatcher.addGenHadTauMatch    (selJets_dR07, genHadTaus);
        jetGenMatcher.addGenJetMatchByIndex(selJets_dR07, jetGenMatch);
      }
      else
      {
        muonGenMatcher.addGenLeptonMatch(preselMuons, genMuons);
        muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch   (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatch(preselElectrons, genElectrons);
        electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons);
        electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch   (preselElectrons, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets_dR07, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets_dR07, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets_dR07, genJets);
      }
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "Event Particle Collection Info\n";
      printCollection("preselElectrons", preselElectrons);
      printCollection("preselMuons", preselMuons);
      printCollection("uncleaned jets", jet_ptrs);
      printCollection("selJets_dR07", selJets_dR07);
    }
  
//--- require exactly one Loose lepton
    if((preselElectrons.size() + preselMuons.size()) != 1) // Giovanni's pre-selection
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS (presel.e + presel.mu != 1) cut\n";
      }
      continue;
    }

    if(preselElectrons.size() >= 1) cutFlowTable_e.update (">= 1 presel/Loose electron", evtWeightRecorder.get(central_or_shift));
    if(preselMuons.size()     >= 1) cutFlowTable_mu.update(">= 1 presel/Loose muon",     evtWeightRecorder.get(central_or_shift));
  
    if(apply_met_filters)
      {
        metFilterHistManager->fillHistograms(metFilter, evtWeightRecorder.get(central_or_shift));
        if(! metFilterSelector(metFilter))
          {
            if(run_lumi_eventSelector)
              {
                std::cout << "event " << eventInfo.str() << " FAILS MEtFilter\n";
              }
            continue;
          }
        cutFlowTable_e.update ("MEt filter", evtWeightRecorder.get(central_or_shift));
        cutFlowTable_mu.update("MEt filter", evtWeightRecorder.get(central_or_shift));
      }

    bool isTriggered_1e = false;
    bool isTriggered_2e = false;
    bool isTriggered_1mu = false;
    bool isTriggered_2mu = false;

    bool isGoodLeptonJetPair = false; // set to true if at least one electron+jet or one muon+jet combination passes trigger requirements
    bool isGoodMuonJetPair = false;
    bool isGoodElectronJetPair = false;
    std::vector<const RecoJet *> cleanedJets;
    std::vector<const RecoJet *> selJets;
    std::vector<const RecoJet*> selBJets_loose;
    std::vector<const RecoJet*> selBJets_medium;

    // muon block
    // loop over triggers_mu (given in descendng order of thresholds in the config)
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_mu)
    {
      hltPath_iter->setIsTriggered(false); // resetting the bool to false

      if(! (hltPath_iter->getValue() >= 1))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS this mu trigger " << *hltPath_iter << '\n';
        }
        continue; // require trigger to fire
      }

      for(const RecoMuon * const preselMuon_ptr: preselMuons)
      {
        const RecoMuon & preselMuon = *preselMuon_ptr;

        // Giovanni's selection for global lepton reco and cone pt cuts
        if(!(preselMuon.cone_pt() > minConePt_global_mu && preselMuon.pt() > minRecoPt_global_mu))
        {
          if(run_lumi_eventSelector)
          {
            std::cout << "event " << eventInfo.str() << " FAILS global muon cone and reco pt cuts\n";
          }
          continue;
        }

        const std::vector<const RecoMuon*> tmp_leptons = { preselMuon_ptr };
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);
        selBJets_loose = jetSelectorBtagLoose(cleanedJets);
        selBJets_medium = jetSelectorBtagMedium(cleanedJets);

        for(const RecoJet * const selJet: selJets)
        {
          if(deltaR(preselMuon.p4(), selJet->p4()) <= 0.7)
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "jet FAILS deltaR(presel. mu, sel-jet) > 0.7 cut\n"
                           "deltaR(preselMuon.p4(), selJet->p4()) " << deltaR(preselMuon.p4(), selJet->p4())
                        << '\n';
            }
            continue;
          }

          if(!( preselMuon.cone_pt() >= hltPath_iter->getMinPt()    &&
                preselMuon.cone_pt() <  hltPath_iter->getMaxPt()    &&
                selJet->pt()         >  hltPath_iter->getMinJetPt() &&
                preselMuon.pt()      >  hltPath_iter->getMinRecoPt()))
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "Muon + jet pair FAILS trigger dep. Pt cuts "                      << "\n"
                           "preselMuon.cone_pt() = "          << preselMuon.cone_pt()         << "\n"
                           "hltPath_iter->getMinPt() = "      << hltPath_iter->getMinPt()     << "\n"
                           "hltPath_iter->getMaxPt() = "      << hltPath_iter->getMaxPt()     << "\n"
                           "selJet->pt() = "                  << selJet->pt()                 << "\n"
                           "Trigger Min. Jet pT = "           << hltPath_iter->getMinJetPt()  << "\n"
                           "preselMuon.pt() = "               << preselMuon.pt()              << "\n"
                           "Trigger Min. Reco Muon pT cut = " << hltPath_iter->getMinRecoPt() << '\n'
              ;
            }
            continue;
          }
          else
          {
            hltPath_iter->setIsTriggered(true);
            isGoodMuonJetPair = true;
            isGoodLeptonJetPair = true;
            break;
          }
        }
      }

      if(hltPath_iter->isTriggered())
      {
        isTriggered_2mu |= hltPath_iter->is_trigger_2mu();
        isTriggered_1mu |= hltPath_iter->is_trigger_1mu();
      }
    }

    // electron block
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_e)
    {
      hltPath_iter->setIsTriggered(false); // resetting the bool to false 

      if(! (hltPath_iter->getValue() >= 1))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS this e trigger " << *hltPath_iter << '\n';
        }
        continue; // require trigger to fire
      }

      for(const RecoElectron * const preselElectron_ptr: preselElectrons)
      {
        const RecoElectron & preselElectron = *preselElectron_ptr;

        // Giovanni's selection for global lepton reco and cone pt cuts
        if(!(preselElectron.cone_pt() > minConePt_global_e && preselElectron.pt() > minRecoPt_global_e))
        {
          if(run_lumi_eventSelector)
          {
            std::cout << "presel Electron FAILS global reco pt and cone pt cuts\n"
                         "minConePt_global_e " << minConePt_global_e << " "
                         "minRecoPt_global_e " << minRecoPt_global_e << '\n'
            ;
          }
          continue;
        }

        const std::vector<const RecoElectron *> tmp_leptons = { preselElectron_ptr };
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);

        for(const RecoJet * const selJet: selJets)
        {
          if(deltaR(preselElectron.p4(), selJet->p4()) <= 0.7)
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "jet FAILS deltaR(presel. e, sel-jet) > 0.7 cut\n"
                           "deltaR(preselElectron.p4(), selJet->p4()) " << deltaR(preselElectron.p4(), selJet->p4())
                        << '\n'
              ;
            }
            continue;
          }


          if(!(preselElectron.cone_pt() >= hltPath_iter->getMinPt()    &&
               preselElectron.cone_pt() <  hltPath_iter->getMaxPt()    &&
               selJet->pt()             >  hltPath_iter->getMinJetPt() &&
               preselElectron.pt()      > hltPath_iter->getMinRecoPt() ))
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "electron + jet pair FAILS trigger dep. Pt cuts "                      << "\n"
                           "preselElectron.cone_pt() = "           << preselElectron.cone_pt()    << "\n"
                           "hltPath_iter->getMinPt() = "          << hltPath_iter->getMinPt()     << "\n"
                           "hltPath_iter->getMaxPt() = "          << hltPath_iter->getMaxPt()     << "\n"
                           "selJet->pt() = "                      << selJet->pt()                 << "\n"
                           "Trigger Min. Jet pT cut = "           << hltPath_iter->getMinJetPt()  << "\n"
                           "preselElectron.pt() = "               << preselElectron.pt()          << "\n"
                           "Trigger Min. Reco Electron pT cut = " << hltPath_iter->getMinRecoPt() << '\n'
              ;
            }
            continue;
          }
          else
          {
            hltPath_iter->setIsTriggered(true);
            isGoodElectronJetPair = true; // set to true as soon as we find a jet matching all the above criteria
            isGoodLeptonJetPair = true;
            break;
          }
        } // loop over selJets ends
      } // loop over preselElectrons ends

      if(hltPath_iter->isTriggered())
      {
        isTriggered_2e |= hltPath_iter->is_trigger_2e();
        isTriggered_1e |= hltPath_iter->is_trigger_1e();
      }
    }

    const bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    const bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    const bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    const bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;

    if(! (selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu))
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n ("
                     "selTrigger_1e = "  << selTrigger_1e  << ", "
                     "selTrigger_2e = "  << selTrigger_2e  << ", "
                     "selTrigger_1mu = " << selTrigger_1mu << ", "
                     "selTrigger_2mu = " << selTrigger_2mu << ")\n"
        ;
      }
      continue;
    }


    //--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
    //    the ranking of the triggers is as follows: 2mu, 2e, 1mu, 1e
    // CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if(! isMC && ! isDEBUG)
    {
      if(selTrigger_1e && (isTriggered_1mu || isTriggered_2e || isTriggered_2mu))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_1e = "   << selTrigger_1e   << ", "
                       "isTriggered_2e = "  << isTriggered_2e  << ", "
                       "isTriggered_1mu = " << isTriggered_1mu << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
      if(selTrigger_1mu && (isTriggered_2e || isTriggered_2mu))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_1mu = "  << selTrigger_1mu  << ", "
                       "isTriggered_2e = "  << isTriggered_2e  << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
      if(selTrigger_2e && isTriggered_2mu)
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_2e = "   << selTrigger_2e   << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
    }

    // prescale weight
    if(isMC)
    {
      if(apply_DYMCNormScaleFactors)
      {
        evtWeightRecorder.record_dy_norm(
          dyNormScaleFactors, genTauLeptons, selJets.size(), selBJets_loose.size(), selBJets_medium.size()
        );
      }
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);

      double prob_all_trigger_fail = 1.0;
      for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_all)
      {
        if(hltPath_iter->isTriggered())
        {
          prob_all_trigger_fail *= (1. - (1. / hltPath_iter->getPrescale()));
        }
      }
      evtWeightRecorder.record_prescale(1.0 - prob_all_trigger_fail);
    }


    // fill histograms for muons
    for(const RecoMuon * const preselMuon_ptr: preselMuons) // loop over preselMuons
    {
      if(! isGoodMuonJetPair)
      {
        break;
      }
      const RecoMuon & preselMuon = *preselMuon_ptr; 
      const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselMuon_ptr, genmet, met, METScaleSyst, metSyst_option, isDEBUG);
      const double mT     = comp_mT    (preselMuon, met_mod.pt(), met_mod.phi());
      const double mT_fix = comp_mT_fix(preselMuon, met_mod.pt(), met_mod.phi());
      if(isDEBUG) {
	std::cout<< "mT (nominal) " << comp_mT(preselMuon, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT_fix (nominal) " << comp_mT_fix(preselMuon, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT " << mT_fix << std::endl;
	std::cout<< "mT_fix " << mT_fix << std::endl;
      }
      // numerator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      // denominator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;

      if(preselMuon.isTight())
      {
        // muon enters the numerator
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
        }
        histograms_incl_beforeCuts_num = histograms_mu_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_mu_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_mu_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_mu_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["mu"]["num"]) << eventInfo.str() << '\n' ;
        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
      {
        histograms_incl_beforeCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);

        if(mT_fix < 15.)
        {
          cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);
        }
      }

      if(preselMuon.isFakeable() && !(preselMuon.isTight())) // applying (isFakeable && !(isTight)) condition [TALLINN METHOD]
      //if(preselMuon.isFakeable())                          // applying (isFakeable) condition [GIOVANNI'S METHOD]
      {
        // muon enters denominator (fakeable)
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "denominator filled\n";
        }
        histograms_incl_beforeCuts_den = histograms_mu_denominator_incl_beforeCuts;
        histograms_incl_afterCuts_den  = histograms_mu_denominator_incl_afterCuts;
        histograms_binned_beforeCuts_den = &histograms_mu_denominator_binned_beforeCuts;
        histograms_binned_afterCuts_den  = &histograms_mu_denominator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["mu"]["den"]) << eventInfo.str() << '\n';
        }
      }

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
        histograms_incl_beforeCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);

        if(mT_fix < 15.)
        {
          cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);
        }
      }
    }
    

    // fill histograms for electrons
    for(const RecoElectron * const preselElectron_ptr: preselElectrons) // loop over preselElectrons
    {
      if(!isGoodElectronJetPair)
      {
        break;
      }
      const RecoElectron & preselElectron = *preselElectron_ptr; 
      const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselElectron_ptr, genmet, met, METScaleSyst, metSyst_option, isDEBUG);
      const double mT     = comp_mT    (preselElectron, met_mod.pt(), met_mod.phi());
      const double mT_fix = comp_mT_fix(preselElectron, met_mod.pt(), met_mod.phi());
      if(isDEBUG) {
	std::cout<< "mT (nominal) " << comp_mT(preselElectron, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT_fix (nominal) " << comp_mT_fix(preselElectron, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT " << mT_fix << std::endl;
	std::cout<< "mT_fix " << mT_fix << std::endl;
      }
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;


      if(preselElectron.isTight())
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
        }
        // electron enters numerator
        histograms_incl_beforeCuts_num = histograms_e_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_e_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_e_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_e_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["e"]["num"]) << eventInfo.str() <<  '\n';
        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
      {
        histograms_incl_beforeCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);
        }
      }


      if(preselElectron.isFakeable() && !(preselElectron.isTight())) // applying (isFakeable && !(isTight)) condition [TALLINN METHOD]
      //if(preselElectron.isFakeable())                              // applying (isFakeable) condition [GIOVANNI'S METHOD]
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "denominator filled\n";
        }
        // electron enters denominator (fakeable but not tight)
        histograms_incl_beforeCuts_den = histograms_e_denominator_incl_beforeCuts;
        histograms_incl_afterCuts_den  = histograms_e_denominator_incl_afterCuts;
        histograms_binned_beforeCuts_den = &histograms_e_denominator_binned_beforeCuts;
        histograms_binned_afterCuts_den  = &histograms_e_denominator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["e"]["den"]) << eventInfo.str() << '\n';
        }
      }

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
        histograms_incl_beforeCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);
        }
      }
    }

    if(! isGoodLeptonJetPair)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS as "
                     "there is no preselected lepton+jet pair in the event satisfying all requirements\n"
        ;
      }
      continue;
    }

    fillWithOverFlow(histogram_met_pt,  met.pt(),  evtWeightRecorder.get(central_or_shift));
    fillWithOverFlow(histogram_met_phi, met.phi(), evtWeightRecorder.get(central_or_shift));

//--- fill generator level histograms (after cuts)
    if(isMC)
    {
      genEvtHistManager_afterCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeightRecorder.get(central_or_shift));
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift));
      }
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeightRecorder.get(central_or_shift);
    histogram_selectedEntries->Fill(0.);
    if(isDEBUG)
    {
      std::cout << evtWeightRecorder << '\n';
    }
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") "
               "processed in " << inputTree -> getProcessedFileCount() << " file(s) "
               "(out of "      << inputTree -> getFileCount()          << ")\n"
               " analyzed = "  << analyzedEntries                      << "\n"
               " selected = "  << selectedEntries
            << " (weighted = " << selectedEntries_weighted << ")\n\n"
               "cut-flow table for electron events\n" << cutFlowTable_e  << "\n"
               "cut-flow table for muon events\n"     << cutFlowTable_mu << '\n';

//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete muonReader;
  delete electronReader;
  delete jetReader;
  delete metReader;
  delete genmetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;
  delete metFilterReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete metFilterHistManager;
  delete l1PreFiringWeightReader;
  delete eventWeightManager;

  hltPaths_LeptonFakeRate_delete(triggers_e);
  hltPaths_LeptonFakeRate_delete(triggers_mu);

  delete histograms_e_numerator_incl_beforeCuts;
  delete histograms_e_denominator_incl_beforeCuts;
  delete histograms_e_numerator_incl_afterCuts;
  delete histograms_e_denominator_incl_afterCuts;
  delete histograms_mu_numerator_incl_beforeCuts;
  delete histograms_mu_denominator_incl_beforeCuts;
  delete histograms_mu_numerator_incl_afterCuts;
  delete histograms_mu_denominator_incl_afterCuts;

  for(const std::vector<numerator_and_denominatorHistManagers *> & histVector:
      {
        histograms_e_numerator_binned_beforeCuts,
        histograms_e_denominator_binned_beforeCuts,
        histograms_e_numerator_binned_afterCuts,
        histograms_e_denominator_binned_afterCuts,
        histograms_mu_numerator_binned_beforeCuts,
        histograms_mu_denominator_binned_beforeCuts,
        histograms_mu_numerator_binned_afterCuts,
        histograms_mu_denominator_binned_afterCuts
      })
  {
    for(numerator_and_denominatorHistManagers * hist: histVector)
    {
      delete hist;
    }
  }

  delete inputTree;

  for(auto & kv: outputFiles)
  {
    for(auto & kv2: kv.second)
    {
      if(kv2.second)
      {
        *kv2.second << std::flush;
        delete kv2.second;
      }
    }
  }

  delete run_lumi_eventSelector;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
} // main func ends
