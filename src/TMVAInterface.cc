#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" 

#include "FWCore/Utilities/interface/Exception.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

TMVAInterface::TMVAInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables, const std::vector<std::string>& spectators)
  : mva_(0)
  , isBDTTransform_(false) 
{
  LocalFileInPath mvaFileName_fip(mvaFileName);
  mvaFileName_ = mvaFileName_fip.fullPath();
  TMVA::Tools::Instance();
  mva_ = new TMVA::Reader("!V:!Silent");
  for ( std::vector<std::string>::const_iterator mvaInputVariable = mvaInputVariables.begin();
	mvaInputVariable != mvaInputVariables.end(); ++mvaInputVariable ) {
    mvaInputVariables_[*mvaInputVariable] = -1.;
    mva_->AddVariable(*mvaInputVariable, &mvaInputVariables_[*mvaInputVariable]);
  }
  for ( std::vector<std::string>::const_iterator spectator = spectators.begin();
	spectator != spectators.end(); ++spectator ) {
    mva_->AddSpectator(*spectator, &spectators_[*spectator]);
  }
  mva_->BookMVA("BDTG", mvaFileName_);
}

TMVAInterface::~TMVAInterface()
{
  delete mva_;
}

double
TMVAInterface::operator()(const std::map<std::string, double>& mvaInputs) const
{
  //std::cout << "<TMVAInterface::operator()>:" << std::endl;
  //std::cout << "mvaFileName = " << mvaFileName_ << std::endl;
  for ( std::map<std::string, Float_t>::iterator mvaInputVariable = mvaInputVariables_.begin();
	mvaInputVariable != mvaInputVariables_.end(); ++mvaInputVariable ) {
    std::map<std::string, double>::const_iterator mvaInput = mvaInputs.find(mvaInputVariable->first);
    if ( mvaInput != mvaInputs.end() ) {
      mvaInputVariable->second = mvaInput->second;
      //std::cout << " " << mvaInputVariable->first << " = " << mvaInputVariable->second << std::endl;
    } else {
      throw cms::Exception("TMVAInterface::operator()")
	<< "Missing value for MVA input variable = '" << mvaInputVariable->first << "' !!\n";
    }
  }

  double mvaOutput = mva_->EvaluateMVA("BDTG");
  if ( isBDTTransform_ ) {
    mvaOutput = 1./(1. + sqrt((1. - mvaOutput)/(1. + mvaOutput)));
  }
  //std::cout << "mvaOutput = " << mvaOutput << std::endl;

  return mvaOutput;
}

