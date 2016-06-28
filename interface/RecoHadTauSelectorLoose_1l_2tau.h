#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauSelectorLoose_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauSelectorLoose_11_2tau_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorLoose.h" // RecoHadTauSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t

#include <string>
#include <map>

class RecoHadTauSelectorLoose_1l_2tau : public RecoHadTauSelectorLoose
{
 public:
  RecoHadTauSelectorLoose_1l_2tau(int index = -1, bool debug = false);
  ~RecoHadTauSelectorLoose_1l_2tau() {}

 protected:
  int index_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauSelectorLoose_1l_2tau_h

