#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauSelectorLoose

RecoHadTauSelectorLoose::RecoHadTauSelectorLoose(int era, int index, bool debug, bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{ 
  min_pt_ = 20.;
  max_absEta_ = 2.3;
  max_dz_ = 0.2; 
  min_decayModeFinding_ = 1;
  set("dR03mvaVLoose"); 
  min_antiElectron_ = -1000;
  min_antiMuon_ = -1000;
}
