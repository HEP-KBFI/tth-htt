#ifndef tthAnalysis_HiggsToTauTau_GenParticle_h
#define tthAnalysis_HiggsToTauTau_GenParticle_h

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR()

class GenParticle
{
public:
  GenParticle() = default;
  GenParticle(Double_t pt,
              Double_t eta,
              Double_t phi,
              Double_t mass);

  Double_t pt_;   ///< pT of the particle
  Double_t eta_;  ///< eta of the particle
  Double_t phi_;  ///< phi of the particle
  Double_t mass_; ///< mass of the particle

  Double_t absEta_; ///< |eta| of the particle

  math::PtEtaPhiMLorentzVector p4_; ///< 4-momentum constructed from the pT, eta, phi and mass

  friend std::ostream &
  operator<<(std::ostream & os,
             const GenParticle & o);

  /**
   * @brief Calculates dR between our and the other particle.
   * @param other  The other lepton.
   * @return dR = sqrt((eta_1 - eta_2)^2 + (phi_1 - phi_2)^2)
   */
  inline double
  dR(const GenParticle & other) const
  {
    return deltaR(eta_, phi_, other.eta_, other.phi_);
  }

  /**
   * @brief Calculates relative pT difference between our and the other particle.
   * @param other     The other particle
   * @param tolerance Tolerance, below which the the pT of the particles are though as similar
   * @return          True, if their relative difference is below the tolerance; false otherwise
   */
  bool
  rel_pT_diff(const GenParticle & other,
              double tolerance) const;

  /**
   * @brief Checks if a given particle is in the same cone as our particle.
   * @param other  The given particle.
   * @param dR_min Max size of the particle cone (think of it as a threshold).
   * @return True, if there is an overlap (= is in the cone); false otherwise.
   */
  bool
  is_overlap(const GenParticle & other,
             double dR_min) const;
};

#endif // tthAnalysis_HiggsToTauTau_GenParticle_h
