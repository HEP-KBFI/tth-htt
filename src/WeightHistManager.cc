#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

WeightHistManager::WeightHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  binningOptions_["genWeight"] = new binningOptionType("genWeight", 200, -10., +10.);
  binningOptions_["pileupWeight"] = new binningOptionType("pileupWeight", 200, 0., 2.);
  binningOptions_["data_to_MC_correction"] = new binningOptionType("data_to_MC_correction", 200, 0., 2.);
  binningOptions_["fakeRate"] = new binningOptionType("fakeRate", 200,-1., +1.);
}

WeightHistManager::~WeightHistManager()
{
  for ( std::map<std::string, binningOptionType*>::iterator it = binningOptions_.begin();
	it != binningOptions_.end(); ++it ) {
    delete it->second;
  }
}

void WeightHistManager::bookHistograms(TFileDirectory& dir, const std::vector<std::string>& weight_names)
{
  for ( std::vector<std::string>::const_iterator weight_name = weight_names.begin();
	weight_name != weight_names.end(); ++weight_name ) {
    std::map<std::string, binningOptionType*>::const_iterator binningOption_iter = binningOptions_.find(*weight_name);
    if ( binningOption_iter == binningOptions_.end() ) {
      throw cms::Exception("WeightHistManager::bookHistograms") 
	<< "No binning options defined for weight of name '" << (*weight_name) << "' !!\n";
    }
    
    const binningOptionType* binningOption = binningOption_iter->second;
    TH1* histogram = book1D(
      dir, binningOption->histogramName_, binningOption->histogramName_, 
      binningOption->numBinsX_, binningOption->xMin_, binningOption->xMax_);
    histograms_weights_[*weight_name] = histogram;
  }
}

void WeightHistManager::fillHistograms(const std::string& weight_name, double weight_value)
{
  double evtWeight = 1.;
  double evtWeightErr = 0.;

  std::map<std::string, TH1*>::const_iterator histogram_iter = histograms_weights_.find(weight_name);
  if ( histogram_iter == histograms_weights_.end() ) {
    throw cms::Exception("WeightHistManager::fillHistograms") 
      << "No histogram booked for weight of name '" << weight_name << "' !!\n";
  }
  
  fillWithOverFlow(histogram_iter->second, weight_value, evtWeight, evtWeightErr);
}
