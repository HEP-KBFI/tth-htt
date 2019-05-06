#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

#include <TFile.h> // TFile

#include <boost/algorithm/string/predicate.hpp> // boost::starts_with()

#include <algorithm> // std::min()

const Int_t SyncNtupleManager::placeholder_value = -9999;

SyncNtupleManager::SyncNtupleManager(const std::string & outputFileName,
                                     const std::string & outputTreeName)
  : outputFile(new TFile(outputFileName.c_str(), "recreate"))
  , outputDir(nullptr)
  , outputTree(nullptr)
  , nof_leps(4)
  , nof_mus(2)
  , nof_eles(2)
  , nof_taus(2)
  , nof_jets(4)
  , nof_fwdJets(4)
{
  std::string outputDirName_;
  std::string outputTreeName_ = outputTreeName;
  const auto nofSlashes = std::count(outputTreeName.cbegin(), outputTreeName.cend(), '/');
  if(nofSlashes == 1)
  {
    const std::size_t slashPos = outputTreeName.find('/');
    outputDirName_ = outputTreeName.substr(0, slashPos);
    outputTreeName_ = outputTreeName.substr(slashPos + 1);
  }
  else if(nofSlashes > 1)
  {
    throw cmsException(this) << "Invalid name for TTree = " << outputTreeName;
  }

  if(! outputDirName_.empty())
  {
    outputDir = outputFile->mkdir(outputDirName_.c_str());
    outputDir -> cd();
  }

  outputTree = new TTree(outputTreeName_.c_str(), outputTreeName_.c_str());
  if(outputDir)
  {
    outputTree->SetDirectory(outputDir);
  }
  for(int var = as_integer(FloatVariableType::PFMET); var <= as_integer(FloatVariableType::genWeight); ++var)
  {
    floatMap[static_cast<FloatVariableType>(var)] = placeholder_value;
  }
}

SyncNtupleManager::~SyncNtupleManager()
{
  outputFile -> Close();
  delete outputFile;
  outputTree = nullptr;
  outputDir = nullptr;
  outputFile = nullptr;
}

