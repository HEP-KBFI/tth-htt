#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorBase.h" // RecoHadTauSelectorBase, RecoHadTauCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorLoose : public RecoHadTauSelectorBase
{
 public:
  RecoHadTauSelectorLoose(int index = -1, bool debug = false);
  ~RecoHadTauSelectorLoose() {}

  friend class RecoHadTauCollectionSelector<RecoHadTauSelectorLoose>;
};

typedef RecoHadTauCollectionSelector<RecoHadTauSelectorLoose> RecoHadTauCollectionSelectorLoose;

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauCollectionSelectorLoose_h

