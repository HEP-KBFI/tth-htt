#ifndef tthAnalysis_HiggsToTauTau_TMVAInterface_OddEven_h
#define tthAnalysis_HiggsToTauTau_TMVAInterface_OddEven_h 

#include <Rtypes.h> // Float_t

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<,>

// forward declarations
namespace TMVA
{
  class Reader;
}

class TMVAInterface_OddEven
{
public:
  TMVAInterface_OddEven(const std::string & mvaFileName_Odd, 
			const std::string & mvaFileName_Even,
			const std::vector<std::string> & mvaInputVariables,
			const std::vector<std::string> & spectators = {});
  ~TMVAInterface_OddEven();

  // CV: call enableBDTTransform if using XML files converted from xgboost trainings,
  //     call disableBDTTransform if using XML files trained with TMVA
  void enableBDTTransform();
  void disableBDTTransform();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs: Values of MVA input variables (stored in std::map with key = MVA input variable name), EventNumber: event number
   * @return          MVA output
   */
  double
    operator()(const std::map<std::string, double> & mvaInputs, const int & EventNumber) const;

private:
  std::string mvaFileName_Odd_;
  std::string mvaFileName_Even_;
  TMVA::Reader * mva_Odd_;
  TMVA::Reader * mva_Even_;
  bool isBDTTransform_;
  mutable std::map<std::string, Float_t> mvaInputVariables_; // key = MVA input variable name
  // we do not really care about variables declared as "spectators" during TMVA training,
  // but TMVA requires that we keep track of these variables...
  mutable std::map<std::string, Float_t> spectators_;
};

#endif // TMVAInterface_OddEven

