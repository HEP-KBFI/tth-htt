#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_2lss_1tau.h" // MEMOutputReader_2lss_1tau

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

#include <cassert> // assert()

std::map<std::string, int> MEMOutputReader_2lss_1tau::numInstances_;
std::map<std::string, MEMOutputReader_2lss_1tau *> MEMOutputReader_2lss_1tau::instances_;

MEMOutputReader_2lss_1tau::MEMOutputReader_2lss_1tau(const std::string & branchName_num,
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
  , hadTau_eta_(nullptr)
  , hadTau_phi_(nullptr)
  , type_(nullptr)
  , weight_ttH_(nullptr)
  , weight_ttH_error_(nullptr)
  , weight_ttZ_(nullptr)
  , weight_ttZ_error_(nullptr)
  , weight_ttZ_Zll_(nullptr)
  , weight_ttZ_Zll_error_(nullptr)
  , weight_tt_(nullptr)
  , weight_tt_error_(nullptr)
  , LR_(nullptr)
  , LR_error_(nullptr)
  , LR_up_(nullptr)
  , LR_down_(nullptr)
  , cpuTime_(nullptr)
  , realTime_(nullptr)
  , isValid_(nullptr)
  , errorFlag_(nullptr)
{
  setBranchNames();
}

MEMOutputReader_2lss_1tau::~MEMOutputReader_2lss_1tau()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    MEMOutputReader_2lss_1tau* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance -> run_;
    delete[] gInstance -> lumi_;
    delete[] gInstance -> evt_;
    delete[] gInstance -> leadLepton_eta_;
    delete[] gInstance -> leadLepton_phi_;
    delete[] gInstance -> subleadLepton_eta_;
    delete[] gInstance -> subleadLepton_phi_;
    delete[] gInstance -> hadTau_eta_;
    delete[] gInstance -> hadTau_phi_;
    delete[] gInstance -> type_;
    delete[] gInstance -> weight_ttH_;
    delete[] gInstance -> weight_ttH_error_;
    delete[] gInstance -> weight_ttZ_;
    delete[] gInstance -> weight_ttZ_error_;
    delete[] gInstance -> weight_ttZ_Zll_;
    delete[] gInstance -> weight_ttZ_Zll_error_;
    delete[] gInstance -> weight_tt_;
    delete[] gInstance -> weight_tt_error_;
    delete[] gInstance -> LR_;
    delete[] gInstance -> LR_error_;
    delete[] gInstance -> LR_up_;
    delete[] gInstance -> LR_down_;
    delete[] gInstance -> cpuTime_;
    delete[] gInstance -> realTime_;
    delete[] gInstance -> isValid_;
    delete[] gInstance -> errorFlag_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
MEMOutputReader_2lss_1tau::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_run_                  = Form("%s_%s", branchName_obj_.data(), "run");
    branchName_lumi_                 = Form("%s_%s", branchName_obj_.data(), "lumi");
    branchName_evt_                  = Form("%s_%s", branchName_obj_.data(), "evt");
    branchName_leadLepton_eta_       = Form("%s_%s", branchName_obj_.data(), "leadLepton_eta");
    branchName_leadLepton_phi_       = Form("%s_%s", branchName_obj_.data(), "leadLepton_phi");
    branchName_subleadLepton_eta_    = Form("%s_%s", branchName_obj_.data(), "subleadLepton_eta");
    branchName_subleadLepton_phi_    = Form("%s_%s", branchName_obj_.data(), "subleadLepton_phi");
    branchName_hadTau_eta_           = Form("%s_%s", branchName_obj_.data(), "hadTau_eta");
    branchName_hadTau_phi_           = Form("%s_%s", branchName_obj_.data(), "hadTau_phi");
    branchName_type_                 = Form("%s_%s", branchName_obj_.data(), "type");
    branchName_weight_ttH_           = Form("%s_%s", branchName_obj_.data(), "weight_ttH");
    branchName_weight_ttH_error_     = Form("%s_%s", branchName_obj_.data(), "weight_ttH_error");
    branchName_weight_ttZ_           = Form("%s_%s", branchName_obj_.data(), "weight_ttZ");
    branchName_weight_ttZ_error_     = Form("%s_%s", branchName_obj_.data(), "weight_ttZ_error");
    branchName_weight_ttZ_Zll_       = Form("%s_%s", branchName_obj_.data(), "weight_ttZ_Zll");
    branchName_weight_ttZ_Zll_error_ = Form("%s_%s", branchName_obj_.data(), "weight_ttZ_Zll_error");
    branchName_weight_tt_            = Form("%s_%s", branchName_obj_.data(), "weight_tt");
    branchName_weight_tt_error_      = Form("%s_%s", branchName_obj_.data(), "weight_tt_error");
    branchName_LR_                   = Form("%s_%s", branchName_obj_.data(), "LR");
    branchName_LR_error_             = Form("%s_%s", branchName_obj_.data(), "LR_error");
    branchName_LR_up_                = Form("%s_%s", branchName_obj_.data(), "LR_up");
    branchName_LR_down_              = Form("%s_%s", branchName_obj_.data(), "LR_down");
    branchName_cpuTime_              = Form("%s_%s", branchName_obj_.data(), "cpuTime");
    branchName_realTime_             = Form("%s_%s", branchName_obj_.data(), "realTime");
    branchName_isValid_              = Form("%s_%s", branchName_obj_.data(), "isValid");
    branchName_errorFlag_            = Form("%s_%s", branchName_obj_.data(), "errorFlag");
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
           " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_] -> branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_] -> branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void
MEMOutputReader_2lss_1tau::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nMEMOutputs_);
    bai.setBranchAddress(nMEMOutputs_, branchName_num_);
    bai.setBranchAddress(run_, branchName_run_);
    bai.setBranchAddress(lumi_, branchName_lumi_);
    bai.setBranchAddress(evt_, branchName_evt_);
    bai.setBranchAddress(leadLepton_eta_, branchName_leadLepton_eta_);
    bai.setBranchAddress(leadLepton_phi_, branchName_leadLepton_phi_);
    bai.setBranchAddress(subleadLepton_eta_, branchName_subleadLepton_eta_);
    bai.setBranchAddress(subleadLepton_phi_, branchName_subleadLepton_phi_);
    bai.setBranchAddress(hadTau_eta_, branchName_hadTau_eta_);
    bai.setBranchAddress(hadTau_phi_, branchName_hadTau_phi_);
    bai.setBranchAddress(type_, branchName_type_);
    bai.setBranchAddress(weight_ttH_, branchName_weight_ttH_);
    bai.setBranchAddress(weight_ttH_error_, branchName_weight_ttH_error_);
    bai.setBranchAddress(weight_ttZ_, branchName_weight_ttZ_);
    bai.setBranchAddress(weight_ttZ_error_, branchName_weight_ttZ_error_);
    bai.setBranchAddress(weight_ttZ_Zll_, branchName_weight_ttZ_Zll_);
    bai.setBranchAddress(weight_ttZ_Zll_error_, branchName_weight_ttZ_Zll_error_);
    bai.setBranchAddress(weight_tt_, branchName_weight_tt_);
    bai.setBranchAddress(weight_tt_error_, branchName_weight_tt_error_);
    bai.setBranchAddress(LR_, branchName_LR_);
    bai.setBranchAddress(LR_error_, branchName_LR_error_);
    bai.setBranchAddress(LR_up_, branchName_LR_up_);
    bai.setBranchAddress(LR_down_, branchName_LR_down_);
    bai.setBranchAddress(cpuTime_, branchName_cpuTime_);
    bai.setBranchAddress(realTime_, branchName_realTime_);
    bai.setBranchAddress(errorFlag_, branchName_errorFlag_);
    bai.setBranchAddress(isValid_, branchName_isValid_);
  }
}

