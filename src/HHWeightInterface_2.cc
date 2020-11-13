#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface_2.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#if defined(__OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/algorithm/string.hpp> // boost::split(), boost::is_any_of()
#pragma GCC diagnostic pop

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()
#include <iostream> // std::cerr, std::fixed

#include <TFile.h> // TH1
#include <TH2.h> // TH2

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

const std::size_t HHWeightInterface_2::nof_JHEP = 13;
const std::vector<double> HHWeightInterface_2::klJHEP   = { 1.0,     7.5,     1.0,     1.0,    -3.5,     1.0,     2.4,     5.0,    15.0,     1.0,    10.0,     2.4,    15.0     };
const std::vector<double> HHWeightInterface_2::ktJHEP   = { 1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0     };
const std::vector<double> HHWeightInterface_2::c2JHEP   = { 0.0,    -1.0,     0.5,    -1.5,    -3.0,     0.0,     0.0,     0.0,     0.0,     1.0,    -1.0,     0.0,     1.0     };
const std::vector<double> HHWeightInterface_2::cgJHEP   = { 0.0,     0.0,    -0.8,     0.0,     0.0,     0.8,     0.2,     0.2,    -1.0,    -0.6,     0.0,     1.0,     0.0     };
const std::vector<double> HHWeightInterface_2::c2gJHEP  = { 0.0,     0.0,     0.6,    -0.8,     0.0,    -1.0,    -0.2,    -0.2,     1.0,     0.6,     0.0,    -1.0,     0.0     };
const std::vector<double> HHWeightInterface_2::normJHEP = { 0.99997, 0.94266, 0.71436, 0.95608, 0.97897, 0.87823, 0.95781, 1.00669, 0.92494, 0.86083, 1.00658, 0.95096, 1.00063 };

