#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"

#include <sstream>

template <typename T>
std::string format_vT(const std::vector<T>& vT)
{
  std::ostringstream os;
  
  os << "{ ";

  unsigned numEntries = vT.size();
  for ( unsigned iEntry = 0; iEntry < numEntries; ++iEntry ) {
    os << vT[iEntry];
    if ( iEntry < (numEntries - 1) ) os << ", ";
  }

  os << " }";
  
  return os.str();
}

std::string format_vstring(const std::vector<std::string>& vs)
{
  return format_vT(vs);
}

std::string format_vdouble(const std::vector<double>& vd)
{
  return format_vT(vd);
}

std::string format_vfloat(const std::vector<float>& vf)
{
  return format_vT(vf);
}

std::string format_vint(const std::vector<int>& vi)
{
  return format_vT(vi);
}

std::string format_vunsigned(const std::vector<unsigned>& vu)
{
  return format_vT(vu);
}

std::string format_vbool(const std::vector<bool>& vb)
{
  return format_vT(vb);
}

std::string format_vInputTag(const std::vector<edm::InputTag>& vit)
{
  std::vector<std::string> vit_string;
  for ( std::vector<edm::InputTag>::const_iterator vit_i = vit.begin();
	vit_i != vit.end(); ++vit_i ) {
    vit_string.push_back(vit_i->label());
  }
  return format_vT(vit_string);
}
