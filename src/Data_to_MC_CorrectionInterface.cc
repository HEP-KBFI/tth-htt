#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile, loadTH1/TH2, get_sf_from_TH1/TH2 
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h" // sf_eToTauFakeRate_2017(), sf_muToTauFakeRate_2017()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TFile.h> // TFile

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with(), boost::starts_with()

#include <cassert> // assert()

//TODO:
// - update the data/MC corrections for 2017 data & MC
// - rename the functions where possible

Data_to_MC_CorrectionInterface::Data_to_MC_CorrectionInterface(const edm::ParameterSet & cfg)
  : effTrigger_ee_(nullptr)
  , effTrigger_em_(nullptr)
  , effTrigger_mm_(nullptr)
  , effTrigger_3l_(nullptr)
  , hadTauSelection_(-1)
  , eToTauFakeRate_option_(kFRet_central)
  , muToTauFakeRate_option_(kFRmt_central)
  , numLeptons_(0)
  , lepton_type_(3)
  , lepton_pt_(3)
  , lepton_eta_(3)
  , numElectrons_(0)
  , electron_pt_(3)
  , electron_eta_(3)
  , numMuons_(0)
  , muon_pt_(3)
  , muon_eta_(3)
  , numHadTaus_(0)
  , hadTau_genPdgId_(3)
  , hadTau_pt_(3)
  , hadTau_eta_(3)
{
  const std::string era_string = cfg.getParameter<std::string>("era");
  if(era_string == "2017")
  {
    era_ = kEra_2017;
  }
  else
  {
    throw cmsException(this) << "Invalid Configuration parameter 'era' = " << era_string;
  }

  const std::string hadTauSelection_string = cfg.getParameter<std::string>("hadTauSelection");
  setHadTauSelection(hadTauSelection_string);

  for(int idxHadTau = 0; idxHadTau < 3; ++idxHadTau)
  {
    hadTauSelection_antiElectron_[idxHadTau] = -1;
    if(cfg.exists("hadTauSelection_antiElectron"))
    {
      hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiElectron");
    }
    else
    {
      const std::string cfgParName = "hadTauSelection_antiElectron" + aux::getHadTauIdxLabel(idxHadTau);
      if(cfg.exists(cfgParName))
      {
        hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>(cfgParName);
      }
    }

    hadTauSelection_antiMuon_[idxHadTau] = -1;
    if(cfg.exists("hadTauSelection_antiMuon"))
    {
      hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiMuon");
    }
    else
    {
      const std::string cfgParName = "hadTauSelection_antiMuon" + aux::getHadTauIdxLabel(idxHadTau);
      if(cfg.exists(cfgParName))
      {
        hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>(cfgParName);
      }
    }
  }

  const std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  if( central_or_shift != "central")
  {
    std::string shiftUp_or_Down;
    if(boost::ends_with(central_or_shift, "Up"))
    {
      shiftUp_or_Down = "Up";
    }
    else if(boost::ends_with(central_or_shift, "Down"))
    {
      shiftUp_or_Down = "Down";
    }
    else
    {
      throw cmsException(this)
              << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift;
    }

    if(boost::starts_with(central_or_shift, "CMS_ttHl_FRet"))
    {
      if     (shiftUp_or_Down == "Up"  ) eToTauFakeRate_option_ = kFRet_shiftUp;
      else if(shiftUp_or_Down == "Down") eToTauFakeRate_option_ = kFRet_shiftDown;
      else                               assert(0);
    }
    else if( boost::starts_with(central_or_shift, "CMS_ttHl_FRmt"))
    {
      if     (shiftUp_or_Down == "Up"  ) muToTauFakeRate_option_ = kFRmt_shiftUp;
      else if(shiftUp_or_Down == "Down") muToTauFakeRate_option_ = kFRmt_shiftDown;
      else                               assert(0);
    }
  }

  if(era_ == kEra_2017)
  {
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root",
      "GsfElectronToMVAVLooseFOIDEmuTightIP2D",
      lut::kXptYabsEta
    ));

    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root",
      "MVAVLooseElectronToMini4",
      lut::kXptYabsEta
    ));

    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root",
      "MVAVLooseElectronToConvVetoIHit1",
      lut::kXptYabsEta
    ));

    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/egammaEffi.txt_EGM2D.root",
      "EGamma_SF2D",
      lut::kXetaYpt
    ));

    sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_3l.root",
      "sf",
      lut::kXptYabsEta
    ));

    sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_2lss.root",
      "sf",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root",
      "SF",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root",
      "SF",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root",
      "SF",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/ratios_HIP_trkEff.root",
      "ratio_eta",
      lut::kXeta
    ));

    sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_3l.root",
      "sf",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_2lss.root",
      "sf",
      lut::kXptYabsEta
    ));

