#ifndef tthAnalysis_HiggsToTauTau_RecoHadTau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTau_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

class RecoHadTau
  : public GenParticle
{
 public:
  RecoHadTau() = default;
  RecoHadTau(Double_t pt,
	     Double_t eta,
	     Double_t phi,
	     Double_t mass,
	     Int_t pdgId,
	     Double_t dz,
	     Int_t decayModeFinding,
	     Int_t id_mva_dR03,
	     Int_t id_mva_dR05,
	     Int_t id_cut_dR03,
	     Int_t id_cut_dR05,
	     Int_t antiElectron,
	     Int_t antiMuon);

  Int_t pdgId_;
  Double_t dz_;            ///< d_{z}, distance on the z axis w.r.t PV
  Int_t decayModeFinding_; ///< decayModeFinding discriminator
  Int_t id_mva_dR03_;      ///< MVA-based tau id computed with dR=0.3 isolation cone
  Int_t id_mva_dR05_;      ///< MVA-based tau id computed with dR=0.5 isolation cone
  Int_t id_cut_dR03_;      ///< cut-based tau id computed with dR=0.3 isolation cone
  Int_t id_cut_dR05_;      ///< cut-based tau id computed with dR=0.5 isolation cone
  Int_t antiElectron_;     ///< discriminator against electrons
  Int_t antiMuon_;         ///< discriminator against muons

//--- matching to generator level particles
  const GenLepton* genLepton_;
  const GenHadTau* genHadTau_;
  const GenJet* genJet_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTau_h

