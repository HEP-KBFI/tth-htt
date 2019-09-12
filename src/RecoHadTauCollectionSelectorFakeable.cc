#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauSelectorFakeable::RecoHadTauSelectorFakeable(int era,
                                                       int index,
                                                       bool debug,
                                                       bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{
  const TauID tauId = TauID::MVAoldDMdR032017v2;
  std::string tauId_str = "";
  for(const auto & kv: TauID_PyMap)
  {
    if(kv.second == tauId)
    {
      tauId_str = kv.first;
      break;
    }
  }
  assert(! tauId_str.empty());
  set(tauId_str + nominal_fakeable_wp_.at(tauId));
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
