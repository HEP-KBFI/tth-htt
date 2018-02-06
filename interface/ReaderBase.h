#ifndef READERBASE_H
#define READERBASE_H

class TTree; // forward declaration

#include <string> // std::string

class ReaderBase
{
public:
  ReaderBase() = default;
  virtual ~ReaderBase() {}

  virtual void
  setBranchAddresses(TTree * tree) = 0;
};

#endif // READERBASE_H
