#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

RecoJet::RecoJet(Double_t _pt,
                 Double_t _eta,
                 Double_t _phi,
                 Double_t _mass,
                 Double_t _csv,
		 Double_t _btagWeight,
                 Int_t _idx)
  : GenJet(_pt, _eta, _phi, _mass)
  , csv(_csv)
  , btagWeight(_btagWeight)
  , idx(_idx)
{}
