#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"

branchEntryBaseType* addBranch(std::vector<branchEntryBaseType*>& branches, const std::string& outputBranchName, const std::string& inputBranchName_and_Type, int idx)
{
  size_t idx1 = inputBranchName_and_Type.find_last_of("/");
  std::string inputBranchName = "";
  std::string inputBranchType = "";
  std::string outputBranchType = "";
  if ( idx1 != std::string::npos ) {
    size_t idx2 = inputBranchName_and_Type.find_last_of("->");
    if ( idx2 > idx1 && idx2 != std::string::npos ) {
      inputBranchName = std::string(inputBranchName_and_Type, 0, idx1);
      inputBranchType = std::string(inputBranchName_and_Type, idx1 + 1, (idx2 - 2) - idx1);
      outputBranchType = std::string(inputBranchName_and_Type, idx2 + 1);
    } else {
      inputBranchName = std::string(inputBranchName_and_Type, 0, idx1);
      inputBranchType = std::string(inputBranchName_and_Type, idx1 + 1);
      outputBranchType = inputBranchType;
    }
  }
  branchEntryBaseType* branch = 0;
  if      ( inputBranchType == "F"       && outputBranchType == "F" ) branch = new branchEntryTypeFD(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "F"       && outputBranchType == "D" ) branch = new branchEntryTypeFD(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "F"       && outputBranchType == "I" ) branch = new branchEntryTypeFI(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "D"       && outputBranchType == "F" ) branch = new branchEntryTypeFD(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "D"       && outputBranchType == "D" ) branch = new branchEntryTypeFD(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "D"       && outputBranchType == "I" ) branch = new branchEntryTypeFI(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "I"       && outputBranchType == "I" ) branch = new branchEntryTypeII(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "l"       && outputBranchType == "l" ) branch = new branchEntryTypeULUL(inputBranchName, inputBranchType, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "Formula" && outputBranchType == "F" ) branch = new branchEntryFormulaTypeF(inputBranchName, outputBranchName, outputBranchType, idx);
  else if ( inputBranchType == "Formula" && outputBranchType == "D" ) branch = new branchEntryFormulaTypeD(inputBranchName, outputBranchName, outputBranchType, idx);
  else throw cms::Exception("addBranch") 
    << "Invalid branch declaration = '" << inputBranchName_and_Type << "' for branch = '" << outputBranchName << "' !!\n";
  branches.push_back(branch);
  return branch;
}
