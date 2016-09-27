#ifndef TYPETRAITS_H
#define TYPETRAITS_H

template <typename T>
struct Traits
{
  static const char * TYPE_NAME;
};

template <typename T> const char * Traits<T>::TYPE_NAME = "unknown";

#define DECLARE_TYPE_TRAIT(type,name) template <> const char * Traits<type>::TYPE_NAME = name;

DECLARE_TYPE_TRAIT(Char_t, "B")
DECLARE_TYPE_TRAIT(UChar_t, "b")
DECLARE_TYPE_TRAIT(Short_t, "S")
DECLARE_TYPE_TRAIT(UShort_t, "s")
DECLARE_TYPE_TRAIT(Int_t, "I")
DECLARE_TYPE_TRAIT(Int_t *, "I")
DECLARE_TYPE_TRAIT(UInt_t, "i")
DECLARE_TYPE_TRAIT(Float_t, "F")
DECLARE_TYPE_TRAIT(Float_t *, "F")
DECLARE_TYPE_TRAIT(Double_t, "D")
DECLARE_TYPE_TRAIT(Long64_t, "L")
DECLARE_TYPE_TRAIT(ULong64_t, "l")
DECLARE_TYPE_TRAIT(Bool_t, "o")

#endif // TYPETRAITS_H
