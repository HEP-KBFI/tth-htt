#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron, RecoLepton, GenLepton

RecoElectron::RecoElectron(Double_t pt,
                           Double_t eta,
                           Double_t phi,
                           Double_t mass,
                           Int_t    pdgId,
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
                           Int_t    passesTightCharge,
                           Int_t    charge,
                           Double_t mvaRawPOG,
                           Double_t sigmaEtaEta,
                           Double_t HoE,
                           Double_t deltaEta,
                           Double_t deltaPhi,
                           Double_t OoEminusOoP,
                           Int_t    nLostHits,
                           Int_t    passesConversionVeto)
  : RecoLepton(pt, eta, phi, mass, pdgId, dxy, dz, relIso, 0, miniIsoCharged, miniIsoNeutral, sip3d, mvaRawTTH,
               jetNDauChargedMVASel, jetPtRel, jetPtRatio, jetBtagCSV, passesTightCharge, charge)
  , mvaRawPOG_(mvaRawPOG)
  , sigmaEtaEta_(sigmaEtaEta)
  , HoE_(HoE)
  , deltaEta_(deltaEta)
  , deltaPhi_(deltaPhi)
  , OoEminusOoP_(OoEminusOoP)
  , nLostHits_(nLostHits)
  , passesConversionVeto_(passesConversionVeto)
{}

std::ostream& operator<<(std::ostream& stream, const RecoElectron& electron)
{
  stream << " pT = " << electron.pt_ << ","
         << " eta = " << electron.eta_ << ","
         << " phi = " << electron.phi_ << ","
         << " charge = " << electron.charge_ << std::endl;
  stream << " dxy = " << electron.dxy_ << ", dz = " << electron.dz_ << ", sip3d = " << electron.sip3d_ << std::endl;
  stream << " relIso = " << electron.relIso_ << std::endl;
  stream << " tightCharge = " << electron.tightCharge_ << std::endl;
  stream << " nLostHits = " << electron.nLostHits_ << ", passesConversionVeto = " << electron.passesConversionVeto_ <<
    std::endl;
  stream << " sigmaEtaEta = " << electron.sigmaEtaEta_ << ", deltaEta = " << electron.deltaEta_ << ", deltaPhi = " <<
    electron.deltaPhi_ << std::endl;
  stream << " HoE = " << electron.HoE_ << ", OoEminusOoP = " << electron.OoEminusOoP_ << std::endl;
  stream << " jetBtagCSV = " << electron.jetBtagCSV_ << std::endl;
  stream << " mvaRawTTH = " << electron.mvaRawTTH_ << std::endl;
  return stream;
}
