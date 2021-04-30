#ifndef tthAnalysis_HiggsToTauTau_compFakeRateAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_compFakeRateAuxFunctions_h

#include <TArrayD.h> // TArrayD

TArrayD
convertToTArrayD(const std::vector<double> & binEdges);

void
compFakeRate(double nPass,
             double nPassErr,
             double nFail,
             double nFailErr,
             double & avFakeRate,
             double & avFakeRateErrUp,
             double & avFakeRateErrDown,
             bool & errorFlag,
             double uncertCap);

#endif // tthAnalysis_HiggsToTauTau_compFakeRateAuxFunctions_h
