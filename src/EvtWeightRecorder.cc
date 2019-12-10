#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder

#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h"
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h"
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_Base.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_1tau_trigger.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_2tau_trigger.h"
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h"
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h"
#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h"
#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h"

#include <algorithm>
#include <cassert> // assert()

EvtWeightRecorder::EvtWeightRecorder()
  : EvtWeightRecorder({ "central" }, "central", false)
{}

EvtWeightRecorder::EvtWeightRecorder(const std::vector<std::string> & central_or_shifts,
                                     const std::string & central_or_shift,
                                     bool isMC)
  : isMC_(isMC)
  , genWeight_(1.)
  , leptonSF_(1.)
  , chargeMisIdProb_(1.)
  , prescale_(1.)
  , bm_weight_(1.)
  , rescaling_(1.)
  , central_or_shift_(central_or_shift)
  , central_or_shifts_(central_or_shifts)
{
  for(const std::string & central_or_shift_option: central_or_shifts_)
  {
    checkOptionValidity(central_or_shift_option, isMC);
  }
  assert(std::find(central_or_shifts_.cbegin(), central_or_shifts_.cend(), central_or_shift_) != central_or_shifts_.cend());
}

double
EvtWeightRecorder::get(const std::string & central_or_shift) const
{
  return (isMC_ ? get_inclusive(central_or_shift) * get_data_to_MC_correction(central_or_shift) * prescale_ : 1.) *
         get_FR(central_or_shift) * chargeMisIdProb_
  ;
}

double
EvtWeightRecorder::get_inclusive(const std::string & central_or_shift) const
{
  return isMC_ ? get_genWeight() * get_bmWeight() * get_auxWeight(central_or_shift) * get_lumiScale(central_or_shift) *
                 get_nom_tH_weight(central_or_shift) * get_puWeight(central_or_shift) *
                 get_l1PreFiringWeight(central_or_shift) * get_lheScaleWeight(central_or_shift) *
                 get_dy_rwgt(central_or_shift) * get_rescaling()
               : 1.
  ;
}

double
EvtWeightRecorder::get_genWeight() const
{
  return genWeight_;
}

double
EvtWeightRecorder::get_bmWeight() const
{
  return bm_weight_;
}

double
EvtWeightRecorder::get_rescaling() const
{
  return rescaling_;
}

double
EvtWeightRecorder::get_auxWeight(const std::string & central_or_shift) const
{
  if(isMC_ && auxWeight_.count(central_or_shift))
  {
    return auxWeight_.at(central_or_shift);
  }
  return 1.;
}

double
EvtWeightRecorder::get_lumiScale(const std::string & central_or_shift) const
{
  if(isMC_ && lumiScale_.count(central_or_shift))
  {
    return lumiScale_.at(central_or_shift);
  }
  return 1.;
}

double
EvtWeightRecorder::get_nom_tH_weight(const std::string & central_or_shift) const
{
  if(isMC_ && nom_tH_weight_.count(central_or_shift))
  {
    return nom_tH_weight_.at(central_or_shift);
  }
  return 1.;
}

