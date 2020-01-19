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
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 0.868; weight_error = 0.141; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 0.779; weight_error = 0.066; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.754; weight_error = 0.080; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.062; weight_error = 0.058; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 0.864; weight_error = 0.104; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 0.785; weight_error = 0.028; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.098; weight_error = 0.049; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 0.960; weight_error = 0.032; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 0.894; weight_error = 0.011; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.031; weight_error = 0.021; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 0.853; weight_error = 0.056; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 0.800; weight_error = 0.007; }
    }
    else if(era_ == kEra_2017)
    {
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 1.453; weight_error = 0.081; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 1.054; weight_error = 0.036; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.884; weight_error = 0.033; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.361; weight_error = 0.035; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 1.091; weight_error = 0.066; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 0.904; weight_error = 0.013; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.432; weight_error = 0.032; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 1.145; weight_error = 0.030; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 0.979; weight_error = 0.006; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.296; weight_error = 0.034; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 1.053; weight_error = 0.023; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 0.950; weight_error = 0.020; }
    }
    else if(era_ == kEra_2018)
    {
      if     (nBMedium >= 2 && nJets >= 4)                 { weight = 1.329; weight_error = 0.140; }
      else if(nBMedium >= 2 && nJets == 3)                 { weight = 1.012; weight_error = 0.046; }
      else if(nBMedium >= 2 && nJets == 2)                 { weight = 0.822; weight_error = 0.021; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets >= 4) { weight = 1.444; weight_error = 0.043; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 3) { weight = 1.049; weight_error = 0.023; }
      else if(nBMedium == 1 && nBLoose >= 2 && nJets == 2) { weight = 0.886; weight_error = 0.009; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets >= 4) { weight = 1.493; weight_error = 0.046; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 3) { weight = 1.110; weight_error = 0.025; }
      else if(nBMedium == 1 && nBLoose == 1 && nJets == 2) { weight = 0.941; weight_error = 0.006; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets >= 4) { weight = 1.424; weight_error = 0.025; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 3) { weight = 1.082; weight_error = 0.025; }
      else if(nBMedium == 0 && nBLoose >= 2 && nJets == 2) { weight = 0.927; weight_error = 0.018; }
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
