#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"

#include <Python.h>

XGBInterface::XGBInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables)
  : mvaInputVariables_(mvaInputVariables)
{
  LocalFileInPath mvaFileName_fip(mvaFileName);
  mvaFileName_ = mvaFileName_fip.fullPath();

  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  // https://ubuntuforums.org/archive/index.php/t-324544.html
  // https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
  // https://gist.github.com/rjzak/5681680
  Py_SetProgramName((char*)"applicationLoad");
  moduleMainString_ = PyString_FromString("__main__");
  moduleMain_ = PyImport_Import(moduleMainString_);
  PyRun_SimpleString(
  "import sys \n"
  "sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-scikit-learn/0.17.1-ikhhed/lib/python2.7/site-packages')\n"
  "import sklearn\n"
  "sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-pandas/0.17.1-ikhhed/lib/python2.7/site-packages/pandas-0.17.1-py2.7-linux-x86_64.egg')\n"
  "import pandas \n"
  "import cPickle as pickle \n"
  "sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-pippkgs_depscipy/3.0-njopjo7/lib/python2.7/site-packages') \n"
  "import xgboost as xgb \n"
  "def load(pklfile): \n"
  "	f = None \n"
  "	pkldata = None \n"
  "	try: \n"
  "		f = open(pklfile,'rb') \n"
  "	except IOError as e: \n"
  "		print('Couldnt open or write to file (%s).' % e) \n"
  "	else: \n"
  "			try: \n"
  "				pkldata = pickle.load(f) \n"
  "			except pickle.UnpicklingError as e: # normal, somewhat expected \n"
  "			  try: \n"
  "				  model = pkldata.booster().get_dump() \n" // this only tests load was ok
  "			  except (AttributeError,  EOFError, ImportError, IndexError) as e: \n"
  "				  print(traceback.format_exc(e)) \n"
  "			  except Exception as e: print(traceback.format_exc(e)) \n"
  "			f.close() \n"
  "	return pkldata \n");
  PyObject* func = PyObject_GetAttrString(moduleMain_, "load");
  PyObject* args = PyTuple_Pack(1, PyString_FromString(mvaFileName_.data()));
  pkldata_ = PyObject_CallObject(func, args);

  // to use it later
  PyRun_SimpleString(
  "from itertools import izip \n"
  "from collections import OrderedDict \n"
  "def evaluate(vec, vec2, pkldata): \n"
  "	new_dict = OrderedDict(izip(vec2,vec)) \n"
  "	data = pandas.DataFrame(columns = list(new_dict.keys())) \n"
  "	data=data.append(new_dict, ignore_index = True) \n"
  "	result=-20 \n"
  "	try: proba = pkldata.predict_proba(data[data.columns.values.tolist()].values  ) \n"
  "	except : print('Oops!',sys.exc_info()[0],'occured.') \n"
  "	else: result = proba[:,1][0] \n"
  "	return result \n");
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
  std::vector<float> vectorValuesVec;
  std::vector<std::basic_string<char>> vectorNamesVec;

  for ( std::vector<std::string>::const_iterator mvaInputVariable = mvaInputVariables_.begin();
	mvaInputVariable != mvaInputVariables_.end(); ++mvaInputVariable ) {
    if ( mvaInputs.find(*mvaInputVariable) != mvaInputs.end() ) {
      //std::cout << " " << (*mvaInputVariable) << " = " << mvaInputs.find(*mvaInputVariable)->second << std::endl;
      vectorValuesVec.push_back(mvaInputs.find(*mvaInputVariable)->second);
      vectorNamesVec.push_back(*mvaInputVariable);
    } else {
      throw cms::Exception("XGBInterface::operator()")
	<< "Missing value for MVA input variable = '" << (*mvaInputVariable) << "' !!\n";
    }
  }
  PyObject* func = PyObject_GetAttrString(moduleMain_, "evaluate");
  PyObject* vectorValues = vectorToTuple_Float(vectorValuesVec); //tuple;//
  PyObject* vecNames = vectorToTuple_String(vectorNamesVec); //tupleNames; //
  PyObject* args = PyTuple_Pack(3, vectorValues, vecNames, pkldata_);
  PyObject* result = PyObject_CallObject(func, args);
  double mvaOutput = PyFloat_AsDouble(result);
  //std::cout << "mvaOutput = " << mvaOutput << std::endl;
  return mvaOutput;
}