double
EvtWeightRecorder::get_puWeight(const std::string & central_or_shift) const
{
  if(isMC_)
  {
    const PUsys puSys_option = getPUsys_option(central_or_shift);
    if(weights_pu_.count(puSys_option))
    {
      return  weights_pu_.at(puSys_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_l1PreFiringWeight(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_l1PreFiring_.empty())
  {
    const L1PreFiringWeightSys l1PreFire_option = getL1PreFiringWeightSys_option(central_or_shift);
    if(weights_l1PreFiring_.count(l1PreFire_option))
    {
      return weights_l1PreFiring_.at(l1PreFire_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_lheScaleWeight(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_lheScale_.empty())
  {
    const int lheScale_option = getLHEscale_option(central_or_shift);
    if(weights_lheScale_.count(lheScale_option))
    {
      return weights_lheScale_.at(lheScale_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_btag(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_btag_.empty())
  {
    const int jetBtagSF_option = getBTagWeight_option(central_or_shift);
    if(weights_btag_.count(jetBtagSF_option))
    {
      return weights_btag_.at(jetBtagSF_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_dy_rwgt(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_dy_rwgt_.empty())
  {
    const int dyMCReweighting_option = getDYMCReweighting_option(central_or_shift);
    if(weights_dy_rwgt_.count(dyMCReweighting_option))
    {
      return weights_dy_rwgt_.at(dyMCReweighting_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_dy_norm(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_dy_norm_.empty())
  {
    const int dyMCNormScaleFactors_option = getDYMCNormScaleFactors_option(central_or_shift);
    if(weights_dy_norm_.count(dyMCNormScaleFactors_option))
    {
      return weights_dy_norm_.at(dyMCNormScaleFactors_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_toppt_rwgt(const std::string & central_or_shift) const
{
  if(isMC_ && ! weights_toppt_rwgt_.empty())
  {
    const int topPtReweighting_option = getTopPtReweighting_option(central_or_shift);
    if(weights_toppt_rwgt_.count(topPtReweighting_option))
    {
      return weights_toppt_rwgt_.at(topPtReweighting_option);
    }
  }
  return 1.;
}

double
EvtWeightRecorder::get_sf_triggerEff(const std::string & central_or_shift) const
{
  double sf_triggerEff = 1.;
  if(isMC_ && (! weights_leptonTriggerEff_.empty() || ! weights_tauTriggerEff_.empty()))
  {
    const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
    if(weights_leptonTriggerEff_.count(triggerSF_option))
    {
      sf_triggerEff *= weights_leptonTriggerEff_.at(triggerSF_option);
    }
    if(weights_tauTriggerEff_.count(triggerSF_option))
    {
      sf_triggerEff *= weights_tauTriggerEff_.at(triggerSF_option);
    }
  }
  return sf_triggerEff;
}

double
EvtWeightRecorder::get_leptonSF() const
{
  return isMC_ ? leptonSF_ : 1.;
}

double
EvtWeightRecorder::get_chargeMisIdProb() const
{
  return chargeMisIdProb_;
}

double
EvtWeightRecorder::get_data_to_MC_correction(const std::string & central_or_shift) const
{
  return isMC_ ? get_sf_triggerEff(central_or_shift) * get_leptonSF() * get_tauSF(central_or_shift) *
                 get_btag(central_or_shift) * get_dy_norm(central_or_shift) * get_toppt_rwgt(central_or_shift)
               : 1.
  ;
}

double
EvtWeightRecorder::get_tauSF(const std::string & central_or_shift) const
{
  double tauSF_weight = 1.;
  if(isMC_)
  {
    const TauIDSFsys tauIDSF_option = getTauIDSFsys_option(central_or_shift);
    if(weights_hadTauID_and_Iso_.count(tauIDSF_option))
    {
      tauSF_weight *= weights_hadTauID_and_Iso_.at(tauIDSF_option);
    }
    const FRet eToTauFakeRate_option = getEToTauFR_option(central_or_shift);
    if(weights_eToTauFakeRate_.count(eToTauFakeRate_option))
    {
      tauSF_weight *= weights_eToTauFakeRate_.at(eToTauFakeRate_option);
    }
    const FRmt muToTauFakeRate_option = getMuToTauFR_option(central_or_shift);
    if(weights_muToTauFakeRate_.count(muToTauFakeRate_option))
    {
      tauSF_weight *= weights_muToTauFakeRate_.at(muToTauFakeRate_option);
    }
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    if(weights_SF_hadTau_lead_.count(jetToTauFakeRate_option))
    {
      tauSF_weight *= weights_SF_hadTau_lead_.at(jetToTauFakeRate_option);
    }
    if(weights_SF_hadTau_sublead_.count(jetToTauFakeRate_option))
    {
      tauSF_weight *= weights_SF_hadTau_sublead_.at(jetToTauFakeRate_option);
    }
  }
  return tauSF_weight;
}

double
EvtWeightRecorder::get_FR(const std::string & central_or_shift) const
{
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
  const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
  if(weights_FR_.count(weightKey))
  {
    return weights_FR_.at(weightKey);
  }
  return 1.;
}

void
EvtWeightRecorder::record_genWeight(double genWeight)
{
  assert(isMC_);
  genWeight_ = genWeight;
}

void
EvtWeightRecorder::record_auxWeight(const EvtWeightManager * const evtWeightManager)
{
  assert(isMC_);
  auxWeight_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    auxWeight_[central_or_shift] = evtWeightManager->has_central_or_shift(central_or_shift) ?
      evtWeightManager->getWeight(central_or_shift) :
      evtWeightManager->getWeight()
    ;
  }
}

void
EvtWeightRecorder::record_dy_rwgt(const DYMCReweighting * const dyReweighting,
                                  const std::vector<GenParticle> & genTauLeptons)
{
  assert(isMC_);
  weights_dy_rwgt_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int dyMCReweighting_option = getDYMCReweighting_option(central_or_shift);
    if(weights_dy_rwgt_.count(dyMCReweighting_option))
    {
      continue;
    }
    weights_dy_rwgt_[dyMCReweighting_option] = dyReweighting->getWeight(genTauLeptons, dyMCReweighting_option);
  }
}

void
EvtWeightRecorder::record_dy_norm(const DYMCNormScaleFactors * const dyNormScaleFactors,
                                  const std::vector<GenParticle> & genTauLeptons,
                                  int nJets,
                                  int nBLoose,
                                  int nBMedium)
{
  assert(isMC_);
  weights_dy_norm_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int dyMCNormScaleFactors_option = getDYMCNormScaleFactors_option(central_or_shift);
    if(weights_dy_norm_.count(dyMCNormScaleFactors_option))
    {
      continue;
    }
    weights_dy_norm_[dyMCNormScaleFactors_option] = dyNormScaleFactors->getWeight(
      genTauLeptons, nJets, nBLoose, nBMedium, dyMCNormScaleFactors_option
    );
  }
}

void
EvtWeightRecorder::record_toppt_rwgt(const std::vector<GenParticle> & genTopQuarks)
{
  assert(isMC_);
  weights_toppt_rwgt_.clear();

  // find generator-level top and anti-top quark
  const GenParticle* genTopQuark     = nullptr;
  const GenParticle* genAntiTopQuark = nullptr;
  for (std::vector<GenParticle>::const_iterator genQuark = genTopQuarks.begin(); genQuark != genTopQuarks.end(); ++genQuark)
  {
    if ( genQuark->pdgId() == +6 ) genTopQuark     = &(*genQuark);
    if ( genQuark->pdgId() == -6 ) genAntiTopQuark = &(*genQuark);
  }

  double topPtWeight = 1.;
  if (genTopQuark && genAntiTopQuark)
  {
    // CV: coefficients for top pT reweighting for Run 2 data vs POWHEG MC taken from
    //       https://twiki.cern.ch/twiki/bin/view/CMS/TopPtReweighting#Use_case_3_ttbar_MC_is_used_to_m
    const double a =  0.0615;
    const double b = -0.0005;
    topPtWeight = sqrt(exp(a + b*genTopQuark->pt())*exp(a + b*genAntiTopQuark->pt()));
  }

  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int topPtReweighting_option = getTopPtReweighting_option(central_or_shift);
    if(weights_toppt_rwgt_.count(topPtReweighting_option))
    {
      continue;
    }
    
    if      (topPtReweighting_option == kTopPtReweighting_central  ) weights_toppt_rwgt_[topPtReweighting_option] = topPtWeight;
    else if (topPtReweighting_option == kTopPtReweighting_shiftUp  ) weights_toppt_rwgt_[topPtReweighting_option] = topPtWeight*topPtWeight;
    else if (topPtReweighting_option == kTopPtReweighting_shiftDown) weights_toppt_rwgt_[topPtReweighting_option] = 1.;
    else assert(0);
  }
}

void
EvtWeightRecorder::record_toppt_rwgt(double sf)
{
  assert(isMC_);
  weights_toppt_rwgt_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int topPtReweighting_option = getTopPtReweighting_option(central_or_shift);
    if(weights_toppt_rwgt_.count(topPtReweighting_option))
    {
      continue;
    }

    if      (topPtReweighting_option == kTopPtReweighting_central  ) weights_toppt_rwgt_[topPtReweighting_option] = sf;
    else if (topPtReweighting_option == kTopPtReweighting_shiftUp  ) weights_toppt_rwgt_[topPtReweighting_option] = sf * sf;
    else if (topPtReweighting_option == kTopPtReweighting_shiftDown) weights_toppt_rwgt_[topPtReweighting_option] = 1.;
    else assert(0);
  }
}
 
void
EvtWeightRecorder::record_lumiScale(const edm::VParameterSet & lumiScales)
{
  assert(isMC_);
  lumiScale_.clear();
  for(const edm::ParameterSet & lumiScale: lumiScales)
  {
    const std::string central_or_shift = lumiScale.getParameter<std::string>("central_or_shift");
    const double nof_events = lumiScale.getParameter<double>("lumi");
    lumiScale_[central_or_shift] = nof_events;
  }
  assert(lumiScale_.count(central_or_shift_));
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    if(! lumiScale_.count(central_or_shift))
    {
      lumiScale_[central_or_shift] = lumiScale_.at(central_or_shift_);
    }
  }
}

void
EvtWeightRecorder::record_rescaling(double rescaling)
{
  assert(isMC_);
  rescaling_ = rescaling;
}

void
EvtWeightRecorder::record_nom_tH_weight(const EventInfo * const eventInfo)
{
  assert(isMC_);
  nom_tH_weight_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    nom_tH_weight_[central_or_shift] = eventInfo->has_central_or_shift(central_or_shift) ?
      eventInfo->genWeight_tH(central_or_shift) :
      eventInfo->genWeight_tH()
    ;
  }
}

void
EvtWeightRecorder::record_leptonSF(double weight)
{
  assert(isMC_);
  leptonSF_ *= weight;
}

void
EvtWeightRecorder::record_chargeMisIdProb(double weight)
{
  chargeMisIdProb_ = weight;
}

void
EvtWeightRecorder::record_prescale(double weight)
{
  assert(isMC_);
  prescale_ = weight;
}

void
EvtWeightRecorder::record_bm(double weight)
{
  assert(isMC_);
  bm_weight_ = weight;
}

void
EvtWeightRecorder::record_l1PrefireWeight(const L1PreFiringWeightReader * const l1PreFiringWeightReader)
{
  assert(isMC_);
  weights_l1PreFiring_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const L1PreFiringWeightSys l1PreFire_option = getL1PreFiringWeightSys_option(central_or_shift);
    if(weights_l1PreFiring_.count(l1PreFire_option))
    {
      continue;
    }
    weights_l1PreFiring_[l1PreFire_option] = l1PreFiringWeightReader->getWeight(l1PreFire_option);
  }
}

void
EvtWeightRecorder::record_lheScaleWeight(const LHEInfoReader * const lheInfoReader)
{
  assert(isMC_);
  weights_lheScale_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int lheScale_option = getLHEscale_option(central_or_shift);
    if(weights_lheScale_.count(lheScale_option))
    {
      continue;
    }
    weights_lheScale_[lheScale_option] = lheInfoReader->getWeight_scale(lheScale_option);
  }
}

void
EvtWeightRecorder::record_puWeight(const EventInfo * const eventInfo)
{
  assert(isMC_);
  weights_pu_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const PUsys puSys_option = getPUsys_option(central_or_shift);
    if(weights_pu_.count(puSys_option))
    {
      continue;
    }
    switch(puSys_option)
    {
      case PUsys::central: weights_pu_[puSys_option] = eventInfo->pileupWeight;     break;
      case PUsys::up:      weights_pu_[puSys_option] = eventInfo->pileupWeightUp;   break;
      case PUsys::down:    weights_pu_[puSys_option] = eventInfo->pileupWeightDown; break;
      default: assert(0);
    }
  }
}

void
EvtWeightRecorder::record_btagWeight(const std::vector<const RecoJet *> & jets)
{
  assert(isMC_);
  weights_btag_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetBtagSF_option = getBTagWeight_option(central_or_shift);
    if(weights_btag_.count(jetBtagSF_option))
    {
      continue;
    }
    weights_btag_[jetBtagSF_option] = get_BtagWeight(jets, jetBtagSF_option);
  }
}

void
EvtWeightRecorder::record_leptonTriggerEff(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface)
{
  assert(isMC_);
  weights_leptonTriggerEff_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
    if(weights_leptonTriggerEff_.count(triggerSF_option))
    {
      continue;
    }
    weights_leptonTriggerEff_[triggerSF_option] = dataToMCcorrectionInterface->getSF_leptonTriggerEff(triggerSF_option);
  }
}

void
EvtWeightRecorder::record_tauTriggerEff(const Data_to_MC_CorrectionInterface_0l_2tau_trigger * const dataToMCcorrectionInterface_0l_2tau_trigger)
{
  assert(isMC_);
  weights_tauTriggerEff_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
    if(weights_tauTriggerEff_.count(triggerSF_option))
    {
      continue;
    }
    weights_tauTriggerEff_[triggerSF_option] = dataToMCcorrectionInterface_0l_2tau_trigger->getSF_triggerEff(triggerSF_option);
  }
}

void
EvtWeightRecorder::record_tauTriggerEff(const Data_to_MC_CorrectionInterface_1l_1tau_trigger * const dataToMCcorrectionInterface_1l_1tau_trigger)
{
  assert(isMC_);
  weights_tauTriggerEff_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
    if(weights_tauTriggerEff_.count(triggerSF_option))
    {
      continue;
    }
    weights_tauTriggerEff_[triggerSF_option] = dataToMCcorrectionInterface_1l_1tau_trigger->getSF_triggerEff(triggerSF_option);
  }
}

void
EvtWeightRecorder::record_tauTriggerEff(const Data_to_MC_CorrectionInterface_1l_2tau_trigger * const dataToMCcorrectionInterface_1l_2tau_trigger)
{
  assert(isMC_);
  weights_tauTriggerEff_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
    if(weights_tauTriggerEff_.count(triggerSF_option))
    {
      continue;
    }
    weights_tauTriggerEff_[triggerSF_option] = dataToMCcorrectionInterface_1l_2tau_trigger->getSF_triggerEff(triggerSF_option);
  }
}

void
EvtWeightRecorder::record_hadTauID_and_Iso(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface)
{
  assert(isMC_);
  weights_hadTauID_and_Iso_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const TauIDSFsys tauIDSF_option = getTauIDSFsys_option(central_or_shift);
    if(weights_hadTauID_and_Iso_.count(tauIDSF_option))
    {
      continue;
    }
    weights_hadTauID_and_Iso_[tauIDSF_option] = dataToMCcorrectionInterface->getSF_hadTauID_and_Iso(tauIDSF_option);
  }
}

void
EvtWeightRecorder::record_eToTauFakeRate(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface)
{
  assert(isMC_);
  weights_eToTauFakeRate_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const FRet eToTauFakeRate_option = getEToTauFR_option(central_or_shift);
    if(weights_eToTauFakeRate_.count(eToTauFakeRate_option))
    {
      continue;
    }
    weights_eToTauFakeRate_[eToTauFakeRate_option] = dataToMCcorrectionInterface->getSF_eToTauFakeRate(eToTauFakeRate_option);
  }
}

void
EvtWeightRecorder::record_muToTauFakeRate(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface)
{
  assert(isMC_);
  weights_muToTauFakeRate_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const FRmt muToTauFakeRate_option = getMuToTauFR_option(central_or_shift);
    if(weights_muToTauFakeRate_.count(muToTauFakeRate_option))
    {
      continue;
    }
    weights_muToTauFakeRate_[muToTauFakeRate_option] = dataToMCcorrectionInterface->getSF_muToTauFakeRate(muToTauFakeRate_option);
  }
}

void
EvtWeightRecorder::record_jetToTau_FR_lead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                                           const RecoHadTau * const hadTau_lead)
{
  const double hadTauPt_lead = hadTau_lead->pt();
  const double hadTauAbsEta_lead = hadTau_lead->absEta();
  weights_FR_hadTau_lead_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    if(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option))
    {
      continue;
    }
    weights_FR_hadTau_lead_[jetToTauFakeRate_option] = jetToTauFakeRateInterface->getWeight_lead(
      hadTauPt_lead, hadTauAbsEta_lead, jetToTauFakeRate_option
    );
  }
}

