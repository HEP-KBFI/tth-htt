
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category 
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
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // RecoElectronSelectorLoose, RecoElectronSelectorTight, RecoMuonSelectorLoose, RecoMuonSelectorTight, RecoHadTauSelector
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h" // EvtHistManager_2lss_1tau

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

//--- declare constants
const double z_mass   = 91.1876;
const double z_window = 10.;
const double met_coef =  0.00397;
const double mht_coef =  0.00265;

enum { k2epp_btight, k2epp_bloose, k2emm_btight, k2emm_bloose, k1e1mupp_btight, k1e1mupp_bloose, k1e1mumm_btight, k1e1mumm_bloose, k2mupp_btight, k2mupp_bloose, k2mumm_btight, k2mumm_bloose };

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
 * @brief Produce datacard and control plots for 2lss channels.
 *
 */

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<analyze_2lss_1tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_2lss_1tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_2lss_1tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_2lss_1tau");

   std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");

  vstring triggers_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggers_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggers_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggers_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggers_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  enum { kOS, kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  int chargeSelection = -1;
  if      ( chargeSelection_string == "OS" ) chargeSelection = kOS;
  else if ( chargeSelection_string == "SS" ) chargeSelection = kSS;
  else throw cms::Exception("analyze_2lss_1tau") 
    << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !!\n";

  enum { kLoose, kFakeable, kTight };
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection");
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("analyze_2lss_1tau") 
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_2lss_1tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if      ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HF")       ) jet_btagWeight_branch = "Jet_bTagWeight_HF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats1") ) jet_btagWeight_branch = "Jet_bTagWeight_HFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_HFStats2") ) jet_btagWeight_branch = "Jet_bTagWeight_HFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LF")       ) jet_btagWeight_branch = "Jet_bTagWeight_LF" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats1") ) jet_btagWeight_branch = "Jet_bTagWeight_LFStats1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_LFStats2") ) jet_btagWeight_branch = "Jet_bTagWeight_LFStats2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr1")    ) jet_btagWeight_branch = "Jet_bTagWeight_cErr1" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag_cErr2")    ) jet_btagWeight_branch = "Jet_bTagWeight_cErr2" + shiftUp_or_Down;
    else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = "Jet_bTagWeight_JES" + shiftUp_or_Down;
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else throw cms::Exception("analyze_2lss_1tau")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  }

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

  TChain* inputTree = new TChain(treeName.data());
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("analyze_2lss_1tau") 
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

  MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);
  LV met_p4(met_pt, met_eta, met_phi, 0.);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader("nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector;
  RecoMuonCollectionSelectorTight tightMuonSelector;

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector;
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector;
  RecoElectronCollectionSelectorTight tightElectronSelector;

  RecoHadTauReader* hadTauReader = new RecoHadTauReader("nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorTight hadTauSelector;
  
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

  std::map<std::string, double> mvaInputs;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  std::string charge_and_leptonSelection = Form("%s_%s", chargeSelection_string.data(), leptonSelection_string.data());
  ElectronHistManager preselElectronHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/electrons", charge_and_leptonSelection.data()), central_or_shift));
  preselElectronHistManager.bookHistograms(fs);
  MuonHistManager preselMuonHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/muons", charge_and_leptonSelection.data()), central_or_shift));
  preselMuonHistManager.bookHistograms(fs);
  HadTauHistManager preselHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/hadTaus", charge_and_leptonSelection.data()), central_or_shift));
  preselHadTauHistManager.bookHistograms(fs);
  JetHistManager preselJetHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/jets", charge_and_leptonSelection.data()), central_or_shift));
  preselJetHistManager.bookHistograms(fs);
  JetHistManager preselBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/BJets_loose", charge_and_leptonSelection.data()), central_or_shift));
  preselBJet_looseHistManager.bookHistograms(fs);
  JetHistManager preselBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/BJets_medium", charge_and_leptonSelection.data()), central_or_shift));
  preselBJet_mediumHistManager.bookHistograms(fs);
  MEtHistManager preselMEtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/met", charge_and_leptonSelection.data()), central_or_shift));
  preselMEtHistManager.bookHistograms(fs);
  EvtHistManager_2lss_1tau preselEvtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/presel/evt", charge_and_leptonSelection.data()), central_or_shift));
  preselEvtHistManager.bookHistograms(fs);
  
  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/electrons", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2epp_btight_lead(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_btight_%s/sel/leadElectron", charge_and_leptonSelection.data()), central_or_shift, 0));
  selElectronHistManager_2epp_btight_lead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2epp_btight_sublead(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_btight_%s/sel/subleadElectron", charge_and_leptonSelection.data()), central_or_shift, 1));
  selElectronHistManager_2epp_btight_sublead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2epp_bloose_lead(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_bloose_%s/sel/leadElectron", charge_and_leptonSelection.data()), central_or_shift, 0));
  selElectronHistManager_2epp_bloose_lead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2epp_bloose_sublead(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_bloose_%s/sel/subleadElectron", charge_and_leptonSelection.data()), central_or_shift, 1));
  selElectronHistManager_2epp_bloose_sublead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2emm_btight_lead(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_btight_%s/sel/leadElectron", charge_and_leptonSelection.data()), central_or_shift, 0));
  selElectronHistManager_2emm_btight_lead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2emm_btight_sublead(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_btight_%s/sel/subleadElectron", charge_and_leptonSelection.data()), central_or_shift, 1));
  selElectronHistManager_2emm_btight_sublead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2emm_bloose_lead(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_bloose_%s/sel/leadElectron", charge_and_leptonSelection.data()), central_or_shift, 0));
  selElectronHistManager_2emm_bloose_lead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_2emm_bloose_sublead(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_bloose_%s/sel/subleadElectron", charge_and_leptonSelection.data()), central_or_shift, 1));
  selElectronHistManager_2emm_bloose_sublead.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_1e1mupp_btight(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_btight_%s/sel/electron", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager_1e1mupp_btight.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_1e1mupp_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_bloose_%s/sel/electron", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager_1e1mupp_bloose.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_1e1mumm_btight(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_btight_%s/sel/electron", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager_1e1mumm_btight.bookHistograms(fs);
  ElectronHistManager selElectronHistManager_1e1mumm_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_bloose_%s/sel/electron", charge_and_leptonSelection.data()), central_or_shift));
  selElectronHistManager_1e1mumm_bloose.bookHistograms(fs);

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/muons", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);
  MuonHistManager selMuonHistManager_1e1mupp_btight(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_btight_%s/sel/muon", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager_1e1mupp_btight.bookHistograms(fs);
  MuonHistManager selMuonHistManager_1e1mupp_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_bloose_%s/sel/muon", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager_1e1mupp_bloose.bookHistograms(fs);
  MuonHistManager selMuonHistManager_1e1mumm_btight(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_btight_%s/sel/muon", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager_1e1mumm_btight.bookHistograms(fs);
  MuonHistManager selMuonHistManager_1e1mumm_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_bloose_%s/sel/muon", charge_and_leptonSelection.data()), central_or_shift));
  selMuonHistManager_1e1mumm_bloose.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mupp_btight_lead(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_btight_%s/sel/leadMuon", charge_and_leptonSelection.data()), central_or_shift, 0));
  selMuonHistManager_2mupp_btight_lead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mupp_btight_sublead(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_btight_%s/sel/subleadMuon", charge_and_leptonSelection.data()), central_or_shift, 1));
  selMuonHistManager_2mupp_btight_sublead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mupp_bloose_lead(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_bloose_%s/sel/leadMuon", charge_and_leptonSelection.data()), central_or_shift, 0));
  selMuonHistManager_2mupp_bloose_lead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mupp_bloose_sublead(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_bloose_%s/sel/subleadMuon", charge_and_leptonSelection.data()), central_or_shift, 1));
  selMuonHistManager_2mupp_bloose_sublead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mumm_btight_lead(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_btight_%s/sel/leadMuon", charge_and_leptonSelection.data()), central_or_shift, 0));
  selMuonHistManager_2mumm_btight_lead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mumm_btight_sublead(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_btight_%s/sel/subleadMuon", charge_and_leptonSelection.data()), central_or_shift, 1));
  selMuonHistManager_2mumm_btight_sublead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mumm_bloose_lead(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_bloose_%s/sel/leadMuon", charge_and_leptonSelection.data()), central_or_shift, 0));
  selMuonHistManager_2mumm_bloose_lead.bookHistograms(fs);
  MuonHistManager selMuonHistManager_2mumm_bloose_sublead(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_bloose_%s/sel/subleadMuon", charge_and_leptonSelection.data()), central_or_shift, 1));
  selMuonHistManager_2mumm_bloose_sublead.bookHistograms(fs);

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/hadTaus", charge_and_leptonSelection.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/jets", charge_and_leptonSelection.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/leadJet", charge_and_leptonSelection.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/subleadJet", charge_and_leptonSelection.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/BJets_loose", charge_and_leptonSelection.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/leadBJet_loose", charge_and_leptonSelection.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/subleadBJet_loose", charge_and_leptonSelection.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/BJets_medium", charge_and_leptonSelection.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/met", charge_and_leptonSelection.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  EvtHistManager_2lss_1tau selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("2lss_1tau_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2epp_btight(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2epp_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2epp_bloose(makeHistManager_cfg(process_string, 
    Form("2epp_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2epp_bloose.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2emm_btight(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2emm_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2emm_bloose(makeHistManager_cfg(process_string, 
    Form("2emm_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2emm_bloose.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_1e1mupp_btight(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_1e1mupp_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_1e1mupp_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mupp_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_1e1mupp_bloose.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_1e1mumm_btight(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_1e1mumm_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_1e1mumm_bloose(makeHistManager_cfg(process_string, 
    Form("1e1mumm_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_1e1mumm_bloose.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2mupp_btight(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2mupp_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2mupp_bloose(makeHistManager_cfg(process_string, 
    Form("2mupp_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2mupp_bloose.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2mumm_btight(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_btight_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2mumm_btight.bookHistograms(fs);
  EvtHistManager_2lss_1tau selEvtHistManager_2mumm_bloose(makeHistManager_cfg(process_string, 
    Form("2mumm_1tau_bloose_%s/sel/evt", charge_and_leptonSelection.data()), central_or_shift));
  selEvtHistManager_2mumm_bloose.bookHistograms(fs);

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    
    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;

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
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
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
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    
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

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.3);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.3);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.5);

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
    
    if ( !(preselLeptons.size() == 2 && selHadTaus.size() == 1 && selJets.size() >= 2 && (selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1)) ) continue;

//--- compute MHT and linear MET discriminant (met_LD)
    LV mht_p4(0,0,0,0);
    for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	  jet != selJets.end(); ++jet ) {
      mht_p4 += (*jet)->p4_;
    }
    for ( std::vector<const RecoLepton*>::const_iterator lepton = preselLeptons.begin();
	  lepton != preselLeptons.end(); ++lepton ) {
      mht_p4 += (*lepton)->p4_;
    }
    double met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();    

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	  jet != selJets.end(); ++jet ) {
      evtWeight *= (*jet)->BtagWeight_;
    }

    double evtWeight_pp = evtWeight;
    double evtWeight_mm = evtWeight;
    if ( chargeSelection == kOS ) {
      const RecoLepton* preselLepton_lead = preselLeptons[0];
      int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId_);      
      double prob_chargeMisId_lead = prob_chargeMisId(preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_);

      const RecoLepton* preselLepton_sublead = preselLeptons[1];
      int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId_);
      double prob_chargeMisId_sublead = prob_chargeMisId(preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);

      evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);

      if ( preselLepton_lead->charge_ < 0 && preselLepton_sublead->charge_ > 0 ) {
	evtWeight_pp *= prob_chargeMisId_lead;
	evtWeight_mm *= prob_chargeMisId_sublead;
      }
      if ( preselLepton_lead->charge_ > 0 && preselLepton_sublead->charge_ < 0 ) {
	evtWeight_pp *= prob_chargeMisId_sublead;
	evtWeight_mm *= prob_chargeMisId_lead;
      }
    } 

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    mvaInputs["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(preselLepton_lead->eta_), std::fabs(preselLepton_sublead->eta_));
    mvaInputs["MT_met_lep1"]                = comp_MT_met_lep1(*preselLepton_lead, met_pt, met_phi);
    mvaInputs["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
    mvaInputs["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*preselLepton_lead, selJets);
    mvaInputs["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*preselLepton_sublead, selJets);
    mvaInputs["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*preselLepton_lead);
    mvaInputs["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*preselLepton_sublead);
    mvaInputs["min(met_pt,400)"]            = std::min(met_pt, (Float_t)400.);
    mvaInputs["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);

    double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs);
    double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table X of AN-2015/321
    Double_t mvaDiscr_2lss = -1;
    if      ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 6.;
    else if ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 5.;
    else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 4.;
    else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 3.;
    else if (                                mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 2.;
    else                                                                  mvaDiscr_2lss = 1.;
    
//--- fill histograms with events passing preselection
    preselMuonHistManager.fillHistograms(preselMuons, evtWeight);
    preselElectronHistManager.fillHistograms(preselElectrons, evtWeight);
    preselHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    preselJetHistManager.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    preselMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    preselEvtHistManager.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    if ( !(selLeptons.size() == 2) ) continue;

    if ( !(selJets.size() >= 4) ) continue;
    
    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = selLeptons.begin();
	  lepton1 != selLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != selLeptons.end(); ++lepton2 ) {
	if ( ((*lepton1)->p4_ + (*lepton2)->p4_).mass() < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) continue;

    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];
    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt_ > minPt_lead && selLepton_sublead->pt_ > minPt_sublead) ) continue;

    bool isCharge_SS = selLepton_lead->charge_*selLepton_sublead->charge_ > 0;
    bool isCharge_OS = selLepton_lead->charge_*selLepton_sublead->charge_ < 0;
    if ( chargeSelection == kOS && isCharge_SS ) continue;
    if ( chargeSelection == kSS && isCharge_OS ) continue;

    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      bool failsZbosonMassVeto = false;
      for ( std::vector<const RecoLepton*>::const_iterator lepton1 = selLeptons.begin();
	    lepton1 != selLeptons.end(); ++lepton1 ) {
	for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	      lepton2 != selLeptons.end(); ++lepton2 ) {
	  if ( std::fabs(((*lepton1)->p4_ + (*lepton2)->p4_).mass() - z_mass) < z_window ) {
	    failsZbosonMassVeto = true;
	  }
	}
      }
      if ( failsZbosonMassVeto ) continue;

      if ( met_LD < 0.2 ) continue;
    }

    if ( leptonSelection == kFakeable && (tightMuons.size() + tightElectrons.size()) >= 2 ) continue; // CV: avoid overlap with signal region

//--- fill histograms with events passing final selection 
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selEvtHistManager.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);

    bool isCharge_pp = selLepton_lead->pdgId_ < 0 && selLepton_sublead->pdgId_ < 0;
    bool isCharge_mm = selLepton_lead->pdgId_ > 0 && selLepton_sublead->pdgId_ > 0;

    int category = -1;
    if      ( selElectrons.size() == 2 &&                         isCharge_pp && selBJets_medium.size() >= 1 ) category = k2epp_btight;
    else if ( selElectrons.size() == 2 &&                         isCharge_pp                                ) category = k2epp_bloose;
    else if ( selElectrons.size() == 2 &&                         isCharge_mm && selBJets_medium.size() >= 1 ) category = k2emm_btight;
    else if ( selElectrons.size() == 2 &&                         isCharge_mm                                ) category = k2emm_bloose;
    else if ( selElectrons.size() == 1 && selMuons.size() == 1 && isCharge_pp && selBJets_medium.size() >= 1 ) category = k1e1mupp_btight;
    else if ( selElectrons.size() == 1 && selMuons.size() == 1 && isCharge_pp                                ) category = k1e1mupp_bloose;
    else if ( selElectrons.size() == 1 && selMuons.size() == 1 && isCharge_mm && selBJets_medium.size() >= 1 ) category = k1e1mumm_btight;
    else if ( selElectrons.size() == 1 && selMuons.size() == 1 && isCharge_mm                                ) category = k1e1mumm_bloose;
    else if (                             selMuons.size() == 2 && isCharge_pp && selBJets_medium.size() >= 1 ) category = k2mupp_btight;
    else if (                             selMuons.size() == 2 && isCharge_pp                                ) category = k2mupp_bloose;
    else if (                             selMuons.size() == 2 && isCharge_mm && selBJets_medium.size() >= 1 ) category = k2mumm_btight;
    else if (                             selMuons.size() == 2 && isCharge_mm                                ) category = k2mumm_bloose;
    else assert(0);

    if ( category == k2epp_btight ) {
      selElectronHistManager_2epp_btight_lead.fillHistograms(selElectrons, evtWeight_pp);
      selElectronHistManager_2epp_btight_sublead.fillHistograms(selElectrons, evtWeight_pp);
      selEvtHistManager_2epp_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight_pp);
    } else if ( category == k2epp_bloose ) {
      selElectronHistManager_2epp_bloose_lead.fillHistograms(selElectrons, evtWeight_pp);
      selElectronHistManager_2epp_bloose_sublead.fillHistograms(selElectrons, evtWeight_pp);
      selEvtHistManager_2epp_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight_pp);
    } else if ( category == k2emm_btight ) {
      selElectronHistManager_2emm_btight_lead.fillHistograms(selElectrons, evtWeight_mm);
      selElectronHistManager_2emm_btight_sublead.fillHistograms(selElectrons, evtWeight_mm);
      selEvtHistManager_2emm_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight_mm);
    } else if ( category == k2emm_bloose ) {
      selElectronHistManager_2emm_bloose_lead.fillHistograms(selElectrons, evtWeight_mm);
      selElectronHistManager_2emm_bloose_sublead.fillHistograms(selElectrons, evtWeight_mm);
      selEvtHistManager_2emm_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight_mm);

BIS HIER !!!

    } else if ( category == k1e1mupp_btight ) {
      selElectronHistManager_1e1mupp_btight.fillHistograms(selElectrons, evtWeight);
      selMuonHistManager_1e1mupp_btight.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_1e1mupp_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k1e1mupp_bloose ) {
      selElectronHistManager_1e1mupp_bloose.fillHistograms(selElectrons, evtWeight);
      selMuonHistManager_1e1mupp_bloose.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_1e1mupp_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k1e1mumm_btight ) {
      selElectronHistManager_1e1mumm_btight.fillHistograms(selElectrons, evtWeight);
      selMuonHistManager_1e1mumm_btight.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_1e1mumm_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k1e1mumm_bloose ) {
      selElectronHistManager_1e1mumm_bloose.fillHistograms(selElectrons, evtWeight);
      selMuonHistManager_1e1mumm_bloose.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_1e1mumm_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k2mupp_btight ) {
      selMuonHistManager_2mupp_btight_lead.fillHistograms(selMuons, evtWeight);
      selMuonHistManager_2mupp_btight_sublead.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_2mupp_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k2mupp_bloose ) {
      selMuonHistManager_2mupp_bloose_lead.fillHistograms(selMuons, evtWeight);
      selMuonHistManager_2mupp_bloose_sublead.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_2mupp_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k2mumm_btight ) {
      selMuonHistManager_2mumm_btight_lead.fillHistograms(selMuons, evtWeight);
      selMuonHistManager_2mumm_btight_sublead.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_2mumm_btight.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } else if ( category == k2mumm_bloose ) {
      selMuonHistManager_2mumm_bloose_lead.fillHistograms(selMuons, evtWeight);
      selMuonHistManager_2mumm_bloose_sublead.fillHistograms(selMuons, evtWeight);
      selEvtHistManager_2mumm_bloose.fillHistograms(mvaOutput_2lss_ttV, mvaOutput_2lss_ttbar, mvaDiscr_2lss, evtWeight);
    } 

    (*selEventsFile) << run << ":" << lumi << ":" << event;

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;

  clock.Start("analyze_2lss_1tau");

  return EXIT_SUCCESS;
}

