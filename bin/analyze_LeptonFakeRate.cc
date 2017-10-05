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
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonFakeRate.h" // EvtHistManager_LeptonFakeRate  // NEW FILE ADDED
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager    
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int    
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int    
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


// ------ MY FUNCTIONS-------- 
double Mt(const RecoLepton& lepton, double met_pt, double met_phi){
  double mt = TMath::Sqrt( 2 * lepton.pt() * met_pt * (1 - TMath::Cos(lepton.phi() - met_phi)) );
  return mt;
}

double Mt_fix(const RecoLepton& lepton, double pt_fix, double met_pt, double met_phi){
  double mt = TMath::Sqrt( 2 * pt_fix * met_pt * (1 - TMath::Cos(lepton.phi() - met_phi)) );
  return mt;
}


// --------- MY NEW CLASSES AND STRUCTS -------------
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


class hltPath_LeptonFakeRate : public hltPath
{
 public:
  hltPath_LeptonFakeRate(const std::string& branchName, double minPt = -1., double maxPt = -1., double min_JetPt = -1., double prescale = 1.)
    : hltPath(branchName, minPt, maxPt) 
    , branchName_(branchName)
    , value_(-1)
    , minPt_(minPt)
    , maxPt_(maxPt)
    , minJetPt_(min_JetPt)
    , prescale_(prescale)
    {}
    ~hltPath_LeptonFakeRate() {}    

  double getMinJetPt() const
  {
    return minJetPt_;  
  }

  double getPrescale() const
  {
    return prescale_;  
  }

  private:
  std::string branchName_;
  Int_t value_;
  double minPt_;
  double maxPt_;
  double minJetPt_;
  double prescale_;
};

// ----- overriding functions written inside "../src/hltPath.cc" ----
void hltPaths_LeptonFakeRate_setBranchAddresses(TTree* tree, const std::vector<hltPath_LeptonFakeRate*>& hltPaths)
{
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths.begin();
        hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    (*hltPath_iter)->setBranchAddress(tree);
  }
}



std::vector<hltPath_LeptonFakeRate*> create_hltPaths_LeptonFakeRate(const std::vector<std::string>& branchNames, double minPt, double maxPt, double jet_MinPt, double prescale)
{
  std::vector<hltPath_LeptonFakeRate*> hltPaths_LeptonFakeRate;
  for ( std::vector<std::string>::const_iterator branchName = branchNames.begin();
        branchName != branchNames.end(); ++branchName ) {
        hltPaths_LeptonFakeRate.push_back(new hltPath_LeptonFakeRate(*branchName, minPt, maxPt, jet_MinPt, prescale));
  }
  return hltPaths_LeptonFakeRate;
}


bool hltPaths_LeptonFakeRate_isTriggered(const std::vector<hltPath_LeptonFakeRate*>& hltPaths_LeptonFakeRate, double lepton_cone_pt, double jet_pt){ 
  bool retVal = false;
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths_LeptonFakeRate.begin();
        hltPath_iter != hltPaths_LeptonFakeRate.end(); ++hltPath_iter ) {
        // std::cout<<" (*hltPath_iter)->getValue() "<< (*hltPath_iter)->getValue() << std::endl; 
    if ( lepton_cone_pt >= (*hltPath_iter)->getMinPt() && lepton_cone_pt < (*hltPath_iter)->getMaxPt() && 
         (*hltPath_iter)->getMinJetPt() > jet_pt && (*hltPath_iter)->getValue() >= 1 ) {
      retVal = true;
      break;
    }
  }
  return retVal;
}  

double hltPaths_LeptonFakeRate_getPrescale(const std::vector<hltPath_LeptonFakeRate*>& hltPaths_LeptonFakeRate, double lepton_cone_pt, double jet_pt){

  double prescale = 1.;
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths_LeptonFakeRate.begin();
        hltPath_iter != hltPaths_LeptonFakeRate.end(); ++hltPath_iter ) {
    // std::cout<<" (*hltPath_iter)->getValue() "<< (*hltPath_iter)->getValue() << std::endl;                                                                                                      
     if ( lepton_cone_pt >= (*hltPath_iter)->getMinPt() && lepton_cone_pt < (*hltPath_iter)->getMaxPt() &&
         (*hltPath_iter)->getMinJetPt() > jet_pt && (*hltPath_iter)->getValue() >= 1 ) {
          prescale = (*hltPath_iter)->getPrescale();
      break;
    }
  }
  return prescale;
}




bool hltPaths_isTriggered(const std::vector<hltPath_LeptonFakeRate*>& hltPaths_LeptonFakeRate)
{
  bool retVal = false;
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths_LeptonFakeRate.begin();
        hltPath_iter != hltPaths_LeptonFakeRate.end(); ++hltPath_iter ) {
    if ( (*hltPath_iter)->getValue() >= 1 ) {
      retVal = true;
      break;
    }
  }
  return retVal;
}



void hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate*>& hltPaths)
{
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths.begin();
        hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    delete (*hltPath_iter);
  }
}


// --------- Histogram Managers --------
struct numeratorHistManagers_muon_LFR_incl
{
 numeratorHistManagers_muon_LFR_incl(const std::string& process, bool isMC, const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      MuonHistManager_incl_(0),
      MuonHistManager_genHadTau_incl_(0),
      MuonHistManager_genLepton_incl_(0),
      MuonHistManager_genJet_incl_(0),
      MuonHistManager_notgenJet_incl_(0),
      EvtHistManager_LeptonFakeRate_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_incl_(0),
      MuonHistManager_aftercuts_incl_(0),
      MuonHistManager_genHadTau_aftercuts_incl_(0),
      MuonHistManager_genLepton_aftercuts_incl_(0),
      MuonHistManager_genJet_aftercuts_incl_(0),
      MuonHistManager_notgenJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_(0)
  {
    subdir2_ = Form("%s/incl", dir_path_.data()); // inclusive
  }

  ~numeratorHistManagers_muon_LFR_incl()
  {
    delete MuonHistManager_incl_;
    delete MuonHistManager_genHadTau_incl_;
    delete MuonHistManager_genLepton_incl_;
    delete MuonHistManager_genJet_incl_;
    delete MuonHistManager_notgenJet_incl_;
    delete EvtHistManager_LeptonFakeRate_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_incl_;
    delete MuonHistManager_aftercuts_incl_;
    delete MuonHistManager_genHadTau_aftercuts_incl_;
    delete MuonHistManager_genLepton_aftercuts_incl_;
    delete MuonHistManager_genJet_aftercuts_incl_;
    delete MuonHistManager_notgenJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                      
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                            
      // inclusive
      MuonHistManager_incl_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
      MuonHistManager_incl_->bookHistograms(dir);

      MuonHistManager_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      MuonHistManager_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_incl_->bookHistograms(dir);
      if(isMC_){
        // inclusive
	std::string process_and_genMatchedHadTau = process_ + "t";
        MuonHistManager_genHadTau_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genHadTau_incl_->bookHistograms(dir);

        MuonHistManager_genHadTau_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genHadTau_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        MuonHistManager_genLepton_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genLepton_incl_->bookHistograms(dir);

	MuonHistManager_genLepton_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genLepton_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        MuonHistManager_genJet_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genJet_incl_->bookHistograms(dir);

        MuonHistManager_genJet_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genJet_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        MuonHistManager_notgenJet_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_notgenJet_incl_->bookHistograms(dir);

        MuonHistManager_notgenJet_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_notgenJet_aftercuts_incl_->bookHistograms(dir);

        // inclusive
	EvtHistManager_LeptonFakeRate_genHadTau_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->bookHistograms(dir);


        EvtHistManager_LeptonFakeRate_genLepton_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->bookHistograms(dir);

      }
  }

  void fillHistograms(const RecoMuon& muon, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
   
   // if(isMC_){ evtWeight /= average_prescale_; } // implemant it in the class evthistmanager class
   // inclusive
      MuonHistManager_incl_->fillHistograms(muon, evtWeight);
      EvtHistManager_LeptonFakeRate_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }

       if( muon.genHadTau() || muon.genLepton() ){
          MuonHistManager_notgenJet_incl_->fillHistograms(muon, evtWeight);
          EvtHistManager_LeptonFakeRate_notgenJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
       }
      }

      if(mT_fix_L < 15.){
          MuonHistManager_aftercuts_incl_->fillHistograms(muon, evtWeight);
          EvtHistManager_LeptonFakeRate_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        if(isMC_){
          if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
            } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }
         if( muon.genHadTau() || muon.genLepton() ){
               MuonHistManager_notgenJet_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
         }
        }     
       }
  }
  std::string process_;
  bool isMC_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir2_; // inclusive
  MuonHistManager* MuonHistManager_incl_;
  MuonHistManager* MuonHistManager_genHadTau_incl_;
  MuonHistManager* MuonHistManager_genLepton_incl_;
  MuonHistManager* MuonHistManager_genJet_incl_;
  MuonHistManager* MuonHistManager_notgenJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_incl_;
  MuonHistManager* MuonHistManager_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genHadTau_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genLepton_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genJet_aftercuts_incl_;
  MuonHistManager* MuonHistManager_notgenJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
};


