#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelectorBtag/Loose
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector

#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonFakeRate.h" // EvtHistManager_LeptonFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector

#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017, getBranchName_bTagWeight()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverflow
#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h" // hltPath_LeptonFakeRate, create_hltPaths_LeptonFakeRate(), hltPaths_LeptonFakeRate_delete()
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin(), getPtBin()
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon

#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles

#include <TRandom3.h> // TRandom3
#include <TBenchmark.h> // TBenchmark
#include <TH1.h> // TH1, TH1D
#include <TMath.h> // TMath::Pi()

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/predicate.hpp> // boost::starts_with(), boost::ends_with()

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

double
comp_mT(const RecoLepton & lepton,
        double met_pt,
        double met_phi)
{
  return std::sqrt(2. * lepton.pt() * met_pt * (1. - std::cos(lepton.phi() - met_phi)));
}

double
comp_mT_fix(const RecoLepton & lepton,
            double met_pt,
            double met_phi)
{
  const double pt_fix = 35.;
  return std::sqrt(2. * pt_fix * met_pt * (1. - std::cos(lepton.phi() - met_phi)));
}

//--- define histograms (same histogram manager class used for numerator and denominator)
struct numerator_and_denominatorHistManagers
{
  numerator_and_denominatorHistManagers(const std::string & process,
                                        bool isMC,
                                        const std::string & central_or_shift,
                                        const std::string & dir,
                                        int lepton_type,
                                        double minAbsEta = -1.,
                                        double maxAbsEta = -1.,
                                        double minPt = -1.,
                                        double maxPt = -1.,
                                        const std::string & subdir_suffix = "")
    : process_(process)
    , isMC_(isMC)
    , central_or_shift_(central_or_shift)
    , lepton_type_(lepton_type)
    , minAbsEta_(minAbsEta)
    , maxAbsEta_(maxAbsEta)
    , minPt_(minPt)
    , maxPt_(maxPt)
    , isInclusive_(minAbsEta_ == maxAbsEta_ && minPt_ == maxPt_)
    , electronHistManager_(nullptr)
    , electronHistManager_genHadTau_(nullptr)
    , electronHistManager_genLepton_(nullptr)
    , electronHistManager_genHadTauOrLepton_(nullptr)
    , electronHistManager_genJet_(nullptr)
    , muonHistManager_(nullptr)
    , muonHistManager_genHadTau_(nullptr)
    , muonHistManager_genLepton_(nullptr)
    , muonHistManager_genHadTauOrLepton_(nullptr)
    , muonHistManager_genJet_(nullptr)
    , evtHistManager_LeptonFakeRate_(nullptr)
    , evtHistManager_LeptonFakeRate_genHadTau_(nullptr)
    , evtHistManager_LeptonFakeRate_genLepton_(nullptr)
    , evtHistManager_LeptonFakeRate_genHadTauOrLepton_(nullptr)
    , evtHistManager_LeptonFakeRate_genJet_(nullptr)
  {
    if(isInclusive_)
    {
      // inclusive event selection
      subdir_ = Form("%s/incl", dir.data());
    }
    else
    {
      const std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
      const std::string PtBin  = getPtBin(minPt_, maxPt_);
      subdir_ = Form("%s/%s/%s", dir.data(), etaBin.data(), PtBin.data());
    }
    if(! subdir_suffix.empty())
    {
      subdir_ += Form("_%s", subdir_suffix.data());
    }

    switch(lepton_type_)
    {
      case kElectron: label_ = "e";  break;
      case kMuon:     label_ = "mu"; break;
      default:         assert(0);
    }
    if(! subdir_suffix.empty())
    {
      label_ += Form(" (%s)", subdir_suffix.data());
    }
    label_ += Form(", %1.0f < pT < %1.0f && %1.2f < |eta| < %1.2f", minPt, maxPt, minAbsEta, maxAbsEta);
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

  std::string
  getLabel() const
  {
    return label_;
  }

  void
  bookHistograms(TFileDirectory & dir)
  {
    const std::string process_and_genMatchedHadTau         = process_ + "t";
    const std::string process_and_genMatchedLepton         = process_ + "l";
    const std::string process_and_genMatchedHadTauOrLepton = process_ + "l_plus_t";
    const std::string process_and_genMatchedJet            = process_ + "j";

    const auto mkCfg = [this](const std::string & process) -> edm::ParameterSet
    {
      return makeHistManager_cfg(process, subdir_, central_or_shift_);
    };

    if(lepton_type_ == kElectron)
    {
      electronHistManager_ = new ElectronHistManager(mkCfg(process_));
      electronHistManager_->bookHistograms(dir);
      if(isMC_)
      {
        electronHistManager_genHadTau_ = new ElectronHistManager(mkCfg(process_and_genMatchedHadTau));
        electronHistManager_genHadTau_->bookHistograms(dir);

        electronHistManager_genLepton_ = new ElectronHistManager(mkCfg(process_and_genMatchedLepton));
        electronHistManager_genLepton_->bookHistograms(dir);

        electronHistManager_genHadTauOrLepton_ = new ElectronHistManager(mkCfg(process_and_genMatchedHadTauOrLepton));
        electronHistManager_genHadTauOrLepton_->bookHistograms(dir);

        electronHistManager_genJet_ = new ElectronHistManager(mkCfg(process_and_genMatchedJet));
        electronHistManager_genJet_->bookHistograms(dir);
      }
    }
    else if(lepton_type_ == kMuon)
    {
      muonHistManager_ = new MuonHistManager(mkCfg(process_));
      muonHistManager_->bookHistograms(dir);
      if(isMC_)
      {
        muonHistManager_genHadTau_ = new MuonHistManager(mkCfg(process_and_genMatchedHadTau));
        muonHistManager_genHadTau_->bookHistograms(dir);

        muonHistManager_genLepton_ = new MuonHistManager(mkCfg(process_and_genMatchedLepton));
        muonHistManager_genLepton_->bookHistograms(dir);

        muonHistManager_genHadTauOrLepton_ = new MuonHistManager(mkCfg(process_and_genMatchedHadTauOrLepton));
        muonHistManager_genHadTauOrLepton_->bookHistograms(dir);

        muonHistManager_genJet_ = new MuonHistManager(mkCfg(process_and_genMatchedJet));
        muonHistManager_genJet_->bookHistograms(dir);
      }
    }
    else
    {
      assert(0);
    }

    evtHistManager_LeptonFakeRate_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_));
    evtHistManager_LeptonFakeRate_->bookHistograms(dir);

