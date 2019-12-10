// latest

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
#include <TMatrixD.h> // TMatrixD
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::Pi()
#include <TLorentzVector.h>

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderHTTv2.h" // RecoJetReaderHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h" // JetHistManagerHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTaggerFill.h" // HadTopTaggerFill
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // isGenMatchedJetTriplet tags
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <math.h> // acos, sqrt
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <numeric> // iota

#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#pragma GCC diagnostic pop
using namespace boost::python;

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kGen_bWj1Wj2, kGen_bWj1, kGen_bWj2, kGen_Wj1Wj2, kGen_b, kGen_Wj1, kGen_Wj2, kGen_none };
bool loopB = true;
bool cleanLep = true;
bool selInJets = true;
size_t cutJetCombo = 20;
bool doResolved = false;

double square(double x)
{
  return x*x;
}

int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_hadTopTagger>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_hadTopTagger");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_hadTopTagger")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  std::cout << "<analyze_hadTopTagger 2 >:" << std::endl;
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_hadTopTagger");
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift);
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option = getJet_option(central_or_shift, isMC);
  const int met_option   = getMET_option(central_or_shift, isMC);

  std::cout
    << "central_or_shift = " << central_or_shift << "\n"
       " -> met_option   = " << met_option       << "\n"
       " -> jetPt_option = " << jetPt_option     << '\n'
  ;

  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_jetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_jetsHTTv2");
  std::string branchName_subjetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_subjetsHTTv2");
  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  std::string branchName_jetGenMatch = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");
  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");

  bool redoGenMatching = false; //cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool readGenObjects = isMC && !redoGenMatching;
  const bool genMatchingByIndex = cfg_analyze.getParameter<bool>("genMatchingByIndex");

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

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isMC);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics(central_or_shift != "central" && isMC);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  RecoJetCollectionCleaner jetCleaner(0.8, isDEBUG); //to clean against AK8

  RecoJetReaderHTTv2* jetReaderHTTv2 = new RecoJetReaderHTTv2(era, branchName_jetsHTTv2, branchName_subjetsHTTv2);
  inputTree -> registerReader(jetReaderHTTv2);
  RecoJetCollectionSelectorHTTv2 jetSelectorHTTv2(era);
  RecoJetCollectionCleanerHTTv2 jetCleanerHTTv2(0.75, isDEBUG); //to clean against leptons and hadronic taus

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);

//--- declare generator level information
  GenJetReader * genJetReader = nullptr;
  LHEInfoReader * lheInfoReader = nullptr;

  GenParticleReader * genMatchToJetReader      = nullptr;
  if(isMC)
  {
    genJetReader = new GenJetReader(branchName_genJets);
    inputTree -> registerReader(genJetReader);

    if(genMatchingByIndex)
    {
      genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
      genMatchToJetReader -> readGenPartFlav(true);
      inputTree -> registerReader(genMatchToJetReader);
    }

    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);
  GenParticleReader* genQuarkFromTopReader = new GenParticleReader(branchName_genQuarkFromTop);

  if ( isMC ) {
    inputTree->registerReader(genTopQuarkReader);
    inputTree->registerReader(genBJetReader);
    inputTree->registerReader(genWBosonReader);
    inputTree->registerReader(genWJetReader);
    inputTree->registerReader(genQuarkFromTopReader);
  }

  HadTopTaggerFill* hadTopTaggerFill = new HadTopTaggerFill();

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
       makeHistManager_cfg(process_string, Form("%s/evtntuple", histogramDir.data()), era_string, "central")
       );
    bdt_filler->register_variable<float_type>(
      ///* // computed by (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
      "m_bWj1Wj2", "m_Wj1Wj2", "m_bWj1", "m_bWj2",
      "m_Wj1Wj2_div_m_bWj1Wj2",
      "pT_b", "eta_b", //"phi_b", "mass_b",
      "kinFit_pT_b", //"kinFit_eta_b", //"kinFit_phi_b", "kinFit_mass_b",
      "pT_Wj1", "eta_Wj1", //"phi_Wj1", "mass_Wj1",
      "kinFit_pT_Wj1", //"kinFit_eta_Wj1", //"kinFit_phi_Wj1", "kinFit_mass_Wj1",
      "pT_Wj2", "eta_Wj2", //"phi_Wj2", "mass_Wj2",
      "kinFit_pT_Wj2", //"kinFit_eta_Wj2", //"kinFit_phi_Wj2", "kinFit_mass_Wj2",
      "cosTheta_leadWj_restTop","cosTheta_subleadWj_restTop",
      "cosTheta_Kin_leadWj_restTop","cosTheta_Kin_subleadWj_restTop",
      "cosTheta_leadEWj_restTop","cosTheta_subleadEWj_restTop",
      "cosTheta_Kin_leadEWj_restTop","cosTheta_Kin_subleadEWj_restTop",
      "cosThetaW_rest","cosThetaKinW_rest","cosThetaW_lab","cosThetaKinW_lab",
      "cosThetab_rest","cosThetaKinb_rest","cosThetab_lab","cosThetaKinb_lab",
      "Dphi_Wj1_Wj2_lab","Dphi_KinWj1_KinWj2_lab",
      "Dphi_Wb_rest","Dphi_KinWb_rest","Dphi_Wb_lab","Dphi_KinWb_lab",
      "cosThetaWj1_restW","cosThetaKinWj_restW",
      "dR_bWj1", "dR_bWj2", "dR_Wj1Wj2", "dR_bW",
      "statusKinFit", "nllKinFit", "alphaKinFit", //"logPKinFit", "logPErrKinFit",
      "pT_bWj1Wj2", "pT_Wj1Wj2",
      "atan_m13_div_m12","m23_div_m123","Rmin_square_one_plus_m13_div_m12_square",
      "Rmax_square_one_plus_m13_div_m12_square",
      //*/
      "tau32Top", "massTop",
      "tau21W", "massW_SD",
      "genTopPt", "genTopEta",
      "genFatPtAll", "genFatEtaAll",
      "drT_gen", "drB_gen", "drW_gen", "drWj1_gen", "drWj2_gen",
      "etaB_gen",  "etaWj1_gen", "etaWj2_gen",
      "ptB_gen",  "ptWj1_gen", "ptWj2_gen",
      "dr_b_wj1", "dr_b_wj2", "dr_wj1_wj2",
      "dr_b_wj1_gen", "dr_b_wj2_gen", "dr_wj1_wj2_gen", "drT_genTriplet", "drT_genJ_max",
      "btagDisc", "qg_Wj1", "qg_Wj2",
      "HTTv2_area", "HTTv2_Ropt", "HTTv2_RoptCalc",
      "genTopMassFromW", "genTopMassFromWj", "genWMassFromWj",
      "genAntiTopMassFromW", "genAntiTopMassFromWj", "genAntiWMassFromWj",
      "genWMass", "genAntiWMass"
    );


    bdt_filler->register_variable<int_type>(
      "typeTop", "collectionSize", "bjet_tag_position", "bWj1Wj2_isGenMatched", "counter",
      "fatjet_isGenMatched", "b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      "nbjets", "nbjets_loose", "njets", "passJetSel"
      //"b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      //"bWj1Wj2_isGenMatched"
    );
	//bdt_filler->register_variable<int_type>("mvaOutput_hadTopTagger");
    bdt_filler->bookTree(fs);
	}

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  int countFatTop = 0;
  int countFatTopPt200 = 0;
  int countFatTopbmatch = 0;
  int countFatTopWj1match = 0;
  int countFatTopWj2match = 0;
  int countFatW = 0;
  int countFatWjets = 0;
  int countFatWpt130 = 0;

  int countpassJetSel = 0;

  int countFatAK8 = 0;
  int countResolved = 0;
  int hadtruth1 = 0; // counter for diagnosis
  int hadtruth2 = 0; // counter for diagnosis
  int hadtruth3 = 0; // counter for diagnosis
  int ca1_cat2 = 0;
  int cat2_cat3 = 0;
  int cat3_cat1 = 0 ;
  int cat3_cat2_cat1 = 0;

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    //if (countFatTop > 50) continue;
    if ( isDEBUG ) {
      std::cout << "processing run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
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
    histogram_analyzedEntries->Fill(0.);

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }

    //std::cout << "before load jets"  << std::endl;
