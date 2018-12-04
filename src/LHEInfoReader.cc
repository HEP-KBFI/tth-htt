#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kLHE_scale_*

#include <cassert> // assert()

std::map<std::string, int> LHEInfoReader::numInstances_;
std::map<std::string, LHEInfoReader*> LHEInfoReader::instances_;

LHEInfoReader::LHEInfoReader(bool has_LHE_weights)
  : max_scale_nWeights_(44)
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

  // Karl: the nomenclature depends on the MG version used
  // below MG ver 2.6:
  //    [0] is muR=0.5 muF=0.5
  //    [1] is muR=0.5 muF=1.0
  //    [2] is muR=0.5 muF=2.0
  //    [3] is muR=1.0 muF=0.5
  //    [4] is muR=1.0 muF=1.0
  //    [5] is muR=1.0 muF=2.0
  //    [6] is muR=2.0 muF=0.5
  //    [7] is muR=2.0 muF=1.0
  //    [8] is muR=2.0 muF=2.0
  if(gInstance->scale_nWeights_ == 9)
  {
    weight_scale_yDown_ = gInstance->scale_weights_[1]; // muR=0.5 muF=1.0
    weight_scale_xDown_ = gInstance->scale_weights_[3]; // muR=1.0 muF=0.5
    weight_scale_xUp_   = gInstance->scale_weights_[5]; // muR=1.0 muF=2.0
    weight_scale_yUp_   = gInstance->scale_weights_[7]; // muR=2.0 muF=1.0
  }
  // MG ver 2.6 and above:
  //    [0]  is muR=0.5 muF=0.5
  //    [1]  is muR=0.5 muF=0.5 dyn_scale_choice=sum pt
  //    [2]  is muR=0.5 muF=0.5 dyn_scale_choice=HT
  //    [3]  is muR=0.5 muF=0.5 dyn_scale_choice=HT/2
  //    [4]  is muR=0.5 muF=0.5 dyn_scale_choice=sqrts
  //    [5]  is muR=0.5 muF=1.0
  //    [6]  is muR=0.5 muF=1.0 dyn_scale_choice=sum pt
  //    [7]  is muR=0.5 muF=1.0 dyn_scale_choice=HT
  //    [8]  is muR=0.5 muF=1.0 dyn_scale_choice=HT/2
  //    [9]  is muR=0.5 muF=1.0 dyn_scale_choice=sqrts
  //    [10] is muR=0.5 muF=2.0
  //    [11] is muR=0.5 muF=2.0 dyn_scale_choice=sum pt
  //    [12] is muR=0.5 muF=2.0 dyn_scale_choice=HT
  //    [13] is muR=0.5 muF=2.0 dyn_scale_choice=HT/2
  //    [14] is muR=0.5 muF=2.0 dyn_scale_choice=sqrts
  //    [15] is muR=1.0 muF=0.5
  //    [16] is muR=1.0 muF=0.5 dyn_scale_choice=sum pt
  //    [17] is muR=1.0 muF=0.5 dyn_scale_choice=HT
  //    [18] is muR=1.0 muF=0.5 dyn_scale_choice=HT/2
  //    [19] is muR=1.0 muF=0.5 dyn_scale_choice=sqrts
  //    [20] is muR=1.0 muF=1.0 dyn_scale_choice=sum pt
  //    [21] is muR=1.0 muF=1.0 dyn_scale_choice=HT
  //    [22] is muR=1.0 muF=1.0 dyn_scale_choice=HT/2
  //    [23] is muR=1.0 muF=1.0 dyn_scale_choice=sqrts
  //    [24] is muR=1.0 muF=2.0
  //    [25] is muR=1.0 muF=2.0 dyn_scale_choice=sum pt
  //    [26] is muR=1.0 muF=2.0 dyn_scale_choice=HT
  //    [27] is muR=1.0 muF=2.0 dyn_scale_choice=HT/2
  //    [28] is muR=1.0 muF=2.0 dyn_scale_choice=sqrts
  //    [29] is muR=2.0 muF=0.5
  //    [30] is muR=2.0 muF=0.5 dyn_scale_choice=sum pt
  //    [31] is muR=2.0 muF=0.5 dyn_scale_choice=HT
  //    [32] is muR=2.0 muF=0.5 dyn_scale_choice=HT/2
  //    [33] is muR=2.0 muF=0.5 dyn_scale_choice=sqrts
  //    [34] is muR=2.0 muF=1.0
  //    [35] is muR=2.0 muF=1.0 dyn_scale_choice=sum pt
  //    [36] is muR=2.0 muF=1.0 dyn_scale_choice=HT
  //    [37] is muR=2.0 muF=1.0 dyn_scale_choice=HT/2
  //    [38] is muR=2.0 muF=1.0 dyn_scale_choice=sqrts
  //    [39] is muR=2.0 muF=2.0
  //    [40] is muR=2.0 muF=2.0 dyn_scale_choice=sum pt
  //    [41] is muR=2.0 muF=2.0 dyn_scale_choice=HT
  //    [42] is muR=2.0 muF=2.0 dyn_scale_choice=HT/2
  //    [43] is muR=2.0 muF=2.0 dyn_scale_choice=sqrts
  else if(gInstance->scale_nWeights_ == 44)
  {
    weight_scale_yDown_ = gInstance->scale_weights_[5];  // muR=0.5 muF=1.0
    weight_scale_xDown_ = gInstance->scale_weights_[15]; // muR=1.0 muF=0.5
    weight_scale_xUp_   = gInstance->scale_weights_[24]; // muR=1.0 muF=2.0
    weight_scale_yUp_   = gInstance->scale_weights_[34]; // muR=2.0 muF=1.0
  }
  else
  {
    throw cmsException(this)
      << "Unexpected number of LHE scale weights: " << gInstance->scale_nWeights_
    ;
  }

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
  return LHEInfoReader::clip(weight_scale_xUp_);
}

