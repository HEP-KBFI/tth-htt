#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

std::vector<std::string> categories_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4 = {
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_ee_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_ee_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_em_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_em_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_mm_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH_mm_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_ee_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_ee_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_em_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_em_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_mm_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW_mm_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_rest_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_rest_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_ee_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_ee_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_em_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_em_bt",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_mm_bl",
  "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_tH_mm_bt"
};

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
    "output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4",
  };
  const std::vector<std::string> sysOpts_all = {
    "mvaDiscr_2lss",
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
EvtHistManager_2lss::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void EvtHistManager_2lss::bookHistograms(
  TFileDirectory & dir
)
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

  histogram_mvaOutput_Hj_tagger_                   = book1D(dir, "mvaOutput_Hj_tagger",                   "mvaOutput_Hj_tagger",                   20, -1., +1.);
  for(const std::string & evt_cat_str: categories_TensorFlow_2lss_ttH_tH_4cat_onlyTHQ_v4)
  {
  histogram_output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_.push_back(book1D(dir, evt_cat_str, evt_cat_str, 100,  0., +1.));
  }
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
                                    double output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4,
                                    std::string category_NN_2lss_ttH_tH_4cat_onlyTHQ_v4
                                  )
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_,   mvaOutput_2lss_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_,        mvaDiscr_2lss,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_Hj_tagger_,                   mvaOutput_Hj_tagger,                   evtWeight, evtWeightErr);

  //std::cout<<" ====================\n";
  for(TH1*  histo: histogram_output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4_)
  {

    if (histo->GetName() == category_NN_2lss_ttH_tH_4cat_onlyTHQ_v4) {
      fillWithOverFlow(histo, output_NN_2lss_ttH_tH_4cat_onlyTHQ_v4, evtWeight, evtWeightErr);
      //std::cout<<" histo->getName() " << histo->GetName() << " category_NN_2lss_ttH_tH_4cat_onlyTHQ_v4 " << category_NN_2lss_ttH_tH_4cat_onlyTHQ_v4 << "\n";
    }
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
