#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorBase.h" // RecoHadTauSelectorBase, RecoHadTauCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>
#include <iostream>
#include <iomanip>

class RecoHadTauSelectorTight : public RecoHadTauSelectorBase
{
 public:
  explicit RecoHadTauSelectorTight(int era, int index = -1, bool debug = false, bool set_selection_flags = true);
  ~RecoHadTauSelectorTight() {}

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorTight>;

 protected:
  void set_selection_flags(const RecoHadTau& hadTau) const { hadTau.set_isTight(); }
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorTight> RecoHadTauCollectionSelectorTight;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h

