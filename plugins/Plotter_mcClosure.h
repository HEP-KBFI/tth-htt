#ifndef tthAnalysis_HiggsToTauTau_Plotter_mcClosure_h
#define tthAnalysis_HiggsToTauTau_Plotter_mcClosure_h

/** \class Plotter_mcClosure
 *
 * Make control plots demonstrating MC closure of procedure for jet->tau fake background estimation.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/PlotterPluginBase.h"
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

#include <vector>
#include <string>

class Plotter_mcClosure : public PlotterPluginBase
{
 public:
  // constructor 
  explicit Plotter_mcClosure(const TFile* inputFile, const edm::ParameterSet& cfg);
  
  // destructor
  virtual ~Plotter_mcClosure();

  virtual void makePlots();

 private:
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {
      signal_ = cfg.getParameter<std::string>("signal");
      sideband_ = cfg.getParameter<std::string>("sideband");
      label_ = cfg.getParameter<std::string>("label");
    }
    ~categoryEntryType() {}
    std::string signal_;
    std::string sideband_;
    std::string label_;
  };
  std::vector<categoryEntryType*> categories_;
  std::vector<std::string> categoryNames_sideband_;

  std::string process_signal_;
  std::string process_sideband_;

  std::vector<plotEntryType*> distributions_;

  HistogramManager* histogramManager_;
  bool showUncertainty_;

  double legendTextSize_;
  double legendPosX_;
  double legendPosY_;
  double legendSizeX_;
  double legendSizeY_;

  std::string labelOnTop_;
  
  std::string outputFileName_;
};

#endif
