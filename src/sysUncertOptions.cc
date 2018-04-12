#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <TString.h> // Form()

#include <boost/algorithm/string/predicate.hpp> // boost::algorithm::starts_with(), boost::algorithm::ends_with()

int
getBTagWeight_option(const std::string & central_or_shift,
                     bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
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
  checkOptionValidity(central_or_shift, isMC);
  int central_or_shift_int = isMC ? kJet_central : kJet_central_nonNominal;
  if     (central_or_shift == "CMS_ttHl_JESUp"  ) central_or_shift_int = kJet_jesUp;
  else if(central_or_shift == "CMS_ttHl_JESDown") central_or_shift_int = kJet_jesDown;
  else if(central_or_shift == "CMS_ttHl_JERUp"  ) central_or_shift_int = kJet_jerUp;
  else if(central_or_shift == "CMS_ttHl_JERDown") central_or_shift_int = kJet_jerDown;
  return central_or_shift_int;
}

int
getMET_option(const std::string & central_or_shift,
              bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  int central_or_shift_int = isMC ? kMEt_central : kMEt_central_nonNominal;
  if     (central_or_shift == "CMS_ttHl_JESUp"            ) central_or_shift_int = kMEt_shifted_JetEnUp;
  else if(central_or_shift == "CMS_ttHl_JESDown"          ) central_or_shift_int = kMEt_shifted_JetEnDown;
  else if(central_or_shift == "CMS_ttHl_JERUp"            ) central_or_shift_int = kMEt_shifted_JetResUp;
  else if(central_or_shift == "CMS_ttHl_JERDown"          ) central_or_shift_int = kMEt_shifted_JetResDown;
  else if(central_or_shift == "CMS_ttHl_UnclusteredEnUp"  ) central_or_shift_int = kMEt_shifted_UnclusteredEnUp;
  else if(central_or_shift == "CMS_ttHl_UnclusteredEnDown") central_or_shift_int = kMEt_shifted_UnclusteredEnDown;
  return central_or_shift_int;
}

int
getHadTauPt_option(const std::string & central_or_shift,
                   bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  int central_or_shift_int = kHadTauPt_central;
  if     (central_or_shift == "CMS_ttHl_tauESUp"  ) central_or_shift_int = kHadTauPt_shiftUp;
  else if(central_or_shift == "CMS_ttHl_tauESDown") central_or_shift_int = kHadTauPt_shiftDown;
  return central_or_shift_int;
}

int
getJetToTauFR_option(const std::string & central_or_shift,
                     bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  int central_or_shift_int = kFRjt_central;
  if     (central_or_shift == "CMS_ttHl_FRjt_normUp"   ) central_or_shift_int = kFRjt_normUp;
  else if(central_or_shift == "CMS_ttHl_FRjt_normDown" ) central_or_shift_int = kFRjt_normDown;
  else if(central_or_shift == "CMS_ttHl_FRjt_shapeUp"  ) central_or_shift_int = kFRjt_shapeUp;
  else if(central_or_shift == "CMS_ttHl_FRjt_shapeDown") central_or_shift_int = kFRjt_shapeDown;
  return central_or_shift_int;
}

FRet
getEToTauFR_option(const std::string & central_or_shift,
                   bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  FRet central_or_shift_int = FRet::central;
  if     (central_or_shift == "CMS_ttHl_FRet_shiftUp"  ) central_or_shift_int = FRet::shiftUp;
  else if(central_or_shift == "CMS_ttHl_FRet_shiftDown") central_or_shift_int = FRet::shiftDown;
  return central_or_shift_int;
}

FRmt
getMuToTauFR_option(const std::string & central_or_shift,
                    bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  FRmt central_or_shift_int = FRmt::central;
  if     (central_or_shift == "CMS_ttHl_FRmt_shiftUp"  ) central_or_shift_int = FRmt::shiftUp;
  else if(central_or_shift == "CMS_ttHl_FRmt_shiftDown") central_or_shift_int = FRmt::shiftDown;
  return central_or_shift_int;
}

int
getLHEscale_option(const std::string & central_or_shift,
                     bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
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
getElectronPt_option(const std::string & central_or_shift,
                     bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
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
getMuon_option(const std::string & central_or_shift,
               bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
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
getJetToLeptonFR_option(const std::string & central_or_shift,
                        bool isMC)
{
  checkOptionValidity(central_or_shift, isMC);
  int central_or_shift_int = kFRl_central;
  if     (central_or_shift == "CMS_ttHl_FRe_shape_ptUp"          ) central_or_shift_int = kFRe_shape_ptUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_ptDown"        ) central_or_shift_int = kFRe_shape_ptDown;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_etaUp"         ) central_or_shift_int = kFRe_shape_etaUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_etaDown"       ) central_or_shift_int = kFRe_shape_etaDown;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_eta_barrelUp"  ) central_or_shift_int = kFRe_shape_eta_barrelUp;
  else if(central_or_shift == "CMS_ttHl_FRe_shape_eta_barrelDown") central_or_shift_int = kFRe_shape_eta_barrelDown;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_ptUp"          ) central_or_shift_int = kFRm_shape_ptUp;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_ptDown"        ) central_or_shift_int = kFRm_shape_ptDown;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_etaUp"         ) central_or_shift_int = kFRm_shape_etaUp;
  else if(central_or_shift == "CMS_ttHl_FRm_shape_etaDown"       ) central_or_shift_int = kFRm_shape_etaDown;
  return central_or_shift_int;
}

