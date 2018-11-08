#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2016, kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kDYMCNormScaleFactors_central, kDYMCNormScaleFactors_Up, kDYMCNormScaleFactors_Down

#include <TFile.h> // TFile

DYMCNormScaleFactors::DYMCNormScaleFactors(int era, int central_or_shift, bool debug)
  : era_(era)
  , central_or_shift_(central_or_shift)
  , debug_(debug)
{

}

DYMCNormScaleFactors::~DYMCNormScaleFactors()
{

}

double
DYMCNormScaleFactors::getWeight(const std::vector<GenParticle>& genTauLeptons, int nJets, int nBLoose, int nBMedium) const
{
  const GenParticle* genTauLeptonPlus = nullptr;
  const GenParticle* genTauLeptonMinus = nullptr;
  for ( std::vector<GenParticle>::const_iterator genTauLepton = genTauLeptons.begin();
	genTauLepton != genTauLeptons.end(); ++genTauLepton ) {
    if ( genTauLepton->charge() > 0 && (!genTauLeptonPlus || genTauLepton->pt() > genTauLeptonPlus->pt()) ) {
      genTauLeptonPlus = &(*genTauLepton);
    }
    if ( genTauLepton->charge() < 0 && (!genTauLeptonMinus || genTauLepton->pt() > genTauLeptonMinus->pt()) ) {
      genTauLeptonMinus = &(*genTauLepton);
    }
  }
  double weight = 1.;
  if ( genTauLeptonPlus && genTauLeptonMinus ) {
    Particle::LorentzVector dileptonP4 = genTauLeptonPlus->p4() + genTauLeptonMinus->p4();
    double dileptonMass = dileptonP4.mass();
    //if(dileptonMass > 100 || dileptonMass < 80){
      
      if(nBMedium >= 2 && nJets >= 4) weight = 1.55849;
      else if(nBMedium >= 2 && nJets == 3) weight = 1.30195;
      else if(nBMedium >= 2 && nJets == 2) weight = 1.26364;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) weight = 1.56412;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) weight = 1.44512;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) weight = 1.31255;
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) weight = 1.58992;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) weight = 1.46169;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) weight = 1.32118;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) weight = 1.62013;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) weight = 1.45674;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) weight = 1.35712;
      //}
    if ( debug_ ) {
      std::cout << "<DYMCNormScaleFactors::getWeight>: dilepton mass = " << dileptonMass << " nBMedium "<<nBMedium<<" nBLoose "<<nBLoose<<" nJets "<<nJets<<" --> weight = " << weight << std::endl;
    }
  } else {
    weight = 1.;
  }
  double retVal = 1.;
  if      ( central_or_shift_ == kDYMCNormScaleFactors_central   ) retVal = weight;
  else if ( central_or_shift_ == kDYMCNormScaleFactors_shiftUp   ) retVal = (weight + weight - 1.0);  //cover difference of SFs from Z->ee and Z->mumu 
  else if ( central_or_shift_ == kDYMCNormScaleFactors_shiftDown ) retVal = 1.;
  else assert(0);
  return retVal;
}
