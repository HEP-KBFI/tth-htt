#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <algorithm> // std::sort()
#include <numeric> // iota

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
                       double & genTopEta,
		       int TypeTop,
		       const Particle::LorentzVector & recFatJet)
{
  std::map<int, bool> genMatchFlags = {
    { kGenMatchedBJet ,     false },
    { kGenMatchedWJet1 ,    false },
    { kGenMatchedWJet2 ,    false },
    { kGenMatchedTriplet ,  false },
		{ kGenMatchedFatJet ,   false },
  };

  int pddIdTop, pddIdWBoson, pdgIdBJet;
  if(mode == kGenTop)
  {
    pddIdTop    =  +6;
    pddIdWBoson = +24;
    pdgIdBJet   =  +5;
  }
  else if(mode == kGenAntiTop)
  {
    pddIdTop    =  -6;
    pddIdWBoson = -24;
    pdgIdBJet   =  -5;
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid parameter mode = " << mode;
  }

  const GenParticle * genTop = nullptr;
  for(const GenParticle & genTopQuark: genTopQuarks)
  {
    if(genTopQuark.pdgId() == pddIdTop && ! genTop)
    {
      genTop = &genTopQuark;
    }
  }
  genTopPt = genTop->pt();
  genTopEta = genTop->eta();

  const GenParticle * genWBosonFromTop = nullptr;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.pdgId() == pddIdWBoson && ! genWBosonFromTop)
    {
      genWBosonFromTop = &genWBoson;
    }
  }

  const GenParticle * genBJetFromTop = nullptr;
  for(const GenParticle & genBJet: genBJets)
  {
    if(genBJet.pdgId() == pdgIdBJet && ! genBJetFromTop)
    {
      genBJetFromTop = &genBJet;
    }
  }

  std::vector<const GenParticle *> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for(auto it1 = genWJets.cbegin(); it1 != genWJets.cend(); ++it1)
  {
    const GenParticle * genWJet1 = &(*it1);
    for(auto it2 = it1 + 1; it2 != genWJets.cend(); ++it2)
    {
      const GenParticle * genWJet2 = &(*it2);
      if(genWBosonFromTop)
      {
        if(((genWJet1->charge() + genWJet2->charge()) - genWBosonFromTop->charge()) < 1.e-2)
        {
          const double genWJetsFromTop_massCurrent = (genWJet1->p4() + genWJet2->p4()).mass();
          const double diff_massCurrent = std::fabs(genWJetsFromTop_massCurrent - genWBosonFromTop->mass());
          const double diff_mass        = std::fabs(genWJetsFromTop_mass        - genWBosonFromTop->mass());
          if(genWJetsFromTop_mass == -1. || diff_massCurrent < diff_mass)
          {
            genWJetsFromTop = { genWJet1, genWJet2 };
            genWJetsFromTop_mass = genWJetsFromTop_massCurrent;
          }
        }
      }
    }
  }

  if(genWJetsFromTop.size() != 2)
  {
    return genMatchFlags;
  }

  std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
  const GenParticle * genWJetFromTop_lead = genWJetsFromTop[0];
  const GenParticle * genWJetFromTop_sublead = genWJetsFromTop[1];

  const bool passWbosonMassVeto_top = passWbosonMassVeto(
    genWJetFromTop_lead, genWJetFromTop_sublead, genWBosonFromTop
  );

	double jetGenMatchdRThrsh = 0.2;
	double fatjetGenMatchdRThrsh = 0.2;
  if (TypeTop==1) fatjetGenMatchdRThrsh = 0.75;
  if (TypeTop==2) fatjetGenMatchdRThrsh = 0.6;
	if (TypeTop==1 || TypeTop==2) {
		jetGenMatchdRThrsh = 0.1;
		fatjetGenMatchdRThrsh = 0.1;
	}


  genMatchFlags[kGenMatchedBJet]    = deltaR(recBJet, genBJetFromTop->p4()) < jetGenMatchdRThrsh;
  genMatchFlags[kGenMatchedWJet1]   =
    (genWJetFromTop_lead    && deltaR(recWJet1, genWJetFromTop_lead->p4())    < jetGenMatchdRThrsh) ||
    (genWJetFromTop_sublead && deltaR(recWJet1, genWJetFromTop_sublead->p4()) < jetGenMatchdRThrsh)
  ;
  genMatchFlags[kGenMatchedWJet2]   =
    (genWJetFromTop_lead    && deltaR(recWJet2, genWJetFromTop_lead->p4())    < jetGenMatchdRThrsh) ||
    (genWJetFromTop_sublead && deltaR(recWJet2, genWJetFromTop_sublead->p4()) < jetGenMatchdRThrsh)
  ;
  genMatchFlags[kGenMatchedTriplet] =
    genMatchFlags[kGenMatchedBJet]  &&
    genMatchFlags[kGenMatchedWJet1] &&
    genMatchFlags[kGenMatchedWJet2] &&
    passWbosonMassVeto_top
  ;

	if (TypeTop==1) {
		genMatchFlags[kGenMatchedFatJet] =
    (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genTop->p4()) < fatjetGenMatchdRThrsh);
	} else if (TypeTop==2) {
		genMatchFlags[kGenMatchedFatJet] =
    (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genWBosonFromTop->p4()) < fatjetGenMatchdRThrsh);
	}

  return genMatchFlags;
}


