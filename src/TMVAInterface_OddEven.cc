#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface_OddEven.h" 

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMVA/Tools.h> // TMVA::Tools::Instance()
#include <TMVA/Reader.h> // TMVA::Reader

TMVAInterface_OddEven::TMVAInterface_OddEven(const std::string & mvaFileName_Odd,
                             const std::string & mvaFileName_Even,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::vector<std::string> & spectators)
  : mva_Odd_(nullptr)
  , mva_Even_(nullptr)
  , isBDTTransform_(false) 
{
  const LocalFileInPath mvaFileName_Odd_fip(mvaFileName_Odd);
  mvaFileName_Odd_ = mvaFileName_Odd_fip.fullPath();

  const LocalFileInPath mvaFileName_Even_fip(mvaFileName_Even);
  mvaFileName_Even_ = mvaFileName_Even_fip.fullPath();

  TMVA::Tools::Instance();
  mva_Odd_ = new TMVA::Reader("!V:!Silent");
  mva_Even_ = new TMVA::Reader("!V:!Silent");

  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    mvaInputVariables_[mvaInputVariable] = -1.;
    mva_Odd_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
    mva_Even_->AddVariable(mvaInputVariable, &mvaInputVariables_[mvaInputVariable]);
  }

  for(const std::string & spectator: spectators)
  {
    mva_Odd_->AddSpectator(spectator, &spectators_[spectator]);
    mva_Even_->AddSpectator(spectator, &spectators_[spectator]);
  }
  mva_Odd_->BookMVA("BDTG", mvaFileName_Odd_);
  mva_Even_->BookMVA("BDTG", mvaFileName_Even_);
}

TMVAInterface_OddEven::~TMVAInterface_OddEven()
{
  delete mva_Odd_;
  delete mva_Even_;
}

void
TMVAInterface_OddEven::enableBDTTransform()
{
  isBDTTransform_ = true;
}

void
TMVAInterface_OddEven::disableBDTTransform()
{
  isBDTTransform_ = false;
}

double
TMVAInterface_OddEven
::operator()(const std::map<std::string, double> & mvaInputs, const int & EventNumber) const
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

  double mvaOutput = -1.0;
  if(EventNumber % 2){ // Odd event number
    mvaOutput = mva_Odd_->EvaluateMVA("BDTG");
    //std::cout<< "mvaOutput Odd original " << mvaOutput << std::endl;
  }else{ // Even event number
    mvaOutput = mva_Even_->EvaluateMVA("BDTG");
    //std::cout<< "mvaOutput Even original " << mvaOutput << std::endl;
  }


  if(isBDTTransform_)
  {
    mvaOutput = 1. / (1. + std::sqrt((1. - mvaOutput) / (1. + mvaOutput)));
    //std::cout<< "mvaOutput transformed " << mvaOutput << std::endl;
  }

  return mvaOutput;
}
