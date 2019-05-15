#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_2lss::EvtHistManager_2lss(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
{
  central_or_shiftOptions_["numElectrons"] = { "central" };
  central_or_shiftOptions_["numMuons"] = { "central" };
  central_or_shiftOptions_["numHadTaus"] = { "central" };
  central_or_shiftOptions_["numJets"] = { "central" };
  central_or_shiftOptions_["numBJets_loose"] = { "central" };
  central_or_shiftOptions_["numBJets_medium"] = { "central" };
  central_or_shiftOptions_["numBJets_loose_vs_numJets"] = { "central" };
  central_or_shiftOptions_["numBJets_medium_vs_numJets"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2lss_ttV"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2lss_ttbar"] = { "central" };
  central_or_shiftOptions_["mvaDiscr_2lss"] = { "*" };
  central_or_shiftOptions_["mvaOutput_Hj_tagger"] = { "central" };
  central_or_shiftOptions_["output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4"] = { "central" };
  central_or_shiftOptions_["EventCounter"] = { "*" };
}

const TH1 *
EvtHistManager_2lss::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void EvtHistManager_2lss::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  //histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  //histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_2lss_ttV_   = book1D(dir, "mvaOutput_2lss_ttV",   "mvaOutput_2lss_ttV",   40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_ = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2lss_        = book1D(dir, "mvaDiscr_2lss",        "mvaDiscr_2lss",         7,  0.5, 7.5);

  histogram_mvaOutput_Hj_tagger_  = book1D(dir, "mvaOutput_Hj_tagger",  "mvaOutput_Hj_tagger",  20, -1., +1.);
  histogram_output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ = book1D(dir, "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4", "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4", 10, 0., +1.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_2lss::fillHistograms(int numElectrons,
                                    int numMuons,
                                    int numHadTaus,
                                    int numJets,
                                    int numBJets_loose,
                                    int numBJets_medium,
                                    double evtWeight,
                                    double mvaOutput_2lss_ttV,
                                    double mvaOutput_2lss_ttbar,
                                    double mvaDiscr_2lss,
                                    double mvaOutput_Hj_tagger,
                                    double output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4)
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

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_,   mvaOutput_2lss_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_,        mvaDiscr_2lss,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_Hj_tagger_,  mvaOutput_Hj_tagger,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_, output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
