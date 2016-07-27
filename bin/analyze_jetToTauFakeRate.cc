
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
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2los_1tau category 
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
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // RecoElectronSelectorTight, RecoMuonSelectorTight, RecoHadTauSelectorLoose, RecoHadTauSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRate.h" // EvtHistManager_jetToTauFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

//--- declare constants
const double met_coef = 0.00397;
const double mht_coef = 0.00265;

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2)
{
  return (particle1->pt_ > particle2->pt_);
}

std::string getEtaBin(double minAbsEta, double maxAbsEta)
{
  std::string absEtaBin = "";
  if      ( minAbsEta > 0. && maxAbsEta > 0. ) absEtaBin.append(Form("absEta%1.1fto%1.1f", minAbsEta, maxAbsEta));
  else if ( minAbsEta > 0.                   ) absEtaBin.append(Form("absEtaGt%1.1f", minAbsEta));
  else if (                   maxAbsEta > 0. ) absEtaBin.append(Form("absEtaLt%1.1f", maxAbsEta));
  absEtaBin = TString(absEtaBin.data()).ReplaceAll(".", "_").Data();
  return absEtaBin;
}

/**
 * @brief Auxiliary class for filling histograms for denominator
 */
struct denominatorHistManagers
{
  denominatorHistManagers(
    const std::string& process, bool isMC, const std::string& chargeSelection, 
    double minAbsEta, double maxAbsEta, const std::string& central_or_shift)
    : process_(process),
      isMC_(isMC),
      chargeSelection_(chargeSelection),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      central_or_shift_(central_or_shift),
      jetHistManager_(0),
      jetHistManager_genHadTau_(0),
      jetHistManager_genLepton_(0),
      jetHistManager_genJet_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    subdir_ = Form("jetToTauFakeRate_%s/denominator/%s", chargeSelection_.data(), etaBin.data());
  }
  ~denominatorHistManagers()
  {
    delete jetHistManager_;
    delete jetHistManager_genHadTau_;
    delete jetHistManager_genLepton_;
    delete jetHistManager_genJet_;
  }
  void bookHistograms(TFileDirectory& dir)
  {
    //std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;
    //std::cout << " subdir = " << subdir_ << std::endl;
    jetHistManager_ = new JetHistManager(makeHistManager_cfg(process_, 
      Form("%s/jets", subdir_.data()), central_or_shift_));
    jetHistManager_->bookHistograms(dir);
    if ( isMC_ ) {
      std::string process_and_genMatchedHadTau = process_ + "t";
      jetHistManager_genHadTau_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, 
        Form("%s/jets", subdir_.data()), central_or_shift_));
      jetHistManager_genHadTau_->bookHistograms(dir);
      std::string process_and_genMatchedLepton = process_ + "l";
      jetHistManager_genLepton_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedLepton, 
        Form("%s/jets", subdir_.data()), central_or_shift_));
      jetHistManager_genLepton_->bookHistograms(dir);
      std::string process_and_genMatchedJet = process_ + "j";
      jetHistManager_genJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatchedJet, 
        Form("%s/jets", subdir_.data()), central_or_shift_));
      jetHistManager_genJet_->bookHistograms(dir);
    }
  } 					 
  void fillHistograms(const RecoJet& jet, double evtWeight)					 
  {
    if ( !(jet.absEta_ > minAbsEta_ && jet.absEta_ < maxAbsEta_) ) return;
    jetHistManager_->fillHistograms(jet, evtWeight);
    if ( isMC_ ) {
      if      ( jet.genHadTau_ ) jetHistManager_genHadTau_->fillHistograms(jet, evtWeight);
      else if ( jet.genLepton_ ) jetHistManager_genLepton_->fillHistograms(jet, evtWeight);
      else                       jetHistManager_genJet_->fillHistograms(jet, evtWeight);
    }
  }			
  std::string process_;
  bool isMC_;
  std::string chargeSelection_;
  double minAbsEta_;
  double maxAbsEta_;
  std::string central_or_shift_;
  std::string subdir_;
  JetHistManager* jetHistManager_;
  JetHistManager* jetHistManager_genHadTau_;
  JetHistManager* jetHistManager_genLepton_;
  JetHistManager* jetHistManager_genJet_;
};

