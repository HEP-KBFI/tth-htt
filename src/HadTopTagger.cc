#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "TLorentzVector.h"
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <Python.h>


HadTopTagger::HadTopTagger(const std::string& mvaFileName)
  : kinFit_(0),
    mva_(0),
    mvaOutput_(-1.)
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
  //if ( mvaFileName != "" ) {
  //  mva_ = new TMVAInterface(mvaFileName, mvaInputVariables_, {});
  //}
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_;
}

//namespace
//{
//  double max(double value1, double value2, double value3)
//  {
//    double max12 = std::max(value1, value2);
//    return std::max(max12, value3);
//  } 
//}

/*

"m_bWj1Wj2", "m_Wj1Wj2", "m_bWj1", "m_bWj2", 
      "m_Wj1Wj2_div_m_bWj1Wj2",
      "CSV_b", "CSV_Wj1", "CSV_Wj2", 
      "pT_b", "eta_b", "phi_b", "mass_b", 
	  "kinFit_pT_b", "kinFit_eta_b", "kinFit_phi_b", "kinFit_mass_b", 
      "pT_Wj1", "eta_Wj1", "phi_Wj1", "mass_Wj1", "kinFit_pT_Wj1", "kinFit_eta_Wj1", "kinFit_phi_Wj1", "kinFit_mass_Wj1", 
      "pT_Wj2", "eta_Wj2", "phi_Wj2", "mass_Wj2", "kinFit_pT_Wj2", "kinFit_eta_Wj2", "kinFit_phi_Wj2", "kinFit_mass_Wj2",
	  "cosThetaWb_rest","cosThetaKinWb_rest","cosThetaWb_lab","cosThetaKinWb_lab",
      "dR_bWj1", "dR_bWj2", "dR_Wj1Wj2", "dR_bW",
      "statusKinFit", "nllKinFit", "alphaKinFit", "logPKinFit", "logPErrKinFit", 
      "qg_b", "qg_Wj1", "qg_Wj2",
      "pT_bWj1Wj2", "pT_Wj1Wj2",
      "max_dR_div_expRjet"
	  
"cosThetaWb_rest","cosThetaKinWb_rest","cosThetaWb_lab","cosThetaKinWb_lab"

CSV_Wj2, 

alphaKinFit, 

dR_bWj1, dR_bWj2, 

eta_Wj1, eta_Wj2, eta_b, 
kinFit_eta_Wj1, kinFit_eta_Wj2, kinFit_eta_b, 

kinFit_mass_Wj1, kinFit_mass_Wj2, kinFit_mass_b, 
mass_Wj1, mass_Wj2, mass_b,

kinFit_pT_Wj1, kinFit_pT_Wj2, kinFit_pT_b, 
pT_Wj1, pT_Wj1Wj2, pT_b, phi_Wj1, phi_Wj2, phi_b, 

kinFit_phi_Wj1, kinFit_phi_Wj2, kinFit_phi_b, 

logPErrKinFit, logPKinFit, 

m_Wj1Wj2_div_m_bWj1Wj2, m_bWj1, m_bWj1Wj2, m_bWj2, max_dR_div_expRjet, 

qg_Wj1, qg_b, statusKinFit

*/

// https://gist.github.com/rjzak/5681680
PyObject* vectorToTuple_Float(const std::vector<float> &data) {
	PyObject* tuple = PyTuple_New( data.size() );
	if (!tuple) throw std::logic_error("Unable to allocate memory for Python tuple");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyFloat_FromDouble( (double) data[i]);
		if (!num) {
			Py_DECREF(tuple);
			throw std::logic_error("Unable to allocate memory for Python tuple");
		}
		PyTuple_SET_ITEM(tuple, i, num);
	}

	return tuple;
}


PyObject* vectorToTuple_String(const std::vector<char*> &data) {
	PyObject* tuple = PyTuple_New( data.size() );
	if (!tuple) throw std::logic_error("Unable to allocate memory for Python tuple");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyString_FromString( (char*) data[i]);
		if (!num) {
			Py_DECREF(tuple);
			throw std::logic_error("Unable to allocate memory for Python tuple");
		}
		PyTuple_SET_ITEM(tuple, i, num);
	}

	return tuple;
}

