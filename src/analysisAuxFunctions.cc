#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <numeric> // std::accumulate()

double
get_BtagWP(int era,
           BtagWP wp)
{
  assert(era == kEra_2017);
  return RecoJet::useDeepCSV ? BtagWP_deepCSV_2017.at(wp) : BtagWP_CSVv2_2017.at(wp);
}

bool
isHigherPt(const Particle * particle1,
           const Particle * particle2)
{
  return particle1->pt() > particle2->pt();
}

bool
isHigherConePt(const RecoLepton * particle1,
               const RecoLepton * particle2)
{
  return (particle1->cone_pt() > particle2->cone_pt());
}

bool
isHigherCSV(const RecoJet * jet1,
            const RecoJet * jet2)
{
  return jet1->BtagCSV() > jet2->BtagCSV();
}

int
get_selection(const std::string & selectionString)
{
  if(selectionString == "Loose")    return kLoose;
  if(selectionString == "Fakeable") return kFakeable;
  if(selectionString == "Tight")    return kTight;
  throw cmsException(__func__) << "Invalid Configuration parameter for object selection = " << selectionString;
}

int
get_era(const std::string & eraString)
{
  if(eraString == "2017")
  {
    return kEra_2017;
  }
  throw cmsException(__func__) << "Invalid Configuration parameter 'era' = " << eraString;
}

int
getHadTau_genPdgId(const RecoHadTau * hadTau)
{
  int hadTau_genPdgId = -1;
  if     (hadTau->genHadTau()) hadTau_genPdgId = 15;
  else if(hadTau->genLepton()) hadTau_genPdgId = std::abs(hadTau->genLepton()->pdgId());
  return hadTau_genPdgId;
}

double
get_BtagWeight(const std::vector<const RecoJet *> & jets)
{
  double btag_weight = 1.;
  for(const RecoJet * jet: jets)
  {
    btag_weight *= jet->BtagWeight();
  }
  return btag_weight;
}

Particle::LorentzVector
compMHT(const std::vector<const RecoLepton *> & leptons,
        const std::vector<const RecoHadTau *> & hadTaus,
        const std::vector<const RecoJet *> & jets)
{
  math::PtEtaPhiMLorentzVector mht_p4(0,0,0,0);
  for(const RecoLepton * lepton: leptons)
  {
    mht_p4 += lepton->p4();
  }
  for(const RecoHadTau * hadTau: hadTaus)
  {
    mht_p4 += hadTau->p4();
  }
  for(const RecoJet * jet: jets)
  {
    mht_p4 += jet->p4();
  }
  return mht_p4;
}

double
compMEt_LD(const Particle::LorentzVector & met_p4,
           const Particle::LorentzVector & mht_p4)
{
  return met_coef * met_p4.pt() + mht_coef * mht_p4.pt();
}

std::vector<const RecoLepton *>
mergeLeptonCollectionsNoSort(const std::vector<const RecoElectron *> & electrons,
                             const std::vector<const RecoMuon *> & muons)
{
  std::vector<const RecoLepton *> leptons;
  const std::size_t nLeptons = electrons.size() + muons.size();
  if(nLeptons > 0)
  {
    leptons.reserve(nLeptons);
    leptons.insert(leptons.end(), electrons.begin(), electrons.end());
    leptons.insert(leptons.end(), muons.begin(), muons.end());
  }
  return leptons;
}

std::vector<const RecoLepton *>
mergeLeptonCollections(const std::vector<const RecoElectron *> & electrons,
                       const std::vector<const RecoMuon *> & muons)
{
  return mergeLeptonCollections(electrons, muons, isHigherPt);
}

template<>
void
printCollection<RecoLepton>(const std::string & collection_name,
                            const std::vector<const RecoLepton *> & leptons)
{
  std::cout << " (#" << collection_name << " = " << leptons.size() << ")\n";
  for(std::size_t idxLepton = 0; idxLepton < leptons.size(); ++idxLepton)
  {
    std::cout << collection_name << "  #" << idxLepton << ":\n";
    const RecoLepton * const lepton = leptons[idxLepton];

    const RecoElectron * const electron = dynamic_cast<const RecoElectron *>(lepton);
    if(electron)
    {
      std::cout << (*electron);
      continue;
    }

    const RecoMuon * const muon = dynamic_cast<const RecoMuon *>(lepton);
    if(muon)
    {
      std::cout << (*muon);
      continue;
    }

    std::cout << (*lepton);
  }
}

int
nCombinationsK(int n,
               int k)
{
  assert(n >= k && n >= 0 && k >= 0);
  if(k > n)     return 0;
  if(k * 2 > n) k = n-k;
  if(k == 0)    return 1;

  int result = n;
  for(int i = 2; i <= k; ++i)
  {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}
