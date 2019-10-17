#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputWriter_3l.h" // MEMOutputWriter_3l

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

MEMOutputWriter_3l::MEMOutputWriter_3l(const std::string & branchName_num,
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
  , weight_ttH_(nullptr)
  , kinfitscore_ttH_(nullptr)
  , weight_tHq_(nullptr)
  , kinfitscore_tHq_(nullptr)
  , weight_ttW_(nullptr)
  , kinfitscore_ttW_(nullptr)
  , weight_ttZ_(nullptr)
  , kinfitscore_ttZ_(nullptr)
  , weight_tt_(nullptr)
  , kinfitscore_tt_(nullptr)
  , LR_(nullptr)
  , cpuTime_(nullptr)
  , realTime_(nullptr)
  , isValid_(nullptr)
  , errorFlag_(nullptr)
{
  setBranchNames();
}

MEMOutputWriter_3l::~MEMOutputWriter_3l()
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
  delete[] weight_ttH_;
  delete[] kinfitscore_ttH_;
  delete[] weight_tHq_;
  delete[] kinfitscore_tHq_;
  delete[] weight_ttW_;
  delete[] kinfitscore_ttW_;
  delete[] weight_ttZ_;
  delete[] kinfitscore_ttZ_;
  delete[] weight_tt_;
  delete[] kinfitscore_tt_;
  delete[] LR_;
  delete[] cpuTime_;
  delete[] realTime_;
  delete[] isValid_;
  delete[] errorFlag_;
}

void MEMOutputWriter_3l::setBranchNames()
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
  branchName_weight_ttH_ = Form("%s_%s", branchName_obj_.data(), "weight_ttH");
  branchName_kinfitscore_ttH_ = Form("%s_%s", branchName_obj_.data(), "kinfitscore_ttH");
  branchName_weight_tHq_ = Form("%s_%s", branchName_obj_.data(), "weight_tHq");
  branchName_kinfitscore_tHq_ = Form("%s_%s", branchName_obj_.data(), "kinfitscore_tHq");
  branchName_weight_ttW_ = Form("%s_%s", branchName_obj_.data(), "weight_ttW");
  branchName_kinfitscore_ttW_ = Form("%s_%s", branchName_obj_.data(), "kinfitscore_ttW");
  branchName_weight_ttZ_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ");
  branchName_kinfitscore_ttZ_ = Form("%s_%s", branchName_obj_.data(), "kinfitscore_ttZ");
  branchName_weight_tt_ = Form("%s_%s", branchName_obj_.data(), "weight_tt");
  branchName_kinfitscore_tt_ = Form("%s_%s", branchName_obj_.data(), "kinfitscore_tt");
  branchName_LR_ = Form("%s_%s", branchName_obj_.data(), "LR");
  branchName_cpuTime_ = Form("%s_%s", branchName_obj_.data(), "cpuTime");
  branchName_realTime_ = Form("%s_%s", branchName_obj_.data(), "realTime");
  branchName_isValid_ = Form("%s_%s", branchName_obj_.data(), "isValid");
  branchName_errorFlag_ = Form("%s_%s", branchName_obj_.data(), "errorFlag");
}

void
MEMOutputWriter_3l::setBranches(TTree * tree)
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
  bai.setBranch(weight_ttH_, branchName_weight_ttH_);
  bai.setBranch(kinfitscore_ttH_, branchName_kinfitscore_ttH_);
  bai.setBranch(weight_tHq_, branchName_weight_tHq_);
  bai.setBranch(kinfitscore_tHq_, branchName_kinfitscore_tHq_);
  bai.setBranch(weight_ttW_, branchName_weight_ttW_);
  bai.setBranch(kinfitscore_ttW_, branchName_kinfitscore_ttW_);
  bai.setBranch(weight_ttZ_, branchName_weight_ttZ_);
  bai.setBranch(kinfitscore_ttZ_, branchName_kinfitscore_ttZ_);
  bai.setBranch(weight_tt_, branchName_weight_tt_);
  bai.setBranch(kinfitscore_tt_, branchName_kinfitscore_tt_);
  bai.setBranch(LR_, branchName_LR_);
  bai.setBranch(cpuTime_, branchName_cpuTime_);
  bai.setBranch(realTime_, branchName_realTime_);
  bai.setBranch(isValid_, branchName_isValid_);
  bai.setBranch(errorFlag_, branchName_errorFlag_);
}

void MEMOutputWriter_3l::write(const std::vector<MEMOutput_3l> & memOutputs)
{
  nMEMOutputs_ = memOutputs.size();
  if(nMEMOutputs_ > max_nMEMOutputs_)
  {
    std::cout << "Warning: Number of MEMOutputs computed = " << nMEMOutputs_ << ", exceeds max_nMEMOutputs = "
              << max_nMEMOutputs_ << " that can be stored in Ntuple --> truncating the collection after "
              << max_nMEMOutputs_ << " objects !!\n";
    nMEMOutputs_ = max_nMEMOutputs_;
  }

  for(Int_t idxMEMOutput = 0; idxMEMOutput < nMEMOutputs_; ++idxMEMOutput)
  {
    const MEMOutput_3l & memOutput = memOutputs[idxMEMOutput];
    run_[idxMEMOutput] = memOutput.eventInfo_.run;
    lumi_[idxMEMOutput] = memOutput.eventInfo_.lumi;
    evt_[idxMEMOutput] = memOutput.eventInfo_.event;
    leadLepton_eta_[idxMEMOutput] = memOutput.leadLepton_eta_;
    leadLepton_phi_[idxMEMOutput] = memOutput.leadLepton_phi_;
    subleadLepton_eta_[idxMEMOutput] = memOutput.subleadLepton_eta_;
    subleadLepton_phi_[idxMEMOutput] = memOutput.subleadLepton_phi_;
    thirdLepton_eta_[idxMEMOutput] = memOutput.thirdLepton_eta_;
    thirdLepton_phi_[idxMEMOutput] = memOutput.thirdLepton_phi_;
    weight_ttH_[idxMEMOutput] = memOutput.weight_ttH();
    kinfitscore_ttH_[idxMEMOutput] = memOutput.kinfitscore_ttH();
    weight_tHq_[idxMEMOutput] = memOutput.weight_tHq();
    kinfitscore_tHq_[idxMEMOutput] = memOutput.kinfitscore_tHq();
    weight_ttW_[idxMEMOutput] = memOutput.weight_ttW();
    kinfitscore_ttW_[idxMEMOutput] = memOutput.kinfitscore_ttW();
    weight_ttZ_[idxMEMOutput] = memOutput.weight_ttZ();
    kinfitscore_ttZ_[idxMEMOutput] = memOutput.kinfitscore_ttZ();
    weight_tt_[idxMEMOutput] = memOutput.weight_tt();
    kinfitscore_tt_[idxMEMOutput] = memOutput.kinfitscore_tt();
    LR_[idxMEMOutput] = memOutput.LR();
    cpuTime_[idxMEMOutput] = memOutput.cpuTime();
    realTime_[idxMEMOutput] = memOutput.realTime();
    isValid_[idxMEMOutput] = memOutput.isValid();
    errorFlag_[idxMEMOutput] = memOutput.errorFlag();
  }
}
