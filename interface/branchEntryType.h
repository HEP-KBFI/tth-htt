#ifndef tthAnalysis_HiggsToTauTau_branchEntryType_h
#define tthAnalysis_HiggsToTauTau_branchEntryType_h

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TTree.h> // TTree
#include <TTreeFormula.h> // TTreeFormula
#include <TString.h> // Form()
#include <TMath.h> // TMath::Nint()

#include <cassert> // assert()

struct branchEntryBaseType
{
  enum { kF, kD, kI, kUI, kUL, kUC, kS, kUS, kB };
  enum { kFixed, kScientific };

  explicit branchEntryBaseType(const std::string & inputBranchName,
                               const std::string & inputBranchType,
                               const std::string & outputBranchName,
                               const std::string & outputBranchType,
                               const std::string & branchTitle = "",
                               int idx = -1);
  virtual ~branchEntryBaseType() {}

  virtual void setInputTree(TTree *) = 0;
  virtual void setOutputTree(TTree *) = 0;

  virtual void update() {}
  virtual void copyBranch() = 0;

  virtual Float_t  getValue_float(int idxElement = 0) const = 0;
  virtual Double_t getValue_double(int idxElement = 0) const = 0;
  virtual Int_t    getValue_int(int idxElement = 0) const = 0;

  int idxColumn_;

  std::string inputBranchName_;
  std::string inputBranchType_string_;
  int inputBranchType_;

  std::string outputBranchName_;
  std::string outputBranchType_string_;
  int outputBranchType_;

  int outputBranchFormat_;
  int outputBranchPrecision_;

  std::string branchTitle_;
};

template <typename T1, typename T2>
struct branchEntryType
  : public branchEntryBaseType
{
  branchEntryType(const std::string & inputBranchName,
                  const std::string & inputBranchType,
                  const std::string & outputBranchName,
                  const std::string & outputBranchType,
                  const std::string & branchTitle,
                  int idx = -1)
    : branchEntryBaseType(inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx)
  {}

  ~branchEntryType() {}

  void
  setInputTree(TTree * inputTree) override
  {
    inputTree->SetBranchAddress(inputBranchName_.data(), &inputValue_);
  }

  void
  setOutputTree(TTree * outputTree) override
  {
    TBranch * branch = outputTree->Branch(
      outputBranchName_.data(), &outputValue_, Form("%s/%s", outputBranchName_.data(), outputBranchType_string_.data())
    );
    if(! branchTitle_.empty())
    {
      branch->SetTitle(branchTitle_.data());
    }
  }

  void
  copyBranch() override
  {
    if(inputBranchType_ == kF && outputBranchType_ == kI)
    {
      outputValue_ = TMath::Nint(static_cast<Float_t>(inputValue_));
    }
    else if(inputBranchType_ == kD && outputBranchType_ == kI)
    {
      outputValue_ = TMath::Nint(static_cast<Double_t>(inputValue_));
    }
    else
    {
      outputValue_ = inputValue_;
    }
  }

  Float_t
  getValue_float(int idxElement = 0) const override
  {
    return outputValue_;
  }

  Double_t
  getValue_double(int idxElement = 0) const override
  {
    return outputValue_;
  }

  Int_t
  getValue_int(int idxElement = 0) const override
  {
    // Note that if T2 is Bool_t, then the function below will produce
    // a compilation warning that's not suppressable via gcc diagnostic
    // Also, RTTI is toothless here since it's not possible to partially
    // enable/disable member functions at well
    // And thirdly, the partial specialization of a template class is
    // extremely complicated
    // So we have to live with the warning messages for now and keep
    // ourselves from not adding -Werror to the build flags
    return TMath::Nint(outputValue_);
  }

  T1 inputValue_;
  T2 outputValue_;
};


template <typename T>
struct branchEntryFormulaType
  : public branchEntryBaseType
{
  branchEntryFormulaType(const std::string & inputExpression,
                         const std::string & outputBranchName,
                         const std::string & outputBranchType,
                         const std::string & branchTitle,
                         int idx = -1)
    : branchEntryBaseType(inputExpression, "F", outputBranchName, outputBranchType, branchTitle, idx)
    , inputExpression_string_(inputExpression)
    , inputExpression_(nullptr)
  {}

  ~branchEntryFormulaType() 
  {
    delete inputExpression_;
  }

  void
  setInputTree(TTree * inputTree) override
  {
    delete inputExpression_;
    inputExpression_ = new TTreeFormula(
      Form("branchEntryTypeFormula_%s", outputBranchName_.data()), inputExpression_string_.data(), inputTree
    );
  }

  void
  setOutputTree(TTree * outputTree) override
  {
    TBranch * branch = outputTree->Branch(
      outputBranchName_.data(), &outputValue_, Form("%s/%s", outputBranchName_.data(), outputBranchType_string_.data())
    );
    if(! branchTitle_.empty())
    {
      branch->SetTitle(branchTitle_.data());
    }
  }

  void
  update() override
  {
    inputExpression_->UpdateFormulaLeaves();
  }

  void
  copyBranch() override
  {
    const Double_t inputValue = inputExpression_->EvalInstance();
    outputValue_ = outputBranchType_ == kI ? TMath::Nint(inputValue) : inputValue;
  }

  Float_t
  getValue_float(int idxElement = 0) const override
  {
    return outputValue_;
  }

  Double_t
  getValue_double(int idxElement = 0) const override
  {
    return outputValue_;
  }

  Int_t
  getValue_int(int idxElement = 0) const override
  {
    return TMath::Nint(outputValue_);
  }

  std::string inputExpression_string_;
  TTreeFormula * inputExpression_;
  T outputValue_;
};

