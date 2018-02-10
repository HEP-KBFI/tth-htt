#ifndef tthAnalysis_HiggsToTauTau_RecoJetBase_h
#define tthAnalysis_HiggsToTauTau_RecoJetBase_h

/** \class RecoJetBase
 *
 * Base-class for different type of jets
 *
 * Derrived classes:
 *   RecoJet      = "resolved" anti-kT jets with dR=0.4
 *   RecoJetAK12  = anti-kT jet with dR=1.2 and jet sub-structure reconstruction, used for reconstruction of boosted hadronic W bosons
 *   RecoJetHTTv2 = collection of jets reconstructed by the hep-top-tagger (HTTv2) algorithm, used for reconstruction of boosted hadronic tops
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#include <map> // std::map<,>

// forward declarations
class GenLepton;
class GenHadTau;

class RecoJetBase
  : public GenJet
{
public:
  RecoJetBase() = default;
  RecoJetBase(const GenJet & particle,
	      Int_t idx);

  virtual ~RecoJetBase();

  /**
   * @brief Set links to generator level particles (matched by dR)
   */
  void set_genLepton(const GenLepton * genLepton, bool isOwner = false);
  void set_genHadTau(const GenHadTau * genHadTau, bool isOwner = false);
  void set_genJet(const GenJet * genJet, bool isOwner = false);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Int_t idx() const;

  const GenLepton * genLepton() const;
  const GenHadTau * genHadTau() const;
  const GenJet * genJet() const;

protected:
  Int_t idx_;             ///< index of jet in the ntuple

//--- matching to generator level particles
  const GenLepton * genLepton_;
  bool genLepton_isOwner_;
  const GenHadTau * genHadTau_;
  bool genHadTau_isOwner_;
  const GenJet * genJet_;
  bool genJet_isOwner_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetBase_h

