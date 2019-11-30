#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" 

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherCSV()
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line()

#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/RunConfig.h" // RunConfig
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/ThreadScheduler.h" // ThreadScheduler
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/NodeScheduler.h" // NodeScheduler
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/MGIntegration.h" // IntegrationMsg_t

#include <TMath.h>
#include <TBenchmark.h> // TBenchmark

#include <algorithm> // std::sort()

MEMInterface_2lss_1tau::MEMInterface_2lss_1tau(const std::string & configFileName)
  : config_(nullptr)
  , clock_(nullptr)
{
  std::cout << "<MEMInterface_2lss_1tau>:\n";

  // remove ".py"
  std::string configFileName_tmp = configFileName;
  const std::size_t pos = configFileName_tmp.find(".py");
  if(pos != std::string::npos)
  {
    configFileName_tmp = std::string(configFileName_tmp, 0, pos);
  }
  std::cout << "configFileName = " << configFileName_tmp << '\n';

  config_ = new RunConfig(configFileName_tmp.data());
  clock_  = new TBenchmark();
}

MEMInterface_2lss_1tau::~MEMInterface_2lss_1tau()
{
  delete config_;
  delete clock_;
}

MEMOutput_2lss_1tau
MEMInterface_2lss_1tau::operator()(const RecoLepton * selLepton_lead,
                                   const RecoLepton * selLepton_sublead,
                                   const RecoHadTau * selHadTau,
                                   const RecoMEt & met,
                                   const std::vector<const RecoJet *> & selJets) const
{
  MEMOutput_2lss_1tau result;
  const std::string func_str = get_human_line(this, __func__);

  if(selJets.size() < 3)
  {
    std::cerr << "Warning in " << func_str << ": Failed to find three jets !!\n";
    result.errorFlag_ = ADDMEM_2LSS1TAU_ERROR_JETMULTIPLICITY;
    return result;
  }

  IntegrationMsg_t inputs[1];
  
  inputs[0].evLep1_4P_[0] = selLepton_lead->p4().px();
  inputs[0].evLep1_4P_[1] = selLepton_lead->p4().py();
  inputs[0].evLep1_4P_[2] = selLepton_lead->p4().pz();
  inputs[0].evLep1_4P_[3] = selLepton_lead->p4().energy();
  inputs[0].lepton1_Type_ = selLepton_lead->pdgId();
  
  inputs[0].evLep2_4P_[0] = selLepton_sublead->p4().px();
  inputs[0].evLep2_4P_[1] = selLepton_sublead->p4().py();
  inputs[0].evLep2_4P_[2] = selLepton_sublead->p4().pz();
  inputs[0].evLep2_4P_[3] = selLepton_sublead->p4().energy();
  inputs[0].lepton2_Type_ = selLepton_sublead->pdgId();

  inputs[0].evHadSys_Tau_4P_[0] = selHadTau->p4().px();
  inputs[0].evHadSys_Tau_4P_[1] = selHadTau->p4().py();
  inputs[0].evHadSys_Tau_4P_[2] = selHadTau->p4().pz();
  inputs[0].evHadSys_Tau_4P_[3] = selHadTau->p4().energy();
  inputs[0].HadtauDecayMode_ = selHadTau->decayMode();

  std::vector<const RecoJet *> selJets_sortedByBtagCSV = selJets;
  std::sort(selJets_sortedByBtagCSV.begin(), selJets_sortedByBtagCSV.end(), isHigherCSV);
  const RecoJet * selBJet1 = selJets_sortedByBtagCSV[0];
  const RecoJet * selBJet2 = selJets_sortedByBtagCSV[1];
  inputs[0].evBJet1_4P_[0] = selBJet1->p4().px();
  inputs[0].evBJet1_4P_[1] = selBJet1->p4().py();
  inputs[0].evBJet1_4P_[2] = selBJet1->p4().pz();
  inputs[0].evBJet1_4P_[3] = selBJet1->p4().energy();
  inputs[0].evBJet2_4P_[0] = selBJet2->p4().px();
  inputs[0].evBJet2_4P_[1] = selBJet2->p4().py();
  inputs[0].evBJet2_4P_[2] = selBJet2->p4().pz();
  inputs[0].evBJet2_4P_[3] = selBJet2->p4().energy();
  
  const RecoJet * selJet1_w = nullptr;
  const RecoJet * selJet2_w = nullptr;
  const double mJetJet_w = 1.e+3;
  const double mW        = 80.4;
  for(std::size_t selJet1_idx = 0; selJet1_idx < selJets.size(); ++selJet1_idx)
  {
    const RecoJet * selJet1 = selJets[selJet1_idx];
    if(selJet1 == selBJet1 || selJet1 == selBJet2)
    {
      continue;
    }
    for(std::size_t selJet2_idx = selJet1_idx + 1; selJet2_idx < selJets.size(); ++selJet2_idx)
    {
      const RecoJet* selJet2 = selJets[selJet2_idx];
      if(selJet2 == selBJet1 || selJet2 == selBJet2)
      {
        continue;
      }
      const double mJetJet = (selJet1->p4() + selJet2->p4()).mass();
      if(! (mJetJet > 60. && mJetJet < 100.))
      {
        continue;
      }
      if(TMath::Abs(mJetJet - mW) < TMath::Abs(mJetJet_w - mW))
      {
        selJet1_w = selJet1;
        selJet2_w = selJet2;
      }
    } // selJets2_idx
  } // selJets1_idx

  if(selJet1_w && selJet2_w)
  {
    inputs[0].integration_type_ = 0;
    inputs[0].evJet1_4P_[0] = selJet1_w->p4().px();
    inputs[0].evJet1_4P_[1] = selJet1_w->p4().py();
    inputs[0].evJet1_4P_[2] = selJet1_w->p4().pz();
    inputs[0].evJet1_4P_[3] = selJet1_w->p4().energy();
    inputs[0].evJet2_4P_[0] = selJet2_w->p4().px();
    inputs[0].evJet2_4P_[1] = selJet2_w->p4().py();
    inputs[0].evJet2_4P_[2] = selJet2_w->p4().pz();
    inputs[0].evJet2_4P_[3] = selJet2_w->p4().energy();
  }
  else
  {
    inputs[0].integration_type_ = 1;
    inputs[0].evJet1_4P_[0] = 0.;
    inputs[0].evJet1_4P_[1] = 0.;
    inputs[0].evJet1_4P_[2] = 0.;
    inputs[0].evJet1_4P_[3] = 0.;
    inputs[0].evJet2_4P_[0] = 0.;
    inputs[0].evJet2_4P_[1] = 0.;
    inputs[0].evJet2_4P_[2] = 0.;
    inputs[0].evJet2_4P_[3] = 0.;
  }

  std::vector<const RecoJet *> selJets_untagged;
  for(const RecoJet * selJet: selJets)
  {
    if(selJet == selBJet1 || selJet == selBJet2)
    {
      continue;
    }
    selJets_untagged.push_back(selJet);
  }
  const std::size_t maxNumJets_untagged = 10;
  inputs[0].n_lightJets_ = std::min(maxNumJets_untagged, selJets_untagged.size());

  for(std::size_t idxJet = 0; idxJet < maxNumJets_untagged; ++idxJet)
  {
    if(idxJet < selJets_untagged.size())
    {
      const RecoJet* selJet = selJets_untagged[idxJet];
      inputs[0].evJets_4P_[idxJet][0] = selJet->p4().px();
      inputs[0].evJets_4P_[idxJet][1] = selJet->p4().py();
      inputs[0].evJets_4P_[idxJet][2] = selJet->p4().pz();
      inputs[0].evJets_4P_[idxJet][3] = selJet->p4().energy();
    }
    else
    {
      inputs[0].evJets_4P_[idxJet][0] = 0.;
      inputs[0].evJets_4P_[idxJet][1] = 0.;
      inputs[0].evJets_4P_[idxJet][2] = 0.;
      inputs[0].evJets_4P_[idxJet][3] = 0.;
    }
  } // idxJet

  inputs[0].evRecoMET4P_[0] = met.p4().px();
  inputs[0].evRecoMET4P_[1] = met.p4().py();
  inputs[0].evRecoMET4P_[2] = 0.;
  inputs[0].evRecoMET4P_[3] = met.p4().pt();

  TMatrixD metCov_inverse = met.cov();
  const double det = metCov_inverse.Determinant();
  if(det != 0)
  {
    metCov_inverse.Invert(); 
    inputs[0].evV_[0] = metCov_inverse(0,0);
    inputs[0].evV_[1] = metCov_inverse(0,1);
    inputs[0].evV_[2] = metCov_inverse(1,0);
    inputs[0].evV_[3] = metCov_inverse(1,1);
  }
  else
  {
    std::cerr << "Warning in " << func_str << ": "
                 "Failed to invert MET covariance matrix (det=0) !!\n";
    result.errorFlag_ = ADDMEM_2LSS1TAU_ERROR_MATRIXINVERSION;
    return result;
  }

  inputs[0].weight_ttH_ = 0.;
  inputs[0].weight_ttZ_ = 0.;
  inputs[0].weight_ttZ_Zll_ = 0.;
  inputs[0].weight_ttbar_DL_fakelep_ = 0.;

  clock_->Reset();
  clock_->Start(func_str.data());

  ThreadScheduler scheduler;
  scheduler.initNodeScheduler(config_, 0);
  scheduler.runNodeScheduler(inputs, 1);

  clock_->Stop(func_str.data());
  clock_->Show(func_str.data());

  result.fillInputs(selLepton_lead, selLepton_sublead, selHadTau);
  result.type_                 = inputs[0].integration_type_;
  result.weight_ttH_           = inputs[0].weight_ttH_;
  result.weight_ttH_error_     = inputs[0].weight_error_ttH_;
  result.weight_ttZ_           = inputs[0].weight_ttZ_;
  result.weight_ttZ_error_     = inputs[0].weight_error_ttZ_;
  result.weight_ttZ_Zll_       = inputs[0].weight_ttZ_Zll_;
  result.weight_ttZ_Zll_error_ = inputs[0].weight_error_ttZ_Zll_;
  result.weight_tt_            = inputs[0].weight_ttbar_DL_fakelep_;
  result.weight_tt_error_      = inputs[0].weight_error_ttbar_DL_fakelep_;

  // compute MEM likelihood ratio
  // (kappa coefficients taken from Table 7 in AN-2016/363 v2)
  double k_ttZ     = 0.;
  double k_ttZ_Zll = 0.;
  double k_tt      = 0.;
  switch(inputs[0].integration_type_)
  {
    case 0:
      k_ttZ     = 1.e-1;
      k_ttZ_Zll = 2.e-1;
      k_tt      = 1.e-18;
      break;
    case 1:
      k_ttZ     = 5.e-2;
      k_ttZ_Zll = 5.e-1;
      k_tt      = 5.e-15;
      break;
    default:
      assert(0);
  }

  const double numerator      =          result.weight_ttH_;
  const double numerator_up   =          result.weight_ttH_ + result.weight_ttH_error_;
  const double numerator_down = std::max(result.weight_ttH_ - result.weight_ttH_error_, 0.f);
  const double denominator =
    numerator +
    k_ttZ     * result.weight_ttZ_ +
    k_ttZ_Zll * result.weight_ttZ_Zll_ +
    k_tt      * result.weight_tt_
  ;
  const double denominator_up =
    numerator_up +
    k_ttZ     * std::max(result.weight_ttZ_     - result.weight_ttZ_error_,     0.f) +
    k_ttZ_Zll * std::max(result.weight_ttZ_Zll_ - result.weight_ttZ_Zll_error_, 0.f) +
    k_tt      * std::max(result.weight_tt_      - result.weight_tt_error_,      0.f)
  ;
  const double denominator_down =
    numerator_down +
    k_ttZ     * (result.weight_ttZ_     + result.weight_ttZ_error_) +
    k_ttZ_Zll * (result.weight_ttZ_Zll_ + result.weight_ttZ_Zll_error_) +
    k_tt      * (result.weight_tt_      + result.weight_tt_error_)
  ;
  if(denominator > 0.)
  {
    result.isValid_ = 1;
    result.LR_      =                         numerator      / denominator;
    result.LR_up_   = denominator_up   > 0. ? numerator_up   / denominator_up   : 0.;
    result.LR_down_ = denominator_down > 0. ? numerator_down / denominator_down : 0.;
    // If the denominator is > 0, but the weight and error of signal hypothesis are 0, then it can be that
    // denominator_up can go to 0 if the errors on the background hypotheses are large enough; but in that case
    // denominator_down > denominator_up >= 0; LR remains 0 for all of these cases.
    // If the numerator is > 0 and the weights and errors on background hypotheses are all 0, then
    // denominator_down can go to 0 as well if the errors on the signal hypothesis are large enough; but in that case
    // denominator_up > denominator_down >= 0 => 0 <= LR(down) < LR(nominal) < LR(up).
    // Therefore, it's not possible that both denominator_up and denominator_down go to 0 at the same
    // time if the nominal denominator is > 0.
  }
  else
  {
    result.errorFlag_ = ADDMEM_2LSS1TAU_ERROR;
    result.LR_      = -1.;
    result.LR_up_   = -1.;
    result.LR_down_ = -1.;
  }

  const double denominator_ttZ_LR =
    numerator +
    k_ttZ     * result.weight_ttZ_ +
    k_ttZ_Zll * result.weight_ttZ_Zll_
  ;
  const double denominator_ttZ_LR_up =
    numerator_up +
    k_ttZ     * std::max(result.weight_ttZ_     - result.weight_ttZ_error_,     0.f) +
    k_ttZ_Zll * std::max(result.weight_ttZ_Zll_ - result.weight_ttZ_Zll_error_, 0.f)
  ;
  const double denominator_ttZ_LR_down =
    numerator_down +
    k_ttZ     * std::max(result.weight_ttZ_     + result.weight_ttZ_error_,     0.f) +
    k_ttZ_Zll * std::max(result.weight_ttZ_Zll_ + result.weight_ttZ_Zll_error_, 0.f)
  ;
  if(denominator_ttZ_LR > 0.)
  {
    result.isValid_ttZ_LR_ = 1;
    result.ttZ_LR_      =                                numerator      / denominator_ttZ_LR;
    result.ttZ_LR_up_   = denominator_ttZ_LR_up   > 0. ? numerator_up   / denominator_ttZ_LR_up   : 0.;
    result.ttZ_LR_down_ = denominator_ttZ_LR_down > 0. ? numerator_down / denominator_ttZ_LR_down : 0.;
  }
  else
  {
    result.errorFlag_ttZ_LR_  = ADDMEM_2LSS1TAU_ERROR;
    result.ttZ_LR_      = -1.;
    result.ttZ_LR_up_   = -1.;
    result.ttZ_LR_down_ = -1.;
  }

  const double denominator_ttbar_LR      = numerator      + k_tt *          result.weight_tt_;
  const double denominator_ttbar_LR_up   = numerator_up   + k_tt * std::max(result.weight_tt_ - result.weight_tt_error_, 0.f);
  const double denominator_ttbar_LR_down = numerator_down + k_tt * std::max(result.weight_tt_ + result.weight_tt_error_, 0.f);
  if(denominator_ttbar_LR > 0.)
  {
    result.isValid_ttbar_LR_ = 1;
    result.ttbar_LR_      =                                  numerator      / denominator_ttbar_LR;
    result.ttbar_LR_up_   = denominator_ttbar_LR_up   > 0. ? numerator_up   / denominator_ttbar_LR_up   : 0.;
    result.ttbar_LR_down_ = denominator_ttbar_LR_down > 0. ? numerator_down / denominator_ttbar_LR_down : 0.;
  }
  else
  {
    result.errorFlag_ttbar_LR_ = ADDMEM_2LSS1TAU_ERROR;
    result.ttbar_LR_      = -1.;
    result.ttbar_LR_up_   = -1.;
    result.ttbar_LR_down_ = -1.;
  }

  result.cpuTime_  = clock_->GetCpuTime(func_str.data());
  result.realTime_ = clock_->GetRealTime(func_str.data());

  return result;
}

