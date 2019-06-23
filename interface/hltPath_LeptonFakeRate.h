#ifndef tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h
#define tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"


/**
 * @brief Auxiliary data structure for handling trigger information
 *
 *        Note: This class represents a customized version of the hltPath class,
 *              specific to bin/analyze_LeptonFakeRate.cc
 */

class hltPath_LeptonFakeRate
  : public hltPath
{
 public:
  hltPath_LeptonFakeRate(const std::string & branchName,
                         bool is_trigger_1mu,
                         bool is_trigger_2mu,
                         bool is_trigger_1e,
                         bool is_trigger_2e,
                         double minPt = -1.,
                         double maxPt = -1.,
                         double minRecoPt = -1.,
                         double min_jetPt = -1.,
                         double prescale = 1.); 
  ~hltPath_LeptonFakeRate() {}

  std::string getPathName() const;
  double getMinJetPt() const;
  double getMinRecoPt() const;
  double getPrescale() const;
  bool is_trigger_1mu() const;
  bool is_trigger_2mu() const;
  bool is_trigger_1e() const;
  bool is_trigger_2e() const;
  bool isTriggered() const;
  void setIsTriggered(bool decision) const;

  friend class hltPathReader;

 private:
  double minRecoPt_;
  double minJetPt_;
  double prescale_;
  bool is_trigger_1mu_;
  bool is_trigger_2mu_;
  bool is_trigger_1e_;
  bool is_trigger_2e_;
  mutable bool isTriggered_;
};

std::vector<hltPath_LeptonFakeRate *>
create_hltPaths_LeptonFakeRate(const std::vector<std::string> & branchNames,
                               const edm::ParameterSet & cfg);

void
hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate *> & hltPaths);
/**
 * @brief Used in sortin HLT paths by reco pT thresholds in descending order (from higher pT threshold to lowest)
 * @param trigger_lhs The first HLT path
 * @param trigger_rhs The second HLT path
 * @return true if the reco pT threshold is higher in the first HLT path than in the second path; false otherwise
 */
bool
isHigherMinRecoPt(hltPath_LeptonFakeRate * trigger_lhs,
                  hltPath_LeptonFakeRate * trigger_rhs);

std::ostream &
operator<<(std::ostream & stream,
           const hltPath_LeptonFakeRate & hltPath_iter);

#endif // tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h
