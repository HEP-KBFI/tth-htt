#ifndef tthAnalysis_HiggsToTauTau_Topness_h
#define tthAnalysis_HiggsToTauTau_Topness_h

/** \class Topness
 *
 * Compute Topness variable, described in the paper
 * [1] "Measuring the triple Higgs self-interaction at the Large Hadron Collider",
 *      J.H. Kim, K. Kong, K.T. Matchev, M. Park
 *    arXiv: 1807.11498
 *
 * \authors Jeong Han Kim, with modifications by Christian Veelken
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector

#include "Math/Minimizer.h"

namespace topness
{
  // CV: define interface to MINUIT algorithm 
  class ObjectiveFunctionAdapterMINUIT
  {
  public:
    double operator()(const double * x) const; // return value = chi^2
  };
}

class Topness
{
 public:
  enum modeType { kPublishedChi2, kFixedChi2 };
  Topness(modeType mode = kPublishedChi2, int maxObjFunctionCalls = 10000);
  ~Topness();

  void set_sigmaW(double sigmaW);
  void set_sigmaTop(double sigmaTop);
  
  /// compute Topness variable according to Eqs. (2) and (3) in Ref. [1]
  void fit(const Particle::LorentzVector& lepton1P4,
	   const Particle::LorentzVector& lepton2P4,
	   const Particle::LorentzVector& bjet1P4,
	   const Particle::LorentzVector& bjet2P4,
	   double metPx, double metPy);

  /// flag indicating whether or not MINUIT fit converged
  bool isValidSolution() const;

  /// access Topness value
  double logTopness() const;

  /// static pointer to this (needed for interface to MINUIT)
  static const Topness* gTopness;

  /// fit-function, called by MINUIT
  double operator()(const double* x) const;

 private:
  modeType mode_;

  Particle::LorentzVector lepton1P4_;
  Particle::LorentzVector lepton2P4_;
  Particle::LorentzVector bjet1P4_;
  Particle::LorentzVector bjet2P4_;
  double metPx_;
  double metPy_;

  double sigmaTop_;
  double sigmaW_;

  mutable int numObjFunctionCalls_;

  //-----------------------------------------------------------------------------
  /// MINUIT algorithm
  ROOT::Math::Minimizer* minimizer_;
  topness::ObjectiveFunctionAdapterMINUIT objectiveFunctionAdapterMINUIT_;
  int maxObjFunctionCalls_;
  mutable int fitStatus_;
  mutable double logTopness_;
  //-----------------------------------------------------------------------------

  const int numPermutations_;
  double* chi2_of_permutation_;
  int* fitStatus_of_permutation_;
};

#endif // tthAnalysis_HiggsToTauTau_Topness_h
