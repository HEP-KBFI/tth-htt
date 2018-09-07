#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TPRegexp.h> // TPRegexp
#include <TRandom3.h> // TRandom3
#include <TMath.h> // TMath::BinarySearch()

#include <climits> // INT_MAX
#include <cassert> // assert()

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
      throw cmsException(this) << "Invalid Configuration parameter 'luminosity' = " << luminosity_ << "!!";
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
        << " ('" << firstRun_ << "' - '" << lastRun_ << "') !!"
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
        << "Run periods '" << runPeriod1.name() << "' and '" << runPeriod2.name() << "' must not overlap !!"
      ;
    }
    return runPeriod1.firstRun() < runPeriod2.firstRun();
  }

  TRandomTH1::TRandomTH1()
    : TRandomTH1(nullptr)
  {}

  TRandomTH1::TRandomTH1(TH1 * histogram)
    : histogram_(histogram)
    , integral_(0.)
    , integral_array_(nullptr)
    , nbinsx_(-1)
  {
    if(histogram_)
    {
      if(histogram_->GetDimension() > 1)
      {
        throw cmsException(this) << "Function only valid for 1-d histograms";
      }
      integral_ = histogram_->ComputeIntegral(true);
      integral_array_ = histogram_->GetIntegral();
      nbinsx_ = histogram_->GetNbinsX();

      if(std::isnan(integral_))
      {
        throw cmsException(this) << "Integral NaN";
      }
      if(integral_ <= 0.)
      {
        throw cmsException(this) << "Integral not positive: " << integral_;
      }
      if(! integral_array_)
      {
        throw cmsException(this) << "Integral array not initialized properly";
      }
      if(nbinsx_ < 1)
      {
        throw cmsException(this) << "Invalid number of bins: " << nbinsx_;
      }
    }
  }

  Double_t
  TRandomTH1::GetRandom(ULong64_t seed) const
  {
    if(histogram_)
    {
      assert(! std::isnan(integral_) && integral_ > 0. && integral_array_ && nbinsx_ > 0);

      TRandom3 rnd;
      const ULong_t seed_ = seed & UINT_MAX; // keep the lower bits
      rnd.SetSeed(seed_); // keep the lower bits
      const Double_t r1 = rnd.Rndm();

      const Int_t ibin = TMath::BinarySearch(nbinsx_, integral_array_, r1);
      Double_t x = histogram_->GetBinLowEdge(ibin + 1);
      if(r1 > integral_array_[ibin])
      {
        x += histogram_->GetBinWidth(ibin+1) *
             (r1 - integral_array_[ibin]) /
             (integral_array_[ibin + 1] - integral_array_[ibin])
        ;
      }
      return x;
    }
    return 0.;
  }
}

EvtYieldHistManager::EvtYieldHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , isMC_(cfg.getParameter<bool>("isMC"))
  , histogram_evtYield_(nullptr)
  , histogram_luminosity_(nullptr)
  , histogram_rnd_(nullptr)
{
  const edm::ParameterSet cfg_runPeriods = cfg.getParameter<edm::ParameterSet>("runPeriods");
  const std::vector<std::string> runPeriodNames = cfg_runPeriods.getParameterNames();
  for(const std::string & runPeriodName: runPeriodNames)
  {
    const edm::ParameterSet cfg_runPeriod = cfg_runPeriods.getParameter<edm::ParameterSet>(runPeriodName);
    runPeriods_.push_back(evtYieldHistManager::RunPeriod(runPeriodName, cfg_runPeriod));
  }
  std::sort(runPeriods_.begin(), runPeriods_.end(), evtYieldHistManager::isLaterRunPeriod);
  if(runPeriods_.empty())
  {
    throw cmsException(this) << "Invalid Configuration parameter 'runPeriods' !!";
  }
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

  if(isMC_)
  {
    histogram_rnd_ = new evtYieldHistManager::TRandomTH1(histogram_luminosity_);
  }
}

void
EvtYieldHistManager:: fillHistograms(const EventInfo & eventInfo,
                                     double evtWeight)
{
  int idxBin_run = -1;
  double run = eventInfo.run;
  if(isMC_)
  {
    if(! (idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX()))
    {
      run = histogram_rnd_->GetRandom(eventInfo.event);
      idxBin_run = histogram_luminosity_->FindBin(run);
    }
  }
  else
  {
    idxBin_run = histogram_luminosity_->FindBin(run);
    if(! (idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX()))
    {
      throw cmsException(this, __func__, __LINE__) << "No luminosity defined for run = " << run << " !!";
    }
  }
  assert(idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX());
  const double luminosity = histogram_luminosity_->GetBinContent(idxBin_run);
  assert(luminosity > 0.);
  histogram_evtYield_->Fill(run, evtWeight / luminosity);
}
