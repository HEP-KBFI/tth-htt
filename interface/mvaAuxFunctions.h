#ifndef tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_mvaAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h"

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<>

void check_mvaInputs(std::map<std::string, double>& mvaInputs, RUN_TYPE run = 0, LUMI_TYPE lumi = 0, EVT_TYPE event = 0);

void check_mvaInputs(std::map<std::string, double> & mvaInputs, const EventInfo & info);

std::vector<std::string> get_mvaInputVariables(const std::vector<std::string>& mvaInputVariables_ttV, const std::vector<std::string>& mvaInputVariables_ttbar);

#endif
