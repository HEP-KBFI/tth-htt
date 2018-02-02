#ifndef tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
#define tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h

double
sf_triggerEff(int numLeptons,
              int lepton1_type,      double lepton1_pt,      double lepton1_eta,
              int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
              int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

double
sf_leptonID_and_Iso_loose(int numLeptons,
                          int lepton1_type,      double lepton1_pt,      double lepton1_eta,
                          int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
                          int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

double
sf_leptonID_and_Iso_fakeable_to_loose(int numLeptons,
                                      int lepton1_type,      double lepton1_pt,      double lepton1_eta,
                                      int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
                                      int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

double
sf_leptonID_and_Iso_tight_to_loose(int numLeptons,
                                   int lepton1_type,      double lepton1_pt,      double lepton1_eta,
                                   int lepton2_type = -1, double lepton2_pt = 0., double lepton2_eta = 0.,
                                   int lepton3_type = -1, double lepton3_pt = 0., double lepton3_eta = 0.);

enum
{
  kFRet_central,
  kFRet_shiftUp,
  kFRet_shiftDown
};

enum
{
  kFRmt_central,
  kFRmt_shiftUp,
  kFRmt_shiftDown
};

double
sf_eToTauFakeRate_2017(double hadTau_pt,
                       double hadTau_absEta,
                       int hadTauSelection_antiElectron,
                       int central_or_shift = kFRet_central);

double
sf_muToTauFakeRate_2017(double hadTau_pt,
                        double hadTau_absEta,
                        int hadTauSelection_antiMuon,
                        int central_or_shift = kFRet_central);

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
