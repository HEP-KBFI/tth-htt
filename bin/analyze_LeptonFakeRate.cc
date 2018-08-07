#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
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
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017, getBTagWeight_option()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // get*_option()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverflow
#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h" // hltPath_LeptonFakeRate, create_hltPaths_LeptonFakeRate(), hltPaths_LeptonFakeRate_delete()
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
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

#include <fstream> // std::ofstream

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
    , electronHistManager_genPhoton_(nullptr)   // GEN PHOTON MATCH
    , muonHistManager_(nullptr)
    , muonHistManager_genHadTau_(nullptr)
    , muonHistManager_genLepton_(nullptr)
    , muonHistManager_genHadTauOrLepton_(nullptr)
    , muonHistManager_genJet_(nullptr)
    , muonHistManager_genPhoton_(nullptr)     // GEN PHOTON MATCH
    , evtHistManager_LeptonFakeRate_(nullptr)
    , evtHistManager_LeptonFakeRate_genHadTau_(nullptr)
    , evtHistManager_LeptonFakeRate_genLepton_(nullptr)
    , evtHistManager_LeptonFakeRate_genHadTauOrLepton_(nullptr)
    , evtHistManager_LeptonFakeRate_genJet_(nullptr)
    , evtHistManager_LeptonFakeRate_genPhoton_(nullptr)  // GEN PHOTON MATCH
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
    delete electronHistManager_genPhoton_;           // GEN PHOTON MATCH
    delete muonHistManager_;
    delete muonHistManager_genHadTau_;
    delete muonHistManager_genLepton_;
    delete muonHistManager_genHadTauOrLepton_;
    delete muonHistManager_genJet_;
    delete muonHistManager_genPhoton_;               // GEN PHOTON MATCH
    delete evtHistManager_LeptonFakeRate_;
    delete evtHistManager_LeptonFakeRate_genHadTau_;
    delete evtHistManager_LeptonFakeRate_genLepton_;
    delete evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
    delete evtHistManager_LeptonFakeRate_genJet_;
    delete evtHistManager_LeptonFakeRate_genPhoton_; // GEN PHOTON MATCH
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
    const std::string process_and_genMatchedPhoton         = process_ + "g";    // GEN PHOTON MATCH

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

        electronHistManager_genPhoton_ = new ElectronHistManager(mkCfg(process_and_genMatchedPhoton));  // GEN PHOTON MATCH
        electronHistManager_genPhoton_->bookHistograms(dir);                                            // GEN PHOTON MATCH
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

        muonHistManager_genPhoton_ = new MuonHistManager(mkCfg(process_and_genMatchedPhoton));  // GEN PHOTON MATCH
        muonHistManager_genPhoton_->bookHistograms(dir);                                        // GEN PHOTON MATCH
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

      evtHistManager_LeptonFakeRate_genPhoton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedPhoton));  // GEN PHOTON MATCH
      evtHistManager_LeptonFakeRate_genPhoton_->bookHistograms(dir);                                                      // GEN PHOTON MATCH
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
          if(electron.genLepton()){ 
	    electronHistManager_genLepton_->fillHistograms(electron, evtWeight);
	    electronHistManager_genHadTauOrLepton_->fillHistograms(electron, evtWeight);
	  }else if(electron.genHadTau()){
	    electronHistManager_genHadTau_->fillHistograms(electron, evtWeight);
	    electronHistManager_genHadTauOrLepton_->fillHistograms(electron, evtWeight);
	  }else if(electron.genPhoton() && !electron.genLepton() && (electron.genPhoton()->pt() > (0.5*electron.pt())) ){
	    electronHistManager_genPhoton_->fillHistograms(electron, evtWeight);
	  }else{
	    electronHistManager_genJet_->fillHistograms(electron, evtWeight);
	  }
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
          if(muon.genLepton()){ 
	    muonHistManager_genLepton_->fillHistograms(muon, evtWeight);
	    muonHistManager_genHadTauOrLepton_->fillHistograms(muon, evtWeight);
	  }else if(muon.genHadTau()){
	    muonHistManager_genHadTau_->fillHistograms(muon, evtWeight);
	    muonHistManager_genHadTauOrLepton_->fillHistograms(muon, evtWeight);
	    //	  }else if(muon.genPhoton() && !muon.genLepton() && (muon.genPhoton()->pt() > (0.5*muon.pt())) ){
	    //    muonHistManager_genPhoton_->fillHistograms(muon, evtWeight);                        
	  }else{
	    muonHistManager_genJet_->fillHistograms(muon, evtWeight);
	  }
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
        if(                      lepton.genPhoton()) evtHistManager_LeptonFakeRate_genPhoton_->fillHistograms(met, mT, mT_fix, evtWeight);   // GEN PHOTON MATCH
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
  ElectronHistManager * electronHistManager_genPhoton_; // GEN PHOTON MATCH

  MuonHistManager * muonHistManager_;
  MuonHistManager * muonHistManager_genHadTau_;
  MuonHistManager * muonHistManager_genLepton_;
  MuonHistManager * muonHistManager_genHadTauOrLepton_;
  MuonHistManager * muonHistManager_genJet_;
  MuonHistManager * muonHistManager_genPhoton_; // GEN PHOTON MATCH

  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genPhoton_; // GEN PHOTON MATCH
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
  const bool isMC_tH = process_string == "tHq" || process_string == "tHW" ? true : false;
  const bool hasLHE  = cfg_analyze.getParameter<bool>("hasLHE");

  const std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  const double lumiScale          = process_string != "data_obs" ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  const bool apply_genWeight      = cfg_analyze.getParameter<bool>("apply_genWeight");
  const bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  const bool redoGenMatching      = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool readGenObjects       = isMC && ! redoGenMatching;
  const bool isDEBUG              = cfg_analyze.getParameter<bool>("isDEBUG");
  const bool apply_met_filters    = cfg_analyze.getParameter<bool>("apply_met_filters");
  
  const vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  const vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  const vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  const vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");

  const bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  const bool use_triggers_2e  = cfg_analyze.getParameter<bool>("use_triggers_2e");
  const bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  const bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");

  const edm::VParameterSet cfg_triggers_e = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_e;
  if(use_triggers_1e || use_triggers_2e)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_e)
      {
        const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
        const bool is_trigger_1e = cfg_trigger.getParameter<bool>("is_trigger_1e");
        const bool is_trigger_2e = cfg_trigger.getParameter<bool>("is_trigger_2e");	
        assert(is_trigger_1e || is_trigger_2e);
	if ( !((is_trigger_1e && use_triggers_1e) ||(is_trigger_2e && use_triggers_2e)) ) {
	  std::cout << "Skipping electron HLT path = '" << trigger_path << "'\n";
	  continue;
	}
        if((is_trigger_1e && std::find(triggerNames_1e.begin(), triggerNames_1e.end(), trigger_path) == triggerNames_1e.end()) ||
           (is_trigger_2e && std::find(triggerNames_2e.begin(), triggerNames_2e.end(), trigger_path) == triggerNames_2e.end())  )
        {
          std::cout << "HLT path '" << trigger_path << "' is not in the list of available electron HLT paths\n";
          continue;
        }
        std::cout << "Selecting electron HLT path = '" << trigger_path << "'\n";
        const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
        triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end());
      }
  }
  const edm::VParameterSet cfg_triggers_mu = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_mu;

  if(use_triggers_1mu || use_triggers_2mu)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_mu)
      {
        const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
        const bool is_trigger_1mu = cfg_trigger.getParameter<bool>("is_trigger_1mu");
        const bool is_trigger_2mu = cfg_trigger.getParameter<bool>("is_trigger_2mu");
        assert(is_trigger_1mu || is_trigger_2mu);
	if ( !((is_trigger_1mu && use_triggers_1mu) ||(is_trigger_2mu && use_triggers_2mu)) ) {
	  std::cout << "Skipping muon HLT path = '" << trigger_path << "'\n";
	  continue;
	}
        if((is_trigger_1mu && std::find(triggerNames_1mu.begin(), triggerNames_1mu.end(), trigger_path) == triggerNames_1mu.end()) ||
           (is_trigger_2mu && std::find(triggerNames_2mu.begin(), triggerNames_2mu.end(), trigger_path) == triggerNames_2mu.end())  )
        {
          std::cout << "HLT path '" << trigger_path << "' is not in the list of available muon HLT paths\n";
          continue;
        }
        std::cout << "Selecting muon HLT path = '" << trigger_path << "'\n";
        const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
        triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end());
      }
  }
  const vdouble etaBins_e  = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  const vdouble ptBins_e   = cfg_analyze.getParameter<vdouble>("ptBins_e");
  const vdouble etaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  const vdouble ptBins_mu  = cfg_analyze.getParameter<vdouble>("ptBins_mu");

  const double minConePt_global_e  = cfg_analyze.getParameter<double>("minConePt_global_e");
  const double minConePt_global_mu = cfg_analyze.getParameter<double>("minConePt_global_mu");
  const double minRecoPt_global_e  = cfg_analyze.getParameter<double>("minRecoPt_global_e");
  const double minRecoPt_global_mu = cfg_analyze.getParameter<double>("minRecoPt_global_mu");

  const double lep_mva_cut = cfg_analyze.getParameter<double>("lep_mva_cut"); // CV: used for tight lepton selection only

  const std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_jets      = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_analyze.getParameter<std::string>("branchName_met");

  const std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  const std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  const std::string branchName_genJets    = cfg_analyze.getParameter<std::string>("branchName_genJets");

  const edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  const MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);

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

  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  const bool writeTo_selEventsFileOut = ! selEventsFileName_output.empty();
  std::map<std::string, std::map<std::string, std::ofstream *>> outputFiles;
  for(const std::string & emu_str: { "e", "mu" })
  {
    for(const std::string & numden_str: { "num", "den" })
    {
      outputFiles[emu_str][numden_str] = writeTo_selEventsFileOut ?
        new std::ofstream(Form(selEventsFileName_output.data(), emu_str.data(), numden_str.data())) :
        nullptr
      ;
    }
  }

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
  }

  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option     = getJet_option       (central_or_shift, isMC);
  const int lheScale_option  = getLHEscale_option  (central_or_shift);
  const int jetBtagSF_option = getBTagWeight_option(central_or_shift);
  const int met_option       = getMET_option       (central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> lheScale_option            = " << lheScale_option            << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option           << "\n"
       " -> met_option                 = " << met_option                 << "\n"
       " -> jetPt_option               = " << jetPt_option               << '\n'
  ;

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

  std::vector<hltPath*> triggers;
  triggers.insert(triggers.end(), triggers_e.begin(), triggers_e.end());
  triggers.insert(triggers.end(), triggers_mu.begin(), triggers_mu.end());
  hltPathReader hltPathReader_instance(triggers);
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

//--- declare particle collections
  RecoMuonReader * muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);
  tightMuonSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoElectronReader * electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  fakeableElectronSelector.enable_offline_e_trigger_cuts();
  tightElectronSelector.enable_offline_e_trigger_cuts();
  tightElectronSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoJetReader * jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner_dR04(0.4);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7); // Christian's suggestion
  RecoJetCollectionSelector jetSelector(era);
  jetSelector.getSelector().set_min_pt(30.); // Setting the min. pt of the jets for Lepton FR analysis
  jetSelector.getSelector().set_max_absEta(2.4); // Setting the max. |eta| of the jets for Lepton FR analysis
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);

