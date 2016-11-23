#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton, GenParticle

#include <cmath> // std::abs

GenLepton::GenLepton(Double_t pt,
                     Double_t eta,
                     Double_t phi,
                     Double_t mass,
                     Int_t pdgId)
  : GenParticle(pt, eta, phi, mass)
  , pdgId_(pdgId)
  , charge_(-pdgId_ / std::abs(pdgId_))
{ }

GenLepton::GenLepton(const math::PtEtaPhiMLorentzVector & p4,
                     Int_t pdgId)
  : GenParticle(p4)
  , pdgId_(pdgId)
  , charge_(-pdgId_ / std::abs(pdgId_))
{ }

std::ostream &
operator<<(std::ostream & os,
           const GenLepton & o)
{
  operator<<(os, static_cast<GenParticle>(o));
  os << "; charge = " << o.charge_;
  return os;
}
