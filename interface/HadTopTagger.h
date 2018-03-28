#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

// forward declarations
class HadTopKinFit;
class TMVAInterface;

enum {
  kXGB_with_kinFit
};

class HadTopTagger
{
public:
  HadTopTagger(const std::string & mvaFileNameWithKinFit);
  ~HadTopTagger();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::map<int, double>
  operator()(const RecoJet & recBJet,
             const RecoJet & recWJet1,
             const RecoJet & recWJet2);

  const std::map<std::string, double> &
  mvaInputs() const;

  const HadTopKinFit *
  kinFit() const;

protected:
  HadTopKinFit * kinFit_;

  std::map<std::string, double> mvaInputsWithKinFit;
  std::vector<std::string> mvaInputsWithKinFitSort;

  TMVAInterface * mva_hadTopTagger_tmva_;
};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