    if(isMC_)
    {
      evtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedHadTau));
      evtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

      evtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedLepton));
      evtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

      evtHistManager_LeptonFakeRate_genHadTauOrLepton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedHadTauOrLepton));
      evtHistManager_LeptonFakeRate_genHadTauOrLepton_->bookHistograms(dir);

      evtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedJet));
      evtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);
    }
  }

  void
  fillHistograms(const RecoLepton & lepton,
                 double met,
                 double mT,
                 double mT_fix,
                 double evtWeight,
                 cutFlowTableType * cutFlowTable = nullptr)
  {
    const bool performFill = isInclusive_ || (
      lepton.absEta() >= minAbsEta_ && lepton.absEta() < maxAbsEta_  &&
      lepton.cone_pt() >= minPt_    && lepton.cone_pt() < maxPt_
    );

    if(performFill)
    {
      if(lepton_type_ == kElectron)
      {
        const RecoElectron * const electron_ptr = dynamic_cast<const RecoElectron *>(&lepton);
        assert(electron_ptr);
        const RecoElectron & electron = *electron_ptr;

        electronHistManager_->fillHistograms(electron, evtWeight);
        if(isMC_)
        {
          if(electron.genHadTau())                         electronHistManager_genHadTau_->fillHistograms(electron, evtWeight);
          if(                        electron.genLepton()) electronHistManager_genLepton_->fillHistograms(electron, evtWeight);
          if(electron.genHadTau() || electron.genLepton()) electronHistManager_genHadTauOrLepton_->fillHistograms(electron, evtWeight);
          else                                             electronHistManager_genJet_->fillHistograms(electron, evtWeight);
        }
      }
      else if(lepton_type_ == kMuon)
      {
        const RecoMuon * const muon_ptr = dynamic_cast<const RecoMuon *>(&lepton);
        assert(muon_ptr);
        const RecoMuon & muon = *muon_ptr;

        muonHistManager_->fillHistograms(muon, evtWeight);
        if(isMC_)
        {
          if(muon.genHadTau()                    ) muonHistManager_genHadTau_->fillHistograms(muon, evtWeight);
          if(                    muon.genLepton()) muonHistManager_genLepton_->fillHistograms(muon, evtWeight);
          if(muon.genHadTau() || muon.genLepton()) muonHistManager_genHadTauOrLepton_->fillHistograms(muon, evtWeight);
          else                                     muonHistManager_genJet_->fillHistograms(muon, evtWeight);
        }
      }
      else
      {
        assert(0);
      }

      evtHistManager_LeptonFakeRate_->fillHistograms(met, mT, mT_fix, evtWeight);
      if(isMC_)
      {
        if(lepton.genHadTau())                       evtHistManager_LeptonFakeRate_genHadTau_->fillHistograms(met, mT, mT_fix, evtWeight);
        if(                      lepton.genLepton()) evtHistManager_LeptonFakeRate_genLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
        if(lepton.genHadTau() || lepton.genLepton()) evtHistManager_LeptonFakeRate_genHadTauOrLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
        else                                         evtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT, mT_fix, evtWeight);
      }

      if(cutFlowTable)
      {
        cutFlowTable->update(label_, evtWeight);
      }
    }
  }

