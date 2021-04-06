#ifndef tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h
#define tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

enum class HHWeightInterfaceNLOMode { none, v1, v2 };

class HHWeightInterfaceCouplings
{
public:
  HHWeightInterfaceCouplings(const edm::ParameterSet & cfg);
  ~HHWeightInterfaceCouplings() {}

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

  static const std::size_t nof_JHEP;
  static const std::vector<double> klJHEP;
  static const std::vector<double> ktJHEP;
  static const std::vector<double> c2JHEP;
  static const std::vector<double> cgJHEP;
  static const std::vector<double> c2gJHEP;
  static const std::vector<double> normJHEP;

  std::vector<double>
  kl() const;

  std::vector<double>
  kt() const;

  std::vector<double>
  c2() const;

  std::vector<double>
  cg() const;

  std::vector<double>
  c2g() const;

  std::vector<double>
  norm() const;

  HHWeightInterfaceNLOMode
  nlo_mode() const;

private:
  void
  loadScanFile(const std::string & filePath,
               const std::string & prefix,
               int indx,
               bool isDEBUG);

  static std::string
  getWeightName(const std::string & suffix);

  std::vector<double> kl_;
  std::vector<double> kt_;
  std::vector<double> c2_;
  std::vector<double> cg_;
  std::vector<double> c2g_;
  std::vector<double> norm_;
  std::vector<std::string> bmNames_;
  std::vector<std::string> bmWeightNames_;

  HHWeightInterfaceNLOMode nlo_mode_;
};

#endif // tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h
