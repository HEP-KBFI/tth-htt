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
    Double_t jecUncertTotal,
	  Double_t BtagCSV,          
	  Double_t BtagWeight,
	  Double_t QGDiscr,
	  Int_t heppyFlavour,
          Int_t idx);

  virtual ~RecoJet();

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton* genLepton, bool isOwner = false) { genLepton_ = genLepton; genLepton_isOwner_ = isOwner; }
  void set_genHadTau(const GenHadTau* genHadTau, bool isOwner = false) { genHadTau_ = genHadTau; genHadTau_isOwner_ = isOwner; }
  void set_genJet(const GenJet* genJet, bool isOwner = false) { genJet_ = genJet; genJet_isOwner_ = isOwner; }

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t jecUncertTotal() const { return jecUncertTotal_; }
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
  Double_t jecUncertTotal_; ///< 1 sigma jet energy correction
  Double_t BtagCSV_;      ///< CSV b-tagging discriminator value
  Double_t BtagWeight_;   ///< weight for data/MC correction of b-tagging efficiency and mistag rate
  Double_t QGDiscr_;      ///< quark/gluon discriminator
  Int_t heppyFlavour_;    ///< Jet heppy flavour
  Int_t idx_;             ///< index of jet in the ntuple

  //---------------------------------------------------------
  // CV: needed by RecoJetWriter
  std::map<int, Double_t> BtagWeight_systematics_; 
  //---------------------------------------------------------

//--- matching to generator level particles
  const GenLepton* genLepton_;
  bool genLepton_isOwner_;
  const GenHadTau* genHadTau_;
  bool genHadTau_isOwner_;
  const GenJet* genJet_;
  bool genJet_isOwner_;
};

std::ostream& operator<<(std::ostream& stream, const RecoJet& jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h

