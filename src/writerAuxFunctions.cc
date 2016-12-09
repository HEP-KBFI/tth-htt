#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h"

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()

void setBranchI(TTree* tree, const std::string& branchName, Int_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/I", branchName.data()));   
}

void setBranchF(TTree* tree, const std::string& branchName, Float_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s/F", branchName.data()));   
}

void setBranchVI(TTree* tree, const std::string& branchName, const std::string& branchName_n, Int_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/I", branchName.data(), branchName_n.data())); 
}

void setBranchVF(TTree* tree, const std::string& branchName, const std::string& branchName_n, Float_t* address)
{
  tree->Branch(branchName.data(), address, Form("%s[%s]/F", branchName.data(), branchName_n.data())); 
}
