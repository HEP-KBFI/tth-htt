#ifndef tthAnalysis_HiggsToTauTau_RecoJetWriter_h
#define tthAnalysis_HiggsToTauTau_RecoJetWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoJetWriter
{
 public:
  RecoJetWriter(int era, bool isMC);
  RecoJetWriter(int era, bool isMC, const std::string& branchName_num, const std::string& branchName_obj);
  ~RecoJetWriter();

  /**
   * @brief Call tree->Branch for all RecoJet branches
   */
  void setBranches(TTree* tree);

  /**
   * @brief Write collection of RecoJet objects to tree
   */
  void write(const std::vector<const RecoJet*>& jets);
  
  /**
   * @brief Write branches containing information on matching of RecoJet objects
   *        to generator level electrons, muons, hadronic taus, and jets to tree
   */
  void writeGenMatching(const std::vector<const RecoJet*>& jets);

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

  GenParticleWriter* genLeptonWriter_;
  GenParticleWriter* genHadTauWriter_;
  GenParticleWriter* genJetWriter_;
  GenParticle dummyGenParticle_;

  std::string branchName_pt_;  
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_jecUncertTotal_;
  std::string branchName_BtagCSV_;
  std::string branchName_BtagWeight_;
  std::string branchName_QGDiscr_;
  std::map<int, std::string> branchNames_BtagWeight_systematics_;

  UInt_t nJets_;
  Float_t* jet_pt_;
  Float_t* jet_eta_;
  Float_t* jet_phi_;
  Float_t* jet_mass_;
  Float_t* jet_jecUncertTotal_;
  Float_t* jet_BtagCSV_;
  Float_t* jet_BtagWeight_;
  Float_t* jet_QGDiscr_;
  std::map<int, Float_t*> jet_BtagWeights_systematics_; 
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetWriter_h

