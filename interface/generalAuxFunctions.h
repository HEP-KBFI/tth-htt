#ifndef tthAnalysis_HiggsToTauTau_generalAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_generalAuxFunctions_h

#include "FWCore/Utilities/interface/InputTag.h"

#include <vector> // std::vector<>
#include <sstream> // std::stringstream

template <typename T>
std::string
to_string_with_precision(const T a_value,
                         const int n = 2)
{
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}

std::string
get_fullpath(const std::string & path);

std::string
format_vstring(const std::vector<std::string>&);

std::string
format_vdouble(const std::vector<double>&);

std::string
format_vfloat(const std::vector<float>&);

std::string
format_vint(const std::vector<int>&);

std::string
format_vunsigned(const std::vector<unsigned>&);

std::string
format_vbool(const std::vector<bool>&);

std::string
format_vInputTag(const std::vector<edm::InputTag> &);

#endif