template <typename T1,
          typename T2>
struct branchEntryVType
  : public branchEntryBaseType
{
  branchEntryVType(const branchEntryBaseType * branch_nElements,
                   int max_nElements,
                   const std::string & inputBranchName,
                   const std::string & inputBranchType,
                   const std::string & outputBranchName,
                   const std::string & outputBranchType,
                   const std::string & branchTitle,
                   int idx = -1)
    : branchEntryBaseType(inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx)
    , branch_nElements_(branch_nElements)
    , max_nElements_(max_nElements)
  {
    assert(branch_nElements_);
    assert(max_nElements_ >= 1);
    inputValues_  = new T1[max_nElements_];
    outputValues_ = new T2[max_nElements_];
  }

  ~branchEntryVType() 
  {
    delete[] inputValues_;
    delete[] outputValues_;
  }

  void
  setInputTree(TTree * inputTree) override
  {
    inputTree->SetBranchAddress(inputBranchName_.data(), inputValues_);
  }

  void
  setOutputTree(TTree * outputTree) override
  {
    TBranch * branch = outputTree->Branch(
      outputBranchName_.data(), outputValues_,
      Form("%s[%s]/%s", outputBranchName_.data(), branch_nElements_->outputBranchName_.data(), outputBranchType_string_.data())
    );
    if(! branchTitle_.empty())
    {
      branch->SetTitle(branchTitle_.data());
    }
  }

  void
  copyBranch() override
  {
    assert(branch_nElements_);
    // CV: branches of "simple" type need to be copied before branches of "vector" type,
    //     to ensure that the branches containing the number of elements in the vectors are initialized before the vectors get copied
    const_cast<branchEntryBaseType *>(branch_nElements_)->copyBranch();

    const int numElements = branch_nElements_->getValue_int();
    if(numElements > max_nElements_)
    {
      throw cmsException(this, __func__, __LINE__)
        << "The number of elements in branch " << inputBranchName_ << " is " << numElements
        << " which exceeds the limit " << max_nElements_;
    }

    for(int idxElement = 0; idxElement < numElements; ++idxElement)
    {
      if(inputBranchType_ == kF && outputBranchType_ == kI)
      {
        outputValues_[idxElement] = TMath::Nint(static_cast<Float_t>(inputValues_[idxElement]));
      }
      else if(inputBranchType_ == kD && outputBranchType_ == kI)
      {
        outputValues_[idxElement] = TMath::Nint(static_cast<Double_t>(inputValues_[idxElement]));
      }
      else
      {
        outputValues_[idxElement] = inputValues_[idxElement];
      }
    }
  }

  Float_t
  getValue_float(int idxElement = 0) const override
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return outputValues_[idxElement];
  }

  Double_t
  getValue_double(int idxElement = 0) const override
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return outputValues_[idxElement];
  }

  Int_t
  getValue_int(int idxElement = 0) const override
  {
    int numElements = branch_nElements_->getValue_int();
    assert(idxElement < numElements);
    return TMath::Nint(outputValues_[idxElement]);
  }

  const branchEntryBaseType * branch_nElements_;
  int max_nElements_;
  T1 * inputValues_;
  T2 * outputValues_;
};

// no Long_t or Char_t b/c apparently these types depend on the machine
typedef branchEntryType<Float_t,     Float_t> branchEntryTypeFF;
typedef branchEntryType<Float_t,    Double_t> branchEntryTypeFD;
typedef branchEntryType<Float_t,       Int_t> branchEntryTypeFI;
typedef branchEntryType<Double_t,    Float_t> branchEntryTypeDF;
typedef branchEntryType<Double_t,   Double_t> branchEntryTypeDD;
typedef branchEntryType<Double_t,      Int_t> branchEntryTypeDI;
typedef branchEntryType<Int_t,         Int_t> branchEntryTypeII;
typedef branchEntryType<UInt_t,       UInt_t> branchEntryTypeUIUI;
typedef branchEntryType<ULong64_t, ULong64_t> branchEntryTypeULUL;
typedef branchEntryType<UChar_t,     UChar_t> branchEntryTypeUCUC;
typedef branchEntryType<Short_t,     Short_t> branchEntryTypeSS;
typedef branchEntryType<UShort_t,   UShort_t> branchEntryTypeUSUS;
typedef branchEntryType<Bool_t,       Bool_t> branchEntryTypeBB;

typedef branchEntryFormulaType<Float_t>  branchEntryFormulaTypeF;
typedef branchEntryFormulaType<Double_t> branchEntryFormulaTypeD;

typedef branchEntryVType<Float_t,   Float_t> branchEntryTypeVFVF;
typedef branchEntryVType<Double_t, Double_t> branchEntryTypeVDVD;
typedef branchEntryVType<Int_t,       Int_t> branchEntryTypeVIVI;
typedef branchEntryVType<UInt_t,     UInt_t> branchEntryTypeVUIVUI;
typedef branchEntryVType<UChar_t,   UChar_t> branchEntryTypeVCVC;
typedef branchEntryVType<Bool_t,     Bool_t> branchEntryTypeVBVB;

branchEntryBaseType *
addBranch(std::vector<branchEntryBaseType *> & branches,
          const std::string & outputBranchName,
          const std::string & inputBranchName_and_Type,
          const std::string & branchTitle,
          int = -1);

#endif
