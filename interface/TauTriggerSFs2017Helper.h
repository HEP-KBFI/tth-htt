#ifndef tthAnalysis_HiggsToTauTau_TauTriggerSFs2017Helper_h
#define tthAnalysis_HiggsToTauTau_TauTriggerSFs2017Helper_h

class TauTriggerSFs2017;
enum class TriggerSFsys;

typedef double (TauTriggerSFs2017::*getTriggerEfficiencyFunc)(double, double, double, int);

getTriggerEfficiencyFunc
getTriggerFuncMC(TriggerSFsys triggerSF_option);

getTriggerEfficiencyFunc
getTriggerFuncData(TriggerSFsys triggerSF_option);

#endif // tthAnalysis_HiggsToTauTau_TauTriggerSFs2017Helper_h
