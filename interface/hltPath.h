#ifndef tthAnalysis_HiggsToTauTau_hltPath_h
#define tthAnalysis_HiggsToTauTau_hltPath_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <Rtypes.h> // Int_t

#include <iosfwd> // std::ostream

/**
 * @brief Auxiliary data structure for handling trigger information
 */
class hltPath
  : public ReaderBase
{
 public:
 hltPath(const std::string & branchName,
         double minPt = -1.,
         double maxPt = -1.);
  ~hltPath() {}

  void
  setBranchAddress(TTree * tree);

  void
  setBranchAddresses(TTree * tree) override;

  const std::string &
  getBranchName() const;

  Int_t
  getValue() const;

  double
  getMinPt() const;

  double
  getMaxPt() const;

 private:
  std::string branchName_;
  Bool_t value_;
  double minPt_;
  double maxPt_;
};

std::vector<hltPath *>
create_hltPaths(const std::vector<std::string> & branchNames);

void
hltPaths_setBranchAddresses(TTree * tree,
                            const std::vector<hltPath *> & hltPaths);

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths);

void
hltPaths_delete(const std::vector<hltPath *> & hltPaths);

std::ostream &
operator<<(std::ostream & stream,
           const hltPath & hltPath_iter);

#endif // tthAnalysis_HiggsToTauTau_hltPath_h
