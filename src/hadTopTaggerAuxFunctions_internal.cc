#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <algorithm> // std::sort()
#include <numeric> // iota
#include <map> //

std::map<int, bool>
isGenMatchedJetTriplet(const Particle::LorentzVector & recBJet,
                       const Particle::LorentzVector & recWJet1,
                       const Particle::LorentzVector & recWJet2,
                       const Particle::LorentzVector  genTopQuarks,
                       const Particle::LorentzVector  genBJetFromTop,
                       const Particle::LorentzVector  genWBosons,
                       const Particle::LorentzVector  genWJetFromTop_lead,
                       const Particle::LorentzVector  genWJetFromTop_sublead,
                       int mode,
		       int TypeTop,
		       const Particle::LorentzVector  recFatJet,
		       bool isAnalysisModeGenStudy)
{
  std::map<int, bool> genMatchFlags = {
    { kGenMatchedBJet ,     false },
    { kGenMatchedWJet1 ,    false },
    { kGenMatchedWJet2 ,    false },
    { kGenMatchedTriplet ,  false },
    { kGenMatchedFatJet ,   false },
  };

  double jetGenMatchdRThrsh = 0.4;
  double fatjetGenMatchdRThrsh = 0.4;
  if (TypeTop==1) {fatjetGenMatchdRThrsh = 1.5; jetGenMatchdRThrsh = 0.3;}
  if (TypeTop==2) {fatjetGenMatchdRThrsh = 1.2; jetGenMatchdRThrsh = 0.3;}

  genMatchFlags[kGenMatchedBJet]    = deltaR(recBJet, genBJetFromTop) < jetGenMatchdRThrsh;
  if ( !isAnalysisModeGenStudy) {
    genMatchFlags[kGenMatchedWJet1]   =
      (genWJetFromTop_lead.pt() > 0    && deltaR(recWJet1, genWJetFromTop_lead)    < jetGenMatchdRThrsh) ||
      (genWJetFromTop_sublead.pt() > 0 && deltaR(recWJet1, genWJetFromTop_sublead) < jetGenMatchdRThrsh)
      ;
    genMatchFlags[kGenMatchedWJet2]   =
      (genWJetFromTop_lead.pt() > 0    && deltaR(recWJet2, genWJetFromTop_lead)    < jetGenMatchdRThrsh) ||
      (genWJetFromTop_sublead.pt() > 0 && deltaR(recWJet2, genWJetFromTop_sublead) < jetGenMatchdRThrsh)
      ;
  } else {
    genMatchFlags[kGenMatchedWJet1]   =
      (genWJetFromTop_lead.pt() > 0    && deltaR(recWJet1, genWJetFromTop_lead)    < jetGenMatchdRThrsh)
      ;
    genMatchFlags[kGenMatchedWJet2]   =
      (genWJetFromTop_sublead.pt() > 0 && deltaR(recWJet2, genWJetFromTop_sublead) < jetGenMatchdRThrsh)
      ;
  }


  genMatchFlags[kGenMatchedTriplet] =
    genMatchFlags[kGenMatchedBJet]  &&
    genMatchFlags[kGenMatchedWJet1] &&
    genMatchFlags[kGenMatchedWJet2]
  ;

  if (TypeTop==1) {
    genMatchFlags[kGenMatchedFatJet] =
      (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genTopQuarks) < fatjetGenMatchdRThrsh);
  } else if (TypeTop==2) {
    genMatchFlags[kGenMatchedFatJet] =
      (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genWBosons) < fatjetGenMatchdRThrsh);
  }

  return genMatchFlags;
}

//template <typename T>
std::vector<size_t>
sort_indexes(const std::vector<double> &v) {
  // initialize original index locations
  std::vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
  return idx;
}
