#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h"

#include "TFile.h"
#include "TF1.h"
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <iostream>


MVAInputVarTransformer::MVAInputVarTransformer(const std::vector<std::string> & mvaInputVariables,
		       const std::string & fitFunctionFileName)
  : mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(fitFunctionFileName)  
{

  TFile* fitFuncFile = TFile::Open(fitFunctionFileName_.c_str(), "read"); // Opens file for reading only 

  if(fitFuncFile == NULL){                                                                                                                                                                  
    std::cout<<"Invalid File Name/ File Does not exist" << std::endl;                                                                                                                           
    exit(EXIT_FAILURE);                                                                                                                                                                           
  }

  for(unsigned int i=0; i<mvaInputVariables_.size(); i++){
    std::string var_name = mvaInputVariables_[i]; 
    mvaInputs_reweighted_.insert(std::pair<std::string, double>(var_name, -1.0)); // Initializing the std::map
    if(var_name != "gen_mHH"){
      std::string fitFuncName = "fitFunction_" + var_name;
      TF1* fitFunc = (TF1*)fitFuncFile->Get(fitFuncName.c_str()); // Accessing the function
      TF1* fitFunc_copy = (TF1*)fitFunc->Clone();
      fitFuncMap_.insert(std::make_pair(var_name, fitFunc_copy));
    }
  } 
  fitFuncFile->Close();
}

MVAInputVarTransformer::~MVAInputVarTransformer()
{}

std::map<std::string, double> MVAInputVarTransformer::TransformMVAInputVars(const std::map<std::string, double> & mvaInputs) const
{
  
  double gen_mHH = mvaInputs.at("gen_mHH"); // Accessing the gen_mHH value  
  
  for(std::map<std::string, double>::const_iterator it = mvaInputs.begin(); it != mvaInputs.end(); it++){
    if(it->first != "gen_mHH"){ 
      std::string var_name = it->first; // Key
      TF1* fitFunc = fitFuncMap_.at(var_name);
      double scale_factor = fitFunc->Eval(gen_mHH);
      double old_value = mvaInputs.at(var_name);
      double new_value = old_value/scale_factor;
      mvaInputs_reweighted_.at(var_name) = new_value;
    }else{
      mvaInputs_reweighted_.at("gen_mHH") = gen_mHH;
    }
  }

  return mvaInputs_reweighted_;
}              
