#include "tthAnalysis/HiggsToTauTau/interface/TauTriggerSFInterface.h"

#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h" // TauTriggerSFs2017
#include "TauAnalysisTools/TauTriggerSFs/interface/SFProvider.h" // tau_trigger::SFProvider

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*, get_tau_id_*(), TauID::
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::getHadTauSelectionLabel()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

std::string
TauTriggerSFInterface::tauTriggerType_toStr(TauTriggerType triggerType)
{
  switch(triggerType)
  {
    case TauTriggerType::DiTau: return "ditau";
    case TauTriggerType::ETau:  return "etau";
    case TauTriggerType::MuTau: return "mutau";
    case TauTriggerType::None: __attribute__((fallthrough));
    default: throw cmsException(__func__, __LINE__) << "Invalid trigger type: " << as_integer(triggerType);
  }
}

TauTriggerSFInterface::TauTriggerSFInterface(TauTriggerType triggerType)
  : eff_mvav2_(nullptr)
  , eff_deep_(nullptr)
  , triggerType_(triggerType)
{}

TauTriggerSFInterface::TauTriggerSFInterface(const std::string & era_str,
                                             const std::string & hadTauSelection,
                                             TauTriggerType triggerType)
  : TauTriggerSFInterface(triggerType)
{
  const int __attribute__((unused)) era = get_era(era_str);
  const TauID tauId = get_tau_id_enum(hadTauSelection);
  const std::string triggerType_str = tauTriggerType_toStr(triggerType);

  if(tauId == TauID::MVAoldDM2017v2 || tauId == TauID::MVAoldDMdR032017v2)
  {
    // use SFs measued for 2017v2 MVA tau ID with cone size of 0.5
    const LocalFileInPath inputFileName(
      Form("TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies%s.root", era_str.data()
    ));
    const std::string wp_str = aux::getHadTauSelectionLabel(hadTauSelection);
    eff_mvav2_ = new TauTriggerSFs2017(inputFileName.fullPath(), triggerType_str, era_str, wp_str, "MVAv2");
  }
  else if(tauId == TauID::DeepTau2017v2VSjet)
  {
    // use SFs measued for anti-jet DeepTau ID
    const LocalFileInPath inputFileName(
      Form("TauAnalysisTools/TauTriggerSFs/data/%s_tauTriggerEff_DeepTau2017v2p1.root", era_str.data()
    ));
    const std::string wp_str = get_tau_id_wp_str(tauId, get_tau_id_wp_int(hadTauSelection));
    eff_deep_ = new tau_trigger::SFProvider(inputFileName.fullPath(), triggerType_str, wp_str);
  }
  else
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid tau ID: " << as_integer(tauId);
  }
}

double
TauTriggerSFInterface::getTauTriggerEvalData(TriggerSFsys central_or_shift,
                                             double pt,
                                             double eta,
                                             double phi,
                                             int dm) const
{
  if(eff_mvav2_)
  {
    switch(getGenericTriggerSFsys(central_or_shift))
    {
      case TriggerSFsys::central:          return eff_mvav2_->getTriggerEfficiencyData          (pt, eta, phi, dm);
      case TriggerSFsys::shiftUp:          return eff_mvav2_->getTriggerEfficiencyDataUncertUp  (pt, eta, phi, dm);
      case TriggerSFsys::shiftDown:        return eff_mvav2_->getTriggerEfficiencyDataUncertDown(pt, eta, phi, dm);
      case TriggerSFsys::shift_2lssUp:     __attribute__((fallthrough));
      case TriggerSFsys::shift_2lssDown:   __attribute__((fallthrough));
      case TriggerSFsys::shift_3lUp:       __attribute__((fallthrough));
      case TriggerSFsys::shift_3lDown:     __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauDown: __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauDown: __attribute__((fallthrough));
      default: assert(false);
    }
  }
  else if(eff_deep_)
  {
    switch(getGenericTriggerSFsys(central_or_shift))
    {
      case TriggerSFsys::central:          return eff_deep_->getEfficiencyData(pt, dm,  0);
      case TriggerSFsys::shiftUp:          return eff_deep_->getEfficiencyData(pt, dm, +1);
      case TriggerSFsys::shiftDown:        return eff_deep_->getEfficiencyData(pt, dm, -1);
      case TriggerSFsys::shift_2lssUp:     __attribute__((fallthrough));
      case TriggerSFsys::shift_2lssDown:   __attribute__((fallthrough));
      case TriggerSFsys::shift_3lUp:       __attribute__((fallthrough));
      case TriggerSFsys::shift_3lDown:     __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauDown: __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauDown: __attribute__((fallthrough));
      default: assert(false);
    }
  }
  throw cmsException(this, __func__, __LINE__) << "Class not initialized properly";
}

