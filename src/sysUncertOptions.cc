#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

#include <TString.h> // Form()

#include <boost/algorithm/string/predicate.hpp> // boost::algorithm::starts_with(), boost::algorithm::ends_with()

bool
isValidJESsource(int era,
                 int central_or_shift)
{
  assert(era == kEra_2016 || era == kEra_2017 || era == kEra_2018);
  if((central_or_shift == kJetMET_jesAbsoluteSampleUp || central_or_shift == kJetMET_jesAbsoluteSampleDown) && era != kEra_2018) return false;
  if((central_or_shift == kJetMET_jesTimeRunBUp       || central_or_shift == kJetMET_jesTimeRunBDown)       && era != kEra_2017) return false;
  if((central_or_shift == kJetMET_jesTimeRunBCDUp     || central_or_shift == kJetMET_jesTimeRunBCDDown)     && era != kEra_2016) return false;
  if((central_or_shift == kJetMET_jesTimeRunCUp       || central_or_shift == kJetMET_jesTimeRunCDown)       && era != kEra_2017) return false;
  if((central_or_shift == kJetMET_jesTimeRunDEUp      || central_or_shift == kJetMET_jesTimeRunDEDown)      && era != kEra_2017) return false;
  if((central_or_shift == kJetMET_jesTimeRunEFUp      || central_or_shift == kJetMET_jesTimeRunEFDown)      && era != kEra_2016) return false;
  if((central_or_shift == kJetMET_jesTimeRunFUp       || central_or_shift == kJetMET_jesTimeRunFDown)       && era != kEra_2017) return false;
  if((central_or_shift == kJetMET_jesTimeRunGHUp      || central_or_shift == kJetMET_jesTimeRunGHDown)      && era != kEra_2016) return false;
  return true;
}

int
getBTagWeight_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kBtag_central;
  if     (central_or_shift == "CMS_ttHl_btag_HFUp"        ) central_or_shift_int = kBtag_hfUp;
  else if(central_or_shift == "CMS_ttHl_btag_HFDown"      ) central_or_shift_int = kBtag_hfDown;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats1Up"  ) central_or_shift_int = kBtag_hfStats1Up;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats1Down") central_or_shift_int = kBtag_hfStats1Down;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats2Up"  ) central_or_shift_int = kBtag_hfStats2Up;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats2Down") central_or_shift_int = kBtag_hfStats2Down;
  else if(central_or_shift == "CMS_ttHl_btag_LFUp"        ) central_or_shift_int = kBtag_lfUp;
  else if(central_or_shift == "CMS_ttHl_btag_LFDown"      ) central_or_shift_int = kBtag_lfDown;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats1Up"  ) central_or_shift_int = kBtag_lfStats1Up;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats1Down") central_or_shift_int = kBtag_lfStats1Down;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats2Up"  ) central_or_shift_int = kBtag_lfStats2Up;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats2Down") central_or_shift_int = kBtag_lfStats2Down;
  else if(central_or_shift == "CMS_ttHl_btag_cErr1Up"     ) central_or_shift_int = kBtag_cErr1Up;
  else if(central_or_shift == "CMS_ttHl_btag_cErr1Down"   ) central_or_shift_int = kBtag_cErr1Down;
  else if(central_or_shift == "CMS_ttHl_btag_cErr2Up"     ) central_or_shift_int = kBtag_cErr2Up;
  else if(central_or_shift == "CMS_ttHl_btag_cErr2Down"   ) central_or_shift_int = kBtag_cErr2Down;
  else if(central_or_shift == "CMS_ttHl_JESUp"            ) central_or_shift_int = kBtag_jesUp;
  else if(central_or_shift == "CMS_ttHl_JESDown"          ) central_or_shift_int = kBtag_jesDown; 
  return central_or_shift_int;
}

int
getJet_option(const std::string & central_or_shift,
              bool isMC)
{
  int central_or_shift_int = isMC ? kJetMET_central : kJetMET_central_nonNominal;
  if     (central_or_shift == "CMS_ttHl_JESUp"  ) central_or_shift_int = kJetMET_jesUp;
  else if(central_or_shift == "CMS_ttHl_JESDown") central_or_shift_int = kJetMET_jesDown;
  else if(central_or_shift == "CMS_ttHl_JERUp"  ) central_or_shift_int = kJetMET_jerUp;
  else if(central_or_shift == "CMS_ttHl_JERDown") central_or_shift_int = kJetMET_jerDown;
  return central_or_shift_int;
}

