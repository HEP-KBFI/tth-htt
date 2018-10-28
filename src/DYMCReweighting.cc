#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kDYMCReweighting_*
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase

#include <TFile.h> // TFile

DYMCReweighting::DYMCReweighting(int era,
                                 int central_or_shift,
                                 bool debug)
  : era_(era)
  , central_or_shift_(central_or_shift)
  , debug_(debug)
  , weights_(nullptr)
{
  // CV: histograms for Drell-Yan MC reweighing have dilepton mass on x-axis and dilepton pT on y-axis,
  //     in order to use the lutWrapperTH2 class, we need to declare the dilepton mass as "eta"
  switch(era_)
  {
    case kEra_2016:
      weights_ = new lutWrapperTH2(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/zpt_weights_summer2016_v2.root",
        "zptmass_histo",
        lut::kXetaYpt, 50., 800., lut::kLimit, 0., 600., lut::kLimit
      );
      break;
    case kEra_2017:
      weights_ = new lutWrapperTH2(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/zpt_weights_2017.root",
        "zptmass_histo",
        lut::kXetaYpt, 50., 1000., lut::kLimit, 0., 1000., lut::kLimit
      );
      break;
    case kEra_2018:
      throw cmsException(this, __func__, __LINE__) << "Implement me!";
    default:
      throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }
}

DYMCReweighting::~DYMCReweighting()
{
  delete weights_;
  for(auto & kv: inputFiles_)
  {
    delete kv.second;
  }
}

double
DYMCReweighting::getWeight(const std::vector<GenParticle> & genTauLeptons) const
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
    const double dileptonPt = dileptonP4.pt();

    assert(weights_);
    weight = weights_->getSF(dileptonPt, dileptonMass);
    // lutWrapperTH2 (lutWrapperBase) class expects dilepton pT to be passed first; dilepton mass declared as "eta"
    if(debug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__)
                << ": dilepton pT = " << dileptonPt << ", mass = " << dileptonMass
                << " --> weight = " << weight << '\n'
      ;
    }
  }

  double retVal = 1.;
  switch(central_or_shift_)
  {
    case kDYMCReweighting_central:   retVal = weight;          break;
    case kDYMCReweighting_shiftUp:   retVal = weight * weight; break;
    case kDYMCReweighting_shiftDown: retVal = 1.;              break;
    default: assert(0);
  }
  return retVal;
}
