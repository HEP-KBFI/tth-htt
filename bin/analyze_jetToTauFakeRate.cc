
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
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
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
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRate.h" // EvtHistManager_jetToTauFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface.h
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

int getHadTau_genPdgId(const RecoHadTau* hadTau)
{
  int hadTau_genPdgId = -1;
  if      ( hadTau->genHadTau_ ) hadTau_genPdgId = 15;
  else if ( hadTau->genLepton_ ) hadTau_genPdgId = std::abs(hadTau->genLepton_->pdgId_);
  return hadTau_genPdgId;
}

/**
 * @brief Auxiliary class for filling histograms for denominator
 */
struct denominatorHistManagers
{
  denominatorHistManagers(
    const std::string& process, int era, bool isMC, const std::string& chargeSelection, 
    double minAbsEta, double maxAbsEta, const std::string& central_or_shift)
    : process_(process),
      era_(era),
      isMC_(isMC),
      chargeSelection_(chargeSelection),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      central_or_shift_(central_or_shift),
      jetHistManager_(0),
      jetHistManager_genHadTau_(0),
      jetHistManager_genLepton_(0),
      jetHistManager_genJet_(0),
      hadTauHistManager_(0), 
      hadTauHistManager_genHadTau_(0),
      hadTauHistManager_genLepton_(0),
      hadTauHistManager_genJet_(0),
      fakeableHadTauSelector_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    subdir_ = Form("jetToTauFakeRate_%s/denominator/%s", chargeSelection_.data(), etaBin.data());
    fakeableHadTauSelector_ = new RecoHadTauSelectorFakeable(era_);
  }
  ~denominatorHistManagers()
  {
    delete jetHistManager_;
    delete jetHistManager_genHadTau_;
    delete jetHistManager_genLepton_;
    delete jetHistManager_genJet_;
    delete hadTauHistManager_;
    delete hadTauHistManager_genHadTau_;
    delete hadTauHistManager_genLepton_;
    delete hadTauHistManager_genJet_;
    delete fakeableHadTauSelector_;
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
    if ( jet.absEta_ > minAbsEta_ && jet.absEta_ < maxAbsEta_ ) {
      jetHistManager_->fillHistograms(jet, evtWeight);
      if ( isMC_ ) {
	if      ( jet.genHadTau_ ) jetHistManager_genHadTau_->fillHistograms(jet, evtWeight);
	else if ( jet.genLepton_ ) jetHistManager_genLepton_->fillHistograms(jet, evtWeight);
	else                       jetHistManager_genJet_->fillHistograms(jet, evtWeight);
      }
    }
    if ( hadTau.absEta_ > minAbsEta_ && hadTau.absEta_ < maxAbsEta_ ) {
      hadTauHistManager_->fillHistograms(hadTau, evtWeight);
      if ( isMC_ ) {
	if      ( hadTau.genHadTau_ ) hadTauHistManager_genHadTau_->fillHistograms(hadTau, evtWeight);
	else if ( hadTau.genLepton_ ) hadTauHistManager_genLepton_->fillHistograms(hadTau, evtWeight);
	else                          hadTauHistManager_genJet_->fillHistograms(hadTau, evtWeight);
      }
    }
  }			
  std::string process_;
  int era_;
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
  HadTauHistManager* hadTauHistManager_;
  HadTauHistManager* hadTauHistManager_genHadTau_;
  HadTauHistManager* hadTauHistManager_genLepton_;
  HadTauHistManager* hadTauHistManager_genJet_;
  RecoHadTauSelectorFakeable* fakeableHadTauSelector_;
};

/**
 * @brief Auxiliary class for applying hadronic tau selection and filling histograms for numerator
 */
