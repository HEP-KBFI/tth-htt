#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface2.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#if defined(__OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/algorithm/string.hpp> // boost::split(), boost::is_any_of()
#pragma GCC diagnostic pop

#include <TFile.h> // TH1
#include <TH2.h> // TH2

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()
#include <iostream> // std::cerr, std::fixed

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

// CV: Define 12 benchmark (BM) scenarios for coupling scan.
//     The BM scenarios are defined in this paper: https://arxiv.org/pdf/1507.02245.pdf
//    (SM case is stored at index 0)
const std::size_t HHWeightInterface2::nof_JHEP_ = 13;
const std::vector<double> HHWeightInterface2::klJHEP_   = { 1.0,     7.5,     1.0,     1.0,    -3.5,     1.0,     2.4,     5.0,    15.0,     1.0,    10.0,     2.4,    15.0     };
const std::vector<double> HHWeightInterface2::ktJHEP_   = { 1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0     };
const std::vector<double> HHWeightInterface2::c2JHEP_   = { 0.0,    -1.0,     0.5,    -1.5,    -3.0,     0.0,     0.0,     0.0,     0.0,     1.0,    -1.0,     0.0,     1.0     };
const std::vector<double> HHWeightInterface2::cgJHEP_   = { 0.0,     0.0,    -0.8,     0.0,     0.0,     0.8,     0.2,     0.2,    -1.0,    -0.6,     0.0,     1.0,     0.0     };
const std::vector<double> HHWeightInterface2::c2gJHEP_  = { 0.0,     0.0,     0.6,    -0.8,     0.0,    -1.0,    -0.2,    -0.2,     1.0,     0.6,     0.0,    -1.0,     0.0     };
const std::vector<double> HHWeightInterface2::normJHEP_ = { 0.99997, 0.94266, 0.71436, 0.95608, 0.97897, 0.87823, 0.95781, 1.00669, 0.92494, 0.86083, 1.00658, 0.95096, 1.00063 };

HHWeightInterface2::HHWeightInterface2(const edm::ParameterSet & cfg)
  : modeldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , func_Weight_(nullptr)
  , nof_sumEvt_entries_(0)
  , fileHH_(nullptr)
  , sumEvt_(nullptr)
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
  fileHH_ = TFileOpenWrapper::Open(FileDenominator.c_str(), "READ");
  if(! fileHH_)
  {
    throw cmsException(this, __func__, __LINE__) << "Could not open file " << FileDenominator;
  }
  if(fileHH_ -> IsZombie())
  {
    cmsException(this, __func__, __LINE__) << "The file '" << FileDenominator << "' appears to be a zombie";
  }
  sumEvt_ = static_cast<TH2 *>(fileHH_ -> Get(histtitle.c_str()));
  if(! sumEvt_)
  {
    cmsException(this, __func__, __LINE__)
      << "The file '" << FileDenominator << "' does not have a TH2 named " << histtitle
    ;
  }
  nof_sumEvt_entries_ = static_cast<int>(sumEvt_->GetEntries());
  assert(nof_sumEvt_entries_ > 0);

  kl_ = {};
  kt_ = {};
  c2_ = {};
  cg_ = {};
  c2g_ = {};
  norm_ = {};
  bmNames_ = {};
  bmWeightNames_ = {};
  //insert JHEP weight BM points 
  if (scanMode == "default" || scanMode == "full")
  {
    for (std::size_t bmIdx = 0; bmIdx < nof_JHEP_; ++bmIdx)
    {
      kl_.push_back(klJHEP_[bmIdx]);
      kt_.push_back(ktJHEP_[bmIdx]);
      c2_.push_back(c2JHEP_[bmIdx]);
      cg_.push_back(cgJHEP_[bmIdx]);
      c2g_.push_back(c2gJHEP_[bmIdx]);
      norm_.push_back(normJHEP_[bmIdx]);
      std::string bmname = (bmIdx == 0 ) ? "SM" : "BM" + std::to_string(bmIdx);
      bmNames_.push_back(bmname);
      bmWeightNames_.push_back("Weight_" + bmname);
      bmName_to_idx_[bmname] = bmIdx;
    }
  }
  // Load a file with an specific scan, that we can decide at later stage on the analysis
  // save the closest shape BM to use this value on the evaluation of a BDT
  if (scanMode == "full" || scanMode == "additional"){
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
      loadScanFile(applicationLoadPath_cgScan, "cg_", 2, isDEBUG);
    }
    if( applicationLoadFile_c2gScan != "" ){
      const std::string applicationLoadPath_c2gScan = LocalFileInPath(applicationLoadFile_c2gScan).fullPath();
      loadScanFile(applicationLoadPath_c2gScan, "c2g_", 2, isDEBUG);
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

  std::cout << "<HHWeightInterface2>: Scanning " << bmNames_.size() << " benchmark scenarios: " << format_vstring(bmNames_) << std::endl;
}