//TODO: understand why it's needed to pass these variables by reference
HHWeightInterface_2::HHWeightInterface_2(const edm::ParameterSet & cfg)
  : modeldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , func_Weight_(nullptr)
  , nof_sumEvt_entries(0)
  , fileHH(nullptr)
  , sumEvt(nullptr)
{
  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  const std::string denominator_hist = cfg.getParameter<std::string>("denominator_file");
   const std::string applicationLoadFile_klScan = cfg.getParameter<std::string>("klScan_file");
  const std::string applicationLoadFile_ktScan = cfg.getParameter<std::string>("ktScan_file");
  const std::string applicationLoadFile_c2Scan = cfg.getParameter<std::string>("c2Scan_file");
  const std::string applicationLoadFile_cgScan = cfg.getParameter<std::string>("cgScan_file");
  const std::string applicationLoadFile_c2gScan = cfg.getParameter<std::string>("c2gScan_file");
  const std::string scanMode = cfg.getParameter<std::string>("scanMode");
  // const std::string applicationLoadFile_klScan = "hhAnalysis/multilepton/data/kl_scan.dat";
  // const std::string applicationLoadFile_ktScan = "hhAnalysis/multilepton/data/kt_scan.dat";
  // const std::string applicationLoadFile_c2Scan = "hhAnalysis/multilepton/data/c2_scan.dat";
  const std::string coefFile = cfg.getParameter<std::string>("coefFile");
  const std::string histtitle = cfg.getParameter<std::string>("histtitle");
  const bool isDEBUG = cfg.getParameter<bool>("isDEBUG");

  // read the python file that we're about to execute
  const std::string applicationLoadPath = LocalFileInPath("hhAnalysis/multilepton/python/do_weight.py").fullPath();
  std::ifstream applicationLoadFile(applicationLoadPath);
  std::string applicationLoadStr;

  applicationLoadFile.seekg(0, std::ios::end);
  applicationLoadStr.reserve(applicationLoadFile.tellg());
  applicationLoadFile.seekg(0, std::ios::beg);
  applicationLoadStr.assign(std::istreambuf_iterator<char>(applicationLoadFile), std::istreambuf_iterator<char>());

  // https://ubuntuforums.org/archive/index.php/t-324544.html
  // https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
  // https://gist.github.com/rjzak/5681680
  Py_SetProgramName(const_cast<char *>("do_weight"));
  moduleMainString_ = PyString_FromString("__main__");
  Py_Initialize();
  moduleMain_ = PyImport_Import(moduleMainString_);
  PyRun_SimpleString(applicationLoadStr.c_str());

  // General: Load the class with the functions to calculate the different parts of the weights
  PyObject * func_load = PyObject_GetAttrString(moduleMain_, "load");
  const std::string coefFilePath = LocalFileInPath(coefFile).fullPath();
  PyObject * coef_path = PyString_FromString(coefFilePath.c_str());
  PyObject * args_load = PyTuple_Pack(1, coef_path);
  modeldata_ = PyObject_CallObject(func_load, args_load);

  // function to calculate and return parts of the weights
  func_Weight_ = PyObject_GetAttrString(moduleMain_, "evaluate_weight");

  // This histogram is adapted to our input events -- it is going to be used event-by-event
  const std::string FileDenominator = LocalFileInPath(denominator_hist).fullPath();
  fileHH = TFileOpenWrapper::Open(FileDenominator.c_str(), "READ");

  if(! fileHH)
  {
    throw cmsException(this, __func__, __LINE__) << "Could not open file " << FileDenominator;
  }
  if(fileHH -> IsZombie())
  {
    throw cmsException(this, __func__, __LINE__) << "The file '" << FileDenominator << "' appears to be a zombie";
  }

  sumEvt = static_cast<TH2 *>(fileHH -> Get(histtitle.c_str()));
  if(! sumEvt)
  {
    throw cmsException(this, __func__, __LINE__)
      << "The file '" << FileDenominator << "' does not have a TH2 named " << histtitle
    ;
  }
  nof_sumEvt_entries = static_cast<int>(sumEvt->GetEntries());
  assert(nof_sumEvt_entries > 0);

  kl_ = {};
  kt_ = {};
  c2_ = {};
  cg_ = {};
  c2g_ = {};
  norm_ = {};
  bmName_ = {};
  bmWeightName_ = {};
  //insert JHEP weight BM points 
  if (scanMode == "default" || scanMode == "full"){
    for (unsigned int i = 0; i < nof_JHEP; i++){
      kl_.push_back(klJHEP[i]);
      kt_.push_back(ktJHEP[i]);
      c2_.push_back(c2JHEP[i]);
      cg_.push_back(cgJHEP[i]);
      c2g_.push_back(c2gJHEP[i]);
      norm_.push_back(normJHEP[i]);
      std::string bmname = (i == 0 ) ? "SM" : "BM" + std::to_string(i);
      bmName_.push_back(bmname);
      bmWeightName_.push_back("Weight_" + bmname);
    }
  }
  // Load a file with an specific scan, that we can decide at later stage on the analysis
  // save the closest shape BM to use this value on the evaluation of a BDT
  if (scanMode == "full"){
    if( applicationLoadFile_klScan != "" ){
      const std::string applicationLoadPath_klScan = LocalFileInPath(applicationLoadFile_klScan).fullPath();
      loadScanFile(applicationLoadPath_klScan, "kl_", 0, isDEBUG);
    }
    if( applicationLoadFile_ktScan != "" ){
      const std::string applicationLoadPath_ktScan = LocalFileInPath(applicationLoadFile_ktScan).fullPath();
      loadScanFile(applicationLoadPath_ktScan, "kt_", 1, isDEBUG);
    }
    if( applicationLoadFile_c2Scan != "" ){
      const std::string applicationLoadPath_c2Scan = LocalFileInPath(applicationLoadFile_c2Scan).fullPath();
      loadScanFile(applicationLoadPath_c2Scan, "c2_", 2, isDEBUG);
    }
    if( applicationLoadFile_cgScan != "" ){
      const std::string applicationLoadPath_cgScan = LocalFileInPath(applicationLoadFile_cgScan).fullPath();
      loadScanFile(applicationLoadPath_cgScan, "cg_", 3, isDEBUG);
    }
    if( applicationLoadFile_c2gScan != "" ){
      const std::string applicationLoadPath_c2gScan = LocalFileInPath(applicationLoadFile_c2gScan).fullPath();
      loadScanFile(applicationLoadPath_c2gScan, "c2g_", 4, isDEBUG);
    }
  }
  if(isDEBUG)
    {
      for(std::size_t bmIdx = 0; bmIdx < norm_.size(); ++bmIdx)
	{
	  std::cout << "line = "<< bmIdx << " kl = " << kl_[bmIdx] << " ; Norm = " << norm_[bmIdx] << '\n';
	}
    }
  Py_XDECREF(coef_path);
  Py_XDECREF(args_load);
  Py_XDECREF(func_load);
}


