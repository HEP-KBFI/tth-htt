#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron, RecoLepton, GenLepton

RecoElectron::RecoElectron(Double_t pt,
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
                           Int_t    passesTightCharge,
                           Int_t    charge,
                           Double_t mvaRawPOG_GP,
                           Double_t mvaRawPOG_HZZ,
                           Double_t sigmaEtaEta,
                           Double_t HoE,
                           Double_t deltaEta,
                           Double_t deltaPhi,
                           Double_t OoEminusOoP,
                           Int_t    nLostHits,
                           Int_t    passesConversionVeto)
  : RecoLepton(pt,
               eta,
               phi,
               mass,
               pdgId,
               dxy,
               dz,
               relIso,
               chargedHadRelIso03,
               miniIsoCharged,
               miniIsoNeutral,
               sip3d,
               mvaRawTTH,
               jetNDauChargedMVASel,
               jetPtRel,
               jetPtRatio,
               jetBtagCSV,
               passesTightCharge,
               charge)
  , mvaRawPOG_GP_(mvaRawPOG_GP)
  , mvaRawPOG_HZZ_(mvaRawPOG_HZZ)
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
  stream << " pT = " << electron.lepton_pt() << " (cone_pT = " << electron.cone_pt() << ") ,"
         << " eta = " << electron.eta() << ","
         << " phi = " << electron.phi() << ","
         << " charge = " << electron.charge() << std::endl;
  stream << " dxy = " << electron.dxy() << ", dz = " << electron.dz() << ", sip3d = " << electron.sip3d() << std::endl;
  stream << " relIso = " << electron.relIso() << std::endl;
  stream << " mvaPOG_GP = " << electron.mvaRawPOG_GP() << std::endl;
  stream << " mvaPOG_HZZ = " << electron.mvaRawPOG_HZZ() << std::endl;
  stream << " tightCharge = " << electron.tightCharge() << std::endl;
  stream << " nLostHits = " << electron.nLostHits() << ", passesConversionVeto = " << electron.passesConversionVeto() << std::endl;
  stream << " sigmaEtaEta = " << electron.sigmaEtaEta() << ", deltaEta = " << electron.deltaEta() << ", deltaPhi = " << electron.deltaPhi() << std::endl;
  stream << " HoE = " << electron.HoE() << ", OoEminusOoP = " << electron.OoEminusOoP() << std::endl;
  stream << " jetBtagCSV = " << electron.jetBtagCSV() << std::endl;
  stream << " mvaRawTTH = " << electron.mvaRawTTH() << std::endl;
  return stream;
}