void
SyncNtupleManager::initializeBranches()
{
  const char * lstr  = "lep";
  const char * mstr  = "mu";
  const char * estr  = "ele";
  const char * tstr  = "tau";
  const char * jstr  = "jet";
  const char * jfstr = "jetFwd";

  const std::string n_sel_lep_str         = Form("n_%s",             lstr);
  const std::string n_presel_mu_str       = Form("n_presel_%s",      mstr);
  const std::string n_fakeablesel_mu_str  = Form("n_fakeablesel_%s", mstr);
  const std::string n_mvasel_mu_str       = Form("n_mvasel_%s",      mstr);
  const std::string n_presel_ele_str      = Form("n_presel_%s",      estr);
  const std::string n_fakeablesel_ele_str = Form("n_fakeablesel_%s", estr);
  const std::string n_mvasel_ele_str      = Form("n_mvasel_%s",      estr);
  const std::string n_presel_tau_str      = Form("n_presel_%s",      tstr);
  const std::string n_presel_jet_str      = Form("n_presel_%s",      jstr);
  const std::string n_presel_fwdJet_str   = Form("n_presel_%s",      jfstr);

  setBranches(
    nEvent,            "nEvent",
    ls,                "ls",
    run,               "run",
    n_sel_lep,         n_sel_lep_str,
    n_presel_mu,       n_presel_mu_str,
    n_fakeablesel_mu,  n_fakeablesel_mu_str,
    n_mvasel_mu,       n_mvasel_mu_str,
    n_presel_ele,      n_presel_ele_str,
    n_fakeablesel_ele, n_fakeablesel_ele_str,
    n_mvasel_ele,      n_mvasel_ele_str,
    n_presel_tau,      n_presel_tau_str,
    n_presel_jet,      n_presel_jet_str,
    n_presel_fwdJet,   n_presel_fwdJet_str,

//--- MET/MHT
    floatMap[FloatVariableType::PFMET],                    "PFMET",
    floatMap[FloatVariableType::PFMETphi],                 "PFMETphi",
    floatMap[FloatVariableType::MHT],                      "MHT",
    floatMap[FloatVariableType::metLD],                    "metLD",

//--- Additional event-level MVA input variables
    isGenMatched,                                          "isGenMatched",

    floatMap[FloatVariableType::mindr_lep1_jet],           "mindr_lep1_jet",
    floatMap[FloatVariableType::mindr_lep2_jet],           "mindr_lep2_jet",
    floatMap[FloatVariableType::mindr_lep3_jet],           "mindr_lep3_jet",
    floatMap[FloatVariableType::mindr_lep4_jet],           "mindr_lep4_jet",

    floatMap[FloatVariableType::mindr_tau1_jet],           "mindr_tau1_jet",
    floatMap[FloatVariableType::mindr_tau2_jet],           "mindr_tau2_jet",

    floatMap[FloatVariableType::avg_dr_jet],               "avg_dr_jet",
    floatMap[FloatVariableType::avr_dr_lep_tau],           "avr_dr_lep_tau",
    floatMap[FloatVariableType::max_dr_jet],               "max_dr_jet",
    floatMap[FloatVariableType::max_dr_lep_tau],           "max_dr_lep_tau",
    floatMap[FloatVariableType::min_dr_tau_jet],           "mindr_tau_jet",
    floatMap[FloatVariableType::min_dr_lep_tau],           "min_dr_lep_tau",
    floatMap[FloatVariableType::min_dr_lep_jet],           "min_dr_lep_jet",

    floatMap[FloatVariableType::dr_leps],                  "dr_leps",
    floatMap[FloatVariableType::dr_taus],                  "dr_taus",

    floatMap[FloatVariableType::dr_lep_tau_ss],            "dR_lep_tau_ss",
    floatMap[FloatVariableType::dr_lep1_tau1],             "dr_lep1_tau",
    floatMap[FloatVariableType::dr_lep2_tau1],             "dr_lep2_tau",
    floatMap[FloatVariableType::dr_lep3_tau1],             "dR_lep3_tau",
    floatMap[FloatVariableType::dr_lep1_tau2],             "dR_lep1_tau2",
    floatMap[FloatVariableType::dr_lep2_tau2],             "dR_lep2_tau2",

    floatMap[FloatVariableType::max_lep_eta],              "max_lep_eta",

    floatMap[FloatVariableType::mT_met_lep1],              "mT_lep1",
    floatMap[FloatVariableType::mT_met_lep2],              "mT_lep2",
    floatMap[FloatVariableType::mT_met_lep3],              "mT_lep3",
    floatMap[FloatVariableType::mT_met_lep4],              "mT_lep4",
    floatMap[FloatVariableType::massL],                    "massL",

    floatMap[FloatVariableType::mTauTauVis],               "mTauTauVis",
    floatMap[FloatVariableType::mvis_l1tau],               "mTauTauVis1",
    floatMap[FloatVariableType::mvis_l2tau],               "mTauTauVis2",

    floatMap[FloatVariableType::mbb],                      "mbb",
    floatMap[FloatVariableType::mbb_loose],                "mbb_loose",

    floatMap[FloatVariableType::cosThetaS_hadTau],         "cosThetaS_hadTau",
    floatMap[FloatVariableType::HTT],                      "HTT",
    floatMap[FloatVariableType::HadTop_pt],                "HadTop_pt",
    floatMap[FloatVariableType::Hj_tagger],                "Hj_tagger",

//--- boosted variables
    floatMap[FloatVariableType::HTT_boosted],             "HTT_boosted",
    floatMap[FloatVariableType::nHTTv2],                  "nHTTv2",

    floatMap[FloatVariableType::jetHTTv2_1_pt],           "jetHTTv2_1_pt",
    floatMap[FloatVariableType::jetHTTv2_1_eta],          "jetHTTv2_1_eta",
    floatMap[FloatVariableType::jetHTTv2_1_phi],          "jetHTTv2_1_phi",
    floatMap[FloatVariableType::jetHTTv2_1_E],            "jetHTTv2_1_E",
    floatMap[FloatVariableType::N_jetAK8],                "N_jetAK8",
    floatMap[FloatVariableType::jetAK8_1_pt],             "jetAK8_1_pt",
    floatMap[FloatVariableType::jetAK8_1_eta],            "jetAK8_1_eta",
    floatMap[FloatVariableType::jetAK8_1_phi],            "jetAK8_1_phi",
    floatMap[FloatVariableType::jetAK8_1_E],              "jetAK8_1_E",
    floatMap[FloatVariableType::NcleanedJets_fromAK8],    "NcleanedJets_fromAK8",
    floatMap[FloatVariableType::HadTop_pt_semi_boosted_fromAK8],  "HadTop_pt_semi_boosted_fromAK8",
    floatMap[FloatVariableType::HTT_semi_boosted_fromAK8],        "HTT_semi_boosted_fromAK8",

    ntags,                                                 "nBJetMedium",
    ntags_loose,                                           "nBJetLoose",
    njets_light,                                           "nLightJet",

//--- Additional event-level MVA output variables
    floatMap[FloatVariableType::mvaOutput_plainKin_ttV],   "mvaOutput_plainKin_ttV",
    floatMap[FloatVariableType::mvaOutput_plainKin_tt],    "mvaOutput_plainKin_ttbar",

    floatMap[FloatVariableType::mvaOutput_HTT_SUM_VT],     "mvaOutput_1l_2tau_HTT_SUM_VT",

    floatMap[FloatVariableType::mvaOutput_plainKin_1B_VT],  "mvaOutput_2l_2tau_plainKin_1B_VT",
    floatMap[FloatVariableType::mvaOutput_plainKin_SUM_VT], "mvaOutput_2l_2tau_plainKin_SUM_VT",

    floatMap[FloatVariableType::mvaOutput_2lss_ttV],                 "mvaOutput_2lss_ttV",
    floatMap[FloatVariableType::mvaOutput_2lss_tt],                  "mvaOutput_2lss_ttbar",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_plainKin_tt],    "mvaOutput_2lss_1tau_plainKin_ttbar",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_plainKin_ttV],   "mvaOutput_2lss_1tau_plainKin_ttV",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_plainKin_1B_M],  "mvaOutput_2lss_1tau_plainKin_1B_M",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_plainKin_SUM_M], "mvaOutput_2lss_1tau_plainKin_SUM_M",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_HTT_SUM_M],      "mvaOutput_2lss_1tau_HTT_SUM_M",
    floatMap[FloatVariableType::mvaOutput_2lss_1tau_HTTMEM_SUM_M],   "mvaOutput_2lss_1tau_HTTMEM_SUM_M",

    floatMap[FloatVariableType::mvaOutput_3l_ttV],         "mvaOutput_3l_ttV",
    floatMap[FloatVariableType::mvaOutput_3l_ttbar],       "mvaOutput_3l_ttbar",
    floatMap[FloatVariableType::mvaOutput_plainKin_SUM_M], "mvaOutput_3l_1tau_plainKin_SUM_M",
    floatMap[FloatVariableType::mvaOutput_plainKin_1B_M],  "mvaOutput_3l_1tau_plainKin_1B_M",

    floatMap[FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH], "mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH",
    floatMap[FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_tH], "mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_tH",
    floatMap[FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW], "mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW",
    floatMap[FloatVariableType::mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_rest], "mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_rest",

    floatMap[FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_ttH], "mvaOutput_3l_ttH_tH_3cat_v8_ttH",
    floatMap[FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_tH], "mvaOutput_3l_ttH_tH_3cat_v8_tH",
    floatMap[FloatVariableType::mvaOutput_3l_ttH_tH_3cat_v8_rest], "mvaOutput_3l_ttH_tH_3cat_v8_rest",

