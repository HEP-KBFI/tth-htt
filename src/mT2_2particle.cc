#include "tthAnalysis/HiggsToTauTau/interface/mT2_2particle.h"

#include "Math/Factory.h"

mT2_2particle::mT2_2particle(int numSteps)
  : minimizer_(nullptr)
  , f_(nullptr)
  , numSteps_(numSteps)
{
  f_ = new ROOT::Math::Functor(mT2Functor_, 2);
  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "");
  minimizer_->SetFunction(*f_);
}

mT2_2particle::~mT2_2particle()
{
  delete minimizer_;
  delete f_;
}

std::pair<double, int> mT2_2particle::operator()(double b1Px, double b1Py, double b1Mass, 
						 double b2Px, double b2Py, double b2Mass,
						 double cSumPx, double cSumPy, double cMass)
{
  mT2Functor_.set_b1(b1Px, b1Py, b1Mass);
  mT2Functor_.set_b2(b2Px, b2Py, b2Mass);
  mT2Functor_.set_cSum(cSumPx, cSumPy, cMass);

  double cSumPt = TMath::Sqrt(cSumPx*cSumPx + cSumPy*cSumPy);
  double log_cSumPt_over_2 = TMath::Log(0.5*TMath::Max(1., cSumPt));

  double min_mT2 = 1.e+6;
  int min_step = -1;
  for ( int iStep = 0; iStep < numSteps_; ++iStep ) {
    double c1Pt  = TMath::Exp(rnd_.Gaus(log_cSumPt_over_2, 1.)); // CV: draw pT from log-normal distribution
    double c1Phi = rnd_.Uniform(-TMath::Pi(), +TMath::Pi());     // CV: draw phi from uniform distribution

    minimizer_->SetLimitedVariable(0, "c1Pt",  c1Pt,  1.e-2*c1Pt,      0.,           1.e+1*c1Pt);
    minimizer_->SetLimitedVariable(1, "c1Phi", c1Phi, 1.e-1,      -TMath::Pi(), +TMath::Pi());  
    minimizer_->Minimize();

    double mT2 = minimizer_->MinValue();
    if ( mT2 < min_mT2 || min_step == -1 ) {
      min_mT2 = mT2;
      min_step = iStep;
    }
  }
  return std::pair<double, int>(min_mT2, min_step);
}
  
