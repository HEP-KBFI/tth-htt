#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet
#include <FWCore/Utilities/interface/Exception.h> // cms::Exception
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles
#include <DataFormats/Math/interface/LorentzVector.h> // math::PtEtaPhiMLorentzVector

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TEfficiency.h>
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::
#include <TH2.h> // TH2
#include <TROOT.h> // TROOT

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_charge_flip.h" // EvtHistManager_charge_flip
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h" // DYMCReweighting
#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h" // DYMCNormScaleFactors
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder
#include "tthAnalysis/HiggsToTauTau/interface/BtagSFRatioFacility.h" // BtagSFRatioFacility
#include "tthAnalysis/HiggsToTauTau/interface/AnalysisConfig.h" // AnalysisConfig

#include "hhAnalysis/multilepton/interface/RecoElectronCollectionSelectorFakeable_hh_multilepton.h" // RecoElectronCollectionSelectorFakeable_hh_multilepton
#include "hhAnalysis/multilepton/interface/RecoMuonCollectionSelectorFakeable_hh_multilepton.h" // RecoMuonCollectionSelectorFakeable_hh_multilepton

#include <iostream> // std::cerr, std::fixed
#include <cstring> // std::strncpm
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

const int printLevel = 0;

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton };

int getBinIdx_pT_and_absEta(double pT, double absEta)
{
  /* map pT and abs(eta) to binIndex
    "BL": 1
    "BM": 2
    "BH": 3
    "EL": 4
    "EM": 5
    "EH": 6*/
  int idxBin = 0;
  if ( absEta > 1.479 ) idxBin += 3;
  if      ( pT >= 10. && pT < 25. ) idxBin += 1;
  else if ( pT >= 25. && pT < 50. ) idxBin += 2;
  else if ( pT >= 50.             ) idxBin += 3;        
  else idxBin = 0;
  return idxBin;
}

/**
 * @brief Produce histograms for the charge flip background.
 */
int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- stop ROOT from keeping track of all histograms
  TH1::AddDirectory(false);

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
  AnalysisConfig analysisConfig("ttH->multilepton+tau", cfg_analyze);
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tHq = process_string == "tHq";
  const bool isMC_tHW = process_string == "tHW";
  const bool isMC_tH = isMC_tHq || isMC_tHW;
  const bool isSignal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  bool isZee = (std::strncmp(process_string.data(), "DY", 2) == 0);
  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const Era era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  
  enum { kLoose, kFakeable, kTight };
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection");
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("analyze_charge_flip")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  bool isCentral = ( central_or_shift == "central" ) ? true : false;
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_DYMCReweighting = cfg_analyze.getParameter<bool>("apply_DYMCReweighting");
  bool apply_DYMCNormScaleFactors = cfg_analyze.getParameter<bool>("apply_DYMCNormScaleFactors");
  std::string apply_topPtReweighting_str = cfg_analyze.getParameter<std::string>("apply_topPtReweighting");
  bool apply_topPtReweighting = ! apply_topPtReweighting_str.empty();
  bool apply_l1PreFireWeight = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  bool apply_btagSFRatio = cfg_analyze.getParameter<bool>("applyBtagSFRatio");

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");

  const double lep_mva_cut_mu = cfg_analyze.getParameter<double>("lep_mva_cut_mu");
  const double lep_mva_cut_e  = cfg_analyze.getParameter<double>("lep_mva_cut_e");
  const std::string lep_mva_wp = cfg_analyze.getParameter<std::string>("lep_mva_wp");
  printf("lep_mva_wp %s, lep_mva_cut_mu %g, lep_mva_cut_e %g \n",
	 lep_mva_wp.c_str(),lep_mva_cut_mu,lep_mva_cut_e);

  if ( ! cfg_analyze.exists("lep_useTightChargeCut") )
  {
    throw cms::Exception("analyze_WZctrl_SFstudy")
      << " Missing input parameter lep_useTightChargeCut !!\n";
  }
  const bool lep_useTightChargeCut = cfg_analyze.exists("lep_useTightChargeCut") ? cfg_analyze.getParameter<bool>("lep_useTightChargeCut") : true;
  printf("lep_useTightChargeCut %d \n",lep_useTightChargeCut);

  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift);
  }

  edm::ParameterSet triggerWhiteList;
  if(! isMC)
  {
    triggerWhiteList = cfg_analyze.getParameter<edm::ParameterSet>("triggerWhiteList");
  }

  checkOptionValidity(central_or_shift, isMC);
  const ElectronPtSys electronPt_option = getElectronPt_option(central_or_shift, isMC);
  const int jetPt_option                = getJet_option       (central_or_shift, isMC);
  const int met_option                  = getMET_option       (central_or_shift, isMC);
    
  std::cout
    << "central_or_shift = "      << central_or_shift              << "\n"
       " -> jetPt_option      = " << jetPt_option                  << "\n"
       " -> met_option        = " << met_option                    << "\n"
       " -> electronPt_option = " << as_integer(electronPt_option) << '\n'
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

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", "disabled");
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("lep_mva_wp", lep_mva_wp);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case Era::k2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case Era::k2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case Era::k2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_charge_flip", __LINE__) << "Invalid era = " << static_cast<int>(era);
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else throw cms::Exception("analyze_charge_flip") 
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  
  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    cfg_leptonFakeRateWeight.addParameter<std::string>("era", era_string);
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");

  std::string branchName_genTauLeptons = cfg_analyze.getParameter<std::string>("branchName_genTauLeptons");
  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");

  bool jetCleaningByIndex = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");
  bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

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

  TTreeWrapper* inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s)." << std::endl;

