#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_2lss::EvtHistManager_2lss(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
{
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "numBJets_loose_vs_numJets",
    "numBJets_medium_vs_numJets",
    "mvaOutput_2lss_ttV",
    "mvaOutput_2lss_ttbar",
    "mvaOutput_Hj_tagger",
    "mvaDiscr_2lss"
  };
  const std::vector<std::string> sysOpts_all = {
    "EventCounter",
    "output_NN_ttH_ee",
    "output_NN_ttH_em",
    "output_NN_ttH_mm",
    "output_NN_ttW_ee",
    "output_NN_ttW_em",
    "output_NN_ttW_mm",
    "output_NN_rest_ee",
    "output_NN_rest_em",
    "output_NN_rest_mm",
    "output_NN_tH_ee",
    "output_NN_tH_em",
    "output_NN_tH_mm",
    "mass_2L_ee_lj_pos",
    "mass_2L_ee_lj_neg",
    "mass_2L_ee_hj_pos",
    "mass_2L_ee_hj_neg",
    "mass_2L_em_lj_pos",
    "mass_2L_em_lj_neg",
    "mass_2L_em_hj_pos",
    "mass_2L_em_hj_neg",
    "mass_2L_mm_lj_pos",
    "mass_2L_mm_lj_neg",
    "mass_2L_mm_hj_pos",
    "mass_2L_mm_hj_neg",
    "mass_2L_cr"
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
EvtHistManager_2lss::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_2lss::bookCategories(TFileDirectory & dir,
                                    const std::map<std::string, std::vector<double>> & categories,
                                    const std::map<std::string, std::vector<double>> & categories_SVA
                                  )
{
  for(auto category: categories)
  {
    if(! category.second.empty())
    {
      const int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    }
    else
    {
      histograms_by_category_[category.first] = book1D(dir, category.first, category.first, 100,  0., +1.);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }

  for(auto category: categories_SVA)
  {
    if(! category.second.empty()) // the CR should have only one bin
    {
      const int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_SVA_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    }
    else
    {
      Float_t bins_mass_2L[10] = {10.,40.0,55.0,70.0,80.0,95.0,110.0,140.0,180.,800.0};
      histograms_by_category_SVA_[category.first] = book1D(dir, category.first, category.first, 9,  bins_mass_2L);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }
}

void
EvtHistManager_2lss::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_mvaOutput_2lss_ttV_   = book1D(dir, "mvaOutput_2lss_ttV",   "mvaOutput_2lss_ttV",   40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_ = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2lss_        = book1D(dir, "mvaDiscr_2lss",        "mvaDiscr_2lss",         7,  0.5, 7.5);
  histogram_mvaOutput_Hj_tagger_  = book1D(dir, "mvaOutput_Hj_tagger",  "mvaOutput_Hj_tagger",  20, -1., +1.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_2lss::fillHistograms(const EvtHistManager_2lss_Input & variables)
{
  const double evtWeightErr = 0.;
  const double & evtWeight = variables.evtWeight;

  fillWithOverFlow(histogram_numElectrons_,    variables.numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        variables.numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      variables.numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         variables.numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  variables.numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, variables.numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_,   variables.mvaOutput_2lss_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, variables.mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_,        variables.mvaDiscr_2lss,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_Hj_tagger_,  variables.mvaOutput_Hj_tagger,  evtWeight, evtWeightErr);

  if(! histograms_by_category_.count(variables.category))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << variables.category << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_[variables.category], variables.mvaOutput_category, evtWeight, evtWeightErr);

  if(! histograms_by_category_SVA_.count(variables.category_SVA))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << variables.category_SVA << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_SVA_[variables.category_SVA], variables.mass_2L, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