std::vector<MEMOutput_2lss_1tau>
MEMOutputReader_2lss_1tau::read() const
{
  MEMOutputReader_2lss_1tau* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  Int_t nMEMOutputs = gInstance -> nMEMOutputs_;
  if(nMEMOutputs > max_nMEMOutputs_)
  {
    throw cmsException(this)
      << "Number of MEMOutputs stored in Ntuple = " << nMEMOutputs << ", "
         "exceeds max_nMEMOutputs = " << max_nMEMOutputs_ << " !!\n";
  }
  std::vector<MEMOutput_2lss_1tau> memOutputs;
  if(nMEMOutputs > 0)
  {
    memOutputs.reserve(nMEMOutputs);
    for(Int_t idxMEMOutput = 0; idxMEMOutput < nMEMOutputs; ++idxMEMOutput)
    {
      MEMOutput_2lss_1tau memOutput;
      memOutput.eventInfo_.run        = gInstance -> run_[idxMEMOutput];
      memOutput.eventInfo_.lumi       = gInstance -> lumi_[idxMEMOutput];
      memOutput.eventInfo_.event      = gInstance -> evt_[idxMEMOutput];
      memOutput.leadLepton_eta_       = gInstance -> leadLepton_eta_[idxMEMOutput];
      memOutput.leadLepton_phi_       = gInstance -> leadLepton_phi_[idxMEMOutput];
      memOutput.subleadLepton_eta_    = gInstance -> subleadLepton_eta_[idxMEMOutput];
      memOutput.subleadLepton_phi_    = gInstance -> subleadLepton_phi_[idxMEMOutput];
      memOutput.hadTau_eta_           = gInstance -> hadTau_eta_[idxMEMOutput];
      memOutput.hadTau_phi_           = gInstance -> hadTau_phi_[idxMEMOutput];
      memOutput.type_                 = gInstance -> type_[idxMEMOutput];
      memOutput.weight_ttH_           = gInstance -> weight_ttH_[idxMEMOutput];
      memOutput.weight_ttH_error_     = gInstance -> weight_ttH_error_[idxMEMOutput];
      memOutput.weight_ttZ_           = gInstance -> weight_ttZ_[idxMEMOutput];
      memOutput.weight_ttZ_error_     = gInstance -> weight_ttZ_error_[idxMEMOutput];
      memOutput.weight_ttZ_Zll_       = gInstance -> weight_ttZ_Zll_[idxMEMOutput];
      memOutput.weight_ttZ_Zll_error_ = gInstance -> weight_ttZ_Zll_error_[idxMEMOutput];
      memOutput.weight_tt_            = gInstance -> weight_tt_[idxMEMOutput];
      memOutput.weight_tt_error_      = gInstance -> weight_tt_error_[idxMEMOutput];
      memOutput.LR_                   = gInstance -> LR_[idxMEMOutput];
      memOutput.LR_error_             = gInstance -> LR_error_[idxMEMOutput];
      memOutput.LR_up_                = gInstance -> LR_up_[idxMEMOutput];
      memOutput.LR_down_              = gInstance -> LR_down_[idxMEMOutput];
      memOutput.cpuTime_              = gInstance -> cpuTime_[idxMEMOutput];
      memOutput.realTime_             = gInstance -> realTime_[idxMEMOutput];
      memOutput.isValid_              = gInstance -> isValid_[idxMEMOutput];
      memOutput.errorFlag_            = gInstance -> errorFlag_[idxMEMOutput];
      memOutputs.push_back(memOutput);
    }
  }
  return memOutputs;
}