struct numeratorSelector_and_HistManagers : public denominatorHistManagers
{
  numeratorSelector_and_HistManagers(
    const std::string& process, int era, bool isMC, const std::string& chargeSelection, 
    const std::string& hadTauSelection, double minAbsEta, double maxAbsEta, const std::string& central_or_shift)
    : denominatorHistManagers(process, era, isMC, chargeSelection, minAbsEta, maxAbsEta, central_or_shift),
      hadTauSelection_(hadTauSelection),
      tightHadTauSelector_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);    
    subdir_ = Form("jetToTauFakeRate_%s/numerator/%s/%s", chargeSelection_.data(), hadTauSelection_.data(), etaBin.data());
    tightHadTauSelector_ = new RecoHadTauSelectorTight(era_);
    tightHadTauSelector_->set(hadTauSelection);
  }
  ~numeratorSelector_and_HistManagers()
  {
    delete tightHadTauSelector_;
  }
  void bookHistograms(TFileDirectory& dir)
  {
    //std::cout << "<numeratorSelector_and_HistManagers::bookHistograms>:" << std::endl;
    //std::cout << " subdir = " << subdir_ << std::endl;
    denominatorHistManagers::bookHistograms(dir);
  } 		
  void fillHistograms(const RecoJet& jet, const RecoHadTau& hadTau, double evtWeight)					 
  {
    denominatorHistManagers::fillHistograms(jet, hadTau, evtWeight);   
  }
  std::string hadTauSelection_;
  RecoHadTauSelectorTight* tightHadTauSelector_;
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

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

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

  vdouble absEtaBins = cfg_analyze.getParameter<vdouble>("absEtaBins");
  if ( absEtaBins.size() < 2 ) throw cms::Exception("analyze_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins' !!\n";

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 

  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int lheScale_option = kLHE_scale_central;
  if ( isMC && central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_jetToTauFakeRate")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
      else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_thu_shape") ) {
      if      ( central_or_shift_tstring.EndsWith("x1Down") ) lheScale_option = kLHE_scale_xDown;
      else if ( central_or_shift_tstring.EndsWith("x1Up")   ) lheScale_option = kLHE_scale_xUp;
      else if ( central_or_shift_tstring.EndsWith("y1Down") ) lheScale_option = kLHE_scale_yDown;
      else if ( central_or_shift_tstring.EndsWith("y1Up")   ) lheScale_option = kLHE_scale_yUp;
      else assert(0);
    } else if ( !(central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") || 
		  central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt")) ) {
      throw cms::Exception("analyze_jetToTauFakeRate")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    }
  }

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", "dR03mvaTight");
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

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
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  preselHadTauSelector.set_min_id_cut_dR05(-1000);
  preselHadTauSelector.set_max_raw_cut_dR05(1.e+6);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);

  RecoJetReader* jetReader = new RecoJetReader(era, "nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader("nGenLep", "GenLep", "nGenLepFromTau", "GenLepFromTau");
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader("nGenJet", "GenJet");
    genJetReader->setBranchAddresses(inputTree);
    lheInfoReader = new LHEInfoReader();
    lheInfoReader->setBranchAddresses(inputTree);
  }

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
  int numEtaBins = absEtaBins.size() - 1;
  for ( int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin ) {
    double minAbsEta = absEtaBins[idxEtaBin];
    double maxAbsEta = absEtaBins[idxEtaBin + 1];

    denominatorHistManagers* denominator = new denominatorHistManagers(
      process_string, era, isMC, chargeSelection_string, minAbsEta, maxAbsEta, central_or_shift);
    denominator->bookHistograms(fs);
    denominators.push_back(denominator);

    for ( vstring::const_iterator hadTauSelection = hadTauSelections.begin();
	  hadTauSelection != hadTauSelections.end(); ++hadTauSelection ) {
      numeratorSelector_and_HistManagers* numerator = new numeratorSelector_and_HistManagers(
        process_string, era, isMC, chargeSelection_string, *hadTauSelection, minAbsEta, maxAbsEta, central_or_shift);
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

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/unbiased/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/sel/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("jetToTauFakeRate_%s/sel/lheInfo", chargeSelection_string.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
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

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
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

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ) {
      continue;
    }
    
//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 1e1mu, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC ) {
      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_1e1mu) ) {
	continue; 
      }
      if ( selTrigger_1mu && isTriggered_1e1mu ) {
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
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
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

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if ( isMC && !fillGenEvtHistograms ) {
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
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    // require exactly two leptons passing loose preselection criteria to avoid overlap with 3l category
    if ( !(preselLeptons.size() == 2) ) {
      continue;
    }
    cutFlowTable.update("2 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId_);
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId_);

    // require that trigger paths match event category (with event category based on preselLeptons);
    if ( preselElectrons.size() == 2 && !selTrigger_1e  ) {
      continue;
    }
    if ( preselMuons.size() == 2 && !selTrigger_1mu ) {
      continue;
    }
    if ( preselElectrons.size() == 1 && preselMuons.size() == 1 && !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ) {
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

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      evtWeight *= pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {	
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	evtWeight *= (*jet)->BtagWeight_;
      }
    }

    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        preselLepton_lead_type, preselLepton_lead->pt_, preselLepton_lead->eta_, 
	preselLepton_sublead_type, preselLepton_sublead->pt_, preselLepton_sublead->eta_);

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
	evtWeight *= dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
      }

//--- apply data/MC corrections for trigger efficiency,
//    and efficiencies for lepton to pass loose identification and isolation criteria      
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();
    }

