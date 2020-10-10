#include "tthAnalysis/HiggsToTauTau/interface/TrigObjReader.h" // TrigObjReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> TrigObjReader::numInstances_;
std::map<std::string, TrigObjReader *> TrigObjReader::instances_;

TrigObjReader::TrigObjReader()
  : TrigObjReader("TrigObj")
{}

TrigObjReader::TrigObjReader(const std::string & branchName_obj)
  : max_nTrigObjs_(1024)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , trigObj_pt_(nullptr)    
  , trigObj_eta_(nullptr)  
  , trigObj_phi_(nullptr)
  , trigObj_filterBits_(nullptr)
  , trigObj_id_(nullptr)
  , trigObj_l1pt_(nullptr)
  , trigObj_l1pt_2_(nullptr)
  , trigObj_l1iso_(nullptr)
{
  setBranchNames();
}

TrigObjReader::~TrigObjReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    TrigObjReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->trigObj_pt_;
    delete[] gInstance->trigObj_eta_;
    delete[] gInstance->trigObj_phi_;
    delete[] gInstance->trigObj_filterBits_;
    delete[] gInstance->trigObj_id_;
    delete[] gInstance->trigObj_l1pt_;
    delete[] gInstance->trigObj_l1pt_2_;
    delete[] gInstance->trigObj_l1iso_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
TrigObjReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");  
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");  
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits"); 
    branchName_id_ = Form("%s_%s", branchName_obj_.data(), "id"); 
    branchName_l1pt_ = Form("%s_%s", branchName_obj_.data(), "l1pt"); 
    branchName_l1pt_2_ = Form("%s_%s", branchName_obj_.data(), "l1pt_2");  
    branchName_l1iso_ = Form("%s_%s", branchName_obj_.data(), "l1iso");   
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
        << " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

std::vector<std::string>
TrigObjReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nTrigObjs_);
    bai.setBranchAddress(nTrigObjs_, branchName_num_);
    bai.setBranchAddress(trigObj_pt_, branchName_pt_);
    bai.setBranchAddress(trigObj_eta_, branchName_eta_);
    bai.setBranchAddress(trigObj_phi_, branchName_phi_);
    bai.setBranchAddress(trigObj_filterBits_, branchName_filterBits_);
    bai.setBranchAddress(trigObj_id_, branchName_id_);
    bai.setBranchAddress(trigObj_l1pt_, branchName_l1pt_);
    bai.setBranchAddress(trigObj_l1pt_2_, branchName_l1pt_2_);
    bai.setBranchAddress(trigObj_l1iso_, branchName_l1iso_);
    return bai.getBoundBranchNames();
  }
  return {};
}

std::vector<TrigObj>
TrigObjReader::read() const
{
  const TrigObjReader * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  std::vector<TrigObj> trigObjs;
  const UInt_t nTrigObjs = gInstance->nTrigObjs_;
  if(nTrigObjs > max_nTrigObjs_)
  {
    throw cmsException(this)
      << "Number of trigger objects stored in Ntuple = " << nTrigObjs << ", "
         "exceeds max_nTrigObjs = " << max_nTrigObjs_ << " !!\n";
  }

  if(nTrigObjs > 0)
  {
    trigObjs.reserve(nTrigObjs);
    for(UInt_t idxTrigObj = 0; idxTrigObj < nTrigObjs; ++idxTrigObj)
    {
      trigObjs.push_back({
        gInstance->trigObj_pt_[idxTrigObj],
        gInstance->trigObj_eta_[idxTrigObj],
        gInstance->trigObj_phi_[idxTrigObj],
        gInstance->trigObj_filterBits_[idxTrigObj],
        gInstance->trigObj_id_[idxTrigObj],
        gInstance->trigObj_l1pt_[idxTrigObj],
        gInstance->trigObj_l1pt_2_[idxTrigObj],
        gInstance->trigObj_l1iso_[idxTrigObj]
      });
    } // idxTrigObj
  } // nTrigObjs > 0
  return trigObjs;
}
