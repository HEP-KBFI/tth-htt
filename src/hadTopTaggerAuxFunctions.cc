#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt

#include <algorithm> // std::sort

std::vector<bool> isGenMatchedJetTriplet(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2,
					 const std::vector<GenParticle>& genTopQuarks,
					 const std::vector<GenParticle>& genBJets, const std::vector<GenParticle>& genWBosons, const std::vector<GenParticle>& genWJets, int mode,
					 double& genTopPt
				 )
{
  std::vector<bool> genMatchFlags(4);
  genMatchFlags[kGenMatchedBJet]    = false;
  genMatchFlags[kGenMatchedWJet1]   = false;
  genMatchFlags[kGenMatchedWJet2]   = false;
  genMatchFlags[kGenMatchedTriplet] = false;

  int pddIdTop, pddIdWBoson, pdgIdBJet;
  if ( mode == kGenTop ) {
    pddIdTop    =  +6;
    pddIdWBoson = +24;
    pdgIdBJet   =  +5;
  } else if ( mode == kGenAntiTop ) {
    pddIdTop    =  -6;
    pddIdWBoson = -24;
    pdgIdBJet   =  -5;
  } else {
    throw cms::Exception("isGenMatchedJetTriplet")
      << "Invalid parameter mode = " << mode << " !!\n";
  }

  const GenParticle* genTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genTopQuarks.begin();
	it != genTopQuarks.end(); ++it ) {
    if ( it->pdgId() == pddIdTop && !genTop ) genTop = &(*it);
  }
	genTopPt = genTop->pt();

  const GenParticle* genWBosonFromTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	it != genWBosons.end(); ++it ) {
    if ( it->pdgId() == pddIdWBoson && !genWBosonFromTop ) genWBosonFromTop = &(*it);
  }
  const GenParticle* genBJetFromTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();it != genBJets.end(); ++it ) {
    if ( it->pdgId() == pdgIdBJet && !genBJetFromTop ) genBJetFromTop = &(*it);
  }

  std::vector<const GenParticle*> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin(); it1 != genWJets.end(); ++it1 ) {
    for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1; it2 != genWJets.end(); ++it2 ) {
      if ( genWBosonFromTop ){
	if ( ((it1->charge() + it2->charge()) - genWBosonFromTop->charge()) < 1.e-2 ) {
	  if ( genWJetsFromTop_mass == -1. ||
	       std::fabs((it1->p4() + it2->p4()).mass() - genWBosonFromTop->mass()) < std::fabs(genWJetsFromTop_mass - genWBosonFromTop->mass()) ) {
	    genWJetsFromTop.clear();
	    genWJetsFromTop.push_back(&(*it1));
	    genWJetsFromTop.push_back(&(*it2));
	    genWJetsFromTop_mass = (it1->p4() + it2->p4()).mass();
	  }
	}
      }
    }
  }

  if ( !(genWJetsFromTop.size() == 2) ) return genMatchFlags;

  const GenParticle* genWJetFromTop_lead = 0;
  const GenParticle* genWJetFromTop_sublead = 0;
  bool passWbosonMassVeto_top = false;
  if ( genWJetsFromTop.size() == 2 && genWBosonFromTop ) {
    std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
    genWJetFromTop_lead = genWJetsFromTop[0];
    genWJetFromTop_sublead = genWJetsFromTop[1];
    if ( std::fabs((genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() - genWBosonFromTop->mass()) < 15.
	 &&  (genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() > 60.
	 && !(genWJetsFromTop_mass == -1.) ) passWbosonMassVeto_top = true;
  }

  genMatchFlags[kGenMatchedBJet]    = deltaR(recBJet.p4(), genBJetFromTop->p4()) < 0.2;
  genMatchFlags[kGenMatchedWJet1]   =
    (genWJetFromTop_lead        && deltaR(recWJet1.p4(), genWJetFromTop_lead->p4())        < 0.2) ||
    (genWJetFromTop_sublead     && deltaR(recWJet1.p4(), genWJetFromTop_sublead->p4())     < 0.2);
  genMatchFlags[kGenMatchedWJet2]   =
    (genWJetFromTop_lead        && deltaR(recWJet2.p4(), genWJetFromTop_lead->p4())        < 0.2) ||
    (genWJetFromTop_sublead     && deltaR(recWJet2.p4(), genWJetFromTop_sublead->p4())     < 0.2);
  genMatchFlags[kGenMatchedTriplet] = genMatchFlags[kGenMatchedBJet] && genMatchFlags[kGenMatchedWJet1] && genMatchFlags[kGenMatchedWJet2] && passWbosonMassVeto_top;

  return genMatchFlags;
}


std::vector<float> isGenMatchedJetTripletVar(const std::vector<GenParticle>& genTopQuarks,
					 const std::vector<GenParticle>& genBJets, const std::vector<GenParticle>& genWBosons, const std::vector<GenParticle>& genWJets, int mode
				 )
{
  std::vector<float> genMatchFlags(16);
	genMatchFlags[kGenPtTop] = -1;
	genMatchFlags[kGenPtTopB] = -1;
	genMatchFlags[kGenPtTopW] = -1;
	genMatchFlags[kGenPtTopWj1] = -1;
	genMatchFlags[kGenPtTopWj2] = -1;
	genMatchFlags[kGenEtaTop] = -100;
	genMatchFlags[kGenEtaTopB] = -100;
	genMatchFlags[kGenEtaTopW] = -100;
	genMatchFlags[kGenEtaTopWj1] = -100;
	genMatchFlags[kGenEtaTopWj2] = -100;
	genMatchFlags[kGenPhiTopB] = -100;
	genMatchFlags[kGenPhiTopWj1] = -100;
	genMatchFlags[kGenPhiTopWj2] = -100;
	genMatchFlags[kGenMTopB] = -100;
	genMatchFlags[kGenMTopWj1] = -100;
	genMatchFlags[kGenMTopWj2] = -100;


  int pddIdTop, pddIdWBoson, pdgIdBJet;
  if ( mode == kGenTop ) {
    pddIdTop    =  +6;
    pddIdWBoson = +24;
    pdgIdBJet   =  +5;
  } else if ( mode == kGenAntiTop ) {
    pddIdTop    =  -6;
    pddIdWBoson = -24;
    pdgIdBJet   =  -5;
  } else {
    throw cms::Exception("isGenMatchedJetTriplet")
      << "Invalid parameter mode = " << mode << " !!\n";
  }
  //std::cout << "top" << std::endl;
  const GenParticle* genTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genTopQuarks.begin();
	it != genTopQuarks.end(); ++it ) {
    if ( it->pdgId() == pddIdTop && !genTop ) {
		genTop = &(*it);
		genMatchFlags[kGenPtTop] = genTop->pt();
		genMatchFlags[kGenEtaTop] = genTop->eta();
	}
  }
  //std::cout << "W" << std::endl;
  const GenParticle* genWBosonFromTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	it != genWBosons.end(); ++it ) {
    if ( it->pdgId() == pddIdWBoson && !genWBosonFromTop ) {
		genWBosonFromTop = &(*it);
		genMatchFlags[kGenPtTopW] = genWBosonFromTop->pt();
		genMatchFlags[kGenEtaTopW] = genWBosonFromTop->eta();
	}
  }
  //std::cout << "b" << std::endl;
  const GenParticle* genBJetFromTop = 0;
  for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();it != genBJets.end(); ++it ) {
    if ( it->pdgId() == pdgIdBJet && !genBJetFromTop ) {
		genBJetFromTop = &(*it);
		genMatchFlags[kGenPtTopB] = genBJetFromTop->pt();
		genMatchFlags[kGenEtaTopB] = genBJetFromTop->eta();
		genMatchFlags[kGenPhiTopB] = genBJetFromTop->phi();
		genMatchFlags[kGenMTopB] = genBJetFromTop->mass();
	}
  }
  //std::cout << "Wj" << std::endl;
  std::vector<const GenParticle*> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin(); it1 != genWJets.end(); ++it1 ) {
    for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1; it2 != genWJets.end(); ++it2 ) {
      if ( genWBosonFromTop ){
	if ( ((it1->charge() + it2->charge()) - genWBosonFromTop->charge()) < 1.e-2 ) {
	  if ( genWJetsFromTop_mass == -1. ||
	       std::fabs((it1->p4() + it2->p4()).mass() - genWBosonFromTop->mass()) < std::fabs(genWJetsFromTop_mass - genWBosonFromTop->mass()) ) {
	    genWJetsFromTop.clear();
	    genWJetsFromTop.push_back(&(*it1));
	    genWJetsFromTop.push_back(&(*it2));
	    genWJetsFromTop_mass = (it1->p4() + it2->p4()).mass();
	  }
	}
      }
    }
  }

  if ( !(genWJetsFromTop.size() == 2) ) return genMatchFlags;
  //std::cout << "Wjets ordering" << std::endl;
  const GenParticle* genWJetFromTop_lead = 0;
  const GenParticle* genWJetFromTop_sublead = 0;
  if ( genWJetsFromTop.size() == 2 && genWBosonFromTop ) {
    std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
    genWJetFromTop_lead = genWJetsFromTop[0];
    genWJetFromTop_sublead = genWJetsFromTop[1];
    if ( std::fabs((genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() - genWBosonFromTop->mass()) < 15.
	 &&  (genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() > 60.
	 && !(genWJetsFromTop_mass == -1.) ) {

	 genMatchFlags[kGenPtTopWj1] = genWJetFromTop_lead->pt();
	 genMatchFlags[kGenPtTopWj2] = genWJetFromTop_sublead->pt();
	 genMatchFlags[kGenEtaTopWj1] = genWJetFromTop_lead->eta();
	 genMatchFlags[kGenEtaTopWj2] = genWJetFromTop_sublead->eta();
	 genMatchFlags[kGenPhiTopWj1] = genWJetFromTop_lead->phi();
	 genMatchFlags[kGenPhiTopWj2] = genWJetFromTop_sublead->phi();
	 genMatchFlags[kGenMTopWj1] = genWJetFromTop_lead->mass();
	 genMatchFlags[kGenMTopWj2] = genWJetFromTop_sublead->mass();
   }
  }

  return genMatchFlags;
}
