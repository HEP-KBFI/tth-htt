#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile

#include <iostream> // std::cout

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
  std::cout << "Loaded histograms '" << histogramName_e << "' and '"
            << histogramName_mu << "' from file " << inputFileName << '\n'
  ;
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
  return lutFakeRate_e_->getSF(electronPt, electronAbsEta);
}

double
LeptonFakeRateInterface::getWeight_mu(double muonPt,
                                      double muonAbsEta) const
{
  return lutFakeRate_mu_->getSF(muonPt, muonAbsEta);
}
