#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_gen.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TAxis.h>

#include <iostream> // std::cerr
#include <iomanip>
#include <assert.h> // assert

CutFlowTableHistManager_gen::CutFlowTableHistManager_gen(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void CutFlowTableHistManager_gen::bookHistograms(TFileDirectory& dir)
{
  int numCuts = 16;
  histogram_cutFlow_ = book1D(dir, "cutFlow", "cutFlow", numCuts, -0.5, numCuts - 0.5);
  TAxis* xAxis = histogram_cutFlow_->GetXaxis();
  xAxis->SetBinLabel(1, "run:ls:event selection");
  xAxis->SetBinLabel(2, "2 genTopQuarks");
  xAxis->SetBinLabel(3, "2 genBJets");
  xAxis->SetBinLabel(4, "4 genWJets");
  xAxis->SetBinLabel(5, "1 genHiggBoson");
  xAxis->SetBinLabel(6, "2 genTaus");
  xAxis->SetBinLabel(7, "genTopQuark && genAntiTopQuark");
  xAxis->SetBinLabel(8, "genBJetFromTop && genBJetFromAntiTop");
  xAxis->SetBinLabel(9, "genWBosonFromTop && genWBosonFromAntiTop");
  xAxis->SetBinLabel(10, "genTopQuark mass");
  xAxis->SetBinLabel(11, "genAntiTopQuark mass");
  xAxis->SetBinLabel(12, "2 genWJetsFromTop && 2 genWJetsFromAntiTop");
  xAxis->SetBinLabel(13, "genWBosonFromTop mass");
  xAxis->SetBinLabel(14, "genWBosonFromAntiTop mass");
  xAxis->SetBinLabel(15, "lead genTau pT > 30 GeV && abs(eta) < 2.5");
  xAxis->SetBinLabel(16, "sublead genTau pT > 30 GeV && abs(eta) < 2.5");
}

void CutFlowTableHistManager_gen::fillHistograms(const std::string& cut, double evtWeight)
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
