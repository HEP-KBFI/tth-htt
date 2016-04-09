#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

GenParticle::GenParticle(Double_t pt,
                         Double_t eta,
                         Double_t phi,
                         Double_t mass)
  : pt_(pt)
  , eta_(eta)
  , phi_(phi)
  , mass_(mass)
{
  absEta_ = std::fabs(eta_);
  p4_ = math::PtEtaPhiMLorentzVector(pt_, eta_, phi_, mass_);
}

inline double
GenParticle::dR(const GenParticle & other) const
{
  return deltaR(eta_, phi_, other.eta_, other.phi_);
}

bool
GenParticle::rel_pT_diff(const GenParticle & other,
                         double tolerance) const
{
  return pt_ > 0.                                    &&
         other.pt_ > 0.                              &&
         (std::fabs(pt_ - other.pt_) / pt_) < tolerance;
}

bool
GenParticle::is_overlap(const GenParticle & other,
                        double dR_min) const
{
  return dR(other) < dR_min;
}
