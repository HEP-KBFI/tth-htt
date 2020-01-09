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
  double weight_error = 0.;
  if(genTauLeptonPlus && genTauLeptonMinus)
  {
    const Particle::LorentzVector dileptonP4 = genTauLeptonPlus->p4() + genTauLeptonMinus->p4();
    const double dileptonMass = dileptonP4.mass();

    if(era_ == kEra_2016)
    {
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 0.740; weight_error = 0.148; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 0.654; weight_error = 0.096; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.649; weight_error = 0.090; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.100; weight_error = 0.051; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 0.876; weight_error = 0.113; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 0.792; weight_error = 0.029; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.125; weight_error = 0.043; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 0.963; weight_error = 0.035; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 0.887; weight_error = 0.011; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.040; weight_error = 0.024; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 0.841; weight_error = 0.062; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 0.791; weight_error = 0.007; }
    }
    else if(era_ == kEra_2017)
    {
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 1.388; weight_error = 0.073; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 0.915; weight_error = 0.043; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.767; weight_error = 0.025; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.559; weight_error = 0.040; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 1.187; weight_error = 0.112; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 0.964; weight_error = 0.011; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.565; weight_error = 0.034; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 1.194; weight_error = 0.048; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 0.995; weight_error = 0.009; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.452; weight_error = 0.044; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 1.134; weight_error = 0.056; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 1.003; weight_error = 0.028; }
    }
    else if(era_ == kEra_2018)
    {
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 1.372; weight_error = 0.090; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 0.990; weight_error = 0.095; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.812; weight_error = 0.042; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.706; weight_error = 0.050; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 1.205; weight_error = 0.033; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 1.024; weight_error = 0.011; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.648; weight_error = 0.047; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 1.191; weight_error = 0.037; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 1.006; weight_error = 0.008; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.609; weight_error = 0.029; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 1.201; weight_error = 0.035; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 1.034; weight_error = 0.025; }
    }
    else
    {
      throw cmsException(this, __func__, __LINE__) << "Invalid era: " << era_;
    }

    if(debug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__)
                << ": dilepton mass = " << dileptonMass
                << " nBMedium = "       << nBMedium
                << " nBLoose = "        << nBLoose
                << " nJets = "          << nJets
                << " --> weight = "     << weight
                << " +/- "              << weight_error
                << '\n'
      ;
    }
  }

  switch(central_or_shift)
  {
    case kDYMCNormScaleFactors_central:                           break;
    case kDYMCNormScaleFactors_shiftUp:   weight += weight_error; break; // cover difference of SFs from Z->ee and Z->mumu
    case kDYMCNormScaleFactors_shiftDown: weight -= weight_error; break; // cover difference of SFs from Z->ee and Z->mumu
    default: assert(0);
  }
  assert(weight > 0.);
  return weight;
}
