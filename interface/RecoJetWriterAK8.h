#ifndef tthAnalysis_HiggsToTauTau_RecoJetWriterAK8_h
#define tthAnalysis_HiggsToTauTau_RecoJetWriterAK8_h

#include <Rtypes.h> // UInt_t, Float_t

#include <string>
#include <vector>
#include <map>

// forward declarations
class TTree;
class RecoJetAK8;
class RecoSubjetWriterAK8;

class RecoJetWriterAK8
{
public:
  RecoJetWriterAK8(int era);
  RecoJetWriterAK8(int era,
                   const std::string & branchName_jet,
                   const std::string & branchName_subjet);
  RecoJetWriterAK8(int era,
                   const std::string & branchName_num_jet,
		   const std::string & branchName_jet,
		   const std::string & branchName_num_subjet,
                   const std::string & branchName_subjet);
  ~RecoJetWriterAK8();

  /**
   * @brief Call tree->Branch for all RecoJetAK8 branches
   */
  void
  setBranches(TTree * tree);

  /**
   * @brief Write collection of RecoJetAK8 objects to tree
   */
  void
  write(const std::vector<const RecoJetAK8 *> & jets);

  /**
   * @brief Write branches containing information on subjets of RecoJetAK8 objects to tree
   */
  void
  writeSubjets(const std::vector<const RecoJetAK8 *> & jets);

protected:
 /**
   * @brief Initialize names of branches to be written to tree
   */
  void
  setBranchNames();

  int era_;
  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  RecoSubjetWriterAK8 * subjetWriter_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_msoftdrop_;
  std::string branchName_subJetIdx1_;
  std::string branchName_subJetIdx2_;
  std::string branchName_tau1_;
  std::string branchName_tau2_;
  std::string branchName_tau3_;
  std::string branchName_tau4_;
  std::string branchName_jetId_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Float_t * jet_msoftdrop_;
  Int_t * subjet_idx1_;
  Int_t * subjet_idx2_;
  Float_t * jet_tau1_;
  Float_t * jet_tau2_;
  Float_t * jet_tau3_;
  Float_t * jet_tau4_;
  Int_t * jet_jetId_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetWriterAK8_h