//--- declare missing transverse energy
  RecoMEtReader * metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

  
//--- declare MET filter
  MEtFilter metFilter;
  MEtFilterReader * metFilterReader = new MEtFilterReader(&metFilter, era);
  inputTree->registerReader(metFilterReader);

// --- Setting up the Met Filter Hist Manager ----
  const edm::ParameterSet metFilterHistManagerCfg = makeHistManager_cfg(process_string, "LeptonFakeRate/met_filters", central_or_shift);
  MEtFilterHistManager * metFilterHistManager = new MEtFilterHistManager(metFilterHistManagerCfg);
  metFilterHistManager->bookHistograms(fs);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenJetReader * genJetReader       = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
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
      if(! branchName_genPhotons.empty())
      {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree->registerReader(genPhotonReader);
      }
      if(! branchName_genJets.empty())
      {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree->registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
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

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

//--- book additional event level histograms
  TH1 * histogram_met_pt  = fs.make<TH1D>("met_pt",  "met_pt",   40, 0., 200.);
  TH1 * histogram_met_phi = fs.make<TH1D>("met_phi", "met_phi",  36, -TMath::Pi(), +TMath::Pi());
  

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1 * histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1 * histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

  cutFlowTableType cutFlowTable_e(isDEBUG);
  initializeCutFlowTable(cutFlowTable_e, ">= 1 presel/Loose electron");
  if(apply_met_filters){ initializeCutFlowTable(cutFlowTable_e, "MEt filter"); }
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_afterCuts);

  cutFlowTableType cutFlowTable_mu(isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu, ">= 1 presel/Loose muon");
  if(apply_met_filters){ initializeCutFlowTable(cutFlowTable_mu, "MEt filter"); }
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
    std::vector<GenPhoton> genPhotons;
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
      if(genPhotonReader)
      {
        genPhotons = genPhotonReader->read();
      }
      if(genJetReader)
      {
        genJets = genJetReader->read();
      }
    }
  
