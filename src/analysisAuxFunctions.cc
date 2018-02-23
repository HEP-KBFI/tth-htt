#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader::kMEt_*
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

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


std::string
getBranchName_bTagWeight(int era,
                         const std::string & central_or_shift)
{
  int central_or_shift_int = kBtag_central;
  if     (central_or_shift == "CMS_ttHl_btag_HFUp"        ) central_or_shift_int = kBtag_hfUp;
  else if(central_or_shift == "CMS_ttHl_btag_HFDown"      ) central_or_shift_int = kBtag_hfDown;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats1Up"  ) central_or_shift_int = kBtag_hfStats1Up;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats1Down") central_or_shift_int = kBtag_hfStats1Down;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats2Up"  ) central_or_shift_int = kBtag_hfStats2Up;
  else if(central_or_shift == "CMS_ttHl_btag_HFStats2Down") central_or_shift_int = kBtag_hfStats2Down;
  else if(central_or_shift == "CMS_ttHl_btag_LFUp"        ) central_or_shift_int = kBtag_lfUp;
  else if(central_or_shift == "CMS_ttHl_btag_LFDown"      ) central_or_shift_int = kBtag_lfDown;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats1Up"  ) central_or_shift_int = kBtag_lfStats1Up;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats1Down") central_or_shift_int = kBtag_lfStats1Down;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats2Up"  ) central_or_shift_int = kBtag_lfStats2Up;
  else if(central_or_shift == "CMS_ttHl_btag_LFStats2Down") central_or_shift_int = kBtag_lfStats2Down;
  else if(central_or_shift == "CMS_ttHl_btag_cErr1Up"     ) central_or_shift_int = kBtag_cErr1Up;
  else if(central_or_shift == "CMS_ttHl_btag_cErr1Down"   ) central_or_shift_int = kBtag_cErr1Down;
  else if(central_or_shift == "CMS_ttHl_btag_cErr2Up"     ) central_or_shift_int = kBtag_cErr2Up;
  else if(central_or_shift == "CMS_ttHl_btag_cErr2Down"   ) central_or_shift_int = kBtag_cErr2Down;
  else if(central_or_shift == "CMS_ttHl_JESUp"            ) central_or_shift_int = kBtag_jesUp;
  else if(central_or_shift == "CMS_ttHl_JESDown"          ) central_or_shift_int = kBtag_jesDown;
  return getBranchName_bTagWeight(era, central_or_shift_int);
}

std::string
getBranchName_bTagWeight(int era,
                         int central_or_shift)
{
  std::map<int, std::string> branchNames_bTagWeight;
  if(era == kEra_2017)
  {
    branchNames_bTagWeight[kBtag_central]      = "Jet_btagSF_csvv2";
    branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "_shape_up_hf";
    branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "_shape_down_hf";
    branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_hfstats2";
    branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_hfstats2";
    branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "_shape_up_lf";
    branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "_shape_down_lf";
    branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_shape_up_lfstats2";
    branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_shape_down_lfstats2";
    branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "_shape_up_cferr1";
    branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "_shape_down_cferr1";
    branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "_shape_up_cferr2";
    branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "_shape_down_cferr2";
    branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "_shape_up_jes";
    branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "_shape_down_jes";
  }
  else
  {
    assert(0);
  }
  assert(branchNames_bTagWeight.count(central_or_shift));
  return branchNames_bTagWeight.at(central_or_shift);
}

std::string
getBranchName_MEt(int,
                  const std::string & default_branchName,
                  int central_or_shift)
{
  std::string branchName = default_branchName; // copy
  switch(central_or_shift)
  {
    case RecoMEtReader::kMEt_central:                                                   break;
    case RecoMEtReader::kMEt_shifted_JetEnUp:           branchName += "_jesTotalUp";    break; // JetEnUp
    case RecoMEtReader::kMEt_shifted_JetEnDown:         branchName += "_jesTotalDown";  break; // JetEnDown
    case RecoMEtReader::kMEt_shifted_JetResUp:          branchName += "_jerUp";         break;
    case RecoMEtReader::kMEt_shifted_JetResDown:        branchName += "_jerDown";       break;
    case RecoMEtReader::kMEt_shifted_UnclusteredEnUp:   branchName += "_unclustEnUp";   break;
    case RecoMEtReader::kMEt_shifted_UnclusteredEnDown: branchName += "_unclustEnDown"; break;
    default:
    {
      std::cerr << "Invalid met correction: " << central_or_shift << '\n';
      throw 1;
    }
  }
  return branchName;
}

int
getHadTau_genPdgId(const RecoHadTau * hadTau)
{
  int hadTau_genPdgId = -1;
  if     (hadTau->genHadTau()) hadTau_genPdgId = 15;
  else if(hadTau->genLepton()) hadTau_genPdgId = std::abs(hadTau->genLepton()->pdgId());
  return hadTau_genPdgId;
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
mergeLeptonCollections(const std::vector<const RecoElectron *> & electrons,
                       const std::vector<const RecoMuon *> & muons)
{ 
  std::vector<const RecoLepton *> leptons;
  const std::size_t nLeptons = electrons.size() + muons.size();
  if(nLeptons > 0)
  {
    leptons.reserve(nLeptons);
    leptons.insert(leptons.end(), electrons.begin(), electrons.end());
    leptons.insert(leptons.end(), muons.begin(), muons.end());
    std::sort(leptons.begin(), leptons.end(), isHigherPt);
  }
  return leptons;
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
