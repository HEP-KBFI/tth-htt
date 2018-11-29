#include "tthAnalysis/HiggsToTauTau/interface/Higgsness.h" // Higgsness

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

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
  if ( !(mode_ == kPublishedChi2 || mode_ == kFixedChi2) ) {
    throw cms::Exception("Higgsness")
      << "Invalid Configuration parameter 'mode' = " << mode_ << " !!\n";
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
  //std::cout << "<Higgsness::operator() @ objFunctionCall #" << numObjFunctionCalls_ << ">" << std::endl;
  //for ( int i = 0; i < 4; ++i ) {
  //  std::cout << " x[" << i << "] = " << x[i] << std::endl;
  //}

  if ( numObjFunctionCalls_ > maxObjFunctionCalls_ ) {
    return -1.;
  }

  double nu1Px = x[0];
  double nu1Py = x[1];
  double nu1Pz = x[2];
  double nu1E  = TMath::Sqrt(nu1Px*nu1Px + nu1Py*nu1Py + nu1Pz*nu1Pz);

  double nu2Px = metPx_ - nu1Px;
  double nu2Py = metPy_ - nu1Py;
  double nu2Pz = x[3];
  double nu2E  = TMath::Sqrt(nu2Px*nu2Px + nu2Py*nu2Py + nu2Pz*nu2Pz);

  double massH_lep = compMassHiggs_lep(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E, lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);
  //std::cout << "massH = " << massH_lep << std::endl;  

  //std::cout << " deltaLLNN = " << (square(massH_lep) - square(mH))/square(sigmaH_lep_) << std::endl;

  double massW_onshell = compMassW(lepton1P4_, nu1Px, nu1Py, nu1Pz, nu1E);
  double massW_offshell = compMassW(lepton2P4_, nu2Px, nu2Py, nu2Pz, nu2E);
  //std::cout << "massW: onshell = " << massW_onshell << ", offshell = " << massW_offshell << std::endl;  

  //std::cout << " deltaLN11on = " << (square(massW_onshell) - square(mW))/square(sigmaW_onshell_)  << "," 
  //              << " deltaLN22off = " << (square(massW_offshell) - square(mW_offshell))/square(sigmaW_offshell_) << std::endl;

  double chi2 = -1.;
  if ( mode_ == kPublishedChi2 ) {
    chi2 = square((square(massH_lep) - square(mH))/square(sigmaH_lep_)) 
      + square((square(massW_onshell) - square(mW))/square(sigmaW_onshell_)) + square((square(massW_offshell) - square(mW_offshell))/square(sigmaW_offshell_));
  } else if ( mode_ == kFixedChi2 ) {
    chi2 = square((massH_lep - mH)/sigmaH_lep_) 
      + square((massW_onshell - mW)/sigmaW_onshell_) + square((massW_offshell - mW_offshell)/sigmaW_offshell_);
  } else assert(0);
  //std::cout << "chi^2 = " << chi2 << std::endl;
  assert(!TMath::IsNaN(chi2));
  
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

  for ( int idxPermutation = 0; idxPermutation < numPermutations_; ++idxPermutation ) {

    //if ( idxPermutation != 0 ) continue; // only for testing !!

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
    ROOT::Math::Functor toMinimize(objectiveFunctionAdapterMINUIT_, 4);
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

    double minValue = minimizer_->MinValue();
    //std::cout << "permutation #" << idxPermutation << ": fitStatus = " << fitStatus_of_permutation_[idxPermutation] << ", min(chi^2) = " << minValue << std::endl;    
    if ( fitStatus_of_permutation_[idxPermutation] == 0 && !TMath::IsNaN(minValue) ) {
      chi2_of_permutation_[idxPermutation] = minValue;
    } else {
      chi2_of_permutation_[idxPermutation] = 1.e+3;
    }
  }

  fitStatus_ = TMath::Min(fitStatus_of_permutation_[0], fitStatus_of_permutation_[1]);
  double minChi2 = -1.;
  for ( int idxPermutation = 0; idxPermutation < numPermutations_; ++idxPermutation ) {
    if ( fitStatus_of_permutation_[idxPermutation] == 0 && (chi2_of_permutation_[idxPermutation] < minChi2 || minChi2 == -1.) ) {
      minChi2 = chi2_of_permutation_[idxPermutation];
    }
  }
  if ( fitStatus_ == 0 && minChi2 > 0. ) {
    logHiggsness_ = TMath::Log10(minChi2);
  } else {
    logHiggsness_ = 1.e+3;
  }

  gErrorIgnoreLevel = currentIgnoreLevel;
}

bool Higgsness::isValidSolution() const
{
  return ( fitStatus_ == 0 ) ? true : false;
}

double Higgsness::logHiggsness() const
{
  return logHiggsness_;
}
