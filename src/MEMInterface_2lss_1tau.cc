#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" 

#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/ThreadScheduler.h" // ThreadScheduler
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/NodeScheduler.h" // NodeScheduler
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/MGIntegration.h" // IntegrationMsg_t

#include <TMath.h> 

#include <algorithm> // std::sort

MEMInterface_2lss_1tau::MEMInterface_2lss_1tau(const std::string& configFileName)
  : config_(0)
  , clock_(0)
{
  std::cout << "<MEMInterface_2lss_1tau>:" << std::endl;
  
  // remove ".py"
  std::string configFileName_tmp = configFileName;
  size_t pos = configFileName_tmp.find(".py");
  if ( pos != string::npos ) {
    configFileName_tmp = std::string(configFileName_tmp, 0, pos);
  }
  std::cout << "configFileName = " << configFileName_tmp << std::endl;

  config_ = new RunConfig(configFileName_tmp.data());

  clock_ = new TBenchmark();
}

MEMInterface_2lss_1tau::~MEMInterface_2lss_1tau()
{
  delete config_;

  delete clock_;
}

namespace
{
  bool isHigherBtagCSV(const RecoJet* jet1, const RecoJet* jet2)
  {
    return (jet1->BtagCSV() > jet2->BtagCSV());
  }
}