//-----------------------------------------------------------------------------

    effTrigger_ee_ = new lutWrapperTH2Poly( // X=pt1, Y=pt2
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root",
      "SSee2DPt__effic",
      lut::kXptYpt
    );

    effTrigger_em_ = new lutWrapperTH2Poly( // X=pt1, Y=pt2
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root",
      "SSeu2DPt_effic",
      lut::kXptYpt
    );

    effTrigger_mm_ = new lutWrapperTH2Poly( // X=pt1, Y=pt2
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root",
      "SSuu2DPt_effic",
      lut::kXptYpt
    );

    effTrigger_3l_ = new lutWrapperTH2Poly( // X=pt1, Y=pt2
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root",
      "__3l2DPt_effic",
      lut::kXptYpt
    );

    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    const int numEtaBins_1e = etaBinEdges_1e.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const char * etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax).data();

      effTrigger_1e_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax
      ));
      effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax
      ));
    }

    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    const int numEtaBins_1m = etaBinEdges_1m.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const char * etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax).data();

      effTrigger_1m_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax
      ));
      effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax
      ));
    }
  } // era_
  else
  {
    assert(0);
  }
}

Data_to_MC_CorrectionInterface::~Data_to_MC_CorrectionInterface()
{
  aux::clearCollection(sfElectronID_and_Iso_loose_);
  aux::clearCollection(sfElectronID_and_Iso_tight_to_loose_woTightCharge_);
  aux::clearCollection(sfElectronID_and_Iso_tight_to_loose_wTightCharge_);
  aux::clearCollection(sfMuonID_and_Iso_loose_);
  aux::clearCollection(sfMuonID_and_Iso_tight_to_loose_woTightCharge_);
  aux::clearCollection(sfMuonID_and_Iso_tight_to_loose_wTightCharge_);
  for(auto & kv: inputFiles_)
  {
    delete kv.second;
  }
  delete effTrigger_ee_;
  delete effTrigger_em_;
  delete effTrigger_mm_;
  delete effTrigger_3l_;
  aux::clearCollection(effTrigger_1e_data_);
  aux::clearCollection(effTrigger_1e_mc_);
  aux::clearCollection(effTrigger_1m_data_);
  aux::clearCollection(effTrigger_1m_mc_);
}

void
Data_to_MC_CorrectionInterface::setHadTauSelection(const std::string& hadTauSelection)
{
  hadTauSelection_ = -1;
  if     (hadTauSelection == "dR03mvaVVLoose") hadTauSelection_ = 1;
  else if(hadTauSelection == "dR03mvaVLoose" ) hadTauSelection_ = 2;
  else if(hadTauSelection == "dR03mvaLoose"  ) hadTauSelection_ = 3;
  else if(hadTauSelection == "dR03mvaMedium" ) hadTauSelection_ = 4;
  else if(hadTauSelection == "dR03mvaTight"  ) hadTauSelection_ = 5;
  else if(hadTauSelection == "dR03mvaVTight" ) hadTauSelection_ = 6;
  else if(hadTauSelection == "dR03mvaVVTight") hadTauSelection_ = 7;
  else throw cmsException(this, __func__)
         << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection;
}

void
Data_to_MC_CorrectionInterface::setLeptons(int lepton1_type, double lepton1_pt, double lepton1_eta,
                                           int lepton2_type, double lepton2_pt, double lepton2_eta,
                                           int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  numElectrons_ = 0;
  if(lepton1_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton1_pt;
    electron_eta_[numElectrons_] = lepton1_eta;
    ++numElectrons_;
  }
  if(lepton2_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton2_pt;
    electron_eta_[numElectrons_] = lepton2_eta;
    ++numElectrons_;
  } 
  if(lepton3_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton3_pt;
    electron_eta_[numElectrons_] = lepton3_eta;
    ++numElectrons_;
  }

  numMuons_ = 0;
  if(lepton1_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton1_pt;
    muon_eta_[numMuons_] = lepton1_eta;
    ++numMuons_;
  }
  if(lepton2_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton2_pt;
    muon_eta_[numMuons_] = lepton2_eta;
    ++numMuons_;
  }
  if(lepton3_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton3_pt;
    muon_eta_[numMuons_] = lepton3_eta;
    ++numMuons_;
  }

  numLeptons_ = 0;
  for(int idxElectron = 0; idxElectron < numElectrons_; ++idxElectron)
  {
    lepton_type_[numLeptons_] = kElectron;
    lepton_pt_[numLeptons_] = electron_pt_[idxElectron];
    lepton_eta_[numLeptons_] = electron_eta_[idxElectron];
    ++numLeptons_;
  }
  for(int idxMuon = 0; idxMuon < numMuons_; ++idxMuon)
  {
    lepton_type_[numLeptons_] = kMuon;
    lepton_pt_[numLeptons_] = muon_pt_[idxMuon];
    lepton_eta_[numLeptons_] = muon_eta_[idxMuon];
    ++numLeptons_;
  }
}