/**
 * @brief Auxiliary class for applying hadronic tau selection and filling histograms for numerator
 */
struct numeratorSelector_and_HistManagers : public denominatorHistManagers
{
  numeratorSelector_and_HistManagers(
    const std::string& process, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection, double minAbsEta, double maxAbsEta, const std::string& central_or_shift)
    : denominatorHistManagers(process, isMC, chargeSelection, minAbsEta, maxAbsEta, central_or_shift),
      hadTauSelection_(hadTauSelection),
      hadTauSelector_(0),
      hadTauHistManager_(0), 
      hadTauHistManager_genHadTau_(0),
      hadTauHistManager_genLepton_(0),
      hadTauHistManager_genJet_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);    
    subdir_ = Form("jetToTauFakeRate_%s/numerator/%s/%s", chargeSelection_.data(), hadTauSelection_.data(), etaBin.data());
    hadTauSelector_ = new RecoHadTauSelectorTight();
    hadTauSelector_->set(hadTauSelection);
  }
  ~numeratorSelector_and_HistManagers()
  {
    delete hadTauSelector_;
    delete hadTauHistManager_;
    delete hadTauHistManager_genHadTau_;
    delete hadTauHistManager_genLepton_;
    delete hadTauHistManager_genJet_;
  }
  void bookHistograms(TFileDirectory& dir)
  {
    //std::cout << "<numeratorSelector_and_HistManagers::bookHistograms>:" << std::endl;
    //std::cout << " subdir = " << subdir_ << std::endl;
    denominatorHistManagers::bookHistograms(dir);
    hadTauHistManager_ = new HadTauHistManager(makeHistManager_cfg(process_, 
      Form("%s/hadTaus", subdir_.data()), central_or_shift_));
    hadTauHistManager_->bookHistograms(dir);
    if ( isMC_ ) {
      std::string process_and_genMatchedHadTau = process_ + "t";
      hadTauHistManager_genHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, 
        Form("%s/hadTaus", subdir_.data()), central_or_shift_));
      hadTauHistManager_genHadTau_->bookHistograms(dir);
      std::string process_and_genMatchedLepton = process_ + "l";
      hadTauHistManager_genLepton_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedLepton, 
        Form("%s/hadTaus", subdir_.data()), central_or_shift_));
      hadTauHistManager_genLepton_->bookHistograms(dir);
      std::string process_and_genMatchedJet = process_ + "j";
      hadTauHistManager_genJet_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatchedJet, 
        Form("%s/hadTaus", subdir_.data()), central_or_shift_));
      hadTauHistManager_genJet_->bookHistograms(dir);
    }
  } 		
  void fillHistograms(const RecoJet& jet, const RecoHadTau& hadTau, double evtWeight)					 
  {
    denominatorHistManagers::fillHistograms(jet, evtWeight);
    if ( !(jet.absEta_ > minAbsEta_ && jet.absEta_ < maxAbsEta_) ) return;
    hadTauHistManager_->fillHistograms(hadTau, evtWeight);
    if ( isMC_ ) {
      if      ( hadTau.genHadTau_ ) hadTauHistManager_genHadTau_->fillHistograms(hadTau, evtWeight);
      else if ( hadTau.genLepton_ ) hadTauHistManager_genLepton_->fillHistograms(hadTau, evtWeight);
      else                          hadTauHistManager_genJet_->fillHistograms(hadTau, evtWeight);
    }
  }
  std::string hadTauSelection_;
  RecoHadTauSelectorTight* hadTauSelector_;
  HadTauHistManager* hadTauHistManager_;
  HadTauHistManager* hadTauHistManager_genHadTau_;
  HadTauHistManager* hadTauHistManager_genLepton_;
  HadTauHistManager* hadTauHistManager_genJet_;
};

