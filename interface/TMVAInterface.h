#ifndef tthAnalysis_HiggsToTauTau_TMVAInterface_h
#define tthAnalysis_HiggsToTauTau_TMVAInterface_h

#include "TMVA/Reader.h"
#include <TROOT.h> // for Float_t

#include <vector>
#include <string>

class TMVAInterface
{
 public:
  TMVAInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables, const std::vector<std::string>& spectators);
  ~TMVAInterface();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  double
  operator()(const std::map<std::string, double>& mvaInputs) const;

 private:
  TMVA::Reader* mva_;

  mutable std::map<std::string, Float_t> mvaInputVariables_; // key = MVA input variable name
  mutable std::map<std::string, Float_t> spectators_; // we do not really care about variables declared as "spectators" during TMVA training, but TMVA requires that we keep track of these variables...
};

#endif // TMVAInterface_h
