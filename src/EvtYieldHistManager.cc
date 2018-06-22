#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TPRegexp.h> // TPRegexp

namespace evtYieldHistManager
{
  RunPeriod::RunPeriod(const std::string & name,
                       const edm::ParameterSet & cfg)
    : name_(name)
    , firstRun_(0)
    , lastRun_(0)
    , luminosity_(cfg.getParameter<double>("luminosity"))
  {
    if(luminosity_ <= 0.)
    {
      throw cmsException(this) << "Invalid Configuration parameter 'luminosity' = " << luminosity_ << "!!\n";
    }

    const std::string runRange = cfg.getParameter<std::string>("runRange");
    TPRegexp regexpParser_range("([0-9]+)-([0-9]+)");
    const TObjArray * const subStrings = regexpParser_range.MatchS(runRange.data());
    if(subStrings->GetEntries() == 3)
    {
      firstRun_ = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atoll();
      lastRun_ = (static_cast<TObjString *>(subStrings->At(2)))->GetString().Atoll();
    }
    delete subStrings;

    if(lastRun_ <= firstRun_)
    {
      throw cmsException(this)
        << "Invalid Configuration parameter 'runRange' = " << runRange
        << " ('" << firstRun_ << "' - '" << lastRun_ << "') !!\n"
      ;
    }
  }

  const std::string &
  RunPeriod::name() const
  {
    return name_;
  }

  UInt_t
  RunPeriod::firstRun() const
  {
    return firstRun_;
  }

  UInt_t
  RunPeriod::lastRun() const
  {
    return lastRun_;
  }

  double
  RunPeriod::luminosity() const
  {
    return luminosity_;
  }

  bool
  isLaterRunPeriod(const RunPeriod & runPeriod1,
                   const RunPeriod & runPeriod2)
  {
    if((runPeriod1.firstRun() > runPeriod2.firstRun() && runPeriod1.firstRun() < runPeriod2.lastRun()) ||
       (runPeriod1.lastRun()  > runPeriod2.firstRun() && runPeriod1.lastRun()  < runPeriod2.lastRun())  )
    {
      throw cmsException(__func__, __LINE__)
        << "Run periods '" << runPeriod1.name() << "' and '" << runPeriod2.name() << "' must not overlap !!\n"
      ;
    }
    return runPeriod1.firstRun() < runPeriod2.firstRun();
  }
}

EvtYieldHistManager::EvtYieldHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  const edm::ParameterSet cfg_runPeriods = cfg.getParameterSet("runPeriods");
  const std::vector<std::string> runPeriodNames = cfg_runPeriods.getParameterNames();
  for(const std::string & runPeriodName: runPeriodNames)
  {
    const edm::ParameterSet cfg_runPeriod = cfg_runPeriods.getParameter<edm::ParameterSet>(runPeriodName);
    runPeriods_.push_back(evtYieldHistManager::RunPeriod(runPeriodName, cfg_runPeriod));
  }
  std::sort(runPeriods_.begin(), runPeriods_.end(), evtYieldHistManager::isLaterRunPeriod);
  if(runPeriods_.empty())
  {
    throw cmsException(this) << "Invalid Configuration parameter 'runPeriods' !!\n";
  }
  isMC_ = cfg.getParameter<bool>("isMC");
}

void
EvtYieldHistManager::bookHistograms(TFileDirectory & dir)
{
  const std::size_t numRunPeriods = runPeriods_.size();
  assert(numRunPeriods >= 1);
  std::vector<double> binning;
  binning.push_back(runPeriods_[0].firstRun() - 0.5);
  for(std::size_t idxRunPeriod = 0; idxRunPeriod < numRunPeriods - 1; ++idxRunPeriod)
  {
    binning.push_back(0.5*(runPeriods_[idxRunPeriod].lastRun() + runPeriods_[idxRunPeriod + 1].firstRun()));
  }
  binning.push_back(runPeriods_[numRunPeriods - 1].lastRun() + 0.5);

  histogram_evtYield_   = book1D(dir, "evtYield",   "evtYield",   numRunPeriods, binning.data());
  histogram_luminosity_ = book1D(dir, "luminosity", "luminosity", numRunPeriods, binning.data());

  for(std::size_t idxRunPeriod = 0; idxRunPeriod < numRunPeriods; ++idxRunPeriod)
  {
    const int idxBin = idxRunPeriod + 1;
    histogram_evtYield_->GetXaxis()->SetBinLabel(idxBin, runPeriods_[idxRunPeriod].name().data());
    histogram_luminosity_->SetBinContent(idxBin, runPeriods_[idxRunPeriod].luminosity());
    histogram_luminosity_->GetXaxis()->SetBinLabel(idxBin, runPeriods_[idxRunPeriod].name().data());
  }
}

void
EvtYieldHistManager:: fillHistograms(const EventInfo & eventInfo,
                                     double evtWeight)
{
  int idxBin_run = -1;
  if ( isMC_ ) {
    while ( !(idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX()) ) {
      double run_mc = histogram_luminosity_->GetRandom();
      //std::cout << "run_mc = " << run_mc << std::endl;
      idxBin_run = histogram_luminosity_->FindBin(run_mc);
    }
  } else {
    idxBin_run = histogram_luminosity_->FindBin(eventInfo.run);
    if(! (idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX()))
    {
      throw cmsException(this, __func__, __LINE__) << "No luminosity defined for run = " << eventInfo.run << " !!\n";
    }
  }
  assert(idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX());
  //std::cout << "runPeriod = " << histogram_luminosity_->GetXaxis()->GetBinLabel(idxBin_run) << std::endl;
  double luminosity = histogram_luminosity_->GetBinContent(idxBin_run);
  assert(luminosity > 0.);
  histogram_evtYield_->Fill(eventInfo.run, evtWeight/luminosity);
}
