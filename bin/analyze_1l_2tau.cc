
#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/ParameterSet/interface/FileInPath.h" // edm::FileInPath
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 1l_2tau category 
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauFakeRateHistManager.h" // HadTauFakeRateHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_2tau.h" // EvtHistManager_1l_2tau
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"
#include "tthAnalysis/HiggsToTauTau/interface/particleIDlooseToTightWeightEntryType.h" // particleIDlooseToTightWeightEntryType
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType

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

#define EPS 1E-2

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

//--- declare constants
const double met_coef = 0.00397;
const double mht_coef = 0.00265;

enum { k1e_btight, k1e_bloose, k1mu_btight, k1mu_bloose };

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2)
{
  return (particle1->pt_ > particle2->pt_);
}

/**
 * @brief Produce datacard and control plots for 1l_2tau category.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<analyze_1l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_1l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_1l_2tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_1l_2tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");

  enum { kOS, kSS };
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  enum { kLoose, kFakeable, kTight };
  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"    ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"    ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  enum { kGenLepton, kGenHadTau, kGenJet, kAll };
  std::string hadTauGenMatch_string = cfg_analyze.getParameter<std::string>("hadTauGenMatch");
  int hadTauGenMatch = -1;
  if      ( hadTauGenMatch_string == "lepton" ) hadTauGenMatch = kGenLepton;
  else if ( hadTauGenMatch_string == "hadTau" ) hadTauGenMatch = kGenHadTau;
  else if ( hadTauGenMatch_string == "jet"    ) hadTauGenMatch = kGenJet;
  else if ( hadTauGenMatch_string == "all"    ) hadTauGenMatch = kAll;  
  else throw cms::Exception("analyze_1l_2tau") 
    << "Invalid Configuration parameter 'hadTauGenMatch' = " << hadTauGenMatch_string << " !!\n";

  vdouble hadTauEtaBins_lead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_lead"); // CV: eta bins in which jet->tau fake-rates are determined
  vdouble hadTauEtaBins_sublead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_sublead");

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_1l_2tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if      ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HF")       ) jet_btagWeight_branch = "Jet_bTagWeightHF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats1") ) jet_btagWeight_branch = "Jet_bTagWeightHFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats2") ) jet_btagWeight_branch = "Jet_bTagWeightHFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LF")       ) jet_btagWeight_branch = "Jet_bTagWeightLF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats1") ) jet_btagWeight_branch = "Jet_bTagWeightLFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats2") ) jet_btagWeight_branch = "Jet_bTagWeightLFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr1")    ) jet_btagWeight_branch = "Jet_bTagWeightcErr1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr2")    ) jet_btagWeight_branch = "Jet_bTagWeightcErr2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = "Jet_bTagWeightJES" + shiftUp_or_Down;
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
      else assert(0);
    } else throw cms::Exception("analyze_1l_2tau")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  }

  std::vector<particleIDlooseToTightWeightEntryType*> jetToTauFakeRateWeights;
  bool applyJetToTauFakeRateWeight = cfg_analyze.getParameter<bool>("applyJetToTauFakeRateWeight");
  if ( applyJetToTauFakeRateWeight ) {
    edm::ParameterSet cfg_jetToTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("jetToTauFakeRateWeight");

    vdouble hadTauEtaBins_lead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_lead"); // CV: eta bins in which jet->tau fake-rates have been measured
    vdouble hadTauEtaBins_sublead = cfg_analyze.getParameter<vdouble>("hadTauEtaBins_sublead");
    
    std::string fitFunctionNormName = cfg_jetToTauFakeRateWeight.getParameter<std::string>("fitFunctionNormName");
    std::string fitFunctionShapeName_lead_central = cfg_jetToTauFakeRateWeight.getParameter<std::string>("fitFunctionShapeName_lead_central");
    std::string graphShapeName_lead, fitFunctionShapeName_lead_shift;    
    int applyFitFunction_or_graph_lead = particleIDlooseToTightWeightEntryType::kFitFunction;
    if ( cfg_jetToTauFakeRateWeight.exists("graphShapeName_lead") ) {
      graphShapeName_lead = cfg_jetToTauFakeRateWeight.getParameter<std::string>("graphShapeName_lead");
      fitFunctionShapeName_lead_shift = cfg_jetToTauFakeRateWeight.getParameter<std::string>("fitFunctionShapeName_lead_shift");
      std::string applyFitFunction_or_graph_lead_string = cfg_jetToTauFakeRateWeight.getParameter<std::string>("applyFitFunction_or_graph_lead");
      if      ( applyFitFunction_or_graph_lead_string == "fitFunction" ) applyFitFunction_or_graph_lead = particleIDlooseToTightWeightEntryType::kFitFunction;
      else if ( applyFitFunction_or_graph_lead_string == "graph"       ) applyFitFunction_or_graph_lead = particleIDlooseToTightWeightEntryType::kGraph;
      else if ( applyFitFunction_or_graph_lead_string == "notApplied"  ) applyFitFunction_or_graph_lead = particleIDlooseToTightWeightEntryType::kNotApplied;
      else throw cms::Exception("analyze_1l_2tau") 
        << "Invalid Configuration parameter 'applyFitFunction_or_graph_lead' = " << applyFitFunction_or_graph_lead_string << " !!\n";
    }
    double fitFunctionShapePower_lead = cfg_jetToTauFakeRateWeight.getParameter<double>("fitFunctionShapePower_lead");
    std::string fitFunctionShapeName_sublead_central = cfg_jetToTauFakeRateWeight.getParameter<std::string>("fitFunctionShapeName_sublead_central");
    std::string graphShapeName_sublead, fitFunctionShapeName_sublead_shift;
    int applyFitFunction_or_graph_sublead = particleIDlooseToTightWeightEntryType::kFitFunction;
    if ( cfg_jetToTauFakeRateWeight.exists("graphShapeName_sublead") ) {
      graphShapeName_sublead = cfg_jetToTauFakeRateWeight.getParameter<std::string>("graphShapeName_sublead");
      fitFunctionShapeName_sublead_shift = cfg_jetToTauFakeRateWeight.getParameter<std::string>("fitFunctionShapeName_sublead_shift");
      std::string applyFitFunction_or_graph_sublead_string = cfg_jetToTauFakeRateWeight.getParameter<std::string>("applyFitFunction_or_graph_sublead");
      if      ( applyFitFunction_or_graph_sublead_string == "fitFunction" ) applyFitFunction_or_graph_sublead = particleIDlooseToTightWeightEntryType::kFitFunction;
      else if ( applyFitFunction_or_graph_sublead_string == "graph"       ) applyFitFunction_or_graph_sublead = particleIDlooseToTightWeightEntryType::kGraph;
      else if ( applyFitFunction_or_graph_sublead_string == "notApplied"  ) applyFitFunction_or_graph_sublead = particleIDlooseToTightWeightEntryType::kNotApplied;
      else throw cms::Exception("analyze_1l_2tau") 
        << "Invalid Configuration parameter 'applyFitFunction_or_graph_sublead' = " << applyFitFunction_or_graph_sublead_string << " !!\n";
    }
    double fitFunctionShapePower_sublead = cfg_jetToTauFakeRateWeight.getParameter<double>("fitFunctionShapePower_sublead");

    std::string inputFileName = cfg_jetToTauFakeRateWeight.getParameter<std::string>("inputFileName");
    TFile* inputFile = new TFile(inputFileName.data());

    int numHadTauEtaBins_lead = hadTauEtaBins_lead.size() - 1;
    for ( int idxHadTauEtaBin_lead = 0; idxHadTauEtaBin_lead < numHadTauEtaBins_lead; ++idxHadTauEtaBin_lead ) {
      double hadTauEtaMin_lead = hadTauEtaBins_lead[idxHadTauEtaBin_lead];
      double hadTauEtaMax_lead = hadTauEtaBins_lead[idxHadTauEtaBin_lead + 1];

      int numHadTauEtaBins_sublead = hadTauEtaBins_sublead.size() - 1;
      for ( int idxHadTauEtaBin_sublead = 0; idxHadTauEtaBin_sublead < numHadTauEtaBins_sublead; ++idxHadTauEtaBin_sublead ) {
        double hadTauEtaMin_sublead = hadTauEtaBins_sublead[idxHadTauEtaBin_sublead];
        double hadTauEtaMax_sublead = hadTauEtaBins_sublead[idxHadTauEtaBin_sublead + 1];

        particleIDlooseToTightWeightEntryType* jetToTauFakeRateWeight = new particleIDlooseToTightWeightEntryType(
          inputFile,
          "tau", hadTauEtaMin_lead, hadTauEtaMax_lead, hadTauEtaMin_sublead, hadTauEtaMax_sublead,
          fitFunctionNormName, 
          graphShapeName_lead, fitFunctionShapeName_lead_central, fitFunctionShapeName_lead_shift, applyFitFunction_or_graph_lead, fitFunctionShapePower_lead, 
          graphShapeName_sublead, fitFunctionShapeName_sublead_central, fitFunctionShapeName_sublead_shift, applyFitFunction_or_graph_sublead, fitFunctionShapePower_sublead);
        jetToTauFakeRateWeights.push_back(jetToTauFakeRateWeight);
      }
    }
    delete inputFile;
  }

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfg_runLumiEventSelector;
    cfg_runLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfg_runLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfg_runLumiEventSelector);
  }

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
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
    throw cms::Exception("analyze_1l_2tau") 
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
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode;
  if ( isSignal ) {
    inputTree->SetBranchAddress(GENHIGGSDECAYMODE_KEY, &genHiggsDecayMode);
  }

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);

  PUWEIGHT_TYPE pileupWeight;
  if ( isMC ) {
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }

  MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader("nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorTight tightMuonSelector;
  tightMuonSelector.disable_tightCharge_cut();

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector;
  RecoElectronCollectionSelectorTight tightElectronSelector;
  tightElectronSelector.disable_tightCharge_cut();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader("nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector;
  preselHadTauSelector.set_min_antiElectron(1);
  preselHadTauSelector.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_lead(0);
  fakeableHadTauSelector_lead.set_min_antiElectron(1);
  fakeableHadTauSelector_lead.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_sublead(1);
  fakeableHadTauSelector_sublead.set_min_antiElectron(2);
  fakeableHadTauSelector_sublead.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_lead(0);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_lead.set(hadTauSelection_part2);
  tightHadTauSelector_lead.set_min_antiElectron(1);
  tightHadTauSelector_lead.set_min_antiMuon(1);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_sublead(1);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_sublead.set(hadTauSelection_part2);
  tightHadTauSelector_sublead.set_min_antiElectron(2);
  tightHadTauSelector_sublead.set_min_antiMuon(1);

  RecoJetReader* jetReader = new RecoJetReader("nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.5);
  RecoJetCollectionSelector jetSelector;  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose;
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium;

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep");
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader("nGenJet", "GenJet");
    genJetReader->setBranchAddresses(inputTree);
  }

//--- initialize BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
  std::string mvaFileName_1l_2tau_ttbar = "tthAnalysis/HiggsToTauTau/data/1l_2tau_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_1l_2tau_ttbar;
  mvaInputVariables_1l_2tau_ttbar.push_back("lep_pt");
  mvaInputVariables_1l_2tau_ttbar.push_back("TMath::Abs(lep_eta)");
  mvaInputVariables_1l_2tau_ttbar.push_back("lep_tth_mva");
  mvaInputVariables_1l_2tau_ttbar.push_back("nJet");
  mvaInputVariables_1l_2tau_ttbar.push_back("nBJetLoose");
  mvaInputVariables_1l_2tau_ttbar.push_back("nBJetMedium");
  mvaInputVariables_1l_2tau_ttbar.push_back("mindr_lep_jet");
  mvaInputVariables_1l_2tau_ttbar.push_back("mindr_tau1_jet");
  mvaInputVariables_1l_2tau_ttbar.push_back("mindr_tau2_jet");
  mvaInputVariables_1l_2tau_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_1l_2tau_ttbar.push_back("ptmiss");
  mvaInputVariables_1l_2tau_ttbar.push_back("mT_lep");
  mvaInputVariables_1l_2tau_ttbar.push_back("htmiss");
  mvaInputVariables_1l_2tau_ttbar.push_back("tau1_pt");
  mvaInputVariables_1l_2tau_ttbar.push_back("tau2_pt");
  mvaInputVariables_1l_2tau_ttbar.push_back("TMath::Abs(tau1_eta)");
  mvaInputVariables_1l_2tau_ttbar.push_back("TMath::Abs(tau2_eta)");
  mvaInputVariables_1l_2tau_ttbar.push_back("dr_lep_tau_os");
  mvaInputVariables_1l_2tau_ttbar.push_back("dr_lep_tau_ss");
  mvaInputVariables_1l_2tau_ttbar.push_back("dr_taus");
  mvaInputVariables_1l_2tau_ttbar.push_back("mTauTauVis");
  TMVAInterface mva_1l_2tau_ttbar(mvaFileName_1l_2tau_ttbar, mvaInputVariables_1l_2tau_ttbar, { "tau1_mva", "tau2_mva" });

  std::map<std::string, double> mvaInputs;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  std::string charge_and_hadTauSelection = Form("%s_%s", hadTauChargeSelection_string.data(), hadTauSelection_part1.data());
  ElectronHistManager preselElectronHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/electrons", charge_and_hadTauSelection.data()), central_or_shift));
  preselElectronHistManager.bookHistograms(fs);
  MuonHistManager preselMuonHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/muons", charge_and_hadTauSelection.data()), central_or_shift));
  preselMuonHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/hadTaus", charge_and_hadTauSelection.data()), central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_lead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/leadHadTau", charge_and_hadTauSelection.data()), central_or_shift));
  preselHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/subleadHadTau", charge_and_hadTauSelection.data()), central_or_shift));
  preselHadTauHistManager_sublead.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/jets", charge_and_hadTauSelection.data()), central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/BJets_loose", charge_and_hadTauSelection.data()), central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/BJets_medium", charge_and_hadTauSelection.data()), central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/met", charge_and_hadTauSelection.data()), central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  EvtHistManager_1l_2tau preselEvtHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/presel/evt", charge_and_hadTauSelection.data()), central_or_shift));
  preselEvtHistManager.bookHistograms(fs);

  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/electrons", charge_and_hadTauSelection.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);
  vstring categories_e = { 
    "1e_2tau_bloose", "1e_2tau_btight"
  };
  std::map<std::string, ElectronHistManager*> selElectronHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_e.begin();
	category != categories_e.end(); ++category ) {
    ElectronHistManager* selElectronHistManager = new ElectronHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/electron", category->data(), charge_and_hadTauSelection.data()), central_or_shift));
    selElectronHistManager->bookHistograms(fs);
    selElectronHistManager_category[*category] = selElectronHistManager;
  }

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/muons", charge_and_hadTauSelection.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);
  vstring categories_mu = { 
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, MuonHistManager*> selMuonHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_mu.begin();
	category != categories_mu.end(); ++category ) {
    MuonHistManager* selMuonHistManager = new MuonHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/muon", category->data(), charge_and_hadTauSelection.data()), central_or_shift));
    selMuonHistManager->bookHistograms(fs);
    selMuonHistManager_category[*category] = selMuonHistManager;
  }

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/hadTaus", charge_and_hadTauSelection.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_lead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/leadHadTau", charge_and_hadTauSelection.data()), central_or_shift));
  selHadTauHistManager_lead.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/subleadHadTau", charge_and_hadTauSelection.data()), central_or_shift));
  selHadTauHistManager_sublead.bookHistograms(fs);
  vstring categories_tau = {
    "1e_2tau_bloose", "1e_2tau_btight",
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_lead_category; // key = category
  std::map<std::string, HadTauHistManager*> selHadTauHistManager_sublead_category; // key = category
  for ( vstring::const_iterator category = categories_tau.begin();
	category != categories_tau.end(); ++category ) {
    HadTauHistManager* selHadTauHistManager_lead = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/leadHadTau", category->data(), charge_and_hadTauSelection.data()), central_or_shift));
    selHadTauHistManager_lead->bookHistograms(fs);
    selHadTauHistManager_lead_category[*category] = selHadTauHistManager_lead;
    HadTauHistManager* selHadTauHistManager_sublead = new HadTauHistManager(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/subleadHadTau", category->data(), charge_and_hadTauSelection.data()), central_or_shift));
    selHadTauHistManager_sublead->bookHistograms(fs);
    selHadTauHistManager_sublead_category[*category] = selHadTauHistManager_sublead;
  }
  edm::ParameterSet cfg_selHadTauFakeRateHistManager = makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/hadTauFakeRates", charge_and_hadTauSelection.data()), central_or_shift);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_lead", hadTauEtaBins_lead);
  cfg_selHadTauFakeRateHistManager.addParameter<vdouble>("etaBins_sublead", hadTauEtaBins_sublead);
  HadTauFakeRateHistManager selHadTauFakeRateHistManager(cfg_selHadTauFakeRateHistManager);
  selHadTauFakeRateHistManager.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/jets", charge_and_hadTauSelection.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/leadJet", charge_and_hadTauSelection.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/subleadJet", charge_and_hadTauSelection.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/BJets_loose", charge_and_hadTauSelection.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/leadBJet_loose", charge_and_hadTauSelection.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/subleadBJet_loose", charge_and_hadTauSelection.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/BJets_medium", charge_and_hadTauSelection.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/met", charge_and_hadTauSelection.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  MVAInputVarHistManager selMVAInputVarHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/mvaInputVariables", charge_and_hadTauSelection.data()), central_or_shift));
  selMVAInputVarHistManager.bookHistograms(fs, mvaInputVariables_1l_2tau_ttbar);

  EvtHistManager_1l_2tau selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("1l_2tau_%s/sel/evt", charge_and_hadTauSelection.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  std::map<std::string, EvtHistManager_1l_2tau*> selEvtHistManager_decayMode; // key = decay mode
  const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString = {
    { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
    { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
    { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
  };
  vstring decayModes_evt;
  decayModes_evt.reserve(decayMode_idString.size());
  boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes_evt));
  if ( isSignal ) {
    for ( vstring::const_iterator decayMode = decayModes_evt.begin();
          decayMode != decayModes_evt.end(); ++decayMode) {
      EvtHistManager_1l_2tau* selEvtHistManager_ptr = new EvtHistManager_1l_2tau(makeHistManager_cfg(decayMode->data(),
        Form("1l_2tau_%s/sel/evt", charge_and_hadTauSelection.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManager_decayMode[*decayMode] = selEvtHistManager_ptr;
    }
  }
  std::map<std::string, EvtHistManager_1l_2tau*> selEvtHistManagers_genMatch; // key = { "tt", "tl", "lt", "tj", "jt", "ll", "lj", "jl", "jj" }
  vstring genMatchOptions = { "tt", "tl", "lt", "tj", "jt", "ll", "lj", "jl", "jj" };
  if ( isMC ) {
    for ( vstring::const_iterator genMatchOption = genMatchOptions.begin();
	  genMatchOption != genMatchOptions.end(); ++genMatchOption ) {
      std::string process_and_genMatch = process_string + (*genMatchOption);
      EvtHistManager_1l_2tau* selEvtHistManager_ptr = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_and_genMatch, 
        Form("1l_2tau_%s/sel/evt", charge_and_hadTauSelection.data()), central_or_shift));
      selEvtHistManager_ptr->bookHistograms(fs);
      selEvtHistManagers_genMatch[*genMatchOption] = selEvtHistManager_ptr;
    }
  }
  vstring categories_evt = { 
    "1e_2tau_bloose", "1e_2tau_btight", 
    "1mu_2tau_bloose", "1mu_2tau_btight"
  };
  std::map<std::string, EvtHistManager_1l_2tau*> selEvtHistManager_category; // key = category
  for ( vstring::const_iterator category = categories_evt.begin();
	category != categories_evt.end(); ++category ) {
    EvtHistManager_1l_2tau* selEvtHistManager = new EvtHistManager_1l_2tau(makeHistManager_cfg(process_string, 
      Form("%s_%s/sel/evt", category->data(), charge_and_hadTauSelection.data()), central_or_shift));
    selEvtHistManager->bookHistograms(fs);
    selEvtHistManager_category[*category] = selEvtHistManager;
  }

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  cutFlowTableType cutFlowTable;
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    
    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");

    bool isTriggered_1e = use_triggers_1e && hltPaths_isTriggered(triggers_1e);
    bool isTriggered_1mu = use_triggers_1mu && hltPaths_isTriggered(triggers_1mu);
    if ( !(isTriggered_1e || isTriggered_1mu) ) continue;
    cutFlowTable.update("trigger");

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons);
    
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> selElectrons = tightElectronSelector(preselElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_lead = fakeableHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_sublead = hadTauCleaner(fakeableHadTauSelector_sublead(preselHadTaus), fakeableHadTaus_lead);
    assert(fakeableHadTaus_lead.size() <= 1 && fakeableHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> fakeableHadTaus;
    fakeableHadTaus.insert(fakeableHadTaus.end(), fakeableHadTaus_lead.begin(), fakeableHadTaus_lead.end());
    fakeableHadTaus.insert(fakeableHadTaus.end(), fakeableHadTaus_sublead.begin(), fakeableHadTaus_sublead.end());
    std::vector<const RecoHadTau*> tightHadTaus_lead = tightHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus_sublead = hadTauCleaner(tightHadTauSelector_sublead(preselHadTaus), tightHadTaus_lead);
    assert(tightHadTaus_lead.size() <= 1 && tightHadTaus_sublead.size() <= 1);
    std::vector<const RecoHadTau*> tightHadTaus;
    tightHadTaus.insert(tightHadTaus.end(), tightHadTaus_lead.begin(), tightHadTaus_lead.end());
    tightHadTaus.insert(tightHadTaus.end(), tightHadTaus_sublead.begin(), tightHadTaus_sublead.end());
    std::vector<const RecoHadTau*> selHadTaus_lead;
    std::vector<const RecoHadTau*> selHadTaus_sublead;
    std::vector<const RecoHadTau*> selHadTaus;
    if ( hadTauSelection == kLoose ) {
      std::vector<const RecoHadTau*> preselHadTaus_lead;
      if ( preselHadTaus.size() >= 1 ) preselHadTaus_lead.push_back(preselHadTaus[0]);
      selHadTaus_lead = preselHadTaus_lead;
      std::vector<const RecoHadTau*> preselHadTaus_sublead;
      if ( preselHadTaus.size() >= 2 ) preselHadTaus_sublead.push_back(preselHadTaus[1]);
      selHadTaus_sublead = preselHadTaus_sublead;
      selHadTaus = preselHadTaus;
    } else if ( hadTauSelection == kFakeable ) {
      selHadTaus_lead = fakeableHadTaus_lead;
      selHadTaus_sublead = fakeableHadTaus_sublead;
      selHadTaus = fakeableHadTaus;
    } else if ( hadTauSelection == kTight ) {
      selHadTaus_lead = tightHadTaus_lead;
      selHadTaus_sublead = tightHadTaus_sublead;
      selHadTaus = tightHadTaus;
    } else assert(0);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selMuons, selElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);    

//--- build collections of generator level particles
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
	    genLepton != genLeptons.end(); ++genLepton ) {
	int abs_pdgId = std::abs(genLepton->pdgId_);
	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }

//--- match reconstructed to generator level particles
    if ( isMC ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.3);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.3);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.5);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.3);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.3);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.5);

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.3);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.3);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.5);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.3);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.3);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.5);
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    // require exactly one lepton passing loose preselection criteria
    if ( !(preselLeptons.size() == 1) ) continue;
    cutFlowTable.update("1 presel lepton");
    const RecoLepton* preselLepton = preselLeptons[0];
    int preselLepton_type = getLeptonType(preselLepton->pdgId_);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( preselElectrons.size() == 1 && !isTriggered_1e  ) continue;
    if ( preselMuons.size()     == 1 && !isTriggered_1mu ) continue;
    cutFlowTable.update("presel lepton trigger match");

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    std::sort(preselHadTaus.begin(), preselHadTaus.end(), isHigherPt);
    if ( !(preselHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 presel taus");
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    double mTauTauVis_presel = (preselHadTau_lead->p4_ + preselHadTau_sublead->p4_).mass();

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets");
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");

//--- compute MHT and linear MET discriminant (met_LD)
    LV met_p4(met_pt, met_eta, met_phi, 0.);
    LV mht_p4(0,0,0,0);
    for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	  jet != selJets.end(); ++jet ) {
      mht_p4 += (*jet)->p4_;
    }
    for ( std::vector<const RecoLepton*>::const_iterator lepton = preselLeptons.begin();
	  lepton != preselLeptons.end(); ++lepton ) {
      mht_p4 += (*lepton)->p4_;
    }
    for ( std::vector<const RecoHadTau*>::const_iterator hadTau = selHadTaus.begin();
	  hadTau != selHadTaus.end(); ++hadTau ) {
      mht_p4 += (*hadTau)->p4_;
    }
    double met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();    

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      evtWeight *= pileupWeight;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	evtWeight *= (*jet)->BtagWeight_;
      }
    }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria
    if ( isMC ) {
      evtWeight *= sf_triggerEff(1, preselLepton_type, preselLepton->pt_, preselLepton->eta_);
      evtWeight *= sf_leptonID_and_Iso_loose(1, preselLepton_type, preselLepton->pt_, preselLepton->eta_);
    }       

//--- fill histograms with events passing preselection
    preselMuonHistManager.fillHistograms(preselMuons, evtWeight);
    preselElectronHistManager.fillHistograms(preselElectrons, evtWeight);
    preselHadTauHistManager.fillHistograms(preselHadTaus, evtWeight);
    preselHadTauHistManager_lead.fillHistograms(preselHadTaus, evtWeight);
    preselHadTauHistManager_sublead.fillHistograms(preselHadTaus, evtWeight);
    preselJetHistManager.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    preselMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    preselEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      -1.,					
      mTauTauVis_presel, evtWeight);

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly one lepton passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() == 1) ) continue;
    cutFlowTable.update("1 sel lepton", evtWeight);
    const RecoLepton* selLepton = selLeptons[0];

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( selElectrons.size() == 1 && !isTriggered_1e  ) continue;
    if ( selMuons.size()     == 1 && !isTriggered_1mu ) continue;
    cutFlowTable.update("sel lepton trigger match", evtWeight);

    // require presence of exactly two hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus_lead.size() >= 1 && selHadTaus_sublead.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus_lead[0];
    bool isGenHadTauMatched_lead = selHadTau_lead->genHadTau_;
    bool isGenLeptonMatched_lead = selHadTau_lead->genLepton_ && !isGenHadTauMatched_lead;
    const RecoHadTau* selHadTau_sublead = selHadTaus_sublead[0];
    bool isGenHadTauMatched_sublead = selHadTau_sublead->genHadTau_;
    bool isGenLeptonMatched_sublead = selHadTau_sublead->genLepton_ && !isGenHadTauMatched_sublead;
    
    bool isGen_t = isGenHadTauMatched_lead && isGenHadTauMatched_sublead;
    bool isGen_l = (isGenLeptonMatched_lead || isGenLeptonMatched_sublead) && !isGen_t;
    bool isGen_j = !(isGen_t || isGen_l);
    if ( hadTauGenMatch == kGenLepton && !isGen_l ) continue;
    if ( hadTauGenMatch == kGenHadTau && !isGen_t ) continue;
    if ( hadTauGenMatch == kGenJet    && !isGen_j ) continue;
    cutFlowTable.update("tau gen match", evtWeight);

    double mTauTauVis = (selHadTau_lead->p4_ + selHadTau_sublead->p4_).mass();

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 4) ) continue;
    cutFlowTable.update(">= 4 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
 
    double minPt = 20.;
    if ( !(selLepton->pt_ > minPt) ) continue;
    cutFlowTable.update("sel lepton pT > 20 GeV", evtWeight);

    bool isCharge_SS = selHadTau_lead->charge_*selHadTau_sublead->charge_ > 0;
    bool isCharge_OS = selHadTau_lead->charge_*selHadTau_sublead->charge_ < 0;
    if ( hadTauChargeSelection == kOS && isCharge_SS ) continue;
    if ( hadTauChargeSelection == kSS && isCharge_OS ) continue;
    cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);

    if ( std::abs(selLepton->charge_ + selHadTau_lead->charge_+ selHadTau_sublead->charge_) != 1 ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;
	std::cout << " (selLepton charge = " << selLepton->charge_ 
		  << ", leading selHadTau charge = " << selHadTau_lead->charge_ 
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge_ << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lepton+tau charge");

    if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus_lead.size() >= 1 && tightHadTaus_sublead.size() >= 1 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
    }

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
    if ( isMC ) {
      double sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(1, preselLepton_type, preselLepton->pt_, preselLepton->eta_);
      evtWeight *= sf_tight_to_loose;
    }    

    if ( applyJetToTauFakeRateWeight ) {
      double selHadTau_lead_pt = selHadTau_lead->pt_;
      double selHadTau_lead_absEta = std::fabs(selHadTau_lead->eta_);
      double selHadTau_sublead_pt = selHadTau_sublead->pt_;
      double selHadTau_sublead_absEta = std::fabs(selHadTau_sublead->eta_);
      particleIDlooseToTightWeightEntryType* jetToTauFakeRateWeight_tauEtaBin = 0;
      for ( std::vector<particleIDlooseToTightWeightEntryType*>::const_iterator jetToTauFakeRateWeight = jetToTauFakeRateWeights.begin();
            jetToTauFakeRateWeight != jetToTauFakeRateWeights.end(); ++jetToTauFakeRateWeight ) {
        if ( ((*jetToTauFakeRateWeight)->particle1EtaMin_ < 0. || selHadTau_lead_absEta    > (*jetToTauFakeRateWeight)->particle1EtaMin_) &&
             ((*jetToTauFakeRateWeight)->particle1EtaMax_ > 5. || selHadTau_lead_absEta    < (*jetToTauFakeRateWeight)->particle1EtaMax_) &&
             ((*jetToTauFakeRateWeight)->particle2EtaMin_ < 0. || selHadTau_sublead_absEta > (*jetToTauFakeRateWeight)->particle2EtaMin_) &&
             ((*jetToTauFakeRateWeight)->particle2EtaMax_ > 5. || selHadTau_sublead_absEta < (*jetToTauFakeRateWeight)->particle2EtaMax_) ) {
          jetToTauFakeRateWeight_tauEtaBin = (*jetToTauFakeRateWeight);
          break;
        }
      }
      if ( jetToTauFakeRateWeight_tauEtaBin ) {
        evtWeight *= jetToTauFakeRateWeight_tauEtaBin->weight(selHadTau_lead_pt, selHadTau_sublead_pt);
      } else {
        std::cerr << "Warning: leadHadTauEta = " << selHadTau_lead_absEta << ", subleadHadTauEta = " << selHadTau_sublead_absEta << " outside range !!" << std::endl;
      }
    }

    const RecoHadTau* selHadTau_OS = 0;
    const RecoHadTau* selHadTau_SS = 0;
    if ( selLepton->charge_*selHadTau_lead->charge_ < 0. ) {
      selHadTau_OS = selHadTau_lead;
      selHadTau_SS = selHadTau_sublead;
    } else if ( selLepton->charge_*selHadTau_lead->charge_ < 0. ) {
      selHadTau_OS = selHadTau_sublead;
      selHadTau_SS = selHadTau_lead;
    }

//--- compute output of BDTs used to discriminate ttH vs. ttbar trained by Arun for 1l_2tau category
    mvaInputs["lep_pt"]               = selLepton->pt_;
    mvaInputs["TMath::Abs(lep_eta)"]  = selLepton->absEta_;
    mvaInputs["lep_tth_mva"]          = selLepton->mvaRawTTH_;
    mvaInputs["nJet"]                 = selJets.size();
    mvaInputs["nBJetLoose"]           = selBJets_loose.size();
    mvaInputs["nBJetMedium"]          = selBJets_medium.size();
    mvaInputs["mindr_lep_jet"]        = TMath::Min(10., comp_mindr_lep1_jet(*selLepton, selJets));
    mvaInputs["mindr_tau1_jet"]       = TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets));
    mvaInputs["mindr_tau2_jet"]       = TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets));
    mvaInputs["avg_dr_jet"]           = comp_avg_dr_jet(selJets);
    mvaInputs["ptmiss"]               = met_pt;
    mvaInputs["mT_lep"]               = comp_MT_met_lep1(*selLepton, met_pt, met_phi);
    mvaInputs["htmiss"]               = mht_p4.pt();
    mvaInputs["tau1_pt"]              = selHadTau_lead->pt_;
    mvaInputs["tau2_pt"]              = selHadTau_sublead->pt_;
    mvaInputs["TMath::Abs(tau1_eta)"] = selHadTau_lead->absEta_;
    mvaInputs["TMath::Abs(tau2_eta)"] = selHadTau_sublead->absEta_;
    mvaInputs["dr_lep_tau_os"]        = ( selHadTau_OS ) ? deltaR(selLepton->p4_, selHadTau_OS->p4_) : 10.;
    mvaInputs["dr_lep_tau_ss"]        = ( selHadTau_SS ) ? deltaR(selLepton->p4_, selHadTau_SS->p4_) : 10.;
    mvaInputs["dr_taus"]              = deltaR(selHadTau_lead->p4_, selHadTau_sublead->p4_);
    mvaInputs["mTauTauVis"]           = mTauTauVis;

    int index = 1;
    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
	  mvaInput != mvaInputs.end(); ++mvaInput ) {
      if ( TMath::IsNaN(mvaInput->second) ) {
	std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << ":" << std::endl; 
	std::cout << " mvaInput #" << index << " ('" << mvaInput->first << "') = " << mvaInput->second << " --> setting mvaInput value to zero !!" << std::endl; 
	mvaInputs[mvaInput->first] = 0.;
	++index;
      }
    }
    
    double mvaOutput_1l_2tau_ttbar = mva_1l_2tau_ttbar(mvaInputs);

//--- fill histograms with events passing final selection 
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager_lead.fillHistograms(selHadTaus_lead, evtWeight);
    selHadTauHistManager_sublead.fillHistograms(selHadTaus_sublead, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus_lead, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus_sublead, evtWeight);
    selHadTauFakeRateHistManager.fillHistograms(selHadTau_lead, selHadTau_sublead, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selMVAInputVarHistManager.fillHistograms(mvaInputs, evtWeight);
    selEvtHistManager.fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mvaOutput_1l_2tau_ttbar,
      mTauTauVis, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selEvtHistManager_decayMode[kv.first]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	    mvaOutput_1l_2tau_ttbar,							
	    mTauTauVis, evtWeight);
          break;
        }
      }
    }
    if ( isMC ) {
      EvtHistManager_1l_2tau* selEvtHistManager_genMatch = 0;
      if ( selHadTau_lead->genHadTau_ ) {
	if      ( selHadTau_sublead->genHadTau_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["tt"];
	else if ( selHadTau_sublead->genLepton_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["tl"];
	else                                      selEvtHistManager_genMatch = selEvtHistManagers_genMatch["tj"];
      } else if ( selHadTau_lead->genLepton_ ) {
	if      ( selHadTau_sublead->genHadTau_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["lt"];
	else if ( selHadTau_sublead->genLepton_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["ll"];
	else                                      selEvtHistManager_genMatch = selEvtHistManagers_genMatch["lj"];
      } else {
	if      ( selHadTau_sublead->genHadTau_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["jt"];
	else if ( selHadTau_sublead->genLepton_ ) selEvtHistManager_genMatch = selEvtHistManagers_genMatch["jl"];
	else                                      selEvtHistManager_genMatch = selEvtHistManagers_genMatch["jj"];
      }
      assert(selEvtHistManager_genMatch);
      selEvtHistManager_genMatch->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar,
        mTauTauVis, evtWeight);
    }

    int category = -1;
    if      ( selElectrons.size() == 1 && selBJets_medium.size() >= 1 ) category = k1e_btight;
    else if ( selElectrons.size() == 1                                ) category = k1e_bloose;
    else if ( selMuons.size()     == 1 && selBJets_medium.size() >= 1 ) category = k1mu_btight;
    else if ( selMuons.size()     == 1                                ) category = k1mu_bloose;
    else assert(0);

    if ( category == k1e_btight ) {
      selElectronHistManager_category["1e_2tau_btight"]->fillHistograms(selElectrons, evtWeight);
      selHadTauHistManager_lead_category["1e_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1e_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1e_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar,
        mTauTauVis, evtWeight);
    } else if ( category == k1e_bloose ) {
      selElectronHistManager_category["1e_2tau_bloose"]->fillHistograms(selElectrons, evtWeight);
      selHadTauHistManager_lead_category["1e_2tau_bloose"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1e_2tau_bloose"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1e_2tau_bloose"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar,
        mTauTauVis, evtWeight);
    } else if ( category == k1mu_btight ) {
      selMuonHistManager_category["1mu_2tau_btight"]->fillHistograms(selMuons, evtWeight);
      selHadTauHistManager_lead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1mu_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar,
        mTauTauVis, evtWeight);
    } else if ( category == k1mu_bloose ) {
      selMuonHistManager_category["1mu_2tau_btight"]->fillHistograms(selMuons, evtWeight);
      selHadTauHistManager_lead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_lead, evtWeight);
      selHadTauHistManager_sublead_category["1mu_2tau_btight"]->fillHistograms(selHadTaus_sublead, evtWeight);
      selEvtHistManager_category["1mu_2tau_btight"]->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
        selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
        mvaOutput_1l_2tau_ttbar,
        mTauTauVis, evtWeight);
    } 

    (*selEventsFile) << run << ":" << lumi << ":" << event;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;
  std::cout << std::endl;

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);

  clock.Show("analyze_1l_2tau");

  return EXIT_SUCCESS;
}

