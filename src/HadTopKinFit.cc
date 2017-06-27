#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include <TMath.h> // TMath::Pi()

#include <math.h> // exp, sin, sqrt

using namespace hadTopKinFit;

/// global pointer for interface to MINUIT
const HadTopKinFit* HadTopKinFit::gHadTopKinFit = 0;

double ObjectiveFunctionAdapter::operator()(const double* x) const // NOTE: return value = chi^2
{
  double alpha = x[0];
  double nll = HadTopKinFit::gHadTopKinFit->comp_nll(alpha);
  return nll;
}

namespace
{
  double square(double x)
  {
    return x*x;
  }
}

HadTopKinFit::HadTopKinFit()
  : nll_(-1.)
  , fit_status_(-1)
  , mTop2_(square(173.1)) // CV: particle masses taken from http://pdg.lbl.gov/2017/listings/contents_listings.html
  , mW2_(square(80.4))
  , mB2_(square(4.2))
  , maxObjFunctionCalls_(10000)
{
//--- instantiate MINUIT
  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

//--- set global pointer to this
  gHadTopKinFit = this;
}

HadTopKinFit::~HadTopKinFit()
{
  delete minimizer_;
}

void HadTopKinFit::fit(const Particle::LorentzVector& recBJetP4, const Particle::LorentzVector& recWJet1P4, const Particle::LorentzVector& recWJet2P4)
{
//--- clear minimizer
  minimizer_->Clear();

//--- set verbosity level of minimizer
  minimizer_->SetPrintLevel(-2);

//--- set interface to MINUIT
  ROOT::Math::Functor toMinimize(objectiveFunctionAdapter_, 1);
  minimizer_->SetFunction(toMinimize); 
  minimizer_->SetVariable(0, "alpha", 1., 5.e-2);
  minimizer_->SetMaxFunctionCalls(maxObjFunctionCalls_);
  minimizer_->SetErrorDef(0.5);

//--- set MINUIT strategy = 2, in order to get reliable error estimates:
//     http://www-cdf.fnal.gov/physics/statistics/recommendations/minuit.html
  minimizer_->SetStrategy(2);

//--- do the minimization
  recBJetP4_ = recBJetP4;
  recWJet1P4_ = recWJet1P4;
  recWJet2P4_ = recWJet2P4;
  alpha_ = 1.;
  nll_ = -1.;
  minimizer_->Minimize();

//--- get Minimizer status code, check if solution is valid:
//       0: Valid solution
//       1: Covariance matrix was made positive definite
//       2: Hesse matrix is invalid
//       3: Estimated distance to minimum (EDM) is above maximum
//       4: Reached maximum number of function calls before reaching convergence
//       5: Any other failure
  fit_status_ = minimizer_->Status();
}

const Particle::LorentzVector& HadTopKinFit::fittedBJet() const 
{ 
  if ( nll_ == -1. ) 
    throw cms::Exception("HadTopKinFit") 
      << "Kinematic fit has not yet run or failed !!\n";
  return fittedBJetP4_;
}

const Particle::LorentzVector& HadTopKinFit::fittedWJet1() const 
{
  if ( nll_ == -1. ) 
    throw cms::Exception("HadTopKinFit") 
      << "Kinematic fit has not yet run or failed !!\n";
  return fittedWJet1P4_;
}

const Particle::LorentzVector& HadTopKinFit::fittedWJet2() const 
{
  if ( nll_ == -1. ) 
    throw cms::Exception("HadTopKinFit") 
      << "Kinematic fit has not yet run or failed !!\n";
  return fittedWJet2P4_;
}

double HadTopKinFit::alpha() const
{
  if ( nll_ == -1. ) 
    throw cms::Exception("HadTopKinFit") 
      << "Kinematic fit has not yet run or failed !!\n";
  return alpha_;
}

double HadTopKinFit::nll() const
{
  return nll_;
}

int HadTopKinFit::fit_status() const
{
  return fit_status_;
}

