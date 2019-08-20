#ifndef tthAnalysis_HiggsToTauTau_MVAInputVarTransformer_h
#define tthAnalysis_HiggsToTauTau_MVAInputVarTransformer_h

#include <TF1.h>

class MVAInputVarTransformer
{
 public:
  MVAInputVarTransformer(const std::vector<std::string> & mvaInputVariables,
                         const std::string & fitFunctionFileName);
  ~MVAInputVarTransformer(); 

  /*                                                                                                                                                                                                    
   * @brief Extracts fitvalues from the fitFunctionFile, scales the Input Variables before they are fed into the BDT  
   * @param Names of MVA input variables (stored in std::vector<std::string> ), Full Name (with Path) to the fitFunctionFile (as std::string) 
   * @return Re-scaled mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   */
  std::map<std::string, double>
  TransformMVAInputVars(const std::map<std::string, double> & mvaInputs) const;


 private:
  std::vector<std::string> mvaInputVariables_;
  std::string fitFunctionFileName_;
  std::map<std::string, TF1 *> fitFuncMap_;
  mutable std::map<std::string, double> mvaInputs_reweighted_;
};

#endif // MVAInputVarTransformer_h  
