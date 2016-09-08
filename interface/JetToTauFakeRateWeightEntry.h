#ifndef tthAnalysis_HiggsToTauTau_JetToTauFakeRateWeightEntry_h
#define tthAnalysis_HiggsToTauTau_JetToTauFakeRateWeightEntry_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include <TFile.h> // TFile
#include <TGraphAsymmErrors.h> // TGraphAsymmErrors
#include <TF1.h> // TF1

#include <string>

enum { kFRt_central, kFRt_normUp, kFRt_normDown, kFRt_shapeUp, kFRt_shapeDown };

struct JetToTauFakeRateWeightEntry
{
  JetToTauFakeRateWeightEntry(double absEtaMin, double absEtaMax, const std::string& hadTauSelection,
			      TFile* inputFile, const edm::ParameterSet& cfg, int central_or_shift);
  ~JetToTauFakeRateWeightEntry();

  double getWeight(double pt) const;
    
  double absEtaMin_;
  double absEtaMax_;
  std::string hadTauSelection_;
  std::string graphName_;
  TGraphAsymmErrors* graph_;
  bool applyGraph_;
  std::string fitFunctionName_;
  TF1* fitFunction_;
  bool applyFitFunction_;
};

#endif