void
EvtWeightRecorder::record_jetToTau_FR_sublead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                                              const RecoHadTau * const hadTau_sublead)
{
  const double hadTauPt_sublead = hadTau_sublead->pt();
  const double hadTauAbsEta_sublead = hadTau_sublead->absEta();
  weights_FR_hadTau_sublead_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    if(weights_FR_hadTau_sublead_.count(jetToTauFakeRate_option))
    {
      continue;
    }
    weights_FR_hadTau_sublead_[jetToTauFakeRate_option] = jetToTauFakeRateInterface->getWeight_sublead(
      hadTauPt_sublead, hadTauAbsEta_sublead, jetToTauFakeRate_option
    );
  }
}

void
EvtWeightRecorder::record_jetToTau_SF_lead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                                           const RecoHadTau * const hadTau_lead)
{
  assert(isMC_);
  const double hadTauPt_lead = hadTau_lead->pt();
  const double hadTauAbsEta_lead = hadTau_lead->absEta();
  weights_SF_hadTau_lead_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    if(weights_SF_hadTau_lead_.count(jetToTauFakeRate_option))
    {
      continue;
    }
    weights_SF_hadTau_lead_[jetToTauFakeRate_option] = jetToTauFakeRateInterface->getSF_lead(
      hadTauPt_lead, hadTauAbsEta_lead, jetToTauFakeRate_option
    );
  }
}

