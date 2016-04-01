#ifndef RECOLEPTON_CC
#define RECOLEPTON_CC

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

class RecoLepton
  : public GenLepton
{
public:
  RecoLepton() = default;
  RecoLepton(Double_t _pt,
             Double_t _eta,
             Double_t _phi,
             Double_t _mass,
             Int_t _pdg_id,
             Double_t _dxy,
             Double_t _dz,
             Double_t _rel_iso,
             Double_t _sip3d,
             Double_t _mva_tth,
	     Double_t _jetPtRatio,
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

  Double_t dxy;         ///< d_{xy}, distance in the transverse plane w.r.t PV
  Double_t dz;          ///< d_{z}, distance on the z axis w.r.t PV
  Double_t rel_iso;     ///< relative isolation
  Double_t sip3d;       ///< significance of IP
  Double_t mva_tth;     ///< lepton MVA discriminator
  Double_t jetPtRatio;  ///< ratio of lepton pT to pT of nearby jet
  Int_t med_mu_id;      ///< Muon medium ID (muon only)
  Int_t ele_mva_id;     ///< Electron MVA id (electron only)
  Int_t lost_hits;      ///< Lost hits in the innermost layer of the tracker (electrons only)
  Int_t loose_id;       ///< Loose ID
  Int_t tight_charge;   ///< Tight charge
  Int_t pass_conv_veto; ///< Conversion veto (electrons only; for muons always true)
};

#endif // RECOLEPTON_CC

