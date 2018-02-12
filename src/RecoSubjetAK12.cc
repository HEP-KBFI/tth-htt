#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK12.h"

RecoSubjetAK12::RecoSubjetAK12(const GenJet & jet,
			       Int_t idx)
  : RecoJetBase(jet, idx)
{}

RecoSubjetAK12::~RecoSubjetAK12()
{}

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetAK12 & jet)
{
  stream << static_cast<const GenJet &>(jet) << ",\n";
  return stream;
}