void
checkOptionValidity(const std::string & central_or_shift,
                    bool isMC)
{
  if(! (central_or_shift.empty() || central_or_shift == "central"))
  {
    if(! isMC)
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
getBranchName_bTagWeight(const std::string & default_collectionName,
                         int era,
                         int central_or_shift,
                         bool useDeepCSV)
{
  std::map<int, std::string> branchNames_bTagWeight; // make static?
  if(era == kEra_2017)
  {
    branchNames_bTagWeight[kBtag_central]      = Form(
      "%s_btagSF_%s", default_collectionName.data(), useDeepCSV ? "deepcsv" : "csvv2"
    );
    branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "_shape_up_hf";
    branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "_shape_down_hf";
    branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_hfstats2";
    branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_hfstats2";
    branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "_shape_up_lf";
    branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "_shape_down_lf";
    branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_lfstats2";
    branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_lfstats2";
    branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "_shape_up_cferr1";
    branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "_shape_down_cferr1";
    branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "_shape_up_cferr2";
    branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "_shape_down_cferr2";
    branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "_shape_up_jes";
    branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "_shape_down_jes";
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid era = " << era;
  }
  assert(branchNames_bTagWeight.count(central_or_shift));
  return branchNames_bTagWeight.at(central_or_shift);
}

std::string
getBranchName_jetPtMass(const std::string & default_collectionName,
                        int era,
                        int central_or_shift,
                        bool isPt)
{
  std::map<int, std::string> branchNames_sys; // make static?
  if(era == kEra_2017)
  {
    branchNames_sys[kJet_central_nonNominal] = Form(
      "%s_%s", default_collectionName.data(), isPt ? "pt" : "mass"
    );
    branchNames_sys[kJet_central] = branchNames_sys[kJet_central_nonNominal] + "_nom";
    branchNames_sys[kJet_jesUp]   = branchNames_sys[kJet_central_nonNominal] + "_jesTotalUp";
    branchNames_sys[kJet_jesDown] = branchNames_sys[kJet_central_nonNominal] + "_jesTotalDown";
    branchNames_sys[kJet_jerUp]   = branchNames_sys[kJet_central_nonNominal] + "_jerUp";
    branchNames_sys[kJet_jerDown] = branchNames_sys[kJet_central_nonNominal] + "_jerDown";
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid era = " << era;
  }
  assert(branchNames_sys.count(central_or_shift));
  return branchNames_sys.at(central_or_shift);
}

std::string
getBranchName_MEt(const std::string & default_branchName,
                  int era,
                  int central_or_shift,
                  bool isPt)
{
  std::map<int, std::string> branchNames_sys; // make static?
  if(era == kEra_2017)
  {
    branchNames_sys[kMEt_central_nonNominal] = Form(
      "%s_%s", default_branchName.data(), isPt ? "pt" : "phi"
    );
    branchNames_sys[kMEt_central]                   = branchNames_sys[kMEt_central_nonNominal] + "_nom";
    branchNames_sys[kMEt_shifted_JetEnUp]           = branchNames_sys[kMEt_central_nonNominal] + "_jesTotalUp";
    branchNames_sys[kMEt_shifted_JetEnDown]         = branchNames_sys[kMEt_central_nonNominal] + "_jesTotalDown";
    branchNames_sys[kMEt_shifted_JetResUp]          = branchNames_sys[kMEt_central_nonNominal] + "_jerUp";
    branchNames_sys[kMEt_shifted_JetResDown]        = branchNames_sys[kMEt_central_nonNominal] + "_jerDown";
    branchNames_sys[kMEt_shifted_UnclusteredEnUp]   = branchNames_sys[kMEt_central_nonNominal] + "_unclustEnUp";
    branchNames_sys[kMEt_shifted_UnclusteredEnDown] = branchNames_sys[kMEt_central_nonNominal] + "_unclustEnDown";
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid era = " << era;
  }
  assert(branchNames_sys.count(central_or_shift));
  return branchNames_sys.at(central_or_shift);
}