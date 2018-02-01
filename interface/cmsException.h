#ifndef CMSEXCEPTION_H
#define CMSEXCEPTION_H

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception
#include <cxxabi.h> // abi::__cxa_demangle()

#include <type_traits> // std::enable_if<>, std::is_null_pointer

template <typename T,
          typename = typename std::enable_if<! std::is_null_pointer<T>::value>>
cms::Exception
cmsException(const T * const this_,
             const std::string & func = "",
             int line = -1)
{
  return cms::Exception(
    std::string(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0)) +
      (func.empty() ? "" : "::" + func)                         +
      (line >= 0 ? ":" + std::to_string(line) : "")             +
      " "
  );
}

cms::Exception
cmsException(const std::string & func,
             int line = -1);

#endif // CMSEXCEPTION_H
