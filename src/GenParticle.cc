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
  , absEta_(std::fabs(eta_))
  , p4_{pt_, eta_, phi_, mass_}
{ }

GenParticle::GenParticle(const Particle::LorentzVector & p4)
  : pt_(p4.pt())
  , eta_(p4.eta())
  , phi_(p4.phi())
  , mass_(p4.mass())
  , absEta_(std::fabs(eta_))
  , p4_(p4)
{ }

std::ostream& operator<<(std::ostream& stream, const GenParticle& particle)
{
  stream << " pT = " << particle.pt() << ","
         << " eta = " << particle.eta() << ","
         << " phi = " << particle.phi() << ","
         << " mass = " << particle.mass() << std::endl;
  return stream;
}
