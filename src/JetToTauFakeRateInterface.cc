#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile

#include <cassert> // assert()

typedef std::vector<double> vdouble;

namespace
{
  void
  initializeJetToTauFakeRateWeights(TFile * inputFile,
                                    const std::string & hadTauSelection,
                                    const edm::ParameterSet & cfg,
                                    const std::string& trigMatching,
                                    int central_or_shift,
                                    std::map<int, std::vector<JetToTauFakeRateWeightEntry *>> & jetToTauFakeRateWeights,
                                    bool & isInitialized)
  {
    const vdouble absEtaBins = cfg.getParameter<vdouble>("absEtaBins");
    const int numAbsEtaBins = absEtaBins.size() - 1;
    if(numAbsEtaBins < 1)
    {
      throw cmsException(__func__)
        << "Invalid Configuration parameter 'absEtaBins' !!\n";
    }

    for(int idxBin = 0; idxBin < numAbsEtaBins; ++idxBin)
    {
      const double absEtaMin = absEtaBins[idxBin];
      const double absEtaMax = absEtaBins[idxBin + 1];
      
      JetToTauFakeRateWeightEntry * jetToTauFakeRateWeight = new JetToTauFakeRateWeightEntry(
        absEtaMin, absEtaMax, hadTauSelection, inputFile, cfg, trigMatching, central_or_shift
      );
      if(! jetToTauFakeRateWeights.count(central_or_shift))
      {
        jetToTauFakeRateWeights[central_or_shift] = {};
      }
      jetToTauFakeRateWeights[central_or_shift].push_back(jetToTauFakeRateWeight);
    }

    isInitialized = true;
  }
}

JetToTauFakeRateInterface::JetToTauFakeRateInterface(const edm::ParameterSet & cfg, const std::string& trigMatching)
  : inputFile_(nullptr)
  , isInitialized_lead_(false)
  , isInitialized_sublead_(false)
  , isInitialized_third_(false)
  , isInitialized_fourth_(false)
{
  const std::string inputFileName = cfg.getParameter<std::string>("inputFileName");
  inputFile_ = openFile(LocalFileInPath(inputFileName));

  const std::string hadTauSelection = cfg.getParameter<std::string>("hadTauSelection");

  const auto initializeJetToTauFRWeights = [&, this](
    const edm::ParameterSet & cfg_prio,
    const std::string& trigMatching_prio,
    std::map<int, std::vector<JetToTauFakeRateWeightEntry *>> & jetToTauFakeRateWeights_prio,
    bool & isInitialized,
    int FRjt_option) -> void
  {
    initializeJetToTauFakeRateWeights(
      inputFile_, hadTauSelection, cfg_prio, trigMatching_prio, FRjt_option, jetToTauFakeRateWeights_prio, isInitialized
    );
  };

  for(int FRjt_option = kFRjt_central; FRjt_option <= kFRjt_shapeDown; ++FRjt_option)
  {
    if(cfg.exists("lead"))
    {
      const edm::ParameterSet cfg_lead = cfg.getParameter<edm::ParameterSet>("lead");
      initializeJetToTauFRWeights(cfg_lead, trigMatching, jetToTauFakeRateWeights_lead_, isInitialized_lead_, FRjt_option);
    }
    if(cfg.exists("sublead"))
    {
      const edm::ParameterSet cfg_sublead = cfg.getParameter<edm::ParameterSet>("sublead");
      initializeJetToTauFRWeights(cfg_sublead, trigMatching, jetToTauFakeRateWeights_sublead_, isInitialized_sublead_, FRjt_option);
    }
    if(cfg.exists("third"))
    {
      const edm::ParameterSet cfg_third = cfg.getParameter<edm::ParameterSet>("third");
      initializeJetToTauFRWeights(cfg_third, trigMatching, jetToTauFakeRateWeights_third_, isInitialized_third_, FRjt_option);
    }
    if(cfg.exists("fourth"))
    {
      const edm::ParameterSet cfg_fourth = cfg.getParameter<edm::ParameterSet>("fourth");
      initializeJetToTauFRWeights(cfg_fourth, trigMatching, jetToTauFakeRateWeights_fourth_, isInitialized_fourth_, FRjt_option);
    }
  }
}

