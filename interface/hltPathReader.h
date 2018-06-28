#ifndef tthAnalysis_HiggsToTauTau_hltPathReader_h
#define tthAnalysis_HiggsToTauTau_hltPathReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath

#include <Rtypes.h> // Int_t

#include <vector>
#include <string>

class hltPathReader
  : public ReaderBase
{
 public:
  hltPathReader(const std::vector<hltPath*> & hltPaths);
  hltPathReader(const std::vector<std::vector<hltPath*>> & hltPaths);
  ~hltPathReader() {}

  void
  setBranchAddresses(TTree * tree) override;

 private:
  std::vector<std::string>
  get_available_branches(TTree * tree) const;

  std::vector<hltPath*> hltPaths_;
};

#endif // tthAnalysis_HiggsToTauTau_hltPathReader_h
