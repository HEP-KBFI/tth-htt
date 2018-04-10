#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK8.h"

RecoSubjetAK8::RecoSubjetAK8(const GenJet & jet,
	//Double_t subJetIdx1,
	//Double_t subJetIdx2,
			       Int_t idx)
  : RecoJetBase(jet, idx)
{}

RecoSubjetAK8::~RecoSubjetAK8()
{}

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetAK8 & jet)
{
  stream << static_cast<const GenJet &>(jet) << ","
            " charge = " << 1.0   << ",\n";
  return stream;
}
