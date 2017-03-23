#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile, loadTH1/TH2, get_sf_from_TH1/TH2 
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <TString.h>

#include <algorithm> // std::sort()
#include <assert.h> // assert

namespace
{
  std::string getEtaBinLabel(double etaMin, double etaMax)
  {
    TString etaBinLabel_tstring;
    if ( etaMin != -1. && etaMax != -1. ) {
      etaBinLabel_tstring = Form("%1.4gto%1.4g", etaMin, etaMax);
    } else if ( etaMin != -1. ) {
      etaBinLabel_tstring = Form("Gt%1.4g", etaMin);
    } else if ( etaMax != -1. ) {
      etaBinLabel_tstring = Form("Lt%1.4g", etaMax);
    } else assert(0);
    std::string etaBinLabel = etaBinLabel_tstring.ReplaceAll(".", "p").Data();
    return etaBinLabel;
  }

  std::string getHadTauIdxLabel(int idx)
  {
    std::string hadTauIdxLabel;
    if      ( idx == 0 ) hadTauIdxLabel = "_lead";
    else if ( idx == 1 ) hadTauIdxLabel = "_sublead";
    else if ( idx == 2 ) hadTauIdxLabel = "_third";
    else assert(0);
    return hadTauIdxLabel;
  }
}

Data_to_MC_CorrectionInterface::Data_to_MC_CorrectionInterface(const edm::ParameterSet& cfg)
  : effTrigger_ee_(0)
  , effTrigger_em_(0)
  , effTrigger_mm_(0)
  , effTrigger_3l_(0)
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
  std::string era_string = cfg.getParameter<std::string>("era");
  if      ( era_string == "2015" ) era_ = kEra_2015;
  else if ( era_string == "2016" ) era_ = kEra_2016;
  else throw cms::Exception("Data_to_MC_CorrectionInterface") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  std::string hadTauSelection_string = cfg.getParameter<std::string>("hadTauSelection");
  setHadTauSelection(hadTauSelection_string);
  for ( int idxHadTau = 0; idxHadTau < 3; ++idxHadTau ) {
    hadTauSelection_antiElectron_[idxHadTau] = -1;
    if ( cfg.exists("hadTauSelection_antiElectron") ) {
      hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiElectron");
    } else {
      std::string cfgParName = "hadTauSelection_antiElectron" + getHadTauIdxLabel(idxHadTau);
      if ( cfg.exists(cfgParName) ) hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>(cfgParName);
    }
    hadTauSelection_antiMuon_[idxHadTau] = -1;
    if ( cfg.exists("hadTauSelection_antiMuon") ) {
      hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiMuon");
    } else {
      std::string cfgParName = "hadTauSelection_antiMuon" + getHadTauIdxLabel(idxHadTau);
      if ( cfg.exists(cfgParName) ) hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>(cfgParName);
    }
  }

  std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("Data_to_MC_CorrectionInterface")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") ) {
      if      ( shiftUp_or_Down == "Up"   ) eToTauFakeRate_option_ = kFRet_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) eToTauFakeRate_option_ = kFRet_shiftDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt") ) {
      if      ( shiftUp_or_Down == "Up"   ) muToTauFakeRate_option_ = kFRmt_shiftUp;
      else if ( shiftUp_or_Down == "Down" ) muToTauFakeRate_option_ = kFRmt_shiftDown;
      else assert(0);
    } 
  }

  if ( era_ == kEra_2015 ) {
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/kinematicBinSFele.root", "MVAVLooseFO_and_IDEmu_and_TightIP2D", 
      lut::kXptYabsEta, -1., 80.));
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/kinematicBinSFele.root", "MiniIso0p4_vs_AbsEta", 
      lut::kXptYabsEta, -1., 80.));
    sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/lepMVAEffSF_e_3l.root", "sf",
      lut::kXptYabsEta, -1., 80.));
    sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/lepMVAEffSF_e_2lss.root", "sf",
      lut::kXptYabsEta, -1., 80.));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/mu_eff_recoToLoose_ttH.root", "FINAL",
      lut::kXptYabsEta, -1., 80.));
    sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/lepMVAEffSF_m_3l.root", "sf",
      lut::kXptYabsEta, -1., 80.));
    sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2015/lepMVAEffSF_m_2lss.root", "sf",
      lut::kXptYabsEta, -1., 80.));
  } else if ( era_ == kEra_2016 ) {
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "GsfElectronToMVAVLooseFOIDEmuTightIP2D",
       lut::kXptYabsEta));
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "MVAVLooseElectronToMini4",
       lut::kXptYabsEta));
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "MVAVLooseElectronToConvVetoIHit1",
       lut::kXptYabsEta));
    sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/egammaEffi.txt_EGM2D.root", "EGamma_SF2D",
       lut::kXetaYpt));
    sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_3l.root", "sf",
      lut::kXptYabsEta));
    sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_2lss.root", "sf",
      lut::kXptYabsEta));

    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "SF",
      lut::kXptYabsEta));
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root", "SF",
      lut::kXptYabsEta));
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root", "SF",
      lut::kXptYabsEta));
    sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/ratios_HIP_trkEff.root", "ratio_eta",
      lut::kXeta));				   
    sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_3l.root", "sf",
      lut::kXptYabsEta));
    sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_2lss.root", "sf",
      lut::kXptYabsEta));

    effTrigger_ee_ = new lutWrapperTH2Poly(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSee2DPt__effic",
      lut::kXptYpt); // X=pt1, Y=pt2
    effTrigger_em_ = new lutWrapperTH2Poly(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSeu2DPt_effic",
      lut::kXptYpt); // X=pt1, Y=pt2
    effTrigger_mm_ = new lutWrapperTH2Poly(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSuu2DPt_effic",
      lut::kXptYpt); // X=pt1, Y=pt2
    effTrigger_3l_ = new lutWrapperTH2Poly(
      inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "__3l2DPt_effic",
      lut::kXptYpt); // X=pt1, Y=pt2

    std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 }; 
    int numEtaBins_1e = etaBinEdges_1e.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1e[idxEtaBin];
      double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
    }

    std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    int numEtaBins_1m = etaBinEdges_1m.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1m[idxEtaBin];
      double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
    }
  } else assert(0);
}
 
