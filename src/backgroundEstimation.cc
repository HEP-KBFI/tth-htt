#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"

#include <cmath> // std::fabs
#include <assert.h> // assert

/**
 * @brief Evaluate probability to mismeasure charge of electrons and muons passing tight charge requirement (Table 8 in AN-2017/029)
 * @param type (either kElectron or kMuon), pT and eta 
 * @return Charge misassignment probability measured in data, to be applied as event weight to events selected in the OS control region in order to estimate "charge flip" background in SS signal region
 */
double prob_chargeMisId(int lepton_type, double lepton_pt, double lepton_eta)
{
  double prob = 1.;
  if ( lepton_type == kElectron ) {
    double abs_lepton_eta = std::fabs(lepton_eta);
    if ( abs_lepton_eta >= 0. && abs_lepton_eta < 1.479 ) {
      if      ( lepton_pt >= 10. && lepton_pt < 25 ) prob = 0.0442*1.e-2;
      else if ( lepton_pt >= 25. && lepton_pt < 50 ) prob = 0.0179*1.e-2;
      else if ( lepton_pt >= 50.                   ) prob = 0.0262*1.e-2;
    } else if ( abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5 ){
      if      ( lepton_pt >= 10. && lepton_pt < 25 ) prob = 0.1329*1.e-2;
      else if ( lepton_pt >= 25. && lepton_pt < 50 ) prob = 0.1898*1.e-2;
      else if ( lepton_pt >= 50.                   ) prob = 0.3067*1.e-2;
    }
  } else if ( lepton_type == kMuon ) {
    prob = 0.;
  } else assert(0);
  return prob;
}
