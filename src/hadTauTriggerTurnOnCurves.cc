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
