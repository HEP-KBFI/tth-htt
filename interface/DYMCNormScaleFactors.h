#ifndef tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h
#define tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

// forward declarations
class TFile;

/**
 * @brief SFs applied to Drell-Yan MC, derived by Christian in Z->ll+jets events
 */
class DYMCNormScaleFactors
{
public:
  DYMCNormScaleFactors(int era,
                       int dyMCNormScaleFactors_option,
                       bool debug = false);
  ~DYMCNormScaleFactors();

  double
  getWeight(const std::vector<GenParticle> & genTauLeptons,
            int nJets,
            int nBLoose,
            int nBMedium) const;

  double
  getWeight(const std::vector<GenParticle> & genTauLeptons,
            int nJets,
            int nBLoose,
            int nBMedium,
            int central_or_shift) const;

protected:
  int era_;
  int central_or_shift_;
  bool debug_;

};

#endif // tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h
