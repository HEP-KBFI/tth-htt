#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // TauID

ObjectMultiplicity::ObjectMultiplicity()
  : nRecoMuon_    ({ { kLoose, -1 }, { kFakeable, -1 }, { kTight, -1 } })
  , nRecoElectron_({ { kLoose, -1 }, { kFakeable, -1 }, { kTight, -1 } })
{
  for(const auto & kv: TauID_PyMap)
  {
    nRecoHadTau_[kv.second] = {};
    const int max_level = TauID_levels.at(kv.second);
    for(int level = 1; level <= max_level; ++level)
    {
      nRecoHadTau_[kv.second][level] = -1;
    }
  }
}

ObjectMultiplicity &
ObjectMultiplicity::operator=(const ObjectMultiplicity & objectMultiplicity)
{
  for(int selection = kLoose; selection <= kTight; ++selection)
  {
    if(! objectMultiplicity.nRecoMuon_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "No such selection for muons: " << selection;
    }
    if(! objectMultiplicity.nRecoElectron_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "No such selection for electrons: " << selection;
    }
    nRecoMuon_[selection]     = objectMultiplicity.nRecoMuon_.at(selection);
    nRecoElectron_[selection] = objectMultiplicity.nRecoElectron_.at(selection);
  }
  for(const auto & kv: TauID_PyMap)
  {
    if(! objectMultiplicity.nRecoHadTau_.count(kv.second))
    {
      throw cmsException(this, __func__, __LINE__) << "No such tau ID: " << as_integer(kv.second);
    }
    const int max_level = TauID_levels.at(kv.second);
    for(int level = 1; level <= max_level; ++level)
    {
      if(! objectMultiplicity.nRecoHadTau_.at(kv.second).count(level))
      {
        throw cmsException(this, __func__, __LINE__)
          << "No such level for tau ID " << as_integer(kv.second) << ": " << level
        ;
      }
      nRecoHadTau_[kv.second][level] = objectMultiplicity.nRecoHadTau_.at(kv.second).at(level);
    }
  }
  return *this;
}

int
ObjectMultiplicity::getNRecoMuon(int selection) const
{
  if(! nRecoMuon_.count(selection))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid selection: " << selection;
  }
  return nRecoMuon_.at(selection);
}

int
ObjectMultiplicity::getNRecoElectron(int selection) const
{
  if(! nRecoElectron_.count(selection))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid selection: " << selection;
  }
  return nRecoElectron_.at(selection);
}

int
ObjectMultiplicity::getNRecoLepton(int selection) const
{
  return getNRecoMuon(selection) + getNRecoElectron(selection);
}

int
ObjectMultiplicity::getNRecoHadTau(TauID tauId,
                                   int level) const
{
  if(! nRecoHadTau_.count(tauId))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid tau ID: " << as_integer(tauId);
  }
  if(! nRecoHadTau_.at(tauId).count(level))
  {
    throw cmsException(this, __func__, __LINE__)
      << "Invalid level associated with tau ID " << as_integer(tauId) << ": " << level
    ;
  }
  return nRecoHadTau_.at(tauId).at(level);
}

void
ObjectMultiplicity::setNRecoMuon(int nLoose,
                                 int nFakeable,
                                 int nTight)
{
  assert(nLoose >= 0 && nFakeable >= 0 && nTight >= 0);
  nRecoMuon_[kLoose]    = nLoose;
  nRecoMuon_[kFakeable] = nFakeable;
  nRecoMuon_[kTight]    = nTight;
}

void
ObjectMultiplicity::setNRecoElectron(int nLoose,
                                     int nFakeable,
                                     int nTight)
{
  assert(nLoose >= 0 && nFakeable >= 0 && nTight >= 0);
  nRecoElectron_[kLoose]    = nLoose;
  nRecoElectron_[kFakeable] = nFakeable;
  nRecoElectron_[kTight]    = nTight;
}

void
ObjectMultiplicity::setNRecoHadTau(TauID tauId,
                                   int level,
                                   int nTau)
{
  assert(nTau >= 0);
  if(! nRecoHadTau_.count(tauId))
  {
    throw cmsException(this, __func__, __LINE__) << "Unrecognizable tau ID: " << as_integer(tauId);
  }
  if(level < 1 || level > static_cast<int>(nRecoHadTau_.at(tauId).size()))
  {
    throw cmsException(this, __func__, __LINE__)
      << "Expected 1 to " << nRecoHadTau_.at(tauId).size() << "levels for tau ID " << as_integer(tauId) << ", "
         "got " << level
    ;
  }

  nRecoHadTau_[tauId][level] = nTau;
}
