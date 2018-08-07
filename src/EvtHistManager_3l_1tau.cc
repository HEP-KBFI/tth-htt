#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_3l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_3l_1tau::EvtHistManager_3l_1tau(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
{}

const TH1 *
EvtHistManager_3l_1tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_3l_1tau::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_3l_ttV_   = book1D(dir, "mvaOutput_3l_ttV",   "mvaOutput_3l_ttV",   40, -1., +1.);
  histogram_mvaOutput_3l_ttbar_ = book1D(dir, "mvaOutput_3l_ttbar", "mvaOutput_3l_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_3l_        = book1D(dir, "mvaDiscr_3l",        "mvaDiscr_3l",         5,  0.5, 5.5);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 20, 0., 200.);

  histogram_memOutput_isValid_           = book1D(dir, "memOutput_isValid",           "memOutput_isValid",             3,  -1.5, +1.5);
  histogram_memOutput_errorFlag_         = book1D(dir, "memOutput_errorFlag",         "memOutput_errorFlag",           2,  -0.5, +1.5);
  histogram_memOutput_logWeight_ttH_     = book1D(dir, "memOutput_logWeight_ttH",     "memOutput_logWeight_ttH",     100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_     = book1D(dir, "memOutput_logWeight_ttZ",     "memOutput_logWeight_ttZ",     100, -20., +20.);
  histogram_memOutput_logWeight_ttH_hww_ = book1D(dir, "memOutput_logWeight_ttH_hww", "memOutput_logWeight_ttH_hww", 100, -20., +20.);
  histogram_memOutput_LR_                = book1D(dir, "memOutput_LR",                "memOutput_LR",                 40,   0.,   1.);
  histogram_mem_logCPUTime_              = book1D(dir, "mem_logCPUTime",              "mem_logCPUTime",              400, -20., +20.);
  histogram_mem_logRealTime_             = book1D(dir, "mem_logRealTime",             "mem_logRealTime",             400, -20., +20.);

  histogram_mvaOutput_plainKin_tt_            = book1D(dir, "mvaOutput_plainKin_tt",            "mvaOutput_plainKin_tt",            100, 0., 1.);
  histogram_mvaOutput_plainKin_ttV_           = book1D(dir, "mvaOutput_plainKin_ttV",           "mvaOutput_plainKin_ttV",           100, 0., 1.);
  histogram_mvaOutput_plainKin_1B_M_          = book1D(dir, "mvaOutput_plainKin_1B_M",          "mvaOutput_plainKin_1B_M",          100, 0., 1.);
  histogram_mvaOutput_plainKin_SUM_M_         = book1D(dir, "mvaOutput_plainKin_SUM_M",         "mvaOutput_plainKin_SUM_M",         100, 0., 1.);
  histogram_mvaOutput_plainKin_SUM_M_noRebin_ = book1D(dir, "mvaOutput_plainKin_SUM_M_noRebin", "mvaOutput_plainKin_SUM_M_noRebin", 100, 0., 1.);

  Float_t binsx[7] = { 0.0, 0.28, 0.35, 0.40, 0.47, 0.53, 1.0 };
  histogram_final_ = book1D(dir, "mvaOutput_final",  "mvaOutput_final",  6, binsx);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_3l_1tau::fillHistograms(int numElectrons,
                                       int numMuons,
                                       int numHadTaus,
                                       int numJets,
                                       int numBJets_loose,
                                       int numBJets_medium,
                                       double mvaOutput_3l_ttV,
                                       double mvaOutput_3l_ttbar,
                                       double mvaDiscr_3l,
                                       double mTauTauVis1,
                                       double mTauTauVis2,
                                       const MEMOutput_3l_1tau * memOutput_3l_1tau,
                                       double evtWeight,
                                       double mvaOutput_plainKin_tt,
                                       double mvaOutput_plainKin_ttV,
                                       double mvaOutput_plainKin_SUM_M,
                                       double mvaOutput_plainKin_1B_M)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow2d(histogram_numBJets_loose_vs_numJets_,  numJets, numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow2d(histogram_numBJets_medium_vs_numJets_, numJets, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_3l_ttV_,   mvaOutput_3l_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_3l_ttbar_, mvaOutput_3l_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_3l_,        mvaDiscr_3l,        evtWeight, evtWeightErr);

  const double mTauTauVisSF = mTauTauVis1 > 0. && mTauTauVis2 > 0. ? 0.5 : 1.;
  if(mTauTauVis1 > 0.)
  {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis1, mTauTauVisSF * evtWeight, mTauTauVisSF * evtWeightErr);
  }
  if(mTauTauVis2 > 0.)
  {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis2, mTauTauVisSF * evtWeight, mTauTauVisSF * evtWeightErr);
  }

  if(memOutput_3l_1tau)
  {
    fillWithOverFlow(histogram_memOutput_isValid_, memOutput_3l_1tau->isValid(), evtWeight, evtWeightErr);

    if(memOutput_3l_1tau->isValid())
    {
      fillWithOverFlow(histogram_memOutput_errorFlag_, memOutput_3l_1tau->errorFlag(), evtWeight, evtWeightErr);

      if(memOutput_3l_1tau->errorFlag() == 0)
      {
        fillWithOverFlow(histogram_memOutput_logWeight_ttH_,     getLogWeight(memOutput_3l_1tau->weight_ttH()), evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_memOutput_logWeight_ttZ_,     getLogWeight(memOutput_3l_1tau->weight_ttZ()), evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_memOutput_logWeight_ttH_hww_, getLogWeight(memOutput_3l_1tau->weight_ttH_hww()), evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_memOutput_LR_,                memOutput_3l_1tau->LR(), evtWeight, evtWeightErr);

        fillWithOverFlow(histogram_mem_logCPUTime_,  std::log(std::max(1.e-21f, memOutput_3l_1tau->cpuTime())),  evtWeight, evtWeightErr);
        fillWithOverFlow(histogram_mem_logRealTime_, std::log(std::max(1.e-21f, memOutput_3l_1tau->realTime())), evtWeight, evtWeightErr);
      }
    }
  }
  else
  {
    fillWithOverFlow(histogram_memOutput_isValid_, -1, evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_mvaOutput_plainKin_tt_,            mvaOutput_plainKin_tt,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_plainKin_ttV_,           mvaOutput_plainKin_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_plainKin_1B_M_,          mvaOutput_plainKin_1B_M,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_plainKin_SUM_M_,         mvaOutput_plainKin_SUM_M, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_plainKin_SUM_M_noRebin_, mvaOutput_plainKin_SUM_M, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_final_,                            mvaOutput_plainKin_SUM_M, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
