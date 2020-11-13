#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowInterfaceLBN.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#pragma GCC diagnostic pop

#include <boost/algorithm/string.hpp> // boost::contains()

#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarTransformer.h" // MVAInputVarTransformer

TensorFlowInterfaceLBN::TensorFlowInterfaceLBN(const std::string & mvaFileName_odd,
                                               const std::vector<std::string> & ll_particleNames,
                                               const std::vector<std::string> & hl_mvaInputVariables,
                                               const std::vector<std::string> & classes,
                                               const std::string & mvaFileName_even,
                                               bool isDEBUG)
  : classes_(classes)
  , mvaFileName_odd_(mvaFileName_odd)
  , graphDef_odd_(nullptr)
  , session_odd_(nullptr)
  , mvaFileName_even_(mvaFileName_even)
  , graphDef_even_(nullptr)
  , session_even_(nullptr)
  , ll_particleNames_(ll_particleNames)
  , hl_mvaInputVariables_(hl_mvaInputVariables)
  , isDEBUG_(isDEBUG)
{
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
}

TensorFlowInterfaceLBN::~TensorFlowInterfaceLBN()
{
  tensorflow::closeSession(session_odd_);
  delete session_odd_;
  delete graphDef_odd_;
  tensorflow::closeSession(session_even_);
  delete session_even_;
  delete graphDef_even_;
}

std::map<std::string, double>
TensorFlowInterfaceLBN::operator()(const std::map<std::string, const Particle*> & ll_particles, const std::map<std::string, double> & hl_mvaInputs, int event_number) const
{
  // set low-level (ll) input variables
  tensorflow::TensorShape ll_shape{{ 1, (int)ll_particleNames_.size(), 4 }}; // batch size x nof particles x 4-momentum
  tensorflow::Tensor ll_inputs(tensorflow::DT_FLOAT, ll_shape);
  for(int idx_particle = 0; idx_particle < (int)ll_particleNames_.size(); ++idx_particle)
  {
    const std::string& particleName = ll_particleNames_[idx_particle];
    std::map<std::string, const Particle*>::const_iterator ll_particle = ll_particles.find(particleName);
    if(ll_particle != ll_particles.end())
    {
      const Particle::LorentzVector& ll_particleP4 = ll_particle->second->p4();
      for(int idx_4vector = 0; idx_4vector < 4; ++idx_4vector)
      {
        double value = 0.;
        if      ( idx_4vector == 0 ) value = ll_particleP4.energy();
        else if ( idx_4vector == 1 ) value = ll_particleP4.px();
        else if ( idx_4vector == 2 ) value = ll_particleP4.py();
        else if ( idx_4vector == 3 ) value = ll_particleP4.pz();
        else assert(0);       
        ll_inputs.tensor<float, 3>()(0, idx_particle, idx_4vector) = value;
      }
    }
    else 
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input particle = '" << particleName << '\''
        ;
    }
  }

  // set high-level (hl) input variables
  tensorflow::TensorShape hl_shape{{ 1, (int)hl_mvaInputVariables_.size() }};
  tensorflow::Tensor hl_inputs(tensorflow::DT_FLOAT, hl_shape);
  for(int idx_input = 0; idx_input < (int)hl_mvaInputVariables_.size(); ++idx_input)
  {
    const std::string& hl_mvaInputVariable = hl_mvaInputVariables_[idx_input];
    std::map<std::string, double>::const_iterator hl_mvaInput = hl_mvaInputs.find(hl_mvaInputVariable);
    if(hl_mvaInput != hl_mvaInputs.end())
    {
      hl_inputs.matrix<float>()(0, idx_input) = hl_mvaInput->second;
      if(isDEBUG_)
      {
        std::cout << hl_mvaInputVariable << " = " << hl_mvaInput->second << '\n';
      }
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Missing value for MVA input variable = '" << hl_mvaInputVariable << '\''
        ;
    }
  }

  tensorflow::Session * session   = (event_number % 2 || event_number == -1) ? session_odd_ : session_even_;
  //tensorflow::GraphDef * graphDef = (event_number % 2 || event_number == -1) ? graphDef_odd_ : graphDef_even_;

  std::vector<tensorflow::Tensor> outputs;
  tensorflow::run(
    session,
    { { "LL", ll_inputs }, { "HL", hl_inputs } }, 
    { "Identity" }, 
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
    for(const auto & kv: mvaOutputs)
    {
      std::cout << "Output " << kv.first << " = " << kv.second << '\n';
    }
  }
  return mvaOutputs;
}
