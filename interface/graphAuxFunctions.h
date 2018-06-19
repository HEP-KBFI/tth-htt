#ifndef tthAnalysis_HiggsToTauTau_graphAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_graphAuxFunctions_h

#include <TGraph.h>
#include <TGraphAsymmErrors.h> 

#include<string>

TGraphAsymmErrors* compRatioGraph(const std::string& ratioGraphName, const TGraph* numerator, const TGraph* denominator);

void dumpGraph(const TGraph* graph);

#endif // tthAnalysis_HiggsToTauTau_graphAuxFunctions_h
