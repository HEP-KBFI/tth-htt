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
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // comp_mindr_lep*_jet(), comp_lep*_conePt(), comp_*()
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // LUMI_*, EVT_*, RUN_*, MET_*_*
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorCutBased.h" // RecoMuonCollectionSelectorCutBased
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonCollectionSelectorMVABased
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtag*
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_*
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager

#include <iostream> // std::cout

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

/**
 * @brief Produce datacard and control plots for 2lss_1tau categories.
 */
int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_SUCCESS;
  }
  std::cout << "<" << argv[0] << ">:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("syncNtuple");

  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string outputTreeName = cfg_analyze.getParameter<std::string>("outputTreeName");
  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const bool debug = cfg_analyze.getParameter<bool>("debug");

//--- declare data-taking period
  const int era = [&era_string, &argv]() -> int
  {
    if     (era_string == "2015") return kEra_2015;
    else if(era_string == "2016") return kEra_2016;
    else
      throw cms::Exception(argv[0])
        << "Invalid configuration parameter 'era' = " << era_string << '\n';
  }();
  const int jetPt_option = RecoJetReader::kJetPt_central;

  const vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  const std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  const vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  const std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  const vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  const std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  const vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  const std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  const vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  const std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);

  const std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_input = "  << selEventsFileName_input  << '\n'
            << "selEventsFileName_output = " << selEventsFileName_output << '\n';

  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << '\n';
  const unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  const std::string outputFileName = outputFile.file();

  TChain* inputTree = new TChain(treeName.data());
  for(const std::string & inputFileName: inputFiles.files())
  {
    std::cout << "input Tree: adding file = " << inputFileName << '\n';
    inputTree -> AddFile(inputFileName.c_str());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception(argv[0]) << "Failed to identify input Tree !!\n";
  }
  
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);

  std::cout << "input Tree contains " << inputTree->GetEntries() << " Entries in "
            << inputTree->GetListOfFiles()->GetEntries() << " files.\n";

