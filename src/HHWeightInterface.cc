#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#include <boost/algorithm/string.hpp> // boost::split(), boost::is_any_of()
#pragma GCC diagnostic pop

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()
#include <iostream> // std::cerr, std::fixed

#include <TFile.h> // TH1
#include <TH2.h> // TH2

const std::size_t HHWeightInterface::nof_JHEP = 13;
const std::vector<double> HHWeightInterface::klJHEP   = { 1.0,     7.5,     1.0,     1.0,    -3.5,     1.0,     2.4,     5.0,    15.0,     1.0,    10.0,     2.4,    15.0     };
const std::vector<double> HHWeightInterface::ktJHEP   = { 1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0     };
const std::vector<double> HHWeightInterface::c2JHEP   = { 0.0,    -1.0,     0.5,    -1.5,    -3.0,     0.0,     0.0,     0.0,     0.0,     1.0,    -1.0,     0.0,     1.0     };
const std::vector<double> HHWeightInterface::cgJHEP   = { 0.0,     0.0,    -0.8,     0.0,     0.0,     0.8,     0.2,     0.2,    -1.0,    -0.6,     0.0,     1.0,     0.0     };
const std::vector<double> HHWeightInterface::c2gJHEP  = { 0.0,     0.0,     0.6,    -0.8,     0.0,    -1.0,    -0.2,    -0.2,     1.0,     0.6,     0.0,    -1.0,     0.0     };
const std::vector<double> HHWeightInterface::normJHEP = { 0.99997, 0.94266, 0.71436, 0.95608, 0.97897, 0.87823, 0.95781, 1.00669, 0.92494, 0.86083, 1.00658, 0.95096, 1.00063 };

//TODO: understand why it's needed to pass these variables by reference
HHWeightInterface::HHWeightInterface(const edm::ParameterSet & cfg)
{
  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  const std::string denominator_hist = cfg.getParameter<std::string>("denominator_file");
  const std::string applicationLoadFile_klScan = cfg.getParameter<std::string>("klScan_file");
  const std::string coefFile = cfg.getParameter<std::string>("coefFile");
  const std::string histtitle = cfg.getParameter<std::string>("histtitle");
  const bool isDEBUG = cfg.getParameter<bool>("isDEBUG");
  const bool do_scan = cfg.getParameter<bool>("do_scan");

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
  fileHH = TFileOpenWrapper::Open(FileDenominator.c_str(), "READ");

  if(! fileHH)
  {
    throw cmsException(this, __func__, __LINE__) << "Could not open file " << FileDenominator;
  }
  if(fileHH -> IsZombie())
  {
    cmsException(this, __func__, __LINE__) << "The file '" << FileDenominator << "' appears to be a zombie";
  }

  sumEvt = static_cast<TH2 *>(fileHH -> Get(histtitle.c_str()));
  if(! sumEvt)
  {
    cmsException(this, __func__, __LINE__)
      << "The file '" << FileDenominator << "' does not have a TH2 named " << histtitle
    ;
  }

  // Load a file with an specific scan, that we can decide at later stage on the analysis
  // save the closest shape BM to use this value on the evaluation of a BDT
  if(do_scan)
  {
    const std::string applicationLoadPath_klScan = LocalFileInPath(applicationLoadFile_klScan).fullPath();
    std::ifstream inFile_kl_scan(applicationLoadPath_klScan);

    if(! inFile_kl_scan)
    {
      cmsException(this, __func__, __LINE__) << "Error on opening file " << applicationLoadFile_klScan;
    }

    for(std::string line; std::getline(inFile_kl_scan, line);)
    {
      std::vector<std::string> line_split;
      boost::split(line_split, line, boost::is_any_of(" "));
      assert(line_split.size() == 7);

      std::vector<double> values;
      std::transform(
        line_split.begin(), line_split.end(), std::back_inserter(values),
        [](const std::string & value_string) -> double { return std::stod(value_string); }
      );
      for(std::size_t colIdx = 0; colIdx < values.size(); ++colIdx)
      {
        const double value = values[colIdx];
        switch(colIdx)
        {
          case 0: kl_scan.push_back(value); break;
          case 1: kt_scan.push_back(value); break;
          case 2: c2_scan.push_back(value); break;
          case 3: cg_scan.push_back(value); break;
          case 4: c2g_scan.push_back(value); break;
          case 5: BM_klScan.push_back(value); break;
          case 6: Norm_klScan.push_back(value); break;
          default: assert(0);
        }
      }
    }

    if(isDEBUG)
    {
      for(std::size_t bmIdx = 0; bmIdx < Norm_klScan.size(); ++bmIdx)
      {
        std::cout << "line = "<< bmIdx << " kl = " << kl_scan[bmIdx] << " ; Norm = " << Norm_klScan[bmIdx] << '\n';
      }
    }
  }

  Py_XDECREF(coef_path);
  Py_XDECREF(args_load);
  Py_XDECREF(func_load);
}

