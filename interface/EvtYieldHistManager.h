#ifndef tthAnalysis_HiggsToTauTau_EvtYieldHistManager_h
#define tthAnalysis_HiggsToTauTau_EvtYieldHistManager_h

/** \class EvtYieldHistManager
 *
 * Book and fill histograms for event yield per unit of luminosity
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

namespace evtYieldHistManager
{
  class RunPeriod
  {
  public:
    RunPeriod(const std::string & name,
              const edm::ParameterSet & cfg);
    ~RunPeriod() {}

    const std::string & name() const;
    UInt_t firstRun() const;
    UInt_t lastRun() const;
    double luminosity() const;

  private:
    std::string name_;
    Long64_t firstRun_; // use return value of TString::Atoll() function for firstRun and lastRun data-members 
    Long64_t lastRun_;
    double luminosity_;
  };

  bool isLaterRunPeriod(const RunPeriod & runPeriod1,
                        const RunPeriod & runPeriod2);
}

class EvtYieldHistManager
  : public HistManagerBase
{
 public:
  EvtYieldHistManager(const edm::ParameterSet & cfg);
  ~EvtYieldHistManager() {}

  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const EventInfo & eventInfo,
                 double evtWeight);

 private:
  std::vector<evtYieldHistManager::RunPeriod> runPeriods_;
  bool isMC_;

  TH1 * histogram_evtYield_;
  TH1 * histogram_luminosity_;
};

#endif
