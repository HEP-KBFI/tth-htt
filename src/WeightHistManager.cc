#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

WeightHistManager::WeightHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  binningOptions_["genWeight"] = new binningOptionType("genWeight", 200, -10., +10.);
  binningOptions_["lheWeight"] = new binningOptionType("lheWeight", 200, -10., +10.);
  binningOptions_["pileupWeight"] = new binningOptionType("pileupWeight", 200, 0., 2.);
  binningOptions_["triggerWeight"] = new binningOptionType("triggerWeight", 100, 0., 10.);
  binningOptions_["btagWeight"] = new binningOptionType("btagWeight", 200, 0., 2.);
  binningOptions_["leptonEff"] = new binningOptionType("leptonEff", 200, 0., 2.);
  binningOptions_["hadTauEff"] = new binningOptionType("hadTauEff", 200, 0., 2.);
  binningOptions_["data_to_MC_correction"] = new binningOptionType("data_to_MC_correction", 200, 0., 2.);
  binningOptions_["fakeRate"] = new binningOptionType("fakeRate", 200,-1., +1.);
}

WeightHistManager::~WeightHistManager()
{
  for(auto & kv: binningOptions_)
  {
    delete kv.second;
  }
}

void
WeightHistManager::bookHistograms(TFileDirectory & dir,
                                  const std::vector<std::string> & weight_names)
{
  for(const std::string & weight_name: weight_names)
  {
    if(! binningOptions_.count(weight_name))
    {
      throw cmsException(this, __func__)
        << "No binning options defined for weight of name '" << weight_name << "' !!";
    }

    const binningOptionType * binningOption = binningOptions_.at(weight_name);
    TH1 * histogram = book1D(
      dir,
      binningOption->histogramName_,
      binningOption->histogramName_,
      binningOption->numBinsX_,
      binningOption->xMin_,
      binningOption->xMax_
    );
    histograms_weights_[weight_name] = histogram;
  }
}

void
WeightHistManager::fillHistograms(const std::string & weight_name,
                                  double weight_value)
{
  const double evtWeight = 1.;
  const double evtWeightErr = 0.;

  if(! histograms_weights_.count(weight_name))
  {
    throw cmsException(this, __func__)
      << "No histogram booked for weight of name '" << weight_name << "' !!";
  }

  fillWithOverFlow(histograms_weights_.at(weight_name), weight_value, evtWeight, evtWeightErr);
}

void
WeightHistManager::bookHistograms(TFileDirectory & dir)
{
  throw cmsException(this, __func__) << "Use another function!";
}

WeightHistManager::binningOptionType::binningOptionType(const std::string & histogramName,
                                                        int numBinsX,
                                                        double xMin,
                                                        double xMax)
  : histogramName_(histogramName)
  , numBinsX_(numBinsX)
  , xMin_(xMin)
  , xMax_(xMax)
{}
