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
#include <TError.h> // gErrorAbortLevel, kError

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_WZctrl.h" // EvtHistManager_WZctrl
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

double getEvtWeight(double lumiScale, double genWeight, bool apply_genWeight, double pileupWeight,
		    LHEInfoReader* lheInfoReader, int lheScale_option,
		    Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface, bool apply_trigger_bits,
		    const RecoLepton* selLepton_lead, const RecoLepton* selLepton_sublead, const RecoLepton* selLepton_third, 
		    const RecoHadTau* selHadTau,
		    const std::vector<const RecoJet*>& selJets)
{
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
  double evtWeight = 1.;
 
  evtWeight *= lumiScale;
  if ( apply_genWeight ) evtWeight *= boost::math::sign(genWeight);
  evtWeight *= pileupWeight;
  evtWeight *= lheInfoReader->getWeight_scale(lheScale_option);
  evtWeight *= get_BtagWeight(selJets);

  if ( selLepton_third ) {
    dataToMCcorrectionInterface->setLeptons(
      getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta(), 
      getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta(), 
      getLeptonType(selLepton_third->pdgId()), selLepton_third->pt(), selLepton_third->eta());
  } else {
    dataToMCcorrectionInterface->setLeptons(
      getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta(), 
      getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta());
  }

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
  if ( !apply_trigger_bits ) {
    evtWeight *= dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
  }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria      
  evtWeight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
  evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();
   
//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
  evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
  if ( selHadTau ) {
    int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);
    dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());
    evtWeight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
    evtWeight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
    evtWeight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
  }

  return evtWeight;
}

