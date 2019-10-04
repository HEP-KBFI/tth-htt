#ifndef tthAnalysis_HiggsToTauTau_METSystComp_LeptonFakeRate_h
#define tthAnalysis_HiggsToTauTau_METSystComp_LeptonFakeRate_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenMEt.h"
#include <TVector2.h>
#include <Math/Vector3D.h> // Needed for ROOT::Math::XYZVector 

class METSystComp_LeptonFakeRate
{
 public:
  METSystComp_LeptonFakeRate(const RecoLepton & lepton, const GenMEt & genmet, const RecoMEt & met, const double & scale, const std::string & central_or_shift, bool debug);

  ROOT::Math::XYZVector Get_MET_RespUp() const {return MET_RespUp_;}  
  ROOT::Math::XYZVector Get_MET_RespDown() const{return MET_RespDown_;}  
  ROOT::Math::XYZVector Get_MET_ResolUp() const{return MET_ResolUp_;}  
  ROOT::Math::XYZVector Get_MET_ResolDown() const{return MET_ResolDown_;}  

 private:
  double scale_;
  ROOT::Math::XYZVector MET_RespUp_;
  ROOT::Math::XYZVector MET_RespDown_;
  ROOT::Math::XYZVector MET_ResolUp_;
  ROOT::Math::XYZVector MET_ResolDown_;
};







#endif // tthAnalysis_HiggsToTauTau_METSystComp_LeptonFakeRate_h
