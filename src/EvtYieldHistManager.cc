#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TArrayD.h>

#include <algorithm> // std::sort

EvtYieldHistManager::EvtYieldHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  edm::ParameterSet cfg_runPeriods = cfg.getParameter<edm::ParameterSet>("runPeriods");
  std::vector<std::string> runPeriodNames = cfg_runPeriods.getParameterNames();
  for ( std::vector<std::string>::const_iterator runPeriodName = runPeriodNames.begin();
	runPeriodName != runPeriodNames.end(); ++runPeriodName ) {
    edm::ParameterSet cfg_runPeriod = cfg_runPeriods.getParameter<edm::ParameterSet>(*runPeriodName);
    runPeriods_.push_back(evtYieldHistManager::RunPeriod(*runPeriodName, cfg_runPeriod));
  }
  std::sort(runPeriods_.begin(), runPeriods_.end(), evtYieldHistManager::isLaterRunPeriod);
  if ( !(runPeriods_.size() >= 1) ) 
    throw cmsException(this)
      << "Invalid Configuration parameter 'runPeriods' !!\n";
}

void EvtYieldHistManager::bookHistograms(TFileDirectory & dir)
{
  size_t numRunPeriods = runPeriods_.size();
  assert(numRunPeriods >= 1);
  TArrayD binning(numRunPeriods);
  for ( size_t idxRunPeriod = 0; idxRunPeriod < numRunPeriods; ++idxRunPeriod ) {
    if      ( idxRunPeriod == 0                   ) binning[idxRunPeriod]     = runPeriods_[idxRunPeriod].firstRun() - 0.5;
    else if ( idxRunPeriod <  (numRunPeriods - 1) ) binning[idxRunPeriod]     = 0.5*(runPeriods_[idxRunPeriod].lastRun() + runPeriods_[idxRunPeriod + 1].firstRun());
    else if ( idxRunPeriod == (numRunPeriods - 1) ) binning[idxRunPeriod + 1] = runPeriods_[idxRunPeriod].lastRun() + 0.5;
  }

  histogram_evtYield_ = book1D(dir, "evtYield",   "evtYield",   numRunPeriods, binning.GetArray());
  histogram_luminosity_ = book1D(dir, "luminosity", "luminosity", numRunPeriods, binning.GetArray());

  for ( size_t idxRunPeriod = 0; idxRunPeriod < numRunPeriods; ++idxRunPeriod ) {
    int idxBin = idxRunPeriod + 1;
    histogram_evtYield_->GetXaxis()->SetBinLabel(idxBin, runPeriods_[idxRunPeriod].name().data());
    histogram_luminosity_->SetBinContent(idxBin, runPeriods_[idxRunPeriod].luminosity());
    histogram_luminosity_->GetXaxis()->SetBinLabel(idxBin, runPeriods_[idxRunPeriod].name().data());
  }
}

void
EvtYieldHistManager:: fillHistograms(const EventInfo& eventInfo,
				     double evtWeight)
{
  int idxBin_run = histogram_luminosity_->FindBin(eventInfo.run);
  if ( !(idxBin_run >= 1 && idxBin_run <= histogram_luminosity_->GetNbinsX()) )
    throw cmsException(this)
      << "No luminosity defined for run = " << eventInfo.run << " !!\n";
  double luminosity = histogram_luminosity_->GetBinContent(idxBin_run);
  assert(luminosity > 0.);
  histogram_evtYield_->Fill(eventInfo.run, evtWeight/luminosity);
}
