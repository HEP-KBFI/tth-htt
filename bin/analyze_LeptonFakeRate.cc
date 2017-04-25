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
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2los_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
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
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <TLorentzVector.h>


typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied


// --------- MY NEW FUNCTIONS                                                                                                                                                                             
std::string getEtaBin(double minAbsEta, double maxAbsEta)
{
  std::string absEtaBin = "";
  if      ( minAbsEta > 0. && maxAbsEta > 0. ) absEtaBin.append(Form("absEta%1.1fto%1.1f", minAbsEta, maxAbsEta));
  else if ( minAbsEta > 0.                   ) absEtaBin.append(Form("absEtaGt%1.1f", minAbsEta));
  else if (                   maxAbsEta > 0. ) absEtaBin.append(Form("absEtaLt%1.1f", maxAbsEta));
  absEtaBin = TString(absEtaBin.data()).ReplaceAll(".", "_").Data();
  return absEtaBin;
}


std::string getPtBin(double minPt, double maxPt)
{
  std::string PtBin = "";
  if ( minPt > 0. && maxPt > 0. ) PtBin.append(Form("Pt%1.1fto%1.1f", minPt, maxPt));
  else if ( minPt > 0. ) PtBin.append(Form("PtGt%1.1f", minPt));
  else if ( maxPt > 0. ) PtBin.append(Form("PtLt%1.1f", maxPt));
  PtBin = TString(PtBin.data()).ReplaceAll(".", "_").Data();
  return PtBin;
}



class LeptonJetPairMaker
{
 public:
  LeptonJetPairMaker(const RecoLepton* fakeableLepton, const RecoJet* selJet) 
                      : fakeableLepton_(fakeableLepton)
                      , selJet_(selJet)
  {
    dR_ = deltaR((fakeableLepton_)->eta(), (fakeableLepton_)->phi(), (selJet_)->eta(), (selJet_)->phi());
  }   
  ~LeptonJetPairMaker(){}

  double getDeltaR() const { return dR_; }
  const RecoLepton* getLepton() const { return fakeableLepton_; }
  const RecoJet* getJet() const { return selJet_; }

 private:
  const RecoLepton* fakeableLepton_;
  const RecoJet* selJet_;
  double dR_;
};


bool SortByDeltaR(LeptonJetPairMaker Pair1, LeptonJetPairMaker Pair2){
  return Pair1.getDeltaR() > Pair2.getDeltaR();
 

}



// ----- overriding functions written inside "../src/hltPath.cc" ----
std::vector<hltPath*> create_hltPaths(const std::vector<std::string>& branchNames, double minPt, double maxPt)
{
  std::vector<hltPath*> hltPaths;
  for ( std::vector<std::string>::const_iterator branchName = branchNames.begin();
        branchName != branchNames.end(); ++branchName ) {
    hltPaths.push_back(new hltPath(*branchName, minPt, maxPt));
  }
  return hltPaths;
}


bool hltPaths_isTriggered(const std::vector<hltPath*>& hltPaths, double lepton_cone_pt){
  bool retVal = false;
  for ( std::vector<hltPath*>::const_iterator hltPath_iter = hltPaths.begin();
        hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    if ( lepton_cone_pt >= (*hltPath_iter)->getMinPt() && lepton_cone_pt <= (*hltPath_iter)->getMaxPt()  && (*hltPath_iter)->getValue() >= 1 ) {
      retVal = true;
      break;
    }
  }
  return retVal;
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

  std::cout << "<analyze_LeptonFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_LeptonFakeRate");