//--- apply final event selection 
    std::vector<const RecoLepton*> selLeptons;    
    selLeptons.reserve(selElectrons.size() + selMuons.size());
    selLeptons.insert(selLeptons.end(), selElectrons.begin(), selElectrons.end());
    selLeptons.insert(selLeptons.end(), selMuons.begin(), selMuons.end());
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt);
    // require exactly two leptons passing tight selection criteria of final event selection 
    if ( !(selLeptons.size() == 2) ) {
      continue;
    }
    cutFlowTable.update("2 sel leptons", evtWeight);
    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    // require exactly one electron and one muon passing tight selection criteria
    if ( !(selElectrons.size() == 1 && selMuons.size() == 1) ) {
      continue;
    }
    cutFlowTable.update("1 sel electron && 1 sel muon", evtWeight);

    // require that trigger paths match event category (with event category based on selLeptons);
    if ( selElectrons.size() == 1 && selMuons.size() == 1 && !(selTrigger_1e  || selTrigger_1mu || selTrigger_1e1mu) ) {
      continue;
    }
    cutFlowTable.update("sel lepton trigger match", evtWeight);

    // apply requirement on jets (incl. b-tagged jets) 
    if ( !(selJets.size() >= 2) ) {
      continue;
    }
    cutFlowTable.update(">= 2 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
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
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);

    double minPt_lead = 20.;
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt_ > minPt_lead && selLepton_sublead->pt_ > minPt_sublead) ) {
      continue;
    }
    cutFlowTable.update("lead lepton pT > 20 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool isCharge_SS = selLepton_lead->charge_*selLepton_sublead->charge_ > 0;
    bool isCharge_OS = selLepton_lead->charge_*selLepton_sublead->charge_ < 0;
    if ( chargeSelection == kOS && isCharge_SS ) {
      continue;
    }
    if ( chargeSelection == kSS && isCharge_OS ) {
      continue;
    }
    cutFlowTable.update(Form("lepton-pair %s charge", chargeSelection_string.data()), evtWeight);

    if ( selLepton_lead->is_electron() && selLepton_sublead->is_electron() ) {
      if ( met_LD < 0.2 ) {
	continue;
      }
    }
    cutFlowTable.update("met LD > 0.2", evtWeight);

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
    if ( isMC ) {
      evtWeight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_woTightCharge();
    }   

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

      const RecoHadTau* preselHadTau_dRmatched = 0;
      double dRmin = 1.e+3;
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
	    preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
	double dR = deltaR((*preselHadTau)->eta_, (*preselHadTau)->phi_, (*cleanedJet)->eta_, (*cleanedJet)->phi_);
	if ( dR < dRmin || !preselHadTau_dRmatched ) {
	  preselHadTau_dRmatched = (*preselHadTau);
	  dRmin = dR;
	}
      }
      if ( !(preselHadTau_dRmatched && dRmin < 0.3) ) continue;

      std::vector<const RecoHadTau*> preselHadTau_ptrs;
      preselHadTau_ptrs.push_back(preselHadTau_dRmatched);
      std::vector<const RecoJet*> cleanedJets_wrtPreselHadTau = jetCleaner(selJets, preselHadTau_ptrs);
      std::vector<const RecoJet*> cleanedBJets_wrtPreselHadTau_loose = jetSelectorBtagLoose(cleanedJets_wrtPreselHadTau);
      std::vector<const RecoJet*> cleanedBJets_wrtPreselHadTau_medium = jetSelectorBtagMedium(cleanedJets_wrtPreselHadTau);    
      if ( !(cleanedBJets_wrtPreselHadTau_loose.size() >= 2 || cleanedBJets_wrtPreselHadTau_medium.size() >= 1) ) continue;
      
      for ( std::vector<denominatorHistManagers*>::iterator denominator = denominators.begin();
	    denominator != denominators.end(); ++denominator ) {
	if ( !(*(*denominator)->fakeableHadTauSelector_)(*preselHadTau_dRmatched) ) continue;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
	double evtWeight_denominator = evtWeight;
	dataToMCcorrectionInterface->setHadTauSelection((*denominator)->fakeableHadTauSelector_->get());
	int preselHadTau_dRmatched_genPdgId = getHadTau_genPdgId(preselHadTau_dRmatched);
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt_, preselHadTau_dRmatched->eta_);
	evtWeight_denominator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();

	(*denominator)->fillHistograms(**cleanedJet, *preselHadTau_dRmatched, evtWeight_denominator);
      }

      for ( std::vector<numeratorSelector_and_HistManagers*>::iterator numerator = numerators.begin();
	    numerator != numerators.end(); ++numerator ) {
	if ( !(*(*numerator)->tightHadTauSelector_)(*preselHadTau_dRmatched) ) continue;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates
	double evtWeight_numerator = evtWeight;
	dataToMCcorrectionInterface->setHadTauSelection((*numerator)->hadTauSelection_);
	int preselHadTau_dRmatched_genPdgId = getHadTau_genPdgId(preselHadTau_dRmatched);
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt_, preselHadTau_dRmatched->eta_);
	evtWeight_numerator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();

	(*numerator)->fillHistograms(**cleanedJet, *preselHadTau_dRmatched, evtWeight_numerator);
      }
    }

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_1e1mu);

  clock.Show("analyze_jetToTauFakeRate");

  return EXIT_SUCCESS;
}

