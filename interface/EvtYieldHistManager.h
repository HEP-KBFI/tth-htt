#ifndef tthAnalysis_HiggsToTauTau_EvtYieldHistManager_h
#define tthAnalysis_HiggsToTauTau_EvtYieldHistManager_h

/** \class EvtYieldHistManager
 *
 * Book and fill histograms for event yield per unit of luminosity
 *
 * \author Christian Veelken, Tallinn
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
    Long64_t firstRun() const;
    Long64_t lastRun() const;
    double luminosity() const;

  private:
    std::string name_;
    Long64_t firstRun_;
    Long64_t lastRun_;
    double luminosity_;
  };

  bool isLaterRunPeriod(const RunPeriod & runPeriod1,
                        const RunPeriod & runPeriod2);

  class TRandomTH1
  {
  public:
    TRandomTH1();
    TRandomTH1(TH1 * histogram);

    /**
     * Baseline: https://github.com/root-project/root/blob/771fdc1b25efc44fc8a00c32aaee2535dc78144f/hist/hist/src/TH1.cxx#L4741
     */
    Double_t
    GetRandom(ULong64_t seed) const;

  private:
    TH1 * histogram_;
    Double_t integral_;
    Double_t * integral_array_;
    Int_t nbinsx_;
  };
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
  evtYieldHistManager::TRandomTH1 * histogram_rnd_;
};

#endif
