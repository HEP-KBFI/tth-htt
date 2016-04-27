#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton, GenLepton

RecoLepton::RecoLepton(Double_t pt,
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
                       Int_t tightCharge)
  : GenLepton(pt, eta, phi, mass, pdgId)
  , dxy_(dxy)
  , dz_(dz)
  , relIso_(relIso)
  , miniIsoCharged_(miniIsoCharged)
  , miniIsoNeutral_(miniIsoNeutral)
  , sip3d_(sip3d)
  , mvaRawTTH_(mvaRawTTH)
  , jetNDauChargedMVASel_(jetNDauChargedMVASel)
  , jetPtRel_(jetPtRel)
  , jetPtRatio_(jetPtRatio)
  , jetBtagCSV_(jetBtagCSV)  
  , tightCharge_(tightCharge)
  , genLepton_(0)
  , genHadTau_(0)
  , genJet_(0)
{}
