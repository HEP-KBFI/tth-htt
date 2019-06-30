#include "tthAnalysis/HiggsToTauTau/interface/PlotterPluginBase.h"

#include <TFile.h>

PlotterPluginBase::PlotterPluginBase(const TFile * inputFile,
                                     const edm::ParameterSet & cfg)
  : inputFile_(inputFile)
  , cfg_(cfg)
{}
  
PlotterPluginBase::~PlotterPluginBase() 
{}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "FWCore/Framework/interface/MakerMacros.h"
#pragma GCC diagnostic pop

EDM_REGISTER_PLUGINFACTORY(PlotterPluginFactory, "PlotterPluginFactory");
