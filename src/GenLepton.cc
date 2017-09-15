#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton, GenParticle

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <cmath> // std::abs

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
                     Double_t charge)
  : GenParticle(pt, eta, phi, mass, pdgId, charge)
{}

GenLepton::GenLepton(const math::PtEtaPhiMLorentzVector & p4,
                     Int_t pdgId)
  : GenParticle(p4, pdgId, -pdgId/std::abs(pdgId))
{}

std::ostream& operator<<(std::ostream& stream, const GenLepton& lepton)
{
  stream << " pT = " << lepton.pt() << ","
         << " eta = " << lepton.eta() << ","
         << " phi = " << lepton.phi() << ","
         << " charge = " << lepton.charge() << std::endl;
  return stream;
}

