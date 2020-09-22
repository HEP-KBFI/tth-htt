#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"

#include <cmath> // std::abs()
#include <cassert> // assert()

#include <iostream>

int
getLeptonType(int pdgId)
{
  const int abs_pdgId = std::abs(pdgId);
  switch(abs_pdgId)
  {
    case 11: return kElectron;
    case 13: return kMuon;
    default: assert(0);
  }
}
