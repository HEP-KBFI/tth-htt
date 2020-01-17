#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::

#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h" // TauIDSFTool

#include <cmath> // std::sqrt()

Data_to_MC_CorrectionInterface_2016::Data_to_MC_CorrectionInterface_2016(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
  // Reconstruction efficiencies of electrons with pT < 20 GeV, measured by EGamma POG
  // https://twiki.cern.ch/twiki/pub/CMS/EgammaIDRecipesRun2/EGM2D_BtoH_low_RecoSF_Legacy2016.root
  // Downloaded from: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2?rev=104#80X_series_80X_Scale_factors_for
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_gsf_ptLt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, -1., 20., lut::kLimit_and_Cut
  ));
  // Reconstruction efficiencies of electrons with pT > 20 GeV, measured by EGamma POG
  // https://twiki.cern.ch/twiki/pub/CMS/EgammaIDRecipesRun2/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_gsf_ptGt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 20., -1., lut::kLimit_and_Cut
  ));
  // Loose electron SFs, measured by the CERN group
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_loose_ele_2016.root
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_loose_ele_2016.root",
    "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_loosettH_ele_2016.root
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_loosettH_ele_2016.root",
    "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));

  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_ttH_ele_2016_3l/passttH/egammaEffi.txt_EGM2D.root
  sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_3l.root", "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_ttH_ele_2016_2lss/passttH/egammaEffi.txt_EGM2D.root
  sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_2lss.root", "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));
  // combined
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/error/SFttbar_2016_ele_pt.root
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/error/SFttbar_2016_ele_eta.root
  sfElectronID_and_Iso_tight_to_loose_errors_up_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_error.root", "histo_eff_data_max",
    lut::kXabsEtaYpt
  ));
  sfElectronID_and_Iso_tight_to_loose_errors_down_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_error.root", "histo_eff_data_min",
    lut::kXabsEtaYpt
  ));

  // Loose muon SFs, measured by the CERN group
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_loose_muon_2016.root",
    "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));

  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_ttH_muon_2016_3l/passttH/egammaEffi.txt_EGM2D.root
  sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_3l.root", "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/TnP_ttH_muon_2016_2lss/passttH/egammaEffi.txt_EGM2D.root
  sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_2lss.root", "EGamma_SF2D",
    lut::kXabsEtaYpt
  ));
  // combined
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/error/SFttbar_2016_muon_pt.root
  // /afs/cern.ch/user/b/balvarez/work/public/ttHAnalysis/error/SFttbar_2016_muon_eta.root
  sfMuonID_and_Iso_tight_to_loose_errors_up_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_error.root", "histo_eff_data_max",
    lut::kXabsEtaYpt
  ));
  sfMuonID_and_Iso_tight_to_loose_errors_down_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_error.root", "histo_eff_data_min",
    lut::kXabsEtaYpt
  ));

  const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
  assert(etaBinEdges_1e.size() > 0);
  const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;
  for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
  {
    const double etaMin = etaBinEdges_1e[idxEtaBin];
    const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
    const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
    effTrigger_1e_data_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
      Form("ZMassEta%s_Data", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
    effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
      Form("ZMassEta%s_MC", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
  }

  const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
  assert(etaBinEdges_1m.size() > 0);
  const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;
  for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
  {
    const double etaMin = etaBinEdges_1m[idxEtaBin];
    const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
    const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
    effTrigger_1m_data_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
      Form("ZMassEta%s_Data", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
    effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
      Form("ZMassEta%s_MC", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
  }

  if(applyHadTauSF_)
  {
    const std::string tauIDSFTool_era = "2016Legacy";
    tauIdSFs_ = new TauIDSFTool(tauIDSFTool_era, tauIDSF_str_, tauIDSF_level_str_, false);
    initAntiEle_tauIDSFs(tauIDSFTool_era);
    initAntiMu_tauIDSFs(tauIDSFTool_era);
  }
}

Data_to_MC_CorrectionInterface_2016::~Data_to_MC_CorrectionInterface_2016()
{}

double
Data_to_MC_CorrectionInterface_2016::getSF_leptonTriggerEff(TriggerSFsys central_or_shift) const
{
  // see https://cernbox.cern.ch/index.php/s/lW2BiTli5tJR0MN
  double sf = 1.;
  double sfErr = 0.;

  const double lepton_cone_pt_sublead = std::min(lepton_cone_pt_[0], lepton_cone_pt_[1]);
  if(numElectrons_ == 2 && numMuons_ == 0)
  {
    if  (lepton_cone_pt_sublead >= 25.) { sf = 1.000; }
    else                                { sf = 0.980; }
    sfErr = 2.;
  }
  else if(numElectrons_ == 1 && numMuons_ == 1)
  {
    sf = 1.000;
    sfErr = 1.;
  }
  else if(numElectrons_ == 0 && numMuons_ == 2)
  {
    sf = 0.990;
    sfErr = 1.;
  }
  else if((numElectrons_ + numMuons_) >= 3)
  {
    sf = 1.;
    sfErr = 1.;
  }

  sfErr /= 100.;
  switch(central_or_shift)
  {
    case TriggerSFsys::central:   return sf;
    case TriggerSFsys::shiftUp:   return sf * (1. + sfErr);
    case TriggerSFsys::shiftDown: return sf * (1. - sfErr);
    default: throw cmsException(this, __func__, __LINE__)
                     << "Invalid option: " << static_cast<int>(central_or_shift)
                   ;
  }

  return sf;
}
