#ifndef CMSEXCEPTION_H
#define CMSEXCEPTION_H

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception
#include <cxxabi.h> // abi::__cxa_demangle()

template <typename T>
cms::Exception
cmsException(const T * const this_)
{
  return cms::Exception(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
}

#endif // CMSEXCEPTION_H