int
getMET_option(const std::string & central_or_shift,
              bool isMC)
{
  int central_or_shift_int = isMC ? kJetMET_central : kJetMET_central_nonNominal;
  if     (central_or_shift == "CMS_ttHl_JESUp"            ) central_or_shift_int = kJetMET_jesUp;
  else if(central_or_shift == "CMS_ttHl_JESDown"          ) central_or_shift_int = kJetMET_jesDown;
  else if(central_or_shift == "CMS_ttHl_JERUp"            ) central_or_shift_int = kJetMET_jerUp;
  else if(central_or_shift == "CMS_ttHl_JERDown"          ) central_or_shift_int = kJetMET_jerDown;
  else if(central_or_shift == "CMS_ttHl_UnclusteredEnUp"  ) central_or_shift_int = kJetMET_UnclusteredEnUp;
  else if(central_or_shift == "CMS_ttHl_UnclusteredEnDown") central_or_shift_int = kJetMET_UnclusteredEnDown;
  return central_or_shift_int;
}

int
getHadTauPt_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kHadTauPt_central;
  if     (central_or_shift == "CMS_ttHl_tauESUp"  ) central_or_shift_int = kHadTauPt_shiftUp;
  else if(central_or_shift == "CMS_ttHl_tauESDown") central_or_shift_int = kHadTauPt_shiftDown;
  return central_or_shift_int;
}

int
getJetToTauFR_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kFRjt_central;
  if     (central_or_shift == "CMS_ttHl_FRjt_normUp"   ) central_or_shift_int = kFRjt_normUp;
  else if(central_or_shift == "CMS_ttHl_FRjt_normDown" ) central_or_shift_int = kFRjt_normDown;
  else if(central_or_shift == "CMS_ttHl_FRjt_shapeUp"  ) central_or_shift_int = kFRjt_shapeUp;
  else if(central_or_shift == "CMS_ttHl_FRjt_shapeDown") central_or_shift_int = kFRjt_shapeDown;
  return central_or_shift_int;
}

FRet
getEToTauFR_option(const std::string & central_or_shift)
{
  FRet central_or_shift_int = FRet::central;
  if     (central_or_shift == "CMS_ttHl_FRet_shiftUp"  ) central_or_shift_int = FRet::shiftUp;
  else if(central_or_shift == "CMS_ttHl_FRet_shiftDown") central_or_shift_int = FRet::shiftDown;
  return central_or_shift_int;
}

FRmt
getMuToTauFR_option(const std::string & central_or_shift)
{
  FRmt central_or_shift_int = FRmt::central;
  if     (central_or_shift == "CMS_ttHl_FRmt_shiftUp"  ) central_or_shift_int = FRmt::shiftUp;
  else if(central_or_shift == "CMS_ttHl_FRmt_shiftDown") central_or_shift_int = FRmt::shiftDown;
  return central_or_shift_int;
}

TauIDSFsys
getTauIDSFsys_option(const std::string & central_or_shift)
{
  TauIDSFsys central_or_shift_int = TauIDSFsys::central;
  if     (central_or_shift == "CMS_ttHl_tauIDSFUp"  ) central_or_shift_int = TauIDSFsys::shiftUp;
  else if(central_or_shift == "CMS_ttHl_tauIDSFDown") central_or_shift_int = TauIDSFsys::shiftDown;
  return central_or_shift_int;
}

TriggerSFsys
getTriggerSF_option(const std::string & central_or_shift)
{
  TriggerSFsys central_or_shift_int = TriggerSFsys::central;
  if     (central_or_shift == "CMS_ttHl_triggerUp"  ) central_or_shift_int = TriggerSFsys::shiftUp;
  else if(central_or_shift == "CMS_ttHl_triggerDown") central_or_shift_int = TriggerSFsys::shiftDown;
  return central_or_shift_int;
}

