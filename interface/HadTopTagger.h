#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

// forward declarations
class TMVAInterface;

enum { kXGB_CSVsort4rd };

class HadTopTagger
{
public:
  HadTopTagger(void) ;
  ~HadTopTagger();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<int, double>
  operator()(const RecoJet & recBJet,
             const RecoJet & recWJet1,
             const RecoJet & recWJet2,
             bool & calculate_matching,
             bool & isGenMatched,
             double & genTopPt,
             const std::map<int, Particle::LorentzVector> & genVar,
             const std::map<int, Particle::LorentzVector> & genVarAnti,
             const bool isDebug = false);

  const std::map<std::string, double> &
  mvaInputs() const;

protected:
  std::map<std::string, double> mvaInputsHTT;
  std::vector<std::string>      mvaInputsHTTSort;
  TMVAInterface * mva_xgb_HTT_CSVsort4rd_;

};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
