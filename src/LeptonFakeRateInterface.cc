#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile

LeptonFakeRateInterface::LeptonFakeRateInterface(const edm::ParameterSet& cfg, int central_or_shift)
  : lutFakeRate_e_(0),
    lutFakeRate_mu_(0)
{
  std::string inputFileName = cfg.getParameter<std::string>("inputFileName");
  std::string histogramName_e = cfg.getParameter<std::string>("histogramName_e");
  std::string histogramName_mu = cfg.getParameter<std::string>("histogramName_mu");
  lutFakeRate_e_ = new lutWrapperTH2(
    inputFiles_, inputFileName, histogramName_e,
    lut::kXptYabsEta, -1., 100.);
  lutFakeRate_mu_ = new lutWrapperTH2(
    inputFiles_, inputFileName, histogramName_mu,
    lut::kXptYabsEta, -1., 100.);
}

LeptonFakeRateInterface::~LeptonFakeRateInterface()
{
  for ( std::map<std::string, TFile*>::iterator it = inputFiles_.begin();
        it != inputFiles_.end(); ++it ) {
    delete it->second;
  }
}

double LeptonFakeRateInterface::getWeight_e(double electronPt, double electronAbsEta) const
{
  double weight = lutFakeRate_e_->getSF(electronPt, electronAbsEta);
  return weight;
}

double LeptonFakeRateInterface::getWeight_mu(double muonPt, double muonAbsEta) const
{
  double weight = lutFakeRate_mu_->getSF(muonPt, muonAbsEta);
  return weight;
}
