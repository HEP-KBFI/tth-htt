#ifndef tthAnalysis_HiggsToTauTau_mt2Interface_h
#define tthAnalysis_HiggsToTauTau_mt2Interface_h

/** \class mt2Interface
 *
 * Compute augMT2ed variable, described in the paper
 *  "Di-Higgs final states augMTed - selecting hh events at the high luminosity LHC",
 *   A.J. Barr, M.J. Dolan, C. Englert and M. Spannowsky
 *  arXiv: 1309.6318
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "DataFormats/Candidate/interface/Candidate.h"

#include "tthAnalysis/HiggsToTauTau/interface/mt2.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

class mt2Interface
{
 public:
  /// constructor
  mt2Interface();

  /// destructor
  ~mt2Interface();

  /// compute augMT2ed variable
  double operator()(const reco::Candidate::LorentzVector&, const reco::Candidate::LorentzVector&, 
		    const reco::Candidate::LorentzVector&, const reco::Candidate::LorentzVector&, const reco::Candidate::LorentzVector&);
  
 protected:
  mt2* mt2_;
  ROOT::Math::Minimizer* minimizer_;
};

#endif
