#ifndef tthAnalysis_HiggsToTauTau_RecoMEtWriter_h
#define tthAnalysis_HiggsToTauTau_RecoMEtWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt, *_t

#include <string> // std::string
#include <map> // std::map<,>

// forward declarations
class TTree;

class RecoMEtWriter
{
 public:
  RecoMEtWriter(int era);
  RecoMEtWriter(int era,
                const std::string & branchName_obj);
  ~RecoMEtWriter();

  /**
   * @brief Call tree->Branch for all RecoMEt branches
   */
  void setBranches(TTree * tree);

  /**
   * @brief Write RecoMEt object to tree
   */
  void write(const RecoMEt & met);
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  std::string branchName_obj_;

  std::map<int, std::string> branchName_pt_;
  std::map<int, std::string> branchName_phi_;
  std::string branchName_covXX_;
  std::string branchName_covXY_;
  std::string branchName_covYY_;

  RecoMEt met_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMEtWriter_h

