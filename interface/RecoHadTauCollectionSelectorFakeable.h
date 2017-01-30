#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorBase.h" // RecoHadTauSelectorBase, RecoHadTauCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorFakeable : public RecoHadTauSelectorBase
{
 public:
  explicit RecoHadTauSelectorFakeable(int era, int index = -1, bool debug = false);
  ~RecoHadTauSelectorFakeable() {}

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorFakeable>;
 
 protected:
  void set_selection_flags(const RecoHadTau& hadTau) const { hadTau.set_isFakeable(); }
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorFakeable> RecoHadTauCollectionSelectorFakeable;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorFakeable_h

