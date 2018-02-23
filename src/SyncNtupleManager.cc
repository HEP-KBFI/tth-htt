#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // comp_lep*_conePt()

#include <TFile.h> // TFile

#include <boost/algorithm/string/predicate.hpp> // boost::starts_with()

#include <algorithm> // std::min()

const Int_t SyncNtupleManager::placeholder_value = -9999;

SyncNtupleManager::SyncNtupleManager(const std::string & outputFileName,
                                     const std::string & outputTreeName)
  : outputFile(new TFile(outputFileName.c_str(), "recreate"))
  , outputTree(new TTree(outputTreeName.c_str(), outputTreeName.c_str()))
  , nof_mus(2)
  , nof_eles(2)
  , nof_taus(2)
  , nof_jets(4)
{
  for(int var = FloatVariableType::PFMET; var <= FloatVariableType::lumiScale; ++var)
  {
    floatMap[static_cast<FloatVariableType>(var)] = placeholder_value;
  }
}

SyncNtupleManager::~SyncNtupleManager()
{
  outputFile -> Close();
  delete outputFile;
  outputTree = nullptr;
  outputFile = nullptr;
}

void
SyncNtupleManager::initializeBranches()
{
  const char * mstr = "mu";
  const char * estr = "ele";
  const char * tstr = "tau";
  const char * jstr = "jet";

  const std::string n_presel_mu_str       = Form("n_presel_%s",      mstr);
  const std::string n_fakeablesel_mu_str  = Form("n_fakeablesel_%s", mstr);
  const std::string n_cutsel_mu_str       = Form("n_cutsel_%s",      mstr);
  const std::string n_mvasel_mu_str       = Form("n_mvasel_%s",      mstr);
  const std::string n_presel_ele_str      = Form("n_presel_%s",      estr);
  const std::string n_fakeablesel_ele_str = Form("n_fakeablesel_%s", estr);
  const std::string n_cutsel_ele_str      = Form("n_cutsel_%s",      estr);
  const std::string n_mvasel_ele_str      = Form("n_mvasel_%s",      estr);
  const std::string n_presel_tau_str      = Form("n_presel_%s",      tstr);
  const std::string n_presel_jet_str      = Form("n_presel_%s",      jstr);

  setBranches(
    nEvent,            "nEvent",
    ls,                "ls",
    run,               "run",
    n_presel_mu,       n_presel_mu_str,
    n_fakeablesel_mu,  n_fakeablesel_mu_str,
    n_cutsel_mu,       n_cutsel_mu_str,
    n_mvasel_mu,       n_mvasel_mu_str,
    n_presel_ele,      n_presel_ele_str,
    n_fakeablesel_ele, n_fakeablesel_ele_str,
    n_cutsel_ele,      n_cutsel_ele_str,
    n_mvasel_ele,      n_mvasel_ele_str,
    n_presel_tau,      n_presel_tau_str,
    n_presel_jet,      n_presel_jet_str,
    floatMap[FloatVariableType::PFMET],            "PFMET",
    floatMap[FloatVariableType::PFMETphi],         "PFMETphi",
    floatMap[FloatVariableType::MHT],              "MHT",
    floatMap[FloatVariableType::metLD],            "metLD",
    floatMap[FloatVariableType::mvaOutput_ttV],    "MVA_2lss_ttV",
    floatMap[FloatVariableType::mvaOutput_ttbar],  "MVA_2lss_ttbar",
    floatMap[FloatVariableType::MC_weight],        "MC_weight",
    floatMap[FloatVariableType::FR_weight],        "FR_weight",
    floatMap[FloatVariableType::triggerSF_weight], "triggerSF_weight",
    floatMap[FloatVariableType::leptonSF_weight],  "leptonSF_weight",
    floatMap[FloatVariableType::bTagSF_weight],    "bTagSF_weight",
    floatMap[FloatVariableType::PU_weight],        "PU_weight",
    floatMap[FloatVariableType::hadTauSF_weight],  "hadTauSF_weight",
    floatMap[FloatVariableType::genWeight],        "genWeight",
    floatMap[FloatVariableType::lumiScale],        "lumiScale",
    lep0_conept,       "lep0_conept",
    lep1_conept,       "lep1_conept",
    mindr_lep0_jet,    "mindr_lep0_jet",
    mindr_lep1_jet,    "mindr_lep1_jet",
    MT_met_lep0,       "MT_met_lep0",
    avg_dr_jet,        "avg_dr_jet",
    n_jet25_recl,      "n_jet25_recl"
  );

  setBranches(
    mstr, nof_mus,
    mu_pt,                   "pt",
    mu_eta,                  "eta",
    mu_phi,                  "phi",
    mu_E,                    "E",
    mu_charge,               "charge",
    mu_miniRelIso,           "miniRelIso",
    mu_miniIsoCharged,       "miniIsoCharged",
    mu_miniIsoNeutral,       "miniIsoNeutral",
    mu_jetPtRatio,           "jetPtRatio",
    mu_jetCSV,               "jetCSV",
    mu_sip3D,                "sip3D",
    mu_dxy,                  "dxy",
    mu_dz,                   "dz",
    mu_segmentCompatibility, "segmentCompatibility",
    mu_leptonMVA,            "leptonMVA",
    mu_conept,               "conept",
    mu_mediumID,             "mediumID",
    mu_isfakeablesel,        "isfakeablesel",
    mu_iscutsel,             "iscutsel",
    mu_ismvasel,             "ismvasel"
  );

  setBranches(
    estr, nof_eles,
    ele_pt,                   "pt",
    ele_eta,                  "eta",
    ele_phi,                  "phi",
    ele_E,                    "E",
    ele_charge,               "charge",
    ele_miniRelIso,           "miniRelIso",
    ele_miniIsoCharged,       "miniIsoCharged",
    ele_miniIsoNeutral,       "miniIsoNeutral",
    ele_jetPtRatio,           "jetPtRatio",
    ele_jetCSV,               "jetCSV",
    ele_sip3D,                "sip3D",
    ele_dxy,                  "dxy",
    ele_dz,                   "dz",
    ele_ntMVAeleID,           "ntMVAeleID",
    ele_leptonMVA,            "leptonMVA",
    ele_conept,               "conept",
    ele_isChargeConsistent,   "isChargeConsistent",
    ele_passesConversionVeto, "passesConversionVeto",
    ele_nMissingHits,         "nMissingHits",
    ele_isfakeablesel,        "isfakeablesel",
    ele_iscutsel,             "iscutsel",
    ele_ismvasel,             "ismvasel"
  );

  setBranches(
    tstr, nof_taus,
    tau_pt,                                              "pt",
    tau_eta,                                             "eta",
    tau_phi,                                             "phi",
    tau_E,                                               "E",
    tau_charge,                                          "charge",
    tau_dxy,                                             "dxy",
    tau_dz,                                              "dz",
    tau_decayModeFindingOldDMs,                          "decayModeFindingOldDMs",
    tau_decayModeFindingNewDMs,                          "decayModeFindingNewDMs",
    tau_byCombinedIsolationDeltaBetaCorr3Hits,           "byCombinedIsolationDeltaBetaCorr3Hits",
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits,      "byLooseCombinedIsolationDeltaBetaCorr3Hits",
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits,     "byMediumCombinedIsolationDeltaBetaCorr3Hits",
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits,      "byTightCombinedIsolationDeltaBetaCorr3Hits",
    tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,  "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",
    tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",
    tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,  "byTightCombinedIsolationDeltaBetaCorr3HitsdR03",
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT,         "byLooseIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT,        "byMediumIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT,         "byTightIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT,        "byVTightIsolationMVArun2v1DBdR03oldDMwLT",
    tau_againstMuonLoose3,                               "againstMuonLoose3",
    tau_againstMuonTight3,                               "againstMuonTight3",
    tau_againstElectronVLooseMVA6,                       "againstElectronVLooseMVA6",
    tau_againstElectronLooseMVA6,                        "againstElectronLooseMVA6",
    tau_againstElectronMediumMVA6,                       "againstElectronMediumMVA6",
    tau_againstElectronTightMVA6,                        "againstElectronTightMVA6",
    tau_againstElectronVTightMVA6,                       "againstElectronVTightMVA6"
  );

  setBranches(
    jstr, nof_jets,
    jet_pt,           "pt",
    jet_eta,          "eta",
    jet_phi,          "phi",
    jet_E,            "E",
    jet_CSV,          "CSV",
    jet_heppyFlavour, "heppyFlavour"
  );

  reset(true);
}

