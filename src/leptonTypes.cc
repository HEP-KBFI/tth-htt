#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"

#include <stdlib.h> // abs
#include <assert.h> // assert

int getLeptonType(int pdgId)
{
  int leptonType = -1;
  int abs_pdgId = abs(pdgId);
  if      ( abs_pdgId == 11 ) leptonType = kElectron;
  else if ( abs_pdgId == 13 ) leptonType = kMuon;
  else assert(0);
  return leptonType;
}
