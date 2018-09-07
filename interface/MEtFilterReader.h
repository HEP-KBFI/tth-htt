#ifndef tthAnalysis_HiggsToTauTau_MEtFilterReader_h
#define tthAnalysis_HiggsToTauTau_MEtFilterReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterFlag.h" // MEtFilterFlag::

#include <array> // std::array<>

// forward declarations
class MEtFilter;

class MEtFilterReader
  : public ReaderBase
{
public:
  MEtFilterReader(MEtFilter * metFilter,
                  int era);
  ~MEtFilterReader();

  void
  setBranchAddresses(TTree * tree) override;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  std::array<std::string, MEtFilterFlag::LAST> branchNames_;

  // CV: make sure that only one MEtFilterReader instance exists,
  static int numInstances_;
  static MEtFilterReader * instance_;

  MEtFilter * metFilter_;
  int era_;
};

#endif
