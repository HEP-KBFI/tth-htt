#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // get_fullpath()
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
  , mvaInputVariables_(mvaInputVariables)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_old)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  mvaFileName_ = get_fullpath(mvaFileName);

  TMVA::Tools::Instance();
  mva_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariableMap_[mvaInputVariable] = -1.;
    mva_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
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
  , mvaInputVariables_(mvaInputVariables)
  , Transform_Ptr_(nullptr)
{

  if(mode_ != Mode::k_odd_even)
  {
    throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
  }

  mvaFileName_odd_ = get_fullpath(mvaFileName_odd);
  mvaFileName_even_ = get_fullpath(mvaFileName_even);

  TMVA::Tools::Instance();
  mva_odd_ = new TMVA::Reader("!V:!Silent");

  TMVA::Tools::Instance();
  mva_even_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariableMap_[mvaInputVariable] = -1.;
    mva_odd_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
    mva_even_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
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
  , mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(get_fullpath(fitFunctionFileName))
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

  mvaFileName_ = get_fullpath(mvaFileName);

  TMVA::Tools::Instance();
  mva_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariableMap_[mvaInputVariable] = -1.;
    mva_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
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
  , mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(get_fullpath(fitFunctionFileName))
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

  mvaFileName_odd_ = get_fullpath(mvaFileName_odd);
  mvaFileName_even_ = get_fullpath(mvaFileName_even);

  TMVA::Tools::Instance();
  mva_odd_ = new TMVA::Reader("!V:!Silent");

  TMVA::Tools::Instance();
  mva_even_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariableMap_[mvaInputVariable] = -1.;
    mva_odd_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
    mva_even_->AddVariable(mvaInputVariable, &mvaInputVariableMap_[mvaInputVariable]);
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
                          int event_number, const bool multiclass) const
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
      return this->operator()(mvaInputs_final, mva_odd_, multiclass);
    }
    else
    {
      return this->operator()(mvaInputs_final, mva_even_, multiclass);
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
                          const TMVA::Reader * mva, const bool multiclass) const
{
  for(auto & mvaInputVariable: mvaInputVariableMap_)
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

  if ( multiclass ) 
  {
    mvamulticlsOutput_ = (const_cast<TMVA::Reader*>(mva))->EvaluateMulticlass("BDTG");
    return std::distance(mvamulticlsOutput_.begin(),std::max_element(mvamulticlsOutput_.begin(),mvamulticlsOutput_.end()));
  } 
  else 
  {
    mvamulticlsOutput_.clear();
  }

  // Casting mva from "const TMVA::Reader*" to "TMVA::Reader*" (since EvaluateMVA() doesn't accept const input)
  double mvaOutput = (const_cast<TMVA::Reader*>(mva))->EvaluateMVA("BDTG");
  //std::cout << "TMVA: mvaOutput (bef. transform.) " << mvaOutput << '\n';
  if(isBDTTransform_)
  {
    mvaOutput = 1. / (1. + std::sqrt((1. - mvaOutput) / (1. + mvaOutput)));
  }

  //std::cout << "TMVA: mvaOutput " << mvaOutput << '\n';
  return mvaOutput;
}

const std::vector<std::string> &
TMVAInterface::mvaInputVariables() const
{
  return mvaInputVariables_;
}

const std::vector<float> & 
TMVAInterface::mvamulticlsOutput() const
{
  return mvamulticlsOutput_;
}
