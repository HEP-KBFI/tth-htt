#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <sstream> // std::ostringstream

std::string
get_fullpath(const std::string & path)
{
  return LocalFileInPath(path).fullPath();
}

template <typename T>
std::string
format_vT(const std::vector<T> & vT)
{
  std::ostringstream os;
  const unsigned numEntries = vT.size();

  os << "{ ";
  for(unsigned iEntry = 0; iEntry < numEntries; ++iEntry)
  {
    os << vT[iEntry];
    if(iEntry < numEntries - 1)
    {
      os << ", ";
    }
  }
  os << " }";

  return os.str();
}

std::string
format_vstring(const std::vector<std::string> & vs)
{
  return format_vT(vs);
}

std::string
format_vdouble(const std::vector<double> & vd)
{
  return format_vT(vd);
}

std::string
format_vfloat(const std::vector<float> & vf)
{
  return format_vT(vf);
}

std::string
format_vint(const std::vector<int> & vi)
{
  return format_vT(vi);
}

std::string
format_vunsigned(const std::vector<unsigned> & vu)
{
  return format_vT(vu);
}

std::string
format_vbool(const std::vector<bool> & vb)
{
  return format_vT(vb);
}

std::string
format_vInputTag(const std::vector<edm::InputTag> & vit)
{
  std::vector<std::string> vit_string;
  for(const edm::InputTag & vit_i: vit)
  {
    vit_string.push_back(vit_i.label());
  }
  return format_vT(vit_string);
}
