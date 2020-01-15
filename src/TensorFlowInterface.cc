#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#pragma GCC diagnostic pop

#include <boost/algorithm/string.hpp> // boost::contains()

#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h" // MVAInputVarTransformer

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName_odd,
                    const std::vector<std::string> & mvaInputVariables,
                    const std::vector<std::string> classes,
                    const std::string & mvaFileName_even,
                    const std::string & fitFunctionFileName)
  : classes_(classes)
  , mvaFileName_odd_(mvaFileName_odd)
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , n_input_layer_odd(0)
  , n_output_layer_odd(0)
  , mvaFileName_even_(mvaFileName_even)
  , graphDef_even_(nullptr)
  , session_even_(nullptr)
  , n_input_layer_even(0)
  , n_output_layer_even(0)
  , mvaInputVariables_(mvaInputVariables)
  , fitFunctionFileName_(fitFunctionFileName)
  , Transform_Ptr_(nullptr)
  , isDEBUG_(false)
{

  if(! fitFunctionFileName_.empty())
  {
    // Intializing the new map and extracts the TF1s
    Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables_, LocalFileInPath(fitFunctionFileName_).fullPath());
  }

// loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");

  graphDef_odd_ = tensorflow::loadGraphDef(LocalFileInPath(mvaFileName_odd_).fullPath());
  session_odd_ = tensorflow::createSession(graphDef_odd_);

  if(! mvaFileName_even_.empty())
  {
    std::cout << "Loaded Odd Evt. No. file: " << mvaFileName_odd_ << '\n';
    graphDef_even_ = tensorflow::loadGraphDef(LocalFileInPath(mvaFileName_even_).fullPath());
    session_even_ = tensorflow::createSession(graphDef_even_);
    std::cout << "Loaded Even Evt. No. file: " << mvaFileName_even_ << '\n';
  }
  else
  {
    std::cout << "Loaded file: " << mvaFileName_odd_ << '\n';
  }

  // getting elements to evaluate -- the number of the input/output layer deppends of how the model was exported
  int shape_variables_odd = 0;
  for(int idx_node = 0; idx_node < graphDef_odd_->node_size(); idx_node++)
  {
    input_layer_name_odd  = graphDef_odd_->node(idx_node).name();
    const bool is_input = boost::contains(input_layer_name_odd, "_input");
    if(is_input)
    {
      n_input_layer_odd = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read input layer "<< input_layer_name_odd << " " << n_input_layer_odd << '\n';
      }

      const auto & shape_odd = graphDef_odd_->node(idx_node).attr().at("shape").shape();
      if(isDEBUG_)
      {
        std::cout << "read input layer shape  " << shape_odd.dim_size() << '\n';
      }

      shape_variables_odd = static_cast<int>(shape_odd.dim(1).size());
      if(isDEBUG_)
      {
        std::cout << "read input layer shape length "<< shape_variables_odd << '\n';
      }
      break;
    }
  }

  if(! mvaFileName_even_.empty())
  {
    int shape_variables_even = 0;
    for(int idx_node = 0; idx_node < graphDef_even_->node_size(); idx_node++)
    {
      input_layer_name_even  = graphDef_even_->node(idx_node).name();
      const bool is_input = boost::contains(input_layer_name_even, "_input");
      if(is_input)
      {
        n_input_layer_even = idx_node;
        if(isDEBUG_)
        {
          std::cout << "read input layer "<< input_layer_name_even << " " << n_input_layer_even << '\n';
        }

        const auto & shape_even = graphDef_even_->node(idx_node).attr().at("shape").shape();
        if(isDEBUG_)
        {
          std::cout << "read input layer shape  " << shape_even.dim_size() << '\n';
        }

        shape_variables_even = static_cast<int>(shape_even.dim(1).size());
        if(isDEBUG_)
        {
          std::cout << "read input layer shape length "<< shape_variables_even << '\n';
        }
        break;
      }
    }
    if(shape_variables_even != static_cast<int>(mvaInputVariables_.size()))
    {
      throw cmsException(this)
        << "number of variables declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
           "the given version (" << shape_variables_even << ')'
      ;
    }
  }

  if(! mvaFileName_even_.empty() && shape_variables_odd != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of variables declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables_odd << ')'
    ;
  }

  //  int shape_classes = 0;
  std::string last_layer =  (classes.size() > 0) ? "/Softmax" : "/Sigmoid";
  for(int idx_node = 0; idx_node < graphDef_odd_->node_size(); idx_node++)
  {
    output_layer_name_odd  = graphDef_odd_->node(idx_node).name();

    const bool is_output = boost::contains(output_layer_name_odd, last_layer);
    if(is_output)
    {
      n_output_layer_odd = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read output layer "<< output_layer_name_odd << " " << idx_node << '\n';
      }
      break;
    }
  }

  if(! mvaFileName_even_.empty())
  {
    for(int idx_node = 0; idx_node < graphDef_even_->node_size(); idx_node++)
    {
      output_layer_name_even  = graphDef_even_->node(idx_node).name();
      const bool is_output = boost::contains(output_layer_name_even, last_layer);
      if(is_output)
      {
        n_output_layer_even = idx_node;
        if(isDEBUG_)
        {
          std::cout << "read output layer "<< output_layer_name_even << " " << idx_node << '\n';
        }
        break;
      }
    }
  }
}

