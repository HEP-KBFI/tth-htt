#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h"

void hltPaths_LeptonFakeRate_setBranchAddresses(TTree* tree, const std::vector<hltPath_LeptonFakeRate*>& hltPaths)
{
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths.begin();
        hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    (*hltPath_iter)->setBranchAddress(tree);
  }
}

std::vector<hltPath_LeptonFakeRate*> create_hltPaths_LeptonFakeRate(const std::vector<std::string>& branchNames, const edm::ParameterSet& cfg)
{
  double minPt = cfg.getParameter<double>("cone_minPt");  
  double maxPt = cfg.getParameter<double>("cone_maxPt"); 
  double jet_minPt = cfg.getParameter<double>("jet_minPt");       
  double prescale = cfg.getParameter<double>("average_prescale");
  double prescale_rand_mc = cfg.getParameter<double>("prescale_rand_mc");
  bool is_trigger_1mu = cfg.getParameter<bool>("is_trigger_1mu");
  bool is_trigger_2mu = cfg.getParameter<bool>("is_trigger_2mu");
  bool is_trigger_1e = cfg.getParameter<bool>("is_trigger_1e");
  bool is_trigger_2e = cfg.getParameter<bool>("is_trigger_2e");
  std::vector<hltPath_LeptonFakeRate*> hltPaths;
  for ( std::vector<std::string>::const_iterator branchName = branchNames.begin();
        branchName != branchNames.end(); ++branchName ) {
    hltPaths.push_back(new hltPath_LeptonFakeRate(
      *branchName, 
      is_trigger_1mu, is_trigger_2mu, is_trigger_1e, is_trigger_2e,
      minPt, maxPt, jet_minPt, prescale, prescale_rand_mc));
  }
  return hltPaths;
}

void hltPaths_LeptonFakeRate_delete(const std::vector<hltPath_LeptonFakeRate*>& hltPaths)
{
  for ( std::vector<hltPath_LeptonFakeRate*>::const_iterator hltPath_iter = hltPaths.begin();
        hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    delete (*hltPath_iter);
  }
}

std::ostream& operator<<(std::ostream& stream, const hltPath_LeptonFakeRate& hltPath_iter)
{
  stream << "hltPath = " << hltPath_iter.getBranchName() << ": value = " << hltPath_iter.getValue() 
	 << " (minPt = " << hltPath_iter.getMinPt() << ", maxPt = " << hltPath_iter.getMaxPt() << ", minJetPt = " << hltPath_iter.getMinJetPt() << ","
	 << " prescale = " << hltPath_iter.getPrescale() << ", prescale_rand_mc = " << hltPath_iter.getPrescale_rand_mc() << ")" << std::endl;
  return stream;
}