//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_LeptonFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_LeptonFakeRate");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  std::string era_string = cfg_analyze.getParameter<std::string>("era");

  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_LeptonFakeRate") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  // vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  // bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  
  // vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  // std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  // bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");

  // vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  // std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  // bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  edm::VParameterSet trigger_e_PSet = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e");
  std::vector<hltPath*> triggers_e;
  // std::vector<hltPath*>::iterator it1;
  for(edm::VParameterSet::const_iterator trigger_PSet = trigger_e_PSet.begin(); trigger_PSet != trigger_e_PSet.end(); trigger_PSet++){
    vstring trigger_paths_e = trigger_PSet->getParameter<vstring>("path");  // READ FROM THE VPSET                                                                                                    
    double minPt_e = trigger_PSet->getParameter<double>("cone_minPt");  // READ FROM THE VPSET                                                                                                    
    double maxPt_e = trigger_PSet->getParameter<double>("cone_maxPt");  // READ FROM THE VPSET                                                                                                    
    std::vector<hltPath*> hltPaths = create_hltPaths(trigger_paths_e, minPt_e, maxPt_e);
    // it1 = triggers_e.begin();
    triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end()); // TO CHANGE THE ORDER OF INSERTION USE triggers_e.begin()
  }
  
  
  edm::VParameterSet trigger_mu_PSet = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu");
  std::vector<hltPath*> triggers_mu;
  // std::vector<hltPath*>::iterator it2;
  for(edm::VParameterSet::const_iterator trigger_PSet = trigger_mu_PSet.begin(); trigger_PSet != trigger_mu_PSet.end(); trigger_PSet++){
    vstring trigger_paths_mu = trigger_PSet->getParameter<vstring>("path");  // READ FROM THE VPSET                                                                                               
    double minPt_mu = trigger_PSet->getParameter<double>("cone_minPt");  // READ FROM THE VPSET                                                                                                    
    double maxPt_mu = trigger_PSet->getParameter<double>("cone_maxPt");  // READ FROM THE VPSET                                                                                                      
    std::vector<hltPath*> hltPaths = create_hltPaths(trigger_paths_mu, minPt_mu, maxPt_mu);
    // it2 = triggers_mu.begin();
    triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end()); // TO CHANGE THE ORDER OF INSERTION USE triggers_mu.begin()
  }
  


  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  // bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  int chargeSelection = -1;
  if      ( chargeSelection_string == "OS" ) chargeSelection = kOS;
  else if ( chargeSelection_string == "SS" ) chargeSelection = kSS;
  else throw cms::Exception("analyze_LeptonFakeRate") 
    << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !!\n";
  
  /*
  double jet_minPt = cfg_analyze.getParameter<double>("jet_minPt");
  double jet_maxPt = cfg_analyze.getParameter<double>("jet_maxPt");
  double jet_minAbsEta = cfg_analyze.getParameter<double>("jet_minAbsEta");
  double jet_maxAbsEta = cfg_analyze.getParameter<double>("jet_maxAbsEta");
  vstring hadTauSelections = cfg_analyze.getParameter<vstring>("hadTauSelections");
  */


  vdouble absEtaBins = cfg_analyze.getParameter<vdouble>("absEtaBins");
  if ( absEtaBins.size() < 2 ) throw cms::Exception("analyze_LeptonFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins' !!\n";

  vdouble EtaBins_e = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  vdouble PtBins_e = cfg_analyze.getParameter<vdouble>("absPtBins_e"); 
  vdouble EtaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  vdouble PtBins_mu = cfg_analyze.getParameter<vdouble>("absPtBins_mu");

  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
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
    else throw cms::Exception("analyze_LeptonFakeRate")
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
      throw cms::Exception("analyze_LeptonFakeRate")
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
    throw cms::Exception("analyze_LeptonFakeRate") 
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


  hltPaths_setBranchAddresses(inputTree, triggers_e);
  hltPaths_setBranchAddresses(inputTree, triggers_mu);

  // hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

  GENWEIGHT_TYPE genWeight = 1.;
  PUWEIGHT_TYPE pileupWeight;
  if ( isMC ) {
    inputTree->SetBranchAddress(GENWEIGHT_KEY, &genWeight);
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }


//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3); // cleaning electrons from overlapping jets within cone radius 0.3
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3); // cleaning hadronic taus from overlapping jets within cone radius 0.3
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  preselHadTauSelector.set_min_id_cut_dR05(-1000);
  preselHadTauSelector.set_max_raw_cut_dR05(1.e+6);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, "nJet", "Jet");
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
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

