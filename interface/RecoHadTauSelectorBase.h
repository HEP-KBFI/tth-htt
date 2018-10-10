#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

class RecoHadTauSelectorBase
{
public:
  explicit
  RecoHadTauSelectorBase(int era,
                         int index = -1,
                         bool debug = false,
                         bool set_selection_flags = true);
  virtual ~RecoHadTauSelectorBase() {}

  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);
  double get_min_pt() const;
  double get_max_absEta() const;

  void set_min_id_mva_dR03(int min_id_mva_dR03);
  void set_min_raw_mva_dR03(double min_raw_mva_dR03);
  void set_min_id_mva_dR05(int min_id_mva_dR05);
  void set_min_raw_mva_dR05(double min_raw_mva_dR05);
  
  void set_min_id_cut_dR03(int min_id_cut_dR03);
  void set_max_raw_cut_dR03(double max_raw_cut_dR03);
  void set_min_id_cut_dR05(int min_id_cut_dR05);
  void set_max_raw_cut_dR05(double max_raw_cut_dR05);

  int    get_min_id_mva_dR03() const;
  double get_min_raw_mva_dR03() const;
  int    get_min_id_mva_dR05() const;
  double get_min_raw_mva_dR05() const;

  int    get_min_id_cut_dR03() const;
  double get_max_raw_cut_dR03() const;
  int    get_min_id_cut_dR05() const;
  double get_max_raw_cut_dR05() const;

  void set_min_antiElectron(int min_antiElectron);
  void set_min_antiMuon    (int min_antiMuon);
  int get_min_antiElectron() const;
  int get_min_antiMuon() const;

  void set(const std::string & cut);
  const std::string & get() const;

  bool set_if_looser(const std::string & cut);

  /**
   * @brief Check if hadronic tau given as function argument passes nominal selection criteria defined in Section 3.5 of AN-2015/321
   * @return True if hadronic tau passes selection; false otherwise
   */
  bool operator()(const RecoHadTau & hadTau) const;

  friend class RecoHadTauCollectionSelectorBase;

protected:
  enum class MVASelection
  {
    kNone, kOR
  };

  virtual void set_selection_flags(const RecoHadTau & hadTau) const = 0;

  bool set_selection_flags_;
  bool debug_;                    ///< enable printout for debugging purposes
  Double_t min_pt_;               ///< lower cut threshold on pT
  Double_t max_absEta_;           ///< upper cut threshold on absolute value of eta
  Double_t max_dz_;               ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Bool_t apply_decayModeFinding_; ///< lower cut threshold on decayModeFinding discriminator
  Int_t min_id_mva_dR03_;         ///< lower cut threshold on MVA-based tau id computed with dR=0.3 isolation cone
  Double_t min_raw_mva_dR03_;     ///< lower cut threshold on raw output of MVA-based tau id computed with dR=0.3 isolation cone
  Int_t min_id_mva_dR05_;         ///< lower cut threshold on MVA-based tau id computed with dR=0.5 isolation cone
  Double_t min_raw_mva_dR05_;     ///< lower cut threshold on raw output of MVA-based tau id computed with dR=0.5 isolation cone
  Int_t min_id_cut_dR03_;         ///< lower cut threshold on cut-based tau id computed with dR=0.3 isolation cone
  Double_t max_raw_cut_dR03_;     ///< upper cut threshold on raw isolation pT-sum of cut-based tau id computed with dR=0.3 isolation cone
  Int_t min_id_cut_dR05_;         ///< lower cut threshold on cut-based tau id computed with dR=0.5 isolation cone
  Double_t max_raw_cut_dR05_;     ///< upper cut threshold on raw isolation pT-sum of cut-based tau id computed with dR=0.5 isolation cone
  Int_t min_antiElectron_;        ///< lower cut threshold on discriminator against electrons
  Int_t min_antiMuon_;            ///< lower cut threshold on discriminator against muons
  std::string cut_;
  MVASelection mva_selection_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h