/**
 * @brief Produce datacard and control plots for 2los_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << "<analyze_jetToTauFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_jetToTauFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_jetToTauFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_jetToTauFakeRate");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  int chargeSelection = -1;
  if      ( chargeSelection_string == "OS" ) chargeSelection = kOS;
  else if ( chargeSelection_string == "SS" ) chargeSelection = kSS;
  else throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !!\n";

  double jet_minPt = cfg_analyze.getParameter<double>("jet_minPt");
  double jet_maxPt = cfg_analyze.getParameter<double>("jet_maxPt");
  double jet_minAbsEta = cfg_analyze.getParameter<double>("jet_minAbsEta");
  double jet_maxAbsEta = cfg_analyze.getParameter<double>("jet_maxAbsEta");

  vstring hadTauSelections = cfg_analyze.getParameter<vstring>("hadTauSelections");

  vdouble hadTauAbsEtaBins = cfg_analyze.getParameter<vdouble>("hadTauAbsEtaBins");
  if ( hadTauAbsEtaBins.size() < 2 ) throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'hadTauAbsEtaBins' !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;

  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";

  int jetPt_option = RecoJetReader::kJetPt_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_jetToTauFakeRate")
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
    } else throw cms::Exception("analyze_jetToTauFakeRate")
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
    throw cms::Exception("analyze_jetToTauFakeRate") 
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

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

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
  LV met_p4(met_pt, met_eta, met_phi, 0.);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader("nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorTight tightMuonSelector;

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector;
  RecoElectronCollectionSelectorTight tightElectronSelector;

  RecoHadTauReader* hadTauReader = new RecoHadTauReader("nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector;
  preselHadTauSelector.set_min_id_cut_dR05(-1000);
  preselHadTauSelector.set_max_raw_cut_dR05(1.e+6);
  RecoHadTauCollectionSelectorTight tightHadTauSelector;

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

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

  ElectronHistManager selElectronHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/electrons", chargeSelection_string.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/muons", chargeSelection_string.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genHadTau(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genHadTau", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genHadTau.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genElectron(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genElectron", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genElectron.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genMuon(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genMuon", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genMuon.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genJet(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/hadTaus_genJet", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genJet.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/jets", chargeSelection_string.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/leadJet", chargeSelection_string.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/subleadJet", chargeSelection_string.data()), central_or_shift, 1));
  selJetHistManager_sublead.bookHistograms(fs);

  std::vector<denominatorHistManagers*> denominators;
  std::vector<numeratorSelector_and_HistManagers*> numerators;
  int numEtaBins = hadTauAbsEtaBins.size() - 1;
  for ( int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin ) {
    double minAbsEta = hadTauAbsEtaBins[idxEtaBin];
    double maxAbsEta = hadTauAbsEtaBins[idxEtaBin + 1];

    denominatorHistManagers* denominator = new denominatorHistManagers(
      process_string, isMC, chargeSelection_string, minAbsEta, maxAbsEta, central_or_shift);
    denominator->bookHistograms(fs);
    denominators.push_back(denominator);

    for ( vstring::const_iterator hadTauSelection = hadTauSelections.begin();
	  hadTauSelection != hadTauSelections.end(); ++hadTauSelection ) {
      numeratorSelector_and_HistManagers* numerator = new numeratorSelector_and_HistManagers(
        process_string, isMC, chargeSelection_string, *hadTauSelection, minAbsEta, maxAbsEta, central_or_shift);
      numerator->bookHistograms(fs);
      numerators.push_back(numerator);
    }
  }

  JetHistManager selBJet_looseHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/BJets_loose", chargeSelection_string.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/leadBJet_loose", chargeSelection_string.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/subleadBJet_loose", chargeSelection_string.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/BJets_medium", chargeSelection_string.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/met", chargeSelection_string.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  EvtHistManager_jetToTauFakeRate selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("jetToTauFakeRate_%s/evt", chargeSelection_string.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);

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

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl; 
	std::cout << " (selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }
    
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 1e1mu, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_1e1mu) ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl; 
	  std::cout << " (selTrigger_1e = " << selTrigger_1e 
		    << ", isTriggered_1mu = " << isTriggered_1mu 
		    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
	}
	continue; 
      }
      if ( selTrigger_1mu && isTriggered_1e1mu ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS trigger selection." << std::endl; 
	  std::cout << " (selTrigger_1mu = " << selTrigger_1mu 
		    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
	}
	continue; 
      }
    }
    cutFlowTable.update("trigger");

    if ( (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
	 (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
	 (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ) {
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
//--- split hadronic tau candidates into different collections,
//    depending on whether they are genuine hadronic taus, e->tau fakes, mu->tau fakes, or jet->tau fakes
    std::vector<const RecoHadTau*> preselHadTaus_genHadTau;
    std::vector<const RecoHadTau*> preselHadTaus_genElectron;
    std::vector<const RecoHadTau*> preselHadTaus_genMuon;
    std::vector<const RecoHadTau*> preselHadTaus_genJet;

    for ( std::vector<const RecoHadTau*>::const_iterator hadTau = preselHadTaus.begin();
          hadTau != preselHadTaus.end(); ++hadTau ) {
      if      ( (*hadTau)->genHadTau_                                                  ) preselHadTaus_genHadTau.push_back(*hadTau);   // generator level match to hadronic tau decay 
      else if ( (*hadTau)->genLepton_ && std::abs((*hadTau)->genLepton_->pdgId_) == 11 ) preselHadTaus_genElectron.push_back(*hadTau); // generator level match to electron 
      else if ( (*hadTau)->genLepton_ && std::abs((*hadTau)->genLepton_->pdgId_) == 13 ) preselHadTaus_genMuon.push_back(*hadTau);     // generator level match to muon
      else                                                                               preselHadTaus_genJet.push_back(*hadTau);      // generator level match to jet (or pileup)
    }
    std::vector<const RecoHadTau*> selHadTaus = tightHadTauSelector(preselHadTaus);
    std::vector<const RecoHadTau*> selHadTaus_genHadTau = tightHadTauSelector(preselHadTaus_genHadTau);
    std::vector<const RecoHadTau*> selHadTaus_genElectron = tightHadTauSelector(preselHadTaus_genElectron);
    std::vector<const RecoHadTau*> selHadTaus_genMuon = tightHadTauSelector(preselHadTaus_genMuon);
    std::vector<const RecoHadTau*> selHadTaus_genJet = tightHadTauSelector(preselHadTaus_genJet);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selMuons, selElectrons);
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
    // require exactly two leptons passing loose preselection criteria to avoid overlap with 3l category
    if ( !(preselLeptons.size() == 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS preselLeptons selection." << std::endl;
	std::cout << " (#preselLeptons = " << preselLeptons.size() << ")" << std::endl;
	for ( size_t idxPreselLepton = 0; idxPreselLepton < preselLeptons.size(); ++idxPreselLepton ) {
	  std::cout << "preselLepton #" << idxPreselLepton << ":" << std::endl;
	  std::cout << (*preselLeptons[idxPreselLepton]);
	}
      }
      continue;
    }
    cutFlowTable.update("2 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId_);
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId_);

    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !selTrigger_1e  ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    if ( preselMuons.size() == 2 && !selTrigger_1mu ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselMuons = " << preselMuons.size() 
		  << ", selTrigger_1mu = " << selTrigger_1mu << ")" << std::endl;
      }
      continue;
    }
    if ( preselElectrons.size() == 1 && preselMuons.size() == 1 && !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given preselLepton multiplicity." << std::endl; 
	std::cout << " (#preselElectrons = " << preselElectrons.size() 
		  << ", #preselMuons = " << preselMuons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1mu = " << selTrigger_1mu
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("presel lepton trigger match");

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
    for ( std::vector<const RecoHadTau*>::const_iterator hadTau = selHadTaus.begin();
	  hadTau != selHadTaus.end(); ++hadTau ) {
      mht_p4 += (*hadTau)->p4_;
    }
    const LV met_p4(met_pt, met_eta, met_phi, 0.);
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
      evtWeight *= sf_triggerEff(2,
        preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
      evtWeight *= sf_leptonID_and_Iso_loose(2,
        preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);
    }    

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly two leptons passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() == 2) ) {
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
    cutFlowTable.update("2 sel leptons", evtWeight);
    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    // require exactly one electron and one muon passing tight selection criteria
    if ( !(selElectrons.size() == 1 && selMuons.size() == 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selElectrons+selMuons selection." << std::endl;
	std::cout << " (#selElectrons = " << selElectrons.size() << ")" << std::endl;
	for ( size_t idxSelElectron = 0; idxSelElectron < selElectrons.size(); ++idxSelElectron ) {
	  std::cout << "selElectron #" << idxSelElectron << ":" << std::endl;
	  std::cout << (*selElectrons[idxSelElectron]);
	}
	std::cout << " (#selMuon = " << selMuons.size() << ")" << std::endl;
	for ( size_t idxSelMuon = 0; idxSelMuon < selMuons.size(); ++idxSelMuon ) {
	  std::cout << "selMuon #" << idxSelMuon << ":" << std::endl;
	  std::cout << (*selMuons[idxSelMuon]);
	}
      }
      continue;
    }
    cutFlowTable.update("1 sel electron && 1 sel muon", evtWeight);

    // require that trigger paths match event category (with event category based on selLeptons);
    if ( selElectrons.size() == 1 && selMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection for given selLepton multiplicity." << std::endl; 
	std::cout << " (#selElectrons = " << selElectrons.size() 
		  << ", #selMuons = " << selMuons.size() 
		  << ", selTrigger_1e = " << selTrigger_1e 
		  << ", selTrigger_1mu = " << selTrigger_1mu 
		  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("sel lepton trigger match", evtWeight);

    // apply requirement on jets (incl. b-tagged jets) 
    if ( !(selJets.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selJets selection." << std::endl;
	std::cout << " (#selJets = " << selJets.size() << ")" << std::endl;
	for ( size_t idxSelJet = 0; idxSelJet < selJets.size(); ++idxSelJet ) {
	  std::cout << "selJet #" << idxSelJet << ":" << std::endl;
	  std::cout << (*selJets[idxSelJet]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS selBJets selection." << std::endl;
	std::cout << " (#selBJets_loose = " << selBJets_loose.size() << ", #selBJets_medium = " << selBJets_medium.size() << ")" << std::endl;
	for ( size_t idxSelBJet_loose = 0; idxSelBJet_loose < selBJets_loose.size(); ++idxSelBJet_loose ) {
	  std::cout << "selJet #" << idxSelBJet_loose << ":" << std::endl;
	  std::cout << (*selJets[idxSelBJet_loose]);
	}
	for ( size_t idxSelBJet_medium = 0; idxSelBJet_medium < selBJets_medium.size(); ++idxSelBJet_medium ) {
	  std::cout << "selJet #" << idxSelBJet_medium << ":" << std::endl;
	  std::cout << (*selJets[idxSelBJet_medium]);
	}
      }
      continue;
    }
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);

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
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);

    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt_ > minPt_lead && selLepton_sublead->pt_ > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton pT selection." << std::endl;
	std::cout << " (leading selLepton pT = " << selLepton_lead->pt_ << ", minPt_lead = " << minPt_lead
		  << ", subleading selLepton pT = " << selLepton_sublead->pt_ << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 20 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool isCharge_SS = selLepton_lead->charge_*selLepton_sublead->charge_ > 0;
    bool isCharge_OS = selLepton_lead->charge_*selLepton_sublead->charge_ < 0;
    if ( chargeSelection == kOS && isCharge_SS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge_ 
		  << ", subleading selLepton charge = " << selLepton_sublead->charge_ << ", chargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( chargeSelection == kSS && isCharge_OS ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton charge selection." << std::endl;
	std::cout << " (leading selLepton charge = " << selLepton_lead->charge_ 
		  << ", subleading selLepton charge = " << selLepton_sublead->charge_ << ", chargeSelection = SS)" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(Form("lepton-pair %s charge", chargeSelection_string.data()), evtWeight);

    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      if ( met_LD < 0.2 ) {
	if ( run_lumi_eventSelector ) {
	  std::cout << "event FAILS MET LD selection." << std::endl;
	  std::cout << " (LD = " << met_LD << ")" << std::endl;
	}
	continue;
      }
    }
    cutFlowTable.update("met LD > 0.2", evtWeight);

//--- fill histograms with events passing final selection 
    selMuonHistManager.fillHistograms(selMuons, evtWeight);
    selElectronHistManager.fillHistograms(selElectrons, evtWeight);
    selHadTauHistManager.fillHistograms(selHadTaus, evtWeight);
    selHadTauHistManager_genHadTau.fillHistograms(selHadTaus_genHadTau, evtWeight);
    selHadTauHistManager_genElectron.fillHistograms(selHadTaus_genElectron, evtWeight);
    selHadTauHistManager_genMuon.fillHistograms(selHadTaus_genMuon, evtWeight);
    selHadTauHistManager_genJet.fillHistograms(selHadTaus_genJet, evtWeight);
    selJetHistManager.fillHistograms(selJets, evtWeight);
    selJetHistManager_lead.fillHistograms(selJets, evtWeight);
    selJetHistManager_sublead.fillHistograms(selJets, evtWeight);
    selBJet_looseHistManager.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_lead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_looseHistManager_sublead.fillHistograms(selBJets_loose, evtWeight);
    selBJet_mediumHistManager.fillHistograms(selBJets_medium, evtWeight);
    selMEtHistManager.fillHistograms(met_p4, mht_p4, met_LD, evtWeight);
    selEvtHistManager.fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
      evtWeight);

//--- iterate over jets
    for ( std::vector<const RecoJet*>::const_iterator cleanedJet = cleanedJets.begin();
	  cleanedJet != cleanedJets.end(); ++cleanedJet ) {
      if ( !((*cleanedJet)->pt_ > jet_minPt && std::fabs((*cleanedJet)->eta_) > jet_minAbsEta  &&
	     (*cleanedJet)->pt_ < jet_maxPt && std::fabs((*cleanedJet)->eta_) < jet_maxAbsEta) ) continue;

      for ( std::vector<denominatorHistManagers*>::iterator denominator = denominators.begin();
	    denominator != denominators.end(); ++denominator ) {
	(*denominator)->fillHistograms(**cleanedJet, evtWeight);
      }

      std::vector<const RecoHadTau*> preselHadTaus_dRmatched;
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
	    preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
	double dR = deltaR((*preselHadTau)->eta_, (*preselHadTau)->phi_, (*cleanedJet)->eta_, (*cleanedJet)->phi_);
	if ( dR < 0.3 ) preselHadTaus_dRmatched.push_back(*preselHadTau);
      }

      for ( std::vector<numeratorSelector_and_HistManagers*>::iterator numerator = numerators.begin();
	    numerator != numerators.end(); ++numerator ) {
	const RecoHadTau* selHadTau_dRmatched = 0;
	double dRmin = 1.e+3;
	for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus_dRmatched.begin();
	      preselHadTau != preselHadTaus_dRmatched.end(); ++preselHadTau ) {
	  if ( !(*(*numerator)->hadTauSelector_)(**preselHadTau) ) continue;
	  double dR = deltaR((*preselHadTau)->eta_, (*preselHadTau)->phi_, (*cleanedJet)->eta_, (*cleanedJet)->phi_);
	  if ( dR < dRmin || !selHadTau_dRmatched ) {
	    selHadTau_dRmatched = (*preselHadTau);
	    dRmin = dR;
	  }
	}
	if ( !(selHadTau_dRmatched && dRmin < 0.3) ) continue;

	std::vector<const RecoHadTau*> selHadTau_ptrs;
	selHadTau_ptrs.push_back(selHadTau_dRmatched);
	std::vector<const RecoJet*> cleanedJets_wrtSelHadTau = jetCleaner(selJets, selHadTau_ptrs);
	std::vector<const RecoJet*> cleanedBJets_wrtSelHadTau_loose = jetSelectorBtagLoose(cleanedJets_wrtSelHadTau);
	std::vector<const RecoJet*> cleanedBJets_wrtSelHadTau_medium = jetSelectorBtagMedium(cleanedJets_wrtSelHadTau);    
	if ( !(cleanedBJets_wrtSelHadTau_loose.size() >= 2 || cleanedBJets_wrtSelHadTau_medium.size() >= 1) ) continue;

	if ( selHadTau_dRmatched ) {
	  (*numerator)->fillHistograms(**cleanedJet, *selHadTau_dRmatched, evtWeight);
	}
      }
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

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1e1mu);

  clock.Show("analyze_jetToTauFakeRate");

  return EXIT_SUCCESS;
}

