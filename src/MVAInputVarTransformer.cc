#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h>

MVAInputVarTransformer::MVAInputVarTransformer(const std::vector<std::string> & mvaInputVariables,
                                               const std::string & fitFunctionFileName)
  : mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(fitFunctionFileName)  
{
  TFile * fitFuncFile = TFile::Open(fitFunctionFileName_.c_str(), "read");

  if(! fitFuncFile){
    throw cmsException(this, __func__, __LINE__)
      << "Invalid file name / file does not exist: " << fitFunctionFileName_ << '\n'
    ;
  }

  const std::string gen_mHH_str = "gen_mHH";
  for(const std::string & var_name: mvaInputVariables_)
  {
    mvaInputs_reweighted_[var_name] = -1.0;
    if(var_name != gen_mHH_str)
    {
      const std::string fitFuncName = "fitFunction_" + var_name;
      TF1 * fitFunc = static_cast<TF1 *>(fitFuncFile->Get(fitFuncName.c_str()));
      TF1 * fitFunc_copy = static_cast<TF1 * >(fitFunc->Clone());
      fitFuncMap_.insert(std::make_pair(var_name, fitFunc_copy));
    }
  } 
  fitFuncFile->Close();
}

MVAInputVarTransformer::~MVAInputVarTransformer()
{}

std::map<std::string, double>
MVAInputVarTransformer::TransformMVAInputVars(const std::map<std::string, double> & mvaInputs) const
{
  const double gen_mHH = mvaInputs.at("gen_mHH");
  for(const auto & it: mvaInputs)
  {
    if(it.first != "gen_mHH")
    {
      const std::string var_name = it.first; // Key
      TF1 * fitFunc = fitFuncMap_.at(var_name);
      const double scale_factor = fitFunc->Eval(gen_mHH);
      const double old_value = mvaInputs.at(var_name);
      const double new_value = old_value/scale_factor;
      mvaInputs_reweighted_[var_name] = new_value;
    }
    else
    {
      mvaInputs_reweighted_["gen_mHH"] = gen_mHH;
    }
  }

  return mvaInputs_reweighted_;
}              
