#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton, GenParticle

GenPhoton::GenPhoton(Double_t pt,
                     Double_t eta,
                     Double_t phi,
                     Double_t mass,
                     Int_t pdgId)
  : GenParticle(pt, eta, phi, mass, pdgId, 0)
{}

std::ostream &
operator<<(std::ostream & stream,
           const GenPhoton & genPhoton)
{
  stream << static_cast<const GenPhoton &>(genPhoton);
  return stream;
}
