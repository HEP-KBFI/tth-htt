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
    TString path_str(path);
    TString option_str(option);
    option_str.ToUpper();

    const TString hdfs_protocol_prefix("hdfs://");
    TPRegexp hdfs_protocol_regex("^" + hdfs_protocol_prefix);

    // if the mode is empty or set to read, and the given path starts
    // with /hdfs, we prepend the path suitable for the hdfs protocol
    // (we want to avoid opening files on /hdfs for writing)
    const TString hdfs_path_prefix("/hdfs");
    TPRegexp hdfs_path_regex("^" + hdfs_path_prefix);

    const auto read_from_hdfs = [&f](
      const char * path,
      Option_t * option,
      const char * ftitle,
      Int_t compress) -> void
    {
      f = new THDFSFile(path, option, ftitle, compress);
      if(f && f -> IsZombie())
      {
        delete f;
        f = nullptr;
      }
      return;
    };

    if(path_str(hdfs_protocol_regex) != "")
    {
      read_from_hdfs(path, option, ftitle, compress);
    }
    else if(path_str(hdfs_path_regex) != "" && (option_str == "" || option_str == "READ"))
    {
      // here we change the path: /hdfs/A/B/C/... -> hdfs:///A/B/C/...
      read_from_hdfs(
        path_str.Replace(0, hdfs_path_prefix.Length(), hdfs_protocol_prefix), option, ftitle, compress
      );
    }
    else
    {
      f = TFile::Open(path, option, ftitle, compress);
    }
    return f;
  }
}
