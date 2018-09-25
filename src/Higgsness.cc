#include "tthAnalysis/HiggsToTauTau/interface/Higgsness.h" // Higgsness

#include <Math/Factory.h> // ROOT::Math::Factory
#include <Math/Functor.h> // ROOT::Math::Functor
#include <TMath.h> // TMath::Sqrt, TMath::Min(), TMath::Max(), TMath::IsNaN()

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

Higgsness::Higgsness(int maxObjFunctionCalls)
  : sigmaW_onshell_(5.)
  , sigmaW_offshell_(5.)
  , sigmaH_lep_(5.)
  , minimizer_(ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad"))
  , maxObjFunctionCalls_(maxObjFunctionCalls)
  , fitStatus_(-1)
  , logHiggsness_(1.e+3)
{}

Higgsness::~Higgsness()
{
  delete minimizer_;
}

void Higgsness::set_sigmaW_onshell(double sigmaW_onshell) 
{ 
  assert(sigmaW_onshell > 0.);
  sigmaW_onshell_ = sigmaW_onshell; 
}

void Higgsness::set_sigmaW_offshell(double sigmaW_offshell) 
{ 
  assert(sigmaW_offshell > 0.);
  sigmaW_offshell_ = sigmaW_offshell; 
}

void Higgsness::set_sigmaH_lep(double sigmaH_lep) 
{ 
  assert(sigmaH_lep > 0.);
  sigmaH_lep_ = sigmaH_lep; 
}
  
namespace
{
  double compMassHiggs_lep(const Particle::LorentzVector& lepton1P4,
			   double nu1Px, double nu1Py, double nu1Pz, double nu1E,
			   const Particle::LorentzVector& lepton2P4,
			   double nu2Px, double nu2Py, double nu2Pz, double nu2E)
  {
    double lepton1Px = lepton1P4.px();
    double lepton1Py = lepton1P4.py();
    double lepton1Pz = lepton1P4.pz();
    double lepton1E  = lepton1P4.energy();

    double lepton2Px = lepton2P4.px();
    double lepton2Py = lepton2P4.py();
    double lepton2Pz = lepton2P4.pz();
    double lepton2E  = lepton2P4.energy();

    double higgsPx   = lepton1Px + nu1Px + lepton2Px + nu2Px;
    double higgsPy   = lepton1Py + nu1Py + lepton2Py + nu2Py;
    double higgsPz   = lepton1Pz + nu1Pz + lepton2Pz + nu2Pz;
    double higgsE    = lepton1E  + nu1E  + lepton2E  + nu2E;
    double higgsMass2 = higgsE*higgsE - (higgsPx*higgsPx + higgsPy*higgsPy + higgsPz*higgsPz);
    if ( higgsMass2 < 0. ) higgsMass2 = 0.;
    double higgsMass = TMath::Sqrt(higgsMass2);

    return higgsMass;
  }

  double compMassW(const Particle::LorentzVector& leptonP4,
		   double nuPx, double nuPy, double nuPz, double nuE)
  {
    double leptonPx = leptonP4.px();
    double leptonPy = leptonP4.py();
    double leptonPz = leptonP4.pz();
    double leptonE  = leptonP4.energy();

    double wPx    = leptonPx + nuPx;
    double wPy    = leptonPy + nuPy;
    double wPz    = leptonPz + nuPz;
    double wE     = leptonE  + nuE;
    double wMass2 = wE*wE - (wPx*wPx + wPy*wPy + wPz*wPz);
    if ( wMass2 < 0. ) wMass2 = 0.;
    double wMass = TMath::Sqrt(wMass2);

    return wMass;
  }

  double square(double x)
  {
    return x*x;
  }
}

double Higgsness::operator()(const double* x) const
{
  if ( numObjFunctionCalls_ > maxObjFunctionCalls_ ) {
    return -1.;
  }
  
  double nu1Px = x[0];
  double nu1Py = x[1];
  double nu1Pz = x[2];
  double nu1E  = TMath::Sqrt(nu1Px*nu1Px + nu1Py*nu1Py + nu1Pz*nu1Pz);

  double nu2Px = metPx_ - nu1Px;
  double nu2Py = metPx_ - nu1Py;
  double nu2Pz = x[3];
  double nu2E  = TMath::Sqrt(nu2Px*nu2Px + nu2Py*nu2Py + nu2Pz*nu2Pz);

  double massH_lep = compMassHiggs_lep(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E, lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);

  double massW_onshell = compMassW(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E);
  double massW_offshell = compMassW(lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);

  double chi2 = square((massH_lep - mH)/sigmaH_lep_) 
    + square((massW_onshell - mW)/sigmaW_onshell_) + square((massW_offshell - mW_offshell)/sigmaW_offshell_);
  assert(!TMath::IsNaN(chi2));

  ++numObjFunctionCalls_;

  return chi2;
}

void Higgsness::fit(const Particle::LorentzVector& lepton1P4,
		    const Particle::LorentzVector& lepton2P4,
		    double metPx, double metPy)
{
//--- clear minimizer
  minimizer_->Clear();

//--- set verbosity level of minimizer
//      -1 quiet (also suppresses all warnings)
//       0 normal
//       1 verbose
  minimizer_->SetPrintLevel(-1);

  const int numPermutations = 2;
  double chi2[numPermutations];
  int fitStatus[numPermutations];
  for ( int idxPermutation = 0; idxPermutation < numPermutations; ++idxPermutation ) {

//--- set reconstructed momenta
    if        ( idxPermutation == 0 ) {
      lepton1P4_ = lepton1P4; // lepton of higher pT is interpreted as coming from the on-shell W,
      lepton2P4_ = lepton2P4; // lepton of lower pT is interpreted as coming from the off-shell W*
    } else if ( idxPermutation == 1 ) {
      lepton1P4_ = lepton2P4; // lepton of lower pT is interpreted as coming from the on-shell W,
      lepton2P4_ = lepton1P4; // lepton of higher pT is interpreted as coming from the off-shell W*
    } else assert(0);
    metPx_       = metPx;
    metPy_       = metPy;
    
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
    minimizer_->Minimize();
    
//--- get Minimizer status code, check if solution is valid:
//       0: Valid solution
//       1: Covariance matrix was made positive definite
//       2: Hesse matrix is invalid
//       3: Estimated distance to minimum (EDM) is above maximum
//       4: Reached maximum number of function calls before reaching convergence
//       5: Any other failure
    fitStatus_ = minimizer_->Status();

    double minValue = minimizer_->MinValue();
    if ( fitStatus[idxPermutation] == 0 && !TMath::IsNaN(minValue) ) {
      chi2[idxPermutation] = minValue;
    } else {
      chi2[idxPermutation] = 1.e+3;
    }
  }
  
  double minChi2 = TMath::Min(chi2[0], chi2[1]);
  if ( minChi2 < 1.e-3 ) minChi2 = 1.e-3;
  fitStatus_ = TMath::Max(fitStatus[0], fitStatus[1]);
  if ( minChi2 >= 0. && fitStatus_ == 0 ) {
    logHiggsness_ = TMath::Log10(minChi2);
  } else {
    logHiggsness_ = 1.e+3;
  }
}

bool Higgsness::isValidSolution() const
{
  return ( fitStatus_ == 0 ) ? true : false;
}

double Higgsness::logHiggsness() const
{
  return logHiggsness_;
}
