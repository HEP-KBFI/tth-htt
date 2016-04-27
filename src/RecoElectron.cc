#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron, RecoLepton, GenLepton

RecoElectron::RecoElectron(Double_t pt,
			   Double_t eta,
			   Double_t phi,
			   Double_t mass,
			   Int_t pdgId,
			   Double_t dxy,
			   Double_t dz,
			   Double_t relIso,
			   Double_t miniIsoCharged,
			   Double_t miniIsoNeutral,
			   Double_t sip3d,
			   Double_t mvaRawTTH,
			   Double_t jetNDauChargedMVASel,
			   Double_t jetPtRel,
			   Double_t jetPtRatio,
			   Double_t jetBtagCSV,
			   Int_t passesTightCharge,
			   Double_t mvaRawPOG,
			   Double_t sigmaEtaEta,
			   Double_t HoE,
			   Double_t deltaEta,
			   Double_t deltaPhi,
			   Double_t OoEminusOoP,
			   Int_t nLostHits,
			   Int_t passesConversionVeto)
  : RecoLepton(pt, eta, phi, mass, pdgId, dxy, dz, relIso, miniIsoCharged, miniIsoNeutral, sip3d, mvaRawTTH,
               jetNDauChargedMVASel, jetPtRel, jetPtRatio, jetBtagCSV, passesTightCharge)
  , mvaRawPOG_(mvaRawPOG)
  , sigmaEtaEta_(sigmaEtaEta)
  , HoE_(HoE)
  , deltaEta_(deltaEta)
  , deltaPhi_(deltaPhi)
  , OoEminusOoP_(OoEminusOoP)
  , nLostHits_(nLostHits)
  , passesConversionVeto_(passesConversionVeto)
{}

