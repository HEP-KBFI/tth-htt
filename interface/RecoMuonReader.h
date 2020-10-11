#ifndef tthAnalysis_HiggsToTauTau_RecoMuonReader_h
#define tthAnalysis_HiggsToTauTau_RecoMuonReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"             // RecoMuon, *_t
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h"           // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

#include <map> // std::map<,>

// forward declarations
class RecoLeptonReader;

class RecoMuonReader
  : public ReaderBase
{
public:
  RecoMuonReader(Era era,
                 bool isMC,
                 bool readGenMatching);
  RecoMuonReader(Era era,
                 const std::string & branchName_obj,
                 bool isMC,
                 bool readGenMatching);
  ~RecoMuonReader();

  /**
   * @brief Call tree->SetBranchAddress for all lepton branches specific to RecoMuons
   */
  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoMuon objects
   * @return Collection of RecoMuon objects
   */
  std::vector<RecoMuon>
  read() const;

  void
  set_mvaTTH_wp(double mvaTTH_wp);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  Era era_;
  std::string branchName_num_;
  std::string branchName_obj_;

  RecoLeptonReader * leptonReader_;

  std::string branchName_mediumIdPOG_;
  std::string branchName_segmentCompatibility_;
  std::string branchName_ptErr_;

  Bool_t  * mediumIdPOG_;
  Float_t * segmentCompatibility_;
  Float_t * ptErr_;

  double mvaTTH_wp_;

  // CV: make sure that only one RecoMuonReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoMuonReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuonReader_h

