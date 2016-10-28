#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton, GenLepton

#include <iomanip>

RecoLepton::RecoLepton(Double_t pt,
                       Double_t eta,
                       Double_t phi,
                       Double_t mass,
                       Int_t    pdgId,
                       Double_t dxy,
                       Double_t dz,
                       Double_t relIso,
                       Double_t chargedHadRelIso03,
                       Double_t miniIsoCharged,
                       Double_t miniIsoNeutral,
                       Double_t sip3d,
                       Double_t mvaRawTTH,
                       Double_t jetNDauChargedMVASel,
                       Double_t jetPtRel,
                       Double_t jetPtRatio,
                       Double_t jetBtagCSV,
                       Int_t    tightCharge,
                       Int_t    charge)
  : GenLepton(pt, eta, phi, mass, pdgId)
  , dxy_(dxy)
  , dz_(dz)
  , relIso_(relIso)
  , chargedHadRelIso03_(chargedHadRelIso03)
  , miniIsoCharged_(miniIsoCharged)
  , miniIsoNeutral_(miniIsoNeutral)
  , sip3d_(sip3d)
  , mvaRawTTH_(mvaRawTTH)
  , jetNDauChargedMVASel_(jetNDauChargedMVASel)
  , jetPtRel_(jetPtRel)
  , jetPtRatio_(jetPtRatio)
  , jetBtagCSV_(jetBtagCSV)
  , tightCharge_(tightCharge)
  , charge_(charge)
  , genLepton_(0)
  , genHadTau_(0)
  , genJet_(0)
{}


std::ostream& operator<<(std::ostream& stream, const RecoLepton& lepton)
{
  stream << " pT = " << lepton.pt_ << ","
         << " eta = " << lepton.eta_ << ","
         << " phi = " << lepton.phi_ << ","
         << " pdgId = " << lepton.pdgId_ << std::endl;
  stream << " dxy = " << lepton.dxy_ << ", dz = " << lepton.dz_ << ", sip3d = " <<
    lepton.sip3d_ << std::endl;
  stream << " relIso = " << lepton.relIso_ << std::endl;
  stream << " chargedHadRelIso03 = " << lepton.chargedHadRelIso03_ << std::endl;
  stream << " tightCharge = " << lepton.tightCharge_ << std::endl;
  stream << " mvaRawTTH = " << lepton.mvaRawTTH_ << std::endl;
  return stream;
}
