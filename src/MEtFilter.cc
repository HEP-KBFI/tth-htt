#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" // MEtFilter

#include <algorithm> // std::fill_n()

MEtFilter::MEtFilter()
{
  flags_.fill(false);
}

bool
MEtFilter::getFlag(MEtFilterFlag flag) const
{
  return flags_[flag];
}

bool &
MEtFilter::getFlagRef(MEtFilterFlag flag)
{
  return flags_[flag];
}
