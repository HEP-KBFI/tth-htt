#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_3l_1tau.h" // MEMOutputWriter_3l_1tau

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVI, setBranchVF

#include <TString.h> // Form

#include <assert.h> // assert

MEMOutputWriter_3l_1tau::MEMOutputWriter_3l_1tau(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nMEMOutputs_(100)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , run_(0)
  , lumi_(0)
  , evt_(0)
  , leadLepton_eta_(0)
  , leadLepton_phi_(0)
  , subleadLepton_eta_(0)
  , subleadLepton_phi_(0)
  , thirdLepton_eta_(0)
  , thirdLepton_phi_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , weight_ttH_(0)
  , weight_ttZ_(0)
  , weight_ttH_hww_(0)
  , LR_(0)
  , cpuTime_(0)
  , realTime_(0)
  , isValid_(0)
  , errorFlag_(0)
{
  setBranchNames();
}

MEMOutputWriter_3l_1tau::~MEMOutputWriter_3l_1tau()
{
  delete[] run_;
  delete[] lumi_;
  delete[] evt_;
  delete[] leadLepton_eta_;
  delete[] leadLepton_phi_;
  delete[] subleadLepton_eta_;
  delete[] subleadLepton_phi_;
  delete[] thirdLepton_eta_;
  delete[] thirdLepton_phi_;
  delete[] hadTau_eta_;
  delete[] hadTau_phi_;
  delete[] weight_ttH_;
  delete[] weight_ttZ_;
  delete[] weight_ttH_hww_;
  delete[] LR_;
  delete[] cpuTime_;
  delete[] realTime_;
  delete[] isValid_;
  delete[] errorFlag_;
}

void MEMOutputWriter_3l_1tau::setBranchNames()
{
  branchName_run_ = Form("%s_%s", branchName_obj_.data(), "run");
  branchName_lumi_ = Form("%s_%s", branchName_obj_.data(), "lumi");
  branchName_evt_ = Form("%s_%s", branchName_obj_.data(), "evt");
  branchName_leadLepton_eta_ = Form("%s_%s", branchName_obj_.data(), "leadLepton_eta");
  branchName_leadLepton_phi_ = Form("%s_%s", branchName_obj_.data(), "leadLepton_phi");
  branchName_subleadLepton_eta_ = Form("%s_%s", branchName_obj_.data(), "subleadLepton_eta");
  branchName_subleadLepton_phi_ = Form("%s_%s", branchName_obj_.data(), "subleadLepton_phi");
  branchName_thirdLepton_eta_ = Form("%s_%s", branchName_obj_.data(), "thirdLepton_eta");
  branchName_thirdLepton_phi_ = Form("%s_%s", branchName_obj_.data(), "thirdLepton_phi");
  branchName_hadTau_eta_ = Form("%s_%s", branchName_obj_.data(), "hadTau_eta");
  branchName_hadTau_phi_ = Form("%s_%s", branchName_obj_.data(), "hadTau_phi");
  branchName_weight_ttH_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH");
  branchName_weight_ttZ_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ");
  branchName_weight_ttH_hww_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH_hww");
  branchName_LR_ = Form("%s_%s", branchName_obj_.data(), "LR");
  branchName_cpuTime_ = Form("%s_%s", branchName_obj_.data(), "cpuTime");
  branchName_realTime_ = Form("%s_%s", branchName_obj_.data(), "realTime");
  branchName_isValid_ = Form("%s_%s", branchName_obj_.data(), "isValid");
  branchName_errorFlag_ = Form("%s_%s", branchName_obj_.data(), "errorFlag");
}

void MEMOutputWriter_3l_1tau::setBranches(TTree* tree)
{
  setBranchI(tree, branchName_num_, &nMEMOutputs_);
  run_ = new RUN_TYPE[max_nMEMOutputs_];
  setBranchVUI(tree, branchName_run_, branchName_num_, run_);
  lumi_ = new LUMI_TYPE[max_nMEMOutputs_];
  setBranchVUI(tree, branchName_lumi_, branchName_num_, lumi_);
  evt_ = new EVT_TYPE[max_nMEMOutputs_];
  setBranchVUL(tree, branchName_evt_, branchName_num_, evt_);
  leadLepton_eta_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_leadLepton_eta_, branchName_num_, leadLepton_eta_); 
  leadLepton_phi_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_leadLepton_phi_, branchName_num_, leadLepton_phi_); 
  subleadLepton_eta_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_subleadLepton_eta_, branchName_num_, subleadLepton_eta_); 
  subleadLepton_phi_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_subleadLepton_phi_, branchName_num_, subleadLepton_phi_); 
  thirdLepton_eta_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_thirdLepton_eta_, branchName_num_, thirdLepton_eta_); 
  thirdLepton_phi_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_thirdLepton_phi_, branchName_num_, thirdLepton_phi_); 
  hadTau_eta_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_hadTau_eta_, branchName_num_, hadTau_eta_); 
  hadTau_phi_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_hadTau_phi_, branchName_num_, hadTau_phi_); 
  weight_ttH_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_weight_ttH_, branchName_num_, weight_ttH_); 
  weight_ttZ_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_weight_ttZ_, branchName_num_, weight_ttZ_); 
  weight_ttH_hww_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_weight_ttH_hww_, branchName_num_, weight_ttH_hww_); 
  LR_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_LR_, branchName_num_, LR_); 
  cpuTime_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_cpuTime_, branchName_num_, cpuTime_); 
  realTime_ = new Float_t[max_nMEMOutputs_];
  setBranchVF(tree, branchName_realTime_, branchName_num_, realTime_); 
  isValid_ = new Int_t[max_nMEMOutputs_];
  setBranchVI(tree, branchName_isValid_, branchName_num_, isValid_); 
  errorFlag_ = new Int_t[max_nMEMOutputs_];
  setBranchVI(tree, branchName_errorFlag_, branchName_num_, errorFlag_); 
}

