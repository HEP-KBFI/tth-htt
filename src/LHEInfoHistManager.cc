#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <assert.h> // assert

LHEInfoHistManager::LHEInfoHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg),
    histogram_pdfWeights_(0)
{}

void LHEInfoHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_scaleWeights_ = book1D(dir, "scaleWeights", "scaleWeights", 4, -0.5, +3.5);
  //histogram_pdfWeights_ = book1D(dir, "pdfWeights", "pdfWeights", 103, -0.5, +102.5);
  dir_ = &dir;

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void LHEInfoHistManager::fillHistograms(const LHEInfoReader& lheInfoReader, double evtWeight)
{
  if ( !histogram_pdfWeights_ ) {
    int numBins = lheInfoReader.getNumWeights_pdf();
    assert(numBins >= 1);
    histogram_pdfWeights_ = book1D(*dir_, "pdfWeights", "pdfWeights", numBins, -0.5, numBins - 0.5);
  }
  
  double evtWeightErr = 0.;

  const int numWeights_scale = 4;
  for ( int idx = 0; idx < numWeights_scale; ++idx ) {
    double weight_scale = 1.;
    if      ( idx == 0 ) weight_scale = lheInfoReader.getWeight_scale_xUp();
    else if ( idx == 1 ) weight_scale = lheInfoReader.getWeight_scale_xDown();
    else if ( idx == 2 ) weight_scale = lheInfoReader.getWeight_scale_yUp();
    else if ( idx == 3 ) weight_scale = lheInfoReader.getWeight_scale_yDown();
    fill(histogram_scaleWeights_, idx, weight_scale*evtWeight, weight_scale*evtWeightErr);
  }

  const int numWeights_pdf = lheInfoReader.getNumWeights_pdf();
  for ( int idx = 0; idx < numWeights_pdf; ++idx ) {
    double weight_pdf = lheInfoReader.getWeight_pdf(idx);
    fill(histogram_pdfWeights_, idx, weight_pdf*evtWeight, weight_pdf*evtWeightErr);
  }
  
  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