std::map<int, Particle::LorentzVector>
isGenMatchedJetTripletVar(const std::vector<GenParticle> & genTopQuarks,
                          const std::vector<GenParticle> & genBJets,
                          const std::vector<GenParticle> & genWBosons,
                          const std::vector<GenParticle> & genWJets,
                          int mode)
{
  std::map<int, Particle::LorentzVector> genMatchValues = {
    { kGenTop,       dumbIni },
    { kGenTopB,      dumbIni },
    { kGenTopW,      dumbIni },
    { kGenTopWj1,      dumbIni },
    { kGenTopWj2,      dumbIni }
  };

  int pddIdTop, pddIdWBoson, pdgIdBJet;
  if(mode == kGenTop)
  {
    pddIdTop    =  +6;
    pddIdWBoson = +24;
    pdgIdBJet   =  +5;
  }
  else if(mode == kGenAntiTop)
  {
    pddIdTop    =  -6;
    pddIdWBoson = -24;
    pdgIdBJet   =  -5;
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid parameter mode = " << mode;
  }

  const GenParticle * genTop = 0;
  for(const GenParticle & genTopQuark: genTopQuarks)
  {
    if(genTopQuark.pdgId() == pddIdTop && ! genTop)
    {
      genTop = &genTopQuark;
      genMatchValues[kGenTop].SetPxPyPzE(genTopQuark.p4().x(), genTopQuark.p4().y(), genTopQuark.p4().z(), genTopQuark.p4().energy());
    }
  }

  const GenParticle * genWBosonFromTop = nullptr;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.pdgId() == pddIdWBoson && ! genWBosonFromTop)
    {
      genWBosonFromTop = &genWBoson;
      genMatchValues[kGenTopW].SetPxPyPzE(genWBoson.p4().x(), genWBoson.p4().y(), genWBoson.p4().z(), genWBoson.p4().energy());
    }
  }

  const GenParticle * genBJetFromTop = nullptr;
  for(const GenParticle & genBJet: genBJets)
  {
    if(genBJet.pdgId() == pdgIdBJet && ! genBJetFromTop )
    {
      genBJetFromTop = &genBJet;
      genMatchValues[kGenTopB].SetPxPyPzE(genBJet.p4().x(), genBJet.p4().y(), genBJet.p4().z(), genBJet.p4().energy());
    }
  }

  std::vector<const GenParticle *> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for(auto it1 = genWJets.cbegin(); it1 != genWJets.cend(); ++it1)
  {
    const GenParticle * genWJet1 = &(*it1);
    for(auto it2 = it1 + 1; it2 != genWJets.cend(); ++it2)
    {
      const GenParticle * genWJet2 = &(*it2);
      if(genWBosonFromTop)
      {
        if(((genWJet1->charge() + genWJet2->charge()) - genWBosonFromTop->charge()) < 1.e-2)
        {
          const double genWJetsFromTop_massCurrent = (genWJet1->p4() + genWJet2->p4()).mass();
          const double diff_massCurrent = std::fabs(genWJetsFromTop_massCurrent - genWBosonFromTop->mass());
          const double diff_mass        = std::fabs(genWJetsFromTop_mass        - genWBosonFromTop->mass());
          if(genWJetsFromTop_mass == -1. || diff_massCurrent < diff_mass)
          {
            genWJetsFromTop = { genWJet1, genWJet2 };
            genWJetsFromTop_mass = genWJetsFromTop_massCurrent;
          }
        }
      }
    }
  }

  if(genWJetsFromTop.size() != 2)
  {
    return genMatchValues;
  }

  std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
  const GenParticle * genWJetFromTop_lead = genWJetsFromTop[0];
  const GenParticle * genWJetFromTop_sublead = genWJetsFromTop[1];

  const bool passWbosonMassVeto_top = passWbosonMassVeto(
    genWJetFromTop_lead, genWJetFromTop_sublead, genWBosonFromTop
  );
  if(passWbosonMassVeto_top)
  {
    genMatchValues[kGenTopWj1].SetPxPyPzE(genWJetFromTop_lead->p4().x(), genWJetFromTop_lead->p4().y(), genWJetFromTop_lead->p4().z(), genWJetFromTop_lead->p4().energy());
    genMatchValues[kGenTopWj2].SetPxPyPzE(genWJetFromTop_sublead->p4().x(), genWJetFromTop_sublead->p4().y(), genWJetFromTop_sublead->p4().z(), genWJetFromTop_sublead->p4().energy());
  }
  return genMatchValues;
}

