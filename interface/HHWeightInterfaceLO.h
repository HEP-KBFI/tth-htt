#ifndef tthAnalysis_HiggsToTauTau_HHWeightInterfaceLO_h
#define tthAnalysis_HiggsToTauTau_HHWeightInterfaceLO_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <Python.h> // PyObject

// forward declarations
class TFile;
class TH2;

class HHWeightInterfaceLO
{
 public:
  HHWeightInterfaceLO(const edm::ParameterSet & cfg);
  ~HHWeightInterfaceLO();

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
   *
   * The purpose of this function is two-fold:
   *  1) reweight the sum of all LO HH MC samples to the case of either SM kinematics (use "bmName" = "SM") or to one of the 12 benchmark (BM) scenarios
   *     dissussed in this paper:
   *       https://arxiv.org/abs/1507.02245
   *     The reweighting is implemented in terms of the two observables gen_mHH and cos(theta*),
   *     which fully parametrize the kinematics of HH events at leading order.
   *  2) account for a bug of the Higgs boson couplings in the gridpacks that were used to produce all LO HH MC samples for 2016, 2017, and 2018.
   *     The effect of the bug is detailed in these presentations:
   *       https://indico.cern.ch/event/762185/contributions/3194682/attachments/1744114/2822965/29_10_2018_HH_becnhmarks_v2.pdf
   *       https://indico.cern.ch/event/996685/contributions/4251752/attachments/2198363/3717406/HH_bbWW_LOtoNLOreweighting_2021Mar01.pdf
   *
   * Because of the bug in the Higgs boson couplings, the LO HH MC samples for 2016, 2017, and 2018 always need to be processed for SM + all 12 BMs
   * and then the weights returned by this function needs to be applied to all events in these samples.
   * In order to obtain a prediction for a SM HH signal, you need to process the SM + all 12 BMs LO HH MC samples 
   * and apply the weight obtained for "bmName" = "SM" when processing each sample,
   * then hadd the datacard/BDT training Ntuple ROOT files.
   *
   */
  double
  getWeight(const std::string & bmName,
            double mHH,
            double cosThetaStar,
            bool isDEBUG = false) const;

  /**
   * @brief Get single reWeight
   *
   * The purpose of this function is to reweight events in the SM + all 12 BMs LO HH MC samples 
   * from the case of SM kinematics to one of the 12 BM scenarios.
   * Note that in this case, the product of weights obtained by getWeight("SM", ...) times  getReWeight("BM1", ...)
   * needs to be applied to all events in the SM + all 12 BMs LO HH MC samples,
   * i.e. the function getReWeight(...) always needs to be used together with the function getWeight(...).
   *
   */
  double
  getReWeight(const std::string & bmName,
              double mHH,
              double cosThetaStar,
              bool isDEBUG = false) const;

  static const std::vector<double> & klJHEP();
  static const std::vector<double> & ktJHEP();
  static const std::vector<double> & c2JHEP();
  static const std::vector<double> & cgJHEP();
  static const std::vector<double> & c2gJHEP();
  static const std::vector<double> & normJHEP();

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

#endif // HHWeightInterfaceLO_h
