#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile

#include <iostream> // std::cout

LeptonFakeRateInterface::LeptonFakeRateInterface(const edm::ParameterSet & cfg)
{
  const std::string inputFileName    = cfg.getParameter<std::string>("inputFileName");
  const std::string histogramName_e  = cfg.getParameter<std::string>("histogramName_e");
  const std::string histogramName_mu = cfg.getParameter<std::string>("histogramName_mu");
  for(int FR_option = kFRl_central; FR_option <= kFRm_shape_eta_barrelDown; ++FR_option)
  {
    std::string suffix = "";
    if(FR_option == kFRl_central || (FR_option >= kFRe_shape_ptUp && FR_option <= kFRe_shape_eta_barrelDown))
    {
      switch(FR_option)
      {
        case kFRl_central:              suffix = "";      break;
        case kFRe_shape_ptUp:           suffix = "_pt1";  break;
        case kFRe_shape_ptDown:         suffix = "_pt2";  break;
        case kFRe_shape_normUp:         suffix = "_up";   break;
        case kFRe_shape_normDown:       suffix = "_down"; break;
        case kFRe_shape_eta_barrelUp:   suffix = "_be1";  break;
        case kFRe_shape_eta_barrelDown: suffix = "_be2";  break;
        default: throw cmsException(this, __func__, __LINE__) << "Invalid option: " << FR_option;
      }
      const std::string histogramName = histogramName_e + suffix;
      lutFakeRate_e_[FR_option]  = new lutWrapperTH2(
        inputFiles_, inputFileName, histogramName,  lut::kXptYabsEta, -1., 100.
      );
      std::cout << "Loaded histogram '" << histogramName << "' from file " << inputFileName << '\n';
    }
    if(FR_option == kFRl_central || (FR_option >= kFRm_shape_ptUp && FR_option <= kFRm_shape_eta_barrelDown))
    {
      switch(FR_option)
      {
        case kFRl_central:              suffix = "";      break;
        case kFRm_shape_ptUp:           suffix = "_pt1";  break;
        case kFRm_shape_ptDown:         suffix = "_pt2";  break;
        case kFRm_shape_normUp:         suffix = "_up";   break;
        case kFRm_shape_normDown:       suffix = "_down"; break;
        case kFRm_shape_eta_barrelUp:   suffix = "_be1";  break;
        case kFRm_shape_eta_barrelDown: suffix = "_be2";  break;
        default: throw cmsException(this, __func__, __LINE__) << "Invalid option: " << FR_option;
      }
      const std::string histogramName = histogramName_mu + suffix;
      lutFakeRate_mu_[FR_option] = new lutWrapperTH2(
        inputFiles_, inputFileName, histogramName, lut::kXptYabsEta, -1., 100.
      );
      std::cout << "Loaded histogram '" << histogramName << "' from file " << inputFileName << '\n';
    }
  }
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
                                     double electronAbsEta,
                                     int central_or_shift) const
{
  if(! lutFakeRate_e_.count(central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option: " << central_or_shift;
  }
  return lutFakeRate_e_.at(central_or_shift)->getSF(electronPt, electronAbsEta);
}

double
LeptonFakeRateInterface::getWeight_mu(double muonPt,
                                      double muonAbsEta,
                                      int central_or_shift) const
{
  if(! lutFakeRate_mu_.count(central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option: " << central_or_shift;
  }
  return lutFakeRate_mu_.at(central_or_shift)->getSF(muonPt, muonAbsEta);
}
