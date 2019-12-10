#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_2017_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_2017_h

#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_Base.h"

class Data_to_MC_CorrectionInterface_2017
  : virtual public Data_to_MC_CorrectionInterface_Base
{
public:
  Data_to_MC_CorrectionInterface_2017(const edm::ParameterSet & cfg);
  ~Data_to_MC_CorrectionInterface_2017() override;

  //-----------------------------------------------------------------------------
  // trigger efficiency turn-on curves for Spring16 non-reHLT MC
  double
  getWeight_leptonTriggerEff() const override;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for electron and muon trigger efficiency
  double
  getSF_leptonTriggerEff(TriggerSFsys central_or_shift) const override;
  //-----------------------------------------------------------------------------
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_2017_h
