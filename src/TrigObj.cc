#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h"

TrigObj::TrigObj()
  : TrigObj(0., 0., 0., -1, -1, 0., 0., -1)
{}

TrigObj::TrigObj(Double_t pt,
		 Double_t eta,
		 Double_t phi,
		 Int_t filterBits,
		 Int_t id,
		 Double_t l1pt,
		 Double_t l1pt_2,
		 Int_t l1iso)
  : pt_(pt)
  , eta_(eta)
  , phi_(phi)
  , p4_(pt_, eta_, phi_, 0.)
  , filterBits_(filterBits)
  , id_(id)
  , l1pt_(l1pt)
  , l1pt_2_(l1pt_2)
  , l1iso_(l1iso)
{}

TrigObj::~TrigObj()
{}

Double_t 
TrigObj::pt() const
{
  return pt_;
}

Double_t 
TrigObj::eta() const
{
  return eta_;
}
 
Double_t 
TrigObj::phi() const
{
  return phi_;
}
 
Int_t 
TrigObj::filterBits() const
{
  return filterBits_;
}

Int_t 
TrigObj::id() const
{
  return id_;
}
 
Double_t 
TrigObj::l1pt() const
{
  return l1pt_;
}
 
Double_t 
TrigObj::l1pt_2() const
{
  return l1pt_2_;
}

Int_t 
TrigObj::l1iso() const
{
  return l1iso_;
}

const Particle::LorentzVector & 
TrigObj::p4() const
{
  return p4_;
}

std::ostream &
operator<<(std::ostream & stream,
           const TrigObj & trigObj)
{
  stream << " pT = "              << trigObj.pt()         << ","
            " eta = "             << trigObj.eta()        << ","
            " phi = "             << trigObj.phi()        << ","
            " HLT filter bits = " << trigObj.filterBits() << ","
            " Id = "              << trigObj.id()         << ","
            " L1 pT: 1st seed = " << trigObj.l1pt()       << ", 2nd seed = " << trigObj.l1pt_2() << ","
            " L1 isolation =    " << trigObj.l1iso()      << '\n';
  return stream;
}
