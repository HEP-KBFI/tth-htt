#ifndef tthAnalysis_HiggsToTauTau_hltPath_h
#define tthAnalysis_HiggsToTauTau_hltPath_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include <Rtypes.h> // Int_t

#include <iosfwd> // std::ostream

/**
 * @brief Auxiliary data structure for handling trigger information
 */
class hltPath
{
public:
  hltPath(const std::string & branchName,
          double minPt = -1.,
          double maxPt = -1.,
          const std::string & label = "");
  ~hltPath() {}

  const std::string &
  getBranchName() const;

  Int_t
  getValue() const;

  double
  getMinPt() const;

  double
  getMaxPt() const;

  const std::string &
  getLabel() const;

  friend class hltPathReader;

protected:
  std::vector<std::string>
  get_available_branches(TTree * tree) const;

  std::string branchName_;
  Bool_t value_;
  double minPt_;
  double maxPt_;
  std::string label_;
};

std::vector<hltPath *>
create_hltPaths(const std::vector<std::string> & branchNames,
                const std::string & label = "");

std::vector<hltPath *>
filter_hltPaths(const std::vector<hltPath *> & hltPaths,
                const std::vector<std::string> & branchNames);

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths,
                     bool verbose = false);

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths,
                     const edm::ParameterSet & runRanges,
                     const EventInfo & eventInfo,
                     bool isMC,
                     bool verbose = false);

void
hltPaths_delete(const std::vector<hltPath *> & hltPaths);

std::ostream &
operator<<(std::ostream & stream,
           const hltPath & hltPath_iter);

#endif // tthAnalysis_HiggsToTauTau_hltPath_h