//--- fill generator level histograms (before cuts)
    double evtWeight_inclusive = 1.;
    if(isMC)
    {
      if(apply_genWeight)    evtWeight_inclusive *= boost::math::sign(eventInfo.genWeight);
      if(isMC_tH)            evtWeight_inclusive *= eventInfo.genWeight_tH;
      if(eventWeightManager) evtWeight_inclusive *= eventWeightManager->getWeight();
      lheInfoReader->read();
      evtWeight_inclusive *= lheInfoReader->getWeight_scale(lheScale_option);
      evtWeight_inclusive *= eventInfo.pileupWeight;
      evtWeight_inclusive *= lumiScale;
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon *> preselMuons = preselMuonSelector(cleanedMuons); // Loose muons
    std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon *> tightMuons = tightMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron *> preselElectrons = preselElectronSelector(cleanedElectrons); // Loose electrons
    std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron *> tightElectrons = tightElectronSelector(preselElectrons);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet *> cleanedJets_dR04 = jetCleaner_dR04(jet_ptrs, fakeableMuons, fakeableElectrons); // changed from presel to be in sync with the analysis channels
    std::vector<const RecoJet *> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);
    std::vector<const RecoJet *> selJets_dR04 = jetSelector(cleanedJets_dR04);
    std::vector<const RecoJet *> cleanedJets_dR07 = jetCleaner_dR07(jet_ptrs, fakeableMuons, fakeableElectrons); // changed from presel to be in sync with the analysis channels
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
      if(genPhotonReader)
      {
        genPhotons = genPhotonReader->read();
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
      electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons, 0.2);
      electronGenMatcher.addGenJetMatch   (preselElectrons, genJets,    0.2);

      jetGenMatcher.addGenLeptonMatch(selJets_dR07, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets_dR07, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch   (selJets_dR07, genJets,    0.2);
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "Event Particle Collection Info\n";
      printCollection("preselElectrons", preselElectrons);
      printCollection("preselMuons", preselMuons);
      // printCollection("selJets_dR04", selJets_dR04);
      printCollection("uncleaned jets", jet_ptrs);
      printCollection("selJets_dR07", selJets_dR07);
    }
  
