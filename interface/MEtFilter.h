#ifndef MEtFilter_H
#define MEtFilter_H

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterFlag.h" // MEtFilterFlag::

#include <array> // std::array<,>

class MEtFilter
{
public:
  MEtFilter();

  bool
  getFlag(MEtFilterFlag flag) const;

  friend class MEtFilterReader;

protected:

  // for MEtFilterReader
  bool &
  getFlagRef(MEtFilterFlag flag);

  std::array<bool, MEtFilterFlag::LAST> flags_;
};

#endif // MEtFilter_H
