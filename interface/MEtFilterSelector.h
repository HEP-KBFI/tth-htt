#ifndef tthAnalysis_HiggsToTauTau_MEtFilterSelector_h
#define tthAnalysis_HiggsToTauTau_MEtFilterSelector_h

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

class MEtFilterSelector 
{
public:
  explicit MEtFilterSelector(const edm::ParameterSet & cfg,
                             bool isMC,
                             bool verbose = false);

  virtual ~MEtFilterSelector() {}

  // Returns value true if the event passes all the filters that are applied 
  bool
  operator()(const MEtFilter & metFilter) const;

protected:
  std::array<bool, MEtFilterFlag::LAST> apply_;
  bool verbose_;
};

#endif // tthAnalysis_HiggsToTauTau_MEtFilterSelector_h
