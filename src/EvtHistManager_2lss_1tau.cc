#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // getSF_from_TH2()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
  , nbinsTarget_{{5, 6, 7, 8, 9, 10}}
  , nbinsStart_{{15, 20}}
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

  const std::array<std::string, 4> label{{ "oldVarA", "HTT", "HTTMEM", "noHTT" }};
  for(Int_t nbinsStartN: nbinsStart_)
  {
    for(Int_t nbinsTargetN: nbinsTarget_)
    {
      for(int histIdx = 0 ; histIdx < 4 ; ++histIdx)
      {
        const char * hist_name = Form("%s_from%i_to_%i", label.at(histIdx).c_str(), nbinsStartN, nbinsTargetN);
        TH1 * hist= book1D(dir, hist_name, hist_name, nbinsTargetN, -0.5, nbinsTargetN + 0.5);
        switch(histIdx)
        {
          case 0:  hist_oldVarA_2D_.push_back(hist); break;
          case 1:  hist_HTT_2D_.push_back(hist);     break;
          case 2:  hist_HTTMEM_2D_.push_back(hist);  break;
          case 3:  hist_noHTT_2D_.push_back(hist);   break;
          default: assert(0);
        }
      }
    }
  }

  histogram_memDiscr_     = book1D(dir, "memDiscr",     "memDiscr",     8,  0.5,  8.5);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);

  histogram_mvaOutput_2lss_oldVarA_tt_   = book1D(dir, "mvaOutput_2lss_oldVarA_tt",   "mvaOutput_2lss_oldVarA_tt",   600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_ttV_  = book1D(dir, "mvaOutput_2lss_oldVarA_ttV",  "mvaOutput_2lss_oldVarA_ttV",  600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_tt_       = book1D(dir, "mvaOutput_2lss_HTT_tt",       "mvaOutput_2lss_HTT_tt",       600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_tt_     = book1D(dir, "mvaOutput_2lss_noHTT_tt",     "mvaOutput_2lss_noHTT_tt",     600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_ttV_    = book1D(dir, "mvaOutput_2lss_noHTT_ttV",    "mvaOutput_2lss_noHTT_ttV",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTTMEM_tt_    = book1D(dir, "mvaOutput_2lss_HTTMEM_tt",    "mvaOutput_2lss_HTTMEM_tt",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTTMEM_ttV_   = book1D(dir, "mvaOutput_2lss_HTTMEM_ttV",   "mvaOutput_2lss_HTTMEM_ttV",   600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_LepID_tt_ = book1D(dir, "mvaOutput_2lss_HTT_LepID_tt", "mvaOutput_2lss_HTT_LepID_tt", 600, 0., +1.);

  histogram_mvaOutput_2lss_HTTMEM_1B_    = book1D(dir, "mvaOutput_2lss_HTTMEM_1B",    "mvaOutput_2lss_HTTMEM_1B",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_1B_       = book1D(dir, "mvaOutput_2lss_HTT_1B",       "mvaOutput_2lss_HTT_1B",       600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_1B_     = book1D(dir, "mvaOutput_2lss_noHTT_1B",     "mvaOutput_2lss_noHTT_1B",     600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_1B_   = book1D(dir, "mvaOutput_2lss_oldVarA_1B",   "mvaOutput_2lss_oldVarA_1B",   600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_2MEM_ = book1D(dir, "mvaOutput_2lss_oldVarA_2MEM", "mvaOutput_2lss_oldVarA_2MEM", 600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_2MEM_   = book1D(dir, "mvaOutput_2lss_noHTT_2MEM",   "mvaOutput_2lss_noHTT_2MEM",   600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_2HTT_   = book1D(dir, "mvaOutput_2lss_noHTT_2HTT",   "mvaOutput_2lss_noHTT_2HTT",   600, 0., +1.);
}

void
EvtHistManager_2lss_1tau::fillHistograms(int numElectrons,
                                         int numMuons,
                                         int numHadTaus,
                                         int numJets,
                                         int numBJets_loose,
                                         int numBJets_medium,
                                         const std::vector<TH2*> & oldVarA,
                                         const std::vector<TH2*> & HTT,
                                         const std::vector<TH2*> & noHTT,
                                         const std::vector<TH2*> & HTTMEM,
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
                                         double memDiscr,
                                         // XGB training 1D
                                         double mvaOutput_2lss_oldVarA_tt,
                                         double mvaOutput_2lss_oldVarA_ttV,
                                         double mvaOutput_2lss_noHTT_tt,
                                         double mvaOutput_2lss_noHTT_ttV,
                                         double mvaOutput_2lss_HTT_tt,
                                         double mvaOutput_2lss_HTTMEM_tt,
                                         double mvaOutput_2lss_HTTMEM_ttV,
                                         double mvaOutput_2lss_HTT_LepID_tt,
                                         // XGB training, joint
                                         double mvaOutput_2lss_HTTMEM_1B,
                                         double mvaOutput_2lss_HTT_1B,
                                         double mvaOutput_2lss_noHTT_1B,
                                         double mvaOutput_2lss_oldVarA_1B,
                                         double mvaOutput_2lss_oldVarA_2MEM,
                                         double mvaOutput_2lss_noHTT_2MEM,
                                         double mvaOutput_2lss_noHTT_2HTT)
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

  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_tt_,   mvaOutput_2lss_oldVarA_tt,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_ttV_,  mvaOutput_2lss_oldVarA_ttV,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_tt_,       mvaOutput_2lss_HTT_tt,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_tt_,     mvaOutput_2lss_noHTT_tt,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_ttV_,    mvaOutput_2lss_noHTT_ttV,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_LepID_tt_, mvaOutput_2lss_HTT_LepID_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_tt_,    mvaOutput_2lss_HTTMEM_tt,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_ttV_,   mvaOutput_2lss_HTTMEM_ttV,   evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_1B_,    mvaOutput_2lss_HTTMEM_1B,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_1B_,       mvaOutput_2lss_HTT_1B,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_1B_,     mvaOutput_2lss_noHTT_1B,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_1B_,   mvaOutput_2lss_oldVarA_1B,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_2MEM_, mvaOutput_2lss_oldVarA_2MEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_2MEM_,   mvaOutput_2lss_noHTT_2MEM,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_2HTT_,   mvaOutput_2lss_noHTT_2HTT,   evtWeight, evtWeightErr);

  // DO 2D
  const int nofHist2 = nbinsStart_.size() * nbinsTarget_.size();
  for(int countHist2 = 0; countHist2 < nofHist2; ++countHist2)
  {
    // in root the bin number starts at 1, while the getSF_from_TH2 starts from zero
    const double hist_oldVarA_2D_value = getSF_from_TH2(oldVarA.at(countHist2),mvaOutput_2lss_oldVarA_tt, mvaOutput_2lss_oldVarA_ttV);
    const double hist_HTT_2D_value     = getSF_from_TH2(HTT.at(countHist2),    mvaOutput_2lss_HTT_tt,     mvaOutput_2lss_noHTT_ttV);
    const double hist_noHTT_2D_value   = getSF_from_TH2(noHTT.at(countHist2),  mvaOutput_2lss_noHTT_tt,   mvaOutput_2lss_noHTT_ttV);
    const double hist_HTTMEM_2D_value  = getSF_from_TH2(HTTMEM.at(countHist2), mvaOutput_2lss_HTTMEM_tt,  mvaOutput_2lss_HTTMEM_ttV);
    fillWithOverFlow(hist_oldVarA_2D_.at(countHist2), hist_oldVarA_2D_value + 1, evtWeight, evtWeightErr);
    fillWithOverFlow(hist_HTT_2D_.at(countHist2),     hist_HTT_2D_value + 1,     evtWeight, evtWeightErr);
    fillWithOverFlow(hist_noHTT_2D_.at(countHist2),   hist_noHTT_2D_value + 1,   evtWeight, evtWeightErr);
    fillWithOverFlow(hist_HTTMEM_2D_.at(countHist2),  hist_HTTMEM_2D_value + 1,  evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}

void
EvtHistManager_2lss_1tau::integralHistograms() const
{
  std::cout << "Integral of histogram " << histogram_mvaOutput_2lss_oldVarA_tt_->Integral() << '\n';
}
