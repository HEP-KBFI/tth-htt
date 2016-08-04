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
  RecoHadTauSelectorTight(int index = -1, bool debug = false);
  ~RecoHadTauSelectorTight() {}

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorTight>;
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorTight> RecoHadTauCollectionSelectorTight;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h

