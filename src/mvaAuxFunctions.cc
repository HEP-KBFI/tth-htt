#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h"

#include <TMath.h> // IsNaN

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <set> // std::set<>

void check_mvaInputs(std::map<std::string, double>& mvaInputs, RUN_TYPE run, LUMI_TYPE lumi, EVT_TYPE event)
{
  int index = 1;
  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
	mvaInput != mvaInputs.end(); ++mvaInput ) {
    if ( TMath::IsNaN(mvaInput->second) ) {
      std::cout << "Warning";
      if ( !(run == 0 && lumi == 0 && event == 0) ) {
	std::cout << " in run = " << run << ", lumi = " << lumi << ", event = " << event;
      }
      std::cout << ":" << std::endl; 
      std::cout << " mvaInput #" << index << " ('" << mvaInput->first << "') = " << mvaInput->second << " --> setting mvaInput value to zero !!" << std::endl; 
      mvaInputs[mvaInput->first] = 0.;
      ++index;
    }
  }
}

std::vector<std::string> get_mvaInputVariables(const std::vector<std::string>& mvaInputVariables_ttV, const std::vector<std::string>& mvaInputVariables_ttbar)
{
  std::set<std::string> mvaInputVariables_set;
  mvaInputVariables_set.insert(mvaInputVariables_ttV.begin(), mvaInputVariables_ttV.end());
  mvaInputVariables_set.insert(mvaInputVariables_ttbar.begin(), mvaInputVariables_ttbar.end());
  std::vector<std::string> mvaInputVariables(mvaInputVariables_set.begin(), mvaInputVariables_set.end());
  return mvaInputVariables;
}
