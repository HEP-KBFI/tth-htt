#include "tthAnalysis/HiggsToTauTau/interface/mt2.h"

double compMtSq(double bPx, double bPy, double bMass, double cPx, double cPy, double cMass)
{
  double bMass2 = bMass*bMass;
  double bEt = TMath::Sqrt(bMass2 + bPx*bPx + bPy*bPy);
  double cMass2 = cMass*cMass;
  double cEt = TMath::Sqrt(cMass2 + cPx*cPx + cPy*cPy);
  double mtSq = bMass2 + cMass2 + 2.*(bEt*cEt - (bPx*cPx + bPy*cPy));
  return mtSq;
}

double mt2::operator()(const double* par) 
{
  double cPt   = par[0];
  double cPhi  = par[1];

  double c1Px  = TMath::Cos(cPhi)*cPt;
  double c1Py  = TMath::Sin(cPhi)*cPt;
  double mtSq1 = compMtSq(b1Px_, b1Py_, b1Mass_, c1Px, c1Py, tau1Mass_);

  double c2Px  = (tau1Px_ + tau2Px_ + metPx_) - c1Px; 
  double c2Py  = (tau1Py_ + tau2Py_ + metPy_) - c1Py;
  double mtSq2 = compMtSq(b2Px_, b2Py_, b2Mass_, c2Px, c2Py, tau2Mass_);

  double mt2_value = TMath::Sqrt(TMath::Max(mtSq1, mtSq2));
  //static int idx = 0;
  //std::cout << " #" << idx << ": cPt = " << cPt << ", cPhi = " << cPhi << " --> mt2 = " << mt2_value << std::endl;
  //++idx;
  return mt2_value;
}