private:
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

  ElectronHistManager * electronHistManager_;
  ElectronHistManager * electronHistManager_genHadTau_;
  ElectronHistManager * electronHistManager_genLepton_;
  ElectronHistManager * electronHistManager_genHadTauOrLepton_;
  ElectronHistManager * electronHistManager_genJet_;

  MuonHistManager * muonHistManager_;
  MuonHistManager * muonHistManager_genHadTau_;
  MuonHistManager * muonHistManager_genLepton_;
  MuonHistManager * muonHistManager_genHadTauOrLepton_;
  MuonHistManager * muonHistManager_genJet_;

  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genJet_;
};

void
fillHistograms(std::vector<numerator_and_denominatorHistManagers *> & histograms,
               const RecoLepton & lepton,
               double met_pt,
               double mT,
               double mT_fix,
               double evtWeight_LepJetPair,
               cutFlowTableType * cutFlowTable = nullptr)
{
  for(numerator_and_denominatorHistManagers * histogram: histograms)
  {
    histogram->fillHistograms(lepton, met_pt, mT, mT_fix, evtWeight_LepJetPair, cutFlowTable);
  }
}

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       const std::string & cut)
{
  // do not increase event counts in cut-flow table, just register cut
  cutFlowTable.update(cut, -1.);
}

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       std::vector<numerator_and_denominatorHistManagers *> & histograms)
{
  for(const numerator_and_denominatorHistManagers * const histogram: histograms)
  {
    initializeCutFlowTable(cutFlowTable, histogram->getLabel());
  }
}

