#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <boost/filesystem.hpp> // boost::filesystem::

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()

XGBInterface::XGBInterface(const std::string & mvaFileName,
                           const std::vector<std::string> & mvaInputVariables)
  : mvaFileName_(LocalFileInPath(mvaFileName).fullPath())
  , mvaInputVariables_(mvaInputVariables)
{
  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  // read the python file that we're about to execute
  const std::string applicationLoadPath = (
    boost::filesystem::path(std::getenv("CMSSW_BASE")) /
    boost::filesystem::path("src/tthAnalysis/HiggsToTauTau/python/xgb/applicationLoad.py")
  ).string();
  std::ifstream applicationLoadFile(applicationLoadPath);
  std::string applicationLoadStr;

  applicationLoadFile.seekg(0, std::ios::end);
  applicationLoadStr.reserve(applicationLoadFile.tellg());
  applicationLoadFile.seekg(0, std::ios::beg);
  applicationLoadStr.assign(std::istreambuf_iterator<char>(applicationLoadFile), std::istreambuf_iterator<char>());

  // https://ubuntuforums.org/archive/index.php/t-324544.html
  // https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
  // https://gist.github.com/rjzak/5681680
  Py_SetProgramName(const_cast<char *>("applicationLoad"));
  moduleMainString_ = PyString_FromString("__main__");
  moduleMain_ = PyImport_Import(moduleMainString_);
  PyRun_SimpleString(applicationLoadStr.c_str());
  PyObject* func = PyObject_GetAttrString(moduleMain_, "load");
  PyObject* args = PyTuple_Pack(1, PyString_FromString(mvaFileName_.data()));
  pkldata_ = PyObject_CallObject(func, args);

  Py_XDECREF(func);
  Py_XDECREF(args);
}

XGBInterface::~XGBInterface()
{
  Py_XDECREF(pkldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);
}

namespace
{
  // https://gist.github.com/rjzak/5681680
  PyObject *
  vectorToTuple_Float(const std::vector<float> & data)
  {
    PyObject * tuple = PyTuple_New(data.size());
    if(! tuple)
    {
      throw std::logic_error("Unable to allocate memory for Python tuple");
    }

    for(unsigned int i = 0; i < data.size(); ++i)
    {
      PyObject * num = PyFloat_FromDouble(static_cast<double>(data[i]));
      if(! num)
      {
        Py_XDECREF(tuple);
        throw cms::Exception("vectorToTuple_Float") << "Unable to allocate memory for Python tuple!";
      }
      PyTuple_SET_ITEM(tuple, i, num);
    }
    return tuple;
  }

  PyObject *
  vectorToTuple_String(const std::vector<std::string> & data)
  {
    PyObject * tuple = PyTuple_New(data.size());
    if(! tuple)
    {
      throw std::logic_error("Unable to allocate memory for Python tuple");
    }

    for(unsigned int i = 0; i < data.size(); ++i)
    {
      PyObject * num = PyString_FromString(data[i].c_str());
      if(! num)
      {
        Py_XDECREF(tuple);
        throw cms::Exception("vectorToTuple_String") << "Unable to allocate memory for Python tuple!";
      }
      PyTuple_SET_ITEM(tuple, i, num);
    }
    return tuple;
  }
}

double
XGBInterface::operator()(const std::map<std::string, double>& mvaInputs) const
{
  std::vector<float> vectorValuesVec;
  std::vector<std::string> vectorNamesVec;

  for(const std::string & mvaInputVariable: mvaInputVariables_)
  {
    if(mvaInputs.count(mvaInputVariable))
    {
      vectorValuesVec.push_back(mvaInputs.at(mvaInputVariable));
      vectorNamesVec.push_back(mvaInputVariable);
    }
    else
    {
      throw cms::Exception("XGBInterface::operator()")
        << "Missing value for MVA input variable = '" << mvaInputVariable << "' !!\n";
    }
  }

  PyObject* func = PyObject_GetAttrString(moduleMain_, "evaluate");
  PyObject* vectorValues = vectorToTuple_Float(vectorValuesVec);
  PyObject* vecNames = vectorToTuple_String(vectorNamesVec);
  PyObject* args = PyTuple_Pack(3, vectorValues, vecNames, pkldata_);
  PyObject* result = PyObject_CallObject(func, args);
  const double mvaOutput = PyFloat_AsDouble(result);

  Py_XDECREF(func);
  Py_XDECREF(vectorValues);
  Py_XDECREF(vecNames);
  Py_XDECREF(args);
  Py_XDECREF(result);

  return mvaOutput;
}
