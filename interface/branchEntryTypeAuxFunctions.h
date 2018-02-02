#ifndef tthAnalysis_HiggsToTauTau_branchEntryTypeAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_branchEntryTypeAuxFunctions_h

#include <TPRegexp.h> // TPRegexp

#include <map> // std::map<,>

// forward declarations
class TTree;
class branchEntryBaseType;

enum { kDrop, kKeep };

typedef std::pair<int, TPRegexp> outputCommandEntry;

std::vector<outputCommandEntry>
getOutputCommands(const std::vector<std::string> & outputCommands_string);

std::map<std::string, bool>
getBranchesToKeep(TTree * inputTree,
                  std::vector<outputCommandEntry> & outputCommands);

void
copyBranches_singleType(TTree * inputTree,
                        TTree * outputTree,
                        const std::map<std::string, bool> & isBranchToKeep,
                        std::map<std::string, branchEntryBaseType *> & outputTree_branches);

void
copyBranches_vectorType(TTree * inputTree, TTree * outputTree,
                        const std::map<std::string, bool> & isBranchToKeep,
                        std::map<std::string, branchEntryBaseType *> & outputTree_branches);

#endif
