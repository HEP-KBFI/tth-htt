#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

Data_to_MC_CorrectionInterface_2018::Data_to_MC_CorrectionInterface_2018(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}

Data_to_MC_CorrectionInterface_2018::~Data_to_MC_CorrectionInterface_2018()
{}

double
Data_to_MC_CorrectionInterface_2018::getWeight_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_hadTauID_and_Iso() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_eToTauFakeRate() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_muToTauFakeRate() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2018 era"
  ;
}