//--- require exactly one Loose lepton
    if((preselElectrons.size() + preselMuons.size()) != 1) // Giovanni's pre-selection
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS (presel.e + presel.mu != 1) cut\n";
      }
      continue;
    }
  

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if(isMC)
    {
      evtWeight *= evtWeight_inclusive;

      const double btagWeight = get_BtagWeight(selJets_dR04); // changed b-tag jet collection to selJets_dR04 from selJets_dR07 here !!!
      evtWeight *= btagWeight;

      if(isDEBUG)
      {
        if(apply_genWeight)
        {
          std::cout << "genWeight    = " << boost::math::sign(eventInfo.genWeight) << '\n';
        }
        std::cout << "lumiScale    = " << lumiScale              << "\n"
                     "pileupWeight = " << eventInfo.pileupWeight << "\n"
                     "btagWeight   = " << btagWeight             << '\n';
      }
    }
  
    if(preselElectrons.size() >= 1) cutFlowTable_e.update (">= 1 presel/Loose electron", evtWeight);
    if(preselMuons.size()     >= 1) cutFlowTable_mu.update(">= 1 presel/Loose muon",     evtWeight);
  
    if(apply_met_filters)
      {
        metFilterHistManager->fillHistograms(metFilter, evtWeight);
        if(! metFilterSelector(metFilter))
          {
            if(run_lumi_eventSelector)
              {
                std::cout << "event " << eventInfo.str() << " FAILS MEtFilter\n";
              }
            continue;
          }
        cutFlowTable_e.update ("MEt filter", evtWeight);
        cutFlowTable_mu.update("MEt filter", evtWeight);
      }
  

