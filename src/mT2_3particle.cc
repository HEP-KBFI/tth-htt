#include "tthAnalysis/HiggsToTauTau/interface/mT2_3particle.h"

#include <Math/Factory.h>
#include <TMath.h> // TMath::Pi()

mT2_3particle::mT2_3particle(int numSteps)
  : minimizer_(ROOT::Math::Factory::CreateMinimizer("Minuit2", ""))
  , mT2Functor_(new mT2_3particle_namespace::mt2Functor_3particle())
  , f_(new ROOT::Math::Functor(*mT2Functor_, 2))
  , numSteps_(numSteps)
  , min_mT2_(1.e+6)
  , min_step_(-1)
{
  minimizer_->SetFunction(*f_);
  minimizer_->SetPrintLevel(-1);
}

mT2_3particle::~mT2_3particle()
{
  delete minimizer_;
  delete f_;
  delete mT2Functor_;
}

void
mT2_3particle::operator()(double a1Px,   double a1Py,   double a1Mass,
                          double a2Px,   double a2Py,   double a2Mass,
                          double b1Px,   double b1Py,   double b1Mass,
                          double b2Px,   double b2Py,   double b2Mass,
                          double cSumPx, double cSumPy, double cMass)
{
  const auto currentIgnoreLevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

  const double cSumPt = std::sqrt(cSumPx*cSumPx + cSumPy*cSumPy);
  const double log_cSumPt_over_2 = std::log(0.5*TMath::Max(1., cSumPt));

  min_mT2_ = 1.e+6;
  min_step_ = -1;
  for(int iStep = 0; iStep < numSteps_; ++iStep )
  {
    const double c1Pt  = std::exp(rnd_.Gaus(log_cSumPt_over_2, 1.)); // CV: draw pT from log-normal distribution
    const double c1Phi = rnd_.Uniform(-TMath::Pi(), +TMath::Pi());   // CV: draw phi from uniform distribution

    minimizer_->SetLimitedVariable(0, "c1Pt",    c1Pt,  1.e-2*c1Pt,      0.,       1.e+1*c1Pt);
    minimizer_->SetLimitedVariable(1, "c1Phi",   c1Phi, 1.e-1,      -TMath::Pi(), +TMath::Pi());
    minimizer_->SetFixedVariable(  2, "a1Px",    a1Px);
    minimizer_->SetFixedVariable(  3, "a1Py",    a1Py);
    minimizer_->SetFixedVariable(  4, "a1Mass",  a1Mass);
    minimizer_->SetFixedVariable(  5, "a2Px",    a2Px);
    minimizer_->SetFixedVariable(  6, "a2Py",    a2Py);
    minimizer_->SetFixedVariable(  7, "a2Mass",  a2Mass);
    minimizer_->SetFixedVariable(  8, "b1Px",    b1Px);
    minimizer_->SetFixedVariable(  9, "b1Py",    b1Py);
    minimizer_->SetFixedVariable( 10, "b1Mass",  b1Mass);
    minimizer_->SetFixedVariable( 11, "b2Px",    b2Px);
    minimizer_->SetFixedVariable( 12, "b2Py",    b2Py);
    minimizer_->SetFixedVariable( 13, "b2Mass",  b2Mass);
    minimizer_->SetFixedVariable( 14, "cSumPx_", cSumPx);
    minimizer_->SetFixedVariable( 15, "cSumPy",  cSumPy);
    minimizer_->SetFixedVariable( 16, "cMass",   cMass);
    minimizer_->Minimize();

    const double mT2 = minimizer_->MinValue();
    if(mT2 < min_mT2_ || min_step_ == -1)
    {
      min_mT2_ = mT2;
      min_step_ = iStep;
    }
  }

  gErrorIgnoreLevel = currentIgnoreLevel;
}
  
double
mT2_3particle::get_min_mT2() const
{
  return min_mT2_;
}
 
int
mT2_3particle::get_min_step() const
{
  return min_step_;
}

double
mT2_3particle::comp_mT(double aPx, double aPy, double aMass,
                       double bPx, double bPy, double bMass,
                       double cPx, double cPy, double cMass)
{
  const double aMass2 = aMass * aMass;
  const double aET = std::sqrt(aMass2 + aPx * aPx + aPy * aPy);
  const double bMass2 = bMass * bMass;
  const double bET = std::sqrt(bMass2 + bPx * bPx + bPy * bPy);
  const double cMass2 = cMass * cMass;
  const double cET = std::sqrt(cMass2 + cPx * cPx + cPy * cPy);
  const double mT2 = aMass2 + bMass2 + cMass2 +
    2. * (aET * bET - (aPx * bPx + aPy * bPy)) +
    2. * (aET * cET - (aPx * cPx + aPy * cPy)) +
    2. * (bET * cET - (bPx * cPx + bPy * cPy))
  ;
  return mT2;
}
