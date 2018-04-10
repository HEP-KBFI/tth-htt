#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

RecoJetHTTv2::RecoJetHTTv2(const GenJet & jet,
			   Double_t area,
			   const RecoSubjetHTTv2* subJet1,
			   const RecoSubjetHTTv2* subJet2,
			   const RecoSubjetHTTv2* subJet3,
			   Double_t fRec,
			   Double_t Ropt,
			   Double_t RoptCalc,
			   Double_t ptForRoptCalc,
			   Double_t tau1,
			   Double_t tau2,
			   Double_t tau3,
				 //Double_t mass, // quantities calculated on filtered jets
				 //Double_t pt,
				 //Double_t phi,
				 //Double_t eta,
			   Int_t idx)
  : RecoJetBase(jet, idx)
  , area_(area)
  , subJet1_(subJet1)
  , subJet2_(subJet2)
  , subJet3_(subJet3)
  , fRec_(fRec)
  , Ropt_(Ropt)
  , RoptCalc_(RoptCalc)
  , ptForRoptCalc_(ptForRoptCalc)
  , tau1_(tau1)
  , tau2_(tau2)
  , tau3_(tau3) //
	//, mass_(mass)
	//, pt_(pt)
	//, phi_(phi)
	//, eta_(eta)
{}

RecoJetHTTv2::~RecoJetHTTv2()
{}

Double_t
RecoJetHTTv2::area() const
{
  return area_;
}

const RecoSubjetHTTv2*
RecoJetHTTv2::subJet1() const
{
  return subJet1_.get();
}

const RecoSubjetHTTv2*
RecoJetHTTv2::subJet2() const
{
  return subJet2_.get();
}

const RecoSubjetHTTv2*
RecoJetHTTv2::subJet3() const
{
  return subJet3_.get();
}

Double_t
RecoJetHTTv2::fRec() const
{
  return fRec_;
}

Double_t
RecoJetHTTv2::Ropt() const
{
  return Ropt_;
}

Double_t
RecoJetHTTv2::RoptCalc() const
{
  return RoptCalc_;
}

Double_t
RecoJetHTTv2::ptForRoptCalc() const
{
  return ptForRoptCalc_;
}

Double_t
RecoJetHTTv2::tau1() const
{
  return tau1_;
}

Double_t
RecoJetHTTv2::tau2() const
{
  return tau2_;
}

Double_t
RecoJetHTTv2::tau3() const
{
  return tau3_;
}

/*
Double_t
RecoJetHTTv2::mass() const
{
  return mass_;
}

Double_t
RecoJetHTTv2::pt() const
{
  return pt_;
}

Double_t
RecoJetHTTv2::eta() const
{
  return eta_;
}

Double_t
RecoJetHTTv2::phi() const
{
  return phi_;
}
*/
std::ostream &
operator<<(std::ostream & stream,
           const RecoJetHTTv2 & jet)
{
  stream << static_cast<const GenJet &>(jet)         << ","
            " area = " << jet.area()                 << ","
            " fRec = " << jet.fRec()                 << ","
            " Ropt = " << jet.Ropt()                 << ","
            " tau1 = " << jet.tau1()                 << ","
            " tau2 = " << jet.tau2()                 << ","
            " tau3 = " << jet.tau3()                 << ",\n"
						//" mass = " << jet.mass()                 << ","
						//" pt = " << jet.pt()                     << ","
						//" eta = " << jet.eta()                   << ","
						//" phi = " << jet.phi()                   << ",\n"
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
  stream << ",\n  idx3 = " << jet.subJet3();
  if(jet.subJet3())
  {
    stream << ": " << *(jet.subJet3());
  }
  stream << '\n';
  return stream;
}
