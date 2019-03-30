#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauSelectorFakeable::RecoHadTauSelectorFakeable(int era,
                                                       int index,
                                                       bool debug,
                                                       bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{
  switch(era)
  {
    case kEra_2016:
    case kEra_2018:
    case kEra_2017: set("dR03mvaVLoose"); break;
    default: throw cmsException(this) << "Invalid era = " << era;
  }
}

void
RecoHadTauSelectorFakeable::set_selection_flags(const RecoHadTau & hadTau) const
{
  hadTau.set_isFakeable();
}

bool
RecoHadTauSelectorFakeable::operator()(const RecoHadTau & hadTau) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n hadTau: " << hadTau << '\n';
  }
  return RecoHadTauSelectorBase::operator()(hadTau);
}