//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    const std::vector<const RecoJet*> selJets = jetSelector(jet_ptrs, isHigherPt);
    const std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(selJets);
    const std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(selJets);
    //std::cout << "after load jets"  << std::endl;
//--- build collections of jets reconstructed by hep-top-tagger (HTTv2) algorithm
    const std::vector<RecoJetHTTv2> jetsHTTv2 = jetReaderHTTv2->read();
    const std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2raw = convert_to_ptrs(jetsHTTv2);
    const std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2 = jetSelectorHTTv2(jet_ptrsHTTv2raw, isHigherPt);
    //std::cout << "after load HTT "<< jet_ptrsHTTv2raw.size()<< " " <<  jet_ptrsHTTv2 .size() << std::endl;

//--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    const std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    const std::vector<const RecoJetAK8*> jet_ptrsAK8raw = convert_to_ptrs(jetsAK8);
    const std::vector<const RecoJetAK8*> jet_ptrsAK8 = jetSelectorAK8(jet_ptrsAK8raw , isHigherPt);
    //std::cout << "after load ak8"  << std::endl;

    // cleaned RecoJet collection from AK8 as well -- to keep b-tag ordering consistent in cat2
    const std::vector<const RecoJet*> cleanedJets = jetCleaner(selJets, jet_ptrsAK8);

    // natural selection of all ttH(multilepton categories)
    bool passJetSel = false;
    if ( selJets.size() >= 4 &&  (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) && selInJets) {passJetSel = true; countpassJetSel++; } //else continue;

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    std::vector<GenJet> genJets;
    std::vector<GenParticle> jetGenMatch;
    if(isMC && redoGenMatching)
    {
      if(genJetReader) genJets = genJetReader->read();

      if(genMatchToJetReader) jetGenMatch = genMatchToJetReader->read();
    }

//--- match reconstructed to generator level particles
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        jetGenMatcher.addGenJetMatchByIndex(selJets, jetGenMatch);
      }
      else
      {
        jetGenMatcher.addGenJetMatch(selJets, genJets, 0.4);
      }
    }

    if ( isMC ) {
      lheInfoReader->read();
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.str() << '\n';
    }

