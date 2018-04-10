#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <algorithm> // std::sort()

std::map<int, bool>
isGenMatchedJetTriplet(const Particle::LorentzVector & recBJet,
                       const Particle::LorentzVector & recWJet1,
                       const Particle::LorentzVector & recWJet2,
                       const std::vector<GenParticle> & genTopQuarks,
                       const std::vector<GenParticle> & genBJets,
                       const std::vector<GenParticle> & genWBosons,
                       const std::vector<GenParticle> & genWJets,
                       int mode,
                       double & genTopPt)
{
  std::map<int, bool> genMatchFlags = {
    { kGenMatchedBJet ,    false },
    { kGenMatchedWJet1 ,   false },
    { kGenMatchedWJet2 ,   false },
    { kGenMatchedTriplet , false },
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

  genMatchFlags[kGenMatchedBJet]    = deltaR(recBJet, genBJetFromTop->p4()) < 0.2;
  genMatchFlags[kGenMatchedWJet1]   =
    (genWJetFromTop_lead    && deltaR(recWJet1, genWJetFromTop_lead->p4())    < 0.2) ||
    (genWJetFromTop_sublead && deltaR(recWJet1, genWJetFromTop_sublead->p4()) < 0.2)
  ;
  genMatchFlags[kGenMatchedWJet2]   =
    (genWJetFromTop_lead    && deltaR(recWJet2, genWJetFromTop_lead->p4())    < 0.2) ||
    (genWJetFromTop_sublead && deltaR(recWJet2, genWJetFromTop_sublead->p4()) < 0.2)
  ;
  genMatchFlags[kGenMatchedTriplet] =
    genMatchFlags[kGenMatchedBJet]  &&
    genMatchFlags[kGenMatchedWJet1] &&
    genMatchFlags[kGenMatchedWJet2] &&
    passWbosonMassVeto_top
  ;

  return genMatchFlags;
}


std::map<int, double>
isGenMatchedJetTripletVar(const std::vector<GenParticle> & genTopQuarks,
                          const std::vector<GenParticle> & genBJets,
                          const std::vector<GenParticle> & genWBosons,
                          const std::vector<GenParticle> & genWJets,
                          int mode)
{
  std::map<int, double> genMatchValues = {
    { kGenPtTop,       -1. },
    { kGenPtTopB,      -1. },
    { kGenPtTopW,      -1. },
    { kGenPtTopWj1,    -1. },
    { kGenPtTopWj2,    -1. },
    { kGenEtaTop,    -100. },
    { kGenEtaTopB,   -100. },
    { kGenEtaTopW,   -100. },
    { kGenEtaTopWj1, -100. },
    { kGenEtaTopWj2, -100. },
    { kGenPhiTopB,   -100. },
    { kGenPhiTopWj1, -100. },
    { kGenPhiTopWj2, -100. },
    { kGenMTopB,     -100. },
    { kGenMTopWj1,   -100. },
    { kGenMTopWj2,   -100. },
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
      genMatchValues[kGenPtTop]  = genTopQuark.pt();
      genMatchValues[kGenEtaTop] = genTopQuark.eta();
    }
  }

  const GenParticle * genWBosonFromTop = nullptr;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.pdgId() == pddIdWBoson && ! genWBosonFromTop)
    {
      genWBosonFromTop = &genWBoson;
      genMatchValues[kGenPtTopW]  = genWBoson.pt();
      genMatchValues[kGenEtaTopW] = genWBoson.eta();
    }
  }

  const GenParticle * genBJetFromTop = nullptr;
  for(const GenParticle & genBJet: genBJets)
  {
    if(genBJet.pdgId() == pdgIdBJet && ! genBJetFromTop )
    {
      genBJetFromTop = &genBJet;
      genMatchValues[kGenPtTopB]  = genBJet.pt();
      genMatchValues[kGenEtaTopB] = genBJet.eta();
      genMatchValues[kGenPhiTopB] = genBJet.phi();
      genMatchValues[kGenMTopB]   = genBJet.mass();
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
    genMatchValues[kGenPtTopWj1]  = genWJetFromTop_lead->pt();
    genMatchValues[kGenPtTopWj2]  = genWJetFromTop_sublead->pt();
    genMatchValues[kGenEtaTopWj1] = genWJetFromTop_lead->eta();
    genMatchValues[kGenEtaTopWj2] = genWJetFromTop_sublead->eta();
    genMatchValues[kGenPhiTopWj1] = genWJetFromTop_lead->phi();
    genMatchValues[kGenPhiTopWj2] = genWJetFromTop_sublead->phi();
    genMatchValues[kGenMTopWj1]   = genWJetFromTop_lead->mass();
    genMatchValues[kGenMTopWj2]   = genWJetFromTop_sublead->mass();
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
