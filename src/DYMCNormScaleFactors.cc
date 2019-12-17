#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2016, kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kDYMCNormScaleFactors_central, kDYMCNormScaleFactors_Up, kDYMCNormScaleFactors_Down

#include <TFile.h> // TFile

DYMCNormScaleFactors::DYMCNormScaleFactors(int era,
                                           bool debug)
  : era_(era)
  , debug_(debug)
{}

DYMCNormScaleFactors::~DYMCNormScaleFactors()
{}

double
DYMCNormScaleFactors::getWeight(const std::vector<GenParticle> & genTauLeptons,
                                int nJets,
                                int nBLoose,
                                int nBMedium,
                                int central_or_shift) const
{
  const GenParticle * genTauLeptonPlus = nullptr;
  const GenParticle * genTauLeptonMinus = nullptr;
  for(const GenParticle & genTauLepton: genTauLeptons)
  {
    if(genTauLepton.charge() > 0 && (! genTauLeptonPlus || genTauLepton.pt() > genTauLeptonPlus->pt()))
    {
      genTauLeptonPlus = &genTauLepton;
    }
    if(genTauLepton.charge() < 0 && (! genTauLeptonMinus || genTauLepton.pt() > genTauLeptonMinus->pt()))
    {
      genTauLeptonMinus = &genTauLepton;
    }
  }

  double weight = 1.;
  if(genTauLeptonPlus && genTauLeptonMinus)
  {
    const Particle::LorentzVector dileptonP4 = genTauLeptonPlus->p4() + genTauLeptonMinus->p4();
    const double dileptonMass = dileptonP4.mass();

    if(era_ == kEra_2016){ 
      if     (nBMedium >= 2 && nJets >= 4)                 weight = 0.801;
      else if(nBMedium >= 2 && nJets == 3)                 weight = 0.685;
      else if(nBMedium >= 2 && nJets == 2)                 weight = 0.672;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) weight = 1.121;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) weight = 0.872;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) weight = 0.801;
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) weight = 1.145;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) weight = 0.968;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) weight = 0.891;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) weight = 1.065;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) weight = 0.845;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) weight = 0.798;
    }
    else if(era_ == kEra_2017){
      if     (nBMedium >= 2 && nJets >= 4)                 weight = 1.353;
      else if(nBMedium >= 2 && nJets == 3)                 weight = 0.949;
      else if(nBMedium >= 2 && nJets == 2)                 weight = 0.828;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) weight = 1.55;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) weight = 1.198;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) weight = 0.971;
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) weight = 1.554;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) weight = 1.20;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) weight = 1.0;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) weight = 1.431;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) weight = 1.138;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) weight = 1.01; 
    }
    else if(era_ == kEra_2018){
      if     (nBMedium >= 2 && nJets >= 4)                 weight = 1.261;
      else if(nBMedium >= 2 && nJets == 3)                 weight = 0.964;
      else if(nBMedium >= 2 && nJets == 2)                 weight = 0.781;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) weight = 1.873;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) weight = 1.318;
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) weight = 1.081;
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) weight = 1.757;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) weight = 1.264;
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) weight = 1.038;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) weight = 1.769;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) weight = 1.336;
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) weight = 1.038;
    }

    if(debug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__)
                << ": dilepton mass = " << dileptonMass
                << " nBMedium = "       << nBMedium
                << " nBLoose = "        << nBLoose
                << " nJets = "          << nJets
                << " --> weight = "     << weight << '\n'
      ;
    }
  }
  double retVal = 1.;
  
  double error=0, emdiff = 0;
  if(era_ == kEra_2016){ //kept same as 2017 till it is evaluated separately for 2016
    if     (nBMedium >= 2 && nJets >= 4)                 {error = 0.040; emdiff = weight - 0.197;}
    else if(nBMedium >= 2 && nJets == 3)                 {error = 0.024; emdiff = weight - 0.274;}
    else if(nBMedium >= 2 && nJets == 2)                 {error = 0.017; emdiff = weight - 0.380;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) {error = 0.035; emdiff = weight - 0.904;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) {error = 0.018; emdiff = weight - 0.884;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) {error = 0.011; emdiff = weight - 0.700;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) {error = 0.025; emdiff = weight - 1.074;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) {error = 0.012; emdiff = weight - 0.935;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) {error = 0.006; emdiff = weight - 0.848;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) {error = 0.019; emdiff = weight - 0.874;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) {error = 0.010; emdiff = weight - 0.794;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) {error = 0.006; emdiff = weight - 0.706;}
  }							   	      
  else if(era_ == kEra_2017){				   	      
    if     (nBMedium >= 2 && nJets >= 4)                 {error = 0.055; emdiff = weight - 0.431;}
    else if(nBMedium >= 2 && nJets == 3)                 {error = 0.026; emdiff = weight - 0.464;}
    else if(nBMedium >= 2 && nJets == 2)                 {error = 0.016; emdiff = weight - 0.494;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) {error = 0.040; emdiff = weight - 1.410;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) {error = 0.020; emdiff = weight - 1.063;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) {error = 0.010; emdiff = weight - 0.925;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) {error = 0.030; emdiff = weight - 1.449;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) {error = 0.013; emdiff = weight - 1.128;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) {error = 0.006; emdiff = weight - 0.968;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) {error = 0.020; emdiff = weight - 1.267;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) {error = 0.010; emdiff = weight - 1.019;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) {error = 0.006; emdiff = weight - 0.933;}
  }							   	      
  else if(era_ == kEra_2018){				   	      
    if     (nBMedium >= 2 && nJets >= 4)                 {error = 0.054; emdiff = weight - 0.732;}
    else if(nBMedium >= 2 && nJets == 3)                 {error = 0.028; emdiff = weight - 0.514;}
    else if(nBMedium >= 2 && nJets == 2)                 {error = 0.015; emdiff = weight - 0.544;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) {error = 0.057; emdiff = weight - 1.709;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) {error = 0.024; emdiff = weight - 1.281;}
    else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) {error = 0.012; emdiff = weight - 1.063;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) {error = 0.038; emdiff = weight - 1.667;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) {error = 0.015; emdiff = weight - 1.236;}
    else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) {error = 0.006; emdiff = weight - 1.017;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) {error = 0.030; emdiff = weight - 1.616;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) {error = 0.014; emdiff = weight - 1.207;}
    else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) {error = 0.006; emdiff = weight - 1.053;}
  }

  switch(central_or_shift)
    {
    case kDYMCNormScaleFactors_central:   retVal = weight;           break;
    case kDYMCNormScaleFactors_shiftUp:   retVal = weight + std::sqrt(error*error + emdiff*emdiff); break; // cover difference of SFs from Z->ee and Z->mumu
    case kDYMCNormScaleFactors_shiftDown: retVal = weight - std::sqrt(error*error + emdiff*emdiff); break; // cover difference of SFs from Z->ee and Z->mumu 
    default: assert(0);
  }
  return retVal;
}
