#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill(), fillWithOverFlow()

#include <TH1.h> // TH1

#include <cassert> // assert()

LHEInfoHistManager::LHEInfoHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg),
    histogram_pdfWeights_(nullptr)
{}

void
LHEInfoHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_scaleWeights_ = book1D(dir, "scaleWeights", "scaleWeights",   4, -0.5,   +3.5);
  histogram_pdfWeights_   = book1D(dir, "pdfWeights", "pdfWeights",     103, -0.5, +102.5);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter",   1, -0.5,   +0.5);
}

void
LHEInfoHistManager::fillHistograms(const LHEInfoReader & lheInfoReader,
                                   double evtWeight)
{
  const double evtWeightErr = 0.;
  const int numWeights_scale = 4;

  for(int idx = 0; idx < numWeights_scale; ++idx)
  {
    double weight_scale = 1.;
    switch(idx)
    {
      case 0: weight_scale = lheInfoReader.getWeight_scale_xUp();   break;
      case 1: weight_scale = lheInfoReader.getWeight_scale_xDown(); break;
      case 2: weight_scale = lheInfoReader.getWeight_scale_yUp();   break;
      case 3: weight_scale = lheInfoReader.getWeight_scale_yDown(); break;
      default: assert(0);
    }
    fill(histogram_scaleWeights_, idx, weight_scale * evtWeight, weight_scale * evtWeightErr);
  }

  const int numWeights_pdf = lheInfoReader.getNumWeights_pdf();
  for(int idx = 0; idx < numWeights_pdf; ++idx)
  {
    const double weight_pdf = lheInfoReader.getWeight_pdf(idx);
    fill(histogram_pdfWeights_, idx, weight_pdf * evtWeight, weight_pdf * evtWeightErr);
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
