#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceLO.h"

#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceCouplings.h" // HHWeightInterfaceCouplings
#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring()

#include <TFile.h> // TH1
#include <TH2.h> // TH2

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()
#include <iostream> // std::cerr, std::fixed

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

HHWeightInterfaceLO::HHWeightInterfaceLO(const HHWeightInterfaceCouplings * const couplings,
                                         const edm::ParameterSet & cfg)
  : couplings_(couplings)
  , modeldata_(nullptr)
  , moduleMainString_(nullptr)
  , moduleMain_(nullptr)
  , func_Weight_(nullptr)
  , nof_sumEvt_entries_(0)
  , sumEvt_(nullptr)
{
  assert(couplings_);

  // AC: limit number of threads running in python to one
  setenv("OMP_NUM_THREADS", "1", 0);

  const std::string coefFile = cfg.getParameter<std::string>("coefFile");

  // read the python file that we're about to execute
  const std::string applicationLoadPath = get_fullpath("hhAnalysis/multilepton/python/do_weight.py");
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
  const std::string coefFilePath = get_fullpath(coefFile);
  PyObject * coef_path = PyString_FromString(coefFilePath.c_str());
  PyObject * args_load = PyTuple_Pack(1, coef_path);
  modeldata_ = PyObject_CallObject(func_load, args_load);

  // function to calculate and return parts of the weights
  func_Weight_ = PyObject_GetAttrString(moduleMain_, "evaluate_weight");

  // function to compute normalization constant
  func_norm_ = PyObject_GetAttrString(moduleMain_, "get_norm");

  sumEvt_ = HHWeightInterfaceCouplings::loadDenominatorHist(
    couplings_->denominator_file_lo(), couplings_->histtitle()
  );
  nof_sumEvt_entries_ = static_cast<int>(sumEvt_->GetEntries());
  assert(nof_sumEvt_entries_ > 0);

  Py_XDECREF(coef_path);
  Py_XDECREF(args_load);
  Py_XDECREF(func_load);

  const std::vector<double> kl = couplings_->kl();
  const std::vector<double> kt = couplings_->kt();
  const std::vector<double> c2 = couplings_->c2();
  const std::vector<double> cg = couplings_->cg();
  const std::vector<double> c2g = couplings_->c2g();
  const std::size_t nof_couplings = couplings_->get_bm_names().size();
  if ( kl.size()  != nof_couplings ||
       kt.size()  != nof_couplings ||
       c2.size()  != nof_couplings ||
       cg.size()  != nof_couplings ||
       c2g.size() != nof_couplings)
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid coupling parameters !!\n";
  }
  norm_.clear();
  for(std::size_t coupling_idx = 0; coupling_idx < nof_couplings; ++coupling_idx)
  {
    norm_.push_back(getNorm({{
      kl.at(coupling_idx),
      kt.at(coupling_idx),
      c2.at(coupling_idx),
      cg.at(coupling_idx),
      c2g.at(coupling_idx),
    }}));
  }
}



HHWeightInterfaceLO::~HHWeightInterfaceLO()
{
  Py_XDECREF(modeldata_);
  Py_XDECREF(moduleMainString_);
  Py_XDECREF(moduleMain_);
  Py_XDECREF(func_Weight_);
  Py_XDECREF(func_norm_);
  delete sumEvt_;
}

double
HHWeightInterfaceLO::getDenom(double mHH, double cosThetaStar) const
{
  return HHWeightInterfaceCouplings::getBinContent(sumEvt_, mHH, cosThetaStar);
}

