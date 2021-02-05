#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h"

#include <iostream> // std::ostream

hltPath_LeptonFakeRate::hltPath_LeptonFakeRate(const std::string & branchName,
                                               bool is_trigger_1mu,
                                               bool is_trigger_2mu,
                                               bool is_trigger_1e,
                                               bool is_trigger_2e,
                                               double minPt,
                                               double maxPt,  
                                               double minRecoPt,
                                               double min_jetPt,
                                               double prescale) 
  : hltPath(branchName, minPt, maxPt)
  , minPt_(minPt)
  , maxPt_(maxPt)
  , minRecoPt_(minRecoPt)
  , minJetPt_(min_jetPt)
  , prescale_(prescale)
  , is_trigger_1mu_(is_trigger_1mu)
  , is_trigger_2mu_(is_trigger_2mu)
  , is_trigger_1e_(is_trigger_1e)
  , is_trigger_2e_(is_trigger_2e)
  , isTriggered_(false)
{}

std::string 
hltPath_LeptonFakeRate::getPathName() const
{
  return branchName_;
}

double
hltPath_LeptonFakeRate::getMinPt() const
{
  return minPt_;
}

double
hltPath_LeptonFakeRate::getMaxPt() const
{
  return maxPt_;
}

double
hltPath_LeptonFakeRate::getMinJetPt() const
{
  return minJetPt_;
}

double
hltPath_LeptonFakeRate::getMinRecoPt() const
{
  return minRecoPt_;
}
double
hltPath_LeptonFakeRate::getPrescale() const
{
  return prescale_;
}

bool
hltPath_LeptonFakeRate::is_trigger_1mu() const
{
  return is_trigger_1mu_;
}

bool
hltPath_LeptonFakeRate::is_trigger_2mu() const
{
  return is_trigger_2mu_;
}

bool
hltPath_LeptonFakeRate::is_trigger_1e() const
{
  return is_trigger_1e_;
}

bool
hltPath_LeptonFakeRate::is_trigger_2e() const
{
  return is_trigger_2e_;
}

bool
hltPath_LeptonFakeRate::isTriggered() const
{
  return isTriggered_;
}

void
hltPath_LeptonFakeRate::setIsTriggered(bool decision) const
{
  isTriggered_ = decision;
}

std::vector<hltPath_LeptonFakeRate *>
create_hltPaths_LeptonFakeRate(const std::vector<std::string> & branchNames,
                               const edm::ParameterSet & cfg)
{
  const double minPt = cfg.getParameter<double>("cone_minPt");
  const double maxPt = cfg.getParameter<double>("cone_maxPt");
  const double minRecoPt = cfg.getParameter<double>("minRecoPt");
  const double jet_minPt = cfg.getParameter<double>("jet_minPt");
  const double prescale = cfg.getParameter<double>("average_prescale");
  const bool is_trigger_1mu = cfg.getParameter<bool>("is_trigger_1mu");
  const bool is_trigger_2mu = cfg.getParameter<bool>("is_trigger_2mu");
  const bool is_trigger_1e = cfg.getParameter<bool>("is_trigger_1e");
  const bool is_trigger_2e = cfg.getParameter<bool>("is_trigger_2e");

  std::vector<hltPath_LeptonFakeRate *> hltPaths;
  for(const std::string & branchName: branchNames)
  {
    hltPaths.push_back(new hltPath_LeptonFakeRate(
      branchName,is_trigger_1mu, is_trigger_2mu, is_trigger_1e, is_trigger_2e,
      minPt, maxPt, minRecoPt, jet_minPt, prescale));
  }
  return hltPaths;
}

void
hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate *> & hltPaths)
{
  for(hltPath_LeptonFakeRate * path: hltPaths)
  {
    delete path;
    path = nullptr;
  }
}

bool
isHigherMinRecoPt(hltPath_LeptonFakeRate * trigger_lhs,
                  hltPath_LeptonFakeRate * trigger_rhs)
{
  return trigger_lhs->getMinRecoPt() > trigger_rhs->getMinRecoPt();
}

std::ostream &
operator<<(std::ostream & stream,
           const hltPath_LeptonFakeRate & hltPath_iter)
{
  stream << "hltPath = " << hltPath_iter.getBranchName() << ": "
            "value = " << hltPath_iter.getValue() << " ("
            "minPt = " << hltPath_iter.getMinPt() << ", "
            "maxPt = " << hltPath_iter.getMaxPt() << ", "
            "minRecoPt = " << hltPath_iter.getMinRecoPt() << ", "
            "minJetPt = " << hltPath_iter.getMinJetPt() << ", "
            "prescale = " << hltPath_iter.getPrescale() 
            << ")\n";
  return stream;
}
