#ifndef tthAnalysis_HiggsToTauTau_RecoMEt_h
#define tthAnalysis_HiggsToTauTau_RecoMEt_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // Particle::LorentzVector

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TMatrixD.h> // TMatrixD
#include "DataFormats/Math/interface/deltaR.h" // deltaR()

class RecoMEt
{
public:
  RecoMEt();
  RecoMEt(Double_t pt,
	  Double_t phi,
	  Double_t covXX,
	  Double_t covXY,
	  Double_t covYY);
  RecoMEt(const math::PtEtaPhiMLorentzVector & p4, const TMatrixD& cov);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t pt() const { return pt_; }
  Double_t phi() const { return phi_; }

  Double_t covXX() const { return covXX_; }
  Double_t covXY() const { return covXY_; }
  Double_t covYY() const { return covYY_; }
  
  const Particle::LorentzVector& p4() const { return p4_; }

  const TMatrixD& cov() const { return cov_; }

 protected:
  Double_t pt_;   ///< pT of missing transverse momentum vector
  Double_t phi_;  ///< phi of missing transverse momentum vector

  Double_t covXX_; ///< XX element of MET resolution matrix
  Double_t covXY_; ///< XY element of MET resolution matrix
  Double_t covYY_; ///< YY element of MET resolution matrix
    
  math::PtEtaPhiMLorentzVector p4_; ///< 4-momentum constructed from pT and phi, assuming eta and mass to be equal to zero

  TMatrixD cov_; ///< MET resolution matrix
};

std::ostream& operator<<(std::ostream& stream, const RecoMEt& met);

#endif // tthAnalysis_HiggsToTauTau_RecoMEt_h
