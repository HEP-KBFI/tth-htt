#ifndef tthAnalysis_HiggsToTauTau_BtagSFRatioFacility_h
#define tthAnalysis_HiggsToTauTau_BtagSFRatioFacility_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

class BtagSFRatioFacility
{
public:
  BtagSFRatioFacility(const edm::ParameterSet & pset);

  double
  get_btagSFRatio(const std::string & central_or_shift,
                  int nselJets) const;

protected:
  double
  get_btagSFRatio(const std::vector<double> & btagSFRatios,
                  int nselJets) const;

  std::map<std::string, std::vector<double>> btagSFRatios_;
  bool has_central_;
  int max_njets_;
};

#endif // tthAnalysis_HiggsToTauTau_BtagSFRatioFacility_h
