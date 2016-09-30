#ifndef tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h
#define tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateWeightEntry.h" // JetToTauFakeRateWeightEntry

#include <TFile.h> // TFile

#include <vector>

class JetToTauFakeRateInterface
{
 public:
  JetToTauFakeRateInterface(const edm::ParameterSet& cfg, int central_or_shift = kFRjt_central);
  ~JetToTauFakeRateInterface();

  double getWeight_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const;
  double getWeight_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const;
  double getWeight_third(double hadTauPt_third, double hadTauAbsEta_third) const;
  
 private:
  TFile* inputFile_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_lead_;
  bool isInitialized_lead_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_sublead_;
  bool isInitialized_sublead_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_third_;
  bool isInitialized_third_;
};

#endif
