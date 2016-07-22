#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/ParameterSet/interface/FileInPath.h" // edm::FileInPath
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TEfficiency.h>

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
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // RecoElectronSelectorLoose, RecoElectronSelectorTight, RecoMuonSelectorLoose, RecoMuonSelectorTight, RecoHadTauSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

#include <iostream> // std::cerr, std::fixed
#include <cstring> // std::strncpm
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
 * @brief Produce histograms for the charge flip background.
 */
int main(int argc, char* argv[])
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
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

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  //bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  //bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  //bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");
  /*enum { kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  //int chargeSelection = -1;
  if ( chargeSelection_string != "SS" )
    throw cms::Exception("analyze_charge_flip")
      << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !! Must be \n";
    */

  enum { kLoose, kFakeable, kTight };
  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection");
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"    ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"    ) leptonSelection = kTight;
  else throw cms::Exception("analyze_charge_flip")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool useData = cfg_analyze.getParameter<bool>("useData");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_charge_flip")
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
    } else throw cms::Exception("analyze_charge_flip")
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
    throw cms::Exception("analyze_charge_flip")
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
  /*GENHIGGSDECAYMODE_TYPE genHiggsDecayMode;
  if(process_string != "data_obs")
    inputTree->SetBranchAddress(GENHIGGSDECAYMODE_KEY, &genHiggsDecayMode);*/

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_2e);
  /*hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_2mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);*/

  /*MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);
  LV met_p4(met_pt, met_eta, met_phi, 0.);
    */
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
  //GenHadTauReader* genHadTauReader = 0;
  //GenJetReader* genJetReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep");
    genLeptonReader->setBranchAddresses(inputTree);
    /*genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader("nGenJet", "GenJet");
    genJetReader->setBranchAddresses(inputTree);*/
  }

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

//--- declare histograms
  std::string charge_and_leptonSelectionSS = Form("%s_%s", "SS", leptonSelection_string.data());
  std::string charge_and_leptonSelectionOS = Form("%s_%s", "OS", leptonSelection_string.data());
  ElectronHistManager preselElectronHistManagerSS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons/%s", charge_and_leptonSelectionSS.data(), process_string.data()), central_or_shift));
  preselElectronHistManagerSS.bookHistograms(fs);
  ElectronHistManager preselElectronHistManagerOS(makeHistManager_cfg(process_string,
    Form("charge_flip_%s/presel/electrons/%s", charge_and_leptonSelectionOS.data(), process_string.data()), central_or_shift));
  preselElectronHistManagerOS.bookHistograms(fs);

  vstring categories_etapt = {  //B-barrel, E-endcap, L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT > 50)
    "BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"
  };
  vstring categories_charge = {
    "SS", "OS"
  };
  //std::map<std::string, std::map<std::string, CompositeParticleHistManager*>> preselZHistManager_cat; // key = category
  std::map<std::string, std::map<std::string, std::map<std::string, TH1D*>>> histos;
  std::map<std::string, std::map<std::string, std::map<std::string, TH1D*>>> histos_2gen;
  
  for ( vstring::const_iterator which = categories_charge.begin(); 	which != categories_charge.end(); ++which ) {
    TFileDirectory subDir = fs.mkdir( which->data() );
    //TFileDirectory subDir2 = subDir.mkdir(process_string);
    TFileDirectory subD1 = fs.mkdir("gen");
    TFileDirectory subD = subD1.mkdir(which->data());

    for ( vstring::const_iterator category = categories_etapt.begin(); 	category != categories_etapt.end(); ++category ) {
      TFileDirectory subDir2 = subDir.mkdir(category->data());
      TFileDirectory subD2 = subD.mkdir(category->data());
      histos[which->data()][*category][process_string] = subDir2.make<TH1D>( process_string.data(), "m_{ll}", 60,  60., 120. );
      if (std::strncmp(process_string.data(), "DY", 2) == 0){
          histos[which->data()][*category]["DY_fake"] = subDir2.make<TH1D>( "DY_fake", "m_{ll}", 60,  60., 120. );
          histos_2gen[which->data()][*category][process_string] = subD2.make<TH1D>( process_string.data(), "m_{ll}", 60,  60., 120. );
      }      
      if (!useData){
        histos[which->data()][*category]["data_obs"] = subDir2.make<TH1D>( Form("data_obs"), "m_{ll}", 60,  60., 120. );
      }
    }
  }
  vstring categories_charge_gen = {
    "ID", "MisID"
  };

  TFileDirectory subDir_fails = fs.mkdir( Form("failed_cuts") );
  TH1I* fail_counter = subDir_fails.make<TH1I>( process_string.data(), "Rejected events", 10,  0, 10 );
  const char *rejcs[10] = {"Trigger", "Trig_2e1e", "2e", "0mu", "2e_trig", "2e_sel", "2e_sel_trig", "0mu_sel", "pT_el", "m_ll"};
  for (int i=1;i<=10;i++) fail_counter->GetXaxis()->SetBinLabel(i,rejcs[i-1]); 


  /*vstring categories_etapt_gen = {  //B-barrel, E-endcap, L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT > 50)
    "B_L", "B_M", "B_H", "E_L", "E_M", "E_M", "E_H"
  };*/

  Double_t bins_eta[3] = {0, 1.479, 2.5};
  Double_t bins_pt[4] = {10, 25, 50, 1000};

  TEfficiency* gen_eff;
  TFileDirectory subD = fs.mkdir("gen_ratio");
  gen_eff = subD.make<TEfficiency>(Form("pt_eta_%s", process_string.data()),"pt_eta;pT;#eta;charge_misID", 3,  bins_pt, 2, bins_eta);

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
    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu);
    
    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    //bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    //bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    //bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_2e) ) {
        if ( run_lumi_eventSelector ) {
	        std::cout << "event FAILS trigger selection." << std::endl; 
	        std::cout << " (selTrigger_1e = " << isTriggered_1e 
		      << ", selTrigger_2e = " << isTriggered_2e 
          << ", selTrigger_1mu = " << isTriggered_1mu
          << ", selTrigger_2mu = " << isTriggered_2mu  
		      << ", selTrigger_1e1mu = " << isTriggered_1e1mu <<")" << std::endl;
        }
        fail_counter->Fill("Trigger", 1);
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
        fail_counter->Fill("Trig_2e1e", 1);
	      continue; 
      }
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
      //genHadTaus = genHadTauReader->read();
      //genJets = genJetReader->read();
    }

