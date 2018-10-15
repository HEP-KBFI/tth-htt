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
  class mt2Functor_3particle;
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

  static double comp_mT(double aPx, double aPy, double aMass, double bPx, double bPy, double bMass, double cPx, double cPy, double cMass);

 protected:
  ROOT::Math::Minimizer* minimizer_;
  mT2_3particle_namespace::mt2Functor_3particle* mT2Functor_;
  ROOT::Math::Functor* f_;
  int numSteps_;
  TRandom3 rnd_;
  double min_mT2_;
  int min_step_;
};

namespace mT2_3particle_namespace
{
  class mt2Functor_3particle
  {
   public:
    double operator()(const double* par)
    {
      double c1Pt   = par[0];
      double c1Phi  = par[1];

      double a1Px   = par[2];
      double a1Py   = par[3];
      double a1Mass = par[4];
      double a2Px   = par[5];
      double a2Py   = par[6];
      double a2Mass = par[7];
      double b1Px   = par[8];
      double b1Py   = par[9];
      double b1Mass = par[10];
      double b2Px   = par[11];
      double b2Py   = par[12];
      double b2Mass = par[13];
      double cSumPx = par[14];
      double cSumPy = par[15];
      double cMass  = par[16];

      double c1Px  = TMath::Cos(c1Phi)*c1Pt;
      double c1Py  = TMath::Sin(c1Phi)*c1Pt;      
      double mT2_1 = mT2_3particle::comp_mT(a1Px, a1Py, a1Mass, b1Px, b1Py, b1Mass, c1Px, c1Py, cMass);

      double c2Px  = cSumPx - c1Px; 
      double c2Py  = cSumPy - c1Py;
      double mT2_2 = mT2_3particle::comp_mT(a2Px, a2Py, a2Mass, b2Px, b2Py, b2Mass, c2Px, c2Py, cMass);

      return TMath::Sqrt(TMath::Max(mT2_1, mT2_2));
    }
  };
}

#endif