//--- Event weights
    floatMap[FloatVariableType::FR_weight],                "FR_weight",
    floatMap[FloatVariableType::triggerSF_weight],         "triggerSF_weight",
    floatMap[FloatVariableType::leptonSF_weight],          "leptonSF_weight",
    floatMap[FloatVariableType::tauSF_weight],             "tauSF_weight",
    floatMap[FloatVariableType::bTagSF_weight],            "bTagSF_weight",
    floatMap[FloatVariableType::PU_weight],                "PU_weight",
    floatMap[FloatVariableType::MC_weight],                "MC_weight",

//--- MEM variables
    floatMap[FloatVariableType::Integral_ttH],             "Integral_ttH",
    floatMap[FloatVariableType::Integral_ttZ],             "Integral_ttZ",
    floatMap[FloatVariableType::Integral_ttZ_Zll],         "Integral_ttZ_Zll",
    floatMap[FloatVariableType::Integral_ttbar],           "Integral_ttbar",
    floatMap[FloatVariableType::integration_type],         "integration_type",
    floatMap[FloatVariableType::MEM_LR],                   "memOutput_LR",

//--- custom additional branches (not necessary in sync)
    floatMap[FloatVariableType::genWeight],                "genWeight"
  );

  setBranches(
    lstr, nof_leps,
    lep_pt,            "pt",
    lep_conePt,        "conePt",
    lep_eta,           "eta",
    lep_phi,           "phi",
    lep_pdgId,         "pdgId",
    lep_isfakeablesel, "isfakeablesel",
    lep_ismvasel,      "ismvasel"
  );

  setBranches(
    mstr, nof_mus,
    mu_pt,                   "pt",
    mu_conept,               "conept",
    mu_eta,                  "eta",
    mu_phi,                  "phi",
    mu_E,                    "E",
    mu_charge,               "charge",
    mu_miniRelIso,           "miniRelIso",
    mu_miniRelIsoCharged,    "miniIsoCharged",
    mu_miniRelIsoNeutral,    "miniIsoNeutral",
    mu_pfRelIso04All,        "PFRelIso04",
    mu_jetNDauChargedMVASel, "jetNDauChargedMVASel",
    mu_jetPtRel,             "jetPtRel",
    mu_jetPtRatio,           "jetPtRatio",
    mu_jetCSV,               "jetCSV",
    mu_jetDeepCSV,           "jetDeepCSV",
    mu_jetDeepJet,           "jetDeepJet",
    mu_sip3D,                "sip3D",
    mu_dxy,                  "dxy",
    mu_dxyAbs,               "dxyAbs",
    mu_dz,                   "dz",
    mu_segmentCompatibility, "segmentCompatibility",
    mu_leptonMVA,            "leptonMVA",
    mu_mediumID,             "mediumID",
    mu_dpt_div_pt,           "dpt_div_pt",
    mu_isfakeablesel,        "isfakeablesel",
    mu_ismvasel,             "ismvasel",
    mu_isGenMatched,         "isGenMatched"
  );

  setBranches(
    estr, nof_eles,
    ele_pt,                   "pt",
    ele_conept,               "conept",
    ele_eta,                  "eta",
    ele_phi,                  "phi",
    ele_E,                    "E",
    ele_charge,               "charge",
    ele_miniRelIso,           "miniRelIso",
    ele_miniRelIsoCharged,    "miniIsoCharged",
    ele_miniRelIsoNeutral,    "miniIsoNeutral",
    ele_pfRelIso04All,        "PFRelIso04",
    ele_jetNDauChargedMVASel, "jetNDauChargedMVASel",
    ele_jetPtRel,             "jetPtRel",
    ele_jetPtRatio,           "jetPtRatio",
    ele_jetCSV,               "jetCSV",
    ele_jetDeepCSV,           "jetDeepCSV",
    ele_jetDeepJet,           "jetDeepJet",
    ele_sip3D,                "sip3D",
    ele_dxyAbs,               "dxyAbs",
    ele_dxy,                  "dxy",
    ele_dz,                   "dz",
    ele_ntMVAeleID,           "ntMVAeleID",
    ele_leptonMVA,            "leptonMVA",
    ele_isChargeConsistent,   "isChargeConsistent",
    ele_passesConversionVeto, "passesConversionVeto",
    ele_nMissingHits,         "nMissingHits",
    ele_sigmaEtaEta,          "sigmaEtaEta",
    ele_HoE,                  "HoE",
    ele_deltaEta,             "deltaEta",
    ele_deltaPhi,             "deltaPhi",
    ele_OoEminusOoP,          "OoEminusOoP",
    ele_isfakeablesel,        "isfakeablesel",
    ele_ismvasel,             "ismvasel",
    ele_isGenMatched,         "isGenMatched"
  );

  setBranches(
    tstr, nof_taus,
    tau_pt,                                        "pt",
    tau_eta,                                       "eta",
    tau_phi,                                       "phi",
    tau_E,                                         "E",
    tau_charge,                                    "charge",
    tau_dxy,                                       "dxy",
    tau_dz,                                        "dz",
    tau_decayMode,                                 "decayMode",
    tau_decayModeFindingOldDMs,                    "decayModeFindingOldDMs",
    tau_decayModeFindingNewDMs,                    "decayModeFindingNewDMs",
    tau_byVVLooseIsolationMVArun2v1DBdR03oldDMwLT, "byVVLooseIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,  "byVLooseIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT,   "byLooseIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT,  "byMediumIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT,   "byTightIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT,  "byVTightIsolationMVArun2v1DBdR03oldDMwLT",
    tau_byVVTightIsolationMVArun2v1DBdR03oldDMwLT, "byVVTightIsolationMVArun2v1DBdR03oldDMwLT",
    tau_rawMVArun2v1DBdR03oldDMwLT,                "rawMVArun2v1DBdR03oldDMwLT",
    tau_againstMuonLoose3,                         "againstMuonLoose3",
    tau_againstMuonTight3,                         "againstMuonTight3",
    tau_againstElectronVLooseMVA6,                 "againstElectronVLooseMVA6",
    tau_againstElectronLooseMVA6,                  "againstElectronLooseMVA6",
    tau_againstElectronMediumMVA6,                 "againstElectronMediumMVA6",
    tau_againstElectronTightMVA6,                  "againstElectronTightMVA6",
    tau_againstElectronVTightMVA6,                 "againstElectronVTightMVA6",
    tau_isGenMatched,                              "isGenMatched"
  );

  setBranches(
    jstr, nof_jets,
    jet_pt,      "pt",
    jet_eta,     "eta",
    jet_phi,     "phi",
    jet_E,       "E",
    jet_CSV,     "CSV",
    jet_DeepCSV, "DeepCSV",
    jet_DeepJet, "DeepJet",
    jet_QGdiscr, "QGdiscr"
  );

  setBranches(
    jfstr, nof_fwdJets,
    jetFwd_pt,  "pt",
    jetFwd_eta, "eta",
    jetFwd_phi, "phi",
    jetFwd_E,   "E"
  );

  reset();
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
SyncNtupleManager::read(const EventInfo & eventInfo)
{
  run = eventInfo.run;
  ls = eventInfo.lumi;
  nEvent = eventInfo.event;
}

