#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h" // branchEntryBaseType, TTree, cmsException()

#include <TObjArray.h> // TObjArray
#include <TObjString.h> // TObjString, TString
#include <TBranch.h> // TBranch
#include <TLeaf.h> // TLeaf

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

#include <iostream> // std::cout

std::vector<outputCommandEntry>
getOutputCommands(const std::vector<std::string> & outputCommands_string)
{
  std::vector<outputCommandEntry> outputCommands;

  TPRegexp validPattern_line("keep|drop\\s+[a-zA-Z0-9_\\*/]+");
  TPRegexp validPattern_items("(keep|drop)\\s+([a-zA-Z0-9_\\*/]+)");

  for(const std::string & outputCommand_string: outputCommands_string)
  {
//--- check if output command specified in configuration file
//    matches the pattern "keep" or "drop" plus branchName
    TString outputCommand_tstring = outputCommand_string.data();

    if(validPattern_line.Match(outputCommand_tstring) == 1)
    {
//--- match individually "keep" or drop statement to branchNames;
//    require three matches (first match refers to entire line)
      const TObjArray * const items = validPattern_items.MatchS(outputCommand_tstring);
      assert(items->GetEntries() == 3);

      const std::string statement = (static_cast<TObjString *>(items->At(1)))->GetString().Data();
      const int statement_int = [&statement]() -> int
      {
        if(statement == "keep")
        {
          return kKeep;
        }
        if(statement == "drop")
        {
          return kDrop;
        }
        assert(0);
      }();

      const std::string branchNamePattern        = (static_cast<TObjString *>(items->At(2)))->GetString().Data();
      const std::string branchNamePattern_regexp = "^" + boost::replace_all_copy(branchNamePattern, "*", "[a-zA-Z0-9_]*") + "$";

      outputCommands.push_back(outputCommandEntry(statement_int, TPRegexp(branchNamePattern_regexp.data())));
      delete items;
    }
  }

  return outputCommands;
}

std::map<std::string, bool>
getBranchesToKeep(TTree * inputTree,
                  std::vector<outputCommandEntry> & outputCommands)
{
  std::map<std::string, bool> isBranchToKeep; // key = branchName

  const TObjArray * const branches = inputTree->GetListOfBranches();
  const int numBranches = branches->GetEntries();

  for(int idxBranch = 0; idxBranch < numBranches; ++idxBranch)
  {
    const TBranch * const branch = dynamic_cast<const TBranch * const>(branches->At(idxBranch));
    assert(branch);
    const std::string branchName = branch->GetName();

    for(outputCommandEntry & outputCommand: outputCommands)
    {
      const int statement = outputCommand.first;
      TPRegexp & branchNamePattern_regexp = outputCommand.second;

      const int branchNamePattern_match = branchNamePattern_regexp.Match(branchName.data());
      if(branchNamePattern_match == 1)
      {
        isBranchToKeep[branchName] = statement;
      }
    } // branchName
  } // idxBranch

  return isBranchToKeep;
}

void
copyBranches_singleType(TTree * inputTree,
                        TTree * outputTree,
                        const std::map<std::string, bool> & isBranchToKeep,
                        std::map<std::string, branchEntryBaseType *> & outputTree_branches)
{
//--- add branches of "simple" type (containing a single number for each event)
  const TObjArray * const inputTree_branches = inputTree->GetListOfBranches();
  const int inputTree_numBranches = inputTree_branches->GetEntries();

  for(int idxBranch = 0; idxBranch < inputTree_numBranches; ++idxBranch)
  {
    const TBranch * const inputTree_branch = dynamic_cast<const TBranch * const>(inputTree_branches->At(idxBranch));
    assert(inputTree_branch);
    const std::string branchName = inputTree_branch->GetName();

    if(isBranchToKeep.at(branchName))
    {
      const TLeaf * const inputTree_leaf = inputTree_branch->GetLeaf(branchName.data());
      if(! inputTree_leaf)
      {
        throw cmsException(__func__, __LINE__)
          << "Failed to identify Leaf type of Branch = '" << branchName << '\'';
      }

      const std::string branchType = inputTree_leaf->GetTypeName();
      const std::string branchInfo = inputTree_leaf->GetTitle();

      if(branchInfo.find("[") != std::string::npos && branchInfo.find("]") != std::string::npos)
      {
        continue; // skip branches of "vector" type
      }

      if(outputTree_branches.count(branchName))
      {
        std::cout << "Warning: copyBranches_singleType: detected a duplicate branch of the name: " << branchName << '\n';
        continue;
      }

      branchEntryBaseType * outputTree_branch = nullptr;
      if     (branchType == "Float_t"  ) outputTree_branch = new branchEntryTypeFF  (branchName, "F", branchName, "F");
      else if(branchType == "Double_t" ) outputTree_branch = new branchEntryTypeDD  (branchName, "D", branchName, "D");
      else if(branchType == "Int_t"    ) outputTree_branch = new branchEntryTypeII  (branchName, "I", branchName, "I");
      else if(branchType == "UInt_t"   ) outputTree_branch = new branchEntryTypeUIUI(branchName, "i", branchName, "i");
      else if(branchType == "ULong64_t") outputTree_branch = new branchEntryTypeULUL(branchName, "l", branchName, "l");
      else if(branchType == "UChar_t"  ) outputTree_branch = new branchEntryTypeUCUC(branchName, "b", branchName, "b");
      else if(branchType == "Short_t"  ) outputTree_branch = new branchEntryTypeSS  (branchName, "S", branchName, "S");
      else if(branchType == "UShort_t" ) outputTree_branch = new branchEntryTypeUSUS(branchName, "s", branchName, "s");
      else if(branchType == "Bool_t"   ) outputTree_branch = new branchEntryTypeBB  (branchName, "O", branchName, "O");
      else throw cmsException(__func__, __LINE__)
        << "Branch = '" << branchName << "' is of unsupported Type = " << branchType;

      outputTree_branch->setInputTree(inputTree);
      outputTree_branch->setOutputTree(outputTree);
      outputTree_branches[branchName] = outputTree_branch;
    } // isBranchesToKeep.at(branchName)
  } // idxBranch
}