// ----- CHRISTIAN'S NEW LOGIC  -----

    bool isTriggered_1e = false;                                                                                                                                                                                 
    bool isTriggered_2e = false;                                                                                                                                                                            
    bool isTriggered_1mu = false;                                                                                                                                                                              
    bool isTriggered_2mu = false;   

    bool isGoodLeptonJetPair = false;     // set to true if at least one electron+jet or one muon+jet combination passes trigger requirements   
    bool isGoodMuonJetPair = false;
    bool isGoodElectronJetPair = false;
    std::vector<const RecoJet *> cleanedJets;
    std::vector<const RecoJet *> selJets;

 // ----- MUON BLOCK ----
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_mu){ // loop over triggers_mu (given in descendng order of thresholds in the config)   
      hltPath_iter->setIsTriggered(false); // resetting the bool to false 
      if(! (hltPath_iter->getValue() >= 1))
        {
          if(run_lumi_eventSelector)
            {
              std::cout << "event " << eventInfo.str() << " FAILS this mu trigger"            "\n"
                "HLT Path name "     << *hltPath_iter            << "\n"
                "Trigger bit value " << hltPath_iter->getValue() << '\n';
            }
          continue; // require trigger to fire
        }

      
        for(const RecoMuon * const preselMuon_ptr: preselMuons){ // loop over preselMuons
        const RecoMuon & preselMuon = *preselMuon_ptr;
        if(!(preselMuon.cone_pt() > minConePt_global_mu && preselMuon.pt() > minRecoPt_global_mu)) // Giovanni's selection for global lepton reco and cone pt cuts
          {
            if(run_lumi_eventSelector)
              {
                std::cout << "event " << eventInfo.str() << " FAILS global muon cone and reco pt cuts\n";
              }
            continue;
          }

        std::vector<const RecoMuon*> tmp_leptons;
        tmp_leptons.push_back(preselMuon_ptr);
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);       
        // bool isGoodMuonJetPair = false;

        for(const RecoJet * const selJet: selJets){ // loop over jets
          if(deltaR(preselMuon.p4(), selJet->p4()) <= 0.7)
            {
              if(run_lumi_eventSelector)
                {
                  std::cout << "jet FAILS deltaR(presel. mu, sel-jet) > 0.7 cut\n"
                    "deltaR(preselMuon.p4(), selJet->p4()) " << deltaR(preselMuon.p4(), selJet->p4())
                            << '\n';
                }
              continue;
            }

              // ---------  REMOVED SINCE DROPPED BY GIOVANNI -------
              // if( !( (preselMuon.cone_pt() < 30. && selBJets_loose_dR04.size() != 0) ||  preselMuon.cone_pt() >= 30.) ){
              //       if(run_lumi_eventSelector)
              //       {
              //              std::cout << "Muon + jet pair FAILS the b-jet cut " << "\n"
              //        "selBJets_loose_dR04.size() " << selBJets_loose_dR04.size() << "\n"
              //               "preselMuon.cone_pt() " << preselElectron.cone_pt() << "\n";
              //             }
              //   continue;
              // }
              // ------------------------------------------------------

          if( !( (preselMuon.cone_pt() >= hltPath_iter->getMinPt() && preselMuon.cone_pt()  < hltPath_iter->getMaxPt()) &&
                 (selJet->pt() > hltPath_iter->getMinJetPt()) && (preselMuon.pt() > hltPath_iter->getMinRecoPt()) ) )
                {
                  if(run_lumi_eventSelector)
                    {
                      std::cout << "Muon + jet pair FAILS trigger dep. Pt cuts "       << "\n"
                        "preselMuon.cone_pt() " << preselMuon.cone_pt() << "\n"
                        "hltPath_iter->getMinPt() " << hltPath_iter->getMinPt()         << "\n"
                        "hltPath_iter->getMaxPt() " << hltPath_iter->getMaxPt()         << "\n"
                        "selJet->pt() "        << selJet->pt()                << "\n"
                        "Trigger Min. Jet pT " << hltPath_iter->getMinJetPt() << "\n"
                        "preselMuon.pt() " << preselMuon.pt()         << "\n"
                        "Trigger Min. Reco Muon pT cut " << hltPath_iter->getMinRecoPt() << "\n";
                    }
                  continue;
                }else{
                hltPath_iter->setIsTriggered(true);
                isGoodMuonJetPair = true;
                isGoodLeptonJetPair = true;
                break;
              }
        } // loop over jets ends
      } // loop over preselMuons ends

      if(hltPath_iter->isTriggered()){
        if(hltPath_iter->is_trigger_2mu()){isTriggered_2mu = true;}
        if(hltPath_iter->is_trigger_1mu()){isTriggered_1mu = true;}
      }else{
        continue;
      }

    } // loop over triggers_mu ends

// --------------



