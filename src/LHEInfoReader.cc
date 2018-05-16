#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kLHE_scale_*

#include <cassert> // assert()

std::map<std::string, int> LHEInfoReader::numInstances_;
std::map<std::string, LHEInfoReader*> LHEInfoReader::instances_;

LHEInfoReader::LHEInfoReader(bool has_LHE_weights)
  : max_scale_nWeights_(9)
  , branchName_scale_nWeights_("nLHEScaleWeight")
  , branchName_scale_weights_("LHEScaleWeight")
  , max_pdf_nWeights_(103)
  , branchName_pdf_nWeights_("nLHEPdfWeight")
  , branchName_pdf_weights_("LHEPdfWeight")
  , scale_nWeights_(0)
  , scale_weights_(nullptr)
  , pdf_nWeights_(0)
  , pdf_weights_(nullptr)
  , weight_scale_xUp_(1.)
  , weight_scale_xDown_(1.)
  , weight_scale_yUp_(1.)
  , weight_scale_yDown_(1.)
  , has_LHE_weights_(has_LHE_weights)
{
  setBranchNames();
}

LHEInfoReader::~LHEInfoReader()
{
  --numInstances_[branchName_scale_weights_];
  assert(numInstances_[branchName_scale_weights_] >= 0);

  if(numInstances_[branchName_scale_weights_] == 0)
  {
    LHEInfoReader * const gInstance = instances_[branchName_scale_weights_];
    assert(gInstance);
    delete[] gInstance->scale_weights_;
    delete[] gInstance->pdf_weights_;
    instances_[branchName_scale_weights_] = nullptr;
  }
}

void
LHEInfoReader::setBranchNames()
{
  if(numInstances_[branchName_scale_weights_] == 0)
  {
    instances_[branchName_scale_weights_] = this;
  }
  else if(has_LHE_weights_)
  {
    const LHEInfoReader * const gInstance = instances_[branchName_scale_weights_];
    if(branchName_scale_nWeights_ != gInstance->branchName_scale_nWeights_ ||
       branchName_pdf_nWeights_   != gInstance->branchName_pdf_nWeights_   ||
       branchName_pdf_weights_    != gInstance->branchName_pdf_weights_     )
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_scale_weights' and 'branchName_pdf_weights'"
           " must be unique: present association 'branchName_scale_weights' = " << branchName_scale_weights_
        << " with 'branchName_pdf_weights' = " << branchName_pdf_weights_
        << " does not match previous association 'branchName_scale_weights' = " << gInstance->branchName_scale_weights_
        << " with 'branchName_pdf_weights' = " << gInstance->branchName_pdf_weights_ << " !!\n";
    }
  }
  ++numInstances_[branchName_scale_weights_];
}

void
LHEInfoReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_scale_weights_] == this && has_LHE_weights_)
  {
    BranchAddressInitializer bai(tree);
    bai.setBranchAddress(scale_nWeights_, branchName_scale_nWeights_);
    bai.setBranchAddress(pdf_nWeights_, branchName_pdf_nWeights_);
    bai.setLenVar(max_scale_nWeights_).setBranchAddress(scale_weights_, branchName_scale_weights_);
    bai.setLenVar(max_pdf_nWeights_).setBranchAddress(pdf_weights_, branchName_pdf_weights_);
  }
}

void
LHEInfoReader::read() const
{
  const LHEInfoReader * const gInstance = instances_[branchName_scale_weights_];
  assert(gInstance);
  if(! has_LHE_weights_)
  {
    return;
  }
  if(gInstance->scale_nWeights_ > max_scale_nWeights_)
  {
    throw cmsException(this)
      << "Number of Scale weights stored in Ntuple = " << gInstance->scale_nWeights_
      << ", exceeds max_scale_nWeights_ = " << max_scale_nWeights_ << " !!\n";
  }

  // Karl: nomenclature:
  //    [0] is muR=0.5 muF=0.5 hdamp=mt=272.7225
  //    [1] is muR=0.5 muF=1   hdamp=mt=272.7225
  //    [2] is muR=0.5 muF=2   hdamp=mt=272.7225
  //    [3] is muR=1   muF=0.5 hdamp=mt=272.7225
  //    [4] is muR=1   muF=1   hdamp=mt=272.7225
  //    [5] is muR=1   muF=2   hdamp=mt=272.7225
  //    [6] is muR=2   muF=0.5 hdamp=mt=272.7225
  //    [7] is muR=2   muF=1   hdamp=mt=272.7225
  //    [8] is muR=2   muF=2   hdamp=mt=272.7225
  weight_scale_yDown_ = gInstance->scale_weights_[1]; // muR=0.5 muF=1
  weight_scale_xDown_ = gInstance->scale_weights_[3]; // muR=1   muF=0.5
  weight_scale_xUp_   = gInstance->scale_weights_[5]; // muR=1   muF=2
  weight_scale_yUp_   = gInstance->scale_weights_[7]; // muR=2   muF=1

  if(gInstance->pdf_nWeights_ > max_pdf_nWeights_)
  {
    throw cmsException(this)
      << "Number of PDF weights stored in Ntuple = " << gInstance->pdf_nWeights_
      << ", exceeds max_pdf_nWeights_ = " << max_pdf_nWeights_ << " !!\n";
  }
}

double
LHEInfoReader::getWeight_scale_xUp() const
{ 
  return weight_scale_xUp_;
}

double
LHEInfoReader::getWeight_scale_xDown() const
{ 
  return weight_scale_xDown_;
}

double
LHEInfoReader::getWeight_scale_yUp() const
{
  return weight_scale_yUp_;
}

double
LHEInfoReader::getWeight_scale_yDown() const
{ 
  return weight_scale_yDown_;
}

double
LHEInfoReader::getWeight_scale(int central_or_shift) const
{
  switch(central_or_shift)
  {
    case kLHE_scale_central: return 1.;
    case kLHE_scale_xDown:   return getWeight_scale_xDown();
    case kLHE_scale_xUp:     return getWeight_scale_xUp();
    case kLHE_scale_yDown:   return getWeight_scale_yDown();
    case kLHE_scale_yUp:     return getWeight_scale_yUp();
    default: throw cmsException(this, __func__, __LINE__)
               << "Invalid LHE scale systematics option: " << central_or_shift;
  }
}

int
LHEInfoReader::getNumWeights_pdf() const
{
  return has_LHE_weights_ ? pdf_nWeights_ : 1;
}

double
LHEInfoReader::getWeight_pdf(unsigned int idx) const
{
  if(! has_LHE_weights_)
  {
    return 1.;
  }
  if(idx >= pdf_nWeights_)
  {
    throw cmsException(this)
      << "Given index = " << idx << ", exceeds number of PDF weights stored in Ntuple = "
      << pdf_nWeights_ << " !!\n";
  }
  return pdf_weights_[idx];
}
