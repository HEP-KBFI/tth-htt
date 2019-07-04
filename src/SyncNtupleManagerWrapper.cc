#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManagerWrapper.h"

#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // contains()

#include <TFile.h> // TFile

SyncNtupleManagerWrapper::SyncNtupleManagerWrapper(const edm::ParameterSet & cfg,
                                                   const std::vector<std::vector<hltPath *>> & hltPaths)
  : SyncNtupleManagerWrapper(cfg, hltPaths, SyncGenMatchCharge::kDisabled)
{}

SyncNtupleManagerWrapper::SyncNtupleManagerWrapper(const edm::ParameterSet & cfg,
                                                   const std::vector<std::vector<hltPath *>> & hltPaths,
                                                   SyncGenMatchCharge genMatchCharge)
  : outputFile(nullptr)
{
  const std::string syncNtuple_output = cfg.getParameter<std::string>("output");
  outputFile = new TFile(syncNtuple_output.c_str(), "recreate");

  const edm::VParameterSet opts = cfg.getParameter<edm::VParameterSet>("options");
  for(const edm::ParameterSet & opt: opts)
  {
    const std::string treeName = opt.getParameter<std::string>("tree");
    if(std::find(treeNames.begin(), treeNames.end(), treeName) != treeNames.end())
    {
      throw cmsException(this, __func__, __LINE__) << "Duplicate sync tree name found: " << treeName;
    }
    treeNames.push_back(treeName);

    const std::vector<std::string> genMatch = opt.getParameter<std::vector<std::string>>("genMatch");
    genMatchers[treeName] = genMatch;

    SyncNtupleManager * snm_part = new SyncNtupleManager(outputFile, treeName, genMatchCharge);
    snm_part->initializeBranches();
    snm_part->initializeHLTBranches(hltPaths);
    managers[treeName] = snm_part;
  }
}

SyncNtupleManagerWrapper::~SyncNtupleManagerWrapper()
{
  for(auto & kv: managers)
  {
    delete kv.second;
  }
  outputFile->Close();
  delete outputFile;
  outputFile = nullptr;
}

std::map<std::string, SyncNtupleManager *>::iterator
SyncNtupleManagerWrapper::begin()
{
  return managers.begin();
}

std::map<std::string, SyncNtupleManager *>::const_iterator
SyncNtupleManagerWrapper::begin() const
{
  return managers.cbegin();
}

std::map<std::string, SyncNtupleManager *>::iterator
SyncNtupleManagerWrapper::end()
{
  return managers.end();
}

std::map<std::string, SyncNtupleManager *>::const_iterator
SyncNtupleManagerWrapper::end() const
{
  return managers.cend();
}

SyncNtupleManagerWrapper::operator bool() const
{
  return ! managers.empty();
}

bool
SyncNtupleManagerWrapper::isGenMatched(const std::string & treeName,
                                       const std::string & genMatchStr) const
{
  if(! genMatchers.count(treeName))
  {
    throw cmsException(this, __func__, __LINE__) << "No such tree found: " << treeName;
  }
  return contains(genMatchers.at(treeName), genMatchStr);
}
