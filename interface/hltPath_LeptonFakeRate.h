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
                         double minRecoPt = -1., // NEWLY ADDED AFTER GIOVANNI SYNC
                         double min_jetPt = -1.,
                         double prescale = 1.,
                         double prescale_rand_mc = 1.); 
  ~hltPath_LeptonFakeRate() {}

  std::string getPathName() const;
  double getMinJetPt() const;
  double getMinRecoPt() const; // NEWLY ADDED AFTER GIOVANNI SYNC 
  double getPrescale() const;
  double getPrescale_rand_mc() const;
  bool is_trigger_1mu() const;
  bool is_trigger_2mu() const;
  bool is_trigger_1e() const;
  bool is_trigger_2e() const;
  bool isTriggered() const; // NEWLY ADDED AFTER CHRISTIAN'S LOGIC
  void setIsTriggered(bool decision) const; // NEWLY ADDED AFTER CHRISTIAN'S LOGIC
 private:
  std::string branchName_;
  Int_t value_;
  double minPt_;
  double maxPt_;
  double minRecoPt_;   // NEWLY ADDED AFTER GIOVANNI SYNC 
  double minJetPt_;
  double prescale_;
  double prescale_rand_mc_;
  bool is_trigger_1mu_;
  bool is_trigger_2mu_;
  bool is_trigger_1e_;
  bool is_trigger_2e_;
  mutable bool isTriggered_; // NEWLY ADDED AFTER CHRISTIAN'S LOGIC
};

void
hltPaths_LeptonFakeRate_setBranchAddresses(TTree * tree,
                                           const std::vector<hltPath_LeptonFakeRate *> & hltPaths);

std::vector<hltPath_LeptonFakeRate *>
create_hltPaths_LeptonFakeRate(const std::vector<std::string> & branchNames,
                               const edm::ParameterSet & cfg);

void
hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate *> & hltPaths);

std::ostream &
operator<<(std::ostream & stream,
           const hltPath_LeptonFakeRate & hltPath_iter);







// bool hltPaths_LeptonFakeRate_isTriggered(const std::vector<hltPath_LeptonFakeRate *> & hltPaths, bool verbose); // NEWLY ADDED AFTER CHRISTIAN'S LOGIC



#endif // tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h
