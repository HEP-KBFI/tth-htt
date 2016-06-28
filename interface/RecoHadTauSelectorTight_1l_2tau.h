#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_1l_2tau_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight.h" // RecoHadTauSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorTight_1l_2tau : public RecoHadTauSelectorTight
{
 public:
  RecoHadTauSelectorTight_1l_2tau(int index = -1, bool debug = false);
  ~RecoHadTauSelectorTight_1l_2tau() {}

 protected:
  int index_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorTight_1l_2tau_h