void
SyncNtupleManager::read(const std::vector<const RecoLepton *> & leptons)
{
  n_sel_lep = leptons.size();
  const Int_t nof_iterations = std::min(n_sel_lep, nof_leps);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoLepton * lepton = leptons[i];
    lep_pt[i] = lepton->pt();
    lep_conePt[i] = lepton->cone_pt();
    lep_eta[i] = lepton->eta();
    lep_phi[i] = lepton->phi();
    lep_pdgId[i] = lepton->pdgId();
    lep_isfakeablesel[i] = lepton->isFakeable();
    lep_ismvasel[i] = lepton->isTight();
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoMuon *> & muons,
                        const std::vector<const RecoMuon *> & fakeable_muons,
                        const std::vector<const RecoMuon *> & tight_muons)
{
  n_presel_mu = muons.size();
  n_fakeablesel_mu = fakeable_muons.size();
  n_mvasel_mu = tight_muons.size();

  const Int_t nof_iterations = std::min(n_presel_mu, nof_mus);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoMuon * const muon = muons[i];
    mu_pt[i] = muon -> pt();
    mu_conept[i] = muon -> cone_pt();
    mu_eta[i] = muon -> eta();
    mu_phi[i] = muon -> phi();
    mu_E[i] = (muon -> p4()).E();
    mu_charge[i] = muon -> charge();
    mu_miniRelIso[i] = muon -> relIso();
    mu_miniRelIsoCharged[i] = muon -> miniRelIsoCharged();
    mu_miniRelIsoNeutral[i] = muon -> miniRelIsoNeutral();
    mu_pfRelIso04All[i] = muon -> pfRelIso04All();
    mu_jetNDauChargedMVASel[i] = muon -> jetNDauChargedMVASel();
    mu_jetPtRel[i] = muon -> jetPtRel();
    mu_jetPtRatio[i] = std::min(muon -> jetPtRatio(), 1.5);
    mu_jetCSV[i] = std::max(0., muon -> jetBtagCSV(Btag::kCSVv2));
    mu_jetDeepCSV[i] = std::max(0., muon -> jetBtagCSV(Btag::kDeepCSV));
    mu_jetDeepJet[i] = std::max(0., muon -> jetBtagCSV(Btag::kDeepJet));
    mu_sip3D[i] = muon -> sip3d();
    mu_dxyAbs[i] = std::fabs(muon -> dxy());
    mu_dxy[i] = muon -> dxy();
    mu_dz[i] = muon -> dz();
    mu_segmentCompatibility[i] = muon -> segmentCompatibility();
    mu_leptonMVA[i] = muon -> mvaRawTTH();
    mu_mediumID[i] = muon -> passesMediumIdPOG();
    mu_dpt_div_pt[i] = muon -> dpt_div_pt();

    mu_isfakeablesel[i] = 0;
    for(const auto & fakeable_muon: fakeable_muons)
    {
      if(muon == fakeable_muon)
      {
        mu_isfakeablesel[i] = 1;
        break;
      }
    }
    mu_ismvasel[i] = 0;
    for(const auto & tight_muon: tight_muons)
    {
      if(muon == tight_muon)
      {
        mu_ismvasel[i] = 1;
        break;
      }
    }

    mu_isGenMatched[i] = muon -> isGenMatched();
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoElectron *> & electrons,
                        const std::vector<const RecoElectron *> & fakeable_electrons,
                        const std::vector<const RecoElectron *> & tight_electrons)
{
  n_presel_ele = electrons.size();
  n_fakeablesel_ele = fakeable_electrons.size();
  n_mvasel_ele = tight_electrons.size();

  const Int_t nof_iterations = std::min(n_presel_ele, nof_eles);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoElectron * const electron = electrons[i];
    ele_pt[i] = electron -> pt();
    ele_conept[i] = electron -> cone_pt();
    ele_eta[i] = electron -> eta();
    ele_phi[i] = electron -> phi();
    ele_E[i] = (electron -> p4()).E();
    ele_charge[i] = electron -> charge();
    ele_miniRelIso[i] = electron -> relIso();
    ele_miniRelIsoCharged[i] = electron -> miniRelIsoCharged();
    ele_miniRelIsoNeutral[i] = electron -> miniRelIsoNeutral();
    ele_pfRelIso04All[i] = electron -> pfRelIso04All();
    ele_jetNDauChargedMVASel[i] = electron -> jetNDauChargedMVASel();
    ele_jetPtRel[i] = electron -> jetPtRel();
    ele_jetPtRatio[i] = std::min(electron -> jetPtRatio(), 1.5);
    ele_jetCSV[i] = std::max(0., electron -> jetBtagCSV(Btag::kCSVv2));
    ele_jetDeepCSV[i] = std::max(0., electron -> jetBtagCSV(Btag::kDeepCSV));
    ele_jetDeepJet[i] = std::max(0., electron -> jetBtagCSV(Btag::kDeepJet));
    ele_sip3D[i] = electron -> sip3d();
    ele_dxyAbs[i] = std::fabs(electron -> dxy());
    ele_dxy[i] = electron -> dxy();
    ele_dz[i] = electron -> dz();
    ele_ntMVAeleID[i] = electron -> mvaRaw_POG();
    ele_leptonMVA[i] = electron -> mvaRawTTH();
    ele_isChargeConsistent[i] = electron -> tightCharge() == 2 ? 1 : 0;
    ele_passesConversionVeto[i] = electron -> passesConversionVeto();
    ele_nMissingHits[i] = electron -> nLostHits();
    ele_sigmaEtaEta[i] = electron -> sigmaEtaEta();
    ele_HoE[i] = electron -> HoE();
    ele_deltaEta[i] = electron -> deltaEta();
    ele_deltaPhi[i] = electron -> deltaPhi();
    ele_OoEminusOoP[i] = electron -> OoEminusOoP();

    ele_isfakeablesel[i] = 0;
    for(const auto & fakeable_electron: fakeable_electrons)
    {
      if(electron == fakeable_electron)
      {
        ele_isfakeablesel[i] = 1;
        break;
      }
    }
    ele_ismvasel[i] = 0;
    for(const auto & tight_electron: tight_electrons)
    {
      if(electron == tight_electron)
      {
        ele_ismvasel[i] = 1;
        break;
      }
    }

    ele_isGenMatched[i] = electron -> isGenMatched();
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
    tau_decayMode[i] = hadtau -> decayMode();
    tau_decayModeFindingOldDMs[i] = hadtau -> decayModeFinding();
    tau_decayModeFindingNewDMs[i] = hadtau -> decayModeFindingNew();

    const Int_t idMVArun2dR03 = hadtau -> id_mva();
    tau_byVVLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 1 ? 1 : 0;
    tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 2 ? 1 : 0;
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 3 ? 1 : 0;
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 4 ? 1 : 0;
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 5 ? 1 : 0;
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 6 ? 1 : 0;
    tau_byVVTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 7 ? 1 : 0;
    tau_rawMVArun2v1DBdR03oldDMwLT[i] = hadtau -> raw_mva();

    const Int_t idAntiMu = hadtau -> antiMuon();
    tau_againstMuonLoose3[i] = idAntiMu >= 1 ? 1 : 0;
    tau_againstMuonTight3[i] = idAntiMu >= 2 ? 1 : 0;

    const Int_t idAntiErun2 = hadtau -> antiElectron();
    tau_againstElectronVLooseMVA6[i] = idAntiErun2 >= 1 ? 1 : 0;
    tau_againstElectronLooseMVA6[i] = idAntiErun2 >= 2 ? 1 : 0;
    tau_againstElectronMediumMVA6[i] = idAntiErun2 >= 3 ? 1 : 0;
    tau_againstElectronTightMVA6[i] = idAntiErun2 >= 4 ? 1 : 0;
    tau_againstElectronVTightMVA6[i] = idAntiErun2 >= 5 ? 1 : 0;
    tau_isGenMatched[i] = hadtau -> isGenMatched();
  }
}

