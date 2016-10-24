#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon, RecoLepton, GenLepton

RecoMuon::RecoMuon(Double_t pt,
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
                   Int_t    passesLooseIdPOG,
                   Int_t    passesMediumIdPOG,
#ifdef DPT_DIV_PT
                   Float_t  dpt_div_pt,
#endif // ifdef DPT_DIV_PT
                   Float_t  segmentCompatibility)
  : RecoLepton(pt,
               eta,
               phi,
               mass,
               pdgId,
               dxy,
               dz,
               relIso,
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
  , passesLooseIdPOG_(passesLooseIdPOG)
  , passesMediumIdPOG_(passesMediumIdPOG)
#ifdef DPT_DIV_PT
  , dpt_div_pt_(dpt_div_pt)
#endif // ifdef DPT_DIV_PT
  , segmentCompatibility_(segmentCompatibility)
{}

std::ostream& operator<<(std::ostream& stream, const RecoMuon& muon)
{
  stream << " pT = " << muon.pt_ << ","
         << " eta = " << muon.eta_ << ","
         << " phi = " << muon.phi_ << ","
         << " pdgId = " << muon.pdgId_ << std::endl;
  stream << " dxy = " << muon.dxy_ << ", dz = " << muon.dz_ << ", sip3d = " <<
    muon.sip3d_ << std::endl;
  stream << " relIso = " << muon.relIso_ << std::endl;
  stream << " passesLooseIdPOG = " << muon.passesLooseIdPOG_ <<
    ", passesMediumIdPOG = " << muon.passesMediumIdPOG_ << std::endl;
  stream << " tightCharge = " << muon.tightCharge_ << std::endl;
  stream << " jetBtagCSV = " << muon.jetBtagCSV_ << std::endl;
  stream << " mvaRawTTH = " << muon.mvaRawTTH_ << std::endl;
  return stream;
}
