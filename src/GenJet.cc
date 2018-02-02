#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet, GenParticle

GenJet::GenJet(Double_t pt,
               Double_t eta,
               Double_t phi,
               Double_t mass)
  : GenParticle(pt, eta, phi, mass, 0, 0)
{}

std::ostream &
operator<<(std::ostream & stream,
           const GenJet & genJet)
{
  stream << static_cast<const GenParticle &>(genJet);
  return stream;
}
