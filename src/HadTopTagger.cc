#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "TLorentzVector.h"
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <Python.h>


HadTopTagger::HadTopTagger(const std::string& mvaFileName)
  : kinFit_(0),
    mva_(0),
    mvaOutput_(-1.)
{
  kinFit_ = new HadTopKinFit();

  mvaInputVariables_.push_back("CSV_Wj1");
  mvaInputVariables_.push_back("CSV_b");
  mvaInputVariables_.push_back("dR_Wj1Wj2");
  mvaInputVariables_.push_back("dR_bW");
  mvaInputVariables_.push_back("m_Wj1Wj2");
  mvaInputVariables_.push_back("nllKinFit");
  mvaInputVariables_.push_back("pT_Wj2");
  mvaInputVariables_.push_back("pT_bWj1Wj2");
  mvaInputVariables_.push_back("qg_Wj2");

  mvaInputVariables_.push_back("m_bWj1Wj2");
  mvaInputVariables_.push_back("m_Wj1Wj2");
  mvaInputVariables_.push_back("m_bWj1");
  mvaInputVariables_.push_back("m_bWj2");
  mvaInputVariables_.push_back("m_Wj1Wj2_div_m_bWj1Wj2");
  mvaInputVariables_.push_back("CSV_b");
  mvaInputVariables_.push_back("CSV_Wj1");
  mvaInputVariables_.push_back("CSV_Wj2");
  mvaInputVariables_.push_back("pT_b");
  mvaInputVariables_.push_back("eta_b");
  mvaInputVariables_.push_back("phi_b");
  mvaInputVariables_.push_back("mass_b");
  mvaInputVariables_.push_back("pT_Wj1");
  mvaInputVariables_.push_back("eta_Wj1");
  mvaInputVariables_.push_back("phi_Wj1");
  mvaInputVariables_.push_back("mass_Wj1");
  mvaInputVariables_.push_back("pT_Wj2");
  mvaInputVariables_.push_back("eta_Wj2");
  mvaInputVariables_.push_back("phi_Wj2");
  mvaInputVariables_.push_back("mass_Wj2");
  
  mvaInputVariables_.push_back("dR_bWj1");
  mvaInputVariables_.push_back("dR_bWj2");
  mvaInputVariables_.push_back("dR_Wj1Wj2");
  mvaInputVariables_.push_back("dR_bW");
  mvaInputVariables_.push_back("statusKinFit");
  mvaInputVariables_.push_back("nllKinFit");
  mvaInputVariables_.push_back("alphaKinFit");
    
  mvaInputVariables_.push_back("kinFit_pT_b");
  mvaInputVariables_.push_back("kinFit_eta_b");
  mvaInputVariables_.push_back("kinFit_phi_b");
  mvaInputVariables_.push_back("kinFit_mass_b");
  mvaInputVariables_.push_back("kinFit_pT_Wj1");
  mvaInputVariables_.push_back("kinFit_eta_Wj1");
  mvaInputVariables_.push_back("kinFit_phi_Wj1");
  mvaInputVariables_.push_back("kinFit_mass_Wj1");
  mvaInputVariables_.push_back("kinFit_pT_Wj2");
  mvaInputVariables_.push_back("kinFit_eta_Wj2");
  mvaInputVariables_.push_back("kinFit_phi_Wj2");
  mvaInputVariables_.push_back("kinFit_mass_Wj2");
  
  mvaInputVariables_.push_back("cosTheta_leadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_subleadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_leadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_subleadWj_restTop");

  mvaInputVariables_.push_back("cosTheta_leadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_subleadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_leadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_subleadEWj_restTop");
  
  mvaInputVariables_.push_back("cosThetaW_rest");
  mvaInputVariables_.push_back("cosThetaKinW_rest");
  mvaInputVariables_.push_back("cosThetaW_lab");
  mvaInputVariables_.push_back("cosThetaKinW_lab");
  
  mvaInputVariables_.push_back("cosThetab_rest");
  mvaInputVariables_.push_back("cosThetaKinb_rest");
  mvaInputVariables_.push_back("cosThetab_lab");
  mvaInputVariables_.push_back("cosThetaKinb_lab");

  mvaInputVariables_.push_back("Dphi_Wj1_Wj2_lab");
  mvaInputVariables_.push_back("Dphi_KinWj1_KinWj2_lab");
  
  mvaInputVariables_.push_back("Dphi_Wb_rest");
  mvaInputVariables_.push_back("Dphi_KinWb_rest");
  mvaInputVariables_.push_back("Dphi_Wb_lab");
  mvaInputVariables_.push_back("Dphi_KinWb_lab");

  mvaInputVariables_.push_back("cosThetaWj1_restW");
  mvaInputVariables_.push_back("cosThetaKinWj_restW");
	  
  mvaInputVariables_.push_back("logPKinFit");
  mvaInputVariables_.push_back("logPErrKinFit");
  mvaInputVariables_.push_back("qg_b");
  mvaInputVariables_.push_back("qg_Wj1");
  mvaInputVariables_.push_back("qg_Wj2");
  mvaInputVariables_.push_back("pT_bWj1Wj2");
  mvaInputVariables_.push_back("pT_Wj1Wj2");
  mvaInputVariables_.push_back("max_dR_div_expRjet");
  //if ( mvaFileName != "" ) {
  //  mva_ = new TMVAInterface(mvaFileName, mvaInputVariables_, {});
  //}
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_;
}

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

