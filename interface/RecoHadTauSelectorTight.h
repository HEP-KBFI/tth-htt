#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorTight
{
 public:
  RecoHadTauSelectorTight(bool debug = false);
  ~RecoHadTauSelectorTight() {}

  /**
   * @brief Check if hadronic tau given as function argument passes nominal selection criteria defined in Section 3.5 of AN-2015/321
   * @return True if hadronic tau passes selection; false otherwise
   */
  bool operator()(const RecoHadTau& hadTau) const;

 protected: 
  Double_t min_pt_;            ///< lower cut threshold on pT
  Double_t max_absEta_;        ///< upper cut threshold on absolute value of eta
  Double_t max_dz_;            ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Int_t min_decayModeFinding_; ///< lower cut threshold on decayModeFinding discriminator
  Int_t min_id_mva_dR03_;      ///< lower cut threshold on MVA-based tau id computed with dR=0.3 isolation cone
  Double_t min_raw_mva_dR03_;  ///< lower cut threshold on raw output of MVA-based tau id computed with dR=0.3 isolation cone
  Int_t min_id_mva_dR05_;      ///< lower cut threshold on MVA-based tau id computed with dR=0.5 isolation cone
  Double_t min_raw_mva_dR05_;  ///< lower cut threshold on raw output of MVA-based tau id computed with dR=0.5 isolation cone
  Int_t min_id_cut_dR03_;      ///< lower cut threshold on cut-based tau id computed with dR=0.3 isolation cone
  Double_t max_raw_cut_dR03_;  ///< upper cut threshold on raw isolation pT-sum of cut-based tau id computed with dR=0.3 isolation cone
  Int_t min_id_cut_dR05_;      ///< lower cut threshold on cut-based tau id computed with dR=0.5 isolation cone
  Double_t max_raw_cut_dR05_;  ///< upper cut threshold on raw isolation pT-sum of cut-based tau id computed with dR=0.5 isolation cone
  Int_t min_antiElectron_;     ///< lower cut threshold on discriminator against electrons
  Int_t min_antiMuon_;         ///< lower cut threshold on discriminator against muons
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_h

