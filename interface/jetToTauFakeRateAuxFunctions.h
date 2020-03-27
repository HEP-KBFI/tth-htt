#ifndef tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h" // TrigObj

#include <vector> // std::vector
#include <string> // std::string

std::string
getEtaBin(double minAbsEta,
          double maxAbsEta);

std::string
getPtBin(double minPt,
         double maxPt);

enum { kFilterBit_notApplied, kFilterBit_looseChargedIso, kFilterBit_mediumChargedIso, kFilterBit_tightChargedIso };

int
getTrigMatchingOption(const std::string& trigMatching);

bool 
matchesTrigObj(const RecoJet& jet, const std::vector<TrigObj>& triggerObjects, int filterBit, double dRmatch = 0.3);

#endif // tthAnalysis_HiggsToTauTau_jetToTauFakeRateAuxFunctions_h
