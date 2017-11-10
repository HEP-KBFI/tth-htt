#ifndef tthAnalysis_HiggsToTauTau_RecoMEt_h
#define tthAnalysis_HiggsToTauTau_RecoMEt_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // Particle::LorentzVector

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <Rtypes.h> // Int_t, Long64_t, Float_t
#include <TMatrixD.h> // TMatrixD

#include <map> // std::map<,>

class RecoMEt
{
public:
  RecoMEt();
  RecoMEt(Float_t pt,
          Float_t phi,
          Float_t covXX,
          Float_t covXY,
          Float_t covYY);
  RecoMEt(const math::PtEtaPhiMLorentzVector & p4,
          const TMatrixD& cov);
  RecoMEt &
  operator=(const RecoMEt & other);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Double_t pt() const { return static_cast<Double_t>(default_.pt_); }
  Double_t phi() const { return static_cast<Double_t>(default_.phi_); }

  Double_t covXX() const { return static_cast<Double_t>(covXX_); }
  Double_t covXY() const { return static_cast<Double_t>(covXY_); }
  Double_t covYY() const { return static_cast<Double_t>(covYY_); }
  
  const Particle::LorentzVector& p4() const { return p4_; }

  const TMatrixD& cov() const { return cov_; }

  friend class RecoMEtReader;
  friend class RecoMEtWriter;

protected:

  struct MEt
  {
    MEt()
     : pt_(0.)
     , phi_(0.)
    {}
    MEt(Float_t pt,
        Float_t phi)
      : pt_(pt)
      , phi_(phi)
    {}
    MEt &
    operator=(const MEt & other)
    {
      pt_ = other.pt_;
      phi_ = other.phi_;
      return *this;
    }
    Float_t pt_;  ///< pT of missing transverse momentum vector
    Float_t phi_; ///< phi of missing transverse momentum vector
  };

  MEt default_; ///< Default values
  std::map<int, MEt> systematics_; ///< Needed by RecoMEtReader/Writer

  Float_t covXX_; ///< XX element of MET resolution matrix
  Float_t covXY_; ///< XY element of MET resolution matrix
  Float_t covYY_; ///< YY element of MET resolution matrix

  ///< (default) 4-momentum constructed from pT and phi, assuming eta and mass to be equal to zero
  math::PtEtaPhiMLorentzVector p4_;

  TMatrixD cov_; ///< MET resolution matrix

  ///< Update cov and p4 (needed by RecoMEtReader)
  void update();
  void update_p4();
  void update_cov();
};

std::ostream& operator<<(std::ostream& stream, const RecoMEt& met);

#endif // tthAnalysis_HiggsToTauTau_RecoMEt_h
