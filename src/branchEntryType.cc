#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"

branchEntryBaseType::branchEntryBaseType(const std::string & inputBranchName,
                                         const std::string & inputBranchType,
                                         const std::string & outputBranchName,
                                         const std::string & outputBranchType,
                                         const std::string & branchTitle,
                                         int idx)
  : idxColumn_(idx)
  , inputBranchName_(inputBranchName)
  , inputBranchType_string_(inputBranchType)
  , outputBranchName_(outputBranchName)
  , outputBranchType_string_(outputBranchType)
  , branchTitle_(branchTitle)
{
  assert(! inputBranchName_.empty());

  if     (inputBranchType == "F") inputBranchType_ = kF;
  else if(inputBranchType == "D") inputBranchType_ = kD;
  else if(inputBranchType == "I") inputBranchType_ = kI;
  else if(inputBranchType == "i") inputBranchType_ = kUI;
  else if(inputBranchType == "l") inputBranchType_ = kUL;
  else if(inputBranchType == "b") inputBranchType_ = kUC;
  else if(inputBranchType == "S") inputBranchType_ = kS;
  else if(inputBranchType == "s") inputBranchType_ = kUS;
  else if(inputBranchType == "O") inputBranchType_ = kB;
  else throw cmsException(this)
    << "Invalid input branch type = '" << inputBranchType
    << "' for branch = '" << inputBranchName << '\'';

  assert(! outputBranchName_.empty());
  if(outputBranchType == "F")
  {
    outputBranchType_      = kF;
    outputBranchFormat_    = kScientific;
    outputBranchPrecision_ = 6;
  }
  else if(outputBranchType == "D")
  {
    outputBranchType_      = kD;
    outputBranchFormat_    = kScientific;
    outputBranchPrecision_ = 6;
  }
  else if(outputBranchType == "I")
  {
    outputBranchType_ = kI;
  }
  else if(outputBranchType == "i")
  {
    outputBranchType_ = kUI;
  }
  else if(outputBranchType == "l")
  {
    outputBranchType_ = kUL;
  }
  else if(outputBranchType == "b")
  {
    outputBranchType_ = kUC;
  }
  else if( outputBranchType == "S")
  {
    outputBranchType_ = kS;
  }
  else if(outputBranchType == "s")
  {
    outputBranchType_ = kUS;
  }
  else if(outputBranchType == "O")
  {
    outputBranchType_ = kB;
  }
  else
  {
    throw cmsException(this)
      << "Invalid output branch type = '" << outputBranchType
      << "' for branch = '" << outputBranchName << '\'';
  }
}

branchEntryBaseType *
addBranch(std::vector<branchEntryBaseType *> & branches,
          const std::string & outputBranchName,
          const std::string & inputBranchName_and_Type,
          const std::string & branchTitle,
          int idx)
{
  const std::size_t idx1 = inputBranchName_and_Type.find_last_of("/");
  std::string inputBranchName = "";
  std::string inputBranchType = "";
  std::string outputBranchType = "";

  if(idx1 != std::string::npos)
  {
    const std::size_t idx2 = inputBranchName_and_Type.find_last_of("->");

    if(idx2 > idx1 && idx2 != std::string::npos)
    {
      inputBranchName  = std::string(inputBranchName_and_Type, 0, idx1);
      inputBranchType  = std::string(inputBranchName_and_Type, idx1 + 1, (idx2 - 2) - idx1);
      outputBranchType = std::string(inputBranchName_and_Type, idx2 + 1);
    }
    else
    {
      inputBranchName  = std::string(inputBranchName_and_Type, 0, idx1);
      inputBranchType  = std::string(inputBranchName_and_Type, idx1 + 1);
      outputBranchType = inputBranchType;
    }
  }

  branchEntryBaseType * branch = nullptr;
  if     (inputBranchType == "F"       && outputBranchType == "F") branch = new branchEntryTypeFD  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "F"       && outputBranchType == "D") branch = new branchEntryTypeFD  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "F"       && outputBranchType == "I") branch = new branchEntryTypeFI  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "D"       && outputBranchType == "F") branch = new branchEntryTypeFD  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "D"       && outputBranchType == "D") branch = new branchEntryTypeFD  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "D"       && outputBranchType == "I") branch = new branchEntryTypeFI  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "I"       && outputBranchType == "I") branch = new branchEntryTypeII  (inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "i"       && outputBranchType == "i") branch = new branchEntryTypeUIUI(inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "l"       && outputBranchType == "l") branch = new branchEntryTypeULUL(inputBranchName, inputBranchType, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "Formula" && outputBranchType == "F") branch = new branchEntryFormulaTypeF(inputBranchName, outputBranchName, outputBranchType, branchTitle, idx);
  else if(inputBranchType == "Formula" && outputBranchType == "D") branch = new branchEntryFormulaTypeD(inputBranchName, outputBranchName, outputBranchType, branchTitle, idx);
  else throw cmsException(__func__, __LINE__)
         << "Invalid branch declaration = '" << inputBranchName_and_Type
         << "' for branch = '" << outputBranchName << '\'';

  branches.push_back(branch);
  return branch;
}
