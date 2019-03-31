#include "tthAnalysis/HiggsToTauTau/interface/TauTriggerSFs2017Helper.h"

#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h" // TauTriggerSFs2017
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys

getTriggerEfficiencyFunc
getTriggerFuncMC(TriggerSFsys triggerSF_option)
{
  switch(triggerSF_option)
  {
    case TriggerSFsys::central:   return &TauTriggerSFs2017::getTriggerEfficiencyMC;           break;
    case TriggerSFsys::shiftUp:   return &TauTriggerSFs2017::getTriggerEfficiencyMCUncertUp;   break;
    case TriggerSFsys::shiftDown: return &TauTriggerSFs2017::getTriggerEfficiencyMCUncertDown; break;
  }
  return nullptr;
}

getTriggerEfficiencyFunc
getTriggerFuncData(TriggerSFsys triggerSF_option)
{
  switch(triggerSF_option)
  {
    case TriggerSFsys::central:   return &TauTriggerSFs2017::getTriggerEfficiencyData;           break;
    case TriggerSFsys::shiftUp:   return &TauTriggerSFs2017::getTriggerEfficiencyDataUncertUp;   break;
    case TriggerSFsys::shiftDown: return &TauTriggerSFs2017::getTriggerEfficiencyDataUncertDown; break;
  }
  return nullptr;
}