double
TauTriggerSFInterface::getTauTriggerEvalMC(TriggerSFsys central_or_shift,
                                           double pt,
                                           double eta,
                                           double phi,
                                           int dm,
                                           bool flip) const
{
  if(eff_mvav2_)
  {
    switch(getGenericTriggerSFsys(central_or_shift))
    {
      case TriggerSFsys::central:          return eff_mvav2_->getTriggerEfficiencyMC   (pt, eta, phi, dm);
      case TriggerSFsys::shiftUp:          return flip ?
                                           eff_mvav2_->getTriggerEfficiencyMCUncertDown(pt, eta, phi, dm) :
                                           eff_mvav2_->getTriggerEfficiencyMCUncertUp  (pt, eta, phi, dm);
      case TriggerSFsys::shiftDown:        return flip ?
                                           eff_mvav2_->getTriggerEfficiencyMCUncertUp  (pt, eta, phi, dm) :
                                           eff_mvav2_->getTriggerEfficiencyMCUncertDown(pt, eta, phi, dm);
      case TriggerSFsys::shift_2lssUp:     __attribute__((fallthrough));
      case TriggerSFsys::shift_2lssDown:   __attribute__((fallthrough));
      case TriggerSFsys::shift_3lUp:       __attribute__((fallthrough));
      case TriggerSFsys::shift_3lDown:     __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauDown: __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauDown: __attribute__((fallthrough));
      default: assert(false);
    }
  }
  else if(eff_deep_)
  {
    switch(getGenericTriggerSFsys(central_or_shift))
    {
      case TriggerSFsys::central:          return eff_deep_->getEfficiencyMC(pt, dm,  0);
      case TriggerSFsys::shiftUp:          return eff_deep_->getEfficiencyMC(pt, dm, flip ? -1 : +1);
      case TriggerSFsys::shiftDown:        return eff_deep_->getEfficiencyMC(pt, dm, flip ? +1 : -1);
      case TriggerSFsys::shift_2lssUp:     __attribute__((fallthrough));
      case TriggerSFsys::shift_2lssDown:   __attribute__((fallthrough));
      case TriggerSFsys::shift_3lUp:       __attribute__((fallthrough));
      case TriggerSFsys::shift_3lDown:     __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_1l1tauDown: __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauUp:   __attribute__((fallthrough));
      case TriggerSFsys::shift_0l2tauDown: __attribute__((fallthrough));
      default: assert(false);
    }
  }
  throw cmsException(this, __func__, __LINE__) << "Class not initialized properly";
}

TriggerSFsys
TauTriggerSFInterface::getGenericTriggerSFsys(TriggerSFsys central_or_shift) const
{
  if(central_or_shift == TriggerSFsys::central ||
     central_or_shift == TriggerSFsys::shiftUp ||
     central_or_shift == TriggerSFsys::shiftDown)
  {
    return central_or_shift;
  }
  else if(central_or_shift == TriggerSFsys::shift_0l2tauUp ||
          central_or_shift == TriggerSFsys::shift_0l2tauDown)
  {
    if(triggerType_ != TauTriggerType::DiTau)
    {
      throw cmsException(this, __func__, __LINE__)
        << "Invalid choice of systematic uncertatinty (" << as_integer(central_or_shift) << ") "
           "for the trigger type " << as_integer(triggerType_)
      ;
    }
    return central_or_shift == TriggerSFsys::shift_0l2tauUp ? TriggerSFsys::shiftUp : TriggerSFsys::shiftDown;
  }
  else if(central_or_shift == TriggerSFsys::shift_1l1tauUp ||
          central_or_shift == TriggerSFsys::shift_1l1tauDown)
  {
    if(triggerType_ != TauTriggerType::ETau && triggerType_ != TauTriggerType::MuTau)
    {
      throw cmsException(this, __func__, __LINE__)
        << "Invalid choice of systematic uncertatinty (" << as_integer(central_or_shift) << ") "
           "for the trigger type " << as_integer(triggerType_)
      ;
    }
    return central_or_shift == TriggerSFsys::shift_1l1tauUp ? TriggerSFsys::shiftUp : TriggerSFsys::shiftDown;
  }
  throw cmsException(this, __func__, __LINE__)
      << "Invalid choice of systematic uncertainty:" << as_integer(central_or_shift)
  ;
}