// ------------------------------------------------

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/unbiased/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/sel/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/sel/lheInfo", chargeSelection_string.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }




  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;



  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);                                                                                                 
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);                                                                                             
  cutFlowTableType cutFlowTable;                                                                                                                                                                        
  
for( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {                                                                                    
       if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {                                                                                                                                    
            std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;                                                                               
            }                                                                                                                                                                                        


     ++analyzedEntries;                                                                                                                                                                              
     histogram_analyzedEntries->Fill(0.);                                                                                                                                                     
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
	int abs_pdgId = std::abs(genLepton->pdgId());
	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }
    

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
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
      if      ( (*hadTau)->genHadTau()                                                    ) preselHadTaus_genHadTau.push_back(*hadTau);   // generator level match to hadronic tau decay 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 11 ) preselHadTaus_genElectron.push_back(*hadTau); // generator level match to electron 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 13 ) preselHadTaus_genMuon.push_back(*hadTau);     // generator level match to muon
      else                                                                                  preselHadTaus_genJet.push_back(*hadTau);      // generator level match to jet (or pileup)
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
    	int abs_pdgId = std::abs(genLepton->pdgId());
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


    std::cout<< "chargeSelections " << chargeSelection  << std::endl;
    // std::cout<< "genElectrons.size() " << genElectrons.size() << " preselElectrons.size() " << preselElectrons.size() << " fakeableElectrons.size()  " << fakeableElectrons.size() << " selElectrons.size() "<< selElectrons.size() << std::endl; 
    // std::cout<< "genMuons.size() " << genMuons.size() << " preselMuons.size() " << preselMuons.size() << " fakeableMuons.size()  " << fakeableMuons.size() << " selMuons.size() "<< selMuons.size() << std::endl; 
    


    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);  
    // std::cout<< "fakeableLeptons.size() " << fakeableLeptons.size() << std::endl;
    // std::cout<< "selJets.size() " << selJets.size() << std::endl;

    // ----- Making the Lepton Jet pairs --------
    std::vector<LeptonJetPairMaker> LeptonJetPairs;
    for(unsigned int i=0; i<fakeableLeptons.size();i++){
       for(unsigned int j=0; j<selJets.size();j++){
	  LeptonJetPairMaker LeptonJetPair = LeptonJetPairMaker(fakeableLeptons[i], selJets[j]);
	  if(LeptonJetPair.getDeltaR() > 0.7){ LeptonJetPairs.push_back(LeptonJetPair);} // selecting lepton jet pairs seperated by deltaR > 0.7
	  
      }
    }

    std::sort (LeptonJetPairs.begin(), LeptonJetPairs.end(), SortByDeltaR); // sorting the pairs by deltaR()
    // std::cout<< "LeptonJetPairs.size() " << LeptonJetPairs.size() << std::endl;


    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

     if ( isMC ) {                                                                                                                                                                                     
          lheInfoReader->read();                                                                                                                                                                        
     }                                                                                                                                                                                                 
    
                                                                                                                                                                                                        
  
     //--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate                                                                                                    
     //   (using the method "Event reweighting using scale factors calculated with a tag and probe method",                                                                                             
     //    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )                                                                                              
     double evtWeight = 1.;                                                                                                                                                                             
     if ( isMC ) {                                                                                                                                                                                      
         evtWeight *= lumiScale;                                                                                                                                                                      
            if ( apply_genWeight ) evtWeight *= sgn(genWeight);                                                                                                                                        
                   evtWeight *= pileupWeight;                                                                                                                                                          
          
       if ( lheScale_option != kLHE_scale_central ) {                                                                                                                                                  
    	 if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();                                                                                          
    	 else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();                                                                                            
    	 else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();                                                                                          
    	 else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();                                                                                             
      }   

     }


