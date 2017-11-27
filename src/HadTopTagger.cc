
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/XGBReader.h" // XGBReader
#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "TLorentzVector.h"
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

HadTopTagger::HadTopTagger(const std::string& mvaFileNameWithKinFit,const std::string& mvaFileNameNoKinFit)
  : kinFit_(0),
    mva_(0),
    mvaOutput_(-1.)
{
  kinFit_ = new HadTopKinFit();
  mvaFileNameWithKinFit_=  mvaFileNameWithKinFit.c_str();
  mvaFileNameNoKinFit_= mvaFileNameNoKinFit.c_str();
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_;
}


std::vector<double> HadTopTagger::operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
{
  std::vector<double> result;
  // order IS important - I will fix that
  // ['CSV_b', 'qg_Wj2', 'pT_bWj1Wj2', 'm_Wj1Wj2', 'nllKinFit', 'pT_b_o_kinFit_pT_b', 'pT_Wj2']
  char* pklpath=(char*) mvaFileNameWithKinFit_; //"HadTopTagger_sklearnV0o17o1_HypOpt/all_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_1000_deph_3_lr_0o01_CSV_sort_withKinFit.pkl";
  mvaInputsWithKinFit_["CSV_b"]                  = recBJet.BtagCSV();
  mvaInputsWithKinFit_["qg_Wj2"]                 = recWJet2.QGDiscr();
  Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  mvaInputsWithKinFit_["pT_bWj1Wj2"]             = p4_bWj1Wj2.pt();
  Particle::LorentzVector p4_Wj1Wj2 = recWJet1.p4() + recWJet2.p4();
  mvaInputsWithKinFit_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputsWithKinFit_["nllKinFit"]              = kinFit_->nll();
  mvaInputsWithKinFit_["pT_b_o_kinFit_pT_b"]     = recBJet.pt()/kinFit_->fittedBJet().pt();
  mvaInputsWithKinFit_["pT_Wj2"]                 = recWJet2.pt();
  double mvaOutputWithKinFit_= XGBReader(mvaInputsWithKinFit_ , pklpath );
  result.push_back(mvaOutputWithKinFit_);
  ///////////////////////////////////////////////////////////////
  // order IS important  - I will fix that
  // ['CSV_b', 'qg_Wj2', 'qg_Wj1', 'm_bWj1Wj2', 'pT_bWj1Wj2', 'm_Wj1Wj2', 'pT_Wj2']
  char* pklpathNoKinFit=(char*) mvaFileNameNoKinFit_; // "HadTopTagger_sklearnV0o17o1_HypOpt/all_HadTopTagger_sklearnV0o17o1_HypOpt_XGB_ntrees_1000_deph_3_lr_0o01_CSV_sort.pkl";
  mvaInputsNoKinFit_["CSV_b"]                  = recBJet.BtagCSV();
  mvaInputsNoKinFit_["qg_Wj2"]                 = recWJet2.QGDiscr();
  mvaInputsNoKinFit_["qg_Wj1"]                 = recWJet1.QGDiscr();
  mvaInputsNoKinFit_["m_bWj1Wj2"]             = p4_bWj1Wj2.mass();
  mvaInputsNoKinFit_["pT_bWj1Wj2"]             = p4_bWj1Wj2.pt();
  mvaInputsNoKinFit_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputsNoKinFit_["pT_Wj2"]                 = recWJet2.pt();
  double mvaOutputNoKinFit_= XGBReader(mvaInputsNoKinFit_ , pklpathNoKinFit );
  result.push_back(mvaOutputNoKinFit_);
  return result;
}

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const Particle* particle1, const Particle* particle2);

