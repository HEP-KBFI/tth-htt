#include "tthAnalysis/HiggsToTauTau/interface/mt2Interface.h"

#include <TMath.h>

mt2Interface::mt2Interface()
{
  mt2_ = new mt2();

  minimizer_ = ROOT::Math::Factory::CreateMinimizer("Minuit2", "");
  minimizer_->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
  minimizer_->SetTolerance(10.0);
  minimizer_->SetPrintLevel(0);
}

mt2Interface::~mt2Interface()
{
  delete mt2_;

  delete minimizer_;
}

double mt2Interface::operator()(const reco::Candidate::LorentzVector& bjet1P4, const reco::Candidate::LorentzVector& bjet2P4,
				const reco::Candidate::LorentzVector& tau1P4, const reco::Candidate::LorentzVector& tau2P4, const reco::Candidate::LorentzVector& metP4)

{
  mt2_->setB1(bjet1P4.px(), bjet1P4.py(), bjet1P4.mass());
  mt2_->setB2(bjet2P4.px(), bjet2P4.py(), bjet2P4.mass());
  mt2_->setTau1(tau1P4.px(), tau1P4.py(), tau1P4.mass());
  mt2_->setTau2(tau2P4.px(), tau2P4.py(), tau2P4.mass());
  mt2_->setMEt(metP4.px(), metP4.py());
    
  double sumPx = tau1P4.px() + tau2P4.px() + metP4.px();
  double sumPy = tau1P4.py() + tau2P4.py() + metP4.py();
  double sumPt = TMath::Sqrt(sumPx*sumPx + sumPy*sumPy);

  ROOT::Math::Functor f(*mt2_, 2);

  minimizer_->SetFunction(f);
  minimizer_->SetLimitedVariable(0, "cPt", 0.5*sumPt, 0.01*sumPt, 0., 10.*sumPt);
  minimizer_->SetLimitedVariable(1, "cPhi", 0., 0.1, -TMath::Pi(), +TMath::Pi());  
  minimizer_->Minimize();
  
  double mt2_value = minimizer_->MinValue();
  return mt2_value;
}