int
getLHEscale_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kLHE_scale_central;
  if(boost::starts_with(central_or_shift, "CMS_ttHl_thu_shape"))
  {
    if     (boost::ends_with(central_or_shift, "x1Down")) central_or_shift_int = kLHE_scale_xDown;
    else if(boost::ends_with(central_or_shift, "x1Up")  ) central_or_shift_int = kLHE_scale_xUp;
    else if(boost::ends_with(central_or_shift, "y1Down")) central_or_shift_int = kLHE_scale_yDown;
    else if(boost::ends_with(central_or_shift, "y1Up")  ) central_or_shift_int = kLHE_scale_yUp;
    else throw cmsException(__func__, __LINE__)
           << "Invalid option to LHE systematics: " << central_or_shift;
  }
  return central_or_shift_int;
}

int
getElectronPt_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kElectronPt_central;
  if     (central_or_shift == "CMS_ttHl_electronESBarrelUp"  ) central_or_shift_int = kElectronPt_scaleUp_barrel;
  else if(central_or_shift == "CMS_ttHl_electronESBarrelDown") central_or_shift_int = kElectronPt_scaleDown_barrel;
  else if(central_or_shift == "CMS_ttHl_electronESEndcapUp"  ) central_or_shift_int = kElectronPt_scaleUp_endcap;
  else if(central_or_shift == "CMS_ttHl_electronESEndcapDown") central_or_shift_int = kElectronPt_scaleDown_endcap;
  else if(central_or_shift == "CMS_ttHl_electronERUp"        ) central_or_shift_int = kElectronPt_resUp;
  else if(central_or_shift == "CMS_ttHl_electronERDown"      ) central_or_shift_int = kElectronPt_resDown;
  return central_or_shift_int;
}

int
getMuon_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kMuon_central;
  if     (central_or_shift == "CMS_ttHl_muonERUp"         ) central_or_shift_int = kMuon_ERUp;
  else if(central_or_shift == "CMS_ttHl_muonERDown"       ) central_or_shift_int = kMuon_ERDown;
  else if(central_or_shift == "CMS_ttHl_muonESBarrel1Up"  ) central_or_shift_int = kMuon_ESBarrel1Up;
  else if(central_or_shift == "CMS_ttHl_muonESBarrel1Down") central_or_shift_int = kMuon_ESBarrel1Down;
  else if(central_or_shift == "CMS_ttHl_muonESBarrel2Up"  ) central_or_shift_int = kMuon_ESBarrel2Up;
  else if(central_or_shift == "CMS_ttHl_muonESBarrel2Down") central_or_shift_int = kMuon_ESBarrel2Down;
  else if(central_or_shift == "CMS_ttHl_muonESEndcap1Up"  ) central_or_shift_int = kMuon_ESEndcap1Up;
  else if(central_or_shift == "CMS_ttHl_muonESEndcap1Down") central_or_shift_int = kMuon_ESEndcap1Down;
  else if(central_or_shift == "CMS_ttHl_muonESEndcap2Up"  ) central_or_shift_int = kMuon_ESEndcap2Up;
  else if(central_or_shift == "CMS_ttHl_muonESEndcap2Down") central_or_shift_int = kMuon_ESEndcap2Down;
  return central_or_shift_int;
}

int
getJetToLeptonFR_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kFRl_central;
  if     (central_or_shift == "CMS_ttHl_FRe_shape_ptUp"          ) central_or_shift_int = kFRe_shape_ptUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_ptDown"        ) central_or_shift_int = kFRe_shape_ptDown;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_normUp"        ) central_or_shift_int = kFRe_shape_normUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_normDown"      ) central_or_shift_int = kFRe_shape_normDown;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_eta_barrelUp"  ) central_or_shift_int = kFRe_shape_eta_barrelUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_eta_barrelDown") central_or_shift_int = kFRe_shape_eta_barrelDown;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_ptUp"          ) central_or_shift_int = kFRm_shape_ptUp;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_ptDown"        ) central_or_shift_int = kFRm_shape_ptDown;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_normUp"        ) central_or_shift_int = kFRm_shape_normUp;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_normDown"      ) central_or_shift_int = kFRm_shape_normDown;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_eta_barrelUp"  ) central_or_shift_int = kFRm_shape_eta_barrelUp;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_eta_barrelDown") central_or_shift_int = kFRm_shape_eta_barrelDown;
  return central_or_shift_int;
}

