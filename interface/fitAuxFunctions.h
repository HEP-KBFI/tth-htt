#ifndef tthAnalysis_HiggsToTauTau_fitAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_fitAuxFunctions_h

#include <TVectorD.h>
#include <TMatrixD.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>

#include <vector>
#include <string>

struct EigenVector_and_Value
{
  EigenVector_and_Value(const TVectorD& eigenVector, double eigenValue)
    : eigenVector_(eigenVector),
      eigenValue_(eigenValue)
  {}
  ~EigenVector_and_Value() {}  
  TVectorD eigenVector_;
  double eigenValue_;
};

std::vector<EigenVector_and_Value> compEigenVectors_and_Values(const TMatrixD& cov);

struct fitFunction_and_legendEntry
{
  fitFunction_and_legendEntry(TF1* fitFunction, const std::string& legendEntry)
    : fitFunction_(fitFunction),
      legendEntry_(legendEntry)
  {}
  ~fitFunction_and_legendEntry() {}
  TF1* fitFunction_;
  std::string legendEntry_;
};

void makeControlPlot_graphs(
       TGraphAsymmErrors* graph_data, const std::string& legendEntry_data,
       TGraphAsymmErrors* graph_mc, const std::string& legendEntry_mc,
       TGraphAsymmErrors* graph_data_div_mc, 
       double xMin, double xMax, const std::string& xAxisTitle, 
       bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yMin_ratio, double yMax_ratio, const std::string& yAxisTitle_ratio, 
       const std::string& outputFileName);
void makeControlPlot_fit(
       TGraphAsymmErrors* graph, 
       TF1* fitFunction_central, std::vector<fitFunction_and_legendEntry>& fitFunctions_sysShifts, 
       double xMin, double xMax, const std::string& xAxisTitle, 
       bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, 
       const std::string& outputFileName);

#endif
