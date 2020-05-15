#ifndef tthAnalysis_HiggsToTauTau_RecoVertexReader_h
#define tthAnalysis_HiggsToTauTau_RecoVertexReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoVertex.h" // RecoVertex

// forward declarations
class TTree;
class EventInfo;

class RecoVertexReader
  : public ReaderBase
{
public:
  explicit RecoVertexReader();
  explicit RecoVertexReader(const std::string & branchName);
  ~RecoVertexReader() override;

  /**
   * @brief Call tree->SetBranchAddress for all RecoVertex branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill RecoVertex object
   * @return RecoVertex object (the primary vertex with the hightest sum(pT^2) of clustered objects)
   */
  RecoVertex
  read() const;

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

  Float_t vertex_x_;
  Float_t vertex_y_;
  Float_t vertex_z_;
  Float_t vertex_ndof_;
  Float_t vertex_chi2_;
  Float_t vertex_score_;
  Int_t vertex_npvs_;
  Int_t vertex_npvsGood_;

  // CV: make sure that only one RecoVertexReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoVertexReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoVertexReader_h
