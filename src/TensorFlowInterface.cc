#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#pragma GCC diagnostic pop

#include <boost/algorithm/string.hpp> // boost::contains()

#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h" // MVAInputVarTransformer

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName,
                                         const std::vector<std::string> & mvaInputVariables,
                                         const std::vector<std::string> classes,
                                         const std::vector<double> & mvaInputVariables_mean,
                                         const std::vector<double> & mvaInputVariables_var)
  : mvaFileName_(LocalFileInPath(mvaFileName).fullPath())
  , graphDef_(nullptr)
  , session_(nullptr)
  , classes_(classes)
  , n_input_layer(0)
  , n_output_layer(0)
  , mvaInputVariables_(mvaInputVariables)
  , mvaInputVariables_mean_(mvaInputVariables_mean)
  , mvaInputVariables_var_(mvaInputVariables_var)
  , mvaFileName_odd_("")
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , n_input_layer_odd(0)
  , n_output_layer_odd(0)
  , mvaInputVariables_mean_odd_({})
  , mvaInputVariables_var_odd_({})
  , mvaFileName_even_("")
  , graphDef_even_(nullptr)  
  , session_even_(nullptr)
  , n_input_layer_even(0)
  , n_output_layer_even(0)
  , mvaInputVariables_mean_even_({})
  , mvaInputVariables_var_even_({})
  , fitFunctionFileName_("")
  , Transform_Ptr_(nullptr)
  , isDEBUG_(false)
{

  if(mode_ != Mode::k_old)
    {
      throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
    }

  // loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");

  graphDef_ = tensorflow::loadGraphDef(mvaFileName_);
  session_ = tensorflow::createSession(graphDef_);
  std::cout << "Loaded: " << mvaFileName_ << '\n';

  // getting elements to evaluate -- the number of the input/output layer deppends of how the model was exported
  int shape_variables = 0;
  for(int idx_node = 0; idx_node < graphDef_->node_size(); idx_node++)
  {
    input_layer_name  = graphDef_->node(idx_node).name();
    const bool is_input = boost::contains(input_layer_name, "_input");
    if(is_input)
    {
      n_input_layer = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read input layer "<< input_layer_name << " " << n_input_layer << '\n';
      }

      const auto & shape = graphDef_->node(idx_node).attr().at("shape").shape();
      if(isDEBUG_)
      {
        std::cout << "read input layer shape  " << shape.dim_size() << '\n';
      }

      shape_variables = static_cast<int>(shape.dim(1).size());
      if(isDEBUG_)
      {
        std::cout << "read input layer shape length "<< shape_variables << '\n';
      }
      break;
    }
  }

  if(shape_variables != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables << ')'
    ;
  }

  //  int shape_classes = 0;
  for (int idx_node = 0; idx_node < graphDef_->node_size(); idx_node++)
  {
    output_layer_name  = graphDef_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name, "/Softmax");
    if(is_output)
    {
      n_output_layer = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read output layer "<< output_layer_name << " " << idx_node << '\n';
      }
      break;
    }
  }
}

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName,
                                         const std::vector<std::string> & mvaInputVariables,
                                         const std::vector<std::string> classes,
					 const std::string & fitFunctionFileName,
                                         const std::vector<double> & mvaInputVariables_mean,
                                         const std::vector<double> & mvaInputVariables_var)
  : mvaFileName_(LocalFileInPath(mvaFileName).fullPath())
  , graphDef_(nullptr)
  , session_(nullptr)
  , classes_(classes)
  , n_input_layer(0)
  , n_output_layer(0)
  , mvaInputVariables_(mvaInputVariables)
  , mvaInputVariables_mean_(mvaInputVariables_mean)
  , mvaInputVariables_var_(mvaInputVariables_var)
  , mvaFileName_odd_("")
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , n_input_layer_odd(0)
  , n_output_layer_odd(0)
  , mvaInputVariables_mean_odd_({})
  , mvaInputVariables_var_odd_({})
  , mvaFileName_even_("")
  , graphDef_even_(nullptr)  
  , session_even_(nullptr)
  , n_input_layer_even(0)
  , n_output_layer_even(0)
  , mvaInputVariables_mean_even_({})
  , mvaInputVariables_var_even_({})
  , fitFunctionFileName_(fitFunctionFileName)
  , isDEBUG_(false)
{

  if(mode_ != Mode::k_old)
    {
      throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
    }

  Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables_, fitFunctionFileName_); // Intializing the new map and extracts the TF1s
  
  // loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");

  graphDef_ = tensorflow::loadGraphDef(mvaFileName_);
  session_ = tensorflow::createSession(graphDef_);
  std::cout << "Loaded: " << mvaFileName_ << '\n';

  // getting elements to evaluate -- the number of the input/output layer deppends of how the model was exported
  int shape_variables = 0;
  for(int idx_node = 0; idx_node < graphDef_->node_size(); idx_node++)
  {
    input_layer_name  = graphDef_->node(idx_node).name();
    const bool is_input = boost::contains(input_layer_name, "_input");
    if(is_input)
    {
      n_input_layer = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read input layer "<< input_layer_name << " " << n_input_layer << '\n';
      }

      const auto & shape = graphDef_->node(idx_node).attr().at("shape").shape();
      if(isDEBUG_)
      {
        std::cout << "read input layer shape  " << shape.dim_size() << '\n';
      }

      shape_variables = static_cast<int>(shape.dim(1).size());
      if(isDEBUG_)
      {
        std::cout << "read input layer shape length "<< shape_variables << '\n';
      }
      break;
    }
  }

  if(shape_variables != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables << ')'
    ;
  }

  //  int shape_classes = 0;
  for (int idx_node = 0; idx_node < graphDef_->node_size(); idx_node++)
  {
    output_layer_name  = graphDef_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name, "/Softmax");
    if(is_output)
    {
      n_output_layer = idx_node;
      if(isDEBUG_)
      {
        std::cout << "read output layer "<< output_layer_name << " " << idx_node << '\n';
      }
      break;
    }
  }
}

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName_odd,
					 const std::string & mvaFileName_even,
                                         const std::vector<std::string> & mvaInputVariables,
                                         const std::vector<std::string> classes,
                                         const std::vector<double> & mvaInputVariables_mean_odd,
					 const std::vector<double> & mvaInputVariables_mean_even,
                                         const std::vector<double> & mvaInputVariables_var_odd,
					 const std::vector<double> & mvaInputVariables_var_even)
  : mvaFileName_("")
  , graphDef_(nullptr)
  , session_(nullptr)
  , classes_(classes)
  , n_input_layer(0)
  , n_output_layer(0)
  , mvaInputVariables_(mvaInputVariables)
  , mvaInputVariables_mean_({})
  , mvaInputVariables_var_({})
  , mvaFileName_odd_(LocalFileInPath(mvaFileName_odd).fullPath())
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , n_input_layer_odd(0)
  , n_output_layer_odd(0)
  , mvaInputVariables_mean_odd_(mvaInputVariables_mean_odd)
  , mvaInputVariables_var_odd_(mvaInputVariables_var_odd)
  , mvaFileName_even_(LocalFileInPath(mvaFileName_even).fullPath())
  , graphDef_even_(nullptr)  
  , session_even_(nullptr)
  , n_input_layer_even(0)
  , n_output_layer_even(0)
  , mvaInputVariables_mean_even_(mvaInputVariables_mean_even)
  , mvaInputVariables_var_even_(mvaInputVariables_var_even)
  , fitFunctionFileName_("")
  , Transform_Ptr_(nullptr)
  , isDEBUG_(false)
{

  if(mode_ != Mode::k_odd_even)
    {
      throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
    }

  // loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");

  graphDef_odd_ = tensorflow::loadGraphDef(mvaFileName_odd_);
  session_odd_ = tensorflow::createSession(graphDef_odd_);
  std::cout << "Loaded Odd Evt. No. file: " << mvaFileName_odd_ << '\n';

  graphDef_even_ = tensorflow::loadGraphDef(mvaFileName_even_);
  session_even_ = tensorflow::createSession(graphDef_even_);
  std::cout << "Loaded Even Evt. No. file: " << mvaFileName_even_ << '\n';

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

  if(shape_variables_odd != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables_odd << ')'
    ;
  }

  if(shape_variables_even != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables_even << ')'
    ;
  }


  //  int shape_classes = 0;
  for (int idx_node = 0; idx_node < graphDef_odd_->node_size(); idx_node++)
  {
    output_layer_name_odd  = graphDef_odd_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name_odd, "/Softmax");
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

  for (int idx_node = 0; idx_node < graphDef_even_->node_size(); idx_node++)
  {
    output_layer_name_even  = graphDef_even_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name_even, "/Softmax");
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

TensorFlowInterface::TensorFlowInterface(const std::string & mvaFileName_odd,
					 const std::string & mvaFileName_even,
                                         const std::vector<std::string> & mvaInputVariables,
                                         const std::vector<std::string> classes,
					 const std::string & fitFunctionFileName,
                                         const std::vector<double> & mvaInputVariables_mean_odd,
					 const std::vector<double> & mvaInputVariables_mean_even,
                                         const std::vector<double> & mvaInputVariables_var_odd,
					 const std::vector<double> & mvaInputVariables_var_even)
  : mvaFileName_("")
  , graphDef_(nullptr)
  , session_(nullptr)
  , classes_(classes)
  , n_input_layer(0)
  , n_output_layer(0)
  , mvaInputVariables_(mvaInputVariables)
  , mvaInputVariables_mean_({})
  , mvaInputVariables_var_({})
  , mvaFileName_odd_(LocalFileInPath(mvaFileName_odd).fullPath())
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , n_input_layer_odd(0)
  , n_output_layer_odd(0)
  , mvaInputVariables_mean_odd_(mvaInputVariables_mean_odd)
  , mvaInputVariables_var_odd_(mvaInputVariables_var_odd)
  , mvaFileName_even_(LocalFileInPath(mvaFileName_even).fullPath())
  , graphDef_even_(nullptr)  
  , session_even_(nullptr)
  , n_input_layer_even(0)
  , n_output_layer_even(0)
  , mvaInputVariables_mean_even_(mvaInputVariables_mean_even)
  , mvaInputVariables_var_even_(mvaInputVariables_var_even)
  , fitFunctionFileName_(fitFunctionFileName)
  , Transform_Ptr_(nullptr)
  , isDEBUG_(false)
{

  if(mode_ != Mode::k_odd_even)
    {
      throw cmsException(this, __func__, __LINE__) << "Using wrong Mode for this constructor";
    }

  Transform_Ptr_ = new MVAInputVarTransformer(mvaInputVariables_, fitFunctionFileName_); // Intializing the new map and extracts the TF1s

// loading the model
  tensorflow::SessionOptions options;
  tensorflow::setThreading(options, 1, "no_threads");

  graphDef_odd_ = tensorflow::loadGraphDef(mvaFileName_odd_);
  session_odd_ = tensorflow::createSession(graphDef_odd_);
  std::cout << "Loaded Odd Evt. No. file: " << mvaFileName_odd_ << '\n';

  graphDef_even_ = tensorflow::loadGraphDef(mvaFileName_even_);
  session_even_ = tensorflow::createSession(graphDef_even_);
  std::cout << "Loaded Even Evt. No. file: " << mvaFileName_even_ << '\n';

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

  if(shape_variables_odd != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables_odd << ')'
    ;
  }

  if(shape_variables_even != static_cast<int>(mvaInputVariables_.size()))
  {
    throw cmsException(this)
      << "number of classes declared ("<< mvaInputVariables_.size() << ") does not match the expected inputs for "
         "the given version (" << shape_variables_even << ')'
    ;
  }


  //  int shape_classes = 0;
  for (int idx_node = 0; idx_node < graphDef_odd_->node_size(); idx_node++)
  {
    output_layer_name_odd  = graphDef_odd_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name_odd, "/Softmax");
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

  for (int idx_node = 0; idx_node < graphDef_even_->node_size(); idx_node++)
  {
    output_layer_name_even  = graphDef_even_->node(idx_node).name();
    const bool is_output = boost::contains(output_layer_name_even, "/Softmax");
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

TensorFlowInterface::~TensorFlowInterface()
{
  tensorflow::closeSession(session_);
  delete session_;
  delete graphDef_;
  tensorflow::closeSession(session_odd_);
  delete session_odd_;
  delete graphDef_odd_;
  tensorflow::closeSession(session_even_);
  delete session_even_;
  delete graphDef_even_;
}

std::map<std::string, double>
TensorFlowInterface::operator()(const std::map<std::string, double> & mvaInputs) const
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
  
  const int nofInputs = mvaInputVariables_.size();
  tensorflow::Tensor inputs(tensorflow::DT_FLOAT, { 1, nofInputs});

  // the order of input variables should be the same as during the training
  for(int idx_input = 0; idx_input < nofInputs; ++idx_input)
  {
    if(mvaInputs_final.count(mvaInputVariables_[idx_input]))
    {
      if(! mvaInputVariables_mean_.empty())
      {
        inputs.matrix<float>()(0, idx_input) = (
            static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input])) - mvaInputVariables_mean_[idx_input]
          ) / mvaInputVariables_var_[idx_input];

        if(isDEBUG_)
        {
          std::cout << mvaInputVariables_[idx_input]
            << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input])
            << " = " << mvaInputVariables_mean_[idx_input]
            << " = " << mvaInputVariables_var_[idx_input]
            << '\n'
          ;
        }
      }
      else
      {
        inputs.matrix<float>()(0, idx_input) = static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input]));
        if(isDEBUG_)
        {
          std::cout << mvaInputVariables_[idx_input]  << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input]) << '\n';
        }
      }
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << mvaInputVariables_[idx_input] << '\''
      ;
    }
  }

  // evaluation
  const int node_count = graphDef_->node_size();
  if(isDEBUG_)
  {
    for (int idx_node = 0; idx_node < node_count; ++idx_node)
    {
      const auto node = graphDef_->node(idx_node);
      std::cout << "Names : " << node.name() << '\n';
    }
  }

  std::vector<tensorflow::Tensor> outputs;
  if(isDEBUG_)
  {
    std::cout
      << "start run " << graphDef_->node(n_input_layer).name()
      << ' '          << graphDef_->node(n_output_layer).name()
      << '\n'
    ;
  }
  tensorflow::run(
    session_,
    { { graphDef_->node(n_input_layer).name(), inputs } },
    { graphDef_->node(n_output_layer).name() },
    &outputs
  );

  // store the output
  std::map<std::string, double> mvaOutputs;
  for(unsigned int idx_class = 0; idx_class < classes_.size(); idx_class++)
  {
    mvaOutputs[classes_[idx_class]] = outputs[0].matrix<float>()(0, idx_class);
  }

  return mvaOutputs;
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

  const int nofInputs = mvaInputVariables_.size();
  tensorflow::Tensor inputs_odd(tensorflow::DT_FLOAT, { 1, nofInputs});
  tensorflow::Tensor inputs_even(tensorflow::DT_FLOAT, { 1, nofInputs});

  std::vector<tensorflow::Tensor> outputs;
  std::map<std::string, double> mvaOutputs;

  if(event_number % 2)
  {// Odd 
    // the order of input variables should be the same as during the training
    for(int idx_input = 0; idx_input < nofInputs; ++idx_input)
      {
	if(mvaInputs_final.count(mvaInputVariables_[idx_input]))
	  {
	    if(! mvaInputVariables_mean_odd_.empty())
	      {
		inputs_odd.matrix<float>()(0, idx_input) = (static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input])) - mvaInputVariables_mean_odd_[idx_input]) 
		  / mvaInputVariables_var_odd_[idx_input];

		if(isDEBUG_)
		  {
		    std::cout << mvaInputVariables_[idx_input]
			      << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input])
			      << " = " << mvaInputVariables_mean_odd_[idx_input]
			      << " = " << mvaInputVariables_var_odd_[idx_input]
			      << '\n';
		  }
	      }
	    else
	      {
		inputs_odd.matrix<float>()(0, idx_input) = static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input]));
		if(isDEBUG_)
		  {
		    std::cout << mvaInputVariables_[idx_input]  << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input]) << '\n';
		  }
	      }
	  }
	else
	  {
	    throw cmsException(this, __func__, __LINE__)
	      << "Missing value for MVA input variable = '" << mvaInputVariables_[idx_input] << '\''
	      ;
	  }
      }

    // evaluation
    const int node_count = graphDef_odd_->node_size();
    if(isDEBUG_)
      {
	for (int idx_node = 0; idx_node < node_count; ++idx_node)
	  {
	    const auto node = graphDef_odd_->node(idx_node);
	    std::cout << "Names : " << node.name() << '\n';
	  }
      }

    // std::vector<tensorflow::Tensor> outputs;
    if(isDEBUG_)
      {
	std::cout
	  << "start run " << graphDef_odd_->node(n_input_layer_odd).name()
	  << ' '          << graphDef_odd_->node(n_output_layer_odd).name()
	  << '\n';
      }
    tensorflow::run(
		    session_odd_,
		    { { graphDef_odd_->node(n_input_layer_odd).name(), inputs_odd } },
		    { graphDef_odd_->node(n_output_layer_odd).name() },
		    &outputs
		    );

    // store the output
    //std::map<std::string, double> mvaOutputs;
    for(unsigned int idx_class = 0; idx_class < classes_.size(); idx_class++)
      {
	mvaOutputs[classes_[idx_class]] = outputs[0].matrix<float>()(0, idx_class);
      }
  }
  else
  { // Even 
    // the order of input variables should be the same as during the training
    for(int idx_input = 0; idx_input < nofInputs; ++idx_input)
      {
	if(mvaInputs_final.count(mvaInputVariables_[idx_input]))
	  {
	    if(! mvaInputVariables_mean_even_.empty())
	      {
		inputs_even.matrix<float>()(0, idx_input) = (static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input])) - mvaInputVariables_mean_even_[idx_input]) / mvaInputVariables_var_even_[idx_input];
		if(isDEBUG_)
		  {
		    std::cout << mvaInputVariables_[idx_input]
			      << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input])
			      << " = " << mvaInputVariables_mean_even_[idx_input]
			      << " = " << mvaInputVariables_var_even_[idx_input]
			      << '\n';
		  }
	      }
	    else
	      {
		inputs_even.matrix<float>()(0, idx_input) = static_cast<float>(mvaInputs_final.at(mvaInputVariables_[idx_input]));
		if(isDEBUG_)
		  {
		    std::cout << mvaInputVariables_[idx_input]  << " = " << mvaInputs_final.at(mvaInputVariables_[idx_input]) << '\n';
		  }
	      }
	  }
	else
	  {
	    throw cmsException(this, __func__, __LINE__)
	      << "Missing value for MVA input variable = '" << mvaInputVariables_[idx_input] << '\''
	      ;
	  }
      }

    // evaluation
    const int node_count = graphDef_even_->node_size();
    if(isDEBUG_)
      {
	for (int idx_node = 0; idx_node < node_count; ++idx_node)
	  {
	    const auto node = graphDef_even_->node(idx_node);
	    std::cout << "Names : " << node.name() << '\n';
	  }
      }

    // std::vector<tensorflow::Tensor> outputs;
    if(isDEBUG_)
      {
	std::cout
	  << "start run " << graphDef_even_->node(n_input_layer_even).name()
	  << ' '          << graphDef_even_->node(n_output_layer_even).name()
	  << '\n';
      }

    tensorflow::run(
		    session_even_,
		    { { graphDef_even_->node(n_input_layer_even).name(), inputs_even } },
		    { graphDef_even_->node(n_output_layer_even).name() },
		    &outputs
		    );

    // store the output
    //std::map<std::string, double> mvaOutputs;
    for(unsigned int idx_class = 0; idx_class < classes_.size(); idx_class++)
      {
	mvaOutputs[classes_[idx_class]] = outputs[0].matrix<float>()(0, idx_class);
      }
  }
  return mvaOutputs;
}