namespace
{
  double comp_cosAngle(const Particle::LorentzVector& p1, const Particle::LorentzVector& p2)
  {
    double p1P = p1.P();
    double p2P = p2.P();
    double cosAngle = ( p1P > 0. && p2P > 0. ) ? (p1.px()*p2.px() + p1.py()*p2.py() + p1.pz()*p2.pz())/(p1P*p2P) : 1.;
    return cosAngle;
  }

  void dumpLorentzVector(const std::string& label, const Particle::LorentzVector& p4)
  {
    std::cout << label << ":" 
	      << " pT = " << p4.pt() << ","
	      << " eta = " << p4.eta() << ","
	      << " phi = " << p4.phi() << ","
	      << " mass = " << p4.mass() << std::endl;
  }
}

double HadTopKinFit::comp_nll(double alpha) const
{
  //std::cout << "<comp_nll>:" << std::endl;
  //std::cout << " alpha = " << alpha << std::endl;

//--- reconstruct W -> j1 j2 decay
  double fittedWJet1P = alpha*recWJet1P4_.P();
  double fittedWJet1Pt = fittedWJet1P*sin(recWJet1P4_.theta());
  Particle::LorentzVector fittedWJet1P4(fittedWJet1Pt, recWJet1P4_.eta(), recWJet1P4_.phi(), 0.);
  //dumpLorentzVector("fittedWJet1", fittedWJet1P4);

  double fittedWJet2P = comp_fittedP2(fittedWJet1P4.energy(), fittedWJet1P4.P(), recWJet2P4_.P(), mW2_, 0., 0., comp_cosAngle(recWJet1P4_, recWJet2P4_));
  double fittedWJet2Pt = fittedWJet2P*sin(recWJet2P4_.theta());
  Particle::LorentzVector fittedWJet2P4(fittedWJet2Pt, recWJet2P4_.eta(), recWJet2P4_.phi(), 0.);
  //dumpLorentzVector("fittedWJet2", fittedWJet2P4);

  Particle::LorentzVector fittedWP4 = fittedWJet1P4 + fittedWJet2P4;
  //dumpLorentzVector("fittedW", fittedWP4);

//--- reconstruct t -> b W decay
  double fittedBJetP = comp_fittedP2(fittedWP4.energy(), fittedWP4.P(), recBJetP4_.P(), mTop2_, mW2_, mB2_, comp_cosAngle(fittedWP4, recBJetP4_));
  double fittedBJetPt = fittedBJetP*sin(recBJetP4_.theta());
  Particle::LorentzVector fittedBJetP4(fittedBJetPt, recBJetP4_.eta(), recBJetP4_.phi(), sqrt(mB2_));
  //dumpLorentzVector("fittedBJetP4", fittedBJetP4);
  
  //Particle::LorentzVector fittedTopP4 = fittedWP4 + fittedBJetP4;
  //dumpLorentzVector("fittedTop", fittedTopP4);

//--- compute goodness-of-fit
  double prob = 1.;
  prob *= evalTF_lightJet(recWJet1P4_.energy(), fittedWJet1P4.energy(), recWJet1P4_.eta());
  prob *= evalTF_lightJet(recWJet2P4_.energy(), fittedWJet2P4.energy(), recWJet2P4_.eta());
  prob *= evalTF_BJet(recBJetP4_.energy(), fittedBJetP4.energy(), recBJetP4_.eta());
  double nll;
  if ( prob > 0. ) nll = -log(prob);
  else nll = std::numeric_limits<float>::max();
  //std::cout << "alpha = " << alpha << ": nll = " << nll << std::endl;

//--- save best fit
  if ( nll_ == -1. || nll < nll_ ) {
    fittedWJet1P4_ = fittedWJet1P4;
    fittedWJet2P4_ = fittedWJet2P4;
    fittedBJetP4_ = fittedBJetP4;
    alpha_ = alpha;
    nll_ = nll;
  }

  return nll;
}