struct numeratorHistManagers_muon_LFR
{
 numeratorHistManagers_muon_LFR(const std::string& process, bool isMC, double minAbsEta, double maxAbsEta, double minPt, double maxPt, 
                                const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      minPt_(minPt),
      maxPt_(maxPt),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      MuonHistManager_(0),
      MuonHistManager_genHadTau_(0),
      MuonHistManager_genLepton_(0),
      MuonHistManager_genJet_(0),
      MuonHistManager_notgenJet_(0),
      EvtHistManager_LeptonFakeRate_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_(0),
      EvtHistManager_LeptonFakeRate_genLepton_(0),
      EvtHistManager_LeptonFakeRate_genJet_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_(0),
      MuonHistManager_aftercuts_(0),
      MuonHistManager_genHadTau_aftercuts_(0),
      MuonHistManager_genLepton_aftercuts_(0),
      MuonHistManager_genJet_aftercuts_(0),
      MuonHistManager_notgenJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    std::string PtBin = getPtBin(minPt_, maxPt_);
    subdir_ = Form("%s/%s/%s", dir_path_.data(), etaBin.data(), PtBin.data());
  }

  ~numeratorHistManagers_muon_LFR()
  {
    delete MuonHistManager_;
    delete MuonHistManager_genHadTau_;
    delete MuonHistManager_genLepton_;
    delete MuonHistManager_genJet_;
    delete MuonHistManager_notgenJet_;
    delete EvtHistManager_LeptonFakeRate_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_;
    delete EvtHistManager_LeptonFakeRate_genJet_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_;
    delete MuonHistManager_aftercuts_;
    delete MuonHistManager_genHadTau_aftercuts_;
    delete MuonHistManager_genLepton_aftercuts_;
    delete MuonHistManager_genJet_aftercuts_;
    delete MuonHistManager_notgenJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                      
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                            
   
      MuonHistManager_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      MuonHistManager_->bookHistograms(dir);

      MuonHistManager_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      MuonHistManager_aftercuts_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_->bookHistograms(dir);

      if(isMC_){
	std::string process_and_genMatchedHadTau = process_ + "t";
        MuonHistManager_genHadTau_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genHadTau_->bookHistograms(dir);

        MuonHistManager_genHadTau_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genHadTau_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        MuonHistManager_genLepton_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genLepton_->bookHistograms(dir);

        MuonHistManager_genLepton_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genLepton_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        MuonHistManager_genJet_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genJet_->bookHistograms(dir);

        MuonHistManager_genJet_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genJet_aftercuts_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        MuonHistManager_notgenJet_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_notgenJet_->bookHistograms(dir);

        MuonHistManager_notgenJet_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_notgenJet_aftercuts_->bookHistograms(dir);


        EvtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->bookHistograms(dir);

      }
  }
 
  void fillHistograms(const RecoMuon& muon, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
    // if(isMC_){ evtWeight /= average_prescale_; } // implemant it in the class evthistmanager class

    if(!(std::abs(muon.eta()) >= minAbsEta_ && std::abs(muon.eta()) < maxAbsEta_ && muon.pt() >= minPt_ && muon.pt() < maxPt_)) return;
       MuonHistManager_->fillHistograms(muon, evtWeight);
       EvtHistManager_LeptonFakeRate_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }

        if( muon.genHadTau() || muon.genLepton() ){
           MuonHistManager_notgenJet_->fillHistograms(muon, evtWeight);
           EvtHistManager_LeptonFakeRate_notgenJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }
      }

    if(mT_fix_L < 15.){
       MuonHistManager_aftercuts_->fillHistograms(muon, evtWeight);
       EvtHistManager_LeptonFakeRate_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
           } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
            }

        if( muon.genHadTau() || muon.genLepton() ){
               MuonHistManager_notgenJet_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }
      }     
    }
  }

  std::string process_;
  bool isMC_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir_;
  MuonHistManager* MuonHistManager_;
  MuonHistManager* MuonHistManager_genHadTau_;
  MuonHistManager* MuonHistManager_genLepton_;
  MuonHistManager* MuonHistManager_genJet_;
  MuonHistManager* MuonHistManager_notgenJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_;
  MuonHistManager* MuonHistManager_aftercuts_;
  MuonHistManager* MuonHistManager_genHadTau_aftercuts_;
  MuonHistManager* MuonHistManager_genLepton_aftercuts_;
  MuonHistManager* MuonHistManager_genJet_aftercuts_;
  MuonHistManager* MuonHistManager_notgenJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
};


struct denominatorHistManagers_muon_LFR_incl
{
  denominatorHistManagers_muon_LFR_incl(const std::string& process, bool isMC, const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      MuonHistManager_incl_(0),
      MuonHistManager_genHadTau_incl_(0),
      MuonHistManager_genLepton_incl_(0),
      MuonHistManager_genJet_incl_(0),
      MuonHistManager_notgenJet_incl_(0),
      EvtHistManager_LeptonFakeRate_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_incl_(0),
      MuonHistManager_aftercuts_incl_(0),
      MuonHistManager_genHadTau_aftercuts_incl_(0),
      MuonHistManager_genLepton_aftercuts_incl_(0),
      MuonHistManager_genJet_aftercuts_incl_(0),
      MuonHistManager_notgenJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_(0)
  {
    subdir2_ = Form("%s/incl", dir_path_.data()); // inclusive
  }

  ~denominatorHistManagers_muon_LFR_incl()
  {
    delete MuonHistManager_incl_;
    delete MuonHistManager_genHadTau_incl_;
    delete MuonHistManager_genLepton_incl_;
    delete MuonHistManager_genJet_incl_;
    delete MuonHistManager_notgenJet_incl_;
    delete EvtHistManager_LeptonFakeRate_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_incl_;
    delete MuonHistManager_aftercuts_incl_;
    delete MuonHistManager_genHadTau_aftercuts_incl_;
    delete MuonHistManager_genLepton_aftercuts_incl_;
    delete MuonHistManager_genJet_aftercuts_incl_;
    delete MuonHistManager_notgenJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                      
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                            
      // inclusive
      MuonHistManager_incl_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
      MuonHistManager_incl_->bookHistograms(dir);

      MuonHistManager_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      MuonHistManager_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_incl_->bookHistograms(dir);
      if(isMC_){
        // inclusive
	std::string process_and_genMatchedHadTau = process_ + "t";
        MuonHistManager_genHadTau_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genHadTau_incl_->bookHistograms(dir);

        MuonHistManager_genHadTau_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genHadTau_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        MuonHistManager_genLepton_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genLepton_incl_->bookHistograms(dir);

	MuonHistManager_genLepton_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genLepton_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        MuonHistManager_genJet_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_genJet_incl_->bookHistograms(dir);

        MuonHistManager_genJet_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_genJet_aftercuts_incl_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        MuonHistManager_notgenJet_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        MuonHistManager_notgenJet_incl_->bookHistograms(dir);

        MuonHistManager_notgenJet_aftercuts_incl_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
        MuonHistManager_notgenJet_aftercuts_incl_->bookHistograms(dir);

        // inclusive
	EvtHistManager_LeptonFakeRate_genHadTau_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->bookHistograms(dir);


        EvtHistManager_LeptonFakeRate_genLepton_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_incl_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->bookHistograms(dir);

      }
  }

  void fillHistograms(const RecoMuon& muon, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
   // inclusive
      MuonHistManager_incl_->fillHistograms(muon, evtWeight);
      EvtHistManager_LeptonFakeRate_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }

       if( muon.genHadTau() || muon.genLepton() ){
          MuonHistManager_notgenJet_incl_->fillHistograms(muon, evtWeight);
          EvtHistManager_LeptonFakeRate_notgenJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
       }
      }

      if(mT_fix_L < 15.){
          MuonHistManager_aftercuts_incl_->fillHistograms(muon, evtWeight);
          EvtHistManager_LeptonFakeRate_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        if(isMC_){
          if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
            } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }
         if( muon.genHadTau() || muon.genLepton() ){
               MuonHistManager_notgenJet_aftercuts_incl_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
         }
        }     
       }
  }
  std::string process_;
  bool isMC_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir2_; // inclusive
  MuonHistManager* MuonHistManager_incl_;
  MuonHistManager* MuonHistManager_genHadTau_incl_;
  MuonHistManager* MuonHistManager_genLepton_incl_;
  MuonHistManager* MuonHistManager_genJet_incl_;
  MuonHistManager* MuonHistManager_notgenJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_incl_;
  MuonHistManager* MuonHistManager_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genHadTau_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genLepton_aftercuts_incl_;
  MuonHistManager* MuonHistManager_genJet_aftercuts_incl_;
  MuonHistManager* MuonHistManager_notgenJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
};


struct denominatorHistManagers_muon_LFR
{
  denominatorHistManagers_muon_LFR(const std::string& process, bool isMC, double minAbsEta, double maxAbsEta, double minPt, double maxPt, 
                              const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      minPt_(minPt),
      maxPt_(maxPt),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      MuonHistManager_(0),
      MuonHistManager_genHadTau_(0),
      MuonHistManager_genLepton_(0),
      MuonHistManager_genJet_(0),
      MuonHistManager_notgenJet_(0),
      EvtHistManager_LeptonFakeRate_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_(0),
      EvtHistManager_LeptonFakeRate_genLepton_(0),
      EvtHistManager_LeptonFakeRate_genJet_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_(0),
      MuonHistManager_aftercuts_(0),
      MuonHistManager_genHadTau_aftercuts_(0),
      MuonHistManager_genLepton_aftercuts_(0),
      MuonHistManager_genJet_aftercuts_(0),
      MuonHistManager_notgenJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_(0)

  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    std::string PtBin = getPtBin(minPt_, maxPt_);
    subdir_ = Form("%s/%s/%s", dir_path_.data(), etaBin.data(), PtBin.data());
  }

