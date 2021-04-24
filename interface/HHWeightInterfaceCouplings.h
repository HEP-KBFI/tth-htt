#ifndef tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h
#define tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

enum class HHWeightInterfaceNLOMode { none, v1, v2, v3 };

// forward declarations
class TH2;
class HHWeightInterfaceLO;

class HHWeightInterfaceCouplings
{
public:
  HHWeightInterfaceCouplings(const edm::ParameterSet & cfg);
  ~HHWeightInterfaceCouplings() {}

  /**
   * @brief Add a scan point
   * @param couplings (kl, kt, c2, cg, c2g)
   * @param name Unique label for the coupling array
   */
  void
  add(const std::array<double, 5> & couplings,
      const std::string & name);

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

  HHWeightInterfaceNLOMode
  nlo_mode() const;

  std::string
  denominator_file_lo() const;

  std::string
  denominator_file_nlo() const;

  std::string
  histtitle() const;

  static TH2 *
  loadDenominatorHist(const std::string & fileName,
                      const std::string & histTitle);

  static double
  getBinContent(const TH2 * const hist,
                double mHH,
                double cosThetaStar);

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
  std::vector<std::string> bmNames_;
  std::vector<std::string> bmWeightNames_;

  HHWeightInterfaceNLOMode nlo_mode_;
  const std::string denominator_file_lo_;
  const std::string denominator_file_nlo_;
  const std::string histtitle_;
};

#endif // tthAnalysis_HiggsToTauTau_HHWeightInterfaceCouplings_h
