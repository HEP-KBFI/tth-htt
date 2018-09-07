#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_2016_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_2016_h

#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_Base.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase

class Data_to_MC_CorrectionInterface_2016
  : virtual public Data_to_MC_CorrectionInterface_Base
{
public:
  Data_to_MC_CorrectionInterface_2016(const edm::ParameterSet & cfg);
  ~Data_to_MC_CorrectionInterface_2016() override;

  //-----------------------------------------------------------------------------
  // trigger efficiency turn-on curves for Spring16 non-reHLT MC
  double
  getWeight_leptonTriggerEff() const override;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for electron and muon trigger efficiency
  double
  getSF_leptonTriggerEff() const override;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC corrections for hadronic tau identification efficiency,
  // and for e->tau and mu->tau misidentification rates
  double
  getSF_hadTauID_and_Iso() const override;

  double
  getSF_eToTauFakeRate() const override;

  double
  getSF_muToTauFakeRate() const override;
  //-----------------------------------------------------------------------------

protected:
  // data/MC corrections for trigger efficiencies in 2016 data
  lutWrapperBase * effTrigger_ee_;
  lutWrapperBase * effTrigger_em_;
  lutWrapperBase * effTrigger_mm_;
  lutWrapperBase * effTrigger_3l_;

  vLutWrapperBase effTrigger_1e_data_;
  vLutWrapperBase effTrigger_1e_mc_;
  vLutWrapperBase effTrigger_1m_data_;
  vLutWrapperBase effTrigger_1m_mc_;
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_2016_h
