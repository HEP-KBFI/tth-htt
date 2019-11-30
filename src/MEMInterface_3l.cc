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

MEMInterface_3l::MEMInterface_3l(const std::string & configFileName,
                                 int era)
  : jetSelectorBtagLoose_(era)
  , shyp_(nullptr)
  , hyp_(nullptr)
  , nPointsHyp_(nullptr)
  , index_hyp_(nullptr)
  , hypIntegrator_(new HypIntegrator())
  , MEMpermutations_ttH_(new Permutations())
  , MEMpermutations_tt_(new Permutations())
  , clock_(new TBenchmark())
{
  std::cout << get_human_line(this) << '\n';

  ConfigParser cfgParser;
  cfgParser.LoadConfig(configFileName);
  cfgParser.GetHypotheses(&nhyp_, &shyp_, &hyp_, &nPointsHyp_, &index_hyp_);
  cfgParser.SetCSVThreshold(jetSelectorBtagLoose_.get_min_BtagCSV());

  hypIntegrator_->InitializeIntegrator(&cfgParser);
  MEMpermutations_ = new Permutations[nhyp_];
}

MEMInterface_3l::~MEMInterface_3l()
{
  delete hypIntegrator_;
  delete[] MEMpermutations_;
  delete MEMpermutations_ttH_;
  delete MEMpermutations_tt_;
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
    result.errorFlag_ = ADDMEM_3L_ERROR_JETMULTIPLICITY;
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
  std::size_t numBJets_loose = 0;
  for(std::size_t idxJet = 0; idxJet < std::min(numJets, maxNumJets); ++idxJet)
  {
    const RecoJet * selJet = selJets_sortedByBtagCSV[idxJet];
    if ( jetSelectorBtagLoose_(*selJet) )
    {
      ++numBJets_loose;
    }
    multiLepton.FillParticle("alljet", 0, getTLorentzVector(selJet->p4()), selJet->BtagCSV());
  }

  TLorentzVector metP4_tlorentzvector;
  metP4_tlorentzvector.SetPxPyPzE(met.pt() * std::cos(met.phi()), met.pt() * std::sin(met.phi()), 0., met.pt());
  multiLepton.mET = metP4_tlorentzvector;
  multiLepton.sumET = met.sumEt();

  if ( numBJets_loose < 1 )
  { 
    // CV: according to Nicholas Chanon, the MEM code for the 3l channel fails (with a segmentation violation !!)
    //     in case there is not at least one b-jet in the event 
    std::cerr << "Warning in " << func_str << ": Failed to find at least one b-jet\n";
    result.errorFlag_ = ADDMEM_3L_ERROR_BJETMULTIPLICITY;
    return result;
  }

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
  // CV: The mapping of indices to processes is defined in
  //       https://github.com/nchanon/MEMmultilepton/blob/master/src/ConfigParser.cpp#L153-L223
  //    (with "TTLL" corresponding to ttZ/gamma^*)
  //     
  //     The mapping is
  //       ttH = 1 + 2 (H->WW->lnuqq and H->WW->lnulnu channels)
  //       tHq = 9
  //       ttW = 3 
  //       ttZ = 0
  //       tt  = 5 + 6 (dilepton and semi-lepton channels)
 
  if(index_hyp_[1] != -1 || index_hyp_[2] != -1)
  {
    CombineTwoHypotheses(
      &MEMpermutations_[index_hyp_[1]], index_hyp_[1],
      &MEMpermutations_[index_hyp_[2]], index_hyp_[2],
      MEMpermutations_ttH_
    );
    result.weight_ttH_ = MEMpermutations_ttH_->resMEM_avgExl0.weight;
    result.weight_ttH_error_ = MEMpermutations_ttH_->resMEM_avgExl0.err;
    result.kinfitscore_ttH_ = MEMpermutations_ttH_->resKin_maxKinFit_Int.weight;
  }
  if(index_hyp_[9] != -1)
  {
    const Permutations * MEMpermutations_tHq = &MEMpermutations_[index_hyp_[9]];
    result.weight_tHq_ = MEMpermutations_tHq->resMEM_avgExl0.weight;
    result.weight_tHq_error_ = MEMpermutations_tHq->resMEM_avgExl0.err;
    result.kinfitscore_tHq_ = MEMpermutations_tHq->resKin_maxKinFit_Int.weight;
  }
  if(index_hyp_[3] != -1)
  {
    const Permutations * MEMpermutations_ttW = &MEMpermutations_[index_hyp_[3]];
    result.weight_ttW_ = MEMpermutations_ttW->resMEM_avgExl0.weight;
    result.weight_ttW_error_ = MEMpermutations_ttW->resMEM_avgExl0.err;
    result.kinfitscore_ttW_ = MEMpermutations_ttW->resKin_maxKinFit_Int.weight;
  }
  if(index_hyp_[0] != -1)
  {
    const Permutations * MEMpermutations_ttZ = &MEMpermutations_[index_hyp_[0]];
    result.weight_ttZ_ = MEMpermutations_ttZ->resMEM_avgExl0.weight;
    result.weight_ttZ_error_ = MEMpermutations_ttZ->resMEM_avgExl0.err;
    result.kinfitscore_ttZ_ = MEMpermutations_ttZ->resKin_maxKinFit_Int.weight;
  }
  if(index_hyp_[5] != -1 || index_hyp_[6] != -1)
  {
    CombineTwoHypotheses(
      &MEMpermutations_[index_hyp_[5]], index_hyp_[5],
      &MEMpermutations_[index_hyp_[6]], index_hyp_[6],
      MEMpermutations_tt_
    );
    result.weight_tt_ = MEMpermutations_tt_->resMEM_avgExl0.weight;
    result.weight_tt_error_ = MEMpermutations_tt_->resMEM_avgExl0.err;
    result.kinfitscore_tt_ = MEMpermutations_tt_->resKin_maxKinFit_Int.weight;
  }

  const double k_tHq = 1.;
  const double numerator =
    result.weight_ttH_ +
    k_tHq * result.weight_tHq_
  ;
  const double numerator_up =
    result.weight_ttH_ + result.weight_ttH_error_ +
    k_tHq * (result.weight_tHq_ + result.weight_tHq_error_)
  ;
  const double numerator_down =
    result.weight_ttH_ - result.weight_ttH_error_ +
    k_tHq * std::max(result.weight_tHq_ - result.weight_tHq_error_, 0.f)
  ;
  const double k_ttW = 1.;
  const double k_ttZ = 1.;
  const double k_tt  = 1.;
  const double denominator =
    numerator +
    k_ttW * result.weight_ttW_ +
    k_ttZ * result.weight_ttZ_ +
    k_tt  * result.weight_tt_
  ;
  const double denominator_up =
    numerator_up +
    k_ttW * std::max(result.weight_ttW_ - result.weight_ttW_error_, 0.f) +
    k_ttZ * std::max(result.weight_ttZ_ - result.weight_ttZ_error_, 0.f) +
    k_tt  * std::max(result.weight_tt_  - result.weight_tt_error_,  0.f)
  ;
  const double denominator_down =
    numerator_down +
    k_ttW * (result.weight_ttW_ + result.weight_ttW_error_) +
    k_ttZ * (result.weight_ttZ_ + result.weight_ttZ_error_) +
    k_tt  * (result.weight_tt_  + result.weight_tt_error_)
  ;
  if(denominator > 0.)
  {
    result.isValid_ = 1;
    result.LR_      =                         numerator      / denominator;
    result.LR_up_   = denominator_up   > 0. ? numerator_up   / denominator_up   : 0.;
    result.LR_down_ = denominator_down > 0. ? numerator_down / denominator_down : 0.;
  }
  else
  {
    result.errorFlag_ = ADDMEM_3L_ERROR;
    result.LR_      = -1.;
    result.LR_up_   = -1.;
    result.LR_down_ = -1.;
  }

  result.cpuTime_  = clock_->GetCpuTime(func_str.data());
  result.realTime_ = clock_->GetRealTime(func_str.data());

  return result;
}
