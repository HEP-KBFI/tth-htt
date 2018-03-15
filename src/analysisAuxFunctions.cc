#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader::kMEt_central, RecoMEtReader::kMEt_shifted_JetEnUp...

#include <TRandom3.h> // TRandom3
#include <TMath.h> // TMath::Nint()

#include <map> // std::map
#include <algorithm> // std::sort

bool isHigherPt(const Particle* particle1, const Particle* particle2)
{
  return (particle1->pt() > particle2->pt());
}

bool isHigherConePt(const RecoLepton* particle1, const RecoLepton* particle2)
{
  return (particle1->cone_pt() > particle2->cone_pt());
}

bool isHigherCSV(const RecoJet* jet1, const RecoJet* jet2)
{
  return (jet1 -> BtagCSV()) > (jet2 -> BtagCSV());
}

int
get_selection(const std::string & selectionString)
{
  if(selectionString == "Loose")    return kLoose;
  if(selectionString == "Fakeable") return kFakeable;
  if(selectionString == "Tight")    return kTight;
  std::cerr << "Invalid Configuration parameter for object selection = " << selectionString << " !!\n";
  throw 1;
}

int
get_era(const std::string & eraString)
{
  if(eraString == "2015") return kEra_2015;
  if(eraString == "2016") return kEra_2016;
  std::cerr  << "Invalid Configuration parameter 'era' = " << eraString << " !!\n";
  throw 1;
}

std::string getBranchName_bTagWeight(int era, const std::string& central_or_shift)
{
  int central_or_shift_int = kBtag_central;
  if      ( central_or_shift == "CMS_ttHl_btag_HFUp"         ) central_or_shift_int = kBtag_hfUp;
  else if ( central_or_shift == "CMS_ttHl_btag_HFDown"       ) central_or_shift_int = kBtag_hfDown;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats1Up"   ) central_or_shift_int = kBtag_hfStats1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats1Down" ) central_or_shift_int = kBtag_hfStats1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats2Up"   ) central_or_shift_int = kBtag_hfStats2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_HFStats2Down" ) central_or_shift_int = kBtag_hfStats2Down;
  else if ( central_or_shift == "CMS_ttHl_btag_LFUp"         ) central_or_shift_int = kBtag_lfUp;
  else if ( central_or_shift == "CMS_ttHl_btag_LFDown"       ) central_or_shift_int = kBtag_lfDown;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats1Up"   ) central_or_shift_int = kBtag_lfStats1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats1Down" ) central_or_shift_int = kBtag_lfStats1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats2Up"   ) central_or_shift_int = kBtag_lfStats2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_LFStats2Down" ) central_or_shift_int = kBtag_lfStats2Down;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr1Up"      ) central_or_shift_int = kBtag_cErr1Up;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr1Down"    ) central_or_shift_int = kBtag_cErr1Down;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr2Up"      ) central_or_shift_int = kBtag_cErr2Up;
  else if ( central_or_shift == "CMS_ttHl_btag_cErr2Down"    ) central_or_shift_int = kBtag_cErr2Down;
  else if ( central_or_shift == "CMS_ttHl_JESUp"             ) central_or_shift_int = kBtag_jesUp;
  else if ( central_or_shift == "CMS_ttHl_JESDown"           ) central_or_shift_int = kBtag_jesDown;
  return getBranchName_bTagWeight(era, central_or_shift_int);
}

