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

#include <TRandom3.h>

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
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverflow
#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h" // hltPath_LeptonFakeRate, create_hltPaths_LeptonFakeRate, hltPaths_LeptonFakeRate_setBranchAddresses, hltPaths_LeptonFakeRate_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

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

const std::string hadTauSelection = "dR03mvaTight";
//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

double comp_mT(const RecoLepton& lepton, double met_pt, double met_phi)
{
  double mt = TMath::Sqrt(2.*lepton.pt()*met_pt*(1. - TMath::Cos(lepton.phi() - met_phi)));
  return mt;
}

double comp_mT_fix(const RecoLepton& lepton, double met_pt, double met_phi)
{
  const double pt_fix = 35.;
  double mt = TMath::Sqrt(2.*pt_fix*met_pt*(1. - TMath::Cos(lepton.phi() - met_phi)));
  return mt;
}

//--- define histograms (same histogram manager class used for numerator and denominator)
struct numerator_and_denominatorHistManagers
{
  enum { kElectron, kMuon };

  numerator_and_denominatorHistManagers(const std::string& process, bool isMC, const std::string& central_or_shift, const std::string& dir,
					const std::string& lepton_type, double minAbsEta = -1., double maxAbsEta = -1., double minPt = -1., double maxPt = -1., 
					const std::string& subdir_suffix = "")
    : process_(process)
    , isMC_(isMC)
    , central_or_shift_(central_or_shift)
    , minAbsEta_(minAbsEta)
    , maxAbsEta_(maxAbsEta)
    , minPt_(minPt)
    , maxPt_(maxPt)
    , electronHistManager_(0)
    , electronHistManager_genHadTau_(0)
    , electronHistManager_genLepton_(0)
    , electronHistManager_genHadTauOrLepton_(0)
    , electronHistManager_genJet_(0)
    , muonHistManager_(0)
    , muonHistManager_genHadTau_(0)
    , muonHistManager_genLepton_(0)
    , muonHistManager_genHadTauOrLepton_(0)
    , muonHistManager_genJet_(0)
    , evtHistManager_LeptonFakeRate_(0)
    , evtHistManager_LeptonFakeRate_genHadTau_(0)
    , evtHistManager_LeptonFakeRate_genLepton_(0)
    , evtHistManager_LeptonFakeRate_genHadTauOrLepton_(0)
    , evtHistManager_LeptonFakeRate_genJet_(0)
  {
    if ( lepton_type == "electron" ) {
      lepton_type_ = kElectron;
    } else if ( lepton_type == "muon" ) {
      lepton_type_ = kMuon;
    } else {
      throw cms::Exception("numerator_and_denominatorHistManagers")
	<< "Invalid Configuration parameter 'lepton_type' = " << lepton_type_ << " !!\n";
    }
    isInclusive_ = (minAbsEta == maxAbsEta && minPt == maxPt);
    if ( isInclusive_ ) { // inclusive event selection
      subdir_ = Form("%s/incl", dir.data());
    } else {
      std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
      std::string PtBin = getPtBin(minPt_, maxPt_);
      subdir_ = Form("%s/%s/%s", dir.data(), etaBin.data(), PtBin.data());
    }
    if ( subdir_suffix != "" ) {
      subdir_ += Form("_%s", subdir_suffix.data());
    }
    if      ( lepton_type_ == kElectron ) label_ = " e";
    else if ( lepton_type_ == kMuon     ) label_ = " mu";
    else assert(0);
    if ( subdir_suffix != "" ) label_ += Form(" (%s)", subdir_suffix.data());
    label_ += ",";
    label_ += Form(" %1.0f < pT < %1.0f && %1.2f < |eta| < %1.2f", minPt, maxPt, minAbsEta, maxAbsEta);
  }

  ~numerator_and_denominatorHistManagers()
  {
    delete electronHistManager_;
    delete electronHistManager_genHadTau_;
    delete electronHistManager_genLepton_;
    delete electronHistManager_genHadTauOrLepton_;
    delete electronHistManager_genJet_;
    delete muonHistManager_;
    delete muonHistManager_genHadTau_;
    delete muonHistManager_genLepton_;
    delete muonHistManager_genHadTauOrLepton_;
    delete muonHistManager_genJet_;
    delete evtHistManager_LeptonFakeRate_;
    delete evtHistManager_LeptonFakeRate_genHadTau_;
    delete evtHistManager_LeptonFakeRate_genLepton_;
    delete evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
    delete evtHistManager_LeptonFakeRate_genJet_;
  }

