#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK12.h"

RecoSubjetAK12::RecoSubjetAK12(const GenJet & jet,
			       Double_t charge,
			       Double_t pullEta,
			       Double_t pullPhi,
			       Double_t pullMag,
			       Int_t idx)
  : RecoJetBase(jet, idx)
  , charge_(charge)
  , pullEta_(pullEta)
  , pullPhi_(pullPhi)
  , pullMag_(pullMag)
{}

RecoSubjetAK12::~RecoSubjetAK12()
{}

Double_t
RecoSubjetAK12::charge() const
{
  return charge_;
}

Double_t
RecoSubjetAK12::pullEta() const
{
  return pullEta_;
}

Double_t
RecoSubjetAK12::pullPhi() const
{
  return pullPhi_;
}

Double_t
RecoSubjetAK12::pullMag() const
{
  return pullMag_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetAK12 & jet)
{
  stream << static_cast<const GenJet &>(jet) << ","
            " charge = " << jet.charge()     << ",\n";
  return stream;
}
