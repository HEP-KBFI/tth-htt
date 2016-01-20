#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#define _USE_MATH_DEFINES // M_PI
#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

GenParticle::GenParticle(Double_t _pt,
                         Double_t _eta,
                         Double_t _phi,
                         Double_t _mass)
  : pt(_pt)
  , eta(_eta)
  , phi(_phi)
  , mass(_mass)
{
  p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
}

inline double
GenParticle::dR(const GenParticle & other) const
{
  const double d_eta = std::fabs(eta - other.eta);
  double d_phi = std::fabs(phi - other.phi);
  if (d_phi > static_cast<double>(M_PI))
    d_phi -= 2 * static_cast<double>(M_PI);
  return std::sqrt(std::pow(d_eta, 2) + std::pow(d_phi, 2));
}

bool
GenParticle::is_overlap(const GenParticle & other,
                        double dR_min) const
{
  return dR(other) < dR_min;
}
