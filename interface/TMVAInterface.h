#ifndef tthAnalysis_HiggsToTauTau_TMVAInterface_h
#define tthAnalysis_HiggsToTauTau_TMVAInterface_h 

#include <Rtypes.h> // Float_t

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<,>

// forward declarations
namespace TMVA
{
  class Reader;
}
class MVAInputVarTransformer;

class TMVAInterface
{
public:
  TMVAInterface(const std::string & mvaFileName,
                const std::vector<std::string> & mvaInputVariables,
                const std::vector<std::string> & spectators = {});
  TMVAInterface(const std::string & mvaFileName_odd,
                const std::string & mvaFileName_even,
                const std::vector<std::string> & mvaInputVariables,
                const std::vector<std::string> & spectators = {});
  TMVAInterface(const std::string & mvaFileName,
                const std::vector<std::string> & mvaInputVariables,
                const std::string & fitFunctionFileName,
                const std::vector<std::string> & spectators = {});
  TMVAInterface(const std::string & mvaFileName_odd,
                const std::string & mvaFileName_even,
                const std::vector<std::string> & mvaInputVariables,
                const std::string & fitFunctionFileName,
                const std::vector<std::string> & spectators = {});
  ~TMVAInterface();

  // CV: call enableBDTTransform if using XML files converted from xgboost trainings,
  //     call disableBDTTransform if using XML files trained with TMVA
  void enableBDTTransform();
  void disableBDTTransform();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */

  double
  operator()(const std::map<std::string, double> & mvaInputs) const;

  double
  operator()(const std::map<std::string, double> & mvaInputs,
             int event_number, const bool multiclass = false) const;

  double 
  operator()(const std::map<std::string, double> & mvaInputs,
             const TMVA::Reader * mva, const bool multiclass = false) const;

  /**
   * @brief Returns output of multi-class MVA (used for debugging/synchronization purposes).
   */
  const std::vector<float>& 
  mvamulticlsOutput() const;

private:
  enum Mode{
    k_old, k_odd_even
  };
  int mode_;
  std::string mvaFileName_;
  TMVA::Reader * mva_;
  std::string mvaFileName_odd_;
  TMVA::Reader * mva_odd_;
  std::string mvaFileName_even_;
  TMVA::Reader * mva_even_;
  bool isBDTTransform_;
  mutable std::map<std::string, Float_t> mvaInputVariables_; // key = MVA input variable name
  // we do not really care about variables declared as "spectators" during TMVA training,
  // but TMVA requires that we keep track of these variables ...
  mutable std::map<std::string, Float_t> spectators_;
  std::string fitFunctionFileName_;
  MVAInputVarTransformer * Transform_Ptr_;
  mutable std::vector<float> mvamulticlsOutput_;
};

#endif // TMVAInterface_h
