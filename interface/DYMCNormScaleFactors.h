#ifndef tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h
#define tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

// forward declarations
class TFile;

class DYMCNormScaleFactors
{
public:
  DYMCNormScaleFactors(int era, int dyMCNormScaleFactors_option, bool debug = false);
  ~DYMCNormScaleFactors();

  // SFs applied to Drell-Yan MC, derived by Christian in Z->ll+jets events

  double
    getWeight(const std::vector<GenParticle>& genTauLeptons, int nJets, int nBLoose, int nBMedium) const;

protected:
  int era_;
  int central_or_shift_;
  bool debug_;

};

#endif // tthAnalysis_HiggsToTauTau_DYMCNormScaleFactors_h