  void bookHistograms(TFileDirectory& dir)
  {
    std::string process_and_genMatchedHadTau = process_ + "t";
    std::string process_and_genMatchedLepton = process_ + "l";
    std::string process_and_genMatchedHadTauOrLepton = process_ + "l_plus_t";
    std::string process_and_genMatchedJet = process_ + "j";

    if ( lepton_type_ == kElectron ) {
      electronHistManager_ = new ElectronHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      electronHistManager_->bookHistograms(dir);
      if ( isMC_ ) {
	electronHistManager_genHadTau_ = new ElectronHistManager(
          makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
	electronHistManager_genHadTau_->bookHistograms(dir);
	electronHistManager_genLepton_ = new ElectronHistManager(
          makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
	electronHistManager_genLepton_->bookHistograms(dir);
	electronHistManager_genHadTauOrLepton_ = new ElectronHistManager(
          makeHistManager_cfg(process_and_genMatchedHadTauOrLepton, Form("%s", subdir_.data()), central_or_shift_));
	electronHistManager_genHadTauOrLepton_->bookHistograms(dir);
	electronHistManager_genJet_ = new ElectronHistManager(
          makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
	electronHistManager_genJet_->bookHistograms(dir);
      }
    } else if ( lepton_type_ == kMuon ) {
      muonHistManager_ = new MuonHistManager(makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
      muonHistManager_->bookHistograms(dir);
      if ( isMC_ ) {
	muonHistManager_genHadTau_ = new MuonHistManager(
          makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
	muonHistManager_genHadTau_->bookHistograms(dir);
	muonHistManager_genLepton_ = new MuonHistManager(
          makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
	muonHistManager_genLepton_->bookHistograms(dir);
	muonHistManager_genHadTauOrLepton_ = new MuonHistManager(
          makeHistManager_cfg(process_and_genMatchedHadTauOrLepton, Form("%s", subdir_.data()), central_or_shift_));
	muonHistManager_genHadTauOrLepton_->bookHistograms(dir);
	muonHistManager_genJet_ = new MuonHistManager(
          makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
	muonHistManager_genJet_->bookHistograms(dir);
      }
    } else assert(0);

    evtHistManager_LeptonFakeRate_ = new EvtHistManager_LeptonFakeRate(
      makeHistManager_cfg(process_, Form("%s", subdir_.data()), central_or_shift_));
    evtHistManager_LeptonFakeRate_->bookHistograms(dir);
    if ( isMC_ ) {
      evtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(
        makeHistManager_cfg(process_and_genMatchedHadTau, Form("%s", subdir_.data()), central_or_shift_));
      evtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);
      evtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(
        makeHistManager_cfg(process_and_genMatchedLepton, Form("%s", subdir_.data()), central_or_shift_));
      evtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);
      evtHistManager_LeptonFakeRate_genHadTauOrLepton_ = new EvtHistManager_LeptonFakeRate(
        makeHistManager_cfg(process_and_genMatchedHadTauOrLepton, Form("%s", subdir_.data()), central_or_shift_));
      evtHistManager_LeptonFakeRate_genHadTauOrLepton_->bookHistograms(dir);
      evtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(
        makeHistManager_cfg(process_and_genMatchedJet, Form("%s", subdir_.data()), central_or_shift_));
      evtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);
    }
  }

  void fillHistograms(const RecoLepton& lepton, double met, double mT, double mT_fix, double evtWeight, cutFlowTableType* cutFlowTable = 0)
  {
    if ( isInclusive_ || (lepton.absEta() >= minAbsEta_ && lepton.absEta() < maxAbsEta_ && lepton.pt() >= minPt_ && lepton.pt() < maxPt_) ) {
      if ( lepton_type_ == kElectron ) {
	const RecoElectron* electron = dynamic_cast<const RecoElectron*>(&lepton);
	assert(electron);
	electronHistManager_->fillHistograms(*electron, evtWeight);
	if ( isMC_ ) {
	  if ( electron->genHadTau() ) electronHistManager_genHadTau_->fillHistograms(*electron, evtWeight);
	  if ( electron->genLepton() ) electronHistManager_genLepton_->fillHistograms(*electron, evtWeight);
	  if ( electron->genHadTau() || electron->genLepton() ) electronHistManager_genHadTauOrLepton_->fillHistograms(*electron, evtWeight);
	  else electronHistManager_genJet_->fillHistograms(*electron, evtWeight);
	}
      } else if ( lepton_type_ == kMuon ) {
	const RecoMuon* muon = dynamic_cast<const RecoMuon*>(&lepton);
	assert(muon);
	muonHistManager_->fillHistograms(*muon, evtWeight);
	if ( isMC_ ) {
          if ( muon->genHadTau() ) muonHistManager_genHadTau_->fillHistograms(*muon, evtWeight);
	  if ( muon->genLepton() ) muonHistManager_genLepton_->fillHistograms(*muon, evtWeight);
	  if ( muon->genHadTau() || muon->genLepton() ) muonHistManager_genHadTauOrLepton_->fillHistograms(*muon, evtWeight);
	  else muonHistManager_genJet_->fillHistograms(*muon, evtWeight);
	}
      } else assert(0);
      evtHistManager_LeptonFakeRate_->fillHistograms(met, mT, mT_fix, evtWeight);
      if ( isMC_ ) {
	if ( lepton.genHadTau() ) evtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT, mT_fix, evtWeight);
	if ( lepton.genLepton() ) evtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
	if ( lepton.genHadTau() || lepton.genLepton() ) evtHistManager_LeptonFakeRate_genHadTauOrLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
	else evtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT, mT_fix, evtWeight);
      }
      if ( cutFlowTable ) {
	cutFlowTable->update(label_, evtWeight);
      }
    }
  }
  std::string process_;
  bool isMC_;
  std::string central_or_shift_;
  int lepton_type_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  bool isInclusive_;
  std::string subdir_;
  std::string label_;
  ElectronHistManager* electronHistManager_;
  ElectronHistManager* electronHistManager_genHadTau_;
  ElectronHistManager* electronHistManager_genLepton_;
  ElectronHistManager* electronHistManager_genHadTauOrLepton_;
  ElectronHistManager* electronHistManager_genJet_;
  MuonHistManager* muonHistManager_;
  MuonHistManager* muonHistManager_genHadTau_;
  MuonHistManager* muonHistManager_genLepton_;
  MuonHistManager* muonHistManager_genHadTauOrLepton_;
  MuonHistManager* muonHistManager_genJet_;
  EvtHistManager_LeptonFakeRate* evtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate* evtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate* evtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate* evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
  EvtHistManager_LeptonFakeRate* evtHistManager_LeptonFakeRate_genJet_;
};

void fillHistograms(std::vector<numerator_and_denominatorHistManagers*>& histograms, 
		    const RecoLepton& lepton, double met_pt, double mT, double mT_fix, double evtWeight_LepJetPair, 
		    cutFlowTableType* cutFlowTable = 0)
{
  for ( std::vector<numerator_and_denominatorHistManagers*>::iterator histogram = histograms.begin();
	histogram != histograms.end(); ++histogram ) {
    (*histogram)->fillHistograms(lepton, met_pt, mT, mT_fix, evtWeight_LepJetPair, cutFlowTable);
  }
}

void initializeCutFlowTable(cutFlowTableType& cutFlowTable, const std::string& cut)
{
  cutFlowTable.update(cut, -1.); // do not increase event counts in cut-flow table, just register cut
}

void initializeCutFlowTable(cutFlowTableType& cutFlowTable, std::vector<numerator_and_denominatorHistManagers*>& histograms)
{
  for ( std::vector<numerator_and_denominatorHistManagers*>::iterator histogram = histograms.begin();
	histogram != histograms.end(); ++histogram ) {
    initializeCutFlowTable(cutFlowTable, (*histogram)->label_);
  }
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
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_LeptonFakeRate") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  bool use_triggers_2e  = cfg_analyze.getParameter<bool>("use_triggers_2e");
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  
  edm::VParameterSet cfg_triggers_e = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e");
  std::vector<hltPath_LeptonFakeRate*> triggers_e;
  for(edm::VParameterSet::const_iterator cfg_trigger = cfg_triggers_e.begin(); 
      cfg_trigger != cfg_triggers_e.end(); ++cfg_trigger ){
    vstring trigger_paths = cfg_trigger->getParameter<vstring>("path");     
    std::vector<hltPath_LeptonFakeRate*> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths, *cfg_trigger);
    triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end()); 
  }

