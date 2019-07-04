#ifndef tthAnalysis_HiggsToTauTau_SyncNtupleManagerWrapper_h
#define tthAnalysis_HiggsToTauTau_SyncNtupleManagerWrapper_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

// forward declarations
class SyncNtupleManager;
class TFile;
class hltPath;
enum class SyncGenMatchCharge;

class SyncNtupleManagerWrapper
{
public:
  SyncNtupleManagerWrapper(const edm::ParameterSet & cfg,
                           const std::vector<std::vector<hltPath *>> & hltPaths);

  SyncNtupleManagerWrapper(const edm::ParameterSet & cfg,
                           const std::vector<std::vector<hltPath *>> & hltPaths,
                           SyncGenMatchCharge genMatchCharge);
  ~SyncNtupleManagerWrapper();

  std::map<std::string, SyncNtupleManager *>::iterator
  begin();

  std::map<std::string, SyncNtupleManager *>::const_iterator
  begin() const;

  std::map<std::string, SyncNtupleManager *>::iterator
  end();

  std::map<std::string, SyncNtupleManager *>::const_iterator
  end() const;

  explicit operator bool() const;

  bool
  isGenMatched(const std::string & treeName,
               const std::string & genMatchStr) const;

protected:
  TFile * outputFile;
  std::map<std::string, SyncNtupleManager *> managers;
  std::map<std::string, std::vector<std::string>> genMatchers;
  std::vector<std::string> treeNames;
};


#endif // tthAnalysis_HiggsToTauTau_SyncNtupleManagerWrapper_h