void
SyncNtupleManager::read(const std::vector<const RecoJet *> & jets,
                        bool isFwd)
{
  if(isFwd)
  {
    n_presel_fwdJet = jets.size();
    const Int_t nof_iterations = std::min(n_presel_fwdJet, nof_fwdJets);
    for(Int_t i = 0; i < nof_iterations; ++i)
    {
      const RecoJet * const jet = jets[i];
      jetFwd_pt[i] = jet -> pt();
      jetFwd_eta[i] = jet -> eta();
      jetFwd_phi[i] = jet -> phi();
      jetFwd_E[i] = (jet -> p4()).E();
    }
  }
  else
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
      if(jet -> hasBtag(Btag::kCSVv2))
      {
        jet_CSV[i] = jet -> BtagCSV(Btag::kCSVv2);
      }
      jet_DeepCSV[i] = jet -> BtagCSV(Btag::kDeepCSV);
      jet_DeepJet[i] = jet -> BtagCSV(Btag::kDeepJet);
      jet_QGdiscr[i] = jet -> QGDiscr();
    }
  }
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
SyncNtupleManager::read(bool is_genMatched,
                        int n_tags,
                        int n_tags_loose,
                        int n_jets_light)
{
  isGenMatched = is_genMatched;
  ntags        = n_tags;
  ntags_loose  = n_tags_loose;
  njets_light  = n_jets_light;
}