  edm::VParameterSet cfg_triggers_mu = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu");
  std::vector<hltPath_LeptonFakeRate*> triggers_mu;
  for(edm::VParameterSet::const_iterator cfg_trigger = cfg_triggers_mu.begin(); 
      cfg_trigger != cfg_triggers_mu.end(); ++cfg_trigger ){
    vstring trigger_paths = cfg_trigger->getParameter<vstring>("path");     
    std::vector<hltPath_LeptonFakeRate*> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths, *cfg_trigger);
    triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end()); 
  }
    
  TRandom3 rand(12345);

  // bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");    // NOT NEEDED FROM NOW ON !
  // bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");  // NOT NEEDED FROM NOW ON !
  // bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); // NOT NEEDED FROM NOW ON

  vdouble etaBins_e = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  vdouble ptBins_e = cfg_analyze.getParameter<vdouble>("ptBins_e"); 
  vdouble etaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  vdouble ptBins_mu = cfg_analyze.getParameter<vdouble>("ptBins_mu");

  double minPt_e = cfg_analyze.getParameter<double>("minPt_e");   // NEWLY ADDED
  double minPt_mu = cfg_analyze.getParameter<double>("minPt_mu"); // NEWLY ADDED

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons1 = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  std::string branchName_genLeptons2 = cfg_analyze.getParameter<std::string>("branchName_genLeptons2");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  bool isDEBUG = ( cfg_analyze.exists("isDEBUG") ) ? cfg_analyze.getParameter<bool>("isDEBUG") : false;
 
  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }
  
  int jetPt_option = RecoJetReader::kJetPt_central;
  int met_option = RecoMEtReader::kMEt_central;
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
      if( shiftUp_or_Down == "Up"   ){ 
        jetPt_option = RecoJetReader::kJetPt_jecUp;
	met_option = RecoMEtReader::kMEt_shifted_JetEnUp;
      } else if( shiftUp_or_Down == "Down" ){ 
        jetPt_option = RecoJetReader::kJetPt_jecDown;
	met_option = RecoMEtReader::kMEt_shifted_JetEnDown;
      } else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JER") ) {
      if ( central_or_shift_tstring.EndsWith("Up") ) met_option = RecoMEtReader::kMEt_shifted_JetResUp;
      else if ( central_or_shift_tstring.EndsWith("Down") ) met_option = RecoMEtReader::kMEt_shifted_JetResDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_UnclusteredEn") ) {
      if ( central_or_shift_tstring.EndsWith("Up") ) met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnUp;
      else if ( central_or_shift_tstring.EndsWith("Down") ) met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnDown;
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
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  for ( const std::vector<hltPath_LeptonFakeRate*> hltPaths: { triggers_e, triggers_mu } ) {
    inputTree->registerReader(hltPaths);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons, readGenObjects);
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionCleaner muonCleaner(0.3); // cleaning muons from overlapping objects within cone radius 0.3 [NEW!]
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  fakeableElectronSelector.enable_offline_e_trigger_cuts();
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  tightElectronSelector.enable_offline_e_trigger_cuts();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree->registerReader(hadTauReader);
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
  tightHadTauSelector.set(hadTauSelection);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets, readGenObjects);
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner_dR04(0.4);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7); // CHRISTIAN'S SUGGESTION
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if ( !readGenObjects ) {
      if ( branchName_genLeptons1 != "" || branchName_genLeptons2 != "" ) {
        genLeptonReader = new GenLeptonReader(Form("n%s", branchName_genLeptons1.data()), branchName_genLeptons1, Form("n%s", branchName_genLeptons2.data()), branchName_genLeptons2);
        inputTree->registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(Form("n%s", branchName_genHadTaus.data()), branchName_genHadTaus);
        inputTree->registerReader(genHadTauReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(Form("n%s", branchName_genJets.data()), branchName_genJets);
        inputTree->registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader();
    inputTree->registerReader(lheInfoReader);
  }

//--- book histograms for numerator and denominator
  numerator_and_denominatorHistManagers* histograms_e_numerator_incl_beforeCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/electrons_tight",
    "electron", -1., -1., -1., -1., "");
  histograms_e_numerator_incl_beforeCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_e_denominator_incl_beforeCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable",
    "electron", -1., -1., -1., -1., "");
  histograms_e_denominator_incl_beforeCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_e_numerator_incl_afterCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/electrons_tight",
    "electron", -1., -1., -1., -1., "aftercuts");
  histograms_e_numerator_incl_afterCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_e_denominator_incl_afterCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable",
    "electron", -1., -1., -1., -1., "aftercuts");
  histograms_e_denominator_incl_afterCuts->bookHistograms(fs);
  std::vector<numerator_and_denominatorHistManagers*> histograms_e_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_e_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_e_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_e_denominator_binned_afterCuts;
  int numEtaBins_e = etaBins_e.size() - 1;
  int numPtBins_e = ptBins_e.size() - 1;
  for ( int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e ) { 
    double minAbsEta_e = std::abs(etaBins_e[idxEtaBin_e]);
    double maxAbsEta_e = std::abs(etaBins_e[idxEtaBin_e + 1]);
    for ( int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e ) {
      double minPt_e = ptBins_e[idxPtBin_e];
      double maxPt_e = ptBins_e[idxPtBin_e + 1];
      numerator_and_denominatorHistManagers* histograms_numerator_beforeCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/electrons_tight",
        "electron", minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "");
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_e_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);
      numerator_and_denominatorHistManagers* histograms_denominator_beforeCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable",
        "electron", minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "");
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_e_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);
      numerator_and_denominatorHistManagers* histograms_numerator_afterCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/electrons_tight",
        "electron", minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts");
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_e_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);
      numerator_and_denominatorHistManagers* histograms_denominator_afterCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/electrons_fakeable",
        "electron", minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts");
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_e_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

  numerator_and_denominatorHistManagers* histograms_mu_numerator_incl_beforeCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/muons_tight",
    "muon", -1., -1., -1., -1., "");
  histograms_mu_numerator_incl_beforeCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_mu_denominator_incl_beforeCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable",
    "muon", -1., -1., -1., -1., "");
  histograms_mu_denominator_incl_beforeCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_mu_numerator_incl_afterCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/muons_tight",
    "muon", -1., -1., -1., -1., "aftercuts");
  histograms_mu_numerator_incl_afterCuts->bookHistograms(fs);
  numerator_and_denominatorHistManagers* histograms_mu_denominator_incl_afterCuts = new numerator_and_denominatorHistManagers(
    process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable",
    "muon", -1., -1., -1., -1., "aftercuts");
  histograms_mu_denominator_incl_afterCuts->bookHistograms(fs);
  std::vector<numerator_and_denominatorHistManagers*> histograms_mu_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_mu_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_mu_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers*> histograms_mu_denominator_binned_afterCuts;
  int numEtaBins_mu = etaBins_mu.size() - 1;
  int numPtBins_mu = ptBins_mu.size() - 1;
  for ( int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu ) { 
    double minAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu]);
    double maxAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu + 1]);
    for ( int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu ) {
      double minPt_mu = ptBins_mu[idxPtBin_mu];
      double maxPt_mu = ptBins_mu[idxPtBin_mu + 1];
      numerator_and_denominatorHistManagers* histograms_numerator_beforeCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/muons_tight",
        "muon", minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "");
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);
      numerator_and_denominatorHistManagers* histograms_denominator_beforeCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable",
        "muon", minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "");
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);
      numerator_and_denominatorHistManagers* histograms_numerator_afterCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/numerator/muons_tight",
        "muon", minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts");
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);
      numerator_and_denominatorHistManagers* histograms_denominator_afterCuts = new numerator_and_denominatorHistManagers(
        process_string, isMC, central_or_shift, "LeptonFakeRate/denominator/muons_fakeable",
        "muon", minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts");
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }
 
  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(
      makeHistManager_cfg(process_string, "LeptonFakeRate/gen_unbiased/genEvt", central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(
      makeHistManager_cfg(process_string, "LeptonFakeRate/gen_sel/genEvt", central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
    lheInfoHistManager = new LHEInfoHistManager(
      makeHistManager_cfg(process_string, "LeptonFakeRate/gen_sel/lheInfo", central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

//--- book additional event level histograms
  TH1* histogram_met_pt = fs.make<TH1D>("met_pt", "met_pt", 40, 0., 200.);                                                                 
  TH1* histogram_met_phi = fs.make<TH1D>("met_phi", "met_phi", 36, -TMath::Pi(), +TMath::Pi());
  TH1* histogram_rnd_e = fs.make<TH1D>("rnd_e", "rnd_e", 100, 0., 1.);
  TH1* histogram_rnd_mu = fs.make<TH1D>("rnd_mu", "rnd_mu", 100, 0., 1.);

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable_e(isDEBUG);
  // define order in which rows are printed in cut-flow table
  initializeCutFlowTable(cutFlowTable_e, ">= 1 fakeable electron");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_afterCuts);
  cutFlowTableType cutFlowTable_mu(isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu, ">= 1 fakeable muon");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, "mT_fix(muon, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_afterCuts);

  while ( inputTree->hasNextEvent() ) {
    if ( inputTree->canReport(reportEvery) ) {
      std::cout << "processing Entry " << inputTree->getCurrentMaxEventIdx()
                << " or " << inputTree->getCurrentEventIdx() << " entry in #" << (inputTree->getProcessedFileCount() - 1)
                << " (" << eventInfo << ") file (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

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

//--- fill generator level histograms (before cuts)
    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons); 
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons); 
    // define muon collection for numerator    
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    // define muon collection for denominator (excluding muons that pass numerator)
    //std::vector<const RecoMuon*> fakeable_and_notTightMuons = muonCleaner(fakeableMuons, tightMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);  
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons); 
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons); 
    // define electron collection for numerator    
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    // define electron collection for denominator (excluding electrons that pass numerator)
    //std::vector<const RecoElectron*> fakeable_and_notTightElectrons = electronCleaner(fakeableElectrons, tightElectrons);

    //std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    //std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    //std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    //std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    //std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(preselHadTaus);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets_dR04 = jetCleaner_dR04(jet_ptrs, preselMuons, preselElectrons); 
    std::vector<const RecoJet*> selJets_dR04 = jetSelector(cleanedJets_dR04);
    std::vector<const RecoJet*> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);
    std::vector<const RecoJet*> cleanedJets_dR07 = jetCleaner_dR04(jet_ptrs, preselMuons, preselElectrons); 
    std::vector<const RecoJet*> selJets_dR07 = jetSelector(cleanedJets_dR07);
    std::vector<const RecoJet*> selBJets_loose_dR07 = jetSelectorBtagLoose(cleanedJets_dR07);

    RecoMEt met = metReader->read();

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

      //hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      //hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      //hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets_dR07, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets_dR07, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets_dR07, genJets, 0.2);
    }

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- require exactly one fakeable lepton
    if ( (fakeableElectrons.size() + fakeableMuons.size()) != 1 ) continue;

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= sgn(eventInfo.genWeight);
      if ( isMC_tH ) evtWeight *= eventInfo.genWeight_tH;
      evtWeight *= eventInfo.pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      double btagWeight = 1.;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets_dR07.begin();
	    jet != selJets_dR07.end(); ++jet ) {
	btagWeight *= (*jet)->BtagWeight();
      }
      evtWeight *= btagWeight;
      if ( isDEBUG ) {
	std::cout << "lumiScale = " << lumiScale << std::endl;
	if ( apply_genWeight ) std::cout << "genWeight = " << sgn(eventInfo.genWeight) << std::endl;
	std::cout << "pileupWeight = " << eventInfo.pileupWeight << std::endl;
	std::cout << "btagWeight = " << btagWeight << std::endl;
      }
    }        
    if ( fakeableElectrons.size() >= 1 ) cutFlowTable_e.update(">= 1 fakeable electron", evtWeight);
    if ( fakeableMuons.size()     >= 1 ) cutFlowTable_mu.update(">= 1 fakeable muon", evtWeight);

    bool isGoodLeptonJetPair = false; // set to true if at least one electron+jet or one muon+jet combination passes trigger requirements

