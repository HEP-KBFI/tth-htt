#ifndef hhAnalysis_multilepton_HHWeightInterface_h
#define hhAnalysis_multilepton_HHWeightInterface_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <Python.h> // PyObject

// forward declarations
class TFile;
class TH2;

class HHWeightInterface
{
public:
  HHWeightInterface(const edm::ParameterSet & cfg);
  ~HHWeightInterface();

  /**
   * @brief Number of scans
   */
  std::size_t
  get_nof_scans() const;

  /**
   * @brief Calculates HH weight (JHEP)
   */
  std::vector<double>
  getJHEPWeight(double mHH,
                double cosThetaStar,
                bool isDEBUG = false) const;

  /**
   * @brief Calculates HH weight (JHEP)
   */
  std::vector<double>
  getScanWeight(double mHH,
                double cosThetaStar,
                bool isDEBUG = false) const;

  static const std::size_t nof_JHEP;

private:
  double
  getDenom(double mHH,
           double cosThetaStar) const;

  PyObject * modeldata_;
  PyObject * moduleMainString_;
  PyObject * moduleMain_;
  PyObject * func_Weight_;

  static const std::vector<double> klJHEP;
  static const std::vector<double> ktJHEP;
  static const std::vector<double> c2JHEP;
  static const std::vector<double> cgJHEP;
  static const std::vector<double> c2gJHEP;
  static const std::vector<double> normJHEP;

  std::vector<double> Norm_klScan;
  std::vector<double> kl_scan;
  std::vector<double> kt_scan;
  std::vector<double> c2_scan;
  std::vector<double> cg_scan;
  std::vector<double> c2g_scan;
  std::vector<double> BM_klScan;

  TFile * fileHH;
  TH2 * sumEvt;
};

#endif // HHWeightInterface_h
