#ifndef tthAnalysis_HiggsToTauTau_TriggerHistManager_h
#define tthAnalysis_HiggsToTauTau_TriggerHistManager_h

/** \class TriggerHistManager
 *
 * Book and fill histogram for HLT paths used in the ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath

class TriggerHistManager
  : public HistManagerBase
{
public:
  TriggerHistManager(const edm::ParameterSet & cfg);
  ~TriggerHistManager();

  /// add HLT paths
  void add_hltPaths(const std::vector<hltPath*>& hltPaths);

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir);

  void
  fillHistograms(const std::vector<hltPath*>& hltPaths,
                 double evtWeight);

private:
  struct hltPathEntry
  {
    hltPathEntry(const std::string& branchName, double binCenter)
      : branchName_(branchName)
      , binCenter_(binCenter)
    {}
    ~hltPathEntry() {}
    std::string branchName_;
    double binCenter_;
  };
  std::map<std::string, hltPathEntry*> hltPathMap_;

  TH1 * histogram_hltPathCounter_;
};

#endif
