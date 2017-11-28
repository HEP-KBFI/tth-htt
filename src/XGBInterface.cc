#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" 

#include "FWCore/Utilities/interface/Exception.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"

#include <Python.h>

XGBInterface::XGBInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables)
  : mvaInputVariableNames_(mvaInputVariables)
{
  LocalFileInPath mvaFileName_fip(mvaFileName);
  mvaFileName_ = mvaFileName_fip.fullPath();
}

XGBInterface::~XGBInterface()
{}

namespace
{
  // https://gist.github.com/rjzak/5681680
  PyObject* vectorToTuple_Float(const std::vector<float>& data) 
  {
    PyObject* tuple = PyTuple_New( data.size() );
    if ( !tuple ) throw std::logic_error("Unable to allocate memory for Python tuple");
    for ( unsigned int i = 0; i < data.size(); i++ ) {
      PyObject* num = PyFloat_FromDouble((double)data[i]);
      if ( !num ) {
	Py_DECREF(tuple);
	throw cms::Exception("vectorToTuple_Float") << "Unable to allocate memory for Python tuple !!\n";
      }
      PyTuple_SET_ITEM(tuple, i, num);
    }
    return tuple;
  }
  
  PyObject* vectorToTuple_String(std::vector<std::basic_string<char>>& data) 
  {
    PyObject* tuple = PyTuple_New( data.size() );
    if ( !tuple ) throw std::logic_error("Unable to allocate memory for Python tuple");
    for (unsigned int i = 0; i < data.size(); i++ ) {
      PyObject* num = PyString_FromString((char*)data[i].c_str());
      if ( !num ) {
	Py_DECREF(tuple);
	throw cms::Exception("vectorToTuple_String") << "Unable to allocate memory for Python tuple !!\n";
      }
      PyTuple_SET_ITEM(tuple, i, num);
    }    
    return tuple;
  }
}

double
XGBInterface::operator()(const std::map<std::string, double>& mvaInputs) const
{
  //std::cout << "<XGBInterface::operator()>:" << std::endl;
  //std::cout << "mvaFileName = " << mvaFileName_ << std::endl;

  // prepare dictionary to pass to pyObject functions
  std::vector<float> vectorValuesVec;
  std::vector<std::basic_string<char>> vectorNamesVec;
  for ( std::vector<std::string>::const_iterator mvaInputVariableName = mvaInputVariableNames_.begin();
	mvaInputVariableName != mvaInputVariableNames_.end(); ++mvaInputVariableName ) {
    if ( mvaInputs.find(*mvaInputVariableName) != mvaInputs.end() ) {
      //std::cout << " " << (*mvaInputVariableName) << " = " << mvaInputs.find(*mvaInputVariableName)->second << std::endl;
      vectorValuesVec.push_back(mvaInputs.find(*mvaInputVariableName)->second);
      vectorNamesVec.push_back(*mvaInputVariableName);
    } else {
      throw cms::Exception("XGBInterface::operator()")
	<< "Missing value for MVA input variable = '" << (*mvaInputVariableName) << "' !!\n";
    }
  }
  
  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  // https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
  Py_SetProgramName((char*) "application");
  PyObject* moduleMainString = PyString_FromString("__main__");
  PyObject* moduleMain = PyImport_Import(moduleMainString);
  // https://ubuntuforums.org/archive/index.php/t-324544.html
  // https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
  // https://gist.github.com/rjzak/5681680
  PyRun_SimpleString(
  "from time import time,ctime \n"
  "import sys,os \n"
  "import sklearn \n"
  "import pandas \n"
  "import cPickle as pickle \n"
  "import numpy as np \n"
  "import subprocess \n"
  "from sklearn.externals import joblib \n"
  "from itertools import izip \n"
  "sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-pippkgs_depscipy/3.0-njopjo7/lib/python2.7/site-packages') \n"
  "import xgboost as xgb \n"
  "from collections import OrderedDict \n"
  "def mul(vec, vec2, pklfile): \n"
  "	new_dict = OrderedDict(izip(vec2,vec)) \n"
  "	data = pandas.DataFrame(columns = list(new_dict.keys())) \n"
  "	data=data.append(new_dict, ignore_index = True) \n"
  "	result=-20 \n"
  "	f = None \n"
  "	try: \n"
  "		f = open(pklfile,'rb') \n"
  "	except IOError as e: \n"
  "		print('Couldnt open or write to file (%s).' % e) \n"
  "	else: \n"
  "			try: \n"
  "				pkldata = pickle.load(f) \n"
  "			except pickle.UnpicklingError as e: # normal, somewhat expected \n"
  "				model = pkldata.booster().get_dump() \n"
  "			except (AttributeError,  EOFError, ImportError, IndexError) as e: \n"
  "				print(traceback.format_exc(e)) \n"
  "			except Exception as e: print(traceback.format_exc(e)) \n"
  "			else:  \n"
  "				try: \n"
  "					proba = pkldata.predict_proba(data[data.columns.values.tolist()].values  ) \n"
  "				except : \n"
  "					print('Oops!',sys.exc_info()[0],'occured.') \n"
  "				else: \n"
  "					result = proba[:,1][0] \n"
  "			f.close() \n"
  "	return result \n");
  PyObject* func = PyObject_GetAttrString(moduleMain, "mul");
  PyObject* vectorValues = vectorToTuple_Float(vectorValuesVec);
  PyObject* vecNames = vectorToTuple_String(vectorNamesVec);
  PyObject* args = PyTuple_Pack(3, vectorValues, vecNames, PyString_FromString(mvaFileName_.data()));
  PyObject* result = PyObject_CallObject(func, args);
  double mvaOutput = PyFloat_AsDouble(result);
  //std::cout << "mvaOutput = " << mvaOutput << std::endl;
  return mvaOutput;
}

