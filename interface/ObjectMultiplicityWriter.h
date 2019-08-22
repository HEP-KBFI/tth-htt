#ifndef tthAnalysis_HiggsToTauTau_ObjectMultiplicityWriter_h
#define tthAnalysis_HiggsToTauTau_ObjectMultiplicityWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity

// forward declarations
class TTree;

class ObjectMultiplicityWriter
{
public:
  ObjectMultiplicityWriter(bool verbose = false);

  void
  setBranches(TTree * tree);

  void
  write(const ObjectMultiplicity & objectMultiplicity);

protected:
  bool verbose_;
  std::string branchName_nMuon_;
  std::string branchName_nElectron_;
  std::string branchName_nHadTau_;

  ObjectMultiplicity objectMultiplicity_;
};

#endif // tthAnalysis_HiggsToTauTau_ObjectMultiplicityWriter_h
