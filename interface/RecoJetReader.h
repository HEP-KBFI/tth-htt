#ifndef tthAnalysis_HiggsToTauTau_RecoJetReader_h
#define tthAnalysis_HiggsToTauTau_RecoJetReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoJetReader
{
 public:
  RecoJetReader(int era, bool isMC, bool readGenMatching = false);
  RecoJetReader(int era, bool isMC, const std::string& branchName_num, const std::string& branchName_obj, bool readGenMatching = false); 
  ~RecoJetReader();

  enum { kJetPt_central, kJetPt_jecUp, kJetPt_jecDown };
  void setJetPt_central_or_shift(int jetPt_option) { jetPt_option_ = jetPt_option; }

  void setBranchName_BtagWeight(const std::string& branchName_BtagWeight) { branchName_BtagWeight_ = branchName_BtagWeight; }

  void read_BtagWeight_systematics(bool flag) { read_BtagWeight_systematics_ = flag; }

  /**
   * @brief Call tree->SetBranchAddress for all RecoJet branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJet objects
   * @return Collection of RecoJet objects
   */
  std::vector<RecoJet> read() const;
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  bool isMC_;
  const int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  /**
   * @brief Read branches containing information on matching of RecoJet objects
   *        to generator level electrons, muons, hadronic taus, and jets from tree
   *        and add this information to collection of RecoJet objects given as function argument
   */
  void readGenMatching(std::vector<RecoJet>& jets) const;

  GenLeptonReader* genLeptonReader_;
  GenHadTauReader* genHadTauReader_;
  GenJetReader* genJetReader_;
  bool readGenMatching_;
  mutable std::vector<GenLepton> matched_genLeptons_;
  mutable std::vector<GenHadTau> matched_genHadTaus_;
  mutable std::vector<GenJet> matched_genJets_;

  std::string branchName_pt_;  
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_corr_;
  std::string branchName_corr_JECUp_;
  std::string branchName_corr_JECDown_;
  std::string branchName_BtagCSV_;
  std::string branchName_BtagWeight_;
  std::string branchName_QGDiscr_;
  std::string branchName_heppyFlavour_;

  std::map<int, std::string> branchNames_BtagWeight_systematics_;

  int jetPt_option_;

  bool read_BtagWeight_systematics_; 

  Int_t nJets_;
  Float_t* jet_pt_;
  Float_t* jet_eta_;
  Float_t* jet_phi_;
  Float_t* jet_mass_;
  Float_t* jet_corr_;
  Float_t* jet_corr_JECUp_;
  Float_t* jet_corr_JECDown_;
  Float_t* jet_BtagCSV_;
  Float_t* jet_BtagWeight_;
  Float_t* jet_QGDiscr_;
  Int_t* jet_heppyFlavour_;

  std::map<int, Float_t*> jet_BtagWeights_systematics_; // CV: needed by RecoJetWriter

  // CV: make sure that only one RecoJetReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReader_h

