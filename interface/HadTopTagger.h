#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface

class HadTopTagger
{
 public:
  HadTopTagger(const std::string& mvaFileName = "");
  ~HadTopTagger();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  double
  operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2);

  const std::vector<std::string>& mvaInputVariables() const;

  const std::map<std::string, double>& mvaInputs() const;

  const HadTopKinFit* kinFit() const;
  
 protected:
  HadTopKinFit* kinFit_;

  std::vector<std::string> mvaInputVariables_;
  TMVAInterface* mva_;
  std::map<std::string, double> mvaInputs_;
  double mvaOutput_;
};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
