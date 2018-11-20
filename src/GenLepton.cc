#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton, GenParticle

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

GenLepton::GenLepton(Double_t pt,
                     Double_t eta,
                     Double_t phi,
                     Double_t mass,
                     Int_t pdgId)
  : GenLepton(pt, eta, phi, mass, pdgId, -boost::math::sign(pdgId))
{}

GenLepton::GenLepton(Double_t pt,
                     Double_t eta,
                     Double_t phi,
                     Double_t mass,
                     Int_t pdgId,
                     Int_t charge)
  : GenParticle(pt, eta, phi, mass, pdgId, charge)
{}

GenLepton::GenLepton(const math::PtEtaPhiMLorentzVector & p4,
                     Int_t pdgId)
  : GenParticle(p4, pdgId, -pdgId / std::abs(pdgId))
{}

std::ostream &
operator<<(std::ostream & stream,
           const GenLepton & lepton)
{
  stream << static_cast<GenParticle>(lepton);
  return stream;
}