void
EvtWeightRecorder::record_jetToTau_SF_sublead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                                              const RecoHadTau * const hadTau_sublead)
{
  assert(isMC_);
  const double hadTauPt_sublead = hadTau_sublead->pt();
  const double hadTauAbsEta_sublead = hadTau_sublead->absEta();
  weights_SF_hadTau_sublead_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    if(weights_SF_hadTau_sublead_.count(jetToTauFakeRate_option))
    {
      continue;
    }
    weights_SF_hadTau_sublead_[jetToTauFakeRate_option] = jetToTauFakeRateInterface->getSF_sublead(
      hadTauPt_sublead, hadTauAbsEta_sublead, jetToTauFakeRate_option
    );
  }
}

void
EvtWeightRecorder::record_jetToLepton_FR(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                         const RecoLepton * const lepton,
                                         std::map<int, double> & weights_FR_lepton)
{
  const int leptonPdgId = std::abs(lepton->pdgId());
  const double leptonPt = lepton->cone_pt();
  const double leptonAbsEta = lepton->absEta();
  assert(leptonPdgId == 11 || leptonPdgId == 13);
  weights_FR_lepton.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    if(weights_FR_lepton.count(jetToLeptonFakeRate_option))
    {
      continue;
    }
    if(leptonPdgId == 11)
    {
      int jetToLeptonFakeRate_option_e = jetToLeptonFakeRate_option;
      if(jetToLeptonFakeRate_option_e >= kFRm_shape_ptUp && jetToLeptonFakeRate_option_e <= kFRm_shape_eta_barrelDown)
      {
        jetToLeptonFakeRate_option_e = kFRl_central;
      }
      weights_FR_lepton[jetToLeptonFakeRate_option] = leptonFakeRateInterface->getWeight_e(
        leptonPt, leptonAbsEta, jetToLeptonFakeRate_option_e
      );
    }
    else if(leptonPdgId == 13)
    {
      int jetToLeptonFakeRate_option_m = jetToLeptonFakeRate_option;
      if(jetToLeptonFakeRate_option_m >= kFRe_shape_ptUp && jetToLeptonFakeRate_option_m <= kFRe_shape_eta_barrelDown)
      {
        jetToLeptonFakeRate_option_m = kFRl_central;
      }
      weights_FR_lepton[jetToLeptonFakeRate_option] = leptonFakeRateInterface->getWeight_mu(
        leptonPt, leptonAbsEta, jetToLeptonFakeRate_option_m
      );
    }
    else
    {
      throw cmsException(this, __func__, __LINE__) << "Invalid PDG ID: " << leptonPdgId;
    }
  }
}

