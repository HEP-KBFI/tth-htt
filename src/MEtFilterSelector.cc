#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h"

#include <TString.h> // Form()
#include <iostream> // std::cout

MEtFilterSelector::MEtFilterSelector(const edm::ParameterSet & cfg,
                                     bool verbose)
  : verbose_(verbose)
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
      if(verbose_)
      {
        std::cout << "Failed MEt Filter " << static_cast<MEtFilterFlag>(flag) << '\n'
                  << getMEtFilterFlagString(static_cast<MEtFilterFlag>(flag)) << '\n'
        ;
      }
      return false;
    }
  }
  return true;
}

