#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"

RecoElectron::RecoElectron(const RecoLepton & lepton,
                           Double_t mvaRawPOG_GP,
                           Double_t mvaRawPOG_HZZ,
                           Double_t sigmaEtaEta,
                           Double_t HoE,
                           Double_t deltaEta,
                           Double_t deltaPhi,
                           Double_t OoEminusOoP,
                           Int_t    nLostHits,
                           Bool_t   passesConversionVeto,
			   Int_t cutbasedID_HLT)
  : RecoLepton(lepton)
  , mvaRawPOG_GP_(mvaRawPOG_GP)
  , mvaRawPOG_HZZ_(mvaRawPOG_HZZ)
  , sigmaEtaEta_(sigmaEtaEta)
  , HoE_(HoE)
  , deltaEta_(deltaEta) 
  , deltaPhi_(deltaPhi) 
  , OoEminusOoP_(OoEminusOoP)
  , nLostHits_(nLostHits)
  , passesConversionVeto_(passesConversionVeto)
  , cutbasedID_HLT_(cutbasedID_HLT)
{}

Double_t
RecoElectron::mvaRawPOG_GP() const
{
  return mvaRawPOG_GP_;
}

Double_t
RecoElectron::mvaRawPOG_HZZ() const
{
  return mvaRawPOG_HZZ_;
}

Double_t
RecoElectron::sigmaEtaEta() const
{
  return sigmaEtaEta_;
}

Double_t
RecoElectron::HoE() const
{
  return HoE_;
}

Double_t
RecoElectron::deltaEta() const
{
  return deltaEta_; 
}

Double_t
RecoElectron::deltaPhi() const
{
  return deltaPhi_; 
}

Double_t
RecoElectron::OoEminusOoP() const
{
  return OoEminusOoP_;
}

Int_t
RecoElectron::nLostHits() const
{
  return nLostHits_;
}

Bool_t
RecoElectron::passesConversionVeto() const
{
  return passesConversionVeto_;
}

Int_t
RecoElectron::cutbasedID_HLT() const
{
  return cutbasedID_HLT_;
}

bool
RecoElectron::is_electron() const
{
  return true;
}

bool
RecoElectron::is_muon() const
{
  return false;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoElectron & electron)
{
  stream << static_cast<const RecoLepton & >(electron)                   << ",\n "
            "mvaPOG_GP = "            << electron.mvaRawPOG_GP()         << ", "
            "mvaPOG_HZZ = "           << electron.mvaRawPOG_HZZ()        << ", "
            "nLostHits = "            << electron.nLostHits()            << ",\n "
            "passesConversionVeto = " << electron.passesConversionVeto() << ", "
            "sigmaEtaEta = "          << electron.sigmaEtaEta()          << ", "
            "deltaEta = "             << electron.deltaEta()             << ",\n "
            "deltaPhi = "             << electron.deltaPhi()             << ", "
            "HoE = "                  << electron.HoE()                  << ", "
            "OoEminusOoP = "          << electron.OoEminusOoP()          << ", "
            "cutbasedID_HLT = "       << electron.cutbasedID_HLT()       << ",\n ";
  return stream;
}
