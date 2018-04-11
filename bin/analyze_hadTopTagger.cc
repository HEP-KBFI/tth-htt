// latest

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
#include <TMatrixD.h> // TMatrixD
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::Pi()

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h" // RecoJetAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderHTTv2.h" // RecoJetReaderHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK12.h" // RecoJetReaderAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
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
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK12.h" // RecoJetSelectorAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h" // JetHistManagerHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerAK12.h" // JetHistManagerAK12
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTaggerFill.h" // HadTopTaggerFill

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <math.h> // acos, sqrt
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <numeric> // iota

#include <iostream>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

enum { kGen_bWj1Wj2, kGen_bWj1, kGen_bWj2, kGen_Wj1Wj2, kGen_b, kGen_Wj1, kGen_Wj2, kGen_none };
bool inAK12 = true;

template <typename T> std::vector<size_t> sort_indexes(const std::vector<T> &v) {
  // initialize original index locations
  std::vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
  return idx;
}

std::vector<size_t> calRank(std::vector<const RecoJet*>& selJetsIt) {
  std::vector<double> btag_disc;
  for ( std::vector<const RecoJet*>::const_iterator jetIterB = selJetsIt.begin();
    jetIterB != selJetsIt.end(); ++jetIterB ) {
      btag_disc.push_back((*jetIterB)->BtagCSV());
    }
    std::vector<size_t> result(btag_disc.size(),0);
    //sorted index
    std::vector<size_t> indx(btag_disc.size());
    iota(indx.begin(),indx.end(),0);
    sort(indx.begin(),indx.end(),[&btag_disc](int i1, int i2){return btag_disc[i1]>btag_disc[i2];});
    //return ranking
    for(size_t iter=0;iter<btag_disc.size();++iter){
        result[indx[iter]]=iter+1;
    }
    std::cout<<"btag discriminant  ";
    for (auto i: btag_disc) std::cout << i << " ";
    std::cout<<std::endl;
    return result;
}

void dumpGenParticles(const std::string& label, const std::vector<GenParticle>& particles)
{
  for ( size_t idxParticle = 0; idxParticle < particles.size(); ++idxParticle ) {
    std::cout << label << " #" << idxParticle << ":" << " ";
    std::cout << particles[idxParticle];
    std::cout << std::endl;
  }
}

double square(double x)
{
  return x*x;
}

double comp_theta_t(const Particle::LorentzVector& jet1_p4, double jet1_pullEta, double jet1_pullPhi, const Particle::LorentzVector& jet2_p4)
{
  double dEta1 = jet1_pullEta - jet1_p4.eta();
  double dPhi1 = jet1_pullPhi - jet1_p4.phi();
  double dEta2 = jet2_p4.eta() - jet1_p4.eta();
  double dPhi2 = jet2_p4.phi() - jet1_p4.phi();
  double dR1 = sqrt(square(dEta1) + square(dPhi1));
  double dR2 = sqrt(square(dEta2) + square(dPhi2));
  if ( dR1*dR2 > 0. ) {
    double cos_theta_t = (dEta1*dEta2 + dPhi1*dPhi2)/(dR1*dR2);
    assert(cos_theta_t >= -1. && cos_theta_t <= +1.);
    return acos(cos_theta_t);
  } else {
    return -1.;
  }
}