namespace
{
  void clearCollection(std::vector<lutWrapperBase*>& collection)
  {
    for ( std::vector<lutWrapperBase*>::iterator it = collection.begin();
	  it != collection.end(); ++it ) {
      delete (*it);
    }
    collection.clear();
  }
}

Data_to_MC_CorrectionInterface::~Data_to_MC_CorrectionInterface()
{
  clearCollection(sfElectronID_and_Iso_loose_);
  clearCollection(sfElectronID_and_Iso_tight_to_loose_woTightCharge_);
  clearCollection(sfElectronID_and_Iso_tight_to_loose_wTightCharge_);
  clearCollection(sfMuonID_and_Iso_loose_);
  clearCollection(sfMuonID_and_Iso_tight_to_loose_woTightCharge_);
  clearCollection(sfMuonID_and_Iso_tight_to_loose_wTightCharge_);
  for ( std::map<std::string, TFile*>::iterator it = inputFiles_.begin();
        it != inputFiles_.end(); ++it ) {
    delete it->second;
  }
  delete effTrigger_ee_;
  delete effTrigger_em_;
  delete effTrigger_mm_;
  delete effTrigger_3l_;
  clearCollection(effTrigger_1e_data_);
  clearCollection(effTrigger_1e_mc_);
  clearCollection(effTrigger_1m_data_);
  clearCollection(effTrigger_1m_mc_);
}

