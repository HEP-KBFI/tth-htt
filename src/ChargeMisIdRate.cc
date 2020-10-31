#include "tthAnalysis/HiggsToTauTau/interface/ChargeMisIdRate.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType(), kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::

#include <TFile.h> // TFile

ChargeMisIdRate::ChargeMisIdRate(Era era,
                                 const std::string & lep_mva_wp,
                                 bool wTightCharge,
                                 bool isDEBUG)
  : chargeMisId_(nullptr)
  , isDEBUG_(isDEBUG)
{
  const std::string path = lep_mva_wp == "hh_multilepton" ?
    "hhAnalysis/multilepton/data/ChargeFlipR_e_mva_hh_multilepton_%s_KBFI_2020Oct27_w%sTightCharge.root" :
    "tthAnalysis/HiggsToTauTau/data/ChargeFlipR_e_ttH_%s_KBFI_2020Jan29_w%sTightCharge.root"
  ;
  chargeMisId_ = new lutWrapperTH2(
    inputFiles_,
    Form(path.data(), get_era(era).data(), wTightCharge ? "" : "o"),
    "chargeMisId",
    lut::kXptYabsEta
  );
}

ChargeMisIdRate::~ChargeMisIdRate()
{
  for(auto & kv: inputFiles_)
  {
    delete kv.second;
  }
  delete chargeMisId_;
}

double
ChargeMisIdRate::get(const RecoLepton * const lepton) const
{
  const double chargeMisIdRate = getLeptonType(lepton->pdgId()) == kElectron ?
    chargeMisId_->getSF(lepton->pt(), lepton->absEta()) :
    0.
  ;
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__)
      << "The charge misidentification rate of lepton ("
         "pT = " << lepton->pt() << ", |eta| = " << lepton->absEta() << ", PDG ID = " << lepton->pdgId()
      << ") is " << chargeMisIdRate << '\n';
    ;
  }
  return chargeMisIdRate;
}

double
ChargeMisIdRate::get(const RecoLepton * const lepton_lead,
                     const RecoLepton * const lepton_sublead) const
{
  return get(lepton_lead) + get(lepton_sublead);
}
