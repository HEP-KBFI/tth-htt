#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h"

void setBranchI(TTree* tree, const std::string& branchName, Int_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/I", branchName.data()));   
}

void setBranchUI(TTree* tree, const std::string& branchName, UInt_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/i", branchName.data()));   
}

void setBranchUL(TTree* tree, const std::string& branchName, ULong64_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/l", branchName.data()));   
}

void setBranchF(TTree* tree, const std::string& branchName, Float_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/F", branchName.data()));   
}

void setBranchVI(TTree* tree, const std::string& branchName, const std::string& branchName_n, Int_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/I", branchName.data(), branchName_n.data())); 
}

void setBranchVUI(TTree* tree, const std::string& branchName, const std::string& branchName_n, UInt_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/i", branchName.data(), branchName_n.data())); 
}

void setBranchVUL(TTree* tree, const std::string& branchName, const std::string& branchName_n, ULong64_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/l", branchName.data(), branchName_n.data())); 
}

void setBranchVF(TTree* tree, const std::string& branchName, const std::string& branchName_n, Float_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/F", branchName.data(), branchName_n.data())); 
}