//--- declare event-level variables
  RUN_TYPE run;
  inputTree->SetBranchAddress(RUN_KEY, &run);
  LUMI_TYPE lumi;
  inputTree->SetBranchAddress(LUMI_KEY, &lumi);
  EVT_TYPE event;
  inputTree->SetBranchAddress(EVT_KEY, &event);

  hltPaths_setBranchAddresses(inputTree, triggers_1e);
  hltPaths_setBranchAddresses(inputTree, triggers_2e);
  hltPaths_setBranchAddresses(inputTree, triggers_1mu);
  hltPaths_setBranchAddresses(inputTree, triggers_2mu);
  hltPaths_setBranchAddresses(inputTree, triggers_1e1mu);

  MET_PT_TYPE met_pt;
  inputTree->SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  inputTree->SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  inputTree->SetBranchAddress(MET_PHI_KEY, &met_phi);

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorCutBased cutBasedSelector;
  RecoMuonCollectionSelectorMVABased mvaBasedSelector;

  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionCleaner electronCleaner(0.05); // KE: 0.3 -> 0.05
  RecoElectronCollectionSelectorLoose preselElectronSelector(-1, debug);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorCutBased cutBasedElectronSelector;
  RecoElectronCollectionSelectorMVABased mvaBasedElectronSelector;

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, "nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionCleaner hadTauCleaner(0.4); // KE: 0.3 -> 0.4
  RecoHadTauCollectionSelectorLoose hadTauSelector; // KE: Tight -> Loose
  
  RecoJetReader* jetReader = new RecoJetReader(era, "nJet", "Jet");
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight("");
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionCleaner jetCleaner(0.4); // KE: 0.5 -> 0.4
  RecoJetCollectionSelector jetSelector;  

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis
  const std::string mvaFileName_2lss_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_ttV_BDTG.weights.xml";
  const std::vector<std::string> mvaInputVariables_2lss_ttV =
  {
    "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",
    "MT_met_lep1",
    "nJet25_Recl",
    "mindr_lep1_jet",
    "mindr_lep2_jet",
    "LepGood_conePt[iF_Recl[0]]",
    "LepGood_conePt[iF_Recl[1]]"
  };
  const TMVAInterface mva_2lss_ttV(
    mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" }
  );

  const std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  const std::vector<std::string> mvaInputVariables_2lss_ttbar =
  {
    "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",
    "nJet25_Recl",
    "mindr_lep1_jet",
    "mindr_lep2_jet",
    "min(met_pt,400)",
    "avg_dr_jet",
    "MT_met_lep1"
  };
  const TMVAInterface mva_2lss_ttbar(
    mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" }
  );

  std::map<std::string, double> mvaInputs;

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = new std::ofstream(selEventsFileName_output.data(), std::ios::out);

  SyncNtupleManager snm(outputFileName, outputTreeName);
  snm.initializeBranches();
  snm.initializeHLTBranches({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});

  const int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;

  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;    
    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    snm.readRunLumiEvent(run, lumi, event);

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
// CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> cutBasedMuons = cutBasedSelector(preselMuons);
    std::vector<const RecoMuon*> mvaBasedMuons = mvaBasedSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons = preselMuons;
    std::sort(preselMuons.begin(), preselMuons.end(), isHigherPt);
    snm.read(preselMuons, fakeableMuons, cutBasedMuons, mvaBasedMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> cutBasedElectrons = cutBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> mvaBasedElectrons = mvaBasedElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons = preselElectrons;
    std::sort(preselElectrons.begin(), preselElectrons.end(), isHigherPt);
    snm.read(preselElectrons, fakeableElectrons, cutBasedElectrons, mvaBasedElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, selMuons, selElectrons);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(cleanedHadTaus);
    std::sort(selHadTaus.begin(), selHadTaus.end(), isHigherPt);
    snm.read(selHadTaus);
    
//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = [&]()
    {
      if     (era == kEra_2015)
        return jetCleaner(jet_ptrs, selMuons, selElectrons, selHadTaus);
      else if(era == kEra_2016)
        return jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
      else
        throw cms::Exception(argv[0]) << "Invalid era = " << era;
    }();
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::sort(selJets.begin(), selJets.end(), isHigherPt);
    snm.read(selJets);

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    const RecoLepton * const preselLepton_lead    = preselLeptons.size() > 0 ? preselLeptons[0] : 0;
    const RecoLepton * const preselLepton_sublead = preselLeptons.size() > 1 ? preselLeptons[1] : 0;

//--- compute MHT and linear MET discriminant (met_LD)
    LV mht_p4(0,0,0,0);
    for(const RecoJet * & jet: selJets)             mht_p4 += jet -> p4_;
    for(const RecoLepton * & lepton: preselLeptons) mht_p4 += lepton -> p4_;
    for(const RecoHadTau * & hadTau: selHadTaus)    mht_p4 += hadTau -> p4_;
    const LV met_p4(met_pt, met_eta, met_phi, 0.);
    const Double_t met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();

    snm.read(met_pt,      FloatVariableType::PFMET);
    snm.read(met_phi,     FloatVariableType::PFMETphi);
    snm.read(mht_p4.pt(), FloatVariableType::MHT);
    snm.read(met_LD,      FloatVariableType::metLD);
    snm.read({triggers_1e, triggers_1mu, triggers_2e, triggers_2mu, triggers_1e1mu});

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
    if(preselLepton_lead)
    {
      mvaInputs["MT_met_lep1"]                = comp_MT_met_lep1(*preselLepton_lead, met_pt, met_phi);
      mvaInputs["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*preselLepton_lead);
      mvaInputs["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*preselLepton_lead, selJets);
    }
    if(preselLepton_sublead)
    {
      mvaInputs["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*preselLepton_sublead);
      mvaInputs["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*preselLepton_sublead, selJets);
    }
    mvaInputs["nJet25_Recl"]     = comp_n_jet25_recl(selJets);
    mvaInputs["avg_dr_jet"]      = comp_avg_dr_jet(selJets);
    mvaInputs["min(met_pt,400)"] = std::min(met_pt, static_cast<Float_t>(400.));

    if(preselLepton_lead && preselLepton_sublead)
    {
      mvaInputs["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] =
        std::max(std::fabs(preselLepton_lead->eta_), std::fabs(preselLepton_sublead->eta_));
      if(selJets.size() > 1)
      {
        snm.read(mva_2lss_ttV(mvaInputs),   FloatVariableType::mvaOutput_ttV);
        snm.read(mva_2lss_ttbar(mvaInputs), FloatVariableType::mvaOutput_ttbar);
      }
    }
    snm.read(mvaInputs);
    mvaInputs.clear();

    snm.fill();
    (*selEventsFile) << run << ':' << lumi << ':' << event << '\n';
    ++selectedEntries;
  }
  snm.write();
  std::cout << "num. Entries = " << numEntries << "\n analyzed = " << analyzedEntries << '\n'
            << "Wrote file = " << outputFileName << '\n';

  delete run_lumi_eventSelector;
  delete selEventsFile;
  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
}
