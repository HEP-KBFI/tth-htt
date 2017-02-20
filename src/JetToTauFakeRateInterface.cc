#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile

#include <assert.h> // assert

typedef std::vector<double> vdouble;

namespace
{
  void initializeJetToTauFakeRateWeights(TFile* inputFile, const std::string& hadTauSelection, const edm::ParameterSet& cfg, int central_or_shift,
					 std::vector<JetToTauFakeRateWeightEntry*>& jetToTauFakeRateWeights, bool& isInitialized)
  {
    vdouble absEtaBins = cfg.getParameter<vdouble>("absEtaBins");
    int numAbsEtaBins = absEtaBins.size() - 1;
    if ( !(numAbsEtaBins >= 1) ) throw cms::Exception("JetToTauFakeRateInterface") 
      << "Invalid Configuration parameter 'absEtaBins' !!\n";
    
    for ( int idxBin = 0; idxBin < numAbsEtaBins; ++idxBin ) {
      double absEtaMin = absEtaBins[idxBin];
      double absEtaMax = absEtaBins[idxBin + 1];
      
      JetToTauFakeRateWeightEntry* jetToTauFakeRateWeight = new JetToTauFakeRateWeightEntry(
        absEtaMin, absEtaMax, hadTauSelection,
        inputFile, cfg, central_or_shift);
      jetToTauFakeRateWeights.push_back(jetToTauFakeRateWeight);
    }

    isInitialized = true;
  }
}

JetToTauFakeRateInterface::JetToTauFakeRateInterface(const edm::ParameterSet& cfg, int central_or_shift)
  : inputFile_(0),
    isInitialized_lead_(false),
    isInitialized_sublead_(false),
    isInitialized_third_(false)
{
  std::string inputFileName = cfg.getParameter<std::string>("inputFileName");
  inputFile_ = openFile(LocalFileInPath(inputFileName));

  std::string hadTauSelection = cfg.getParameter<std::string>("hadTauSelection");

  if ( cfg.exists("lead") ) {
    edm::ParameterSet cfg_lead = cfg.getParameter<edm::ParameterSet>("lead");
    initializeJetToTauFakeRateWeights(inputFile_, hadTauSelection, cfg_lead, central_or_shift, jetToTauFakeRateWeights_lead_, isInitialized_lead_);
  }
  if ( cfg.exists("sublead") ) {
    edm::ParameterSet cfg_sublead = cfg.getParameter<edm::ParameterSet>("sublead");
    initializeJetToTauFakeRateWeights(inputFile_, hadTauSelection, cfg_sublead, central_or_shift, jetToTauFakeRateWeights_sublead_, isInitialized_sublead_);
  }
  if ( cfg.exists("third") ) {
    edm::ParameterSet cfg_third = cfg.getParameter<edm::ParameterSet>("third");
    initializeJetToTauFakeRateWeights(inputFile_, hadTauSelection, cfg_third, central_or_shift, jetToTauFakeRateWeights_third_, isInitialized_third_);
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
  for ( std::vector<JetToTauFakeRateWeightEntry*>::iterator it = jetToTauFakeRateWeights_third_.begin();
	it != jetToTauFakeRateWeights_third_.end(); ++it ) {
    delete (*it);
  }
  delete inputFile_;
}

double JetToTauFakeRateInterface::getWeight_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const
{
  return getWeight_or_SF_lead(hadTauPt_lead, hadTauAbsEta_lead, kWeight);
}

double JetToTauFakeRateInterface::getWeight_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const
{
  return getWeight_or_SF_sublead(hadTauPt_sublead, hadTauAbsEta_sublead, kWeight);
}

double JetToTauFakeRateInterface::getWeight_third(double hadTauPt_third, double hadTauAbsEta_third) const
{
  return getWeight_or_SF_third(hadTauPt_third, hadTauAbsEta_third, kWeight);
}

double JetToTauFakeRateInterface::getSF_lead(double hadTauPt_lead, double hadTauAbsEta_lead) const
{
  return getWeight_or_SF_lead(hadTauPt_lead, hadTauAbsEta_lead, kSF);
}

double JetToTauFakeRateInterface::getSF_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead) const
{
  return getWeight_or_SF_sublead(hadTauPt_sublead, hadTauAbsEta_sublead, kSF);
}

