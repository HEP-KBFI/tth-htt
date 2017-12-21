#include "tthAnalysis/HiggsToTauTau/interface/branchEntryTypeAuxFunctions.h"

#include <TObjArray.h> // TObjArray
#include <TObjString.h> // TObjString
#include <TBranch.h> // TBranch
#include <TLeaf.h> // TLeaf

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()

std::vector<outputCommandEntry> getOutputCommands(const std::vector<std::string>& outputCommands_string)
{
  std::vector<outputCommandEntry> outputCommands;

  TPRegexp validPattern_line("keep|drop\\s+[a-zA-Z0-9_\\*/]+");
  TPRegexp validPattern_items("(keep|drop)\\s+([a-zA-Z0-9_\\*/]+)");
  typedef std::pair<int, TPRegexp> outputCommandEntry;
  for ( std::vector<std::string>::const_iterator outputCommand_string = outputCommands_string.begin();
	outputCommand_string != outputCommands_string.end(); ++outputCommand_string ) {

//--- check if output command specified in configuration file
//    matches the pattern "keep" or "drop" plus branchName
    TString outputCommand_tstring = outputCommand_string->data();
    if ( validPattern_line.Match(outputCommand_tstring) == 1 ) {

//--- match individually "keep" or drop statement to branchNames;
//    require three matches (first match refers to entire line)
      TObjArray* items = validPattern_items.MatchS(outputCommand_tstring);
      assert(items->GetEntries() == 3);

      std::string statement = ((TObjString*)items->At(1))->GetString().Data();
      int statement_int = -1;
      if ( statement == "keep" ) statement_int = kKeep;
      if ( statement == "drop" ) statement_int = kDrop;
      assert(statement_int == kKeep || statement_int == kDrop);
      //std::cout << " statement = " << statement << "(int = " << statement_int << ")" << std::endl;
        
      std::string branchNamePattern = ((TObjString*)items->At(2))->GetString().Data();
      std::string branchNamePattern_regexp = TString("^").Append(branchNamePattern.data()).ReplaceAll("*", "[a-zA-Z0-9_]*").Append("$").Data();
      //std::cout << " branchNamePattern_regexp = " << branchNamePattern_regexp << std::endl;

      outputCommands.push_back(outputCommandEntry(statement_int, TPRegexp(branchNamePattern_regexp.data())));
    }
  }

  return outputCommands;
}

std::map<std::string, bool> getBranchesToKeep(TTree* inputTree, std::vector<outputCommandEntry>& outputCommands)
{
  std::map<std::string, bool> isBranchToKeep; // key = branchName

  TObjArray* branches = inputTree->GetListOfBranches();
  int numBranches = branches->GetEntries();
  for ( int idxBranch = 0; idxBranch < numBranches; ++idxBranch ) {
    const TBranch* branch = dynamic_cast<const TBranch*>(branches->At(idxBranch));
    assert(branch);
    std::string branchName = branch->GetName();
    //std::cout << "branchName = " << branchName << std::endl;

    for ( std::vector<outputCommandEntry>::iterator outputCommand = outputCommands.begin();
          outputCommand != outputCommands.end(); ++outputCommand ) {
      int statement = outputCommand->first;
      std::string statement_string = ( statement == kKeep ) ? "keep" : "drop";
      //std::cout << " statement = " << statement_string << "(int = " << statement << ")" << std::endl;
      
      TPRegexp& branchNamePattern_regexp = outputCommand->second;
      //std::cout << " branchNamePattern_regexp = '" << branchNamePattern_regexp.GetPattern() << "'" << std::endl;
      
      int branchNamePattern_match = branchNamePattern_regexp.Match(branchName.data());
      //std::cout << " branchNamePattern_match = " << branchNamePattern_match << std::endl;
      
      if ( branchNamePattern_match == 1 ) isBranchToKeep[branchName] = statement;
    }
    
    //if ( isBranchToKeep[branchName] ) std::cout << "--> keeping branch = '" << branchName << "'" << std::endl;
    //else std::cout << "--> dropping branch = '" << branchName << "'" << std::endl;
  }

  return isBranchToKeep;
}

