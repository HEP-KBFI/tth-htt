#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_2tau_trigger_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_2tau_trigger_h

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase
#include "tthAnalysis/HiggsToTauTau/interface/TauTriggerSFInterface.h" // TauTriggerSFInterface, TriggerSFsys

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
  setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi, int hadTau1_decayMode,
             double hadTau2_pt, double hadTau2_eta, double hadTau2_phi, int hadTau2_decayMode);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for trigger efficiency 
  double
  getSF_triggerEff(TriggerSFsys central_or_shift) const;
  //-----------------------------------------------------------------------------

protected:
  bool
  check_triggerSFsys_opt(TriggerSFsys central_or_shift) const;

  std::string era_str_;
  int era_;
  std::string hadTauSelection_;
  bool isDEBUG_;
  std::vector<int> allowedDecayModes_;

  bool isTriggered_2tau_;

  int hadTau1_genPdgId_;
  double hadTau1_pt_;
  double hadTau1_eta_;
  double hadTau1_phi_;
  int hadTau1_decayMode_;

  int hadTau2_genPdgId_;
  double hadTau2_pt_;
  double hadTau2_eta_;
  double hadTau2_phi_;
  int hadTau2_decayMode_;

  //-----------------------------------------------------------------------------
  // data/MC corrections for trigger efficiencies

  TauTriggerSFInterface effTrigger_tauLeg_;
  //-----------------------------------------------------------------------------
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_0l_2tau_trigger_h
