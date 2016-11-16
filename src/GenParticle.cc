#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

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

std::ostream &
operator<<(std::ostream & os,
           const GenParticle & o)
{
  os << "pt = " << o.pt_ << "; "
     << "eta = " << o.eta_ << "; "
     << "phi = " << o.phi_ << "; "
     << "mass = " << o.mass_;
  return os;
}
