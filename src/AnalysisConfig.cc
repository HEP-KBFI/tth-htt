#include "tthAnalysis/HiggsToTauTau/interface/AnalysisConfig.h"

#include <TPRegexp.h>
#include <TObjString.h>
#include <TObjArray.h>

AnalysisConfig::AnalysisConfig(const std::string & analysis, const edm::ParameterSet & cfg)
  : analysis_string_(analysis)
  , process_string_(cfg.getParameter<std::string>("process"))
{
  isMC_     = cfg.getParameter<bool>("isMC");
  isData_   = !isMC_;
  isMC_WZ_  = process_string_ == "WZ";
  isMC_ZZ_  = process_string_ == "ZZ";
  isMC_tH_  = process_string_ == "tHq" || process_string_ == "tHW";
  isMC_ttH_ = process_string_ == "ttH" || process_string_ == "ttH_ctcvcp";
  isMC_ggH_ = process_string_ == "ggH";
  isMC_qqH_ = process_string_ == "qqH";
  isMC_VH_  = process_string_ == "VH";
  isMC_H_   = isMC_tH_ || isMC_ttH_ || isMC_ggH_ || isMC_qqH_ || isMC_VH_ || process_string_ == "TTWH" || process_string_ == "TTZH";

  decayModes_H_ = { "hww", "hzz", "htt", "hzg", "hmm" };

  TPRegexp parser_HH_resonant_spin0("signal_(ggf|vbf)_spin0_[0-9]+_*");
  isMC_HH_resonant_spin0_ = parser_HH_resonant_spin0.Match(process_string_.data());
  TPRegexp parser_HH_resonant_spin2("signal_(ggf|vbf)_spin2_[0-9]+_*");
  isMC_HH_resonant_spin2_ = parser_HH_resonant_spin2.Match(process_string_.data());
  assert(!(isMC_HH_resonant_spin0_ && isMC_HH_resonant_spin2_));
  isMC_HH_resonant_       = isMC_HH_resonant_spin0_ || isMC_HH_resonant_spin2_;
  TPRegexp parser_HH_nonresonant("signal_(ggf|vbf)_nonresonant_*");
  isMC_HH_nonresonant_    = parser_HH_nonresonant.Match(process_string_.data());
  assert(!(isMC_HH_resonant_ && isMC_HH_nonresonant_));
  isMC_HH_  = isMC_HH_resonant_ || isMC_HH_nonresonant_ || process_string_ == "HH";

  std::string apply_topPtReweighting_string = cfg.getParameter<std::string>("apply_topPtReweighting");
  apply_topPtReweighting_ = !apply_topPtReweighting_string.empty();
}

AnalysisConfig::~AnalysisConfig()
{}

const std::string & 
AnalysisConfig::analysis() const
{
  return analysis_string_;
}

const std::string & 
AnalysisConfig::process() const
{
  return process_string_;
}

bool
AnalysisConfig::isData() const
{
  return isData_;
}

bool
AnalysisConfig::isMC() const
{
  return isMC_;
}
 
bool
AnalysisConfig::isMC_WZ() const
{
  return isMC_WZ_;
}
 
bool
AnalysisConfig::isMC_ZZ() const
{
  return isMC_ZZ_;
}

bool
AnalysisConfig::isMC_tH() const
{
  return isMC_tH_;
}
 
bool 
AnalysisConfig::isMC_ttH() const
{
  return isMC_ttH_;
}

bool
AnalysisConfig::isMC_ggH() const
{
  return isMC_ggH_;
}
 
bool
AnalysisConfig::isMC_qqH() const
{
  return isMC_qqH_;
}

bool
AnalysisConfig::isMC_VH() const
{
  return isMC_VH_;
}

bool
AnalysisConfig::isMC_H() const
{
  return isMC_H_;
}

bool
AnalysisConfig::isMC_HH() const
{
  return isMC_HH_;
}

bool 
AnalysisConfig::isMC_HH_resonant() const
{
  return isMC_HH_resonant_;
}

bool
AnalysisConfig::isMC_HH_resonant_spin0() const
{
  return isMC_HH_resonant_spin0_;
}

bool
AnalysisConfig::isMC_HH_resonant_spin2() const
{
  return isMC_HH_resonant_spin2_;
}

bool
AnalysisConfig::isMC_HH_nonresonant() const
{
  return isMC_HH_nonresonant_;
}

std::vector<std::string> 
AnalysisConfig::get_decayModes_H() const
{
  return decayModes_H_;
}

bool
AnalysisConfig::apply_topPtReweighting() const
{
  return apply_topPtReweighting_;
}
