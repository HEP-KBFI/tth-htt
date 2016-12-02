#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_3l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_3l_1tau::CutFlowTableHistManager_3l_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_3l_1tau::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 19;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "trigger");
  xAxis->SetBinLabel(3, ">= 3 presel leptons");
  xAxis->SetBinLabel(4, "presel lepton trigger match");
  xAxis->SetBinLabel(5, ">= 2 jets (1)");
  xAxis->SetBinLabel(6, ">= 2 loose b-jets || 1 medium b-jet (1)");
  xAxis->SetBinLabel(7, ">= 1 sel tau (1)");
  xAxis->SetBinLabel(8, "3 sel leptons");
  xAxis->SetBinLabel(9, "sel lepton trigger match");
  xAxis->SetBinLabel(10, ">= 2 jets (2)");
  xAxis->SetBinLabel(11, ">= 2 loose b-jets || 1 medium b-jet (2)");
  xAxis->SetBinLabel(12, ">= 1 sel tau (2)");
  xAxis->SetBinLabel(13, "m(ll) > 12 GeV");
  xAxis->SetBinLabel(14, "lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV && third lepton pT > 10 GeV");
  xAxis->SetBinLabel(15, "sel lepton charge");
  xAxis->SetBinLabel(16, "sel lepton+tau charge");
  xAxis->SetBinLabel(17, "Z-boson mass veto");
  xAxis->SetBinLabel(18, "met LD");
  xAxis->SetBinLabel(19, "signal region veto");
}

void CutFlowTableHistManager_3l_1tau::fillHistograms(const std::string& cut, double evtWeight)
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
