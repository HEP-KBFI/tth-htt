#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet
#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <FWCore/Utilities/interface/Exception.h> // cms::Exception
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles
#include <DataFormats/Math/interface/LorentzVector.h> // math::PtEtaPhiMLorentzVector

#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TEfficiency.h>
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::
#include <TH2.h> // TH2

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
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
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_charge_flip.h" // EvtHistManager_charge_flip
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
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
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <cstring> // std::strncpm
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

enum { kFR_disabled, kFR_2lepton };

const std::string hadTauSelection = "dR03mvaMedium"; // CV: dummy value that has no effect, but is required by Data_to_MC_CorrectionInterface

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
  if      ( pT >= 15. && pT < 25. ) idxBin += 1;
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
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isZee = (std::strncmp(process_string.data(), "DY", 2) == 0);
  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

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
  bool isMC_tH = ( process_string == "tHq" || process_string == "tHW" ) ? true : false;
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  bool isCentral = ( central_or_shift == "central" ) ? true : false;
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
  }
  
  checkOptionValidity(central_or_shift, isMC);
  const int electronPt_option          = getElectronPt_option   (central_or_shift);
  const int jetPt_option               = getJet_option          (central_or_shift, isMC);
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  const int lheScale_option            = getLHEscale_option     (central_or_shift);
  const int jetBtagSF_option           = getBTagWeight_option   (central_or_shift);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> jetToLeptonFakeRate_option = " << jetToLeptonFakeRate_option << "\n"
       " -> lheScale_option            = " << lheScale_option            << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option           << "\n"
       " -> jetPt_option               = " << jetPt_option               << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection); 
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_charge_flip", __LINE__) << "Invalid era = " << era;
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
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

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
  EventInfo eventInfo(false, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_2e });
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree->registerReader(jetReader);
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenPhotonReader* genPhotonReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if ( !readGenObjects ) {
      if ( branchName_genLeptons != "" ) {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree -> registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree -> registerReader(genHadTauReader);
      }
      if ( branchName_genPhotons != "" ) {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree -> registerReader(genPhotonReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
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
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionSS.data()), central_or_shift.data()));
  preselElectronHistManagerSS.bookHistograms(fs);
  ElectronHistManager preselElectronHistManagerOS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons", charge_and_leptonSelectionOS.data()), central_or_shift.data()));
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

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/unbiased/genEvt", charge_and_leptonSelectionSS.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/genEvt", charge_and_leptonSelectionSS.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("charge_flip_%s/sel/lheInfo", charge_and_leptonSelectionSS.data()), central_or_shift));
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
    process_string, Form("charge_flip_%s/sel/cutFlow", charge_and_leptonSelectionSS.data()), central_or_shift
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "trigger",
    "= 2 presel electrons",
    "presel electron trigger match",
    "= 0 presel muons",
    "= 2 sel electrons",
    "sel electron trigger match",
    "lead electron pT > 25 GeV && sublead electron pT > 15 GeV",
    "tight electron charge",
    "60 < m(ee) < 120 GeV",
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

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo) ) {
      continue;
    }

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

    double evtWeight_inclusive = 1.;
    if(isMC)
    {
      if(apply_genWeight)    evtWeight_inclusive *= boost::math::sign(eventInfo.genWeight);
      if(isMC_tH)            evtWeight_inclusive *= eventInfo.genWeight_tH;
      if(eventWeightManager) evtWeight_inclusive *= eventWeightManager->getWeight();
      lheInfoReader->read();
      evtWeight_inclusive *= lheInfoReader->getWeight_scale(lheScale_option);
      evtWeight_inclusive *= eventInfo.pileupWeight;
      evtWeight_inclusive *= lumiScale;
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e);
    
    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    if ( !(selTrigger_1e || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl; 
	std::cout << " (selTrigger_1e = " << isTriggered_1e 
		  << ", selTrigger_2e = " << isTriggered_2e << ")" << std::endl;
      }
      continue;
    }
        
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && isTriggered_2e ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl; 
	  std::cout << " (selTrigger_1e = " << selTrigger_1e 
		    << ", isTriggered_2e = " << isTriggered_2e << ")" << std::endl;
	}
	continue; 
      }
    }
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);

    if ( (selTrigger_2e && !apply_offline_e_trigger_cuts_2e) ||
	 (selTrigger_1e && !apply_offline_e_trigger_cuts_1e) ) {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
      tightElectronSelector.enable_offline_e_trigger_cuts();
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
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else if ( leptonSelection == kTight    ) selElectrons = tightElectrons;
    else assert(0);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if ( isMC && redoGenMatching && !fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);
    }

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
    cutFlowTable.update("= 2 presel electrons");
    cutFlowHistManager->fillHistograms("= 2 presel electrons", lumiScale);
    
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
    cutFlowTable.update("presel electron trigger match");
    cutFlowHistManager->fillHistograms("presel electron trigger match", lumiScale);

    // require exactly zero preselected muons
    if ( !(preselMuons.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS 0 presel Muons selection" << std::endl; 
	std::cout << " (#preselMuons = " << preselMuons.size() 
		  << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("= 0 presel muons");
    cutFlowHistManager->fillHistograms("= 0 presel muons", lumiScale);

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= evtWeight_inclusive;
      evtWeight *= get_BtagWeight(selJets);
    }

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
    cutFlowTable.update("= 2 sel electrons");
    cutFlowHistManager->fillHistograms("= 2 sel electrons", evtWeight);

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
    cutFlowTable.update("sel electron trigger match");
    cutFlowHistManager->fillHistograms("sel electron trigger match", evtWeight);

    const RecoElectron* selElectron_lead = selElectrons[0];
    const GenLepton* genElectron_lead = 0;
    if ( selElectron_lead->genLepton() && abs(selElectron_lead->genLepton()->pdgId()) == 11 ) {
      genElectron_lead = selElectron_lead->genLepton();
    }
    double selElectron_lead_pT = selElectron_lead->cone_pt();
    double selElectron_lead_eta = selElectron_lead->eta();
    double selElectron_lead_absEta = std::fabs(selElectron_lead_eta);
    double selElectron_lead_phi = selElectron_lead->phi();
    double selElectron_lead_mass = selElectron_lead->mass();

    const RecoElectron* selElectron_sublead = selElectrons[1];
    const GenLepton* genElectron_sublead = 0;
    if ( selElectron_sublead->genLepton() && abs(selElectron_sublead->genLepton()->pdgId()) == 11 ) {
      genElectron_sublead = selElectron_sublead->genLepton();
    }
    double selElectron_sublead_pT = selElectron_sublead->cone_pt();
    double selElectron_sublead_eta = selElectron_sublead->eta();
    double selElectron_sublead_absEta = std::fabs(selElectron_sublead_eta);
    double selElectron_sublead_phi = selElectron_sublead->phi();
    double selElectron_sublead_mass = selElectron_sublead->mass();

    if ( electronPt_option == kElectronPt_scaleUp_barrel ) {
      if ( selElectron_lead_absEta    < 1.479 ) selElectron_lead_pT *= 1.01;
      if ( selElectron_sublead_absEta < 1.479 ) selElectron_sublead_pT *= 1.01;
    } else if ( electronPt_option == kElectronPt_scaleDown_barrel ) {
      if ( selElectron_lead_absEta    < 1.479 ) selElectron_lead_pT *= 0.99;
      if ( selElectron_sublead_absEta < 1.479 ) selElectron_sublead_pT *= 0.99;
    } else if ( electronPt_option == kElectronPt_scaleUp_endcap ) {
      if ( selElectron_lead_absEta    > 1.479 ) selElectron_lead_pT *= 1.01;
      if ( selElectron_sublead_absEta > 1.479 ) selElectron_sublead_pT *= 1.01;
    } else if ( electronPt_option == kElectronPt_scaleDown_endcap ) {
      if ( selElectron_lead_absEta    > 1.479 ) selElectron_lead_pT *= 0.99;
      if ( selElectron_sublead_absEta > 1.479 ) selElectron_sublead_pT *= 0.99;
    } else if ( electronPt_option == kElectronPt_resUp ) {
      if ( genElectron_lead    ) selElectron_lead_pT += 0.25*(selElectron_lead_pT - genElectron_lead->pt());
      if ( genElectron_sublead ) selElectron_sublead_pT += 0.25*(selElectron_sublead_pT - genElectron_sublead->pt());
    } else if ( electronPt_option == kElectronPt_resDown ) {
      if ( genElectron_lead    ) selElectron_lead_pT -= 0.25*(selElectron_lead_pT - genElectron_lead->pt());
      if ( genElectron_sublead ) selElectron_sublead_pT -= 0.25*(selElectron_sublead_pT - genElectron_sublead->pt());
    }
    math::PtEtaPhiMLorentzVector selElectron_lead_p4;
    const RecoElectron* selElectron_lead_tmp = 0;
    const GenLepton* genElectron_lead_tmp = 0;
    math::PtEtaPhiMLorentzVector selElectron_sublead_p4;
    const RecoElectron* selElectron_sublead_tmp = 0;
    const GenLepton* genElectron_sublead_tmp = 0;
    if ( selElectron_sublead_pT > selElectron_lead_pT ) { // CV: leading and subleading electrons have swapped order due to being affected directly by the systematic variations
                                                          //    (this may happen if the pT of both electrons are similar)
      selElectron_lead_p4 = math::PtEtaPhiMLorentzVector(selElectron_sublead_pT, selElectron_sublead_eta, selElectron_sublead_phi, selElectron_sublead_mass);
      selElectron_lead_tmp = selElectron_sublead;
      genElectron_lead_tmp = genElectron_sublead;
      selElectron_sublead_p4 = math::PtEtaPhiMLorentzVector(selElectron_lead_pT, selElectron_lead_eta, selElectron_lead_phi, selElectron_lead_mass);
      selElectron_sublead_tmp = selElectron_lead;
      genElectron_sublead_tmp = genElectron_lead;
    } else {
      selElectron_lead_p4 = math::PtEtaPhiMLorentzVector(selElectron_lead_pT, selElectron_lead_eta, selElectron_lead_phi, selElectron_lead_mass);
      selElectron_lead_tmp = selElectron_lead;
      genElectron_lead_tmp = genElectron_lead;
      selElectron_sublead_p4 = math::PtEtaPhiMLorentzVector(selElectron_sublead_pT, selElectron_sublead_eta, selElectron_sublead_phi, selElectron_sublead_mass);
      selElectron_sublead_tmp = selElectron_sublead;
      genElectron_sublead_tmp = genElectron_sublead;
    }
    double selElectron_lead_charge = selElectron_lead_tmp->charge();
    Particle::LorentzVector genElectron_lead_p4; // generator-level electron associated to the reconstructed electron of higher pT 
                                                 // (not necessarily the generator-level electron of higher pT!)
    double genElectron_lead_charge = 0.;
    bool isGenElectron_lead = false;
    if ( genElectron_lead_tmp ) {
      genElectron_lead_p4 = genElectron_lead_tmp->p4();
      genElectron_lead_charge = genElectron_lead_tmp->charge();
      isGenElectron_lead = true;
    }
    double selElectron_sublead_charge = selElectron_sublead_tmp->charge();
    Particle::LorentzVector genElectron_sublead_p4; // generator-level electron associated to the reconstructed electron of lower pT 
                                                    // (not necessarily the generator-level electron of lower pT!)
    double genElectron_sublead_charge = 0.;
    bool isGenElectron_sublead = false;
    if ( genElectron_sublead_tmp ) {
      genElectron_sublead_p4 = genElectron_sublead_tmp->p4();
      genElectron_sublead_charge = genElectron_sublead_tmp->charge();
      isGenElectron_sublead = true;
    }

    double m_ee = (selElectron_lead_p4 + selElectron_sublead_p4).mass();
    
    double minPt_lead = 20.;
    double minPt_sublead = 15.;
    if ( !(selElectron_lead_pT > minPt_lead && selElectron_sublead_pT > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selElectron_lead_p4.pt() << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selElectron_sublead_p4.pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead electron pT > 25 GeV && sublead electron pT > 15 GeV");
    cutFlowHistManager->fillHistograms("lead electron pT > 25 GeV && sublead electron pT > 15 GeV", evtWeight);
    
    bool failsTightChargeCut = false;
    for ( std::vector<const RecoElectron*>::const_iterator electron = selElectrons.begin();
	  electron != selElectrons.end(); ++electron ) {
      if ( (*electron)->tightCharge() < 2 ) failsTightChargeCut = true;
    }
    if ( failsTightChargeCut ) {
      if ( run_lumi_eventSelector ) {
      	std::cout << "event FAILS tight lepton charge requirement." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("tight electron charge");
    cutFlowHistManager->fillHistograms("tight electron charge", evtWeight);

    if ( !(m_ee > 60. && m_ee < 120.) ) {
      if ( run_lumi_eventSelector ) {
      	std::cout << "event FAILS mass window requirement." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("60 < m(ee) < 120 GeV");
    cutFlowHistManager->fillHistograms("60 < m(ee) < 120 GeV", evtWeight);
          
    bool isCharge_SS = selElectron_lead_charge*selElectron_sublead_charge > 0;
    bool isCharge_OS = selElectron_lead_charge*selElectron_sublead_charge < 0;

    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        kElectron, selElectron_lead_p4.pt(), selElectron_lead_p4.eta(), 
	kElectron, selElectron_sublead_p4.pt(), selElectron_sublead_p4.eta());

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria      
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      double weight_data_to_MC_correction_tight = 1.;
    
      if ( leptonSelection == kFakeable ) {
	weight_data_to_MC_correction_tight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
        weight_data_to_MC_correction_tight = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }
      evtWeight *= weight_data_to_MC_correction_tight;
              
      double weight_fakeRate = 1.;
      if ( applyFakeRateWeights == kFR_2lepton) {
        double prob_fake_electron_lead = leptonFakeRateInterface->getWeight_e(selElectron_lead_tmp->cone_pt(), selElectron_lead_tmp->absEta());
        bool passesTight_electron_lead = isMatched(*selElectron_lead_tmp, tightElectrons);
        double prob_fake_electron_sublead = leptonFakeRateInterface->getWeight_e(selElectron_sublead_tmp->cone_pt(), selElectron_sublead_tmp->absEta());
        bool passesTight_electron_sublead = isMatched(*selElectron_sublead_tmp, tightElectrons);
        weight_fakeRate = getWeight_2L(
	  prob_fake_electron_lead, passesTight_electron_lead, 
	  prob_fake_electron_sublead, passesTight_electron_sublead);
        evtWeight *= weight_fakeRate;
      }
    }

//--- fill histograms with events passing final selection
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
    selElectron_lead_absEta = std::fabs(selElectron_lead_p4.eta());
	  histogram_prob_charge_flip_gen_rec->FillWeighted(selElectron_lead_charge != genElectron_lead_charge, evtWeight, selElectron_lead_p4.pt(), selElectron_lead_absEta);
    selElectron_sublead_absEta = std::fabs(selElectron_sublead_p4.eta());
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
	}
      } else {
	// DY_fake
	evtHistManager_DY_fake->fillHistograms(selElectron_lead_p4, selElectron_sublead_p4, m_ee, isCharge_SS, evtWeight);
      }
    }

    if      ( isCharge_SS ) preselElectronHistManagerSS.fillHistograms(preselElectrons, evtWeight);
    else if ( isCharge_OS ) preselElectronHistManagerOS.fillHistograms(preselElectrons, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    
    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    if ( isCentral ) {
      histogram_selectedEntries->Fill(0.);
    }
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n";

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
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);

  clock.Show("analyze_charge_flip");

  return EXIT_SUCCESS;
}
