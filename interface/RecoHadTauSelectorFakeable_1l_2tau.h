#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorFakeable_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorFakeable_1l_2tau_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorFakeable.h" // RecoHadTauSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorFakeable_1l_2tau : public RecoHadTauSelectorFakeable
{
 public:
  RecoHadTauSelectorFakeable_1l_2tau(int index = -1, bool debug = false);
  ~RecoHadTauSelectorFakeable_1l_2tau() {}

 protected:
  int index_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorFakeable_1l_2tau_h

