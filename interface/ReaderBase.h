#ifndef READERBASE_H
#define READERBASE_H

class TTree; // forward declaration

class ReaderBase
{
public:
  ReaderBase() = default;
  virtual ~ReaderBase() {}

  virtual void
  setBranchAddresses(TTree * tree) = 0;
};

#endif // READERBASE_H