void
SyncNtupleManager::initializeHLTBranches(const std::vector<std::vector<hltPath *>> & hltPaths)
{
  for(const auto & hltVector: hltPaths)
  {
    for(const auto & hlt: hltVector)
    {
      hltMap[hlt -> getBranchName()] = -1;
    }
  }
  for(auto & kv: hltMap)
  {
    setBranches(hltMap[kv.first], kv.first);
  }
}

void
SyncNtupleManager::readRunLumiEvent(UInt_t run_,
                                    UInt_t lumi_,
                                    ULong64_t event_)
{
  nEvent = event_;
  ls = lumi_;
  run = run_;
}

void
SyncNtupleManager::readRunLumiEvent(const EventInfo & eventInfo)
{
  return readRunLumiEvent(eventInfo.run, eventInfo.lumi, eventInfo.event);
}

void
SyncNtupleManager::read(const std::vector<const RecoMuon *> & muons,
                        const std::vector<const RecoMuon *> & fakeable_muons,
                        const std::vector<const RecoMuon *> & cutbased_muons,
                        const std::vector<const RecoMuon *> & mvabased_muons)
{
  n_presel_mu = muons.size();
  n_fakeablesel_mu = fakeable_muons.size();
  n_cutsel_mu = cutbased_muons.size();
  n_mvasel_mu = mvabased_muons.size();

  const Int_t nof_iterations = std::min(n_presel_mu, nof_mus);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoMuon * const muon = muons[i];
    mu_pt[i] = muon -> pt();
    mu_eta[i] = muon -> eta();
    mu_phi[i] = muon -> phi();
    mu_E[i] = (muon -> p4()).E();
    mu_charge[i] = muon -> charge();
    mu_miniRelIso[i] = muon -> relIso();
    mu_miniIsoCharged[i] = muon -> miniIsoCharged();
    mu_miniIsoNeutral[i] = muon -> miniIsoNeutral();
    mu_jetPtRatio[i] = muon -> jetPtRatio();
    mu_jetCSV[i] = muon -> jetBtagCSV();
    mu_sip3D[i] = muon -> sip3d();
    mu_dxy[i] = muon -> dxy();
    mu_dz[i] = muon -> dz();
    mu_segmentCompatibility[i] = muon -> segmentCompatibility();
    mu_leptonMVA[i] = muon -> mvaRawTTH();
    mu_conept[i] = comp_lep1_conePt(*muon);
    mu_mediumID[i] = muon -> passesMediumIdPOG();

    mu_isfakeablesel[i] = 0;
    for(const auto & fakeable_muon: fakeable_muons)
    {
      if(muon == fakeable_muon)
      {
        mu_isfakeablesel[i] = 1;
        break;
      }
    }
    mu_iscutsel[i] = 0;
    for(const auto & cutbased_muon: cutbased_muons)
    {
      if(muon == cutbased_muon)
      {
        mu_iscutsel[i] = 1;
        break;
      }
    }
    mu_ismvasel[i] = 0;
    for(const auto & mvabased_muon: mvabased_muons)
    {
      if(muon == mvabased_muon)
      {
        mu_ismvasel[i] = 1;
        break;
      }
    }
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoElectron *> & electrons,
                        const std::vector<const RecoElectron *> & fakeable_electrons,
                        const std::vector<const RecoElectron *> & cutbased_electrons,
                        const std::vector<const RecoElectron *> & mvabased_electrons)
{
  n_presel_ele = electrons.size();
  n_fakeablesel_ele = fakeable_electrons.size();
  n_cutsel_ele = cutbased_electrons.size();
  n_mvasel_ele = mvabased_electrons.size();

  const Int_t nof_iterations = std::min(n_presel_ele, nof_eles);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoElectron * const electron = electrons[i];
    ele_pt[i] = electron -> pt();
    ele_eta[i] = electron -> eta();
    ele_phi[i] = electron -> phi();
    ele_E[i] = (electron -> p4()).E();
    ele_charge[i] = electron -> charge();
    ele_miniRelIso[i] = electron -> relIso();
    ele_miniIsoCharged[i] = electron -> miniIsoCharged();
    ele_miniIsoNeutral[i] = electron -> miniIsoNeutral();
    ele_jetPtRatio[i] = electron -> jetPtRatio();
    ele_jetCSV[i] = electron -> jetBtagCSV();
    ele_sip3D[i] = electron -> sip3d();
    ele_dxy[i] = electron -> dxy();
    ele_dz[i] = electron -> dz();
    ele_ntMVAeleID[i] = electron -> mvaRawPOG_HZZ();
    ele_leptonMVA[i] = electron -> mvaRawTTH();
    ele_conept[i] = comp_lep1_conePt(*electron);
    ele_isChargeConsistent[i] = electron -> tightCharge() == 2 ? 1 : 0;
    ele_passesConversionVeto[i] = electron -> passesConversionVeto();
    ele_nMissingHits[i] = electron -> nLostHits();

    ele_isfakeablesel[i] = 0;
    for(const auto & fakeable_electron: fakeable_electrons)
    {
      if(electron == fakeable_electron)
      {
        ele_isfakeablesel[i] = 1;
        break;
      }
    }
    ele_iscutsel[i] = 0;
    for(const auto & cutbased_electron: cutbased_electrons)
    {
      if(electron == cutbased_electron)
      {
        ele_iscutsel[i] = 1;
        break;
      }
    }
    ele_ismvasel[i] = 0;
    for(const auto & mvabased_electron: mvabased_electrons)
    {
      if(electron == mvabased_electron)
      {
        ele_ismvasel[i] = 1;
        break;
      }
    }
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoHadTau *> & hadtaus)
{
  n_presel_tau = hadtaus.size();
  const Int_t nof_iterations = std::min(n_presel_tau, nof_taus);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoHadTau * const hadtau = hadtaus[i];
    tau_pt[i] = hadtau -> pt();
    tau_eta[i] = hadtau -> eta();
    tau_phi[i] = hadtau -> phi();
    tau_E[i] = (hadtau -> p4()).E();
    tau_charge[i] = hadtau -> charge();
    tau_dxy[i] = hadtau -> dxy();
    tau_dz[i] = hadtau -> dz();
    tau_decayModeFindingOldDMs[i] = hadtau -> decayModeFinding();
    tau_decayModeFindingNewDMs[i] = hadtau -> decayModeFindingNew();

    const Int_t idCI3hit = hadtau -> id_cut_dR05();
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 1 ? 1 : 0;
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 2 ? 1 : 0;
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 3 ? 1 : 0;

    const Int_t idCI3hitdR03 = hadtau -> id_cut_dR03();
    tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 1 ? 1 : 0;
    tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 2 ? 1 : 0;
    tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 3 ? 1 : 0;

    const Int_t idMVArun2dR03 = hadtau -> id_mva_dR03();
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 3 ? 1 : 0;
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 4 ? 1 : 0;
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 5 ? 1 : 0;
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 6 ? 1 : 0;

    const Int_t idAntiMu = hadtau -> antiMuon();
    tau_againstMuonLoose3[i] = idAntiMu >= 1 ? 1 : 0;
    tau_againstMuonTight3[i] = idAntiMu >= 2 ? 1 : 0;

    const Int_t idAntiErun2 = hadtau -> antiElectron();
    tau_againstElectronVLooseMVA6[i] = idAntiErun2 >= 1 ? 1 : 0;
    tau_againstElectronLooseMVA6[i] = idAntiErun2 >= 2 ? 1 : 0;
    tau_againstElectronMediumMVA6[i] = idAntiErun2 >= 3 ? 1 : 0;
    tau_againstElectronTightMVA6[i] = idAntiErun2 >= 4 ? 1 : 0;
    tau_againstElectronVTightMVA6[i] = idAntiErun2 >= 5 ? 1 : 0;
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoJet *> & jets)
{
  n_presel_jet = jets.size();
  const Int_t nof_iterations = std::min(n_presel_jet, nof_jets);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoJet * const jet = jets[i];
    jet_pt[i] = jet -> pt();
    jet_eta[i] = jet -> eta();
    jet_phi[i] = jet -> phi();
    jet_E[i] = (jet -> p4()).E();
    jet_CSV[i] = jet -> BtagCSV();
    jet_heppyFlavour[i] = jet -> heppyFlavour();
  }
}