double HadTopKinFit::comp_fittedP2(double fittedE1, double fittedP1, double recP2, double M_2, double m1_2, double m2_2, double cosAngle) const
{
  double fittedE1_2 = square(fittedE1);
  double fittedP1_2 = square(fittedP1);
  double recP2_2 = square(recP2);
  double cosAngle_2 = square(cosAngle);
  double term1 = M_2 - (m1_2 + m2_2);
  double term1_2 = square(term1);
  double term2 = cosAngle*term1*fittedP1*recP2;
  double term3 = (fittedE1_2 - cosAngle_2*fittedP1_2)*recP2_2;
  double term4 = sqrt(fittedE1_2*(term1_2 - 4.*fittedE1_2*m2_2 + 4.*cosAngle_2*m2_2*fittedP1_2)*recP2_2);
  double alpha1 = (term2 + term4)/(2.*term3);
  double alpha2 = (term2 - term4)/(2.*term3);
  if      ( alpha1 > 0. && alpha2 < 0. ) return alpha1*recP2;
  else if ( alpha2 > 0. && alpha1 < 0. ) return alpha2*recP2;
  else if ( alpha1 > 0. && alpha2 > 0. ) {
    double alpha_massless = term1/(2.*fittedP1*recP2*(1. - cosAngle));
    if ( std::fabs(alpha1 - alpha_massless) < std::fabs(alpha2 - alpha_massless) ) return alpha1*recP2;
    else return alpha2*recP2;
  } else return 0.;
}

//---------------------------------------------------------------------------------------------------------------
// CV: transfer functions for energy of bottom and light quark jets taken from ttH, H->bb matrix element analysis 
//       https://github.com/bianchini/Code/blob/master/src/Parameters.cpp

int eta_to_bin(double eta)
{
  double absEta = std::fabs(eta);
  if ( absEta < 1.0 ) return 0;
  else return 1;
}

double Chi2(double x, double m, double s)
{
  return ( s > 0. ) ? square((x - m)/s) : 1.e+3;
}

double HadTopKinFit::evalTF_BJet(double recE, double fittedE, double eta) const
{
  //std::cout << "<evalTF_BJet>:" << std::endl;
  //std::cout << " E: rec = " << recE << ", fitted = " << fittedE << std::endl;
  //std::cout << " eta = " << eta << std::endl;
  int eta_bin = eta_to_bin(eta);
  const double* par = TF_B_param[eta_bin];
  double f  = par[10];
  double m1 = par[0] + par[1]*fittedE;
  double m2 = par[5] + par[6]*fittedE;
  double s1 = fittedE*sqrt(square(par[2]) + square(par[3])/fittedE + square(par[4])/square(fittedE));
  double s2 = fittedE*sqrt(square(par[7]) + square(par[8])/fittedE + square(par[9])/square(fittedE));
  double c1 = Chi2(recE, m1, s1);
  double c2 = Chi2(recE, m2, s2);
  const double one_over_sqrtTwoPi = 1./sqrt(2.*TMath::Pi());
  double p = one_over_sqrtTwoPi*((f/s1)*exp(-0.5*c1) + ((1. - f)/s2)*exp(-0.5*c2));
  //std::cout << "p = " << p << std::endl;
  return p;
}

double HadTopKinFit::evalTF_lightJet(double recE, double fittedE, double eta) const
{
  //std::cout << "<evalTF_lightJet>:" << std::endl;
  //std::cout << " E: rec = " << recE << ", fitted = " << fittedE << std::endl;
  //std::cout << " eta = " << eta << std::endl;
  int eta_bin = eta_to_bin(eta);
  const double* par = TF_Q_param[eta_bin];
  double m1  = par[0] + par[1]*fittedE;
  double s1  = fittedE*sqrt(square(par[2]) + square(par[3])/fittedE + square(par[4])/square(fittedE));
  double c1  = Chi2(recE, m1, s1);
  const double one_over_sqrtTwoPi = 1./sqrt(2.*TMath::Pi());
  double p =  one_over_sqrtTwoPi*(1./s1)*exp(-0.5*c1);
  //std::cout << "p = " << p << std::endl;
  return p;
}
//---------------------------------------------------------------------------------------------------------------
