#ifndef tthAnalysis_HiggsToTauTau_PlotterPluginBase_h
#define tthAnalysis_HiggsToTauTau_PlotterPluginBase_h

/** \class PlotterPluginBase
 *
 * Pure virtual base-class for plotter plugins,
 * used by makePlots and makePlots_mcClosure executables
 * 
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// forward declarations
class TFile;

class PlotterPluginBase
{
 public:
  explicit PlotterPluginBase(const TFile * inputFile,
                             const edm::ParameterSet & cfg);
  virtual ~PlotterPluginBase();

  virtual void makePlots() = 0;

 protected:
  const TFile * inputFile_;
  edm::ParameterSet cfg_;
};

#include "FWCore/PluginManager/interface/PluginFactory.h"

typedef edmplugin::PluginFactory<PlotterPluginBase*(const TFile *, const edm::ParameterSet &)> PlotterPluginFactory;

#endif  

