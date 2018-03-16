#ifndef tthAnalysis_HiggsToTauTau_HadTopTaggerFill_h
#define tthAnalysis_HiggsToTauTau_HadTopTaggerFill_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

// forward declarations
class HadTopKinFit;
class MVAInputVarHistManager;

class HadTopTaggerFill
{
public:
  HadTopTaggerFill();
  ~HadTopTaggerFill();

  /**
   * @brief Calculates MVA output.
   * @param mvaInputs Values of MVA input variables (stored in std::map with key = MVA input variable name)
   * @return          MVA output
   */
	// Case III] Non-boosted top 
  double
  operator()(const RecoJet & recBJet,
             const RecoJet & recWJet1,
             const RecoJet & recWJet2);

  std::vector<bool>
  isTruth(const RecoJet & recBJet,
          const RecoJet & recWJet1,
          const RecoJet & recWJet2,
          const std::vector<GenParticle> & genTopQuarks,
          const std::vector<GenParticle> & genBJets,
          const std::vector<GenParticle> & genWBosons);

  std::vector<bool>
  isTruth3Jet(const RecoJet & recBJet,
              const RecoJet & recWJet1,
              const RecoJet & recWJet2,
              const std::vector<GenParticle> & genTopQuarks,
              const std::vector<GenParticle> & genBJets,
              const std::vector<GenParticle> & genWBosons,
              const std::vector<GenParticle> & genWJets);

  const std::vector<std::string> &
  defineBinnings(MVAInputVarHistManager * mvaInputHistManager);

  const std::map<std::string, double> &
  mvaInputs() const;

  const HadTopKinFit *
  kinFit() const;


  // Case I] Boosted top with merged b and W jets from top
	double
	operator()(const RecoSubjetHTTv2 & recBJet,
						 const RecoSubjetHTTv2 & recWJet1,
						 const RecoSubjetHTTv2 & recWJet2);
	
	// Case II] Boosted W with merged WJet1 and WJet2 and separate b-jet
	double
	operator()(const RecoJet & recBJet,
						 const RecoSubjetAK12 & recWJet1,
						 const RecoSubjetAK12  & recWJet2);

	
protected:
  HadTopKinFit * kinFit_;
  std::vector<std::string> mvaInputVariables_;
  std::map<std::string, double> mvaInputs_;

private:

  struct MVAInputVarHistManagerWrapper
  {
    MVAInputVarHistManagerWrapper(HadTopTaggerFill * outer,
                                  MVAInputVarHistManager * mvaInputHistManager);

    void
    defineBinning(const std::string & histogramName,
                  int numBinsX,
                  double xMin,
                  double xMax);
    HadTopTaggerFill * outer_;
    MVAInputVarHistManager * mvaInputHistManager_;
  };

};

#endif // tthAnalysis_HiggsToTauTau_HadTopTagger_h
