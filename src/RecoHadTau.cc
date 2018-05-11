#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau, GenParticle

#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

RecoHadTau::RecoHadTau(const GenHadTau & particle,
                       Double_t dxy,
                       Double_t dz,
                       Int_t decayMode,
                       Bool_t decayModeFinding,
                       Bool_t decayModeFindingNew,
                       Int_t id_mva_dR03,
                       Double_t raw_mva_dR03,
                       Int_t id_mva_dR05,
                       Double_t raw_mva_dR05,
                       Int_t id_cut_dR03,
                       Double_t raw_cut_dR03,
                       Int_t id_cut_dR05,
                       Double_t raw_cut_dR05,
                       Int_t antiElectron,
                       Int_t antiMuon,
                       UInt_t filterBits)
  : GenHadTau(particle)
  , dxy_(dxy)
  , dz_(dz)
  , decayMode_(decayMode)
  , decayModeFinding_(decayModeFinding)
  , decayModeFindingNew_(decayModeFindingNew)
  , id_mva_dR03_(id_mva_dR03)
  , raw_mva_dR03_(raw_mva_dR03)
  , id_mva_dR05_(id_mva_dR05)
  , raw_mva_dR05_(raw_mva_dR05)
  , id_cut_dR03_(id_cut_dR03)
  , raw_cut_dR03_(raw_cut_dR03)
  , id_cut_dR05_(id_cut_dR05)
  , raw_cut_dR05_(raw_cut_dR05)
  , antiElectron_(antiElectron)
  , antiMuon_(antiMuon)
  , filterBits_(filterBits)
  , genLepton_(nullptr)
  , genHadTau_(nullptr)
  , genJet_(nullptr)
  , isLoose_(false)
  , isFakeable_(false)
  , isTight_(false)
{}

RecoHadTau::~RecoHadTau()
{}

void
RecoHadTau::set_isLoose() const
{
  isLoose_ = true;
}

void
RecoHadTau::set_isFakeable() const
{
  isFakeable_ = true;
}

void
RecoHadTau::set_isTight() const
{
  isTight_ = true;
}

void
RecoHadTau::set_genLepton(const GenLepton * genLepton)
{
  genLepton_.reset(genLepton);
}

void
RecoHadTau::set_genHadTau(const GenHadTau * genHadTau)
{
  genHadTau_.reset(genHadTau);
}

void
RecoHadTau::set_genJet(const GenJet * genJet)
{
  genJet_.reset(genJet);
}

Double_t
RecoHadTau::dxy() const
{
  return dxy_;
}

Double_t
RecoHadTau::dz() const
{
  return dz_;
}

Int_t
RecoHadTau::decayMode() const
{
  return decayMode_;
}

Bool_t
RecoHadTau::decayModeFinding() const
{
  return decayModeFinding_;
}

Bool_t
RecoHadTau::decayModeFindingNew() const
{
  return decayModeFindingNew_;
}

Int_t
RecoHadTau::id_mva_dR03() const
{
  return id_mva_dR03_;
}

Double_t
RecoHadTau::raw_mva_dR03() const
{
  return raw_mva_dR03_;
}

Int_t
RecoHadTau::id_mva_dR05() const
{
  return id_mva_dR05_;
}

Double_t
RecoHadTau::raw_mva_dR05() const
{
  return raw_mva_dR05_;
}

Int_t
RecoHadTau::id_cut_dR03() const
{
  return id_cut_dR03_;
}

Double_t
RecoHadTau::raw_cut_dR03() const
{
  return raw_cut_dR03_;
}

Int_t
RecoHadTau::id_cut_dR05() const
{
  return id_cut_dR05_;
}

Double_t
RecoHadTau::raw_cut_dR05() const
{
  return raw_cut_dR05_;
}

Int_t
RecoHadTau::antiElectron() const
{
  return antiElectron_;
}

Int_t
RecoHadTau::antiMuon() const
{
  return antiMuon_;
}

UInt_t
RecoHadTau::filterBits() const
{
  return filterBits_;
}

const GenLepton *
RecoHadTau::genLepton() const
{
  return genLepton_.get();
}

const GenHadTau *
RecoHadTau::genHadTau() const
{
  return genHadTau_.get();
}

const GenJet *
RecoHadTau::genJet() const
{
  return genJet_.get();
}

bool
RecoHadTau::isGenMatched() const
{
  return !! genHadTau_;
}

bool
RecoHadTau::hasAnyGenMatch() const
{
  return !! genLepton_ || !! genHadTau_ || !! genJet_;
}

bool
RecoHadTau::isLoose() const
{
  return isLoose_;
}

bool
RecoHadTau::isFakeable() const
{
  return isFakeable_;
}

bool
RecoHadTau::isTight() const
{
  return isTight_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoHadTau & hadTau)
{
  stream << static_cast<const GenHadTau &>(hadTau)               << ",\n"
            " decayModeFinding = " << hadTau.decayModeFinding()  << ","
            " id_mva_dR03 = "      << hadTau.id_mva_dR03()       <<
            " (raw = "             << hadTau.raw_mva_dR03()      << "),\n"
            " antiElectron = "     << hadTau.antiElectron()      << ","
            " antiMuon = "         << hadTau.antiMuon()          << ",\n"
            " is loose/fakeable/tight = " << hadTau.isLoose()    << '/'
                                          << hadTau.isFakeable() << '/'
                                          << hadTau.isTight()    << ",\n"
            " gen. matching:";
  stream << ",\n  lepton = " << hadTau.genLepton();
  if(hadTau.genLepton())
  {
    stream << ": " << *(hadTau.genLepton());
  }
  stream << ",\n  hadTau = " << hadTau.genHadTau();
  if(hadTau.genHadTau())
  {
    stream << ": " << *(hadTau.genHadTau());
  }
  stream << ",\n  jet    = " << hadTau.genJet();
  if(hadTau.genJet())
  {
    stream << ": " << *(hadTau.genJet());
  }
  stream << '\n';
  return stream;
}
