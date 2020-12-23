#ifndef tthAnalysis_HiggsToTauTau_HHWeightInterfaceLOtoNLO_h
#define tthAnalysis_HiggsToTauTau_HHWeightInterfaceLOtoNLO_h

/**
 * @brief Compute weights to reweight leading-order (LO) non-resonant HH signal MC samples to next-to-leading order (NLO).
 *        The code for the reweighting is based on code ( https://github.com/pmandrik/VSEVA/tree/master/HHWWgg/reweight ) 
 *        developed for the CMS HH->WWgammagamma analysis, using LO and NLO cross-sections 
 *        documented in the arXiv paper https://arxiv.org/pdf/1806.05162.pdf
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <TH1.h> // TH1

#include <vector> // std::vector
#include <string> // std::string
#include <map>    // std::map

class HHWeightInterfaceLOtoNLO
{
 public:
  HHWeightInterfaceLOtoNLO(double max_reWeight = 10., bool isDEBUG = false);
  ~HHWeightInterfaceLOtoNLO();

  /**
   * @brief Get single reWeight
   */
  double
  getReWeight(const std::string & bmName,
              double mHH,
              double cosThetaStar,
              bool isDEBUG = false) const;

 private:
  LocalFileInPath xsecFileName_lo_;
  LocalFileInPath xsecFileName_nlo_;

  std::map<std::string, const TH1 *> dXsec_lo_;  // key = bmName
  std::map<std::string, const TH1 *> dXsec_nlo_; // key = bmName
  std::map<std::string, const TH1 *> reWeights_; // key = bmName

  double max_reWeight_;
  
  bool isDEBUG_;
};

#endif // HHWeightInterfaceLOtoNLO_h