HHWeightInterface::~HHWeightInterface()
{
  Py_XDECREF(modeldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);
  Py_XDECREF(func_Weight_);
  fileHH->Close();
}

std::size_t
HHWeightInterface::get_nof_scans() const
{
  return kl_scan.size();
}

double
HHWeightInterface::getDenom(double mHH,
                            double cosThetaStar) const
{
  const double denominator = sumEvt->GetBinContent(
        sumEvt->GetXaxis()->FindBin(mHH),
        sumEvt->GetYaxis()->FindBin(std::fabs(cosThetaStar))
  );
  return denominator;
}

std::vector<double>
HHWeightInterface::getJHEPWeight(double mHH,
                                 double cosThetaStar,
                                 bool isDEBUG) const
{
  const double denominator = getDenom(mHH, cosThetaStar);

  // This can be calculated at post-production stage
  std::vector<double> WeightBM;
  for(std::size_t bmIdx = 0; bmIdx < nof_JHEP; ++bmIdx)
  {
    PyObject* args_BM_list = PyTuple_Pack(10,
      PyFloat_FromDouble(static_cast<double>(klJHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(ktJHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(c2JHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(cgJHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(c2gJHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(mHH)),
      PyFloat_FromDouble(static_cast<double>(cosThetaStar)),
      PyFloat_FromDouble(static_cast<double>(normJHEP[bmIdx])),
      PyFloat_FromDouble(static_cast<double>(denominator)),
      modeldata_
    );
    WeightBM.push_back(
      PyFloat_AsDouble(PyObject_CallObject(func_Weight_, args_BM_list))
    );
    Py_XDECREF(args_BM_list);
  }

  if(isDEBUG)
  {
    std::cout << "Denominator = " << denominator << '\n';
    for(std::size_t bmIdx = 0; bmIdx < WeightBM.size(); ++bmIdx)
    {
      std::cout << "Weight #" << bmIdx << " = " <<  WeightBM[bmIdx] << '\n';
    }
  }

  return WeightBM;
}

std::vector<double>
HHWeightInterface::getScanWeight(double mHH,
                                 double cosThetaStar,
                                 bool isDEBUG) const
{
  const double denominator = getDenom(mHH, cosThetaStar);

  // This part is for any scan that we can decide at later stage on the analysis
  std::vector<double> Weight_klScan;
  for(std::size_t scanIdx = 0; scanIdx < Norm_klScan.size(); ++scanIdx)
  {
    PyObject* args_kl_scan_list = PyTuple_Pack(10,
      PyFloat_FromDouble(static_cast<double>(kl_scan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(kt_scan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(c2_scan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(cg_scan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(c2g_scan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(mHH)),
      PyFloat_FromDouble(static_cast<double>(cosThetaStar)),
      PyFloat_FromDouble(static_cast<double>(Norm_klScan[scanIdx])),
      PyFloat_FromDouble(static_cast<double>(denominator)),
      modeldata_
    );
    Weight_klScan.push_back(
      PyFloat_AsDouble(PyObject_CallObject(func_Weight_, args_kl_scan_list))
    );
    Py_XDECREF(args_kl_scan_list);
  }

  if(isDEBUG)
  {
    std::cout << "Denominator = " << denominator << '\n';
    for(std::size_t scanIdx = 0; scanIdx < Weight_klScan.size(); ++scanIdx)
    {
      std::cout << "Weight #" << scanIdx << " = " <<  Weight_klScan[scanIdx] << '\n';
    }
  }

  return Weight_klScan;
}