void HHWeightInterface_2::loadScanFile(std::string filePath, std::string prefix, int indx, bool isDEBUG){
  std::ifstream inFile_scan(filePath);
  if(! inFile_scan)
    {
      throw cmsException(this, __func__, __LINE__) << "Error on opening file " << filePath;
    }
  for(std::string line; std::getline(inFile_scan, line);)
    {
      std::vector<std::string> line_split;
      boost::split(line_split, line, boost::is_any_of(" "));
      assert(line_split.size() == 7);
      std::vector<double> values;
      std::transform(
		     line_split.begin(), line_split.end(), std::back_inserter(values),
		     [](const std::string & value_string) -> double { return std::stod(value_string); }
		     );
      double to_store = 1.0;
      for(std::size_t colIdx = 0; colIdx < values.size(); ++colIdx)
	{
	  const double value = values[colIdx];
	  switch(colIdx)
	    {
	    case 0:
	      kl_.push_back(value);
	      if (indx == 0) to_store = value;
	      break;
	    case 1:
	      kt_.push_back(value);
	      if (indx == 1) to_store = value;
	      break;
	    case 2:
	      c2_.push_back(value);
	      if (indx == 2) to_store = value;
	      break;
	    case 3:
	      cg_.push_back(value);
	      if (indx == 3) to_store = value;
	      break;
	    case 4:
	      c2g_.push_back(value);
	      if (indx == 4) to_store = value;
	      break;
	    case 5: break;
	    case 6: norm_.push_back(value); break;
	    default: assert(0);
	    }
	}
      std::string bmName = prefix; 
      std::string bmWeightName = "Weight_" + prefix; 
      bmName += to_string_with_precision(to_store); //  boost::lexical_cast<std::string>();
      bmWeightName += to_string_with_precision(to_store); //  boost::lexical_cast<std::string>();
      boost::replace_all(bmName, "-", "m");
      boost::replace_all(bmName, ".", "p");
      boost::replace_all(bmWeightName, "-", "m");
      boost::replace_all(bmWeightName, ".", "p");
      if (isDEBUG) {
        std::cout << "bmName = " << bmName << "\n";
      }
      bmName_.push_back(bmName);
      bmWeightName_.push_back(bmWeightName);
    }

}

HHWeightInterface_2::~HHWeightInterface_2()
{
  Py_XDECREF(modeldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);
  Py_XDECREF(func_Weight_);
  fileHH->Close();
}

double
HHWeightInterface_2::getDenom(double mHH,
                            double cosThetaStar) const
{
  const double denominator = sumEvt->GetBinContent(
        sumEvt->GetXaxis()->FindBin(mHH),
        sumEvt->GetYaxis()->FindBin(std::fabs(cosThetaStar))
  );
  return denominator;
}



std::vector<double>
HHWeightInterface_2::getWeight(double mHH,
                                 double cosThetaStar,
                                 bool isDEBUG) const
{
  const double denominator = getDenom(mHH, cosThetaStar);

  // This can be calculated at post-production stage
  std::vector<double> Weights;
  for(std::size_t bmIdx = 0; bmIdx < norm_.size(); ++bmIdx)
  {
    PyObject* args_BM_list = PyTuple_Pack(10,
      PyFloat_FromDouble(static_cast<double>(kl_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(kt_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(c2_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(cg_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(c2g_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(mHH)),
      PyFloat_FromDouble(static_cast<double>(cosThetaStar)),
      PyFloat_FromDouble(static_cast<double>(norm_[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(denominator)),
      modeldata_
    );
    Weights.push_back(
      PyFloat_AsDouble(PyObject_CallObject(func_Weight_, args_BM_list)) * nof_sumEvt_entries
    );
    Py_XDECREF(args_BM_list);
  }

  if(isDEBUG)
  {
    std::cout << "Denominator = " << denominator << '\n';
    for(std::size_t bmIdx = 0; bmIdx < Weights.size(); ++bmIdx)
    {
      std::cout << "Weight #" << bmName_[bmIdx] << " = " <<  Weights[bmIdx] << '\n';
    }
  }

  return Weights;
}


std::map<std::string, double>
HHWeightInterface_2::getWeightMap(double mHH,
                                 double cosThetaStar,
                                 bool isDEBUG) const
{
  std::vector<double> weights = getWeight(mHH,
					  cosThetaStar,
					  isDEBUG);
  std::map<std::string, double> weight_map;
  for (unsigned int i = 0; i < bmWeightName_.size(); i++){
    weight_map[bmWeightName_[i]] = weights[i];
  }
  return weight_map;

}


std::map<std::string, double>
HHWeightInterface_2::getReWeightMap(double mHH,
                                 double cosThetaStar,
                                 bool isDEBUG) const
{
  std::vector<double> weights = getWeight(mHH,
					  cosThetaStar,
					  isDEBUG);
  double smWeight = weights[0];
  std::map<std::string, double> weight_map;
  for (unsigned int i = 0; i < bmName_.size(); i++){
    (bmName_[i] == "SM") ? weight_map[bmName_[i]] = 1. : weight_map[bmName_[i]] = weights[i]/smWeight;
  }
  return weight_map;
}

std::vector<std::string> HHWeightInterface_2::get_weight_names() const{
  return bmWeightName_;
}

std::vector<std::string> HHWeightInterface_2::get_bm_names() const{
  return bmName_;
}
