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
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kHadTauPt_*
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <TMath.h> // TMath::Sqrt
#include <numeric> // std::accumulate()

double
get_BtagWP(Era era,
           Btag btag,
           BtagWP wp)
{
  return BtagWP_map.at(era).at(btag).at(wp);
}

double
min_Deta_fwdJet_jet(Particle::LorentzVector FwdJet, std::vector<const RecoJet *> selJets)
{
  double min_deta = 10000.;
  for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin(); selJet != selJets.end(); ++selJet )
  {
    double teste = std::abs(FwdJet.Eta() - (*selJet) -> eta());
    if (teste < min_deta) { min_deta = teste; }
  }
  return min_deta;
}


Particle::LorentzVector
HighestEtaFwdJet(std::vector<const RecoJet *> selJetsForward)
{
  Particle::LorentzVector mostFwdJet;
  if (selJetsForward.size() > 0 )
  {
   double teste = 0;
   for ( std::vector<const RecoJet*>::const_iterator selFwdJet = selJetsForward.begin(); selFwdJet != selJetsForward.end(); ++selFwdJet )
   {
     if ((*selFwdJet) -> absEta() > teste) { mostFwdJet = (*selFwdJet) -> p4(); }
     teste = std::abs(mostFwdJet.Eta());
   }
  }
  return mostFwdJet;
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
  if(jet1->subJet1()) jet1BtagCSV += jet1->subJet1()->BtagCSV();
  if(jet1->subJet2()) jet1BtagCSV += jet1->subJet2()->BtagCSV();
  double jet2BtagCSV = 0.;
  if(jet2->subJet1()) jet2BtagCSV += jet2->subJet1()->BtagCSV();
  if(jet2->subJet2()) jet2BtagCSV += jet2->subJet2()->BtagCSV();
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

Era
get_era(const std::string & eraString)
{
  if(eraString == "2016")
  {
    return Era::k2016;
  }
  else if(eraString == "2017")
  {
    return Era::k2017;
  }
  else if(eraString == "2018")
  {
    return Era::k2018;
  }
  throw cmsException(__func__) << "Invalid Configuration parameter 'era' = " << eraString;
}

std::string
get_era(Era era)
{
  switch(era)
  {
    case Era::k2016: return "2016";
    case Era::k2017: return "2017";
    case Era::k2018: return "2018";
    default: throw cmsException(__func__, __LINE__) << "Invalid era: " << static_cast<int>(era);
  }
}

TauID
get_tau_id_enum(const std::string & tauId_str)
{
  const std::string wp_type = tauId_str.substr(0, 7);
  if(! TauID_PyMap.count(wp_type))
  {
    throw cmsException(__func__, __LINE__) << "Unrecognizable tau ID selection: " << tauId_str;
  }
  return TauID_PyMap.at(wp_type);
}

int
get_tau_id_wp_int(const std::string & tauId_str)
{

  return get_tau_id_wp_int(get_tau_id_enum(tauId_str), tauId_str.substr(7));
}

int
get_tau_id_wp_int(TauID tauID,
                  const std::string & wp_str)
{
  assert(TauID_levels.count(tauID));
  const int nof_levels = TauID_levels.at(tauID);
  assert(TauID_level_strings.count(nof_levels));
  const std::vector<std::string> & levels = TauID_level_strings.at(nof_levels);
  const auto wp_str_it = std::find(levels.begin(), levels.end(), wp_str);
  if(wp_str_it == levels.end())
  {
    throw cmsException(__func__, __LINE__)
      << "Invalid tau ID string requested for tau ID " << as_integer(tauID) << ": " << wp_str
    ;
  }
  return static_cast<int>(std::distance(levels.begin(), wp_str_it)) + 1;
}

std::string
get_tau_id_wp_str(TauID tauID,
                  int wp_int)
{
  assert(TauID_levels.count(tauID));
  const int nof_levels = TauID_levels.at(tauID);
  if(wp_int < 1 || wp_int > nof_levels)
  {
    throw cmsException(__func__, __LINE__)
      << "Invalid level requested for tau ID " << as_integer(tauID) << ": " << wp_int
    ;
  }
  assert(TauID_level_strings.count(nof_levels));
  const std::vector<std::string> & levels = TauID_level_strings.at(nof_levels);
  assert(static_cast<int>(levels.size()) == nof_levels);
  return levels.at(wp_int - 1);
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

double
get_BtagWeight(const std::vector<const RecoJet *> & jets,
               int central_or_shift)
{
  double btag_weight = 1.;
  for(const RecoJet * jet: jets)
  {
    btag_weight *= jet->BtagWeight(central_or_shift);
  }
  return btag_weight;
}

double
get_EWK_jet_weight(const std::vector<const RecoJet *> & jets,
                   EWKJetSys ewk_jet_option)
{
  const double ewk_jet_weight = 1.;
  const double ewk_jet_unc = 0.3;
  if(jets.size() > 2)
  {
    switch(ewk_jet_option)
    {
      case EWKJetSys::central: return ewk_jet_weight;
      case EWKJetSys::up:      return ewk_jet_weight + ewk_jet_unc;
      case EWKJetSys::down:    return ewk_jet_weight - ewk_jet_unc;
      default: assert(0);
    }
  }
  return ewk_jet_weight;
}

double
get_EWK_bjet_weight(const std::vector<const RecoJet *> & bjets,
                    EWKBJetSys ewk_bjet_option)
{
  const double ewk_bjet_weight = 1.;
  const double ewk_bjet_unc = bjets.size() > 1 ? 0.4 : 0.1;
  switch(ewk_bjet_option)
  {
    case EWKBJetSys::central: return ewk_bjet_weight;
    case EWKBJetSys::up:      return ewk_bjet_weight + ewk_bjet_unc;
    case EWKBJetSys::down:    return ewk_bjet_weight - ewk_bjet_unc;
    default: assert(0);
  }
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
comp_Smin(const Particle::LorentzVector & visP4,
          double metPx,
          double metPy)
{
  const double visPt = visP4.pt();
  const double visMass = visP4.mass();
  const double visMass2 = visMass * visMass;
  const double visEt = std::sqrt(visMass2 + visPt * visPt);
  const double metEt = std::sqrt(metPx * metPx + metPy * metPy);
  const double Smin = std::sqrt(visMass2 + 2. * (visEt * metEt - (visP4.px() * metPx + visP4.py() * metPy)));
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
  for(const RecoLepton * const lepton: leptons)
  {
    if(lepton->is_electron())
    {
      countLeptonGenMatches(lepton, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
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
  for(const RecoLepton * const lepton: leptons)
  {
    if(lepton->is_muon())
    {
      countLeptonGenMatches(lepton, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
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
  for(const RecoHadTau * const hadTau: hadTaus)
  {
    countHadTauGenMatches(hadTau, numGenMatchedHadTaus, numGenMatchedElectrons, numGenMatchedMuons, numGenMatchedJets);
  }
  return numGenMatchedJets;
}

int
countElectrons(const std::vector<const RecoLepton *> & leptons)
{
  return std::count_if(leptons.cbegin(), leptons.cend(), [](const RecoLepton * lepton) -> bool { return lepton->is_electron(); });
}

int
countMuons(const std::vector<const RecoLepton *> & leptons)
{
  return std::count_if(leptons.cbegin(), leptons.cend(), [](const RecoLepton * lepton) -> bool { return lepton->is_muon(); });
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
countTrigObjs_passingL1(const std::vector<TrigObj> & trigObjs,
                        int Id,
                        double min_l1pt,
                        double min_l1pt_2)
{
  return std::count_if(
    trigObjs.begin(), trigObjs.end(),
    [Id, min_l1pt, min_l1pt_2](const TrigObj & trigObj) -> bool
    {
      return
        trigObj.id() == Id                 &&
        trigObj.l1pt() > min_l1pt          &&
        (
          trigObj.l1pt_2() > min_l1pt_2 ||
          min_l1pt_2 == -1.
        )
      ;
    }
  );
}

bool
contains(const std::vector<std::string> & list_of_strings,
         const std::string & keyWord)
{
  return std::find(list_of_strings.begin(), list_of_strings.end(), keyWord) != list_of_strings.end();
}

std::string
findFile(const std::string & fileName)
{
  const LocalFileInPath inputFile(fileName);
  if(inputFile.fullPath().empty())
  {
    throw cmsException(__func__, __LINE__)
      << "Cannot find file = " << fileName
    ;
  }
  return inputFile.fullPath();
}

bool
isSFOS(const std::vector<const RecoLepton *> & leptons)
{
  bool isSameFlavor_OS = false;
  for(auto lepton1_it = leptons.begin(); lepton1_it != leptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != leptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      if(lepton1->pdgId() == -lepton2->pdgId())
      {
        // pair of same flavor leptons of opposite charge
        isSameFlavor_OS = true;
        break;
      }
    }
  }
  return isSameFlavor_OS;
}

bool
isfailsLowMassVeto(const std::vector<const RecoLepton *> & preselLeptons)
{
  bool failsLowMassVeto = false;
  for(auto lepton1_it = preselLeptons.begin(); lepton1_it != preselLeptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != preselLeptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      const double mass = (lepton1->p4() + lepton2->p4()).mass();
      if(mass < 12.)
      {
        failsLowMassVeto = true;
        break;
      }
    }
  }
  return failsLowMassVeto;
}

double
massL(const std::vector<const RecoLepton *> & Leptons)
{
  double massFO = 10000.;
  for(auto lepton1_it = Leptons.begin(); lepton1_it != Leptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != Leptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      const double mass = (lepton1->cone_p4() + lepton2->cone_p4()).mass();
      if(mass < massFO)
      {
        massFO = mass;
      }
    }
  }
  return massFO;
}

bool
isfailsZbosonMassVeto(const std::vector<const RecoLepton *> & preselLeptons,
                      bool ignoreOS,
                      bool isDEBUG)
{
  bool failsZbosonMassVeto = false;
  for(auto lepton1_it = preselLeptons.begin(); lepton1_it != preselLeptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != preselLeptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      if(ignoreOS || (! ignoreOS && lepton1->pdgId() == -lepton2->pdgId()))
      {
        // pair of same flavor leptons of opposite charge
        const double mass = (lepton1->p4() + lepton2->p4()).mass();
        if(std::fabs(mass - z_mass) < z_window )
        {
          if(isDEBUG)
          {
            std::cout
              << "Found a pair of leptons with mass of " << mass << ", thus falling within the Z mass window of ("
              << z_mass - z_window << ", " << z_mass + z_window << "):\n" << *lepton1 << '\n' << *lepton2 << '\n'
            ;
          }
          failsZbosonMassVeto = true;
          break;
        }
      }
    }
  }
  return failsZbosonMassVeto;
}

int
countZbosonSFOSpairs(const std::vector<const RecoLepton *> & preselLeptons,
                     bool ignoreOS)
{
  int compatibleZbosonPairs = 0;
  for(auto lepton1_it = preselLeptons.begin(); lepton1_it != preselLeptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != preselLeptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      if(ignoreOS || (! ignoreOS && lepton1->pdgId() == -lepton2->pdgId()))
      {
        // pair of same flavor leptons of opposite charge
        const double mass = (lepton1->p4() + lepton2->p4()).mass();
        if(std::fabs(mass - z_mass) < z_window )
        {
          ++compatibleZbosonPairs;
        }
      }
    }
  }
  return compatibleZbosonPairs;
}

bool
isfailsHtoZZVeto(const std::vector<const RecoLepton *> & preselLeptons)
{
  bool failsHtoZZVeto = false;
  for(auto lepton1_it = preselLeptons.begin(); lepton1_it != preselLeptons.end(); ++lepton1_it)
  {
    const RecoLepton * lepton1 = *lepton1_it;
    for(auto lepton2_it = lepton1_it + 1; lepton2_it != preselLeptons.end(); ++lepton2_it)
    {
      const RecoLepton * lepton2 = *lepton2_it;
      if(lepton1->pdgId() == -lepton2->pdgId())
      {
        // first pair of same flavor leptons of opposite charge
        for(auto lepton3_it = preselLeptons.begin(); lepton3_it != preselLeptons.end(); ++lepton3_it)
        {
          const RecoLepton * lepton3 = *lepton3_it;
          if(lepton3 == lepton1 || lepton3 == lepton2)
          {
            continue;
          }
          for(auto lepton4_it = lepton3_it + 1; lepton4_it != preselLeptons.end(); ++lepton4_it)
          {
            const RecoLepton * lepton4 = *lepton4_it;
            if(lepton4 == lepton1 || lepton4 == lepton2)
            {
              continue;
            }

            if(lepton3->pdgId() == -lepton4->pdgId())
            {
              // second pair of same flavor leptons of opposite charge
              const double mass = (lepton1->p4() + lepton2->p4() + lepton3->p4() + lepton4->p4()).mass();
              if(mass < 140.)
              {
                failsHtoZZVeto = true;
                break;
              }
            }
          }
        }
      }
    }
  }
  return failsHtoZZVeto;
}

int
get_VH_productionMode(const std::vector<GenParticle> & genWBosons)
{
  int Vboson_pdgId = 0;
  for(const GenParticle & genWBoson: genWBosons)
  {
    if(genWBoson.statusFlags() == 4481) // isPrompt, isHardProcess, fromHardProcess, isFirstCopy
    {
      Vboson_pdgId = std::abs(genWBoson.pdgId());
      break;
    }
  }
  return Vboson_pdgId > 0 ? 1000000 * Vboson_pdgId + 25 : -1;
}

std::string
get_key_hist(const EventInfo & eventInfo,
             const std::vector<GenParticle> & genWBosons,
             bool isMC_HH,
             bool isMC_VH,
             bool isDebug)
{
  std::string decayModeStr;
  if(! isMC_HH && ! isMC_VH)
  {
    decayModeStr = eventInfo.getDecayModeString();
  }
  else if(isMC_HH)
  {
    decayModeStr = eventInfo.getDiHiggsDecayModeString();
  }
  else if(isMC_VH)
  {
    int VH_pdgID = 0;
    int count_Vs = 0;
    std::string decayModeStrTest = eventInfo.getDecayModeString();
    if(decayModeStrTest.empty())
    {
      std::cout << "Found rare decay mode: " << eventInfo.genHiggsDecayMode << '\n';
      return "";
    }
    if ( decayModeStrTest == "hzg" || decayModeStrTest == "hmm")
    {
      decayModeStrTest = "hzz";// for definitivess, that should be very rare
    }
    for(std::size_t genWBosonIdx = 0 ; genWBosonIdx < genWBosons.size(); ++genWBosonIdx)
    {
      if(genWBosons[genWBosonIdx].statusFlags() == 4481)
      {
        VH_pdgID = std::abs(genWBosons[genWBosonIdx].pdgId());
        ++count_Vs;
      }
    }
    if(count_Vs != 1)
    {
        std::cout
          << "Invalid number of generator level vector bosons found: "
          << count_Vs << " for decay mode " << decayModeStrTest << '\n'
        ; // rarely happens, can afford to ignore it
        return "";
    }
    if(VH_pdgID == 23)
    {
      decayModeStr = "ZH_" + decayModeStrTest;
    }
    else if(VH_pdgID == 24)
    {
      decayModeStr = "WH_" + decayModeStrTest;
    }

    if(isDebug)
    {
      std::cout << "count_Vs = " << count_Vs << " decayModeStrTest " << decayModeStrTest << "\n";
    }
  }
  return decayModeStr;
}

std::vector<std::string>
get_key_list_hist(const EventInfo & eventInfo,
                  bool isMC_HH,
                  bool isMC_VH)
{
  std::vector<std::string> decayModes_evt;
  if(isMC_HH)
  {
    decayModes_evt = eventInfo.getDiHiggsDecayModes();
  }
  else
  {
    if(! isMC_VH)
    {
      decayModes_evt = eventInfo.getDecayModes();
    }
    else
    {
      for(const std::string & evt_decay_str: eventInfo.getDecayModes())
      {
        std::string evt_decay_strTest = evt_decay_str;
        if (evt_decay_strTest == "hzg" || evt_decay_strTest == "hmm" ) continue;
        decayModes_evt.push_back("WH_" + evt_decay_strTest);
      }
      for(const std::string & evt_decay_str: eventInfo.getDecayModes())
      {
        std::string evt_decay_strTest = evt_decay_str;
        if (evt_decay_strTest == "hzg" || evt_decay_strTest == "hmm" ) continue;
        decayModes_evt.push_back("ZH_" + evt_decay_strTest);
      }
    }
  }
  return  decayModes_evt;
}

std::string
get_prefix(const std::string & process_string,
           bool isMC_tH,
           bool isMC_HH,
           bool isMC_H,
           bool isMC_VH)
{
  std::string decayMode_and_genMatch;
  if(isMC_tH ||  isMC_HH || isMC_H)
  {
    decayMode_and_genMatch = process_string;
    decayMode_and_genMatch += "_";
  }
  else if(isMC_VH)
  {
    decayMode_and_genMatch = "";
  }
  else if(process_string == "ttH" || process_string == "ttH_ctcvcp")
  {
    decayMode_and_genMatch = process_string + "_";
  }
  return decayMode_and_genMatch;
}

std::vector<std::pair<std::string, int>>
get_htxs_binning(bool isMC_ttH)
{
  std::vector<std::pair<std::string, int>> binning;
  if(isMC_ttH)
  {
    binning = {
      { "fwd",        HTXSCategory::kForward    },
      { "pt0to60",    HTXSCategory::kPt0to60    },
      { "pt60to120",  HTXSCategory::kPt60to120  },
      { "pt120to200", HTXSCategory::kPt120to200 },
      { "pt200to300", HTXSCategory::kPt200to300 },
      { "ptGt300",    HTXSCategory::kPt300to450 | HTXSCategory::kPtGt450 },
      { "pt300to450", HTXSCategory::kPt300to450 },
      { "ptGt450",    HTXSCategory::kPtGt450    },
    };
  }
  return binning;
}

pileupJetID
get_pileupJetID(const std::string & pileupJetID_str)
{
  if     (pileupJetID_str == "disabled") return kPileupJetID_disabled;
  else if(pileupJetID_str == "loose"   ) return kPileupJetID_loose;
  else if(pileupJetID_str == "medium"  ) return kPileupJetID_medium;
  else if(pileupJetID_str == "tight"   ) return kPileupJetID_tight;
  else throw cmsException(__func__, __LINE__) << "Invalid argument: " << pileupJetID_str;
}

std::vector<const RecoJetBase*>
convert_to_RecoJetBase(const std::vector<const RecoJet*>& jets_derived)
{
  std::vector<const RecoJetBase*> jets_base;
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_derived.begin(); jet != jets_derived.end(); ++jet )
  {
    jets_base.push_back(*jet);
  }
  return jets_base;
}

double
clip(double value,
     double min_value,
     double max_value)
{
  return std::clamp(value, min_value, max_value);
}

std::vector<const RecoElectron *>
recompute_p4(const std::vector<const RecoElectron *> & electrons,
             ElectronPtSys option,
             bool (*sortFunction)(const Particle *, const Particle *))
{
  std::vector<const RecoElectron *> electrons_shifted;
  for(const RecoElectron * electron: electrons)
  {
    double corrFactor = 1.;
    switch(option)
    {
      case ElectronPtSys::central:                                                                break;
      case ElectronPtSys::scaleUp_barrel:   corrFactor = electron->absEta() <  1.479 ? 1.01 : 1.; break;
      case ElectronPtSys::scaleDown_barrel: corrFactor = electron->absEta() <  1.479 ? 0.99 : 1.; break;
      case ElectronPtSys::scaleUp_endcap:   corrFactor = electron->absEta() >= 1.479 ? 1.01 : 1.; break;
      case ElectronPtSys::scaleDown_endcap: corrFactor = electron->absEta() >= 1.479 ? 0.99 : 1.; break;
      case ElectronPtSys::resUp:            corrFactor = electron->genLepton() ?
                                                         1. + (1. - electron->genLepton()->pt() / electron->pt()) / 4. :
                                                         1.;                                      break;
      case ElectronPtSys::resDown:          corrFactor = electron->genLepton() ?
                                                         1. - (1. - electron->genLepton()->pt() / electron->pt()) / 4. :
                                                         1.;                                      break;
      case ElectronPtSys::uncorrected:      corrFactor = 1. / electron->eCorr();                  break;
    }
    RecoElectron * electron_nonConst = const_cast<RecoElectron *>(electron);
    electron_nonConst->set_ptEtaPhiMass(corrFactor * electron->pt(), electron->eta(), electron->phi(), electron->mass());
    electrons_shifted.push_back(electron_nonConst);
  }
  std::sort(electrons_shifted.begin(), electrons_shifted.end(), sortFunction);
  return electrons_shifted;
}

std::vector<RecoMuon>
recompute_p4(const std::vector<RecoMuon> & muons,
             MuonPtSys option,
             bool (*sortFunction)(const RecoMuon &, const RecoMuon &))
{
  std::vector<RecoMuon> muons_shifted;
  for(const RecoMuon & muon: muons)
  {
    double corrFactor = 1.;
    switch(option)
    {
      case MuonPtSys::central:                                                                             break;
      case MuonPtSys::ESBarrel1Up:   corrFactor = muon.absEta() < 0.9                         ? 1.02 : 1.; break;
      case MuonPtSys::ESBarrel1Down: corrFactor = muon.absEta() < 0.9                         ? 0.98 : 1.; break;
      case MuonPtSys::ESBarrel2Up:   corrFactor = muon.absEta() >= 0.9 && muon.absEta() < 1.2 ? 1.02 : 1.; break;
      case MuonPtSys::ESBarrel2Down: corrFactor = muon.absEta() >= 0.9 && muon.absEta() < 1.2 ? 0.98 : 1.; break;
      case MuonPtSys::ESEndcap1Up:   corrFactor = muon.absEta() >= 1.2 && muon.absEta() < 2.1 ? 1.02 : 1.; break;
      case MuonPtSys::ESEndcap1Down: corrFactor = muon.absEta() >= 1.2 && muon.absEta() < 2.1 ? 0.98 : 1.; break;
      case MuonPtSys::ESEndcap2Up:   corrFactor = muon.absEta() > 2.1                         ? 1.02 : 1.; break;
      case MuonPtSys::ESEndcap2Down: corrFactor = muon.absEta() > 2.1                         ? 0.98 : 1.; break;
      case MuonPtSys::ERUp:          /* has a special meaning in the context of charge flio measurement */ break;
      case MuonPtSys::ERDown:        /* has a special meaning in the context of charge flio measurement */ break;
    }
    RecoMuon muon_copy = muon;
    muon_copy.set_ptEtaPhiMass(corrFactor * muon.pt(), muon.eta(), muon.phi(), muon.mass());
    muons_shifted.push_back(muon_copy);
  }
  std::sort(muons_shifted.begin(), muons_shifted.end(), sortFunction);
  return muons_shifted;
}

std::map<std::string, double>
InitializeInputVarMap(const std::map<std::string, double> & AllVars_Map,
                      const std::vector<std::string> & BDTInputVariables)
{
  std::map<std::string, double> BDTInputs;
  for(unsigned int i = 0; i < BDTInputVariables.size(); i++){
    const std::string & BDTInputVariable = BDTInputVariables[i];
    std::map<std::string, double>::const_iterator BDTInput = AllVars_Map.find(BDTInputVariable);
    if ( BDTInput == AllVars_Map.end() )
      throw cmsException(__func__, __LINE__) << "Input variable = " << BDTInputVariable << " not in map given as function argument !!\n";
    //std::cout<<"Filling Map for Input Var.: " << BDTInputVariable << " with value " << BDTInput->second; << std::endl;
    BDTInputs[BDTInputVariable] = BDTInput->second;
  }
  return BDTInputs;
}

std::map<std::string, double>
InitializeInputVarMap(const std::map<std::string, double> & AllVars_Map,
                      const std::vector<std::string> & BDTInputVariables,
                      bool isNonRes)
{
  std::map<std::string, double> BDTInputs;
  if(isNonRes){// Initialize all Non-Reso. "one-hot encoders" to zero
    for(unsigned int i = 0; i < BDTInputVariables.size(); i++){
      const std::string & BDTInputVariable = BDTInputVariables[i];
      if(BDTInputVariable == "SM"){ 
	BDTInputs["SM"] = 0; 
      }else if(BDTInputVariable == "BM1"){ 
	BDTInputs["BM1"] = 0; 
      }else if(BDTInputVariable == "BM2"){ 
	BDTInputs["BM2"] = 0; 
      }else if(BDTInputVariable == "BM3"){ 
	BDTInputs["BM3"] = 0; 
      }else if(BDTInputVariable == "BM4"){ 
	BDTInputs["BM4"] = 0; 
      }else if(BDTInputVariable == "BM5"){ 
	BDTInputs["BM5"] = 0; 
      }else if(BDTInputVariable == "BM6"){ 
	BDTInputs["BM6"] = 0; 
      }else if(BDTInputVariable == "BM7"){ 
	BDTInputs["BM7"] = 0; 
      }else if(BDTInputVariable == "BM8"){ 
	BDTInputs["BM8"] = 0; 
      }else if(BDTInputVariable == "BM9"){ 
	BDTInputs["BM9"] = 0; 
      }else if(BDTInputVariable == "BM10"){ 
	BDTInputs["BM10"] = 0; 
      }else if(BDTInputVariable == "BM11"){ 
	BDTInputs["BM11"] = 0; 
      }else if(BDTInputVariable == "BM12"){ 
	BDTInputs["BM12"] = 0; 
      }else{
        std::map<std::string, double>::const_iterator BDTInput = AllVars_Map.find(BDTInputVariable);
        if ( BDTInput == AllVars_Map.end() )
          throw cmsException(__func__, __LINE__) << "Input variable = " << BDTInputVariable << " not in map given as function argument !!\n";
        //std::cout<<"Filling Map for Input Var.: " << BDTInputVariable << " with value " << BDTInput->second; << std::endl;
        BDTInputs[BDTInputVariable] = BDTInput->second;
      }
    }
  }else{
    for(unsigned int i = 0; i < BDTInputVariables.size(); i++){
      const std::string & BDTInputVariable = BDTInputVariables[i];
      if(BDTInputVariable == "gen_mHH"){ 
	BDTInputs["gen_mHH"] = 0; 
      }else{
        std::map<std::string, double>::const_iterator BDTInput = AllVars_Map.find(BDTInputVariable);
        if ( BDTInput == AllVars_Map.end() )
          throw cmsException(__func__, __LINE__) << "Input variable = " << BDTInputVariable << " not in map given as function argument !!\n";
        //std::cout<<"Filling Map for Input Var.: " << BDTInputVariable << " with value " << BDTInput->second; << std::endl;
        BDTInputs[BDTInputVariable] = BDTInput->second;
      }
    }
  }
  return BDTInputs;
}

std::string 
DoubleToUInt_Convertor(double BDT_param,
                       bool isNonRes,
                       const std::string & spin_label)
{
  std::string key;
  if ( !isNonRes )
  { 
    // resonant HH production
    key = Form("%1.0f", BDT_param);
  }
  else // Non-Resonant (Non SM BM Indices)
  {
    // non-resonant HH production (SM and non-SM coupling scenarios)
    key = Form("BM%i", TMath::Nint(BDT_param));
  }

  if ( !isNonRes && !spin_label.empty() )
  { 
    // add spin hypothesis to the output label
    key += spin_label;
  }
  return key;
}

std::map<std::string, std::map<std::string, double>>
CreateDNNOutputMap(const std::vector<double> & DNN_params,
		   TensorFlowInterface * DNN,
		   std::map<std::string, double> & DNNInputs,
		   int event_number,
		   bool isNonRes,
		   const std::string & spin_label)
{ 
  std::map<std::string, std::map<std::string, double>> retVal = CreateMVAOutputMap<TensorFlowInterface, std::map<std::string, double>>(
    DNN_params, DNN, DNNInputs, event_number, isNonRes, spin_label);
  return retVal;
}

std::map<std::string, std::map<std::string, double>>
CreateLBNOutputMap(const std::vector<double> & LBN_params,
                   std::vector<TensorFlowInterfaceLBN *>& LBN,
                   const std::map<std::string, const Particle*> & ll_particles,
                   std::map<std::string, double> & hl_mvaInputs,
                   int event_number,
                   bool isNonRes,
                   const std::string & label)
{
  std::map<std::string, std::map<std::string, double>> LBNOutput_Map;
  for ( size_t i = 0; i < LBN_params.size(); ++i ) // Loop over LBN_params: signal mass (Reso.)/BM index (Non Reso.)
  {
    std::string key;
    if ( !isNonRes )
    {
      // resonant case
      hl_mvaInputs["gen_mHH"] = LBN_params[i];
      key = DoubleToUInt_Convertor(LBN_params[i], isNonRes, label);
    }
    else
    {
      // non-resonant case
      if ( LBN_params[i] == 0 )
      {
        // SM
        key = "SM";
      }
      else
      {
        // non-SM coupling scenario
        key = Form("BM%i", TMath::Nint(LBN_params[i]));
      }
    }
    if ( event_number != -1 )
    {
      // use odd-even method
      LBNOutput_Map.insert(std::make_pair(key, (*LBN[i])(ll_particles, hl_mvaInputs, event_number)));
    }
    else
    {
      // use same LBN for all events
      LBNOutput_Map.insert(std::make_pair(key, (*LBN[i])(ll_particles, hl_mvaInputs)));
    }
  }
  return LBNOutput_Map;
}



std::map<std::string, std::map<std::string, double>>
CreateLBNOutputMap(const std::vector<double> & LBN_params,
		   TensorFlowInterfaceLBN * LBN,
                   const std::map<std::string, const Particle*> & ll_particles,
		   std::map<std::string, double> & hl_mvaInputs,
		   int event_number,
		   bool isNonRes,
		   const std::string & label)
{
  std::map<std::string, std::map<std::string, double>> LBNOutput_Map;
  for ( size_t i = 0; i < LBN_params.size(); ++i ) // Loop over LBN_params: signal mass (Reso.)/BM index (Non Reso.)
  { 
    std::string key;
    if ( !isNonRes )
    {
      // resonant case
      hl_mvaInputs["gen_mHH"] = LBN_params[i];
      key = DoubleToUInt_Convertor(LBN_params[i], isNonRes, label);
    }
    else 
    { 
      // non-resonant case
      if ( LBN_params[i] == 0 )
      {
        // SM
	hl_mvaInputs["SM"] = 1;  
	key = "SM";
      }
      else
      {
        // non-SM coupling scenario
	hl_mvaInputs["SM"] = 0;
        key = Form("BM%i", TMath::Nint(LBN_params[i]));
	hl_mvaInputs[key] = 1;   
	if ( i >= 2 )
        {
          std::string key_prev = Form("BM%i", TMath::Nint(LBN_params[i - 1]));
          hl_mvaInputs[key_prev] = 0; // Resetting the prev. hot encoder to zero
        }
      }
    }
    if ( event_number != -1 )
    { 
      // use odd-even method
      LBNOutput_Map.insert(std::make_pair(key, (*LBN)(ll_particles, hl_mvaInputs, event_number)));
    }
    else
    { 
      // use same LBN for all events
      LBNOutput_Map.insert(std::make_pair(key, (*LBN)(ll_particles, hl_mvaInputs)));
    }
  }
  return LBNOutput_Map;
}
