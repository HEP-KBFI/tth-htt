#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

RecoJetBase::RecoJetBase(const GenJet & jet,
                         Int_t idx)
  : GenJet(jet)
  , idx_(idx)
  , genLepton_(nullptr)
  , genLepton_isOwner_(false)
  , genHadTau_(nullptr)
  , genHadTau_isOwner_(false)
  , genJet_(nullptr)
  , genJet_isOwner_(false)
{}

RecoJetBase::~RecoJetBase()
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
RecoJetBase::set_genLepton(const GenLepton * genLepton,
                       bool isOwner)
{
  genLepton_ = genLepton;
  genLepton_isOwner_ = isOwner;
}

void
RecoJetBase::set_genHadTau(const GenHadTau*  genHadTau,
                       bool isOwner)
{
  genHadTau_ = genHadTau;
  genHadTau_isOwner_ = isOwner;
}

void
RecoJetBase::set_genJet(const GenJet * genJet,
                    bool isOwner)
{
  genJet_ = genJet;
  genJet_isOwner_ = isOwner;
}

Int_t
RecoJetBase::idx() const
{
  return idx_;
}

const GenLepton *
RecoJetBase::genLepton() const
{
  return genLepton_;
}

const GenHadTau *
RecoJetBase::genHadTau() const
{
  return genHadTau_;
}

const GenJet *
RecoJetBase::genJet() const
{
  return genJet_;
}

bool
RecoJetBase::isGenMatched() const
{
  return !! genJet_;
}

bool
RecoJetBase::hasAnyGenMatch() const
{
  return !! genLepton_ || !! genHadTau_ || !! genJet_;
}

