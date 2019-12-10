#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h" // MVAInputVarTransformer

#include <TMVA/Tools.h> // TMVA::Tools::Instance()
#include <TMVA/Reader.h> // TMVA::Reader

#include <assert.h>

TMVAInterface::TMVAInterface(const std::string & mvaFileName,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::vector<std::string> & spectators)
  : mode_(Mode::k_old)
  , mva_(nullptr)
  , mva_odd_(nullptr)
  , mva_even_(nullptr)
  , isBDTTransform_(false)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_old)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

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


TMVAInterface::TMVAInterface(const std::string & mvaFileName_odd,
                             const std::string & mvaFileName_even,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::vector<std::string> & spectators)
  : mode_(Mode::k_odd_even)
  , mva_(nullptr)
  , mva_odd_(nullptr)
  , mva_even_(nullptr)
  , isBDTTransform_(false)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_odd_even)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  const LocalFileInPath mvaFileName_odd_fip(mvaFileName_odd);
  mvaFileName_odd_ = mvaFileName_odd_fip.fullPath();

  const LocalFileInPath mvaFileName_even_fip(mvaFileName_even);
  mvaFileName_even_ = mvaFileName_even_fip.fullPath();

  TMVA::Tools::Instance();
  mva_odd_ = new TMVA::Reader("!V:!Silent");

  TMVA::Tools::Instance();
  mva_even_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariables_[mvaInputVariable] = -1.;
    mva_odd_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
    mva_even_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
  }

  for(const std::string & spectator: spectators)
  {
    mva_odd_->AddSpectator(spectator, &spectators_[spectator]);
    mva_even_->AddSpectator(spectator, &spectators_[spectator]);
  }
  mva_odd_->BookMVA("BDTG", mvaFileName_odd_);
  mva_even_->BookMVA("BDTG", mvaFileName_even_);
}

TMVAInterface::TMVAInterface(const std::string & mvaFileName,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::string & fitFunctionFileName,
                             const std::vector<std::string> & spectators)
  : mode_(Mode::k_old)
  , mva_(nullptr)
  , mva_odd_(nullptr)
  , mva_even_(nullptr)
  , isBDTTransform_(false)
  , fitFunctionFileName_(fitFunctionFileName)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_old)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  if (fitFunctionFileName_ != "")
  {
    Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables, fitFunctionFileName_); // Intializing the new map and extracts the TF1s
  }

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

TMVAInterface::TMVAInterface(const std::string & mvaFileName_odd,
                             const std::string & mvaFileName_even,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::string & fitFunctionFileName,
                             const std::vector<std::string> & spectators)

  : mode_(Mode::k_odd_even)
  , mva_(nullptr)
  , mva_odd_(nullptr)
  , mva_even_(nullptr)
  , isBDTTransform_(false)
  , fitFunctionFileName_(fitFunctionFileName)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_odd_even)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  if (fitFunctionFileName_ != "")
  {
    Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables, fitFunctionFileName_);
  }

  const LocalFileInPath mvaFileName_odd_fip(mvaFileName_odd);
  mvaFileName_odd_ = mvaFileName_odd_fip.fullPath();

  const LocalFileInPath mvaFileName_even_fip(mvaFileName_even);
  mvaFileName_even_ = mvaFileName_even_fip.fullPath();

  TMVA::Tools::Instance();
  mva_odd_ = new TMVA::Reader("!V:!Silent");

  TMVA::Tools::Instance();
  mva_even_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariables_[mvaInputVariable] = -1.;
    mva_odd_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
    mva_even_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
  }

  for(const std::string & spectator: spectators)
  {
    mva_odd_->AddSpectator(spectator, &spectators_[spectator]);
    mva_even_->AddSpectator(spectator, &spectators_[spectator]);
  }
  mva_odd_->BookMVA("BDTG", mvaFileName_odd_);
  mva_even_->BookMVA("BDTG", mvaFileName_even_);
}


TMVAInterface::~TMVAInterface()
{
  delete mva_;
  delete mva_odd_;
  delete mva_even_;
  delete Transform_Ptr_;
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
TMVAInterface::operator()(const std::map<std::string, double> & mvaInputs,
                          int event_number) const
{
    std::map<std::string, double> mvaInputs_final;
    if(fitFunctionFileName_ != "")
    {
      mvaInputs_final = Transform_Ptr_->TransformMVAInputVars(mvaInputs); // Re-weight Input Var.s
    }
    else
    {
      mvaInputs_final = mvaInputs;
    }

    if(event_number % 2)
    {
      return this->operator()(mvaInputs_final, mva_odd_);
    }
    else
    {
      return this->operator()(mvaInputs_final, mva_even_);
    }
}

double
TMVAInterface::operator()(const std::map<std::string, double> & mvaInputs) const
{
    std::map<std::string, double> mvaInputs_final;
    if(fitFunctionFileName_ != "")
    {
      mvaInputs_final = Transform_Ptr_->TransformMVAInputVars(mvaInputs);       // Re-weight Input Var.s
    }
    else
    {
      mvaInputs_final = mvaInputs;
    }
    return this->operator()(mvaInputs_final, mva_);
}


double
TMVAInterface::operator()(const std::map<std::string, double> & mvaInputs,
                          const TMVA::Reader * mva) const
{
  for(auto & mvaInputVariable: mvaInputVariables_)
  {
    if(mvaInputs.count(mvaInputVariable.first))
    {
      mvaInputVariable.second = mvaInputs.at(mvaInputVariable.first);
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << mvaInputVariable.first << '\'';
    }
  }

  // Casting mva from "const TMVA::Reader*" to "TMVA::Reader*" (since EvaluateMVA() doesn't accept const input)
  double mvaOutput = (const_cast<TMVA::Reader*>(mva))->EvaluateMVA("BDTG");
  if(isBDTTransform_)
  {
    mvaOutput = 1. / (1. + std::sqrt((1. - mvaOutput) / (1. + mvaOutput)));
  }

  //std::cout << "TMVA: mvaOutput " << mvaOutput << '\n';
  return mvaOutput;
}
