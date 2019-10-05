#ifndef tthAnalysis_HiggsToTauTau_GenMEtReader_h
#define tthAnalysis_HiggsToTauTau_GenMEtReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/GenMEt.h" // GenMEt

#include <map> // std::map<,>

// forward declarations
class TTree;

class GenMEtReader
: public ReaderBase
{
 public:
  GenMEtReader(int era,
                bool isMC);
  GenMEtReader(int era,
                bool isMC,
                const std::string & branchName_obj);
  ~GenMEtReader();

  /**
   * @brief Call tree->SetBranchAddress for all RecoMEt branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill RecoMEt object
   * @return RecoMEt object
   */
  GenMEt
  read() const;

protected:
  /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;
  bool isMC_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_phi_;

  GenMEt met_;

  // CV: make sure that only one GenMEtReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenMEtReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenMEtReader_h  
