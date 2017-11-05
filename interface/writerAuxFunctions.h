#ifndef tthAnalysis_HiggsToTauTau_writerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_writerAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>

#include <Rtypes.h> // Int_t, UInt_t, ULong64_t, Float_t
#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_scalar<>
#include <string> // std::string

template<typename T,
         typename = std::enable_if<std::is_scalar<T>::value>>
void
setBranch(TTree * tree,
          T * address,
          const std::string & branchName,
          const std::string & branchName_n = "")
{
  tree -> Branch(branchName.data(), address, Form(
    "%s%s/%s", branchName.data(), branchName_n.empty() ? "" : Form("[%s]", branchName_n.data()), Traits<T>::TYPE_NAME)
  );
}

void setBranchI(TTree* tree, const std::string& branchName, Int_t* address);
void setBranchUI(TTree* tree, const std::string& branchName, UInt_t* address);
void setBranchUL(TTree* tree, const std::string& branchName, ULong64_t* address);
void setBranchF(TTree* tree, const std::string& branchName, Float_t* address);
void setBranchVI(TTree* tree, const std::string& branchName, const std::string& branchName_n, Int_t* address);
void setBranchVUI(TTree* tree, const std::string& branchName, const std::string& branchName_n, UInt_t* address);
void setBranchVUL(TTree* tree, const std::string& branchName, const std::string& branchName_n, ULong64_t* address);
void setBranchVF(TTree* tree, const std::string& branchName, const std::string& branchName_n, Float_t* address);

#endif