void
EvtWeightRecorder::record_jetToLepton_FR_lead(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                              const RecoLepton * const lepton_lead)
{
  record_jetToLepton_FR(leptonFakeRateInterface, lepton_lead, weights_FR_lepton_lead_);
}

void
EvtWeightRecorder::record_jetToLepton_FR_sublead(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                                 const RecoLepton * const lepton_sublead)
{
  record_jetToLepton_FR(leptonFakeRateInterface, lepton_sublead, weights_FR_lepton_sublead_);
}

void
EvtWeightRecorder::record_jetToLepton_FR_third(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                               const RecoLepton * const lepton_third)
{
  record_jetToLepton_FR(leptonFakeRateInterface, lepton_third, weights_FR_lepton_third_);
}

void
EvtWeightRecorder::record_jetToLepton_FR_fourth(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                                const RecoLepton * const lepton_fourth)
{
  record_jetToLepton_FR(leptonFakeRateInterface, lepton_fourth, weights_FR_lepton_fourth_);
}

void
EvtWeightRecorder::compute_FR_2l2tau(bool passesTight_lepton_lead,
                                     bool passesTight_lepton_sublead,
                                     bool passesTight_hadTau_lead,
                                     bool passesTight_hadTau_sublead)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  assert(! weights_FR_hadTau_lead_.empty());
  assert(! weights_FR_hadTau_sublead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    assert(weights_FR_hadTau_sublead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_4L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead,
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),       passesTight_hadTau_lead,
      weights_FR_hadTau_sublead_.at(jetToTauFakeRate_option),    passesTight_hadTau_sublead
    );
  }
}

