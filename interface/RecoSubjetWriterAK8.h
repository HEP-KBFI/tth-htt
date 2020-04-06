#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetWriterAK8_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetWriterAK8_h

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

#include <Rtypes.h> // UInt_t, Float_t

#include <string>
#include <vector>
#include <map>

// forward declarations
class TTree;
class RecoSubjetAK8;
enum class Btag;

class RecoSubjetWriterAK8
{
public:
  RecoSubjetWriterAK8(Era era);
  RecoSubjetWriterAK8(Era era,
                      const std::string & branchName_obj);
  RecoSubjetWriterAK8(Era era,
                      const std::string & branchName_num,
                      const std::string & branchName_obj);
  ~RecoSubjetWriterAK8();

  /**
   * @brief Call tree->Branch for all RecoSubjetAK8 branches
   */
  void
  setBranches(TTree * tree);

  /**
   * @brief Write collection of RecoSubjetAK8 objects to tree
   */
  void
  write(const std::vector<const RecoSubjetAK8 *> & jets);

protected:
 /**
   * @brief Initialize names of branches to be written to tree
   */
  void
  setBranchNames();

  Era era_;
  Btag btag_;

  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;
  std::string branchName_btag_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_BtagCSV_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Float_t * jet_BtagCSV_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetReaderAK8_h