int getGenMatch(bool b_isGenMatched, bool Wj1_isGenMatched, bool Wj2_isGenMatched)
{
  int idxGenMatch = -1;
  if      ( b_isGenMatched && Wj1_isGenMatched && Wj2_isGenMatched ) idxGenMatch = kGen_bWj1Wj2;
  else if ( b_isGenMatched && Wj1_isGenMatched                     ) idxGenMatch = kGen_bWj1;
  else if ( b_isGenMatched                     && Wj2_isGenMatched ) idxGenMatch = kGen_bWj2;
  else if (                   Wj1_isGenMatched && Wj2_isGenMatched ) idxGenMatch = kGen_Wj1Wj2;
  else if ( b_isGenMatched                                         ) idxGenMatch = kGen_b;
  else if (                   Wj1_isGenMatched                     ) idxGenMatch = kGen_Wj1;
  else if (                                       Wj2_isGenMatched ) idxGenMatch = kGen_Wj2;
  else                                                               idxGenMatch = kGen_none;
  return idxGenMatch;
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

  std::cout << "<analyze_hadTopTagger>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_hadTopTagger");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_hadTopTagger")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_hadTopTagger");
  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;
  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2017" ) era = kEra_2017;
  else throw cms::Exception("analyze_hadTopTagger")
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId");
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tH" ) ? true : false;
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  const int jetPt_option     = getJet_option       (central_or_shift, isMC);
  const int jetBtagSF_option = getBTagWeight_option(central_or_shift, isMC);

  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_jetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_jetsHTTv2");
  std::string branchName_subjetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_subjetsHTTv2");
  std::string branchName_jetsAK12 = cfg_analyze.getParameter<std::string>("branchName_jetsAK12");
  std::string branchName_subjetsAK12 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK12");
  std::string branchName_jetsAK8 = cfg_analyze.getParameter<std::string>("branchName_jetsAK8");
  std::string branchName_subjetsAK8 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK8");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");

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

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  RecoJetReaderHTTv2* jetReaderHTTv2 = new RecoJetReaderHTTv2(era, branchName_jetsHTTv2, branchName_subjetsHTTv2);
  inputTree -> registerReader(jetReaderHTTv2);
  RecoJetCollectionSelectorHTTv2 jetSelectorHTTv2(era);

  RecoJetReaderAK12* jetReaderAK12 = new RecoJetReaderAK12(era, branchName_jetsAK12, branchName_subjetsAK12);
  inputTree -> registerReader(jetReaderAK12);
  RecoJetCollectionSelectorAK12 jetSelectorAK12(era);

  RecoJetReaderAK8* jetReaderAK8 = new RecoJetReaderAK8(era, branchName_jetsAK8, branchName_subjetsAK8);
  inputTree -> registerReader(jetReaderAK8);
  RecoJetCollectionSelectorAK8 jetSelectorAK8(era);

