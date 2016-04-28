#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon, RecoLepton, GenLepton

RecoMuon::RecoMuon(Double_t pt,
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
		   Int_t charge,
		   Int_t passesLooseIdPOG,
		   Int_t passesMediumIdPOG,
		   Float_t segmentCompatibility)
  : RecoLepton(pt, eta, phi, mass, pdgId, dxy, dz, relIso, miniIsoCharged, miniIsoNeutral, sip3d, mvaRawTTH,
               jetNDauChargedMVASel, jetPtRel, jetPtRatio, jetBtagCSV, passesTightCharge, charge)
  , passesLooseIdPOG_(passesLooseIdPOG)
  , passesMediumIdPOG_(passesMediumIdPOG)
  , segmentCompatibility_(segmentCompatibility)
{}

