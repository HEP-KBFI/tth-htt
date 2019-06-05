#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h"

#include <TString.h> // Form()

#include <algorithm> // std::replace()
#include <cassert> // assert()

std::string
get_tH_weight_str(double kt,
                  double kv)
{
  std::string kt_kv_str = Form("kt_%.3g_kv_%.3g", kt, kv);
  std::replace(kt_kv_str.begin(), kt_kv_str.end(), '.', 'p');
  std::replace(kt_kv_str.begin(), kt_kv_str.end(), '-', 'm');
  return kt_kv_str;
}

std::string
get_tH_SM_str()
{
  return get_tH_weight_str(1.0, 1.0);
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

  // make sure that we can recover the encoding string
  const std::string kt_kv_str_re = get_tH_weight_str(kt, kv);
  assert(kt_kv_str == kt_kv_str_re);

  return std::pair<double, double>(kt, kv);
}
