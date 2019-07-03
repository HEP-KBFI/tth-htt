#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h"

#include <TMath.h> // TMath::Pi()

JetHistManagerHTTv2::JetHistManagerHTTv2(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
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
    throw cmsException(__func__) << "Invalid Configuration parameter 'option' = " << option_string << " !!";
  }
  const std::vector<std::string> sysOpts_central = {
    "pt",
    "eta",
    "phi",
    "mass",
    "tau32",
    "fRec",
    "deltaRopt",
    "maxSubjetBtagCSV",
    "tau21",
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
}

void
JetHistManagerHTTv2::bookHistograms(TFileDirectory & dir)
{
  histogram_pt_               = book1D(dir, "pt",               "pt",              100,   0.,  1000.);
  histogram_eta_              = book1D(dir, "eta",              "eta",              46,  -2.3,   +2.3);
  histogram_phi_              = book1D(dir, "phi",              "phi",              36, -TMath::Pi(), +TMath::Pi());
  histogram_mass_             = book1D(dir, "mass",             "mass",             40,   0.,     2.);
  histogram_tau32_            = book1D(dir, "tau32",            "tau32",            40,   0.2,    1.); 

  if ( option_ == kOption_allHistograms ) {
    histogram_fRec_             = book1D(dir, "fRec",             "fRec",             50,   0.,     0.5);
    histogram_deltaRopt_        = book1D(dir, "deltaRopt",        "deltaRopt",        36,  -0.8,    1.);
    histogram_maxSubjetBtagCSV_ = book1D(dir, "maxSubjetBtagCSV", "maxSubjetBtagCSV", 40,   0.,     1.);
    histogram_tau21_            = book1D(dir, "tau21",            "tau21",            40,   0.2,    1.); 
  }
}

void
JetHistManagerHTTv2::fillHistograms(const RecoJetHTTv2 & jet,
                                    double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,          jet.pt(),              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,         jet.eta(),             evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,         jet.phi(),             evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mass_,        jet.mass(),            evtWeight, evtWeightErr);
  if(jet.tau2() > 0.)
  {
    fillWithOverFlow(histogram_tau32_,     jet.tau3()/jet.tau2(), evtWeight, evtWeightErr);
  }

  if(option_ == kOption_allHistograms)
  {
    fillWithOverFlow(histogram_fRec_,      jet.fRec(),            evtWeight, evtWeightErr);

    const double deltaRopt = jet.Ropt() - jet.RoptCalc();
    fillWithOverFlow(histogram_deltaRopt_, deltaRopt,             evtWeight, evtWeightErr);

    double maxSubjetBtagCSV = -1.;
    if(jet.subJet1() && jet.subJet1()->BtagCSV() > maxSubjetBtagCSV) maxSubjetBtagCSV = jet.subJet1()->BtagCSV();
    if(jet.subJet2() && jet.subJet2()->BtagCSV() > maxSubjetBtagCSV) maxSubjetBtagCSV = jet.subJet2()->BtagCSV();
    if(jet.subJet3() && jet.subJet3()->BtagCSV() > maxSubjetBtagCSV) maxSubjetBtagCSV = jet.subJet3()->BtagCSV();
    fillWithOverFlow(histogram_maxSubjetBtagCSV_, maxSubjetBtagCSV, evtWeight, evtWeightErr);

    if(jet.tau1() > 0.)
    {
      fillWithOverFlow(histogram_tau21_,   jet.tau2()/jet.tau1(), evtWeight, evtWeightErr);
    }
  }
}

void
JetHistManagerHTTv2::fillHistograms(const std::vector<const RecoJetHTTv2 *> & jet_ptrs,
                                    double evtWeight)
{
  const int numJets = jet_ptrs.size();
  for(int idxJet = 0; idxJet < numJets; ++idxJet)
  {
    const RecoJetHTTv2 * jet = jet_ptrs[idxJet];
    if(idx_ >= 0 && idxJet != idx_)
    {
      continue;
    }
    fillHistograms(*jet, evtWeight);
  }
}
