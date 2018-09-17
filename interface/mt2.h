#ifndef tthAnalysis_HiggsToTauTau_mt2_h
#define tthAnalysis_HiggsToTauTau_mt2_h

#include <TMath.h>

#include <string>
#include <iostream>

class mt2
{
 public:
  mt2() { name_ = "thing"; }

  double operator()(const double*);

  void setB1(double b1Px, double b1Py, double b1Mass) { b1Px_ = b1Px; b1Py_ = b1Py; b1Mass_ = b1Mass; }
  void setB2(double b2Px, double b2Py, double b2Mass) { b2Px_ = b2Px; b2Py_ = b2Py; b2Mass_ = b2Mass; }
  void setTau1(double tau1Px, double tau1Py, double tau1Mass) { tau1Px_ = tau1Px; tau1Py_ = tau1Py; tau1Mass_ = tau1Mass; }
  void setTau2(double tau2Px, double tau2Py, double tau2Mass) { tau2Px_ = tau2Px; tau2Py_ = tau2Py; tau2Mass_ = tau2Mass; }
  void setMEt(double metPx, double metPy) { metPx_ = metPx; metPy_ = metPy; }
  
 protected:
  std::string name_;
  double b1Px_;
  double b1Py_;
  double b1Mass_;
  double b2Px_;
  double b2Py_;
  double b2Mass_;
  double tau1Px_;
  double tau1Py_;
  double tau1Mass_;
  double tau2Px_;
  double tau2Py_;
  double tau2Mass_;
  double metPx_;
  double metPy_;
};

#endif
