#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle, Particle

GenParticle::GenParticle()
  : GenParticle(0., 0., 0., 0., 0, 0)
{}

GenParticle::GenParticle(Double_t pt,
                         Double_t eta,
                         Double_t phi,
                         Double_t mass,
                         Int_t pdgId,
                         Int_t charge)
  : Particle(pt, eta, phi, mass)
  , pdgId_(pdgId)
  , charge_(charge)
  , isMatchedToReco_(false)
{}

GenParticle::GenParticle(const math::PtEtaPhiMLorentzVector & p4,
                         Int_t pdgId,
                         Int_t charge)
  : Particle(p4)
  , pdgId_(pdgId)
  , charge_(charge)
  , isMatchedToReco_(false)
{}

Int_t
GenParticle::pdgId() const
{
  return pdgId_;
}

Int_t
GenParticle::charge() const
{
  return charge_;
}

void
GenParticle::setMatchedToReco()
{
  isMatchedToReco_ = true;
}

bool
GenParticle::isMatchedToReco() const
{
  return isMatchedToReco_;
}

std::ostream &
operator<<(std::ostream & stream,
           const GenParticle & particle)
{
  stream << static_cast<const Particle &>(particle) << ","
            " pdgId = "   << particle.pdgId()
         << " (charge = " << particle.charge() << ')'
  ;
  return stream;
}
