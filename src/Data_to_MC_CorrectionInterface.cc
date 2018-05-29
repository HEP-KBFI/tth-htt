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
// - update all data/MC corrections for 2017 data & MC
// - rename the functions where possible

Data_to_MC_CorrectionInterface::Data_to_MC_CorrectionInterface(const edm::ParameterSet & cfg)
  : hadTauSelection_(-1)
  , eToTauFakeRate_option_(FRet::central)
  , muToTauFakeRate_option_(FRmt::central)
  , numLeptons_(0)
  , lepton_type_(4)
  , lepton_pt_(4)
  , lepton_eta_(4)
  , numElectrons_(0)
  , electron_pt_(4)
  , electron_eta_(4)
  , numMuons_(0)
  , muon_pt_(4)
  , muon_eta_(4)
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

  eToTauFakeRate_option_ = getEToTauFR_option(central_or_shift, true);
  muToTauFakeRate_option_ = getMuToTauFR_option(central_or_shift, true);

  if(era_ == kEra_2017)
  {
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptLt20.root",
      "EGamma_SF2D",
      lut::kXetaYpt, -2.5, +2.5, lut::kLimit, -1., 20., lut::kLimit_and_Cut
    ));
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptGt20.root",
      "EGamma_SF2D",
      lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 20., -1., lut::kLimit_and_Cut
    ));

    sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_e_3l.root",
      "sf",
      lut::kXptYabsEta
    ));
    sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_e_2lss.root",
      "sf",
      lut::kXptYabsEta
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptLt10.root",
      "ratio_eff_eta3_tk0_dr030e030_corr",
      lut::kXetaYpt, -2.4, +2.4, lut::kLimit, -1., 10., lut::kCut
    ));
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptGt10.root",
      "ratio_eff_eta3_dr030e030_corr",
      lut::kXetaYpt, -2.4, +2.4, lut::kLimit, 10., -1., lut::kCut
    ));
    
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptLt30.root",
      "NUM_LooseID_DEN_genTracks_pt_abseta",
      lut::kXptYabsEta, -1., 30., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
    ));
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptGt30.root",
      "NUM_LooseID_DEN_genTracks_pt_abseta",
      lut::kXptYabsEta, 30., -1., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
    ));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkVtxCut_and_isoEff.root",
      "NUM_ttHLoo_DEN_LooseID",
      lut::kXptYabsEta, 10., 120., lut::kLimit, 0., 2.4, lut::kLimit
    ));

    sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_m_3l.root",
      "sf",
      lut::kXptYabsEta
    ));
    sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_m_2lss.root",
      "sf",
      lut::kXptYabsEta
    ));
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
                                           int lepton3_type, double lepton3_pt, double lepton3_eta,
                                           int lepton4_type, double lepton4_pt, double lepton4_eta)
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
  if(lepton4_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton4_pt;
    electron_eta_[numElectrons_] = lepton4_eta;
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
  if(lepton4_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton4_pt;
    muon_eta_[numMuons_] = lepton4_eta;
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
                     int lepton2_type, double lepton2_pt, double lepton2_eta, 
                     int lepton3_type, double lepton3_pt, double lepton3_eta, // unused
		     int lepton4_type, double lepton4_pt, double lepton4_eta) // unused
  {
    double sf = 1.;
    if(numElectrons == 2 && numMuons == 0)
    {
      double lepton_pt_lead = TMath::Max(lepton1_pt, lepton2_pt);
      if   ( lepton_pt_lead >= 30. ) sf = 0.991;
      else                           sf = 0.937;
    }
    else if(numElectrons == 1 && numMuons == 1)
    {
      double lepton_pt_lead = TMath::Max(lepton1_pt, lepton2_pt);
      if      ( lepton_pt_lead >= 50. ) sf = 1.000;
      else if ( lepton_pt_lead >= 50. ) sf = 0.983;
      else                              sf = 0.952;
    }
    else if(numElectrons == 0 && numMuons == 2)
    {
      double lepton_pt_lead = TMath::Max(lepton1_pt, lepton2_pt);
      if   ( lepton_pt_lead >= 35. ) sf = 0.994;
      else                           sf = 0.972;
    }
    else if ((numElectrons + numMuons) >= 3)
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
      lepton_type_[3], lepton_pt_[3], lepton_eta_[3]);
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
    //std::cout << "<getSF_hadTauID_and_Iso_2017>:" << std::endl;
    //std::cout << " hadTauSelection = " << hadTauSelection << std::endl;

    // CV: take data/MC (SF) measured for MVA-based tau ID with dR = 0.5 from
    //       https://indico.cern.ch/event/719250/contributions/2971854/attachments/1635435/2609013/tauid_recommendations2017.pdf 
    //     as the SF for MVA-based tau ID with dR = 0.3 have not been measured yet.

    double sf = 1.;
    double sfErr = 0.;

    if      ( hadTauSelection == 1 ) { sf = 0.85; sfErr = 0.05; } // take SF for dR03mvaVLoose, as SF for dR03mvaVVLoose has not been measured yet
    else if ( hadTauSelection == 2 ) { sf = 0.85; sfErr = 0.05; } // dR03mvaVLoose
    else if ( hadTauSelection == 3 ) { sf = 0.89; sfErr = 0.05; } // dR03mvaLoose
    else if ( hadTauSelection == 4 ) { sf = 0.89; sfErr = 0.05; } // dR03mvaMedium
    else if ( hadTauSelection == 5 ) { sf = 0.87; sfErr = 0.05; } // dR03mvaTight
    else if ( hadTauSelection == 6 ) { sf = 0.85; sfErr = 0.05; } // dR03mvaVTight
    else if ( hadTauSelection == 7 ) { sf = 0.82; sfErr = 0.05; } // dR03mvaVVTight
    //std::cout << " sf = " << sf << " +/- " << sfErr << std::endl;
    assert(sfErr >= 0); // CV: used just to avoid compilation errors due to "variable 'sfErr' set but not used"

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
      if ( era_ == kEra_2017 ) {
	sf *= sf_eToTauFakeRate_2017(pt, absEta, hadTauSelection_antiElectron_[idxHadTau], eToTauFakeRate_option_);
      } else assert(0);
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
      if ( era_ == kEra_2017 ) {
	sf *= sf_muToTauFakeRate_2017(pt, absEta, hadTauSelection_antiMuon_[idxHadTau], muToTauFakeRate_option_);
      } else assert(0);
    }
  }
  return sf;
}
//-----------------------------------------------------------------------------

