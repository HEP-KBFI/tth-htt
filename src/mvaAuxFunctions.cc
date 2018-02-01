#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h"

#include <TMath.h> // IsNaN()

#include <set> // std::set<>

void
check_mvaInputs(std::map<std::string, double> & mvaInputs,
                UInt_t run,
                UInt_t lumi,
                ULong64_t event)
{
  int index = 1;
  for(const auto & mvaInput: mvaInputs)
  {
    if(TMath::IsNaN(mvaInput.second))
    {
      std::cout << "Warning";
      if(! (run == 0 && lumi == 0 && event == 0))
      {
        std::cout << " in run = " << run << ", lumi = " << lumi << ", event = " << event;
      }
      std::cout << ":\n mvaInput #" << index << " ('" << mvaInput.first << "') = "
                << mvaInput.second << " --> setting mvaInput value to zero !!\n";
      mvaInputs[mvaInput.first] = 0.;
      ++index;
    }
  }
}

void
check_mvaInputs(std::map<std::string, double> & mvaInputs,
                const EventInfo & info)
{
  return check_mvaInputs(mvaInputs, info.run, info.lumi, info.event);
}

std::vector<std::string>
get_mvaInputVariables(const std::vector<std::string> & mvaInputVariables_ttV,
                      const std::vector<std::string> & mvaInputVariables_ttbar)
{
  std::set<std::string> mvaInputVariables_set;
  mvaInputVariables_set.insert(mvaInputVariables_ttV.begin(),   mvaInputVariables_ttV.end());
  mvaInputVariables_set.insert(mvaInputVariables_ttbar.begin(), mvaInputVariables_ttbar.end());
  std::vector<std::string> mvaInputVariables(mvaInputVariables_set.begin(), mvaInputVariables_set.end());
  return mvaInputVariables;
}