PUsys
getPUsys_option(const std::string & central_or_shift)
{
  PUsys central_or_shift_int = PUsys::central;
  if     (central_or_shift == "CMS_ttHl_pileupUp"  ) central_or_shift_int = PUsys::up;
  else if(central_or_shift == "CMS_ttHl_pileupDown") central_or_shift_int = PUsys::down;
  return central_or_shift_int;
}


L1PreFiringWeightSys
getL1PreFiringWeightSys_option(const std::string & central_or_shift)
{
  L1PreFiringWeightSys central_or_shift_int = L1PreFiringWeightSys::nominal;
  if     (central_or_shift == "CMS_ttHl_l1PreFireUp")   central_or_shift_int = L1PreFiringWeightSys::up;
  else if(central_or_shift == "CMS_ttHl_l1PreFireDown") central_or_shift_int = L1PreFiringWeightSys::down;
  return central_or_shift_int;
}

int
getDYMCReweighting_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kDYMCReweighting_central;
  if     (central_or_shift == "CMS_ttHl_DYMCReweightingUp"  ) central_or_shift_int = kDYMCReweighting_shiftUp;
  else if(central_or_shift == "CMS_ttHl_DYMCReweightingDown") central_or_shift_int = kDYMCReweighting_shiftDown;
  return central_or_shift_int;
}

int
getDYMCNormScaleFactors_option(const std::string & central_or_shift)
{
  int central_or_shift_int = kDYMCNormScaleFactors_central;
  if     (central_or_shift == "CMS_ttHl_DYMCNormScaleFactorsUp"  ) central_or_shift_int = kDYMCNormScaleFactors_shiftUp;
  else if(central_or_shift == "CMS_ttHl_DYMCNormScaleFactorsDown") central_or_shift_int = kDYMCNormScaleFactors_shiftDown;
  return central_or_shift_int;
}

void
checkOptionValidity(const std::string & central_or_shift,
                    bool isMC)
{
  if(! (central_or_shift.empty() || central_or_shift == "central"))
  {
    if(! isMC && getJetToLeptonFR_option(central_or_shift) != kFRl_central && getJetToTauFR_option(central_or_shift) != kFRjt_central)
    {
      throw cmsException(__func__, __LINE__) << "Non-empty or non-central systematics option passed to data";
    }
    if(isMC && ! (boost::ends_with(central_or_shift, "Up") || boost::ends_with(central_or_shift, "Down")))
    {
      throw cmsException(__func__, __LINE__) << "Non-central MC systematics option not ending with Up or Down";
    }
  }
}

std::string
getBranchName_bTagWeight(Btag btag,
                         const std::string & default_collectionName,
                         int central_or_shift)
{
  std::map<int, std::string> branchNames_bTagWeight;
  std::string discrName;
  switch(btag)
  {
    case Btag::kDeepJet: discrName = "deepjet"; break;
    case Btag::kDeepCSV: discrName = "deepcsv"; break;
    case Btag::kCSVv2:   discrName = "csvv2";   break;
  }
  branchNames_bTagWeight[kBtag_central] = Form("%s_btagSF_%s_shape", default_collectionName.data(), discrName.data());
  branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "_up_hf";
  branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "_down_hf";
  branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_up_hfstats1";
  branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_down_hfstats1";
  branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_up_hfstats2";
  branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_down_hfstats2";
  branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "_up_lf";
  branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "_down_lf";
  branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_up_lfstats1";
  branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_down_lfstats1";
  branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_up_lfstats2";
  branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_down_lfstats2";
  branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "_up_cferr1";
  branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "_down_cferr1";
  branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "_up_cferr2";
  branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "_down_cferr2";
  branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "_up_jes";
  branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "_down_jes";
  assert(branchNames_bTagWeight.count(central_or_shift));
  return branchNames_bTagWeight.at(central_or_shift);
}

