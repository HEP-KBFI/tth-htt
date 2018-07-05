#include "tthAnalysis/HiggsToTauTau/interface/PlotterPluginBase.h"

PlotterPluginBase::PlotterPluginBase(const TFile* inputFile, const edm::ParameterSet& cfg)
  : inputFile_(inputFile)
  , cfg_(cfg)
{}
  
PlotterPluginBase::~PlotterPluginBase() 
{}

#include "FWCore/Framework/interface/MakerMacros.h"

EDM_REGISTER_PLUGINFACTORY(PlotterPluginFactory, "PlotterPluginFactory");
