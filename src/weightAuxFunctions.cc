#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h"

#include <TString.h> // Form()

#include <algorithm> // std::replace()

double
get_tHq_sf(double kt,
           double kv)
{
  return 2.63 * kt * kt + 3.588 * kv * kv - 5.21 * kt * kv;
}

double
get_tHq_sf(const std::pair<double, double> & kt_kv)
{
  return get_tHq_sf(kt_kv.first, kt_kv.second);
}

double
get_tHq_sf(const std::string & kt_kv_str)
{
  return get_tHq_sf(get_tH_params(kt_kv_str));
}

double
get_tHW_sf(double kt,
           double kv)
{
  return 2.91 * kt * kt + 2.31 * kv * kv - 4.22 * kt * kv;
}

double
get_tHW_sf(const std::pair<double, double> & kt_kv)
{
  return get_tHW_sf(kt_kv.first, kt_kv.second);
}

double
get_tHW_sf(const std::string & kt_kv_str)
{
  return get_tHW_sf(get_tH_params(kt_kv_str));
}

std::string
get_tH_weight_str(double kt,
                  double kv)
{
  std::string kt_kv_str = Form("kt_%.3g_kv_%.3g", kt, kv);
  std::replace(kt_kv_str.begin(), kt_kv_str.end(), '.', 'p');
  std::replace(kt_kv_str.begin(), kt_kv_str.end(), '-', 'm');
  return kt_kv_str;
}

std::pair<double, double>
get_tH_params(const std::string & kt_kv_str)
{
  std::string kt_str = kt_kv_str.substr(kt_kv_str.find("kt_") + 3, kt_kv_str.find("kv_") - 4);
  std::string kv_str = kt_kv_str.substr(kt_kv_str.find("kv_") + 3);
  std::replace(kt_str.begin(), kt_str.end(), 'p', '.');
  std::replace(kt_str.begin(), kt_str.end(), 'm', '-');
  std::replace(kv_str.begin(), kv_str.end(), 'p', '.');
  std::replace(kv_str.begin(), kv_str.end(), 'm', '-');
  const double kt = std::stod(kt_str);
  const double kv = std::stod(kv_str);
  return std::pair<double, double>(kt, kv);
}
