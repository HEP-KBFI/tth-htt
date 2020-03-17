#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era, kEra_*, cmsException()

#include <TFile.h> // TFile

#include <iostream> // std::cout

LeptonFakeRateInterface::LeptonFakeRateInterface(const edm::ParameterSet & cfg)
  : jetToEleFakeRateCorr_(1.)
  , jetToMuFakeRateCorr_(1.)
{
  const std::string inputFileName    = cfg.getParameter<std::string>("inputFileName");
  const std::string histogramName_e  = cfg.getParameter<std::string>("histogramName_e");
  const std::string histogramName_mu = cfg.getParameter<std::string>("histogramName_mu");

  const int era = get_era(cfg.getParameter<std::string>("era"));
  switch(era)
  {
    // Slide 16 in https://indico.cern.ch/event/885279/contributions/3789360/attachments/2004535/3347458/mar15.pdf
    case kEra_2016: jetToEleFakeRateCorr_ = 1.376; jetToMuFakeRateCorr_ = 1.050; break;
    case kEra_2017: jetToEleFakeRateCorr_ = 1.252; jetToMuFakeRateCorr_ = 1.157; break;
    case kEra_2018: jetToEleFakeRateCorr_ = 1.325; jetToMuFakeRateCorr_ = 1.067; break;
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
  int central_or_shift_e = central_or_shift;
  if(central_or_shift_e == kFRe_shape_corrUp || central_or_shift_e == kFRe_shape_corrDown)
  {
    central_or_shift_e = kFRl_central;
  }
  if(! lutFakeRate_e_.count(central_or_shift_e))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option: " << central_or_shift_e;
  }
  const double jetToEleFakeRate = lutFakeRate_e_.at(central_or_shift_e)->getSF(electronPt, electronAbsEta);
  if(central_or_shift == kFRe_shape_corrUp)
  {
    return jetToEleFakeRate * jetToEleFakeRateCorr_ * jetToEleFakeRateCorr_;
  }
  else if(central_or_shift == kFRe_shape_corrDown)
  {
    return jetToEleFakeRate;
  }
  return jetToEleFakeRate * jetToEleFakeRateCorr_;
}

double
LeptonFakeRateInterface::getWeight_mu(double muonPt,
                                      double muonAbsEta,
                                      int central_or_shift) const
{
  int central_or_shift_m = central_or_shift;
  if(central_or_shift_m == kFRm_shape_corrUp || central_or_shift_m == kFRm_shape_corrDown)
  {
    central_or_shift_m = kFRl_central;
  }
  if(! lutFakeRate_mu_.count(central_or_shift_m))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option: " << central_or_shift_m;
  }
  const double jetToMuFakeRate = lutFakeRate_mu_.at(central_or_shift_m)->getSF(muonPt, muonAbsEta);
  if(central_or_shift == kFRm_shape_corrUp)
  {
    return jetToMuFakeRate * jetToMuFakeRateCorr_ * jetToMuFakeRateCorr_;
  }
  else if(central_or_shift == kFRm_shape_corrDown)
  {
    return jetToMuFakeRate;
  }
  return jetToMuFakeRate * jetToMuFakeRateCorr_;
}