std::string
getBranchName_jetMET(const std::string & default_branchName,
                        int era,
                        int central_or_shift,
                        bool isPt)
{
  static std::map<int, std::string> branchNames_sys;
  const bool isJet = default_branchName == "Jet";
  const bool isMET = default_branchName == "MET";
  if(! isJet && ! isMET)
  {
    throw cmsException(__func__, __LINE__) << "Invalid branch name provided: " << default_branchName;
  }
  branchNames_sys[kJetMET_central_nonNominal] = Form(
    "%s_%s", default_branchName.data(), isPt ? "pt" : (isJet ? "mass" : "phi")
  );
  branchNames_sys[kJetMET_central]                                 = branchNames_sys[kJetMET_central_nonNominal] + "_nom";
  branchNames_sys[kJetMET_jesUp]                                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalUp";
  branchNames_sys[kJetMET_jesDown]                                 = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalDown";
  branchNames_sys[kJetMET_jesAbsoluteFlavMapUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteFlavMapUp";
  branchNames_sys[kJetMET_jesAbsoluteFlavMapDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteFlavMapDown";
  branchNames_sys[kJetMET_jesAbsoluteMPFBiasUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteMPFBiasUp";
  branchNames_sys[kJetMET_jesAbsoluteMPFBiasDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteMPFBiasDown";
  branchNames_sys[kJetMET_jesAbsoluteSampleUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteSampleUp";
  branchNames_sys[kJetMET_jesAbsoluteSampleDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteSampleDown";
  branchNames_sys[kJetMET_jesAbsoluteScaleUp]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteScaleUp";
  branchNames_sys[kJetMET_jesAbsoluteScaleDown]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteScaleDown";
  branchNames_sys[kJetMET_jesAbsoluteStatUp]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteStatUp";
  branchNames_sys[kJetMET_jesAbsoluteStatDown]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesAbsoluteStatDown";
  branchNames_sys[kJetMET_jesCorrelationGroupbJESUp]               = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupbJESUp";
  branchNames_sys[kJetMET_jesCorrelationGroupbJESDown]             = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupbJESDown";
  branchNames_sys[kJetMET_jesCorrelationGroupFlavorUp]             = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupFlavorUp";
  branchNames_sys[kJetMET_jesCorrelationGroupFlavorDown]           = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupFlavorDown";
  branchNames_sys[kJetMET_jesCorrelationGroupIntercalibrationUp]   = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupIntercalibrationUp";
  branchNames_sys[kJetMET_jesCorrelationGroupIntercalibrationDown] = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupIntercalibrationDown";
  branchNames_sys[kJetMET_jesCorrelationGroupMPFInSituUp]          = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupMPFInSituUp";
  branchNames_sys[kJetMET_jesCorrelationGroupMPFInSituDown]        = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupMPFInSituDown";
  branchNames_sys[kJetMET_jesCorrelationGroupUncorrelatedUp]       = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupUncorrelatedUp";
  branchNames_sys[kJetMET_jesCorrelationGroupUncorrelatedDown]     = branchNames_sys[kJetMET_central_nonNominal] + "_jesCorrelationGroupUncorrelatedDown";
  branchNames_sys[kJetMET_jesFlavorPhotonJetUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPhotonJetUp";
  branchNames_sys[kJetMET_jesFlavorPhotonJetDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPhotonJetDown";
  branchNames_sys[kJetMET_jesFlavorPureBottomUp]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureBottomUp";
  branchNames_sys[kJetMET_jesFlavorPureBottomDown]                 = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureBottomDown";
  branchNames_sys[kJetMET_jesFlavorPureCharmUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureCharmUp";
  branchNames_sys[kJetMET_jesFlavorPureCharmDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureCharmDown";
  branchNames_sys[kJetMET_jesFlavorPureGluonUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureGluonUp";
  branchNames_sys[kJetMET_jesFlavorPureGluonDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureGluonDown";
  branchNames_sys[kJetMET_jesFlavorPureQuarkUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureQuarkUp";
  branchNames_sys[kJetMET_jesFlavorPureQuarkDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorPureQuarkDown";
  branchNames_sys[kJetMET_jesFlavorQCDUp]                          = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorQCDUp";
  branchNames_sys[kJetMET_jesFlavorQCDDown]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorQCDDown";
  branchNames_sys[kJetMET_jesFlavorZJetUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorZJetUp";
  branchNames_sys[kJetMET_jesFlavorZJetDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesFlavorZJetDown";
  branchNames_sys[kJetMET_jesFragmentationUp]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesFragmentationUp";
  branchNames_sys[kJetMET_jesFragmentationDown]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesFragmentationDown";
  branchNames_sys[kJetMET_jesPileUpDataMCUp]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpDataMCUp";
  branchNames_sys[kJetMET_jesPileUpDataMCDown]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpDataMCDown";
  branchNames_sys[kJetMET_jesPileUpEnvelopeUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpEnvelopeUp";
  branchNames_sys[kJetMET_jesPileUpEnvelopeDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpEnvelopeDown";
  branchNames_sys[kJetMET_jesPileUpMuZeroUp]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpMuZeroUp";
  branchNames_sys[kJetMET_jesPileUpMuZeroDown]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpMuZeroDown";
  branchNames_sys[kJetMET_jesPileUpPtBBUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtBBUp";
  branchNames_sys[kJetMET_jesPileUpPtBBDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtBBDown";
  branchNames_sys[kJetMET_jesPileUpPtEC1Up]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtEC1Up";
  branchNames_sys[kJetMET_jesPileUpPtEC1Down]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtEC1Down";
  branchNames_sys[kJetMET_jesPileUpPtEC2Up]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtEC2Up";
  branchNames_sys[kJetMET_jesPileUpPtEC2Down]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtEC2Down";
  branchNames_sys[kJetMET_jesPileUpPtHFUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtHFUp";
  branchNames_sys[kJetMET_jesPileUpPtHFDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtHFDown";
  branchNames_sys[kJetMET_jesPileUpPtRefUp]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtRefUp";
  branchNames_sys[kJetMET_jesPileUpPtRefDown]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesPileUpPtRefDown";
  branchNames_sys[kJetMET_jesRelativeBalUp]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeBalUp";
  branchNames_sys[kJetMET_jesRelativeBalDown]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeBalDown";
  branchNames_sys[kJetMET_jesRelativeFSRUp]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeFSRUp";
  branchNames_sys[kJetMET_jesRelativeFSRDown]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeFSRDown";
  branchNames_sys[kJetMET_jesRelativeJEREC1Up]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJEREC1Up";
  branchNames_sys[kJetMET_jesRelativeJEREC1Down]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJEREC1Down";
  branchNames_sys[kJetMET_jesRelativeJEREC2Up]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJEREC2Up";
  branchNames_sys[kJetMET_jesRelativeJEREC2Down]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJEREC2Down";
  branchNames_sys[kJetMET_jesRelativeJERHFUp]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJERHFUp";
  branchNames_sys[kJetMET_jesRelativeJERHFDown]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeJERHFDown";
  branchNames_sys[kJetMET_jesRelativePtBBUp]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtBBUp";
  branchNames_sys[kJetMET_jesRelativePtBBDown]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtBBDown";
  branchNames_sys[kJetMET_jesRelativePtEC1Up]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtEC1Up";
  branchNames_sys[kJetMET_jesRelativePtEC1Down]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtEC1Down";
  branchNames_sys[kJetMET_jesRelativePtEC2Up]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtEC2Up";
  branchNames_sys[kJetMET_jesRelativePtEC2Down]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtEC2Down";
  branchNames_sys[kJetMET_jesRelativePtHFUp]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtHFUp";
  branchNames_sys[kJetMET_jesRelativePtHFDown]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativePtHFDown";
  branchNames_sys[kJetMET_jesRelativeSampleUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeSampleUp";
  branchNames_sys[kJetMET_jesRelativeSampleDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeSampleDown";
  branchNames_sys[kJetMET_jesRelativeStatECUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatECUp";
  branchNames_sys[kJetMET_jesRelativeStatECDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatECDown";
  branchNames_sys[kJetMET_jesRelativeStatFSRUp]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatFSRUp";
  branchNames_sys[kJetMET_jesRelativeStatFSRDown]                  = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatFSRDown";
  branchNames_sys[kJetMET_jesRelativeStatHFUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatHFUp";
  branchNames_sys[kJetMET_jesRelativeStatHFDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesRelativeStatHFDown";
  branchNames_sys[kJetMET_jesSinglePionECALUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesSinglePionECALUp";
  branchNames_sys[kJetMET_jesSinglePionECALDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesSinglePionECALDown";
  branchNames_sys[kJetMET_jesSinglePionHCALUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesSinglePionHCALUp";
  branchNames_sys[kJetMET_jesSinglePionHCALDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesSinglePionHCALDown";
  branchNames_sys[kJetMET_jesSubTotalAbsoluteUp]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalAbsoluteUp";
  branchNames_sys[kJetMET_jesSubTotalAbsoluteDown]                 = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalAbsoluteDown";
  branchNames_sys[kJetMET_jesSubTotalMCUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalMCUp";
  branchNames_sys[kJetMET_jesSubTotalMCDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalMCDown";
  branchNames_sys[kJetMET_jesSubTotalPileUpUp]                     = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalPileUpUp";
  branchNames_sys[kJetMET_jesSubTotalPileUpDown]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalPileUpDown";
  branchNames_sys[kJetMET_jesSubTotalPtUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalPtUp";
  branchNames_sys[kJetMET_jesSubTotalPtDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalPtDown";
  branchNames_sys[kJetMET_jesSubTotalRelativeUp]                   = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalRelativeUp";
  branchNames_sys[kJetMET_jesSubTotalRelativeDown]                 = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalRelativeDown";
  branchNames_sys[kJetMET_jesSubTotalScaleUp]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalScaleUp";
  branchNames_sys[kJetMET_jesSubTotalScaleDown]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesSubTotalScaleDown";
  branchNames_sys[kJetMET_jesTimePtEtaUp]                          = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimePtEtaUp";
  branchNames_sys[kJetMET_jesTimePtEtaDown]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimePtEtaDown";
  branchNames_sys[kJetMET_jesTimeRunBUp]                           = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunBUp";
  branchNames_sys[kJetMET_jesTimeRunBDown]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunBDown";
  branchNames_sys[kJetMET_jesTimeRunBCDUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunBCDUp";
  branchNames_sys[kJetMET_jesTimeRunBCDDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunBCDDown";
  branchNames_sys[kJetMET_jesTimeRunCUp]                           = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunCUp";
  branchNames_sys[kJetMET_jesTimeRunCDown]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunCDown";
  branchNames_sys[kJetMET_jesTimeRunDEUp]                          = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunDEUp";
  branchNames_sys[kJetMET_jesTimeRunDEDown]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunDEDown";
  branchNames_sys[kJetMET_jesTimeRunEFUp]                          = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunEFUp";
  branchNames_sys[kJetMET_jesTimeRunEFDown]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunEFDown";
  branchNames_sys[kJetMET_jesTimeRunFUp]                           = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunFUp";
  branchNames_sys[kJetMET_jesTimeRunFDown]                         = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunFDown";
  branchNames_sys[kJetMET_jesTimeRunGHUp]                          = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunGHUp";
  branchNames_sys[kJetMET_jesTimeRunGHDown]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesTimeRunGHDown";
  branchNames_sys[kJetMET_jesTotalNoFlavorUp]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoFlavorUp";
  branchNames_sys[kJetMET_jesTotalNoFlavorDown]                    = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoFlavorDown";
  branchNames_sys[kJetMET_jesTotalNoFlavorNoTimeUp]                = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoFlavorNoTimeUp";
  branchNames_sys[kJetMET_jesTotalNoFlavorNoTimeDown]              = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoFlavorNoTimeDown";
  branchNames_sys[kJetMET_jesTotalNoTimeUp]                        = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoTimeUp";
  branchNames_sys[kJetMET_jesTotalNoTimeDown]                      = branchNames_sys[kJetMET_central_nonNominal] + "_jesTotalNoTimeDown";
  branchNames_sys[kJetMET_jerUp]                                   = branchNames_sys[kJetMET_central_nonNominal] + "_jerUp";
  branchNames_sys[kJetMET_jerDown]                                 = branchNames_sys[kJetMET_central_nonNominal] + "_jerDown";
  branchNames_sys[kJetMET_UnclusteredEnUp]                         = branchNames_sys[kJetMET_central_nonNominal] + "_unclustEnUp";
  branchNames_sys[kJetMET_UnclusteredEnDown]                       = branchNames_sys[kJetMET_central_nonNominal] + "_unclustEnDown";
  assert(branchNames_sys.count(central_or_shift));
  assert(isValidJESsource(era, central_or_shift));
  return branchNames_sys.at(central_or_shift);
}

std::string
getBranchName_pileup(PUsys puSys_option)
{
  switch(puSys_option)
  {
    case PUsys::central: return "puWeight";
    case PUsys::up:      return "puWeightUp";
    case PUsys::down:    return "puWeightDown";
    default: throw cmsException(__func__, __LINE__) << "Invalid option = " << static_cast<int>(puSys_option);
  }
}
