#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_3l.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_3l::EvtHistManager_3l(const edm::ParameterSet & cfg)
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
    "mvaOutput_3l_ttV",
    "mvaOutput_3l_ttbar",
    "memOutput_isValid",
    "memOutput_errorFlag",
    "memOutput_logWeight_ttH",
    "memOutput_logWeight_tt",
    "memOutput_LR",
    "mem_logCPUTime",
    "mem_logRealTime",
    "output_NN_3l_ttH_tH_3cat_v8_ttH_bl",
    "output_NN_3l_ttH_tH_3cat_v8_ttH_bt",
    "output_NN_3l_ttH_tH_3cat_v8_tH_bl",
    "output_NN_3l_ttH_tH_3cat_v8_tH_bt",
    "output_NN_3l_ttH_tH_3cat_v8_rest_bl",
    "output_NN_3l_ttH_tH_3cat_v8_rest_bt",
    "output_NN_3l_ttH_tH_3cat_v8_cr",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_ttH_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_ttH_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_tH_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_tH_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eee_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eee_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eem_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_eem_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_emm_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_emm_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_mmm_bl",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_rest_mmm_bt",
    "output_NN_sig_2p5_rest_2_th_2p5_withWZ_cr",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_ttH_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_ttH_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_tH_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_tH_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eee_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eee_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eem_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_eem_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_emm_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_emm_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_mmm_bl",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_rest_mmm_bt",
    "output_NN_sig_2_rest_2p5_th_2_withWZ_cr",
    "output_NN_sig_2_rest_2_th_2_withWZ_cr"
  };
  const std::vector<std::string> sysOpts_all = {
    "mvaDiscr_3l",
    "EventCounter",
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
EvtHistManager_3l::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_3l::bookCategories(TFileDirectory & dir,
                                  const std::map<std::string, std::vector<double>> & categories,
                                  const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ,
                                  const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ,
                                  const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ
                                )
{
  for(auto category: categories)
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
  ////////////////////////////////
  for(auto category: categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ)
  {
    if ( category.second.size() > 0 )
    {
      int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_TensorFlow_3l_sig_2_rest_2_th_2_withWZ_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    } else {
      histograms_by_category_TensorFlow_3l_sig_2_rest_2_th_2_withWZ_[category.first] = book1D(dir, category.first, category.first, 100,  0., +1.);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }
  ////////////////////////////////
  for(auto category: categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ)
  {
    if ( category.second.size() > 0 )
    {
      int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    } else {
      histograms_by_category_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ_[category.first] = book1D(dir, category.first, category.first, 100,  0., +1.);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }
  ////////////////////////////////
  for(auto category: categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ)
  {
    if ( category.second.size() > 0 )
    {
      int npoints = category.second.size();
      Float_t binsx[npoints];
      std::copy(category.second.begin(), category.second.end(), binsx);
      histograms_by_category_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ_[category.first] = book1D(dir, category.first, category.first, npoints - 1, binsx);
    } else {
      histograms_by_category_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ_[category.first] = book1D(dir, category.first, category.first, 100,  0., +1.);
    }
    central_or_shiftOptions_[category.first] = { "*" };
  }
  ////////////////////////////////
}

void
EvtHistManager_3l::setCRcategories(TFileDirectory & dir,
                                   const std::vector<std::string> & ctrl_categories)
{
  ctrl_cateories_ = ctrl_categories;
  if(! ctrl_cateories_.empty())
  {
    histogram_ctrl_ = book1D(dir, "control", "control", ctrl_cateories_.size(), -0.5, ctrl_cateories_.size() - 0.5);
    if(histogram_ctrl_)
    {
      for(std::size_t ctrl_idx = 0; ctrl_idx < ctrl_cateories_.size(); ++ctrl_idx)
      {
        histogram_ctrl_->GetXaxis()->SetBinLabel(ctrl_idx + 1, ctrl_cateories_.at(ctrl_idx).data());
      }
    }
  }
}

void
EvtHistManager_3l::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  //histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  //histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_3l_ttV_   = book1D(dir, "mvaOutput_3l_ttV",   "mvaOutput_3l_ttV",   40, -1., +1.);
  histogram_mvaOutput_3l_ttbar_ = book1D(dir, "mvaOutput_3l_ttbar", "mvaOutput_3l_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_3l_        = book1D(dir, "mvaDiscr_3l",        "mvaDiscr_3l",         5,  0.5, 5.5);

  histogram_memOutput_isValid_           = book1D(dir, "memOutput_isValid",           "memOutput_isValid",             3,  -1.5, +1.5);
  histogram_memOutput_errorFlag_         = book1D(dir, "memOutput_errorFlag",         "memOutput_errorFlag",           2,  -0.5, +1.5);
  histogram_memOutput_logWeight_ttH_     = book1D(dir, "memOutput_logWeight_ttH",     "memOutput_logWeight_ttH",     100, -20., +20.);
  histogram_memOutput_logWeight_tt_      = book1D(dir, "memOutput_logWeight_tt",      "memOutput_logWeight_tt",      100, -20., +20.);
  histogram_memOutput_LR_                = book1D(dir, "memOutput_LR",                "memOutput_LR",                 40,   0.,   1.);
  histogram_mem_logCPUTime_              = book1D(dir, "mem_logCPUTime",              "mem_logCPUTime",              400, -20., +20.);
  histogram_mem_logRealTime_             = book1D(dir, "mem_logRealTime",             "mem_logRealTime",             400, -20., +20.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_3l::fillHistograms(int numElectrons,
                                  int numMuons,
                                  int numHadTaus,
                                  int numJets,
                                  int numBJets_loose,
                                  int numBJets_medium,
                                  const std::string & ctrl_category,
                                  double mvaOutput_3l_ttV,
                                  double mvaOutput_3l_ttbar,
                                  double mvaDiscr_3l,
                                  double mvaOutput_category,   const std::string & category,
                                  double mvaOutput_category_sig_2_rest_2_th_2_withWZ,   const std::string & category_sig_2_rest_2_th_2_withWZ,
                                  double mvaOutput_category_sig_2p5_rest_2_th_2p5_withWZ,   const std::string & category_sig_2p5_rest_2_th_2p5_withWZ,
                                  double mvaOutput_category_sig_2_rest_2p5_th_2_withWZ,   const std::string & category_sig_2_rest_2p5_th_2_withWZ,
				  const MEMOutput_3l * memOutput_3l,
                                  double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  //fillWithOverFlow2d(histogram_numBJets_loose_vs_numJets_,  numJets, numBJets_loose,  evtWeight, evtWeightErr);
  //fillWithOverFlow2d(histogram_numBJets_medium_vs_numJets_, numJets, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_3l_ttV_,   mvaOutput_3l_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_3l_ttbar_, mvaOutput_3l_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_3l_,        mvaDiscr_3l,        evtWeight, evtWeightErr);

  if(! ctrl_cateories_.empty())
  {
    const auto ctrl_it = std::find(ctrl_cateories_.cbegin(), ctrl_cateories_.cend(), ctrl_category);
    if(ctrl_it == ctrl_cateories_.cend())
    {
      throw cmsException(this, __func__, __LINE__) << "Unrecognizable category: " << ctrl_category;
    }
    const int ctrl_idx = std::distance(ctrl_cateories_.cbegin(), ctrl_it);
    fillWithOverFlow(histogram_ctrl_, ctrl_idx, evtWeight, evtWeightErr);
  }

  if(! histograms_by_category_.count(category))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << category << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_[category], mvaOutput_category, evtWeight, evtWeightErr);

  if(! histograms_by_category_TensorFlow_3l_sig_2_rest_2_th_2_withWZ_.count(category_sig_2_rest_2_th_2_withWZ))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << category_sig_2_rest_2_th_2_withWZ << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_TensorFlow_3l_sig_2_rest_2_th_2_withWZ_[category_sig_2_rest_2_th_2_withWZ], mvaOutput_category_sig_2_rest_2_th_2_withWZ, evtWeight, evtWeightErr);

  if(! histograms_by_category_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ_.count(category_sig_2p5_rest_2_th_2p5_withWZ))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << category_sig_2p5_rest_2_th_2p5_withWZ << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ_[category_sig_2p5_rest_2_th_2p5_withWZ], mvaOutput_category_sig_2p5_rest_2_th_2p5_withWZ, evtWeight, evtWeightErr);

  if(! histograms_by_category_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ_.count(category_sig_2_rest_2p5_th_2_withWZ))
  {
    throw cmsException(this, __func__, __LINE__) << "Histogram of the name '" << category_sig_2_rest_2p5_th_2_withWZ << "' was never booked";
  }
  fillWithOverFlow(histograms_by_category_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ_[category_sig_2_rest_2p5_th_2_withWZ], mvaOutput_category_sig_2_rest_2p5_th_2_withWZ, evtWeight, evtWeightErr);

  if(memOutput_3l)
  {
    fillWithOverFlow(histogram_memOutput_isValid_, memOutput_3l->isValid(), evtWeight, evtWeightErr);

    if(memOutput_3l->isValid())
    {
      fillWithOverFlow(histogram_memOutput_errorFlag_, memOutput_3l->errorFlag(), evtWeight, evtWeightErr);

      if(memOutput_3l->errorFlag() == 0)
      {
        fillWithOverFlow(histogram_memOutput_logWeight_ttH_,     getLogWeight(memOutput_3l->weight_ttH()), evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_memOutput_logWeight_tt_,      getLogWeight(memOutput_3l->weight_tt()), evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_memOutput_LR_,                memOutput_3l->LR(), evtWeight, evtWeightErr);

        fillWithOverFlow(histogram_mem_logCPUTime_,  std::log(std::max(1.e-21f, memOutput_3l->cpuTime())),  evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_mem_logRealTime_, std::log(std::max(1.e-21f, memOutput_3l->realTime())), evtWeight, evtWeightErr);
      }
    }
  }
  else
  {
    fillWithOverFlow(histogram_memOutput_isValid_, -1, evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
