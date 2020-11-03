#ifndef hhAnalysis_multilepton_HHWeightInterface2_h
#define hhAnalysis_multilepton_HHWeightInterface2_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <Python.h> // PyObject

// forward declarations
class TFile;
class TH2;

class HHWeightInterface2
{
 public:
  HHWeightInterface2(const edm::ParameterSet & cfg);
  ~HHWeightInterface2();

  /**
   * @brief Get HH weight names
   */
  std::vector<std::string>
  get_weight_names() const;

  /**
   * @brief Get HH BM names
   */
  std::vector<std::string>
  get_bm_names() const;

  /**
   * @brief Get single Weight
   */
  double
  getWeight(const std::string & bmName,
            double mHH,
            double cosThetaStar,
            bool isDEBUG = false) const;

  /**
   * @brief Get single reWeight
   */
  double
  getReWeight(const std::string & bmName,
              double mHH,
              double cosThetaStar,
              bool isDEBUG = false) const;

 private:
  void loadScanFile(const std::string & filePath, const std::string & prefix, int indx, bool isDEBUG);
  double
  getDenom(double mHH, double cosThetaStar) const;

  PyObject * modeldata_;
  PyObject * moduleMainString_;
  PyObject * moduleMain_;
  PyObject * func_Weight_;

  static const std::size_t nof_JHEP_;
  static const std::vector<double> klJHEP_;
  static const std::vector<double> ktJHEP_;
  static const std::vector<double> c2JHEP_;
  static const std::vector<double> cgJHEP_;
  static const std::vector<double> c2gJHEP_;
  static const std::vector<double> normJHEP_;

  std::vector<double> kl_;
  std::vector<double> kt_;
  std::vector<double> c2_;
  std::vector<double> cg_;
  std::vector<double> c2g_;
  std::vector<double> norm_;
  std::vector<std::string> bmNames_;
  std::vector<std::string> bmWeightNames_;
  std::map<std::string, size_t> bmName_to_idx_;

  int nof_sumEvt_entries_;
  TFile * fileHH_;
  TH2 * sumEvt_;
};

#endif // HHWeightInterface2_h
