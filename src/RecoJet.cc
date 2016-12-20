#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

#include <iomanip>

RecoJet::RecoJet(Double_t pt,
                 Double_t eta,
                 Double_t phi,
                 Double_t mass,
		 Double_t corr,
		 Double_t corr_JECUp,
		 Double_t corr_JECDown,
                 Double_t BtagCSV,
		 Double_t BtagWeight,
                 Int_t idx)
  : GenJet(pt, eta, phi, mass)
  , corr_(corr)
  , corr_JECUp_(corr_JECUp)
  , corr_JECDown_(corr_JECDown)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , idx_(idx)
  , genLepton_(0)
  , genHadTau_(0)
  , genJet_(0)
{}

std::ostream& operator<<(std::ostream& stream, const RecoJet& jet)
{
  stream << " pT = " << jet.pt() << ","
	 << " eta = " << jet.eta() << "," 
	 << " phi = " << jet.phi() << "," 
	 << " mass = " << jet.mass() << "," 
	 << " CSV = " << jet.BtagCSV() << std::endl; 
  return stream;
}
