#ifndef tthAnalysis_HiggsToTauTau_WeightHistManager_h
#define tthAnalysis_HiggsToTauTau_WeightHistManager_h

/** \class WeightHistManager
 *
 * Book and fill histograms for monitoring event weights
 * applied in the ttH, H->tautau analysis. 
 * The histogram manager class is written in a generic way so that it can be used for different channels.
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include <string> // std::string
#include <map> // std::map
#include <assert.h> // assert

class WeightHistManager
  : public HistManagerBase
{
 public:
  WeightHistManager(edm::ParameterSet const& cfg);
  ~WeightHistManager();

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir, const std::vector<std::string>& weight_names);
  void bookHistograms(TFileDirectory& dir) { assert (0); } // call bookHistograms(TFileDirectory& dir, const std::vector<std::string>& weight_names) instead !!
  void fillHistograms(const std::string& weight_name, double weight_value);

 private:
  struct binningOptionType
  {
    binningOptionType(const std::string& histogramName, int numBinsX, double xMin, double xMax)
      : histogramName_(histogramName),
	numBinsX_(numBinsX),
	xMin_(xMin),
	xMax_(xMax)
    {}
    ~binningOptionType() {}
    std::string histogramName_;
    int numBinsX_;
    double xMin_;
    double xMax_;
  };
  std::map<std::string, binningOptionType*> binningOptions_;

  std::map<std::string, TH1*> histograms_weights_; // key = weight_name

  std::vector<TH1*> histograms_;
};

#endif
