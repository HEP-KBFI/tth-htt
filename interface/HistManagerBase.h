#ifndef tthAnalysis_HiggsToTauTau_HistManagerBase_h
#define tthAnalysis_HiggsToTauTau_HistManagerBase_h

/** \class HistManagerBase
 *
 * Base class for histogram booking and filling for ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <CommonTools/Utils/interface/TFileDirectory.h> // TFileDirectory, TH1

// forward declarations
class TH2;

class HistManagerBase
{
public:
  HistManagerBase(const edm::ParameterSet & cfg);
  virtual ~HistManagerBase() {}

  /// book and fill histograms
  virtual void
  bookHistograms(TFileDirectory & dir) = 0;

  /// manually write histograms to output file (usually not necessary, as histogram writing is done automatically when output file gets closed)
  static void
  writeHistograms();

protected:
  TH1 *
  book1D(TDirectory * dir,
         const std::string & distribution,
         const std::string & title,
         int numBins,
         double min,
         double max);
  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBins,
         double min,
         double max);
  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         int numBins,
         double min,
         double max);
  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBins,
         float * binning);
  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         int numBins,
         float * binning);

  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBins,
         double * binning);
  TH1 *
  book1D(TFileDirectory & dir,
         const std::string & distribution,
         int numBins,
         double * binning);

  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBinsX,
         double xMin,
         double xMax,
         int numBinsY,
         double yMin,
         double yMax);
  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         int numBinsX,
         double xMin,
         double xMax,
         int numBinsY,
         double yMin,
         double yMax);

  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBinsX,
         float * binningX,
         int numBinsY,
         float * binningY);
  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         int numBinsX,
         float * binningX,
         int numBinsY,
         float * binningY);

  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         const std::string & title,
         int numBinsX,
         double * binningX,
         int numBinsY,
         double * binningY);
  TH2 *
  book2D(TFileDirectory & dir,
         const std::string & distribution,
         int numBinsX,
         double * binningX,
         int numBinsY,
         double * binningY);

  bool 
  checkOptionIsSelected(const std::string &) const;

  TDirectory *
  createHistogramSubdirectory(TFileDirectory & dir);

  std::string
  getHistogramName(const std::string & distribution) const;

  std::string process_;
  std::string category_;
  std::string central_or_shift_;

  // key = histogramName, value = central_or_shift options for which histogram is to be booked & filled
  std::map<std::string, std::vector<std::string>> central_or_shiftOptions_;

  std::vector<TH1 *> histograms_;
  std::vector<TH2 *> histograms_2d_;

  // global list of all histograms (1d and 2d) booked by analysis job 
  static std::map<TDirectory *, std::vector<TH1 *>> gHistograms_;
};

edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
                    int idx = -1);

edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
                    const std::string & option,
                    int idx = -1);

#endif // tthAnalysis_HiggsToTauTau_HistManagerBase_h
