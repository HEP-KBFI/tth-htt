#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTF1

#include "Math/GSLMCIntegrator.h" // ROOT::Math::GSLMCIntegrator
#include <TMath.h> // TMath::Pi()

#include <math.h> // exp, sin, sqrt

using namespace hadTopKinFit;

/// global pointer for interface to MINUIT
const HadTopKinFit* HadTopKinFit::gHadTopKinFit = 0;

double ObjectiveFunctionAdapterMINUIT::operator()(const double* x) const // NOTE: return value = -log(p)
{
  double alpha = x[0];
  double prob = HadTopKinFit::gHadTopKinFit->comp_prob(alpha);
  double nll;
  if ( prob > 0. ) nll = -log(prob);
  else nll = std::numeric_limits<float>::min();
  return nll;
}

double ObjectiveFunctionAdapterVEGAS::operator()(const double* x) const // NOTE: return value = p
{
  double alpha = x[0];
  double prob = HadTopKinFit::gHadTopKinFit->comp_prob(alpha);
  if ( TMath::IsNaN(prob) ) prob = 0.;
  return prob;
}

namespace
{
  double square(double x)
  {
    return x*x;
  }

  TF1* loadTF(TFile* inputFile, const std::string& functionName)
  {
    TF1* tf = loadTF1(inputFile, functionName);
    tf->SetNpx(10000);
    tf->SetRange(0., 500.);
    return tf;
  }
}

HadTopKinFit::HadTopKinFit(int tf_mode, const std::string& tf_fileName)
  : tf_mode_(tf_mode)
  , tf_file_(0)
  , tf_q_barrel_(0)
  , tf_q_endcap_(0)
  , tf_b_barrel_(0)
  , tf_b_endcap_(0)
  , max_prob_(-1.)  
  , mTop2_(square(173.1)) // CV: particle masses taken from http://pdg.lbl.gov/2017/listings/contents_listings.html
  , mW2_(square(80.4))
  , mB2_(square(4.2))
  , maxObjFunctionCalls_(10000)
  , nll_(-1.)
  , fit_status_(-1)
  , p_(-1.)
  , pErr_(-1.)
{
  if ( tf_mode_ > 0 ) {
    tf_file_ = openFile(LocalFileInPath(tf_fileName));
    tf_q_barrel_ = loadTF(tf_file_, "tf_l_etabin0");
    tf_q_endcap_ = loadTF(tf_file_, "tf_l_etabin1");
    tf_b_barrel_ = loadTF(tf_file_, "tf_b_etabin0");
    tf_b_endcap_ = loadTF(tf_file_, "tf_b_etabin1");
  }

//--- instantiate MINUIT
  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

//--- set global pointer to this
  gHadTopKinFit = this;
}

HadTopKinFit::~HadTopKinFit()
{
  delete tf_file_;
  delete tf_q_barrel_;
  delete tf_q_endcap_;
  delete tf_b_barrel_;
  delete tf_b_endcap_;
  delete minimizer_;
}

void HadTopKinFit::fit(const Particle::LorentzVector& recBJetP4, const Particle::LorentzVector& recWJet1P4, const Particle::LorentzVector& recWJet2P4)
{
  //std::cout << "<HadTopKinFit::fit>:" << std::endl;

//--- clear minimizer
  minimizer_->Clear();

//--- set verbosity level of minimizer
  minimizer_->SetPrintLevel(-2);

//--- set interface to MINUIT
  ROOT::Math::Functor toMinimize(objectiveFunctionAdapterMINUIT_, 1);
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
  minimizer_->Minimize();
  if ( max_prob_ > 0. ) nll_ = -log(max_prob_);
  else nll_ = std::numeric_limits<float>::min();

//--- get Minimizer status code, check if solution is valid:
//       0: Valid solution
//       1: Covariance matrix was made positive definite
//       2: Hesse matrix is invalid
//       3: Estimated distance to minimum (EDM) is above maximum
//       4: Reached maximum number of function calls before reaching convergence
//       5: Any other failure
  fit_status_ = minimizer_->Status();

}

