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

  // jet->tau fake-rates (product of fake-rates in MC, determined in bins of tau candidate pT and eta, and data/MC scale factors)
  double getWeight_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const;
  double getWeight_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const;
  double getWeight_third(double hadTauPt_third, double hadTauAbsEta_third) const;
  
  // jet->tau fake-rate scale factors (ratio of jet->tau fake-rates in data and MC simulation);
  // to be applied to simulated events in case data-driven "fake" background estimation is applied to leptons only
  double getSF_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const;
  double getSF_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const;
  double getSF_third(double hadTauPt_third, double hadTauAbsEta_third) const;

 protected:
  enum { kWeight, kSF };
  double getWeight_or_SF_lead(double hadTauPt_lead, double hadTauAbsEta_lead, int mode) const;
  double getWeight_or_SF_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead, int mode) const;
  double getWeight_or_SF_third(double hadTauPt_third, double hadTauAbsEta_third, int mode) const;

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
