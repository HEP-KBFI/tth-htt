#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

MVAInputVarHistManager::MVAInputVarHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  binningOptions_["avg_dr_jet"] = new binningOptionType("avg_dr_jet", 50, 0., 5.);
  binningOptions_["dr_lep_tau_os"] = new binningOptionType("dr_lep_tau_os", 50, 0., 5.);
  binningOptions_["dr_lep_tau_ss"] = new binningOptionType("dr_lep_tau_ss", 50, 0., 5.);
  binningOptions_["dr_tau_lep"] = new binningOptionType("dr_tau_lep", 50, 0., 5.);
  binningOptions_["dr_taus"] = new binningOptionType("dr_taus", 50, 0., 5.);
  binningOptions_["htmiss"] = new binningOptionType("htmiss", 40, 0., 200.);
  binningOptions_["lep_pt"] = new binningOptionType("lep_pt", 40, 0., 200.);
  binningOptions_["lep_tth_mva"] = new binningOptionType("lep_tth_mva", 40, -1., +1.);
  binningOptions_["lep1_pt"] = new binningOptionType("lep1_pt", 40, 0., 200.);
  binningOptions_["lep1_tth_mva"] = new binningOptionType("lep1_tth_mva", 40, -1., +1.);
  binningOptions_["lep2_pt"] = new binningOptionType("lep2_pt", 40, 0., 200.);
  binningOptions_["lep2_tth_mva"] = new binningOptionType("lep2_tth_mva", 40, -1., +1.);
  binningOptions_["mindr_lep_jet"] = new binningOptionType("mindr_lep_jet", 50, 0., 5.);
  binningOptions_["mindr_lep1_jet"] = new binningOptionType("mindr_lep1_jet", 50, 0., 5.);
  binningOptions_["mindr_lep2_jet"] = new binningOptionType("mindr_lep2_jet", 50, 0., 5.);
  binningOptions_["mindr_tau_jet"] = new binningOptionType("mindr_tau_jet", 50, 0., 5.);
  binningOptions_["mindr_tau1_jet"] = new binningOptionType("mindr_tau1_jet", 50, 0., 5.);
  binningOptions_["mindr_tau2_jet"] = new binningOptionType("mindr_tau2_jet", 50, 0., 5.);
  binningOptions_["mT_lep"] = new binningOptionType("mT_lep", 40, 0., 200.);
  binningOptions_["mT_lep1"] = new binningOptionType("mT_lep1", 40, 0., 200.);
  binningOptions_["mT_lep2"] = new binningOptionType("mT_lep2", 40, 0., 200.);
  binningOptions_["mT_tau1"] = new binningOptionType("mT_tau1", 40, 0., 200.);
  binningOptions_["mT_tau2"] = new binningOptionType("mT_tau2", 40, 0., 200.);
  binningOptions_["mTauTau"] = new binningOptionType("mTauTau", 40, 0., 200.);
  binningOptions_["mTauTauVis"] = new binningOptionType("mTauTauVis", 40, 0., 200.);
  binningOptions_["nJet"] = new binningOptionType("nJet", 20, -0.5, +19.5);
  binningOptions_["nBJetLoose"] = new binningOptionType("nBJetLoose", 10, -0.5, +9.5);
  binningOptions_["nBJetMedium"] = new binningOptionType("nBJetMedium", 10, -0.5, +9.5);
  binningOptions_["ptmiss"] = new binningOptionType("ptmiss", 40, 0., 200.);
  binningOptions_["tau_pt"] = new binningOptionType("tau_pt", 40, 0., 200.);
  binningOptions_["tau1_pt"] = new binningOptionType("tau1_pt", 40, 0., 200.);
  binningOptions_["tau2_pt"] = new binningOptionType("tau2_pt", 40, 0., 200.);
  binningOptions_["TMath::Abs(lep_eta)"] = new binningOptionType("lep_absEta", 50, 0., +2.5);
  binningOptions_["TMath::Abs(lep1_eta)"] = new binningOptionType("lep1_absEta", 50, 0., +2.5);
  binningOptions_["TMath::Abs(lep2_eta)"] = new binningOptionType("lep2_absEta", 50, 0., +2.5);
  binningOptions_["TMath::Abs(tau_eta)"] = new binningOptionType("TMath::Abs(tau_eta)", 50, 0., +2.5);
  binningOptions_["TMath::Abs(tau1_eta)"] = new binningOptionType("TMath::Abs(tau1_eta)", 50, 0., +2.5);
  binningOptions_["TMath::Abs(tau2_eta)"] = new binningOptionType("TMath::Abs(tau2_eta)", 50, 0., +2.5);
}

MVAInputVarHistManager::~MVAInputVarHistManager()
{
  for ( std::map<std::string, binningOptionType*>::iterator it = binningOptions_.begin();
	it != binningOptions_.end(); ++it ) {
    delete it->second;
  }
}

void MVAInputVarHistManager::bookHistograms(TFileDirectory& dir, const std::vector<std::string>& mvaInputVariables)
{
  for ( std::vector<std::string>::const_iterator mvaInputVariable = mvaInputVariables.begin();
	mvaInputVariable != mvaInputVariables.end(); ++mvaInputVariable ) {
    std::map<std::string, binningOptionType*>::const_iterator binningOption_iter = binningOptions_.find(*mvaInputVariable);
    if ( binningOption_iter == binningOptions_.end() ) {
      throw cms::Exception("MVAInputVarHistManager::bookHistograms") 
	<< "No binning options defined for MVA input variable '" << (*mvaInputVariable) << "' !!\n";
    }
    
    const binningOptionType* binningOption = binningOption_iter->second;
    TH1* histogram = book1D(
      dir, binningOption->histogramName_, binningOption->histogramName_, 
      binningOption->numBinsX_, binningOption->xMin_, binningOption->xMax_);
    histograms_mvaInputVariables_[*mvaInputVariable] = histogram;
  }
}

void MVAInputVarHistManager::fillHistograms(const std::map<std::string, double>& mvaInputs, double evtWeight)
{
  double evtWeightErr = 0.;

  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
	mvaInput != mvaInputs.end(); ++mvaInput ) {
    std::map<std::string, TH1*>::const_iterator histogram_iter = histograms_mvaInputVariables_.find(mvaInput->first);
    if ( histogram_iter == histograms_mvaInputVariables_.end() ) {
      throw cms::Exception("MVAInputVarHistManager::fillHistograms") 
	<< "No histogram booked for MVA input variable '" << mvaInput->first << "' !!\n";
    }

    fillWithOverFlow(histogram_iter->second, mvaInput->second, evtWeight, evtWeightErr);
  }
}
