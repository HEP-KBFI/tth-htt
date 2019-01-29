#ifndef tthAnalysis_HiggsToTauTau_RecoJetWriter_h
#define tthAnalysis_HiggsToTauTau_RecoJetWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle, *_t

#include <string>
#include <vector>
#include <map>

// forward declarations
class TTree;
class RecoJet;
class GenParticleWriter;

class RecoJetWriter
{
public:
  RecoJetWriter(int era,
                bool isMC);
  RecoJetWriter(int era,
                bool isMC,
                const std::string & branchName_obj);
  RecoJetWriter(int era,
                bool isMC,
                const std::string & branchName_num,
                const std::string & branchName_obj);
  ~RecoJetWriter();

  void
  setPtMass_central_or_shift(int central_or_shift);

  void
  write_ptMass_systematics(bool flag);

  void
  write_BtagWeight_systematics(bool flag);

  /**
   * @brief Call tree->Branch for all RecoJet branches
   */
  void
  setBranches(TTree * tree);

  /**
   * @brief Write collection of RecoJet objects to tree
   */
  void
  write(const std::vector<const RecoJet *> & jets);

  /**
   * @brief Write branches containing information on matching of RecoJet objects
   *        to generator level electrons, muons, hadronic taus, and jets to tree
   */
  void
  writeGenMatching(const std::vector<const RecoJet *> & jets);

protected:
 /**
   * @brief Initialize names of branches to be written to tree
   */
  void
  setBranchNames();

  int era_;
  bool isMC_;
  int ptMassOption_;
  bool write_ptMass_systematics_;
  bool write_BtagWeight_systematics_;

  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;
  std::string branchName_btag_;

  GenParticleWriter * genLeptonWriter_;
  GenParticleWriter * genHadTauWriter_;
  GenParticleWriter * genJetWriter_;
  GenParticle dummyGenParticle_;

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
  std::map<int, std::string> branchNames_pt_systematics_;
  std::map<int, std::string> branchNames_mass_systematics_;
  std::map<int, std::string> branchNames_BtagWeight_systematics_;

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
  std::map<int, Float_t *> jet_pt_systematics_;
  std::map<int, Float_t *> jet_mass_systematics_;
  std::map<int, Float_t *> jet_BtagWeights_systematics_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetWriter_h

