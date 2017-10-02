#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle

#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

Particle::Particle()
  : Particle(0., 0., 0., 0.)
{}

Particle::Particle(Double_t pt,
		   Double_t eta,
		   Double_t phi,
		   Double_t mass)
  : pt_(pt)
  , eta_(eta)
  , phi_(phi)
  , mass_(mass)
  , absEta_(std::fabs(eta_))
  , p4_{pt_, eta_, phi_, mass_}
  , isValid_(pt_ > 0.)
{ }

Particle::Particle(const Particle::LorentzVector & p4)
  : pt_(p4.pt())
  , eta_(p4.eta())
  , phi_(p4.phi())
  , mass_(p4.mass())
  , absEta_(std::fabs(eta_))
  , p4_(p4)
  , isValid_(true)
{ }

bool
Particle::isValid() const
{
  return isValid_;
}

std::ostream& operator<<(std::ostream& stream, const Particle& particle)
{
  stream << " pT = " << particle.pt() << ","
         << " eta = " << particle.eta() << ","
         << " phi = " << particle.phi() << ","
         << " mass = " << particle.mass() << std::endl;
  return stream;
}
