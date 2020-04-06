#ifndef tthAnalysis_HiggsToTauTau_backgroundEstimation_h
#define tthAnalysis_HiggsToTauTau_backgroundEstimation_h

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

double
prob_chargeMisId(Era era,
                 int lepton_type,
                 double lepton_pt,
                 double lepton_eta);

#endif // tthAnalysis_HiggsToTauTau_backgroundEstimation_h



