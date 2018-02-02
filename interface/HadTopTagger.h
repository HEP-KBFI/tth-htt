#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

// forward declarations
class HadTopKinFit;
class XGBInterface;
class TMVAInterface;

enum {
  kXGB_with_kinFit,
  kTMVA_with_kinFit,
  kXGB_no_kinFit
};

class HadTopTagger
{
public:
  HadTopTagger(const std::string & mvaFileNameWithKinFit,
               const std::string & mvaFileNameNoKinFit,
               const std::string & mvaFileName_hadTopTagger_tmva);
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
  std::map<std::string, double> mvaInputsNoKinFit;

  std::vector<std::string> mvaInputsWithKinFitSort;
  std::vector<std::string> mvaFileNameNoKinFitSort;

  XGBInterface * mva_hadTopTagger_xgb_withKinFit;
  TMVAInterface * mva_hadTopTagger_tmva_;
  XGBInterface * mva_hadTopTagger_xgb_noKinFit_;
};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
