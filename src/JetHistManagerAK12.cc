#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerAK12.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK12.h"

#include <TMath.h> // TMath::Pi()

JetHistManagerAK12::JetHistManagerAK12(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , idx_(cfg.getParameter<int>("idx"))
{
  std::string option_string = cfg.getParameter<std::string>("option");
  if ( option_string == "allHistograms" ) {
    option_ = kOption_allHistograms;
  } else if ( option_string == "minimalHistograms" ) {
    option_ = kOption_minimalHistograms;
  } else {
    throw cmsException(__func__) << "Invalid Configuration parameter 'option' = " << option_string << " !!";
  }

  central_or_shiftOptions_["pt"] = { "central" };
  central_or_shiftOptions_["eta"] = { "central" };
  central_or_shiftOptions_["phi"] = { "central" };
  central_or_shiftOptions_["msoftdrop"] = { "central" };
  central_or_shiftOptions_["tau21"] = { "central" };

  central_or_shiftOptions_["mass"] = { "central" };
  central_or_shiftOptions_["charge"] = { "central" };
  central_or_shiftOptions_["pullMag"] = { "central" };
  central_or_shiftOptions_["QjetVolatility"] = { "central" };
  central_or_shiftOptions_["tau32"] = { "central" };
}

void
JetHistManagerAK12::bookHistograms(TFileDirectory & dir)
{
  histogram_pt_               = book1D(dir, "pt",             "pt",              50,  0.,  500.);
  histogram_eta_              = book1D(dir, "eta",            "eta",             46, -2.3,  +2.3);
  histogram_phi_              = book1D(dir, "phi",            "phi",             36, -TMath::Pi(), +TMath::Pi());
  histogram_msoftdrop_        = book1D(dir, "msoftdrop",      "msoftdrop",       40,  0.,  200.);
  histogram_tau21_            = book1D(dir, "tau21",          "tau21",           40,  0.2,   1.); 

  if ( option_ == kOption_allHistograms ) {
    histogram_mass_           = book1D(dir, "mass",           "mass",            40,  0.,    2.);
    histogram_charge_         = book1D(dir, "charge",         "charge",          40, -1.,   +1.);
    histogram_pullMag_        = book1D(dir, "pullMag",        "pullMag",        100,  0.,    0.1);
    histogram_QjetVolatility_ = book1D(dir, "QjetVolatility", "QjetVolatility", 100,  0.,   10.);
    histogram_tau32_          = book1D(dir, "tau32",          "tau32",           40,  0.2,   1.); 
  }
}

void
JetHistManagerAK12::fillHistograms(const RecoJetAK12 & jet,
				    double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,               jet.pt(),              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,              jet.eta(),             evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,              jet.phi(),             evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_msoftdrop_,        jet.msoftdrop(),       evtWeight, evtWeightErr);
  if ( jet.tau1() > 0. ) {
    fillWithOverFlow(histogram_tau21_,          jet.tau2()/jet.tau1(), evtWeight, evtWeightErr);
  }

  if ( option_ == kOption_allHistograms ) {
    fillWithOverFlow(histogram_mass_,           jet.mass(),            evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_charge_,         jet.charge(),          evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_pullMag_,        jet.pullMag(),         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_QjetVolatility_, jet.QjetVolatility(),  evtWeight, evtWeightErr);    
    if ( jet.tau2() > 0. ) {
      fillWithOverFlow(histogram_tau32_,        jet.tau3()/jet.tau2(), evtWeight, evtWeightErr);
    }
  }
}

void
JetHistManagerAK12::fillHistograms(const std::vector<const RecoJetAK12 *> & jet_ptrs,
				   double evtWeight)
{
  const int numJets = jet_ptrs.size();
  for(int idxJet = 0; idxJet < numJets; ++idxJet)
  {
    const RecoJetAK12 * jet = jet_ptrs[idxJet];
    if(idx_ >= 0 && idxJet != idx_)
    {
      continue;
    }
    fillHistograms(*jet, evtWeight);
  }
}