void
SyncNtupleManager::read(const std::map<std::string, Double_t> & mvaInputs)
{
  if(mvaInputs.find("LepGood_conePt[iF_Recl[0]]") != mvaInputs.end()) lep0_conept    = static_cast<decltype(lep0_conept)>   (mvaInputs.at("LepGood_conePt[iF_Recl[0]]"));
  if(mvaInputs.find("LepGood_conePt[iF_Recl[1]]") != mvaInputs.end()) lep1_conept    = static_cast<decltype(lep1_conept)>   (mvaInputs.at("LepGood_conePt[iF_Recl[1]]"));
  if(mvaInputs.find("mindr_lep1_jet")             != mvaInputs.end()) mindr_lep0_jet = static_cast<decltype(mindr_lep0_jet)>(mvaInputs.at("mindr_lep1_jet"));
  if(mvaInputs.find("mindr_lep2_jet")             != mvaInputs.end()) mindr_lep1_jet = static_cast<decltype(mindr_lep1_jet)>(mvaInputs.at("mindr_lep2_jet"));
  if(mvaInputs.find("MT_met_lep1")                != mvaInputs.end()) MT_met_lep0    = static_cast<decltype(MT_met_lep0)>   (mvaInputs.at("MT_met_lep1"));
  if(mvaInputs.find("avg_dr_jet")                 != mvaInputs.end()) avg_dr_jet     = static_cast<decltype(avg_dr_jet)>    (mvaInputs.at("avg_dr_jet"));
  if(mvaInputs.find("nJet25_Recl")                != mvaInputs.end()) n_jet25_recl   = static_cast<decltype(n_jet25_recl)>  (mvaInputs.at("nJet25_Recl"));
}

