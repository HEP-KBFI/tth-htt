#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era, kEra_*, cmsException()

#include <TFile.h> // TFile

#include <iostream> // std::cout

LeptonFakeRateInterface::LeptonFakeRateInterface(const edm::ParameterSet & cfg)
  : jetToEleFakeRateCorr(1.)
{
  const std::string inputFileName    = cfg.getParameter<std::string>("inputFileName");
  const std::string histogramName_e  = cfg.getParameter<std::string>("histogramName_e");
  const std::string histogramName_mu = cfg.getParameter<std::string>("histogramName_mu");

  const int era = get_era(cfg.getParameter<std::string>("era"));
  switch(era)
  {
    // Slide 3 in https://cernbox.cern.ch/index.php/s/u8bcCuU4WM2wzFY
    case kEra_2016: jetToEleFakeRateCorr = 1.4; break;
    case kEra_2017: jetToEleFakeRateCorr = 1.2; break;
    case kEra_2018: jetToEleFakeRateCorr = 1.3; break;
  }

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
  const double jetToEleFakeRate = lutFakeRate_e_.at(central_or_shift)->getSF(electronPt, electronAbsEta);
  return jetToEleFakeRate * jetToEleFakeRateCorr;
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
