#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile

typedef std::vector<double> vdouble;

JetToTauFakeRateInterface::JetToTauFakeRateInterface(const edm::ParameterSet& cfg, int central_or_shift)
  : inputFile_(0)
{
  std::string inputFileName = cfg.getParameter<std::string>("inputFileName");
  inputFile_ = openFile(edm::FileInPath(inputFileName));

  vdouble absEtaBins = cfg.getParameter<vdouble>("absEtaBins");
  int numAbsEtaBins = absEtaBins.size() - 1;
  if ( !(numAbsEtaBins >= 1) ) throw cms::Exception("JetToTauFakeRateInterface") 
    << "Invalid Configuration parameter 'absEtaBins' !!\n";

  std::string hadTauSelection = cfg.getParameter<std::string>("hadTauSelection");
  
  std::string graphName_lead = cfg.getParameter<std::string>("graphName_lead");
  bool applyGraph_lead = cfg.getParameter<bool>("applyGraph_lead");
  std::string fitFunctionName_lead = cfg.getParameter<std::string>("fitFunctionName_lead");
  bool applyFitFunction_lead = cfg.getParameter<bool>("applyFitFunction_lead");
  
  std::string graphName_sublead = cfg.getParameter<std::string>("graphName_sublead");
  bool applyGraph_sublead = cfg.getParameter<bool>("applyGraph_sublead");
  std::string fitFunctionName_sublead = cfg.getParameter<std::string>("fitFunctionName_sublead");
  bool applyFitFunction_sublead = cfg.getParameter<bool>("applyFitFunction_sublead");

  for ( int idxBin = 0; idxBin < numAbsEtaBins; ++idxBin ) {
    double absEtaMin = absEtaBins[idxBin];
    double absEtaMax = absEtaBins[idxBin + 1];
    
    JetToTauFakeRateWeightEntry* jetToTauFakeRateWeights_lead = new JetToTauFakeRateWeightEntry(
      absEtaMin, absEtaMax, hadTauSelection,
      inputFile_, graphName_lead, applyGraph_lead, fitFunctionName_lead, applyFitFunction_lead, central_or_shift);
    jetToTauFakeRateWeights_lead_.push_back(jetToTauFakeRateWeights_lead);
    
    JetToTauFakeRateWeightEntry* jetToTauFakeRateWeights_sublead = new JetToTauFakeRateWeightEntry(
      absEtaMin, absEtaMax, hadTauSelection,
      inputFile_, graphName_sublead, applyGraph_sublead, fitFunctionName_sublead, applyFitFunction_sublead, central_or_shift);
    jetToTauFakeRateWeights_sublead_.push_back(jetToTauFakeRateWeights_sublead);
  }
}

JetToTauFakeRateInterface::~JetToTauFakeRateInterface()
{
  for ( std::vector<JetToTauFakeRateWeightEntry*>::iterator it = jetToTauFakeRateWeights_lead_.begin();
	it != jetToTauFakeRateWeights_lead_.end(); ++it ) {
    delete (*it);
  }
  for ( std::vector<JetToTauFakeRateWeightEntry*>::iterator it = jetToTauFakeRateWeights_sublead_.begin();
	it != jetToTauFakeRateWeights_sublead_.end(); ++it ) {
    delete (*it);
  }
  delete inputFile_;
}

double JetToTauFakeRateInterface::getWeight_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const
{
  double weight = 1.;
  for ( std::vector<JetToTauFakeRateWeightEntry*>::const_iterator jetToTauFakeRateWeightEntry = jetToTauFakeRateWeights_lead_.begin();
	jetToTauFakeRateWeightEntry != jetToTauFakeRateWeights_lead_.end(); ++jetToTauFakeRateWeightEntry ) {
    if ( hadTauAbsEta_lead >= (*jetToTauFakeRateWeightEntry)->absEtaMin_ && hadTauAbsEta_lead < (*jetToTauFakeRateWeightEntry)->absEtaMax_ ) {
      weight *= (*jetToTauFakeRateWeightEntry)->getWeight(hadTauPt_lead);
      break;
    }
  }
  return weight;
}

double JetToTauFakeRateInterface::getWeight_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const
{
  double weight = 1.;
  for ( std::vector<JetToTauFakeRateWeightEntry*>::const_iterator jetToTauFakeRateWeightEntry = jetToTauFakeRateWeights_sublead_.begin();
	jetToTauFakeRateWeightEntry != jetToTauFakeRateWeights_sublead_.end(); ++jetToTauFakeRateWeightEntry ) {
    if ( hadTauAbsEta_sublead >= (*jetToTauFakeRateWeightEntry)->absEtaMin_ && hadTauAbsEta_sublead < (*jetToTauFakeRateWeightEntry)->absEtaMax_ ) {
      weight *= (*jetToTauFakeRateWeightEntry)->getWeight(hadTauPt_sublead);
      break;
    }
  }
  return weight;
}
