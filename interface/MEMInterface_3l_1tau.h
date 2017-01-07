#ifndef tthAnalysis_HiggsToTauTau_MEMInterface_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMInterface_3l_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l_1tau.h" // MEMOutput_3l_1tau

#include "tthAnalysis/tthMEM/interface/MEMInterface_3l1tau.h" // MEMInterface_3l1tau, MEMOutput_3l1tau

#include <TBenchmark.h> // TBenchmark

#include <memory> // std::unique_ptr<>

/**
 * @brief Class wrapping around the general-purpose MEM interface.
 */
class MEMInterface_3l_1tau
{
 public:
  MEMInterface_3l_1tau();
  ~MEMInterface_3l_1tau();

  /**
   * @brief Calculates output of MEM integration for 3l1tau channel.
   * @param selLepton_lead    Pointer to leading lepton
   * @param selLepton_sublead Pointer to subleading lepton
   * @param selLepton_third   Pointer to third lepton
   * @param selHadTau         Pointer to hadronic tau
   * @param met               MET (pt, phi and covariance matrix)
   * @param selJets           Vector of pointers to selected jet
   * @return Struct holding all calculated values
   */
  MEMOutput_3l_1tau
  operator()(const RecoLepton * selLepton_lead,
             const RecoLepton * selLepton_sublead,
             const RecoLepton * selLepton_third,
             const RecoHadTau * selHadTau,
             const RecoMEt & met,
             const std::vector<const RecoJet *> & selJets);

 private:
  std::unique_ptr<MEMInterface_3l1tau> mem_;

  TBenchmark* clock_;
};

#endif // tthAnalysis_HiggsToTauTau_MEMInterface_3l_1tau_h
