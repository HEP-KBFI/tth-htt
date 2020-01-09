#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h" // MVAInputVarTransformer

#include <boost/filesystem.hpp> // boost::filesystem::

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()
#include <iostream>

XGBInterface::XGBInterface(const std::string & mvaFileName,
                           const std::vector<std::string> & mvaInputVariables)
  : mode_(Mode::k_old)
  , mvaFileName_(LocalFileInPath(mvaFileName).fullPath())
  , pkldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , mvaFileName_odd_("")
  , pkldata_odd_(nullptr)
  , moduleMainString_odd_(nullptr)
  , moduleMain_odd_(nullptr)
  , mvaFileName_even_("")
  , pkldata_even_(nullptr)
  , moduleMainString_even_(nullptr)
  , moduleMain_even_(nullptr)
  , mvaInputVariables_(mvaInputVariables)
  , Transform_Ptr_(nullptr)
  , fitFunctionFileName_("")
{
  if(mode_ != Mode::k_old)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

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

XGBInterface::XGBInterface(const std::string & mvaFileName_odd,
                           const std::string & mvaFileName_even,
                           const std::vector<std::string> & mvaInputVariables)
  : mode_(Mode::k_odd_even)
  , mvaFileName_("")
  , pkldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , mvaFileName_odd_(LocalFileInPath(mvaFileName_odd).fullPath())
  , pkldata_odd_(nullptr)
  , moduleMainString_odd_(nullptr)
  , moduleMain_odd_(nullptr)
  , mvaFileName_even_(LocalFileInPath(mvaFileName_even).fullPath())
  , pkldata_even_(nullptr)
  , moduleMainString_even_(nullptr)
  , moduleMain_even_(nullptr)
  , mvaInputVariables_(mvaInputVariables)
  , Transform_Ptr_(nullptr)
  , fitFunctionFileName_("")
{
  if(mode_ != Mode::k_odd_even)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

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
  // moduleMainString_ = PyString_FromString("__main__");
  // moduleMain_ = PyImport_Import(moduleMainString_);

  moduleMainString_odd_ = PyString_FromString("__main__");
  moduleMain_odd_ = PyImport_Import(moduleMainString_odd_);

  moduleMainString_even_ = PyString_FromString("__main__");
  moduleMain_even_ = PyImport_Import(moduleMainString_even_);

  PyRun_SimpleString(applicationLoadStr.c_str());

  //PyObject* func = PyObject_GetAttrString(moduleMain_, "load");
  //PyObject* args = PyTuple_Pack(1, PyString_FromString(mvaFileName_.data()));
  //pkldata_ = PyObject_CallObject(func, args);

  PyObject * func_odd = PyObject_GetAttrString(moduleMain_odd_, "load");
  PyObject * args_odd = PyTuple_Pack(1, PyString_FromString(mvaFileName_odd_.data()));
  pkldata_odd_ = PyObject_CallObject(func_odd, args_odd);

  PyObject * func_even = PyObject_GetAttrString(moduleMain_even_, "load");
  PyObject * args_even = PyTuple_Pack(1, PyString_FromString(mvaFileName_even_.data()));
  pkldata_even_ = PyObject_CallObject(func_even, args_even);

  //Py_XDECREF(func);
  //Py_XDECREF(args);

  Py_XDECREF(func_odd);
  Py_XDECREF(args_odd);

  Py_XDECREF(func_even);
  Py_XDECREF(args_even);
}

XGBInterface::XGBInterface(const std::string & mvaFileName,
                           const std::vector<std::string> & mvaInputVariables,
                           const std::string & fitFunctionFileName)
  : mode_(Mode::k_old)
  , mvaFileName_(LocalFileInPath(mvaFileName).fullPath())
  , pkldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , mvaFileName_odd_("")
  , pkldata_odd_(nullptr)
  , moduleMainString_odd_(nullptr)
  , moduleMain_odd_(nullptr)
  , mvaFileName_even_("")
  , pkldata_even_(nullptr)
  , moduleMainString_even_(nullptr)
  , moduleMain_even_(nullptr)
  , mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(LocalFileInPath(fitFunctionFileName).fullPath())
{
  if(mode_ != Mode::k_old)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  if (fitFunctionFileName_ != ""){
    Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables, fitFunctionFileName_); // Intializing the new map
  }

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
  PyObject * func = PyObject_GetAttrString(moduleMain_, "load");
  PyObject * args = PyTuple_Pack(1, PyString_FromString(mvaFileName_.data()));
  pkldata_ = PyObject_CallObject(func, args);

  Py_XDECREF(func);
  Py_XDECREF(args);
}

