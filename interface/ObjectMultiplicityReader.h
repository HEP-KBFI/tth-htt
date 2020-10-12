#ifndef tthAnalysis_HiggsToTauTau_ObjectMultiplicityReader_h
#define tthAnalysis_HiggsToTauTau_ObjectMultiplicityReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

// forward declarations
class TTree;
class ObjectMultiplicity;

class ObjectMultiplicityReader
  : public ReaderBase
{
public:
  ObjectMultiplicityReader();
  ObjectMultiplicityReader(ObjectMultiplicity * objectMultiplicity);
  ~ObjectMultiplicityReader() override;

  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  void
  setObjectMultiplicity(ObjectMultiplicity * objectMultiplicity);

protected:
  ObjectMultiplicity * objectMultiplicity_;

  std::string branchName_nMuon_;
  std::string branchName_nElectron_;
  std::string branchName_nHadTau_;
};

#endif // tthAnalysis_HiggsToTauTau_ObjectMultiplicityReader_h
