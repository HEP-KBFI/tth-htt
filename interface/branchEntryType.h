#ifndef tthAnalysis_HiggsToTauTau_branchEntryType_h
#define tthAnalysis_HiggsToTauTau_branchEntryType_h

#include "FWCore/Utilities/interface/Exception.h"

#include <Rtypes.h> // Float_t, Double_t, Int_t, UInt_t, ULong64_t, Char_t
#include <TTree.h>
#include <TTreeFormula.h>
#include <TString.h>
#include <TMath.h>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h> // assert

struct branchEntryBaseType
{
  branchEntryBaseType(const std::string& inputBranchName, const std::string& inputBranchType, const std::string& outputBranchName, const std::string& outputBranchType, int idx = -1)
    : inputBranchName_(inputBranchName),
      inputBranchType_string_(inputBranchType),
      idxColumn_(idx),
      outputBranchName_(outputBranchName),
      outputBranchType_string_(outputBranchType)
  {
    assert(inputBranchName_ != "");
    if      ( inputBranchType == "F" ) inputBranchType_ = kF;
    else if ( inputBranchType == "D" ) inputBranchType_ = kD;
    else if ( inputBranchType == "I" ) inputBranchType_ = kI;
    else if ( inputBranchType == "i" ) inputBranchType_ = kUI;
    else if ( inputBranchType == "l" ) inputBranchType_ = kUL;
    else throw cms::Exception("branchEntryBaseType") 
      << "Invalid branch type = '" << inputBranchType << "' for branch = '" << inputBranchName << "' !!\n";
    assert(outputBranchName_ != "");
    if ( outputBranchType == "F" ) {
      outputBranchType_ = kF;
      outputBranchFormat_ = kScientific;
      outputBranchPrecision_ = 6;
    } else if ( outputBranchType == "D" ) {
      outputBranchType_ = kD;
      outputBranchFormat_ = kScientific;
      outputBranchPrecision_ = 6;
    } else if ( outputBranchType == "I" ) {
      outputBranchType_ = kI;
    } else if ( outputBranchType == "i" ) {
      outputBranchType_ = kUI;
    } else if ( outputBranchType == "l" ) {
      outputBranchType_ = kUL;
    } else throw cms::Exception("branchEntryBaseType") 
      << "Invalid branch type = '" << outputBranchType << "' for branch = '" << outputBranchName << "' !!\n";
  }
  virtual ~branchEntryBaseType() {}
  virtual void setInputTree(TTree*) = 0;
  virtual void setOutputTree(TTree*) = 0;
  virtual void update() {}
  virtual void copyBranch() = 0;
  virtual Float_t getValue_float(int idxElement = 0) const = 0;
  virtual Double_t getValue_double(int idxElement = 0) const = 0;
  virtual Int_t getValue_int(int idxElement = 0) const = 0;
  std::string inputBranchName_;
  std::string inputBranchType_string_;
  enum { kF, kD, kI, kUI, kUL };
  int inputBranchType_;
  int idxColumn_;
  std::string outputBranchName_;
  std::string outputBranchType_string_;
  int outputBranchType_;
  enum { kFixed, kScientific };
  int outputBranchFormat_;
  int outputBranchPrecision_;
};

template <typename T1, typename T2>
struct branchEntryType : branchEntryBaseType
{
  branchEntryType(const std::string& inputBranchName, const std::string& inputBranchType, const std::string& outputBranchName, const std::string& outputBranchType, int idx = -1)
    : branchEntryBaseType(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx)
  {}
  ~branchEntryType() {}
  void setInputTree(TTree* inputTree)
  {
    inputTree->SetBranchAddress(inputBranchName_.data(), &inputValue_);
  }
  void setOutputTree(TTree* outputTree)
  {
    outputTree->Branch(outputBranchName_.data(), &outputValue_, Form("%s/%s", outputBranchName_.data(), outputBranchType_string_.data()));
  }
  void copyBranch()
  {
    if ( inputBranchType_ == kF && outputBranchType_ == kI ) {
      outputValue_ = TMath::Nint((Float_t)inputValue_);
    } else if ( inputBranchType_ == kD && outputBranchType_ == kI ) {
      outputValue_ = TMath::Nint((Double_t)inputValue_);
    } else {
      outputValue_ = inputValue_;
    }
  }
  Float_t getValue_float(int idxElement = 0) const
  {
    return outputValue_;
  }
  Double_t getValue_double(int idxElement = 0) const
  {
    return outputValue_;
  }
  Int_t getValue_int(int idxElement = 0) const
  {
    return TMath::Nint(outputValue_);
  }
  T1 inputValue_;
  T2 outputValue_;
};
typedef branchEntryType<Float_t,     Float_t> branchEntryTypeFF;
typedef branchEntryType<Float_t,    Double_t> branchEntryTypeFD;
typedef branchEntryType<Float_t,       Int_t> branchEntryTypeFI;
typedef branchEntryType<Double_t,    Float_t> branchEntryTypeDF;
typedef branchEntryType<Double_t,   Double_t> branchEntryTypeDD;
typedef branchEntryType<Double_t,      Int_t> branchEntryTypeDI;
typedef branchEntryType<Int_t,         Int_t> branchEntryTypeII;
typedef branchEntryType<UInt_t,       UInt_t> branchEntryTypeUIUI;
typedef branchEntryType<ULong64_t, ULong64_t> branchEntryTypeULUL;

