#ifndef tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
#define tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h

enum { kElectron, kMuon };

double data_to_MC_correction_triggerEff(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);

double data_to_MC_correction_leptonIDandIso_loose(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);
double data_to_MC_correction_leptonIDandIso_fakeable(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);
double data_to_MC_correction_leptonIDandIso_tight(int lepton1_type, double lepton1_pt, double lepton1_eta, int lepton2_type, double lepton2_pt, double lepton2_eta);


#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
