
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
#include <TRandom3.h> // TRandom3
#include <TH1D.h> // TH1D

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_gen.h" // CutFlowTableHistManager_gen
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

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

enum { kGen_bWj1Wj2, kGen_bWj1, kGen_bWj2, kGen_Wj1Wj2, kGen_b, kGen_Wj1, kGen_Wj2, kGen_none };

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

TH1* book1D(const std::string& name, const std::string& title, int numBins, double min, double max)
{
  TH1* histogram = new TH1D(name.data(), title.data(), numBins, min, max);
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

void dumpGenParticles(const std::string& label, const std::vector<GenParticle>& particles)
{
  for ( size_t idxParticle = 0; idxParticle < particles.size(); ++idxParticle ) {
    std::cout << label << " #" << idxParticle << ":" << std::endl;
    std::cout << particles[idxParticle];
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

/**
 * @brief Produce datacard and control plots for 1l_2tau category.
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
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_hadTopTagger") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"    ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"    ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_hadTopTagger") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 

  bool isDEBUG = ( cfg_analyze.exists("isDEBUG") ) ? cfg_analyze.getParameter<bool>("isDEBUG") : false; 
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled !!" << std::endl;

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfg_runLumiEventSelector;
    cfg_runLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfg_runLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfg_runLumiEventSelector);
  }

  bool selectBDT = ( cfg_analyze.exists("selectBDT") ) ? cfg_analyze.getParameter<bool>("selectBDT") : false;
  
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
    throw cms::Exception("analyze_hadTopTagger") 
      << "Failed to identify input Tree !!\n";
  }
  
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

  GENWEIGHT_TYPE genWeight = 1.;
  PUWEIGHT_TYPE pileupWeight = 1.;
  if ( isMC ) {
    inputTree->SetBranchAddress(GENWEIGHT_KEY, &genWeight);
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }
  
//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons);
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  

  GenParticleReader* genTopQuarkReader = new GenParticleReader(Form("n%s", branchName_genTopQuarks.data()), branchName_genTopQuarks);
  genTopQuarkReader->setBranchAddresses(inputTree);
  GenParticleReader* genBJetReader = new GenParticleReader(Form("n%s", branchName_genBJets.data()), branchName_genBJets);
  genBJetReader->setBranchAddresses(inputTree);
  GenParticleReader* genWBosonReader = new GenParticleReader(Form("n%s", branchName_genWBosons.data()), branchName_genWBosons);
  genWBosonReader->setBranchAddresses(inputTree);
  GenParticleReader* genWJetReader = new GenParticleReader(Form("n%s", branchName_genWJets.data()), branchName_genWJets);
  genWJetReader->setBranchAddresses(inputTree);

  HadTopTagger* hadTopTagger = new HadTopTagger();

//--- declare histograms
  std::map<int, MVAInputVarHistManager*> mvaInputHistManagers;
  std::map<int, TH1*> mvaOutputHistManagers;
  for ( int idxGenMatch = kGen_bWj1Wj2; idxGenMatch <= kGen_none; ++idxGenMatch ) {
    std::string genMatch;
    if      ( idxGenMatch == kGen_bWj1Wj2 ) genMatch = "gen_bWj1Wj2";
    else if ( idxGenMatch == kGen_bWj1    ) genMatch = "gen_bWj1";
    else if ( idxGenMatch == kGen_bWj2    ) genMatch = "gen_bWj2";
    else if ( idxGenMatch == kGen_Wj1Wj2  ) genMatch = "gen_Wj1Wj2";
    else if ( idxGenMatch == kGen_b       ) genMatch = "gen_b";
    else if ( idxGenMatch == kGen_Wj1     ) genMatch = "gen_Wj1";
    else if ( idxGenMatch == kGen_Wj2     ) genMatch = "gen_Wj2";
    else if ( idxGenMatch == kGen_none    ) genMatch = "gen_none";
    else assert(0);
    MVAInputVarHistManager* mvaInputHistManager = new MVAInputVarHistManager(makeHistManager_cfg(process_string, 
      Form("%s/%s/mvaInputs", histogramDir.data(), genMatch.data()), "central"));
    mvaInputHistManager->defineBinningOption("m_bWj1Wj2", 100, 0., 1.e+3);
    mvaInputHistManager->defineBinningOption("m_Wj1Wj2", 100, 0., 1.e+3);
    mvaInputHistManager->defineBinningOption("m_bWj1", 100, 0., 1.e+3);
    mvaInputHistManager->defineBinningOption("m_bWj2", 100, 0., 1.e+3);
    mvaInputHistManager->defineBinningOption("m_Wj1Wj2_div_m_bWj1Wj2", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("CSV_b", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("CSV_Wj1", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("CSV_Wj2", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("pT_b", 100, 0., 5.e+2);
    mvaInputHistManager->defineBinningOption("pT_Wj1", 100, 0., 5.e+2);
    mvaInputHistManager->defineBinningOption("pT_Wj2", 100, 0., 5.e+2);
    mvaInputHistManager->defineBinningOption("dR_bWj1", 100, 0., 5.);
    mvaInputHistManager->defineBinningOption("dR_bWj2", 100, 0., 5.);
    mvaInputHistManager->defineBinningOption("dR_Wj1Wj2", 100, 0., 5.);
    mvaInputHistManager->defineBinningOption("dR_bW", 100, 0., 5.);
    mvaInputHistManager->defineBinningOption("statusKinFit", 6, -1., +5.);
    mvaInputHistManager->defineBinningOption("nllKinFit", 150, -10., +5.);
    mvaInputHistManager->defineBinningOption("alphaKinFit", 200, 0., 2.);
    mvaInputHistManager->defineBinningOption("logPKinFit", 150, -10., +5.);
    mvaInputHistManager->defineBinningOption("logPErrKinFit", 250, -20., +5.);
    mvaInputHistManager->defineBinningOption("qg_b", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("qg_Wj1", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("qg_Wj2", 100, 0., 1.);
    mvaInputHistManager->defineBinningOption("pT_bWj1Wj2", 100, 0., 5.e+2);
    mvaInputHistManager->defineBinningOption("pT_Wj1Wj2", 100, 0., 5.e+2);
    mvaInputHistManager->defineBinningOption("max_dR_div_expRjet", 200, 0., 2.);
    mvaInputHistManager->bookHistograms(fs, hadTopTagger->mvaInputVariables());
    mvaInputHistManagers[idxGenMatch] = mvaInputHistManager; 

    std::string subdirName = Form("%s/%s/%s", histogramDir.data(), genMatch.data(), process_string.data());
    TDirectory* subdir = createSubdirectory_recursively(fs, subdirName);
    subdir->cd();

    TH1* histogram_mvaOutput = book1D("mvaOutput", "mvaOutput", 200, -1., +1.);
    mvaOutputHistManagers[idxGenMatch] = histogram_mvaOutput;
  }

  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if ( selectBDT ) {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/evtntuple", histogramDir.data()), "central")
    );
    bdt_filler->register_variable<float_type>(
      "m_bWj1Wj2", "m_Wj1Wj2", "m_bWj1", "m_bWj2", 
      "m_Wj1Wj2_div_m_bWj1Wj2",
      "CSV_b", "CSV_Wj1", "CSV_Wj2",
      "pT_b", "pT_Wj1", "pT_Wj2",
      "dR_bWj1", "dR_bWj2", "dR_Wj1Wj2", "dR_bW",
      "statusKinFit", "nllKinFit", "alphaKinFit", "logPKinFit", "logPErrKinFit", 
      "qg_b", "qg_Wj1", "qg_Wj2",
      "pT_bWj1Wj2", "pT_Wj1Wj2",
      "max_dR_div_expRjet"
    );
    bdt_filler->register_variable<int_type>(
      "b_isGenMatched", "Wj1_isGenMatched", "Wj2_isGenMatched",
      "bWj1Wj2_isGenMatched"
    );
    bdt_filler->bookTree(fs);
  }

  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  CutFlowTableHistManager_gen* cutFlowHistManager = new CutFlowTableHistManager_gen(makeHistManager_cfg(process_string,
    Form("%s/cutFlow", histogramDir.data()), "central"));
  cutFlowHistManager->bookHistograms(fs);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");
    cutFlowHistManager->fillHistograms("run:ls:event selection");

    if ( isDEBUG ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event << std::endl;
      if ( inputTree->GetFile() ) std::cout << "input File = " << inputTree->GetFile()->GetName() << std::endl;
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, fakeableMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);

//--- build collections of generator level particles 
    std::vector<GenParticle> genTopQuarks = genTopQuarkReader->read();
    std::vector<GenParticle> genBJets = genBJetReader->read();
    std::vector<GenParticle> genWBosons = genWBosonReader->read();
    std::vector<GenParticle> genWJets = genWJetReader->read();

    if ( isDEBUG ) {
      dumpGenParticles("genTopQuark", genTopQuarks);
      dumpGenParticles("genBJet", genBJets);
      dumpGenParticles("genWBoson", genWBosons);
      dumpGenParticles("genWJet", genWJets);
      std::cout << std::endl;
    }

    if ( !(genTopQuarks.size() == 2) ) continue;
    cutFlowTable.update("2 genTopQuarks");
    cutFlowHistManager->fillHistograms("2 genTopQuarks");
    if ( !(genBJets.size() == 2) ) continue;
    cutFlowTable.update("2 genBJets");
    cutFlowHistManager->fillHistograms("2 genBJets");
    if ( !(genWBosons.size() == 2) ) continue;
    cutFlowTable.update("2 genWBosons");
    cutFlowHistManager->fillHistograms("2 genWBosons");
    if ( !(genWJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 genWJets");
    cutFlowHistManager->fillHistograms(">= 2 genWJets");
    
    const GenParticle* genTopQuark = 0;
    const GenParticle* genAntiTopQuark = 0;
    for ( std::vector<GenParticle>::const_iterator it = genTopQuarks.begin();
	  it != genTopQuarks.end(); ++it ) {
      if ( it->pdgId() == +6 && !genTopQuark     ) genTopQuark = &(*it);
      if ( it->pdgId() == -6 && !genAntiTopQuark ) genAntiTopQuark = &(*it);
    }
    if ( !(genTopQuark && genAntiTopQuark) ) continue;
    cutFlowTable.update("genTopQuark && genAntiTopQuark");
    cutFlowHistManager->fillHistograms("genTopQuark && genAntiTopQuark");

    const GenParticle* genBJetFromTop = 0;
    const GenParticle* genBJetFromAntiTop = 0;
    for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();
	  it != genBJets.end(); ++it ) {
      if ( it->pdgId() == +5 && !genBJetFromTop     ) genBJetFromTop = &(*it);
      if ( it->pdgId() == -5 && !genBJetFromAntiTop ) genBJetFromAntiTop = &(*it);
    }
    if ( !(genBJetFromTop && genBJetFromAntiTop) ) continue;
    cutFlowTable.update("genBJetFromTop && genBJetFromAntiTop");
    cutFlowHistManager->fillHistograms("genBJetFromTop && genBJetFromAntiTop");

    const GenParticle* genWBosonFromTop = 0;
    const GenParticle* genWBosonFromAntiTop = 0;
    for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	  it != genWBosons.end(); ++it ) {
      if ( it->pdgId() == +24 && !genWBosonFromTop     ) genWBosonFromTop = &(*it);
      if ( it->pdgId() == -24 && !genWBosonFromAntiTop ) genWBosonFromAntiTop = &(*it);
    }
    if ( !(genWBosonFromTop && genWBosonFromAntiTop) ) continue;
    cutFlowTable.update("genWBosonFromTop && genWBosonFromAntiTop");
    cutFlowHistManager->fillHistograms("genWBosonFromTop && genWBosonFromAntiTop");

    if ( !(std::fabs((genBJetFromTop->p4() + genWBosonFromTop->p4()).mass() - genTopQuark->mass()) < 1.e+1) ) continue;
    cutFlowTable.update("genTopQuark mass");
    cutFlowHistManager->fillHistograms("genTopQuark mass");
    if ( !(std::fabs((genBJetFromAntiTop->p4() + genWBosonFromAntiTop->p4()).mass() - genAntiTopQuark->mass()) < 1.e+1) ) continue;
    cutFlowTable.update("genAntiTopQuark mass");
    cutFlowHistManager->fillHistograms("genAntiTopQuark mass");

    std::vector<const GenParticle*> genWJetsFromTop;
    double genWJetsFromTop_mass = -1.;
    std::vector<const GenParticle*> genWJetsFromAntiTop;
    double genWJetsFromAntiTop_mass = -1.;
    for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin();
	  it1 != genWJets.end(); ++it1 ) {
      for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1;
	    it2 != genWJets.end(); ++it2 ) {
	if ( ((it1->charge() + it2->charge()) - genWBosonFromTop->charge()) < 1.e-2 ) {
	  if ( genWJetsFromTop_mass == -1. || 
	       std::fabs((it1->p4() + it2->p4()).mass() - genWBosonFromTop->mass()) < std::fabs(genWJetsFromTop_mass - genWBosonFromTop->mass()) ) {
	    genWJetsFromTop.clear();
	    genWJetsFromTop.push_back(&(*it1));
	    genWJetsFromTop.push_back(&(*it2));
	    genWJetsFromTop_mass = (it1->p4() + it2->p4()).mass();
	  }
	}
	if ( ((it1->charge() + it2->charge()) - genWBosonFromAntiTop->charge()) < 1.e-2 ) {
	  if ( genWJetsFromAntiTop_mass == -1. || 
	       std::fabs((it1->p4() + it2->p4()).mass() - genWBosonFromAntiTop->mass()) < std::fabs(genWJetsFromAntiTop_mass - genWBosonFromAntiTop->mass()) ) {
	    genWJetsFromAntiTop.clear();
	    genWJetsFromAntiTop.push_back(&(*it1));
	    genWJetsFromAntiTop.push_back(&(*it2));
	    genWJetsFromAntiTop_mass = (it1->p4() + it2->p4()).mass();
	  }
	}
      }
    }    
    if ( !(genWJetsFromTop.size() == 2 || genWJetsFromAntiTop.size() == 2) ) continue;
    cutFlowTable.update("2 genWJetsFromTop || 2 genWJetsFromAntiTop");
    cutFlowHistManager->fillHistograms("2 genWJetsFromTop || 2 genWJetsFromAntiTop");
    const GenParticle* genWJetFromTop_lead = 0;
    const GenParticle* genWJetFromTop_sublead = 0;
    bool failsWbosonMassVeto_top = false;
    if ( genWJetsFromTop.size() == 2 ) {
      std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
      genWJetFromTop_lead = genWJetsFromTop[0];
      genWJetFromTop_sublead = genWJetsFromTop[1];
      if ( !(std::fabs((genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() - genWBosonFromTop->mass()) < 5.) ) failsWbosonMassVeto_top = true;
    }
    if ( failsWbosonMassVeto_top ) continue; 
    cutFlowTable.update("genWBosonFromTop mass");
    cutFlowHistManager->fillHistograms("genWBosonFromTop mass");
    const GenParticle* genWJetFromAntiTop_lead = 0;
    const GenParticle* genWJetFromAntiTop_sublead = 0;
    bool failsWbosonMassVeto_antiTop = false;
    if ( genWJetsFromAntiTop.size() == 2 ) {
      std::sort(genWJetsFromAntiTop.begin(), genWJetsFromAntiTop.end(), isHigherPt);
      genWJetFromAntiTop_lead = genWJetsFromAntiTop[0];
      genWJetFromAntiTop_sublead = genWJetsFromAntiTop[1];
      if ( !(std::fabs((genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4()).mass() - genWBosonFromAntiTop->mass()) < 5.) ) failsWbosonMassVeto_antiTop = true;
    }
    if ( failsWbosonMassVeto_antiTop ) continue; 
    cutFlowTable.update("genWBosonFromAntiTop mass");
    cutFlowHistManager->fillHistograms("genWBosonFromAntiTop mass");
    
    if ( isDEBUG ) {
      std::cout << "top:" << (*genTopQuark);
      std::cout << " b:" << (*genBJetFromTop);
      std::cout << " W:" << (*genWBosonFromTop);
      if ( genWJetFromTop_lead && genWJetFromTop_sublead ) {
	std::cout << " Wj1:" << (*genWJetFromTop_lead);
	std::cout << " Wj2:" << (*genWJetFromTop_sublead);
      } else {
	std::cout << "(leptonic W decay)" << std::endl;
      }
      std::cout << "anti-top:" << (*genAntiTopQuark);
      std::cout << " b:" << (*genBJetFromAntiTop);
      std::cout << " W:" << (*genWBosonFromAntiTop);
      if ( genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
	std::cout << " Wj1:" << (*genWJetFromAntiTop_lead);
	std::cout << " Wj2:" << (*genWJetFromAntiTop_sublead);
      } else {
	std::cout << "(leptonic W decay)" << std::endl;
      }
      std::cout << std::endl;
    }
    
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= sgn(genWeight);
      evtWeight *= pileupWeight;
    }

    for ( std::vector<const RecoJet*>::const_iterator selBJet = selJets.begin();
	  selBJet != selJets.end(); ++selBJet ) {
      bool selBJet_isFromTop = deltaR((*selBJet)->p4(), genBJetFromTop->p4()) < 0.2;
      bool selBJet_isFromAntiTop = deltaR((*selBJet)->p4(), genBJetFromAntiTop->p4()) < 0.2;
      for ( std::vector<const RecoJet*>::const_iterator selWJet1 = selBJet + 1;
	    selWJet1 != selJets.end(); ++selWJet1 ) {
	bool selWJet1_isFromTop = 
	  (genWJetFromTop_lead        && deltaR((*selWJet1)->p4(), genWJetFromTop_lead->p4())        < 0.2) || 
	  (genWJetFromTop_sublead     && deltaR((*selWJet1)->p4(), genWJetFromTop_sublead->p4())     < 0.2);
	bool selWJet1_isFromAntiTop = 
	  (genWJetFromAntiTop_lead    && deltaR((*selWJet1)->p4(), genWJetFromAntiTop_lead->p4())    < 0.2) || 
	  (genWJetFromAntiTop_sublead && deltaR((*selWJet1)->p4(), genWJetFromAntiTop_sublead->p4()) < 0.2);
	for ( std::vector<const RecoJet*>::const_iterator selWJet2 = selWJet1 + 1;
	      selWJet2 != selJets.end(); ++selWJet2 ) {
	  bool selWJet2_isFromTop = 
  	    (genWJetFromTop_lead        && deltaR((*selWJet2)->p4(), genWJetFromTop_lead->p4())        < 0.2) || 
	    (genWJetFromTop_sublead     && deltaR((*selWJet2)->p4(), genWJetFromTop_sublead->p4())     < 0.2);
	  bool selWJet2_isFromAntiTop = 
	    (genWJetFromAntiTop_lead    && deltaR((*selWJet2)->p4(), genWJetFromAntiTop_lead->p4())    < 0.2) || 
	    (genWJetFromAntiTop_sublead && deltaR((*selWJet2)->p4(), genWJetFromAntiTop_sublead->p4()) < 0.2);

	  double mvaOutput = (*hadTopTagger)(**selBJet, **selWJet1, **selWJet2);
	  const std::map<std::string, double>& mvaInputs = hadTopTagger->mvaInputs();

	  int idxGenMatch_top     = getGenMatch(selBJet_isFromTop, selWJet1_isFromTop, selWJet2_isFromTop);
	  int idxGenMatch_antiTop = getGenMatch(selBJet_isFromAntiTop, selWJet1_isFromAntiTop, selWJet2_isFromAntiTop);

	  if ( idxGenMatch_antiTop != kGen_bWj1Wj2 ) { // CV: don't consider top matching if reconstructed jet triplet is (fully) matched to anti-top
	    assert(mvaInputHistManagers.find(idxGenMatch_top) != mvaInputHistManagers.end());
	    mvaInputHistManagers[idxGenMatch_top]->fillHistograms(mvaInputs, evtWeight);
	    fillWithOverFlow(mvaOutputHistManagers[idxGenMatch_top], mvaOutput, evtWeight);
	    bdt_filler->operator()({ run, lumi, event });
	    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
		  mvaInput != mvaInputs.end(); ++mvaInput ) {
	      bdt_filler->operator()(mvaInput->first, mvaInput->second);
	    }
	    bdt_filler->operator()("b_isGenMatched", selBJet_isFromTop);
	    bdt_filler->operator()("Wj1_isGenMatched", selWJet1_isFromTop);
	    bdt_filler->operator()("Wj2_isGenMatched", selWJet2_isFromTop);
	    bdt_filler->operator()("bWj1Wj2_isGenMatched", selBJet_isFromTop && selWJet1_isFromTop && selWJet2_isFromTop);
	    bdt_filler->fill();
	  }
	  if ( idxGenMatch_top != kGen_bWj1Wj2 ) { // CV: don't consider anti-top matching if reconstructed jet triplet is (fully) matched to top
	    assert(mvaInputHistManagers.find(idxGenMatch_antiTop) != mvaInputHistManagers.end());
	    mvaInputHistManagers[idxGenMatch_antiTop]->fillHistograms(mvaInputs, evtWeight);
	    fillWithOverFlow(mvaOutputHistManagers[idxGenMatch_antiTop], mvaOutput, evtWeight);
	    bdt_filler->operator()({ run, lumi, event });
	    for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
		  mvaInput != mvaInputs.end(); ++mvaInput ) {
	      bdt_filler->operator()(mvaInput->first, mvaInput->second);
	    }
	    bdt_filler->operator()("b_isGenMatched", selBJet_isFromAntiTop);
	    bdt_filler->operator()("Wj1_isGenMatched", selWJet1_isFromAntiTop);
	    bdt_filler->operator()("Wj2_isGenMatched", selWJet2_isFromAntiTop);
	    bdt_filler->operator()("bWj1Wj2_isGenMatched", selBJet_isFromAntiTop && selWJet1_isFromAntiTop && selWJet2_isFromAntiTop);
	    bdt_filler->fill();
	  }
	}
      }
    }
        
    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;
  std::cout << std::endl;
  
  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  delete run_lumi_eventSelector;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;

  delete genTopQuarkReader;
  delete genBJetReader;
  delete genWBosonReader;
  delete genWJetReader;

  delete hadTopTagger;

  clock.Show("analyze_hadTopTagger");

  return EXIT_SUCCESS;
}

