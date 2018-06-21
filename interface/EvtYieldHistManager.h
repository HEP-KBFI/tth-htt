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

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" 

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <TPRegexp.h>
#include <TObjString.h>
#include <TObjArray.h>

#include <vector>
#include <string>

namespace evtYieldHistManager
{
  class RunPeriod
  {
   public:
    RunPeriod(const std::string& name, const edm::ParameterSet& cfg)
      : name_(name)
      , firstRun_(0)
      , lastRun_(0)
    {
      std::string runRange = cfg.getParameter<std::string>("runRange");
      TPRegexp regexpParser_range("([0-9]+)-([0-9]+)");
      const TObjArray* const subStrings = regexpParser_range.MatchS(runRange.data());
      if ( subStrings->GetEntries() == 3 ) {
	firstRun_ = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atoll();
	lastRun_ = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atoll();
      }
      if ( !(lastRun_ > firstRun_) )
	throw cmsException(this)
	  << "Invalid Configuration parameter 'runRange' = " << runRange << "!!\n";
      luminosity_ = cfg.getParameter<double>("luminosity");
      if ( !(luminosity_ > 0.) )
	throw cmsException(this)
	  << "Invalid Configuration parameter 'luminosity' = " << luminosity_ << "!!\n";
    }
    ~RunPeriod() {}

    const std::string& name() const { return name_; }
    UInt_t firstRun() const { return firstRun_; }
    UInt_t lastRun() const { return lastRun_; }
    double luminosity() const { return luminosity_; }

   private:
    std::string name_;
    Long64_t firstRun_; // use return value of TString::Atoll() function for firstRun and lastRun data-members 
    Long64_t lastRun_;
    double luminosity_;
  };
  
  bool isLaterRunPeriod(const RunPeriod& runPeriod1, const RunPeriod& runPeriod2)
  {
    if ( (runPeriod1.firstRun() > runPeriod2.firstRun() && runPeriod1.firstRun() < runPeriod2.lastRun()) ||
	 (runPeriod1.lastRun()  > runPeriod2.firstRun() && runPeriod1.lastRun()  < runPeriod2.lastRun()) ) {
      throw cms::Exception("isLaterRunPeriod")
	<< "Run periods '" << runPeriod1.name() << "' and '" << runPeriod2.name() << "' must not overlap !!\n";
    }
    return runPeriod1.firstRun() > runPeriod2.firstRun();
  }
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
  fillHistograms(const EventInfo& eventInfo,
		 double evtWeight);

 private:
  std::vector<evtYieldHistManager::RunPeriod> runPeriods_;

  TH1 * histogram_evtYield_;
  TH1 * histogram_luminosity_;
};

#endif
