#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

enum {
  kGenMatchedBJet, kGenMatchedWJet1, kGenMatchedWJet2, kGenMatchedTriplet
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
isGenMatchedJetTriplet(const RecoJet & recBJet,
                       const RecoJet & recWJet1,
                       const RecoJet & recWJet2,
                       const std::vector<GenParticle> & genTopQuarks,
                       const std::vector<GenParticle> & genBJets,
                       const std::vector<GenParticle> & genWBosons,
                       const std::vector<GenParticle> & genWJets,
                       int mode,
                       double & genTopPt);

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

#endif
