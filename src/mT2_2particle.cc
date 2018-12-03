#include "tthAnalysis/HiggsToTauTau/interface/mT2_2particle.h"

#include "Math/Factory.h"

mT2_2particle::mT2_2particle(int numSteps)
  : minimizer_(nullptr)
  , mT2Functor_(nullptr)
  , f_(nullptr)
  , numSteps_(numSteps)
  , min_mT2_(1.e+6)
  , min_step_(-1)
{
  mT2Functor_ = new mT2_2particle_namespace::mt2Functor_2particle();
  f_ = new ROOT::Math::Functor(*mT2Functor_, 2);
  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "");
  minimizer_->SetFunction(*f_);
  minimizer_->SetPrintLevel(-1);
}

mT2_2particle::~mT2_2particle()
{
  delete minimizer_;
  delete f_;
  delete mT2Functor_;
}

void mT2_2particle::operator()(double b1Px, double b1Py, double b1Mass,
                               double b2Px, double b2Py, double b2Mass,
                               double cSumPx, double cSumPy, double cMass)
{
  const auto currentIgnoreLevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

  double cSumPt = TMath::Sqrt(cSumPx*cSumPx + cSumPy*cSumPy);
  double log_cSumPt_over_2 = TMath::Log(0.5*TMath::Max(1., cSumPt));

  min_mT2_ = 1.e+6;
  min_step_ = -1;
  for ( int iStep = 0; iStep < numSteps_; ++iStep ) {
    double c1Pt  = TMath::Exp(rnd_.Gaus(log_cSumPt_over_2, 1.)); // CV: draw pT from log-normal distribution
    double c1Phi = rnd_.Uniform(-TMath::Pi(), +TMath::Pi());     // CV: draw phi from uniform distribution

    minimizer_->SetLimitedVariable(0, "c1Pt",    c1Pt,  1.e-2*c1Pt,      0.,           1.e+1*c1Pt);
    minimizer_->SetLimitedVariable(1, "c1Phi",   c1Phi, 1.e-1,      -TMath::Pi(), +TMath::Pi());  
    minimizer_->SetFixedVariable(  2, "b1Px",    b1Px);
    minimizer_->SetFixedVariable(  3, "b1Py",    b1Py);
    minimizer_->SetFixedVariable(  4, "b1Mass",  b1Mass);
    minimizer_->SetFixedVariable(  5, "b2Px",    b2Px);
    minimizer_->SetFixedVariable(  6, "b2Py",    b2Py);
    minimizer_->SetFixedVariable(  7, "b2Mass",  b2Mass);
    minimizer_->SetFixedVariable(  8, "cSumPx_", cSumPx);
    minimizer_->SetFixedVariable(  9, "cSumPy",  cSumPy);
    minimizer_->SetFixedVariable( 10, "cMass",   cMass);
    minimizer_->Minimize();

    double mT2 = minimizer_->MinValue();
    //std::cout << "step #" << iStep << ": mT2 = " << mT2 << std::endl;
    if ( mT2 < min_mT2_ || min_step_ == -1 ) {
      min_mT2_ = mT2;
      min_step_ = iStep;
    }
  }

  gErrorIgnoreLevel = currentIgnoreLevel;
}
  
double mT2_2particle::get_min_mT2() const
{
  return min_mT2_;
}
 
int mT2_2particle::get_min_step() const
{
  return min_step_;
}

double mT2_2particle::comp_mT(double bPx, double bPy, double bMass, double cPx, double cPy, double cMass)
{
  double bMass2 = bMass*bMass;
  double bET = TMath::Sqrt(bMass2 + bPx*bPx + bPy*bPy);
  double cMass2 = cMass*cMass;
  double cET = TMath::Sqrt(cMass2 + cPx*cPx + cPy*cPy);
  double mT2 = bMass2 + cMass2 + 2.*(bET*cET - (bPx*cPx + bPy*cPy));
  return mT2;
}