std::string getBranchName_bTagWeight(int era, int central_or_shift)
{
  std::map<int, std::string> branchNames_bTagWeight;
  if ( era == kEra_2015 ) {
    branchNames_bTagWeight[kBtag_central]      = "Jet_bTagWeight";
    branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "HFUp";
    branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "HFDown";
    branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "HFStats1Up";
    branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "HFStats1Down";
    branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "HFStats2Up";
    branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "HFStats2Down";
    branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "LFUp";
    branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "LFDown";
    branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "LFStats1Up";
    branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "LFStats1Down";
    branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "LFStats2Up";
    branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "LFStats2Down";
    branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "cErr1Up";
    branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "cErr1Down";
    branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "cErr2Up";
    branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "cErr2Down";
    branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "JESUp";
    branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "JESDown";
  } else if ( era == kEra_2016 ) {
    branchNames_bTagWeight[kBtag_central]      = "Jet_btagWeightCSV";
    branchNames_bTagWeight[kBtag_hfUp]         = branchNames_bTagWeight[kBtag_central] + "_up_hf";
    branchNames_bTagWeight[kBtag_hfDown]       = branchNames_bTagWeight[kBtag_central] + "_down_hf";
    branchNames_bTagWeight[kBtag_hfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_up_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_down_hfstats1";
    branchNames_bTagWeight[kBtag_hfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_up_hfstats2";
    branchNames_bTagWeight[kBtag_hfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_down_hfstats2";
    branchNames_bTagWeight[kBtag_lfUp]         = branchNames_bTagWeight[kBtag_central] + "_up_lf";
    branchNames_bTagWeight[kBtag_lfDown]       = branchNames_bTagWeight[kBtag_central] + "_down_lf";
    branchNames_bTagWeight[kBtag_lfStats1Up]   = branchNames_bTagWeight[kBtag_central] + "_up_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats1Down] = branchNames_bTagWeight[kBtag_central] + "_down_lfstats1";
    branchNames_bTagWeight[kBtag_lfStats2Up]   = branchNames_bTagWeight[kBtag_central] + "_up_lfstats2";
    branchNames_bTagWeight[kBtag_lfStats2Down] = branchNames_bTagWeight[kBtag_central] + "_down_lfstats2";
    branchNames_bTagWeight[kBtag_cErr1Up]      = branchNames_bTagWeight[kBtag_central] + "_up_cferr1";
    branchNames_bTagWeight[kBtag_cErr1Down]    = branchNames_bTagWeight[kBtag_central] + "_down_cferr1";
    branchNames_bTagWeight[kBtag_cErr2Up]      = branchNames_bTagWeight[kBtag_central] + "_up_cferr2";
    branchNames_bTagWeight[kBtag_cErr2Down]    = branchNames_bTagWeight[kBtag_central] + "_down_cferr2";
    branchNames_bTagWeight[kBtag_jesUp]        = branchNames_bTagWeight[kBtag_central] + "_up_jes";
    branchNames_bTagWeight[kBtag_jesDown]      = branchNames_bTagWeight[kBtag_central] + "_down_jes";
  } else assert(0);
  std::map<int, std::string>::const_iterator branchName_bTagWeight = branchNames_bTagWeight.find(central_or_shift);
  assert(branchName_bTagWeight != branchNames_bTagWeight.end());
  return branchName_bTagWeight->second;
}

std::string
getBranchName_MEt(int,
                  const std::string & default_branchName,
                  int central_or_shift)
{
  std::string branchName = default_branchName; // copy
  switch(central_or_shift)
  {
    case RecoMEtReader::kMEt_central:                                                               break;
    case RecoMEtReader::kMEt_shifted_JetEnUp:           branchName += "_shifted_JetEnUp";           break;
    case RecoMEtReader::kMEt_shifted_JetEnDown:         branchName += "_shifted_JetEnDown";         break;
    case RecoMEtReader::kMEt_shifted_JetResUp:          branchName += "_shifted_JetResUp";          break;
    case RecoMEtReader::kMEt_shifted_JetResDown:        branchName += "_shifted_JetResDown";        break;
    case RecoMEtReader::kMEt_shifted_UnclusteredEnUp:   branchName += "_shifted_UnclusteredEnUp";   break;
    case RecoMEtReader::kMEt_shifted_UnclusteredEnDown: branchName += "_shifted_UnclusteredEnDown"; break;
    default:
    {
      std::cerr << "Invalid met correction: " << central_or_shift << '\n';
      throw 1;
    }
  }
  return branchName;
}

int getHadTau_genPdgId(const RecoHadTau* hadTau)
{
  int hadTau_genPdgId = -1;
  if      ( hadTau->genHadTau() ) hadTau_genPdgId = 15;
  else if ( hadTau->genLepton() ) hadTau_genPdgId = std::abs(hadTau->genLepton()->pdgId());
  return hadTau_genPdgId;
}

Particle::LorentzVector compMHT(const std::vector<const RecoLepton*>& leptons, const std::vector<const RecoHadTau*>& hadTaus, const std::vector<const RecoJet*>& jets)
{
  math::PtEtaPhiMLorentzVector mht_p4(0,0,0,0);
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    mht_p4 += (*lepton)->p4();
  }
  for ( std::vector<const RecoHadTau*>::const_iterator hadTau = hadTaus.begin();
	hadTau != hadTaus.end(); ++hadTau ) {
    mht_p4 += (*hadTau)->p4();
  }
  for ( std::vector<const RecoJet*>::const_iterator jet = jets.begin();
	jet != jets.end(); ++jet ) {
    mht_p4 += (*jet)->p4();
  }
  return mht_p4;
}

double compMEt_LD(const Particle::LorentzVector& met_p4, const Particle::LorentzVector& mht_p4)
{
  double met_LD = met_coef*met_p4.pt() + mht_coef*mht_p4.pt();
  return met_LD;
}

std::vector<const RecoLepton*> mergeLeptonCollections(const std::vector<const RecoElectron*>& electrons, const std::vector<const RecoMuon*>& muons)
{
  std::vector<const RecoLepton*> leptons;
  size_t nLeptons = electrons.size() + muons.size();
  if ( nLeptons > 0 ) {
    leptons.reserve(nLeptons);
    leptons.insert(leptons.end(), electrons.begin(), electrons.end());
    leptons.insert(leptons.end(), muons.begin(), muons.end());
    std::sort(leptons.begin(), leptons.end(), isHigherPt);
  }
  return leptons;
}

void printGenLeptonCollection(const std::string& collection_name, const std::vector<GenLepton>& genLeptons)
{
  std::cout << " (#" << collection_name << " = " << genLeptons.size() << ")" << std::endl;
  for ( size_t idxGenLepton = 0; idxGenLepton < genLeptons.size(); ++idxGenLepton ) {
    std::cout << collection_name << "  #" << idxGenLepton << ":" << std::endl;
    std::cout << genLeptons[idxGenLepton];
  }
}

void printLeptonCollection(const std::string& collection_name, const std::vector<const RecoLepton*>& leptons)
{
  std::cout << " (#" << collection_name << " = " << leptons.size() << ")" << std::endl;
  for ( size_t idxLepton = 0; idxLepton < leptons.size(); ++idxLepton ) {
    std::cout << collection_name << "  #" << idxLepton << ":" << std::endl;
    const RecoElectron* electron = dynamic_cast<const RecoElectron*>(leptons[idxLepton]);
    if ( electron ) {
      std::cout << (*electron);
      continue;
    }
    const RecoMuon* muon = dynamic_cast<const RecoMuon*>(leptons[idxLepton]);
    if ( muon ) {
      std::cout << (*muon);
      continue;
    }
    std::cout << (*leptons[idxLepton]);
  }
}

void printGenHadTauCollection(const std::string& collection_name, const std::vector<GenHadTau>& genHadTaus)
{
  std::cout << " (#" << collection_name << " = " << genHadTaus.size() << ")" << std::endl;
  for ( size_t idxGenHadTau = 0; idxGenHadTau < genHadTaus.size(); ++idxGenHadTau ) {
    std::cout << collection_name << "  #" << idxGenHadTau << ":" << std::endl;
    std::cout << genHadTaus[idxGenHadTau];
  }
}

void printHadTauCollection(const std::string& collection_name, const std::vector<const RecoHadTau*>& hadTaus)
{
  std::cout << " (#" << collection_name << " = " << hadTaus.size() << ")" << std::endl;
  for ( size_t idxHadTau = 0; idxHadTau < hadTaus.size(); ++idxHadTau ) {
    std::cout << collection_name << "  #" << idxHadTau << ":" << std::endl;
    std::cout << (*hadTaus[idxHadTau]);
  }
}

void printGenJetCollection(const std::string& collection_name, const std::vector<GenJet>& genJets)
{
  std::cout << " (#" << collection_name << " = " << genJets.size() << ")" << std::endl;
  for ( size_t idxGenJet = 0; idxGenJet < genJets.size(); ++idxGenJet ) {
    std::cout << collection_name << "  #" << idxGenJet << ":" << std::endl;
    std::cout << genJets[idxGenJet];
  }
}

void printJetCollection(const std::string& collection_name, const std::vector<const RecoJet*>& jets)
{
  std::cout << " (#" << collection_name << " = " << jets.size() << ")" << std::endl;
  for ( size_t idxJet = 0; idxJet < jets.size(); ++idxJet ) {
    std::cout << collection_name << "  #" << idxJet << ":" << std::endl;
    std::cout << (*jets[idxJet]);
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

double comp_mvaOutput_Hj_tagger(const RecoJet* jet,
                                const std::vector<const RecoLepton*>& leptons,
                                std::map<std::string, double>& mvaInputs_Hj_tagger,
                                TMVAInterface& mva_Hj_tagger,
                                const EventInfo & eventInfo)
{
  double dRmin_lepton = -1.;
  double dRmax_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(jet->eta(), jet->phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) dRmin_lepton = dR;
    if ( dRmax_lepton == -1. || dR > dRmax_lepton ) dRmax_lepton = dR;
  }

  mvaInputs_Hj_tagger["Jet_lepdrmin"] = dRmin_lepton;
  mvaInputs_Hj_tagger["max(Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags,0.)"] = std::max(0., jet->BtagCSV());
  mvaInputs_Hj_tagger["max(Jet_qg,0.)"] = std::max(0., jet->QGDiscr());
  mvaInputs_Hj_tagger["Jet_lepdrmax"] = dRmax_lepton;
  mvaInputs_Hj_tagger["Jet_pt"] = jet->pt();

  check_mvaInputs(mvaInputs_Hj_tagger, eventInfo);

  double mvaOutput_Hj_tagger = mva_Hj_tagger(mvaInputs_Hj_tagger);
  return mvaOutput_Hj_tagger;
}

double comp_mvaOutput_Hjj_tagger(const RecoJet* jet1, const RecoJet* jet2, const std::vector<const RecoJet*>& jets,
				 const std::vector<const RecoLepton*>& leptons,
				 std::map<std::string, double>& mvaInputs_Hjj_tagger, TMVAInterface& mva_Hjj_tagger,
				 std::map<std::string, double>& mvaInputs_Hj_tagger, TMVAInterface& mva_Hj_tagger,
                 const EventInfo & eventInfo)
{
  double jet1_mvaOutput_Hj_tagger = comp_mvaOutput_Hj_tagger(
    jet1, leptons,
    mvaInputs_Hj_tagger, mva_Hj_tagger,
    eventInfo);
  double jet2_mvaOutput_Hj_tagger = comp_mvaOutput_Hj_tagger(
    jet2, leptons,
    mvaInputs_Hj_tagger, mva_Hj_tagger,
    eventInfo);
  Particle::LorentzVector dijetP4 = jet1->p4() + jet2->p4();
  const RecoLepton* lepton_nearest = 0;
  double dRmin_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(dijetP4.eta(), dijetP4.phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) {
      lepton_nearest = (*lepton);
      dRmin_lepton = dR;
    }
  }
  double dRmin_jet_other = -1.;
  double dRmax_jet_other = -1.;
  for ( std::vector<const RecoJet*>::const_iterator jet_other = jets.begin();
	jet_other != jets.end(); ++jet_other ) {
    if ( (*jet_other) == jet1 || (*jet_other) == jet2 ) continue;
    double dR = deltaR(dijetP4.eta(), dijetP4.phi(), (*jet_other)->eta(), (*jet_other)->phi());
    if ( dRmin_jet_other == -1. || dR < dRmin_jet_other ) dRmin_jet_other = dR;
    if ( dRmax_jet_other == -1. || dR > dRmax_jet_other ) dRmax_jet_other = dR;
  }
  mvaInputs_Hjj_tagger["bdtJetPair_minlepmass"] = ( lepton_nearest ) ? (dijetP4 + lepton_nearest->p4()).mass() : 0.;
  mvaInputs_Hjj_tagger["bdtJetPair_sumbdt"] = jet1_mvaOutput_Hj_tagger + jet2_mvaOutput_Hj_tagger;
  mvaInputs_Hjj_tagger["bdtJetPair_dr"] = deltaR(jet1->eta(), jet1->phi(), jet2->eta(), jet2->phi());
  mvaInputs_Hjj_tagger["bdtJetPair_minjdr"] = dRmin_jet_other;
  mvaInputs_Hjj_tagger["bdtJetPair_mass"] = dijetP4.mass();
  mvaInputs_Hjj_tagger["bdtJetPair_minjOvermaxjdr"] = ( dRmax_jet_other > 0. ) ? dRmin_jet_other/dRmax_jet_other : 1.;

  check_mvaInputs(mvaInputs_Hjj_tagger, eventInfo);

  double mvaOutput_Hjj_tagger = mva_Hjj_tagger(mvaInputs_Hjj_tagger);
  return mvaOutput_Hjj_tagger;
}
