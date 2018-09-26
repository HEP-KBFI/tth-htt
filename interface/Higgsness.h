#ifndef tthAnalysis_HiggsToTauTau_Higgsness_h
#define tthAnalysis_HiggsToTauTau_Higgsness_h

/** \class Higgsness
 *
 * Compute Higgsness variable, described in the paper
 * [1] "Measuring the triple Higgs self-interaction at the Large Hadron Collider",
 *      J.H. Kim, K. Kong, K.T. Matchev, M. Park
 *    arXiv: 1807.11498
 *
 * \authors Jeong Han Kim, with modifications by Christian Veelken
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector

#include "Math/Minimizer.h"

namespace higgsness
{
  // CV: define interface to MINUIT algorithm 
  class ObjectiveFunctionAdapterMINUIT
  {
  public:
    double operator()(const double * x) const; // return value = chi^2
  };
}

class Higgsness
{
 public:
  enum modeType { kPublishedChi2, kFixedChi2 };
  Higgsness(modeType mode = kPublishedChi2, int maxObjFunctionCalls = 10000);
  ~Higgsness();

  void set_sigmaW_onshell(double sigmaW_onshell);
  void set_sigmaW_offshell(double sigmaW_offshell);
  void set_sigmaH_lep(double sigmaH_lep);
  
  /// compute Higgsness variable according to Eq. (4) in Ref. [1]
  void fit(const Particle::LorentzVector& lepton1P4,
	   const Particle::LorentzVector& lepton2P4,
	   double metPx, double metPy);

  /// flag indicating whether or not MINUIT fit converged
  bool isValidSolution() const;

  /// access Higgsness value
  double logHiggsness() const;

  /// static pointer to this (needed for interface to MINUIT)
  static const Higgsness* gHiggsness;

  /// fit-function, called by MINUIT
  double operator()(const double* x) const;

 private:
  modeType mode_;

  Particle::LorentzVector lepton1P4_;
  Particle::LorentzVector lepton2P4_;
  double metPx_;
  double metPy_;

  double sigmaW_onshell_;
  double sigmaW_offshell_;
  double sigmaH_lep_;

  mutable int numObjFunctionCalls_;

  //-----------------------------------------------------------------------------
  /// MINUIT algorithm
  ROOT::Math::Minimizer* minimizer_;
  higgsness::ObjectiveFunctionAdapterMINUIT objectiveFunctionAdapterMINUIT_;
  int maxObjFunctionCalls_;
  mutable int fitStatus_;
  mutable double logHiggsness_;
  //-----------------------------------------------------------------------------

  const int numPermutations_;
  double* chi2_of_permutation_;
  int* fitStatus_of_permutation_;
};

#endif // tthAnalysis_HiggsToTauTau_Higgsness_h