double HadTopTagger::operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
{
  mvaInputs_["pT_Wj2"]                 = recWJet2.pt();
  Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  mvaInputs_["pT_bWj1Wj2"]             = p4_bWj1Wj2.pt();
  Particle::LorentzVector p4_Wj1Wj2 = recWJet1.p4() + recWJet2.p4();
  mvaInputs_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputs_["CSV_b"]                  = recBJet.BtagCSV();
  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["nllKinFit"]              = kinFit_->nll();
  mvaInputs_["qg_Wj2"]                 = recWJet2.QGDiscr();
  mvaInputs_["pT_Wj1Wj2"]              = p4_Wj1Wj2.pt();
  std::vector<float> vectorValuesVec;
  std::vector<std::basic_string<char>> vectorNamesVec;  
  // prepare dictionary to pass to pyObject functions
  for ( std::map<std::string, double>::const_iterator mvaInput = mvaInputs_.begin();
  	  mvaInput != mvaInputs_.end(); ++mvaInput ) { 
	  vectorValuesVec.push_back(mvaInput->second);
	  vectorNamesVec.push_back((std::basic_string<char>) mvaInput->first);
	  //std::cout << " " << mvaInput->first << " = " << mvaInput->second << std::endl;
  }

  if ( 1>0 ) { // if ( mva_ ) {
    check_mvaInputs(mvaInputs_);
    mvaOutput_ = 34; // (*mva_)(mvaInputs_);
	// https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
	char* pklpath=(char*) "HadTopTagger_sklearnV0o17o1_HypOpt/TTToSemilepton_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_2_deph_1_lr_0o01_CSV_sort.pkl";
	char* pkldir=(char*) "/home/acaan/CMSSW_9_4_0_pre1/src/tth-bdt-training-test/HadTopTagger/";
	std::cout << "Do python, HTT, size: "<<mvaInputs_.size() << std::endl;
	Py_SetProgramName((char*) "application");
	PyObject *moduleMainString = PyString_FromString("__main__");
	PyObject *moduleMain = PyImport_Import(moduleMainString);
	// https://ubuntuforums.org/archive/index.php/t-324544.html
	// https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
	PyRun_SimpleString(
	"from time import time,ctime\n"
	"import sys,os \n"\
	"import sklearn\n"\
	"import pandas\n"\
	"import cPickle as pickle\n"\
	"import numpy as np \n"\
	"import subprocess \n"\
	"from sklearn.externals import joblib \n"\
	"from itertools import izip \n"\
	"sys.path.insert(0, '/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/py2-pippkgs_depscipy/3.0-njopjo7/lib/python2.7/site-packages') \n"\
	"import xgboost as xgb  \n"\
	"print('The xgb version is {}.'.format(xgb.__version__)) \n"\
	"def mul(vec, vec2,pkldir,pklpath): \n"\
	"	#print 'Today is',ctime(time()), 'All python libraries we need loaded good	HTT'\n"\
	"	new_dict = dict(izip(vec2,vec)) \n"\
	"	#print (new_dict) \n"\
	"	data = pandas.DataFrame() \n"\
	"	data=data.append(new_dict, ignore_index=True) \n"\
	"	result=-20 \n"\
	"	f = None  \n"\
	"	try: \n"\
	"		f = open(pkldir+pklpath,'rb') \n"\
	"	except IOError as e: \n"\
	"		print('Couldnt open or write to file (%s).' % e) \n"\
	"	else:  \n"\
	"			#print ('file opened') \n"\
	"			try: \n"\
	"				pkldata = pickle.load(f) \n"\
	"			except pickle.UnpicklingError as e:  \n"\
    "				# normal, somewhat expected  \n"\
	"				model = pkldata.booster().get_dump() \n"\
    "				print len(model) \n"\
	"			except (AttributeError,  EOFError, ImportError, IndexError) as e:  \n"\
    "				# secondary errors  \n"\
	"				print(traceback.format_exc(e))  \n"\
    "				#continue  \n"\
	"			except Exception as e:  \n"\
    "				# everything else, possibly fatal  \n"\
	"				print(traceback.format_exc(e))  \n"\
	"				print('Oops!',sys.exc_info()[0],'occured.') \n"\
	"			else:  \n"\
	"				#print ('pkl loaded') \n"\
	"				try: \n"\
	"					proba = pkldata.predict_proba(data[data.columns.values.tolist()].values  ) \n"\
	"				except : \n"\
	"					print('Oops!',sys.exc_info()[0],'occured.') \n"\			
	"				else:  \n"\
	"					result = proba[:,1][0]\n"\
	"					#print ('predict BDT to one event',result)  \n"\
	"			f.close()  \n"\
	"	return result                                \n"
	);
	PyObject *func = PyObject_GetAttrString(moduleMain, "mul");
	PyObject* vectorValues=vectorToTuple_Float(vectorValuesVec);
	PyObject* vecNames=vectorToTuple_String(vectorNamesVec);
	PyObject *args = PyTuple_Pack(4, vectorValues, vecNames , PyString_FromString( (char*) pkldir), PyString_FromString( (char*) pklpath) ); //    
	PyObject *result = PyObject_CallObject(func, args);
	mvaOutput_=PyFloat_AsDouble(result);
	// https://gist.github.com/rjzak/5681680
	///////////////////////////////////////////////////////////////	
  } else mvaOutput_=-3;
  return mvaOutput_;
}

const std::vector<std::string>& HadTopTagger::mvaInputVariables() const
{ 
  return mvaInputVariables_; 
}

const std::map<std::string, double>& HadTopTagger::mvaInputs() const
{ 
  return mvaInputs_; 
}

const HadTopKinFit* HadTopTagger::kinFit() const 
{ 
  return kinFit_; 
}

