#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

class HadTopTagger
{
 public:
  HadTopTagger(const std::string&, const std::string&, const std::string&);
  ~HadTopTagger();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  bool operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2, std::vector<double>& result);

  void isTruth3Jet(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2,
		   std::vector<GenParticle> genTopQuarks, std::vector<GenParticle> genBJets,std::vector<GenParticle> genWBosons,
		   std::vector<GenParticle> genWJets, std::vector<bool>& truth);

  std::vector<Particle::LorentzVector> Particles(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2);
  const std::vector<std::string>& mvaInputVariables() const;

  const std::map<std::string, double>& mvaInputs() const;

  const HadTopKinFit* kinFit() const;

 protected:
  HadTopKinFit* kinFit_;
  //const char*
  //const char* mvaFileNameWithKinFitRead;
  //std::string mvaFileName_hadTopTagger_tmvaRead;
  //std::string mvaFileNameNoKinFitRead;

  std::map<std::string, double> mvaInputsWithKinFit;
  std::map<std::string, double> mvaInputsNoKinFit;

  std::vector<std::string> mvaInputsWithKinFitSort;
  //double mva_hadTopTagger_xgb( const std::map<std::basic_string<char>>&  , const std::vector<std::string>& ) ;
  //double  mva_hadTopTagger_tmva(const std::map<std::basic_string<char>>& mvaFileName_hadTopTagger_tmvaRead , std::vector<std::string>& mvaInputsWithKinFitSort) ;
  std::vector<std::string> mvaFileNameNoKinFitSort;
  //double  mva_hadTopTagger_xgb_2(const std::map<std::basic_string<char>>& mvaFileNameNoKinFitRead, const std::vector<std::string>& mvaFileNameNoKinFitSort)  ;

  std::vector<std::string> mvaInputVariables_;
  TMVAInterface* mva_;
  double mvaOutput_;
  //XGBInterface* xgb_;
  XGBInterface* mva_hadTopTagger_xgb_;
  XGBInterface* mva_hadTopTagger_xgb_2_;
  TMVAInterface* mva_hadTopTagger_tmva_;


};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
