#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h" // TauIDSFTool

#include <cmath> // std::fabs(), std::sqrt()

Data_to_MC_CorrectionInterface_2017::Data_to_MC_CorrectionInterface_2017(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
  // Reconstruction efficiencies of electrons with pT < 20 GeV, measured by EGamma POG
  // https://twiki.cern.ch/twiki/pub/CMS/Egamma2017DataRecommendations/egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptLt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, -1., 20., lut::kLimit_and_Cut
  ));
  // Reconstruction efficiencies of electrons with pT > 20 GeV, measured by EGamma POG
  // https://twiki.cern.ch/twiki/pub/CMS/Egamma2017DataRecommendations/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptGt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 20., -1., lut::kLimit_and_Cut
  ));

  // Efficiency of electron isolation (and track vertex cuts)?
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_trkVtxCut_and_isoEff.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 10., 500., lut::kLimit
  ));

  // Loose-to-tight electron ID SFs, measured by the CERN group
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

  // Tracking efficiency for muons with pT < 10 GeV, measured by Muon POG (?)
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptLt10.root",
    "ratio_eff_eta3_tk0_dr030e030_corr",
    lut::kXetaYpt, -2.4, +2.4, lut::kLimit, -1., 10., lut::kCut
  ));
  // Tracking efficiency for muons with pT > 10 GeV, measured by Muon POG (?)
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptGt10.root",
    "ratio_eff_eta3_dr030e030_corr",
    lut::kXetaYpt, -2.4, +2.4, lut::kLimit, 10., -1., lut::kCut
  ));

  // Identification efficiencies of loose muons with pT < 20 GeV, measured by Muon POG
  // https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ID_JPsi.root
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptLt20.root",
    "NUM_LooseID_DEN_genTracks_pt_abseta",
    lut::kXptYabsEta, -1., 20., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
  ));
  // Identification efficiencies of loose muons with pT > 20 GeV, measured by Muon POG
  // https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ID.root
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptGt20.root",
    "NUM_LooseID_DEN_genTracks_pt_abseta",
    lut::kXptYabsEta, 20., -1., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
  ));

  // Efficiency of muon isolation (and track vertex cuts)
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkVtxCut_and_isoEff.root",
    "NUM_ttHLoo_DEN_LooseID",
    lut::kXptYabsEta, 10., 120., lut::kLimit, 0., 2.4, lut::kLimit
  ));

  // Loose-to-tight muon ID SFs, measured by the CERN group
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

  if(applyHadTauSF_)
  {
    const std::string tauIDSFTool_era = "2017ReReco";
    tauIdSFs_ = new TauIDSFTool(tauIDSFTool_era, tauIDSF_str_, tauIDSF_level_str_, false);
    initAntiEle_tauIDSFs(tauIDSFTool_era);
    initAntiMu_tauIDSFs(tauIDSFTool_era);
  }
}

Data_to_MC_CorrectionInterface_2017::~Data_to_MC_CorrectionInterface_2017()
{}

double
Data_to_MC_CorrectionInterface_2017::getWeight_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2017 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2017::getSF_leptonTriggerEff(TriggerSFsys central_or_shift) const
{
  // see Table 12 in AN2018/098v18
  double sf = 1.;
  double sfErr = 0.;

  const double lepton_pt_lead = std::max(lepton_pt_[0], lepton_pt_[1]);
  if(numElectrons_ == 2 && numMuons_ == 0)
  {
    if  (lepton_pt_lead >= 30.) { sf = 0.991; sfErr = 0.002; }
    else                        { sf = 0.937; sfErr = 0.027; }
  }
  else if(numElectrons_ == 1 && numMuons_ == 1)
  {
    if     (lepton_pt_lead >= 50.) { sf = 1.000; sfErr = 0.001; }
    else if(lepton_pt_lead >= 35.) { sf = 0.983; sfErr = 0.003; }
    else                           { sf = 0.952; sfErr = 0.008; }
  }
  else if(numElectrons_ == 0 && numMuons_ == 2)
  {
    if  (lepton_pt_lead >= 35.) { sf = 0.994; sfErr = 0.001; }
    else                        { sf = 0.972; sfErr = 0.006; }
  }
  else if((numElectrons_ + numMuons_) >= 3)
  {
    sf = 1.;
    sfErr = 0.050;
  }

  switch(central_or_shift)
  {
    case TriggerSFsys::central:   return sf;
    case TriggerSFsys::shiftUp:   return sf + sfErr;
    case TriggerSFsys::shiftDown: return sf - sfErr;
    default: throw cmsException(this, __func__, __LINE__)
                     << "Invalid option: " << static_cast<int>(central_or_shift)
                   ;
  }

  return sf;
}
