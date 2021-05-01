#ifndef GENPHOTONREADER_H
#define GENPHOTONREADER_H

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton

#include <map> // std::map<,>

// forward declarations
class TTree;

class GenPhotonReader
  : public ReaderBase
{
public:

  GenPhotonReader(unsigned int max_nPhotons = 36);
  GenPhotonReader(const std::string & branchName_obj,
                  unsigned int max_nPhotons = 36);
  ~GenPhotonReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenPhoton branches
   */
  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of GenPhoton objects
   * @return Collection of GenPhoton objects
   */
  std::vector<GenPhoton>
  read(bool readAll = false) const;

  /**
   * @brief enable/disable read genPartFlav branch
   * @param flag If true, reads genPartFlav branch; if false, does not read genPartFlav branch
   */
  void
  readGenPartFlav(bool flag);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  const unsigned int max_nPhotons_;
  std::string branchName_num_;
  std::string branchName_obj_;

  bool readGenPartFlav_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_pdgId_;
  std::string branchName_status_;
  std::string branchName_statusFlags_;
  std::string branchName_genPartFlav_;

  UInt_t nPhotons_;
  Float_t * photon_pt_;
  Float_t * photon_eta_;
  Float_t * photon_phi_;
  Float_t * photon_mass_;
  Int_t * photon_pdgId_;
  Int_t * photon_status_;
  Int_t * photon_statusFlags_;
  UChar_t * photon_genPartFlav_;

  // CV: make sure that only one GenPhotonReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenPhotonReader *> instances_;
};

#endif // GENPHOTONREADER_H
