#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h"

RecoJetAK12::RecoJetAK12(const GenJet & jet,
			 Double_t charge,
			 Double_t pullEta,
			 Double_t pullPhi,
			 Double_t pullMag,
			 Double_t QjetVolatility,
			 Double_t msoftdrop,
			 const RecoSubjetAK12* subJet1,
			 const RecoSubjetAK12* subJet2,
			 Double_t tau1,
			 Double_t tau2,
			 Double_t tau3,
			 Double_t tau4,
			 Int_t idx)
  : RecoJetBase(jet, idx)
  , charge_(charge)
  , pullEta_(pullEta)
  , pullPhi_(pullPhi)
  , pullMag_(pullMag)
  , QjetVolatility_(QjetVolatility)
  , msoftdrop_(msoftdrop)
  , subJet1_(subJet1)
  , subJet2_(subJet2)
  , tau1_(tau1)
  , tau2_(tau2)
  , tau3_(tau3)
  , tau4_(tau4)
{}

RecoJetAK12::~RecoJetAK12()
{}

Double_t 
RecoJetAK12::charge() const
{
  return charge_;
}

Double_t 
RecoJetAK12::pullEta() const
{
  return pullEta_;
}

Double_t 
RecoJetAK12::pullPhi() const
{
  return pullPhi_;
}

Double_t 
RecoJetAK12::pullMag() const
{
  return pullMag_;
}

Double_t 
RecoJetAK12::QjetVolatility() const
{
  return QjetVolatility_;
}

Double_t 
RecoJetAK12::msoftdrop() const
{
  return msoftdrop_;
}

const RecoSubjetAK12* 
RecoJetAK12::subJet1() const
{
  return subJet1_;
}
 
const RecoSubjetAK12* 
RecoJetAK12::subJet2() const
{
  return subJet2_;
}
 
Double_t 
RecoJetAK12::tau1() const
{
  return tau1_;
}

Double_t 
RecoJetAK12::tau2() const
{
  return tau2_;
}

Double_t 
RecoJetAK12::tau3() const
{
  return tau3_;
}

Double_t 
RecoJetAK12::tau4() const
{
  return tau4_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoJetAK12 & jet)
{
  stream << static_cast<const GenJet &>(jet)             << ","
            " charge = " << jet.charge()                 << ","
            " QjetVolatility = " << jet.QjetVolatility() << ","
            " msoftdrop = " << jet.msoftdrop()           << ","
            " tau1 = " << jet.tau1()                     << ","
            " tau2 = " << jet.tau2()                     << ",\n"
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
