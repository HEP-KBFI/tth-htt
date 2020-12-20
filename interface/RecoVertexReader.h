#ifndef tthAnalysis_HiggsToTauTau_RecoVertexReader_h
#define tthAnalysis_HiggsToTauTau_RecoVertexReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <map> // std::map<,>

// forward declarations
class TTree;
class RecoVertex;

class RecoVertexReader
  : public ReaderBase
{
public:
  explicit RecoVertexReader(RecoVertex * recoVertex);
  explicit RecoVertexReader(RecoVertex * recoVertex,
                            const std::string & branchName);
  ~RecoVertexReader() override;

  /**
   * @brief Call tree->SetBranchAddress for all RecoVertex branches
   */
  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Set reco vertex member
   * @param recoVertex Pointer to the reco vertex object
   */
  void
  set_recoVertex(RecoVertex * recoVertex);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  std::string branchName_;

  std::string branchName_x_;
  std::string branchName_y_;
  std::string branchName_z_;
  std::string branchName_ndof_;
  std::string branchName_chi2_;
  std::string branchName_score_;
  std::string branchName_npvs_;
  std::string branchName_npvsGood_;

  RecoVertex * recoVertex_;

  // CV: make sure that only one RecoVertexReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoVertexReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoVertexReader_h