void
Data_to_MC_CorrectionInterface::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta,
                                           int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta,
                                           int hadTau3_genPdgId, double hadTau3_pt, double hadTau3_eta)
{
  numHadTaus_ = 0;
  if(hadTau1_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau1_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau1_pt;
    hadTau_eta_[numHadTaus_] = hadTau1_eta;
    ++numHadTaus_;
  }
  if(hadTau2_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau2_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau2_pt;
    hadTau_eta_[numHadTaus_] = hadTau2_eta;
    ++numHadTaus_;
  }
  if(hadTau3_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau3_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau3_pt;
    hadTau_eta_[numHadTaus_] = hadTau3_eta;
    ++numHadTaus_;
  }
}

//-----------------------------------------------------------------------------
// trigger efficiency turn-on curves for Spring16 non-reHLT MC

double
Data_to_MC_CorrectionInterface::getWeight_leptonTriggerEff() const
{
  double weight = 1.;
  if(era_ == kEra_2017)
  {
    if(numLeptons_ >= 2)
    {
      std::vector<double> lepton_pt_sorted;
      for(int idxLepton = 0; idxLepton < numLeptons_; ++idxLepton)
      {
        lepton_pt_sorted.push_back(lepton_pt_[idxLepton]);
      }
      std::sort(lepton_pt_sorted.begin(), lepton_pt_sorted.end(), std::greater<int>());
      const double pt1 = lepton_pt_sorted[0];
      const double pt2 = lepton_pt_sorted[1];

      if     (numElectrons_ == 2 && numMuons_ == 0) weight = effTrigger_ee_->getSF(pt1, pt2);
      else if(numElectrons_ == 1 && numMuons_ == 1) weight = effTrigger_em_->getSF(pt1, pt2);
      else if(numElectrons_ == 0 && numMuons_ == 2) weight = effTrigger_mm_->getSF(pt1, pt2);
      else if(numLeptons_   >= 3                  ) weight = effTrigger_3l_->getSF(pt1, pt2);
      else assert(0);
    }
    else if(numElectrons_ == 1 && numMuons_ == 0)
    {
      weight = get_from_lut(effTrigger_1e_mc_, electron_pt_[0], electron_eta_[0]);
    }
    else if(numElectrons_ == 0 && numMuons_ == 1)
    {
      weight = get_from_lut(effTrigger_1m_mc_, muon_pt_[0], muon_eta_[0]);
    }
  }
  return weight;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC correction for electron and muon trigger efficiency

namespace
{
  /**
   * @brief Evaluate data/MC correction for electron and muon trigger efficiency in 2016 data (Table 4 in AN-2016/211)
   * @param type (either kElectron or kMuon), pT and eta of all leptons
   * @return data/MC scale-factor, to be applied as event weight to simulated events
   */
  double
  sf_triggerEff_2017(int numElectrons, int numMuons,
                     int lepton1_type, double lepton1_pt, double lepton1_eta,
                     int lepton2_type, double lepton2_pt, double lepton2_eta, // unused
                     int lepton3_type, double lepton3_pt, double lepton3_eta, // unused
                     const std::vector<lutWrapperBase *> & effTrigger_1e_data,
                     const std::vector<lutWrapperBase *> & effTrigger_1e_mc,
                     const std::vector<lutWrapperBase *> & effTrigger_1m_data,
                     const std::vector<lutWrapperBase *> & effTrigger_1m_mc)
  {
    double sf = 1.;
    if(numElectrons == 1 && numMuons == 0)
    {
      const double eff_data = get_from_lut(effTrigger_1e_data, lepton1_pt, lepton1_eta);
      const double eff_mc   = get_from_lut(effTrigger_1e_mc,   lepton1_pt, lepton1_eta);
      sf = aux::compSF(eff_data, eff_mc);
    }
    else if(numElectrons == 0 && numMuons == 1)
    {
      const double eff_data = get_from_lut(effTrigger_1m_data, lepton1_pt, lepton1_eta);
      const double eff_mc   = get_from_lut(effTrigger_1m_mc,   lepton1_pt, lepton1_eta);
      sf = aux::compSF(eff_data, eff_mc);
    }
    else if(numElectrons == 2 && numMuons == 0)
    {
      sf = 1.01;
    }
    else if(numElectrons == 1 && numMuons == 1)
    {
      sf = 1.01;
    }
    else if(numElectrons == 0 && numMuons == 2)
    {
      sf = 1.;
    }
    else
    {
      sf = 1.;
    }
    return sf;
  }
}

double
Data_to_MC_CorrectionInterface::getSF_leptonTriggerEff() const
{
  double sf = 1.;
  if ( era_ == kEra_2017 ) {
    sf = sf_triggerEff_2017(
      numElectrons_, numMuons_,
      lepton_type_[0], lepton_pt_[0], lepton_eta_[0],
      lepton_type_[1], lepton_pt_[1], lepton_eta_[1],
      lepton_type_[2], lepton_pt_[2], lepton_eta_[2],
      effTrigger_1e_data_, effTrigger_1e_mc_, 
      effTrigger_1m_data_, effTrigger_1m_mc_
    );
  }
  else
  {
    assert(0);
  }
  return sf;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC corrections for electron and muon identification and isolation efficiency,
// including the cut on the ttH multilepton MVA

namespace
{
  double
  getSF_leptonID_and_Iso(int numLeptons,
                         const std::vector<double> & lepton_pt,
                         const std::vector<double> & lepton_eta,
                         const std::vector<lutWrapperBase *> & corrections)
  {
    double sf = 1.;
    for(int idxLepton = 0; idxLepton < numLeptons; ++idxLepton)
    {
      const double pt = lepton_pt[idxLepton];
      const double eta = lepton_eta[idxLepton];
      sf *= get_from_lut(corrections, pt, eta);
    }
    return sf;
  }
}

double
Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_loose() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_loose_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfMuonID_and_Iso_loose_)
  ;
  return sf;
}

