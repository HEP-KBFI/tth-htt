#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorBase.h" // RecoHadTauSelectorBase, RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelector.h" // RecoHadTauCollectionSelector

class RecoHadTauSelectorTight
  : public RecoHadTauSelectorBase
{
public:
  explicit
  RecoHadTauSelectorTight(int era,
                          int index = -1,
                          bool debug = false,
                          bool set_selection_flags = true);
  ~RecoHadTauSelectorTight() {}

  bool
  set_if_looser(const std::string & cut);

  bool operator()(const RecoHadTau & hadTau) const;

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorTight>;

protected:
  void set_selection_flags(const RecoHadTau & hadTau) const;
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorTight> RecoHadTauCollectionSelectorTight;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorTight_h

