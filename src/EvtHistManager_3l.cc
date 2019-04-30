#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_3l.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_3l::EvtHistManager_3l(const edm::ParameterSet & cfg)
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
  central_or_shiftOptions_["mvaOutput_3l_ttV"] = { "central" };
  central_or_shiftOptions_["mvaOutput_3l_ttbar"] = { "central" };
  central_or_shiftOptions_["mvaDiscr_3l"] = { "*" };
  central_or_shiftOptions_["memOutput_isValid"] = { "central" };
  central_or_shiftOptions_["memOutput_errorFlag"] = { "central" };
  central_or_shiftOptions_["memOutput_logWeight_ttH"] = { "central" };
  central_or_shiftOptions_["memOutput_logWeight_tt"] = { "central" };
  central_or_shiftOptions_["memOutput_LR"] = { "central" };
  central_or_shiftOptions_["mem_logCPUTime"] = { "central" };
  central_or_shiftOptions_["mem_logRealTime"] = { "central" };
  central_or_shiftOptions_["output_NN_3l_ttH_tH_3cat_v8"] = { "central" };
  central_or_shiftOptions_["EventCounter"] = { "*" };
}

const TH1 *
EvtHistManager_3l::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
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
  histogram_output_NN_3l_ttH_tH_3cat_v8_ = book1D(dir, "output_NN_3l_ttH_tH_3cat_v8",             "output_NN_3l_ttH_tH_3cat_v8",             7, 0., 1.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_3l::fillHistograms(int numElectrons,
                                  int numMuons,
                                  int numHadTaus,
                                  int numJets,
                                  int numBJets_loose,
                                  int numBJets_medium,
                                  double mvaOutput_3l_ttV,
                                  double mvaOutput_3l_ttbar,
                                  double mvaDiscr_3l,
                                  double output_NN_3l_ttH_tH_3cat_v8,
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
  fillWithOverFlow(histogram_output_NN_3l_ttH_tH_3cat_v8_,        output_NN_3l_ttH_tH_3cat_v8,        evtWeight, evtWeightErr);

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
