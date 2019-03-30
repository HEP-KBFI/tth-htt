#ifndef tthAnalysis_HiggsToTauTau_TrigObj_h
#define tthAnalysis_HiggsToTauTau_TrigObj_h

/** @class TrigObj
 *
 * Class to access information for "trigger objects" 
 * (HLT filter objects with associated L1 information)
 *
 * @author Christian Veelken, Tallinn
 *
 */

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector

class TrigObj
{
public:
  TrigObj();
  TrigObj(Double_t pt,
          Double_t eta,
          Double_t phi,
          Int_t filterBits,
          Int_t id,
          Double_t l1pt,
          Double_t l1pt_2,
          Int_t l1iso);

  virtual ~TrigObj();

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t pt() const;
  Double_t eta() const;
  Double_t phi() const;
  Int_t filterBits() const;
  Int_t id() const;
  Double_t l1pt() const;
  Double_t l1pt_2() const;
  Int_t l1iso() const;

  const Particle::LorentzVector & p4() const;

  friend class TrigObjReader;

protected:
  Double_t pt_;                ///< pT of the trigger object
  Double_t eta_;               ///< eta of the trigger object
  Double_t phi_;               ///< phi of the trigger object
  Particle::LorentzVector p4_; ///< 4-momentum constructed from the pT, eta, and phi, assuming trigger object to be massless
  Int_t filterBits_;           ///< extra bits of associated information (cf. https://test-cms-nanoaod-integration.web.cern.ch/integration/master/mc94X_doc.html#TrigObj )
  Int_t id_;                   ///< ID of the object: 11 = Electron (PixelMatched e/gamma), 22 = Photon (PixelMatch-vetoed e/gamma), 13 = Muon, 15 = Tau, 1 = Jet, 2 = MET, 3 = HT, 4 = MHT
  Double_t l1pt_;              ///< pT of 1st associated L1 seed
  Double_t l1pt_2_;            ///< pT of 2nd associated L1 seed (used for cross triggers with two L1 seeds)
  Int_t l1iso_;                ///< isolation of associated L1 seed
};

std::ostream &
operator<<(std::ostream & stream,
           const TrigObj & trigObj);

#endif // tthAnalysis_HiggsToTauTau_TrigObj_h

