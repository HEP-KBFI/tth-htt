#ifndef tthAnalysis_HiggsToTauTau_TMVAInterface_h
#define tthAnalysis_HiggsToTauTau_TMVAInterface_h

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE  

#include "TMVA/Reader.h"
#include <TROOT.h> // for Float_t
#include <TMath.h> 

#include <vector>
#include <string>

class TMVAInterface
{
 public:
  TMVAInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables, const std::vector<std::string>& spectators = {});
  ~TMVAInterface();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  double
  operator()(const std::map<std::string, double>& mvaInputs) const;

 private:
  std::string mvaFileName_;

  TMVA::Reader* mva_;

  mutable std::map<std::string, Float_t> mvaInputVariables_; // key = MVA input variable name
  mutable std::map<std::string, Float_t> spectators_; // we do not really care about variables declared as "spectators" during TMVA training, but TMVA requires that we keep track of these variables...
};

void checkInputs(std::map<std::string, double>& mvaInputs, RUN_TYPE run, LUMI_TYPE lumi, EVT_TYPE event)
{
  int index = 1;
  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs.begin();
	mvaInput != mvaInputs.end(); ++mvaInput ) {
    if ( TMath::IsNaN(mvaInput->second) ) {
      std::cout << "Warning in run = " << run << ", lumi = " << lumi << ", event = " << event << ":" << std::endl; 
      std::cout << " mvaInput #" << index << " ('" << mvaInput->first << "') = " << mvaInput->second << " --> setting mvaInput value to zero !!" << std::endl; 
      mvaInputs[mvaInput->first] = 0.;
      ++index;
    }
  }
}

#endif // TMVAInterface_h
