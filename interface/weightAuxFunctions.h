#ifndef tthAnalysis_HiggsToTauTau_weightAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_weightAuxFunctions_h

#include <string> // std::string
#include <utility> // std::pair<,>

double
get_tHq_sf(double kt,
           double kv);

double
get_tHq_sf(const std::pair<double, double> & kt_kv);

double
get_tHq_sf(const std::string & kt_kv_str);

double
get_tHW_sf(double kt,
           double kv);

double
get_tHW_sf(const std::pair<double, double> & kt_kv);

double
get_tHW_sf(const std::string & kt_kv_str);

std::string
get_tH_weight_str(double kt,
                  double kv);

std::pair<double, double>
get_tH_params(const std::string & kt_kv_str);

#endif
