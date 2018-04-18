#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"

RecoElectron::RecoElectron(const RecoLepton & lepton,
                           Double_t eCorr,
                           Double_t mvaRawPOG,
                           Bool_t mvaRawPOG_WP80,
                           Bool_t mvaRawPOG_WP90,
                           Bool_t mvaRawPOG_WPL,
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
  , mvaRawPOG_(mvaRawPOG)
  , mvaRawPOG_WP80_(mvaRawPOG_WP80)
  , mvaRawPOG_WP90_(mvaRawPOG_WP90)
  , mvaRawPOG_WPL_(mvaRawPOG_WPL)
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
RecoElectron::mvaRawPOG() const
{
  return mvaRawPOG_;
}

Bool_t
RecoElectron::mvaRawPOG_WP80() const
{
  return mvaRawPOG_WP80_;
}

Bool_t
RecoElectron::mvaRawPOG_WP90() const
{
  return mvaRawPOG_WP90_;
}

Bool_t
RecoElectron::mvaRawPOG_WPL() const
{
  return mvaRawPOG_WPL_;
}

Bool_t
RecoElectron::mvaRawPOG_WP(EGammaPOG wp) const
{
  switch(wp)
  {
    case EGammaPOG::kWP80: return mvaRawPOG_WP80();
    case EGammaPOG::kWP90: return mvaRawPOG_WP90();
    case EGammaPOG::kWPL:  return mvaRawPOG_WPL();
    default: assert(0);
  }
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

Double_t
RecoElectron::cone_pt() const
{
  return mvaRawTTH() > 0.90 ? pt() : assocJet_pt();
}

const Particle::LorentzVector &
RecoElectron::cone_p4() const
{
  return mvaRawTTH() > 0.90 ? p4() : assocJet_p4();
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoElectron & electron)
{
  stream << static_cast<const RecoLepton & >(electron)                   << ",\n "
            "eCorr = "                << electron.eCorr()                << ", "
            "mvaRawPOG = "            << electron.mvaRawPOG()            << " ("
            "80/90/Loose = "          << electron.mvaRawPOG_WP80()       << '/'
                                      << electron.mvaRawPOG_WP90()       << '/'
                                      << electron.mvaRawPOG_WPL()        << "), "
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
