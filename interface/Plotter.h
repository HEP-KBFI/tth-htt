#ifndef tthAnalysis_HiggsToTauTau_Plotter_h
#define tthAnalysis_HiggsToTauTau_Plotter_h

/** \class Plotter
 *
 * Base-class to make control plots (prefit and postfit) for different analysis.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/PlotterPluginBase.h"
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

#include <vector>
#include <string>

class Plotter : public PlotterPluginBase
{
 public:
  // constructor 
  Plotter(const TFile* inputFile, const edm::ParameterSet& cfg);
  
  // destructor
  virtual ~Plotter();

  virtual void makePlots();

 private:
  virtual void makePlot(double canvasSizeX, double canvasSizeY,
			TH1* histogramData, TH1* histogramData_blinded,
			std::vector<histogramEntryType*>& histogramsBackground, 	
			TH1* histogramSignal,
			TH1* histogramUncertainty,
			double legendTextSize, double legendPosX, double legendPosY, double legendSizeX, double legendSizeY, 
			const std::string& labelOnTop,
			std::vector<std::string>& extraLabels, double labelTextSize,
			double labelPosX, double labelPosY, double labelSizeX, double labelSizeY,
			double xMin, double xMax, const std::string& xAxisTitle, double xAxisOffset,
			bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
			const std::string& outputFileName, 
			bool isRebinned, 
			bool divideByBinWidth) = 0;
  
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {
      name_ = cfg.getParameter<std::string>("name");
      label_ = cfg.getParameter<std::string>("label");
    }
    ~categoryEntryType() {}
    std::string name_;
    std::string label_;
  };
  std::vector<categoryEntryType*> categories_;
  std::vector<std::string> categoryNames_;

  std::string processData_;
  std::vector<std::string> processesBackground_;
  std::string processSignal_;

  std::vector<plotEntryType*> distributions_;

  bool applyRebinning_;
  bool apply_fixed_rebinning_;
  bool apply_automatic_rebinning_;
  double minEvents_automatic_rebinning_;
  bool applyAutoBlinding_;
  bool divideByBinWidth_;

  HistogramManager* histogramManager_;
  bool showUncertainty_;

  std::string labelOnTop_;
  
  std::string outputFileName_;
};


#endif
