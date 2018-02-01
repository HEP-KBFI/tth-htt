#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

cms::Exception
cmsException(const std::string & func,
             int line)
{
  return cms::Exception(func + (line >= 0 ? ":" + std::to_string(line) : ""));
}
