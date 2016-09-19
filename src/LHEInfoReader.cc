#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

#include "FWCore/Utilities/interface/Exception.h"

#include <assert.h> // assert

std::map<std::string, int> LHEInfoReader::numInstances_;
std::map<std::string, LHEInfoReader*> LHEInfoReader::instances_;

LHEInfoReader::LHEInfoReader()
  : max_scale_nWeights_(6)
  , branchName_scale_nWeights_("nLHE_weights_scale")
  , branchName_scale_weights_("LHE_weights_scale_wgt")
  , branchName_scale_ids_("LHE_weights_scale_id")
  , max_pdf_nWeights_(103)
  , branchName_pdf_nWeights_("nLHE_weights_pdf")
  , branchName_pdf_weights_("LHE_weights_pdf_wgt")
  , weight_scale_xUp_(1.)
  , weight_scale_xDown_(1.)
  , weight_scale_yUp_(1.)
  , weight_scale_yDown_(1.)
{
  setBranchNames();
}

LHEInfoReader::~LHEInfoReader()
{
  --numInstances_[branchName_scale_weights_];
  assert(numInstances_[branchName_scale_weights_] >= 0);
  if ( numInstances_[branchName_scale_weights_] == 0 ) {
    LHEInfoReader* gInstance = instances_[branchName_scale_weights_];
    assert(gInstance);
    delete[] gInstance->scale_weights_;
    delete[] gInstance->scale_ids_;
    delete[] gInstance->pdf_weights_;
    instances_[branchName_scale_weights_] = 0;
  }
}

void LHEInfoReader::setBranchNames()
{
  if ( numInstances_[branchName_scale_weights_] == 0 ) {
    instances_[branchName_scale_weights_] = this;
  } else {
    LHEInfoReader* gInstance = instances_[branchName_scale_weights_];
    if ( branchName_scale_nWeights_ != gInstance->branchName_scale_nWeights_ ||
	 branchName_scale_ids_      != gInstance->branchName_scale_ids_      ||
	 branchName_pdf_nWeights_   != gInstance->branchName_pdf_nWeights_   ||
         branchName_pdf_weights_    != gInstance->branchName_pdf_weights_    ) {
      throw cms::Exception("LHEInfoReader") 
	<< "Association between configuration parameters 'branchName_scale_weights' and 'branchName_pdf_weights' must be unique:"
	<< " present association 'branchName_scale_weights' = " << branchName_scale_weights_ << " with 'branchName_pdf_weights' = " << branchName_pdf_weights_ 
	<< " does not match previous association 'branchName_scale_weights' = " << gInstance->branchName_scale_weights_ << " with 'branchName_pdf_weights' = " << gInstance->branchName_pdf_weights_ << " !!\n";
    }
  }
  ++numInstances_[branchName_scale_weights_];
}

void LHEInfoReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_scale_weights_] == this ) {
    tree->SetBranchAddress(branchName_scale_nWeights_.data(), &scale_nWeights_);   
    scale_weights_ = new Float_t[max_scale_nWeights_];
    tree->SetBranchAddress(branchName_scale_weights_.data(), scale_weights_); 
    scale_ids_ = new Int_t[max_scale_nWeights_];
    tree->SetBranchAddress(branchName_scale_ids_.data(), scale_ids_); 
    tree->SetBranchAddress(branchName_pdf_nWeights_.data(), &pdf_nWeights_);   
    pdf_weights_ = new Float_t[max_pdf_nWeights_];
    tree->SetBranchAddress(branchName_pdf_weights_.data(), pdf_weights_); 
  }
}

void LHEInfoReader::read() const
{
  LHEInfoReader* gInstance = instances_[branchName_scale_weights_];
  assert(gInstance);
  if ( gInstance->scale_nWeights_ > max_scale_nWeights_ ) {
    throw cms::Exception("LHEInfoReader") 
      << "Number of Scale weights stored in Ntuple = " << gInstance->scale_nWeights_ << ", exceeds max_scale_nWeights_ = " << max_scale_nWeights_ << " !!\n";
  }
  weight_scale_xUp_   = 1.;
  weight_scale_xDown_ = 1.;
  weight_scale_yUp_   = 1.;
  weight_scale_yDown_ = 1.;
  for ( int idx = 0; idx < gInstance->scale_nWeights_; ++idx ) {
    double weight = gInstance->scale_weights_[idx];
    int id = gInstance->scale_ids_[idx];
    if      ( id == 1002 ) weight_scale_xUp_   = weight; // muF = 2, muR = 1
    else if ( id == 1003 ) weight_scale_xDown_ = weight; // muF = 0.5, muR = 1
    else if ( id == 1004 ) weight_scale_yUp_   = weight; // muF = 1, muR = 2
    else if ( id == 1007 ) weight_scale_yDown_ = weight; // muF = 1, muR = 0.5
  }
  if ( gInstance->pdf_nWeights_ > max_pdf_nWeights_ ) {
    throw cms::Exception("LHEInfoReader") 
      << "Number of PDF weights stored in Ntuple = " << gInstance->pdf_nWeights_ << ", exceeds max_pdf_nWeights_ = " << max_pdf_nWeights_ << " !!\n";
  }
}

double LHEInfoReader::getWeight_scale_xUp() const 
{ 
  return weight_scale_xUp_; 
}
double LHEInfoReader::getWeight_scale_xDown() const 
{ 
  return weight_scale_xDown_; 
}
double LHEInfoReader::getWeight_scale_yUp() const 
{
  return weight_scale_yUp_; 
}
double LHEInfoReader::getWeight_scale_yDown() const 
{ 
  return weight_scale_yDown_; 
}

int LHEInfoReader::getNumWeights_pdf() const
{
  return pdf_nWeights_;
}
double LHEInfoReader::getWeight_pdf(int idx) const
{
  if ( !(idx >= 0 && idx < pdf_nWeights_) ) {
    throw cms::Exception("LHEInfoReader") 
      << "Given index = " << idx << ", exceeds number of PDF weights stored in Ntuple = " << pdf_nWeights_ << " !!\n";
  }
  return pdf_weights_[idx];
}







