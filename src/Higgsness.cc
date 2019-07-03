#include "tthAnalysis/HiggsToTauTau/interface/Higgsness.h" // Higgsness

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <Math/Factory.h> // ROOT::Math::Factory
#include <Math/Functor.h> // ROOT::Math::Functor

#include <TError.h> // gErrorIgnoreLevel, kWarning

using namespace higgsness;

/// global pointer for interface to MINUIT
const Higgsness* Higgsness::gHiggsness = nullptr;

/// define mass of top quark, W boson and Higgs boson 
/// (taken from "The review of particle physics", M. Tanabashi et al. (Particle Data Group), Phys. Rev. D 98, 030001 (2018))
const double mTop = 173.1; // GeV
const double mW = 80.379; // GeV
const double mH = 125.09; // GeV

/// define peak of off-shell W* ~ mH - mW
const double mW_offshell = 30.; // GeV

double ObjectiveFunctionAdapterMINUIT::operator()(const double* x) const 
{
  double chi2 = Higgsness::gHiggsness->operator()(x);
  return chi2;
}

Higgsness::Higgsness(modeType mode, int maxObjFunctionCalls)
  : mode_(mode)
  , sigmaW_onshell_(5.)
  , sigmaW_offshell_(5.)
  , sigmaH_lep_(2.)
  , numObjFunctionCalls_(0)
  , minimizer_(ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad"))
  , maxObjFunctionCalls_(maxObjFunctionCalls)
  , fitStatus_(-1)
  , logHiggsness_(1.e+3)
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

Higgsness::~Higgsness()
{
  delete minimizer_;
  delete [] chi2_of_permutation_;
  delete [] fitStatus_of_permutation_;
}

void
Higgsness::set_sigmaW_onshell(double sigmaW_onshell)
{ 
  assert(sigmaW_onshell > 0.);
  sigmaW_onshell_ = sigmaW_onshell; 
}

void
Higgsness::set_sigmaW_offshell(double sigmaW_offshell)
{ 
  assert(sigmaW_offshell > 0.);
  sigmaW_offshell_ = sigmaW_offshell; 
}

void
Higgsness::set_sigmaH_lep(double sigmaH_lep)
{ 
  assert(sigmaH_lep > 0.);
  sigmaH_lep_ = sigmaH_lep; 
}
  
namespace
{
  double
  compMassHiggs_lep(const Particle::LorentzVector & lepton1P4,
                    double nu1Px,
                    double nu1Py,
                    double nu1Pz,
                    double nu1E,
                    const Particle::LorentzVector & lepton2P4,
                    double nu2Px,
                    double nu2Py,
                    double nu2Pz,
                    double nu2E)
  {
    const double lepton1Px = lepton1P4.px();
    const double lepton1Py = lepton1P4.py();
    const double lepton1Pz = lepton1P4.pz();
    const double lepton1E  = lepton1P4.energy();

    const double lepton2Px = lepton2P4.px();
    const double lepton2Py = lepton2P4.py();
    const double lepton2Pz = lepton2P4.pz();
    const double lepton2E  = lepton2P4.energy();

    const double higgsPx   = lepton1Px + nu1Px + lepton2Px + nu2Px;
    const double higgsPy   = lepton1Py + nu1Py + lepton2Py + nu2Py;
    const double higgsPz   = lepton1Pz + nu1Pz + lepton2Pz + nu2Pz;
    const double higgsE    = lepton1E  + nu1E  + lepton2E  + nu2E;
    const double higgsMass2 = std::max(higgsE * higgsE - (higgsPx * higgsPx + higgsPy * higgsPy + higgsPz * higgsPz), 0.);
    const double higgsMass  = std::sqrt(higgsMass2);

    return higgsMass;
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
    const double wMass2 = std::max(wE*wE - (wPx*wPx + wPy*wPy + wPz*wPz), 0.);
    const double wMass = std::sqrt(wMass2);

    return wMass;
  }

  double square(double x)
  {
    return x * x;
  }
}

double
Higgsness::operator()(const double * x) const
{
  if(numObjFunctionCalls_ > maxObjFunctionCalls_)
  {
    return -1.;
  }

  const double nu1Px = x[0];
  const double nu1Py = x[1];
  const double nu1Pz = x[2];
  const double nu1E  = std::sqrt(nu1Px * nu1Px + nu1Py * nu1Py + nu1Pz * nu1Pz);

  const double nu2Px = metPx_ - nu1Px;
  const double nu2Py = metPy_ - nu1Py;
  const double nu2Pz = x[3];
  const double nu2E  = std::sqrt(nu2Px * nu2Px + nu2Py * nu2Py + nu2Pz * nu2Pz);

  const double massH_lep = compMassHiggs_lep(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E, lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);

  const double massW_onshell  = compMassW(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E);
  const double massW_offshell = compMassW(lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);

  double chi2 = -1.;
  if(mode_ == kPublishedChi2)
  {
    chi2 = square((square(massH_lep)      - square(mH))          / square(sigmaH_lep_))     +
           square((square(massW_onshell)  - square(mW))          / square(sigmaW_onshell_)) +
           square((square(massW_offshell) - square(mW_offshell)) / square(sigmaW_offshell_))
    ;
  }
  else if(mode_ == kFixedChi2)
  {
    chi2 = square((massH_lep      - mH)          / sigmaH_lep_)     +
           square((massW_onshell  - mW)          / sigmaW_onshell_) +
           square((massW_offshell - mW_offshell) / sigmaW_offshell_)
    ;
  }
  else
  {
    assert(0);
  }
  assert(! std::isnan(chi2));
  ++numObjFunctionCalls_;

  return chi2;
}

void Higgsness::fit(const Particle::LorentzVector& lepton1P4,
                    const Particle::LorentzVector& lepton2P4,
                    double metPx, double metPy)
{
  const auto currentIgnoreLevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kWarning;

//--- clear minimizer
  minimizer_->Clear();

  for(int idxPermutation = 0; idxPermutation < numPermutations_; ++idxPermutation)
  {
//--- set reconstructed momenta
    if(idxPermutation == 0)
    {
      lepton1P4_ = lepton1P4; // lepton of higher pT is interpreted as coming from the on-shell W,
      lepton2P4_ = lepton2P4; // lepton of lower pT is interpreted as coming from the off-shell W*
    }
    else if(idxPermutation == 1)
    {
      lepton1P4_ = lepton2P4; // lepton of lower pT is interpreted as coming from the on-shell W,
      lepton2P4_ = lepton1P4; // lepton of higher pT is interpreted as coming from the off-shell W*
    }
    else
    {
      assert(0);
    }
    metPx_ = metPx;
    metPy_ = metPy;
    
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
    gHiggsness = this;
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
    if(fitStatus_of_permutation_[idxPermutation] == 0 && ! std::isnan(minValue))
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
    logHiggsness_ = std::log10(minChi2);
  }
  else
  {
    logHiggsness_ = 1.e+3;
  }

  gErrorIgnoreLevel = currentIgnoreLevel;
}

bool Higgsness::isValidSolution() const
{
  return fitStatus_ == 0;
}

double Higgsness::logHiggsness() const
{
  return logHiggsness_;
}
