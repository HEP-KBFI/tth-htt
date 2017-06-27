#ifndef tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE 

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<>

void check_mvaInputs(std::map<std::string, double>& mvaInputs, RUN_TYPE run = 0, LUMI_TYPE lumi = 0, EVT_TYPE event = 0);

std::vector<std::string> get_mvaInputVariables(const std::vector<std::string>& mvaInputVariables_ttV, const std::vector<std::string>& mvaInputVariables_ttbar);

#endif
