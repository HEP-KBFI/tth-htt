#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h

#include <TString.h> // TString, Form
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include <map>

TString stringTmp = "";

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
getType(size_t sizeHTTv2, size_t sizeFatW, size_t sizeResolved);

//template <typename T>
std::vector<size_t>
sort_indexes(const std::vector<double> &v);

std::vector<size_t>
calRank(std::vector<double> & btag_discEnter);

std::vector<double>
getBdiscr(std::vector<const RecoJet*> selJetsIt);

#endif