int
main(int argc,
     char ** argv)
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_LeptonFakeRate>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- initialize RNG
  TRandom3 rand(12345);

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1];
  }

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_LeptonFakeRate");
  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isSignal = process_string == "signal" ? true : false;

  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);
  const bool isMC    = cfg_analyze.getParameter<bool>("isMC");
  const bool isMC_tH = process_string == "tH" ? true : false;

  const std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  const double lumiScale          = process_string != "data_obs" ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  const bool apply_genWeight      = cfg_analyze.getParameter<bool>("apply_genWeight");
  const bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  const bool redoGenMatching      = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool readGenObjects       = isMC && ! redoGenMatching;
  const bool isDEBUG              = cfg_analyze.exists("isDEBUG") ? cfg_analyze.getParameter<bool>("isDEBUG") : false;

  const bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId");
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << '\n';

  const bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  const bool use_triggers_2e  = cfg_analyze.getParameter<bool>("use_triggers_2e");
  const bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  const bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");

  const edm::VParameterSet cfg_triggers_e = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e");
  std::vector<hltPath_LeptonFakeRate *> triggers_e;
  for(const edm::ParameterSet & cfg_trigger: cfg_triggers_e)
  {
    const vstring trigger_paths = cfg_trigger.getParameter<vstring>("path");
    const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths, cfg_trigger);
    triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end());
  }

  const edm::VParameterSet cfg_triggers_mu = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu");
  std::vector<hltPath_LeptonFakeRate *> triggers_mu;
  for(const edm::ParameterSet & cfg_trigger: cfg_triggers_mu)
  {
    const vstring trigger_paths = cfg_trigger.getParameter<vstring>("path");
    const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate(trigger_paths, cfg_trigger);
    triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end());
  }

  const vdouble etaBins_e  = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  const vdouble ptBins_e   = cfg_analyze.getParameter<vdouble>("ptBins_e");
  const vdouble etaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  const vdouble ptBins_mu  = cfg_analyze.getParameter<vdouble>("ptBins_mu");

  const double minPt_e  = cfg_analyze.getParameter<double>("minPt_e");
  const double minPt_mu = cfg_analyze.getParameter<double>("minPt_mu");

  const std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_jets      = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_analyze.getParameter<std::string>("branchName_met");

  const std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  const std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genJets    = cfg_analyze.getParameter<std::string>("branchName_genJets");

  const edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  const MEtFilterSelector metFilterSelector(cfgMEtFilter);

  const std::string selEventsFileName_input = cfg_analyze.exists("selEventsFileName_input") ?
                                              cfg_analyze.getParameter<std::string>("selEventsFileName_input") : ""
  ;
  std::cout << "selEventsFileName_input = '" << selEventsFileName_input << "'\n";
  RunLumiEventSelector * run_lumi_eventSelector = nullptr;
  if(! selEventsFileName_input.empty())
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator",     ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  std::string jet_btagWeight_branch;
  if(isMC)
  {
    switch(era)
    {
      case kEra_2017: jet_btagWeight_branch = "Jet_btagSF_csvv2"; break;
      default:        assert(0);
    }
  }

  int jetPt_option    = RecoJetReader::kJetPt_central;
  int met_option      = RecoMEtReader::kMEt_central;
  int lheScale_option = kLHE_scale_central;

  if(isMC && central_or_shift != "central")
  {
    enum { kUndefined, kUp, kDown };
    int shiftUp_or_Down = kUndefined;
    if     (boost::ends_with(central_or_shift, "Up")  ) shiftUp_or_Down = kUp;
    else if(boost::ends_with(central_or_shift, "Down")) shiftUp_or_Down = kDown;
    else throw cmsException(argv[0])
           << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift;

    if(boost::starts_with(central_or_shift, "CMS_ttHl_btag"))
    {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
    }
    else if(boost::starts_with(central_or_shift, "CMS_ttHl_JES"))
    {
      jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      switch(shiftUp_or_Down)
      {
        case kUp:
        {
          jetPt_option = RecoJetReader::kJetPt_jecUp;
          met_option   = RecoMEtReader::kMEt_shifted_JetEnUp;
          break;
        }
        case kDown:
        {
          jetPt_option = RecoJetReader::kJetPt_jecDown;
          met_option   = RecoMEtReader::kMEt_shifted_JetEnDown;
          break;
        }
        default: assert(0);
      }
    }
    else if(boost::starts_with(central_or_shift, "CMS_ttHl_JER"))
    {
      switch(shiftUp_or_Down)
      {
        case kUp:   met_option = RecoMEtReader::kMEt_shifted_JetResUp;   break;
        case kDown: met_option = RecoMEtReader::kMEt_shifted_JetResDown; break;
        default:    assert(0);
      }
    }
    else if(boost::starts_with(central_or_shift, "CMS_ttHl_UnclusteredEn"))
    {
      switch(shiftUp_or_Down)
      {
        case kUp:   met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnUp;   break;
        case kDown: met_option = RecoMEtReader::kMEt_shifted_UnclusteredEnDown; break;
        default:    assert(0);
      }
    }
    else if(boost::starts_with(central_or_shift, "CMS_ttHl_thu_shape"))
    {
      if     (boost::ends_with(central_or_shift, "x1Down")) lheScale_option = kLHE_scale_xDown;
      else if(boost::ends_with(central_or_shift, "x1Up"  )) lheScale_option = kLHE_scale_xUp;
      else if(boost::ends_with(central_or_shift, "y1Down")) lheScale_option = kLHE_scale_yDown;
      else if(boost::ends_with(central_or_shift, "y1Up"  )) lheScale_option = kLHE_scale_yUp;
      else                                                  assert(0);
    }
    else if(! (boost::starts_with(central_or_shift, "CMS_ttHl_FRet") ||
               boost::starts_with(central_or_shift, "CMS_ttHl_FRmt") ||
               boost::starts_with(central_or_shift, "CMS_ttHl_tauES")))
    {
      throw cmsException(argv[0])
        << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift;
    }
  }

  fwlite::InputSource inputFiles(cfg);
  const int maxEvents        = inputFiles.maxEvents();
  const unsigned reportEvery = inputFiles.reportAfter();

  TTreeWrapper * inputTree = new TTreeWrapper(treeName, inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s).\n";

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  for(const std::vector<hltPath_LeptonFakeRate *> hltPaths: { triggers_e, triggers_mu })
  {
    inputTree->registerReader(hltPaths);
  }

//--- declare particle collections
  RecoMuonReader * muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  muonReader->set_HIP_mitigation(use_HIP_mitigation_mediumMuonId);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);

  RecoElectronReader * electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  fakeableElectronSelector.enable_offline_e_trigger_cuts();

  RecoJetReader * jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner_dR04(0.4);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7); // Christian's suggestion
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);

//--- declare missing transverse energy
  RecoMEtReader * metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

//--- declare MET filter
  MEtFilter metFilter;
  MEtFilterReader * metFilterReader = new MEtFilterReader(&metFilter);
  inputTree->registerReader(metFilterReader);

