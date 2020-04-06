#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorBase.h"       // RecoHadTauSelectorBase, RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelector.h" // RecoHadTauCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"         // Era

class RecoHadTauSelectorFakeable
  : public RecoHadTauSelectorBase
{
public:
  explicit
  RecoHadTauSelectorFakeable(Era era,
                             int index = -1,
                             bool debug = false,
                             bool set_selection_flags = true);
  ~RecoHadTauSelectorFakeable() {}

  bool operator()(const RecoHadTau & hadTau) const;

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorFakeable>;

protected:
  void set_selection_flags(const RecoHadTau & hadTau) const;
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorFakeable> RecoHadTauCollectionSelectorFakeable;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h

