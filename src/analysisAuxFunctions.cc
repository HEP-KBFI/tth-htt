#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#include <map>

bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2)
{
  return (particle1->pt_ > particle2->pt_);
}

std::string getBranchName_bTagWeight(int era, const std::string& central_or_shift)
{
  int central_or_shift_int = kBtag_central;
  if      ( central_or_shift == "CMS_ttHl_btag_HFUp"         ) central_or_shift_int = kBtag_hfUp;
  else if ( central_or_shift == "CMS_ttHl_btag_HFDown"       ) central_or_shift_int = kBtag_hfDown;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats1Up"   ) central_or_shift_int = kBtag_hfStats1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats1Down" ) central_or_shift_int = kBtag_hfStats1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats2Up"   ) central_or_shift_int = kBtag_hfStats2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats2Down" ) central_or_shift_int = kBtag_hfStats2Down;
  else if ( central_or_shift == "CMS_ttHl_btag_LFUp"         ) central_or_shift_int = kBtag_lfUp;
  else if ( central_or_shift == "CMS_ttHl_btag_LFDown"       ) central_or_shift_int = kBtag_lfDown;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats1Up"   ) central_or_shift_int = kBtag_lfStats1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats1Down" ) central_or_shift_int = kBtag_lfStats1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats2Up"   ) central_or_shift_int = kBtag_lfStats2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats2Down" ) central_or_shift_int = kBtag_lfStats2Down;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr1Up"      ) central_or_shift_int = kBtag_cErr1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr1Down"    ) central_or_shift_int = kBtag_cErr1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr2Up"      ) central_or_shift_int = kBtag_cErr2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr2Down"    ) central_or_shift_int = kBtag_cErr2Down;
  else if ( central_or_shift == "CMS_ttHl_JESUp"             ) central_or_shift_int = kBtag_jesUp;
  else if ( central_or_shift == "CMS_ttHl_JESDown"           ) central_or_shift_int = kBtag_jesDown;
  return getBranchName_bTagWeight(era, central_or_shift_int);
}

std::string getBranchName_bTagWeight(int era, int central_or_shift)
{
  std::map<int, std::string> branchNames_bTagWeight;
  if ( era == kEra_2015 ) {
    branchNames_bTagWeight[kBtag_central]      = "Jet_bTagWeight";
    branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "HFUp";
    branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "HFDown";
    branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "HFStats1Up";
    branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "HFStats1Down";
    branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "HFStats2Up";
    branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "HFStats2Down";
    branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "LFUp";
    branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "LFDown";
    branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "LFStats1Up";
    branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "LFStats1Down";
    branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "LFStats2Up";
    branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "LFStats2Down";
    branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "cErr1Up";
    branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "cErr1Down";
    branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "cErr2Up";
    branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "cErr2Down";
    branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "JESUp";
    branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "JESDown";
  } else if ( era == kEra_2016 ) {
    branchNames_bTagWeight[kBtag_central]      = "Jet_btagWeightCSV";
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
  } else assert(0);
  std::map<int, std::string>::const_iterator branchName_bTagWeight = branchNames_bTagWeight.find(central_or_shift);
  assert(branchName_bTagWeight != branchNames_bTagWeight.end());
  return branchName_bTagWeight->second;
}
