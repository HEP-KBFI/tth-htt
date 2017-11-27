#include <Python.h>
#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <map>
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs

// https://gist.github.com/rjzak/5681680
PyObject* vectorToTuple_Float(const std::vector<float> &data) {
	PyObject* tuple = PyTuple_New( data.size() );
	if (!tuple) throw std::logic_error("Unable to allocate memory for Python tuple");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyFloat_FromDouble( (double) data[i]);
		if (!num) {
			Py_DECREF(tuple);
			throw std::logic_error("Unable to allocate memory for Python tuple");
		}
		PyTuple_SET_ITEM(tuple, i, num);
	}

	return tuple;
}

PyObject* vectorToTuple_String(std::vector<std::basic_string<char>> &data) {
	PyObject* tuple = PyTuple_New( data.size() );
	if (!tuple) throw std::logic_error("Unable to allocate memory for Python tuple");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyString_FromString( (char*) data[i].c_str());
		if (!num) {
			Py_DECREF(tuple);
			throw std::logic_error("Unable to allocate memory for Python tuple");
		}
		PyTuple_SET_ITEM(tuple, i, num);
	}

	return tuple;
}

double XGBReader( std::map<std::string, double> mvaInputs_ , char* pklpath )
{
  setenv("OMP_NUM_THREADS", "1", 0);
	double mvaOutput_=-20;
    // here I can start the XGBReader
	char* pkldir=(char*) "/home/acaan/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/data/"; //
	std::vector<float> vectorValuesVec;
	std::vector<std::basic_string<char>> vectorNamesVec;
	// prepare dictionary to pass to pyObject functions
	for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_.begin();
		mvaInput != mvaInputs_.end(); ++mvaInput ) {
		vectorValuesVec.push_back(mvaInput->second);
		vectorNamesVec.push_back((std::basic_string<char>) mvaInput->first);
		//std::cout << " " << mvaInput->first << " : " << mvaInput->second << std::endl;
	}

    check_mvaInputs(mvaInputs_);
    //mvaOutput_ = 34; // (*mva_)(mvaInputs_);
	// https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
	//std::cout << "Do python, HTT, size: "<<mvaInputs_.size() << std::endl;
	Py_SetProgramName((char*) "application");
	PyObject *moduleMainString = PyString_FromString("__main__");
	PyObject *moduleMain = PyImport_Import(moduleMainString);
	// https://ubuntuforums.org/archive/index.php/t-324544.html
	// https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
  // https://gist.github.com/rjzak/5681680
	PyRun_SimpleString(
	"from time import time,ctime\n"
  "import sys,os \n"
  "import sklearn\n"
  "import pandas\n"
  "import cPickle as pickle\n"
  "import numpy as np \n"
  "import subprocess \n"
  "from sklearn.externals import joblib \n"
  "from itertools import izip \n"
  "sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-pippkgs_depscipy/3.0-njopjo7/lib/python2.7/site-packages') \n"
  "import xgboost as xgb  \n"
	"from collections import OrderedDict \n"
  "def mul(vec, vec2,pkldir,pklpath): \n"
  "	#print 'Today is',ctime(time()), 'All python libraries we need loaded good	HTT'\n"
  "	new_dict = OrderedDict(izip(vec2,vec)) \n"
  "	#print (new_dict) \n"
  "	data = pandas.DataFrame(columns=list(new_dict.keys())) \n"
  "	data=data.append(new_dict, ignore_index=True) \n"
  "	result=-20 \n"
  "	f = None  \n"
  "	try: \n"
  "		f = open(pkldir+pklpath,'rb') \n"
  "	except IOError as e: \n"
  "		print('Couldnt open or write to file (%s).' % e) \n"
  "	else: \n"
  "			try: \n"
  "				pkldata = pickle.load(f) \n"
  "			except pickle.UnpicklingError as e: # normal, somewhat expected  \n"
  "				model = pkldata.booster().get_dump() \n"
  "			except (AttributeError,  EOFError, ImportError, IndexError) as e:  \n"
  "				print(traceback.format_exc(e))  \n"
  "			except Exception as e: print(traceback.format_exc(e))  \n"
  "			else:  \n"
  "				try: \n"
  "					proba = pkldata.predict_proba(data[data.columns.values.tolist()].values  ) \n"
  "				except : \n"
  "					print('Oops!',sys.exc_info()[0],'occured.') \n"
  "				else:  \n"
  "					result = proba[:,1][0]\n"
  "			f.close()  \n"
	"	return result                                \n"
	);
	PyObject *func = PyObject_GetAttrString(moduleMain, "mul");
	PyObject* vectorValues=vectorToTuple_Float(vectorValuesVec);
	PyObject* vecNames=vectorToTuple_String(vectorNamesVec);
	PyObject *args = PyTuple_Pack(4, vectorValues, vecNames , PyString_FromString( (char*) pkldir), PyString_FromString( (char*) pklpath) ); //
  PyObject *result = PyObject_CallObject(func, args);
  mvaOutput_=PyFloat_AsDouble(result);
    return mvaOutput_;
}
