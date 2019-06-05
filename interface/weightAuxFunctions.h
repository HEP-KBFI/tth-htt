#ifndef tthAnalysis_HiggsToTauTau_weightAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_weightAuxFunctions_h

#include <string> // std::string
#include <utility> // std::pair<,>

std::string
get_tH_weight_str(double kt,
                  double kv);

std::pair<double, double>
get_tH_params(const std::string & kt_kv_str);

#endif
