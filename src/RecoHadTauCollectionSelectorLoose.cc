#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauSelectorLoose

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauSelectorLoose::RecoHadTauSelectorLoose(int era,
                                                 int index,
                                                 bool debug,
                                                 bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{ 
  min_pt_                 = 20.;
  max_absEta_             = 2.3;
  max_dz_                 = 0.2;
  apply_decayModeFinding_ = true;
  min_antiElectron_       = -1000;
  min_antiMuon_           = -1000;
  switch(era)
  {
    case kEra_2016: set("dR03mvaLoose"); break; // was dR03mvaVLoose, i.e. one step lower than what fakeable selector required
    case kEra_2017: set("dR03mvaVLoose"); break;
    case kEra_2018: throw cmsException(this) << "Implement me!";
    default: throw cmsException(this) << "Invalid era = " << era;
  }
}

void
RecoHadTauSelectorLoose::set_selection_flags(const RecoHadTau & hadTau) const
{
  hadTau.set_isLoose();
}

bool
RecoHadTauSelectorLoose::operator()(const RecoHadTau & hadTau) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n hadTau: " << hadTau << '\n';
  }
  return RecoHadTauSelectorBase::operator()(hadTau);
}
