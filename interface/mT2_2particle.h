#ifndef tthAnalysis_HiggsToTauTau_mt2_2particle_h
#define tthAnalysis_HiggsToTauTau_mt2_2particle_h

/** \class mt2_2particle
 *
 * Compute generalized mT2 variable, described in the papers
 * [1] "Using subsystem mT2 for complete mass determination in decay chains with missing energy at hadron colliders",
 *      M. Burns, K. Kong and K.T. Matchev
 *    arXiv: 0810.5576
 * [2] "Di-Higgs final states augMTed - selecting hh events at the high luminosity LHC",
 *      A.J. Barr, M.J. Dolan, C. Englert and M. Spannowsky
 *    arXiv: 1309.6318
 *
 * This class implements the mT2 computation for the case that 2 "stable" visible particles are produced per decay chain.
 * It covers the cases:
 *  1) WW -> lnu lnu 
 *    (case mT2(1,1,0 in Ref. [1]; with b1=lepton1, b2=lepton2, cSum=MET, cMass=0)
 *  2) ttbar -> bW bW, 
 *     where both W bosons decay to electrons or muons, 
 *     the latter being referred to as "lepton1" and "lepton2" 
 *    (case mT2(2,1,0) in Ref. [2]; with b1=bjet1, b2=bjet2, cSum=lepton1+lepton2+MET, cMass=mW)
 *  3) ttbar -> bW bW, 
 *     where both W bosons decay to tau leptons, which subsequently decay to electrons, muons, or tau_h, 
 *     the latter being referred to as "vis1" and "vis2" 
 *    (described in Section "KINEMATIC BOUNDING VARIABLES" in Ref. [2]; with b1=bjet1, b2=bjet2, cSum=vis1+vis2+MET, cMass=mW)
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "DataFormats/Candidate/interface/Candidate.h"

#include "tthAnalysis/HiggsToTauTau/interface/mt2.h"

#include "Math/Minimizer.h"
#include "Math/Functor.h"
#include <TRandom3.h>
#include <TMath.h>

namespace mT2_2particle_namespace
{
  double comp_mT_2particle(double bPx, double bPy, double bMass, double cPx, double cPy, double cMass)
  {
    double bMass2 = bMass*bMass;
    double bET = TMath::Sqrt(bMass2 + bPx*bPx + bPy*bPy);
    double cMass2 = cMass*cMass;
    double cET = TMath::Sqrt(cMass2 + cPx*cPx + cPy*cPy);
    double mT2 = bMass2 + cMass2 + 2.*(bET*cET - (bPx*cPx + bPy*cPy));
    return mT2;
  }

  class mt2Functor_2particle
  {
   public:
    void set_b1(double b1Px, double b1Py, double b1Mass)
    {
      b1Px_   = b1Px;
      b1Py_   = b1Py;
      b1Mass_ = b1Mass;
    }
    void set_b2(double b2Px, double b2Py, double b2Mass)
    {
      b2Px_   = b2Px; 
      b2Py_   = b2Py;
      b2Mass_ = b2Mass;
    }
    void set_cSum(double cSumPx, double cSumPy, double cMass)
    {
      cSumPx_ = cSumPx;
      cSumPy_ = cSumPy;
      cMass_  = cMass;
    }
    double operator()(const double* par)
    {
      double c1Pt   = par[0];
      double c1Phi  = par[1];

      double c1Px  = TMath::Cos(c1Phi)*c1Pt;
      double c1Py  = TMath::Sin(c1Phi)*c1Pt;
      double mT2_1 = comp_mT_2particle(b1Px_, b1Py_, b1Mass_, c1Px, c1Py, cMass_);

      double c2Px  = cSumPx_ - c1Px; 
      double c2Py  = cSumPy_ - c1Py;
      double mT2_2 = comp_mT_2particle(b2Px_, b2Py_, b2Mass_, c2Px, c2Py, cMass_);

      return TMath::Sqrt(TMath::Max(mT2_1, mT2_2));
    }
   private:
    double b1Px_;
    double b1Py_;
    double b1Mass_;
    double b2Px_;
    double b2Py_;
    double b2Mass_;
    double cSumPx_;
    double cSumPy_;
    double cMass_;
  };
}

class mT2_2particle
{
 public:
  /// constructor
  mT2_2particle(int numSteps = 100);

  /// destructor
  ~mT2_2particle();

  /// compute mT2 variable
  std::pair<double, int> operator()(double b1Px, double b1Py, double b1Mass, 
				    double b2Px, double b2Py, double b2Mass,
				    double cSumPx, double cSumPy, double cMass);
  
 protected:
  ROOT::Math::Minimizer* minimizer_;
  mT2_2particle_namespace::mt2Functor_2particle mT2Functor_;
  ROOT::Math::Functor* f_;
  int numSteps_;
  TRandom3 rnd_;
};

#endif
