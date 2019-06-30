#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGen*

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <algorithm> // std::sort()
#include <numeric> // std::iota()

std::map<int, Particle::LorentzVector>
isGenMatchedJetTripletVar(const std::vector<GenParticle> & genTopQuarks,
                          const std::vector<GenParticle> & genBJets,
                          const std::vector<GenParticle> & genWBosons,
                          const std::vector<GenParticle> & genQuarkFromTop,
                          int mode)
{
  std::map<int, Particle::LorentzVector> genMatchValues = {
    { kGenTop,        Particle::LorentzVector(0., 0., 0., 0.) },
    { kGenTopB,       Particle::LorentzVector(0., 0., 0., 0.) },
    { kGenTopW,       Particle::LorentzVector(0., 0., 0., 0.) },
    { kGenTopWj1,     Particle::LorentzVector(0., 0., 0., 0.) },
    { kGenTopWj2,     Particle::LorentzVector(0., 0., 0., 0.) }
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

  const GenParticle * genBJetFromTop = nullptr;
  for(const GenParticle & genBJet: genBJets)
  {
    if(genBJet.pdgId() == pdgIdBJet && ! genBJetFromTop )
    {
      genBJetFromTop = &genBJet;
      genMatchValues[kGenTopB].SetPxPyPzE(genBJet.p4().x(), genBJet.p4().y(), genBJet.p4().z(), genBJet.p4().energy());
    }
  }

  std::vector<const GenParticle *> genWBosonsFromTop; // = nullptr;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.pdgId() == pddIdWBoson ) // && ! genWBosonFromTop
    {
      genWBosonsFromTop.push_back(&genWBoson);
    }
  }

  double mass_diff = 1000000.;
  const GenParticle * genWBosonFromTopFinal = nullptr;
  //for(auto itW = genWBosons.cbegin(); itW != genWBosons.cend(); ++itW)
  for(auto itW = genWBosonsFromTop.cbegin(); itW != genWBosonsFromTop.cend(); ++itW) // Edit Siddhesh
  {
    const GenParticle * genWBosonFromTop = (*itW);
    if(! genBJetFromTop || ! genTop)
    {
      continue;
    }
    if ( std::fabs((genWBosonFromTop->p4() + genBJetFromTop->p4()).mass() - genTop->p4().mass()) < mass_diff)
    {
      genWBosonFromTopFinal = genWBosonFromTop;
      genMatchValues[kGenTopW].SetPxPyPzE(genWBosonFromTop->p4().x(), genWBosonFromTop->p4().y(), genWBosonFromTop->p4().z(), genWBosonFromTop->p4().energy());
      mass_diff = std::fabs((genWBosonFromTop->p4() + genBJetFromTop->p4()).mass() - genTop->p4().mass());
    }
  }

  //std::cout<<" genWBosonsFromTop.size() "<< genWBosonsFromTop.size() << std::endl;
  std::vector<const GenParticle *> genWJetsFromTop;
  if (genWBosonFromTopFinal) {
  double genWJetsFromTop_mass = -1.;
  double genWJetsFromTop_massW = -1.;
  for(auto it1 = genQuarkFromTop.cbegin(); it1 != genQuarkFromTop.cend(); ++it1)
  {
    const GenParticle * genWJet1 = &(*it1);
    for(auto it2 = it1 + 1; it2 != genQuarkFromTop.cend(); ++it2)
    {
      const GenParticle * genWJet2 = &(*it2);
      if ( boost::math::sign(genWJet1->charge()) == boost::math::sign(genWBosonFromTopFinal->charge()) &&
	     boost::math::sign(genWJet2->charge()) == boost::math::sign(genWBosonFromTopFinal->charge()) ) // Edit Siddhesh
      {
        const double genWJetsFromTop_massCurrent = (genWJet1->p4() + genWJet2->p4() + genBJetFromTop->p4()).mass();
        const double diff_massCurrent = std::fabs((genWJet1->p4() + genWJet2->p4() + genBJetFromTop->p4()).mass() - genTop->p4().mass());
        const double diff_mass        = std::fabs(genWJetsFromTop_mass        - genTop->p4().mass());

        const double genWJetsFromTop_massWCurrent = (genWJet1->p4() + genWJet2->p4()).mass();
        const double diff_massWCurrent = std::fabs(genWJetsFromTop_massWCurrent - genWBosonFromTopFinal->p4().mass());
        const double diff_massW        = std::fabs(genWJetsFromTop_massW        - genWBosonFromTopFinal->p4().mass());

        if(genWJetsFromTop_mass == -1. || ((diff_massCurrent < diff_mass) || (diff_massWCurrent < diff_massW)))
        {
          const bool passWbosonMassVeto_top = passWbosonMassVeto(
            genWJet1, genWJet2, genWBosonFromTopFinal
          );
          if(passWbosonMassVeto_top)
          {
            genWJetsFromTop = { genWJet1, genWJet2 };
            genWJetsFromTop_mass = genWJetsFromTop_massCurrent;
            genWJetsFromTop_massW = genWJetsFromTop_massWCurrent;
          }
        }
      } // close if charge
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

  genMatchValues[kGenTopWj1].SetPxPyPzE(genWJetFromTop_lead->p4().x(), genWJetFromTop_lead->p4().y(), genWJetFromTop_lead->p4().z(), genWJetFromTop_lead->p4().energy());
  genMatchValues[kGenTopWj2].SetPxPyPzE(genWJetFromTop_sublead->p4().x(), genWJetFromTop_sublead->p4().y(), genWJetFromTop_sublead->p4().z(), genWJetFromTop_sublead->p4().energy());


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
getType(std::size_t sizeHTTv2,
        std::size_t sizeFatW,
        std::size_t sizeResolved)
{
  if     (sizeHTTv2    > 0) return 1;
  else if(sizeFatW     > 0) return 2;
  else if(sizeResolved > 0) return 3;
  return -1;
}

std::vector<double>
getBdiscr(const std::vector<const RecoJet *> & selJetsIt)
{
  std::vector<double> btag_disc;
  for(const RecoJet * jetIterB: selJetsIt)
  {
    btag_disc.push_back(jetIterB->BtagCSV());
  }
  return btag_disc;
}

std::vector<size_t>
calRank( std::vector<double> & btag_disc)
{
  std::vector<std::size_t> result(btag_disc.size(), 0);
  //sorted index
  std::vector<std::size_t> indx(btag_disc.size());
  std::iota(indx.begin(), indx.end(), 0);
  std::sort(indx.begin(), indx.end(), [&btag_disc](std::size_t i1, std::size_t i2) { return btag_disc[i1] > btag_disc[i2]; });
  //return ranking
  for(std::size_t iter = 0; iter < btag_disc.size(); ++iter)
  {
    result[indx[iter]] = iter + 1;
  }
  return result;
}

std::vector<std::size_t>
sort_indexes(const std::vector<double> & v)
{
  // initialize original index locations
  std::vector<std::size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(), [&v](std::size_t i1, std::size_t i2) { return v[i1] > v[i2]; });
  return idx;
}
