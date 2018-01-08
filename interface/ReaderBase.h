#ifndef READERBASE_H
#define READERBASE_H

class TTree; // forward declaration

#include <vector> // std::vector<>
#include <string> // std::string

class ReaderBase
{
public:
  ReaderBase() = default;
  virtual ~ReaderBase() {}

  virtual std::vector<std::string>
  setBranchAddresses(TTree * tree) = 0;
};

#endif // READERBASE_H
