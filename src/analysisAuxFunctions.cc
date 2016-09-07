#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2)
{
  return (particle1->pt_ > particle2->pt_);
}
