#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

enum {
  kGenMatchedBJet, kGenMatchedWJet1, kGenMatchedWJet2, kGenMatchedTriplet, kGenMatchedFatJet
};

enum {
  kGenTop, kGenAntiTop
};

enum {
  kGenPtTop, kGenPtTopB, kGenPtTopW, kGenPtTopWj1, kGenPtTopWj2,
  kGenEtaTop, kGenEtaTopB, kGenEtaTopW, kGenEtaTopWj1, kGenEtaTopWj2,
  kGenPhiTopB, kGenPhiTopWj1, kGenPhiTopWj2,
  kGenMTopB, kGenMTopWj1, kGenMTopWj2
};

std::map<int, bool>
isGenMatchedJetTriplet(const Particle::LorentzVector & recBJet,
                       const Particle::LorentzVector & recWJet1,
                       const Particle::LorentzVector & recWJet2,
                       const std::vector<GenParticle> & genTopQuarks,
                       const std::vector<GenParticle> & genBJets,
                       const std::vector<GenParticle> & genWBosons,
                       const std::vector<GenParticle> & genWJets,
                       int mode,
                       double & genTopPt,
											 int TypeTop = 3,
											 const Particle::LorentzVector & recFatJet = Particle::LorentzVector(0., 0., 0., 0.));

std::map<int, double>
isGenMatchedJetTripletVar(const std::vector<GenParticle> & genTopQuarks,
                          const std::vector<GenParticle> & genBJets,
                          const std::vector<GenParticle> & genWBosons,
                          const std::vector<GenParticle> & genWJets,
                          int mode);

bool
passWbosonMassVeto(const GenParticle * genWJetFromTop_lead,
                   const GenParticle * genWJetFromTop_sublead,
                   const GenParticle * genWBosonFromTop);

int
getType(size_t sizeHTTv2, size_t sizeFatW, size_t sizeResolved);

//template <typename T>
std::vector<size_t>
sort_indexes(const std::vector<double> &v);

std::vector<size_t>
calRank(std::vector<double> & btag_discEnter);

std::vector<double>
getBdiscr(std::vector<const RecoJet*> selJetsIt);

#endif
