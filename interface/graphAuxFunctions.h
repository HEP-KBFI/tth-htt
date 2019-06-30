#ifndef tthAnalysis_HiggsToTauTau_graphAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_graphAuxFunctions_h

#include <string>

// forward declarations
class TGraphAsymmErrors;
class TGraph;

TGraphAsymmErrors *
compRatioGraph(const std::string & ratioGraphName,
               const TGraph * numerator,
               const TGraph * denominator);

void
dumpGraph(const TGraph * graph);

#endif // tthAnalysis_HiggsToTauTau_graphAuxFunctions_h
