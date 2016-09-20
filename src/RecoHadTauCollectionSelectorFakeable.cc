#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauSelectorFakeable

#include <cmath> // fabs

RecoHadTauSelectorFakeable::RecoHadTauSelectorFakeable(int index, bool debug)
  : RecoHadTauSelectorBase(index, debug)
{
  min_pt_ = 20.;
  max_absEta_ = 2.3;
  max_dz_ = 0.2;
  min_decayModeFinding_ = 1;
  set("dR03mvaVLoose"); 
  min_antiElectron_ = -1000;
  min_antiMuon_ = -1000;
}
