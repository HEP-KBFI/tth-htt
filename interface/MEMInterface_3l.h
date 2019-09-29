#ifndef tthAnalysis_HiggsToTauTau_MEMInterface_3l_h
#define tthAnalysis_HiggsToTauTau_MEMInterface_3l_h

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

#include <string>

// forward declarations
class HypIntegrator;
class Permutations;
class TBenchmark;
class RecoLepton;
class RecoJet;

class MEMInterface_3l
{
public:
  MEMInterface_3l(const std::string & configFileName,
                  int era);
  ~MEMInterface_3l();

  /**
   * @brief Calculates output of MEM integration.
   * @param pointers to leading, subleading and third lepton, MET and
   *        MET covariance matrix, collections of b-tagged jets and non-b-tagged jets
   * @return object with         MVA output
   */
  MEMOutput_3l
  operator()(const RecoLepton * selLepton_lead,
             const RecoLepton * selLepton_sublead,
             const RecoLepton * selLepton_third,
             const RecoMEt & met,
             const std::vector<const RecoJet *> & selJets) const;

private:
  int nhyp_;
  std::string * shyp_;
  int * hyp_;
  int * nPointsHyp_;
  int * index_hyp_;
  mutable HypIntegrator * hypIntegrator_;
  mutable Permutations * MEMpermutations_;
  mutable Permutations * MEMpermutationsTTH_;
  mutable Permutations * MEMpermutationsTTbar_;
  TBenchmark * clock_;
};

#endif // MEMInterface_3l_h
