#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h"

RecoSubjetHTTv2::RecoSubjetHTTv2(const GenJet & jet,
                                 Bool_t IDPassed,
                                 Double_t BtagCSV,
                                 Double_t area,
                                 Int_t idx)
  : RecoJetBase(jet, idx)
  , IDPassed_(IDPassed)
  , BtagCSV_(BtagCSV)
  , area_(area)
{}

RecoSubjetHTTv2::~RecoSubjetHTTv2()
{}

Bool_t
RecoSubjetHTTv2::IDPassed() const
{
  return IDPassed_;
}

Double_t
RecoSubjetHTTv2::BtagCSV() const
{
  return BtagCSV_;
}

Double_t
RecoSubjetHTTv2::area() const
{
  return area_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetHTTv2 & jet)
{
  stream << static_cast<const GenJet &>(jet) << ","
            " IDPassed = " << jet.IDPassed() << ","
            " BtagCSV = " << jet.BtagCSV()   << ","
            " area = " << jet.area()         << ",\n";
  return stream;
}
