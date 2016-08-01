#include "tthAnalysis/HiggsToTauTau/interface/hadTauTriggerTurnOnCurves.h"

#include <TMath.h>

#include <limits>

/**
 * @brief Integral of Crystal Ball function for fitting trigger efficiency turn-on curves (code from Pascal Paganini)
 * @param m = pT of reconstructed hadronic tau candidates; the other parameters refer to the shape of the Crystal Ball function, cf. Section 6.2.3 of AN-2016/027
 * @return efficiency for passing trigger, per hadronic tau leg
 */

double integralCrystalBall(double m, double m0, double sigma, double alpha, double n, double norm) 
{
  const double sqrtPiOver2 = 1.2533141373;
  const double sqrt2 = 1.4142135624;
  
  double sig = fabs((double)sigma);
  
  double t = (m - m0)/sig;
  
  if (alpha < 0) t = -t;
  
  double absAlpha = fabs(alpha / sig);
  double a = TMath::Power(n/absAlpha, n)*exp(-0.5*absAlpha*absAlpha);
  double b = absAlpha - n/absAlpha;
  
  if ( a >= std::numeric_limits<double>::max() ) return -1.;
  
  double ApproxErf;
  double arg = absAlpha / sqrt2;
  if      ( arg >  5. ) ApproxErf =  1;
  else if ( arg < -5. ) ApproxErf = -1;
  else                  ApproxErf = erf(arg);
  
  double leftArea = (1 + ApproxErf) * sqrtPiOver2;
  double rightArea = ( a * 1/TMath::Power(absAlpha - b,n-1)) / (n - 1);
  double area = leftArea + rightArea;
  
  if ( t <= absAlpha ) {
    arg = t / sqrt2;
    if      ( arg >  5.) ApproxErf =  1;
    else if ( arg < -5.) ApproxErf = -1;
    else                 ApproxErf = erf(arg);
    return norm * (1 + ApproxErf) * sqrtPiOver2 / area;
  } else {
    return norm * (leftArea +  a * (1/TMath::Power(t-b, n - 1) - 1/TMath::Power(absAlpha - b, n - 1)) / (1 - n)) / area;
  }
}

/**
 * @brief Trigger efficiency turn-on curve for HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg trigger measured by Riccardo for 2016 data
 * @param pT and eta of both reconstructed hadronic tau candidates
 * @return efficiency for passing trigger,
    cf. slide 6 of https://indico.cern.ch/event/544712/contributions/2213574/attachments/1295299/1930984/htt_tau_trigger_17_6_2016.pdf
   (parameters of Crystal Ball function taken for Tight WP of MVA-based tau ID trained with dR=0.5 isolation cone)
 */

double effHLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg(double tau1Pt, double tau1Eta, double tau2Pt, double tau2Eta) 
{
  double m1 = tau1Pt;
  if ( m1 <  20. ) m1 =  20.; // CV: restrict m to Pt-range actually fitted
  if ( m1 > 170. ) m1 = 170.;
  double m2 = tau2Pt;
  if ( m2 <  20. ) m2 =  20.; // CV: restrict m to Pt-range actually fitted
  if ( m2 > 170. ) m2 = 170.;
  
  const double m0 = 3.76157e+1;
  const double sigma = 4.76127e0;
  const double alpha = 3.62497e0;
  const double n = 3.51839e0;
  const double norm = 9.83701e-1;
  return TMath::Max(0., integralCrystalBall(m1, m0, sigma, alpha, n, norm))*TMath::Max(0., integralCrystalBall(m2, m0, sigma, alpha, n, norm)); 
}
