#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_4l.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_4l::EvtHistManager_4l(const edm::ParameterSet & cfg)
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
    "massL"
  };
  const std::vector<std::string> sysOpts_all = {
    "EventCounter",
    "control",
    "mva_4l"
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
EvtHistManager_4l::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_4l::setCRcategories(TFileDirectory & dir,
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
EvtHistManager_4l::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
  histogram_massL_ = book1D(dir, "massL", "massL", 8, 10., 100.);
  Float_t binsx[3] = { 0.0, 0.31, 1.0 };
  histogram_mva_4l_ = book1D(dir, "mva_4l", "mva_4l", 2, binsx);
}

void
EvtHistManager_4l::fillHistograms(int numElectrons,
                                  int numMuons,
                                  int numJets,
                                  int numBJets_loose,
                                  int numBJets_medium,
                                  double massL,
                                  double mva_4l,
                                  const std::string & ctrl_category,
                                  double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_massL_, massL, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mva_4l_, mva_4l, evtWeight, evtWeightErr);

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

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
