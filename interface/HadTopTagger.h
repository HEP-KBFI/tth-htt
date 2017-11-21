#ifndef tthAnalysis_HiggsToTauTau_HadTopTagger_h
#define tthAnalysis_HiggsToTauTau_HadTopTagger_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface

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
  HadTopTagger(const std::string& mvaFileNameWithKinFit,const std::string& mvaFileNameNoKinFit);
  ~HadTopTagger();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
  std::vector<double> operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2);

  bool isTruth3Jet(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2,\
					//std::vector<const RecoJet*> selJets,
					std::vector<GenParticle> genTopQuarks, std::vector<GenParticle> genBJets,std::vector<GenParticle> genWBosons,\
					std::vector<GenParticle> genWJets, std::vector<bool>& truth_);

  std::vector<Particle::LorentzVector> Particles(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2);
  const std::vector<std::string>& mvaInputVariables() const;

  const std::map<std::string, double>& mvaInputs() const;

  const HadTopKinFit* kinFit() const;

 protected:
  HadTopKinFit* kinFit_;
  const char* mvaFileNameWithKinFit_;
  const char* mvaFileNameNoKinFit_;

  std::vector<std::string> mvaInputVariables_;
  TMVAInterface* mva_;
  std::map<std::string, double> mvaInputsWithKinFit_;
  std::map<std::string, double> mvaInputsNoKinFit_;
  double mvaOutput_;
};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
