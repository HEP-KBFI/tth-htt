#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

RecoJet::RecoJet(const GenJet & jet,
                 Double_t jecUncertTotal,
                 Double_t BtagCSV,
                 Double_t BtagWeight,
                 Double_t QGDiscr,
                 Int_t heppyFlavour,
                 Int_t idx)
  : GenJet(jet)
  , jecUncertTotal_(jecUncertTotal)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , QGDiscr_(QGDiscr)
  , heppyFlavour_(heppyFlavour)
  , idx_(idx)
  , genLepton_(nullptr)
  , genLepton_isOwner_(false)
  , genHadTau_(nullptr)
  , genHadTau_isOwner_(false)
  , genJet_(nullptr)
  , genJet_isOwner_(false)
{}

RecoJet::~RecoJet()
{
  if(genLepton_isOwner_ && genLepton_)
  {
    delete genLepton_;
  }
  if(genHadTau_isOwner_ && genHadTau_)
  {
    delete genHadTau_;
  }
  if(genJet_isOwner_ && genJet_)
  {
    delete genJet_;
  }
}

void
RecoJet::set_genLepton(const GenLepton * genLepton,
                       bool isOwner)
{
  genLepton_ = genLepton;
  genLepton_isOwner_ = isOwner;
}

void
RecoJet::set_genHadTau(const GenHadTau*  genHadTau,
                       bool isOwner)
{
  genHadTau_ = genHadTau;
  genHadTau_isOwner_ = isOwner;
}

void
RecoJet::set_genJet(const GenJet * genJet,
                    bool isOwner)
{
  genJet_ = genJet;
  genJet_isOwner_ = isOwner;
}

Double_t
RecoJet::jecUncertTotal() const
{
  return jecUncertTotal_;
}

Double_t
RecoJet::BtagCSV() const
{
  return BtagCSV_;
}

Double_t
RecoJet::BtagWeight() const
{
  return BtagWeight_;
}

Double_t
RecoJet::QGDiscr() const
{
  return QGDiscr_;
}

Int_t
RecoJet::heppyFlavour() const
{
  return heppyFlavour_;
}

Int_t
RecoJet::idx() const
{
  return idx_;
}

const GenLepton *
RecoJet::genLepton() const
{
  return genLepton_;
}

const GenHadTau *
RecoJet::genHadTau() const
{
  return genHadTau_;
}

const GenJet *
RecoJet::genJet() const
{
  return genJet_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet)
{
  stream << static_cast<const GenJet &>(jet)         << ","
            " CSV = " << jet.BtagCSV()               << ","
            " heppyFlavour = " << jet.heppyFlavour() << ",\n"
            " gen. matching:";
  stream << ",\n  lepton = " << jet.genLepton();
  if(jet.genLepton())
  {
    stream << ": " << *(jet.genLepton());
  }
  stream << ",\n  hadTau = " << jet.genHadTau();
  if(jet.genHadTau())
  {
    stream << ": " << *(jet.genHadTau());
  }
  stream << ",\n  jet    = " << jet.genJet();
  if(jet.genJet())
  {
    stream << ": " << *(jet.genJet());
  }
  stream << '\n';
  return stream;
}
