#ifndef tthAnalysis_HiggsToTauTau_branchEntryTypeAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_branchEntryTypeAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"

#include <TPRegexp.h>
#include <TTree.h>

#include <vector>
#include <string>

enum { kDrop, kKeep };

typedef std::pair<int, TPRegexp> outputCommandEntry;

std::vector<outputCommandEntry> getOutputCommands(const std::vector<std::string>& outputCommands_string);

std::map<std::string, bool> getBranchesToKeep(TTree* inputTree, std::vector<outputCommandEntry>& outputCommands);

void copyBranches_singleType(TTree* inputTree, TTree* outputTree, std::map<std::string, bool>& isBranchToKeep, std::map<std::string, branchEntryBaseType*>& outputTree_branches);
void copyBranches_vectorType(TTree* inputTree, TTree* outputTree, std::map<std::string, bool>& isBranchToKeep, std::map<std::string, branchEntryBaseType*>& outputTree_branches);

#endif
