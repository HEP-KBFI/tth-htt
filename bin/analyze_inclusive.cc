#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing MVA input variables
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h" // SyncNtupleManager

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet
#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <TBenchmark.h> // TBenchmark
#include <TError.h> // gErrorAbortLevel, kError

const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

/**
 * @brief Run inclusive selection for synchronization
 */
int
main(int argc,
     char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_inclusive>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  }

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_inclusive");
  const std::string treeName    = cfg_analyze.getParameter<std::string>("treeName");
  const std::string era_string  = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if(era_string == "2017")
  {
    era = kEra_2017;
  }
  else
  {
    throw cmsException(argv[0])
      << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";
  }

  const std::string hadTauSelection_WP = cfg_analyze.getParameter<std::string>("hadTauSelection_WP");

  const std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isSignal = ( process_string == "signal" ) ? true : false;
  const bool isMC = cfg_analyze.getParameter<bool>("isMC");
  const bool isMC_tH = ( process_string == "tH" ) ? true : false;

  const bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");

  const std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  const std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  const bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  const std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << '\n';
  RunLumiEventSelector * run_lumi_eventSelector = nullptr;
  if(! selEventsFileName_input.empty())
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const fwlite::InputSource inputFiles(cfg);
  const int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  const unsigned reportEvery = inputFiles.reportAfter();

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- prepare sync Ntuple
  SyncNtupleManager * snm = nullptr;
  const edm::ParameterSet syncNtuple_cfg = cfg_analyze.getParameter<edm::ParameterSet>("syncNtuple");
  const std::string syncNtuple_tree = syncNtuple_cfg.getParameter<std::string>("tree");
  const std::string syncNtuple_output = syncNtuple_cfg.getParameter<std::string>("output");
  if(! syncNtuple_tree.empty() && ! syncNtuple_output.empty())
  {
    snm = new SyncNtupleManager(syncNtuple_output, syncNtuple_tree);
    snm->initializeBranches();
  }

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

//--- declare particle collections
  const bool readGenObjects = isMC && ! redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  muonReader->set_HIP_mitigation(use_HIP_mitigation_mediumMuonId);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(RecoHadTauReader::kHadTauPt_central);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if(hadTauSelection_WP == "dR03mvaVLoose" ||
     hadTauSelection_WP == "dR03mvaVVLoose" )
  {
    preselHadTauSelector.set(hadTauSelection_WP);
  }
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader * jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setJetPt_central_or_shift(RecoJetReader::kJetPt_central);
  jetReader->setBranchName_BtagWeight(kBtag_central);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);

//--- declare missing transverse energy
  RecoMEtReader * metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(RecoMEtReader::kMEt_central);
  inputTree -> registerReader(metReader);

  int analyzedEntries = 0;
  int selectedEntries = 0;

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;

    if(isDEBUG)
    {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    const std::vector<RecoMuon> muons = muonReader->read();
    const std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    const std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon *> preselMuons = preselMuonSelector(cleanedMuons);
    std::sort(preselMuons.begin(), preselMuons.end(), isHigherPt);
    if(isDEBUG)
    {
      for(std::size_t idxPreselMuon = 0; idxPreselMuon < preselMuons.size(); ++idxPreselMuon)
      {
        std::cout << "preselMuon #" << idxPreselMuon << ":\n" << (*preselMuons[idxPreselMuon]);
      }
    }

    const std::vector<RecoElectron> electrons = electronReader->read();
    const std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    const std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron *> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::sort(preselElectrons.begin(), preselElectrons.end(), isHigherPt);
    if(isDEBUG)
    {
      for(std::size_t idxPreselElectron = 0; idxPreselElectron < preselElectrons.size(); ++idxPreselElectron)
      {
        std::cout << "preselElectron #" << idxPreselElectron << ":\n" << (*preselElectrons[idxPreselElectron]);
      }
    }

    const std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    const std::vector<const RecoHadTau *> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau *> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::sort(cleanedHadTaus.begin(), cleanedHadTaus.end(), isHigherPt);
    const std::vector<const RecoHadTau *> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    if(isDEBUG)
    {
      for(std::size_t idxPreselHadTau = 0; idxPreselHadTau < preselHadTaus.size(); ++idxPreselHadTau)
      {
        std::cout << "preselHadTau #" << idxPreselHadTau << ":\n" << (*preselHadTaus[idxPreselHadTau]);
      }
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    const std::vector<RecoJet> jets = jetReader->read();
    const std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    if(isDEBUG)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << " (#uncleanedJets = " << jet_ptrs.size() << ")\n";
        for(std::size_t idxJet = 0; idxJet < jet_ptrs.size(); ++idxJet)
        {
          std::cout << "uncleanedJet #" << idxJet << ":\n" << (*jet_ptrs[idxJet]);
        }
      }
    }
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, preselElectrons, preselMuons); // OK?
    std::sort(cleanedJets.begin(), cleanedJets.end(), isHigherPt);
    const std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);

