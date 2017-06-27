#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau, GenParticle

#include <iomanip>

RecoHadTau::RecoHadTau(Double_t pt,
		       Double_t eta,
		       Double_t phi,
		       Double_t mass,
		       Int_t charge,
		       Double_t dxy,
		       Double_t dz,
		       Int_t decayMode,
		       Int_t decayModeFinding,
		       Int_t decayModeFindingNew,
		       Int_t id_mva_dR03,		       
		       Double_t raw_mva_dR03,
		       Int_t id_mva_dR05,
		       Double_t raw_mva_dR05,
		       Int_t id_cut_dR03,
		       Double_t raw_cut_dR03,
		       Int_t id_cut_dR05,
		       Double_t raw_cut_dR05,
		       Int_t antiElectron,
		       Int_t antiMuon)
  : Particle(pt, eta, phi, mass)
  , charge_(charge)
  , dxy_(dxy)
  , dz_(dz)
  , decayMode_(decayMode)
  , decayModeFinding_(decayModeFinding)
  , decayModeFindingNew_(decayModeFindingNew)
  , id_mva_dR03_(id_mva_dR03)
  , raw_mva_dR03_(raw_mva_dR03)
  , id_mva_dR05_(id_mva_dR05)
  , raw_mva_dR05_(raw_mva_dR05)
  , id_cut_dR03_(id_cut_dR03)
  , raw_cut_dR03_(raw_cut_dR03)
  , id_cut_dR05_(id_cut_dR05)
  , raw_cut_dR05_(raw_cut_dR05)   
  , antiElectron_(antiElectron)
  , antiMuon_(antiMuon)
  , genLepton_(0)
  , genHadTau_(0)
  , genJet_(0)
  , isLoose_(false)
  , isFakeable_(false)
  , isTight_(false)
{}

std::ostream& operator<<(std::ostream& stream, const RecoHadTau& hadTau)
{
  stream << " pT = " << hadTau.pt() << ","
	 << " eta = " << hadTau.eta() << "," 
	 << " phi = " << hadTau.phi() << "," 
	 << " mass = " << hadTau.mass() << "," 
	 << " charge = " << hadTau.charge() << std::endl; 
  stream << " decayModeFinding = " << hadTau.decayModeFinding() << "," 
	 << " id_mva_dR03 = " << hadTau.id_mva_dR03() << " (raw = " << hadTau.raw_mva_dR03() << ")," 
	 << " antiElectron = " << hadTau.antiElectron() << ", antiMuon = " << hadTau.antiMuon()  << std::endl;
  stream << "gen. matching:" 
	 << " lepton = " << hadTau.genLepton() << "," 
	 << " hadTau = " << hadTau.genHadTau() << "," 
	 << " jet = " << hadTau.genJet() << std::endl;
  return stream;
}

