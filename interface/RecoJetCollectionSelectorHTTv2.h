#ifndef tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorHTTv2_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h" // RecoJet

class RecoJetSelectorHTTv2
{
public:
  explicit RecoJetSelectorHTTv2(int era,
                                int index = -1,
                                bool debug = false);
  ~RecoJetSelectorHTTv2() {}

  /**
   * @brief Set cut thresholds
   */
  void set_min_pt(double min_pt);
  void set_max_absEta(double max_absEta);
  void set_subJet1_min_jetId(int subJet1_min_jetId); // bool: eta cut in subjets is already here (also pt>20 GeV)
  void set_subJet2_min_jetId(int subJet2_min_jetId);
  void set_subJet3_min_jetId(int subJet3_min_jetId);
  void set_subJet1_min_pt(int subJet1_min_pt); // reccomendation in documentation is 30 GeV
  void set_subJet2_min_pt(int subJet2_min_pt);
  void set_subJet3_min_pt(int subJet3_min_pt);
  /**
   * @brief Get cut thresholds
   */
  double get_min_pt() const;
  double get_max_absEta() const;
  int get_subJet1_min_jetId() const;
  int get_subJet2_min_jetId() const;
  int get_subJet3_min_jetId() const;
  int get_subJet1_min_pt() const;
  int get_subJet2_min_pt() const;
  int get_subJet3_min_pt() const;

  /**
   * @brief
   * @return True if jet passes selection; false otherwise
   */
  bool
  operator()(const RecoJetHTTv2 & jet) const;

protected:
  Double_t min_pt_;     ///< lower cut threshold on pT
  Double_t max_absEta_; ///< upper cut threshold on absolute value of eta
  Int_t subJet1_min_jetId_;     ///< lower cut threshold on jet ID value
  Int_t subJet2_min_jetId_;     ///< lower cut threshold on jet ID value
  Int_t subJet3_min_jetId_;     ///< lower cut threshold on jet ID value
  Int_t subJet1_min_pt_;     ///< lower cut threshold on jet pt value
  Int_t subJet2_min_pt_;     ///< lower cut threshold on jet pt value
  Int_t subJet3_min_pt_;     ///< lower cut threshold on jet pt value
  bool debug_;
};

typedef ParticleCollectionSelector<RecoJetHTTv2, RecoJetSelectorHTTv2> RecoJetCollectionSelectorHTTv2;

#endif // tthAnalysis_HiggsToTauTau_RecoJetCollectionSelectorHTTv2_h