void
SyncNtupleManager::reset()
{
  nEvent = 0;
  ls = 0;
  run = 0;

  reset(
    n_presel_mu,
    n_fakeablesel_mu,
    n_mvasel_mu,
    n_presel_ele,
    n_fakeablesel_ele,
    n_mvasel_ele,
    n_presel_tau,
    n_presel_jet,
    n_presel_fwdJet,
    isGenMatched,
    ntags,
    ntags_loose,
    njets_light
  );

  for(auto & kv: floatMap)
  {
    kv.second = placeholder_value;
  }

  reset(
    nof_leps,
    lep_pt,
    lep_eta,
    lep_phi,
    lep_pdgId,
    lep_isfakeablesel,
    lep_ismvasel
  );

  reset(
    nof_mus,
    mu_pt,
    mu_conept,
    mu_eta,
    mu_phi,
    mu_E,
    mu_charge,
    mu_miniRelIso,
    mu_miniRelIsoCharged,
    mu_miniRelIsoNeutral,
    mu_pfRelIso04All,
    mu_jetNDauChargedMVASel,
    mu_jetPtRel,
    mu_jetPtRatio,
    mu_jetCSV,
    mu_jetDeepCSV,
    mu_jetDeepJet,
    mu_sip3D,
    mu_dxy,
    mu_dxyAbs,
    mu_dz,
    mu_segmentCompatibility,
    mu_leptonMVA,
    mu_mediumID,
    mu_dpt_div_pt,
    mu_isfakeablesel,
    mu_ismvasel,
    mu_isGenMatched
  );

  reset(
    nof_eles,
    ele_pt,
    ele_conept,
    ele_eta,
    ele_phi,
    ele_E,
    ele_charge,
    ele_miniRelIso,
    ele_miniRelIsoCharged,
    ele_miniRelIsoNeutral,
    ele_pfRelIso04All,
    ele_jetNDauChargedMVASel,
    ele_jetPtRel,
    ele_jetPtRatio,
    ele_jetCSV,
    ele_jetDeepCSV,
    ele_jetDeepJet,
    ele_sip3D,
    ele_dxy,
    ele_dxyAbs,
    ele_dz,
    ele_ntMVAeleID,
    ele_leptonMVA,
    ele_isChargeConsistent,
    ele_passesConversionVeto,
    ele_nMissingHits,
    ele_sigmaEtaEta,
    ele_HoE,
    ele_deltaEta,
    ele_deltaPhi,
    ele_OoEminusOoP,
    ele_isfakeablesel,
    ele_ismvasel,
    ele_isGenMatched
  );

  reset(
    nof_taus,
    tau_pt,
    tau_eta,
    tau_phi,
    tau_E,
    tau_charge,
    tau_dxy,
    tau_dz,
    tau_decayMode,
    tau_decayModeFindingOldDMs,
    tau_decayModeFindingNewDMs,
    tau_byVVLooseIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT,
    tau_byVVTightIsolationMVArun2v1DBdR03oldDMwLT,
    tau_rawMVArun2v1DBdR03oldDMwLT,
    tau_againstMuonLoose3,
    tau_againstMuonTight3,
    tau_againstElectronVLooseMVA6,
    tau_againstElectronLooseMVA6,
    tau_againstElectronMediumMVA6,
    tau_againstElectronTightMVA6,
    tau_againstElectronVTightMVA6,
    tau_isGenMatched
  );

  reset(
    nof_jets,
    jet_pt,
    jet_eta,
    jet_phi,
    jet_E,
    jet_CSV,
    jet_DeepCSV,
    jet_DeepJet,
    jet_QGdiscr
  );

  reset(
    nof_fwdJets,
    jetFwd_pt,
    jetFwd_eta,
    jetFwd_phi,
    jetFwd_E
  );

  for(auto & kv: hltMap)
  {
    hltMap[kv.first] = -1;
  }
}

void
SyncNtupleManager::fill()
{
  if(outputDir)
  {
    outputDir -> cd();
  }
  else
  {
    outputFile -> cd();
  }
  outputTree -> Fill();
  reset();
}

void
SyncNtupleManager::write()
{
  if(outputDir)
  {
    outputDir -> cd();
  }
  else
  {
    outputFile -> cd();
  }
  outputTree -> Write();
}
