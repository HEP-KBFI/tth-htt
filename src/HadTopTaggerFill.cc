#include "tthAnalysis/HiggsToTauTau/interface/HadTopTaggerFill.h" // HadTopTagger

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "TLorentzVector.h"
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <Python.h>

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const Particle* particle1, const Particle* particle2);

HadTopTaggerFill::HadTopTaggerFill(const std::string& mvaFileName)
  : kinFit_(0)
{
  kinFit_ = new HadTopKinFit();

  mvaInputVariables_.push_back("CSV_Wj1");
  mvaInputVariables_.push_back("CSV_b");
  mvaInputVariables_.push_back("dR_Wj1Wj2");
  mvaInputVariables_.push_back("dR_bW");
  mvaInputVariables_.push_back("m_Wj1Wj2");
  mvaInputVariables_.push_back("nllKinFit");
  mvaInputVariables_.push_back("pT_Wj2");
  mvaInputVariables_.push_back("pT_bWj1Wj2");
  mvaInputVariables_.push_back("qg_Wj2");

  mvaInputVariables_.push_back("m_bWj1Wj2");
  mvaInputVariables_.push_back("m_Wj1Wj2");
  mvaInputVariables_.push_back("m_bWj1");
  mvaInputVariables_.push_back("m_bWj2");
  mvaInputVariables_.push_back("m_Wj1Wj2_div_m_bWj1Wj2");
  mvaInputVariables_.push_back("CSV_b");
  mvaInputVariables_.push_back("CSV_Wj1");
  mvaInputVariables_.push_back("CSV_Wj2");
  mvaInputVariables_.push_back("pT_b");
  mvaInputVariables_.push_back("eta_b");
  mvaInputVariables_.push_back("phi_b");
  mvaInputVariables_.push_back("mass_b");
  mvaInputVariables_.push_back("pT_Wj1");
  mvaInputVariables_.push_back("eta_Wj1");
  mvaInputVariables_.push_back("phi_Wj1");
  mvaInputVariables_.push_back("mass_Wj1");
  mvaInputVariables_.push_back("pT_Wj2");
  mvaInputVariables_.push_back("eta_Wj2");
  mvaInputVariables_.push_back("phi_Wj2");
  mvaInputVariables_.push_back("mass_Wj2");

  mvaInputVariables_.push_back("dR_bWj1");
  mvaInputVariables_.push_back("dR_bWj2");
  mvaInputVariables_.push_back("dR_Wj1Wj2");
  mvaInputVariables_.push_back("dR_bW");
  mvaInputVariables_.push_back("statusKinFit");
  mvaInputVariables_.push_back("nllKinFit");
  mvaInputVariables_.push_back("alphaKinFit");

  mvaInputVariables_.push_back("kinFit_pT_b");
  mvaInputVariables_.push_back("kinFit_eta_b");
  mvaInputVariables_.push_back("kinFit_phi_b");
  mvaInputVariables_.push_back("kinFit_mass_b");
  mvaInputVariables_.push_back("kinFit_pT_Wj1");
  mvaInputVariables_.push_back("kinFit_eta_Wj1");
  mvaInputVariables_.push_back("kinFit_phi_Wj1");
  mvaInputVariables_.push_back("kinFit_mass_Wj1");
  mvaInputVariables_.push_back("kinFit_pT_Wj2");
  mvaInputVariables_.push_back("kinFit_eta_Wj2");
  mvaInputVariables_.push_back("kinFit_phi_Wj2");
  mvaInputVariables_.push_back("kinFit_mass_Wj2");

  mvaInputVariables_.push_back("cosTheta_leadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_subleadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_leadWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_subleadWj_restTop");

  mvaInputVariables_.push_back("cosTheta_leadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_subleadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_leadEWj_restTop");
  mvaInputVariables_.push_back("cosTheta_Kin_subleadEWj_restTop");

  mvaInputVariables_.push_back("cosThetaW_rest");
  mvaInputVariables_.push_back("cosThetaKinW_rest");
  mvaInputVariables_.push_back("cosThetaW_lab");
  mvaInputVariables_.push_back("cosThetaKinW_lab");

  mvaInputVariables_.push_back("cosThetab_rest");
  mvaInputVariables_.push_back("cosThetaKinb_rest");
  mvaInputVariables_.push_back("cosThetab_lab");
  mvaInputVariables_.push_back("cosThetaKinb_lab");

  mvaInputVariables_.push_back("Dphi_Wj1_Wj2_lab");
  mvaInputVariables_.push_back("Dphi_KinWj1_KinWj2_lab");

  mvaInputVariables_.push_back("Dphi_Wb_rest");
  mvaInputVariables_.push_back("Dphi_KinWb_rest");
  mvaInputVariables_.push_back("Dphi_Wb_lab");
  mvaInputVariables_.push_back("Dphi_KinWb_lab");

  mvaInputVariables_.push_back("cosThetaWj1_restW");
  mvaInputVariables_.push_back("cosThetaKinWj_restW");

  mvaInputVariables_.push_back("logPKinFit");
  mvaInputVariables_.push_back("logPErrKinFit");
  mvaInputVariables_.push_back("qg_b");
  mvaInputVariables_.push_back("qg_Wj1");
  mvaInputVariables_.push_back("qg_Wj2");
  mvaInputVariables_.push_back("pT_bWj1Wj2");
  mvaInputVariables_.push_back("pT_Wj1Wj2");
  mvaInputVariables_.push_back("max_dR_div_expRjet");

}