void copyBranches_singleType(TTree* inputTree, TTree* outputTree, std::map<std::string, bool>& isBranchToKeep, std::map<std::string, branchEntryBaseType*>& outputTree_branches)
{
  // add branches of "simple" type (containing a single number for each event)
  //std::cout << "<copyBranches_singleType>:" << std::endl;
  TObjArray* inputTree_branches = inputTree->GetListOfBranches();
  int inputTree_numBranches = inputTree_branches->GetEntries();
  for ( int idxBranch = 0; idxBranch < inputTree_numBranches; ++idxBranch ) {
    const TBranch* inputTree_branch = dynamic_cast<const TBranch*>(inputTree_branches->At(idxBranch));
    assert(inputTree_branch);
    std::string branchName = inputTree_branch->GetName();
    //std::cout << "branchName = " << branchName << std::endl;

    if ( isBranchToKeep[branchName] ) {
      TLeaf* inputTree_leaf = inputTree_branch->GetLeaf(branchName.data());
      if ( !inputTree_leaf ) 
	throw cms::Exception("copyBranches") 
	  << "Failed to identify Leaf type of Branch = '" << branchName << "' !!\n";
      
      std::string branchType = inputTree_leaf->GetTypeName();
      std::string branchInfo = inputTree_leaf->GetTitle();

      if ( branchInfo.find("[") != std::string::npos && branchInfo.find("]") != std::string::npos ) continue; // skip branches of "vector" type

      branchEntryBaseType* outputTree_branch = 0;
      if      ( branchType == "Float_t"   ) outputTree_branch = new branchEntryTypeFF  (branchName, "F", branchName, "F");
      else if ( branchType == "Double_t"  ) outputTree_branch = new branchEntryTypeDD  (branchName, "D", branchName, "D");
      else if ( branchType == "Int_t"     ) outputTree_branch = new branchEntryTypeII  (branchName, "I", branchName, "I");
      else if ( branchType == "UInt_t"    ) outputTree_branch = new branchEntryTypeUIUI(branchName, "i", branchName, "i");
      else if ( branchType == "ULong64_t" ) outputTree_branch = new branchEntryTypeULUL(branchName, "l", branchName, "l");
      else if ( branchType == "UChar_t"   ) outputTree_branch = new branchEntryTypeUCUC(branchName, "b", branchName, "b");
      else if ( branchType == "Short_t"   ) outputTree_branch = new branchEntryTypeSS  (branchName, "S", branchName, "S");
      else if ( branchType == "UShort_t"  ) outputTree_branch = new branchEntryTypeUSUS(branchName, "s", branchName, "s");
      else if ( branchType == "Bool_t"    ) outputTree_branch = new branchEntryTypeBB  (branchName, "O", branchName, "O");
      else throw cms::Exception("copyBranches") 
        << "Branch = '" << branchName << "' is of unsupported Type = " << branchType << " !!\n";
      outputTree_branch->setInputTree(inputTree);
      outputTree_branch->setOutputTree(outputTree);
      outputTree_branches[branchName] = outputTree_branch;
    }
  }
}

void copyBranches_vectorType(TTree* inputTree, TTree* outputTree, std::map<std::string, bool>& isBranchToKeep, std::map<std::string, branchEntryBaseType*>& outputTree_branches)
{
  // add branches of "vector" type (containing a vector of numbers for each event)
  //std::cout << "<copyBranches_vectorType>:" << std::endl;
  TObjArray* inputTree_branches = inputTree->GetListOfBranches();
  int inputTree_numBranches = inputTree_branches->GetEntries();
  for ( int idxBranch = 0; idxBranch < inputTree_numBranches; ++idxBranch ) {
    const TBranch* inputTree_branch = dynamic_cast<const TBranch*>(inputTree_branches->At(idxBranch));
    assert(inputTree_branch);
    std::string branchName = inputTree_branch->GetName();
    //std::cout << "branchName = " << branchName << std::endl;

    if ( isBranchToKeep[branchName] ) {
      TLeaf* inputTree_leaf = inputTree_branch->GetLeaf(branchName.data());
      if ( !inputTree_leaf ) 
	throw cms::Exception("copyBranches") 
	  << "Failed to identify Leaf type of Branch = '" << branchName << "' !!\n";
      
      std::string branchType = inputTree_leaf->GetTypeName();
      std::string branchInfo = inputTree_leaf->GetTitle();

      if ( !(branchInfo.find("[") != std::string::npos && branchInfo.find("]") != std::string::npos) ) continue; // skip branches of "simple" type
      int pos1 = branchInfo.find_last_of("[");
      int pos2 = branchInfo.find_last_of("]");
      std::string branchName_n = std::string(branchInfo, pos1 + 1, pos2 - (pos1 + 1));
      if ( outputTree_branches.find(branchName_n) == outputTree_branches.end() )
	throw cms::Exception("produceNtuple_2lss_1tau") 
	  << "Failed to identify Branch = '" << branchName_n << "' that specifies number of elements in Branch = '" << branchName << "' !!\n";
      const branchEntryBaseType* branch_nElements = outputTree_branches[branchName_n];
      int max_nElements = ( branchName.find("LHE") != std::string::npos ) ? 102 : 48;

      branchEntryBaseType* outputTree_branch = 0;
      if      ( branchType == "Float_t"   ) outputTree_branch = new branchEntryTypeVFVF(branch_nElements, max_nElements, branchName, "F", branchName, "F");
      else if ( branchType == "Int_t"     ) outputTree_branch = new branchEntryTypeVIVI(branch_nElements, max_nElements, branchName, "I", branchName, "I");
      else throw cms::Exception("copyBranches") 
	<< "Branch = '" << branchName << "' is of unsupported Type = " << branchType << " !!\n";
      outputTree_branch->setInputTree(inputTree);
      outputTree_branch->setOutputTree(outputTree);
      outputTree_branches[branchName] = outputTree_branch;
    }
  }
}
