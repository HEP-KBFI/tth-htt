#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_1l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_1l_1tau::CutFlowTableHistManager_1l_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_1l_1tau::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 20;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "trigger");
  xAxis->SetBinLabel(3, "1 presel lepton");
  xAxis->SetBinLabel(4, "presel lepton trigger match");
  xAxis->SetBinLabel(5, ">= 1 presel taus");
  xAxis->SetBinLabel(6, ">= 2 jets");
  xAxis->SetBinLabel(7, ">= 2 loose b-jets || 1 medium b-jet (1)");
  xAxis->SetBinLabel(8, "1 sel lepton");
  xAxis->SetBinLabel(9, "<= 1 tight leptons");
  xAxis->SetBinLabel(10, "sel lepton trigger match");
  xAxis->SetBinLabel(11, ">= 1 sel taus");
  xAxis->SetBinLabel(12, "<= 1 tight taus");
  xAxis->SetBinLabel(13, ">= 4 jets");
  xAxis->SetBinLabel(14, ">= 2 loose b-jets || 1 medium b-jet (2)");
  xAxis->SetBinLabel(15, "m(ll) > 12 GeV");
  xAxis->SetBinLabel(16, "sel lepton pT > 25(e)/20(mu) GeV");
  xAxis->SetBinLabel(17, "sel lepton abs(eta) < 2.1");
  xAxis->SetBinLabel(18, "sel hadTau pT > 30 GeV");
  xAxis->SetBinLabel(19, "lepton+tau charge");
  xAxis->SetBinLabel(20, "signal region veto");
}

void CutFlowTableHistManager_1l_1tau::fillHistograms(const std::string& cut, double evtWeight)
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