//--- declare generator level information
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    //}
    lheInfoReader = new LHEInfoReader();
    inputTree -> registerReader(lheInfoReader);
  }

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);

  if ( isMC ) {
    inputTree->registerReader(genTopQuarkReader);
    inputTree->registerReader(genBJetReader);
    inputTree->registerReader(genWBosonReader);
    inputTree->registerReader(genWJetReader);
  }

  HadTopTaggerFill* hadTopTaggerFill = new HadTopTaggerFill();

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
       makeHistManager_cfg(process_string, Form("%s/evtntuple", histogramDir.data()), "central")
       );
    bdt_filler->register_variable<float_type>(
      "tau32Top", "massTop",
      "tau21W", "massW",  "massW_SD",
      "genTopPt"
      /*
      "m_bWj1Wj2", "m_Wj1Wj2", "m_bWj1", "m_bWj2",
      "m_Wj1Wj2_div_m_bWj1Wj2",
      "CSV_b", "CSV_Wj1", "CSV_Wj2",
      "pT_b", "eta_b", "phi_b", "mass_b",
	  "kinFit_pT_b", "kinFit_eta_b", "kinFit_phi_b", "kinFit_mass_b",
      "pT_Wj1", "eta_Wj1", "phi_Wj1", "mass_Wj1",
	  "kinFit_pT_Wj1", "kinFit_eta_Wj1", "kinFit_phi_Wj1", "kinFit_mass_Wj1",
      "pT_Wj2", "eta_Wj2", "phi_Wj2", "mass_Wj2",
	  "kinFit_pT_Wj2", "kinFit_eta_Wj2", "kinFit_phi_Wj2", "kinFit_mass_Wj2",
	  "cosTheta_leadWj_restTop","cosTheta_subleadWj_restTop", "cosTheta_Kin_leadWj_restTop","cosTheta_Kin_subleadWj_restTop",
	  "cosTheta_leadEWj_restTop","cosTheta_subleadEWj_restTop", "cosTheta_Kin_leadEWj_restTop","cosTheta_Kin_subleadEWj_restTop",
	  "cosThetaW_rest","cosThetaKinW_rest","cosThetaW_lab","cosThetaKinW_lab",
	  "cosThetab_rest","cosThetaKinb_rest","cosThetab_lab","cosThetaKinb_lab",
	  "Dphi_Wj1_Wj2_lab","Dphi_KinWj1_KinWj2_lab",
	  "Dphi_Wb_rest","Dphi_KinWb_rest","Dphi_Wb_lab","Dphi_KinWb_lab",
	  "cosThetaWj1_restW","cosThetaKinWj_restW",
      "dR_bWj1", "dR_bWj2", "dR_Wj1Wj2", "dR_bW",
      "statusKinFit", "nllKinFit", "alphaKinFit", "logPKinFit", "logPErrKinFit",
      "qg_b", "qg_Wj1", "qg_Wj2",
      "pT_bWj1Wj2", "pT_Wj1Wj2",
      "max_dR_div_expRjet","genTopPt","genAntiTopPt"
      */
    );


    bdt_filler->register_variable<int_type>(
      "typeTop", "collectionSize", "bjet_tag_position", "bWj1Wj2_isGenMatched", "counter"
      //"b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      //"bWj1Wj2_isGenMatched"
    );
	//bdt_filler->register_variable<int_type>("mvaOutput_hadTopTagger");
    bdt_filler->bookTree(fs);
	}

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  int countFatTop = 0;
  int countFatAK8 = 0;
  int countFatAK12 = 0;
  int countResolved8 = 0;
  int countResolved12 = 0;

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if ( isDEBUG ) {
      std::cout << "processing run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
    }

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

    //std::cout << "before load jets"  << std::endl;
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> selJetsraw = convert_to_ptrs(jets);
    std::vector<const RecoJet*> selJets = jetSelector(selJetsraw, isHigherPt);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(selJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(selJets);
    //std::cout << "after load jets"  << std::endl;
//--- build collections of jets reconstructed by hep-top-tagger (HTTv2) algorithm
    std::vector<RecoJetHTTv2> jetsHTTv2 = jetReaderHTTv2->read();
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2raw = convert_to_ptrs(jetsHTTv2);
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2 =  jetSelectorHTTv2(jet_ptrsHTTv2raw, isHigherPt);
    //std::cout << "after load HTT"  << std::endl;
//--- build collections of jets reconstructed by anti-kT algorithm with dR=1.2 (AK12)
    std::vector<RecoJetAK12> jetsAK12 = jetReaderAK12->read();
    std::vector<const RecoJetAK12*> jet_ptrsAK12raw = convert_to_ptrs(jetsAK12);
    std::vector<const RecoJetAK12*> jet_ptrsAK12 = jetSelectorAK12(jet_ptrsAK12raw, isHigherPt);
    //std::cout << "after load ak12"  << std::endl;
//--- build collections of jets reconstructed by anti-kT algorithm with dR=0.8 (AK8)
    std::vector<RecoJetAK8> jetsAK8 = jetReaderAK8->read();
    std::vector<const RecoJetAK8*> jet_ptrsAK8raw = convert_to_ptrs(jetsAK8);
    std::vector<const RecoJetAK8*> jet_ptrsAK8 = jetSelectorAK8(jet_ptrsAK8raw , isHigherPt);
    //std::cout << "after load ak8"  << std::endl;
//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    std::vector<GenJet> genJets;
    if ( isMC && redoGenMatching ) {
      if ( genJetReader ) {
				genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

    if ( isMC ) {
      lheInfoReader->read();
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

//--- build collections of generator level particles
    std::vector<GenParticle> genTopQuarks = genTopQuarkReader->read();
    std::vector<GenParticle> genBJets = genBJetReader->read();
    std::vector<GenParticle> genWBosons = genWBosonReader->read();
    std::vector<GenParticle> genWJets = genWJetReader->read();

		std::cout << "\nTreeEntry "<<analyzedEntries << " passed selection conditions" << std::endl;
    std::cout << "Size of jet collections "
      <<jet_ptrsHTTv2.size()<< " "<< jet_ptrsAK8.size() << " "<< jet_ptrsAK12.size() << " " << selJets.size() << std::endl;
    // typeTop: 1 - FatTop; 21 - countFatAK8; 22 countFatAK12; 31 - countResolved8; 32 - countResolved12;

    int collectionSize = 0;
    Particle::LorentzVector unfittedHadTopP4, selBJet, selWJet1, selWJet2 ;
    bool isGenMatched = false;
    double genTopPtProbeTop = -1.;
    double genTopPtProbeAntiTop = -1.;
    double genTopPt = -1.;
    //bool hadtruth = false;
    int typeTop = -1; // 1 - FatTop; 21 - countFatAK8; 22 countFatAK12; 31 - countResolved8; 32 - countResolved12;
    if (jet_ptrsHTTv2.size() > 0) {
      countFatTop++;
      typeTop = 1;
      collectionSize = jet_ptrsHTTv2.size();
    }
    else {
      if (inAK12) {
        if (jet_ptrsAK12.size() >0) {
          countFatAK12++;
          typeTop = 2;
          collectionSize = jet_ptrsAK12.size();
        }
        else if (selJets.size() >0) {
          countResolved12++;
          typeTop = 3;
          collectionSize = selJets.size();
        }
      } else {
        if (jet_ptrsAK8.size() >0) {
          countFatAK8++;
          typeTop = 2;
          collectionSize = jet_ptrsAK8.size();
        }
        else if (selJets.size() >0) {
          countResolved8++;
          typeTop = 3;
          collectionSize = selJets.size();
        }
      }
    }

    if (typeTop == 1) {
      std::cout<<"filling "<<typeTop<<std::endl;
      for ( std::vector<const RecoJetHTTv2*>::const_iterator jetIter = jet_ptrsHTTv2.begin();
        jetIter != jet_ptrsHTTv2.end(); ++jetIter ) {
          unfittedHadTopP4 = (*jetIter)->p4();
          // I just take the subjet with highest b-tag score to be the b-candidate
          const RecoSubjetHTTv2* recSubJet[3];
          recSubJet[0] = (*jetIter)->subJet1();
          recSubJet[1] = (*jetIter)->subJet2();
          recSubJet[2] = (*jetIter)->subJet3();
          std::vector<double> btag_disc = {recSubJet[0]->BtagCSV(), recSubJet[1]->BtagCSV(), recSubJet[2]->BtagCSV()};
          auto btag_order = sort_indexes(btag_disc);
          selBJet = recSubJet[btag_order[0]]->p4();
          selWJet1 = recSubJet[btag_order[1]]->p4();
          selWJet2 = recSubJet[btag_order[2]]->p4();
          //std::cout<<"Toppt = "<< (*jetIter)->pt() <<std::endl;
          //std::cout<<"Topeta = "<< (*jetIter)->eta() <<std::endl;
          //std::cout<<"Top mass = "<< (*jetIter)->mass() <<" "<< unfittedHadTopP4.mass() <<std::endl;
          //std::cout<<"subjet pt = "<< selBJet.pt() <<std::endl;
          //std::cout<<" tau3 tau2 = "<< (*jetIter)->tau3()<<" "<< (*jetIter)->tau2() <<std::endl;
          // checking btag ordering
          std::cout<<"btag ordering  ";
          for (auto i: btag_order) std::cout << i << " ";
          std::cout<<" typeTop = "<<typeTop<<std::endl;
          std::cout<<"btag discriminant  ";
          for (auto i: btag_disc) std::cout << i << " ";
          std::cout<<std::endl;
          std::cout<<"max btag position "<< btag_order[0] <<" value "<< btag_disc[btag_order[0]] <<std::endl;
          // calculate matching
          std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenTop, genTopPtProbeTop, typeTop,unfittedHadTopP4);
          std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(selBJet, selWJet1,  selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop, genTopPtProbeAntiTop, typeTop,unfittedHadTopP4);
          if(genMatchingTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeTop;
          if(genMatchingAntiTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeAntiTop;
          isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
          if ( bdt_filler ) {
            bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
            ("typeTop",              typeTop)
            ("tau32Top",             (*jetIter)->tau3()/(*jetIter)->tau2())
            ("massTop",              unfittedHadTopP4.mass())
            ("tau21W",               -1.)
            ("massW",                (selWJet1+selWJet2).mass())
            ("massW_SD",             -1.)
            ("genTopPt",             genTopPt)
            ("collectionSize",       collectionSize)
            ("bjet_tag_position",    1)
            ("bWj1Wj2_isGenMatched", isGenMatched)
            ("counter",              (inputTree -> getProcessedFileCount() - 1))
                .fill();
          }
        }
    } else if (typeTop!=-1) {
    // store b-tag classification
    std::cout<<std::endl;
    auto btag_order = calRank(selJets);
    std::cout<<"btag ordering  ";
    for (auto i: btag_order) std::cout << i << " ";
    std::cout<<" typeTop = "<<typeTop<<std::endl;
    // classify between 2 and 3
    if (typeTop == 2 and inAK12) {
      std::cout<<"filling "<<typeTop<<std::endl;
      for ( std::vector<const RecoJetAK12*>::const_iterator jetIter = jet_ptrsAK12.begin();
        jetIter != jet_ptrsAK12.end(); ++jetIter ) {
          for ( unsigned int bjetCandidate = 0; bjetCandidate < selJets.size(); bjetCandidate++ ) {
              unfittedHadTopP4 = (*jetIter)->p4() + (*selJets[bjetCandidate]).p4();
              //std::cout<<"TopPt = "<<unfittedHadTopP4.pt()<<std::endl;
              //std::cout<<"Wtau21 = "<< (*jetIter)->tau2()/(*jetIter)->tau1() <<std::endl;
              //std::cout<<"Wmass = "<< (*jetIter)->mass() <<std::endl;
              //std::cout<<"WmassSD = "<< (*jetIter)->msoftdrop() <<std::endl;
              //std::cout<<"btag position = "<< btag_order[bjetCandidate] <<std::endl;
              selBJet = (*selJets[bjetCandidate]).p4();
              //std::cout<<"loaded bjet "<< selBJet.pt()<<std::endl;
              //std::cout<<"Wpt = "<< (*jetIter)->pt() <<std::endl;
              //std::cout<<"Weta = "<< (*jetIter)->eta() <<std::endl;
              //std::cout<<" subjet index = "<< (*jetIter)->subJetIdx1()<<" "<< (*jetIter)->subJetIdx2() <<std::endl;
              //if (massMD_typeTop22 < 1) continue;
              selWJet1 = (*jetIter)->subJet1()->p4();
              selWJet2 = (*jetIter)->subJet2()->p4();
              //std::cout<<"loaded subjets "<<selWJet1.pt()<<" "<<selWJet2.pt()<<std::endl;
              // calculate matching
              std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenTop, genTopPtProbeTop, typeTop,(*jetIter)->p4());
              std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(selBJet, selWJet1,  selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop, genTopPtProbeAntiTop, typeTop,(*jetIter)->p4());
              if(genMatchingTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeTop;
              if(genMatchingAntiTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeAntiTop;
              isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
              if ( bdt_filler ) {
                bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                ("typeTop",              typeTop)
                ("tau32Top",             -1.)
                ("massTop",              unfittedHadTopP4.mass())
                ("tau21W",               (*jetIter)->tau2()/(*jetIter)->tau1())
                ("massW",                (*jetIter)->mass())
                ("massW_SD",             (*jetIter)->msoftdrop())
                ("genTopPt",             genTopPt)
                ("collectionSize",       collectionSize)
                ("bjet_tag_position",    btag_order[bjetCandidate])
                ("bWj1Wj2_isGenMatched", isGenMatched)
                ("counter",              (inputTree -> getProcessedFileCount() - 1))
                    .fill();
              }
          }
        }
    } else if (typeTop == 2) {
        std::cout<<"filling "<<typeTop<<std::endl;
        for ( std::vector<const RecoJetAK8*>::const_iterator jetIter = jet_ptrsAK8.begin();
          jetIter != jet_ptrsAK8.end(); ++jetIter ) {
            for ( unsigned int bjetCandidate = 0; bjetCandidate < selJets.size(); bjetCandidate++ ) {
                unfittedHadTopP4 = (*jetIter)->p4() + (*selJets[bjetCandidate]).p4();
                //std::cout<<"TopPt = "<<unfittedHadTopP4.pt()<<std::endl;
                //std::cout<<"Wtau21 = "<< (*jetIter)->tau2()/(*jetIter)->tau1() <<std::endl;
                //std::cout<<"Wmass = "<< (*jetIter)->mass() <<std::endl;
                //std::cout<<"WmassSD = "<< (*jetIter)->msoftdrop() <<std::endl;
                //std::cout<<"Wpt = "<< (*jetIter)->pt() <<std::endl;
                //std::cout<<"Weta = "<< (*jetIter)->eta() <<std::endl;
                selBJet = (*selJets[bjetCandidate]).p4();
                //std::cout<<" subjet index = "<< (*jetIter)->subjet_idx1()<<" "<< (*jetIter)->subjet_idx2() <<std::endl;
                selWJet1 = (*jetIter)->subJet1()->p4();
                selWJet2 = (*jetIter)->subJet2()->p4();
                // calculate matching
                std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenTop, genTopPtProbeTop, typeTop,(*jetIter)->p4());
                std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(selBJet, selWJet1,  selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop, genTopPtProbeAntiTop, typeTop,(*jetIter)->p4());
                if(genMatchingTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeTop;
                if(genMatchingAntiTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeAntiTop;
                isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                //
                if ( bdt_filler ) {
                  bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                  ("typeTop",              typeTop)
                  ("tau32Top",             -1.)
                  ("massTop",              unfittedHadTopP4.mass())
                  ("tau21W",               (*jetIter)->tau2()/(*jetIter)->tau1())
                  ("massW",                (*jetIter)->mass())
                  ("massW_SD",             (*jetIter)->msoftdrop())
                  ("genTopPt",             genTopPt)
                  ("collectionSize",       collectionSize)
                  ("bjet_tag_position",    btag_order[bjetCandidate])
                  ("bWj1Wj2_isGenMatched", isGenMatched)
                  ("counter",              (inputTree -> getProcessedFileCount() - 1))
                      .fill();
                }
            }
            }
        } else if (typeTop == 3) {
          for ( unsigned int bjetCandidate = 0; bjetCandidate < selJets.size(); bjetCandidate++ )  {
            for ( std::vector<const RecoJet*>::const_iterator selWJet1Candidate = selJets.begin();
              selWJet1Candidate != selJets.end(); ++selWJet1Candidate ) {
               if ( (*selWJet1Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
               for ( std::vector<const RecoJet*>::const_iterator selWJet2Candidate = selWJet1Candidate + 1;
                 selWJet2Candidate != selJets.end(); ++selWJet2Candidate ) {
                  if ( (*selWJet2Candidate)->pt() == (*selJets[bjetCandidate]).pt() ) continue;
                  if ( (*selWJet2Candidate)->pt() == (*selWJet1Candidate)->pt() ) continue;
                  selBJet = (*selJets[bjetCandidate]).p4();
                  selWJet1 = (*selWJet1Candidate)->p4();
                  selWJet2 = (*selWJet2Candidate)->p4();
                  // calculate gen matching
                  std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenTop, genTopPtProbeTop);
                  std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(selBJet, selWJet1,  selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop, genTopPtProbeAntiTop);
                  if(genMatchingTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeTop;
                  if(genMatchingAntiTop[kGenMatchedTriplet]) genTopPt=genTopPtProbeAntiTop;
                  isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
                  //std::cout<<"btag position = "<< btag_order[bjetCandidate] <<std::endl;
                  if ( bdt_filler ) {
                    bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
                    ("typeTop",              typeTop)
                    ("tau32Top",                -1.)
                    ("massTop",              unfittedHadTopP4.mass())
                    ("tau21W",                -1.)
                    ("massW",                (selWJet1+selWJet2).mass())
                    ("massW_SD",             -1.) // maybe add the kinfitted mass here
                    ("genTopPt",             genTopPt)
                    ("collectionSize",       collectionSize)
                    ("bjet_tag_position",    btag_order[bjetCandidate])
                    ("bWj1Wj2_isGenMatched", isGenMatched)
                    ("counter",              (inputTree -> getProcessedFileCount() - 1))
                        .fill();
                  }
               }
            }
          }
    } //else throw cms::Exception("analyze_hadTopTagger")
      //<< "Does not fall in any category " << " !!\n";
  }

		++selectedEntries;
    //selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }
  //if(bdt_filler) bdt_filler->write();

  std::cout << "AK8 separation = " << countFatTop << " " << countFatAK8 << " " << countResolved8<< " " << countFatTop+countFatAK8+countResolved8<< std::endl;
  std::cout << "AK12 separation = " << countFatTop << " " << countFatAK12 << " " << countResolved12<< " " << countFatTop+countFatAK12+countResolved12<< std::endl;

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;

  delete jetReader;
  delete genJetReader;
  delete lheInfoReader;
  delete hadTopTaggerFill;
  delete inputTree;

  clock.Show("analyze_hadTopTagger");

  return EXIT_SUCCESS;
}
