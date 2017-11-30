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

  // CV: call enableBDTTransform if using XML files converted from xgboost trainings,
  //     call disableBDTTransform if using XML files trained with TMVA
  void enableBDTTransform() { isBDTTransform_ = true; }
  void disableBDTTransform() { isBDTTransform_ = false; }

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

  bool isBDTTransform_;

  mutable std::map<std::string, Float_t> mvaInputVariables_; // key = MVA input variable name
  mutable std::map<std::string, Float_t> spectators_; // we do not really care about variables declared as "spectators" during TMVA training, but TMVA requires that we keep track of these variables...
};

#endif // TMVAInterface_h
