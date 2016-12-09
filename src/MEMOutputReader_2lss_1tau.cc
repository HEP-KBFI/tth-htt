#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_2lss_1tau.h" // MEMOutputReader_2lss_1tau

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

#include <assert.h> // assert

std::map<std::string, int> MEMOutputReader_2lss_1tau::numInstances_;
std::map<std::string, MEMOutputReader_2lss_1tau*> MEMOutputReader_2lss_1tau::instances_;

MEMOutputReader_2lss_1tau::MEMOutputReader_2lss_1tau(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nMEMOutputs_(100)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leadLepton_eta_(0)
  , leadLepton_phi_(0)
  , subleadLepton_eta_(0)
  , subleadLepton_phi_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , type_(0)
  , weight_ttH_(0)
  , weight_ttZ_(0)
  , weight_ttZ_Zll_(0)
  , weight_tt_(0)
  , LR_(0)
  , cpuTime_(0)
  , realTime_(0)
  , errorFlag_(0)
{
  setBranchNames();
}

MEMOutputReader_2lss_1tau::~MEMOutputReader_2lss_1tau()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    MEMOutputReader_2lss_1tau* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->leadLepton_eta_;
    delete[] gInstance->leadLepton_phi_;
    delete[] gInstance->subleadLepton_eta_;
    delete[] gInstance->subleadLepton_phi_;
    delete[] gInstance->hadTau_eta_;
    delete[] gInstance->hadTau_phi_;
    delete[] gInstance->type_;
    delete[] gInstance->weight_ttH_;
    delete[] gInstance->weight_ttZ_;
    delete[] gInstance->weight_ttZ_Zll_;
    delete[] gInstance->weight_tt_;
    delete[] gInstance->LR_;
    delete[] gInstance->cpuTime_;
    delete[] gInstance->realTime_;
    delete[] gInstance->errorFlag_;
    instances_[branchName_obj_] = 0;
  }
}

void MEMOutputReader_2lss_1tau::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_leadLepton_eta_ = Form("%s_%s", branchName_obj_.data(), "leadLepton_eta");
    branchName_leadLepton_phi_ = Form("%s_%s", branchName_obj_.data(), "leadLepton_phi");
    branchName_subleadLepton_eta_ = Form("%s_%s", branchName_obj_.data(), "subleadLepton_eta");
    branchName_subleadLepton_phi_ = Form("%s_%s", branchName_obj_.data(), "subleadLepton_phi");
    branchName_hadTau_eta_ = Form("%s_%s", branchName_obj_.data(), "hadTau_eta");
    branchName_hadTau_phi_ = Form("%s_%s", branchName_obj_.data(), "hadTau_phi");
    branchName_type_ = Form("%s_%s", branchName_obj_.data(), "type");
    branchName_weight_ttH_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH");
    branchName_weight_ttZ_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ");
    branchName_weight_ttZ_Zll_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ_Zll");
    branchName_weight_tt_ = Form("%s_%s", branchName_obj_.data(), "weight_tt");
    branchName_LR_ = Form("%s_%s", branchName_obj_.data(), "LR");
    branchName_cpuTime_ = Form("%s_%s", branchName_obj_.data(), "cpuTime");
    branchName_realTime_ = Form("%s_%s", branchName_obj_.data(), "realTime");
    branchName_errorFlag_ = Form("%s_%s", branchName_obj_.data(), "errorFlag");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("MEMOutputReader_2lss_1tau") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void MEMOutputReader_2lss_1tau::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nMEMOutputs_);   
    leadLepton_eta_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_leadLepton_eta_.data(), leadLepton_eta_); 
    leadLepton_phi_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_leadLepton_phi_.data(), leadLepton_phi_); 
    subleadLepton_eta_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_subleadLepton_eta_.data(), subleadLepton_eta_); 
    subleadLepton_phi_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_subleadLepton_phi_.data(), subleadLepton_phi_); 
    hadTau_eta_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_hadTau_eta_.data(), hadTau_eta_); 
    hadTau_phi_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_hadTau_phi_.data(), hadTau_phi_); 
    type_ = new Int_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_type_.data(), type_); 
    weight_ttH_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_weight_ttH_.data(), weight_ttH_); 
    weight_ttZ_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_weight_ttZ_.data(), weight_ttZ_); 
    weight_ttZ_Zll_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_weight_ttZ_Zll_.data(), weight_ttZ_Zll_); 
    weight_tt_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_weight_tt_.data(), weight_tt_); 
    LR_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_LR_.data(), LR_); 
    cpuTime_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_cpuTime_.data(), cpuTime_); 
    realTime_ = new Float_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_realTime_.data(), realTime_); 
    errorFlag_ = new Int_t[max_nMEMOutputs_];
    tree->SetBranchAddress(branchName_errorFlag_.data(), errorFlag_); 
  }
}

std::vector<MEMOutput_2lss_1tau> MEMOutputReader_2lss_1tau::read() const
{
  MEMOutputReader_2lss_1tau* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<MEMOutput_2lss_1tau> memOutputs;
  Int_t nMEMOutputs = gInstance->nMEMOutputs_;
  if ( nMEMOutputs > max_nMEMOutputs_ ) {
    throw cms::Exception("MEMOutputReader_2lss_1tau") 
      << "Number of MEMOutputs stored in Ntuple = " << nMEMOutputs << ", exceeds max_nMEMOutputs = " << max_nMEMOutputs_ << " !!\n";
  }
  memOutputs.reserve(nMEMOutputs);
  for ( Int_t idxMEMOutput = 0; idxMEMOutput < nMEMOutputs; ++idxMEMOutput ) {
    memOutputs.push_back(MEMOutput_2lss_1tau({
      gInstance->leadLepton_eta_[idxMEMOutput],
      gInstance->leadLepton_phi_[idxMEMOutput],
      gInstance->subleadLepton_eta_[idxMEMOutput],
      gInstance->subleadLepton_phi_[idxMEMOutput],
      gInstance->hadTau_eta_[idxMEMOutput],
      gInstance->hadTau_phi_[idxMEMOutput],
      gInstance->type_[idxMEMOutput],
      gInstance->weight_ttH_[idxMEMOutput],
      gInstance->weight_ttZ_[idxMEMOutput],
      gInstance->weight_ttZ_Zll_[idxMEMOutput],
      gInstance->weight_tt_[idxMEMOutput],
      gInstance->LR_[idxMEMOutput],
      gInstance->cpuTime_[idxMEMOutput],
      gInstance->realTime_[idxMEMOutput],
      gInstance->errorFlag_[idxMEMOutput] }));
  }
  return memOutputs;
}
