#ifndef tthAnalysis_HiggsToTauTau_SyncNtupleManagerBase_h
#define tthAnalysis_HiggsToTauTau_SyncNtupleManagerBase_h

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_arithmetic<>
#include <regex> // std::regex

// forward declarations
class TFile;

class SyncNtupleManagerBase
{
public:
  SyncNtupleManagerBase(TFile * outputFilePtr,
                        const std::string & outputTreeName);
  virtual ~SyncNtupleManagerBase();

  virtual void initializeBranches() = 0;
  void fill();
  void write();
  virtual void resetBranches() = 0;

  static const Int_t placeholder_value;
  static const std::regex endsWithNumberRegex;

protected:
  static bool
  endsWithNumber(const std::string & infix);

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(const std::string & infix,
              int count,
              T * & var,
              const std::string & label)
  {
    if(count > 0)
    {
      const bool isEndsWithNumber = SyncNtupleManagerBase::endsWithNumber(infix);
      var = new T[count];
      for(int i = 0; i < count; ++i)
      {
        var[i] = placeholder_value;
        const std::string branchName = Form("%s%s%d_%s",
          infix.c_str(), isEndsWithNumber ? "_" : "", i + 1, label.c_str()
        );
        outputTree -> Branch(branchName.c_str(), &(var[i]), Form("%s/%s", branchName.c_str(), Traits<T>::TYPE_NAME));
      }
    }
    else
    {
      throw cmsException(this, __func__)
        << "Invalid array size = " << count << " for variable " << label << " with infix = " << infix;
    }
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(const std::string & infix,
              int count,
              T * & var,
              const std::string & label,
              Args & ... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(infix, count, var, label);
    setBranches(infix, count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(T & var,
              const std::string & label)
  {
    var = placeholder_value;
    outputTree -> Branch(label.c_str(), &var, Form("%s/%s", label.c_str(), Traits<T>::TYPE_NAME));
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(T & var,
              const std::string & label,
              Args & ... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(var, label);
    setBranches(remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(int count,
        T * & var)
  {
    for(int i = 0; i < count; ++i)
    {
      if(typeid(T) != typeid(Bool_t))
      {
        var[i] = placeholder_value;
      }
      else
      {
        var[i] = false;
      }
    }
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(int count,
        T * & var,
        Args & ... remainingVars)
  {
    reset(count, var);
    reset(count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(T & var)
  {
    if(typeid(T) != typeid(Bool_t))
    {
      var = placeholder_value;
    }
    else
    {
      var = false;
    }
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(T & var,
        Args & ... remainingVars)
  {
    reset(var);
    reset(remainingVars...);
  }

  TFile * outputFile;
  TDirectory * outputDir;
  TTree * outputTree;
};

#endif // tthAnalysis_HiggsToTauTau_SyncNtupleManagerBase_h