JetToTauFakeRateInterface::~JetToTauFakeRateInterface()
{
  for(auto & kv: jetToTauFakeRateWeights_lead_)
  {
    for(JetToTauFakeRateWeightEntry * & it: kv.second)
    {
      delete it;
    }
  }
  for(auto & kv: jetToTauFakeRateWeights_sublead_)
  {
    for(JetToTauFakeRateWeightEntry * & it: kv.second)
    {
      delete it;
    }
  }
  for(auto & kv: jetToTauFakeRateWeights_third_)
  {
    for(JetToTauFakeRateWeightEntry * & it: kv.second)
    {
      delete it;
    }
  }
  for(auto & kv: jetToTauFakeRateWeights_fourth_)
  {
    for(JetToTauFakeRateWeightEntry * & it: kv.second)
    {
      delete it;
    }
  }
  delete inputFile_;
}

double
JetToTauFakeRateInterface::getWeight_lead(double hadTauPt_lead,
                                          double hadTauAbsEta_lead,
                                          int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_lead, hadTauAbsEta_lead, kWeight, 0, central_or_shift);
}

double
JetToTauFakeRateInterface::getWeight_sublead(double hadTauPt_sublead,
                                             double hadTauAbsEta_sublead,
                                             int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_sublead, hadTauAbsEta_sublead, kWeight, 1, central_or_shift);
}

double
JetToTauFakeRateInterface::getWeight_third(double hadTauPt_third,
                                           double hadTauAbsEta_third,
                                           int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_third, hadTauAbsEta_third, kWeight, 2, central_or_shift);
}

double
JetToTauFakeRateInterface::getWeight_fourth(double hadTauPt_fourth,
                                            double hadTauAbsEta_fourth,
                                            int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_fourth, hadTauAbsEta_fourth, kWeight, 3, central_or_shift);
}

double
JetToTauFakeRateInterface::getSF_lead(double hadTauPt_lead,
                                      double hadTauAbsEta_lead,
                                      int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_lead, hadTauAbsEta_lead, kSF, 0, central_or_shift);
}

double
JetToTauFakeRateInterface::getSF_sublead(double hadTauPt_sublead,
                                         double hadTauAbsEta_sublead,
                                         int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_sublead, hadTauAbsEta_sublead, kSF, 1, central_or_shift);
}

double
JetToTauFakeRateInterface::getSF_third(double hadTauPt_third,
                                       double hadTauAbsEta_third,
                                       int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_third, hadTauAbsEta_third, kSF, 2, central_or_shift);
}

double
JetToTauFakeRateInterface::getSF_fourth(double hadTauPt_fourth,
                                        double hadTauAbsEta_fourth,
                                        int central_or_shift) const
{
  return getWeight_or_SF(hadTauPt_fourth, hadTauAbsEta_fourth, kSF, 3, central_or_shift);
}

double
JetToTauFakeRateInterface::getWeight_or_SF(double hadTauPt,
                                           double hadTauAbsEta,
                                           int mode,
                                           int order,
                                           int central_or_shift) const
{
  std::string name;
  bool isInitialized = false;
  std::vector<JetToTauFakeRateWeightEntry *> j2tFRweights;
  switch(order)
  {
    case 0: name = "leading";    isInitialized = isInitialized_lead_;    j2tFRweights = jetToTauFakeRateWeights_lead_.at(central_or_shift);    break;
    case 1: name = "subleading"; isInitialized = isInitialized_sublead_; j2tFRweights = jetToTauFakeRateWeights_sublead_.at(central_or_shift); break;
    case 2: name = "third";      isInitialized = isInitialized_third_;   j2tFRweights = jetToTauFakeRateWeights_third_.at(central_or_shift);   break;
    case 3: name = "fourth";     isInitialized = isInitialized_fourth_;  j2tFRweights = jetToTauFakeRateWeights_fourth_.at(central_or_shift);  break;
    default: assert(0);
  }

  if(! isInitialized )
    throw cmsException(this, __func__)
      << "Jet->tau fake-rate weights for '" << name << "' tau requested, but not initialized";

  double weight = 1.;
  for(const JetToTauFakeRateWeightEntry * const jetToTauFakeRateWeightEntry: j2tFRweights)
  {
    if(hadTauAbsEta >= jetToTauFakeRateWeightEntry->absEtaMin() &&
       hadTauAbsEta < jetToTauFakeRateWeightEntry->absEtaMax())
    {
      switch(mode)
      {
        case kWeight: weight *= jetToTauFakeRateWeightEntry->getWeight(hadTauPt); break;
        case kSF:     weight *= jetToTauFakeRateWeightEntry->getSF(hadTauPt);     break;
        default: assert(0);
      }
      break;
    }
  }
  return weight;
}
