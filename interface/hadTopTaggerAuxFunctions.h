#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include <map>

// forward declarations
class RecoJet;

std::map<int, Particle::LorentzVector>
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
getType(std::size_t sizeHTTv2,
        std::size_t sizeFatW,
        std::size_t sizeResolved);

std::vector<size_t>
sort_indexes(const std::vector<double> & v);

std::vector<std::size_t>
calRank(std::vector<double> & btag_discEnter);

std::vector<double>
getBdiscr(const std::vector<const RecoJet *> & selJetsIt);

#endif
