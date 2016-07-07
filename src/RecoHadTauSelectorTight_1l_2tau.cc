#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorTight_1l_2tau.h" // RecoHadTauSelectorTight_1l_2tau

#include <cmath> // fabs

RecoHadTauSelectorTight_1l_2tau::RecoHadTauSelectorTight_1l_2tau(int index, bool debug)
  : RecoHadTauSelectorTight(debug)
  , index_(index)
{
  // CV: require very tight WP of MVA-based discriminator trained for dR=0.3 isolation cone
  //     instead of loose WP of cut-based tau isolation discriminator computed within dR=0.5 isolation cone
  min_id_mva_dR03_ = 5;
  min_id_cut_dR05_ = -1000;
  // CV: require leading (subleading) hadronic tau candidates selected in 1l_2tau channel to pass very loose (loose) WP of discriminator against electrons
  if ( index == -1 || index == 0 ) {
    min_antiElectron_ = 1;
  } else if ( index == 1 ) {
    min_antiElectron_ = 2;
  } else assert(0);
  // CV: require hadronic tau candidates selected in 1l_2tau channel to pass loose WP of discriminator against muons 
  min_antiMuon_ = 1;
}