MEMOutput_2lss_1tau
MEMInterface_2lss_1tau::operator()(
  const RecoLepton* selLepton_lead, const RecoLepton* selLepton_sublead, const RecoHadTau* selHadTau, 
  const RecoMEt& met,
  const std::vector<const RecoJet*>& selJets)
{
  MEMOutput_2lss_1tau result;

  if ( !(selJets.size() >= 3) ) {
    std::cerr << "Warning in <MEMInterface_2lss_1tau::operator()>: Failed to find three jets !!" << std::endl;
    result.errorFlag_ = 1;
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

  std::vector<const RecoJet*> selJets_sortedByBtagCSV = selJets;
  std::sort(selJets_sortedByBtagCSV.begin(), selJets_sortedByBtagCSV.end(), isHigherBtagCSV);
  const RecoJet* selBJet1 = selJets_sortedByBtagCSV[0];
  const RecoJet* selBJet2 = selJets_sortedByBtagCSV[1];
  inputs[0].evBJet1_4P_[0] = selBJet1->p4().px();
  inputs[0].evBJet1_4P_[1] = selBJet1->p4().py();
  inputs[0].evBJet1_4P_[2] = selBJet1->p4().pz();
  inputs[0].evBJet1_4P_[3] = selBJet1->p4().energy();
  inputs[0].evBJet2_4P_[0] = selBJet2->p4().px();
  inputs[0].evBJet2_4P_[1] = selBJet2->p4().py();
  inputs[0].evBJet2_4P_[2] = selBJet2->p4().pz();
  inputs[0].evBJet2_4P_[3] = selBJet2->p4().energy();
  
  const RecoJet* selJet1_w = 0;
  const RecoJet* selJet2_w = 0;
  double mJetJet_w = 1.e+3;
  const double mW = 80.4; 
  for ( std::vector<const RecoJet*>::const_iterator selJet1 = selJets.begin();
	selJet1 != selJets.end(); ++selJet1 ) {
    if ( (*selJet1) == selBJet1 || (*selJet1) == selBJet2 ) continue;
    for ( std::vector<const RecoJet*>::const_iterator selJet2 = selJet1 + 1;
	  selJet2 != selJets.end(); ++selJet2 ) {
      if ( (*selJet2) == selBJet1 || (*selJet2) == selBJet2 ) continue;
      double mJetJet = ((*selJet1)->p4() + (*selJet2)->p4()).mass();
      if ( !(mJetJet > 60. && mJetJet < 100.) ) continue;
      if ( TMath::Abs(mJetJet - mW) < TMath::Abs(mJetJet_w - mW) ) {
	selJet1_w = (*selJet1);
	selJet2_w = (*selJet2);
      }
    }
  }
  if ( selJet1_w && selJet2_w ) {
    inputs[0].integration_type_ = 0;
    inputs[0].evJet1_4P_[0] = selJet1_w->p4().px();
    inputs[0].evJet1_4P_[1] = selJet1_w->p4().py();
    inputs[0].evJet1_4P_[2] = selJet1_w->p4().pz();
    inputs[0].evJet1_4P_[3] = selJet1_w->p4().energy();
    inputs[0].evJet2_4P_[0] = selJet2_w->p4().px();
    inputs[0].evJet2_4P_[1] = selJet2_w->p4().py();
    inputs[0].evJet2_4P_[2] = selJet2_w->p4().pz();
    inputs[0].evJet2_4P_[3] = selJet2_w->p4().energy();
  } else {
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

  std::vector<const RecoJet*> selJets_untagged;
  for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin();
	selJet != selJets.end(); ++selJet ) {
    if ( (*selJet) == selBJet1 || (*selJet) == selBJet2 ) continue;
    selJets_untagged.push_back(*selJet);
  }  
  const int maxNumJets_untagged = 10;
  inputs[0].n_lightJets_ = std::min(maxNumJets_untagged, (int)selJets_untagged.size());
  for ( int idxJet = 0; idxJet < maxNumJets_untagged; ++idxJet ) {
    if ( idxJet < (int)selJets_untagged.size() ) {
      const RecoJet* selJet = selJets_untagged[idxJet];
      inputs[0].evJets_4P_[idxJet][0] = selJet->p4().px();
      inputs[0].evJets_4P_[idxJet][1] = selJet->p4().py();
      inputs[0].evJets_4P_[idxJet][2] = selJet->p4().pz();
      inputs[0].evJets_4P_[idxJet][3] = selJet->p4().energy();
    } else {
      inputs[0].evJets_4P_[idxJet][0] = 0.;
      inputs[0].evJets_4P_[idxJet][1] = 0.;
      inputs[0].evJets_4P_[idxJet][2] = 0.;
      inputs[0].evJets_4P_[idxJet][3] = 0.;      
    }
  }

  inputs[0].evRecoMET4P_[0] = met.p4().px();
  inputs[0].evRecoMET4P_[1] = met.p4().py();
  inputs[0].evRecoMET4P_[2] = 0.;
  inputs[0].evRecoMET4P_[3] = met.p4().pt();

  TMatrixD metCov_inverse = met.cov();
  double det = metCov_inverse.Determinant();
  if ( det != 0 ) { 
    metCov_inverse.Invert(); 
    inputs[0].evV_[0] = metCov_inverse(0,0);
    inputs[0].evV_[1] = metCov_inverse(0,1);
    inputs[0].evV_[2] = metCov_inverse(1,0);
    inputs[0].evV_[3] = metCov_inverse(1,1);
  } else {
    std::cerr << "Warning in <MEMInterface_2lss_1tau::operator(): Failed to invert MET covariance matrix (det=0) !!" << std::endl;
    result.errorFlag_ = 1;
    return result;
  }

  inputs[0].weight_ttH_ = 0.;
  //inputs[0].weight_ttH_ = 1.;
  inputs[0].weight_ttZ_ = 0.;
  inputs[0].weight_ttZ_Zll_ = 0.;
  inputs[0].weight_ttbar_DL_fakelep_ = 0.;

  clock_->Reset();
  clock_->Start("<MEMInterface_2lss_1tau::operator()>");

  ThreadScheduler scheduler;
  scheduler.initNodeScheduler(config_, 0);
  scheduler.runNodeScheduler(inputs, 1);

  clock_->Stop("<MEMInterface_2lss_1tau::operator()>");
  clock_->Show("<MEMInterface_2lss_1tau::operator()>");

  result.leadLepton_eta_ = selLepton_lead->eta();
  result.leadLepton_phi_ = selLepton_lead->phi();
  result.subleadLepton_eta_ = selLepton_sublead->eta();
  result.subleadLepton_phi_ = selLepton_sublead->phi();
  result.hadTau_eta_ = selHadTau->eta();
  result.hadTau_phi_ = selHadTau->phi();
  result.type_ = inputs[0].integration_type_;
  result.weight_ttH_ = inputs[0].weight_ttH_;
  result.weight_ttZ_ = inputs[0].weight_ttZ_;
  result.weight_ttZ_Zll_ = inputs[0].weight_ttZ_Zll_;
  result.weight_tt_ = inputs[0].weight_ttbar_DL_fakelep_;
  // compute MEM likelihood ratio
  // (kappa coefficients taken from Table 7 in AN-2016/363 v2)
  double k_ttZ = 0.;
  double k_ttZ_Zll = 0.;
  double k_tt = 0.;
  switch ( inputs[0].integration_type_ ) {
  case 0 :
    k_ttZ = 1.e-1;
    k_ttZ_Zll = 2.e-1;
    k_tt = 1.e-18;
    break;
  case 1 :
    k_ttZ = 5.e-2;
    k_ttZ_Zll = 5.e-1;
    k_tt = 5.e-15;
    break;
  default:
    assert(0);
  }
  double numerator = result.weight_ttH_;
  double denominator = result.weight_ttH_ + k_ttZ*result.weight_ttZ_ + k_ttZ_Zll*result.weight_ttZ_Zll_ + k_tt*result.weight_tt_;
  if ( denominator > 0. ) {
    result.isValid_ = 1;
    result.LR_ = numerator/denominator;
  } else {
    result.errorFlag_ = 1;
    result.LR_ = -1.;
  }
  result.cpuTime_ = clock_->GetCpuTime("<MEMInterface_2lss_1tau::operator()>");
  result.realTime_ = clock_->GetRealTime("<MEMInterface_2lss_1tau::operator()>");

  return result;
}