// ----- ELECTRON BLOCK ----
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_e){ // loop over triggers_e (given in descendng order of thresholds in the config) 
      hltPath_iter->setIsTriggered(false); // resetting the bool to false 
      if(! (hltPath_iter->getValue() >= 1)){ 
        if(run_lumi_eventSelector){
          std::cout << "event " << eventInfo.str() << " FAILS this e trigger" "\n"
            "HLT Path name " << *hltPath_iter  << "\n"
            "Trigger bit value " << hltPath_iter->getValue() << '\n';
             }
        continue; // require trigger to fire
      }
      for(const RecoElectron * const preselElectron_ptr: preselElectrons){ // loop over preselElectrons
        const RecoElectron & preselElectron = *preselElectron_ptr;
        if(!(preselElectron.cone_pt() > minConePt_global_e && preselElectron.pt() > minRecoPt_global_e)) // Giovanni's selection for global lepton reco and cone pt cuts
          {
            if(run_lumi_eventSelector)
              {
                std::cout << "presel Electron FAILS global reco pt and cone pt cuts\n"
                  "minConePt_global_e " << minConePt_global_e << " "
                  "minRecoPt_global_e " << minRecoPt_global_e << '\n';
              }
            continue;
          }

        std::vector<const RecoElectron*> tmp_leptons;
        tmp_leptons.push_back(preselElectron_ptr);
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);       
        // bool isGoodElectronJetPair = false;

        for(const RecoJet * const selJet: selJets){ // loop over jets
          if(deltaR(preselElectron.p4(), selJet->p4()) <= 0.7)
            {
              if(run_lumi_eventSelector)
                {
                  std::cout << "jet FAILS deltaR(presel. e, sel-jet) > 0.7 cut\n"
                    "deltaR(preselElectron.p4(), selJet->p4()) " << deltaR(preselElectron.p4(), selJet->p4())
                            << '\n';
                }
              continue;
            }


          if( !( (preselElectron.cone_pt() >= hltPath_iter->getMinPt() && preselElectron.cone_pt()  < hltPath_iter->getMaxPt()) &&
                 (selJet->pt() > hltPath_iter->getMinJetPt()) && (preselElectron.pt() > hltPath_iter->getMinRecoPt()) ) )
            {
              if(run_lumi_eventSelector)
                {
                  std::cout << "electron + jet pair FAILS trigger dep. Pt cuts "       << "\n"
                    "preselElectron.cone_pt() " << preselElectron.cone_pt() << "\n"
                    "hltPath_iter->getMinPt() " << hltPath_iter->getMinPt()         << "\n"
                    "hltPath_iter->getMaxPt() " << hltPath_iter->getMaxPt()         << "\n"
                    "selJet->pt() "        << selJet->pt()                << "\n"
                    "Trigger Min. Jet pT cut " << hltPath_iter->getMinJetPt() << "\n"
                    "preselElectron.pt() " << preselElectron.pt()         << "\n"
                    "Trigger Min. Reco Electron pT cut " << hltPath_iter->getMinRecoPt() << "\n";
                }
              continue;
            }else{
            hltPath_iter->setIsTriggered(true);
            isGoodElectronJetPair = true; // set to true as soon as we find a jet matching all the above criteria
            isGoodLeptonJetPair = true;
            break;
          }
        } // loop over selJets ends
      } // loop over preselElectrons ends

      if(hltPath_iter->isTriggered()){
        if(hltPath_iter->is_trigger_2e()){isTriggered_2e = true;}
        if(hltPath_iter->is_trigger_1e()){isTriggered_1e = true;}
      }else{
        continue;
      }
      
    } // loop over triggers_e ends
    
