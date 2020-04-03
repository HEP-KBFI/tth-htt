#ifndef tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h"   // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h"    // TrigObj
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h"  // TauFilterBit (enum)

#include <vector> // std::vector
#include <string> // std::string

std::string
getEtaBin(double minAbsEta,
          double maxAbsEta);

std::string
getPtBin(double minPt,
         double maxPt);

TauFilterBit
getTrigMatchingOption(const std::string& trigMatching);

#endif // tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h
