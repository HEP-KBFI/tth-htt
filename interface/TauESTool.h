#ifndef tthAnalysis_HiggsToTauTau_TauESTool_h
#define tthAnalysis_HiggsToTauTau_TauESTool_h

#include <map> // std::map

#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"

class TauESTool
{
public:
  TauESTool(int era,
            int central_or_shift = kHadTauPt_central,
            bool debug = false);

  void
  set_central_or_shift(int central_or_shift);

  double
  getTES(int dm,
         int genmatch = 5) const;

private:
  int central_or_shift_;
  std::map<int, double> sf_;
  std::map<int, double> sfErr_;
};

#endif // tthAnalysis_HiggsToTauTau_TauESTool_h
