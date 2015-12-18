#ifndef RECOLEPTON_CC
#define RECOLEPTON_CC

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"

class RecoLepton
  : public GenLepton
{
public:
  RecoLepton() = default;
  RecoLepton(Int_t _pdg_id,
             Double_t _pt,
             Double_t _eta,
             Double_t _phi,
             Double_t _mass,
             Double_t _dxy,
             Double_t _dz,
             Double_t _rel_iso,
             Double_t _sip3d,
             Double_t _mva_tth,
             Int_t _med_mu_id,
             Int_t _ele_mva_id,
             Int_t _lost_hits,
             Int_t _loose_id,
             Int_t _tight_charge,
             Int_t _pass_conv_veto);

  /**
   * @brief Checks whether a given lepton is an electron by its PDG id
   * @return True if it is an electron; false otherwise
   */
  bool
  is_electron() const;

  /**
   * @brief Checks whether a given lepton is a muon by its PDG id
   * @return True if it is a muon; false otherwise
   */
  bool
  is_muon() const;

  /**
   * @brief Calculates dR between our and the other lepton.
   * @param other  The other lepton.
   * @return dR = sqrt((eta_1 - eta_2)^2 + (phi_1 - phi_2)^2)
   */
  inline double
  dR(const GenLepton & other) const;

  /**
   * @brief Checks if a given lepton is in the same cone as our lepton.
   * @param other  The given lepton.
   * @param dR_min Max size of the lepton cone (think of it as a threshold).
   * @return True, if there is an overlap (= is in the cone); false otherwise.
   */
  bool
  is_overlap(const GenLepton & other,
             double dR_min) const;

  Double_t dxy;         ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz;          ///< d_{z}, distance on the z axis w.r.t PV
  Double_t rel_iso;     ///< relative isolation
  Double_t sip3d;       ///< significance of IP
  Double_t mva_tth;     ///< lepton MVA discriminator
  Int_t med_mu_id;      ///< Muon medium ID (muon only)
  Int_t ele_mva_id;     ///< Electron MVA id (electron only)
  Int_t lost_hits;      ///< Lost hits in the innermost layer of the tracker (electrons only)
  Int_t loose_id;       ///< Loose ID
  Int_t tight_charge;   ///< Tight charge
  Int_t pass_conv_veto; ///< Conversion veto (electrons only; for muons always true)
};

#endif // RECOLEPTON_CC

