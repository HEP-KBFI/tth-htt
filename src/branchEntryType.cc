#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"

#include "FWCore/Utilities/interface/Exception.h"

#include <iostream>
#include <assert.h>

branchEntryType::branchEntryType(const std::string& name, int type, int idxColumn)
  : name_(name),
    type_(type),
    idxColumn_(idxColumn),
    inputValue_int_(-1),
    inputValue_float_(-999.0),
    inputValue_char_(' '),
    outputValue_int_(-1),
    outputValue_float_(-999.0),
    outputValue_char_(' ')
{
  if      ( type_ == kInt   ) name_and_type_ = Form("%s/I", name_.data());
  else if ( type_ == kFloat ) name_and_type_ = Form("%s/D", name_.data());
  else if ( type_ == kChar  ) name_and_type_ = Form("%s/C", name_.data());
  else throw cms::Exception("branchEntryType") 
    << "Invalid type = " << type_ << " !!\n";
}

void branchEntryType::setInputTree(TTree* inputTree)
{
  if      ( type_ == kInt   ) inputTree->SetBranchAddress(name_.data(), &inputValue_int_);
  else if ( type_ == kFloat ) inputTree->SetBranchAddress(name_.data(), &inputValue_float_);
  else if ( type_ == kChar  ) inputTree->SetBranchAddress(name_.data(), &inputValue_char_);
  else assert(0);
}

void branchEntryType::setOutputTree(TTree* outputTree)
{
  if      ( type_ == kInt   ) outputTree->Branch(name_.data(), &outputValue_int_, name_and_type_.data());
  else if ( type_ == kFloat ) outputTree->Branch(name_.data(), &outputValue_float_, name_and_type_.data());
  else if ( type_ == kChar  ) outputTree->Branch(name_.data(), &outputValue_char_, name_and_type_.data());
  else assert(0);
}

void branchEntryType::copyInputToOutputValue()
{
  outputValue_int_ = inputValue_int_;
  outputValue_float_ = inputValue_float_;
  outputValue_char_ = inputValue_char_;
}

branchEntryType* addBranch(std::vector<branchEntryType*>& branches, const std::string& branchName, int type, int idxColumn)
{
  branchEntryType* branch = new branchEntryType(branchName, type, idxColumn);
  branches.push_back(branch);
  return branch;
}

