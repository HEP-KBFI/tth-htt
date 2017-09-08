#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper::, TFile, TString
#include "tthAnalysis/HiggsToTauTau/interface/THDFSFile.h" // THDFSFile

#include <TPRegexp.h> // TPRegexp

namespace TFileOpenWrapper
{
/**
   * @brief Opens the given path via the hdfs protocol if possible
   *        If not possible, resort to built-in ROOT
   * @param path     URI, the path to open
   * @param option   Options (e.g. in which mode the file is opened)
   * @param ftitle   Title???
   * @param compress Compression level and algorithm
   * @return Pointer to a TFile * instance
   *
   * @note NB! Need to free the memory explicitly! Even though we could only have an
   *       upcasted pointer to play with (i.e. TFile *, not THDFSFile *), the fact
   *       that the TFile destructor is made virtual will delete all additional
   *       memory inherited by its base classes thanks to dynamic dispatch.
   *
   * @todo Safeguards for writing? This is not supported by the THDFSFile class
   */
  TFile *
  Open(const char * path,
       Option_t * option,
       const char * ftitle,
       Int_t compress)
  {
    TFile * f = nullptr;
    const TString path_str(path);
    // we use triple forward slashes because if the user opts for
    // the hdfs protocol, the given path must be absolute/full and
    // therefore starting with a forward slash (although this check
    // is probably done in THDFSFile as well)
    const TString hdfs_protocol_prefix("hdfs:///");
    TPRegexp hdfs_regex("^" + hdfs_protocol_prefix);
    if(path_str(hdfs_regex) != "")
    {
      f = new THDFSFile(path, option, ftitle, compress);
      if(f && f -> IsZombie())
      {
        delete f;
        f = nullptr;
      }
    }
    else
    {
      f = TFile::Open(path, option, ftitle, compress);
    }
    return f;
  }
}
