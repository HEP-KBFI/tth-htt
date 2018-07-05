#ifndef tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h
#define tthAnalysis_HiggsToTauTau_JetToTauFakeRateInterface_h

#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateWeightEntry.h" // JetToTauFakeRateWeightEntry
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kFRjt_*

#include <vector> // std::vector<>

class JetToTauFakeRateInterface
{
public:
  JetToTauFakeRateInterface(const edm::ParameterSet & cfg,
                            int central_or_shift = kFRjt_central);
  ~JetToTauFakeRateInterface();

  // jet->tau fake-rates (product of fake-rates in MC, determined in bins of tau candidate pT and eta, and data/MC scale factors)
  double
  getWeight_lead(double hadTauPt_lead,
                 double hadTauAbsEta_lead) const;

  double
  getWeight_sublead(double hadTauPt_sublead,
                    double hadTauAbsEta_sublead) const;

  double
  getWeight_third(double hadTauPt_third,
                  double hadTauAbsEta_third) const;
  
  double
  getWeight_fourth(double hadTauPt_fourth,
		   double hadTauAbsEta_fourth) const;

  // jet->tau fake-rate scale factors (ratio of jet->tau fake-rates in data and MC simulation);
  // to be applied to simulated events in case data-driven "fake" background estimation is applied to leptons only
  double
  getSF_lead(double hadTauPt_lead,
             double hadTauAbsEta_lead) const;

  double
  getSF_sublead(double hadTauPt_sublead,
                double hadTauAbsEta_sublead) const;

  double
  getSF_third(double hadTauPt_third,
              double hadTauAbsEta_third) const;

  double
  getSF_fourth(double hadTauPt_fourth,
	       double hadTauAbsEta_fourth) const;
protected:
  enum { kWeight, kSF };

  double
  getWeight_or_SF(double hadTauPt_lead,
                  double hadTauAbsEta_lead,
                  int mode,
                  int order) const;

private:
  TFile * inputFile_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_lead_;
  bool isInitialized_lead_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_sublead_;
  bool isInitialized_sublead_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_third_;
  bool isInitialized_third_;
  std::vector<JetToTauFakeRateWeightEntry*> jetToTauFakeRateWeights_fourth_;
  bool isInitialized_fourth_;
};

#endif