void
SyncNtupleManager::read(Float_t value,
                        FloatVariableType type)
{
  floatMap[type] = value;
}

void
SyncNtupleManager::read(const std::vector<std::vector<hltPath *>> & hltPaths)
{
  for(const auto & hltVector: hltPaths)
  {
    for(const auto & hlt: hltVector)
    {
      hltMap[hlt -> getBranchName()] = hlt -> getValue();
    }
  }
}

void
SyncNtupleManager::reset(bool is_initializing)
{
  nEvent = 0;
  ls = 0;
  run = 0;

  reset(
    n_presel_mu,
    n_fakeablesel_mu,
    n_cutsel_mu,
    n_mvasel_mu,
    n_presel_ele,
    n_fakeablesel_ele,
    n_cutsel_ele,
    n_mvasel_ele,
    n_presel_tau,
    n_presel_jet,
    lep0_conept,
    lep1_conept,
    mindr_lep0_jet,
    mindr_lep1_jet,
    MT_met_lep0,
    avg_dr_jet,
    n_jet25_recl
  );

  for(auto & kv: floatMap)
  {
    kv.second = placeholder_value;
  }

  const Int_t nof_mu_iterations = is_initializing ? nof_mus : std::min(n_presel_mu, nof_mus);
  reset(
    nof_mu_iterations,
    mu_pt,
    mu_eta,
    mu_phi,
    mu_E,
    mu_charge,
    mu_miniRelIso,
    mu_miniIsoCharged,
    mu_miniIsoNeutral,
    mu_jetPtRatio,
    mu_jetCSV,
    mu_sip3D,
    mu_dxy,
    mu_dz,
    mu_segmentCompatibility,
    mu_leptonMVA,
    mu_conept,
    mu_mediumID,
    mu_isfakeablesel,
    mu_iscutsel,
    mu_ismvasel
  );

  const Int_t nof_ele_iterations = is_initializing ? nof_eles : std::min(n_presel_ele, nof_eles);
  reset(
    nof_ele_iterations,
    ele_pt,
    ele_eta,
    ele_phi,
    ele_E,
    ele_charge,
    ele_miniRelIso,
    ele_miniIsoCharged,
    ele_miniIsoNeutral,
    ele_jetPtRatio,
    ele_jetCSV,
    ele_sip3D,
    ele_dxy,
    ele_dz,
    ele_ntMVAeleID,
    ele_leptonMVA,
    ele_conept,
    ele_isChargeConsistent,
    ele_passesConversionVeto,
    ele_nMissingHits,
    ele_isfakeablesel,
    ele_iscutsel,
    ele_ismvasel
  );

  const Int_t nof_tau_iterations = is_initializing ? nof_taus : std::min(n_presel_tau, nof_taus);
  reset(
    nof_tau_iterations,
    tau_pt,
    tau_eta,
    tau_phi,
    tau_E,
    tau_charge,
    tau_dxy,
    tau_dz,
    tau_decayModeFindingOldDMs,
    tau_decayModeFindingNewDMs,
    tau_byCombinedIsolationDeltaBetaCorr3Hits,
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits,
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits,
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits,
    tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,
    tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,
    tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT,
    tau_againstMuonLoose3,
    tau_againstMuonTight3,
    tau_againstElectronVLooseMVA6,
    tau_againstElectronLooseMVA6,
    tau_againstElectronMediumMVA6,
    tau_againstElectronTightMVA6,
    tau_againstElectronVTightMVA6
  );


  const Int_t nof_jet_iterations = is_initializing ? nof_jets : std::min(n_presel_jet, nof_jets);
  reset(
    nof_jet_iterations,
    jet_pt,
    jet_eta,
    jet_phi,
    jet_E,
    jet_CSV,
    jet_heppyFlavour
  );

  for(auto & kv: hltMap)
  {
    hltMap[kv.first] = -1;
  }
}

void
SyncNtupleManager::fill()
{
  outputTree -> Fill();
  reset(false);
}

void
SyncNtupleManager::write()
{
  outputFile -> cd();
  outputTree -> Write();
}
