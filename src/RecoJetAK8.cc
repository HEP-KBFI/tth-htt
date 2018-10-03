#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"

RecoJetAK8::RecoJetAK8(const GenJet & jet,
			 Double_t msoftdrop,
			 const RecoSubjetAK8* subJet1,
			 const RecoSubjetAK8* subJet2,
			 Double_t tau1,
			 Double_t tau2,
			 Double_t tau3,
			 Double_t tau4,
		         Int_t jetId,
			 Int_t idx)
  : RecoJetBase(jet, idx)
  , msoftdrop_(msoftdrop)
  , subJet1_(subJet1)
  , subJet2_(subJet2)
  , tau1_(tau1)
  , tau2_(tau2)
  , tau3_(tau3)
  , tau4_(tau4)
  , jetId_(jetId)
{}

RecoJetAK8::~RecoJetAK8()
{}


Double_t
RecoJetAK8::msoftdrop() const
{
  return msoftdrop_;
}

const RecoSubjetAK8*
RecoJetAK8::subJet1() const
{
  return subJet1_.get();
}

const RecoSubjetAK8*
RecoJetAK8::subJet2() const
{
  return subJet2_.get();
}

Double_t
RecoJetAK8::tau1() const
{
  return tau1_;
}

Double_t
RecoJetAK8::tau2() const
{
  return tau2_;
}

Double_t
RecoJetAK8::tau3() const
{
  return tau3_;
}

Double_t
RecoJetAK8::tau4() const
{
  return tau4_;
}

Int_t
RecoJetAK8::jetId() const
{
  return jetId_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetAK8 & jet)
{
  stream << static_cast<const GenJet &>(jet)             << ","
            " jet ID = " << jet.jetId()                  << ","
            " msoftdrop = " << jet.msoftdrop()           << ","
            " tau1 = " << jet.tau1()                     << ","
            " tau2 = " << jet.tau2()                     << ","
            " tau3 = " << jet.tau3()                     << ",\n"
            " subjets:";
  stream << ",\n  idx1 = " << jet.subJet1();
  if(jet.subJet1())
  {
    stream << ": " << *(jet.subJet1());
  }
  stream << ",\n  idx2 = " << jet.subJet2();
  if(jet.subJet2())
  {
    stream << ": " << *(jet.subJet2());
  }
  stream << '\n';
  return stream;
}