// ------------------------


    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;

    
    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
        std::cout << " (selTrigger_1e = " << selTrigger_1e
                  << ", selTrigger_2e = " << selTrigger_2e
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_2mu = " << selTrigger_2mu << ")" << std::endl;
      }
      continue;
    }

    //--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
    //    the ranking of the triggers is as follows: 2mu, 2e, 1mu, 1e
    // CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC && !isDEBUG ) {
      if ( selTrigger_1e && (isTriggered_1mu || isTriggered_2e || isTriggered_2mu) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1e = " << selTrigger_1e
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_1mu = " << isTriggered_1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_2mu) ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1mu = " << selTrigger_1mu
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e && isTriggered_2mu ) {
        if ( run_lumi_eventSelector ) {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_2e = " << selTrigger_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu << ")" << std::endl;
        }
        continue;
      }
    }



    double evtWeight_trigger = 1.0;

    if(isMC){ // prescale weight
      std::vector<hltPath_LeptonFakeRate *> triggers_all = triggers_mu;
      triggers_all.insert( triggers_all.end(), triggers_e.begin(), triggers_e.end() );
      double prob_all_trigger_fail = 1.0;
      for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_all){
        if(hltPath_iter->isTriggered()){ prob_all_trigger_fail *= (1. - (1./hltPath_iter->getPrescale()) );  }
      } 
      evtWeight_trigger = (1.0 - prob_all_trigger_fail) ; 
    }

    evtWeight *= evtWeight_trigger;
   

    // ------ FILLING HISTOGRAMS MUONS
    for(const RecoMuon * const preselMuon_ptr: preselMuons) // loop over preselMuons
    {
      if(!isGoodMuonJetPair) break;
      const RecoMuon & preselMuon = *preselMuon_ptr; 
      const double mT     = comp_mT(preselMuon, met.pt(), met.phi());
      const double mT_fix = comp_mT_fix(preselMuon, met.pt(), met.phi());
      
      double evtWeight_LepJetPair = evtWeight; // copying evtWeight

      // numerator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      // denominator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;



      if(preselMuon.isTight())
      {
        // muon enters numerator
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
        }
        histograms_incl_beforeCuts_num = histograms_mu_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_mu_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_mu_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_mu_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["mu"]["num"]) << eventInfo.str() << '\n' ;
        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
	{
	  histograms_incl_beforeCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	  fillHistograms(*histograms_binned_beforeCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);
	  
	  if(mT_fix < 15.)
	    {
	      cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeight_LepJetPair);
	      histograms_incl_afterCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
	      fillHistograms(*histograms_binned_afterCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);
	    }
	}

      if(preselMuon.isFakeable() && !(preselMuon.isTight())) // Applying (isFakeable && !(isTight)) condition [TALLINN METHOD]
      // if(preselMuon.isFakeable())         // Applying (isFakeable) condition [GIOVANNI'S METHOD]
      {
        // muon enters denominator (fakeable)
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "denominator filled\n";
        }
        histograms_incl_beforeCuts_den = histograms_mu_denominator_incl_beforeCuts;
        histograms_incl_afterCuts_den  = histograms_mu_denominator_incl_afterCuts;
        histograms_binned_beforeCuts_den = &histograms_mu_denominator_binned_beforeCuts;
        histograms_binned_afterCuts_den  = &histograms_mu_denominator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["mu"]["den"]) << eventInfo.str() << '\n';
        }
      }

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
        histograms_incl_beforeCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
        fillHistograms(*histograms_binned_beforeCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);

        if(mT_fix < 15.)
        {
          cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV", evtWeight_LepJetPair);
          histograms_incl_afterCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
          fillHistograms(*histograms_binned_afterCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_mu);
        }
      }

    } // loop over preselMuons ends
    

    // ------ FILLING HISTOGRAMS ELECTRONS
    for(const RecoElectron * const preselElectron_ptr: preselElectrons) // loop over preselElectrons
    {

      if(!isGoodElectronJetPair) break;

      const RecoElectron & preselElectron = *preselElectron_ptr; 
      const double mT     = comp_mT(preselElectron, met.pt(), met.phi());
      const double mT_fix = comp_mT_fix(preselElectron, met.pt(), met.phi());
      
      double evtWeight_LepJetPair = evtWeight; // copying evtWeight
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;


      if(preselElectron.isTight())
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
        }
        // electron enters numerator
        histograms_incl_beforeCuts_num = histograms_e_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_e_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_e_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_e_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["e"]["num"]) << eventInfo.str() <<  '\n';

             // " lep pt() " << preselElectron.pt() <<
             // " eta " << preselElectron.eta() <<
             // " phi "  << preselElectron.phi() <<
             // " mva " << preselElectron.mvaRawTTH() <<
             // " ptRatio " << preselElectron.jetPtRatio() <<
             // " deltaEta " << preselElectron.deltaEta() <<
             // " deltaPhi " << preselElectron.deltaPhi() <<
             // " away jet pt " << sel_Jet_pt_e <<
             // " eta " << sel_Jet_eta_e <<
             // " met pt " << met.pt() <<
             // " phi " << met.phi() <<
             // " HLT passed " <<  hltpath_passed <<
             // " " << hltpath_trigger_bit <<


             // " lep cone_pt() " << preselElectron.cone_pt() <<
             // " lep assocJet_pt() " << preselElectron.assocJet_pt() <<
             // " lep dxy() " << preselElectron.dxy() <<
             // " lep dz() " << preselElectron.dz() <<
             // " lep sip3d() " << preselElectron.sip3d() <<
             // " lep relIso() " << preselElectron.relIso() <<
             // " lep pfRelIso04All() " << preselElectron.pfRelIso04All() <<
             // " lep miniIsoNeutral() " << preselElectron.miniIsoNeutral() <<
             // " lep miniIsoCharged() " << preselElectron.miniIsoCharged() <<

             // " e mvaRaw_POG() " << preselElectron.mvaRaw_POG() <<
             // " e sigmaEtaEta() " << preselElectron.sigmaEtaEta() <<
             // " e HoE() " << preselElectron.HoE() <<
             // " e OoEminusOoP() " << preselElectron.OoEminusOoP() <<
             // " e nLostHits() " << preselElectron.nLostHits() <<
             // " e passesConversionVeto() " << preselElectron.passesConversionVeto() << '\n';

        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
      {
        histograms_incl_beforeCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
        fillHistograms(*histograms_binned_beforeCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeight_LepJetPair);
          histograms_incl_afterCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
          fillHistograms(*histograms_binned_afterCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);
        }
      }


      if(preselElectron.isFakeable() && !(preselElectron.isTight())) // Applying (isFakeable && !(isTight)) condition [TALLINN METHOD]
      // if(preselElectron.isFakeable())  // Applying (isFakeable) condition [GIOVANNI'S METHOD]
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "denominator filled\n";
        }
        // electron enters denominator (fakeable but not tight)
        histograms_incl_beforeCuts_den = histograms_e_denominator_incl_beforeCuts;
        histograms_incl_afterCuts_den  = histograms_e_denominator_incl_afterCuts;
        histograms_binned_beforeCuts_den = &histograms_e_denominator_binned_beforeCuts;
        histograms_binned_afterCuts_den  = &histograms_e_denominator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["e"]["den"]) << eventInfo.str() << '\n';
          //  " lep pt() " << preselElectron.pt() <<
          //  " eta " << preselElectron.eta() <<
          //  " phi "  << preselElectron.phi() <<
          //  " mva " << preselElectron.mvaRawTTH() <<
          //  " ptRatio " << preselElectron.jetPtRatio() <<
          //  " deltaEta " << preselElectron.deltaEta() <<
          //  " deltaPhi " << preselElectron.deltaPhi() <<
          //  " away jet pt " << sel_Jet_pt_e <<
          //  " eta " << sel_Jet_eta_e <<
          //  " met pt " << met.pt() <<
          //  " phi " << met.phi() <<
          //  " HLT passed " <<  hltpath_passed <<
          //  " " << hltpath_trigger_bit <<

          //  " lep cone_pt() " << preselElectron.cone_pt() <<
          //  " lep assocJet_pt() " << preselElectron.assocJet_pt() <<
          //  " lep dxy() " << preselElectron.dxy() <<
          //  " lep dz() " << preselElectron.dz() <<
          //  " lep sip3d() " << preselElectron.sip3d() <<
          //  " lep relIso() " << preselElectron.relIso() <<
          //  " lep pfRelIso04All() " << preselElectron.pfRelIso04All() <<
          //  " lep miniIsoNeutral() " << preselElectron.miniIsoNeutral() <<
          //  " lep miniIsoCharged() " << preselElectron.miniIsoCharged() <<

          // " e mvaRaw_POG() " << preselElectron.mvaRaw_POG() <<
          // " e sigmaEtaEta() " << preselElectron.sigmaEtaEta() <<
          // " e HoE() " << preselElectron.HoE() <<
          // " e OoEminusOoP() " << preselElectron.OoEminusOoP() <<
          // " e nLostHits() " << preselElectron.nLostHits() <<
          // " e passesConversionVeto() " << preselElectron.passesConversionVeto() << '\n';

        }
      }

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
        histograms_incl_beforeCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
        fillHistograms(*histograms_binned_beforeCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV", evtWeight_LepJetPair);
          histograms_incl_afterCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair);
          fillHistograms(*histograms_binned_afterCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeight_LepJetPair, &cutFlowTable_e);
        }
      }

    } // loop over preselElectrons ends
    
