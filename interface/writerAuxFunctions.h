#ifndef tthAnalysis_HiggsToTauTau_writerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_writerAuxFunctions_h

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string> // std::string

void setBranchI(TTree* tree, const std::string& branchName, Int_t* address);
void setBranchF(TTree* tree, const std::string& branchName, Float_t* address);
void setBranchVI(TTree* tree, const std::string& branchName, const std::string& branchName_n, Int_t* address);
void setBranchVF(TTree* tree, const std::string& branchName, const std::string& branchName_n, Float_t* address);

#endif
