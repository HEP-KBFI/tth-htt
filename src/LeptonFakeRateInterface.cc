#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile

LeptonFakeRateInterface::LeptonFakeRateInterface(const edm::ParameterSet & cfg,
                                                 int central_or_shift)
  : central_or_shift_(central_or_shift)
  , lutFakeRate_e_(nullptr)
  , lutFakeRate_mu_(nullptr)
{
  const std::string inputFileName    = cfg.getParameter<std::string>("inputFileName");
  const std::string histogramName_e  = cfg.getParameter<std::string>("histogramName_e");
  const std::string histogramName_mu = cfg.getParameter<std::string>("histogramName_mu");
  lutFakeRate_e_  = new lutWrapperTH2(inputFiles_, inputFileName, histogramName_e,  lut::kXptYabsEta, -1., 100.);
  lutFakeRate_mu_ = new lutWrapperTH2(inputFiles_, inputFileName, histogramName_mu, lut::kXptYabsEta, -1., 100.);
}

LeptonFakeRateInterface::~LeptonFakeRateInterface()
{
  for(auto & kv: inputFiles_)
  {
    delete kv.second;
  }
}

double
LeptonFakeRateInterface::getWeight_e(double electronPt,
                                     double electronAbsEta) const
{
  double weight = lutFakeRate_e_->getSF(electronPt, electronAbsEta);
  if(central_or_shift_ != kFRl_central)
  {
    if(central_or_shift_ == kFRe_shape_ptUp)
    {
      if(electronPt > 30.) weight *= 1.4;
      else                 weight *= 0.6;
    }
    else if( central_or_shift_ == kFRe_shape_ptDown)
    {
      if(electronPt > 30.) weight *= 0.6;
      else                 weight *= 1.4;
    }
    else if(central_or_shift_ == kFRe_shape_etaUp)
    {
      if(electronAbsEta < 1.479) weight *= 1.4;
      else                       weight *= 0.6;
    }
    else if(central_or_shift_ == kFRe_shape_etaDown)
    {
      if(electronAbsEta < 1.479) weight *= 0.6;
      else                       weight *= 1.4;
    }
    else if(central_or_shift_ == kFRe_shape_eta_barrelUp)
    {
      if     (electronAbsEta < 0.8)   weight *= 1.4;
      else if(electronAbsEta < 1.479) weight *= 0.6;
    }
    else if(central_or_shift_ == kFRe_shape_eta_barrelDown)
    {
      if     (electronAbsEta < 0.8)   weight *= 0.6;
      else if(electronAbsEta < 1.479) weight *= 1.4;
    }
  }
  return weight;
}

double
LeptonFakeRateInterface::getWeight_mu(double muonPt,
                                      double muonAbsEta) const
{
  double weight = lutFakeRate_mu_->getSF(muonPt, muonAbsEta);
  if(central_or_shift_ != kFRl_central)
  {
    if(central_or_shift_ == kFRm_shape_ptUp)
    {
      if(muonPt > 30.) weight *= 1.4;
      else             weight *= 0.6;
    }
    else if(central_or_shift_ == kFRm_shape_ptDown)
    {
      if(muonPt > 30.) weight *= 0.6;
      else             weight *= 1.4;
    }
    else if(central_or_shift_ == kFRm_shape_etaUp)
    {
      if(muonAbsEta < 1.479) weight *= 1.4;
      else                   weight *= 0.6;
    }
    else if(central_or_shift_ == kFRm_shape_etaDown)
    {
      if(muonAbsEta < 1.479) weight *= 0.6;
      else                   weight *= 1.4;
    }
  }
  return weight;
}