  ~denominatorHistManagers_muon_LFR()
  {
    delete MuonHistManager_;
    delete MuonHistManager_genHadTau_;
    delete MuonHistManager_genLepton_;
    delete MuonHistManager_genJet_;
    delete MuonHistManager_notgenJet_;
    delete EvtHistManager_LeptonFakeRate_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_;
    delete EvtHistManager_LeptonFakeRate_genJet_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_;
    delete MuonHistManager_aftercuts_;
    delete MuonHistManager_genHadTau_aftercuts_;
    delete MuonHistManager_genLepton_aftercuts_;
    delete MuonHistManager_genJet_aftercuts_;
    delete MuonHistManager_notgenJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
  }


  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                      
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                            
   
      MuonHistManager_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      MuonHistManager_->bookHistograms(dir);

      MuonHistManager_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      MuonHistManager_aftercuts_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_->bookHistograms(dir);

      if(isMC_){
	std::string process_and_genMatchedHadTau = process_ + "t";
        MuonHistManager_genHadTau_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genHadTau_->bookHistograms(dir);

        MuonHistManager_genHadTau_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genHadTau_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        MuonHistManager_genLepton_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genLepton_->bookHistograms(dir);

        MuonHistManager_genLepton_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genLepton_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        MuonHistManager_genJet_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_genJet_->bookHistograms(dir);

        MuonHistManager_genJet_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_genJet_aftercuts_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        MuonHistManager_notgenJet_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        MuonHistManager_notgenJet_->bookHistograms(dir);

        MuonHistManager_notgenJet_aftercuts_ = new MuonHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        MuonHistManager_notgenJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->bookHistograms(dir);
      }
  }


  void fillHistograms(const RecoMuon& muon, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
    if ( !(std::abs(muon.eta()) >= minAbsEta_ && std::abs(muon.eta()) < maxAbsEta_ && muon.pt() >= minPt_ && muon.pt() < maxPt_) ) return;
      MuonHistManager_->fillHistograms(muon, evtWeight);
      EvtHistManager_LeptonFakeRate_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
    if(isMC_){
      if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }

      if( muon.genHadTau() || muon.genLepton() ){
	MuonHistManager_notgenJet_->fillHistograms(muon, evtWeight);
	EvtHistManager_LeptonFakeRate_notgenJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }

    if(mT_fix_L < 15.){
      MuonHistManager_aftercuts_->fillHistograms(muon, evtWeight);
      EvtHistManager_LeptonFakeRate_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( muon.genHadTau() ){ 
               MuonHistManager_genHadTau_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
           } else if( muon.genLepton()){ 
               MuonHistManager_genLepton_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               MuonHistManager_genJet_aftercuts_->fillHistograms(muon, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
            }
      }

      if( muon.genHadTau() || muon.genLepton() ){
	MuonHistManager_notgenJet_aftercuts_->fillHistograms(muon, evtWeight);
	EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }
  }

  std::string process_;
  bool isMC_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir_;
  MuonHistManager* MuonHistManager_;
  MuonHistManager* MuonHistManager_genHadTau_;
  MuonHistManager* MuonHistManager_genLepton_;
  MuonHistManager* MuonHistManager_genJet_;
  MuonHistManager* MuonHistManager_notgenJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_;
  MuonHistManager* MuonHistManager_aftercuts_;
  MuonHistManager* MuonHistManager_genHadTau_aftercuts_;
  MuonHistManager* MuonHistManager_genLepton_aftercuts_;
  MuonHistManager* MuonHistManager_genJet_aftercuts_;
  MuonHistManager* MuonHistManager_notgenJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
};


struct numeratorHistManagers_electron_LFR_incl
{
  numeratorHistManagers_electron_LFR_incl(const std::string& process, bool isMC, const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      ElectronHistManager_incl_(0),
      ElectronHistManager_genHadTau_incl_(0),
      ElectronHistManager_genLepton_incl_(0),
      ElectronHistManager_genJet_incl_(0),
      ElectronHistManager_notgenJet_incl_(0),
      EvtHistManager_LeptonFakeRate_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_incl_(0),
      ElectronHistManager_aftercuts_incl_(0),
      ElectronHistManager_genHadTau_aftercuts_incl_(0),
      ElectronHistManager_genLepton_aftercuts_incl_(0),
      ElectronHistManager_genJet_aftercuts_incl_(0),
      ElectronHistManager_notgenJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_(0)
  {
    subdir2_ = Form("%s/incl", dir_path_.data()); // inclusive                                                                                                                                          
  }

  ~numeratorHistManagers_electron_LFR_incl()
  {
    delete ElectronHistManager_incl_;
    delete ElectronHistManager_genHadTau_incl_;
    delete ElectronHistManager_genLepton_incl_;
    delete ElectronHistManager_genJet_incl_;
    delete ElectronHistManager_notgenJet_incl_;
    delete EvtHistManager_LeptonFakeRate_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_incl_;
    delete ElectronHistManager_aftercuts_incl_;
    delete ElectronHistManager_genHadTau_aftercuts_incl_;
    delete ElectronHistManager_genLepton_aftercuts_incl_;
    delete ElectronHistManager_genJet_aftercuts_incl_;
    delete ElectronHistManager_notgenJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                   
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                        
    // inclusive                                                                                                                                                                                        
    ElectronHistManager_incl_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
    ElectronHistManager_incl_->bookHistograms(dir);

    ElectronHistManager_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
    ElectronHistManager_aftercuts_incl_->bookHistograms(dir);

    EvtHistManager_LeptonFakeRate_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
    EvtHistManager_LeptonFakeRate_incl_->bookHistograms(dir);

    EvtHistManager_LeptonFakeRate_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
    EvtHistManager_LeptonFakeRate_aftercuts_incl_->bookHistograms(dir);
    if(isMC_){
      // inclusive                                                                                                                                                                                      
      std::string process_and_genMatchedHadTau = process_ + "t";
      ElectronHistManager_genHadTau_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genHadTau_incl_->bookHistograms(dir);

      ElectronHistManager_genHadTau_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genHadTau_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_genMatchedLepton = process_ + "l";
      ElectronHistManager_genLepton_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genLepton_incl_->bookHistograms(dir);

      ElectronHistManager_genLepton_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genLepton_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_genMatchedJet = process_ + "j";
      ElectronHistManager_genJet_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genJet_incl_->bookHistograms(dir);

      ElectronHistManager_genJet_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genJet_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
      ElectronHistManager_notgenJet_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_notgenJet_incl_->bookHistograms(dir);

      ElectronHistManager_notgenJet_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_notgenJet_aftercuts_incl_->bookHistograms(dir);

      // inclusive                                                                                                                                                                                      
      EvtHistManager_LeptonFakeRate_genHadTau_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genHadTau_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->bookHistograms(dir);


      EvtHistManager_LeptonFakeRate_genLepton_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genLepton_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genJet_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_notgenJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_notgenJet_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->bookHistograms(dir);

    }
  }

  void fillHistograms(const RecoElectron& electron, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
      // inclusive                                                                                                                                                                                      
      ElectronHistManager_incl_->fillHistograms(electron, evtWeight);
      EvtHistManager_LeptonFakeRate_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);

    if(isMC_){
      if(electron.genHadTau()){
         ElectronHistManager_genHadTau_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genHadTau_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }else if(electron.genLepton()){
         ElectronHistManager_genLepton_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genLepton_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }else{
	 ElectronHistManager_genJet_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }

      if( electron.genHadTau() || electron.genLepton() ){
	ElectronHistManager_notgenJet_incl_->fillHistograms(electron, evtWeight);
	EvtHistManager_LeptonFakeRate_notgenJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }
      
    if(mT_fix_L < 15.){
      ElectronHistManager_aftercuts_incl_->fillHistograms(electron, evtWeight);
      EvtHistManager_LeptonFakeRate_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
	if( electron.genHadTau() ){
	  ElectronHistManager_genHadTau_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	} else if( electron.genLepton()){
	  ElectronHistManager_genLepton_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}else{
	  ElectronHistManager_genJet_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}

	if( electron.genHadTau() || electron.genLepton() ){
	  ElectronHistManager_notgenJet_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}
      }
    }
  }

  std::string process_;
  bool isMC_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir2_; // inclusive                                                                                                                                                                    
  ElectronHistManager* ElectronHistManager_incl_;
  ElectronHistManager* ElectronHistManager_genHadTau_incl_;
  ElectronHistManager* ElectronHistManager_genLepton_incl_;
  ElectronHistManager* ElectronHistManager_genJet_incl_;
  ElectronHistManager* ElectronHistManager_notgenJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_incl_;
  ElectronHistManager* ElectronHistManager_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genHadTau_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genLepton_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genJet_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_notgenJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
};


struct numeratorHistManagers_electron_LFR
{
  numeratorHistManagers_electron_LFR(const std::string& process, bool isMC, double minAbsEta, double maxAbsEta, double minPt, double maxPt, 
                                     const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      minPt_(minPt),
      maxPt_(maxPt),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      ElectronHistManager_(0),
      ElectronHistManager_genHadTau_(0),
      ElectronHistManager_genLepton_(0),
      ElectronHistManager_genJet_(0),
      ElectronHistManager_notgenJet_(0),
      EvtHistManager_LeptonFakeRate_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_(0),
      EvtHistManager_LeptonFakeRate_genLepton_(0),
      EvtHistManager_LeptonFakeRate_genJet_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_(0),
      ElectronHistManager_aftercuts_(0),
      ElectronHistManager_genHadTau_aftercuts_(0),
      ElectronHistManager_genLepton_aftercuts_(0),
      ElectronHistManager_genJet_aftercuts_(0),
      ElectronHistManager_notgenJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    std::string PtBin = getPtBin(minPt_, maxPt_);
    // subdir_ = Form("LeptonFakeRate/denominator/%s/%s", etaBin.data(), PtBin.data());                                                                                                                 
    subdir_ = Form("%s/%s/%s", dir_path_.data(), etaBin.data(), PtBin.data());
  }

