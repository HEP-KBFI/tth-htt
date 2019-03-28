#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // countLeptonGenMatches()
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // countHadTauGenMatches()
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <TMath.h> // TMath::Sqrt

#include <numeric> // std::accumulate()

double
get_BtagWP(int era,
           BtagWP wp)
{
  return BtagWP_map.at(era).at(Btag::kDeepJet).at(wp);
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

bool
isHigherCSV_ak8(const RecoJetAK8 * jet1,
		const RecoJetAK8 * jet2)
{
  double jet1BtagCSV = 0.;
  if ( jet1->subJet1() ) jet1BtagCSV += jet1->subJet1()->BtagCSV();
  if ( jet1->subJet2() ) jet1BtagCSV += jet1->subJet2()->BtagCSV();
  double jet2BtagCSV = 0.;
  if ( jet2->subJet1() ) jet2BtagCSV += jet2->subJet1()->BtagCSV();
  if ( jet2->subJet2() ) jet2BtagCSV += jet2->subJet2()->BtagCSV();
  return jet1BtagCSV > jet2BtagCSV;
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
  if(eraString == "2016")
  {
    return kEra_2016;
  }
  else if(eraString == "2017")
  {
    return kEra_2017;
  }
  else if(eraString == "2018")
  {
    return kEra_2018;
  }
  throw cmsException(__func__) << "Invalid Configuration parameter 'era' = " << eraString;
}

int
get_tau_id_wp_int(const std::string & wp_str)
{
  int wp_int = -1;
  if     (wp_str == "VVLoose") wp_int = 1;
  else if(wp_str == "VLoose" ) wp_int = 2;
  else if(wp_str == "Loose"  ) wp_int = 3;
  else if(wp_str == "Medium" ) wp_int = 4;
  else if(wp_str == "Tight"  ) wp_int = 5;
  else if(wp_str == "VTight" ) wp_int = 6;
  else if(wp_str == "VVTight") wp_int = 7;
  else
  {
    throw cmsException(__func__, __LINE__)
      << "Invalid argument 'wp_str' = " << wp_str
    ;
  }
  return wp_int;
}

std::string
get_tau_id_wp_str(int wp_int)
{
  if     (wp_int == 1) return "VVLoose";
  else if(wp_int == 2) return "VLoose";
  else if(wp_int == 3) return "Loose";
  else if(wp_int == 4) return "Medium";
  else if(wp_int == 5) return "Tight";
  else if(wp_int == 6) return "VTight";
  else if(wp_int == 7) return "VVTight";
  else throw cmsException(__func__, __LINE__)
         << "Invalid argument 'wp_int' = " << wp_int
       ;
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

double 
comp_Smin(const Particle::LorentzVector& visP4, double metPx, double metPy)
{
  double visPt = visP4.pt();
  double visMass = visP4.mass();
  double visMass2 = visMass*visMass;
  double visEt = TMath::Sqrt(visMass2 + visPt*visPt);
  double metEt = TMath::Sqrt(metPx*metPx + metPy*metPy);
  double Smin = TMath::Sqrt(visMass2 + 2.*(visEt*metEt - (visP4.px()*metPx + visP4.py()*metPy)));
  return Smin;
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
    std::cout << collection_name << " #" << idxLepton << ": ";
    const RecoLepton * const lepton = leptons[idxLepton];

    const RecoElectron * const electron = dynamic_cast<const RecoElectron *>(lepton);
    if(electron)
    {
      std::cout << (*electron) << std::endl;
      continue;
    }

    const RecoMuon * const muon = dynamic_cast<const RecoMuon *>(lepton);
    if(muon)
    {
      std::cout << (*muon) << std::endl;
      continue;
    }

    std::cout << (*lepton) << std::endl;
  }
}

int
countFakeElectrons(const std::vector<const RecoLepton *> & leptons)
{
  int numGenMatchedLeptons = 0;
  int numGenMatchedPhotons = 0;
  int numGenMatchedJets = 0;
  for ( std::vector<const RecoLepton *>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++ lepton ) {
    if ( (*lepton)->is_electron() ) {
      countLeptonGenMatches(*lepton, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
    }
  }
  return numGenMatchedJets;
}

int 
countFakeMuons(const std::vector<const RecoLepton *> & leptons)
{
  int numGenMatchedLeptons = 0;
  int numGenMatchedPhotons = 0;
  int numGenMatchedJets = 0;
  for ( std::vector<const RecoLepton *>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    if ( (*lepton)->is_muon() ) {
      countLeptonGenMatches(*lepton, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
    }
  }
  return numGenMatchedJets;
}

int 
countFakeHadTaus(const std::vector<const RecoHadTau *> & hadTaus)
{
  int numGenMatchedHadTaus = 0;
  int numGenMatchedElectrons = 0;
  int numGenMatchedMuons = 0;
  int numGenMatchedJets = 0;
  for ( std::vector<const RecoHadTau *>::const_iterator hadTau = hadTaus.begin();
	hadTau != hadTaus.end(); ++hadTau ) {
    countHadTauGenMatches(*hadTau, numGenMatchedHadTaus, numGenMatchedElectrons, numGenMatchedMuons, numGenMatchedJets);
  }
  return numGenMatchedJets;
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

int
countTrigObjs_passingL1(const std::vector<TrigObj>& trigObjs, int Id, double min_l1pt, double min_l1pt_2)
{
  int numSelTrigObjs = 0;
  for ( std::vector<TrigObj>::const_iterator trigObj = trigObjs.begin();
	trigObj != trigObjs.end(); ++trigObj ) {
    if ( trigObj->id() == Id && trigObj->l1pt() > min_l1pt && (trigObj->l1pt_2() > min_l1pt_2 || min_l1pt_2 == -1.) ) {
      ++numSelTrigObjs;
    }
  }
  return numSelTrigObjs;
}

bool
contains(const std::vector<std::string>& list_of_strings, const std::string& keyWord)
{
  for ( std::vector<std::string>::const_iterator entry = list_of_strings.begin();
	entry != list_of_strings.end(); ++entry ) {
    if ( (*entry) == keyWord ) {
      return true;
    }
  }
  return false;
}

std::string
findFile(const std::string& fileName)
{
  LocalFileInPath inputFile(fileName);
  if ( inputFile.fullPath().empty() ) {
    std::cerr << "Error: Cannot find file = " << fileName;
    assert(0);
  }
  return inputFile.fullPath();
}
