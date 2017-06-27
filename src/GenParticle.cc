#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle, Particle

#include <cmath> // std::abs

GenParticle::GenParticle(Double_t pt,
			 Double_t eta,
			 Double_t phi,
			 Double_t mass,
			 Int_t pdgId,
			 Double_t charge)
  : Particle(pt, eta, phi, mass)
  , pdgId_(pdgId)
  , charge_(charge)
{}

GenParticle::GenParticle(const math::PtEtaPhiMLorentzVector & p4,
			 Int_t pdgId,
			 Double_t charge)
  : Particle(p4)
  , pdgId_(pdgId)
  , charge_(charge)
{}

std::ostream& operator<<(std::ostream& stream, const GenParticle& particle)
{
  stream << " E = " << particle.p4().energy() << " (p = " << particle.p4().P() << "),"
	 << " pT = " << particle.pt() << ","
         << " eta = " << particle.eta() << ","
         << " phi = " << particle.phi() << ","
	 << " mass = " << particle.mass() << ","
         << " pdgId = " << particle.pdgId() << " (charge = " << particle.charge() << ")" << std::endl;
  return stream;
}

