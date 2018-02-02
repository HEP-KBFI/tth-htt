#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau, GenParticleBase

GenHadTau::GenHadTau(Double_t pt,
                     Double_t eta,
                     Double_t phi,
                     Double_t mass,
                     Int_t charge)
  : GenParticle(pt, eta, phi, mass, 0, charge)
{}

std::ostream &
operator<<(std::ostream & stream,
           const GenHadTau & hadTau)
{
  stream << static_cast<const Particle &>(hadTau) << ","
            " charge = " << hadTau.charge();
  return stream;
}