// --- Setting up the Met Filter Hist Manager ----
  const edm::ParameterSet metFilterHistManagerCfg = makeHistManager_cfg(
    process_string, "LeptonFakeRate/met_filters", central_or_shift
  );
  MEtFilterHistManager * metFilterHistManager = new MEtFilterHistManager(metFilterHistManagerCfg);
  metFilterHistManager->bookHistograms(fs);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenJetReader * genJetReader       = nullptr;
  LHEInfoReader * lheInfoReader     = nullptr;
  if(isMC)
  {
    if(! readGenObjects)
    {
      if(! branchName_genLeptons.empty())
      {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree->registerReader(genLeptonReader);
      }
      if(! branchName_genHadTaus.empty())
      {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree->registerReader(genHadTauReader);
      }
      if(! branchName_genJets.empty())
      {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree->registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader();
    inputTree->registerReader(lheInfoReader);
  }

  const auto get_num_den_hist_managers =
    [&process_string, isMC, &central_or_shift](const std::string & dir,
                                               int lepton_type,
                                               double minAbsEta = -1.,
                                               double maxAbsEta = -1.,
                                               double minPt = -1.,
                                               double maxPt = -1.,
                                               const std::string & subdir_suffix = "")
    -> numerator_and_denominatorHistManagers * const
  {
    return new numerator_and_denominatorHistManagers(
      process_string, isMC, central_or_shift, Form("LeptonFakeRate/%s", dir.data()),
      lepton_type, minAbsEta, maxAbsEta, minPt, maxPt, subdir_suffix
    );
  };

//--- book histograms for electron numerator and denominator
  auto histograms_e_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/electrons_tight", kElectron);
  histograms_e_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/electrons_fakeable", kElectron);
  histograms_e_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/electrons_tight", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/electrons_fakeable", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_afterCuts;
  const int numEtaBins_e = etaBins_e.size() - 1;
  const int numPtBins_e  = ptBins_e.size()  - 1;

  for(int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e)
  {
    const double minAbsEta_e = std::abs(etaBins_e[idxEtaBin_e]);
    const double maxAbsEta_e = std::abs(etaBins_e[idxEtaBin_e + 1]);

    for(int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e)
    {
      const double minPt_e = ptBins_e[idxPtBin_e];
      const double maxPt_e = ptBins_e[idxPtBin_e + 1];

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_e_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_e_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_e_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_e_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book histograms for muon numerator and denominator
  auto histograms_mu_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/muons_tight", kMuon);
  histograms_mu_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/muons_fakeable", kMuon);
  histograms_mu_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/muons_tight", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/muons_fakeable", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_afterCuts;
  const int numEtaBins_mu = etaBins_mu.size() - 1;
  const int numPtBins_mu  = ptBins_mu.size()  - 1;

  for(int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu)
  {
    const double minAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu]);
    const double maxAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu + 1]);

    for(int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu)
    {
      const double minPt_mu = ptBins_mu[idxPtBin_mu];
      const double maxPt_mu = ptBins_mu[idxPtBin_mu + 1];

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book generator-level histograms for MC
  GenEvtHistManager * genEvtHistManager_beforeCuts = nullptr;
  GenEvtHistManager * genEvtHistManager_afterCuts  = nullptr;
  LHEInfoHistManager * lheInfoHistManager          = nullptr;
  if(isMC)
  {
    const auto getHistManagerCfg = [&process_string, &central_or_shift](const std::string & dir)
      -> edm::ParameterSet
    {
      return makeHistManager_cfg(process_string, Form("LeptonFakeRate/%s", dir.data()), central_or_shift);
    };
    genEvtHistManager_beforeCuts = new GenEvtHistManager(getHistManagerCfg("gen_unbiased/genEvt"));
    genEvtHistManager_beforeCuts->bookHistograms(fs);

    genEvtHistManager_afterCuts = new GenEvtHistManager(getHistManagerCfg("gen_sel/genEvt"));
    genEvtHistManager_afterCuts->bookHistograms(fs);

    lheInfoHistManager = new LHEInfoHistManager(getHistManagerCfg("gen_sel/lheInfo"));
    lheInfoHistManager->bookHistograms(fs);
  }

//--- book additional event level histograms
  TH1 * histogram_met_pt  = fs.make<TH1D>("met_pt",  "met_pt",   40, 0., 200.);
  TH1 * histogram_met_phi = fs.make<TH1D>("met_phi", "met_phi",  36, -TMath::Pi(), +TMath::Pi());
  TH1 * histogram_rnd_e   = fs.make<TH1D>("rnd_e",   "rnd_e",   100, 0.,   1.);
  TH1 * histogram_rnd_mu  = fs.make<TH1D>("rnd_mu",  "rnd_mu",  100, 0.,   1.);

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1 * histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1 * histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

  cutFlowTableType cutFlowTable_e(isDEBUG);
  initializeCutFlowTable(cutFlowTable_e, ">= 1 fakeable electron");
  initializeCutFlowTable(cutFlowTable_e, "MEt filter");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_afterCuts);

  cutFlowTableType cutFlowTable_mu(isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu, ">= 1 fakeable muon");
  initializeCutFlowTable(cutFlowTable_mu, "MEt filter");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, "mT_fix(muon, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_afterCuts);

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1) << " ("
                << eventInfo << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if(isDEBUG)
    {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
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

//--- build collections of generator level particles (before any cuts are applied,
//    to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if(isMC && fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader)
      {
        genHadTaus = genHadTauReader->read();
      }
      if(genJetReader)
      {
        genJets = genJetReader->read();
      }
    }