void MEMOutputWriter_3l_1tau::write(const std::vector<MEMOutput_3l_1tau>& memOutputs)
{
  nMEMOutputs_ = memOutputs.size();
  if ( nMEMOutputs_ > max_nMEMOutputs_ ) {
    std::cout << "Warning: Number of MEMOutputs computed = " << nMEMOutputs_ << ", exceeds max_nMEMOutputs = " << max_nMEMOutputs_ << " that can be stored in Ntuple"
	      << " --> truncating the collection after " << max_nMEMOutputs_ << " objects !!\n";
    nMEMOutputs_ = max_nMEMOutputs_;
  }
  for ( Int_t idxMEMOutput = 0; idxMEMOutput < nMEMOutputs_; ++idxMEMOutput ) {
    const MEMOutput_3l_1tau& memOutput = memOutputs[idxMEMOutput];
    run_[idxMEMOutput] = memOutput.eventInfo_.run;
    lumi_[idxMEMOutput] = memOutput.eventInfo_.lumi;
    evt_[idxMEMOutput] = memOutput.eventInfo_.event;
    leadLepton_eta_[idxMEMOutput] = memOutput.leadLepton_eta_;
    leadLepton_phi_[idxMEMOutput] = memOutput.leadLepton_phi_;
    subleadLepton_eta_[idxMEMOutput] = memOutput.subleadLepton_eta_;
    subleadLepton_phi_[idxMEMOutput] = memOutput.subleadLepton_phi_;
    thirdLepton_eta_[idxMEMOutput] = memOutput.thirdLepton_eta_;
    thirdLepton_phi_[idxMEMOutput] = memOutput.thirdLepton_phi_;
    hadTau_eta_[idxMEMOutput] = memOutput.hadTau_eta_;
    hadTau_phi_[idxMEMOutput] = memOutput.hadTau_phi_;
    weight_ttH_[idxMEMOutput] = memOutput.weight_ttH();
    weight_ttZ_[idxMEMOutput] = memOutput.weight_ttZ();
    weight_ttH_hww_[idxMEMOutput] = memOutput.weight_ttH_hww();
    LR_[idxMEMOutput] = memOutput.LR();
    cpuTime_[idxMEMOutput] = memOutput.cpuTime();
    realTime_[idxMEMOutput] = memOutput.realTime();
    isValid_[idxMEMOutput] = memOutput.isValid();
    errorFlag_[idxMEMOutput] = memOutput.errorFlag();
  }
}
