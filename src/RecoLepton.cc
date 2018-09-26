#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton, GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

RecoLepton::RecoLepton(const GenLepton & lepton,
                       Double_t dxy,
                       Double_t dz,
                       Double_t relIso,
                       Double_t pfRelIso04All,
                       Double_t miniIsoCharged,
                       Double_t miniIsoNeutral,
                       Double_t sip3d,
                       Double_t mvaRawTTH,
                       Double_t jetPtRatio,
                       Double_t jetPtRel,
                       Double_t jetBtagCSV,
                       Int_t    jetNDauChargedMVASel,
                       Int_t    tightCharge,
                       Int_t    charge,
                       UInt_t   filterBits)
  : GenLepton(lepton)
  , dxy_(dxy)
  , dz_(dz)
  , relIso_(relIso)
  , pfRelIso04All_(pfRelIso04All)
  , miniIsoCharged_(miniIsoCharged)
  , miniIsoNeutral_(miniIsoNeutral)
  , sip3d_(sip3d)
  , mvaRawTTH_(mvaRawTTH)
  , jetPtRatio_(jetPtRatio)
  , jetPtRel_(jetPtRel)
  , jetBtagCSV_(jetBtagCSV)
  , jetNDauChargedMVASel_(jetNDauChargedMVASel)
  , tightCharge_(tightCharge)
  , charge_(charge)
  , filterBits_(filterBits)
  , assocJet_pt_(jetPtRatio_ > 1.e-3 ? 0.90 * pt_ / jetPtRatio_ : pt_)
  , assocJet_p4_(assocJet_pt_, eta_, phi_, mass_)
  , genLepton_(nullptr)
  , genHadTau_(nullptr)
  , genJet_(nullptr)
  , isLoose_(false)
  , isFakeable_(false)
  , isTight_(false)
{}

RecoLepton::~RecoLepton()
{}

void
RecoLepton::set_isLoose() const
{
  isLoose_ = true;
}

void
RecoLepton::set_isFakeable() const
{
  isFakeable_ = true;
}

void
RecoLepton::set_isTight() const
{
  isTight_ = true;
}

void
RecoLepton::set_genLepton(const GenLepton * genLepton)
{
  genLepton_.reset(genLepton);
}

void
RecoLepton::set_genHadTau(const GenHadTau * genHadTau)
{
  genHadTau_.reset(genHadTau);
}

void
RecoLepton::set_genPhoton(const GenPhoton * genPhoton)
{
  genPhoton_.reset(genPhoton);
}

void
RecoLepton::set_genJet(const GenJet * genJet)
{
  genJet_.reset(genJet);
}

bool
RecoLepton::is_electron() const
{
  return false;
}

bool
RecoLepton::is_muon() const
{
  return false;
}

Double_t
RecoLepton::lepton_pt() const
{
  return pt_;
}

const Particle::LorentzVector &
RecoLepton::lepton_p4() const
{
  return p4_;
}

Double_t
RecoLepton::pt() const
{
  return pt_;
}

const Particle::LorentzVector &
RecoLepton::p4() const
{
  return p4_;
}

Double_t
RecoLepton::cone_pt() const
{
  return mvaRawTTH() >= 0.90 ? pt_ : assocJet_pt_;
}

const Particle::LorentzVector &
RecoLepton::cone_p4() const
{
  return mvaRawTTH() >= 0.90 ? p4_ : assocJet_p4_;
}

Double_t
RecoLepton::assocJet_pt() const
{
  return assocJet_pt_;
}

const Particle::LorentzVector &
RecoLepton::assocJet_p4() const
{
  return assocJet_p4_;
}

Double_t
RecoLepton::dxy() const
{
  return dxy_;
}

Double_t
RecoLepton::dz() const
{
  return dz_;
}

Double_t
RecoLepton::relIso() const
{
  return relIso_;
}

Double_t
RecoLepton::pfRelIso04All() const
{
  return pfRelIso04All_;
}

Double_t
RecoLepton::miniIsoCharged() const
{
  return miniIsoCharged_;
}

Double_t
RecoLepton::miniIsoNeutral() const
{
  return miniIsoNeutral_;
}

Double_t
RecoLepton::sip3d() const
{
  return sip3d_;
}

Double_t
RecoLepton::mvaRawTTH() const
{
  return mvaRawTTH_;
}

Double_t
RecoLepton::jetPtRatio() const
{
  return jetPtRatio_;
}

Double_t
RecoLepton::jetPtRel() const
{
  return jetPtRel_;
}

Double_t
RecoLepton::jetBtagCSV() const
{
  return jetBtagCSV_;
}

Int_t
RecoLepton::jetNDauChargedMVASel() const
{
  return jetNDauChargedMVASel_;
}

Int_t
RecoLepton::tightCharge() const
{
  return tightCharge_;
}

Int_t
RecoLepton::charge() const
{
  return charge_;
}

UInt_t
RecoLepton::filterBits() const
{
  return filterBits_;
}

const GenLepton *
RecoLepton::genLepton() const
{
  return genLepton_.get();
}

const GenHadTau *
RecoLepton::genHadTau() const
{
  return genHadTau_.get();
}

const GenPhoton *
RecoLepton::genPhoton() const
{
  return genPhoton_.get();
}

const GenJet *
RecoLepton::genJet() const
{
  return genJet_.get();
}

bool
RecoLepton::isGenMatched() const
{
  return !! genLepton_;
}

bool
RecoLepton::hasAnyGenMatch() const
{
  return !! genLepton_ || !! genHadTau_ || !! genPhoton_ || !! genJet_;
}

bool
RecoLepton::isLoose() const
{
  return isLoose_;
}

bool
RecoLepton::isFakeable() const
{
  return isFakeable_;
}

bool
RecoLepton::isTight() const
{
  return isTight_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoLepton & lepton)
{
  stream << static_cast<const GenLepton &>(lepton)        << ",\n"
            " cone_pT = "       << lepton.cone_pt()       << ","
            " dxy = "           << lepton.dxy()           << ","
            " dz = "            << lepton.dz()            << ",\n"
            " sip3d = "         << lepton.sip3d()         << ","
            " relIso = "        << lepton.relIso()        << ","
            " pfRelIso04All = " << lepton.pfRelIso04All() << ",\n"
            " tightCharge = "   << lepton.tightCharge()   << ","
            " jetBtagCSV = "    << lepton.jetBtagCSV()    << ","
            " jetPtRatio = "    << lepton.jetPtRatio()    << ",\n"
            " jetPtRel = "      << lepton.jetPtRel()      << ","
            " mvaRawTTH = "     << lepton.mvaRawTTH()     << ",\n"
            " is loose/fakeable/tight = " << lepton.isLoose()    << '/'
                                          << lepton.isFakeable() << '/'
                                          << lepton.isTight()    << ",\n"
            " gen. matching:";
  stream << ",\n  lepton = " << lepton.genLepton();
  if(lepton.genLepton())
  {
    stream << ": " << *(lepton.genLepton());
  }
  stream << ",\n  hadTau = " << lepton.genHadTau();
  if(lepton.genHadTau())
  {
    stream << ": " << *(lepton.genHadTau());
  }
  stream << ",\n  photon = " << lepton.genPhoton();
  if(lepton.genPhoton())
  {
    stream << ": " << *(lepton.genPhoton());
  }
  stream << ",\n  jet    = " << lepton.genJet();
  if(lepton.genJet())
  {
    stream << ": " << *(lepton.genJet());
  }
  stream << '\n';
  return stream;
}
