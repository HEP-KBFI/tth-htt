#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l.h" 

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherCSV()
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line()

#include "tthAnalysis/MEMmultilepton/interface/HypIntegrator.h" // HypIntegrator
#include "tthAnalysis/MEMmultilepton/interface/MultiLepton.h" // MultiLepton
#include "tthAnalysis/MEMmultilepton/interface/ConfigParser.h" // ConfigParser
#include "tthAnalysis/MEMmultilepton/interface/Tools.h" // CombineTwoHypotheses()

#include <TBenchmark.h> // TBenchmark

#include <algorithm> // std::sort(), std::min()

MEMInterface_3l::MEMInterface_3l(const std::string & configFileName)
  : shyp_(nullptr)
  , hyp_(nullptr)
  , nPointsHyp_(nullptr)
  , index_hyp_(nullptr)
  , hypIntegrator_(new HypIntegrator())
  , MEMpermutationsTTH_(new Permutations())
  , MEMpermutationsTTbar_(new Permutations())
  , clock_(new TBenchmark())
{
  std::cout << get_human_line(this) << '\n';

  ConfigParser cfgParser;
  cfgParser.LoadConfig(configFileName);
  cfgParser.GetHypotheses(&nhyp_, &shyp_, &hyp_, &nPointsHyp_, &index_hyp_);

  hypIntegrator_->InitializeIntegrator(&cfgParser);
  MEMpermutations_ = new Permutations[nhyp_];
}

MEMInterface_3l::~MEMInterface_3l()
{
  delete hypIntegrator_;
  delete[] MEMpermutations_;
  delete MEMpermutationsTTH_;
  delete MEMpermutationsTTbar_;
  delete clock_;
}

namespace
{
  TLorentzVector getTLorentzVector(const Particle::LorentzVector & p4)
  {
    TLorentzVector p4_tlorentzvector;
    p4_tlorentzvector.SetPtEtaPhiE(p4.pt(), p4.eta(), p4.phi(), p4.energy());
    return p4_tlorentzvector;
  }
}

MEMOutput_3l
MEMInterface_3l::operator()(const RecoLepton * selLepton_lead,
                            const RecoLepton * selLepton_sublead,
                            const RecoLepton * selLepton_third,
                            const RecoMEt & met,
                            const std::vector<const RecoJet *> & selJets) const
{
  MEMOutput_3l result;
  const std::string func_str = get_human_line(this, __func__);
  if(selJets.size() < 2)
  {
    std::cerr << "Warning in " << func_str << ": Failed to find two jets\n";
    result.errorFlag_ = 1;
    return result;
  }

  std::vector<const RecoJet *> selJets_sortedByBtagCSV = selJets;
  std::sort(selJets_sortedByBtagCSV.begin(), selJets_sortedByBtagCSV.end(), isHigherCSV);

  MultiLepton multiLepton;
  multiLepton.FillParticle("lepton", selLepton_lead->pdgId(), getTLorentzVector(selLepton_lead->p4()));
  multiLepton.FillParticle("lepton", selLepton_sublead->pdgId(), getTLorentzVector(selLepton_sublead->p4()));
  multiLepton.FillParticle("lepton", selLepton_third->pdgId(), getTLorentzVector(selLepton_third->p4()));

  const std::size_t maxNumJets = 10;
  const std::size_t numJets = selJets_sortedByBtagCSV.size();
  for(std::size_t idxJet = 0; idxJet < std::min(numJets, maxNumJets); ++idxJet)
  {
    const RecoJet * selJet = selJets_sortedByBtagCSV[idxJet];
    multiLepton.FillParticle("alljet", 0, getTLorentzVector(selJet->p4()), selJet->BtagCSV());
  }

  TLorentzVector metP4_tlorentzvector;
  metP4_tlorentzvector.SetPxPyPzE(met.pt() * std::cos(met.phi()), met.pt() * std::sin(met.phi()), 0., met.pt());
  multiLepton.mET = metP4_tlorentzvector;
  multiLepton.sumET = met.sumEt();

  clock_->Reset();
  clock_->Start(func_str.data());

  for(int ih = 0; ih < nhyp_; ++ih) // loop on each MEM hypothesis defined in the config
  { 
    // setup permutations for each hyppothesis: leptons, jets and b-jets will be permutated within the multiLepton object
    MEMpermutations_[ih].SetMultiLepton(&multiLepton, hypIntegrator_);

    const int initresult = MEMpermutations_[ih].InitializeHyp(hypIntegrator_, hyp_[ih], nPointsHyp_[ih], shyp_[ih]);

    //Computation of all weights, and average of the MEM weights over permutations
    if(initresult == 1)
    {
      MEMpermutations_[ih].LoopPermutations(hypIntegrator_);
    }
  }

  clock_->Stop(func_str.data());
  clock_->Show(func_str.data());

  result.fillInputs(selLepton_lead, selLepton_sublead, selLepton_third);
  if(index_hyp_[1] != -1 || index_hyp_[2] != -1)
  {
    CombineTwoHypotheses(
      &MEMpermutations_[index_hyp_[1]], index_hyp_[1],
      &MEMpermutations_[index_hyp_[2]], index_hyp_[2],
      MEMpermutationsTTH_
    );
    result.weight_ttH_ = MEMpermutationsTTH_->resMEM_avgExl0.weight;
    result.kinfitscore_ttH_ = MEMpermutationsTTH_->resKin_maxKinFit_Int.weight;
  }
  if(index_hyp_[5] != -1 || index_hyp_[6] != -1)
  {
    CombineTwoHypotheses(
      &MEMpermutations_[index_hyp_[5]], index_hyp_[5],
      &MEMpermutations_[index_hyp_[6]], index_hyp_[6],
      MEMpermutationsTTbar_
    );
    result.weight_tt_ = MEMpermutationsTTbar_->resMEM_avgExl0.weight;
    result.kinfitscore_tt_ = MEMpermutationsTTbar_->resKin_maxKinFit_Int.weight;
  }

  const double numerator = result.weight_ttH_;
  const double k_tt = 1.;
  const double denominator = result.weight_ttH_ + k_tt*result.weight_tt_;
  if(denominator > 0.)
  {
    result.isValid_ = 1;
    result.LR_      = numerator / denominator;
  }
  else
  {
    result.errorFlag_ = 1;
    result.LR_        = -1.;
  }

  result.cpuTime_  = clock_->GetCpuTime(func_str.data());
  result.realTime_ = clock_->GetRealTime(func_str.data());

  return result;
}

