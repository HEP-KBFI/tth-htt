#ifndef tthAnalysis_HiggsToTauTau_XGBInterface_h
#define tthAnalysis_HiggsToTauTau_XGBInterface_h

#include <Python.h> // PyObject
#include <vector> // std::vector<>
#include <string> // std::string
#include <map> // std::map<,>

#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h"

class XGBInterface
{
public:
  XGBInterface(const std::string & mvaFileName,
               const std::vector<std::string> & mvaInputVariables);
  XGBInterface(const std::string & mvaFileName_odd,
	       const std::string & mvaFileName_even,
               const std::vector<std::string> & mvaInputVariables);
  XGBInterface(const std::string & mvaFileName,
               const std::vector<std::string> & mvaInputVariables,
	       const std::string & fitFunctionFileName);
  XGBInterface(const std::string & mvaFileName_odd,
	       const std::string & mvaFileName_even,
	       const std::string & fitFunctionFileName,
               const std::vector<std::string> & mvaInputVariables);
  ~XGBInterface();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  double
    operator()(const std::map<std::string, double> & mvaInputs) const;

  double
    operator()(const std::map<std::string, double> & mvaInputs, const int event_number) const;

private:
  enum Mode{k_old, k_odd_even};
  int mode_;
  std::string mvaFileName_;
  PyObject* pkldata_;
  PyObject* moduleMainString_;
  PyObject* moduleMain_;
  std::string mvaFileName_odd_;
  PyObject* pkldata_odd_;
  PyObject* moduleMainString_odd_;
  PyObject* moduleMain_odd_;
  std::string mvaFileName_even_;
  PyObject* pkldata_even_;
  PyObject* moduleMainString_even_;
  PyObject* moduleMain_even_;
  std::vector<std::string> mvaInputVariables_; // list of MVA input variables
  MVAInputVarTransformer* Transform_Ptr_;
  std::string fitFunctionFileName_;
};

#endif // XGBInterface_h