void Data_to_MC_CorrectionInterface::setHadTauSelection(const std::string& hadTauSelection)
{
  hadTauSelection_ = -1;
  if      ( hadTauSelection == "dR03mvaVVLoose" ) hadTauSelection_ = 1;
  else if ( hadTauSelection == "dR03mvaVLoose"  ) hadTauSelection_ = 2;
  else if ( hadTauSelection == "dR03mvaLoose"   ) hadTauSelection_ = 3;
  else if ( hadTauSelection == "dR03mvaMedium"  ) hadTauSelection_ = 4;
  else if ( hadTauSelection == "dR03mvaTight"   ) hadTauSelection_ = 5;
  else if ( hadTauSelection == "dR03mvaVTight"  ) hadTauSelection_ = 6;
  else if ( hadTauSelection == "dR03mvaVVTight" ) hadTauSelection_ = 7;
  else throw cms::Exception("Data_to_MC_CorrectionInterface") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection << " !!\n";
}

void Data_to_MC_CorrectionInterface::setLeptons(int lepton1_type, double lepton1_pt, double lepton1_eta,
						int lepton2_type, double lepton2_pt, double lepton2_eta, 
						int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  numElectrons_ = 0;
  if ( lepton1_type == kElectron ) {
    electron_pt_[numElectrons_] = lepton1_pt;
    electron_eta_[numElectrons_] = lepton1_eta;
    ++numElectrons_;
  }
  if ( lepton2_type == kElectron ) {
    electron_pt_[numElectrons_] = lepton2_pt;
    electron_eta_[numElectrons_] = lepton2_eta;
    ++numElectrons_;
  } 
  if ( lepton3_type == kElectron ) {
    electron_pt_[numElectrons_] = lepton3_pt;
    electron_eta_[numElectrons_] = lepton3_eta;
    ++numElectrons_;
  } 

  numMuons_ = 0;
  if ( lepton1_type == kMuon ) {
    muon_pt_[numMuons_] = lepton1_pt;
    muon_eta_[numMuons_] = lepton1_eta;
    ++numMuons_;
  }
  if ( lepton2_type == kMuon ) {
    muon_pt_[numMuons_] = lepton2_pt;
    muon_eta_[numMuons_] = lepton2_eta;
    ++numMuons_;
  } 
  if ( lepton3_type == kMuon ) {
    muon_pt_[numMuons_] = lepton3_pt;
    muon_eta_[numMuons_] = lepton3_eta;
    ++numMuons_;
  } 

  numLeptons_ = 0;
  for ( int idxElectron = 0; idxElectron < numElectrons_; ++idxElectron ) {
    lepton_type_[numLeptons_] = kElectron;
    lepton_pt_[numLeptons_] = electron_pt_[idxElectron];
    lepton_eta_[numLeptons_] = electron_eta_[idxElectron];
    ++numLeptons_;
  }
  for ( int idxMuon = 0; idxMuon < numMuons_; ++idxMuon ) {
    lepton_type_[numLeptons_] = kMuon;
    lepton_pt_[numLeptons_] = muon_pt_[idxMuon];
    lepton_eta_[numLeptons_] = muon_eta_[idxMuon];
    ++numLeptons_;
  }
}

void Data_to_MC_CorrectionInterface::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, 
						int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta,
						int hadTau3_genPdgId, double hadTau3_pt, double hadTau3_eta)
{
  numHadTaus_ = 0;
  if ( hadTau1_pt > 0. ) {
    hadTau_genPdgId_[numHadTaus_] = hadTau1_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau1_pt;
    hadTau_eta_[numHadTaus_] = hadTau1_eta;
    ++numHadTaus_;
  }
  if ( hadTau2_pt > 0. ) {
    hadTau_genPdgId_[numHadTaus_] = hadTau2_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau2_pt;
    hadTau_eta_[numHadTaus_] = hadTau2_eta;
    ++numHadTaus_;
  }
  if ( hadTau3_pt > 0. ) {
    hadTau_genPdgId_[numHadTaus_] = hadTau3_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau3_pt;
    hadTau_eta_[numHadTaus_] = hadTau3_eta;
    ++numHadTaus_;
  }
}

//-----------------------------------------------------------------------------
// trigger efficiency turn-on curves for Spring16 non-reHLT MC
  