void HadTopKinFit::integrate(const Particle::LorentzVector& recBJetP4, const Particle::LorentzVector& recWJet1P4, const Particle::LorentzVector& recWJet2P4)
{
  //std::cout << "<HadTopKinFit::integrate>:" << std::endl;

//--- create instance of VEGAS integration algorithm
  ROOT::Math::GSLMCIntegrator vegas("vegas", 0., 1.e-6, 10000);
  ROOT::Math::Functor toIntegrate(&objectiveFunctionAdapterVEGAS_, &ObjectiveFunctionAdapterVEGAS::operator(), 1);
  vegas.SetFunction(toIntegrate);
  double xl[1];
  xl[0] = 1. - 5./std::max(1., TMath::Sqrt(recWJet1P4_.energy()));
  if ( xl[0] < 0. ) xl[0] = 0.;
  double xh[1];
  xh[0] = 1. + 5./std::max(1., TMath::Sqrt(recWJet1P4_.energy()));
  if ( xh[0] > 1.e+1 ) xh[0] = 1.e+1;
  p_ = vegas.Integral(xl, xh);
  pErr_ = vegas.Error();
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

double HadTopKinFit::p() const
{
  return p_;
}

double HadTopKinFit::pErr() const
{
  return pErr_;
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
/*
  void dumpLorentzVector(const std::string& label, const Particle::LorentzVector& p4)
  {
    std::cout << label << ":" 
	      << " pT = " << p4.pt() << ","
	      << " eta = " << p4.eta() << ","
	      << " phi = " << p4.phi() << ","
	      << " mass = " << p4.mass() << std::endl;
  }
 */
}

double HadTopKinFit::comp_prob(double alpha) const
{
  //std::cout << "<comp_prob>:" << std::endl;
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
  prob *= evalTF_lightJet(recWJet1P4_, fittedWJet1P4);
  prob *= evalTF_lightJet(recWJet2P4_, fittedWJet2P4);
  prob *= evalTF_BJet(recBJetP4_, fittedBJetP4);
  //std::cout << "alpha = " << alpha << ": prob = " << prob << std::endl;

//--- save best fit
  if ( max_prob_ == -1. || prob > max_prob_ ) {
    fittedWJet1P4_ = fittedWJet1P4;
    fittedWJet2P4_ = fittedWJet2P4;
    fittedBJetP4_ = fittedBJetP4;
    alpha_ = alpha;
    max_prob_ = prob;
  }

  return prob;
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

double HadTopKinFit::evalTF_BJet(const Particle::LorentzVector& recP4, const Particle::LorentzVector& fittedP4) const
{
  //std::cout << "<evalTF_BJet>:" << std::endl;
  double eta = recP4.eta();
  int eta_bin = eta_to_bin(eta);
  double p = 1.;
  if ( tf_mode_ == 0 ) {
    double recE = recP4.energy();
    double fittedE = fittedP4.energy();
    //std::cout << " E: rec = " << recE << ", fitted = " << fittedE << std::endl;
    //std::cout << " eta = " << eta << std::endl;
    const double* par = TF_B_param[eta_bin];
    double f  = par[10];
    double m1 = par[0] + par[1]*fittedE;
    double m2 = par[5] + par[6]*fittedE;
    double s1 = fittedE*sqrt(square(par[2]) + square(par[3])/fittedE + square(par[4])/square(fittedE));
    double s2 = fittedE*sqrt(square(par[7]) + square(par[8])/fittedE + square(par[9])/square(fittedE));
    double c1 = Chi2(recE, m1, s1);
    double c2 = Chi2(recE, m2, s2);
    const double one_over_sqrtTwoPi = 1./sqrt(2.*TMath::Pi());
    p = one_over_sqrtTwoPi*((f/s1)*exp(-0.5*c1) + ((1. - f)/s2)*exp(-0.5*c2));
  } else {
    TF1* tf = 0;
    if ( eta_bin == 0 ) tf = tf_b_barrel_;
    else tf = tf_b_endcap_;
    double recPt = recP4.pt();
    double fittedPt = fittedP4.pt();
    //std::cout << " pT: rec = " << recPt << ", fitted = " << fittedPt << std::endl;
    //std::cout << " eta = " << eta << std::endl;
    tf->SetParameter(0, fittedPt);
    p = tf->Eval(recPt);
  }
  //std::cout << "p = " << p << std::endl;
  return p;
}

double HadTopKinFit::evalTF_lightJet(const Particle::LorentzVector& recP4, const Particle::LorentzVector& fittedP4) const
{
  //std::cout << "<evalTF_lightJet>:" << std::endl;
  double eta = recP4.eta();
  int eta_bin = eta_to_bin(eta);
  double p = 1.;
  if ( tf_mode_ == 0 ) {
    double recE = recP4.energy();
    double fittedE = fittedP4.energy();
    //std::cout << " E: rec = " << recE << ", fitted = " << fittedE << std::endl;
    //std::cout << " eta = " << eta << std::endl;
    const double* par = TF_Q_param[eta_bin];
    double m1  = par[0] + par[1]*fittedE;
    double s1  = fittedE*sqrt(square(par[2]) + square(par[3])/fittedE + square(par[4])/square(fittedE));
    double c1  = Chi2(recE, m1, s1);
    const double one_over_sqrtTwoPi = 1./sqrt(2.*TMath::Pi());
    p = one_over_sqrtTwoPi*(1./s1)*exp(-0.5*c1);
  } else {
    TF1* tf = 0;
    if ( eta_bin == 0 ) tf = tf_q_barrel_;
    else tf = tf_q_endcap_;
    double recPt = recP4.pt();
    double fittedPt = fittedP4.pt();
    //std::cout << " pT: rec = " << recPt << ", fitted = " << fittedPt << std::endl;
    //std::cout << " eta = " << eta << std::endl;
    tf->SetParameter(0, fittedPt);
    p = tf->Eval(recPt);
  }
  //std::cout << "p = " << p << std::endl;
  return p;
}
//---------------------------------------------------------------------------------------------------------------
