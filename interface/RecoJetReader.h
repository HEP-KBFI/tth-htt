#ifndef tthAnalysis_HiggsToTauTau_RecoJetReader_h
#define tthAnalysis_HiggsToTauTau_RecoJetReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include <map> // std::map<,>

// forward declarations
class TTree;
class GenLeptonReader;
class GenHadTauReader;
class GenJetReader;

class RecoJetReader
  : public ReaderBase
{
public:
  RecoJetReader(int era,
                bool isMC,
                bool readGenMatching = false);
  RecoJetReader(int era,
                bool isMC,
                const std::string & branchName_obj,
                bool readGenMatching = false);
  ~RecoJetReader();

  void
  setPtMass_central_or_shift(int central_or_shift);

  void
  setBranchName_BtagWeight(int central_or_shift);

  void
  read_BtagWeight_systematics(bool flag);

  void
  read_ptMass_systematics(bool flag);

  /**
   * @brief Call tree->SetBranchAddress for all RecoJet branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJet objects
   * @return Collection of RecoJet objects
   */
  std::vector<RecoJet>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;
  bool isMC_;
  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;
  std::string branchName_btag_;

  /**
   * @brief Read branches containing information on matching of RecoJet objects
   *        to generator level electrons, muons, hadronic taus, and jets from tree
   *        and add this information to collection of RecoJet objects given as function argument
   */
  void
  readGenMatching(std::vector<RecoJet> & jets) const;

  GenLeptonReader * genLeptonReader_;
  GenHadTauReader * genHadTauReader_;
  GenJetReader * genJetReader_;
  bool readGenMatching_;
 
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_jetCharge_;
  std::string branchName_BtagCSV_;
  std::string branchName_BtagWeight_;
  std::string branchName_QGDiscr_;
  std::string branchName_pullEta_;
  std::string branchName_pullPhi_;
  std::string branchName_pullMag_;
  std::string branchName_jetId_;
  std::string branchName_puId_;
  std::string branchName_genMatchIdx_;

  std::map<int, std::string> branchNames_pt_systematics_;
  std::map<int, std::string> branchNames_mass_systematics_;
  std::map<int, std::string> branchNames_BtagWeight_systematics_;

  bool read_ptMass_systematics_;
  bool read_BtagWeight_systematics_;
  int ptMassOption_;

  UInt_t nJets_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_charge_;
  Float_t * jet_BtagCSV_;
  Float_t * jet_BtagWeight_;
  Float_t * jet_QGDiscr_;
  Float_t * jet_pullEta_;
  Float_t * jet_pullPhi_;
  Float_t * jet_pullMag_;
  Int_t * jet_jetId_;
  Int_t * jet_puId_;
  Int_t * jet_genMatchIdx_;

  std::map<int, Float_t *> jet_pt_systematics_;
  std::map<int, Float_t *> jet_mass_systematics_;
  std::map<int, Float_t *> jet_BtagWeights_systematics_; // CV: needed by RecoJetWriter

  // CV: make sure that only one RecoJetReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReader_h
