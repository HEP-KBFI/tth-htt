#include "tthAnalysis/HiggsToTauTau/interface/BtagSFRatioFacility.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <cassert> // assert()

BtagSFRatioFacility::BtagSFRatioFacility(const edm::ParameterSet & pset)
  : has_central_(false)
  , max_njets_(-1)
{
  const std::vector<std::string> central_or_shifts = pset.getParameterNames();
  if(central_or_shifts.empty())
  {
    throw cmsException(this, __func__, __LINE__) << "Empty PSet provided";
  }
  for(const std::string & central_or_shift: central_or_shifts)
  {
    const std::vector<double> btagSFRatios = pset.getParameter<std::vector<double>>(central_or_shift);
    if(max_njets_ < 0)
    {
      max_njets_ = btagSFRatios.size();
    }
    else
    {
      if(max_njets_ != static_cast<int>(btagSFRatios.size()))
      {
        throw cmsException(this, __func__, __LINE__)
          << "Detected histograms with different number of bins: expected" << max_njets_ << ", got " << btagSFRatios.size()
        ;
      }
    }
    btagSFRatios_[central_or_shift] = btagSFRatios;
  }
  has_central_ = btagSFRatios_.count("central");
  if(max_njets_ < 2)
  {
    throw cmsException(this, __func__, __LINE__) << "Too few bins: " << max_njets_;
  }
}

double
BtagSFRatioFacility::get_btagSFRatio(const std::string & central_or_shift,
                                     int nselJets) const
{
  if(btagSFRatios_.count(central_or_shift))
  {
    return get_btagSFRatio(btagSFRatios_.at(central_or_shift), nselJets);
  }
  else
  {
    if(! has_central_)
    {
      throw cmsException(this, __func__, __LINE__)
        << "b-tagging SF ratio Requested for '" << central_or_shift << "' nor for 'central' not loaded"
      ;
    }
    return get_btagSFRatio(btagSFRatios_.at("central"), nselJets);
  }
}

double
BtagSFRatioFacility::get_btagSFRatio(const std::vector<double> & btagSFRatios,
                                     int nselJets) const
{
  const int jetIdx = std::min(max_njets_ - 1, nselJets);
  assert(jetIdx >= 0);
  return btagSFRatios.at(jetIdx);
}
