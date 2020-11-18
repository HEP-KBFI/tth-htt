#ifndef tthAnalysis_HiggsToTauTau_TensorFlowInterfaceLBN_h
#define tthAnalysis_HiggsToTauTau_TensorFlowInterfaceLBN_h

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
class Particle;

class TensorFlowInterfaceLBN
{
public:
  TensorFlowInterfaceLBN(const std::string & mvaFileName_odd,
                         const std::vector<std::string> & ll_particleNames,
                         const std::vector<std::string> & hl_mvaInputVariables,
                         const std::vector<std::string> & classes,
                         const std::string & mvaFileName_even = "",
                         bool isDEBUG = false);
  ~TensorFlowInterfaceLBN();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<std::string, double>
  operator()(const std::map<std::string, const Particle*> & ll_particles,
             const std::map<std::string, double> & hl_mvaInputs,
             int event_number = -1) const;

  /**
   * @brief Return list of low-level MVA input variables / particle names
   */
  const std::vector<std::string> &
  ll_particleNames() const;

  /**
   * @brief Return list of high-level MVA input variables
   */
  const std::vector<std::string> &
  hl_mvaInputVariables() const;

private:
  const std::vector<std::string> classes_;
  std::string mvaFileName_odd_;
  tensorflow::GraphDef * graphDef_odd_;
  tensorflow::Session * session_odd_;
  std::string input_layer_name_odd;
  std::string output_layer_name_odd;

  std::string mvaFileName_even_;
  tensorflow::GraphDef * graphDef_even_;
  tensorflow::Session * session_even_;
  std::string input_layer_name_even;
  std::string output_layer_name_even;

  std::vector<std::string> ll_particleNames_;
  std::vector<std::string> hl_mvaInputVariables_;

  bool isDEBUG_;
};

#endif // TensorFlowInterfaceLBN_h
