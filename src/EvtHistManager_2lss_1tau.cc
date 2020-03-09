#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
  , option_(kOption_undefined)
{
  const std::string option_string = cfg.getParameter<std::string>("option");
  if(option_string == "allHistograms")
  {
    option_ = kOption_allHistograms;
  }
  else if(option_string == "minimalHistograms")
  {
    option_ = kOption_minimalHistograms;
  }
  else
  {
    throw cmsException(__func__) << "Invalid Configuration parameter 'option' = " << option_string;
  }
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "numBJets_loose_vs_numJets",
    "numBJets_medium_vs_numJets",
    "mTauTauVis",
    "mTauTauVis1",
    "mTauTauVis2",
    "memOutput_LR",
    "mvaOutput_final",
    "output_NN_sig_2_rest_2p2_th_2_ttH",
    "output_NN_sig_2_rest_2p2_th_2_tH",
    "output_NN_sig_2_rest_2p2_th_2_rest",
    "output_NN_sig_2_rest_2p5_th_2_ttH",
    "output_NN_sig_2_rest_2p5_th_2_tH",
    "output_NN_sig_2_rest_2p5_th_2_rest"
  };
  const std::vector<std::string> sysOpts_all = {
    "EventCounter",
    "output_NN_ttH",
    "output_NN_tH",
    "output_NN_rest"
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
  for(const std::string & sysOpt: sysOpts_all)
  {
    central_or_shiftOptions_[sysOpt] = { "*" };
  }
}

const TH1 *
EvtHistManager_2lss_1tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_2lss_1tau::bookCategories(TFileDirectory & dir,
                                         const std::map<std::string, std::vector<double>> &  categories_list_NN)
{
  for(auto category: categories_list_NN)
  {
    if ( category.second.size() > 0 )
    {
      int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    } else {
      histograms_by_category_[category.first] = book1D(dir, category.first, category.first, 100,  0., +1.);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }
}

void EvtHistManager_2lss_1tau::bookHistograms(TFileDirectory & dir)
{
  if(option_ == kOption_allHistograms)
  {
    histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
    histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
    histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
    histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
    histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
    histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);
  }

  Float_t binsx[12] = { 0.0, 0.14, 0.18, 0.22, 0.28, 0.32, 0.35, 0.38, 0.43, 0.47, 0.53, 1.0 };
  histogram_final_  = book1D(dir, "mvaOutput_final",  "mvaOutput_final", 11, binsx);

  histogram_mTauTauVis_   = book1D(dir, "mTauTauVis",   "mTauTauVis",    20,  0., 200.);
  histogram_mTauTauVis1_  = book1D(dir, "mTauTauVis1",  "mTauTauVis1",   20,  0., 200.);
  histogram_mTauTauVis2_  = book1D(dir, "mTauTauVis2",  "mTauTauVis2",   20,  0., 200.);
  if(option_ == kOption_allHistograms)
  {
    histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 100,  0.,   1.);
  }

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter",   1, -0.5, +0.5);
}

void
EvtHistManager_2lss_1tau::fillHistograms(const EvtHistManager_2lss_1tau_Input & variables)
{
  const double evtWeightErr = 0.;
  const double & evtWeight = variables.evtWeight;

  if(option_ == kOption_allHistograms)
  {
    fillWithOverFlow(histogram_numElectrons_,    variables.numElectrons,    evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numMuons_,        variables.numMuons,        evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numHadTaus_,      variables.numHadTaus,      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numJets_,         variables.numJets,         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numBJets_loose_,  variables.numBJets_loose,  evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numBJets_medium_, variables.numBJets_medium, evtWeight, evtWeightErr);

  }
  fillWithOverFlow(histogram_final_, variables.mvaOutput_2lss_1tau_HTT_SUM_M, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_,   variables.mTauTauVis1,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis1_,  variables.mTauTauVis1,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis2_,  variables.mTauTauVis2,  evtWeight, evtWeightErr);
  if(option_ == kOption_allHistograms)
  {
    fillWithOverFlow(histogram_memOutput_LR_, variables.memOutput_LR, evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);

  if(! histograms_by_category_.count(variables.category_NN_TF))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << variables.category_NN_TF << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_[variables.category_NN_TF], variables.output_NN, evtWeight, evtWeightErr);

}