//--- fill generator level histograms (before cuts)
    if(isMC)
    {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon *> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron *> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet *> cleanedJets_dR04 = jetCleaner_dR04(jet_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoJet *> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);
    std::vector<const RecoJet *> cleanedJets_dR07 = jetCleaner_dR07(jet_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoJet *> selJets_dR07 = jetSelector(cleanedJets_dR07);

    const RecoMEt met = metReader->read();

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if(isMC && redoGenMatching && ! fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader)
      {
        genHadTaus = genHadTauReader->read();
      }
      if(genJetReader)
      {
        genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if(isMC && redoGenMatching)
    {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch   (preselMuons, genJets,    0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenJetMatch   (preselElectrons, genJets,    0.2);

      jetGenMatcher.addGenLeptonMatch(selJets_dR07, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets_dR07, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch   (selJets_dR07, genJets,    0.2);
    }

    if(isMC)
    {
      lheInfoReader->read();
    }

//--- require exactly one fakeable lepton
    if((fakeableElectrons.size() + fakeableMuons.size()) != 1)
    {
      continue;
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if(isMC)
    {
      evtWeight *= lumiScale;
      evtWeight *= eventInfo.pileupWeight;

      if(apply_genWeight) evtWeight *= boost::math::sign(eventInfo.genWeight);
      if(isMC_tH)         evtWeight *= eventInfo.genWeight_tH;

      switch(lheScale_option)
      {
        case kLHE_scale_central: break;
        case kLHE_scale_xDown:   evtWeight *= lheInfoReader->getWeight_scale_xDown(); break;
        case kLHE_scale_xUp:     evtWeight *= lheInfoReader->getWeight_scale_xUp();   break;
        case kLHE_scale_yDown:   evtWeight *= lheInfoReader->getWeight_scale_yDown(); break;
        case kLHE_scale_yUp:     evtWeight *= lheInfoReader->getWeight_scale_yUp();   break;
        default:                 assert(0);
      }

      double btagWeight = 1.;
      for(const RecoJet * const jet: selJets_dR07)
      {
        btagWeight *= jet->BtagWeight();
      }
      evtWeight *= btagWeight;

      if(isDEBUG)
      {
        if(apply_genWeight)
        {
          std::cout << "genWeight    = " << boost::math::sign(eventInfo.genWeight) << '\n';
        }
        std::cout << "lumiScale    = " << lumiScale              << "\n"
                     "pileupWeight = " << eventInfo.pileupWeight << "\n"
                     "btagWeight   = " << btagWeight             << '\n'
        ;
      }
    }

    if(fakeableElectrons.size() >= 1) cutFlowTable_e.update (">= 1 fakeable electron", evtWeight);
    if(fakeableMuons.size()     >= 1) cutFlowTable_mu.update(">= 1 fakeable muon",     evtWeight);

    metFilterHistManager->fillHistograms(metFilter, evtWeight);

    if(! metFilterSelector(metFilter))
    {
      continue;
    }
    cutFlowTable_e.update ("MEt filter", evtWeight);
    cutFlowTable_mu.update("MEt filter", evtWeight);

    // set to true if at least one electron+jet or one muon+jet combination passes trigger requirements
    bool isGoodLeptonJetPair = false;

//--- fill electron histograms (numerator and denominator)
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_e)
    {
      if(! (hltPath_iter->getValue() >= 1))
      {
        continue; // require trigger to fire
      }

      if((use_triggers_1e && hltPath_iter->is_trigger_1e()) ||
         (use_triggers_2e && hltPath_iter->is_trigger_2e())  )
      {
        for(const RecoElectron * const fakeableElectron_ptr: fakeableElectrons)
        {
          const RecoElectron & fakeableElectron = *fakeableElectron_ptr;
          if(! (fakeableElectron.cone_pt() > minPt_e))
          {
            continue;
          }

          bool isGoodElectronJetPair = false;
          for(const RecoJet * selJet: selJets_dR07)
          {
            if(deltaR(fakeableElectron.p4(), selJet->p4()) < 0.7)
            {
              continue;
            }

            if(fakeableElectron.cone_pt() >= hltPath_iter->getMinPt() &&
               fakeableElectron.cone_pt()  < hltPath_iter->getMaxPt() &&
               selJet->pt()                > hltPath_iter->getMinJetPt())
            {
              isGoodElectronJetPair = true;
            }
          }
          if(! isGoodElectronJetPair)
          {
            continue;
          }

          cutFlowTable_e.update("electron+jet pair passing trigger bit", evtWeight);
          std::cout << *hltPath_iter;

          const double mT     = comp_mT    (fakeableElectron, met.pt(), met.phi());
          const double mT_fix = comp_mT_fix(fakeableElectron, met.pt(), met.phi());

          double evtWeight_LepJetPair = evtWeight; // copying evtWeight
          if(isMC)
          {
            if(hltPath_iter->getPrescale_rand_mc() > 1.)
            {
              // get uniformly distributed random number between 0 and 1
              const double u = rand.Rndm();
              fillWithOverFlow(histogram_rnd_e, u, 1.);

              if(u > (1. / hltPath_iter->getPrescale_rand_mc()))
              {
                continue;
              }
              evtWeight_LepJetPair *= hltPath_iter->getPrescale_rand_mc() / hltPath_iter->getPrescale();
            }
            else
            {
              evtWeight_LepJetPair *= 1. / hltPath_iter->getPrescale();
            }
          }

          cutFlowTable_e.update("electron+jet pair passing trigger bit && prescale", evtWeight_LepJetPair);

          isGoodLeptonJetPair = true;
          numerator_and_denominatorHistManagers * histograms_incl_beforeCuts = nullptr;
          numerator_and_denominatorHistManagers * histograms_incl_afterCuts  = nullptr;
          std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts = nullptr;
          std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts  = nullptr;
          if(fakeableElectron.isTight())
          {
            // electron enters numerator
            histograms_incl_beforeCuts = histograms_e_numerator_incl_beforeCuts;
            histograms_incl_afterCuts  = histograms_e_numerator_incl_afterCuts;
            histograms_binned_beforeCuts = &histograms_e_numerator_binned_beforeCuts;
            histograms_binned_afterCuts  = &histograms_e_numerator_binned_afterCuts;
          }
          else if(fakeableElectron.isFakeable())
          {
            // electron enters denominator (fakeable but not tight)
            histograms_incl_beforeCuts = histograms_e_denominator_incl_beforeCuts;
            histograms_incl_afterCuts  = histograms_e_denominator_incl_afterCuts;
            histograms_binned_beforeCuts = &histograms_e_denominator_binned_beforeCuts;
            histograms_binned_afterCuts  = &histograms_e_denominator_binned_afterCuts;
          }
          else
          {
            assert(0);
          }

          histograms_incl_beforeCuts->fillHistograms(fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
          fillHistograms(
            *histograms_binned_beforeCuts, fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e
          );

          if(mT_fix < 15.)
          {
            cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeight_LepJetPair);

            histograms_incl_afterCuts->fillHistograms(fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
            fillHistograms(
              *histograms_binned_afterCuts, fakeableElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e
            );
          }
        } // fakeableElectron
      } // 1e || 2e
    } // hltPath_iter in triggers_e

//--- fill muon histograms (numerator and denominator)
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_mu)
    {
      if(! (hltPath_iter->getValue() >= 1))
      {
        continue; // require trigger to fire
      }

      if((use_triggers_1mu && hltPath_iter->is_trigger_1mu()) ||
         (use_triggers_2mu && hltPath_iter->is_trigger_2mu())  )
      {
        for(const RecoMuon * fakeableMuon_ptr: fakeableMuons)
        {
          const RecoMuon & fakeableMuon = *fakeableMuon_ptr;
          if(! (fakeableMuon.cone_pt() > minPt_mu))
          {
            continue;
          }

          bool isGoodMuonJetPair = false;
          for(const RecoJet * const selJet: selJets_dR07)
          {
            if(deltaR(fakeableMuon.p4(), selJet->p4()) < 0.7)
            {
              continue;
            }

            if((fakeableMuon.cone_pt() < 30. && selBJets_loose_dR04.size() != 0) ||
               fakeableMuon.cone_pt() >= 30.                                      )
            {
              if(fakeableMuon.cone_pt() >= hltPath_iter->getMinPt() &&
                 fakeableMuon.cone_pt()  < hltPath_iter->getMaxPt() &&
                 selJet->pt()            > hltPath_iter->getMinJetPt())
              {
                isGoodMuonJetPair = true;
              }
            }
          }
          if(! isGoodMuonJetPair)
          {
            continue;
          }

          cutFlowTable_mu.update("muon+jet pair passing trigger bit", evtWeight);
          std::cout << *hltPath_iter;

          const double mT     = comp_mT    (fakeableMuon, met.pt(), met.phi());
          const double mT_fix = comp_mT_fix(fakeableMuon, met.pt(), met.phi());

          double evtWeight_LepJetPair = evtWeight; // copying evtWeight
          if(isMC)
          {
            if(hltPath_iter->getPrescale_rand_mc() > 1.)
            {
              // get uniformly distributed random number between 0 and 1
              const double u = rand.Rndm();
              fillWithOverFlow(histogram_rnd_mu, u, 1.);

              if(u > (1. / hltPath_iter->getPrescale_rand_mc()))
              {
                continue;
              }
              evtWeight_LepJetPair *= hltPath_iter->getPrescale_rand_mc() / hltPath_iter->getPrescale();
            }
            else
            {
              evtWeight_LepJetPair *= 1. / hltPath_iter->getPrescale();
            }
          }

          cutFlowTable_mu.update("muon+jet pair passing trigger bit && prescale", evtWeight_LepJetPair);

          isGoodLeptonJetPair = true;
          numerator_and_denominatorHistManagers * histograms_incl_beforeCuts = nullptr;
          numerator_and_denominatorHistManagers * histograms_incl_afterCuts  = nullptr;
          std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts = nullptr;
          std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts  = nullptr;
          if(fakeableMuon.isTight())
          {
            // muon enters numerator
            histograms_incl_beforeCuts = histograms_mu_numerator_incl_beforeCuts;
            histograms_incl_afterCuts  = histograms_mu_numerator_incl_afterCuts;
            histograms_binned_beforeCuts = &histograms_mu_numerator_binned_beforeCuts;
            histograms_binned_afterCuts  = &histograms_mu_numerator_binned_afterCuts;
          }
          else if(fakeableMuon.isFakeable())
          {
            // muon enters denominator (fakeable but not tight)
            histograms_incl_beforeCuts = histograms_mu_denominator_incl_beforeCuts;
            histograms_incl_afterCuts  = histograms_mu_denominator_incl_afterCuts;
            histograms_binned_beforeCuts = &histograms_mu_denominator_binned_beforeCuts;
            histograms_binned_afterCuts  = &histograms_mu_denominator_binned_afterCuts;
          }
          else
          {
            assert(0);
          }

          histograms_incl_beforeCuts->fillHistograms(fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
          fillHistograms(
            *histograms_binned_beforeCuts, fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu
          );

          if(mT_fix < 15.)
          {
            cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeight_LepJetPair);

            histograms_incl_afterCuts->fillHistograms(fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
            fillHistograms(
              *histograms_binned_afterCuts, fakeableMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu
            );
          }
        } // fakeableMuon
      } // 1mu || 2mu
    } // hltPath_iter in triggers_mu

    if(! isGoodLeptonJetPair)
    {
      continue;
    }

    fillWithOverFlow(histogram_met_pt,  met.pt(),  evtWeight);
    fillWithOverFlow(histogram_met_phi, met.phi(), evtWeight);

//--- fill generator level histograms (after cuts)
    if(isMC)
    {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") "
               "processed in " << inputTree -> getProcessedFileCount() << " file(s) "
               "(out of "      << inputTree -> getFileCount()          << ")\n"
               " analyzed = "  << analyzedEntries                      << "\n"
               " selected = "  << selectedEntries
            << " (weighted = " << selectedEntries_weighted << ")\n\n"
               "cut-flow table for electron events\n" << cutFlowTable_e  << "\n"
               "cut-flow table for muon events\n"     << cutFlowTable_mu << '\n'
  ;

  delete muonReader;
  delete electronReader;
  delete jetReader;
  delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;
  delete metFilterReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete metFilterHistManager;

  hltPaths_LeptonFakeRate_delete(triggers_e);
  hltPaths_LeptonFakeRate_delete(triggers_mu);

  delete histograms_e_numerator_incl_beforeCuts;
  delete histograms_e_denominator_incl_beforeCuts;
  delete histograms_e_numerator_incl_afterCuts;
  delete histograms_e_denominator_incl_afterCuts;
  delete histograms_mu_numerator_incl_beforeCuts;
  delete histograms_mu_denominator_incl_beforeCuts;
  delete histograms_mu_numerator_incl_afterCuts;
  delete histograms_mu_denominator_incl_afterCuts;

  for(const std::vector<numerator_and_denominatorHistManagers *> & histVector:
      {
        histograms_e_numerator_binned_beforeCuts,
        histograms_e_denominator_binned_beforeCuts,
        histograms_e_numerator_binned_afterCuts,
        histograms_e_denominator_binned_afterCuts,
        histograms_mu_numerator_binned_beforeCuts,
        histograms_mu_denominator_binned_beforeCuts,
        histograms_mu_numerator_binned_afterCuts,
        histograms_mu_denominator_binned_afterCuts
      })
  {
    for(numerator_and_denominatorHistManagers * hist: histVector)
    {
      delete hist;
    }
  }

  delete inputTree;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
}