double Data_to_MC_CorrectionInterface::getWeight_leptonTriggerEff() const
{
  double weight = 1.;
  if ( era_ == kEra_2016 ) {
    if ( numLeptons_ >= 2 ) {
      std::vector<double> lepton_pt_sorted;
      for ( int idxLepton = 0; idxLepton < numLeptons_; ++idxLepton ) {
	lepton_pt_sorted.push_back(lepton_pt_[idxLepton]);
      }
      std::sort(lepton_pt_sorted.begin(), lepton_pt_sorted.end(), std::greater<int>());
      double pt1 = lepton_pt_sorted[0];
      double pt2 = lepton_pt_sorted[1];
      if      ( numElectrons_ == 2 && numMuons_ == 0 ) weight = effTrigger_ee_->getSF(pt1, pt2);
      else if ( numElectrons_ == 1 && numMuons_ == 1 ) weight = effTrigger_em_->getSF(pt1, pt2);
      else if ( numElectrons_ == 0 && numMuons_ == 2 ) weight = effTrigger_mm_->getSF(pt1, pt2);
      else if ( numLeptons_   >= 3                   ) weight = effTrigger_3l_->getSF(pt1, pt2);
      else assert(0);
    } else if ( numElectrons_ == 1 && numMuons_ == 0 ) {
      weight = get_from_lut(effTrigger_1e_mc_, electron_pt_[0], electron_eta_[0]);
    } else if ( numElectrons_ == 0 && numMuons_ == 1 ) {
      weight = get_from_lut(effTrigger_1m_mc_, muon_pt_[0], muon_eta_[0]);
    }
  }
  //std::cout << "<Data_to_MC_CorrectionInterface::getWeight_leptonTriggerEff>: weight = " << weight << std::endl;
  return weight;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC correction for electron and muon trigger efficiency

namespace
{
  double compSF(double eff_data, double eff_mc)
  {
    const double epsilon = 1.e-1;
    double sf = eff_data/TMath::Max(epsilon, eff_mc);
    return sf;
  }

  /**
   * @brief Evaluate data/MC correction for electron and muon trigger efficiency in 2015 data (Table 10 in AN-2015/321)
   * @param type (either kElectron or kMuon), pT and eta of all leptons
   * @return data/MC scale-factor, to be applied as event weight to simulated events
   */
  double sf_triggerEff_2015(int numElectrons, int numMuons,		     
			    int lepton1_type, double lepton1_pt, double lepton1_eta, 
			    int lepton2_type, double lepton2_pt, double lepton2_eta, 
			    int lepton3_type, double lepton3_pt, double lepton3_eta,
			    const std::vector<lutWrapperBase*>& effTrigger_1e_data, const std::vector<lutWrapperBase*>& effTrigger_1e_mc, 
			    const std::vector<lutWrapperBase*>& effTrigger_1m_data, const std::vector<lutWrapperBase*>& effTrigger_1m_mc)
  {
    double sf = 1.;
    if ( numElectrons == 1 && numMuons == 0 ) {
      double eff_data = get_from_lut(effTrigger_1e_data, lepton1_pt, lepton1_eta);
      double eff_mc = get_from_lut(effTrigger_1e_mc, lepton1_pt, lepton1_eta);
      sf = compSF(eff_data, eff_mc);
    } else if ( numElectrons == 0 && numMuons == 1 ) {
      double eff_data = get_from_lut(effTrigger_1m_data, lepton1_pt, lepton1_eta);
      double eff_mc = get_from_lut(effTrigger_1m_mc, lepton1_pt, lepton1_eta);
      sf = compSF(eff_data, eff_mc);
    } else if ( numElectrons == 2 && numMuons == 0 ) {
      if ( std::max(lepton1_pt, lepton2_pt) > 40. ) sf = 0.99;
      else sf = 0.95;
    } else if ( numElectrons == 1 && numMuons == 1 ) {
      sf = 0.98;
    } else {
      sf = 1.;
    }
    return sf;
  }

  /**
   * @brief Evaluate data/MC correction for electron and muon trigger efficiency in 2016 data (Table 4 in AN-2016/211)
   * @param type (either kElectron or kMuon), pT and eta of all leptons
   * @return data/MC scale-factor, to be applied as event weight to simulated events
   */
  double sf_triggerEff_2016(int numElectrons, int numMuons,		     
			    int lepton1_type, double lepton1_pt, double lepton1_eta, 
			    int lepton2_type, double lepton2_pt, double lepton2_eta, 
			    int lepton3_type, double lepton3_pt, double lepton3_eta,
			    const std::vector<lutWrapperBase*>& effTrigger_1e_data, const std::vector<lutWrapperBase*>& effTrigger_1e_mc, 
			    const std::vector<lutWrapperBase*>& effTrigger_1m_data, const std::vector<lutWrapperBase*>& effTrigger_1m_mc)
  {
    double sf = 1.;
    if ( numElectrons == 1 && numMuons == 0 ) {
      double eff_data = get_from_lut(effTrigger_1e_data, lepton1_pt, lepton1_eta);
      double eff_mc = get_from_lut(effTrigger_1e_mc, lepton1_pt, lepton1_eta);
      sf = compSF(eff_data, eff_mc);
    } else if ( numElectrons == 0 && numMuons == 1 ) {
      double eff_data = get_from_lut(effTrigger_1m_data, lepton1_pt, lepton1_eta);
      double eff_mc = get_from_lut(effTrigger_1m_mc, lepton1_pt, lepton1_eta);
      sf = compSF(eff_data, eff_mc);
    } else if ( numElectrons == 2 && numMuons == 0 ) {
      sf = 1.01;
    } else if ( numElectrons == 1 && numMuons == 1 ) {
      sf = 1.01;
    } else if ( numElectrons == 0 && numMuons == 2 ) {
      sf = 1.;
    } else {
      sf = 1.;
    }
    return sf;
  }
}

double Data_to_MC_CorrectionInterface::getSF_leptonTriggerEff() const
{
  double sf = 1.;
  if ( era_ == kEra_2015 ) {
    sf = sf_triggerEff_2015(
      numElectrons_, numMuons_,		     
      lepton_type_[0], lepton_pt_[0], lepton_eta_[0], 
      lepton_type_[1], lepton_pt_[1], lepton_eta_[1], 
      lepton_type_[2], lepton_pt_[2], lepton_eta_[2],
      effTrigger_1e_data_, effTrigger_1e_mc_, 
      effTrigger_1m_data_, effTrigger_1m_mc_);
  } else if ( era_ == kEra_2016 ) {
    sf = sf_triggerEff_2016(
      numElectrons_, numMuons_,	
      lepton_type_[0], lepton_pt_[0], lepton_eta_[0], 
      lepton_type_[1], lepton_pt_[1], lepton_eta_[1], 
      lepton_type_[2], lepton_pt_[2], lepton_eta_[2],
      effTrigger_1e_data_, effTrigger_1e_mc_, 
      effTrigger_1m_data_, effTrigger_1m_mc_);
  } else assert(0);
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_leptonTriggerEff>: sf = " << sf << std::endl;
  return sf;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC corrections for electron and muon identification and isolation efficiency,
// including the cut on the ttH multilepton MVA

namespace
{
  double getSF_leptonID_and_Iso(int numLeptons, const std::vector<double>& lepton_pt, const std::vector<double>& lepton_eta, 
				const std::vector<lutWrapperBase*>& corrections)
  {
    double sf = 1.;
    for ( int idxLepton = 0; idxLepton < numLeptons; ++idxLepton ) {
      double pt = lepton_pt[idxLepton];
      double eta = lepton_eta[idxLepton];
      sf *= get_from_lut(corrections, pt, eta);
    }
    return sf;
  }
}

double Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_loose() const
{
  double sf = 1.;
  sf *= getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_loose_);
  sf *= getSF_leptonID_and_Iso(numMuons_, muon_pt_, muon_eta_, sfMuonID_and_Iso_loose_);
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_loose>: sf = " << sf << std::endl;
  return sf;
}

double Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_fakeable_to_loose() const
{
  return 1.; // CV: no data/MC corrections for "fakeable" leptons determined yet
}

double Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_woTightCharge() const
{
  double sf = 1.;
  sf *= getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_woTightCharge_);
  sf *= getSF_leptonID_and_Iso(numMuons_, muon_pt_, muon_eta_, sfElectronID_and_Iso_tight_to_loose_woTightCharge_);
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_woTightCharge>: sf = " << sf << std::endl; 
  return sf;
}

double Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_wTightCharge() const
{
  double sf = 1.;
  sf *= getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_wTightCharge_);
  sf *= getSF_leptonID_and_Iso(numMuons_, muon_pt_, muon_eta_, sfElectronID_and_Iso_tight_to_loose_wTightCharge_);
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_leptonID_and_Iso_tight_to_loose_wTightCharge>: sf = " << sf << std::endl;
  return sf;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// data/MC corrections for hadronic tau identification efficiency,
// and for e->tau and mu->tau misidentification rates,
// taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV

namespace
{
  double getSF_hadTauID_and_Iso_2015(int hadTauSelection)
  {
    // CV: take data/MC correction to be equal to unity, following Tau POG recommendation for 2015 data,
    //     cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV
    return 1.; 
  }

  double getSF_hadTauID_and_Iso_2016(int hadTauSelection)
  {
    // CV: take data/MC correction to be equal to unity, following Tau POG recommendation for 2016 data,
    //     cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV
    double sf = 1.;
    if      ( hadTauSelection <= 5 ) sf = 0.99;
    else if ( hadTauSelection >= 6 ) sf = 0.91;
    return sf; 
  }
}

double Data_to_MC_CorrectionInterface::getSF_hadTauID_and_Iso() const
{
  double sf = 1.;
  for ( int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau ) {
    if ( hadTau_genPdgId_[idxHadTau] == 15 ) {
      if      ( era_ == kEra_2015 ) sf *= getSF_hadTauID_and_Iso_2015(hadTauSelection_);
      else if ( era_ == kEra_2016 ) sf *= getSF_hadTauID_and_Iso_2016(hadTauSelection_);
      else assert(0);
    }
  }
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_hadTauID_and_Iso>: sf = " << sf << std::endl;
  return sf;
}