double
HHWeightInterfaceLO::getWeight(const std::string & bmName,
                               double mHH,
                               double cosThetaStar,
                               bool isDEBUG) const
{
  const std::vector<std::string> bmNames = couplings_->get_bm_names();
  const std::vector<std::string>::const_iterator bmIdxIt = std::find(bmNames.cbegin(), bmNames.cend(), bmName);
  if(bmIdxIt == bmNames.end())
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid parameter 'bmName' = " << bmName << " !!\n";
  }
  const std::size_t bmIdx = std::distance(bmNames.cbegin(), bmIdxIt);
  const double denominator = getDenom(mHH, cosThetaStar);

  const std::vector<double> kl = couplings_->kl();
  const std::vector<double> kt = couplings_->kt();
  const std::vector<double> c2 = couplings_->c2();
  const std::vector<double> cg = couplings_->cg();
  const std::vector<double> c2g = couplings_->c2g();

  const std::size_t nof_couplings = bmNames.size();
  if ( kl.size()    != nof_couplings ||
       kt.size()    != nof_couplings ||
       c2.size()    != nof_couplings ||
       cg.size()    != nof_couplings ||
       c2g.size()   != nof_couplings ||
       norm_.size() != nof_couplings  )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid coupling parameters !!\n";
  }

  PyObject* kl_py = PyFloat_FromDouble(static_cast<double>(kl[bmIdx]));
  PyObject* kt_py = PyFloat_FromDouble(static_cast<double>(kt[bmIdx]));
  PyObject* c2_py = PyFloat_FromDouble(static_cast<double>(c2[bmIdx]));
  PyObject* cg_py = PyFloat_FromDouble(static_cast<double>(cg[bmIdx]));
  PyObject* c2g_py = PyFloat_FromDouble(static_cast<double>(c2g[bmIdx]));
  PyObject* mHH_py = PyFloat_FromDouble(static_cast<double>(mHH));
  PyObject* cosThetaStar_py = PyFloat_FromDouble(static_cast<double>(cosThetaStar));
  PyObject* norm_py = PyFloat_FromDouble(static_cast<double>(norm_[bmIdx]));
  PyObject* denominator_py = PyFloat_FromDouble(static_cast<double>(denominator));
  PyObject* args_BM_list = PyTuple_Pack(10,
    kl_py,
    kt_py,
    c2_py,
    cg_py,
    c2g_py,
    mHH_py,
    cosThetaStar_py,
    norm_py,
    denominator_py,
    modeldata_
  );
  PyObject* weight_ptr = PyObject_CallObject(func_Weight_, args_BM_list);
  const double weight = PyFloat_AsDouble(weight_ptr) * nof_sumEvt_entries_;

  Py_XDECREF(kl_py);
  Py_XDECREF(kt_py);
  Py_XDECREF(c2_py);
  Py_XDECREF(cg_py);
  Py_XDECREF(c2g_py);
  Py_XDECREF(mHH_py);
  Py_XDECREF(cosThetaStar_py);
  Py_XDECREF(norm_py);
  Py_XDECREF(denominator_py);
  Py_XDECREF(args_BM_list);
  Py_XDECREF(weight_ptr);

  if(isDEBUG)
  {
    std::cout
      << "denominator = " << denominator << "\n"
         "weight #" << bmIdx << " (bmName = " << bmName << ") = " << weight << '\n'
    ;
  }
  return weight;
}

double
HHWeightInterfaceLO::getRelativeWeight(const std::string & bmName,
                                       double mHH,
                                       double cosThetaStar,
                                       bool isDEBUG) const
{
  double reWeight = 1.;
  if ( bmName == "SM" )
  {
    reWeight = 1.;
  }
  else
  {
    double smWeight = getWeight("SM", mHH, cosThetaStar, isDEBUG);
    double bmWeight = getWeight(bmName, mHH, cosThetaStar, isDEBUG);
    reWeight = ( smWeight > 0. ) ? bmWeight/smWeight : 1.;
  }
  return reWeight;
}

std::vector<double>
HHWeightInterfaceLO::getNorm() const
{
  return norm_;
}

double
HHWeightInterfaceLO::getNorm(const std::array<double, 5> & couplings) const
{
  PyObject* kl_py = PyFloat_FromDouble(static_cast<double>(couplings.at(0)));
  PyObject* kt_py = PyFloat_FromDouble(static_cast<double>(couplings.at(1)));
  PyObject* c2_py = PyFloat_FromDouble(static_cast<double>(couplings.at(2)));
  PyObject* cg_py = PyFloat_FromDouble(static_cast<double>(couplings.at(3)));
  PyObject* c2g_py = PyFloat_FromDouble(static_cast<double>(couplings.at(4)));
  PyObject* denom_py = PyString_FromString(get_fullpath(couplings_->denominator_file_lo()).data());
  PyObject* hist_py = PyString_FromString(couplings_->histtitle().data());

  PyObject* args_norm_list = PyTuple_Pack(8,
    kl_py,
    kt_py,
    c2_py,
    cg_py,
    c2g_py,
    denom_py,
    hist_py,
    modeldata_
  );
  PyObject* norm_ptr = PyObject_CallObject(func_norm_, args_norm_list);
  const double norm = PyFloat_AsDouble(norm_ptr);

  Py_XDECREF(kl_py);
  Py_XDECREF(kt_py);
  Py_XDECREF(c2_py);
  Py_XDECREF(cg_py);
  Py_XDECREF(c2g_py);
  Py_XDECREF(denom_py);
  Py_XDECREF(hist_py);
  Py_XDECREF(args_norm_list);
  Py_XDECREF(norm_ptr);

  return norm;
}
