#ifndef GENPARTICLE_H
#define GENPARTICLE_H

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

class GenParticle
{
public:
  GenParticle() = default;
  GenParticle(Double_t _pt,
              Double_t _eta,
              Double_t _phi,
              Double_t _mass);

  Double_t pt;   ///< pT of the particle
  Double_t eta;  ///< eta of the particle
  Double_t phi;  ///< phi of the particle
  Double_t mass; ///< mass of the particle

  math::PtEtaPhiMLorentzVector p4; ///< 4-momentum constructed from the pT, eta, phi and mass

  /**
   * @brief Calculates dR between our and the other lepton.
   * @param other  The other lepton.
   * @return dR = sqrt((eta_1 - eta_2)^2 + (phi_1 - phi_2)^2)
   */
  inline double
  dR(const GenParticle & other) const;

  /**
   * @brief Checks if a given lepton is in the same cone as our lepton.
   * @param other  The given lepton.
   * @param dR_min Max size of the lepton cone (think of it as a threshold).
   * @return True, if there is an overlap (= is in the cone); false otherwise.
   */
  bool
  is_overlap(const GenParticle & other,
             double dR_min) const;
};

#endif // GENPARTICLE_H
