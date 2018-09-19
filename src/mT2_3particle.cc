#include "tthAnalysis/HiggsToTauTau/interface/mT2_3particle.h"

#include "Math/Factory.h"

mT2_3particle::mT2_3particle(int numSteps)
  : minimizer_(nullptr)
  , f_(nullptr)
  , numSteps_(numSteps)
  , min_mT2_(1.e+6)
  , min_step_(-1)
{
  f_ = new ROOT::Math::Functor(mT2Functor_, 2);
  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "");
  minimizer_->SetFunction(*f_);
}

mT2_3particle::~mT2_3particle()
{
  delete minimizer_;
  delete f_;
}

void mT2_3particle::operator()(double a1Px, double a1Py, double a1Mass, 
			       double a2Px, double a2Py, double a2Mass,
			       double b1Px, double b1Py, double b1Mass, 
			       double b2Px, double b2Py, double b2Mass,
			       double cSumPx, double cSumPy, double cMass)
{
  mT2Functor_.set_a1(a1Px, a1Py, a1Mass);
  mT2Functor_.set_a2(a2Px, a2Py, a2Mass);
  mT2Functor_.set_b1(b1Px, b1Py, b1Mass);
  mT2Functor_.set_b2(b2Px, b2Py, b2Mass);
  mT2Functor_.set_cSum(cSumPx, cSumPy, cMass);

  double cSumPt = TMath::Sqrt(cSumPx*cSumPx + cSumPy*cSumPy);
  double log_cSumPt_over_2 = TMath::Log(0.5*TMath::Max(1., cSumPt));

  min_mT2_ = 1.e+6;
  min_step_ = -1;
  for ( int iStep = 0; iStep < numSteps_; ++iStep ) {
    double c1Pt  = TMath::Exp(rnd_.Gaus(log_cSumPt_over_2, 1.)); // CV: draw pT from log-normal distribution
    double c1Phi = rnd_.Uniform(-TMath::Pi(), +TMath::Pi());     // CV: draw phi from uniform distribution

    minimizer_->SetLimitedVariable(0, "c1Pt",  c1Pt,  1.e-2*c1Pt,      0.,           1.e+1*c1Pt);
    minimizer_->SetLimitedVariable(1, "c1Phi", c1Phi, 1.e-1,      -TMath::Pi(), +TMath::Pi());  
    minimizer_->Minimize();

    double mT2 = minimizer_->MinValue();
    if ( mT2 < min_mT2_ || min_step_ == -1 ) {
      min_mT2_ = mT2;
      min_step_ = iStep;
    }
  }
}
  
double mT2_3particle::get_min_mT2() const
{
  return min_mT2_;
}
 
int mT2_3particle::get_min_step() const
{
  return min_step_;
}