//--- compute MHT and linear MET discriminant (met_LD)
    const RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons);
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherPt);
    const Particle::LorentzVector mht_p4 = compMHT(preselLeptons, preselHadTaus, selJets); // OK?
    const double met_LD = compMEt_LD(met.p4(), mht_p4);

    if(snm)
    {
      const double ht          = compHT(preselLeptons, preselHadTaus, selJets);
      const double MT_met_lep0 = comp_MT_met_lep1(preselLepton_lead->cone_p4(),    met.pt(), met.phi());
      const double MT_met_lep1 = comp_MT_met_lep2(selLepton_sublead->cone_p4(), met.pt(), met.phi());
      const double dR_l0tau    = deltaR(selLepton_lead->p4(),    selHadTau->p4());
      const double dR_l1tau    = deltaR(selLepton_sublead->p4(), selHadTau->p4());
      const double dR_leps     = deltaR(selLepton_lead->p4(),    selLepton_sublead->p4());
      const double max_dr_jet  = comp_max_dr_jet(selJets);

      snm->read(eventInfo);
      snm->read(preselMuons,     {}, {}, {});
      snm->read(preselElectrons, {}, {}, {});
      snm->read(preselHadTaus);
      snm->read(selJets);

      //snm->read({}); // no triggers read here
      //snm->read(isGenMatched, selBJets_medium.size(), selBJets_loose.size());

      // if there's at least one lepton in the event
      if(preselLeptons.size())
      {
        //
      }

      snm->read(met.pt(),                               FloatVariableType::PFMET);
      snm->read(met.phi(),                              FloatVariableType::PFMETphi);
      snm->read(mht_p4.pt(),                            FloatVariableType::MHT);
      snm->read(met_LD,                                 FloatVariableType::metLD);

      snm->read(lep1_conePt,                            FloatVariableType::lep0_conept);
      snm->read(lep2_conePt,                            FloatVariableType::lep1_conept);
      snm->read(mindr_lep1_jet,                         FloatVariableType::mindr_lep0_jet);
      snm->read(mindr_lep2_jet,                         FloatVariableType::mindr_lep1_jet);
      // mindr_lep2_jet not filled
      snm->read(mindr_tau_jet,                          FloatVariableType::mindr_tau_jet);
      snm->read(MT_met_lep0,                            FloatVariableType::MT_met_lep0);
      snm->read(avg_dr_jet,                             FloatVariableType::avg_dr_jet);
      snm->read(mvaOutput_2lss_ttV,                     FloatVariableType::MVA_2lss_ttV);
      snm->read(mvaOutput_2lss_ttbar,                   FloatVariableType::MVA_2lss_ttbar);
      // tt_deltaR not filled
      // tt_mvis not filled
      // tt_pt not filled
      snm->read(max_dr_jet,                             FloatVariableType::max_dr_jet);
      snm->read(ht,                                     FloatVariableType::HT);
      // MVA_1l2tau_ttbar not filled
      // MVA_1l2tau_ttbar_v2 not filled
      // MVA_1l2tau_ttZ_v2 not filled
      // MVA_1l2tau_2Dbin_v2 not filled
      snm->read(mTauTauVis2_sel,                        FloatVariableType::mvis_l1tau);
      snm->read(dR_l0tau,                               FloatVariableType::dR_l0tau);
      snm->read(dR_l1tau,                               FloatVariableType::dR_l1tau);
      // dR_l2tau not filled
      // MT_met_lep2 not filled
      // MVA_3l1tau_ttbar not filled
      // MVA_3l1tau_ttV not filled
      // MVA_3l1tau_2Dbin not filled

      snm->read(weight_fakeRate,                        FloatVariableType::FR_weight);
      snm->read(triggerWeight,                          FloatVariableType::triggerSF_weight);
      snm->read(leptonSF_weight,                        FloatVariableType::leptonSF_weight);
      snm->read(tauSF_weight,                           FloatVariableType::tauSF_weight);
      snm->read(btagWeight,                             FloatVariableType::bTagSF_weight);
      snm->read(eventInfo.pileupWeight,                 FloatVariableType::PU_weight);
      snm->read(boost::math::sign(eventInfo.genWeight), FloatVariableType::MC_weight);

      snm->read(memOutput_ttH,                          FloatVariableType::Integral_ttH);
      snm->read(memOutput_ttZ,                          FloatVariableType::Integral_ttZ);
      snm->read(memOutput_ttZ_Zll,                      FloatVariableType::Integral_ttZ_Zll);
      snm->read(memOutput_tt,                           FloatVariableType::Integral_ttbar);
      snm->read(memOutput_type,                         FloatVariableType::integration_type);
      snm->read(memOutput_LR,                           FloatVariableType::MEM_LR);
      snm->read(dR_leps,                                FloatVariableType::dR_leps);
      snm->read(mTauTauVis1_sel,                        FloatVariableType::mvis_l0tau);
      snm->read(mvaOutput_2lss_1tau_ttbar,              FloatVariableType::MVA_2lSS1tau_noMEM_ttbar);
      snm->read(mvaOutput_2lss_1tau_ttV,                FloatVariableType::MVA_2lSS1tau_noMEM_ttV);
      snm->read(mvaDiscr_2lss_1tau,                     FloatVariableType::MVA_2lSS1tau_noMEM_2Dbin);
      snm->read(mvaOutput_2lss_1tau_ttbar_wMEM,         FloatVariableType::MVA_2lSS1tau_MEM_ttbar);
      snm->read(mvaOutput_2lss_1tau_ttV_wMEM,           FloatVariableType::MVA_2lSS1tau_MEM_ttV);
      snm->read(mvaDiscr_2lss_1tau_wMEM,                FloatVariableType::MVA_2lSS1tau_MEM_2Dbin);

      // lep2_conept not filled
      // lep3_conept not filled
      // mindr_lep4_jet not filled
      snm->read(MT_met_lep1,                            FloatVariableType::MT_met_lep1);
      // MT_met_lep3 not filled
      snm->read(eventInfo.genWeight,                    FloatVariableType::genWeight);

      snm->fill();
    }

    ++selectedEntries;
  }

  if(snm)
  {
    snm->write();
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << "\n\n"
  ;

  delete run_lumi_eventSelector;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;

  delete inputTree;
  delete snm;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
}