void
EvtWeightRecorder::compute_FR_2l1tau(bool passesTight_lepton_lead,
                                     bool passesTight_lepton_sublead,
                                     bool passesTight_hadTau)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  assert(! weights_FR_hadTau_lead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_3L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead,
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),       passesTight_hadTau
    );
  }
}

void
EvtWeightRecorder::compute_FR_2l(bool passesTight_lepton_lead,
                                 bool passesTight_lepton_sublead)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_2L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead
    );
  }
}

void
EvtWeightRecorder::compute_FR_3l(bool passesTight_lepton_lead,
                                 bool passesTight_lepton_sublead,
                                 bool passesTight_lepton_third)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  assert(! weights_FR_lepton_third_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_third_.count(jetToLeptonFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_3L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead,
      weights_FR_lepton_third_.at(jetToLeptonFakeRate_option),   passesTight_lepton_third
    );
  }
}

void
EvtWeightRecorder::compute_FR_4l(bool passesTight_lepton_lead,
                                 bool passesTight_lepton_sublead,
                                 bool passesTight_lepton_third,
                                 bool passesTight_lepton_fourth)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  assert(! weights_FR_lepton_third_.empty());
  assert(! weights_FR_lepton_fourth_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_third_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_fourth_.count(jetToLeptonFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_4L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead,
      weights_FR_lepton_third_.at(jetToLeptonFakeRate_option),   passesTight_lepton_third,
      weights_FR_lepton_fourth_.at(jetToLeptonFakeRate_option),  passesTight_lepton_fourth
    );
  }
}

