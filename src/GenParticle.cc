#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include "DataFormats/Math/interface/deltaR.h" // deltaR

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
  return deltaR(eta, phi, other.eta, other.phi);
}

bool
GenParticle::rel_pT_diff(const GenParticle & other,
                         double tolerance) const
{
  return pt > 0                                    &&
         other.pt > 0                              &&
         (std::fabs(pt - other.pt) / pt) < tolerance;
}

bool
GenParticle::is_overlap(const GenParticle & other,
                        double dR_min) const
{
  return dR(other) < dR_min;
}
