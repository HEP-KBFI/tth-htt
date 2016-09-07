#ifndef tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include <vector>

//--- declare constants
const double z_mass   = 91.1876;
const double z_window = 10.;
const double met_coef =  0.00397;
const double mht_coef =  0.00265;

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2);

/**
 * @brief Auxiliary function for checking if leptons passing fake-able lepton selection pass tight lepton identification criteria also
 */
template <typename Tfakeable, typename Ttight>
bool isMatched(const Tfakeable& fakeableLepton, const std::vector<Ttight*>& tightLeptons, double dRmax = 1.e-2)
{
  for ( typename std::vector<const Ttight*>::const_iterator tightLepton = tightLeptons.begin();
        tightLepton != tightLeptons.end(); ++tightLepton ) {
    double dR = deltaR(fakeableLepton.eta_, fakeableLepton.phi_, (*tightLepton)->eta_, (*tightLepton)->phi_);
    if ( dR < dRmax ) return true; // found match
  }
  return false; // no match found
}

#endif
