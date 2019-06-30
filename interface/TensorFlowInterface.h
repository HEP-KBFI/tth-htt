#ifndef tthAnalysis_HiggsToTauTau_TensorFlowInterface_h
#define tthAnalysis_HiggsToTauTau_TensorFlowInterface_h

#include <Rtypes.h> // Float_t

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<,>

// forward declarations
namespace tensorflow
{
  class Reader;
  class GraphDef;
  class Session;
  class Status;
}

class TensorFlowInterface
{
public:
  TensorFlowInterface(const std::string & mvaFileName,
                      const std::vector<std::string> & mvaInputVariables,
                      const std::vector<std::string> classes,
                      const std::vector<double> & mvaInputVariables_mean = {},
                      const std::vector<double> & mvaInputVariables_var = {});
  ~TensorFlowInterface();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<std::string, double>
  operator()(const std::map<std::string, double> & mvaInputs) const;

private:
  std::string mvaFileName_;
  tensorflow::GraphDef * graphDef_;
  tensorflow::Session * session_;
  const std::vector<std::string> classes_;
  std::string input_layer_name;
  std::string output_layer_name;
  int n_input_layer;
  int n_output_layer;

  std::vector<std::string>  mvaInputVariables_; // key = MVA input variable name
  std::vector<double>  mvaInputVariables_mean_; // key = MVA input variable name
  std::vector<double>  mvaInputVariables_var_; // key = MVA input variable name
  // we do not really care about variables declared as "spectators" during TMVA training,
  // but TMVA requires that we keep track of these variables...
  mutable std::map<std::string, Float_t> spectators_;

  bool isDEBUG_;
};

#endif // TensorFlowInterface_h
