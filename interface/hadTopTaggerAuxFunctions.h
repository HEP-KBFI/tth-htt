#ifndef tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTopTaggerAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

#include <vector>

enum { kGenMatchedBJet, kGenMatchedWJet1, kGenMatchedWJet2, kGenMatchedTriplet };
enum { kGenTop, kGenAntiTop };

std::vector<bool> isGenMatchedJetTriplet(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2,
					 const std::vector<GenParticle>& genTopQuarks,
					 const std::vector<GenParticle>& genBJets, const std::vector<GenParticle>& genWBosons, const std::vector<GenParticle>& genWJets, int mode,
					 double& genTopPt
				 );
#endif