bool
passWbosonMassVeto(const GenParticle * genWJetFromTop_lead,
                   const GenParticle * genWJetFromTop_sublead,
                   const GenParticle * genWBosonFromTop)
{
  const double genWJetFromTop_mass = (genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass();
  return std::fabs(genWJetFromTop_mass - genWBosonFromTop->mass()) < 15. && genWJetFromTop_mass > 60.;
}

int
getType(size_t sizeHTTv2, size_t sizeFatW, size_t sizeResolved){
  int typeTop = -1;
  if (sizeHTTv2 > 0) typeTop = 1;
  else if (sizeFatW >0) typeTop = 2;
  else if (sizeResolved >0) typeTop = 3;
  return typeTop;
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

std::vector<double>
getBdiscr(std::vector<const RecoJet*> selJetsIt){
  std::vector<double> btag_disc;
  for ( std::vector<const RecoJet*>::const_iterator jetIterB = selJetsIt.begin();
  jetIterB != selJetsIt.end(); ++jetIterB ) {
    btag_disc.push_back((*jetIterB)->BtagCSV());
  }
  return btag_disc;
}

std::vector<size_t>
calRank( std::vector<double> & btag_disc ) {
    std::vector<size_t> result(btag_disc.size(),0);
    //sorted index
    std::vector<size_t> indx(btag_disc.size());
    iota(indx.begin(),indx.end(),0);
    sort(indx.begin(),indx.end(),[&btag_disc](int i1, int i2){return btag_disc[i1]>btag_disc[i2];});
    //return ranking
    for(size_t iter=0;iter<btag_disc.size();++iter) result[indx[iter]]=iter+1;
    //std::cout<<"btag discriminant  ";
    //for (auto i: btag_disc) std::cout << i << " ";
    //std::cout<<std::endl;
    return result;
}



std::map<int, bool>
isGenMatchedJetTriplet_Method2(const Particle::LorentzVector & recBJet,
			       const Particle::LorentzVector & recWJet1,
			       const Particle::LorentzVector & recWJet2,
			       const std::vector<GenParticle> & genTopQuarks,
			       const std::vector<GenParticle> & genBJets,
			       const std::vector<GenParticle> & genWBosons,
			       const std::vector<GenParticle> & genWJets,
			       int mode,
			       double & genTopPt,
			       int TypeTop,
			       const Particle::LorentzVector & recFatJet,
			       TString & sPrint)
{
  std::map<int, bool> genMatchFlags = {
    { kGenMatchedBJet ,     false },
    { kGenMatchedWJet1 ,    false },
    { kGenMatchedWJet2 ,    false },
    { kGenMatchedTriplet ,  false },
		{ kGenMatchedFatJet ,   false },
  };

  int pddIdTop, pddIdWBoson, pdgIdBJet;
  if(mode == kGenTop)
  {
    pddIdTop    =  +6;
    pddIdWBoson = +24;
    pdgIdBJet   =  +5;
  }
  else if(mode == kGenAntiTop)
  {
    pddIdTop    =  -6;
    pddIdWBoson = -24;
    pdgIdBJet   =  -5;
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid parameter mode = " << mode;
  }

    
  const GenParticle * genTop = nullptr;
  for(const GenParticle & genTopQuark: genTopQuarks) {
    if(genTopQuark.pdgId() == pddIdTop && ! genTop) {
      genTop = &genTopQuark;
    }
    //if (genTopQuark.pdgId() == pddIdTop) nParticles++;
  }
  genTopPt = genTop->pt();
  
  
  std::vector<const GenParticle*> genBJetsFromTop;
  for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();
	it != genBJets.end(); ++it ) {
    if ( it->pdgId() == pdgIdBJet ) genBJetsFromTop.push_back(&(*it));
  }
  
  std::vector<const GenParticle*> genWBosonsFromTop;
  for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	it != genWBosons.end(); ++it ) {
    if ( it->pdgId() == pddIdWBoson ) genWBosonsFromTop.push_back(&(*it));
  }
  
  const GenParticle* genBJetFromTop = 0;
  const GenParticle* genWBosonFromTop = 0;
  double genBJet_plus_WBosonMassFromTop = -1.;
  for ( std::vector<const GenParticle*>::const_iterator genBJet = genBJetsFromTop.begin();
	genBJet != genBJetsFromTop.end(); ++genBJet ) {
    for ( std::vector<const GenParticle*>::const_iterator genWBoson = genWBosonsFromTop.begin();
	  genWBoson != genWBosonsFromTop.end(); ++genWBoson ) {
      double genBJet_plus_WBosonMass = ((*genBJet)->p4() + (*genWBoson)->p4()).mass();
      if ( std::fabs(genBJet_plus_WBosonMass - genTop->mass()) < std::fabs(genBJet_plus_WBosonMassFromTop - genTop->mass())  ||
	   !(genBJetFromTop && genWBosonFromTop) ) {
	genBJetFromTop = (*genBJet);
	genWBosonFromTop = (*genWBoson);
	genBJet_plus_WBosonMassFromTop = genBJet_plus_WBosonMass;
      }
    }
  }
  
  
  std::vector<const GenParticle*> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin(); it1 != genWJets.end(); ++it1 ) {
    for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1;
	  it2 != genWJets.end(); ++it2 ) {
      double genDijetMass = (it1->p4() + it2->p4()).mass();
      // CV: Matching the generator-level charge of the two quarks to the generator-level charge of the W boson is a bit cumbersome,
      //     because charge of Particles is stored as integer in Ntuple,
      //     so only sign of charge is well defined for quarks (fractional charge is not supported!)
      //
      //     For W->jj decays, the sign of the charge of both jets is equal to the sign of the charge of the W boson,
      //     i.e. the W boson decays either via
      //       W+ -> up-type-quark (q = +2/3) + anti-down-type-quark (+1/3)
      //     or via
      //       W- -> anti-up-type-quark (q = -2/3) + down-type-quark (-1/3)
      if ( boost::math::sign(it1->charge()) == boost::math::sign(genWBosonFromTop->charge()) &&
	   boost::math::sign(it2->charge()) == boost::math::sign(genWBosonFromTop->charge()) ) {
	if ( std::fabs(genDijetMass - genWBosonFromTop->mass()) < 15. &&
	     (genWJetsFromTop_mass == -1. ||
	      std::fabs(genDijetMass - genWBosonFromTop->mass()) < std::fabs(genWJetsFromTop_mass - genWBosonFromTop->mass())) ) {
	  genWJetsFromTop.clear();
	  genWJetsFromTop.push_back(&(*it1));
	  genWJetsFromTop.push_back(&(*it2));
	  genWJetsFromTop_mass = genDijetMass;
	}
      }
    }
  }
  
  /*
  int nParticles = 0;
  const GenParticle * genTop = nullptr;
  for(const GenParticle & genTopQuark: genTopQuarks)
    {
    if(genTopQuark.pdgId() == pddIdTop && ! genTop)
    {
      genTop = &genTopQuark;
    }
    if (genTopQuark.pdgId() == pddIdTop) nParticles++;
  }
  genTopPt = genTop->pt();
  sPrint += Form("ngenTopQuark:%i \n",nParticles);

  nParticles = 0;
  const GenParticle * genWBosonFromTop = nullptr;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.pdgId() == pddIdWBoson && ! genWBosonFromTop)
    {
      genWBosonFromTop = &genWBoson;
    }
    if (genWBoson.pdgId() == pddIdWBoson) {
      nParticles++;
      sPrint += Form("WBoson mass: %f,  ",genWBoson.mass());
    }
  }
  sPrint += Form("ngenWBosons:%i \n",nParticles);

  nParticles = 0;
  const GenParticle * genBJetFromTop = nullptr;
  for(const GenParticle & genBJet: genBJets)
  {
    if(genBJet.pdgId() == pdgIdBJet && ! genBJetFromTop)
    {
      genBJetFromTop = &genBJet;
    }
    if (genBJet.pdgId() == pdgIdBJet) nParticles++;
  }
  sPrint += Form("ngenBJets:%i \n",nParticles);

  std::vector<const GenParticle *> genWJetsFromTop;
  double genWJetsFromTop_mass = -1.;
  for(auto it1 = genWJets.cbegin(); it1 != genWJets.cend(); ++it1)
  {
    const GenParticle * genWJet1 = &(*it1);
    for(auto it2 = it1 + 1; it2 != genWJets.cend(); ++it2)
    {
      const GenParticle * genWJet2 = &(*it2);
      if(genWBosonFromTop)
      {
        if(((genWJet1->charge() + genWJet2->charge()) - genWBosonFromTop->charge()) < 1.e-2)
        {
          const double genWJetsFromTop_massCurrent = (genWJet1->p4() + genWJet2->p4()).mass();
          const double diff_massCurrent = std::fabs(genWJetsFromTop_massCurrent - genWBosonFromTop->mass());
          const double diff_mass        = std::fabs(genWJetsFromTop_mass        - genWBosonFromTop->mass());
          if(genWJetsFromTop_mass == -1. || diff_massCurrent < diff_mass)
          {
            genWJetsFromTop = { genWJet1, genWJet2 };
            genWJetsFromTop_mass = genWJetsFromTop_massCurrent;
          }
        }
      }
    }
  }
  */

  if(genWJetsFromTop.size() != 2) {
    return genMatchFlags;
  }
  
  std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
  const GenParticle * genWJetFromTop_lead = genWJetsFromTop[0];
  const GenParticle * genWJetFromTop_sublead = genWJetsFromTop[1];

  
  //TString  sPrint = "";
  /*
    sPrint += Form("isGenMatchedJetTriplet():: mode %i \n",mode);
  sPrint += Form(" Top:     (%f, %f, %f, %f); \n b:       (%f, %f, %f, %f); \n W1:      (%f, %f, %f, %f); \n W2:      (%f, %f, %f, %f)\n",
		 genTop->pt(),genTop->eta(),genTop->phi(),genTop->mass(),
		 genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass(),
		 genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass(),
		 genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass());*/
  //std::cout<<sPrint<<std::endl;
  
  
  //sPrint += "AuxFunction sPrint1 ";
  //if (TypeTop != 3) std::cout<<"Print 2 :" <<sPrint<<std::endl;
  
  
  const bool passWbosonMassVeto_top = passWbosonMassVeto(
	  genWJetFromTop_lead, genWJetFromTop_sublead, genWBosonFromTop
							 );
  //passWbosonMassVeto_top = true;
  
  //double jetGenMatchdRThrsh = 0.2;
  double fatjetGenMatchdRThrsh = 0.2;
  double jetBJetGenMatchdRThrsh = 0.3;
  double jetWJetsGenMatchdRThrsh = 0.3;
  if (TypeTop==1) {
    fatjetGenMatchdRThrsh   = 0.75;
    jetBJetGenMatchdRThrsh  = 0.25; // 0.1
    jetWJetsGenMatchdRThrsh = 0.25; //0.1
  }
  if (TypeTop==2) {
    fatjetGenMatchdRThrsh = 0.6;
    jetBJetGenMatchdRThrsh = 0.3;
    jetWJetsGenMatchdRThrsh = 0.2;
  }

  

  genMatchFlags[kGenMatchedBJet]    = deltaR(recBJet, genBJetFromTop->p4()) < jetBJetGenMatchdRThrsh;
  genMatchFlags[kGenMatchedWJet1]   =
    (genWJetFromTop_lead    && deltaR(recWJet1, genWJetFromTop_lead->p4())    < jetWJetsGenMatchdRThrsh) ||
    (genWJetFromTop_sublead && deltaR(recWJet1, genWJetFromTop_sublead->p4()) < jetWJetsGenMatchdRThrsh)
  ;
  genMatchFlags[kGenMatchedWJet2]   =
    (genWJetFromTop_lead    && deltaR(recWJet2, genWJetFromTop_lead->p4())    < jetWJetsGenMatchdRThrsh) ||
    (genWJetFromTop_sublead && deltaR(recWJet2, genWJetFromTop_sublead->p4()) < jetWJetsGenMatchdRThrsh)
  ;
  genMatchFlags[kGenMatchedTriplet] =
    genMatchFlags[kGenMatchedBJet]  &&
    genMatchFlags[kGenMatchedWJet1] &&
    genMatchFlags[kGenMatchedWJet2] &&
    passWbosonMassVeto_top
  ;

  if (TypeTop==1) {
    genMatchFlags[kGenMatchedFatJet] =
      (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genTop->p4()) < fatjetGenMatchdRThrsh);
  } else if (TypeTop==2) {
    genMatchFlags[kGenMatchedFatJet] =
      (recFatJet.pt() > 0. && recFatJet.mass() > 0.  && deltaR(recFatJet, genWBosonFromTop->p4()) < fatjetGenMatchdRThrsh);
  }
  
  return genMatchFlags;
}