//--- fill electron histograms (numerator and denominator)
    for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = triggers_e.begin();
	  hltPath_iter != triggers_e.end(); ++hltPath_iter ) {
      if ( !((*hltPath_iter)->getValue() >= 1) ) continue; // require trigger to fire
      if ( (use_triggers_1e && (*hltPath_iter)->is_trigger_1e()) ||
	   (use_triggers_2e && (*hltPath_iter)->is_trigger_2e()) ) {
	for ( std::vector<const RecoElectron*>::const_iterator fakeableElectron = fakeableElectrons.begin();
	      fakeableElectron != fakeableElectrons.end(); ++fakeableElectron ) {
	  if ( !((*fakeableElectron)->pt() > minPt_e) ) continue;
	  bool isGoodElectronJetPair = false;
	  for ( std::vector<const RecoJet*>::const_iterator selJet = selJets_dR07.begin();
		selJet != selJets_dR07.end(); ++selJet ) {
	    if ( deltaR((*fakeableElectron)->p4(), (*selJet)->p4()) < 0.7 ) continue;
	    if( (*fakeableElectron)->cone_pt() >= (*hltPath_iter)->getMinPt() && (*fakeableElectron)->cone_pt() < (*hltPath_iter)->getMaxPt() &&
		(*selJet)->pt() > (*hltPath_iter)->getMinJetPt() ) {
	      isGoodElectronJetPair = true;
	    }
	  }
	  if ( !isGoodElectronJetPair ) continue;
	  cutFlowTable_e.update("electron+jet pair passing trigger bit", evtWeight);
	  //std::cout << "evtWeight = " << evtWeight << std::endl;
	  double mT = comp_mT(**fakeableElectron, met.pt(), met.phi());
	  double mT_fix = comp_mT_fix(**fakeableElectron, met.pt(), met.phi());
	  double evtWeight_LepJetPair = evtWeight; // copying evtWeight
	  std::cout << (**hltPath_iter);
	  if ( isMC ) {
	    if ( (*hltPath_iter)->getPrescale_rand_mc() > 1. ){
	      double u = rand.Rndm(); // returns uniformly distributed random number between 0 and 1  
	      //std::cout << "u = " << u << std::endl;
	      fillWithOverFlow(histogram_rnd_e, u, 1.);
	      if ( u > (1./(*hltPath_iter)->getPrescale_rand_mc()) ) continue;
	      evtWeight_LepJetPair *= (*hltPath_iter)->getPrescale_rand_mc()/(*hltPath_iter)->getPrescale();
	    } else {
	      evtWeight_LepJetPair *= 1./(*hltPath_iter)->getPrescale();              
	    }
	  }
	  cutFlowTable_e.update("electron+jet pair passing trigger bit && prescale", evtWeight_LepJetPair);
	  //std::cout << "evtWeight_LepJetPair = " << evtWeight_LepJetPair << std::endl;
	  isGoodLeptonJetPair = true;
	  numerator_and_denominatorHistManagers* histograms_incl_beforeCuts = 0;
	  numerator_and_denominatorHistManagers* histograms_incl_afterCuts = 0;
	  std::vector<numerator_and_denominatorHistManagers*>* histograms_binned_beforeCuts = 0;
	  std::vector<numerator_and_denominatorHistManagers*>* histograms_binned_afterCuts = 0;
	  if ( (*fakeableElectron)->isTight() ) { // electron enters numerator
	    histograms_incl_beforeCuts = histograms_e_numerator_incl_beforeCuts;
	    histograms_incl_afterCuts = histograms_e_numerator_incl_afterCuts;
	    histograms_binned_beforeCuts = &histograms_e_numerator_binned_beforeCuts;
	    histograms_binned_afterCuts = &histograms_e_numerator_binned_afterCuts;
	  } else { // electron enters denominator
	    histograms_incl_beforeCuts = histograms_e_denominator_incl_beforeCuts;
	    histograms_incl_afterCuts = histograms_e_denominator_incl_afterCuts;
	    histograms_binned_beforeCuts = &histograms_e_denominator_binned_beforeCuts;
	    histograms_binned_afterCuts = &histograms_e_denominator_binned_afterCuts;
	  }
	  histograms_incl_beforeCuts->fillHistograms(**fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	  fillHistograms(*histograms_binned_beforeCuts, **fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);
	  if ( mT_fix < 15. ) {
	    cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeight_LepJetPair);
	    histograms_incl_afterCuts->fillHistograms(**fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	    fillHistograms(*histograms_binned_afterCuts, **fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);
	  }
	}
      }
    }

//--- fill muon histograms (numerator and denominator)
    for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = triggers_mu.begin();
	  hltPath_iter != triggers_mu.end(); ++hltPath_iter ) {
      if ( !((*hltPath_iter)->getValue() >= 1) ) continue; // require trigger to fire
      if ( (use_triggers_1mu && (*hltPath_iter)->is_trigger_1mu()) ||
	   (use_triggers_2mu && (*hltPath_iter)->is_trigger_2mu()) ) {
	for ( std::vector<const RecoMuon*>::const_iterator fakeableMuon = fakeableMuons.begin();
	      fakeableMuon != fakeableMuons.end(); ++fakeableMuon ) {
	  if ( !((*fakeableMuon)->pt() > minPt_mu) ) continue;
	  bool isGoodMuonJetPair = false;
	  for ( std::vector<const RecoJet*>::const_iterator selJet = selJets_dR07.begin();
		selJet != selJets_dR07.end(); ++selJet ) {
	    if ( deltaR((*fakeableMuon)->p4(), (*selJet)->p4()) < 0.7 ) continue;
	    if( ((*fakeableMuon)->cone_pt() < 30. && selBJets_loose_dR04.size() != 0) || (*fakeableMuon)->cone_pt() >= 30. ) {
	      if( (*fakeableMuon)->cone_pt() >= (*hltPath_iter)->getMinPt() && (*fakeableMuon)->cone_pt() < (*hltPath_iter)->getMaxPt() &&
		  (*selJet)->pt() > (*hltPath_iter)->getMinJetPt() ) {
		isGoodMuonJetPair = true;
	      }
	    }
	  }
	  if ( !isGoodMuonJetPair ) continue;	 
	  cutFlowTable_mu.update("muon+jet pair passing trigger bit", evtWeight);
	  //std::cout << "evtWeight = " << evtWeight << std::endl;
	  double mT = comp_mT(**fakeableMuon, met.pt(), met.phi());
	  double mT_fix = comp_mT_fix(**fakeableMuon, met.pt(), met.phi());
	  double evtWeight_LepJetPair = evtWeight; // copying evtWeight
	  std::cout << (**hltPath_iter);
	  if ( isMC ) {
	    if ( (*hltPath_iter)->getPrescale_rand_mc() > 1. ){
	      double u = rand.Rndm(); // returns uniformly distributed random number between 0 and 1
	      //std::cout << "u = " << u << std::endl;
	      fillWithOverFlow(histogram_rnd_mu, u, 1.);
	      if ( u > (1./(*hltPath_iter)->getPrescale_rand_mc()) ) continue;
	      evtWeight_LepJetPair *= (*hltPath_iter)->getPrescale_rand_mc()/(*hltPath_iter)->getPrescale();
	    } else {
	      evtWeight_LepJetPair *= 1./(*hltPath_iter)->getPrescale();              
	    }
	  }
	  cutFlowTable_mu.update("muon+jet pair passing trigger bit && prescale", evtWeight_LepJetPair);
	  //std::cout << "evtWeight_LepJetPair = " << evtWeight_LepJetPair << std::endl;
	  isGoodLeptonJetPair = true;
	  numerator_and_denominatorHistManagers* histograms_incl_beforeCuts = 0;
	  numerator_and_denominatorHistManagers* histograms_incl_afterCuts = 0;
	  std::vector<numerator_and_denominatorHistManagers*>* histograms_binned_beforeCuts = 0;
	  std::vector<numerator_and_denominatorHistManagers*>* histograms_binned_afterCuts = 0;
	  if ( (*fakeableMuon)->isTight() ) { // muon enters numerator
	    histograms_incl_beforeCuts = histograms_mu_numerator_incl_beforeCuts;
	    histograms_incl_afterCuts = histograms_mu_numerator_incl_afterCuts;
	    histograms_binned_beforeCuts = &histograms_mu_numerator_binned_beforeCuts;
	    histograms_binned_afterCuts = &histograms_mu_numerator_binned_afterCuts;
	  } else { // muon enters denominator
	    histograms_incl_beforeCuts = histograms_mu_denominator_incl_beforeCuts;
	    histograms_incl_afterCuts = histograms_mu_denominator_incl_afterCuts;
	    histograms_binned_beforeCuts = &histograms_mu_denominator_binned_beforeCuts;
	    histograms_binned_afterCuts = &histograms_mu_denominator_binned_afterCuts;
	  }
	  histograms_incl_beforeCuts->fillHistograms(**fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	  fillHistograms(*histograms_binned_beforeCuts, **fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);
	  if ( mT_fix < 15. ) {
	    cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeight_LepJetPair);
	    histograms_incl_afterCuts->fillHistograms(**fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	    fillHistograms(*histograms_binned_afterCuts, **fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);
	  }
	}    
      }
    }

    if ( !isGoodLeptonJetPair ) continue;

    fillWithOverFlow(histogram_met_pt, met.pt(), evtWeight); 
    fillWithOverFlow(histogram_met_phi, met.phi(), evtWeight); 
  
//--- fill generator level histograms (after cuts)
    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in " << inputTree -> getProcessedFileCount() << " file(s) (out of " << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n";

  std::cout << "cut-flow table for electron events" << std::endl;
  cutFlowTable_e.print(std::cout);
  std::cout << std::endl;

  std::cout << "cut-flow table for muon events" << std::endl;
  cutFlowTable_mu.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;

  hltPaths_LeptonFakeRate_delete(triggers_e);
  hltPaths_LeptonFakeRate_delete(triggers_mu);

  delete inputTree;

  clock.Show("analyze_LeptonFakeRate");

  return EXIT_SUCCESS;
}
 
