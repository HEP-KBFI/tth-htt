#ifndef tthAnalysis_HiggsToTauTau_MVAInputVarCorrelationHistManager_h
#define tthAnalysis_HiggsToTauTau_MVAInputVarCorrelationHistManager_h

/** \class MVAInputVarCorrelationHistManager
 *
 * Compute linear (Pearson) correlation between any two MVA input variables:
 *   https://en.wikipedia.org/wiki/Pearson_correlation_coefficient
 * The correlation is computed by storing the following sums as bin-contents of histograms:
 *  - sum(w*x_i)
 *  - sum(w*x_i^2 )
 *  - sum(w*x_i*y_i)
 *  - sum(w*y_i)
 *  - sum(w*y_i^2)
 * and using the formula:
 *   rho = [ W*sum(w*x_i*y_i) - W*sum(w*x_i)*sum(w*y_i) ]/[ sqrt(W*sum(w*x_i^2) - (sum(w*x_i))^2  ] ,
 * where x_i and y_i denote the value of variables x and y for the i-th event,
 * w_i denotes the weight of the i-th event and W = sum(w) the sum of these weights.
 * The final computation of the Pearson correlation coefficient rho is implemented in:
 *   tthAnalysis/HiggsToTauTau/macros/compMVAInputVarCorrelation.C
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include <TH1.h> // TH1
#include <TH2.h> // TH2

#include <cassert> // assert()

class MVAInputVarCorrelationHistManager
  : public HistManagerBase
{
public:
  MVAInputVarCorrelationHistManager(const edm::ParameterSet & cfg);
  ~MVAInputVarCorrelationHistManager();

  /// book and fill histograms
  void bookHistograms(TFileDirectory & dir,
                      const std::vector<std::string> & mvaInputVariables);

  // call bookHistograms(TFileDirectory& dir, const std::vector<std::string>& mvaInputVariables) instead !!
  void bookHistograms(TFileDirectory &) override { assert (0); }

  void
  fillHistograms(const std::map<std::string, double> & mvaInputs,
                 double evtWeight);

private:
  std::vector<std::string> mvaInputVariables_;

  TH1 * histogram_sumX_;
  TH1 * histogram_sumX2_;
  TH2 * histogram_sumXY_;
  TH1 * histogram_sumWeights_;

  std::vector<TH1 *> histograms_;
};

std::vector<std::string>
getKeys(const std::map<std::string, double> & mvaInputs);

#endif
