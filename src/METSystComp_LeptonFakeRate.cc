#include "tthAnalysis/HiggsToTauTau/interface/METSystComp_LeptonFakeRate.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMath.h>
#include <Math/Vector3D.h> // Needed for ROOT::Math::XYZVector

METSystComp_LeptonFakeRate::METSystComp_LeptonFakeRate(const RecoLepton & lepton, const GenMEt & genmet, const RecoMEt & met, const double & scale , const std::string & central_or_shift, bool debug)
  : scale_(scale)
  , MET_RespUp_(0.,0.,0.)
  , MET_RespDown_(0.,0.,0.)
  , MET_ResolUp_(0.,0.,0.)
  , MET_ResolDown_(0.,0.,0.)
{
  if((scale_ <= 0.) || (scale_ >= 1.0) )
    {
    throw cmsException(this, __func__, __LINE__) << "Scale should always lie in the interval (0.,1.)"; 
    }
  double reco_lepton_px = ( lepton.pt() * (TMath::Cos(lepton.phi())) );
  double reco_lepton_py = ( lepton.pt() * (TMath::Sin(lepton.phi())) );
  double reco_met_x = ( met.pt() * (TMath::Cos(met.phi())) );
  double reco_met_y = ( met.pt() * (TMath::Sin(met.phi())) );
  double gen_met_x = ( genmet.pt() * (TMath::Cos(genmet.phi())) );
  double gen_met_y = ( genmet.pt() * (TMath::Sin(genmet.phi())) );
  double gen_lepton_px = 0.;
  double gen_lepton_py = 0.;

  if(lepton.genLepton()){ // check for existence of gen-matched lepton
    gen_lepton_px = ( lepton.genLepton()->pt() * (TMath::Cos(lepton.genLepton()->phi())) );
    gen_lepton_py = ( lepton.genLepton()->pt() * (TMath::Sin(lepton.genLepton()->phi())) );
  }else{ // in case there is no gen-matched lepton use reco-lepton instead => Had. Recoil (RECO) = Had. Recoil (GEN)
    gen_lepton_px = reco_lepton_px;
    gen_lepton_py = reco_lepton_py;
  }
  
  if(debug){
    std::cout<< "reco_lepton_px "<< reco_lepton_px << " reco_lepton_py "<< reco_lepton_py << " Computed reco_lepton_pt " << TMath::Sqrt(TMath::Power(reco_lepton_px, 2.0) + TMath::Power(reco_lepton_py, 2.0)) 
	     << " lepton.pt() " << lepton.pt() << " lepton.phi() " << lepton.phi() << std::endl;
    std::cout<< "reco_met_x "<< reco_met_x << " reco_met_y "<< reco_met_y << " Computed RecoMET " << TMath::Sqrt(TMath::Power(reco_met_x, 2.0) + TMath::Power(reco_met_y, 2.0)) 
	     << " met.pt() " << met.pt() << " met.phi() " << met.phi() << std::endl;
    std::cout<< "gen_met_x "<< gen_met_x << " gen_met_y "<< gen_met_y << " Computed RecoMET " << TMath::Sqrt(TMath::Power(gen_met_x, 2.0) + TMath::Power(gen_met_y, 2.0)) 
	     << " genmet.pt() " << genmet.pt() << " genmet.phi() " << genmet.phi() << std::endl;
    std::cout<< "gen_lepton_px "<< gen_lepton_px << " gen_lepton_py " << gen_lepton_py << " Computed gen_lepton_pt " << TMath::Sqrt(TMath::Power(gen_lepton_px, 2.0) + TMath::Power(gen_lepton_py, 2.0)) << std::endl; 
    if(lepton.genLepton()){ std::cout<< " lepton.genLepton()->pt() " << lepton.genLepton()->pt() <<  " lepton.genLepton()->phi() " <<  lepton.genLepton()->phi()  << std::endl; }
  }

  ROOT::Math::XYZVector reco_lepton_vec(reco_lepton_px, reco_lepton_py, 0.);
  ROOT::Math::XYZVector reco_met_vec(reco_met_x, reco_met_y, 0.);
  ROOT::Math::XYZVector gen_met_vec(gen_met_x, gen_met_y, 0.);
  ROOT::Math::XYZVector gen_lepton_vec(gen_lepton_px, gen_lepton_py, 0.);

  if(debug){
    std::cout<< " reco_lepton_vec.Rho() " << reco_lepton_vec.Rho() << " reco_lepton_vec.Phi() " << reco_lepton_vec.Phi() << std::endl;
    std::cout<< " reco_met_vec.Rho() " << reco_met_vec.Rho() << " reco_met_vec.Phi() " << reco_met_vec.Phi() << std::endl;
    std::cout<< " gen_met_vec.Rho() " << gen_met_vec.Rho() << " gen_met_vec.Phi() " << gen_met_vec.Phi() << std::endl;
    std::cout<< " gen_lepton_vec.Rho() " << gen_lepton_vec.Rho() << " gen_lepton_vec.Phi() " << gen_lepton_vec.Phi() << std::endl;
  }

  // Computing Reco Hadronic Recoil and its systematic shifts
  ROOT::Math::XYZVector reco_had_recoil_vec_nom       = (-1.0) * (reco_met_vec + reco_lepton_vec); 
  ROOT::Math::XYZVector reco_had_recoil_vec_ScaleUp   = (1.0 + scale_) * (reco_had_recoil_vec_nom);
  ROOT::Math::XYZVector reco_had_recoil_vec_ScaleDown = (1.0 - scale_) * (reco_had_recoil_vec_nom);

  if(debug){
    std::cout<< " reco_had_recoil_vec_nom.Rho() " << reco_had_recoil_vec_nom.Rho() << " reco_had_recoil_vec_nom.Phi() " << reco_had_recoil_vec_nom.Phi() << std::endl;
    std::cout<< " reco_had_recoil_vec_ScaleUp.Rho() " << reco_had_recoil_vec_ScaleUp.Rho() << " reco_had_recoil_vec_ScaleUp.Phi() " << reco_had_recoil_vec_ScaleUp.Phi() << std::endl;
    std::cout<< " reco_had_recoil_vec_ScaleDown.Rho() " << reco_had_recoil_vec_ScaleDown.Rho() << " reco_had_recoil_vec_ScaleDown.Phi() " << reco_had_recoil_vec_ScaleDown.Phi() << std::endl;
  }

  // Computing Gen Hadronic Recoil
  ROOT::Math::XYZVector gen_had_recoil_vec_nom  = (-1.0) * (gen_met_vec + gen_lepton_vec); 

  if(debug){
    std::cout<< " gen_had_recoil_vec_nom.Rho() " << gen_had_recoil_vec_nom.Rho() << " gen_had_recoil_vec_nom.Phi() " << gen_had_recoil_vec_nom.Phi() << std::endl;
  }

  if(central_or_shift == "MET_RespUp"){
    // Computing MET Response Systematic shift Up
    ROOT::Math::XYZVector MET_RespUp_vec = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ScaleUp); 
    if(debug){std::cout<< " MET_RespUp_vec.Rho() " << MET_RespUp_vec.Rho() << " MET_RespUp_vec.Phi() " << MET_RespUp_vec.Phi() << std::endl;}
    MET_RespUp_ = MET_RespUp_vec;
  }else if(central_or_shift == "MET_RespDown"){
    // Computing MET Response Systematic shift Down
    ROOT::Math::XYZVector MET_RespDown_vec = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ScaleDown);
    if(debug){std::cout<< " MET_RespDown_vec.Rho() " << MET_RespDown_vec.Rho() << " MET_RespDown_vec.Phi() " << MET_RespDown_vec.Phi() << std::endl;} 
    MET_RespDown_ = MET_RespDown_vec;
  }else if(central_or_shift == "MET_ResolUp"){
    // Computing Systematic shifts in Reco Had Recoil Resolution Up
    ROOT::Math::XYZVector reco_had_recoil_vec_ResolUp = reco_had_recoil_vec_nom  + (scale_ * (reco_had_recoil_vec_nom - gen_had_recoil_vec_nom));
    if(debug){std::cout<< "reco_had_recoil_vec_ResolUp.Rho() " << reco_had_recoil_vec_ResolUp.Rho() << " reco_had_recoil_vec_ResolUp.Phi() " << reco_had_recoil_vec_ResolUp.Phi() << std::endl;}
    // Computing MET Resolution Systematic shifts Up
    ROOT::Math::XYZVector MET_ResolUp_vec = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ResolUp); 
    if(debug){std::cout<< " MET_ResolUp_vec.Rho() " << MET_ResolUp_vec.Rho() << " MET_ResolUp_vec.Phi() " << MET_ResolUp_vec.Phi() << std::endl;}
    MET_ResolUp_ = MET_ResolUp_vec;
  }else if(central_or_shift == "MET_ResolDown"){
    // Computing Systematic shifts in Reco Had Recoil Resolution Down
    ROOT::Math::XYZVector reco_had_recoil_vec_ResolDown = reco_had_recoil_vec_nom  - (scale_ * (reco_had_recoil_vec_nom - gen_had_recoil_vec_nom));
    if(debug){std::cout<< "reco_had_recoil_vec_ResolDown.Rho() " << reco_had_recoil_vec_ResolDown.Rho() << " reco_had_recoil_vec_ResolUp.Phi() " << reco_had_recoil_vec_ResolDown.Phi() << std::endl;}
    // Computing MET Resolution Systematic shifts Down
    ROOT::Math::XYZVector MET_ResolDown_vec = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ResolDown); 
    if(debug){std::cout<< " MET_ResolDown_vec.Rho() " << MET_ResolDown_vec.Rho() << " MET_ResolDown_vec.Phi() " << MET_ResolDown_vec.Phi() << std::endl;}
    MET_ResolDown_ = MET_ResolDown_vec;
  }else{
    throw cmsException(this, __func__, __LINE__) << "Systematic Name did not match any one of: MET_RespUp, MET_RespDown, MET_ResolUp, MET_ResolDown";
  }

}


