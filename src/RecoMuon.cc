#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon, RecoLepton, GenLepton

RecoMuon::RecoMuon(Double_t pt,
		   Double_t eta,
		   Double_t phi,
		   Double_t mass,
		   Int_t pdgId,
		   Double_t dxy,
		   Double_t dz,
		   Double_t relIso,
		   Double_t sip3d,
		   Double_t mvaRawTTH,
		   Double_t jetPtRatio,
		   Double_t jetBtagCSV,
		   Int_t passesTightCharge,
		   Int_t passesLooseIdPOG,
		   Int_t passesMediumIdPOG)
  : RecoLepton(pt, eta, phi, mass, pdgId, dxy, dz, relIso, sip3d, mvaRawTTH, jetPtRatio, jetBtagCSV, passesTightCharge)
  , passesLooseIdPOG_(passesLooseIdPOG)
  , passesMediumIdPOG_(passesMediumIdPOG)
{}

