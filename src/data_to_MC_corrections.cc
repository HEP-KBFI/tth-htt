#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

enum { kElectron, kMuon };

/**
 * @brief Evaluate data/MC correction for electron and muon trigger efficiency (Table 10 in AN-2015/321)
 * @param type (either kElectron or kMuon), pT and eta of both leptons
 * @return data/MC scale-factor, to be applied as event weight to simulated events
 */
double data_to_MC_correction_triggerEff(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  if ( lepton1_type == kElectron && lepton2_type == kElectron ) {
    if ( std::max(lepton1_pt, lepton2_pt) > 40. ) return 0.99;
    else return 0.95;
  } else if ( lepton1_type == kMuon && lepton2_type == kMuon ) {
    return 0.98;
  } else {
    return 1.00;
  }
}


double data_to_MC_correction_leptonIDandIso_loose(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);
double data_to_MC_correction_leptonIDandIso_fakeable(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta)
{
  return data_to_MC_correction_leptonIDandIso_loose(lepton1_type, lepton1_pt, lepton1_eta, lepton2_type, lepton2_pt, lepton2_eta);
}
double data_to_MC_correction_leptonIDandIso_tight(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);
