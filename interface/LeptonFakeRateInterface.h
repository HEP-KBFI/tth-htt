#ifndef tthAnalysis_HiggsToTauTau_LeptonFakeRateInterface_h
#define tthAnalysis_HiggsToTauTau_LeptonFakeRateInterface_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase

#include <TFile.h> // TFile

#include <map>

enum { kFRl_central };

class LeptonFakeRateInterface
{
 public:
  LeptonFakeRateInterface(const edm::ParameterSet& cfg, int central_or_shift = kFRl_central);
  ~LeptonFakeRateInterface();

  double getWeight_e(double electronPt, double electronAbsEta) const;
  double getWeight_mu(double muonPt, double muonAbsEta) const;
  
 private:
  std::map<std::string, TFile*> inputFiles_;
  
  lutWrapperBase* lutFakeRate_e_;
  lutWrapperBase* lutFakeRate_mu_;
};

#endif
