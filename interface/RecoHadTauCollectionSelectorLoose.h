#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorBase.h" // RecoHadTauSelectorBase, RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelector.h" // RecoHadTauCollectionSelector

class RecoHadTauSelectorLoose
  : public RecoHadTauSelectorBase
{
public:
  explicit
  RecoHadTauSelectorLoose(int era,
                          int index = -1,
                          bool debug = false,
                          bool set_selection_flags = true);
  ~RecoHadTauSelectorLoose() {}

  bool
  set_if_looser(const std::string & cut);

  void
  set(const std::string & cut);

  bool operator()(const RecoHadTau & hadTau) const;

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorLoose>;

protected:
  void set_selection_flags(const RecoHadTau & hadTau) const;
  void reset_cuts();
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorLoose> RecoHadTauCollectionSelectorLoose;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h

