#ifndef tthAnalysis_HiggsToTauTau_SubjetBtagSF_h
#define tthAnalysis_HiggsToTauTau_SubjetBtagSF_h

#include <CondFormats/BTauObjects/interface/BTagEntry.h> // BTagEntry::OperatingPoint::OP_MEDIUM, BTagEntry::JetFlavor

// forward declarations
class GenParticle;
class RecoJetAK8;
class RecoSubjetAK8;
class TFile;
class lutWrapperBase;
class BTagCalibration;
class BTagCalibrationReader;
enum class Era;
enum class SubjetBtagSys;

class SubjetBtagSF
{
public:
  /**
   * @brief ctor for class that computes subjet b-tagging SFs
   * @param era Era (2016, 2017 or 2018)
   * @param procName Unique process name (needed for MC efficiency)
   * @param wp b-tagging working point (WP), defaults to medium
   */
  SubjetBtagSF(Era era,
               const std::string & procName,
               BTagEntry::OperatingPoint wp = BTagEntry::OperatingPoint::OP_MEDIUM);

  ~SubjetBtagSF();

  /**
   * @brief Record the gen particles subjet for dR-matching to AK8 subjets
   * @param genParticles The list of gen particles
   * @return this pointer
   */
  SubjetBtagSF * const
  addGenParticles(const std::vector<GenParticle> & genParticles);

  /**
   * @brief Record the AK8 subjets from which the b-tagging SF is derived
   * @param fatJet The AK8 jet, the subjet of which we want to b-tag
   * @return this pointer
   */
  SubjetBtagSF * const
  addSubjets(const RecoJetAK8 * const fatJet);

  /**
   * @brief Retrieve b-tagging SF computed with method 1a of
   *        https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods
   * @param option Central, up- or down-shift
   * @return The subjet b-tagging SF
   */
  double
  get_sf(SubjetBtagSys option);

  /**
   * @brief For clearing the list of gen particles and subjets
   */
  SubjetBtagSF * const
  reset();
protected:
  /**
   * @brief Auxiliary function for performing dR-matching of
   *        gen particles to AK8 subjets
   */
  void
  get_flavors();

  static std::map<int, BTagEntry::JetFlavor> flavorMap_;

  double btag_wp_;
  std::vector<GenParticle> genParticles_;
  std::vector<const RecoSubjetAK8 *> subjets_;
  std::map<std::string, TFile *> inputFiles_;
  std::map<int, lutWrapperBase *> effMaps_;
  BTagCalibration * calibration_;
  BTagCalibrationReader * reader_;
  std::vector<int> flavors_;
};

#endif // tthAnalysis_HiggsToTauTau_SubjetBtagSF_h
