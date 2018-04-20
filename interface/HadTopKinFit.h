#ifndef tthAnalysis_HiggsToTauTau_HadTopKinFit_h
#define tthAnalysis_HiggsToTauTau_HadTopKinFit_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector

// forward declarations
class TF1;
class TFile;
namespace ROOT {
  namespace Math {
    class Minimizer;
  }
}

namespace hadTopKinFit
{
  // CV: define interface to MINUIT algorithm 
  class ObjectiveFunctionAdapterMINUIT
  {
  public:
    double
    operator()(const double * x) const; // NOTE: return value = -log(p)
  };

  // CV: define interface to VEGAS algorithm 
  class ObjectiveFunctionAdapterVEGAS
  {
  public:
    double
    operator()(const double * x) const; // NOTE: return value = p
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
  HadTopKinFit(int tf_mode = 1,
               const std::string & tf_fileName = "tthAnalysis/HiggsToTauTau/data/TF_jets.root");
  ~HadTopKinFit();

  //-----------------------------------------------------------------------------
  /// functions to call when using HadTopKinFit in "fit mode"
  void
  fit(const Particle::LorentzVector & recBJetP4,
      const Particle::LorentzVector & recWJet1P4,
      const Particle::LorentzVector & recWJet2P4);

  const Particle::LorentzVector &
  fittedBJet() const;

  const Particle::LorentzVector &
  fittedWJet1() const;

  const Particle::LorentzVector &
  fittedWJet2() const;

  Particle::LorentzVector
  fittedTop() const;

  Particle::LorentzVector
  fittedW() const;

  double
  alpha() const;

  double
  nll() const;

  int
  fit_status() const;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  /// functions to call when using HadTopKinFit in "integration mode"
  void
  integrate(const Particle::LorentzVector & recBJetP4,
            const Particle::LorentzVector & recWJet1P4,
            const Particle::LorentzVector & recWJet2P4);

  double
  p() const;

  double
  pErr() const;
  //-----------------------------------------------------------------------------

  /// static pointer to this (needed for interface to MINUIT)
  static const HadTopKinFit * gHadTopKinFit;
       
  /// "objective" function that gets called by MINUIT and VEGAS (via operator() function of ObjectiveFunctionAdapter class)
  double
  comp_prob(double alpha) const;

protected:
  double
  comp_fittedP2(double fittedE1,
                double fittedP1,
                double recP2,
                double M_2,
                double m1_2,
                double m2_2,
                double cosAngle) const;

  double
  evalTF_BJet(const Particle::LorentzVector & recP4,
              const Particle::LorentzVector & fittedP4) const;

  double
  evalTF_lightJet(const Particle::LorentzVector & recP4,
                  const Particle::LorentzVector & fittedP4) const;

  int tf_mode_; // set to 0 to use hard-coded TF, set to 1 to use TF from ROOT file
  TFile * tf_file_;
  TF1 * tf_q_barrel_;
  TF1 * tf_q_endcap_;
  TF1 * tf_b_barrel_;
  TF1 * tf_b_endcap_;

  Particle::LorentzVector recBJetP4_;
  Particle::LorentzVector recWJet1P4_;
  Particle::LorentzVector recWJet2P4_;

  mutable Particle::LorentzVector fittedBJetP4_;
  mutable Particle::LorentzVector fittedWJet1P4_;
  mutable Particle::LorentzVector fittedWJet2P4_;
  mutable double max_prob_;

  const double mTop2_;
  const double mW2_;
  const double mB2_;

  //-----------------------------------------------------------------------------
  /// MINUIT algorithm
  ROOT::Math::Minimizer * minimizer_;
  hadTopKinFit::ObjectiveFunctionAdapterMINUIT objectiveFunctionAdapterMINUIT_;
  int maxObjFunctionCalls_;
  mutable double alpha_;
  mutable double nll_;
  mutable int fit_status_;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  /// VEGAS algorithm
  hadTopKinFit::ObjectiveFunctionAdapterVEGAS objectiveFunctionAdapterVEGAS_;
  double p_;
  double pErr_;
  //-----------------------------------------------------------------------------
};

#endif // tthAnalysis_HiggsToTauTau_HadTopKinFit_h
