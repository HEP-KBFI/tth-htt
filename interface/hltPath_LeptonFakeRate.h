#ifndef tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h
#define tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"

/**
 * @brief Auxiliary data structure for handling trigger information
 *
 *        Note: This class represents a customized version of the hltPath class,
 *              specific to bin/analyze_LeptonFakeRate.cc
 */

class hltPath_LeptonFakeRate : public hltPath
{
 public:
  hltPath_LeptonFakeRate(const std::string& branchName, 
			 bool is_trigger_1mu, bool is_trigger_2mu, bool is_trigger_1e, bool is_trigger_2e,
			 double minPt = -1., double maxPt = -1., double min_jetPt = -1., double prescale = 1., double prescale_rand_mc = 1.)
    : hltPath(branchName, minPt, maxPt) 
    , branchName_(branchName)
    , value_(-1)
    , minPt_(minPt)
    , maxPt_(maxPt)
    , minJetPt_(min_jetPt)
    , prescale_(prescale)
    , prescale_rand_mc_(prescale_rand_mc)
    , is_trigger_1mu_(is_trigger_1mu)
    , is_trigger_2mu_(is_trigger_2mu)
    , is_trigger_1e_(is_trigger_1e)
    , is_trigger_2e_(is_trigger_2e)
    {}
    ~hltPath_LeptonFakeRate() {}    

  double getMinJetPt() const
  {
    return minJetPt_;  
  }

  double getPrescale() const
  {
    return prescale_;  
  }

  double getPrescale_rand_mc() const
  {
    return prescale_rand_mc_;  
  }

  std::string getPathName() const
  {
    return branchName_;
  }

  bool is_trigger_1mu() const 
  { 
    return is_trigger_1mu_; 
  }
  bool is_trigger_2mu() const 
  { 
    return is_trigger_2mu_; 
  }
  bool is_trigger_1e() const 
  { 
    return is_trigger_1e_; 
  }
  bool is_trigger_2e() const 
  { 
    return is_trigger_2e_; 
  }

 private:
  std::string branchName_;  
  Int_t value_;
  double minPt_;
  double maxPt_;
  double minJetPt_;
  double prescale_;
  double prescale_rand_mc_;
  bool is_trigger_1mu_;
  bool is_trigger_2mu_;
  bool is_trigger_1e_;
  bool is_trigger_2e_;
};

void hltPaths_LeptonFakeRate_setBranchAddresses(TTree* tree, const std::vector<hltPath_LeptonFakeRate*>& hltPaths);
std::vector<hltPath_LeptonFakeRate*> create_hltPaths_LeptonFakeRate(const std::vector<std::string>& branchNames, const edm::ParameterSet& cfg);
void hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate*>& hltPaths);

#endif // tthAnalysis_HiggsToTauTau_hltPath_LeptonFakeRate_h
