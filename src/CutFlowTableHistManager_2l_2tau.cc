#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_2l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_2l_2tau::CutFlowTableHistManager_2l_2tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_2l_2tau::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 22;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "trigger");
  xAxis->SetBinLabel(3, ">= 2 presel leptons");
  xAxis->SetBinLabel(4, "presel lepton trigger match");
  xAxis->SetBinLabel(5, ">= 2 presel taus");
  xAxis->SetBinLabel(6, ">= N jets (1)");
  xAxis->SetBinLabel(7, ">= 2 loose b-jets || 1 medium b-jet (1)");
  xAxis->SetBinLabel(8, ">= 2 sel leptons");
  xAxis->SetBinLabel(9, "sel lepton trigger match");
  xAxis->SetBinLabel(10, ">= 2 sel taus");
  xAxis->SetBinLabel(11, "<= 2 tight leptons");
  xAxis->SetBinLabel(12, ">= N jets (2)");
  xAxis->SetBinLabel(13, ">= 2 loose b-jets || 1 medium b-jet (2)");
  xAxis->SetBinLabel(14, ">= 2 sel tau (2)");
  xAxis->SetBinLabel(15, "m(ll) > 12 GeV");
  xAxis->SetBinLabel(16, "lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV");
  xAxis->SetBinLabel(17, "sel lepton-pair OS/SS charge");
  xAxis->SetBinLabel(18, "tau-pair OS/SS charge");
  xAxis->SetBinLabel(19, "sel lepton+tau charge");
  xAxis->SetBinLabel(20, "Z-boson mass veto");
  xAxis->SetBinLabel(21, "met LD");
  xAxis->SetBinLabel(22, "signal region veto");
}

void CutFlowTableHistManager_2l_2tau::fillHistograms(const std::string& cut, double evtWeight)
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
