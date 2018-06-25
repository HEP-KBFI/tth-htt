#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_2tau_trigger_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_2tau_trigger_h

#include "tthAnalysis/TauTriggerSFs2017/interface/TauTriggerSFs2017.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase

class Data_to_MC_CorrectionInterface_0l_2tau_trigger
{
public:
  Data_to_MC_CorrectionInterface_0l_2tau_trigger(const edm::ParameterSet & cfg);
  ~Data_to_MC_CorrectionInterface_0l_2tau_trigger();

  //-----------------------------------------------------------------------------
  // set HLT trigger bits
  // (to be called once per event, before calling any of the getSF.. functions)
  void
  setTriggerBits(bool isTriggered_2tau);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // set hadTau pT, eta and decay mode
  // (to be called once per event, before calling any of the getSF.. functions)
  void
  setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi,
             double hadTau2_pt, double hadTau2_eta, double hadTau2_phi);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // trigger efficiency turn-on curves for Spring16 non-reHLT MC (not yet implemented)
  double
  getWeight_triggerEff() const;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for trigger efficiency 
  double
  getSF_triggerEff() const;
  //-----------------------------------------------------------------------------

private:

  //-----------------------------------------------------------------------------
  // data/MC corrections for trigger efficiencies in 2017 ReReco data and Summer17 MC

  TauTriggerSFs2017* effTrigger_tauLeg_;
  //-----------------------------------------------------------------------------

  int era_;
  std::string hadTauSelection_;
  bool isDEBUG_;
  int triggerSF_option_;

  bool isTriggered_2tau_;

  double hadTau1_pt_;
  double hadTau1_eta_;
  double hadTau1_phi_;
  double hadTau2_pt_;
  double hadTau2_eta_;
  double hadTau2_phi_;
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_0l_2tau_trigger_h