  ~numeratorHistManagers_electron_LFR()
  {
    delete ElectronHistManager_;
    delete ElectronHistManager_genHadTau_;
    delete ElectronHistManager_genLepton_;
    delete ElectronHistManager_genJet_;
    delete ElectronHistManager_notgenJet_;
    delete EvtHistManager_LeptonFakeRate_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_;
    delete EvtHistManager_LeptonFakeRate_genJet_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_;
    delete ElectronHistManager_aftercuts_;
    delete ElectronHistManager_genHadTau_aftercuts_;
    delete ElectronHistManager_genLepton_aftercuts_;
    delete ElectronHistManager_genJet_aftercuts_;
    delete ElectronHistManager_notgenJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    //std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                           
    //std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                               
      ElectronHistManager_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      ElectronHistManager_->bookHistograms(dir);

      ElectronHistManager_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      ElectronHistManager_aftercuts_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_= new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_= new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_->bookHistograms(dir);

      if(isMC_){
	std::string process_and_genMatchedHadTau = process_ + "t";
        ElectronHistManager_genHadTau_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genHadTau_->bookHistograms(dir);

        ElectronHistManager_genHadTau_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genHadTau_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        ElectronHistManager_genLepton_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genLepton_->bookHistograms(dir);

        ElectronHistManager_genLepton_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genLepton_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        ElectronHistManager_genJet_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genJet_->bookHistograms(dir);

        ElectronHistManager_genJet_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genJet_aftercuts_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        ElectronHistManager_notgenJet_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_notgenJet_->bookHistograms(dir);

        ElectronHistManager_notgenJet_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_notgenJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->bookHistograms(dir);
      }
  } 

  void fillHistograms(const RecoElectron& electron, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
    if ( !(std::abs(electron.eta()) >= minAbsEta_ && std::abs(electron.eta()) < maxAbsEta_ && electron.pt() >= minPt_ && electron.pt() < maxPt_) ) return;
    ElectronHistManager_->fillHistograms(electron, evtWeight);
    EvtHistManager_LeptonFakeRate_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
    if(isMC_){
      if( electron.genHadTau() ){ 
               ElectronHistManager_genHadTau_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( electron.genLepton()){ 
               ElectronHistManager_genLepton_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               ElectronHistManager_genJet_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }

      if( electron.genHadTau() || electron.genLepton() ){ 
          ElectronHistManager_notgenJet_->fillHistograms(electron, evtWeight);
          EvtHistManager_LeptonFakeRate_notgenJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }

    if(mT_fix_L < 15.){
         ElectronHistManager_aftercuts_->fillHistograms(electron, evtWeight);
         EvtHistManager_LeptonFakeRate_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( electron.genHadTau() ){ 
               ElectronHistManager_genHadTau_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( electron.genLepton()){ 
               ElectronHistManager_genLepton_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               ElectronHistManager_genJet_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }

      if( electron.genHadTau() || electron.genLepton() ){ 
         ElectronHistManager_genJet_aftercuts_->fillHistograms(electron, evtWeight);
         EvtHistManager_LeptonFakeRate_genJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
     }
    }
   }

  std::string process_;
  bool isMC_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir_;
  ElectronHistManager* ElectronHistManager_;
  ElectronHistManager* ElectronHistManager_genHadTau_;
  ElectronHistManager* ElectronHistManager_genLepton_;
  ElectronHistManager* ElectronHistManager_genJet_;
  ElectronHistManager* ElectronHistManager_notgenJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_;
  ElectronHistManager* ElectronHistManager_aftercuts_;
  ElectronHistManager* ElectronHistManager_genHadTau_aftercuts_;
  ElectronHistManager* ElectronHistManager_genLepton_aftercuts_;
  ElectronHistManager* ElectronHistManager_genJet_aftercuts_;
  ElectronHistManager* ElectronHistManager_notgenJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
};


struct denominatorHistManagers_electron_LFR_incl
{
  denominatorHistManagers_electron_LFR_incl(const std::string& process, bool isMC, const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      ElectronHistManager_incl_(0),
      ElectronHistManager_genHadTau_incl_(0),
      ElectronHistManager_genLepton_incl_(0),
      ElectronHistManager_genJet_incl_(0),
      ElectronHistManager_notgenJet_incl_(0),
      EvtHistManager_LeptonFakeRate_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_incl_(0),
      ElectronHistManager_aftercuts_incl_(0),
      ElectronHistManager_genHadTau_aftercuts_incl_(0),
      ElectronHistManager_genLepton_aftercuts_incl_(0),
      ElectronHistManager_genJet_aftercuts_incl_(0),
      ElectronHistManager_notgenJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_(0)
  {
    subdir2_ = Form("%s/incl", dir_path_.data()); // inclusive                                                                                                                                          
  }

  ~denominatorHistManagers_electron_LFR_incl()
  {
    delete ElectronHistManager_incl_;
    delete ElectronHistManager_genHadTau_incl_;
    delete ElectronHistManager_genLepton_incl_;
    delete ElectronHistManager_genJet_incl_;
    delete ElectronHistManager_notgenJet_incl_;
    delete EvtHistManager_LeptonFakeRate_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_incl_;
    delete ElectronHistManager_aftercuts_incl_;
    delete ElectronHistManager_genHadTau_aftercuts_incl_;
    delete ElectronHistManager_genLepton_aftercuts_incl_;
    delete ElectronHistManager_genJet_aftercuts_incl_;
    delete ElectronHistManager_notgenJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    // std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                   
    // std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                        
    // inclusive                                                                                                                                                                                        
    ElectronHistManager_incl_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
    ElectronHistManager_incl_->bookHistograms(dir);

    ElectronHistManager_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
    ElectronHistManager_aftercuts_incl_->bookHistograms(dir);

    EvtHistManager_LeptonFakeRate_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir2_.data()), central_or_shift_));
    EvtHistManager_LeptonFakeRate_incl_->bookHistograms(dir);

    EvtHistManager_LeptonFakeRate_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
    EvtHistManager_LeptonFakeRate_aftercuts_incl_->bookHistograms(dir);
    if(isMC_){
      // inclusive                                                                                                                                                                                      
      std::string process_and_genMatchedHadTau = process_ + "t";
      ElectronHistManager_genHadTau_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genHadTau_incl_->bookHistograms(dir);

      ElectronHistManager_genHadTau_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genHadTau_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_genMatchedLepton = process_ + "l";
      ElectronHistManager_genLepton_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genLepton_incl_->bookHistograms(dir);

      ElectronHistManager_genLepton_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genLepton_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_genMatchedJet = process_ + "j";
      ElectronHistManager_genJet_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genJet_incl_->bookHistograms(dir);

      ElectronHistManager_genJet_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_genJet_aftercuts_incl_->bookHistograms(dir);

      std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
      ElectronHistManager_notgenJet_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      ElectronHistManager_notgenJet_incl_->bookHistograms(dir);

      ElectronHistManager_notgenJet_aftercuts_incl_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir2_.data()), central_or_shift_));
      ElectronHistManager_notgenJet_aftercuts_incl_->bookHistograms(dir);

      // inclusive                                                                                                                                                                                      
      EvtHistManager_LeptonFakeRate_genHadTau_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genHadTau_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->bookHistograms(dir);


      EvtHistManager_LeptonFakeRate_genLepton_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genLepton_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_genJet_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_notgenJet_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir2_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_notgenJet_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir2_.data()),central_or_shift_));
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->bookHistograms(dir);

    }
  }

  void fillHistograms(const RecoElectron& electron, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
      // inclusive                                                                                                                                                                                      
      ElectronHistManager_incl_->fillHistograms(electron, evtWeight);
      EvtHistManager_LeptonFakeRate_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);

    if(isMC_){
      if(electron.genHadTau()){
         ElectronHistManager_genHadTau_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genHadTau_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }else if(electron.genLepton()){
         ElectronHistManager_genLepton_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genLepton_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }else{
	 ElectronHistManager_genJet_incl_->fillHistograms(electron, evtWeight);
	 EvtHistManager_LeptonFakeRate_genJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }

      if( electron.genHadTau() || electron.genLepton() ){
	ElectronHistManager_notgenJet_incl_->fillHistograms(electron, evtWeight);
	EvtHistManager_LeptonFakeRate_notgenJet_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }
      
    if(mT_fix_L < 15.){
      ElectronHistManager_aftercuts_incl_->fillHistograms(electron, evtWeight);
      EvtHistManager_LeptonFakeRate_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
	if( electron.genHadTau() ){
	  ElectronHistManager_genHadTau_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	} else if( electron.genLepton()){
	  ElectronHistManager_genLepton_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}else{
	  ElectronHistManager_genJet_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}

	if( electron.genHadTau() || electron.genLepton() ){
	  ElectronHistManager_notgenJet_aftercuts_incl_->fillHistograms(electron, evtWeight);
	  EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
	}
      }
    }
  }

  std::string process_;
  bool isMC_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir2_; // inclusive                                                                                                                                                                    
  ElectronHistManager* ElectronHistManager_incl_;
  ElectronHistManager* ElectronHistManager_genHadTau_incl_;
  ElectronHistManager* ElectronHistManager_genLepton_incl_;
  ElectronHistManager* ElectronHistManager_genJet_incl_;
  ElectronHistManager* ElectronHistManager_notgenJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_incl_;
  ElectronHistManager* ElectronHistManager_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genHadTau_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genLepton_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_genJet_aftercuts_incl_;
  ElectronHistManager* ElectronHistManager_notgenJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_incl_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_incl_;
};