void
EvtWeightRecorder::compute_FR_3l1tau(bool passesTight_lepton_lead,
                                     bool passesTight_lepton_sublead,
                                     bool passesTight_lepton_third,
                                     bool passesTight_hadTau)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_lepton_sublead_.empty());
  assert(! weights_FR_lepton_third_.empty());
  assert(! weights_FR_hadTau_lead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_lepton_third_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_4L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option),    passesTight_lepton_lead,
      weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option), passesTight_lepton_sublead,
      weights_FR_lepton_third_.at(jetToLeptonFakeRate_option),   passesTight_lepton_third,
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),       passesTight_hadTau
    );
  }
}

void
EvtWeightRecorder::compute_FR_1l2tau(bool passesTight_lepton,
                                     bool passesTight_hadTau_lead,
                                     bool passesTight_hadTau_sublead)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_hadTau_lead_.empty());
  assert(! weights_FR_hadTau_sublead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    assert(weights_FR_hadTau_sublead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_3L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option), passesTight_lepton,
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),    passesTight_hadTau_lead,
      weights_FR_hadTau_sublead_.at(jetToTauFakeRate_option), passesTight_hadTau_sublead
    );
  }
}

void
EvtWeightRecorder::compute_FR_1l1tau(bool passesTight_lepton,
                                     bool passesTight_hadTau)
{
  assert(! weights_FR_lepton_lead_.empty());
  assert(! weights_FR_hadTau_lead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_2L(
      weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option), passesTight_lepton,
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),    passesTight_hadTau
    );
  }
}

void
EvtWeightRecorder::compute_FR_1tau()
{
  assert(! weights_FR_hadTau_lead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_1L(weights_FR_hadTau_lead_.at(jetToTauFakeRate_option));
  }
}

void
EvtWeightRecorder::compute_FR_2tau(bool passesTight_hadTau_lead,
                                   bool passesTight_hadTau_sublead)
{
  assert(! weights_FR_hadTau_lead_.empty());
  assert(! weights_FR_hadTau_sublead_.empty());
  weights_FR_.clear();
  for(const std::string & central_or_shift: central_or_shifts_)
  {
    const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
    const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
    assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
    assert(weights_FR_hadTau_sublead_.count(jetToTauFakeRate_option));
    const std::string weightKey = jetToLeptonFakeRate_option == kFRl_central && jetToTauFakeRate_option == kFRjt_central ? "central" : central_or_shift;
    if(weights_FR_.count(weightKey))
    {
      continue;
    }
    weights_FR_[weightKey] = getWeight_2L(
      weights_FR_hadTau_lead_.at(jetToTauFakeRate_option),    passesTight_hadTau_lead,
      weights_FR_hadTau_sublead_.at(jetToTauFakeRate_option), passesTight_hadTau_sublead
    );
  }
}

double
EvtWeightRecorder::get_jetToLepton_FR_lead(const std::string & central_or_shift)
{
  assert(! weights_FR_lepton_lead_.empty());
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  assert(weights_FR_lepton_lead_.count(jetToLeptonFakeRate_option));
  return weights_FR_lepton_lead_.at(jetToLeptonFakeRate_option);
}