double
Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_fakeable_to_loose() const
{
  return 1.; // CV: no data/MC corrections for "fakeable" leptons determined yet
}

double
Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_woTightCharge() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_woTightCharge_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfElectronID_and_Iso_tight_to_loose_woTightCharge_)
  ;
  return sf;
}

double
Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_wTightCharge() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_wTightCharge_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfElectronID_and_Iso_tight_to_loose_wTightCharge_)
  ;
  return sf;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC corrections for hadronic tau identification efficiency,
// and for e->tau and mu->tau misidentification rates,
// taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV

namespace
{
  double constexpr
  getSF_hadTauID_and_Iso_2017(int hadTauSelection)
  {
    // CV: take data/MC correction to be equal to 0.95 for all WPs, following Tau POG recommendation for 2016 data,
    //     cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV
    const double sf = 0.95;
    return sf; 
  }
}

double
Data_to_MC_CorrectionInterface::getSF_hadTauID_and_Iso() const
{
  double sf = 1.;
  for(int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 15)
    {
      switch(era_)
      {
        case kEra_2017: sf *= getSF_hadTauID_and_Iso_2017(hadTauSelection_); break;
        default:        assert(0);
      }
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface::getSF_eToTauFakeRate() const
{
  double sf = 1.;
  for(int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 11)
    {
      double pt = hadTau_pt_[idxHadTau];
      double absEta = std::fabs(hadTau_eta_[idxHadTau]);
      // CV: e->tau misidentification rate has not yet been measured in 2016 data,
      //     use data/MC corrections measured in 2015 data for both data-taking periods
      sf *= sf_eToTauFakeRate_2017(pt, absEta, hadTauSelection_antiElectron_[idxHadTau], eToTauFakeRate_option_);
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface::getSF_muToTauFakeRate() const
{
  double sf = 1.;
  for(int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 13)
    {
      const double pt = hadTau_pt_[idxHadTau];
      const double absEta = std::fabs(hadTau_eta_[idxHadTau]);
      // CV: no mu->tau misidentification rate measurement available for 2015 data,
      //     use data/MC corrections measured in 2016 data for both data-taking periods
      sf *= sf_muToTauFakeRate_2017(pt, absEta, hadTauSelection_antiMuon_[idxHadTau], muToTauFakeRate_option_);
    }
  }
  return sf;
}
//-----------------------------------------------------------------------------

