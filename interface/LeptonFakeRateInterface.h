#ifndef tthAnalysis_HiggsToTauTau_LeptonFakeRateInterface_h
#define tthAnalysis_HiggsToTauTau_LeptonFakeRateInterface_h

#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kFRl_*

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <map> // std::map<,>

// forward declarations
class lutWrapperBase;
class TFile;

class LeptonFakeRateInterface
{
public:
  LeptonFakeRateInterface(const edm::ParameterSet & cfg,
                          int central_or_shift = kFRl_central);
  ~LeptonFakeRateInterface();

  double
  getWeight_e(double electronPt,
              double electronAbsEta) const;

  double
  getWeight_mu(double muonPt,
               double muonAbsEta) const;

private:
  int central_or_shift_;

  std::map<std::string, TFile *> inputFiles_;

  lutWrapperBase * lutFakeRate_e_;
  lutWrapperBase * lutFakeRate_mu_;
};

#endif