void HHWeightInterface2::loadScanFile(const std::string & filePath, const std::string & prefix, int idx, bool isDEBUG)
{
  // CV: read coupling scans from text files
  std::ifstream inFile_scan(filePath);
  if(! inFile_scan)
  {
    cmsException(this, __func__, __LINE__) << "Error on opening file " << filePath;
  }
  for (std::string line; std::getline(inFile_scan, line); ) 
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
	  if (idx == 0) to_store = value;
	  break;
	case 1:
	  kt_.push_back(value);
	  if (idx == 1) to_store = value;
	  break;
	case 2:
	  c2_.push_back(value);
	  if (idx == 2) to_store = value;
	  break;
	case 3:
	  cg_.push_back(value);
	  if (idx == 3) to_store = value;
	  break;
	case 4:
	  c2g_.push_back(value);
	  if (idx == 4) to_store = value;
	  break;
	case 5: 
          break;
	case 6: 
          norm_.push_back(value); 
          break;
	default: 
          assert(0);
      }
    }
    std::string bmName = prefix; 
    std::string bmWeightName = "Weight_" + prefix; 
    bmName += to_string_with_precision(to_store);
    bmWeightName += to_string_with_precision(to_store);
    boost::replace_all(bmName, "-", "m");
    boost::replace_all(bmName, ".", "p");
    boost::replace_all(bmWeightName, "-", "m");
    boost::replace_all(bmWeightName, ".", "p");
    if (isDEBUG) 
    {
      std::cout << "bmName = " << bmName << "\n";
    }
    bmNames_.push_back(bmName);
    bmWeightNames_.push_back(bmWeightName);
  }
}

HHWeightInterface2::~HHWeightInterface2()
{
  Py_XDECREF(modeldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);
  Py_XDECREF(func_Weight_);
  fileHH_->Close();
}

double
HHWeightInterface2::getDenom(double mHH, double cosThetaStar) const
{
  const double denominator = sumEvt_->GetBinContent(
        sumEvt_->GetXaxis()->FindBin(mHH),
        sumEvt_->GetYaxis()->FindBin(std::fabs(cosThetaStar))
  );
  return denominator;
}

double
HHWeightInterface2::getWeight(const std::string & bmName, double mHH, double cosThetaStar, bool isDEBUG) const
{
  std::map<std::string, size_t>::const_iterator bmIdx = bmName_to_idx_.find(bmName);
  if ( bmIdx == bmName_to_idx_.end() )
    throw cmsException(this, __func__, __LINE__) << "Invalid parameter 'bmName' = " << bmName << " !!\n";
  const double denominator = getDenom(mHH, cosThetaStar);
  PyObject* args_BM_list = PyTuple_Pack(10,
    PyFloat_FromDouble(static_cast<double>(kl_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(kt_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(c2_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(cg_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(c2g_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(mHH)),
    PyFloat_FromDouble(static_cast<double>(cosThetaStar)),
    PyFloat_FromDouble(static_cast<double>(norm_[bmIdx->second])),
    PyFloat_FromDouble(static_cast<double>(denominator)),
    modeldata_
  );
  double weight = PyFloat_AsDouble(PyObject_CallObject(func_Weight_, args_BM_list)) * nof_sumEvt_entries_;
  Py_XDECREF(args_BM_list);
  if(isDEBUG)
  {
    std::cout << "denominator = " << denominator << std::endl;
    std::cout << "weight #" << bmIdx->second << " (bmName = " << bmName << ") = " << weight << std::endl;
  }
  return weight;
}

double
HHWeightInterface2::getReWeight(const std::string & bmName, double mHH, double cosThetaStar, bool isDEBUG) const
{
  if ( bmName == "SM" )
  {
    return 1.;
  }
  else
  {
    double smWeight = getWeight("SM", mHH, cosThetaStar, isDEBUG);
    double bmWeight = getWeight(bmName, mHH, cosThetaStar, isDEBUG);
    return ( smWeight > 0. ) ? bmWeight/smWeight : 1.;
  }
}

std::vector<std::string>
HHWeightInterface2::get_weight_names() const
{
  return bmWeightNames_;
}

std::vector<std::string>
HHWeightInterface2::get_bm_names() const
{
  return bmNames_;
}
