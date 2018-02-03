#ifndef BRANCHADDRESSINITIALIZER_H
#define BRANCHADDRESSINITIALIZER_H

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_arithmetic<>
#include <string> // std::string
#include <algorithm> // std::sort(), std::set_union(), std::fill_n()

struct BranchAddressInitializer
{
  BranchAddressInitializer(TTree * tree = nullptr,
                           int lenVar = -1,
                           const std::string & branchName_n = "")
    : tree_(tree)
    , lenVar_(lenVar)
    , branchName_n_(branchName_n)
  {
    if(! tree_)
    {
      throw cmsException(this) << "No TTree provided!";
    }
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranch(T & value,
            const std::string & branchName)
  {
    tree_ -> Branch(branchName.data(), &value, Form("%s/%s", branchName.data(), Traits<T>::TYPE_NAME));
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranch(T * & address,
            const std::string & branchName)
  {
    if(lenVar_ > 0)
    {
      address = new T[lenVar_];
    }
    tree_ -> Branch(branchName.data(), address, Form(
      "%s%s/%s", branchName.data(), Form("[%s]", branchName_n_.data()), Traits<T>::TYPE_NAME)
    );
  }

  template<typename T,
           typename U = T,
           typename = typename std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranchAddress(T & value,
                   const std::string & branchName,
                   U default_value = 0)
  {
    if(! branchName.empty())
    {
      tree_ -> SetBranchAddress(branchName.data(), &value);
      value = static_cast<T>(default_value);
    }
  }

  template<typename T,
           typename U = T,
           typename = std::enable_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>>
  void
  setBranchAddress(T * & address,
                   const std::string & branchName,
                   U default_value = 0)
  {
    if(lenVar_ > 0)
    {
      address = new T[lenVar_];
      std::fill_n(address, lenVar_, static_cast<T>(default_value));
    }
    if(! branchName.empty())
    {
      tree_ -> SetBranchAddress(branchName.data(), address);
    }
  }

  BranchAddressInitializer &
  setLenVar(int lenVar)
  {
    lenVar_ = lenVar;
    return *this;
  }

  TTree * tree_;
  int lenVar_;
  std::string branchName_n_;
};

#endif // BRANCHADDRESSINITIALIZER_H
