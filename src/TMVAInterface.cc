#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" 

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMVA/Tools.h> // TMVA::Tools::Instance()
#include <TMVA/Reader.h> // TMVA::Reader

TMVAInterface::TMVAInterface(const std::string & mvaFileName,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::vector<std::string> & spectators)
  : mva_(nullptr)
  , isBDTTransform_(false) 
{
  const LocalFileInPath mvaFileName_fip(mvaFileName);
  mvaFileName_ = mvaFileName_fip.fullPath();

  TMVA::Tools::Instance();
  mva_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariables_[mvaInputVariable] = -1.;
    mva_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
  }

  for(const std::string & spectator: spectators)
  {
    mva_->AddSpectator(spectator, &spectators_[spectator]);
  }
  mva_->BookMVA("BDTG", mvaFileName_);
}

TMVAInterface::~TMVAInterface()
{
  delete mva_;
}

void
TMVAInterface::enableBDTTransform()
{
  isBDTTransform_ = true;
}

void
TMVAInterface::disableBDTTransform()
{
  isBDTTransform_ = false;
}

double
TMVAInterface::operator()(const std::map<std::string, double> & mvaInputs) const
{
  for(auto & mvaInputVariable: mvaInputVariables_)
  {
    if(mvaInputs.count(mvaInputVariable.first))
    {
      mvaInputVariable.second = mvaInputs.at(mvaInputVariable.first);
    }
    else
    {
      throw cmsException(this, __func__)
        << "Missing value for MVA input variable = '" << mvaInputVariable.first << "' !!\n";
    }
  }

  double mvaOutput = mva_->EvaluateMVA("BDTG");
  if(isBDTTransform_)
  {
    mvaOutput = 1. / (1. + std::sqrt((1. - mvaOutput) / (1. + mvaOutput)));
  }

  return mvaOutput;
}
