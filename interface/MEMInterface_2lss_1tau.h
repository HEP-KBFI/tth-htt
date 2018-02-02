#ifndef tthAnalysis_HiggsToTauTau_MEMInterface_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMInterface_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

// forward declarations
class RunConfig;
class TBenchmark;
class RecoLepton;
class RecoHadTau;
class RecoJet;

class MEMInterface_2lss_1tau
{
public:
  MEMInterface_2lss_1tau(const std::string & configFileName);
  ~MEMInterface_2lss_1tau();

  /**
   * @brief Calculates output of MEM integration.
   * @param pointers to leading and subleading lepton, hadronic tau, MET and
   *        MET covariance matrix, collections of b-tagged jets and non-b-tagged jets
   * @return object with         MVA output
   */
  MEMOutput_2lss_1tau
  operator()(const RecoLepton * selLepton_lead,
             const RecoLepton * selLepton_sublead,
             const RecoHadTau * selHadTau,
             const RecoMEt & met,
             const std::vector<const RecoJet *> & selJets) const;

private:
  RunConfig * config_;
  TBenchmark * clock_;
};

#endif // MEMInterface_2lss_1tau_h