// ----- CHRISTIAN'S NEW LOGIC ENDS -----


    if(! isGoodLeptonJetPair)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS as there is no presel.lepton+Jet pair in the event satisfying all requirements\n";
      }
      continue;
    }


    fillWithOverFlow(histogram_met_pt,  met.pt(),  evtWeight);
    fillWithOverFlow(histogram_met_phi, met.phi(), evtWeight);

//--- fill generator level histograms (after cuts)
    if(isMC)
    {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  } // while loop over events ends

 std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") "
               "processed in " << inputTree -> getProcessedFileCount() << " file(s) "
               "(out of "      << inputTree -> getFileCount()          << ")\n"
               " analyzed = "  << analyzedEntries                      << "\n"
               " selected = "  << selectedEntries
            << " (weighted = " << selectedEntries_weighted << ")\n\n"
               "cut-flow table for electron events\n" << cutFlowTable_e  << "\n"
               "cut-flow table for muon events\n"     << cutFlowTable_mu << '\n';

  delete muonReader;
  delete electronReader;
  delete jetReader;
  delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;
  delete metFilterReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete metFilterHistManager;
  delete eventWeightManager;

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

  for(auto & kv: outputFiles)
  {
    for(auto & kv2: kv.second)
    {
      if(kv2.second)
      {
        *kv2.second << std::flush;
        delete kv2.second;
      }
    }
  }

  delete run_lumi_eventSelector;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
} // main func ends
