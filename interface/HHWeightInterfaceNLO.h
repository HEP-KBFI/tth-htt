#ifndef tthAnalysis_HiggsToTauTau_HHWeightInterfaceNLO_h
#define tthAnalysis_HiggsToTauTau_HHWeightInterfaceNLO_h

/**
 * @brief Compute weights to reweight leading-order (LO) non-resonant HH signal MC samples to next-to-leading order (NLO).
 *        The code for the reweighting is based on code ( https://github.com/pmandrik/VSEVA/tree/master/HHWWgg/reweight ) 
 *        developed for the CMS HH->WWgammagamma analysis, using LO and NLO cross-sections 
 *        documented in the arXiv paper https://arxiv.org/pdf/1806.05162.pdf
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"      // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k2016, Era::k2017, Era::k2018

#include <TH1.h> // TH1
#include <TH2.h> // TH2

#include <vector> // std::vector
#include <string> // std::string
#include <map>    // std::map

class HHWeightInterfaceNLO
{
 public:
  HHWeightInterfaceNLO(Era era, bool apply_coupling_fix_CMS = false, double max_reWeight = 10., bool isDEBUG = false);
  ~HHWeightInterfaceNLO();

  /**
   * @brief Get single Weight
   *
   * The purpose of this function is to reweight the kinematics of events in the LO HH MC samples to the distribution
   * in gen_mHH and cos(theta*) computed at NLO accuracy.
   *
   * The function getWeight_V1(...) returns the weights documented in the arXiv paper https://arxiv.org/pdf/1806.05162.pdf,
   * which are parametrized as function of the observable gen_mHH only, i.e. the distribution in cos(theta*) is not reweighted to NLO accuracy.
   * The function getWeight_V2(...) extends the reweighting to both observables gen_mHH and cos(theta*),
   * and extendds the reweighting in gen_mHH to higher mass (up to 5 TeV, compared to 1040 GeV in the getWeight_V1(...) function)
   *
   * Note: The weights returned by the functions getWeight_V1(...) and getWeight_V2(...) are meant to be used in combination 
   *       with the weights obtained by the function HHWeightInterfaceLO::getWeight(...).
   */
  double
  getWeight_V1(const std::string & bmName,
               double mHH,
               double cosThetaStar,
               bool isDEBUG = false) const;

  double
  getWeight_V2(const std::string & bmName,
               double mHH,
               double cosThetaStar,
               bool isDEBUG = false) const;

  /**
   * @brief Get single reWeight
   *
   * The purpose of this function is to switch the NLO corrections from the case of SM kinematics 
   * to the kinematics corresponding to one of the 12 BM scenarios documented in the arXiv paper https://arxiv.org/abs/1507.02245
   *
   * Note: The weights returned by the functions getReWeight_V1(...) and getReWeight_V2(...) are meant to be used in combination 
   *       with the weights obtained by the functions
   *         HHWeightInterfaceLO::getWeight(...) * HHWeightInterfaceLO::getReWeight(...) * HHWeightInterfaceNLO::getWeight(...).
   *
   */
  double
  getReWeight_V1(const std::string & bmName,
                 double mHH,
                 double cosThetaStar,
                 bool isDEBUG = false) const;

  double
  getReWeight_V2(const std::string & bmName,
                 double mHH,
                 double cosThetaStar,
                 bool isDEBUG = false) const;//std::cout << "line #" << idxLine << ": line = " << line << std::endl;


 private:
  LocalFileInPath xsecFileName_V1_lo_;
  LocalFileInPath xsecFileName_V1_nlo_;

  std::map<std::string, const TH1 *> dXsec_V1_lo_;  // key = bmName
  std::map<std::string, const TH1 *> dXsec_V1_nlo_; // key = bmName
  std::map<std::string, const TH1 *> weights_V1_; // key = bmName

  LocalFileInPath xsecFileName_V2_lo_;
  LocalFileInPath xsecFileName_V2_nlo_;

  std::map<std::string, const TH2 *> dXsec_V2_lo_;  // key = bmName
  std::map<std::string, const TH2 *> dXsec_V2_nlo_; // key = bmName
  std::map<std::string, const TH2 *> weights_V2_; // key = bmName

  Era era_;
  bool apply_coupling_fix_CMS_;

  double max_reWeight_;
  
  bool isDEBUG_;
};

#endif // HHWeightInterfaceNLO_h