HadTopTaggerFill::~HadTopTaggerFill()
{
  delete kinFit_;
}


double HadTopTaggerFill::operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
{
  Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  mvaInputs_["m_bWj1Wj2"]              = p4_bWj1Wj2.mass();
  Particle::LorentzVector p4_Wj1Wj2 = recWJet1.p4() + recWJet2.p4();
  mvaInputs_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputs_["m_bWj1"]                 = (recBJet.p4() + recWJet1.p4()).mass();
  mvaInputs_["m_bWj2"]                 = (recBJet.p4() + recWJet2.p4()).mass();
  mvaInputs_["m_Wj1Wj2_div_m_bWj1Wj2"] = ( p4_bWj1Wj2.mass() > 0. ) ? p4_Wj1Wj2.mass()/p4_bWj1Wj2.mass() : -1.;
  mvaInputs_["CSV_b"]                  = recBJet.BtagCSV();
  mvaInputs_["CSV_Wj1"]                = recWJet1.BtagCSV();
  mvaInputs_["CSV_Wj2"]                = recWJet2.BtagCSV();
  mvaInputs_["pT_b"]                   = recBJet.pt();
  mvaInputs_["eta_b"]                  = recBJet.eta();
  mvaInputs_["phi_b"]                  = recBJet.phi();
  mvaInputs_["mass_b"]                 = recBJet.mass();
  mvaInputs_["pT_Wj1"]                 = recWJet1.pt();
  mvaInputs_["eta_Wj1"]                = recWJet1.eta();
  mvaInputs_["phi_Wj1"]                = recWJet1.phi();
  mvaInputs_["mass_Wj1"]               = recWJet1.mass();
  mvaInputs_["pT_Wj2"]                 = recWJet2.pt();
  mvaInputs_["eta_Wj2"]                = recWJet2.eta();
  mvaInputs_["phi_Wj2"]                = recWJet2.phi();
  mvaInputs_["mass_Wj2"]               = recWJet2.mass();
  double dR_bWj1 = deltaR(recBJet.p4(), recWJet1.p4());
  mvaInputs_["dR_bWj1"]                = dR_bWj1;
  double dR_bWj2 = deltaR(recBJet.p4(), recWJet2.p4());
  mvaInputs_["dR_bWj2"]                = dR_bWj2;
  double dR_Wj1Wj2 = deltaR(recWJet1.p4(), recWJet2.p4());
  mvaInputs_["dR_Wj1Wj2"]              = dR_Wj1Wj2;
  mvaInputs_["dR_bW"]                  = deltaR(recBJet.p4(), p4_Wj1Wj2);
  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["statusKinFit"]           = kinFit_->fit_status();
  mvaInputs_["nllKinFit"]              = kinFit_->nll();
  mvaInputs_["alphaKinFit"]            = kinFit_->alpha();

  mvaInputs_["kinFit_pT_b"]            = kinFit_->fittedBJet().pt();
  mvaInputs_["kinFit_eta_b"]           = kinFit_->fittedBJet().eta();
  mvaInputs_["kinFit_phi_b"]           = kinFit_->fittedBJet().phi();
  mvaInputs_["kinFit_mass_b"]          = kinFit_->fittedBJet().mass();
  mvaInputs_["kinFit_pT_Wj1"]          = kinFit_->fittedWJet1().pt();
  mvaInputs_["kinFit_eta_Wj1"]         = kinFit_->fittedWJet1().eta();
  mvaInputs_["kinFit_phi_Wj1"]         = kinFit_->fittedWJet1().phi();
  mvaInputs_["kinFit_mass_Wj1"]        = kinFit_->fittedWJet1().mass();
  mvaInputs_["kinFit_pT_Wj2"]          = kinFit_->fittedWJet2().pt();
  mvaInputs_["kinFit_eta_Wj2"]         = kinFit_->fittedWJet2().eta();
  mvaInputs_["kinFit_phi_Wj2"]         = kinFit_->fittedWJet2().phi();
  mvaInputs_["kinFit_mass_Wj2"]        = kinFit_->fittedWJet2().mass();
  //star angle computation
  TLorentzVector PWj1, PWj2, PW, Pb, Ptop, PWboost, Pbboost, PWj1boost, PWj1boostTop, PWj2boostTop;
  TLorentzVector kinFit_PWj1, kinFit_PWj2, kinFit_PW, kinFit_Pb, kinFit_Ptop,
    kinFit_PWboost, kinFit_Pbboost, kinFit_PWj1boost, kinFit_PWj1boostTop, kinFit_PWj2boostTop;
  PWj1.SetPtEtaPhiM(recWJet1.pt(),
    recWJet1.eta(),
    recWJet1.phi(),
    recWJet1.mass());
  PWj2.SetPtEtaPhiM(recWJet2.pt(),
    recWJet2.eta(),
    recWJet2.phi(),
    recWJet2.mass());
  PW = PWj1 + PWj2;
  Pb.SetPtEtaPhiM(recBJet.pt(),
    recBJet.eta(),
    recBJet.phi(),
    recBJet.mass());
  Ptop = PW + Pb;
  PWboost=PW;
  Pbboost=Pb;
  PWboost.Boost(-Ptop.BoostVector());
  Pbboost.Boost(-Ptop.BoostVector());
  PWj1boost=PWj1;
  PWj1boost.Boost(-PW.BoostVector());

  PWj1boostTop=PWj1;
  PWj1boostTop.Boost(-Ptop.BoostVector());
  PWj2boostTop=PWj2;
  PWj2boostTop.Boost(-Ptop.BoostVector());

  float leadingCostS_Wj_top= -100;
  float subleadingCostS_Wj_top =-100;
  if (PWj1boostTop.Pt() > PWj2boostTop.Pt()) {
    leadingCostS_Wj_top=PWj1boostTop.CosTheta();
    subleadingCostS_Wj_top=PWj2boostTop.CosTheta();
  }  else {
    leadingCostS_Wj_top=PWj2boostTop.CosTheta();
    subleadingCostS_Wj_top=PWj1boostTop.CosTheta();
  }

  float leadingECostS_Wj_top= -100;
  float subleadingECostS_Wj_top =-100;
  if (PWj1boostTop.E() > PWj2boostTop.E()) {
    leadingECostS_Wj_top=PWj1boostTop.CosTheta();
    subleadingECostS_Wj_top=PWj2boostTop.CosTheta();
  }  else {
    leadingECostS_Wj_top=PWj2boostTop.CosTheta();
    subleadingECostS_Wj_top=PWj1boostTop.CosTheta();
  }
  //////////////////////////////////////////////////////

  kinFit_PWj1.SetPtEtaPhiM(kinFit_->fittedWJet1().pt(),
    kinFit_->fittedWJet1().eta(),
    kinFit_->fittedWJet1().phi(),
    kinFit_->fittedWJet1().mass());
  kinFit_PWj2.SetPtEtaPhiM(kinFit_->fittedWJet2().pt(),
  kinFit_->fittedWJet2().eta(),
  kinFit_->fittedWJet2().phi(),
  kinFit_->fittedWJet2().mass());
  kinFit_PW = kinFit_PWj1 + kinFit_PWj2;
  kinFit_Pb.SetPtEtaPhiM(kinFit_->fittedBJet().pt(),
    kinFit_->fittedBJet().eta(),
    kinFit_->fittedBJet().phi(),
    kinFit_->fittedBJet().mass());
  kinFit_Ptop = kinFit_PW + kinFit_Pb;
  kinFit_PWboost=kinFit_PW;
  kinFit_Pbboost=kinFit_Pb;
  kinFit_PWboost.Boost(-kinFit_Ptop.BoostVector());
  kinFit_Pbboost.Boost(-kinFit_Ptop.BoostVector());
  kinFit_PWj1boost=kinFit_PWj1;
  kinFit_PWj1boost.Boost(-kinFit_PW.BoostVector());

  kinFit_PWj1boostTop=kinFit_PWj1;
  kinFit_PWj1boostTop.Boost(-kinFit_Ptop.BoostVector());
  kinFit_PWj2boostTop=kinFit_PWj2;
  kinFit_PWj2boostTop.Boost(-kinFit_Ptop.BoostVector());

  float kinFit_leadingCostS_Wj_top =-100;
  float  kinFit_subleadingCostS_Wj_top =-100;
  if (kinFit_PWj1boostTop.Pt() > kinFit_PWj2boostTop.Pt()) {
    kinFit_leadingCostS_Wj_top=kinFit_PWj1boostTop.CosTheta();
    kinFit_subleadingCostS_Wj_top=kinFit_PWj2boostTop.CosTheta();
  }  else {
    kinFit_leadingCostS_Wj_top=kinFit_PWj2boostTop.CosTheta();
    kinFit_subleadingCostS_Wj_top=kinFit_PWj1boostTop.CosTheta();
  }

  mvaInputs_["cosTheta_leadWj_restTop"]         = leadingCostS_Wj_top;
  mvaInputs_["cosTheta_subleadWj_restTop"]         = subleadingCostS_Wj_top;
  mvaInputs_["cosTheta_Kin_leadWj_restTop"]         = kinFit_leadingCostS_Wj_top;
  mvaInputs_["cosTheta_Kin_subleadWj_restTop"]         = kinFit_subleadingCostS_Wj_top;

  float kinFit_leadingECostS_Wj_top =-100;
  float  kinFit_subleadingECostS_Wj_top =-100;
  if (kinFit_PWj1boostTop.E() > kinFit_PWj2boostTop.E()) {
    kinFit_leadingECostS_Wj_top=kinFit_PWj1boostTop.CosTheta();
    kinFit_subleadingECostS_Wj_top=kinFit_PWj2boostTop.CosTheta();
  }  else {
    kinFit_leadingECostS_Wj_top=kinFit_PWj2boostTop.CosTheta();
    kinFit_subleadingECostS_Wj_top=kinFit_PWj1boostTop.CosTheta();
  }

  mvaInputs_["cosTheta_leadEWj_restTop"]         = leadingECostS_Wj_top;
  mvaInputs_["cosTheta_subleadEWj_restTop"]         = subleadingECostS_Wj_top;
  mvaInputs_["cosTheta_Kin_leadEWj_restTop"]         = kinFit_leadingECostS_Wj_top;
  mvaInputs_["cosTheta_Kin_subleadEWj_restTop"]         = kinFit_subleadingECostS_Wj_top;

  mvaInputs_["cosThetaW_rest"]         = PWboost.CosTheta();
  mvaInputs_["cosThetaKinW_rest"]        = kinFit_PWboost.CosTheta();
  mvaInputs_["cosThetaW_lab"]         = PW.CosTheta();
  mvaInputs_["cosThetaKinW_lab"]        = kinFit_PW.CosTheta();

  mvaInputs_["cosThetab_rest"]         = Pbboost.CosTheta();
  mvaInputs_["cosThetaKinb_rest"]        = kinFit_Pbboost.CosTheta();
  mvaInputs_["cosThetab_lab"]         = Pb.CosTheta();
  mvaInputs_["cosThetaKinb_lab"]        = kinFit_Pb.CosTheta();

  mvaInputs_["Dphi_Wj1_Wj2_lab"]         = PWj1.DeltaPhi(PWj2);
  mvaInputs_["Dphi_KinWj1_KinWj2_lab"]         = kinFit_PWj1.DeltaPhi(kinFit_PWj2);

  mvaInputs_["Dphi_Wb_rest"]         = Pbboost.DeltaPhi(PWboost);
  mvaInputs_["Dphi_KinWb_rest"]        = kinFit_Pbboost.DeltaPhi(kinFit_PWboost);
  mvaInputs_["Dphi_Wb_lab"]         = Pb.DeltaPhi(PW);
  mvaInputs_["Dphi_KinWb_lab"]        = kinFit_Pb.DeltaPhi(kinFit_PW);

  mvaInputs_["cosThetaWj1_restW"]         = PWj1boost.CosTheta();
  mvaInputs_["cosThetaKinWj_restW"]         = kinFit_PWj1boost.CosTheta();

  kinFit_->integrate(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["logPKinFit"]             = ( kinFit_->p()    > 0. ) ? log(kinFit_->p())    : -1.e+3;
  mvaInputs_["logPErrKinFit"]          = ( kinFit_->pErr() > 0. ) ? log(kinFit_->pErr()) : -1.e+3;
  mvaInputs_["qg_b"]                   = recBJet.QGDiscr();
  mvaInputs_["qg_Wj1"]                 = recWJet1.QGDiscr();
  mvaInputs_["qg_Wj2"]                 = recWJet2.QGDiscr();
  mvaInputs_["pT_bWj1Wj2"]             = p4_bWj1Wj2.pt();
  mvaInputs_["pT_Wj1Wj2"]              = p4_Wj1Wj2.pt();
  //double expRjet = ( p4_bWj1Wj2.pt() > 0. ) ? 327./p4_bWj1Wj2.pt() : -1.;
  mvaInputs_["max_dR_div_expRjet"]     = 1.0; //max(dR_bWj1, dR_bWj2, dR_Wj1Wj2)/expRjet;
  return 0;

}

void HadTopTaggerFill::DefineHist(MVAInputVarHistManager* mvaInputHistManager){
  mvaInputHistManager->defineBinningOption("m_bWj1Wj2", 100, 0., 1.e+3);
  mvaInputHistManager->defineBinningOption("m_Wj1Wj2", 100, 0., 1.e+3);
  mvaInputHistManager->defineBinningOption("m_bWj1", 100, 0., 1.e+3);
  mvaInputHistManager->defineBinningOption("m_bWj2", 100, 0., 1.e+3);
  mvaInputHistManager->defineBinningOption("m_Wj1Wj2_div_m_bWj1Wj2", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("CSV_b", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("CSV_Wj1", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("CSV_Wj2", 100, 0., 1.);

  mvaInputHistManager->defineBinningOption("pT_b", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("pT_Wj1", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("pT_Wj2", 100, 0., 5.e+2);

  mvaInputHistManager->defineBinningOption("eta_b", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("eta_Wj1", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("eta_Wj2", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("phi_b", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("phi_Wj1", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("phi_Wj2", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("mass_b", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("mass_Wj1", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("mass_Wj2", 100, 0., 5.e+2);
  ////
  mvaInputHistManager->defineBinningOption("kinFit_pT_b", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("kinFit_pT_Wj1", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("kinFit_pT_Wj2", 100, 0., 5.e+2);

  mvaInputHistManager->defineBinningOption("kinFit_eta_b", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("kinFit_eta_Wj1", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("kinFit_eta_Wj2", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("kinFit_phi_b", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("kinFit_phi_Wj1", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("kinFit_phi_Wj2", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("kinFit_mass_b", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("kinFit_mass_Wj1", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("kinFit_mass_Wj2", 100, 0., 5.e+2);
  // 	  ,, ,,

  mvaInputHistManager->defineBinningOption("cosTheta_leadWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_subleadWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_Kin_leadWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_Kin_subleadWj_restTop", 100, -1., 1.);

  mvaInputHistManager->defineBinningOption("cosTheta_leadEWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_subleadEWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_Kin_leadEWj_restTop", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosTheta_Kin_subleadEWj_restTop", 100, -1., 1.);

  mvaInputHistManager->defineBinningOption("cosThetaW_rest", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaKinW_rest", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaW_lab", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaKinW_lab", 100, -1., 1.);

  mvaInputHistManager->defineBinningOption("cosThetab_rest", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaKinb_rest", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetab_lab", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaKinb_lab", 100, -1., 1.);


  mvaInputHistManager->defineBinningOption("Dphi_Wj1_Wj2_lab", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("Dphi_KinWj1_KinWj2_lab", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("Dphi_Wb_rest", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("Dphi_KinWb_rest", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("Dphi_Wb_lab", 100, -5., 5.);
  mvaInputHistManager->defineBinningOption("Dphi_KinWb_lab", 100, -5., 5.);

  mvaInputHistManager->defineBinningOption("cosThetaWj1_restW", 100, -1., 1.);
  mvaInputHistManager->defineBinningOption("cosThetaKinWj_restW", 100, -1., 1.);

  mvaInputHistManager->defineBinningOption("dR_bWj1", 100, 0., 5.);
  mvaInputHistManager->defineBinningOption("dR_bWj2", 100, 0., 5.);
  mvaInputHistManager->defineBinningOption("dR_Wj1Wj2", 100, 0., 5.);
  mvaInputHistManager->defineBinningOption("dR_bW", 100, 0., 5.);
  mvaInputHistManager->defineBinningOption("statusKinFit", 6, -1., +5.);
  mvaInputHistManager->defineBinningOption("nllKinFit", 150, -10., +5.);
  mvaInputHistManager->defineBinningOption("alphaKinFit", 200, 0., 2.);
  mvaInputHistManager->defineBinningOption("logPKinFit", 150, -10., +5.);
  mvaInputHistManager->defineBinningOption("logPErrKinFit", 250, -20., +5.);
  mvaInputHistManager->defineBinningOption("qg_b", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("qg_Wj1", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("qg_Wj2", 100, 0., 1.);
  mvaInputHistManager->defineBinningOption("pT_bWj1Wj2", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("pT_Wj1Wj2", 100, 0., 5.e+2);
  mvaInputHistManager->defineBinningOption("max_dR_div_expRjet", 200, 0., 2.);

}

const std::vector<std::string>& HadTopTaggerFill::mvaInputVariables() const {  return mvaInputVariables_; }

const std::map<std::string, double>& HadTopTaggerFill::mvaInputs() const {  return mvaInputs_; }

const HadTopKinFit* HadTopTaggerFill::kinFit() const {  return kinFit_; }