struct denominatorHistManagers_electron_LFR
{
  denominatorHistManagers_electron_LFR(const std::string& process, bool isMC, double minAbsEta, double maxAbsEta, double minPt, double maxPt, 
                              const std::string& central_or_shift, const std::string& dir_path)
    : process_(process),
      isMC_(isMC),
      minAbsEta_(minAbsEta),
      maxAbsEta_(maxAbsEta),
      minPt_(minPt),
      maxPt_(maxPt),
      central_or_shift_(central_or_shift),
      dir_path_(dir_path),
      ElectronHistManager_(0),
      ElectronHistManager_genHadTau_(0),
      ElectronHistManager_genLepton_(0),
      ElectronHistManager_genJet_(0),
      ElectronHistManager_notgenJet_(0),
      EvtHistManager_LeptonFakeRate_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_(0),
      EvtHistManager_LeptonFakeRate_genLepton_(0),
      EvtHistManager_LeptonFakeRate_genJet_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_(0),
      ElectronHistManager_aftercuts_(0),
      ElectronHistManager_genHadTau_aftercuts_(0),
      ElectronHistManager_genLepton_aftercuts_(0),
      ElectronHistManager_genJet_aftercuts_(0),
      ElectronHistManager_notgenJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genLepton_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_genJet_aftercuts_(0),
      EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_(0)
  {
    std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    std::string PtBin = getPtBin(minPt_, maxPt_);
    // subdir_ = Form("LeptonFakeRate/denominator/%s/%s", etaBin.data(), PtBin.data());                                                                                                                 
    subdir_ = Form("%s/%s/%s", dir_path_.data(), etaBin.data(), PtBin.data());
  }

  ~denominatorHistManagers_electron_LFR()
  {
    delete ElectronHistManager_;
    delete ElectronHistManager_genHadTau_;
    delete ElectronHistManager_genLepton_;
    delete ElectronHistManager_genJet_;
    delete ElectronHistManager_notgenJet_;
    delete EvtHistManager_LeptonFakeRate_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_;
    delete EvtHistManager_LeptonFakeRate_genJet_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_;
    delete ElectronHistManager_aftercuts_;
    delete ElectronHistManager_genHadTau_aftercuts_;
    delete ElectronHistManager_genLepton_aftercuts_;
    delete ElectronHistManager_genJet_aftercuts_;
    delete ElectronHistManager_notgenJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;    
    delete EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
    delete EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
  }
 

  void bookHistograms(TFileDirectory& dir)
  {
    //std::cout << "<denominatorHistManagers::bookHistograms>:" << std::endl;                                                                                                                           
    //std::cout << " subdir = " << subdir_ << std::endl;                                                                                                                                               
      ElectronHistManager_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      ElectronHistManager_->bookHistograms(dir);

      ElectronHistManager_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      ElectronHistManager_aftercuts_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_= new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_->bookHistograms(dir);

      EvtHistManager_LeptonFakeRate_aftercuts_= new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
      EvtHistManager_LeptonFakeRate_aftercuts_->bookHistograms(dir);

      if(isMC_){
	std::string process_and_genMatchedHadTau = process_ + "t";
        ElectronHistManager_genHadTau_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genHadTau_->bookHistograms(dir);

        ElectronHistManager_genHadTau_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genHadTau_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedLepton = process_ + "l";
        ElectronHistManager_genLepton_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genLepton_->bookHistograms(dir);

        ElectronHistManager_genLepton_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genLepton_aftercuts_->bookHistograms(dir);

	std::string process_and_genMatchedJet = process_ + "j";
        ElectronHistManager_genJet_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_genJet_->bookHistograms(dir);

        ElectronHistManager_genJet_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_genJet_aftercuts_->bookHistograms(dir);

	std::string process_and_notgenMatchedJet = process_ + "l_plus_t";
        ElectronHistManager_notgenJet_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        ElectronHistManager_notgenJet_->bookHistograms(dir);

        ElectronHistManager_notgenJet_aftercuts_ = new ElectronHistManager(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        ElectronHistManager_notgenJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedHadTau,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedLepton, Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_genJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_genMatchedJet, Form("%s/aftercuts", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_genJet_aftercuts_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_->bookHistograms(dir);

        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_ = new EvtHistManager_LeptonFakeRate(makeHistManager_cfg(process_and_notgenMatchedJet,Form("%s/aftercuts",subdir_.data()),central_or_shift_));
        EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->bookHistograms(dir);
      }
  } 

  void fillHistograms(const RecoElectron& electron, double met, double mT_L, double mT_fix_L, double evtWeight)
  {
    if ( !(std::abs(electron.eta()) >= minAbsEta_ && std::abs(electron.eta()) < maxAbsEta_ && electron.pt() >= minPt_ && electron.pt() < maxPt_) ) return;
    ElectronHistManager_->fillHistograms(electron, evtWeight);
    EvtHistManager_LeptonFakeRate_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
    if(isMC_){
      if( electron.genHadTau() ){ 
               ElectronHistManager_genHadTau_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( electron.genLepton()){ 
               ElectronHistManager_genLepton_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               ElectronHistManager_genJet_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
      if( electron.genHadTau() || electron.genLepton() ){ 
               ElectronHistManager_notgenJet_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_notgenJet_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      }
    }

    if(mT_fix_L < 15.){
         ElectronHistManager_aftercuts_->fillHistograms(electron, evtWeight);
         EvtHistManager_LeptonFakeRate_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
      if(isMC_){
        if( electron.genHadTau() ){ 
               ElectronHistManager_genHadTau_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
          } else if( electron.genLepton()){ 
               ElectronHistManager_genLepton_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genLepton_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
             }else{
               ElectronHistManager_genJet_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_genJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }
        if( electron.genHadTau() || electron.genLepton() ){ 
               ElectronHistManager_notgenJet_aftercuts_->fillHistograms(electron, evtWeight);
               EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_->fillHistograms(met, mT_L, mT_fix_L, evtWeight);
        }
      }
    }
  }
  std::string process_;
  bool isMC_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string central_or_shift_;
  std::string dir_path_;
  std::string subdir_;
  ElectronHistManager* ElectronHistManager_;
  ElectronHistManager* ElectronHistManager_genHadTau_;
  ElectronHistManager* ElectronHistManager_genLepton_;
  ElectronHistManager* ElectronHistManager_genJet_;
  ElectronHistManager* ElectronHistManager_notgenJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_;
  ElectronHistManager* ElectronHistManager_aftercuts_;
  ElectronHistManager* ElectronHistManager_genHadTau_aftercuts_;
  ElectronHistManager* ElectronHistManager_genLepton_aftercuts_;
  ElectronHistManager* ElectronHistManager_genJet_aftercuts_;
  ElectronHistManager* ElectronHistManager_notgenJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genHadTau_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genLepton_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_genJet_aftercuts_;
  EvtHistManager_LeptonFakeRate* EvtHistManager_LeptonFakeRate_notgenJet_aftercuts_;
};



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

  edm::VParameterSet trigger_e_PSet = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e");
  std::vector<hltPath_LeptonFakeRate*> triggers_e;
  // std::vector<hltPath*>::iterator it1;
  for(edm::VParameterSet::const_iterator trigger_PSet = trigger_e_PSet.begin(); trigger_PSet != trigger_e_PSet.end(); trigger_PSet++){
    vstring trigger_paths_e = trigger_PSet->getParameter<vstring>("path");     // READ FROM THE VPSET                                                                                              
    double minPt_e   = trigger_PSet->getParameter<double>("cone_minPt");       // READ FROM THE VPSET                                                                                           
    double maxPt_e   = trigger_PSet->getParameter<double>("cone_maxPt");       // READ FROM THE VPSET                                                                               
    double jet_minPt = trigger_PSet->getParameter<double>("jet_minPt");        // READ FROM THE VPSET                                                                               
    double prescale  = trigger_PSet->getParameter<double>("average_prescale"); // READ FROM THE VPSET                                                                               
    std::vector<hltPath_LeptonFakeRate*> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths_e, minPt_e, maxPt_e, jet_minPt, prescale);
    // it1 = triggers_e.begin();
    triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end()); // TO CHANGE THE ORDER OF INSERTION USE triggers_e.begin()
  }
  
  edm::VParameterSet trigger_mu_PSet = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu");
  std::vector<hltPath_LeptonFakeRate*> triggers_mu;
  // std::vector<hltPath*>::iterator it2;
  for(edm::VParameterSet::const_iterator trigger_PSet = trigger_mu_PSet.begin(); trigger_PSet != trigger_mu_PSet.end(); trigger_PSet++){
    vstring trigger_paths_mu = trigger_PSet->getParameter<vstring>("path");    // READ FROM THE VPSET                                                                                               
    double minPt_mu = trigger_PSet->getParameter<double>("cone_minPt");        // READ FROM THE VPSET                                                                                              
    double maxPt_mu = trigger_PSet->getParameter<double>("cone_maxPt");        // READ FROM THE VPSET
    double jet_minPt = trigger_PSet->getParameter<double>("jet_minPt");        // READ FROM THE VPSET                                                                                        
    double prescale  = trigger_PSet->getParameter<double>("average_prescale"); // READ FROM THE VPSET                                                                               
    std::vector<hltPath_LeptonFakeRate*> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths_mu, minPt_mu, maxPt_mu, jet_minPt, prescale);
    // it2 = triggers_mu.begin();
    triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end()); // TO CHANGE THE ORDER OF INSERTION USE triggers_mu.begin()
  }
  
  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");


  /*
  enum { kOS, kSS };
  std::string chargeSelection_string = cfg_analyze.getParameter<std::string>("chargeSelection");
  int chargeSelection = -1;
  if      ( chargeSelection_string == "OS" ) chargeSelection = kOS;
  else if ( chargeSelection_string == "SS" ) chargeSelection = kSS;
  else throw cms::Exception("analyze_LeptonFakeRate") 
    << "Invalid Configuration parameter 'chargeSelection' = " << chargeSelection_string << " !!\n";
  */

  vdouble EtaBins_e = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  vdouble PtBins_e = cfg_analyze.getParameter<vdouble>("absPtBins_e"); 
  vdouble EtaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  vdouble PtBins_mu = cfg_analyze.getParameter<vdouble>("absPtBins_mu");

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 


  bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");


  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }

  
  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;

  
  int lheScale_option = kLHE_scale_central;
  TString central_or_shift_tstring = central_or_shift.data();

  std::string met_branch = "met";
  if ( isMC && central_or_shift != "central" ) {
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_LeptonFakeRate")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      if( shiftUp_or_Down == "Up"   ){ 
        jetPt_option = RecoJetReader::kJetPt_jecUp;
        met_branch += "_shifted_JetEnUp";
      } else if( shiftUp_or_Down == "Down" ){ 
        jetPt_option = RecoJetReader::kJetPt_jecDown;
        met_branch += "_shifted_JetEnDown";
      }else assert(0);
    }else if(central_or_shift_tstring.BeginsWith("CMS_ttHl_JER")){
      if(central_or_shift_tstring.EndsWith("Up")) met_branch += "_shifted_JetResUp";
      else if(central_or_shift_tstring.EndsWith("Down")) met_branch += "_shifted_JetResDown";
    }else if(central_or_shift_tstring.BeginsWith("CMS_ttHl_UnclusteredEn")){
      if(central_or_shift_tstring.EndsWith("Up")) met_branch += "_shifted_UnclusteredEnUp";
      else if(central_or_shift_tstring.EndsWith("Down")) met_branch += "_shifted_UnclusteredEnDown";
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


  // ---- INPUT ROOT FILE -----------
  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();


  // ------ OUTPUT ROOT FILE ------
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


  hltPaths_LeptonFakeRate_setBranchAddresses(inputTree, triggers_e);
  hltPaths_LeptonFakeRate_setBranchAddresses(inputTree, triggers_mu);
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
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7); // CHRISTIAN'S SUGGESTION
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);


