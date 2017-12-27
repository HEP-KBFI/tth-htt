#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon, RecoLepton, GenLepton

RecoMuon::RecoMuon(Double_t pt,
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
                   Double_t jetPtRatio,
                   Double_t jetBtagCSV,
                   Int_t    passesTightCharge,
                   Int_t    charge,
                   Bool_t    passesLooseIdPOG,
                   Bool_t    passesMediumIdPOG,
                   Float_t  segmentCompatibility)
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
               jetPtRatio,
               jetBtagCSV,
               passesTightCharge,
               charge)
  , passesLooseIdPOG_(passesLooseIdPOG)
  , passesMediumIdPOG_(passesMediumIdPOG)
  , segmentCompatibility_(segmentCompatibility)
{}

std::ostream& operator<<(std::ostream& stream, const RecoMuon& muon)
{
  stream << " pT = " << muon.lepton_pt() << " (cone_pT = " << muon.cone_pt() << ") ,"
         << " eta = " << muon.eta() << ","
         << " phi = " << muon.phi() << ","
         << " pdgId = " << muon.pdgId() << std::endl;
  stream << " dxy = " << muon.dxy() << ", dz = " << muon.dz() << ", sip3d = " << muon.sip3d() << std::endl;
  stream << " relIso = " << muon.relIso() << std::endl;
  stream << " chargedHadRelIso03 = " << muon.chargedHadRelIso03() << std::endl;
  stream << " passesLooseIdPOG = " << muon.passesLooseIdPOG() << ", passesMediumIdPOG = " << muon.passesMediumIdPOG() << std::endl;
  stream << " tightCharge = " << muon.tightCharge() << std::endl;
  stream << " jetBtagCSV = " << muon.jetBtagCSV() << std::endl;
  stream << " mvaRawTTH = " << muon.mvaRawTTH() << std::endl;
  stream << "gen. matching:" 
	 << " lepton = " << muon.genLepton() << "," 
	 << " hadTau = " << muon.genHadTau() << "," 
	 << " jet = " << muon.genJet() << std::endl;
  return stream;
}