double
EvtWeightRecorder::get_jetToLepton_FR_sublead(const std::string & central_or_shift)
{
  assert(! weights_FR_lepton_sublead_.empty());
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  assert(weights_FR_lepton_sublead_.count(jetToLeptonFakeRate_option));
  return weights_FR_lepton_sublead_.at(jetToLeptonFakeRate_option);
}

double
EvtWeightRecorder::get_jetToLepton_FR_third(const std::string & central_or_shift)
{
  assert(! weights_FR_lepton_third_.empty());
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  assert(weights_FR_lepton_third_.count(jetToLeptonFakeRate_option));
  return weights_FR_lepton_third_.at(jetToLeptonFakeRate_option);
}

double
EvtWeightRecorder::get_jetToLepton_FR_fourth(const std::string & central_or_shift)
{
  assert(! weights_FR_lepton_fourth_.empty());
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  assert(weights_FR_lepton_fourth_.count(jetToLeptonFakeRate_option));
  return weights_FR_lepton_fourth_.at(jetToLeptonFakeRate_option);
}

double
EvtWeightRecorder::get_jetToTau_FR_lead(const std::string & central_or_shift)
{
  assert(! weights_FR_hadTau_lead_.empty());
  const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
  assert(weights_FR_hadTau_lead_.count(jetToTauFakeRate_option));
  return weights_FR_hadTau_lead_.at(jetToTauFakeRate_option);
}

double
EvtWeightRecorder::get_jetToTau_FR_sublead(const std::string & central_or_shift)
{
  assert(! weights_FR_hadTau_sublead_.empty());
  const int jetToTauFakeRate_option = getJetToTauFR_option(central_or_shift);
  assert(weights_FR_hadTau_sublead_.count(jetToTauFakeRate_option));
  return weights_FR_hadTau_sublead_.at(jetToTauFakeRate_option);
}

std::ostream &
operator<<(std::ostream & os,
           const EvtWeightRecorder & evtWeightRecorder)
{
  for(const std::string & central_or_shift: evtWeightRecorder.central_or_shifts_)
  {
    os << "central_or_shift = " << central_or_shift                                                     << "\n"
          "  genWeight             = " << evtWeightRecorder.get_genWeight()                             << "\n"
          "  BM weight             = " << evtWeightRecorder.get_bmWeight()                              << "\n"
          "  stitching weight      = " << evtWeightRecorder.get_auxWeight(central_or_shift)             << "\n"
          "  lumiScale             = " << evtWeightRecorder.get_lumiScale(central_or_shift)             << "\n"
          "  nominal tH weight     = " << evtWeightRecorder.get_nom_tH_weight(central_or_shift)         << "\n"
          "  PU weight             = " << evtWeightRecorder.get_puWeight(central_or_shift)              << "\n"
          "  L1 prefiring weight   = " << evtWeightRecorder.get_l1PreFiringWeight(central_or_shift)     << "\n"
          "  LHE scale weight      = " << evtWeightRecorder.get_lheScaleWeight(central_or_shift)        << "\n"
          "  DY reweighting weight = " << evtWeightRecorder.get_dy_rwgt(central_or_shift)               << "\n"
          "  inclusive weight      = " << evtWeightRecorder.get_inclusive(central_or_shift)             << "\n"
          "  trigger eff SF        = " << evtWeightRecorder.get_sf_triggerEff(central_or_shift)         << "\n"
          "  lepton SF             = " << evtWeightRecorder.get_leptonSF()                              << "\n"
          "  tau SF                = " << evtWeightRecorder.get_tauSF(central_or_shift)                 << "\n"
          "  DY norm weight        = " << evtWeightRecorder.get_dy_norm(central_or_shift)               << "\n"
          "  btag weight           = " << evtWeightRecorder.get_btag(central_or_shift)                  << "\n"
          "  data/MC correction    = " << evtWeightRecorder.get_data_to_MC_correction(central_or_shift) << "\n"
          "  FR weight             = " << evtWeightRecorder.get_FR(central_or_shift)                    << "\n"
          "  charge mis-ID prob    = " << evtWeightRecorder.get_chargeMisIdProb()                       << "\n"
          "  final weight          = " << evtWeightRecorder.get(central_or_shift)                       << '\n'
   ;
  }
  return os;
}
