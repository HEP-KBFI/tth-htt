#ifndef tthAnalysis_HiggsToTauTau_plottingAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_plottingAuxFunctions_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet, edm::VParameterSet

// forward declarations
class TH1;
class TDirectory;

struct histogramEntryType
{
  histogramEntryType(const std::string & process,
                     TH1 * histogram);
  ~histogramEntryType() {}
  std::string process_;
  TH1 * histogram_;
};

struct plotEntryType
{
  plotEntryType(const edm::ParameterSet & cfg);
  ~plotEntryType() {}
  std::string histogramName_;
  std::string outputFileName_;
  double xMin_;
  double xMax_;
  std::string xAxisTitle_;
  double xAxisOffset_;
  double yMin_;
  double yMax_;
  std::string yAxisTitle_;
  double yAxisOffset_;
  std::vector<std::pair<double, double>> keepBlinded_;
  std::vector<double> explicitBinning_;

  bool
  hasExplicitBinning() const;
};

//-----------------------------------------------------------------------------
void
parseValue_and_Uncertainty(const std::string & valueErr_string,
                           double & value,
                           double & err);

TH1 *
getHistogram_wrapper(const TDirectory * dir,
                     const std::string & process,
                     const std::string & histogramName,
                     const std::string & central_or_shift,
                     bool enableException);

void
printHistogram(const TH1 * histogram);

struct HistogramManager
{
  HistogramManager(const std::vector<std::string> & processesBackground,
                   const std::string & processSignal,
                   const std::vector<std::string> & categories,
                   const edm::ParameterSet & cfg);

  ~HistogramManager() {}

  void setDirectory(TDirectory * dir);
  void setCategory(const std::string & category);
  void setHistogram(const std::string & histogramName);

  TH1 *
  getHistogramPrefit(const std::string & process,
                     bool enableException);
  TH1 *
  getHistogramPostfit(const std::string & process,
                      bool enableException);
  TH1 *
  getHistogramUncertainty();

  void
  getSF(const std::string & process,
        double & sf,
        double & sfErr) const;
  
  void update();

  typedef std::vector<std::string> vstring;
  vstring processes_;

  struct normEntryType
  {
    std::string process_;
    std::string category_;
    double sf_;
    double sfErr_;
  };
  typedef std::map<std::string, normEntryType> stringToNormEntryTypeMap;
  std::map<std::string, stringToNormEntryTypeMap> normalizationValues_and_Uncertainties_; // keys = process, category
  vstring sysShifts_;

  struct shapeEntryType
  {
    std::string sysShift_;
    double value_;
    double err_;
  };
  std::map<std::string, shapeEntryType> shapeValues_and_Uncertainties_; // key = sysShift

  TDirectory * currentDir_;
  std::string currentCategory_;
  std::string currentHistogramName_;

  bool isUpToDate_;

  typedef std::map<std::string, TH1 *> map_string_to_TH1;
  map_string_to_TH1 histograms_prefit_;  // key = process
  map_string_to_TH1 histograms_postfit_; // key = process
  std::map<std::string, map_string_to_TH1> histograms_sysShifts_; // key = process, sysShift
  TH1 * histogram_uncertainty_;
};
//-----------------------------------------------------------------------------

TH1 *
divideHistogramByBinWidth(TH1* histogram);

std::pair<double, double>
compYmin_and_YmaxForClearance(TH1 * histogram,
			      double legendPosX,
			      double legendPosY,
			      double labelPosY,
			      bool useLogScale,
			      double numOrdersOfMagnitude);

std::vector<plotEntryType *>
readDistributions(const edm::VParameterSet & cfgDistributions);

#endif