/*
// ----- TRIGGER PART --------------
     bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);                                                                                                         
     bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);                                                                                                      
     // bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);                                                                                                  
     

                                                                                                                                                                                                
     bool selTrigger_1e = use_triggers_1e && isTriggered_1e;                                                                                                                                  
     bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;                                                                                                                                         
     // bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;                                                                                                                                

     // if ( !(selTrigger_1e || selTrigger_1mu || selTrigger_1e1mu) ){
     if ( !(selTrigger_1e || selTrigger_1mu) ){
          continue;
     }           
// ----------------------------------
*/



    if(isMC){
       genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
       lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }



    // ------ Trigger logic -------
    bool trigger_fired_e = false;
    bool trigger_fired_mu = false;
    for (std::vector<LeptonJetPairMaker>::const_iterator LeptonJetPair = LeptonJetPairs.begin();
         LeptonJetPair != LeptonJetPairs.end(); LeptonJetPair++)
    {
      if( LeptonJetPair->getLepton()->is_electron() && hltPaths_isTriggered(triggers_e, LeptonJetPair->getLepton()->cone_pt()) ){ trigger_fired_e = true;} // to ensure bool stays true once turned on  
      if( LeptonJetPair->getLepton()->is_muon() && hltPaths_isTriggered(triggers_mu, LeptonJetPair->getLepton()->cone_pt()) ){ trigger_fired_mu = true;}  // to ensure bool stays true once turned on  
      // std::cout<< "trigger_fired_e " << trigger_fired_e << " trigger_fired_mu " << trigger_fired_mu << std::endl;

    }

    if(!trigger_fired_e && !trigger_fired_mu)
    {
      // std::cout<< "Event dropped "<< std::endl;
      continue; // Drop the event if it fires no trigger
    }
    //------------------------------


    int numEtaBins_e = EtaBins_e.size() - 1;
    int numPtBins_e  = PtBins_e.size() - 1;
    int numEtaBins_mu = EtaBins_mu.size() - 1;
    int numPtBins_mu  = PtBins_mu.size() - 1;

    for (std::vector<LeptonJetPairMaker>::const_iterator LeptonJetPair = LeptonJetPairs.begin();
         LeptonJetPair != LeptonJetPairs.end(); LeptonJetPair++)
    {
        if(LeptonJetPair->getDeltaR() <= 0.7)
        { 
	  continue; // deltaR() cond.
	}	   
          
        // @@@@@@@@@@@  LOOP OVER ELECTRON PT AND ETA BINS @@@@@@@@@@             
        if(trigger_fired_e && LeptonJetPair->getLepton()->is_electron() && LeptonJetPair->getLepton()->cone_pt() > 30. && LeptonJetPair->getJet()->pt() > 30.)
        {
          for(int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e ) { // ELECTRON ETA LOOP                          
                   double minAbsEta_e = std::abs(EtaBins_e[idxEtaBin_e]);
                   double maxAbsEta_e = std::abs(EtaBins_e[idxEtaBin_e + 1]);
            for(int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e ) { // ELECTRON PT LOOP                          
	             double minPt_e = PtBins_e[idxPtBin_e];
	             double maxPt_e = PtBins_e[idxPtBin_e + 1];
	             // std::cout<< "Eta bins electron " << minAbsEta_e << " - " << maxAbsEta_e << std::endl;
	             // std::cout<< "Pt bins electron " << minPt_e << " - " << maxPt_e << std::endl;
                     std::string etaBin_e = getEtaBin(minAbsEta_e, maxAbsEta_e);
	             std::string PtBin_e = getPtBin(minPt_e, maxPt_e);
	             // std::cout << "etaBin_e " << etaBin_e << " PtBin_e " << PtBin_e << std::endl;
            } // ELECTRON PT LOOP ENDS                          
          }   // ELECTRON ETA LOOP ENDS                         
	}   // ELECTRON SECTION ENDS
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


        // @@@@@@@@@@@  LOOP OVER MUON PT AND ETA BINS @@@@@@@@@@
        if(trigger_fired_mu && LeptonJetPair->getLepton()->is_muon() && ((LeptonJetPair->getLepton()->cone_pt() > 30. && LeptonJetPair->getJet()->pt()> 30.) || 
           (LeptonJetPair->getLepton()->cone_pt() > 10. && LeptonJetPair->getJet()->pt()> 40.) ) )
        {
          for(int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu ) { // MUON ETA LOOP                          
                   double minAbsEta_mu = std::abs(EtaBins_mu[idxEtaBin_mu]);
                   double maxAbsEta_mu = std::abs(EtaBins_mu[idxEtaBin_mu + 1]);
            for(int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu ) { // MUON PT LOOP                          
	             double minPt_mu = PtBins_mu[idxPtBin_mu];
	             double maxPt_mu = PtBins_mu[idxPtBin_mu + 1];
	             // std::cout<< "Eta bins muon " << minAbsEta_mu << " - " << maxAbsEta_mu << std::endl;
	             // std::cout<< "Pt bins muon " << minPt_mu << " - " << maxPt_mu << std::endl;
                     std::string etaBin_mu = getEtaBin(minAbsEta_mu, maxAbsEta_mu);
	             std::string PtBin_mu = getPtBin(minPt_mu, maxPt_mu);
	             // std::cout << "etaBin_mu " << etaBin_mu << " PtBin_mu " << PtBin_mu << std::endl;
            } // MUON PT LOOP ENDS                          
          }   // MUON ETA LOOP ENDS                         
	}   // MUON SECTION ENDS
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    

    } // LOOP OVER LEPTON JET PAIRS END

     ++selectedEntries;
     selectedEntries_weighted += evtWeight;
     histogram_selectedEntries->Fill(0.);
 } // LOOP OVER THE CHAIN ENDS