/**
 * @brief Produce datacard and control plots for WZctrl categories.
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

  std::cout << "<analyze_WZctrl>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_WZctrl");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_WZctrl") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_WZctrl");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if ( era_string == "2017" ) era = kEra_2017;
  else throw cms::Exception("analyze_WZctrl") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");
  vstring triggerNames_1e2mu = cfg_analyze.getParameter<vstring>("triggers_1e2mu");
  std::vector<hltPath*> triggers_1e2mu = create_hltPaths(triggerNames_1e2mu);
  bool use_triggers_1e2mu = cfg_analyze.getParameter<bool>("use_triggers_1e2mu");
  vstring triggerNames_2e1mu = cfg_analyze.getParameter<vstring>("triggers_2e1mu");
  std::vector<hltPath*> triggers_2e1mu = create_hltPaths(triggerNames_2e1mu);
  bool use_triggers_2e1mu = cfg_analyze.getParameter<bool>("use_triggers_2e1mu");
  vstring triggerNames_3mu = cfg_analyze.getParameter<vstring>("triggers_3mu");
  std::vector<hltPath*> triggers_3mu = create_hltPaths(triggerNames_3mu);
  bool use_triggers_3mu = cfg_analyze.getParameter<bool>("use_triggers_3mu");
  vstring triggerNames_3e = cfg_analyze.getParameter<vstring>("triggers_3e");
  std::vector<hltPath*> triggers_3e = create_hltPaths(triggerNames_3e);
  bool use_triggers_3e = cfg_analyze.getParameter<bool>("use_triggers_3e");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");
  bool apply_offline_e_trigger_cuts_1e2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e2mu");
  bool apply_offline_e_trigger_cuts_2e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e1mu");
  bool apply_offline_e_trigger_cuts_3mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3mu");
  bool apply_offline_e_trigger_cuts_3e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_3e");

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  //std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  //int hadTauSelection = -1;
  //if      ( hadTauSelection_part1 == "Loose"    ) hadTauSelection = kLoose;
  //else if ( hadTauSelection_part1 == "Fakeable" ) hadTauSelection = kFakeable;
  //else if ( hadTauSelection_part1 == "Tight"    ) hadTauSelection = kTight;
  //else throw cms::Exception("analyze_WZctrl") 
  //  << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  const int jetPt_option     = getJet_option       (central_or_shift, isMC);
  const int lheScale_option  = getLHEscale_option  (central_or_shift, isMC);
  const int jetBtagSF_option = getBTagWeight_option(central_or_shift, isMC);
  const int hadTauPt_option  = getHadTauPt_option  (central_or_shift, isMC);
  const int met_option       = getMET_option       (central_or_shift, isMC);

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
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

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

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
  EventInfo eventInfo(isSignal, isMC, false);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  for(const std::vector<hltPath*> hltPaths: { triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu, triggers_1e2mu, triggers_2e1mu, triggers_3e, triggers_3mu })
    {
      inputTree -> registerReader(hltPaths);
    }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight hadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) hadTauSelector.set(hadTauSelection_part2);
  hadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  hadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  
  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters);
  inputTree -> registerReader(metFilterReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
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
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis
  std::string mvaFileName_2lss_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttV;
  mvaInputVariables_2lss_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttV.push_back("MT_met_lep1");
  mvaInputVariables_2lss_ttV.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[1]]");
  TMVAInterface mva_2lss_ttV(mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttbar;
  mvaInputVariables_2lss_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttbar.push_back("min(met_pt,400)");
  mvaInputVariables_2lss_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_ttbar.push_back("MT_met_lep1");
  TMVAInterface mva_2lss_ttbar(mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_2lss = get_mvaInputVariables(mvaInputVariables_2lss_ttV, mvaInputVariables_2lss_ttbar);
  std::map<std::string, double> mvaInputs_2lss;

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 3l category of ttH multilepton analysis
  std::string mvaFileName_3l_ttV = "tthAnalysis/HiggsToTauTau/data/3l_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_3l_ttV;
  mvaInputVariables_3l_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_3l_ttV.push_back("MT_met_lep1");
  mvaInputVariables_3l_ttV.push_back("nJet25_Recl");
  mvaInputVariables_3l_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_3l_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_3l_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  mvaInputVariables_3l_ttV.push_back("LepGood_conePt[iF_Recl[2]]");
  TMVAInterface mva_3l_ttV(mvaFileName_3l_ttV, mvaInputVariables_3l_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_3l_ttbar = "tthAnalysis/HiggsToTauTau/data/3l_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_3l_ttbar;
  mvaInputVariables_3l_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_3l_ttbar.push_back("MT_met_lep1");
  mvaInputVariables_3l_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_3l_ttbar.push_back("mhtJet25_Recl");
  mvaInputVariables_3l_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_3l_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_3l_ttbar.push_back("mindr_lep2_jet");
  TMVAInterface mva_3l_ttbar(mvaFileName_3l_ttbar, mvaInputVariables_3l_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::vector<std::string> mvaInputVariables_3l = get_mvaInputVariables(mvaInputVariables_3l_ttV, mvaInputVariables_3l_ttbar);
  std::map<std::string, double> mvaInputs_3l;

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    trained by Arun for 2lss_1tau category 
  std::string mvaFileName_2lss_1tau_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttV_sklearn_10var.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttV;
  mvaInputVariables_2lss_1tau_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttV.push_back("lep1_pt");
  mvaInputVariables_2lss_1tau_ttV.push_back("lep2_pt");
  mvaInputVariables_2lss_1tau_ttV.push_back("max_lep_eta");
  mvaInputVariables_2lss_1tau_ttV.push_back("mT_lep1");
  mvaInputVariables_2lss_1tau_ttV.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttV.push_back("mTauTauVis1");
  mvaInputVariables_2lss_1tau_ttV.push_back("mTauTauVis2");
  TMVAInterface mva_2lss_1tau_ttV(mvaFileName_2lss_1tau_ttV, mvaInputVariables_2lss_1tau_ttV);

  std::string mvaFileName_2lss_1tau_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_1tau_ttbar_sklearn_11var.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_1tau_ttbar;
  mvaInputVariables_2lss_1tau_ttbar.push_back("nJet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_1tau_ttbar.push_back("max_lep_eta");
  mvaInputVariables_2lss_1tau_ttbar.push_back("ptmiss");
  mvaInputVariables_2lss_1tau_ttbar.push_back("mT_lep1");
  mvaInputVariables_2lss_1tau_ttbar.push_back("htmiss");
  mvaInputVariables_2lss_1tau_ttbar.push_back("dr_leps");
  mvaInputVariables_2lss_1tau_ttbar.push_back("tau_pt");
  mvaInputVariables_2lss_1tau_ttbar.push_back("dr_lep1_tau");
  TMVAInterface mva_2lss_1tau_ttbar(mvaFileName_2lss_1tau_ttbar, mvaInputVariables_2lss_1tau_ttbar);

  std::vector<std::string> mvaInputVariables_2lss_1tau = get_mvaInputVariables(mvaInputVariables_2lss_1tau_ttV, mvaInputVariables_2lss_1tau_ttbar);
  std::map<std::string, double> mvaInputs_2lss_1tau;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  ElectronHistManager preselElectronHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/electrons", era_string, central_or_shift));
  preselElectronHistManager.bookHistograms(fs);
  MuonHistManager preselMuonHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/muons", era_string, central_or_shift));
  preselMuonHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/hadTaus", era_string, central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/jets", era_string, central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/BJets_loose", era_string, central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/BJets_medium", era_string, central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/met", era_string, central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  MEtFilterHistManager preselMEtFilterHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/metFilters", era_string, central_or_shift));
  preselMEtFilterHistManager.bookHistograms(fs);
  EvtHistManager_WZctrl preselEvtHistManager(makeHistManager_cfg(process_string, 
    "WZctrl/presel/evt", era_string, central_or_shift));
  preselEvtHistManager.bookHistograms(fs);

  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    MVAInputVarHistManager* mvaInputVariables_2lss_;
    MVAInputVarHistManager* mvaInputVariables_2lss_1tau_;
    EvtHistManager_WZctrl* evt_;
    std::map<std::string, EvtHistManager_WZctrl*> evt_in_decayModes_;
  };
  std::map<int, selHistManagerType*> selHistManagers;
  enum { k2lepton, k3lepton, k2lepton_1tau };
  for ( int idxEvtSel = k2lepton; idxEvtSel <= k2lepton_1tau; ++idxEvtSel ) {

    std::string histogramDir = "WZctrl";
    if      ( idxEvtSel == k2lepton      ) histogramDir.append("_2lepton");
    else if ( idxEvtSel == k3lepton      ) histogramDir.append("_3lepton");
    else if ( idxEvtSel == k2lepton_1tau ) histogramDir.append("_2lepton_1tau");
    else assert(0);

    selHistManagerType* selHistManager = new selHistManagerType();
    selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
    selHistManager->electrons_->bookHistograms(fs);
    selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/muons", histogramDir.data()), central_or_shift));
    selHistManager->muons_->bookHistograms(fs);
    selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
    selHistManager->hadTaus_->bookHistograms(fs);
    selHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/jets", histogramDir.data()), central_or_shift));
    selHistManager->jets_->bookHistograms(fs);
    selHistManager->leadJet_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/leadJet", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadJet_->bookHistograms(fs);
    selHistManager->subleadJet_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/subleadJet", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadJet_->bookHistograms(fs);
    selHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/BJets_loose", histogramDir.data()), central_or_shift));
    selHistManager->BJets_loose_->bookHistograms(fs);
    selHistManager->leadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/leadBJet_loose", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadBJet_loose_->bookHistograms(fs);
    selHistManager->subleadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/subleadBJet_loose", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadBJet_loose_->bookHistograms(fs);
    selHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/BJets_medium", histogramDir.data()), central_or_shift));
    selHistManager->BJets_medium_->bookHistograms(fs);
    selHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/met", histogramDir.data()), central_or_shift));
    selHistManager->met_->bookHistograms(fs);
    selHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/metFilters", histogramDir.data()), central_or_shift));
    selHistManager->metFilters_->bookHistograms(fs);
    selHistManager->mvaInputVariables_2lss_ = new MVAInputVarHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/mvaInputs_2lss", histogramDir.data()), central_or_shift));
    selHistManager->mvaInputVariables_2lss_->bookHistograms(fs, mvaInputVariables_2lss);
    selHistManager->mvaInputVariables_2lss_1tau_ = new MVAInputVarHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/mvaInputs_2lss_1tau", histogramDir.data()), central_or_shift));
    selHistManager->mvaInputVariables_2lss_1tau_->bookHistograms(fs, mvaInputVariables_2lss_1tau);
    selHistManager->evt_ = new EvtHistManager_WZctrl(makeHistManager_cfg(process_string, 
      Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
    selHistManager->evt_->bookHistograms(fs);
    std::map<std::string, EvtHistManager_WZctrl*> selEvtHistManager_decayMode; // key = decay mode
    const vstring decayModes_evt = eventInfo.getDecayModes();
    if ( isSignal ) {
      for ( vstring::const_iterator decayMode = decayModes_evt.begin();
            decayMode != decayModes_evt.end(); ++decayMode) {
        selHistManager->evt_in_decayModes_[*decayMode] = new EvtHistManager_WZctrl(makeHistManager_cfg(*decayMode,
          Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift));
        selHistManager->evt_in_decayModes_[*decayMode]->bookHistograms(fs);
      }
    }
    selHistManagers[idxEvtSel] = selHistManager;
  }
 
  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      "WZctrl/unbiased/genEvt", era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      "WZctrl/sel/genEvt", era_string, central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      "WZctrl/sel/lheInfo", era_string, central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
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
    histogram_analyzedEntries->Fill(0.);

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }
    cutFlowTable.update("run:ls:event selection");

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
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
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e2mu = hltPaths_isTriggered(triggers_1e2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_2e1mu = hltPaths_isTriggered(triggers_2e1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_3mu = hltPaths_isTriggered(triggers_3mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_3e = hltPaths_isTriggered(triggers_3e) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    bool selTrigger_1e2mu = use_triggers_1e2mu && isTriggered_1e2mu;
    bool selTrigger_2e1mu = use_triggers_2e1mu && isTriggered_2e1mu;
    bool selTrigger_3mu = use_triggers_3mu && isTriggered_3mu;
    bool selTrigger_3e = use_triggers_3e && isTriggered_3e;

    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu || selTrigger_1e2mu || selTrigger_2e1mu || selTrigger_3e || selTrigger_3mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl;
	std::cout << " (selTrigger_1e = " << selTrigger_1e
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_2e = " << selTrigger_2e
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2mu = " << selTrigger_2mu
		  << ", selTrigger_3e = " << selTrigger_3e
		  << ", selTrigger_2e1mu = " << selTrigger_2e1mu
		  << ", selTrigger_1e2mu = " << selTrigger_1e2mu
		  << ", selTrigger_3mu = " << selTrigger_3mu << ")" << std::endl;
      }
      continue;
    }




    
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {

      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_2e || isTriggered_1e1mu || isTriggered_2mu || isTriggered_3e || isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1e = " << selTrigger_1e
                    << ", isTriggered_1mu = " << isTriggered_1mu
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_3e = " << isTriggered_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_1e1mu || isTriggered_2mu || isTriggered_3e || isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1mu = " << selTrigger_1mu
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_3e = " << isTriggered_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e && (isTriggered_1e1mu || isTriggered_2mu || isTriggered_3e || isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_2e = " << selTrigger_2e
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_3e = " << isTriggered_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1e1mu && (isTriggered_2mu || isTriggered_3e || isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1e1mu = " << selTrigger_1e1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_3e = " << isTriggered_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2mu && (isTriggered_3e || isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_2mu = " << selTrigger_2mu
                    << ", isTriggered_3e = " << isTriggered_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_3e && (isTriggered_2e1mu || isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_3e = " << selTrigger_3e
                    << ", isTriggered_2e1mu = " << isTriggered_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e1mu && (isTriggered_1e2mu || isTriggered_3mu) ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_2e1mu = " << selTrigger_2e1mu
                    << ", isTriggered_1e2mu = " << isTriggered_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1e2mu && isTriggered_3mu ) {
        if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl;
	  std::cout << " (selTrigger_1e2mu = " << selTrigger_1e2mu
                    << ", isTriggered_3mu = " << isTriggered_3mu << ")" << std::endl;
        }
        continue;
      }
    }
    cutFlowTable.update("trigger");

    if ( (selTrigger_3mu     && !apply_offline_e_trigger_cuts_3mu)     ||
         (selTrigger_3e      && !apply_offline_e_trigger_cuts_3e)      ||
         (selTrigger_1e2mu   && !apply_offline_e_trigger_cuts_1e2mu)   ||
         (selTrigger_2e1mu   && !apply_offline_e_trigger_cuts_2e1mu)   ||
         (selTrigger_2mu     && !apply_offline_e_trigger_cuts_2mu)     ||
         (selTrigger_1mu     && !apply_offline_e_trigger_cuts_1mu)     ||
         (selTrigger_2e      && !apply_offline_e_trigger_cuts_2e)      ||
         (selTrigger_1e1mu   && !apply_offline_e_trigger_cuts_1e1mu)   ||
         (selTrigger_1e      && !apply_offline_e_trigger_cuts_1e)    ) {
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
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
    std::vector<const RecoMuon*> selMuons = tightMuons;
    
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons = tightElectrons;

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, preselHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);
  
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
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }
  
//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons, isHigherPt);
    // require two or more leptons passing loose preselection criteria 
    if ( !(preselLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS preselLeptons selection." << std::endl;
  printCollection("preselLeptons", preselLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons");

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 2 &&                            (selTrigger_2e    || selTrigger_1e                  )) ||
	   (preselElectrons.size() >= 1 && preselMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                               preselMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", #preselMuons = " << preselMuons.size() 
		  << ", selTrigger_2mu = " << selTrigger_2mu 
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2e = " << selTrigger_2e 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    } 
    cutFlowTable.update("presel lepton trigger match");

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection " << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets (1)");
    if ( !(selBJets_loose.size() == 0 && selBJets_medium.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection (1)." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("0 loose b-jets && 0 medium b-jets");
  
//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselMuonHistManager.fillHistograms(preselMuons, 1.);
    preselElectronHistManager.fillHistograms(preselElectrons, 1.);
    preselHadTauHistManager.fillHistograms(selHadTaus, 1.);
    preselJetHistManager.fillHistograms(selJets, 1.);
    preselBJet_looseHistManager.fillHistograms(selBJets_loose, 1.);
    preselBJet_mediumHistManager.fillHistograms(selBJets_medium, 1.);
    preselMEtHistManager.fillHistograms(met, mht_p4, met_LD, 1.);
    preselMEtFilterHistManager.fillHistograms(metFilters, 1.);
    preselEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1., -1., -1., -1., -1., -1., -1., -1.,
      -1., -1., 0., 1.);
  
//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons, isHigherPt);
    // require two or more leptons passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selLeptons selection." << std::endl;
	std::cout << " (#selLeptons = " << selLeptons.size() << ")" << std::endl;
	for ( size_t idxSelLepton = 0; idxSelLepton < selLeptons.size(); ++idxSelLepton ) {
	  std::cout << "selLepton #" << idxSelLepton << ":" << std::endl;
	  std::cout << (*selLeptons[idxSelLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 sel leptons");
    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];
    const RecoLepton* selLepton_third = ( selLeptons.size() >= 3 ) ? selLeptons[2] : 0;
    int sumLeptonCharge = selLepton_lead->charge() + selLepton_sublead->charge();
    if ( selLepton_third ) sumLeptonCharge += selLepton_third->charge();

     if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight taking data/MC corrections for identification, isolation, and trigger efficiency
//    of the two leading leptons into account
    double evtWeight_2lepton = 1.;
    if ( isMC ) {
      evtWeight_2lepton = getEvtWeight(
        lumiScale, eventInfo.genWeight, apply_genWeight, eventInfo.pileupWeight,
	lheInfoReader, lheScale_option,
        dataToMCcorrectionInterface, apply_trigger_bits,
	selLepton_lead, selLepton_sublead, 0, 0, selJets);
    }
  
    std::vector<const RecoLepton*> tightLeptons = mergeLeptonCollections(tightElectrons, tightMuons, isHigherPt);
    if ( !(tightLeptons.size() <= 3) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS tightLeptons selection." << std::endl;
  printCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("<= 3 tight leptons", evtWeight_2lepton);

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((fakeableElectrons.size() >= 2 &&                              (selTrigger_2e    || selTrigger_1e                  )) ||
	   (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                                 fakeableMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given fakeableLepton multiplicity." << std::endl; 
	std::cout << " (#fakeableElectrons = " << fakeableElectrons.size() 
		  << ", #fakeableMuons = " << fakeableMuons.size() 
		  << ", selTrigger_2mu = " << selTrigger_2mu 
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
		  << ", selTrigger_2e = " << selTrigger_2e 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    } 
    cutFlowTable.update("fakeable lepton trigger match", evtWeight_2lepton);

//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,    selTrigger_1e    },
        { hltPathsE::trigger_1mu,   selTrigger_1mu   },
        { hltPathsE::trigger_2e,    selTrigger_2e    },
        { hltPathsE::trigger_2mu,   selTrigger_2mu   },
        { hltPathsE::trigger_1e1mu, selTrigger_1e1mu },
      };
      if(! hltFilter(trigger_bits, fakeableLeptons, {}))
      {
        if(run_lumi_eventSelector || isDEBUG)
        {
          std::cout << "event FAILS HLT filter matching\n";
        }
        continue;
      }
    }
    cutFlowTable.update("HLT filter matching", evtWeight_2lepton);
      
    // apply requirement on jets (incl. b-tagged jets) on level of final event selection
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection (2)." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
	for ( size_t idxSelJet = 0; idxSelJet < selJets.size(); ++idxSelJet ) {
	  std::cout << "selJet #" << idxSelJet << ":" << std::endl;
	  std::cout << (*selJets[idxSelJet]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets (2)", evtWeight_2lepton);
    if ( !(selBJets_loose.size() <= 1 && selBJets_medium.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection (2)." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("<= 1 loose b-jets && 0 medium b-jet (2)");

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = selLeptons.begin();
	  lepton1 != selLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != selLeptons.end(); ++lepton2 ) {
	if ( ((*lepton1)->p4() + (*lepton2)->p4()).mass() < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight_2lepton);

    double minPt_lead = -1.;
    if ( era == kEra_2017 ) minPt_lead = 25.; // CV: increase minimum lepton pT cut to 25 GeV to keep-up with higher trigger thresholds in 2016 data
    else assert(0);
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    double minPt_third = selLepton_third ? 10. : -1.;
    if ( !(selLepton_lead->cone_pt() > minPt_lead && selLepton_sublead->cone_pt() > minPt_sublead && selLepton_third->cone_pt() > minPt_third) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = "       << selLepton_lead->pt()    << ", minPt_lead = "    << minPt_lead
                  << ", sub-leading selLepton pT = "   << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead
                  << ", third leading selLepton pT = " << selLepton_third->pt()   << ", minPt_third = " << minPt_third << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV && third lepton pT > 10 GeV", evtWeight_2lepton);

    double mLL = -1.;
    const RecoLepton* selLepton_extra = 0;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptons.begin();
    lepton1 != preselLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
      lepton2 != preselLeptons.end(); ++lepton2 ) {
	if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // lepton pair of same flavor and opposite charge
	  double m12 = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	  if ( std::fabs(m12 - z_mass) < std::fabs(mLL - z_mass) ) {
	    mLL = m12;
	    if      ( !((*lepton1) == selLepton_lead    || (*lepton2) == selLepton_lead)    ) selLepton_extra = selLepton_lead;
	    else if ( !((*lepton1) == selLepton_sublead || (*lepton2) == selLepton_sublead) ) selLepton_extra = selLepton_sublead;
	    else if ( !((*lepton1) == selLepton_third   || (*lepton2) == selLepton_third)   ) selLepton_extra = selLepton_third;
	  }
	}
      }
    }
    bool passesZbosonMassCut = std::fabs(mLL - z_mass) < z_window;
    if ( !passesZbosonMassCut ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS Z-boson cut." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass cut", evtWeight_2lepton);

    double mT = ( selLepton_extra ) ? comp_MT_met_lep1(*selLepton_extra, met.pt(), met.phi()) : -1.;

    if ( met_LD < 0.2 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS MET LD selection." << std::endl;
	std::cout << " (LD = " << met_LD << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("met LD > 0.2", evtWeight_2lepton);
    
    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS MEt filters." << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeight_2lepton);

    const RecoHadTau* selHadTau = ( selHadTaus.size() >= 1 )  ? selHadTaus[0] : 0;

    double mTauTauVis1 = -1.;
    double mTauTauVis2 = -1.;
    if ( selHadTau ) {
      mTauTauVis1 = (selLepton_lead->p4() + selHadTau->p4()).mass();
      mTauTauVis2 = (selLepton_sublead->p4() + selHadTau->p4()).mass();
    }

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    mvaInputs_2lss["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(selLepton_lead->eta()), std::fabs(selLepton_sublead->eta()));
    mvaInputs_2lss["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
    mvaInputs_2lss["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs_2lss["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*selLepton_lead, selJets);
    mvaInputs_2lss["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
    mvaInputs_2lss["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*selLepton_lead);
    mvaInputs_2lss["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*selLepton_sublead);
    mvaInputs_2lss["min(met_pt,400)"]            = std::min(met.pt(), (Double_t)400.);
    mvaInputs_2lss["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);
    
    check_mvaInputs(mvaInputs_2lss, eventInfo);
    
    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs_2lss);
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs_2lss);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 () of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_2lss = -1;
    if ( era == kEra_2017 ) {
      if      ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.4 ) mvaDiscr_2lss = 7.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV >  +0.1 ) mvaDiscr_2lss = 6.;
      else if ( mvaOutput_2lss_ttbar > +0.4 && mvaOutput_2lss_ttV <= +0.1 ) mvaDiscr_2lss = 5.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV >  +0.3 ) mvaDiscr_2lss = 4.;
      else if ( mvaOutput_2lss_ttbar > +0.1 && mvaOutput_2lss_ttV <= +0.3 ) mvaDiscr_2lss = 3.;
      else if ( mvaOutput_2lss_ttbar > -0.2                               ) mvaDiscr_2lss = 2.;
      else                                                                  mvaDiscr_2lss = 1.;
    } else assert(0);

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 3l category of ttH multilepton analysis 
    double mvaOutput_3l_ttV = -1.;
    double mvaOutput_3l_ttbar = -1.;
    if ( selLepton_third ) {
      mvaInputs_3l["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(selLepton_lead->eta()), std::fabs(selLepton_sublead->eta()));
      mvaInputs_3l["MT_met_lep1"]                = comp_MT_met_lep1(selLepton_lead->cone_p4(), met.pt(), met.phi());
      mvaInputs_3l["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
      mvaInputs_3l["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*selLepton_lead, selJets);
      mvaInputs_3l["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*selLepton_sublead, selJets);
      mvaInputs_3l["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*selLepton_lead);
      mvaInputs_3l["LepGood_conePt[iF_Recl[2]]"] = comp_lep3_conePt(*selLepton_third);
      mvaInputs_3l["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);
      mvaInputs_3l["mhtJet25_Recl"]              = mht_p4.pt();
      
      check_mvaInputs(mvaInputs_3l, eventInfo);

      mvaOutput_3l_ttV = mva_3l_ttV(mvaInputs_3l);
      mvaOutput_3l_ttbar = mva_3l_ttbar(mvaInputs_3l);
    }

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table 16 (10) of AN-2015/321 (AN-2016/211) for analysis of 2015 (2016) data
    Double_t mvaDiscr_3l = -1;
    if ( era == kEra_2017 ) {
      if      ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 5.;
      else if ( mvaOutput_3l_ttbar > +0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 4.;
      else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV >  +0.25 ) mvaDiscr_3l = 3.;
      else if ( mvaOutput_3l_ttbar > -0.30 && mvaOutput_3l_ttV <= +0.25 ) mvaDiscr_3l = 2.;
      else                                                                mvaDiscr_3l = 1.;
    } else assert(0);

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar trained by Arun for 2lss_1tau category
    mvaInputs_2lss_1tau["lep1_pt"]        = selLepton_lead->pt();
    mvaInputs_2lss_1tau["lep2_pt"]        = selLepton_sublead->pt();
    mvaInputs_2lss_1tau["max_lep_eta"]    = TMath::Max(selLepton_lead->absEta(), selLepton_sublead->absEta());
    mvaInputs_2lss_1tau["mindr_lep1_jet"] = TMath::Min(10., comp_mindr_lep1_jet(*selLepton_lead, selJets));
    mvaInputs_2lss_1tau["mindr_lep2_jet"] = TMath::Min(10., comp_mindr_lep2_jet(*selLepton_sublead, selJets));
    mvaInputs_2lss_1tau["avg_dr_jet"]     = comp_avg_dr_jet(selJets);
    mvaInputs_2lss_1tau["ptmiss"]         = met.pt();
    mvaInputs_2lss_1tau["mT_lep1"]        = comp_MT_met_lep1(selLepton_lead->p4(), met.pt(), met.phi());
    mvaInputs_2lss_1tau["htmiss"]         = mht_p4.pt();
    mvaInputs_2lss_1tau["dr_leps"]        = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    mvaInputs_2lss_1tau["nJet"]           = selJets.size();
    mvaInputs_2lss_1tau["tau_pt"]         = ( selHadTau ) ? selHadTau->pt() : -1.;
    mvaInputs_2lss_1tau["dr_lep1_tau"]    = ( selHadTau ) ? deltaR(selLepton_lead->p4(), selHadTau->p4()) : -1.;
    mvaInputs_2lss_1tau["mTauTauVis1"]    = mTauTauVis1;
    mvaInputs_2lss_1tau["mTauTauVis2"]    = mTauTauVis2;

    check_mvaInputs(mvaInputs_2lss_1tau, eventInfo);
    //for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_2lss.begin();
    //	    mvaInput != mvaInputs_2lss.end(); ++mvaInput ) {
    //  std::cout << " " << mvaInput->first << " = " << mvaInput->second << std::endl;
    //}

    double mvaOutput_2lss_1tau_ttV = mva_2lss_1tau_ttV(mvaInputs_2lss_1tau);
    //std::cout << "mvaOutput_2lss_1tau_ttV = " << mvaOutput_2lss_1tau_ttV << std::endl;
    double mvaOutput_2lss_1tau_ttbar = mva_2lss_1tau_ttbar(mvaInputs_2lss_1tau);
    //std::cout << "mvaOutput_2lss_1tau_ttbar = " << mvaOutput_2lss_1tau_ttbar << std::endl;    

//--- fill histograms with events passing final selection 
    for ( int idxEvtSel = k2lepton; idxEvtSel <= k2lepton_1tau; ++idxEvtSel ) {

      double evtWeight = 1.;
      if ( idxEvtSel == k2lepton ) {
	evtWeight = evtWeight_2lepton;
      } else if ( idxEvtSel == k3lepton ) {
	if ( !(selLeptons.size() == 3 && std::abs(sumLeptonCharge) == 1) ) continue;
	if ( isMC ) {
	  evtWeight = getEvtWeight(
            lumiScale, eventInfo.genWeight, apply_genWeight, eventInfo.pileupWeight,
	    lheInfoReader, lheScale_option,
	    dataToMCcorrectionInterface, apply_trigger_bits,
	    selLepton_lead, selLepton_sublead, selLepton_third, 0, selJets);	
	}
      } else if ( idxEvtSel == k2lepton_1tau ) {
	if ( !(selLeptons.size() == 2 && selHadTau && std::abs(sumLeptonCharge + selHadTau->charge()) == 1) ) continue;
	if ( isMC ) {
	  evtWeight = getEvtWeight(
            lumiScale, eventInfo.genWeight, apply_genWeight, eventInfo.pileupWeight,
	    lheInfoReader, lheScale_option,
	    dataToMCcorrectionInterface, apply_trigger_bits,
	    selLepton_lead, selLepton_sublead, 0, selHadTau, selJets);	
	}
      } else assert(0);

      selHistManagerType* selHistManager = selHistManagers[idxEvtSel];
      assert(selHistManager);
      selHistManager->electrons_->fillHistograms(selElectrons, evtWeight);
      selHistManager->muons_->fillHistograms(selMuons, evtWeight);
      selHistManager->hadTaus_->fillHistograms(selHadTaus, evtWeight);
      selHistManager->jets_->fillHistograms(selJets, evtWeight);
      selHistManager->leadJet_->fillHistograms(selJets, evtWeight);
      selHistManager->subleadJet_->fillHistograms(selJets, evtWeight);
      selHistManager->BJets_loose_->fillHistograms(selBJets_loose, evtWeight);
      selHistManager->leadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
      selHistManager->subleadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
      selHistManager->BJets_medium_->fillHistograms(selBJets_medium, evtWeight);
      selHistManager->met_->fillHistograms(met, mht_p4, met_LD, evtWeight);
      selHistManager->metFilters_->fillHistograms(metFilters, evtWeight);
      selHistManager->mvaInputVariables_2lss_->fillHistograms(mvaInputs_2lss, evtWeight);
      selHistManager->mvaInputVariables_2lss_1tau_->fillHistograms(mvaInputs_2lss_1tau, evtWeight);
      selHistManager->evt_->fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
        mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, 
	mvaOutput_3l_ttV, mvaOutput_3l_ttbar, mvaDiscr_3l, 
        mvaOutput_2lss_1tau_ttV, mvaOutput_2lss_1tau_ttbar, 
        mLL, mT, sumLeptonCharge, evtWeight);
      if ( isSignal ) {
        const std::string decayModeStr = eventInfo.getDecayModeString();
        if(! decayModeStr.empty())
        {
          selHistManager->evt_in_decayModes_[decayModeStr]->fillHistograms(
            selElectrons.size(),
            selMuons.size(),
            selHadTaus.size(),
            selJets.size(),
            selBJets_loose.size(),
            selBJets_medium.size(),
            mvaOutput_2lss_ttV,
            mvaOutput_2lss_ttbar,
            mvaDiscr_2lss,
            mvaOutput_3l_ttV,
            mvaOutput_3l_ttbar,
            mvaDiscr_3l,
            mvaOutput_2lss_1tau_ttV,
            mvaOutput_2lss_1tau_ttbar,
            mLL,
            mT,
            sumLeptonCharge,
            evtWeight
          );
        }
      }

      //!!! ONLY FOR DEBUGGING
      if ( idxEvtSel == k3lepton && selLeptons.size() == 3 && (selElectrons.size() == 1 || selElectrons.size() == 2 || selMuons.size() == 1 || selMuons.size() == 2) ) {
        (*selEventsFile) << eventInfo.run << ":" << eventInfo.lumi << ":" << eventInfo.event << std::endl;
      }
      //    FOR DEBUGGING ONLY !!!
    }

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight_2lepton);
    }

    //(*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight_2lepton;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete metFilterReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;

  clock.Show("analyze_WZctrl");

  return EXIT_SUCCESS;
}