bool HadTopTagger::isTruth3Jet(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2,
					//std::vector<const RecoJet*> selJets,
					std::vector<GenParticle> genTopQuarks, std::vector<GenParticle> genBJets, std::vector<GenParticle> genWBosons,
					std::vector<GenParticle> genWJets , std::vector<bool>& truth_)
{
	const GenParticle* genTopQuark = 0;
  const GenParticle* genAntiTopQuark = 0;
	for ( std::vector<GenParticle>::const_iterator it = genTopQuarks.begin();
	  it != genTopQuarks.end(); ++it ) {
      if ( it->pdgId() == +6 && !genTopQuark     ) genTopQuark = &(*it);
      if ( it->pdgId() == -6 && !genAntiTopQuark ) genAntiTopQuark = &(*it);
    }
	const GenParticle* genWBosonFromTop = 0;
    const GenParticle* genWBosonFromAntiTop = 0;
    for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	  it != genWBosons.end(); ++it ) {
      if ( it->pdgId() == +24 && !genWBosonFromTop     ) genWBosonFromTop = &(*it);
      if ( it->pdgId() == -24 && !genWBosonFromAntiTop ) genWBosonFromAntiTop = &(*it);
	}
	const GenParticle* genBJetFromTop = 0;
    const GenParticle* genBJetFromAntiTop = 0;
    for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();it != genBJets.end(); ++it ) {
      if ( it->pdgId() == +5 && !genBJetFromTop     ) genBJetFromTop = &(*it);
      if ( it->pdgId() == -5 && !genBJetFromAntiTop ) genBJetFromAntiTop = &(*it);
    }
	////////////////////////////////////////////////////////////////////////
    std::vector<const GenParticle*> genWJetsFromTop;
    double genWJetsFromTop_mass = -1.;
    std::vector<const GenParticle*> genWJetsFromAntiTop;
    double genWJetsFromAntiTop_mass = -1.;

    for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin(); it1 != genWJets.end(); ++it1 ) {
		for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1; it2 != genWJets.end(); ++it2 ) {
      if (genWBosonFromTop){
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
      if (genWBosonFromAntiTop) {
			if ( ((it1->charge() + it2->charge()) - genWBosonFromAntiTop->charge()) < 1.e-2 ) {
			  if ( genWJetsFromAntiTop_mass == -1. ||
				   std::fabs((it1->p4() + it2->p4()).mass() - genWBosonFromAntiTop->mass()) < std::fabs(genWJetsFromAntiTop_mass - genWBosonFromAntiTop->mass()) ) {
				genWJetsFromAntiTop.clear();
				genWJetsFromAntiTop.push_back(&(*it1));
				genWJetsFromAntiTop.push_back(&(*it2));
				genWJetsFromAntiTop_mass = (it1->p4() + it2->p4()).mass();
				}
			}
    }
		}
    }
	/////////////////////////////////////////////////////////
    if ( !(genWJetsFromTop.size() == 2 || genWJetsFromAntiTop.size() == 2) and  genWJets.size() < 2  ) return 0;
    const GenParticle* genWJetFromTop_lead = 0;
    const GenParticle* genWJetFromTop_sublead = 0;
    bool passWbosonMassVeto_top = false;
    if ( genWJetsFromTop.size() == 2 && genWBosonFromTop) {
      std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
      genWJetFromTop_lead = genWJetsFromTop[0];
      genWJetFromTop_sublead = genWJetsFromTop[1];
      if ( std::fabs((genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() - genWBosonFromTop->mass()) < 15.
            &&  (genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() > 60.
            && !(genWJetsFromTop_mass == -1.) ) passWbosonMassVeto_top = true;
    }
    const GenParticle* genWJetFromAntiTop_lead = 0;
    const GenParticle* genWJetFromAntiTop_sublead = 0;
    bool passWbosonMassVeto_AntiTop = false;
    if ( genWJetsFromAntiTop.size() == 2 && genWBosonFromAntiTop) {
      std::sort(genWJetsFromAntiTop.begin(), genWJetsFromAntiTop.end(), isHigherPt);
      genWJetFromAntiTop_lead = genWJetsFromAntiTop[0];
      genWJetFromAntiTop_sublead = genWJetsFromAntiTop[1];
      if ( std::fabs((genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4()).mass() - genWBosonFromAntiTop->mass()) < 15.
            &&  (genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4()).mass() > 60.
            && !(genWJetsFromAntiTop_mass == -1.) ) passWbosonMassVeto_AntiTop = true;
    }
	bool selBJet_isFromTop = deltaR(recBJet.p4(), genBJetFromTop->p4()) < 0.2;
	bool selBJet_isFromAntiTop = deltaR(recBJet.p4(), genBJetFromAntiTop->p4()) < 0.2;

	bool selWJet1_isFromTop =
		(genWJetFromTop_lead        && deltaR(recWJet1.p4(), genWJetFromTop_lead->p4())        < 0.2) ||
		(genWJetFromTop_sublead     && deltaR(recWJet1.p4(), genWJetFromTop_sublead->p4())     < 0.2);
	bool selWJet1_isFromAntiTop =
		(genWJetFromAntiTop_lead    && deltaR(recWJet1.p4(), genWJetFromAntiTop_lead->p4())    < 0.2) ||
		(genWJetFromAntiTop_sublead && deltaR(recWJet1.p4(), genWJetFromAntiTop_sublead->p4()) < 0.2);
	bool selWJet2_isFromTop =
		(genWJetFromTop_lead        && deltaR(recWJet2.p4(), genWJetFromTop_lead->p4())        < 0.2) ||
		(genWJetFromTop_sublead     && deltaR(recWJet2.p4(), genWJetFromTop_sublead->p4())     < 0.2);
	bool selWJet2_isFromAntiTop =
		(genWJetFromAntiTop_lead    && deltaR(recWJet2.p4(), genWJetFromAntiTop_lead->p4())    < 0.2) ||
		(genWJetFromAntiTop_sublead && deltaR(recWJet2.p4(), genWJetFromAntiTop_sublead->p4()) < 0.2);
    truth_[0]=(selBJet_isFromAntiTop);
  	truth_[1]=(selWJet1_isFromAntiTop && passWbosonMassVeto_AntiTop );
  	truth_[2]=(selWJet2_isFromAntiTop && passWbosonMassVeto_AntiTop );

  	truth_[3]=(selBJet_isFromTop );
  	truth_[4]=(selWJet1_isFromTop && passWbosonMassVeto_top );
  	truth_[5]=(selWJet2_isFromTop && passWbosonMassVeto_top );

	bool ttruthAnti= (selBJet_isFromAntiTop == 1) && \
					 (selWJet1_isFromAntiTop == 1) && \
					 (selWJet2_isFromAntiTop == 1) &&
					 passWbosonMassVeto_AntiTop;
	bool ttruth    = (selBJet_isFromTop == 1) && \
					 (selWJet1_isFromTop == 1) && \
					 (selWJet2_isFromTop == 1) &&
					 passWbosonMassVeto_top;

    truth_[6]=(ttruthAnti);
    truth_[7]=(ttruth);

	return 1;
}

std::vector<Particle::LorentzVector> HadTopTagger::Particles(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
{
  std::vector<Particle::LorentzVector> particles;
  Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  Particle::LorentzVector p4_Wj1Wj2 = recWJet1.p4() + recWJet2.p4();
  particles.push_back(p4_bWj1Wj2);
  particles.push_back(recBJet.p4());
  particles.push_back(p4_Wj1Wj2);
  return particles;
}

const std::vector<std::string>& HadTopTagger::mvaInputVariables() const { return mvaInputVariables_; }

const std::map<std::string, double>& HadTopTagger::mvaInputs() const { return mvaInputsWithKinFit_; }

const HadTopKinFit* HadTopTagger::kinFit() const { return kinFit_; }
