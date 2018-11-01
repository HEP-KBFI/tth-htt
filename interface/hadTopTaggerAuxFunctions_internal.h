#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_internal_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_internal_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include <TString.h> // TString, Form
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <map>

enum {
  kGenMatchedBJet, kGenMatchedWJet1, kGenMatchedWJet2, kGenMatchedTriplet, kGenMatchedFatJet
};

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
                       int TypeTop = 3,
                       const Particle::LorentzVector  recFatJet = Particle::LorentzVector(0., 0., 0., 0.),
		       bool isAnalysisModeGenStudy = false);

//template <typename T>
std::vector<size_t>
sort_indexes(const std::vector<double> &v);

#endif