void
copyBranches_vectorType(TTree * inputTree,
                        TTree * outputTree,
                        const std::map<std::string, bool> & isBranchToKeep,
                        std::map<std::string, branchEntryBaseType *> & outputTree_branches)
{
//--- add branches of "vector" type (containing a vector of numbers for each event)
  const TObjArray * const inputTree_branches = inputTree->GetListOfBranches();
  const int inputTree_numBranches = inputTree_branches->GetEntries();

  for(int idxBranch = 0; idxBranch < inputTree_numBranches; ++idxBranch)
  {
    const TBranch * const inputTree_branch = dynamic_cast<const TBranch * const>(inputTree_branches->At(idxBranch));
    assert(inputTree_branch);
    const std::string branchName = inputTree_branch->GetName();

    if(isBranchToKeep.at(branchName))
    {
      const TLeaf * const inputTree_leaf = inputTree_branch->GetLeaf(branchName.data());
      if(! inputTree_leaf)
      {
        throw cmsException(__func__, __LINE__)
          << "Failed to identify Leaf type of Branch = '" << branchName << '\'';
      }
      
      const std::string branchType = inputTree_leaf->GetTypeName();
      const std::string branchInfo = inputTree_leaf->GetTitle();

      if(! (branchInfo.find("[") != std::string::npos && branchInfo.find("]") != std::string::npos))
      {
        continue; // skip branches of "simple" type
      }

      if(outputTree_branches.count(branchName))
      {
        std::cout << "Warning: copyBranches_vectorType: detected a duplicate branch of the name: " << branchName << '\n';
        continue;
      }

      const int pos1 = branchInfo.find_last_of("[");
      const int pos2 = branchInfo.find_last_of("]");
      const std::string branchName_n = std::string(branchInfo, pos1 + 1, pos2 - (pos1 + 1));

      if(! outputTree_branches.count(branchName_n))
      {
        throw cmsException(__func__, __LINE__)
          << "Failed to identify Branch = '" << branchName_n << "' "
             "that specifies number of elements in Branch = '" << branchName << '\'';
      }

      const branchEntryBaseType * const branch_nElements = outputTree_branches[branchName_n];
      const int max_nElements = 103;

      branchEntryBaseType * outputTree_branch = nullptr;
      if(branchType == "Float_t")
      {
        outputTree_branch = new branchEntryTypeVFVF(branch_nElements, max_nElements, branchName, "F", branchName, "F");
      }
      else if(branchType == "Int_t")
      {
        outputTree_branch = new branchEntryTypeVIVI(branch_nElements, max_nElements, branchName, "I", branchName, "I");
      }
      else if(branchType == "UChar_t")
      {
        outputTree_branch = new branchEntryTypeVCVC(branch_nElements, max_nElements, branchName, "b", branchName, "b");
      }
      else if(branchType == "Bool_t")
      {
        outputTree_branch = new branchEntryTypeVBVB(branch_nElements, max_nElements, branchName, "O", branchName, "O");
      }
      else
      {
        throw cmsException(__func__, __LINE__)
          << "Branch = '" << branchName << "' is of unsupported Type = " << branchType << " !!\n";
      }

      outputTree_branch->setInputTree(inputTree);
      outputTree_branch->setOutputTree(outputTree);
      outputTree_branches[branchName] = outputTree_branch;
    }
  }
}
