#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h"

#include <TString.h> // Form()
#include <iostream>

MEtFilterSelector::MEtFilterSelector(const edm::ParameterSet & cfg)
{
  for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
  {
    const std::string cfgParam = Form("apply_%s", getMEtFilterFlagString(static_cast<MEtFilterFlag>(flag)));
    apply_[flag] = cfg.exists(cfgParam) ? cfg.getParameter<bool>(cfgParam) : false;
  }
}

bool
MEtFilterSelector::operator()(const MEtFilter & metFilter) const
{
  for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
  {
    if(apply_.at(flag) && ! metFilter.getFlag(static_cast<MEtFilterFlag>(flag)))
    {
      std::cout << "Failed MEt Filter " << static_cast<MEtFilterFlag>(flag) << std::endl;
      std::cout << getMEtFilterFlagString(static_cast<MEtFilterFlag>(flag)) << std::endl;
      return false;
    }
  }
  return true;
}