namespace
{
  double getSF_eToTauFakeRate_2015(double hadTau_pt, double hadTau_absEta, int hadTauSelection_antiElectron, int central_or_shift)
  {
    double sf = 1.;
    double sfErr = 0.;
    if ( hadTauSelection_antiElectron <= 0 ) { // no anti-electron discriminator applied
      return sf; 
    } else if ( hadTauSelection_antiElectron == 1 ) { // vLoose
      if   ( hadTau_absEta < 1.479 ) { sf = 1.02; sfErr = 0.05; }
      else                           { sf = 1.11; sfErr = 0.05; }
    } else if ( hadTauSelection_antiElectron == 2 ) { // Loose
      if   ( hadTau_absEta < 1.479 ) { sf = 1.14; sfErr = 0.04; }
      else                           { sf = 1.09; sfErr = 0.05; }
    } else if ( hadTauSelection_antiElectron == 3 ) { // Medium
      if   ( hadTau_absEta < 1.479 ) { sf = 1.50; sfErr = 0.13; }
      else                           { sf = 1.06; sfErr = 0.18; }
    } else if ( hadTauSelection_antiElectron == 4 ) { // Tight
      if   ( hadTau_absEta < 1.479 ) { sf = 1.80; sfErr = 0.23; }
      else                           { sf = 1.30; sfErr = 0.42; }
    } else if ( hadTauSelection_antiElectron == 5 ) { // vTight
      if   ( hadTau_absEta < 1.479 ) { sf = 1.89; sfErr = 0.35; }
      else                           { sf = 1.69; sfErr = 0.68; }
    } else throw cms::Exception("getSF_eToTauFakeRate") 
	<< "Invalid parameter 'hadTauSelection_antiElectron' = " << hadTauSelection_antiElectron << " !!\n";
    if      ( central_or_shift == kFRet_shiftUp   ) sf += sfErr;
    else if ( central_or_shift == kFRet_shiftDown ) sf -= sfErr;
    else if ( central_or_shift != kFRet_central   ) throw cms::Exception("sf_eToTauFakeRate") 
      << "Invalid parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( sf < 0. ) sf = 0.; // CV: require e->tau fake-rates to be positive
    return sf;
  }

