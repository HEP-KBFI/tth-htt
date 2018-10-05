#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerAK8.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK8.h"

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <TMath.h> // TMath::Pi()

JetHistManagerAK8::JetHistManagerAK8(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , idx_(cfg.getParameter<int>("idx"))
{}

void
JetHistManagerAK8::bookHistograms(TFileDirectory & dir)
{
  histogram_pt_              = book1D(dir, "pt",              "pt",              50,  0.,  500.);
  histogram_eta_             = book1D(dir, "eta",             "eta",             60, -3.0,  +3.0);
  histogram_phi_             = book1D(dir, "phi",             "phi",             36, -TMath::Pi(), +TMath::Pi());
  histogram_mass_            = book1D(dir, "mass",            "mass",            40,  0.,    2.);
  histogram_msoftdrop_       = book1D(dir, "msoftdrop",       "msoftdrop",       40,  0.,  200.);
  histogram_tau21_           = book1D(dir, "tau21",           "tau21",           40,  0.2,   1.);
  histogram_tau32_           = book1D(dir, "tau32",           "tau32",           40,  0.2,   1.);
  histogram_subjet1_pt_      = book1D(dir, "subjet1_pt",      "subjet1_pt",      50,  0.,  500.);
  histogram_subjet1_eta_     = book1D(dir, "subjet1_eta",     "subjet1_eta",     60, -3.0,  +3.0);
  histogram_subjet1_BtagCSV_ = book1D(dir, "subjet1_BtagCSV", "subjet1_BtagCSV", 40,  0.,    1.);
  histogram_subjet2_pt_      = book1D(dir, "subjet2_pt",      "subjet2_pt",      50,  0.,  500.);
  histogram_subjet2_eta_     = book1D(dir, "subjet2_eta",     "subjet2_eta",     60, -3.0,  +3.0);
  histogram_subjet2_BtagCSV_ = book1D(dir, "subjet2_BtagCSV", "subjet2_BtagCSV", 40,  0.,    1.);
  histogram_dR_subjets_      = book1D(dir, "dR_subjets",      "dR_subjets",      40,  0.,    2.);
}

void
JetHistManagerAK8::fillHistograms(const RecoJetAK8 & jet,
				    double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_pt_,                jet.pt(),           evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,               jet.eta(),          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,               jet.phi(),          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mass_,              jet.mass(),         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_msoftdrop_,         jet.msoftdrop(),    evtWeight, evtWeightErr);
  if ( jet.tau1() > 0. ) {
    fillWithOverFlow(histogram_tau21_, jet.tau2()/jet.tau1(), evtWeight, evtWeightErr);
  }
  if ( jet.tau2() > 0. ) {
    fillWithOverFlow(histogram_tau32_, jet.tau3()/jet.tau2(), evtWeight, evtWeightErr);
  }
  const RecoSubjetAK8* subJet1 = jet.subJet1();
  if ( subJet1 ) {
    fillWithOverFlow(histogram_subjet1_pt_,      subJet1->pt(),      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_subjet1_eta_,     subJet1->eta(),     evtWeight, evtWeightErr); 
    fillWithOverFlow(histogram_subjet1_BtagCSV_, subJet1->BtagCSV(), evtWeight, evtWeightErr);
  }
  const RecoSubjetAK8* subJet2 = jet.subJet2();
  if ( subJet2 ) {
    fillWithOverFlow(histogram_subjet2_pt_,      subJet2->pt(),      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_subjet2_eta_,     subJet2->eta(),     evtWeight, evtWeightErr); 
    fillWithOverFlow(histogram_subjet2_BtagCSV_, subJet2->BtagCSV(), evtWeight, evtWeightErr);
  }
  if ( subJet1 && subJet2 ) {
    fillWithOverFlow(histogram_dR_subjets_, deltaR(subJet1->p4(), subJet2->p4()), evtWeight, evtWeightErr);
  }
}

void
JetHistManagerAK8::fillHistograms(const std::vector<const RecoJetAK8 *> & jet_ptrs,
				   double evtWeight)
{
  const int numJets = jet_ptrs.size();
  for(int idxJet = 0; idxJet < numJets; ++idxJet)
  {
    const RecoJetAK8 * jet = jet_ptrs[idxJet];
    if(idx_ >= 0 && idxJet != idx_)
    {
      continue;
    }
    fillHistograms(*jet, evtWeight);
  }
}
