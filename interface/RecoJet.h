#ifndef tthAnalysis_HiggsToTauTau_RecoJet_h
#define tthAnalysis_HiggsToTauTau_RecoJet_h

#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

#include <map>
#include <ostream>

class RecoJet
  : public GenJet
{
public:
  RecoJet() = default;
  RecoJet(Double_t pt,
          Double_t eta,
          Double_t phi,
          Double_t mass,
	  Double_t corr,
	  Double_t corr_JECUp,
	  Double_t corr_JECDown,
	  Double_t BtagCSV,          
	  Double_t BtagWeight,
	  Double_t QGDiscr,
	  Int_t heppyFlavour,
          Int_t idx);

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton* genLepton) { genLepton_ = genLepton; }
  void set_genHadTau(const GenHadTau* genHadTau) { genHadTau_ = genHadTau; }
  void set_genJet(const GenJet* genJet) { genJet_ = genJet; }

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t corr() const { return corr_; }  
  Double_t corr_JECUp() const { return corr_JECUp_; }
  Double_t corr_JECDown() const { return corr_JECDown_; }
  Double_t BtagCSV() const { return BtagCSV_; }
  Double_t BtagWeight() const { return BtagWeight_; }
  Double_t QGDiscr() const { return QGDiscr_; }
  Int_t heppyFlavour() const { return heppyFlavour_; }
  Int_t idx() const { return idx_; }

  const GenLepton* genLepton() const { return genLepton_; }
  const GenHadTau* genHadTau() const { return genHadTau_; }
  const GenJet* genJet() const { return genJet_; }

  friend class RecoJetReader;
  friend class RecoJetWriter;

 protected:
  Double_t corr_;         ///< nominal jet energy correction (L1FastL2L3 for MC, L1FastL2L3Residual for data)
  Double_t corr_JECUp_;   ///< +1 sigma (upward shifted) jet energy correction
  Double_t corr_JECDown_; ///< -1 sigma (downward shifted) jet energy correction
  Double_t BtagCSV_;      ///< CSV b-tagging discriminator value
  Double_t BtagWeight_;   ///< weight for data/MC correction of b-tagging efficiency and mistag rate
  Double_t QGDiscr_;      ///< quark/gluon discriminator
  Int_t heppyFlavour_;    ///< Jet heppy flavour
  Int_t idx_;             ///< index of jet in the ntuple

  //---------------------------------------------------------
  // CV: needed by RecoJetWriter
  Double_t BtagCSVwHipMitigation_;  
  Double_t BtagCSVwoHipMitigation_; 
  std::map<int, Double_t> BtagWeight_systematics_; 
  //---------------------------------------------------------

//--- matching to generator level particles
  const GenLepton* genLepton_;
  const GenHadTau* genHadTau_;
  const GenJet* genJet_;
};

std::ostream& operator<<(std::ostream& stream, const RecoJet& jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h