//--- match reconstructed to generator level particles
    if ( isMC ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.3);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.3);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.5);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.3);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.3);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.5);

      /*hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.3);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.3);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.5);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.3);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.3);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.5);*/
    }
//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    
    // require exactly two preselected electrons
    if ( !(preselElectrons.size() == 2) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS 2 presel Electrons selection" << std::endl; 
	      std::cout << " #preselElectrons = " << preselElectrons.size() 
		        << std::endl;
      }
      fail_counter->Fill("2e", 1);
      continue;
    }
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId_);
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId_);
    
    // require exactly zero preselected muons
    if ( !(preselMuons.size() == 0) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS 0 presel Muons selection" << std::endl; 
	      std::cout << " (#preselMuons = " << preselMuons.size() 
           << ")" << std::endl;
      }
      fail_counter->Fill("0mu", 1);
      continue;
    }
    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	      std::cout << " (#preselElectrons = " << preselElectrons.size() 
		        << ", selTrigger_1e = " << selTrigger_1e 
		        << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      fail_counter->Fill("2e_trig", 1);
      continue;
    }
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = lumiScale;
    for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	  jet != selJets.end(); ++jet ) {
      evtWeight *= (*jet)->BtagWeight_;
    }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria
    /*if ( isMC ) {
      evtWeight *= sf_triggerEff(preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      evtWeight *= sf_leptonID_and_Iso_loose(preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
    }*/

    //--- apply final event selection
    std::vector<const RecoLepton*> selLeptons;
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
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
      fail_counter->Fill("2e_sel", 1);
      continue;
    }
    
    if ( selElectrons.size() == 2 && !(selTrigger_1e  || selTrigger_2e) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS trigger selection for given selElectron multiplicity." << std::endl; 
	      std::cout << " (#selElectrons = " << selElectrons.size() 
		        << ", selTrigger_1e = " << selTrigger_1e 
		        << ", selTrigger_2e = " << selTrigger_2e << ")" << std::endl;
      }
      fail_counter->Fill("2e_sel_trig", 1);
      continue;
    }

    if ( selMuons.size() != 0) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS selection for selMuon = 0." << std::endl; 
	      std::cout << " (#selMuons = " << selMuons.size() << ")" << std::endl;
      }
      fail_counter->Fill("0mu_sel", 1);
      continue;
    }

    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    // require that trigger paths match event category (with event category based on selLeptons);
    /*if ( selElectrons.size() == 2 &&                         !(selTrigger_1e  || selTrigger_2e)                       ) continue;
    if ( selElectrons.size() == 1 && selMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) continue;
    */
    
    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    //TODO: verify treatment:
    //double minPt_lead = 10.;
    //double minPt_sublead = 10.;
    if ( !(selLepton_lead->pt_ > minPt_lead && selLepton_sublead->pt_ > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS lepton pT selection." << std::endl;
	      std::cout << " (leading selLepton pT = " << selLepton_lead->pt_ << ", minPt_lead = " << minPt_lead
		        << ", subleading selLepton pT = " << selLepton_sublead->pt_ << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      fail_counter->Fill("pT_el", 1);
      continue;
    }  
    bool isCharge_SS = selLepton_lead->charge_*selLepton_sublead->charge_ > 0;
    bool isCharge_OS = selLepton_lead->charge_*selLepton_sublead->charge_ < 0;
    

    /*if ( leptonSelection == kFakeable && (tightMuons.size() + tightElectrons.size()) >= 2 ) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS tightElectrons+tightMuons selection." << std::endl;
	      std::cout << " (#tightElectrons = " << tightElectrons.size() << ", #tightMuons = " << tightMuons.size() << ")" << std::endl;
            }
      continue; // CV: avoid overlap with signal region
    }*/

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
    if ( isMC && false) { //FIXME
      double sf_tight_to_loose = 1.;
      if ( leptonSelection == kFakeable ) {
	      sf_tight_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      } else if ( leptonSelection == kTight ) {
      	sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      }
      evtWeight *= sf_tight_to_loose;
      //evtWeight_pp *= sf_tight_to_loose;
      //evtWeight_mm *= sf_tight_to_loose;
    }

//--- Calclulate mass of lepton system
    math::PtEtaPhiMLorentzVector p4 =
      math::PtEtaPhiMLorentzVector(preselElectrons[0]->pt_, preselElectrons[0]->eta_, preselElectrons[0]->phi_, preselElectrons[0]->mass_) +
      math::PtEtaPhiMLorentzVector(preselElectrons[1]->pt_, preselElectrons[1]->eta_, preselElectrons[1]->phi_, preselElectrons[1]->mass_);

    Double_t mass_ll = p4.M();
    if (mass_ll < 60 || mass_ll > 120) {
      if ( run_lumi_eventSelector ) {
	      std::cout << "event FAILS dilepton mass selection." << std::endl;
	      std::cout << " (dilepton mass = " << mass_ll << ")" << std::endl;
      }
      fail_counter->Fill("m_ll", 1);
      continue;
    }
//--- fill histograms with events passing final selection

    std::string stEta;
    std::string stLeadPt;
    std::string stSubPt;
    if (selLepton_lead->pt_ >= 10 && selLepton_lead->pt_ < 25) stLeadPt = "L";
    else if (selLepton_lead->pt_ >= 25 && selLepton_lead->pt_ < 50) stLeadPt = "M";
    else if (selLepton_lead->pt_ > 50) stLeadPt = "H";
    if (selLepton_sublead->pt_ >= 10 && selLepton_sublead->pt_ < 25) stSubPt = "L";
    else if (selLepton_sublead->pt_ >= 25 && selLepton_sublead->pt_ < 50) stSubPt = "M";
    else if (selLepton_sublead->pt_ > 50) stSubPt = "H";
    else assert(0);

    Double_t etaL1 = std::fabs(selLepton_lead->eta_);
    Double_t etaL2 = std::fabs(selLepton_sublead->eta_);
    if (etaL1 < 1.479 && etaL2 < 1.479) stEta = "BB";
    else if (etaL1 > 1.479 && etaL2 > 1.479) stEta = "EE";
    else if (etaL1 < etaL2) stEta = "BE";
    else
    {
      if (std::strncmp(stLeadPt.data(), stSubPt.data(), 1) == 0) stEta = "BE";       //Symmetric case
      else stEta = "EB";
    }
    std::string category = Form("%s_%s%s", stEta.data(), stLeadPt.data(), stSubPt.data());

    std::string charge_cat = ( isCharge_SS ) ? "SS" : "OS";
    if (std::strncmp(process_string.data(), "DY", 2) == 0){    //Split DY
      const GenLepton *gp0 = preselElectrons[0]->genLepton_;
      const GenLepton *gp1 = preselElectrons[1]->genLepton_;
      if (gp0 != 0 && gp1 != 0 && abs(preselElectrons[0]->pdgId_) == abs(gp0->pdgId_) && abs(preselElectrons[1]->pdgId_) == abs(gp1->pdgId_)) {
        histos[charge_cat][category.data()]["DY"]->Fill(mass_ll, evtWeight);
        histos[charge_cat]["total"]["DY"]->Fill(mass_ll, evtWeight);
      }
      else {
        histos[charge_cat][category.data()]["DY_fake"]->Fill(mass_ll, evtWeight);
        histos[charge_cat]["total"]["DY_fake"]->Fill(mass_ll, evtWeight);
      }
    }
    else {//Otherwise
      histos[charge_cat][category.data()][process_string]->Fill(mass_ll, evtWeight);
      histos[charge_cat]["total"][process_string]->Fill(mass_ll, evtWeight);
    }     

    if (!useData){
      histos[charge_cat][category.data()]["data_obs"]->Fill(mass_ll, evtWeight);
      histos[charge_cat]["total"]["data_obs"]->Fill(mass_ll, evtWeight);      
    }
    if (std::strncmp(process_string.data(), "DY", 2) == 0)
    {
      /*if(preselElectrons[0]->genLepton_ == 0 && preselElectrons[1]->genLepton_ == 0)
        std::cout << "doublejama " << std::endl;
      else if (preselElectrons[0]->genLepton_ == 0 || preselElectrons[1]->genLepton_ == 0)
        std::cout << "lihtjama " << std::endl;
      else
        std::cout << "nojama " << std::endl;*/
      for (int i = 0; i < 2; i++)
      {
        const GenLepton *gp = preselElectrons[i]->genLepton_;
        if (gp == 0)
        {
          //std::cout << "jama " << i << " " << preselElectrons[i]->pt_ << " " << preselElectrons[i]->eta_ << std::endl;
          continue;
        }
        gen_eff->FillWeighted(preselElectrons[i]->charge_ != gp->charge_, evtWeight, gp->pt_, std::fabs(gp->eta_));
      }
      const GenLepton *gen1 = preselElectrons[0]->genLepton_;
      const GenLepton *gen2 = preselElectrons[1]->genLepton_;
      if (!(gen1 == 0 || gen2 == 0)){
        const GenLepton *gp1;
        const GenLepton *gp2;
        if (gen2->pt_ > gen1->pt_){        
          gp1 = gen2;
          gp2 = gen1;
        }
        else {
          gp1 = gen1;
          gp2 = gen2;
        }
        std::string stEtaGen;
        std::string stLeadPtGen;
        std::string stSubPtGen;
        assert(gp1->pt_ >= gp2->pt_);
        if (gp1->pt_ >= 10 && gp1->pt_ < 25) stLeadPtGen = "L";
        else if (gp1->pt_ >= 25 && gp1->pt_ < 50) stLeadPtGen = "M";
        else if (gp1->pt_ > 50) stLeadPtGen = "H";
        if (gp2->pt_ >= 10 && gp2->pt_ < 25) stSubPtGen = "L";
        else if (gp2->pt_ >= 25 && gp2->pt_ < 50) stSubPtGen = "M";
        else if (gp2->pt_ > 50) stSubPtGen = "H";
        else assert(0);

        Double_t etaL1Gen = std::fabs(gp1->eta_);
        Double_t etaL2Gen = std::fabs(gp2->eta_);
        if (etaL1Gen < 1.479 && etaL2Gen < 1.479) stEtaGen = "BB";
        else if (etaL1Gen > 1.479 && etaL2Gen > 1.479) stEtaGen = "EE";
        else if (etaL1Gen < etaL2Gen) stEtaGen = "BE";
        else
        {
          if (std::strncmp(stLeadPtGen.data(), stSubPtGen.data(), 1) == 0) stEtaGen = "BE";       //Symmetric case
          else stEtaGen = "EB";
        }
        std::string categoryGen = Form("%s_%s%s", stEtaGen.data(), stLeadPtGen.data(), stSubPtGen.data());
        std::string charge_catGen = ( isCharge_SS ) ? "SS" : "OS";
        histos_2gen[charge_catGen][categoryGen.data()][process_string]->Fill(mass_ll, evtWeight);
        histos_2gen[charge_catGen]["total"][process_string]->Fill(mass_ll, evtWeight);
      }
    }

    if (isCharge_SS)
      preselElectronHistManagerSS.fillHistograms(preselElectrons, evtWeight);
    else if (isCharge_OS)
      preselElectronHistManagerOS.fillHistograms(preselElectrons, evtWeight);

    if (!useData){
      for ( vstring::const_iterator which = categories_charge.begin(); 	which != categories_charge.end(); ++which ) {
        for ( vstring::const_iterator category = categories_etapt.begin(); 	category != categories_etapt.end(); ++category ) {
          for (int b = 0; b <= histos[which->data()][*category]["data_obs"]->GetNbinsX(); b++)
          {
            histos[which->data()][*category]["data_obs"]->SetBinError(b, sqrt(histos[which->data()][*category]["data_obs"]->GetBinContent(b)));
          }
        }
      }
    }
    (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;

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

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);

  clock.Show("analyze_charge_flip");

  return EXIT_SUCCESS;
}
