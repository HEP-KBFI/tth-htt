#ifndef tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
#define tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h

double sf_triggerEff(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

double sf_leptonID_and_Iso_loose(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0., 
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);
double sf_leptonID_and_Iso_fakeable_to_loose(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0., 
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);
double sf_leptonID_and_Iso_fakeable(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0., 
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);
double sf_leptonID_and_Iso_tight_to_loose(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);
double sf_leptonID_and_Iso_tight(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta,
  int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0., 
  int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
