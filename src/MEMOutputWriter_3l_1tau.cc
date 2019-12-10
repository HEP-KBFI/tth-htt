#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_3l_1tau.h" // MEMOutputWriter_3l_1tau

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

MEMOutputWriter_3l_1tau::MEMOutputWriter_3l_1tau(const std::string & branchName_num,
                                                 const std::string & branchName_obj)
  : max_nMEMOutputs_(100)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , run_(nullptr)
  , lumi_(nullptr)
  , evt_(nullptr)
  , leadLepton_eta_(nullptr)
  , leadLepton_phi_(nullptr)
  , subleadLepton_eta_(nullptr)
  , subleadLepton_phi_(nullptr)
  , thirdLepton_eta_(nullptr)
  , thirdLepton_phi_(nullptr)
  , hadTau_eta_(nullptr)
  , hadTau_phi_(nullptr)
  , weight_ttH_(nullptr)
  , weight_ttH_error_(nullptr)
  , weight_ttZ_(nullptr)
  , weight_ttZ_error_(nullptr)
  , weight_ttH_hww_(nullptr)
  , weight_ttH_hww_error_(nullptr)
  , LR_(nullptr)
  , LR_up_(nullptr)
  , LR_down_(nullptr)
  , cpuTime_(nullptr)
  , realTime_(nullptr)
  , isValid_(nullptr)
  , errorFlag_(nullptr)
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
  delete[] weight_ttH_error_;
  delete[] weight_ttZ_;
  delete[] weight_ttZ_error_;
  delete[] weight_ttH_hww_;
  delete[] weight_ttH_hww_error_;
  delete[] LR_;
  delete[] LR_up_;
  delete[] LR_down_;
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
  branchName_weight_ttH_error_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH_error");
  branchName_weight_ttZ_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ");
  branchName_weight_ttZ_error_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ_error");
  branchName_weight_ttH_hww_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH_hww");
  branchName_weight_ttH_hww_error_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH_hww_error");
  branchName_LR_ = Form("%s_%s", branchName_obj_.data(), "LR");
  branchName_LR_up_ = Form("%s_%s", branchName_obj_.data(), "LR_up");
  branchName_LR_down_ = Form("%s_%s", branchName_obj_.data(), "LR_down");
  branchName_cpuTime_ = Form("%s_%s", branchName_obj_.data(), "cpuTime");
  branchName_realTime_ = Form("%s_%s", branchName_obj_.data(), "realTime");
  branchName_isValid_ = Form("%s_%s", branchName_obj_.data(), "isValid");
  branchName_errorFlag_ = Form("%s_%s", branchName_obj_.data(), "errorFlag");
}

void MEMOutputWriter_3l_1tau::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree, max_nMEMOutputs_, branchName_num_);
  bai.setBranch(nMEMOutputs_, branchName_num_);
  bai.setBranch(run_, branchName_run_);
  bai.setBranch(lumi_, branchName_lumi_);
  bai.setBranch(evt_, branchName_evt_);
  bai.setBranch(leadLepton_eta_, branchName_leadLepton_eta_);
  bai.setBranch(leadLepton_phi_, branchName_leadLepton_phi_);
  bai.setBranch(subleadLepton_eta_, branchName_subleadLepton_eta_);
  bai.setBranch(subleadLepton_phi_, branchName_subleadLepton_phi_);
  bai.setBranch(thirdLepton_eta_, branchName_thirdLepton_eta_);
  bai.setBranch(thirdLepton_phi_, branchName_thirdLepton_phi_);
  bai.setBranch(hadTau_eta_, branchName_hadTau_eta_);
  bai.setBranch(hadTau_phi_, branchName_hadTau_phi_);
  bai.setBranch(weight_ttH_, branchName_weight_ttH_);
  bai.setBranch(weight_ttH_error_, branchName_weight_ttH_error_);
  bai.setBranch(weight_ttZ_, branchName_weight_ttZ_);
  bai.setBranch(weight_ttZ_error_, branchName_weight_ttZ_error_);
  bai.setBranch(weight_ttH_hww_, branchName_weight_ttH_hww_);
  bai.setBranch(weight_ttH_hww_error_, branchName_weight_ttH_hww_error_);
  bai.setBranch(LR_, branchName_LR_);
  bai.setBranch(LR_up_, branchName_LR_up_);
  bai.setBranch(LR_down_, branchName_LR_down_);
  bai.setBranch(cpuTime_, branchName_cpuTime_);
  bai.setBranch(realTime_, branchName_realTime_);
  bai.setBranch(isValid_, branchName_isValid_);
  bai.setBranch(errorFlag_, branchName_errorFlag_);
}

void MEMOutputWriter_3l_1tau::write(const std::vector<MEMOutput_3l_1tau> & memOutputs)
{
  nMEMOutputs_ = memOutputs.size();
  if ( nMEMOutputs_ > max_nMEMOutputs_ ) {
    std::cout << "Warning: Number of MEMOutputs computed = " << nMEMOutputs_ << ", exceeds max_nMEMOutputs = "
              << max_nMEMOutputs_ << " that can be stored in Ntuple --> truncating the collection after "
              << max_nMEMOutputs_ << " objects !!\n";
    nMEMOutputs_ = max_nMEMOutputs_;
  }

  for(Int_t idxMEMOutput = 0; idxMEMOutput < nMEMOutputs_; ++idxMEMOutput)
  {
    const MEMOutput_3l_1tau & memOutput = memOutputs[idxMEMOutput];
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
    weight_ttH_error_[idxMEMOutput] = memOutput.weight_ttH_error();
    weight_ttZ_[idxMEMOutput] = memOutput.weight_ttZ();
    weight_ttZ_error_[idxMEMOutput] = memOutput.weight_ttZ_error();
    weight_ttH_hww_[idxMEMOutput] = memOutput.weight_ttH_hww();
    weight_ttH_hww_error_[idxMEMOutput] = memOutput.weight_ttH_hww_error();
    LR_[idxMEMOutput] = memOutput.LR();
    LR_up_[idxMEMOutput] = memOutput.LR_up();
    LR_down_[idxMEMOutput] = memOutput.LR_down();
    cpuTime_[idxMEMOutput] = memOutput.cpuTime();
    realTime_[idxMEMOutput] = memOutput.realTime();
    isValid_[idxMEMOutput] = memOutput.isValid();
    errorFlag_[idxMEMOutput] = memOutput.errorFlag();
  }
}
