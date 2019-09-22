#ifndef tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h
#define tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h

#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateWeightEntry.h" // JetToTauFakeRateWeightEntry
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kFRjt_*

#include <vector> // std::vector<>

class JetToTauFakeRateInterface
{
public:
  JetToTauFakeRateInterface(const edm::ParameterSet & cfg);
  ~JetToTauFakeRateInterface();

  // jet->tau fake-rates (product of fake-rates in MC, determined in bins of tau candidate pT and eta, and data/MC scale factors)
  double
  getWeight_lead(double hadTauPt_lead,
                 double hadTauAbsEta_lead,
                 int central_or_shift) const;

  double
  getWeight_sublead(double hadTauPt_sublead,
                    double hadTauAbsEta_sublead,
                    int central_or_shift) const;

  double
  getWeight_third(double hadTauPt_third,
                  double hadTauAbsEta_third,
                  int central_or_shift) const;

  double
  getWeight_fourth(double hadTauPt_fourth,
                   double hadTauAbsEta_fourth,
                   int central_or_shift) const;

  // jet->tau fake-rate scale factors (ratio of jet->tau fake-rates in data and MC simulation);
  // to be applied to simulated events in case data-driven "fake" background estimation is applied to leptons only
  double
  getSF_lead(double hadTauPt_lead,
             double hadTauAbsEta_lead,
             int central_or_shift) const;

  double
  getSF_sublead(double hadTauPt_sublead,
                double hadTauAbsEta_sublead,
                int central_or_shift) const;

  double
  getSF_third(double hadTauPt_third,
              double hadTauAbsEta_third,
              int central_or_shift) const;

  double
  getSF_fourth(double hadTauPt_fourth,
               double hadTauAbsEta_fourth,
               int central_or_shift) const;

protected:
  enum { kWeight, kSF };

  double
  getWeight_or_SF(double hadTauPt_lead,
                  double hadTauAbsEta_lead,
                  int mode,
                  int order,
                  int central_or_shift) const;

private:
  TFile * inputFile_;
  std::map<int, std::vector<JetToTauFakeRateWeightEntry*>> jetToTauFakeRateWeights_lead_;
  bool isInitialized_lead_;
  std::map<int, std::vector<JetToTauFakeRateWeightEntry*>> jetToTauFakeRateWeights_sublead_;
  bool isInitialized_sublead_;
  std::map<int, std::vector<JetToTauFakeRateWeightEntry*>> jetToTauFakeRateWeights_third_;
  bool isInitialized_third_;
  std::map<int, std::vector<JetToTauFakeRateWeightEntry*>> jetToTauFakeRateWeights_fourth_;
  bool isInitialized_fourth_;
};

#endif
