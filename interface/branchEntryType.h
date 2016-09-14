#ifndef tthAnalysis_HiggsToTauTau_branchEntryType_h
#define tthAnalysis_HiggsToTauTau_branchEntryType_h

#include <TObject.h> // CV: include typedefs for Int_t and Double_t
#include <TTree.h>
#include <TString.h>

#include <string>
#include <vector>
#include <map>

struct branchEntryType
{
  branchEntryType(const std::string&, int, int = -1);
  ~branchEntryType() {}
  void setInputTree(TTree*);
  void setOutputTree(TTree*);
  Int_t getValue_int() const 
  { 
    return inputValue_int_; 
  }
  Float_t getValue_float() const 
  { 
    return inputValue_float_; 
  }
  Double_t getValue_double() const 
  { 
    return inputValue_double_; 
  }
  Char_t getValue_char() const 
  { 
    return inputValue_char_; 
  }
  void setValue_int(Int_t value) 
  { 
    inputValue_int_ = value; 
    outputValue_int_ = value; 
  }
  void setValue_float(Float_t value) 
  { 
    inputValue_float_ = value;
    outputValue_float_ = value;
  }
  void setValue_double(Double_t value) 
  { 
    inputValue_double_ = value;
    outputValue_double_ = value;
  }
  void setValue_char(Char_t value) 
  { 
    inputValue_char_ = value; 
    outputValue_char_ = value; 
  }
  void copyInputToOutputValue();
  std::string name_;
  enum { kInt, kFloat, kChar };
  int type_;
  std::string name_and_type_;
  int idxColumn_;
  Int_t inputValue_int_;
  Float_t inputValue_float_;
  Double_t inputValue_double_;
  Char_t inputValue_char_;
  Int_t outputValue_int_;
  Float_t outputValue_float_;
  Double_t outputValue_double_;
  Char_t outputValue_char_;
};

branchEntryType* addBranch(std::vector<branchEntryType*>&, const std::string&, int, int = -1);

#endif
