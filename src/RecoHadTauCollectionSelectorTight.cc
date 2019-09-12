#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauSelectorTight::RecoHadTauSelectorTight(int era,
                                                 int index,
                                                 bool debug,
                                                 bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{}

void
RecoHadTauSelectorTight::set_selection_flags(const RecoHadTau & hadTau) const
{
  hadTau.set_isTight();
}

bool
RecoHadTauSelectorTight::set_if_looser(const std::string & cut)
{
  throw cmsException(this, __func__, __LINE__) << "Invalid call";
}

bool
RecoHadTauSelectorTight::operator()(const RecoHadTau & hadTau) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n hadTau: " << hadTau << '\n';
  }
  return RecoHadTauSelectorBase::operator()(hadTau);
}
