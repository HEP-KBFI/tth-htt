#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>
#include <iostream>
#include <iomanip>

class RecoHadTauSelectorBase
{
 public:
  RecoHadTauSelectorBase(int index = -1, bool debug = false);
  ~RecoHadTauSelectorBase() {}

  void set_min_pt(double min_pt) { min_pt_ = min_pt; }
  void set_max_absEta(double max_absEta) { max_absEta_ = max_absEta; }

  void set_min_id_mva_dR03(int min_id_mva_dR03) { min_id_mva_dR03_ = min_id_mva_dR03; }
  void set_min_raw_mva_dR03(double min_raw_mva_dR03) { min_raw_mva_dR03_ = min_raw_mva_dR03; }
  void set_min_id_mva_dR05(int min_id_mva_dR05) { min_id_mva_dR05_ = min_id_mva_dR05; }
  void set_min_raw_mva_dR05(double min_raw_mva_dR05) { min_raw_mva_dR05_ = min_raw_mva_dR05; }
  
  void set_min_id_cut_dR03(int min_id_cut_dR03) { min_id_cut_dR03_ = min_id_cut_dR03; }
  void set_max_raw_cut_dR03(double max_raw_cut_dR03) { max_raw_cut_dR03_ = max_raw_cut_dR03; }
  void set_min_id_cut_dR05(int min_id_cut_dR05) { min_id_cut_dR05_ = min_id_cut_dR05; }
  void set_max_raw_cut_dR05(double max_raw_cut_dR05) { max_raw_cut_dR05_ = max_raw_cut_dR05; }

  void set(const std::string& cut)
  {    
    set_min_id_mva_dR03(-1000);
    set_min_id_mva_dR05(-1000);
    set_min_id_cut_dR03(-1000);
    set_min_id_cut_dR05(-1000);
    if      ( cut == "dR05isoLoose"   ) set_min_id_cut_dR05(1);
    else if ( cut == "dR05isoMedium"  ) set_min_id_cut_dR05(2);
    else if ( cut == "dR05isoTight"   ) set_min_id_cut_dR05(3);
    else if ( cut == "dR03mvaVVLoose" ) set_min_id_mva_dR03(1); // custom WP with 95% signal efficiency, computed in RecoHadTauReader
    else if ( cut == "dR03mvaVLoose"  ) set_min_id_mva_dR03(2);
    else if ( cut == "dR03mvaLoose"   ) set_min_id_mva_dR03(3);
    else if ( cut == "dR03mvaMedium"  ) set_min_id_mva_dR03(4);
    else if ( cut == "dR03mvaTight"   ) set_min_id_mva_dR03(5);
    else if ( cut == "dR03mvaVTight"  ) set_min_id_mva_dR03(6);
    else if ( cut == "dR03mvaVVTight" ) set_min_id_mva_dR03(7);
    else {
      std::cerr << "Invalid Configuration parameter 'cut' = " << cut << " !!" << std::endl;
      assert(0);
    }
  }

  void set_min_antiElectron(int min_antiElectron) { min_antiElectron_ = min_antiElectron; }
  void set_min_antiMuon(int min_antiMuon) { min_antiMuon_ = min_antiMuon; }

  /**
   * @brief Check if hadronic tau given as function argument passes nominal selection criteria defined in Section 3.5 of AN-2015/321
   * @return True if hadronic tau passes selection; false otherwise
   */
  bool operator()(const RecoHadTau& hadTau) const;

  friend class RecoHadTauCollectionSelectorBase;
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

template<typename T>
class RecoHadTauCollectionSelector
{
 public:
  RecoHadTauCollectionSelector(int index = -1, bool debug = false)
    : selIndex_(index)
    , selector_(index, debug)
  {}
  ~RecoHadTauCollectionSelector() {}

  void set_min_pt(double min_pt) { selector_.set_min_pt(min_pt); }
  void set_max_absEta(double max_absEta) { selector_.set_max_absEta(max_absEta); }

  void set_min_id_mva_dR03(int min_id_mva_dR03) { selector_.set_min_id_mva_dR03(min_id_mva_dR03); }
  void set_min_raw_mva_dR03(double min_raw_mva_dR03) { selector_.set_min_raw_mva_dR03(min_raw_mva_dR03); }
  void set_min_id_mva_dR05(int min_id_mva_dR05) { selector_.set_min_id_mva_dR05(min_id_mva_dR05); }
  void set_min_raw_mva_dR05(double min_raw_mva_dR05) { selector_.set_min_raw_mva_dR05(min_raw_mva_dR05); }
  
  void set_min_id_cut_dR03(int min_id_cut_dR03) { selector_.set_min_id_cut_dR03(min_id_cut_dR03); }
  void set_max_raw_cut_dR03(double max_raw_cut_dR03) { selector_.set_max_raw_cut_dR03(max_raw_cut_dR03); }
  void set_min_id_cut_dR05(int min_id_cut_dR05) { selector_.set_min_id_cut_dR05(min_id_cut_dR05); }
  void set_max_raw_cut_dR05(double max_raw_cut_dR05) { selector_.set_max_raw_cut_dR05(max_raw_cut_dR05); }

  void set(const std::string& cut) { selector_.set(cut); }
  
  void set_min_antiElectron(int min_antiElectron) { selector_.set_min_antiElectron(min_antiElectron); }
  void set_min_antiMuon(int min_antiMuon) { selector_.set_min_antiMuon(min_antiMuon); }

  std::vector<const RecoHadTau*> operator()(const std::vector<const RecoHadTau*>& hadTaus) const
  {
    std::vector<const RecoHadTau*> selHadTaus;
    int idx = 0;
    for ( typename std::vector<const RecoHadTau*>::const_iterator hadTau = hadTaus.begin();
	  hadTau != hadTaus.end(); ++hadTau ) {
      if ( selector_(**hadTau) ) {
	if ( idx == selIndex_ || selIndex_ == -1 ) {
	  selHadTaus.push_back(*hadTau);
	}
	++idx;
      }
    }
    return selHadTaus;
  }
  
 protected: 
  int selIndex_;
  T selector_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorBase_h

