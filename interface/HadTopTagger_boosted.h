#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_boosted_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_boosted_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"
//#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGenTop...
#include <map>

// forward declarations
//class HadTopKinFit;
class TMVAInterface;
class XGBInterface;

enum { kXGB_boosted_no_kinFit };

class HadTopTagger_boosted
{
public:
  HadTopTagger_boosted(void) ;
  ~HadTopTagger_boosted();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<int, double>
  operator()(
    const RecoJetHTTv2 & jet_HTTv2,
    bool & calculate_matching, bool & isGenMatched,
    double & genTopPt,
    std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti
  );

  const std::map<std::string, double> &
  mvaInputs() const;

protected:

  std::map<std::string, double> mvaInputsHTT;
  std::vector<std::string>      mvaInputsHTTSort;
  TMVAInterface * mva_xgb_HTT_highestCSV_;

};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