//--- declare event-level variables
  EventInfo eventInfo(analysisConfig);
  if(isMC)
  {
    const double ref_genWeight = cfg_analyze.getParameter<double>("ref_genWeight");
    eventInfo.set_refGetWeight(ref_genWeight);
  }
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isSignal) && ! tHweights.empty())
  {
    eventInfo.set_central_or_shift(central_or_shift);
    eventInfo.loadWeight_tH(tHweights);
  }
  EventInfoReader eventInfoReader(&eventInfo);
  if(apply_topPtReweighting)
  {
    eventInfoReader.setTopPtRwgtBranchName(apply_topPtReweighting_str);
  }
  inputTree->registerReader(&eventInfoReader);

  ObjectMultiplicity objectMultiplicity;
  ObjectMultiplicityReader objectMultiplicityReader(&objectMultiplicity);
  if(useObjectMultiplicity)
  {
    inputTree -> registerReader(&objectMultiplicityReader);
  }

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_2e });
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

  BtagSFRatioFacility * btagSFRatioFacility = nullptr;
  if(apply_btagSFRatio)
  {
    const edm::ParameterSet btagSFRatio = cfg_analyze.getParameterSet("btagSFRatio");
    btagSFRatioFacility = new BtagSFRatioFacility(btagSFRatio);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector_default(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable_hh_multilepton fakeableMuonSelector_hh_multilepton(era, -1, isDEBUG);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);
  muonReader->set_mvaTTH_wp(lep_mva_cut_mu);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher(isDEBUG);
  RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector_default(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable_hh_multilepton fakeableElectronSelector_hh_multilepton(era, -1, isDEBUG);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  electronReader->set_mvaTTH_wp(lep_mva_cut_e);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics(central_or_shift != "central" && isMC);
  inputTree->registerReader(jetReader);
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);

  GenParticleReader* genTauLeptonReader = nullptr;
  if ( isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors)) {
    genTauLeptonReader = new GenParticleReader(branchName_genTauLeptons);
    inputTree->registerReader(genTauLeptonReader);
  }

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  GenJetReader * genJetReader = nullptr;
  LHEInfoReader * lheInfoReader = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  if(isMC)
  {
    if(! readGenObjects)
    {
      genLeptonReader = new GenLeptonReader(branchName_genLeptons);
      inputTree -> registerReader(genLeptonReader);
      genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
      inputTree -> registerReader(genHadTauReader);
      genJetReader = new GenJetReader(branchName_genJets);
      inputTree -> registerReader(genJetReader);

      if(genMatchingByIndex)
      {
        genMatchToMuonReader = new GenParticleReader(branchName_muonGenMatch);
        genMatchToMuonReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToMuonReader);

        genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
        genMatchToElectronReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToElectronReader);
      }
      else
      {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree -> registerReader(genPhotonReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  std::string charge_and_leptonSelectionSS = Form("%s_%s", "SS", leptonSelection_string.data());
  std::string charge_and_leptonSelectionOS = Form("%s_%s", "OS", leptonSelection_string.data());
  ElectronHistManager preselElectronHistManagerSS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionSS.data()), era_string, central_or_shift, "allHistograms"));
  preselElectronHistManagerSS.bookHistograms(fs);
  ElectronHistManager preselElectronHistManagerOS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionOS.data()), era_string, central_or_shift, "allHistograms"));
  preselElectronHistManagerOS.bookHistograms(fs);

  EvtHistManager_charge_flip evtHistManager(makeHistManager_cfg(process_string,
    "", era_string, central_or_shift));
  evtHistManager.bookHistograms(fs);
  EvtHistManager_charge_flip* evtHistManager_DY_fake = 0;
  if ( isZee ) {
    evtHistManager_DY_fake = new EvtHistManager_charge_flip(makeHistManager_cfg("DY_fake",
      "", era_string, central_or_shift));
    evtHistManager_DY_fake->bookHistograms(fs);
  }

  EvtHistManager_charge_flip* evtHistManager_DY_genCategory = 0;
  EvtHistManager_charge_flip* evtHistManager_DY_recCategory = 0;
  if ( isZee ) {
    evtHistManager_DY_genCategory = new EvtHistManager_charge_flip(makeHistManager_cfg("DY",
      "gen", era_string, central_or_shift));
    evtHistManager_DY_genCategory->bookHistograms(fs);
    evtHistManager_DY_recCategory = new EvtHistManager_charge_flip(makeHistManager_cfg("DY",
      "gen_rec", era_string, central_or_shift));
    evtHistManager_DY_recCategory->bookHistograms(fs);
  } 

  const int numBins_absEta = 2;
  Double_t binning_absEta[numBins_absEta + 1] = { 0., 1.479, 2.5 };
  const int numBins_pT = 3;
  Double_t binning_pT[numBins_pT + 1] = { 10., 25., 50., 1000. };

  TH2* histogram_gen_OS = 0;
  TH2* histogram_gen_SS = 0;
  TEfficiency* histogram_prob_charge_flip_gen = 0;
  TEfficiency* histogram_prob_charge_flip_gen_rec = 0;
  TH2* histogram_idxBin_pT_and_eta_rec_vs_gen = 0;
  TH2* histogram_idxBin_pT_and_eta_rec_vs_gen_OS = 0;
  TH2* histogram_idxBin_pT_and_eta_rec_vs_gen_SS = 0;
  if ( isZee && central_or_shift == "central" ) {
    TDirectory* subdir_gen = createSubdirectory_recursively(fs, "gen_ratio/DY", false);
    subdir_gen->cd();
    histogram_gen_OS = new TH2D("pt_eta_OS", "pt_eta_OS", numBins_pT, binning_pT, numBins_absEta, binning_absEta);
    histogram_gen_OS->Sumw2();
    histogram_gen_SS = new TH2D("pt_eta_SS", "pt_eta_SS", numBins_pT, binning_pT, numBins_absEta, binning_absEta);
    histogram_gen_SS->Sumw2();
    histogram_prob_charge_flip_gen = new TEfficiency("pt_eta_DY", "pt_eta;pT;#eta;charge_misID", numBins_pT, binning_pT, numBins_absEta, binning_absEta);
    histogram_prob_charge_flip_gen->SetUseWeightedEvents();
    histogram_prob_charge_flip_gen->SetStatisticOption(TEfficiency::kFNormal);
    histogram_prob_charge_flip_gen_rec = new TEfficiency("pt_eta_DY_rec", "pt_eta;pT;#eta;charge_misID", numBins_pT, binning_pT, numBins_absEta, binning_absEta);
    histogram_prob_charge_flip_gen_rec->SetUseWeightedEvents();
    histogram_prob_charge_flip_gen_rec->SetStatisticOption(TEfficiency::kFNormal);
    histogram_idxBin_pT_and_eta_rec_vs_gen = new TH2D("transfer_matrix", "transfer_matrix", 6, 0.5, 6.5, 6, 0.5, 6.5);
    histogram_idxBin_pT_and_eta_rec_vs_gen->Sumw2();
    histogram_idxBin_pT_and_eta_rec_vs_gen_OS = new TH2D("transfer_matrix_flip", "transfer_matrix_flip", 6, 0.5, 6.5, 6, 0.5, 6.5);
    histogram_idxBin_pT_and_eta_rec_vs_gen_OS->Sumw2();
    histogram_idxBin_pT_and_eta_rec_vs_gen_SS = new TH2D("transfer_matrix_noflip", "transfer_matrix_noflip", 6, 0.5, 6.5, 6, 0.5, 6.5);
    histogram_idxBin_pT_and_eta_rec_vs_gen_SS->Sumw2();
  }

  TH2* histogram_pT_gen_vs_rec_meeAbove100_ePtAvobe50 = 0;
  TH2* histogram_pT_gen_vs_rec_meeAbove100_BBHH = 0;
  TH2* histogram_pT_gen_vs_rec_meeAbove100_EEHH = 0;
  TH2* histogram_pT_gen_vs_rec_meeAbove100_BEHH = 0;
  if ( isZee && central_or_shift == "central" ) {
    TDirectory* subdir = createSubdirectory_recursively(fs, "DY", false);
    subdir->cd();
    histogram_pT_gen_vs_rec_meeAbove100_ePtAvobe50 = new TH2D("pT_gen_vs_rec_meeAbove100_ePtAvobe50", "pT_gen_vs_rec_meeAbove100_ePtAvobe50", 200,0,200, 200,0,200);
    histogram_pT_gen_vs_rec_meeAbove100_BBHH = new TH2D("pT_gen_vs_rec_meeAbove100_BBHH", "pT_gen_vs_rec_meeAbove100_BBHH", 200,0,200, 200,0,200);
    histogram_pT_gen_vs_rec_meeAbove100_EEHH = new TH2D("pT_gen_vs_rec_meeAbove100_EEHH", "pT_gen_vs_rec_meeAbove100_EEHH", 200,0,200, 200,0,200);
    histogram_pT_gen_vs_rec_meeAbove100_BEHH = new TH2D("pT_gen_vs_rec_meeAbove100_BEHH", "pT_gen_vs_rec_meeAbove100_BEHH", 200,0,200, 200,0,200);    
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/unbiased/genEvt", charge_and_leptonSelectionSS.data()), era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/genEvt", charge_and_leptonSelectionSS.data()), era_string, central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/lheInfo", charge_and_leptonSelectionSS.data()), era_string, central_or_shift));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }


  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  const edm::ParameterSet cutFlowTableCfg = makeHistManager_cfg(
    process_string, Form("charge_flip_%s/sel/cutFlow", charge_and_leptonSelectionSS.data()), era_string, central_or_shift
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "object multiplicity",
    "trigger",
    "trigger 1e",
    "trigger 2e",
    "trigger 1e && 2e",
    "= 2 presel electrons",
    "presel electron trigger match",
    "= 0 presel muons",
    "= 2 sel electrons",
    "sel electron trigger match",
    "lead electron pT > 25 GeV && sublead electron pT > 10 GeV",
    "tight electron charge",
    "60 < m(ee) < 120 GeV",
    "selectedEvt_1eTrig",
    "selectedEvt_2eTrig",
    "selectedEvt 1e && 2eTrig",
  };
  CutFlowTableHistManager * cutFlowHistManager = new CutFlowTableHistManager(cutFlowTableCfg, cuts);
  cutFlowHistManager->bookHistograms(fs);

  while ( inputTree->hasNextEvent() && (!run_lumi_eventSelector || (run_lumi_eventSelector && !run_lumi_eventSelector->areWeDone())) ) {
    if ( inputTree->canReport(reportEvery) ) {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    if ( isCentral ) {
      histogram_analyzedEntries->Fill(0.);
    }
    EvtWeightRecorder evtWeightRecorder({central_or_shift}, central_or_shift, isMC);
    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo) ) {
      continue;
    }
    cutFlowTable.update("run:ls:event selection", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("run:ls:event selection", evtWeightRecorder.get(central_or_shift));

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoElectron(leptonSelection) != 2)
      {
        if(isDEBUG)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }
    cutFlowTable.update("object multiplicity", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("object multiplicity", evtWeightRecorder.get(central_or_shift));

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;

    std::vector<GenParticle> muonGenMatch;
    std::vector<GenParticle> electronGenMatch;
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
    }

    std::vector<GenParticle> genTauLeptons;
    if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
    {
      genTauLeptons = genTauLeptonReader->read();
    }

    if(isMC)
    {
      if(apply_genWeight)         evtWeightRecorder.record_genWeight(eventInfo);
      if(apply_DYMCReweighting)   evtWeightRecorder.record_dy_rwgt(dyReweighting, genTauLeptons);
      if(eventWeightManager)      evtWeightRecorder.record_auxWeight(eventWeightManager);
      if(l1PreFiringWeightReader) evtWeightRecorder.record_l1PrefireWeight(l1PreFiringWeightReader);
      if(apply_topPtReweighting)  evtWeightRecorder.record_toppt_rwgt(eventInfo.topPtRwgtSF);
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

    const bool isTriggered_1e = hltPaths_isTriggered(triggers_1e, triggerWhiteList, eventInfo, isMC);
    const bool isTriggered_2e = hltPaths_isTriggered(triggers_2e, triggerWhiteList, eventInfo, isMC);
    
    const bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    const bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    if ( !(selTrigger_1e || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl; 
	std::cout << " (selTrigger_1e = " << isTriggered_1e 
		  << ", selTrigger_2e = " << isTriggered_2e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("trigger", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("trigger", evtWeightRecorder.get(central_or_shift));

    if (selTrigger_1e) {
      cutFlowTable.update("trigger 1e", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("trigger 1e", evtWeightRecorder.get(central_or_shift));
    }
    if (selTrigger_2e) {
      cutFlowTable.update("trigger 2e", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("trigger 2e", evtWeightRecorder.get(central_or_shift));
    }
    if (selTrigger_1e && selTrigger_2e) {
      cutFlowTable.update("trigger 1e && 2e", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("trigger 1e && 2e", evtWeightRecorder.get(central_or_shift));
    }

    if ( (selTrigger_2e && !apply_offline_e_trigger_cuts_2e) ||
	 (selTrigger_1e && !apply_offline_e_trigger_cuts_1e) ) {
      fakeableElectronSelector_default.disable_offline_e_trigger_cuts();
      fakeableElectronSelector_hh_multilepton.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      fakeableElectronSelector_default.enable_offline_e_trigger_cuts();
      fakeableElectronSelector_hh_multilepton.enable_offline_e_trigger_cuts();
      tightElectronSelector.enable_offline_e_trigger_cuts();
    } 

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
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    const std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    const std::vector<const RecoMuon*> fakeableMuons = lep_mva_wp == "hh_multilepton" ?
      fakeableMuonSelector_hh_multilepton(preselMuons) :
      fakeableMuonSelector_default(preselMuons)
    ;
    const std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    const std::vector<const RecoMuon*> selMuons = selectObjects(
      leptonSelection, preselMuons, fakeableMuons, tightMuons
    );

//--- match reconstructed muons to generator level particles
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        muonGenMatcher.addGenLeptonMatchByIndex(preselMuons, muonGenMatch, GenParticleType::kGenMuon);
        muonGenMatcher.addGenHadTauMatch       (preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch          (preselMuons, genJets);
      }
      else
      {
        muonGenMatcher.addGenLeptonMatch(preselMuons, genMuons);
        muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch   (preselMuons, genJets);
      }
    }

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);

//--- match reconstructed electrons to generator level particles
//    we need to find the gen matches of cleaned electrons instead of loose electrons because shifts in energy resolution
//    change the acceptance of the loose selection, and gen matching can modify the energy resolution
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        electronGenMatcher.addGenLeptonMatchByIndex(cleanedElectrons, electronGenMatch, GenParticleType::kGenElectron);
        electronGenMatcher.addGenPhotonMatchByIndex(cleanedElectrons, electronGenMatch);
        electronGenMatcher.addGenHadTauMatch       (cleanedElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch          (cleanedElectrons, genJets);
      }
      else
      {
        // Some of the electron pT may be carried away by bremsstrahlung photon at the generator level. Altough
        // the bremsstrahlung photon is included in the reconstruction of the electron, the generator level
        // electrons that are considered in the gen matching are final state electrons which have already undergone
        // bremsstrahlung. This is not accounted for in NanoAOD and has to be corrected for the purpose of this
        // analysis. The solution here is to redo the gen matching between reconstructed and gen electrons by allowing
        // the pT of reconstructed electrons to be four times as high as the pT of gen electrons for them to be gen-matched.
        // This matches with the previous implementation of our gen-matching, where we required the ratio of gen pT
        // to reco pT be greater than 0.25.
        electronGenMatcher.addGenLeptonMatch(cleanedElectrons, genElectrons, 0.3, -0.5, 3.00);
        electronGenMatcher.addGenPhotonMatch(cleanedElectrons, genPhotons);
        electronGenMatcher.addGenHadTauMatch(cleanedElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch   (cleanedElectrons, genJets);
      }
    }
    const std::vector<const RecoElectron*> electrons_shifted = recompute_p4(cleanedElectrons, electronPt_option);
    const std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(electrons_shifted);
    const std::vector<const RecoElectron*> fakeableElectrons = lep_mva_wp == "hh_multilepton" ?
        fakeableElectronSelector_hh_multilepton(preselElectrons) :
        fakeableElectronSelector_default(preselElectrons)
    ;
    const std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    const std::vector<const RecoElectron*> selElectrons = selectObjects(
      leptonSelection, preselElectrons, fakeableElectrons, tightElectrons
    );

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> cleanedJets = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableMuons, fakeableElectrons) :
      jetCleaner       (jet_ptrs, fakeableMuons, fakeableElectrons)
    ;
    const std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    const std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets, isHigherPt);
    const std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);

//--- apply preselection
    
    // require exactly two preselected electrons
    if ( !(preselElectrons.size() == 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS 2 presel Electrons selection" << std::endl; 
	std::cout << " #preselElectrons = " << preselElectrons.size() 
		  << std::endl;
      }
      continue;
    }
    cutFlowTable.update("= 2 presel electrons", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("= 2 presel electrons", evtWeightRecorder.get(central_or_shift));
    
    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !(selTrigger_1e || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("presel electron trigger match", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("presel electron trigger match", evtWeightRecorder.get(central_or_shift));

    // require exactly zero preselected muons
    if ( !(preselMuons.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS 0 presel Muons selection" << std::endl; 
	std::cout << " (#preselMuons = " << preselMuons.size() 
		  << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("= 0 presel muons", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("= 0 presel muons", evtWeightRecorder.get(central_or_shift));

//--- apply final event selection

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
      continue;
    }
    cutFlowTable.update("= 2 sel electrons", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("= 2 sel electrons", evtWeightRecorder.get(central_or_shift));

    // require that trigger paths match event category (with event category based on selLeptons);
    if ( selElectrons.size() == 2 && !(selTrigger_1e || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selElectron multiplicity." << std::endl; 
	std::cout << " (#selElectrons = " << selElectrons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel electron trigger match", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("sel electron trigger match", evtWeightRecorder.get(central_or_shift));


    // Require that trigger paths match primary datasets,
    // to avoid that the same event is selected multiple times when processing different primary datasets (PD).
    // In case the same event passes the triggers paths for more than one primary datasets,
    // the event is selected in the PD of highest priority only. 
    // The ranking of the PDs is as follows: DoubleMuon, MuonEG, DoubleEG, SingleMuon, SingleElectron
    if ( !isMC && !isDEBUG ) 
    {
      //bool isTriggered_SingleElectron = isTriggered_1e && fakeableElectrons.size() >= 1;
      bool isTriggered_DoubleEG = isTriggered_2e && fakeableElectrons.size() >= 2;

      bool selTrigger_SingleElectron = selTrigger_1e;
      //bool selTrigger_DoubleEG = selTrigger_2e;

      if ( selTrigger_SingleElectron && isTriggered_DoubleEG && era != Era::k2018 ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_SingleElectron = " << selTrigger_SingleElectron
                    << ", isTriggered_DoubleEG = " << isTriggered_DoubleEG << ")" << std::endl;
        }
        continue;
      }
    }              
    cutFlowTable.update("trigger & dataset matching", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("trigger & dataset matching", evtWeightRecorder.get(central_or_shift));

    
    const RecoElectron * selElectron_lead = selElectrons[0];
    const GenLepton * genElectron_lead = nullptr;
    if(selElectron_lead->genLepton() && abs(selElectron_lead->genLepton()->pdgId()) == 11)
    {
      genElectron_lead = selElectron_lead->genLepton();
    }
    const double selElectron_lead_pT = selElectron_lead->pt();
    const double selElectron_lead_eta = selElectron_lead->eta();
    const double selElectron_lead_absEta = std::fabs(selElectron_lead_eta);

    const RecoElectron * selElectron_sublead = selElectrons[1];
    const GenLepton * genElectron_sublead = nullptr;
    if(selElectron_sublead->genLepton() && abs(selElectron_sublead->genLepton()->pdgId()) == 11)
    {
      genElectron_sublead = selElectron_sublead->genLepton();
    }
    const double selElectron_sublead_pT = selElectron_sublead->pt();
    const double selElectron_sublead_eta = selElectron_sublead->eta();
    const double selElectron_sublead_absEta = std::fabs(selElectron_sublead_eta);

    const math::PtEtaPhiMLorentzVector selElectron_lead_p4 = selElectron_lead->p4();
    const math::PtEtaPhiMLorentzVector selElectron_sublead_p4 = selElectron_sublead->p4();
    const double selElectron_lead_charge = selElectron_lead->charge();
    Particle::LorentzVector genElectron_lead_p4; // generator-level electron associated to the reconstructed electron of higher pT 
                                                 // (not necessarily the generator-level electron of higher pT!)
    double genElectron_lead_charge = 0.;
    bool isGenElectron_lead = false;
    if ( genElectron_lead ) {
      genElectron_lead_p4 = genElectron_lead->p4();
      genElectron_lead_charge = genElectron_lead->charge();
      isGenElectron_lead = true;
    }
    const double selElectron_sublead_charge = selElectron_sublead->charge();
    Particle::LorentzVector genElectron_sublead_p4; // generator-level electron associated to the reconstructed electron of lower pT 
                                                    // (not necessarily the generator-level electron of lower pT!)
    double genElectron_sublead_charge = 0.;
    bool isGenElectron_sublead = false;
    if ( genElectron_sublead ) {
      genElectron_sublead_p4 = genElectron_sublead->p4();
      genElectron_sublead_charge = genElectron_sublead->charge();
      isGenElectron_sublead = true;
    }

    const double m_ee = (selElectron_lead_p4 + selElectron_sublead_p4).mass();
    
    const double minPt_lead = 20.;
    const double minPt_sublead = 10.;
    if ( !(selElectron_lead_pT > minPt_lead && selElectron_sublead_pT > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selElectron_lead_p4.pt() << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selElectron_sublead_p4.pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead electron pT > 20 GeV && sublead electron pT > 10 GeV", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("lead electron pT > 20 GeV && sublead electron pT > 10 GeV", evtWeightRecorder.get(central_or_shift));
    
    bool failsTightChargeCut = false;
    for ( std::vector<const RecoElectron*>::const_iterator electron = selElectrons.begin();
	  electron != selElectrons.end(); ++electron ) {
      if ( (*electron)->tightCharge() < 2 ) failsTightChargeCut = true;
    }
    if ( failsTightChargeCut && lep_useTightChargeCut ) {
      if ( run_lumi_eventSelector ) {
      	std::cout << "event FAILS tight lepton charge requirement." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("tight electron charge", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("tight electron charge", evtWeightRecorder.get(central_or_shift));

    if ( !(m_ee > 60. && m_ee < 120.) ) {
      if ( run_lumi_eventSelector ) {
      	std::cout << "event FAILS mass window requirement." << std::endl;
      }
      continue; 
    }

    cutFlowTable.update("60 < m(ee) < 120 GeV", evtWeightRecorder.get(central_or_shift));
    cutFlowHistManager->fillHistograms("60 < m(ee) < 120 GeV", evtWeightRecorder.get(central_or_shift));

    if (selTrigger_1e) {
      cutFlowTable.update("selectedEvt_1eTrig", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("selectedEvt_1eTrig", evtWeightRecorder.get(central_or_shift));
    }
    if (selTrigger_2e) {
      cutFlowTable.update("selectedEvt_2eTrig", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("selectedEvt_2eTrig", evtWeightRecorder.get(central_or_shift));
    }
    if (selTrigger_1e && selTrigger_2e) {
      cutFlowTable.update("selectedEvt 1e && 2eTrig", evtWeightRecorder.get(central_or_shift));
      cutFlowHistManager->fillHistograms("selectedEvt 1e && 2eTrig", evtWeightRecorder.get(central_or_shift));
    }
              
    const bool isCharge_SS = selElectron_lead_charge*selElectron_sublead_charge > 0;
    const bool isCharge_OS = selElectron_lead_charge*selElectron_sublead_charge < 0;

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
      if(btagSFRatioFacility)
      {
        evtWeightRecorder.record_btagSFRatio(btagSFRatioFacility, selJets.size());
      }

      bool requireChargeMatch = lep_useTightChargeCut;
      dataToMCcorrectionInterface->setLeptons({ selElectron_lead, selElectron_sublead }, requireChargeMatch);

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria
      evtWeightRecorder.record_leptonTriggerEff(dataToMCcorrectionInterface);

      evtWeightRecorder.record_leptonIDSF_recoToLoose(dataToMCcorrectionInterface);

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if(leptonSelection >= kFakeable)
      {
        // apply looseToTight SF to leptons matched to generator-level prompt leptons and passing Tight selection conditions
	bool woTightCharge = lep_useTightChargeCut ? false : true;
	evtWeightRecorder.record_leptonIDSF_looseToTight(dataToMCcorrectionInterface, woTightCharge);	
      }
    }

    if(applyFakeRateWeights == kFR_2lepton)
    {
      evtWeightRecorder.record_jetToLepton_FR_lead(leptonFakeRateInterface, selElectron_lead);
      evtWeightRecorder.record_jetToLepton_FR_sublead(leptonFakeRateInterface, selElectron_sublead);
      const bool passesTight_electron_lead = isMatched(*selElectron_lead, tightElectrons);
      const bool passesTight_electron_sublead = isMatched(*selElectron_sublead, tightElectrons);
      evtWeightRecorder.compute_FR_2l(passesTight_electron_lead, passesTight_electron_sublead);
    }
    
    
//--- fill histograms with events passing final selection
    const double evtWeight = evtWeightRecorder.get(central_or_shift);
    evtHistManager.fillHistograms(selElectron_lead_p4, selElectron_sublead_p4, m_ee, isCharge_SS, evtWeight);
    if ( isZee ) {
      bool isDY = (isGenElectron_lead && isGenElectron_sublead);
      if ( isDY ) {
	if ( genElectron_lead_p4.pt() > genElectron_sublead_p4.pt() ) {
          evtHistManager_DY_genCategory->fillHistograms(genElectron_lead_p4, genElectron_sublead_p4, m_ee, isCharge_SS, evtWeight);
	} else {
          evtHistManager_DY_genCategory->fillHistograms(genElectron_sublead_p4, genElectron_lead_p4, m_ee, isCharge_SS, evtWeight);
	}
        evtHistManager_DY_recCategory->fillHistograms(selElectron_lead_p4, selElectron_sublead_p4, m_ee, isCharge_SS, evtWeight);
 
	if ( central_or_shift == "central" ) {
	  TH1* histogram_gen = 0;
	  if      ( isCharge_SS ) histogram_gen = histogram_gen_SS;
	  else if ( isCharge_OS ) histogram_gen = histogram_gen_OS;
	  else assert(0);
	  double genElectron_lead_absEta = std::fabs(genElectron_lead_p4.eta());
          fillWithOverFlow(histogram_gen, genElectron_lead_p4.pt(), genElectron_lead_absEta, evtWeight);
	  double genElectron_sublead_absEta = std::fabs(genElectron_sublead_p4.eta());
          fillWithOverFlow(histogram_gen, genElectron_sublead_p4.pt(), genElectron_sublead_absEta, evtWeight);
	  
          histogram_prob_charge_flip_gen->FillWeighted(selElectron_lead_charge != genElectron_lead_charge, evtWeight, genElectron_lead_p4.pt(), genElectron_lead_absEta);
          histogram_prob_charge_flip_gen->FillWeighted(selElectron_sublead_charge != genElectron_sublead_charge, evtWeight, genElectron_sublead_p4.pt(), genElectron_sublead_absEta);
          histogram_prob_charge_flip_gen_rec->FillWeighted(selElectron_lead_charge != genElectron_lead_charge, evtWeight, selElectron_lead_p4.pt(), selElectron_lead_absEta);
          histogram_prob_charge_flip_gen_rec->FillWeighted(selElectron_sublead_charge != genElectron_sublead_charge, evtWeight, selElectron_sublead_p4.pt(), selElectron_sublead_absEta);
	  
	  int idxBin_lead_gen = getBinIdx_pT_and_absEta(genElectron_lead_p4.pt(), genElectron_lead_absEta);
	  int idxBin_lead_rec = getBinIdx_pT_and_absEta(selElectron_lead_p4.pt(), selElectron_lead_absEta);      
          histogram_idxBin_pT_and_eta_rec_vs_gen->Fill(idxBin_lead_gen, idxBin_lead_rec, evtWeight);
          if      ( isCharge_SS ) histogram_idxBin_pT_and_eta_rec_vs_gen_SS->Fill(idxBin_lead_gen, idxBin_lead_rec, evtWeight);
          else if ( isCharge_OS ) histogram_idxBin_pT_and_eta_rec_vs_gen_OS->Fill(idxBin_lead_gen, idxBin_lead_rec, evtWeight);
	  int idxBin_sublead_gen = getBinIdx_pT_and_absEta(genElectron_sublead_p4.pt(), genElectron_sublead_absEta);
	  int idxBin_sublead_rec = getBinIdx_pT_and_absEta(selElectron_sublead_p4.pt(), selElectron_sublead_absEta);
	  histogram_idxBin_pT_and_eta_rec_vs_gen->Fill(idxBin_sublead_gen, idxBin_sublead_rec, evtWeight);
	  if      ( isCharge_SS ) histogram_idxBin_pT_and_eta_rec_vs_gen_SS->Fill(idxBin_sublead_gen, idxBin_sublead_rec, evtWeight);
	  else if ( isCharge_OS ) histogram_idxBin_pT_and_eta_rec_vs_gen_OS->Fill(idxBin_sublead_gen, idxBin_sublead_rec, evtWeight);

	  //---- DY mountain-like tail above mee >100
	  int binIdx_lead    = getBinIdx_pT_and_absEta(selElectron_lead_p4.pt(),    selElectron_lead_p4.eta());
	  int binIdx_sublead = getBinIdx_pT_and_absEta(selElectron_sublead_p4.pt(), selElectron_sublead_p4.eta());
	  if ( (binIdx_lead    == 3 || binIdx_lead    == 6) &&
	       (binIdx_sublead == 3 || binIdx_sublead == 6)) { // lead.pt > 50 && sublead.pt > 50	  
	    if (m_ee >= 100.) {
	      histogram_pT_gen_vs_rec_meeAbove100_ePtAvobe50->Fill(genElectron_lead_p4.pt(), selElectron_lead_p4.pt(), evtWeight);
	      if (binIdx_lead == 3 && binIdx_sublead == 3) {
		histogram_pT_gen_vs_rec_meeAbove100_BBHH->Fill(genElectron_lead_p4.pt(), selElectron_lead_p4.pt(), evtWeight);
	      } else if (binIdx_lead == 6 && binIdx_sublead == 6) {
		histogram_pT_gen_vs_rec_meeAbove100_EEHH->Fill(genElectron_lead_p4.pt(), selElectron_lead_p4.pt(), evtWeight);
	      } else {
		histogram_pT_gen_vs_rec_meeAbove100_BEHH->Fill(genElectron_lead_p4.pt(), selElectron_lead_p4.pt(), evtWeight);
	      }
	    }
	  }
	  
	}
      } else {
	// DY_fake
        evtHistManager_DY_fake->fillHistograms(selElectron_lead_p4, selElectron_sublead_p4, m_ee, isCharge_SS, evtWeight);
      }
    }

    if      ( isCharge_SS ) preselElectronHistManagerSS.fillHistograms(preselElectrons, evtWeight);
    else if ( isCharge_OS ) preselElectronHistManagerOS.fillHistograms(preselElectrons, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift));
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift));
      }
    }

    (*selEventsFile) << eventInfo.str() << '\n';
    
    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    if ( isCentral ) {
      histogram_selectedEntries->Fill(0.);
    }
    if(isDEBUG)
    {
      std::cout << evtWeightRecorder << '\n';
    }
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n";
  cutFlowTable.print(std::cout);
  std::cout << std::endl;
 
//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete dataToMCcorrectionInterface;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete l1PreFiringWeightReader;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);

  clock.Show("analyze_charge_flip");

  return EXIT_SUCCESS;
}
