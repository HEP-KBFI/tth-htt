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
 *    (case mT2(1,1,0 in Ref. [1]; with b1=lepton1, b2=lepton2, cSum=MET, cMass=0 [ c=neutrinos produced in W boson decays ])
 *  2) ttbar -> bW bW, 
 *     where both W bosons decay to electrons or muons, 
 *     the latter being referred to as "lepton1" and "lepton2" 
 *    (case mT2(2,1,0) in Ref. [2]; with b1=bjet1, b2=bjet2, cSum=lepton1+lepton2+MET, cMass=mW [ c=W bosons ])
 *  3) ttbar -> bW bW, 
 *     where both W bosons decay to tau leptons, which subsequently decay to electrons, muons, or tau_h, 
 *     the latter being referred to as "vis1" and "vis2" 
 *    (described in Section "KINEMATIC BOUNDING VARIABLES" in Ref. [2]; with b1=bjet1, b2=bjet2, cSum=vis1+vis2+MET, cMass=mW [ c=W bosons ])
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include <DataFormats/Candidate/interface/Candidate.h>

#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <TRandom3.h>

namespace mT2_2particle_namespace
{
  class mt2Functor_2particle;
}

class mT2_2particle
{
public:
  mT2_2particle(int numSteps = 100);
  ~mT2_2particle();

  void
  operator()(double b1Px,   double b1Py,   double b1Mass,
             double b2Px,   double b2Py,   double b2Mass,
             double cSumPx, double cSumPy, double cMass);
  
  double get_min_mT2() const;
  int get_min_step() const;

  static double
  comp_mT(double bPx, double bPy, double bMass,
          double cPx, double cPy, double cMass);

protected:
  ROOT::Math::Minimizer * minimizer_;
  mT2_2particle_namespace::mt2Functor_2particle * mT2Functor_;
  ROOT::Math::Functor * f_;
  int numSteps_;
  TRandom3 rnd_;
  double min_mT2_;
  int min_step_;
};

namespace mT2_2particle_namespace
{
  class mt2Functor_2particle
  {
   public:
    double operator()(const double* par)
    {
      const double c1Pt   = par[0];
      const double c1Phi  = par[1];

      const double b1Px   = par[2];
      const double b1Py   = par[3];
      const double b1Mass = par[4];
      const double b2Px   = par[5];
      const double b2Py   = par[6];
      const double b2Mass = par[7];
      const double cSumPx = par[8];
      const double cSumPy = par[9];
      const double cMass  = par[10];

      const double c1Px  = std::cos(c1Phi) * c1Pt;
      const double c1Py  = std::sin(c1Phi) * c1Pt;
      const double mT2_1 = mT2_2particle::comp_mT(b1Px, b1Py, b1Mass, c1Px, c1Py, cMass);

      const double c2Px  = cSumPx - c1Px;
      const double c2Py  = cSumPy - c1Py;
      const double mT2_2 = mT2_2particle::comp_mT(b2Px, b2Py, b2Mass, c2Px, c2Py, cMass);

      return std::sqrt(std::max(mT2_1, mT2_2));
    }
  };
}

#endif
