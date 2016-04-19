#ifndef tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_lutAuxFunctions_h

#include "FWCore/ParameterSet/interface/FileInPath.h" // edm::FileInPath

#include <TH1.h> // TH1
#include <TH2.h> // TH2

TH1* loadTH1(const edm::FileInPath& fileName, const std::string& histogramName);
double get_sf_from_TH1(TH1* lut, double pt_or_eta);

TH2* loadTH2(const edm::FileInPath& fileName, const std::string& histogramName);
double get_sf_from_TH2(TH2* lut, double pt, double eta);

#endif // tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
