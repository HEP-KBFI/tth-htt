#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

// forward declarations
class HadTopKinFit;
class TMVAInterface;
class XGBInterface;

enum { kXGB_multilep, kXGB_CSVsort4rd };

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
             bool & calculate_matching, bool & isGenMatched,
             double & genTopPt,
             std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti,
             bool massCut
           );

  const std::map<std::string, double> &
  mvaInputs() const;

protected:

  std::map<std::string, double> mvaInputsHTT_multilep;
  std::vector<std::string>      mvaInputsHTT_multilepSort;
  TMVAInterface * mva_hadTopTagger_multilep_;

  std::map<std::string, double> mvaInputsHTT;
  std::vector<std::string>      mvaInputsHTTSort;
  TMVAInterface * mva_xgb_HTT_CSVsort4rd_;

};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