double JetToTauFakeRateInterface::getSF_third(double hadTauPt_third, double hadTauAbsEta_third) const
{
  return getWeight_or_SF_third(hadTauPt_third, hadTauAbsEta_third, kSF);
}

double JetToTauFakeRateInterface::getWeight_or_SF_lead(double hadTauPt_lead, double hadTauAbsEta_lead, int mode) const
{
  if ( !isInitialized_lead_ ) throw cms::Exception("JetToTauFakeRateInterface") 
    << "Jet->tau fake-rate weights for 'leading' tau requested, but not initialized !!\n"; 
  double weight = 1.;
  for ( std::vector<JetToTauFakeRateWeightEntry*>::const_iterator jetToTauFakeRateWeightEntry = jetToTauFakeRateWeights_lead_.begin();
	jetToTauFakeRateWeightEntry != jetToTauFakeRateWeights_lead_.end(); ++jetToTauFakeRateWeightEntry ) {
    if ( hadTauAbsEta_lead >= (*jetToTauFakeRateWeightEntry)->absEtaMin() && hadTauAbsEta_lead < (*jetToTauFakeRateWeightEntry)->absEtaMax() ) {
      if      ( mode == kWeight ) weight *= (*jetToTauFakeRateWeightEntry)->getWeight(hadTauPt_lead);
      else if ( mode == kSF     ) weight *= (*jetToTauFakeRateWeightEntry)->getSF(hadTauPt_lead);
      else assert(0);
      break;
    }
  }
  return weight;
}

double JetToTauFakeRateInterface::getWeight_or_SF_sublead(double hadTauPt_sublead, double hadTauAbsEta_sublead, int mode) const
{
  if ( !isInitialized_sublead_ ) throw cms::Exception("JetToTauFakeRateInterface") 
    << "Jet->tau fake-rate weights for 'subleading' tau requested, but not initialized !!\n"; 
  double weight = 1.;
  for ( std::vector<JetToTauFakeRateWeightEntry*>::const_iterator jetToTauFakeRateWeightEntry = jetToTauFakeRateWeights_sublead_.begin();
	jetToTauFakeRateWeightEntry != jetToTauFakeRateWeights_sublead_.end(); ++jetToTauFakeRateWeightEntry ) {
    if ( hadTauAbsEta_sublead >= (*jetToTauFakeRateWeightEntry)->absEtaMin() && hadTauAbsEta_sublead < (*jetToTauFakeRateWeightEntry)->absEtaMax() ) {
      if      ( mode == kWeight ) weight *= (*jetToTauFakeRateWeightEntry)->getWeight(hadTauPt_sublead);
      else if ( mode == kSF     ) weight *= (*jetToTauFakeRateWeightEntry)->getSF(hadTauPt_sublead);
      else assert(0);
      break;
    }
  }
  return weight;
}

double JetToTauFakeRateInterface::getWeight_or_SF_third(double hadTauPt_third, double hadTauAbsEta_third, int mode) const
{
  if ( !isInitialized_third_ ) throw cms::Exception("JetToTauFakeRateInterface") 
    << "Jet->tau fake-rate weights for 'third' tau requested, but not initialized !!\n"; 
  double weight = 1.;
  for ( std::vector<JetToTauFakeRateWeightEntry*>::const_iterator jetToTauFakeRateWeightEntry = jetToTauFakeRateWeights_third_.begin();
	jetToTauFakeRateWeightEntry != jetToTauFakeRateWeights_third_.end(); ++jetToTauFakeRateWeightEntry ) {
    if ( hadTauAbsEta_third >= (*jetToTauFakeRateWeightEntry)->absEtaMin() && hadTauAbsEta_third < (*jetToTauFakeRateWeightEntry)->absEtaMax() ) {
      if      ( mode == kWeight ) weight *= (*jetToTauFakeRateWeightEntry)->getWeight(hadTauPt_third);
      else if ( mode == kSF     ) weight *= (*jetToTauFakeRateWeightEntry)->getSF(hadTauPt_third);
      else assert(0);
      break;
    }
  }
  return weight;
}
