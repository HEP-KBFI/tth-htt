#ifndef tthAnalysis_HiggsToTauTau_writerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_writerAuxFunctions_h

#include <Rtypes.h> // Int_t, UInt_t, ULong64_t, Float_t
#include <TTree.h> // TTree

#include <string> // std::string

void setBranchI(TTree* tree, const std::string& branchName, Int_t* address);
void setBranchUI(TTree* tree, const std::string& branchName, UInt_t* address);
void setBranchUL(TTree* tree, const std::string& branchName, ULong64_t* address);
void setBranchF(TTree* tree, const std::string& branchName, Float_t* address);
void setBranchVI(TTree* tree, const std::string& branchName, const std::string& branchName_n, Int_t* address);
void setBranchVUI(TTree* tree, const std::string& branchName, const std::string& branchName_n, UInt_t* address);
void setBranchVUL(TTree* tree, const std::string& branchName, const std::string& branchName_n, ULong64_t* address);
void setBranchVF(TTree* tree, const std::string& branchName, const std::string& branchName_n, Float_t* address);

#endif
