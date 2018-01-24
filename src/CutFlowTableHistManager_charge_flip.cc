#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_charge_flip.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_charge_flip::CutFlowTableHistManager_charge_flip(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_charge_flip::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 10;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "trigger");
  xAxis->SetBinLabel(3, "= 2 presel electrons");
  xAxis->SetBinLabel(4, "presel electron trigger match");
  xAxis->SetBinLabel(5, "= 0 presel muons");
  xAxis->SetBinLabel(6, "= 2 sel electrons");
  xAxis->SetBinLabel(7, "sel electron trigger match");
  xAxis->SetBinLabel(8, "lead electron pT > 25 GeV && sublead electron pT > 15 GeV");
  xAxis->SetBinLabel(9, "tight electron charge");
  xAxis->SetBinLabel(10, "60 < m(ee) < 120 GeV");
}

void CutFlowTableHistManager_charge_flip::fillHistograms(const std::string& cut, double evtWeight)
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
