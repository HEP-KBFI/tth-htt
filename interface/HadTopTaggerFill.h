#ifndef tthAnalysis_HiggsToTauTau_HadTopTaggerFill_h
#define tthAnalysis_HiggsToTauTau_HadTopTaggerFill_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

// forward declarations
class HadTopKinFit;
class MVAInputVarHistManager;

class HadTopTaggerFill
{
public:
  HadTopTaggerFill();
  ~HadTopTaggerFill();

  void
  operator()(const Particle::LorentzVector & recBJet,
                               const Particle::LorentzVector & recWJet1,
                               const Particle::LorentzVector & recWJet2
                             );

  const std::vector<std::string> &
  defineBinnings(MVAInputVarHistManager * mvaInputHistManager);

  const std::map<std::string, double> &
  mvaInputs() const;

  const HadTopKinFit *
  kinFit() const;

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
