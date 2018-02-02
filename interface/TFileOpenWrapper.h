#ifndef TFILEOPENWRAPPER_H
#define TFILEOPENWRAPPER_H

#include <Rtypes.h> // Option_t, Int_t

// forward declarations
class TFile;

/**
 * Workaround to the problem that CMSSW workspace doesn't ship with HDFS support.
 * So we gotta parse the given paths ourselves and pass it to the THDFSFile class
 * which we have customized to our needs.
 *
 * The TFileOpenWrapper::Open() function mimics the behavior of TFile::Open()
 */
namespace TFileOpenWrapper
{
  TFile *
  Open(const char * path,
       Option_t * option = "",
       const char * ftitle = "",
       Int_t compress = 1);

  void
  Close(TFile * & f);
}

#endif // TFILEOPENWRAPPER_H
