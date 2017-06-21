#ifndef tthAnalysis_HiggsToTauTau_HadTopKinFit_h
#define tthAnalysis_HiggsToTauTau_HadTopKinFit_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector

#include "Math/Factory.h" // ROOT::Math::Factory
#include "Math/Minimizer.h" // ROOT::Math::Minimizer
#include "Math/Functor.h" // ROOT::Math::Functor

namespace hadTopKinFit
{
  // CV: define interface to MINUIT algorithm for chi^2 minimization
  class ObjectiveFunctionAdapter
  {
   public:
    double operator()(const double* x) const; // NOTE: return value = chi^2
  };

  //---------------------------------------------------------------------------------------------------------------
  // CV: transfer functions for energy of bottom and light quark jets taken from ttH, H->bb matrix element analysis 
  //       https://github.com/bianchini/Code/blob/master/interface/Parameters.h
  const double TF_Q_param[2][5] = { 
    { 0.00e+00, 1.00e+00, 0.00e+00, 1.56e+00, 0.00e+00 },
    { 0.00e+00, 1.00e+00, 1.30e-01, 1.52e+00, 0.00e+00 }
  };
  const double TF_B_param[2][11] = { 
    { -3.60e+00, 1.00e+00, 0.00e+00, 0.99e+00, 5.70e+00,-3.30e+00, 0.94e+00, 0.16e+00, 1.70e+00, 6.60e+00, 0.65e+00 },
    { -4.30e+00, 0.98e+00, 0.00e+00, 1.90e+00, 6.00e+00, 0.91e+01, 0.87e+00, 0.23e+00, 1.10e+00, 0.00e+00, 0.65e+00 },
  };
  //---------------------------------------------------------------------------------------------------------------
}

class HadTopKinFit
{
 public:
  HadTopKinFit();
  ~HadTopKinFit();

  void fit(const Particle::LorentzVector& recBJetP4, const Particle::LorentzVector& recWJet1P4, const Particle::LorentzVector& recWJet2P4);

  const Particle::LorentzVector& fittedBJet() const;
  const Particle::LorentzVector& fittedWJet1() const;
  const Particle::LorentzVector& fittedWJet2() const;
  double alpha() const;
  double nll() const;
  int fit_status() const;

  /// static pointer to this (needed for interface to MINUIT)
  static const HadTopKinFit* gHadTopKinFit;

  double comp_nll(double alpha) const;

 protected:
  double comp_fittedP2(double fittedE1, double fittedP1, double recP2, double M_2, double m1_2, double m2_2, double cosAngle) const;

  double evalTF_BJet(double recE, double fittedE, double eta) const;
  double evalTF_lightJet(double recE, double fittedE, double eta) const;

  Particle::LorentzVector recBJetP4_;
  Particle::LorentzVector recWJet1P4_;
  Particle::LorentzVector recWJet2P4_;

  mutable Particle::LorentzVector fittedBJetP4_;
  mutable Particle::LorentzVector fittedWJet1P4_;
  mutable Particle::LorentzVector fittedWJet2P4_;
  mutable double alpha_;
  mutable double nll_;
  mutable int fit_status_;

  const double mTop2_;
  const double mW2_;
  const double mB2_;

  /// MINUIT instance 
  ROOT::Math::Minimizer* minimizer_;
  /// interface to MINUIT algorithm for chi^2 minimization
  hadTopKinFit::ObjectiveFunctionAdapter objectiveFunctionAdapter_;
  int maxObjFunctionCalls_;
};

#endif // tthAnalysis_HiggsToTauTau_HadTopKinFit_h
