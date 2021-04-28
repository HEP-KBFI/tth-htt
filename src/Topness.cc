#include "tthAnalysis/HiggsToTauTau/interface/Topness.h" // Topness

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"

#include <Math/Factory.h> // ROOT::Math::Factory
#include <Math/Functor.h> // ROOT::Math::Functor

#include <TError.h> // gErrorIgnoreLevel, kWarning

using namespace topness;

/// global pointer for interface to MINUIT
const Topness* Topness::gTopness = nullptr;

/// define mass of top quark and of W boson 
/// (taken from "The review of particle physics", M. Tanabashi et al. (Particle Data Group), Phys. Rev. D 98, 030001 (2018))
const double mTop = 173.1; // GeV
const double mW = 80.379; // GeV

double ObjectiveFunctionAdapterMINUIT::operator()(const double* x) const 
{
  double chi2 = Topness::gTopness->operator()(x);
  return chi2;
}

Topness::Topness(modeType mode, int maxObjFunctionCalls)
  : mode_(mode)
  , sigmaTop_(5.)
  , sigmaW_(5.)
  , numObjFunctionCalls_(0)
  , minimizer_(ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad"))
  , maxObjFunctionCalls_(maxObjFunctionCalls)
  , fitStatus_(-1)
  , logTopness_(1.e+3)
  , numPermutations_(2)
{
  if(! (mode_ == kPublishedChi2 || mode_ == kFixedChi2))
  {
    throw cmsException(this, __func__, __LINE__)
      << "Invalid Configuration parameter 'mode' = " << mode_
    ;
  }
  chi2_of_permutation_ = new double[numPermutations_];
  fitStatus_of_permutation_ = new int[numPermutations_];

//--- set verbosity level of minimizer
//      -1 quiet (also suppresses all warnings)
//       0 normal
//       1 verbose
  minimizer_->SetPrintLevel(-1);
}

Topness::~Topness()
{
  delete minimizer_;
  delete [] chi2_of_permutation_;
  delete [] fitStatus_of_permutation_;
}

void
Topness::set_sigmaW(double sigmaW)
{ 
  assert(sigmaW > 0.);
  sigmaW_ = sigmaW; 
}

void
Topness::set_sigmaTop(double sigmaTop)
{ 
  assert(sigmaTop > 0.);
  sigmaTop_ = sigmaTop; 
}
  
namespace
{
  double
  compMassTop(const Particle::LorentzVector & leptonP4,
              const Particle::LorentzVector & bjetP4,
              double nuPx,
              double nuPy,
              double nuPz,
              double nuE)
  {
    const double leptonPx = leptonP4.px();
    const double leptonPy = leptonP4.py();
    const double leptonPz = leptonP4.pz();
    const double leptonE  = leptonP4.energy();

    const double bjetPx   = bjetP4.px();
    const double bjetPy   = bjetP4.py();
    const double bjetPz   = bjetP4.pz();
    const double bjetE    = bjetP4.energy();

    const double topPx    = bjetPx + leptonPx + nuPx;
    const double topPy    = bjetPy + leptonPy + nuPy;
    const double topPz    = bjetPz + leptonPz + nuPz;
    const double topE     = bjetE  + leptonE  + nuE;
    const double topMass2 = std::max(topE*topE - (topPx * topPx + topPy * topPy + topPz * topPz), 0.);
    const double topMass = std::sqrt(topMass2);

    return topMass;
  }

  double
  compMassW(const Particle::LorentzVector & leptonP4,
            double nuPx,
            double nuPy,
            double nuPz,
            double nuE)
  {
    const double leptonPx = leptonP4.px();
    const double leptonPy = leptonP4.py();
    const double leptonPz = leptonP4.pz();
    const double leptonE  = leptonP4.energy();

    const double wPx    = leptonPx + nuPx;
    const double wPy    = leptonPy + nuPy;
    const double wPz    = leptonPz + nuPz;
    const double wE     = leptonE  + nuE;
    const double wMass2 = std::max(wE*wE - (wPx * wPx + wPy * wPy + wPz * wPz), 0.);
    const double wMass = std::sqrt(wMass2);

    return wMass;
  }

  double
  square(double x)
  {
    return x * x;
  }
}

double
Topness::operator()(const double * x) const
{
  if(numObjFunctionCalls_ > maxObjFunctionCalls_)
  {
    return -1.;
  }
  if ( std::isnan(x[0]) ||
       std::isnan(x[1]) ||
       std::isnan(x[2]) ||
       std::isnan(x[3]) )
    {
      return 1.e+6;
    }
  const double nu1Px = x[0];
  const double nu1Py = x[1];
  const double nu1Pz = x[2];
  const double nu1E  = std::sqrt(nu1Px * nu1Px + nu1Py * nu1Py + nu1Pz * nu1Pz);

  const double massTop1 = compMassTop(lepton1P4_, bjet1P4_, nu1Px, nu1Py, nu1Pz, nu1E);
  const double massW1 = compMassW(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E);

  const double nu2Px = metPx_ - nu1Px;
  const double nu2Py = metPy_ - nu1Py;
  const double nu2Pz = x[3];
  const double nu2E  = std::sqrt(nu2Px * nu2Px + nu2Py * nu2Py + nu2Pz * nu2Pz);

  const double massTop2 = compMassTop(lepton2P4_, bjet2P4_, nu2Px, nu2Py, nu2Pz, nu2E);
  const double massW2 = compMassW(lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);
  
  double chi2 = -1.;
  if(mode_ == kPublishedChi2)
  {
    chi2 = square((square(massTop1) - square(mTop)) / square(sigmaTop_)) +
           square((square(massW1)   - square(mW))   / square(sigmaW_))   +
           square((square(massTop2) - square(mTop)) / square(sigmaTop_)) +
           square((square(massW2)   - square(mW))   / square(sigmaW_))
    ;
  }
  else if(mode_ == kFixedChi2)
  {
    chi2 = square((massTop1 - mTop) / sigmaTop_) + square((massW1 - mW) / sigmaW_) +
           square((massTop2 - mTop) / sigmaTop_) + square((massW2 - mW) / sigmaW_);
  }
  else
  {
    assert(0);
  }

  assert(! std::isnan(chi2));

  ++numObjFunctionCalls_;

  return chi2;
}

void
Topness::fit(const Particle::LorentzVector& lepton1P4,
             const Particle::LorentzVector& lepton2P4,
             const Particle::LorentzVector& bjet1P4,
             const Particle::LorentzVector& bjet2P4,
             double metPx,
             double metPy)
{
  const auto currentIgnoreLevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

//--- clear minimizer
  minimizer_->Clear();

  for ( int idxPermutation = 0; idxPermutation < numPermutations_; ++idxPermutation ) {

//--- set reconstructed momenta
    if(idxPermutation == 0)
    {
      lepton1P4_ = lepton1P4; 
      lepton2P4_ = lepton2P4; 
    }
    else if(idxPermutation == 1)
    {
      lepton1P4_ = lepton2P4; 
      lepton2P4_ = lepton1P4; 
    }
    else
    {
      assert(0);
    }
    bjet1P4_ = bjet1P4;
    bjet2P4_ = bjet2P4;
    metPx_   = metPx;
    metPy_   = metPy;
    
//--- set interface to MINUIT
    const ROOT::Math::Functor toMinimize(objectiveFunctionAdapterMINUIT_, 4);
    minimizer_->SetFunction(toMinimize); 
    minimizer_->SetLimitedVariable(0, "Nu1Px", 0., 0.1, -5.e+3, +5.e+3);
    minimizer_->SetLimitedVariable(1, "Nu1Py", 0., 0.1, -5.e+3, +5.e+3);
    minimizer_->SetLimitedVariable(2, "Nu1Pz", 0., 0.1, -5.e+3, +5.e+3);
    minimizer_->SetLimitedVariable(3, "Nu2Pz", 0., 0.1, -5.e+3, +5.e+3);
    minimizer_->SetMaxFunctionCalls(maxObjFunctionCalls_);
    minimizer_->SetErrorDef(0.5);
  
//--- set MINUIT strategy = 2, in order to get reliable error estimates:
//     http://www-cdf.fnal.gov/physics/statistics/recommendations/minuit.html
    minimizer_->SetStrategy(2);

//--- do the minimization  
    numObjFunctionCalls_ = 0;
    gTopness = this;
    minimizer_->Minimize();
    
//--- get Minimizer status code, check if solution is valid:
//       0: Valid solution
//       1: Covariance matrix was made positive definite
//       2: Hesse matrix is invalid
//       3: Estimated distance to minimum (EDM) is above maximum
//       4: Reached maximum number of function calls before reaching convergence
//       5: Any other failure
    fitStatus_of_permutation_[idxPermutation] = minimizer_->Status();

    const double minValue = minimizer_->MinValue();
    if(fitStatus_of_permutation_[idxPermutation] == 0 && !std::isnan(minValue))
    {
      chi2_of_permutation_[idxPermutation] = minValue;
    }
    else
    {
      chi2_of_permutation_[idxPermutation] = 1.e+3;
    }
  }

  fitStatus_ = std::min(fitStatus_of_permutation_[0], fitStatus_of_permutation_[1]);
  double minChi2 = -1.;
  for(int idxPermutation = 0; idxPermutation < numPermutations_; ++idxPermutation)
  {
    if(fitStatus_of_permutation_[idxPermutation] == 0 &&
       (chi2_of_permutation_[idxPermutation] < minChi2 || minChi2 == -1.))
    {
      minChi2 = chi2_of_permutation_[idxPermutation];
    }
  }

  if(fitStatus_ == 0 && minChi2 > 0.)
  {
    logTopness_ = std::log10(minChi2);
  }
  else
  {
    logTopness_ = 1.e+3;
  }

  gErrorIgnoreLevel = currentIgnoreLevel;
}

bool
Topness::isValidSolution() const
{
  return fitStatus_ == 0;
}

double Topness::logTopness() const
{
  return logTopness_;
}