TensorFlowInterface::~TensorFlowInterface()
{
  tensorflow::closeSession(session_odd_);
  delete session_odd_;
  delete graphDef_odd_;
  tensorflow::closeSession(session_even_);
  delete session_even_;
  delete graphDef_even_;
}

std::map<std::string, double>
TensorFlowInterface::operator()(const std::map<std::string, double> & mvaInputs, int event_number) const
{

  std::map<std::string, double> mvaInputs_final;
  if(! fitFunctionFileName_.empty())
  {
    mvaInputs_final = Transform_Ptr_->TransformMVAInputVars(mvaInputs);       // Re-weight Input Var.s
  }
  else
  {
    mvaInputs_final = mvaInputs;
  }
  if(isDEBUG_)
  {
    std::cout << "Input variables ";
    for (auto elem : mvaInputs_final ) std::cout << elem.first << " " << elem.second << "\n";
    std::cout << '\n';
  }

  const int nofInputs = mvaInputVariables_.size();

  tensorflow::Tensor inputs(tensorflow::DT_FLOAT, { 1, nofInputs});

  // the order of input variables should be the same as during the training
  for(int idx_input = 0; idx_input < nofInputs; ++idx_input)
  {
    if(mvaInputs_final.count(mvaInputVariables_[idx_input]))
    {
      inputs.matrix<float>()(0, idx_input) = static_cast<float>(mvaInputs_final.at(mvaInputVariables_.at(idx_input)));
      if(isDEBUG_)
      {
        std::cout << mvaInputVariables_[idx_input]  << " = " << mvaInputs_final.at(mvaInputVariables_.at(idx_input)) << '\n';
      }
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << mvaInputVariables_[idx_input] << '\''
        ;
    }
  }

  tensorflow::GraphDef * graphDef = (event_number % 2 || event_number == -1) ? graphDef_odd_ : graphDef_even_;

  const int node_count = graphDef->node_size();
  if(isDEBUG_)
  {
    for (int idx_node = 0; idx_node < node_count; ++idx_node)
    {
      const auto node = graphDef->node(idx_node);
      std::cout << "Names : " << node.name() << '\n';
    }
  }

  std::vector<tensorflow::Tensor> outputs;
  const int n_input_layer  = (event_number % 2 || event_number == -1) ? n_input_layer_odd  : n_input_layer_even;
  const int n_output_layer = (event_number % 2 || event_number == -1) ? n_output_layer_odd : n_output_layer_even;
  if(isDEBUG_)
  {
    std::cout
          << "start run " << event_number << " " << graphDef->node(n_input_layer).name()
          << ' '          << graphDef->node(n_output_layer).name()
          << '\n';
  }
  tensorflow::run(
    session_odd_,
    { { graphDef->node(n_input_layer).name(), inputs } },
    { graphDef->node(n_output_layer).name() },
    &outputs
  );

  // store the output
  std::map<std::string, double> mvaOutputs;
  if(! classes_.empty())
  {
    for(unsigned int idx_class = 0; idx_class < classes_.size(); idx_class++)
    {
      mvaOutputs[classes_[idx_class]] = outputs[0].matrix<float>()(0, idx_class);
    }
  }
  else
  {
    mvaOutputs = {
      {"output", outputs[0].matrix<float>()(0, 0)}
    };
  }
  if(isDEBUG_)
  {
    std::cout << "Output " << outputs.size() << " " << outputs[0].matrix<float>()(0, 0) << '\n';
  }
  return mvaOutputs;
}
