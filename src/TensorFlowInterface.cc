#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
//#include "tensorflow/core/util/memmapped_file_system.h"

#include <boost/filesystem.hpp> // boost::filesystem::
#include "boost/algorithm/string.hpp"

#include <fstream> // std::ifstream
#include <streambuf> // std::istreambuf_iterator<>()

bool isDEBUG = false;

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName,
                             const std::vector<std::string> & mvaInputVariables,
                             const std::vector<std::string> classes,
                             std::vector<double> mvaInputVariables_mean,
                             std::vector<double> mvaInputVariables_var
                           )
  : session_(nullptr)
  , mvaInputVariables_(mvaInputVariables)
  , classes_(classes)
{
  // loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");
  const LocalFileInPath mvaFileName_fip(mvaFileName);
  mvaFileName_ = mvaFileName_fip.fullPath();
  graphDef_ = tensorflow::loadGraphDef(mvaFileName_);
  session_ = tensorflow::createSession(graphDef_);
  std::cout << "Loaded: " << mvaFileName_ <<"\n";

  mvaInputVariables_mean_ = mvaInputVariables_mean;
  mvaInputVariables_var_ = mvaInputVariables_var;

  // getting elements to evaluate -- the number of the input/output layer deppends of how the model was exported
  int shape_variables = 0;
  for (int ii = 0; ii < graphDef_->node_size(); ii++) {
    //input_layer_name  = graphDef_->node(graphDef_->node_size() - 1).name();
    input_layer_name  = graphDef_->node(ii).name();
    bool is_input = boost::contains(input_layer_name, "_input");
    if (is_input) {
      n_input_layer = ii;
      if (isDEBUG) std::cout << "read input layer "<< input_layer_name << " " << n_input_layer << std::endl;
      const auto& shape = graphDef_->node(ii).attr().at("shape").shape();
      if (isDEBUG) std::cout << "read input layer shape  " << shape.dim_size() << std::endl;
      shape_variables = int(shape.dim(1).size());
      if (isDEBUG) std::cout << "read input layer shape length "<< shape_variables << std::endl;
      break;
    }
  }
  if( shape_variables != int(mvaInputVariables_.size()) ) throw cms::Exception("TensorFlowInterface") << "number of classes declared ("<< int(mvaInputVariables_.size()) << ") does not match the expected inputs for the given version (" << shape_variables <<")";

  //int shape_classes = 0;
  for (int ii = 0; ii < graphDef_->node_size(); ii++) {
    output_layer_name  = graphDef_->node(ii).name();
    bool is_output = boost::contains(output_layer_name, "/Softmax");
    if (is_output) {
      n_output_layer = ii;
      if (isDEBUG) std::cout << "read output layer "<< output_layer_name << " " << ii << std::endl;
      //const auto& shape = graphDef_->node(ii-1).attr().at("shape").shape();
      //std::cout << "read output layer shape  " << shape.dim_size() << std::endl;
      //shape_classes = int(shape.dim(0).size());
      break;
    }
  }
  //if(shape_classes != int(classes_.size())) throw cms::Exception("TensorFlowInterface") << "number of classes declared ("<< int(classes_.size()) << ") does not match the expected inputs for the given version (" << shape_classes <<")";

}

TensorFlowInterface::~TensorFlowInterface()
{
  tensorflow::closeSession(session_);
  delete session_;
  delete graphDef_;
}


std::map<std::string, double>
TensorFlowInterface::operator()(const std::map<std::string, double> & mvaInputs) const
{

  const int NumberOfInputs = mvaInputVariables_.size();
  tensorflow::Tensor inputs(tensorflow::DT_FLOAT, { 1, NumberOfInputs});
  // the order of input variables should be the same as during the training
  for (int i = 0; i < NumberOfInputs; i++) {
    if(mvaInputs.count(mvaInputVariables_[i]))
    {
      if ( mvaInputVariables_mean_.size() > 0) {
      inputs.matrix<float>()(0, i) = (
        float(mvaInputs.at(mvaInputVariables_[i])) - mvaInputVariables_mean_[i]
      )/mvaInputVariables_var_[i];
      if ( isDEBUG ) std::cout << mvaInputVariables_[i]
      << " = " << mvaInputs.at(mvaInputVariables_[i])
      << " = " << mvaInputVariables_mean_[i]
      << " = " << mvaInputVariables_var_[i]
      << std::endl;
    } else {
      inputs.matrix<float>()(0, i) = float(mvaInputs.at(mvaInputVariables_[i]));
      if (isDEBUG) std::cout << mvaInputVariables_[i]  << " = " << mvaInputs.at(mvaInputVariables_[i]) << std::endl;
    }
    }
    else
    {
      throw cms::Exception("TensorFlowInterface::operator()")
        << "Missing value for MVA input variable = '" << mvaInputVariables_[i] << "' !!\n";
    }
  }

  // evaluation
  int node_count = graphDef_->node_size();
  if (isDEBUG) for (int i = 0; i < node_count; i++)
  {
          auto n = graphDef_->node(i);
          std::cout<<"Names : "<< n.name() <<std::endl;
  }
  std::vector<tensorflow::Tensor> outputs;
  if (isDEBUG) std::cout << "start run "<< graphDef_->node(n_input_layer).name() << " " << graphDef_->node(n_output_layer).name()<< std::endl;
  tensorflow::run(session_, { { graphDef_->node(n_input_layer).name(), inputs } }, {graphDef_->node(n_output_layer).name() }, &outputs);
  // store the output
  std::map<std::string, double> mvaOutputs;
  for (unsigned int i = 0; i < classes_.size(); i++) mvaOutputs[classes_[i]] = outputs[0].matrix<float>()(0, i);
  return mvaOutputs;
}
