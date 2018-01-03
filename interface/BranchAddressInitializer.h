#ifndef BRANCHADDRESSINITIALIZER_H
#define BRANCHADDRESSINITIALIZER_H

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>

#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_scalar<>
#include <string> // std::string

struct BranchAddressInitializer
{
  BranchAddressInitializer(TTree * tree = nullptr,
                           const std::string & branchName_n = "",
                           int lenVar = -1)
    : tree_(tree)
    , lenVar_(lenVar)
    , branchName_n_(branchName_n)
  {}

  template<typename T,
           typename = std::enable_if<std::is_scalar<T>::value>>
  void
  setBranch(T & value,
            const std::string & branchName)
  {
    tree_ -> Branch(branchName.data(), &value, Form("%s/%s", branchName.data(), Traits<T>::TYPE_NAME));
  }

  template<typename T,
           typename = std::enable_if<std::is_scalar<T>::value>>
  void
  setBranch(T * & address,
            const std::string & branchName,
            bool disable_array_init = false)
  {
    if(lenVar_ > 0 && !disable_array_init)
    {
      address = new T[lenVar_];
    }
    tree_ -> Branch(branchName.data(), address, Form(
      "%s%s/%s", branchName.data(), Form("[%s]", branchName_n_.data()), Traits<T>::TYPE_NAME)
    );
  }

  TTree * tree_;
  int lenVar_;
  std::string branchName_n_;
};

#endif // BRANCHADDRESSINITIALIZER_H
