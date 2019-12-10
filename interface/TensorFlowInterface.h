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
class MVAInputVarTransformer;

class TensorFlowInterface
{
public:
  TensorFlowInterface(const std::string & mvaFileName_odd,
                      const std::vector<std::string> & mvaInputVariables,
                      const std::vector<std::string> classes,
                      const std::string & mvaFileName_even = "",
                      const std::string & fitFunctionFileName = "");
  ~TensorFlowInterface();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<std::string, double>
  operator()(const std::map<std::string, double> & mvaInputs,
             int event_number = -1) const;


private:
  const std::vector<std::string> classes_;
  std::string mvaFileName_odd_;
  tensorflow::GraphDef * graphDef_odd_;
  tensorflow::Session * session_odd_;
  std::string input_layer_name_odd;
  std::string output_layer_name_odd;
  int n_input_layer_odd;
  int n_output_layer_odd;

  std::string mvaFileName_even_;
  tensorflow::GraphDef * graphDef_even_;
  tensorflow::Session * session_even_;
  std::string input_layer_name_even;
  std::string output_layer_name_even;
  int n_input_layer_even;
  int n_output_layer_even;

  std::vector<std::string>  mvaInputVariables_; // key = MVA input variable name
  // we do not really care about variables declared as "spectators" during TMVA training,
  // but TMVA requires that we keep track of these variables...
  mutable std::map<std::string, Float_t> spectators_;
  std::string fitFunctionFileName_;
  MVAInputVarTransformer * Transform_Ptr_;

  bool isDEBUG_;
};

#endif // TensorFlowInterface_h