//--- build collections of generator level particles
    std::vector<GenParticle> genTopQuarks = genTopQuarkReader->read();
    std::vector<GenParticle> genBJets = genBJetReader->read();
    std::vector<GenParticle> genWBosons = genWBosonReader->read();
    std::vector<GenParticle> genWJets = genWJetReader->read();
    std::vector<GenParticle> genQuarkFromTop = genQuarkFromTopReader->read();

    //std::cout << "Size of genjet collections "
    //  <<genQuarkFromTop.size()<< " "<< genWJets.size() << " " << genWBosons.size() << std::endl;
    if (genQuarkFromTop.size() < 2) continue;

    Particle::LorentzVector unfittedHadTopP4, selBJet, selWJet1, selWJet2 ;
    double m12=-1.,m23=-1.,m13=-1.,m123=-1.;
    double m23_div_m123 = -1;

    bool isGenMatched = false;
		bool fatjet_isGenMatched = false;
    bool b_isGenMatched = false;
    bool wj1_isGenMatched = false;
    bool wj2_isGenMatched = false;
    double genTopPt = -1.;
    double genTopEta = -1.;
    double genFatPtAll = -1.;
    double drT_gen = -1.;
    double drW_gen = -1.;
    double drB_gen = -1.;
    double drWj1_gen = -1.;
    double drWj2_gen = -1.;
    double genFatEtaAll = -2.5;
    double etaB_gen = -1;
    double etaWj1_gen = -1;
    double etaWj2_gen = -1;
    double ptB_gen = -1;
    double ptWj1_gen = -1;
    double ptWj2_gen = -1;
    double drb_wj1_gen = -1;
    double drb_wj2_gen = -1;
    double drwj1_wj2_gen = -1;
    double drT_genTriplet = -1;
    double drT_genJ_max = -1;
    double HTTv2_area = -1;
    double HTTv2_Ropt = -1;
    double HTTv2_RoptCalc = -1;
    double genTopMassFromW = -1;
    double genTopMassFromWj = -1;
    double genWMassFromWj = -1;
    double genAntiTopMassFromW = -1;
    double genAntiTopMassFromWj = -1;
    double genAntiWMassFromWj = -1;
    double genAntiWMass = -1.;
    double genWMass = -1.;
    //
    bool cat1 = false;
    bool cat2 = false;
    bool cat3 = false;

    // it returns the gen-triplets organized in top/anti-top
    std::map<int, Particle::LorentzVector> genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop); // genWJets,
    std::map<int, Particle::LorentzVector> genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop); // genWJets,

    if (genQuarkFromTop.size() == 2 ) {
      //&& genVar[kGenTopWj1].pt() > 0 && genVar[kGenTopWj2] > 0
      double diff_Top = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass() - genVar[kGenTop].mass();
      double diff_AntiTop = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass() - genVarAnti[kGenTop].mass();
      if( diff_Top < diff_AntiTop && genVar[kGenTopWj1].px() > 0) {
        genTopMassFromW = (genVar[kGenTopW]+genVar[kGenTopB]).mass();
        genTopMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass();
        genWMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]).mass();
        genWMass = genVar[kGenTopW].mass();
      } else if (genVarAnti[kGenTopWj1].px() > 0){
        genAntiTopMassFromW = (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass();
        genAntiTopMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass();
        genAntiWMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).mass();
        genAntiWMass = genVarAnti[kGenTopW].mass();
      }
    } else if (genQuarkFromTop.size() == 4) {

      if ( genVar[kGenTopWj1].px() > 0 ) {
        genTopMassFromW = (genVar[kGenTopW]+genVar[kGenTopB]).mass();
        genTopMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]+genVar[kGenTopB]).mass();
        genWMassFromWj = (genVar[kGenTopWj1]+genVar[kGenTopWj2]).mass();
      }

      if ( genVarAnti[kGenTopWj1].px() > 0 ) {
        genAntiTopMassFromW = (genVarAnti[kGenTopW]+genVarAnti[kGenTopB]).mass();
        genAntiTopMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]+genVarAnti[kGenTopB]).mass();
        genAntiWMassFromWj = (genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).mass();
      }

    }

    // to be used at analysis level
    int typeTop = -1; // 1 - FatTop; 2 - countFatAK8; 3- countResolved;
    //else typeTop = getType(jet_ptrsHTTv2.size(), jet_ptrsAK8.size(), selJets.size());
    // start loops in jets
    //if (typeTop == 1) {

      if (jet_ptrsHTTv2.size() > 0 ) countFatTop++;
      typeTop = 1;
      int counter = 0;
      for ( std::vector<const RecoJetHTTv2*>::const_iterator jetIter = jet_ptrsHTTv2.begin();
        jetIter != jet_ptrsHTTv2.end(); ++jetIter ) {
          genFatPtAll = -1.;
          genTopEta = -2.5;
          unfittedHadTopP4 = (*jetIter)->p4();
          HTTv2_area = (*jetIter)->area();
          HTTv2_Ropt = (*jetIter)->Ropt();
          HTTv2_RoptCalc = (*jetIter)->RoptCalc();

          const RecoSubjetHTTv2* recSubJet[3];
          recSubJet[0] = (*jetIter)->subJet1();
          recSubJet[1] = (*jetIter)->subJet2();
          recSubJet[2] = (*jetIter)->subJet3();
          double btag_orderType1 = -1;
          double btag_discType1 = -1;

          // loop on bjetCandidate version 1 :
          //bool foundtruth = false;
          //for (int bb = 0; bb < 3; bb++) {
          //  if (foundtruth) continue;
          //  for (int wj1 = 0; wj1 < 3; wj1++) {
          //   if (bb == wj1) continue;
          //    for (int wj2 = 0; wj2 < 3; wj2++) {
          //      if (bb == wj2 || wj1 == wj2 || foundtruth) continue;
          //        selBJet = recSubJet[bb]->p4();
          //        selWJet1 = recSubJet[wj1]->p4();
          //        selWJet2 = recSubJet[wj2]->p4();
          //        std::vector<double> btag_disc1 = {recSubJet[bb]->BtagCSV(), recSubJet[wj1]->BtagCSV(), recSubJet[wj2]->BtagCSV()};
          //  auto btag_order1 = calRank(btag_disc1);
          //  btag_orderType1 = btag_order1[0];
          //  btag_discType1 = btag_disc1[0];
          //  std::cout<<" btag position of bjet "<< btag_order1[0] <<" value "<< btag_disc1[0] <<std::endl;

          ////////////
          // loop on bjetCandidate version 2 :
          //int perm [5] = { 0, 1, 2, 0, 1 }; // I do not care about the ordering of wj1/2 so no fancy permutation solution is required
          //for (int bb = 0; bb < 3; bb++) {
          //  if (foundtruth) continue;
          //  selBJet = recSubJet[perm[bb]]->p4();
          //  selWJet1 = recSubJet[perm[bb+1]]->p4();
          //  selWJet2 = recSubJet[perm[bb+2]]->p4();
          //  std::vector<double> btag_disc1 = {recSubJet[perm[bb]]->BtagCSV(), recSubJet[perm[bb+1]]->BtagCSV(), recSubJet[perm[bb+2]]->BtagCSV()};
            // checking btag ordering
          //  auto btag_order1 = calRank(btag_disc1);
          //  btag_orderType1 = btag_order1[0];
          //  btag_discType1 = recSubJet[perm[bb]]->BtagCSV();
          //  std::cout<<"btag discr  ";
          //  for (auto i: btag_disc1) std::cout << i << " ";
          //  std::cout<<" btag ordering  ";
          //  for (auto i: btag_order1) std::cout << i << " ";
          //  std::cout<<" typeTop = "<<typeTop << " b-tag discrim: " << recSubJet[perm[bb]]->BtagCSV() << " on position " << btag_order1[0] <<std::endl;

            // Just take the subjet with highest b-tag score to be the b-candidate
            std::vector<double> btag_disc = {recSubJet[0]->BtagCSV(), recSubJet[1]->BtagCSV(), recSubJet[2]->BtagCSV()};
            auto btag_order = sort_indexes(btag_disc);
            selBJet = recSubJet[btag_order[0]]->p4();
            selWJet1 = recSubJet[btag_order[1]]->p4();
            selWJet2 = recSubJet[btag_order[2]]->p4();
            btag_orderType1 = 1;
            btag_discType1 = recSubJet[btag_order[0]]->BtagCSV();
            //std::cout<<"btag discr  ";
            //for (auto i: btag_disc) std::cout << i << " ";
            //std::cout<<" position of highest  "<< btag_order[0] << " (" << btag_discType1 <<") "<< foundtruth <<std::endl;

            std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
              selBJet, selWJet1, selWJet2,
              genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
              typeTop, unfittedHadTopP4
            );
            std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
              selBJet, selWJet1, selWJet2,
              genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
              typeTop, unfittedHadTopP4
            );
            if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt();  genTopEta = genVar[kGenTop].eta();}
            if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt();  genTopEta = genVarAnti[kGenTop].eta();}

            isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
            fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
            b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
            wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
            wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
            //if (b_isGenMatched) foundtruth = true; // if loop on subjets
            if (isGenMatched) {hadtruth1++; cat1 = true; } // foundtruth = true;
          //}}} // end loop on subjets version 1
          //} // end loop on subjets version 2
          // debug gen-matching

          double minT = deltaR(selBJet, genVar[kGenTopB]) + deltaR(selWJet1+selWJet2, genVar[kGenTopWj2]);//std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
          double minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]) + deltaR(selWJet1+selWJet2, genVarAnti[kGenTopWj2]);//std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));

          if ( minT < minAntiT ){
            genFatPtAll = genVar[kGenTopVar].pt();
            genFatEtaAll = genVar[kGenTopVar].eta();
            drT_gen = deltaR(unfittedHadTopP4, genVar[kGenTop]);
            drT_genTriplet = deltaR(unfittedHadTopP4, genVar[kGenTopWj1]+genVar[kGenTopWj1]+genVar[kGenTopB]);
            drT_genJ_max = std::max(deltaR(unfittedHadTopP4, genVar[kGenTopB]),std::max(deltaR(unfittedHadTopP4, genVar[kGenTopWj1]),deltaR(unfittedHadTopP4, genVar[kGenTopWj2])));
            drB_gen = deltaR(selBJet, genVar[kGenTopB]);
            drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
            drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
            etaB_gen = genVar[kGenTopB].eta();
            etaWj1_gen = genVar[kGenTopWj1].eta();
            etaWj2_gen = genVar[kGenTopWj2].eta();
            ptB_gen = genVar[kGenTopB].pt();
            ptWj1_gen = genVar[kGenTopWj1].pt();
            ptWj2_gen = genVar[kGenTopWj2].pt();
            drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
            drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
            drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
            drW_gen = deltaR(selWJet1 + selWJet2 , genVar[kGenTopW]);
            if(selBJet.pt()>selWJet1.pt() && selBJet.pt()>selWJet2.pt()){
             if(selWJet1.pt()>selWJet2.pt()){
                m12 = (selBJet + selWJet1).mass();
                m23 = (selWJet1 + selWJet2).mass();
                m13 = (selBJet + selWJet1).mass();
             }
             else{
                m12 = (selBJet + selWJet2).mass();
                m23 = (selWJet1 + selWJet2).mass();
                m13 = (selBJet + selWJet2).mass();
             }
            }
           else if(selWJet1.pt()>selBJet.pt() && selWJet1.pt()>selWJet2.pt()){
             if(selBJet.pt()>selWJet2.pt()){
                m12 = (selBJet + selWJet1).mass();
                m23 = (selBJet + selWJet2).mass();
                m13 = (selWJet2 + selWJet1).mass();
             }
             else{
                m12 = (selWJet1 + selWJet2).mass();
                m23 = (selBJet + selWJet2).mass();
                m13 = (selBJet + selWJet1).mass();
             }
            }
          else if(selWJet2.pt()>selBJet.pt() && selWJet2.pt()>selWJet1.pt()){
             if(selBJet.pt()>selWJet1.pt()){
                m12 = (selBJet + selWJet2).mass();
                m23 = (selBJet + selWJet1).mass();
                m13 = (selWJet2 + selWJet1).mass();
             }
             else{
                m12 = (selWJet1 + selWJet2).mass();
                m23 = (selBJet + selWJet1).mass();
                m13 = (selBJet + selWJet2).mass();
             }
            }
           m123 = (selBJet + selWJet1 + selWJet2).mass();
           m23_div_m123 = 1.0*m23/m123;

          } else {
            genFatPtAll = genVarAnti[kGenTopVar].pt();
            genFatEtaAll = genVarAnti[kGenTopVar].eta();
            drT_gen = deltaR(unfittedHadTopP4, genVarAnti[kGenTop]);
            drT_genTriplet = deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj1]+genVarAnti[kGenTopB]);
            drT_genJ_max = std::max(deltaR(unfittedHadTopP4, genVarAnti[kGenTopB]),std::max(deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj1]),deltaR(unfittedHadTopP4, genVarAnti[kGenTopWj2])));
            drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
            drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
            drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
            etaB_gen = genVarAnti[kGenTopB].eta();
            etaWj1_gen = genVarAnti[kGenTopWj1].eta();
            etaWj2_gen = genVarAnti[kGenTopWj2].eta();
            ptB_gen = genVarAnti[kGenTopB].pt();
            ptWj1_gen = genVarAnti[kGenTopWj1].pt();
            ptWj2_gen = genVarAnti[kGenTopWj2].pt();
            drb_wj1_gen = deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
            drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
            drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
            drW_gen = deltaR(selWJet1 + selWJet2 , genVarAnti[kGenTopW]);
	    if(selBJet.pt()>selWJet1.pt() && selBJet.pt()>selWJet2.pt()){
             if(selWJet1.pt()>selWJet2.pt()){
                m12 = (selBJet + selWJet1).mass();
                m23 = (selWJet1 + selWJet2).mass();
                m13 = (selBJet + selWJet1).mass();
             }
             else{
                m12 = (selBJet + selWJet2).mass();
                m23 = (selWJet1 + selWJet2).mass();
                m13 = (selBJet + selWJet2).mass();
             }
            }
           else if(selWJet1.pt()>selBJet.pt() && selWJet1.pt()>selWJet2.pt()){
             if(selBJet.pt()>selWJet2.pt()){
                m12 = (selBJet + selWJet1).mass();
                m23 = (selBJet + selWJet2).mass();
                m13 = (selWJet2 + selWJet1).mass();
             }
             else{
                m12 = (selWJet1 + selWJet2).mass();
                m23 = (selBJet + selWJet2).mass();
                m13 = (selBJet + selWJet1).mass();
             }
            }
          else if(selWJet2.pt()>selBJet.pt() && selWJet2.pt()>selWJet1.pt()){
             if(selBJet.pt()>selWJet1.pt()){
                m12 = (selBJet + selWJet2).mass();
                m23 = (selBJet + selWJet1).mass();
                m13 = (selWJet2 + selWJet1).mass();
             }
             else{
                m12 = (selWJet1 + selWJet2).mass();
                m23 = (selBJet + selWJet1).mass();
                m13 = (selBJet + selWJet2).mass();
             }
            }
	  m123 = (selBJet + selWJet1 + selWJet2).mass();
          m23_div_m123 = 1.0*m23/m123;

          }
          if ( genFatPtAll > 200 && (genVarAnti[kGenTopB]+genVarAnti[kGenTopWj1]+genVarAnti[kGenTopWj2]).eta() < 2.4 && counter == 0 && drT_gen < 0.75) {
            countFatTopPt200++; counter++;
          }
          if ( counter == 1 && b_isGenMatched && selBJet.pt() > 30 ) {
            countFatTopbmatch++;
            if ( wj1_isGenMatched && selWJet1.pt() > 30) {
              countFatTopWj1match++;
              if ( wj2_isGenMatched && selWJet2.pt() > 30) countFatTopWj2match++;
            }
          }

          if ( bdt_filler ) {
            (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2); // calculates the quantities that take only kinematics
            const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
            for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
              mvaInput != mvaInputs.end(); ++mvaInput ) {
              bdt_filler->operator()(mvaInput->first, mvaInput->second);
            }
            bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
            ("typeTop",              typeTop)
            ("tau32Top",             (*jetIter)->tau3()/(*jetIter)->tau2())
            ("massTop",              unfittedHadTopP4.mass())
            ("tau21W",               -1.)
            ("massW_SD",             -1.)
            ("btagDisc",             btag_discType1)
            ("qg_Wj1",                -1.)
            ("qg_Wj2",                -1.)
            ("genTopPt",             genTopPt)
            ("genTopEta",            std::fabs(genTopEta))
            ("genFatPtAll", genFatPtAll)
            ("genFatEtaAll",         std::fabs(genFatEtaAll))
            ("drT_gen",       drT_gen)
            ("drT_genTriplet",  drT_genTriplet)
            ("drT_genJ_max", drT_genJ_max)
            ("drB_gen", drB_gen)
            ("drW_gen", drW_gen)
            ("drWj1_gen", drWj1_gen)
            ("drWj2_gen", drWj2_gen)
            ("etaB_gen", etaB_gen)
            ("etaWj1_gen", etaWj1_gen)
            ("etaWj2_gen", etaWj2_gen)
            ("ptB_gen", ptB_gen)
            ("ptWj1_gen", ptWj1_gen)
            ("ptWj2_gen", ptWj2_gen)
            ("dr_b_wj1", deltaR(selBJet, selWJet1))
            ("dr_b_wj2", deltaR(selBJet, selWJet2))
            ("dr_wj1_wj2", deltaR(selWJet1, selWJet2))
            ("dr_b_wj1_gen", drb_wj1_gen)
            ("dr_b_wj2_gen", drb_wj2_gen)
            ("dr_wj1_wj2_gen", drwj1_wj2_gen)
            ("collectionSize",       jet_ptrsHTTv2.size())
            ("bjet_tag_position",    btag_orderType1)
            ("bWj1Wj2_isGenMatched", isGenMatched)
            ("fatjet_isGenMatched",  fatjet_isGenMatched)
            ("b_isGenMatched",       b_isGenMatched)
            ("Wj1_isGenMatched", wj1_isGenMatched)
            ("Wj2_isGenMatched", wj2_isGenMatched)
            ("counter",        analyzedEntries)
            ("nbjets",  selBJets_medium.size())
            ("nbjets_loose",  selBJets_loose.size())
            ("njets",  selJets.size())
            ("passJetSel", passJetSel)
            ("HTTv2_area", HTTv2_area)
            ("HTTv2_Ropt", HTTv2_Ropt)
            ("HTTv2_RoptCalc", HTTv2_RoptCalc)
            ("genTopMassFromW", genTopMassFromW )
            ("genTopMassFromWj", genTopMassFromWj )
            ("genWMassFromWj", genWMassFromWj )
            ("genAntiTopMassFromW", genAntiTopMassFromW )
            ("genAntiTopMassFromWj", genAntiTopMassFromWj )
            ("genAntiWMassFromWj", genAntiWMassFromWj )
            ("genWMass", genWMass)
            ("genAntiWMass", genAntiWMass)
            ("atan_m13_div_m12", atan(1.0*m13/m12))
            ("m23_div_m123",m23_div_m123)
            ("Rmin_square_one_plus_m13_div_m12_square",0.7*0.7*(1+1.0*(m13/m12)*(m13/m12)))
            ("Rmax_square_one_plus_m13_div_m12_square",1.3*1.3*(1+1.0*(m13/m12)*(m13/m12)))
                .fill();
          }
        } // end typeTop == 1 (HTTv2 loop)
    //} else if (typeTop!=-1) {
    // store b-tag classification of cleaned jet collection
    if (cleanedJets.size()>0) {
    std::vector<double> btag_disc = getBdiscr(cleanedJets);
    auto btag_order = calRank(btag_disc);
    unsigned int bToLoop = cleanedJets.size();
    if (!loopB) bToLoop = 1;
        if (jet_ptrsAK8.size() > 0 && cleanedJets.size() > 0) {countFatAK8++; typeTop = 2;}
        for ( std::vector<const RecoJetAK8*>::const_iterator jetIter = jet_ptrsAK8.begin();
          jetIter != jet_ptrsAK8.end(); ++jetIter ) {
            for ( unsigned int bjetCandidate = 0; bjetCandidate < bToLoop; bjetCandidate++ ) { // cleanedJets.size()
                unfittedHadTopP4 = (*jetIter)->p4() + (*cleanedJets[bjetCandidate]).p4();
                selBJet = (*cleanedJets[bjetCandidate]).p4();
                if((*jetIter)->subJet1() && (*jetIter)->subJet2()) {
                selWJet1 = (*jetIter)->subJet1()->p4();
                selWJet2 = (*jetIter)->subJet2()->p4();

                std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
                  selBJet, selWJet1, selWJet2,
                  genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
                  typeTop, (*jetIter)->p4()
                );
                std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
                  selBJet, selWJet1, selWJet2,
                  genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
                  typeTop, (*jetIter)->p4()
                );
                if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt();  genTopEta = genVar[kGenTop].eta();}
                if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt();  genTopEta = genVarAnti[kGenTop].eta();}

                isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
                b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
                wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
                wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
                if (btag_order[bjetCandidate] > cutJetCombo) continue;
                if (isGenMatched) {hadtruth2++; cat2 = true;}

                double minT;
                double minAntiT;
                if (loopB) {
                  minT = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  minAntiT = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                } else {
                  minT = deltaR(selBJet, genVar[kGenTopB]);
                  minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]);
                }

                if ( minT < minAntiT ){
                  genFatPtAll = genVar[kGenTopW].pt();
                  genFatEtaAll = genVar[kGenTopW].pt();
                  drT_gen = deltaR(unfittedHadTopP4, genVar[kGenTop]);
                  drB_gen = deltaR(selBJet, genVar[kGenTopB]);
                  drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
                  drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  etaB_gen = genVar[kGenTopB].eta();
                  etaWj1_gen = genVar[kGenTopWj1].eta();
                  etaWj2_gen = genVar[kGenTopWj2].eta();
                  ptB_gen = genVar[kGenTopB].pt();
                  ptWj1_gen = genVar[kGenTopWj1].pt();
                  ptWj2_gen = genVar[kGenTopWj2].pt();
                  drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
                  drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
                  drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
                  drW_gen = deltaR(unfittedHadTopP4 , genVar[kGenTopW]);

                } else {
                  genFatPtAll = genVarAnti[kGenTopW].pt();
                  genFatEtaAll = genVarAnti[kGenTopW].pt();
                  drT_gen = deltaR(unfittedHadTopP4, genVarAnti[kGenTop]);
                  drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
                  drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
                  drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                  etaB_gen = genVarAnti[kGenTopB].eta();
                  etaWj1_gen = genVarAnti[kGenTopWj1].eta();
                  etaWj2_gen = genVarAnti[kGenTopWj2].eta();
                  ptB_gen = genVarAnti[kGenTopB].pt();
                  ptWj1_gen = genVarAnti[kGenTopWj1].pt();
                  ptWj2_gen = genVarAnti[kGenTopWj2].pt();
                  drb_wj1_gen= deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
                  drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
                  drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
                  drW_gen = deltaR(unfittedHadTopP4 , genVarAnti[kGenTopW]);
                }

                if ( bdt_filler ) {
                  (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
                  const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
                  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
                    mvaInput != mvaInputs.end(); ++mvaInput ) {
                    bdt_filler->operator()(mvaInput->first, mvaInput->second);
                  }
                  bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                  ("typeTop",              typeTop)
                  ("tau32Top",             -1.)
                  ("massTop",              unfittedHadTopP4.mass())
                  ("tau21W",               (*jetIter)->tau2()/(*jetIter)->tau1())
                  ("massW_SD",             (*jetIter)->msoftdrop())
                  ("btagDisc",             (*cleanedJets[bjetCandidate]).BtagCSV())
                  ("qg_Wj1",                -1.)
                  ("qg_Wj2",                -1.)
                  ("genTopPt",             genTopPt)
                  ("genTopEta",             genTopEta)
                  ("genFatPtAll", genFatPtAll)
                  ("genFatEtaAll",         std::fabs(genFatEtaAll))
                  ("drT_gen",       drT_gen)
                  ("drT_genTriplet",  drT_genTriplet)
                  ("drT_genJ_max", drT_genJ_max)
                  ("drB_gen", drB_gen)
                  ("drW_gen", drW_gen)
                  ("drWj1_gen", drWj1_gen)
                  ("drWj2_gen", drWj2_gen)
                  ("etaB_gen", etaB_gen)
                  ("etaWj1_gen", etaWj1_gen)
                  ("etaWj2_gen", etaWj2_gen)
                  ("ptB_gen", ptB_gen)
                  ("ptWj1_gen", ptWj1_gen)
                  ("ptWj2_gen", ptWj2_gen)
                  ("dr_b_wj1", deltaR(selBJet, selWJet1))
                  ("dr_b_wj2", deltaR(selBJet, selWJet2))
                  ("dr_wj1_wj2", deltaR(selBJet, selWJet2))
                  ("dr_b_wj1_gen", drb_wj1_gen)
                  ("dr_b_wj2_gen", drb_wj2_gen)
                  ("dr_wj1_wj2_gen", drwj1_wj2_gen)
                  ("collectionSize",       jet_ptrsAK8.size())
                  ("bjet_tag_position",    btag_order[bjetCandidate])
                  ("bWj1Wj2_isGenMatched", isGenMatched)
                  ("fatjet_isGenMatched",  fatjet_isGenMatched)
                  ("b_isGenMatched",       b_isGenMatched)
                  ("Wj1_isGenMatched", wj1_isGenMatched)
                  ("Wj2_isGenMatched", wj2_isGenMatched)
                  ("counter",        analyzedEntries)
                  ("nbjets",  selBJets_medium.size())
                  ("nbjets_loose",  selBJets_loose.size())
                  ("njets",  selJets.size())
                  ("passJetSel", passJetSel)
                  ("HTTv2_area", HTTv2_area)
                  ("HTTv2_Ropt", HTTv2_Ropt)
                  ("HTTv2_RoptCalc", HTTv2_RoptCalc)
                  ("genTopMassFromW", genTopMassFromW )
                  ("genTopMassFromWj", genTopMassFromWj )
                  ("genWMassFromWj", genWMassFromWj )
                  ("genAntiTopMassFromW", genAntiTopMassFromW )
                  ("genAntiTopMassFromWj", genAntiTopMassFromWj )
                  ("genAntiWMassFromWj", genAntiWMassFromWj )
                  ("genWMass", genWMass)
                  ("genAntiWMass", genAntiWMass)
		  ("atan_m13_div_m12", 1.)
                  ("m23_div_m123",1.)
                  ("Rmin_square_one_plus_m13_div_m12_square",1.)
                  ("Rmax_square_one_plus_m13_div_m12_square",1.)

                      .fill();
                }
              } //else { std::cout<<" type2 akt8 did not had subjets "<<std::endl; continue;}
            }
          } // end typeTop == 2 ak8 loop
        } // end if enough cleanJets.size()
          // store b-tag classification
          //std::cout<<std::endl;
          //std::cout<<"btag ordering  ";
          //for (auto i: btag_order_selJets) std::cout << i << " ";
          ///*
        if (doResolved) {
          //std::cout<<" typeTop = "<<typeTop<<" collectionSize "<< collectionSize <<std::endl;
          if (selJets.size() > 2) {
          std::vector<double> btag_disc = getBdiscr(selJets);
          auto btag_order_selJets = calRank(btag_disc);
          typeTop = 3;
          std::cout<<" typeTop = "<<typeTop<<std::endl;
          countResolved++;
          for ( unsigned int bjetCandidate = 0; bjetCandidate < selJets.size(); bjetCandidate++ )  {
            for ( std::vector<const RecoJet*>::const_iterator selWJet1Candidate = selJets.begin();
              selWJet1Candidate != selJets.end(); ++selWJet1Candidate ) {
               if ( (*selWJet1Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
               for ( std::vector<const RecoJet*>::const_iterator selWJet2Candidate = selWJet1Candidate + 1;
                 selWJet2Candidate != selJets.end(); ++selWJet2Candidate ) {
                  //std::cout<<" bjetCandidate = "<<bjetCandidate<<std::endl;
                  if ( (*selWJet2Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
                  if ( (*selWJet2Candidate)->pt() == (*selWJet1Candidate)->pt() ) continue;
                  selBJet = (*selJets[bjetCandidate]).p4();
                  selWJet1 = (*selWJet1Candidate)->p4();
                  selWJet2 = (*selWJet2Candidate)->p4();

                  std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
                    selBJet, selWJet1, selWJet2,
                    genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2]
                  );
                  std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
                    selBJet, selWJet1, selWJet2,
                    genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]
                  );
                  if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt();  genTopEta = genVar[kGenTop].eta();}
                  if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt();  genTopEta = genVarAnti[kGenTop].eta();}

                  isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                  fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
                  b_isGenMatched = (genMatchingTop[kGenMatchedBJet] || genMatchingAntiTop[kGenMatchedBJet]);
                  wj1_isGenMatched = (genMatchingTop[kGenMatchedWJet1] || genMatchingAntiTop[kGenMatchedWJet1]);
                  wj2_isGenMatched = (genMatchingTop[kGenMatchedWJet2] || genMatchingAntiTop[kGenMatchedWJet2]);
                  //std::cout<<" done loading flags "<<std::endl;
                  if (btag_order_selJets[bjetCandidate] > cutJetCombo) continue;
                  if (isGenMatched) {hadtruth3++; cat3 = true;}
                  //std::cout<<"btag position = "<< btag_order[bjetCandidate] <<std::endl;

                  // debug gen-matching
                  genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenTop);
                  genVarAnti = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop);
                  double minT = deltaR(selBJet, genVar[kGenTopB]) + std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2])) + std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                  double minAntiT = deltaR(selBJet, genVarAnti[kGenTopB]) + std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2])) + std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                  if ( minT < minAntiT ){
                    genFatPtAll = genVar[kGenTopW].pt();
                    genFatEtaAll = genVar[kGenTopW].pt();
                    drB_gen = deltaR(selBJet, genVar[kGenTopB]);
                    drWj1_gen = std::min(deltaR(selWJet1, genVar[kGenTopWj1]),deltaR(selWJet1, genVar[kGenTopWj2]));
                    drWj2_gen = std::min(deltaR(selWJet2, genVar[kGenTopWj2]),deltaR(selWJet2, genVar[kGenTopWj1]));
                    etaB_gen = genVar[kGenTopB].eta();
                    etaWj1_gen = genVar[kGenTopWj1].eta();
                    etaWj2_gen = genVar[kGenTopWj2].eta();
                    ptB_gen = genVar[kGenTopB].pt();
                    ptWj1_gen = genVar[kGenTopWj1].pt();
                    ptWj2_gen = genVar[kGenTopWj2].pt();
                    drb_wj1_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj1]);
                    drb_wj2_gen = deltaR(genVar[kGenTopB], genVar[kGenTopWj2]);
                    drwj1_wj2_gen = deltaR(genVar[kGenTopWj1], genVar[kGenTopWj2]);
                  } else {
                    genFatPtAll = genVarAnti[kGenTopW].pt();
                    genFatEtaAll = genVarAnti[kGenTopW].pt();
                    drB_gen = deltaR(selBJet, genVarAnti[kGenTopB]);
                    drWj1_gen = std::min(deltaR(selWJet1, genVarAnti[kGenTopWj1]),deltaR(selWJet1, genVarAnti[kGenTopWj2]));
                    drWj2_gen = std::min(deltaR(selWJet2, genVarAnti[kGenTopWj2]),deltaR(selWJet2, genVarAnti[kGenTopWj1]));
                    etaB_gen = genVarAnti[kGenTopB].eta();
                    etaWj1_gen = genVarAnti[kGenTopWj1].eta();
                    etaWj2_gen = genVarAnti[kGenTopWj2].eta();
                    ptB_gen = genVarAnti[kGenTopB].pt();
                    ptWj1_gen = genVarAnti[kGenTopWj1].pt();
                    ptWj2_gen = genVarAnti[kGenTopWj2].pt();
                    drb_wj1_gen= deltaR(genVarAnti[kGenTopB], genVarAnti[kGenTopWj1]);
                    drb_wj2_gen = deltaR(genVarAnti[kGenTopB], genVar[kGenTopWj2]);
                    drwj1_wj2_gen = deltaR(genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2]);
                  }

                  if ( bdt_filler ) {
                    (*hadTopTaggerFill)(selBJet, selWJet1, selWJet2);
                    const std::map<std::string, double>& mvaInputs =  hadTopTaggerFill->mvaInputs();
                    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
                      mvaInput != mvaInputs.end(); ++mvaInput ) {
                      bdt_filler->operator()(mvaInput->first, mvaInput->second);
                    }
                    //std::cout<<" pass fill kin "<<std::endl;
                  bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                  ("typeTop",              typeTop)
                  ("tau32Top",              -1.)
                  ("massTop",              -1.) // should be the one calculated with the groomed jet
                  ("tau21W",                -1.)
                  ("massW_SD",             -1.) // maybe add the kinfitted mass here
                  ("btagDisc",             (*selJets[bjetCandidate]).BtagCSV())
                  ("qg_Wj1",               (*selWJet1Candidate)->QGDiscr())
                  ("qg_Wj2",               (*selWJet2Candidate)->QGDiscr())
                  ("genTopPt",             genTopPt)
                  ("genTopEta",             genTopEta)
                  ("genFatPtAll", genFatPtAll)
                  ("genFatEtaAll",         std::fabs(genFatEtaAll))
                  ("drT_gen",       drT_gen)
                  ("drT_genTriplet",  drT_genTriplet)
                  ("drT_genJ_max", drT_genJ_max)
                  ("drB_gen", drB_gen)
                  ("drW_gen", drW_gen)
                  ("drWj1_gen", drWj1_gen)
                  ("drWj2_gen", drWj2_gen)
                  ("etaB_gen", etaB_gen)
                  ("etaWj1_gen", etaWj1_gen)
                  ("etaWj2_gen", etaWj2_gen)
                  ("ptB_gen", ptB_gen)
                  ("ptWj1_gen", ptWj1_gen)
                  ("ptWj2_gen", ptWj2_gen)
                  ("dr_b_wj1", deltaR(selBJet, selWJet1))
                  ("dr_b_wj2", deltaR(selBJet, selWJet2))
                  ("dr_wj1_wj2", deltaR(selBJet, selWJet2))
                  ("dr_b_wj1_gen", drb_wj1_gen)
                  ("dr_b_wj2_gen", drb_wj2_gen)
                  ("dr_wj1_wj2_gen", drwj1_wj2_gen)
                  ("collectionSize",       selJets.size())
                  ("bjet_tag_position",    btag_order_selJets[bjetCandidate])
                  ("bWj1Wj2_isGenMatched", isGenMatched)
                  ("fatjet_isGenMatched",  false)
                  ("b_isGenMatched",       b_isGenMatched)
                  ("Wj1_isGenMatched", wj1_isGenMatched)
                  ("Wj2_isGenMatched", wj2_isGenMatched)
                  ("counter",         analyzedEntries)
                  ("nbjets",  selBJets_medium.size())
                  ("nbjets_loose",  selBJets_loose.size())
                  ("njets",  selJets.size())
                  ("passJetSel", passJetSel)
                  ("HTTv2_area", HTTv2_area)
                  ("HTTv2_Ropt", HTTv2_Ropt)
                  ("HTTv2_RoptCalc", HTTv2_RoptCalc)
                  ("genTopMassFromW", genTopMassFromW )
                  ("genTopMassFromWj", genTopMassFromWj )
                  ("genWMassFromWj", genWMassFromWj )
                  ("genAntiTopMassFromW", genAntiTopMassFromW )
                  ("genAntiTopMassFromWj", genAntiTopMassFromWj )
                  ("genAntiWMassFromWj", genAntiWMassFromWj )
                  ("genWMass", genWMass)
                  ("genAntiWMass", genAntiWMass)
                      .fill();
                 }
              }
            }
          } // end typeTop == 3 loop
        } // end if has 3 jets
      } // end doResolved
        //*/
      //<< "Does not fall in any category " << " !!\n";
  //}

		++selectedEntries;
    //selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
    if (cat1 && cat2 && !cat3) ca1_cat2++;
    if (cat2 && cat3 && !cat1) cat2_cat3++;
    if (cat3 && cat1 && !cat2) cat3_cat1++ ;
    if (cat3 && cat2 && cat1) cat3_cat2_cat1++;
  }
  //if(bdt_filler) bdt_filler->write();

  std::cout << "AK8 separation = " << countFatTop << " " << countFatAK8 << " " << countResolved<< " " << countFatTop+countFatAK8+countResolved<<std::endl;
  std::cout << "truth counters = "<<hadtruth1 << " "<<hadtruth2 << " "<<hadtruth3 << std::endl;
  std::cout << "overlaps = "<< ca1_cat2 << " "<< cat2_cat3 << " "<< cat3_cat1 << " " << cat3_cat2_cat1 << std::endl;

  std::cout << "HTTv2 > 0  " << countFatTop <<std::endl;
  std::cout << "+ closest genTop > 200 " << countFatTopPt200 << " " << countFatTopbmatch << " " << countFatTopWj1match << " " << countFatTopWj2match <<std::endl;

  std::cout << countFatWpt130 << "fatW  " << countFatWjets << " " << " " << countFatW <<std::endl;

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;

  delete jetReader;
  delete genJetReader;
  delete lheInfoReader;
  delete hadTopTaggerFill;
  delete inputTree;
  delete eventWeightManager;

  clock.Show("analyze_hadTopTagger");

  return EXIT_SUCCESS;
}
