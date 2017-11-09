#ifndef tthAnalysis_HiggsToTauTau_Particle_h
#define tthAnalysis_HiggsToTauTau_Particle_h

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR()

class Particle
{
 public:
  typedef math::PtEtaPhiMLorentzVector LorentzVector;

  Particle();
  Particle(Double_t pt,
	   Double_t eta,
	   Double_t phi,
	   Double_t mass);
  Particle(const Particle::LorentzVector & p4);

  virtual ~Particle() {}

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   * 
   * NOTE: get_pt and get_p4 functions needs to be virtual, so that they can be overwritten 
   *       to implement cone_pT logic for fakeable && !tight leptons in RecoLepton class
   */
  virtual Double_t pt() const { return pt_; } 
  Double_t eta() const { return eta_; } 
  Double_t phi() const { return phi_; } 
  Double_t mass() const { return mass_; } 
  
  Double_t absEta() const { return absEta_; }

  bool isValid() const;

  virtual const Particle::LorentzVector& p4() const { return p4_; }

 protected:
  Double_t pt_;   ///< pT of the particle
  Double_t eta_;  ///< eta of the particle
  Double_t phi_;  ///< phi of the particle
  Double_t mass_; ///< mass of the particle

  Double_t absEta_; ///< |eta| of the particle

  Particle::LorentzVector p4_; ///< 4-momentum constructed from the pT, eta, phi and mass

  bool isValid_; ///< true if the particle is physical (meaning that its pT > 0)
};

std::ostream& operator<<(std::ostream& stream, const Particle& particle);

#endif // tthAnalysis_HiggsToTauTau_Particle_h
