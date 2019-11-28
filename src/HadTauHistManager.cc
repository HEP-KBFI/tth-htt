#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // TauID::

#include <TMath.h> // TMath::Pi()

HadTauHistManager::HadTauHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
  , option_(kOption_undefined)
  , idx_(cfg.getParameter<int>("idx"))
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
    "pt",
    "eta",
    "phi",
    "abs_genPdgId",
    "decayMode",
    "mass",
    "charge",
    "dz",
    "dxy",
    "decayModeFinding",
    "id_mva",
    "antiElectron",
    "antiMuon",
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
}

void HadTauHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_pt_                 = book1D(dir, "pt",               "pt",              40,  0.,  200.);
  histogram_eta_                = book1D(dir, "eta",              "eta",             46, -2.3,  +2.3);
  histogram_phi_                = book1D(dir, "phi",              "phi",             36, -TMath::Pi(), +TMath::Pi());
  histogram_abs_genPdgId_       = book1D(dir, "abs_genPdgId",     "abs_genPdgId",    22, -0.5, +21.5);

  if ( option_ == kOption_allHistograms ) {
    const int & anti_e_bins = TauID_levels.at(TauID::DeepTau2017v2VSe);
    const int & anti_mu_bins = TauID_levels.at(TauID::DeepTau2017v2VSmu);
    histogram_decayMode_        = book1D(dir, "decayMode",        "decayMode",       12, -0.5, +11.5);
    histogram_mass_             = book1D(dir, "mass",             "mass",            40,  0.,    2.);
    histogram_charge_           = book1D(dir, "charge",           "charge",           3, -1.5,  +1.5);
    histogram_dz_               = book1D(dir, "dz",               "dz",              40, -0.2,  +0.2);
    histogram_dxy_              = book1D(dir, "dxy",              "dxy",             40, -0.1,  +0.1);
    histogram_decayModeFinding_ = book1D(dir, "decayModeFinding", "decayModeFinding", 2, -0.5, +1.5);
    histogram_id_mva_           = book1D(dir, "id_mva",          "id_mva",            9, -0.5, +8.5);
    histogram_antiElectron_     = book1D(dir, "antiElectron",     "antiElectron",     anti_e_bins,  -0.5, anti_e_bins  - 0.5);
    histogram_antiMuon_         = book1D(dir, "antiMuon",         "antiMuon",         anti_mu_bins, -0.5, anti_mu_bins - 0.5);
  }
}

void
HadTauHistManager::fillHistograms(const RecoHadTau & hadTau,
                                  double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,                 hadTau.pt(),               evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,                hadTau.eta(),              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,                hadTau.phi(),              evtWeight, evtWeightErr);
  
  int abs_genPdgId = 0;
  if      ( hadTau.genHadTau() ) abs_genPdgId = 15;                                    // generator level match to hadronic tau decay
  else if ( hadTau.genLepton() ) abs_genPdgId = std::abs(hadTau.genLepton()->pdgId()); // generator level match to electron or muon
  else if ( hadTau.genJet()    ) abs_genPdgId = 21;                                    // generator level match to jet; fill histogram with pdgId of gluon
  else                           abs_genPdgId =  0;                                    // no match to any generator level particle
                                                                                       // (reconstructed tauh most likely due to pileup)
  fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);

  if ( option_ == kOption_allHistograms ) {
    fillWithOverFlow(histogram_decayMode_,        hadTau.decayMode(),                      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mass_,             hadTau.mass(),                           evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_charge_,           hadTau.charge(),                         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_dz_,               hadTau.dz(),                             evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_dxy_,              hadTau.dxy(),                            evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_decayModeFinding_, hadTau.idDecayMode(),                    evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_id_mva_,           hadTau.id_mva(),                         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_antiElectron_,     hadTau.id_mva(TauID::DeepTau2017v2VSe),  evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_antiMuon_,         hadTau.id_mva(TauID::DeepTau2017v2VSmu), evtWeight, evtWeightErr);
  }
}

void
HadTauHistManager::fillHistograms(const std::vector<const RecoHadTau *> & hadTau_ptrs,
                                  double evtWeight)
{
  const int numHadTaus = hadTau_ptrs.size();
  for(int idxHadTau = 0; idxHadTau < numHadTaus; ++idxHadTau)
  {
    const RecoHadTau * hadTau = hadTau_ptrs[idxHadTau];
    if(idx_ >= 0 && idxHadTau != idx_)
    {
      continue;
    }
    fillHistograms(*hadTau, evtWeight);
  }
}