double HadTopTagger::operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
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
  
  /*                  
        P1boost = P1; 
        P12 = P1 + P2; // this is the total vectorial momenta of the system
        P1boost.Boost(-P12.BoostVector()); 
        thetast = P1boost.Theta();  
	costhetast = P1boost.CosTheta()
	*/
	
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
  if ( 1>0 ) { // if ( mva_ ) {
    check_mvaInputs(mvaInputs_);
    mvaOutput_ = 34; // (*mva_)(mvaInputs_);
	//const double vec[2] = [5.0,6.7];
	// https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
	std::vector<float> vec; // = [5.0,6.7];
	vec.push_back(recBJet.BtagCSV());
	vec.push_back(recWJet1.QGDiscr());
	vec.push_back(recWJet2.QGDiscr());
	vec.push_back(p4_bWj1Wj2.mass()); 
	vec.push_back(p4_bWj1Wj2.pt());
	vec.push_back(p4_Wj1Wj2.mass());
	vec.push_back(kinFit_->nll());
	vec.push_back(kinFit_->alpha());
	vec.push_back(recBJet.pt());
	vec.push_back(recBJet.pt()/kinFit_->fittedBJet().pt());
	vec.push_back(recWJet1.pt()/kinFit_->fittedWJet1().pt());
	vec.push_back(recWJet2.pt());
	vec.push_back(recWJet2.pt()/kinFit_->fittedWJet2().pt());
	vec.push_back(PWboost.CosTheta());
	vec.push_back(leadingECostS_Wj_top);
	vec.push_back(subleadingECostS_Wj_top);
	vec.push_back(PWj1boost.CosTheta());
	/*
					'CSV_b',
				'qg_Wj2',
				'qg_Wj1',
				'm_bWj1Wj2',
				'pT_bWj1Wj2',
				'm_Wj1Wj2',
				'nllKinFit',
				'alphaKinFit',
				'pT_b', 
				'pT_b_o_kinFit_pT_b',
				'pT_Wj1_o_kinFit_pT_Wj1',			
				'pT_Wj2', 
				'pT_Wj2_o_kinFit_pT_Wj2',
				"cosThetaW_rest",
				"cosTheta_leadEWj_restTop",
				"cosTheta_subleadEWj_restTop",
				"cosThetaWj1_restW"#,
	*/
	//const std::string vec2[2]=["e1","e2"];
	std::vector<char*> vec2;
	vec2.push_back((char*) "CSV_b");
	vec2.push_back((char*) "qg_Wj2");
	vec2.push_back((char*) "qg_Wj1");
	vec2.push_back((char*) "m_bWj1Wj2");
	vec2.push_back((char*) "pT_bWj1Wj2");
	vec2.push_back((char*) "m_Wj1Wj2");
	vec2.push_back((char*) "nllKinFit");
	vec2.push_back((char*) "alphaKinFit");
	vec2.push_back((char*) "pT_b");
	vec2.push_back((char*) "pT_b_o_kinFit_pT_b");
	vec2.push_back((char*) "pT_Wj1_o_kinFit_pT_Wj1");
	vec2.push_back((char*) "pT_Wj2");
	vec2.push_back((char*) "pT_Wj2_o_kinFit_pT_Wj2");
	vec2.push_back((char*) "cosThetaW_rest");
	vec2.push_back((char*) "cosTheta_leadEWj_restTop");
	vec2.push_back((char*) "cosTheta_subleadEWj_restTop");
	vec2.push_back((char*) "cosThetaWj1_restW");
	/*
	vec2.push_back((char*) "CSV_b");
	vec2.push_back((char*) "alphaKinFit");
	vec2.push_back((char*) "dR_Wj1Wj2");
	vec2.push_back((char*) "dR_bW");
	vec2.push_back((char*) "m_Wj1Wj2");
	vec2.push_back((char*) "m_bWj1Wj2");
	vec2.push_back((char*) "nllKinFit");
	vec2.push_back((char*) "pT_Wj1");
	vec2.push_back((char*) "pT_Wj1Wj2");
	vec2.push_back((char*) "pT_Wj2");
	vec2.push_back((char*) "pT_b");
	vec2.push_back((char*) "pT_bWj1Wj2");
	vec2.push_back((char*) "qg_Wj1");
	vec2.push_back((char*) "qg_Wj2");
	*/
	//char* pklpath=(char*) 'TTToSemilepton_HadTopTagger_2000trees_angleVar_XGB_allVar_allBKG_CSV_screening.pkl';
	//char* pkldir=(char*) '/home/acaan/CMSSW_9_4_0_pre1/src/tth-bdt-training-test/HadTopTagger/HadTopTagger_2000trees_angleVar/';
	std::cout << "Do python, HTT, size: "<<vec.size() << std::endl;
	Py_SetProgramName((char*) "application");
	PyObject *moduleMainString = PyString_FromString("__main__");
	PyObject *moduleMain = PyImport_Import(moduleMainString);
	//PyObject *syspath;
	//path = Py_GetPath();
	//printf("Python search path is:\n%s\n", path);
	//syspath = PySys_GetObject((char*) "path");
	//PyObject *sysPath = PySys_GetObject((char*) pklpath);
	//PyList_Append(sysPath, programName);
	// https://ubuntuforums.org/archive/index.php/t-324544.html
	// https://stackoverflow.com/questions/4060221/how-to-reliably-open-a-file-in-the-same-directory-as-a-python-script
	PyRun_SimpleString(
	"from time import time,ctime\n"
	"import sklearn\n"\
	"import pandas\n"\
	"import cPickle as pickle\n"\
	"import sys,os \n"\
	"import numpy as np \n"\
	"import subprocess \n"\
	"from sklearn.externals import joblib \n"\
	"from itertools import izip \n"\
	"sys.path.insert(0, '/home/acaan/classifiers/xgboost/python-package') \n"\
	"import xgboost as xgb  \n"\
	"print('The xgb version is {}.'.format(xgb.__version__)) \n"\
	"def mul(vec, vec2): \n"\
	"	print 'Today is',ctime(time()), 'All python libraries we need loaded good	HTT'\n"\
	"	new_dict= { \n"\
	"	'CSV_b' : 0.612080, \n"\
	"	'qg_Wj2' :  0.441440, \n"\
	"	'qg_Wj1' :  0.880838, \n"\
	"	'm_bWj1Wj2' :  128.454788, \n"\
	"	'pT_bWj1Wj2' :  92.036545, \n"\
	"	'm_Wj1Wj2' : 64.853416, \n"\
	"	'nllKinFit' : 2.032994, \n"\
	"	'alphaKinFit' :  1.281113, \n"\
	"	'pT_b' : 33.733780, \n"\
	"	'pT_b_o_kinFit_pT_b' : 0.653336, \n"\
	"	'pT_Wj1_o_kinFit_pT_Wj1' : 0.780571, \n"\
	"	'pT_Wj2' : 47.432297, \n"\
	"	'pT_Wj2_o_kinFit_pT_Wj2' : 0.795164, \n"\
	"	'cosThetaW_rest' : 0.146524, \n"\
	"	'cosTheta_leadEWj_restTop' : 0.846982, \n"\
	"	'cosTheta_subleadEWj_restTop' : 0.740536, \n"\
	"	'cosThetaWj1_restW' :  0.962535} \n"\
	"	print (new_dict) \n"\
	"	data = pandas.DataFrame() \n"\
	"	data=data.append(new_dict, ignore_index=True) \n"\
	"	print len(data) \n"\
	"	result=-20 \n"\
	"	f = None  \n"\
	"	try: \n"\
	"		f = open('/home/acaan/CMSSW_9_4_0_pre1/src/tth-bdt-training-test/HadTopTagger/HadTopTagger_sklearnV0o17o1/TTToSemilepton_HadTopTagger_sklearnV0o17o1_XGB_allVar_allBKG_CSV_screening.pkl','rb') \n"\
	"	except IOError as e: \n"\
	"		print('Couldnt open or write to file (%s).' % e) \n"\
	"	else:  \n"\
	"			print ('file opened') \n"\
	"			try: \n"\
	"				pkldata = pickle.load(f) \n"\
	"				model = pkldata.booster().get_dump(fmap='', with_stats=False) \n"\
	"				print len(model) \n"\
	"			except : \n"\
	"				print('Oops!',sys.exc_info()[0],'occured.') \n"\
	"			else:  \n"\
	"				print ('pkl loaded') \n"\
	"				try: \n"\
	"					proba = pkldata.predict_proba(data[vec2].values  ) \n"\
	"				except : \n"\
	"					print('Oops!',sys.exc_info()[0],'occured.') \n"\
	"					result = proba[:,1][0]\n"\
	"				else:  \n"\
	"					print ('predict BDT to one event',result)  \n"\
	"			f.close()  \n"\
	"	return result                                \n"
	);
	PyObject *func = PyObject_GetAttrString(moduleMain, "mul");
	//PyObject *args = PyTuple_Pack(2, PyFloat_FromDouble(3.0), PyFloat_FromDouble(4.0));
	// subprocess.call('/home/acaan/CMSSW_9_4_0_pre1/src/tth-bdt-training-test/HadTopTagger/HadTopTagger_2000trees_angleVar/TTToSemilepton_HadTopTagger_2000trees_angleVar_XGB_allVar_allBKG_CSV_screening.pkl')
	PyObject* vector1=vectorToTuple_Float(vec);
	PyObject* vector2=vectorToTuple_String(vec2);
	PyObject *args = PyTuple_Pack(2, vector1, vector2 ); //    
	PyObject *result = PyObject_CallObject(func, args);
	printf("mul(3,4): %.2f\n", PyFloat_AsDouble(result)); // 12
	mvaOutput_=PyFloat_AsDouble(result);
	// https://gist.github.com/rjzak/5681680
	///////////////////////////////////////////////////////////////
	//float output_HH=0;
	/* //"print 'Today is',ctime(time()), 'All python libraries we need loaded good	HTT'\n"\
	std::cout << "Begin python" << std::endl; 
	const char* argv[0];
    Py_SetProgramName(argv[0]);  // optional but recommended 
    Py_Initialize();
	std::cout << "initialized" << std::endl;
	PyRun_SimpleString("from time import time,ctime\n"
					 "import sklearn\n"
					 "import pandas\n"
					 "import pickle\n"
					 //"with open(pklpath, 'rb') as fpkl, open('%s.json' % pklpath, 'w') as fjson:\n"
					 //"		pkldata = pickle.load(fpkl)\n"
					 "print 'Today is',ctime(time()), 'All python libraries we need loaded good	'\n"
					 "return 0'\n");
	//output_HH = extract<float>(main_namespace["result"]);
	std::cout << "passed" << std::endl;
	Py_Finalize();
	std::cout << "End python" << std::endl;
	// */
	
	///////////////////////////////////////////////////////////////
	//*/
    /*
	const char *command;
	Py_SetProgramName(command);
	Py_Initialize();
	boost::python::class_<std::vector<double> >("PyVec")
	.def(boost::python::vector_indexing_suite<std::vector<double> >());

	object main_module = import("__main__");
	object globals = main_module.attr("__dict__");
	globals["var"]=vec;
	object ignored = exec( 
			 "from time import time,ctime\n" 
			 "import sklearn\n"
			 "import pandas\n"
			 "import pickle\n"
			 "result = sum(var)\n" 
			 "print 'Today is',ctime(time()), 'All python libraries we need loaded good	'\n"
		, globals, globals);
	double result = extract<double>(globals["result"]);
	std::cout << result << std::endl;
	
	//*/

  } else mvaOutput_=-3;
  return mvaOutput_;
}

const std::vector<std::string>& HadTopTagger::mvaInputVariables() const
{ 
  return mvaInputVariables_; 
}

const std::map<std::string, double>& HadTopTagger::mvaInputs() const
{ 
  return mvaInputs_; 
}

const HadTopKinFit* HadTopTagger::kinFit() const 
{ 
  return kinFit_; 
}

