#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_0l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_0l_2tau::CutFlowTableHistManager_0l_2tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_0l_2tau::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 14;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "trigger");
  xAxis->SetBinLabel(3, ">= 2 presel taus");
  xAxis->SetBinLabel(4, ">= 2 jets");
  xAxis->SetBinLabel(5, ">= 2 loose b-jets || 1 medium b-jet (1)");
  xAxis->SetBinLabel(6, ">= 2 sel taus");
  xAxis->SetBinLabel(7, "no tight leptons");
  xAxis->SetBinLabel(8, ">= 4 jets");
  xAxis->SetBinLabel(9, ">= 2 loose b-jets || 1 medium b-jet (2)");
  xAxis->SetBinLabel(10, "m(ll) > 12 GeV");
  xAxis->SetBinLabel(11, "lead hadTau pT > 40 GeV && abs(eta) < 2.1");
  xAxis->SetBinLabel(12, "sublead hadTau pT > 40 GeV && abs(eta) < 2.1");
  xAxis->SetBinLabel(13, "tau-pair OS/SS charge");
  xAxis->SetBinLabel(14, "signal region veto");
}

void CutFlowTableHistManager_0l_2tau::fillHistograms(const std::string& cut, double evtWeight)
{
  double evtWeightErr = 0.;

  const TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  int idxBin = (const_cast<TAxis*>(xAxis))->FindBin(cut.data());
  if ( idxBin >= 1 && idxBin <= xAxis->GetNbins() ) {
    double binCenter = xAxis->GetBinCenter(idxBin);
    fill(histogram_cutFlow_, binCenter, evtWeight, evtWeightErr);
  } else {
    std::cerr << "Error: cut = '" << cut << "' not defined !!" << std::endl;
    assert(0);
  }
}
