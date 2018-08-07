#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"

RecoElectron::RecoElectron(const RecoLepton & lepton,
                           Double_t eCorr,
                           Double_t mvaRaw_POG,
                           Bool_t mvaID_POG,
                           Double_t sigmaEtaEta,
                           Double_t HoE,
                           Double_t deltaEta,
                           Double_t deltaPhi,
                           Double_t OoEminusOoP,
                           Int_t    nLostHits,
                           Bool_t   passesConversionVeto,
                           Int_t cutbasedID_HLT)
  : RecoLepton(lepton)
  , eCorr_(eCorr)
  , mvaRaw_POG_(mvaRaw_POG)
  , mvaID_POG_(mvaID_POG)
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
RecoElectron::eCorr() const
{
  return eCorr_;
}

Double_t
RecoElectron::mvaRaw_POG() const
{
  return mvaRaw_POG_;
}

Bool_t
RecoElectron::mvaID_POG() const
{
  return mvaID_POG_;
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
            "eCorr = "                << electron.eCorr()                << ", "
            "mvaRaw_POG = "           << electron.mvaRaw_POG()           << " ("
            "mvaID_POG = "            << electron.mvaID_POG()            << "), "
            "nLostHits = "            << electron.nLostHits()            << ",\n "
            "passesConversionVeto = " << electron.passesConversionVeto() << ", "
            "sigmaEtaEta = "          << electron.sigmaEtaEta()          << ", "
            "deltaEta = "             << electron.deltaEta()             << ",\n "
            "deltaPhi = "             << electron.deltaPhi()             << ", "
            "HoE = "                  << electron.HoE()                  << ", "
            "OoEminusOoP = "          << electron.OoEminusOoP()          << ",\n"
            "cutbasedID_HLT = "       << electron.cutbasedID_HLT()       << '\n'
  ;
  return stream;
}
