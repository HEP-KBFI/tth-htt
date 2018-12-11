#ifndef tthAnalysis_HiggsToTauTau_GenParticleWriter_h
#define tthAnalysis_HiggsToTauTau_GenParticleWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include <string> // std::string
#include <vector> // std::vector<>

// forward declaration
class TTree;

class GenParticleWriter
{
public:
  GenParticleWriter(const std::string & branchName_obj,
                    unsigned int max_nParticles = 36);
  GenParticleWriter(const std::string & branchName_num,
                    const std::string & branchName_obj,
                    unsigned int max_nParticles = 36);
  ~GenParticleWriter();

  /**
   * @brief Call tree->Branch for all GenParticle branches
   */
  void setBranches(TTree * tree);

  /**
   * @brief Write collection of GenParticle objects to tree
   */
  void write(const std::vector<GenParticle> & particles);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  const unsigned int max_nParticles_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_charge_;
  std::string branchName_pdgId_;

  UInt_t nParticles_;
  Float_t * particle_pt_;
  Float_t * particle_eta_;
  Float_t * particle_phi_;
  Float_t * particle_mass_;
  Int_t * particle_charge_;
  Int_t * particle_pdgId_;
};

#endif // tthAnalysis_HiggsToTauTau_GenParticleWriter_h