//--- declare missing transverse energy [implement the shape unc branches HERE !!! ]]
  RecoMEtReader* metReader = new RecoMEtReader(era, met_branch);
  metReader->setBranchAddresses(inputTree);



// ---------- GEN LEVEL INFO -----------------
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




// ------------ BOOK HISTOGRAMS ----------

// ------- inclusive Histograms -------
 numeratorHistManagers_muon_LFR_incl* numerator_mu_tight_incl = new numeratorHistManagers_muon_LFR_incl( process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/muons_tight");
 numerator_mu_tight_incl->bookHistograms(fs);

 denominatorHistManagers_muon_LFR_incl* denominator_mu_fakeable_incl = new denominatorHistManagers_muon_LFR_incl( process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable");
 denominator_mu_fakeable_incl->bookHistograms(fs);

 numeratorHistManagers_electron_LFR_incl* numerator_e_tight_incl = new numeratorHistManagers_electron_LFR_incl( process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/electrons_tight");
 numerator_e_tight_incl->bookHistograms(fs);

 denominatorHistManagers_electron_LFR_incl* denominator_e_fakeable_incl = new denominatorHistManagers_electron_LFR_incl( process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable");
 denominator_e_fakeable_incl->bookHistograms(fs);


// ------ Fake Leptons (Electron/Muon) in bins of pT and Eta  
  std::vector<denominatorHistManagers_electron_LFR*> electron_denominators_fakeable;
  std::vector<numeratorHistManagers_electron_LFR*> electron_numerators_tight;

  std::vector<denominatorHistManagers_muon_LFR*> muon_denominators_fakeable;
  std::vector<numeratorHistManagers_muon_LFR*> muon_numerators_tight;


  int numEtaBins_e  = EtaBins_e.size() - 1;
  int numPtBins_e   = PtBins_e.size() - 1;
  int numEtaBins_mu = EtaBins_mu.size() - 1;
  int numPtBins_mu  = PtBins_mu.size() - 1;

  for(int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e ) { // ELECTRON ETA LOOP                          
          double minAbsEta_e = std::abs(EtaBins_e[idxEtaBin_e]);
          double maxAbsEta_e = std::abs(EtaBins_e[idxEtaBin_e + 1]);
     for(int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e ) { // ELECTRON PT LOOP                          
             double minPt_e = PtBins_e[idxPtBin_e];
	     double maxPt_e = PtBins_e[idxPtBin_e + 1];
           
             // ------ Electron --------
             denominatorHistManagers_electron_LFR* denominator_e_fakeable = new denominatorHistManagers_electron_LFR( process_string, isMC, minAbsEta_e, maxAbsEta_e, minPt_e,
  		                    					            			     maxPt_e, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable");
             denominator_e_fakeable->bookHistograms(fs);
             electron_denominators_fakeable.push_back(denominator_e_fakeable);


             numeratorHistManagers_electron_LFR* numerator_e_tight = new numeratorHistManagers_electron_LFR( process_string, isMC, minAbsEta_e, maxAbsEta_e, minPt_e,
		                     								       maxPt_e, central_or_shift, "LeptonFakeRate/numerator/electrons_tight");
             numerator_e_tight->bookHistograms(fs);
             electron_numerators_tight.push_back(numerator_e_tight);

     }
  }


  for(int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu ) { // MUON ETA LOOP                          
          double minAbsEta_mu = std::abs(EtaBins_mu[idxEtaBin_mu]);
          double maxAbsEta_mu = std::abs(EtaBins_mu[idxEtaBin_mu + 1]);
     for(int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu ) { // MUON PT LOOP                          
             double minPt_mu = PtBins_mu[idxPtBin_mu];
	     double maxPt_mu = PtBins_mu[idxPtBin_mu + 1];


             // ------ Muon --------
             denominatorHistManagers_muon_LFR* denominator_mu_fakeable = new denominatorHistManagers_muon_LFR( process_string, isMC, minAbsEta_mu, maxAbsEta_mu, minPt_mu,
		                     								       maxPt_mu, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable");
             denominator_mu_fakeable->bookHistograms(fs);
             muon_denominators_fakeable.push_back(denominator_mu_fakeable);

             numeratorHistManagers_muon_LFR* numerator_mu_tight = new numeratorHistManagers_muon_LFR( process_string, isMC, minAbsEta_mu, maxAbsEta_mu, minPt_mu,
		                     								maxPt_mu, central_or_shift, "LeptonFakeRate/numerator/muons_tight");
             numerator_mu_tight->bookHistograms(fs);
             muon_numerators_tight.push_back(numerator_mu_tight);

     }
  }


  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if(isMC){
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
    //  Form("LeptonFakeRate_%s/unbiased/genEvt", chargeSelection_string.data()), central_or_shift));
    "LeptonFakeRate/gen_unbiased/genEvt", central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
    //  Form("LeptonFakeRate_%s/sel/genEvt", chargeSelection_string.data()), central_or_shift));
    "LeptonFakeRate/gen_sel/genEvt", central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
    //  Form("LeptonFakeRate_%s/sel/lheInfo", chargeSelection_string.data()), central_or_shift));
    "LeptonFakeRate/gen_sel/lheInfo", central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;

  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);                                                                                                 
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);                                                                                             
  cutFlowTableType cutFlowTable; // NOT USED AT THE MOMENT

  // Global Event level Histograms
  TH1F* histogram_MET = fs.make<TH1F>("MET", "MET", 40, 0., 200.);                                                                                                 
  TH1F* histogram_MET_PHI = fs.make<TH1F>("MET_phi", "MET_phi", 10, -TMath::Pi(), TMath::Pi());                                                                                                 

  

                                                                                                                                                                        
  
for( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) { // LOOP OVER EVENTS BEGIN
           if(idxEntry > 0 && (idxEntry % reportEvery) == 0){                                                                                                                                    
               std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;                                                                        
               }                                                                                                                                                                              
          
     ++analyzedEntries;                                                                                                                                                                              
     histogram_analyzedEntries->Fill(0.);                                                                                                                                                     
     inputTree->GetEntry(idxEntry);    



    RecoMEt met = metReader->read();


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
    

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);    // clean muons passing Loose object def.
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons); // clean muons passing Loose and Fakeable object def.s
    // std::vector<const RecoMuon*> selMuons = tightMuonSelector(preselMuons); // DEF LINE
    std::vector<const RecoMuon*> selMuons = tightMuonSelector(fakeableMuons);       // clean muons passing Loose, Fakeable and Tight object def.s

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);  // removing overlap b/w electrons and preselMuons
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);      // clean electrons passing Loose object def.
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);   // clean electrons passing Loose and Fakeable object def.s
    // std::vector<const RecoElectron*> selElectrons = tightElectronSelector(preselElectrons); // DEF LINE
    std::vector<const RecoElectron*> selElectrons = tightElectronSelector(fakeableElectrons);         // clean electrons passing Loose, Fakeable and Tight object def.s

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons); // removing overlap b/w hadTaus with preselMuons and preselElectrons
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
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, selMuons, selElectrons); // removing overlap b/w jets with preselMuons and preselElectrons
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


    // std::cout<< "chargeSelections " << chargeSelection  << std::endl;
    // std::cout<< "genElectrons.size() " << genElectrons.size() << " preselElectrons.size() " << preselElectrons.size() << " fakeableElectrons.size()  " << fakeableElectrons.size() << " selElectrons.size() "<< selElectrons.size() << std::endl; 
    // std::cout<< "genMuons.size() " << genMuons.size() << " preselMuons.size() " << preselMuons.size() << " fakeableMuons.size()  " << fakeableMuons.size() << " selMuons.size() "<< selMuons.size() << std::endl; 
    

    // -------- Making fakeLeptons collection --------
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);  
    std::vector<const RecoJet*> cleanedJets_dR07   = jetCleaner_dR07(jet_ptrs, fakeableLeptons); // removing overlap b/w jets with fakeableLeptons (within cone dR = 0.7)
    std::vector<const RecoJet*> cleanedJets_dR04   = jetCleaner(jet_ptrs, fakeableLeptons);      // removing overlap b/w jets with fakeableLeptons (within cone dR = 0.4) [TO BE USED FOR B-TAG]
    std::vector<const RecoJet*> selJets_dR07       = jetSelector(cleanedJets_dR07);    
    std::vector<const RecoJet*> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);

    // std::cout<< "fakeableLeptons.size() " << fakeableLeptons.size() << std::endl;
    // std::cout<< "selJets_dR07.size() " << selJets_dR07.size() << std::endl;
    if(fakeableLeptons.size() != 1){continue;} // vetoing events with > 1 fakeable lepton [NEEDED FOR REJECTION OF ttZ BACKGROUND]

    
    // ----- Making the fakeLepton Jet pairs --------
    std::vector<LeptonJetPairMaker> LeptonJetPairs;
    for(unsigned int i=0; i<fakeableLeptons.size();i++){ // LOOP OVE FAKEABLE LEPTONS BEGINS
       // if(fakeableLeptons[i]->isTight()){std::cout<< "This fakeLepton passes tight selections"<< std::endl;}
       for(unsigned int j=0; j<selJets_dR07.size();j++){ // LOOP OVER SEL-JETS_dR07 BEGINS
           LeptonJetPairMaker LeptonJetPair = LeptonJetPairMaker(fakeableLeptons[i], selJets_dR07[j]);
	   if(LeptonJetPair.getDeltaR() > 0.7){ LeptonJetPairs.push_back(LeptonJetPair);} // selecting lepton jet pairs seperated by deltaR > 0.7
       } // LOOP OVER SEL-JETS_dR07 ENDS


    } // LOOP OVE FAKEABLE LEPTONS BEGINS

    // ------- Sorting the pairs by deltaR() -------
    std::sort (LeptonJetPairs.begin(), LeptonJetPairs.end(), SortByDeltaR); 
    // std::cout<< "LeptonJetPairs.size() " << LeptonJetPairs.size() << std::endl;

    if(LeptonJetPairs.size() == 0){continue;} // demanding atleast one fakelepton-jet pair



    //--- compute MHT and linear MET discriminant (met_LD)
    // std::vector<const RecoLepton*> fakeableLeptons2 = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    // Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons2, selHadTaus, selJets);
    // double met_LD = compMEt_LD(met.p4(), mht_p4);

    // ----- Filling Gen level Histograms (before gen level cuts) ------
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
    double btagWeight = 1.;
    if ( isMC ) {                                                                                                                                                                                          // std::cout<< "evtWeight "<< evtWeight << std::endl; 
       evtWeight *= lumiScale;                                                                                                                                                         
       // std::cout<< "evtWeight * lumiscale "<< evtWeight << std::endl;                                                                                                                      
           if ( apply_genWeight ) evtWeight *= sgn(genWeight);
	   // std::cout<< "genWeight "<< genWeight << " sgn(genWeight) "<< sgn(genWeight) << std::endl;                               
           // std::cout<< "evtWeight * lumiscale * sgn(genweight) "<< evtWeight << std::endl;                                                                                 
                  evtWeight *= pileupWeight;                                                                                                                                                          
		  std::cout<< "evtWeight * lumiscale * sgn(genweight) * pileupWeight "<< evtWeight << std::endl;
		  
      if ( lheScale_option != kLHE_scale_central ) {                                                                                                                                                  
  	 if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();                                                                                          
    	 else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();                                                                                            
    	 else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();                                                                                          
    	 else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();                                                                                             
      }   

    // -------- APPLYING B-TAG WEIGHTS -------
    for (std::vector<LeptonJetPairMaker>::const_iterator LeptonJetPair = LeptonJetPairs.begin();
         LeptonJetPair != LeptonJetPairs.end(); LeptonJetPair++)
      {
	btagWeight *= (LeptonJetPair->getJet())->BtagWeight();
      }   
      evtWeight *= btagWeight;
    }
    // std::cout<< "evtWeight after applying LHEInfo weights "<< evtWeight << std::endl;

    
    std::cout<< "evtWeight after applying btag weights "<< evtWeight << std::endl;


    // ----- Filling Gen level Histograms (before gen level cuts) ------
    if(isMC){
       genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
       lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

  // ################## GLOBAL TRIGGER LOGIC (INSPIRED FROM analyze_1l_2tau.cc) #############
    //  bool isTriggered_1e = hltPaths_isTriggered(triggers_e) || (isMC && !apply_trigger_bits);   
    //  bool isTriggered_1mu = hltPaths_isTriggered(triggers_mu) || (isMC && !apply_trigger_bits); 

    bool isTriggered_1e = false;
    bool isTriggered_1mu = false;

    for (std::vector<LeptonJetPairMaker>::const_iterator LeptonJetPair = LeptonJetPairs.begin();
         LeptonJetPair != LeptonJetPairs.end(); LeptonJetPair++)
    {
      if( LeptonJetPair->getLepton()->is_electron() && use_triggers_1e && 
          (hltPaths_LeptonFakeRate_isTriggered(triggers_e, LeptonJetPair->getLepton()->cone_pt(), LeptonJetPair->getJet()->pt()) || (isMC && !apply_trigger_bits)) )  // apply_trigger_bits = true for both data and MC
      { 
	if(isMC) evtWeight *= 1./( hltPaths_LeptonFakeRate_getPrescale(triggers_e, LeptonJetPair->getLepton()->cone_pt(), LeptonJetPair->getJet()->pt()) );
          // std::cout<< "evtWeight after applying prescales "<< evtWeight << std::endl;
          isTriggered_1e = true;
      } // to ensure bool stays true once turned on 
 
      if( LeptonJetPair->getLepton()->is_muon() && use_triggers_1mu &&
          (hltPaths_LeptonFakeRate_isTriggered(triggers_mu, LeptonJetPair->getLepton()->cone_pt(), LeptonJetPair->getJet()->pt()) || (isMC && !apply_trigger_bits)) )
      { 
	if(isMC) evtWeight *= 1./( hltPaths_LeptonFakeRate_getPrescale(triggers_mu, LeptonJetPair->getLepton()->cone_pt(), LeptonJetPair->getJet()->pt()) );
          // std::cout<< "evtWeight after applying prescales "<< evtWeight << std::endl;
          isTriggered_1mu = true;
      }  // to ensure bool stays true once turned on  
    }



  bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
  bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
  if ( !(selTrigger_1e || selTrigger_1mu) ) {
    continue;
  }

  //--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;                                                                
  //    the ranking of the triggers is as follows: 1e1mu, 1mu, 1e                                                                                                                                 
  // CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets                                                                
  if ( !isMC ) {
    if ( selTrigger_1e && isTriggered_1mu) {
      continue;
    }
  }

  
  if((selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu) ||
     (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ){
       tightElectronSelector.disable_offline_e_trigger_cuts();
       fakeableElectronSelector.disable_offline_e_trigger_cuts();
  }else{
       tightElectronSelector.enable_offline_e_trigger_cuts();
       fakeableElectronSelector.enable_offline_e_trigger_cuts();
  }
  // ###########################################
  

// ---- Fill Global reco-level histograms ----
   histogram_MET->Fill(met.pt(), evtWeight);                                                                                                                                                     
   histogram_MET_PHI->Fill(met.phi(), evtWeight);                                                                                                                                                     




    for (std::vector<LeptonJetPairMaker>::const_iterator LeptonJetPair = LeptonJetPairs.begin();
         LeptonJetPair != LeptonJetPairs.end(); LeptonJetPair++)
    {
        if(LeptonJetPair->getDeltaR() <= 0.7)
        { 
	  continue; // deltaR() cond.
	}

	if( !((LeptonJetPair->getLepton())->isFakeable()) )
          {
            continue; // veto all lepton pairs where the lepton fails the fakeable selections
          }	   
          
	// std::cout<< "Mt_fix "<< Mt_fix(*(LeptonJetPair->getLepton()), 35., met.pt(), met.phi())<< std::endl;

	double mT_L     = Mt(*(LeptonJetPair->getLepton()), met.pt(), met.phi());
	double mT_fix_L = Mt_fix(*(LeptonJetPair->getLepton()), 35., met.pt(), met.phi());;

	/*
	if( (LeptonJetPair->getLepton())->genLepton()){
            std::cout<< " This is a Gen-Matched/prompt lepton"<< std::endl;
           } else {
            std::cout<< " This is a Non-prompt lepton"<< std::endl;
	}


	if((LeptonJetPair->getLepton())->isTight()){
            std::cout<< " This is a Tight lepton"<< std::endl;
	}else if((LeptonJetPair->getLepton())->isFakeable()){
            std::cout<< " This is a fakeble lepton"<< std::endl;
	}
	*/


	// -------- NEW LOGIC -----------
        // @@@@@@@@@@@  LOOP OVER ELECTRON PT AND ETA BINS @@@@@@@@@@ 
	if(LeptonJetPair->getLepton()->is_electron()){
          const RecoElectron* fake_electron = dynamic_cast<const RecoElectron*>(LeptonJetPair->getLepton());
	  // std::cout<< "electron H/E "<< fake_electron->HoE() << std::endl;
          if(LeptonJetPair->getLepton()->isTight()){ // Tight/Numerator
                   (numerator_e_tight_incl)->fillHistograms(*fake_electron, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms inclusive   
             for ( std::vector<numeratorHistManagers_electron_LFR*>::iterator numerator_e_tight = electron_numerators_tight.begin();
         	   numerator_e_tight != electron_numerators_tight.end(); numerator_e_tight++ ) {
	           (*numerator_e_tight)->fillHistograms(*fake_electron, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms
	     }

	  }else{ // Fakeable/Denominator
	           (denominator_e_fakeable_incl)->fillHistograms(*fake_electron, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms inclusive   
             for ( std::vector<denominatorHistManagers_electron_LFR*>::iterator denominator_e_fakeable = electron_denominators_fakeable.begin();
           	   denominator_e_fakeable != electron_denominators_fakeable.end(); denominator_e_fakeable++ ) {
	           (*denominator_e_fakeable)->fillHistograms(*fake_electron, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }

	  }
	}
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     


	// @@@@@@@@@@@  LOOP OVER MUON PT AND ETA BINS @@@@@@@@@@ 
	if(LeptonJetPair->getLepton()->is_muon()){

	  if(LeptonJetPair->getLepton()->cone_pt() < 30. && selBJets_loose_dR04.size() == 0 ){continue;}

           const RecoMuon* fake_muon = dynamic_cast<const RecoMuon*>(LeptonJetPair->getLepton());
	   // std::cout<< "muon relIso() " << fake_muon->relIso() << std::endl;
	  if(LeptonJetPair->getLepton()->isTight()){ // Tight/Numerator
         	 (numerator_mu_tight_incl)->fillHistograms(*fake_muon, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms inclusive   
             for(std::vector<numeratorHistManagers_muon_LFR*>::iterator numerator_mu_tight = muon_numerators_tight.begin();
	           numerator_mu_tight != muon_numerators_tight.end(); numerator_mu_tight++ ) { // MUON NUMERATOR (TIGHT)
	           (*numerator_mu_tight)->fillHistograms(*fake_muon, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms   
    	     }

	  } else { // Fakeable/Denominator
                 (denominator_mu_fakeable_incl)->fillHistograms(*fake_muon, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms inclusive   
             for(std::vector<denominatorHistManagers_muon_LFR*>::iterator denominator_mu_fakeable = muon_denominators_fakeable.begin();
	           denominator_mu_fakeable != muon_denominators_fakeable.end(); denominator_mu_fakeable++){ // MUON DENOMINATOR (FAKEABLE)
	           (*denominator_mu_fakeable)->fillHistograms(*fake_muon, met.pt(), mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }

	  }
	}
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     
	// ------------------------------


/*
        // @@@@@@@@@@@  LOOP OVER ELECTRON PT AND ETA BINS @@@@@@@@@@             
        if(LeptonJetPair->getLepton()->is_electron() && LeptonJetPair->getLepton()->cone_pt() > 30. && LeptonJetPair->getJet()->pt() > 30.)
        {
          const RecoElectron* fake_electron = dynamic_cast<const RecoElectron*>(LeptonJetPair->getLepton());
	  std::cout<< "electron H/E "<< fake_electron->HoE() << std::endl;

         if(LeptonJetPair->getLepton()->isTight()){ // ELECTRON NUMERATOR (TIGHT)
	   if( (LeptonJetPair->getLepton())->genLepton()){ // PROMPT ELECTRON
             for ( std::vector<numeratorHistManagers_electron_LFR*>::iterator numerator_e_prompt = electron_numerators_prompt.begin();
         	   numerator_e_prompt != electron_numerators_prompt.end(); numerator_e_prompt++ ) {
	           (*numerator_e_prompt)->fillHistograms(*fake_electron, mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms
	     }

	   } else { // FAKE ELECTRON

             for ( std::vector<numeratorHistManagers_electron_LFR*>::iterator numerator_e_fake = electron_numerators_fake.begin();
         	   numerator_e_fake != electron_numerators_fake.end(); numerator_e_fake++ ) {
	           (*numerator_e_fake)->fillHistograms(*fake_electron, mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms
	     }

	    }
	  }


          if(LeptonJetPair->getLepton()->isFakeable()){ // ELECTRON DENOMINATOR (FAKEABLE)
	   if( (LeptonJetPair->getLepton())->genLepton()){ // PROMPT ELECTRON
             for ( std::vector<denominatorHistManagers_electron_LFR*>::iterator denominator_e_prompt = electron_denominators_prompt.begin();
         	   denominator_e_prompt != electron_denominators_prompt.end(); denominator_e_prompt++ ) {
	           (*denominator_e_prompt)->fillHistograms(*fake_electron, mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }

	   } else { // FAKE ELECTRON

             for ( std::vector<denominatorHistManagers_electron_LFR*>::iterator denominator_e_fake = electron_denominators_fake.begin();
         	   denominator_e_fake != electron_denominators_fake.end(); denominator_e_fake++ ) {
	           (*denominator_e_fake)->fillHistograms(*fake_electron, mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }
	   }

	  }
        }   // ELECTRON SECTION ENDS
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


        // @@@@@@@@@@@  LOOP OVER MUON PT AND ETA BINS @@@@@@@@@@
        if(LeptonJetPair->getLepton()->is_muon() && ((LeptonJetPair->getLepton()->cone_pt() > 30. && LeptonJetPair->getJet()->pt()> 30.) || 
									 (LeptonJetPair->getLepton()->cone_pt() > 10. && LeptonJetPair->getJet()->pt()> 40.) ||
									 (LeptonJetPair->getLepton()->cone_pt() < 30. && selBJets_loose_dR04.size() >= 1)) )
         { // last selection for better agreement of ttbar and QCD fake rates (AN-2017-029_v5)
          const RecoMuon* fake_muon = dynamic_cast<const RecoMuon*>(LeptonJetPair->getLepton());
	  std::cout<< "muon relIso() " << fake_muon->relIso() << std::endl;

          if(LeptonJetPair->getLepton()->isTight()){
	   if( (LeptonJetPair->getLepton())->genLepton()){ // PROMPT MUON
             for ( std::vector<numeratorHistManagers_muon_LFR*>::iterator numerator_mu_prompt = muon_numerators_prompt.begin();
	           numerator_mu_prompt != muon_numerators_prompt.end(); numerator_mu_prompt++ ) { // MUON NUMERATOR (TIGHT)
	           (*numerator_mu_prompt)->fillHistograms(*fake_muon, mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms   
    	     }

	   } else { // FAKE MUON

             for ( std::vector<numeratorHistManagers_muon_LFR*>::iterator numerator_mu_fake = muon_numerators_fake.begin();
	           numerator_mu_fake != muon_numerators_fake.end(); numerator_mu_fake++ ) { // MUON NUMERATOR (TIGHT)
	           (*numerator_mu_fake)->fillHistograms(*fake_muon, mT_L, mT_fix_L, evtWeight);  //------ Numerator Histograms   
    	     }

	   }
	  }


          if(LeptonJetPair->getLepton()->isFakeable()){
           if( (LeptonJetPair->getLepton())->genLepton()){ // PROMPT MUON
             for ( std::vector<denominatorHistManagers_muon_LFR*>::iterator denominator_mu_prompt = muon_denominators_prompt.begin();
	           denominator_mu_prompt != muon_denominators_prompt.end(); denominator_mu_prompt++ ) { // MUON DENOMINATOR (FAKEABLE)
	           (*denominator_mu_prompt)->fillHistograms(*fake_muon, mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }


	   } else { // FAKE MUON

             for ( std::vector<denominatorHistManagers_muon_LFR*>::iterator denominator_mu_fake = muon_denominators_fake.begin();
	           denominator_mu_fake != muon_denominators_fake.end(); denominator_mu_fake++ ) { // MUON DENOMINATOR (FAKEABLE)
	           (*denominator_mu_fake)->fillHistograms(*fake_muon, mT_L, mT_fix_L, evtWeight);  //------ Denominator Histograms
      	     }

	   }
	  }
	    
      	}   // MUON SECTION ENDS
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    
*/



    } // LOOP OVER LEPTON JET PAIRS END

     ++selectedEntries;
     selectedEntries_weighted += evtWeight;
     histogram_selectedEntries->Fill(0.);
 } // LOOP OVER THE CHAIN ENDS

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;

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

  hltPaths_LeptonFakeRate_delete(triggers_e);
  hltPaths_LeptonFakeRate_delete(triggers_mu);

  clock.Show("analyze_LeptonFakeRate");

  return EXIT_SUCCESS;
}