template <typename T>
struct branchEntryFormulaType : branchEntryBaseType
{
  branchEntryFormulaType(const std::string& inputExpression, const std::string& outputBranchName, const std::string& outputBranchType, int idx = -1)
    : branchEntryBaseType(inputExpression, "F", outputBranchName, outputBranchType, idx),
      inputExpression_string_(inputExpression),
      inputExpression_(0)
  {}
  ~branchEntryFormulaType() 
  {
    delete inputExpression_;
  }
  void setInputTree(TTree* inputTree)
  {
    delete inputExpression_;
    inputExpression_ = new TTreeFormula(Form("branchEntryTypeFormula_%s", outputBranchName_.data()), inputExpression_string_.data(), inputTree);
  }
  void setOutputTree(TTree* outputTree)
  {
    outputTree->Branch(outputBranchName_.data(), &outputValue_, Form("%s/%s", outputBranchName_.data(), outputBranchType_string_.data()));
  }
  void update()
  {
    inputExpression_->UpdateFormulaLeaves();
  }
  void copyBranch()
  {
    Double_t inputValue = inputExpression_->EvalInstance();
    if ( outputBranchType_ == kI ) {
      outputValue_ = TMath::Nint(inputValue);
    } else {
      outputValue_ = inputValue;
    }
  }
  Float_t getValue_float(int idxElement = 0) const
  {
    return outputValue_;
  }
  Double_t getValue_double(int idxElement = 0) const
  {
    return outputValue_;
  }
  Int_t getValue_int(int idxElement = 0) const
  {
    return TMath::Nint(outputValue_);
  }
  std::string inputExpression_string_;
  TTreeFormula* inputExpression_;
  T outputValue_;
};
typedef branchEntryFormulaType<Float_t>  branchEntryFormulaTypeF;
typedef branchEntryFormulaType<Double_t> branchEntryFormulaTypeD;

template <typename T1, typename T2>
struct branchEntryVType : branchEntryBaseType
{
  branchEntryVType(const branchEntryBaseType* branch_nElements, int max_nElements,
		   const std::string& inputBranchName, const std::string& inputBranchType, const std::string& outputBranchName, const std::string& outputBranchType, int idx = -1)
    : branchEntryBaseType(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx)
    , branch_nElements_(branch_nElements)
    , max_nElements_(max_nElements)
  {
    assert(branch_nElements_);
    assert(max_nElements_ >= 1);
    inputValues_ = new T1[max_nElements_];
    outputValues_ = new T2[max_nElements_];
  }
  ~branchEntryVType() 
  {
    delete[] inputValues_;    
    delete[] outputValues_;
  }
  void setInputTree(TTree* inputTree)
  {
    inputTree->SetBranchAddress(inputBranchName_.data(), inputValues_);
  }
  void setOutputTree(TTree* outputTree)
  {
    outputTree->Branch(outputBranchName_.data(), outputValues_, 
      Form("%s[%s]/%s", outputBranchName_.data(), branch_nElements_->outputBranchName_.data(), outputBranchType_string_.data()));
  }
  void copyBranch()
  {
    assert(branch_nElements_);
    // CV: branches of "simple" type need to be copied before branches of "vector" type,
    //     to ensure that the branches containing the number of elements in the vectors are initialized before the vectors get copied
    (const_cast<branchEntryBaseType*>(branch_nElements_))->copyBranch();
    int numElements = branch_nElements_->getValue_int();
    assert(numElements <= max_nElements_);
    for ( int idxElement = 0; idxElement < numElements; ++idxElement ) {
      if ( inputBranchType_ == kF && outputBranchType_ == kI ) {
	outputValues_[idxElement] = TMath::Nint((Float_t)inputValues_[idxElement]);
      } else if ( inputBranchType_ == kD && outputBranchType_ == kI ) {
	outputValues_[idxElement] = TMath::Nint((Double_t)inputValues_[idxElement]);
      } else {
	outputValues_[idxElement] = inputValues_[idxElement];
      }
    }
  }
  Float_t getValue_float(int idxElement = 0) const
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return outputValues_[idxElement];
  }
  Double_t getValue_double(int idxElement = 0) const
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return outputValues_[idxElement];
  }
  Int_t getValue_int(int idxElement = 0) const
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return TMath::Nint(outputValues_[idxElement]);
  }
  const branchEntryBaseType* branch_nElements_;
  int max_nElements_;
  T1* inputValues_;
  T2* outputValues_;
};
typedef branchEntryVType<Float_t,   Float_t> branchEntryTypeVFVF;
typedef branchEntryVType<Double_t, Double_t> branchEntryTypeVDVD;
typedef branchEntryVType<Int_t,       Int_t> branchEntryTypeVIVI;

branchEntryBaseType* addBranch(std::vector<branchEntryBaseType*>&, const std::string&, const std::string&, int = -1);

#endif