  double getSF_muToTauFakeRate_2016(double hadTau_pt, double hadTau_absEta, int hadTauSelection_antiMuon, int central_or_shift)
  {
    double sf = 1.;
    double sfErr = 0.;
    if ( hadTauSelection_antiMuon <= 0 ) { // no anti-muon discriminator applied
      return sf; 
    } else if ( hadTauSelection_antiMuon == 1 ) { // Loose
      if      ( hadTau_absEta < 0.4 ) { sf = 1.15; sfErr = 0.05; }
      else if ( hadTau_absEta < 0.8 ) { sf = 1.15; sfErr = 0.05; }
      else if ( hadTau_absEta < 1.2 ) { sf = 1.18; sfErr = 0.05; }
      else if ( hadTau_absEta < 1.7 ) { sf = 1.20; sfErr = 0.20; }
      else if ( hadTau_absEta < 2.3 ) { sf = 1.30; sfErr = 0.30; }
    } else if ( hadTauSelection_antiMuon == 2 ) { // Tight
      if      ( hadTau_absEta < 0.4 ) { sf = 1.50; sfErr = 0.10; }
      else if ( hadTau_absEta < 0.8 ) { sf = 1.40; sfErr = 0.10; }
      else if ( hadTau_absEta < 1.2 ) { sf = 1.21; sfErr = 0.06; }
      else if ( hadTau_absEta < 1.7 ) { sf = 2.60; sfErr = 0.90; }
      else if ( hadTau_absEta < 2.3 ) { sf = 2.10; sfErr = 0.90; }
    } else throw cms::Exception("getSF_muToTauFakeRate") 
	<< "Invalid parameter 'hadTauSelection_antiMuon' = " << hadTauSelection_antiMuon << " !!\n";
    if      ( central_or_shift == kFRet_shiftUp   ) sf += sfErr;
    else if ( central_or_shift == kFRet_shiftDown ) sf -= sfErr;
    else if ( central_or_shift != kFRet_central   ) throw cms::Exception("sf_muToTauFakeRate") 
      << "Invalid parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( sf < 0. ) sf = 0.; // CV: require mu->tau fake-rates to be positive
    return sf;
  }
}

double Data_to_MC_CorrectionInterface::getSF_eToTauFakeRate() const
{
  double sf = 1.;
  for ( int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau ) {
    if ( hadTau_genPdgId_[idxHadTau] == 11 ) {
      double pt = hadTau_pt_[idxHadTau];
      double absEta = std::fabs(hadTau_eta_[idxHadTau]);
      // CV: e->tau misidentification rate has not yet been measured in 2016 data,
      //     use data/MC corrections measured in 2015 data for both data-taking periods
      sf *= getSF_eToTauFakeRate_2015(pt, absEta, hadTauSelection_antiElectron_[idxHadTau], eToTauFakeRate_option_);
    }
  }
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_eToTauFakeRate>: sf = " << sf << std::endl;
  return sf;
}

double Data_to_MC_CorrectionInterface::getSF_muToTauFakeRate() const
{
  double sf = 1.;
  for ( int idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau ) {
    if ( hadTau_genPdgId_[idxHadTau] == 13 ) {
      double pt = hadTau_pt_[idxHadTau];
      double absEta = std::fabs(hadTau_eta_[idxHadTau]);
      // CV: no mu->tau misidentification rate measurement available for 2015 data,
      //     use data/MC corrections measured in 2016 data for both data-taking periods
      sf *= getSF_muToTauFakeRate_2016(pt, absEta, hadTauSelection_antiMuon_[idxHadTau], muToTauFakeRate_option_);
    }
  }
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_muToTauFakeRate>: sf = " << sf << std::endl;
  return sf;
}
//-----------------------------------------------------------------------------

