
/** \executable makePlots
 *
 * Make different types of control plots for ttH, H->tautau analysis (and for other analyses).
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PluginManager/interface/PluginManager.h"
#include "FWCore/PluginManager/interface/standard.h"

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/PlotterPluginBase.h"

#include <TFile.h>
#include <TBenchmark.h>
#include <TROOT.h>
#include <TError.h> // gErrorAbortLevel, kError

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<makePlots>:" << std::endl;

  gROOT->SetBatch(true);

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("makePlots");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("makePlots") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgMakePlots = cfg.getParameter<edm::ParameterSet>("makePlots");

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("makePlots") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  std::string pluginType = cfgMakePlots.getParameter<std::string>("pluginType");
  edmplugin::PluginManager::configure(edmplugin::standard::config());
  auto plugin = PlotterPluginFactory::get()->create(pluginType, inputFile, cfgMakePlots);
  plugin->makePlots();
  
  delete inputFile;
  
  clock.Show("makePlots");

  return 0;
}



