#ifndef hhAnalysis_multilepton_HHWeightInterface_2_h
#define hhAnalysis_multilepton_HHWeightInterface_2_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <Python.h> // PyObject

// forward declarations
class TFile;
class TH2;

class HHWeightInterface_2
{
public:
  HHWeightInterface_2(const edm::ParameterSet & cfg);
  ~HHWeightInterface_2();

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
   * @brief Get Weight map
   */
  std::map<std::string, double>
  getWeightMap(double mHH,
                double cosThetaStar,
                bool isDEBUG = false) const;

  /**
   * @brief Get reWeightMap
   */

  std::map<std::string, double>
  getReWeightMap(double mHH,
                double cosThetaStar,
                bool isDEBUG = false) const;

private:
  void loadScanFile(std::string filePath, std::string prefix, int indx, bool isDEBUG);
  double
  getDenom(double mHH,
           double cosThetaStar) const;

  std::vector<double> getWeight(double mHH,
		   double cosThetaStar, bool isDEBUG) const;
  PyObject * modeldata_;
  PyObject * moduleMainString_;
  PyObject * moduleMain_;
  PyObject * func_Weight_;

  static const std::size_t nof_JHEP;
  static const std::vector<double> klJHEP;
  static const std::vector<double> ktJHEP;
  static const std::vector<double> c2JHEP;
  static const std::vector<double> cgJHEP;
  static const std::vector<double> c2gJHEP;
  static const std::vector<double> normJHEP;

  std::vector<double> kl_;
  std::vector<double> kt_;
  std::vector<double> c2_;
  std::vector<double> cg_;
  std::vector<double> c2g_;
  std::vector<double> norm_;
  std::vector<std::string> bmName_;
  std::vector<std::string> bmWeightName_;

  int nof_sumEvt_entries;
  TFile * fileHH;
  TH2 * sumEvt;
};

#endif // HHWeightInterface_2_h