/*
// ************************ DEF LINES BEGIN  ***********************************************

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, "nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  preselHadTauSelector.set_min_id_cut_dR05(-1000);
  preselHadTauSelector.set_max_raw_cut_dR05(1.e+6);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, "nJet", "Jet");
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, "met");
  metReader->setBranchAddresses(inputTree);

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
    Form("LeptonFakeRate_%s/electrons", chargeSelection_string.data()), central_or_shift));
  selElectronHistManager.bookHistograms(fs);

  MuonHistManager selMuonHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/muons", chargeSelection_string.data()), central_or_shift));
  selMuonHistManager.bookHistograms(fs);

  HadTauHistManager selHadTauHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/hadTaus", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genHadTau(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/hadTaus_genHadTau", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genHadTau.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genElectron(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/hadTaus_genElectron", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genElectron.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genMuon(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/hadTaus_genMuon", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genMuon.bookHistograms(fs);
  HadTauHistManager selHadTauHistManager_genJet(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/hadTaus_genJet", chargeSelection_string.data()), central_or_shift));
  selHadTauHistManager_genJet.bookHistograms(fs);

  JetHistManager selJetHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/jets", chargeSelection_string.data()), central_or_shift));
  selJetHistManager.bookHistograms(fs);
  JetHistManager selJetHistManager_lead(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/leadJet", chargeSelection_string.data()), central_or_shift, 0));
  selJetHistManager_lead.bookHistograms(fs);
  JetHistManager selJetHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/subleadJet", chargeSelection_string.data()), central_or_shift, 1));
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
    Form("LeptonFakeRate_%s/BJets_loose", chargeSelection_string.data()), central_or_shift));
  selBJet_looseHistManager.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_lead(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/leadBJet_loose", chargeSelection_string.data()), central_or_shift, 0));
  selBJet_looseHistManager_lead.bookHistograms(fs);
  JetHistManager selBJet_looseHistManager_sublead(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/subleadBJet_loose", chargeSelection_string.data()), central_or_shift, 1));
  selBJet_looseHistManager_sublead.bookHistograms(fs);
  JetHistManager selBJet_mediumHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/BJets_medium", chargeSelection_string.data()), central_or_shift));
  selBJet_mediumHistManager.bookHistograms(fs);

  MEtHistManager selMEtHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/met", chargeSelection_string.data()), central_or_shift));
  selMEtHistManager.bookHistograms(fs);

  EvtHistManager_jetToTauFakeRate selEvtHistManager(makeHistManager_cfg(process_string, 
    Form("LeptonFakeRate_%s/evt", chargeSelection_string.data()), central_or_shift));
  selEvtHistManager.bookHistograms(fs);

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/unbiased/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/sel/genEvt", chargeSelection_string.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("LeptonFakeRate_%s/sel/lheInfo", chargeSelection_string.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);
    
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
	int abs_pdgId = std::abs(genLepton->pdgId());
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
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
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
      if      ( (*hadTau)->genHadTau()                                                    ) preselHadTaus_genHadTau.push_back(*hadTau);   // generator level match to hadronic tau decay 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 11 ) preselHadTaus_genElectron.push_back(*hadTau); // generator level match to electron 
      else if ( (*hadTau)->genLepton() && std::abs((*hadTau)->genLepton()->pdgId()) == 13 ) preselHadTaus_genMuon.push_back(*hadTau);     // generator level match to muon
      else                                                                                  preselHadTaus_genJet.push_back(*hadTau);      // generator level match to jet (or pileup)
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
    	int abs_pdgId = std::abs(genLepton->pdgId());
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
    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons);
    // require two leptons passing loose preselection criteria 
    if ( !(preselLeptons.size() >= 2) ) {
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    int preselLepton_lead_type = getLeptonType(preselLepton_lead->pdgId());
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    int preselLepton_sublead_type = getLeptonType(preselLepton_sublead->pdgId());

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 2 &&                             selTrigger_1e                                       ) ||
	   (preselElectrons.size() >= 1 && preselMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                               preselMuons.size() >= 2 &&  selTrigger_1mu                                      )) ) {
      continue;
    } 
    cutFlowTable.update("presel lepton trigger match");
    
//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= sgn(genWeight);
      evtWeight *= pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {	
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	evtWeight *= (*jet)->BtagWeight();
      }
    }

    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        preselLepton_lead_type, preselLepton_lead->pt(), preselLepton_lead->eta(), 
	preselLepton_sublead_type, preselLepton_sublead->pt(), preselLepton_sublead->eta());

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
    std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons);
    // require exactly two leptons passing tight selection criteria to avoid overlap with 3l category
    if ( !(selLeptons.size() == 2) ) {
      continue;
    }
    cutFlowTable.update("2 sel leptons", evtWeight);
    const RecoLepton* selLepton_lead = selLeptons[0];
    const RecoLepton* selLepton_sublead = selLeptons[1];

    const RecoLepton* selLepton_e = 0;
    const RecoLepton* selLepton_mu = 0;
    if      ( selLepton_lead->is_electron()    ) selLepton_e  = selLepton_lead;
    else if ( selLepton_lead->is_muon()        ) selLepton_mu = selLepton_lead;
    if      ( selLepton_sublead->is_electron() ) selLepton_e  = selLepton_sublead;
    else if ( selLepton_sublead->is_muon()     ) selLepton_mu = selLepton_sublead;
    if ( !(selLepton_e && selLepton_mu) ) {
      continue;
    }
    cutFlowTable.update("1 sel electron + 1 sel muon", evtWeight);

    double mLL = (selLepton_lead->p4() + selLepton_sublead->p4()).mass();
    double mT_e = ( selLepton_e ) ? comp_MT_met_lep1(*selLepton_e, met.pt(), met.phi()) : -1.;
    double mT_mu = ( selLepton_e ) ? comp_MT_met_lep1(*selLepton_mu, met.pt(), met.phi()) : -1.;

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((selElectrons.size() >= 2 &&                          selTrigger_1e                                       ) ||
	   (selElectrons.size() >= 1 && selMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                            selMuons.size() >= 2 &&  selTrigger_1mu                                      )) ) {
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
	if ( ((*lepton1)->p4() + (*lepton2)->p4()).mass() < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) {
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);

    double minPt_lead = -1.;
    if      ( era == kEra_2015 ) minPt_lead = 20.;
    else if ( era == kEra_2016 ) minPt_lead = 25.; // CV: increase minimum lepton pT cut to 25 GeV to keep-up with higher trigger thresholds in 2016 data
    else assert(0);
    double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt() > minPt_lead && selLepton_sublead->pt() > minPt_sublead) ) {
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool isCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
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
    selMEtHistManager.fillHistograms(met, mht_p4, met_LD, evtWeight);
    selEvtHistManager.fillHistograms(selElectrons.size(), selMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
      mLL, mT_e, mT_mu, 
      evtWeight);

//--- iterate over jets
    for ( std::vector<const RecoJet*>::const_iterator cleanedJet = cleanedJets.begin();
	  cleanedJet != cleanedJets.end(); ++cleanedJet ) {
      if ( !((*cleanedJet)->pt() > jet_minPt && std::fabs((*cleanedJet)->eta()) > jet_minAbsEta  &&
	     (*cleanedJet)->pt() < jet_maxPt && std::fabs((*cleanedJet)->eta()) < jet_maxAbsEta) ) continue;

      const RecoHadTau* preselHadTau_dRmatched = 0;
      double dRmin = 1.e+3;
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
	    preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
	double dR = deltaR((*preselHadTau)->eta(), (*preselHadTau)->phi(), (*cleanedJet)->eta(), (*cleanedJet)->phi());
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
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt(), preselHadTau_dRmatched->eta());
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
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_dRmatched_genPdgId, preselHadTau_dRmatched->pt(), preselHadTau_dRmatched->eta());
	evtWeight_numerator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();

	(*numerator)->fillHistograms(**cleanedJet, *preselHadTau_dRmatched, evtWeight_numerator);
      }
    }

    for ( std::vector<denominatorHistManagers*>::iterator denominator = denominators.begin();
	  denominator != denominators.end(); ++denominator ) {
      int numHadTaus_denominator = 0;
      double evtWeight_denominator = evtWeight;
      dataToMCcorrectionInterface->setHadTauSelection((*denominator)->fakeableHadTauSelector_->get());
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
	    preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
	if ( (*(*denominator)->fakeableHadTauSelector_)(**preselHadTau) ) ++numHadTaus_denominator;
	int preselHadTau_genPdgId = getHadTau_genPdgId(*preselHadTau);
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_genPdgId, (*preselHadTau)->pt(), (*preselHadTau)->eta());
	evtWeight_denominator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      }
      (*denominator)->evtHistManager_->fillHistograms(selElectrons.size(), selMuons.size(), numHadTaus_denominator,
	selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
	mLL, mT_e, mT_mu, 					      
	evtWeight_denominator);
    }
    
    for ( std::vector<numeratorSelector_and_HistManagers*>::iterator numerator = numerators.begin();
	  numerator != numerators.end(); ++numerator ) {
      int numHadTaus_numerator = 0;
      double evtWeight_numerator = evtWeight;
      dataToMCcorrectionInterface->setHadTauSelection((*numerator)->hadTauSelection_);
      for ( std::vector<const RecoHadTau*>::const_iterator preselHadTau = preselHadTaus.begin();
	    preselHadTau != preselHadTaus.end(); ++preselHadTau ) {
	if ( (*(*numerator)->tightHadTauSelector_)(**preselHadTau) ) ++numHadTaus_numerator;
	int preselHadTau_genPdgId = getHadTau_genPdgId(*preselHadTau);
	dataToMCcorrectionInterface->setHadTaus(preselHadTau_genPdgId, (*preselHadTau)->pt(), (*preselHadTau)->eta());
	evtWeight_numerator *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      }
      (*numerator)->evtHistManager_->fillHistograms(selElectrons.size(), selMuons.size(), numHadTaus_numerator,
	selJets.size(), selBJets_loose.size(), selBJets_medium.size(), 
	mLL, mT_e, mT_mu, 
	evtWeight);
    }

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

// ************************ DEF LINES END ***********************************************
*/

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

  // std::cout << "cut-flow table" << std::endl;
  // cutFlowTable.print(std::cout);
  // std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  // delete muonReader;
  // delete electronReader;
  // delete hadTauReader;
  // delete jetReader;
  // delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;

  hltPaths_delete(triggers_e);
  hltPaths_delete(triggers_mu);

  // hltPaths_delete(triggers_1e1mu);

  clock.Show("analyze_LeptonFakeRate");

  return EXIT_SUCCESS;
}

