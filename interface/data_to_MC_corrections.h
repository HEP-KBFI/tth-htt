#ifndef tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
#define tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h

#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // FRet, FRmt

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

double
sf_eToTauFakeRate_2017(double hadTau_pt,
                       double hadTau_absEta,
                       int hadTauSelection_antiElectron,
                       FRet central_or_shift = FRet::central);

double
sf_muToTauFakeRate_2017(double hadTau_pt,
                        double hadTau_absEta,
                        int hadTauSelection_antiMuon,
                        FRmt central_or_shift = FRmt::central);

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_h