double
LHEInfoReader::getWeight_scale_xDown() const
{ 
  return LHEInfoReader::clip(weight_scale_xDown_);
}

double
LHEInfoReader::getWeight_scale_yUp() const
{
  return LHEInfoReader::clip(weight_scale_yUp_);
}

double
LHEInfoReader::getWeight_scale_yDown() const
{ 
  return LHEInfoReader::clip(weight_scale_yDown_);
}

double
LHEInfoReader::getWeight_scale(int central_or_shift) const
{
  switch(central_or_shift)
  {
    case kLHE_scale_central: return 1.;
    case kLHE_scale_xDown:   return LHEInfoReader::clip(getWeight_scale_xDown());
    case kLHE_scale_xUp:     return LHEInfoReader::clip(getWeight_scale_xUp());
    case kLHE_scale_yDown:   return LHEInfoReader::clip(getWeight_scale_yDown());
    case kLHE_scale_yUp:     return LHEInfoReader::clip(getWeight_scale_yUp());
    default: throw cmsException(this, __func__, __LINE__)
               << "Invalid LHE scale systematics option: " << central_or_shift;
  }
}

int
LHEInfoReader::getNumWeights_pdf() const
{
  // If the # of PDF error sets is
  // a) 33 -- PDF4LHC15_nnlo_30_pdfas (LHAID = 91400) (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/PDF4LHC15_nnlo_30_pdfas.tar.gz)
  //          mem=0 => alphas(MZ)=0.118 central value; mem=1-30 => PDF symmetric eigenvectors; mem=31 => alphas(MZ)=0.1165 central value; mem=32 => alphas(MZ)=0.1195
  // b) 103
  //    i) NNPDF31_nnlo_hessian_pdfas (LHAID = 306000) (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF31_nnlo_hessian_pdfas.tar.gz)
  //       mem=0 central value => Alphas(MZ)=0.118; mem=1-100 => PDF eig.; mem=101 => central value Alphas(MZ)=0.116; mem=102 => central value Alphas(MZ)=0.120
  //
  //    ii) NNPDF30_nlo_nf_4_pdfas (LHAID = 292000) for some FXFX 80X samples (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF30_nlo_nf_4_pdfas.tar.gz)
  //        mem=0 to mem=100 with alphas(MZ)=0.118, mem=0 => average on replicas 1-100; mem=1-100 => PDF replicas with  alphas(MZ)=0.118;
  //        mem=101 => central value for alphas=0.117; mem=102 => central value for alphas=0.119; maximum number of active flavors NF=4
  //
  //    iii) NNPDF30_nlo_nf_5_pdfas (LHAID = 292200) for some FXFX 80X samples (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF30_nlo_nf_5_pdfas.tar.gz)
  //         mem=0 to mem=100 with alphas(MZ)=0.118, mem=0 => average on replicas 1-100; mem=1-100 => PDF replicas with  alphas(MZ)=0.118;
  //         mem=101 => central value for alphas=0.117; mem=102 => central value for alphas=0.119
  // c) 101
  //    i) NNPDF30_nlo_as_0118 (LHAID = 260000) for some 92X samples (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF30_nlo_as_0118.tar.gz)
  //       alphas(MZ)=0.118. mem=0 => average on replicas; mem=1-100 => PDF replicas

  //    ii) NNPDF30_lo_as_0130 (LHAID = 262000) for some MLM 80X samples (http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF30_lo_as_0130.tar.gz)
  //        alphas(MZ)=0.130. mem=0 => average on replicas; mem=1-100 => PDF replicas
  //
  // In order to find out which PDF error set the sample has, open the Ntuple, read the LHEPDFweight array branch and look for LHEID in the title of the branch.
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
  return LHEInfoReader::clip(pdf_weights_[idx]);
}

double
LHEInfoReader::clip(double value,
                    double min_value,
                    double max_value)
{
  return std::min(std::max(value, min_value), max_value);
}