XGBInterface::XGBInterface(const std::string & mvaFileName_odd,
                           const std::string & mvaFileName_even,
                           const std::string & fitFunctionFileName,
                           const std::vector<std::string> & mvaInputVariables)
  : mode_(Mode::k_odd_even)
  , mvaFileName_("")
  , pkldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , mvaFileName_odd_(LocalFileInPath(mvaFileName_odd).fullPath())
  , pkldata_odd_(nullptr)
  , moduleMainString_odd_(nullptr)
  , moduleMain_odd_(nullptr)
  , mvaFileName_even_(LocalFileInPath(mvaFileName_even).fullPath())
  , pkldata_even_(nullptr)
  , moduleMainString_even_(nullptr)
  , moduleMain_even_(nullptr)
  , mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(LocalFileInPath(fitFunctionFileName).fullPath())
{
  if(mode_ != Mode::k_odd_even)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  if (fitFunctionFileName_ != "") {
    Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables, fitFunctionFileName_); // Intializing the new map
  }

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
  // moduleMainString_ = PyString_FromString("__main__");
  // moduleMain_ = PyImport_Import(moduleMainString_);

  moduleMainString_odd_ = PyString_FromString("__main__");
  moduleMain_odd_ = PyImport_Import(moduleMainString_odd_);

  moduleMainString_even_ = PyString_FromString("__main__");
  moduleMain_even_ = PyImport_Import(moduleMainString_even_);

  PyRun_SimpleString(applicationLoadStr.c_str());

  //PyObject* func = PyObject_GetAttrString(moduleMain_, "load");
  //PyObject* args = PyTuple_Pack(1, PyString_FromString(mvaFileName_.data()));
  //pkldata_ = PyObject_CallObject(func, args);

  PyObject * func_odd = PyObject_GetAttrString(moduleMain_odd_, "load");
  PyObject * args_odd = PyTuple_Pack(1, PyString_FromString(mvaFileName_odd_.data()));
  pkldata_odd_ = PyObject_CallObject(func_odd, args_odd);

  PyObject * func_even = PyObject_GetAttrString(moduleMain_even_, "load");
  PyObject * args_even = PyTuple_Pack(1, PyString_FromString(mvaFileName_even_.data()));
  pkldata_even_ = PyObject_CallObject(func_even, args_even);

  //Py_XDECREF(func);
  //Py_XDECREF(args);

  Py_XDECREF(func_odd);
  Py_XDECREF(args_odd);

  Py_XDECREF(func_even);
  Py_XDECREF(args_even);
}


XGBInterface::~XGBInterface()
{
  Py_XDECREF(pkldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);

  Py_XDECREF(pkldata_odd_);
  Py_XDECREF(moduleMainString_odd_);
  Py_XDECREF(moduleMain_odd_);

  Py_XDECREF(pkldata_even_);
  Py_XDECREF(moduleMainString_even_);
  Py_XDECREF(moduleMain_even_);

  delete Transform_Ptr_;
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
XGBInterface::operator()(const std::map<std::string, double> & mvaInputs) const
{
  std::map<std::string, double> mvaInputs_final;

  if(fitFunctionFileName_ != "")
  {
    mvaInputs_final = Transform_Ptr_->TransformMVAInputVars(mvaInputs); // Re-weight Input Var.s
  }
  else
  {
    mvaInputs_final = mvaInputs;
  }

  std::vector<float> vectorValuesVec;
  std::vector<std::string> vectorNamesVec;

  for(const std::string & mvaInputVariable: mvaInputVariables_)
  {
    if(mvaInputs_final.count(mvaInputVariable))
    {
      vectorValuesVec.push_back(mvaInputs_final.at(mvaInputVariable));
      vectorNamesVec.push_back(mvaInputVariable);
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << mvaInputVariable << '\''
      ;
    }
  }

  PyObject * func = PyObject_GetAttrString(moduleMain_, "evaluate");
  PyObject * vectorValues = vectorToTuple_Float(vectorValuesVec);
  PyObject * vecNames = vectorToTuple_String(vectorNamesVec);
  PyObject * args = PyTuple_Pack(3, vectorValues, vecNames, pkldata_);
  PyObject * result = PyObject_CallObject(func, args);
  const double mvaOutput = PyFloat_AsDouble(result);

  Py_XDECREF(func);
  Py_XDECREF(vectorValues);
  Py_XDECREF(vecNames);
  Py_XDECREF(args);
  Py_XDECREF(result);

  //std::cout << "XGB: mvaOutput " << mvaOutput << '\n';
  return mvaOutput;
}

double
XGBInterface::operator()(const std::map<std::string, double> & mvaInputs,
                         int event_number) const
{
  std::map<std::string, double> mvaInputs_final;

  if(fitFunctionFileName_ != "")
  {
    mvaInputs_final = Transform_Ptr_->TransformMVAInputVars(mvaInputs); // Re-weight Input Var.s
  }
  else
  {
    mvaInputs_final = mvaInputs;
  }

  std::vector<float> vectorValuesVec;
  std::vector<std::string> vectorNamesVec;

  for(const std::string & mvaInputVariable: mvaInputVariables_)
  {
    if(mvaInputs_final.count(mvaInputVariable))
    {
      vectorValuesVec.push_back(mvaInputs_final.at(mvaInputVariable));
      vectorNamesVec.push_back(mvaInputVariable);
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << mvaInputVariable << '\''
      ;
    }
  }

  PyObject * vectorValues = vectorToTuple_Float(vectorValuesVec);
  PyObject * vecNames = vectorToTuple_String(vectorNamesVec);
  PyObject * func = nullptr;
  PyObject * args = nullptr;

  if(event_number % 2)
  {
    func = PyObject_GetAttrString(moduleMain_odd_, "evaluate");
    args = PyTuple_Pack(3, vectorValues, vecNames, pkldata_odd_);
  }
  else
  {
    func = PyObject_GetAttrString(moduleMain_even_, "evaluate");
    args = PyTuple_Pack(3, vectorValues, vecNames, pkldata_even_);
  }

  PyObject * result = PyObject_CallObject(func, args);
  const double mvaOutput = PyFloat_AsDouble(result);

  Py_XDECREF(vectorValues);
  Py_XDECREF(vecNames);
  Py_XDECREF(func);
  Py_XDECREF(args);
  Py_XDECREF(result);

  //std::cout << "XGB: mvaOutput " << mvaOutput << '\n';
  return mvaOutput;
}
