#ifndef tthAnalysis_HiggsToTauTau_mt2_3particle_h
#define tthAnalysis_HiggsToTauTau_mt2_3particle_h

/** \class mt2_3particle
 *
 * Compute generalized mT2 variable, described in the paper
 * [1] "Using subsystem mT2 for complete mass determination in decay chains with missing energy at hadron colliders",
 *      M. Burns, K. Kong and K.T. Matchev
 *    arXiv: 0810.5576
 *
 * This class implements the mT2 computation for the case that 3 "stable" visible particles are produced per decay chain.
 * It covers the case:
 *  1) ttbar -> bW bW -> blnu blnu, 
 *     where both W bosons decay to electrons or muons, 
 *     the latter being referred to as "lepton1" and "lepton2" 
 *    (case mT2(2,2,0) in Ref. [1]; with a1=bjet1, a2=bjet2, b1=lepton1, b2=lepton2, cSum=MET, cMass=0 [ c=neutrinos produced in W boson decays])
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "DataFormats/Candidate/interface/Candidate.h"

#include "Math/Minimizer.h"
#include "Math/Functor.h"
#include <TRandom3.h>
#include <TMath.h>

namespace mT2_3particle_namespace
{
  double comp_mT_3particle(double aPx, double aPy, double aMass, double bPx, double bPy, double bMass, double cPx, double cPy, double cMass)
  {
    double aMass2 = aMass*aMass;
    double aET = TMath::Sqrt(aMass2 + aPx*aPx + aPy*aPy);
    double bMass2 = bMass*bMass;
    double bET = TMath::Sqrt(bMass2 + bPx*bPx + bPy*bPy);
    double cMass2 = cMass*cMass;
    double cET = TMath::Sqrt(cMass2 + cPx*cPx + cPy*cPy);
    double mT2 = aMass2 + bMass2 + cMass2 + 2.*(aET*bET - (aPx*bPx + aPy*bPy)) + 2.*(aET*cET - (aPx*cPx + aPy*cPy)) + 2.*(bET*cET - (bPx*cPx + bPy*cPy));
    return mT2;
  }

  class mt2Functor_3particle
  {
   public:
    void set_a1(double a1Px, double a1Py, double a1Mass)
    {
      a1Px_   = a1Px;
      a1Py_   = a1Py;
      a1Mass_ = a1Mass;
    }
    void set_a2(double a2Px, double a2Py, double a2Mass)
    {
      a2Px_   = a2Px; 
      a2Py_   = a2Py;
      a2Mass_ = a2Mass;
    }
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
      double mT2_1 = comp_mT_3particle(a1Px_, a1Py_, a1Mass_, b1Px_, b1Py_, b1Mass_, c1Px, c1Py, cMass_);

      double c2Px  = cSumPx_ - c1Px; 
      double c2Py  = cSumPy_ - c1Py;
      double mT2_2 = comp_mT_3particle(a2Px_, a2Py_, a2Mass_, b2Px_, b2Py_, b2Mass_, c2Px, c2Py, cMass_);

      return TMath::Sqrt(TMath::Max(mT2_1, mT2_2));
    }
   private:
    double a1Px_;
    double a1Py_;
    double a1Mass_;
    double a2Px_;
    double a2Py_;
    double a2Mass_;
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

class mT2_3particle
{
 public:
  /// constructor
  mT2_3particle(int numSteps = 100);

  /// destructor
  ~mT2_3particle();

  /// compute mT2 variable
  void operator()(double a1Px, double a1Py, double a1Mass, 
		  double a2Px, double a2Py, double a2Mass,
		  double b1Px, double b1Py, double b1Mass, 
		  double b2Px, double b2Py, double b2Mass,
		  double cSumPx, double cSumPy, double cMass);
  
  double get_min_mT2() const;
  int get_min_step() const;

 protected:
  ROOT::Math::Minimizer* minimizer_;
  mT2_3particle_namespace::mt2Functor_3particle mT2Functor_;
  ROOT::Math::Functor* f_;
  int numSteps_;
  TRandom3 rnd_;
  double min_mT2_;
  int min_step_;
};

#endif
