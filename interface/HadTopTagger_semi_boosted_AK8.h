#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_semi_boosted_AK8_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_semi_boosted_AK8_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"
//#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGenTop...
#include <map>

// forward declarations
//class HadTopKinFit;
class TMVAInterface;
class XGBInterface;

enum {
  kXGB_semi_boosted_AK8_no_kinFit
};

class HadTopTagger_semi_boosted_AK8
{
public:
  HadTopTagger_semi_boosted_AK8(void) ;
  ~HadTopTagger_semi_boosted_AK8();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<int, double>
  operator()(
    const RecoJetAK8 & jet_ptrsAK8, const RecoJet & b_jet_candidate,
    bool & calculate_matching, bool & isGenMatched,
    double & genTopPt,
    std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti
  );

  const std::map<std::string, double> &
  mvaInputs() const;

protected:

  std::map<std::string, double> mvaInputsHTT_AK8;
  std::vector<std::string>      mvaInputsHTT_AK8Sort;
  TMVAInterface * mva_xgb_HTT_AK8_;

};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
