#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

#include <cmath> // std::fabs()
#include <cassert> // assert()

/**
 * @brief Evaluate probability to mismeasure charge of electrons and
 *        muons passing tight charge requirement (Table 33 in AN-2018/098)
 * @param type (either kElectron or kMuon), pT and eta 
 * @return Charge misassignment probability measured in data, to be applied as
 *         event weight to events selected in the OS control region in order to
 *         estimate "charge flip" background in SS signal region
 */
double
prob_chargeMisId(int era,
                 int lepton_type,
                 double lepton_pt,
                 double lepton_eta)
{
  double prob = 1.;
  if(lepton_type == kElectron)
  {
    const double abs_lepton_eta = std::fabs(lepton_eta);
    if(era == kEra_2016)
    {
      if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 5.82117e-4;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 9.16626e-5;
        else if(lepton_pt >= 50.                  ) prob = 1.53866e-4;
      }
      else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 6.04459e-4;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 1.02072e-3;
        else if(lepton_pt >= 50.                  ) prob = 1.61979e-3;
      }
    }
    else if(era == kEra_2017)
    {
      if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 1.29248e-4;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 5.29988e-5;
        else if(lepton_pt >= 50.                  ) prob = 1.11898e-4;
      }
      else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 4.08034e-4;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 5.00129e-4;
        else if(lepton_pt >= 50.                  ) prob = 8.85938e-4;
      }
    }
    else if(era == kEra_2018)
    {
      if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 3.50000e-5;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 6.09854e-5;
        else if(lepton_pt >= 50.                  ) prob = 2.99421e-5;
      }
      else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
      {
        if     (lepton_pt >= 10. && lepton_pt < 25) prob = 4.49484e-4;
        else if(lepton_pt >= 25. && lepton_pt < 50) prob = 5.07696e-4;
        else if(lepton_pt >= 50.                  ) prob = 9.50909e-4;
      }
    }
  }
  else if(lepton_type == kMuon)
  {
    prob = 0.;
  }
  else
  {
    assert(0);
  }
  return prob;
}
