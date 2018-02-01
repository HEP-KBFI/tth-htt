#ifndef tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h"

void
check_mvaInputs(std::map<std::string, double> & mvaInputs,
                UInt_t run = 0,
                UInt_t lumi = 0,
                ULong64_t event = 0);

void
check_mvaInputs(std::map<std::string, double> & mvaInputs,
                const EventInfo & info);

std::vector<std::string>
get_mvaInputVariables(const std::vector<std::string> & mvaInputVariables_ttV,
                      const std::vector<std::string> & mvaInputVariables_ttbar);

#endif // tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h
