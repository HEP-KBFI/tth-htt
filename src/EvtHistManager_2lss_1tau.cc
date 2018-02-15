#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // getSF_from_TH2()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  const std::string era_string = cfg.getParameter<std::string>("era");
  if(era_string == "2017" )
  {
    era_ = kEra_2017;
  }
  else
  {
    throw cmsException(this)
      << "Invalid Configuration parameter 'era' = " << era_string;
  }
}

const TH1 *
EvtHistManager_2lss_1tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void EvtHistManager_2lss_1tau::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_2lss_ttV_   = book1D(dir, "mvaOutput_2lss_ttV",   "mvaOutput_2lss_ttV",   40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_ = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  switch(era_)
  {
    case kEra_2017: histogram_mvaDiscr_2lss_ = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 7, 0.5, 7.5); break;
    default:        assert(0);
  }

  histogram_mvaOutput_2lss_1tau_ttV_        = book1D(dir, "mvaOutput_2lss_1tau_ttV",        "mvaOutput_2lss_1tau_ttV",       600,  -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_      = book1D(dir, "mvaOutput_2lss_1tau_ttbar",      "mvaOutput_2lss_1tau_ttbar",     600,  -1., +1.);
  histogram_mvaDiscr_2lss_1tau_             = book1D(dir, "mvaDiscr_2lss_1tau",             "mvaDiscr_2lss_1tau",              7,   0.5, 7.5);
  histogram_mvaOutput_2lss_1tau_ttV_wMEM_   = book1D(dir, "mvaOutput_2lss_1tau_ttV_wMEM",   "mvaOutput_2lss_1tau_ttV_wMEM",   600, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_wMEM_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar_wMEM", "mvaOutput_2lss_1tau_ttbar_wMEM", 600, -1., +1.);
  histogram_mvaDiscr_2lss_1tau_wMEM_        = book1D(dir, "mvaDiscr_2lss_1tau_wMEM",        "mvaDiscr_2lss_1tau_wMEM",          7, 0.5, 7.5);

  histogram_mvaOutput_Hj_tagger_  = book1D(dir, "mvaOutput_Hj_tagger",  "mvaOutput_Hj_tagger",  20, -1., +1.);
  histogram_mvaOutput_Hjj_tagger_ = book1D(dir, "mvaOutput_Hjj_tagger", "mvaOutput_Hjj_tagger", 20, -1., +1.);

  histogram_mTauTauVis_   = book1D(dir, "mTauTauVis",   "mTauTauVis",    20, 0., 200.);
  histogram_mTauTauVis1_  = book1D(dir, "mTauTauVis1",  "mTauTauVis1",   20, 0., 200.);
  histogram_mTauTauVis2_  = book1D(dir, "mTauTauVis2",  "mTauTauVis2",   20, 0., 200.);
  histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 600, 0.,   1.);

  histogram_memDiscr_     = book1D(dir, "memDiscr",     "memDiscr",     8,  0.5,  8.5);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_2lss_1tau::fillHistograms(int numElectrons,
                                         int numMuons,
                                         int numHadTaus,
                                         int numJets,
                                         int numBJets_loose,
                                         int numBJets_medium,
                                         double evtWeight,
                                         double mvaOutput_2lss_ttV,
                                         double mvaOutput_2lss_ttbar,
                                         double mvaDiscr_2lss,
                                         double mvaOutput_2lss_1tau_ttV,
                                         double mvaOutput_2lss_1tau_ttbar,
                                         double mvaDiscr_2lss_1tau,
                                         double mvaOutput_2lss_1tau_ttV_wMEM,
                                         double mvaOutput_2lss_1tau_ttbar_wMEM,
                                         double mvaDiscr_2lss_1tau_wMEM,
                                         double mvaOutput_Hj_tagger,
                                         double mvaOutput_Hjj_tagger,
                                         double mTauTauVis1,
                                         double mTauTauVis2,
                                         double memOutput_LR,
                                         double memDiscr)
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

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_,   mvaOutput_2lss_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_,        mvaDiscr_2lss,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttV_,        mvaOutput_2lss_1tau_ttV,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_,      mvaOutput_2lss_1tau_ttbar,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_1tau_,             mvaDiscr_2lss_1tau,             evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttV_wMEM_,   mvaOutput_2lss_1tau_ttV_wMEM,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_wMEM_, mvaOutput_2lss_1tau_ttbar_wMEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_1tau_wMEM_,        mvaDiscr_2lss_1tau_wMEM,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_Hj_tagger_,  mvaOutput_Hj_tagger,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_Hjj_tagger_, mvaOutput_Hjj_tagger, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_,   mTauTauVis1,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis1_,  mTauTauVis1,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis2_,  mTauTauVis2,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_memOutput_LR_, memOutput_LR, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_memDiscr_,     memDiscr ,    evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}

void
EvtHistManager_2lss_1tau::integralHistograms() const
{
  std::cout << "Integral of histogram " << histogram_mTauTauVis_->Integral() << '\n';
}
