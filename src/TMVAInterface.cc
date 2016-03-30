#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" 

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

TMVAInterface::TMVAInterface(const std::string& mvaFileName, const std::vector<std::string>& mvaInputVariables, const std::vector<std::string>& spectators)
  : mva_(0)
{
  edm::FileInPath mvaFileName_fip(mvaFileName);
  std::string mvaFileName_full = mvaFileName_fip.fullPath();
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
  mva_->BookMVA("BDTG", mvaFileName_full);
}

TMVAInterface::~TMVAInterface()
{
  delete mva_;
}

double
TMVAInterface::operator()(const std::map<std::string, double>& mvaInputs) const
{
  for ( std::map<std::string, Float_t>::iterator mvaInputVariable = mvaInputVariables_.begin();
	mvaInputVariable != mvaInputVariables_.end(); ++mvaInputVariable ) {
    std::map<std::string, double>::const_iterator mvaInput = mvaInputs.find(mvaInputVariable->first);
    if ( mvaInput != mvaInputs.end() ) {
      mvaInputVariable->second = mvaInput->second;
    } else {
      throw cms::Exception("TMVAInterface::operator()")
	<< "Missing value for MVA input variable = " << mvaInputVariable->first << " !!\n";
    }
  }

  double mvaOutput = mva_->EvaluateMVA("BDTG");
  return mvaOutput;
}

