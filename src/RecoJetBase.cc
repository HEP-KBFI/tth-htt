#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

RecoJetBase::RecoJetBase(const GenJet & jet,
                         Int_t idx)
  : GenJet(jet)
  , idx_(idx)
  , genLepton_(nullptr)
  , genHadTau_(nullptr)
  , genJet_(nullptr)
{}

RecoJetBase::~RecoJetBase()
{}

void
RecoJetBase::set_genLepton(const GenLepton * genLepton)
{
  genLepton_.reset(genLepton);
}

void
RecoJetBase::set_genHadTau(const GenHadTau *  genHadTau)
{
  genHadTau_.reset(genHadTau);
}

void
RecoJetBase::set_genJet(const GenJet * genJet)
{
  genJet_.reset(genJet);
}

Int_t
RecoJetBase::idx() const
{
  return idx_;
}

const GenLepton *
RecoJetBase::genLepton() const
{
  return genLepton_.get();
}

const GenHadTau *
RecoJetBase::genHadTau() const
{
  return genHadTau_.get();
}

const GenJet *
RecoJetBase::genJet() const
{
  return genJet_.get();
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

