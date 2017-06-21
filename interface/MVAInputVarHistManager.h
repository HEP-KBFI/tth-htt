#ifndef tthAnalysis_HiggsToTauTau_MVAInputVarHistManager_h
#define tthAnalysis_HiggsToTauTau_MVAInputVarHistManager_h

/** \class MVAInputVarHistManager
 *
 * Book and fill histograms for input variables of MVA used to separate the ttH signal from backgrounds 
 * in the ttH, H->tautau analysis. 
 * The histogram manager class is written in a generic way so that it can be used for different channels.
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include <string> // std::string
#include <map> // std::map
#include <assert.h> // assert

class MVAInputVarHistManager
  : public HistManagerBase
{
 public:
  MVAInputVarHistManager(edm::ParameterSet const& cfg);
  ~MVAInputVarHistManager();

  /// define binning options
  void defineBinningOption(const std::string& histogramName, int numBinsX, double xMin, double xMax);

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir, const std::vector<std::string>& mvaInputVariables);
  void bookHistograms(TFileDirectory& dir) { assert (0); } // call bookHistograms(TFileDirectory& dir, const std::vector<std::string>& mvaInputVariables) instead !!
  void fillHistograms(const std::map<std::string, double>& mvaInputs, double evtWeight);

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

  std::map<std::string, TH1*> histograms_mvaInputVariables_; // key = mvaInputVariable

  std::vector<TH1*> histograms_;
};

#endif
