#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h"

#include <algorithm> // std::min()
#include <type_traits> // std::remove_pointer<>

#include <TString.h> // Form()


SyncNtupleManager::SyncNtupleManager(const std::string & outputFileName,
                                     const std::string & outputTreeName)
  : placeholder_value(-9999)
  , nof_mus(2)
  , nof_eles(2)
  , nof_taus(2)
  , nof_jets(4)
{
  outputFile = new TFile(outputFileName.c_str(), "recreate");
  outputTree = new TTree(outputTreeName.c_str(), outputTreeName.c_str());
}

SyncNtupleManager::~SyncNtupleManager()
{
  outputFile -> Close();
  if(outputFile)  delete outputFile;
  outputTree = nullptr;
  outputFile = nullptr;
}

void
SyncNtupleManager::initializeBranches()
{
  mu_pt = new std::remove_pointer<decltype(mu_pt)>::type[nof_eles];
  mu_eta = new std::remove_pointer<decltype(mu_eta)>::type[nof_eles];
  mu_phi = new std::remove_pointer<decltype(mu_phi)>::type[nof_eles];
  mu_E = new std::remove_pointer<decltype(mu_E)>::type[nof_eles];
  mu_charge = new std::remove_pointer<decltype(mu_charge)>::type[nof_eles];
  mu_miniRelIso = new std::remove_pointer<decltype(mu_miniRelIso)>::type[nof_eles];
  mu_miniIsoCharged = new std::remove_pointer<decltype(mu_miniIsoCharged)>::type[nof_eles];
  mu_miniIsoNeutral = new std::remove_pointer<decltype(mu_miniIsoNeutral)>::type[nof_eles];
  mu_jetNDauChargedMVASel = new std::remove_pointer<decltype(mu_jetNDauChargedMVASel)>::type[nof_eles];
  mu_jetPtRel = new std::remove_pointer<decltype(mu_jetPtRel)>::type[nof_eles];
  mu_jetPtRatio = new std::remove_pointer<decltype(mu_jetPtRatio)>::type[nof_eles];
  mu_jetCSV = new std::remove_pointer<decltype(mu_jetCSV)>::type[nof_eles];
  mu_sip3D = new std::remove_pointer<decltype(mu_sip3D)>::type[nof_eles];
  mu_dxy = new std::remove_pointer<decltype(mu_dxy)>::type[nof_eles];
  mu_dz = new std::remove_pointer<decltype(mu_dz)>::type[nof_eles];
  mu_segmentCompatibility = new std::remove_pointer<decltype(mu_segmentCompatibility)>::type[nof_eles];
  mu_leptonMVA = new std::remove_pointer<decltype(mu_leptonMVA)>::type[nof_eles];
  mu_mediumID = new std::remove_pointer<decltype(mu_mediumID)>::type[nof_eles];
  mu_dpt_div_pt = new std::remove_pointer<decltype(mu_dpt_div_pt)>::type[nof_eles];
  mu_isfakeablesel = new std::remove_pointer<decltype(mu_isfakeablesel)>::type[nof_eles];
  mu_iscutsel = new std::remove_pointer<decltype(mu_iscutsel)>::type[nof_eles];
  mu_ismvasel = new std::remove_pointer<decltype(mu_ismvasel)>::type[nof_eles];

  ele_pt = new std::remove_pointer<decltype(ele_pt)>::type[nof_eles];
  ele_eta = new std::remove_pointer<decltype(ele_eta)>::type[nof_eles];
  ele_phi = new std::remove_pointer<decltype(ele_phi)>::type[nof_eles];
  ele_E = new std::remove_pointer<decltype(ele_E)>::type[nof_eles];
  ele_charge = new std::remove_pointer<decltype(ele_charge)>::type[nof_eles];
  ele_miniRelIso = new std::remove_pointer<decltype(ele_miniRelIso)>::type[nof_eles];
  ele_miniIsoCharged = new std::remove_pointer<decltype(ele_miniIsoCharged)>::type[nof_eles];
  ele_miniIsoNeutral = new std::remove_pointer<decltype(ele_miniIsoNeutral)>::type[nof_eles];
  ele_jetNDauChargedMVASel = new std::remove_pointer<decltype(ele_jetNDauChargedMVASel)>::type[nof_eles];
  ele_jetPtRel = new std::remove_pointer<decltype(ele_jetPtRel)>::type[nof_eles];
  ele_jetPtRatio = new std::remove_pointer<decltype(ele_jetPtRatio)>::type[nof_eles];
  ele_jetCSV = new std::remove_pointer<decltype(ele_jetCSV)>::type[nof_eles];
  ele_sip3D = new std::remove_pointer<decltype(ele_sip3D)>::type[nof_eles];
  ele_dxy = new std::remove_pointer<decltype(ele_dxy)>::type[nof_eles];
  ele_dz = new std::remove_pointer<decltype(ele_dz)>::type[nof_eles];
  ele_ntMVAeleID = new std::remove_pointer<decltype(ele_ntMVAeleID)>::type[nof_eles];
  ele_leptonMVA = new std::remove_pointer<decltype(ele_leptonMVA)>::type[nof_eles];
  ele_isChargeConsistent = new std::remove_pointer<decltype(ele_isChargeConsistent)>::type[nof_eles];
  ele_passesConversionVeto = new std::remove_pointer<decltype(ele_passesConversionVeto)>::type[nof_eles];
  ele_nMissingHits = new std::remove_pointer<decltype(ele_nMissingHits)>::type[nof_eles];
  ele_isfakeablesel = new std::remove_pointer<decltype(ele_isfakeablesel)>::type[nof_eles];
  ele_iscutsel = new std::remove_pointer<decltype(ele_iscutsel)>::type[nof_eles];
  ele_ismvasel = new std::remove_pointer<decltype(ele_ismvasel)>::type[nof_eles];

  tau_pt = new std::remove_pointer<decltype(tau_pt)>::type[nof_eles];
  tau_eta = new std::remove_pointer<decltype(tau_eta)>::type[nof_eles];
  tau_phi = new std::remove_pointer<decltype(tau_phi)>::type[nof_eles];
  tau_E = new std::remove_pointer<decltype(tau_E)>::type[nof_eles];
  tau_charge = new std::remove_pointer<decltype(tau_charge)>::type[nof_eles];
  tau_dxy = new std::remove_pointer<decltype(tau_dxy)>::type[nof_eles];
  tau_dz = new std::remove_pointer<decltype(tau_dz)>::type[nof_eles];
  tau_decayModeFindingOldDMs = new std::remove_pointer<decltype(tau_decayModeFindingOldDMs)>::type[nof_eles];
  tau_decayModeFindingNewDMs = new std::remove_pointer<decltype(tau_decayModeFindingNewDMs)>::type[nof_eles];
  tau_byCombinedIsolationDeltaBetaCorr3Hits = new std::remove_pointer<decltype(tau_byCombinedIsolationDeltaBetaCorr3Hits)>::type[nof_eles];
  tau_byLooseCombinedIsolationDeltaBetaCorr3Hits = new std::remove_pointer<decltype(tau_byLooseCombinedIsolationDeltaBetaCorr3Hits)>::type[nof_eles];
  tau_byMediumCombinedIsolationDeltaBetaCorr3Hits = new std::remove_pointer<decltype(tau_byMediumCombinedIsolationDeltaBetaCorr3Hits)>::type[nof_eles];
  tau_byTightCombinedIsolationDeltaBetaCorr3Hits = new std::remove_pointer<decltype(tau_byTightCombinedIsolationDeltaBetaCorr3Hits)>::type[nof_eles];
  tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03 = new std::remove_pointer<decltype(tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)>::type[nof_eles];
  tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03 = new std::remove_pointer<decltype(tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)>::type[nof_eles];
  tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03 = new std::remove_pointer<decltype(tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)>::type[nof_eles];
  tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT = new std::remove_pointer<decltype(tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT)>::type[nof_eles];
  tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT = new std::remove_pointer<decltype(tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT)>::type[nof_eles];
  tau_byTightIsolationMVArun2v1DBdR03oldDMwLT = new std::remove_pointer<decltype(tau_byTightIsolationMVArun2v1DBdR03oldDMwLT)>::type[nof_eles];
  tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT = new std::remove_pointer<decltype(tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT)>::type[nof_eles];
  tau_againstMuonLoose3 = new std::remove_pointer<decltype(tau_againstMuonLoose3)>::type[nof_eles];
  tau_againstMuonTight3 = new std::remove_pointer<decltype(tau_againstMuonTight3)>::type[nof_eles];
  tau_againstElectronVLooseMVA6 = new std::remove_pointer<decltype(tau_againstElectronVLooseMVA6)>::type[nof_eles];
  tau_againstElectronLooseMVA6 = new std::remove_pointer<decltype(tau_againstElectronLooseMVA6)>::type[nof_eles];
  tau_againstElectronMediumMVA6 = new std::remove_pointer<decltype(tau_againstElectronMediumMVA6)>::type[nof_eles];
  tau_againstElectronTightMVA6 = new std::remove_pointer<decltype(tau_againstElectronTightMVA6)>::type[nof_eles];

  jet_pt = new std::remove_pointer<decltype(jet_pt)>::type[nof_eles];
  jet_eta = new std::remove_pointer<decltype(jet_eta)>::type[nof_eles];
  jet_phi = new std::remove_pointer<decltype(jet_phi)>::type[nof_eles];
  jet_E = new std::remove_pointer<decltype(jet_E)>::type[nof_eles];
  jet_CSV = new std::remove_pointer<decltype(jet_CSV)>::type[nof_eles];

  if(outputTree)
  {
    const char * mstr = "mu";
    const char * estr = "ele";
    const char * tstr = "tau";
    const char * jstr = "jet";

    outputTree -> Branch("nEvent", &(nEvent), Form("nEvent/%s", Traits<decltype(nEvent)>::TYPE_NAME));
    outputTree -> Branch("ls", &(ls), Form("ls/%s", Traits<decltype(ls)>::TYPE_NAME));
    outputTree -> Branch("run", &(run), Form("run/%s", Traits<decltype(run)>::TYPE_NAME));

    outputTree -> Branch(Form("n_presel_%s", mstr), &(n_presel_mu), Form("n_presel_%s/%s", mstr, Traits<decltype(n_presel_mu)>::TYPE_NAME));
    outputTree -> Branch(Form("n_fakeablesel_%s", mstr), &(n_fakeablesel_mu), Form("n_fakeablesel_%s/%s", mstr, Traits<decltype(n_fakeablesel_mu)>::TYPE_NAME));
    outputTree -> Branch(Form("n_cutsel_%s", mstr), &(n_cutsel_mu), Form("n_cutsel_%s/%s", mstr, Traits<decltype(n_cutsel_mu)>::TYPE_NAME));
    outputTree -> Branch(Form("n_mvasel_%s", mstr), &(n_mvasel_mu), Form("n_mvasel_%s/%s", mstr, Traits<decltype(n_mvasel_mu)>::TYPE_NAME));

    outputTree -> Branch(Form("n_presel_%s", estr), &(n_presel_ele), Form("n_presel_%s/%s", estr, Traits<decltype(n_presel_ele)>::TYPE_NAME));
    outputTree -> Branch(Form("n_fakeablesel_%s", estr), &(n_fakeablesel_ele), Form("n_fakeablesel_%s/%s", estr, Traits<decltype(n_fakeablesel_ele)>::TYPE_NAME));
    outputTree -> Branch(Form("n_cutsel_%s", estr), &(n_cutsel_ele), Form("n_cutsel_%s/%s", estr, Traits<decltype(n_cutsel_ele)>::TYPE_NAME));
    outputTree -> Branch(Form("n_mvasel_%s", estr), &(n_mvasel_ele), Form("n_mvasel_%s/%s", estr, Traits<decltype(n_mvasel_ele)>::TYPE_NAME));

    outputTree -> Branch(Form("n_presel_%s", tstr), &(n_presel_tau), Form("n_presel_%s/%s", tstr, Traits<decltype(n_presel_tau)>::TYPE_NAME));
    outputTree -> Branch(Form("n_presel_%s", jstr), &(n_presel_jet), Form("n_presel_%s/%s", jstr, Traits<decltype(n_presel_jet)>::TYPE_NAME));

    for(Int_t i = 0; i < nof_mus; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "pt"), &(mu_pt[i]), Form("%s%d_%s/%s", mstr, i, "pt", Traits<decltype(mu_pt)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "eta"), &(mu_eta[i]), Form("%s%d_%s/%s", mstr, i, "eta", Traits<decltype(mu_eta)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "phi"), &(mu_phi[i]), Form("%s%d_%s/%s", mstr, i, "phi", Traits<decltype(mu_phi)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "E"), &(mu_E[i]), Form("%s%d_%s/%s", mstr, i, "E", Traits<decltype(mu_E)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "charge"), &(mu_charge[i]), Form("%s%d_%s/%s", mstr, i, "charge", Traits<decltype(mu_charge)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniRelIso"), &(mu_miniRelIso[i]), Form("%s%d_%s/%s", mstr, i, "miniRelIso", Traits<decltype(mu_miniRelIso)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniIsoCharged"), &(mu_miniIsoCharged[i]), Form("%s%d_%s/%s", mstr, i, "miniIsoCharged", Traits<decltype(mu_miniIsoCharged)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniIsoNeutral"), &(mu_miniIsoNeutral[i]), Form("%s%d_%s/%s", mstr, i, "miniIsoNeutral", Traits<decltype(mu_miniIsoNeutral)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetNDauChargedMVASel"), &(mu_jetNDauChargedMVASel[i]), Form("%s%d_%s/%s", mstr, i, "jetNDauChargedMVASel", Traits<decltype(mu_jetNDauChargedMVASel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetPtRel"), &(mu_jetPtRel[i]), Form("%s%d_%s/%s", mstr, i, "jetPtRel", Traits<decltype(mu_jetPtRel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetPtRatio"), &(mu_jetPtRatio[i]), Form("%s%d_%s/%s", mstr, i, "jetPtRatio", Traits<decltype(mu_jetPtRatio)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetCSV"), &(mu_jetCSV[i]), Form("%s%d_%s/%s", mstr, i, "jetCSV", Traits<decltype(mu_jetCSV)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "sip3D"), &(mu_sip3D[i]), Form("%s%d_%s/%s", mstr, i, "sip3D", Traits<decltype(mu_sip3D)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dxy"), &(mu_dxy[i]), Form("%s%d_%s/%s", mstr, i, "dxy", Traits<decltype(mu_dxy)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dz"), &(mu_dz[i]), Form("%s%d_%s/%s", mstr, i, "dz", Traits<decltype(mu_dz)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "segmentCompatibility"), &(mu_segmentCompatibility[i]), Form("%s%d_%s/%s", mstr, i, "segmentCompatibility", Traits<decltype(mu_segmentCompatibility)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "leptonMVA"), &(mu_leptonMVA[i]), Form("%s%d_%s/%s", mstr, i, "leptonMVA", Traits<decltype(mu_leptonMVA)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "mediumID"), &(mu_mediumID[i]), Form("%s%d_%s/%s", mstr, i, "mediumID", Traits<decltype(mu_mediumID)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dpt_div_pt"), &(mu_dpt_div_pt[i]), Form("%s%d_%s/%s", mstr, i, "dpt_div_pt", Traits<decltype(mu_dpt_div_pt)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "isfakeablesel"), &(mu_isfakeablesel[i]), Form("%s%d_%s/%s", mstr, i, "isfakeablesel", Traits<decltype(mu_isfakeablesel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "iscutsel"), &(mu_iscutsel[i]), Form("%s%d_%s/%s", mstr, i, "iscutsel", Traits<decltype(mu_iscutsel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "ismvasel"), &(mu_ismvasel[i]), Form("%s%d_%s/%s", mstr, i, "ismvasel", Traits<decltype(mu_ismvasel)>::TYPE_NAME));
    }

    for(Int_t i = 0; i < nof_eles; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", estr, i, "pt"), &(ele_pt[i]), Form("%s%d_%s/%s", estr, i, "pt", Traits<decltype(ele_pt)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "eta"), &(ele_eta[i]), Form("%s%d_%s/%s", estr, i, "eta", Traits<decltype(ele_eta)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "phi"), &(ele_phi[i]), Form("%s%d_%s/%s", estr, i, "phi", Traits<decltype(ele_phi)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "E"), &(ele_E[i]), Form("%s%d_%s/%s", estr, i, "E", Traits<decltype(ele_E)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "charge"), &(ele_charge[i]), Form("%s%d_%s/%s", estr, i, "charge", Traits<decltype(ele_charge)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniRelIso"), &(ele_miniRelIso[i]), Form("%s%d_%s/%s", estr, i, "miniRelIso", Traits<decltype(ele_miniRelIso)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniIsoCharged"), &(ele_miniIsoCharged[i]), Form("%s%d_%s/%s", estr, i, "miniIsoCharged", Traits<decltype(ele_miniIsoCharged)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniIsoNeutral"), &(ele_miniIsoNeutral[i]), Form("%s%d_%s/%s", estr, i, "miniIsoNeutral", Traits<decltype(ele_miniIsoNeutral)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetNDauChargedMVASel"), &(ele_jetNDauChargedMVASel[i]), Form("%s%d_%s/%s", estr, i, "jetNDauChargedMVASel", Traits<decltype(ele_jetNDauChargedMVASel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetPtRel"), &(ele_jetPtRel[i]), Form("%s%d_%s/%s", estr, i, "jetPtRel", Traits<decltype(ele_jetPtRel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetPtRatio"), &(ele_jetPtRatio[i]), Form("%s%d_%s/%s", estr, i, "jetPtRatio", Traits<decltype(ele_jetPtRatio)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetCSV"), &(ele_jetCSV[i]), Form("%s%d_%s/%s", estr, i, "jetCSV", Traits<decltype(ele_jetCSV)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "sip3D"), &(ele_sip3D[i]), Form("%s%d_%s/%s", estr, i, "sip3D", Traits<decltype(ele_sip3D)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "dxy"), &(ele_dxy[i]), Form("%s%d_%s/%s", estr, i, "dxy", Traits<decltype(ele_dxy)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "dz"), &(ele_dz[i]), Form("%s%d_%s/%s", estr, i, "dz", Traits<decltype(ele_dz)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "ntMVAeleID"), &(ele_ntMVAeleID[i]), Form("%s%d_%s/%s", estr, i, "ntMVAeleID", Traits<decltype(ele_ntMVAeleID)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "leptonMVA"), &(ele_leptonMVA[i]), Form("%s%d_%s/%s", estr, i, "leptonMVA", Traits<decltype(ele_leptonMVA)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "isChargeConsistent"), &(ele_isChargeConsistent[i]), Form("%s%d_%s/%s", estr, i, "isChargeConsistent", Traits<decltype(ele_isChargeConsistent)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "passesConversionVeto"), &(ele_passesConversionVeto[i]), Form("%s%d_%s/%s", estr, i, "passesConversionVeto", Traits<decltype(ele_passesConversionVeto)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "nMissingHits"), &(ele_nMissingHits[i]), Form("%s%d_%s/%s", estr, i, "nMissingHits", Traits<decltype(ele_nMissingHits)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "isfakeablesel"), &(ele_isfakeablesel[i]), Form("%s%d_%s/%s", estr, i, "isfakeablesel", Traits<decltype(ele_isfakeablesel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "iscutsel"), &(ele_iscutsel[i]), Form("%s%d_%s/%s", estr, i, "iscutsel", Traits<decltype(ele_iscutsel)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "ismvasel"), &(ele_ismvasel[i]), Form("%s%d_%s/%s", estr, i, "ismvasel", Traits<decltype(ele_ismvasel)>::TYPE_NAME));
    }

    for(Int_t i = 0; i < nof_taus; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "pt"), &(tau_pt[i]), Form("%s%d_%s/%s", tstr, i, "pt", Traits<decltype(tau_pt)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "eta"), &(tau_eta[i]), Form("%s%d_%s/%s", tstr, i, "eta", Traits<decltype(tau_eta)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "phi"), &(tau_phi[i]), Form("%s%d_%s/%s", tstr, i, "phi", Traits<decltype(tau_phi)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "E"), &(tau_E[i]), Form("%s%d_%s/%s", tstr, i, "E", Traits<decltype(tau_E)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "charge"), &(tau_charge[i]), Form("%s%d_%s/%s", tstr, i, "charge", Traits<decltype(tau_charge)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "dxy"), &(tau_dxy[i]), Form("%s%d_%s/%s", tstr, i, "dxy", Traits<decltype(tau_dxy)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "dz"), &(tau_dz[i]), Form("%s%d_%s/%s", tstr, i, "dz", Traits<decltype(tau_dz)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "decayModeFindingOldDMs"), &(tau_decayModeFindingOldDMs[i]), Form("%s%d_%s/%s", tstr, i, "decayModeFindingOldDMs", Traits<decltype(tau_decayModeFindingOldDMs)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "decayModeFindingNewDMs"), &(tau_decayModeFindingNewDMs[i]), Form("%s%d_%s/%s", tstr, i, "decayModeFindingNewDMs", Traits<decltype(tau_decayModeFindingNewDMs)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/%s", tstr, i, "byCombinedIsolationDeltaBetaCorr3Hits", Traits<decltype(tau_byCombinedIsolationDeltaBetaCorr3Hits)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byLooseCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3Hits", Traits<decltype(tau_byLooseCombinedIsolationDeltaBetaCorr3Hits)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byMediumCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3Hits", Traits<decltype(tau_byMediumCombinedIsolationDeltaBetaCorr3Hits)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byTightCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3Hits", Traits<decltype(tau_byTightCombinedIsolationDeltaBetaCorr3Hits)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03", Traits<decltype(tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", Traits<decltype(tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3HitsdR03", Traits<decltype(tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/%s", tstr, i, "byLooseIsolationMVArun2v1DBdR03oldDMwLT", Traits<decltype(tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/%s", tstr, i, "byMediumIsolationMVArun2v1DBdR03oldDMwLT", Traits<decltype(tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/%s", tstr, i, "byTightIsolationMVArun2v1DBdR03oldDMwLT", Traits<decltype(tau_byTightIsolationMVArun2v1DBdR03oldDMwLT)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byVTightIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/%s", tstr, i, "byVTightIsolationMVArun2v1DBdR03oldDMwLT", Traits<decltype(tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstMuonLoose3"), &(tau_againstMuonLoose3[i]), Form("%s%d_%s/%s", tstr, i, "againstMuonLoose3", Traits<decltype(tau_againstMuonLoose3)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstMuonTight3"), &(tau_againstMuonTight3[i]), Form("%s%d_%s/%s", tstr, i, "againstMuonTight3", Traits<decltype(tau_againstMuonTight3)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronVLooseMVA6"), &(tau_againstElectronVLooseMVA6[i]), Form("%s%d_%s/%s", tstr, i, "againstElectronVLooseMVA6", Traits<decltype(tau_againstElectronVLooseMVA6)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronLooseMVA6"), &(tau_againstElectronLooseMVA6[i]), Form("%s%d_%s/%s", tstr, i, "againstElectronLooseMVA6", Traits<decltype(tau_againstElectronLooseMVA6)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronMediumMVA6"), &(tau_againstElectronMediumMVA6[i]), Form("%s%d_%s/%s", tstr, i, "againstElectronMediumMVA6", Traits<decltype(tau_againstElectronMediumMVA6)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronTightMVA6"), &(tau_againstElectronTightMVA6[i]), Form("%s%d_%s/%s", tstr, i, "againstElectronTightMVA6", Traits<decltype(tau_againstElectronTightMVA6)>::TYPE_NAME));
    }

    for(Int_t i = 0; i < nof_jets; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "pt"), &(jet_pt[i]), Form("%s%d_%s/%s", jstr, i, "pt", Traits<decltype(jet_pt)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "eta"), &(jet_eta[i]), Form("%s%d_%s/%s", jstr, i, "eta", Traits<decltype(jet_eta)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "phi"), &(jet_phi[i]), Form("%s%d_%s/%s", jstr, i, "phi", Traits<decltype(jet_phi)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "E"), &(jet_E[i]), Form("%s%d_%s/%s", jstr, i, "E", Traits<decltype(jet_E)>::TYPE_NAME));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "CSV"), &(jet_CSV[i]), Form("%s%d_%s/%s", jstr, i, "CSV", Traits<decltype(jet_CSV)>::TYPE_NAME));
    }

    outputTree -> Branch("PFMET", &(PFMET), Form("PFMET/%s", Traits<decltype(PFMET)>::TYPE_NAME));
    outputTree -> Branch("PFMETphi", &(PFMETphi), Form("PFMETphi/%s", Traits<decltype(PFMETphi)>::TYPE_NAME));
    outputTree -> Branch("MHT", &(MHT), Form("MHT/%s", Traits<decltype(MHT)>::TYPE_NAME));
    outputTree -> Branch("metLD", &(metLD), Form("metLD/%s", Traits<decltype(metLD)>::TYPE_NAME));

    outputTree -> Branch("lep0_conept", &(lep0_conept), Form("lep0_conept/%s", Traits<decltype(lep0_conept)>::TYPE_NAME));
    outputTree -> Branch("lep1_conePt", &(lep1_conePt), Form("lep1_conePt/%s", Traits<decltype(lep1_conePt)>::TYPE_NAME));
    outputTree -> Branch("mindr_lep0_jet", &(mindr_lep0_jet), Form("mindr_lep0_jet/%s", Traits<decltype(mindr_lep0_jet)>::TYPE_NAME));
    outputTree -> Branch("mindr_lep1_jet", &(mindr_lep1_jet), Form("mindr_lep1_jet/%s", Traits<decltype(mindr_lep1_jet)>::TYPE_NAME));
    outputTree -> Branch("MT_met_lep0", &(MT_met_lep0), Form("MT_met_lep0/%s", Traits<decltype(MT_met_lep0)>::TYPE_NAME));
    outputTree -> Branch("avg_dr_jet", &(avg_dr_jet), Form("avg_dr_jet/%s", Traits<decltype(avg_dr_jet)>::TYPE_NAME));
    outputTree -> Branch("MVA_2lss_ttV", &(MVA_2lss_ttV), Form("MVA_2lss_ttV/%s", Traits<decltype(MVA_2lss_ttV)>::TYPE_NAME));
    outputTree -> Branch("MVA_2lss_ttbar", &(MVA_2lss_ttbar), Form("MVA_2lss_ttbar/%s", Traits<decltype(MVA_2lss_ttbar)>::TYPE_NAME));

    reset(true);
  }
  else
    std::cerr << "SyncNtuple:WARNING:Should initialize the instance only once!\n";
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
SyncNtupleManager::read(std::vector<const RecoMuon *> & muons)
{
  n_presel_mu = muons.size();
  const Int_t nof_iterations = std::min(n_presel_mu, nof_mus);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoMuon * const muon = muons[i];
    mu_pt[i] = muon -> pt_;
    mu_eta[i] = muon -> eta_;
    mu_phi[i] = muon -> phi_;
    mu_E[i] = (muon -> p4_).E();
    mu_charge[i] = muon -> charge_;
    mu_miniRelIso[i] = muon -> relIso_;
    mu_miniIsoCharged[i] = muon -> miniIsoCharged_;
    mu_miniIsoNeutral[i] = muon -> miniIsoNeutral_;
    mu_jetNDauChargedMVASel[i] = muon -> jetNDauChargedMVASel_;
    mu_jetPtRel[i] = muon -> jetPtRel_;
    mu_jetPtRatio[i] = muon -> jetPtRatio_;
    mu_jetCSV[i] = muon -> jetBtagCSV_;
    mu_sip3D[i] = muon -> sip3d_;
    mu_dxy[i] = muon -> dxy_;
    mu_dz[i] = muon -> dz_;
    mu_segmentCompatibility[i] = muon -> segmentCompatibility_;
    mu_leptonMVA[i] = muon -> mvaRawTTH_;
    mu_mediumID[i] = muon -> passesMediumIdPOG_;
    //
  }
}

void
SyncNtupleManager::read(std::vector<const RecoElectron *> & electrons)
{
  n_presel_ele = electrons.size();
  const Int_t nof_iterations = std::min(n_presel_ele, nof_eles);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoElectron * const electron = electrons[i];
    ele_pt[i] = electron -> pt_;
    ele_eta[i] = electron -> eta_;
    ele_phi[i] = electron -> phi_;
    ele_E[i] = (electron -> p4_).E();
    ele_charge[i] = electron -> charge_;
    ele_miniRelIso[i] = electron -> relIso_;
    ele_miniIsoCharged[i] = electron -> miniIsoCharged_;
    ele_miniIsoNeutral[i] = electron -> miniIsoNeutral_;
    ele_jetNDauChargedMVASel[i] = electron -> jetNDauChargedMVASel_;
    ele_jetPtRel[i] = electron -> jetPtRel_;
    ele_jetPtRatio[i] = electron -> jetPtRatio_;
    ele_jetCSV[i] = electron -> jetBtagCSV_;
    ele_sip3D[i] = electron -> sip3d_;
    ele_dxy[i] = electron -> dxy_;
    ele_dz[i] = electron -> dz_;
    ele_ntMVAeleID[i] = electron -> mvaRawPOG_;
    ele_leptonMVA[i] = electron -> mvaRawTTH_;
    ele_isChargeConsistent[i] = electron -> tightCharge_ == 2 ? 1 : 0;
    ele_passesConversionVeto[i] = electron -> passesConversionVeto_;
    ele_nMissingHits[i] = electron -> nLostHits_;
    //
  }
}

void
SyncNtupleManager::read(std::vector<const RecoHadTau *> & hadtaus)
{
  n_presel_tau = hadtaus.size();
  const Int_t nof_iterations = std::min(n_presel_tau, nof_taus);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoHadTau * const hadtau = hadtaus[i];
    tau_pt[i] = hadtau -> pt_;
    tau_eta[i] = hadtau -> eta_;
    tau_phi[i] = hadtau -> phi_;
    tau_E[i] = (hadtau -> p4_).E();
    tau_charge[i] = hadtau -> charge_;
    tau_dxy[i] = hadtau -> dxy_;
    tau_dz[i] = hadtau -> dz_;
    tau_decayModeFindingOldDMs[i] = hadtau -> decayModeFinding_;
    tau_decayModeFindingNewDMs[i] = hadtau -> decayModeFindingNew_;
    tau_byCombinedIsolationDeltaBetaCorr3Hits[i] = hadtau -> raw_cut_dR05_;

    const Int_t idCI3hit = hadtau -> id_cut_dR05_;
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 1 ? 1 : 0;
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 2 ? 1 : 0;
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits[i] = idCI3hit >= 3 ? 1 : 0;

    const Int_t idCI3hitdR03 = hadtau -> id_cut_dR03_;
    tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 1 ? 1 : 0;
    tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 2 ? 1 : 0;
    tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03[i] = idCI3hitdR03 >= 3 ? 1 : 0;

    const Int_t idMVArun2dR03 = hadtau -> id_mva_dR03_;
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 2 ? 1 : 0;
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 3 ? 1 : 0;
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 4 ? 1 : 0;
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i] = idMVArun2dR03 >= 5 ? 1 : 0;

    const Int_t idAntiMu = hadtau -> antiMuon_;
    tau_againstMuonLoose3[i] = idAntiMu >= 1 ? 1 : 0;
    tau_againstMuonTight3[i] = idAntiMu >= 2 ? 1 : 0;

    const Int_t idAntiErun2 = hadtau -> antiElectron_;
    tau_againstElectronVLooseMVA6[i] = idAntiErun2 >= 1 ? 1 : 0;
    tau_againstElectronLooseMVA6[i] = idAntiErun2 >= 2 ? 1 : 0;
    tau_againstElectronMediumMVA6[i] = idAntiErun2 >= 3 ? 1 : 0;
    tau_againstElectronTightMVA6[i] = idAntiErun2 >= 4 ? 1 : 0;
  }
}

void
SyncNtupleManager::read(std::vector<const RecoJet *> & jets)
{
  n_presel_jet = jets.size();
  const Int_t nof_iterations = std::min(n_presel_jet, nof_jets);
  for(Int_t i = 0; i < nof_iterations; ++i)
  {
    const RecoJet * const jet = jets[i];
    jet_pt[i] = jet -> pt_;
    jet_eta[i] = jet -> eta_;
    jet_phi[i] = jet -> phi_;
    jet_E[i] = (jet -> p4_).E();
    jet_CSV[i] = jet -> BtagCSV_;
  }
}

void
SyncNtupleManager::read(Float_t value,
                        FloatVariableType type)
{
  if     (type == FloatVariableType::PFMET)    PFMET = value;
  else if(type == FloatVariableType::PFMETphi) PFMETphi = value;
  else if(type == FloatVariableType::MHT)      MHT = value;
  else if(type == FloatVariableType::metLD)    metLD = value;
}

void
SyncNtupleManager::reset(bool is_initializing)
{
  nEvent = 0;
  ls = 0;
  run = 0;

  const Int_t nof_mu_iterations = is_initializing ? nof_mus : std::min(n_presel_mu, nof_mus);
  for(Int_t i = 0; i < nof_mu_iterations; ++i)
  {
    mu_pt[i] = placeholder_value;
    mu_eta[i] = placeholder_value;
    mu_phi[i] = placeholder_value;
    mu_E[i] = placeholder_value;
    mu_charge[i] = placeholder_value;
    mu_miniRelIso[i] = placeholder_value;
    mu_miniIsoCharged[i] = placeholder_value;
    mu_miniIsoNeutral[i] = placeholder_value;
    mu_jetNDauChargedMVASel[i] = placeholder_value;
    mu_jetPtRel[i] = placeholder_value;
    mu_jetPtRatio[i] = placeholder_value;
    mu_jetCSV[i] = placeholder_value;
    mu_sip3D[i] = placeholder_value;
    mu_dxy[i] = placeholder_value;
    mu_dz[i] = placeholder_value;
    mu_segmentCompatibility[i] = placeholder_value;
    mu_leptonMVA[i] = placeholder_value;
    mu_mediumID[i] = placeholder_value;
    mu_dpt_div_pt[i] = placeholder_value;
    mu_isfakeablesel[i] = placeholder_value;
    mu_iscutsel[i] = placeholder_value;
    mu_ismvasel[i] = placeholder_value;
  }
  n_presel_mu = placeholder_value;
  n_fakeablesel_mu = placeholder_value;
  n_cutsel_mu = placeholder_value;
  n_mvasel_mu = placeholder_value;

  const Int_t nof_ele_iterations = is_initializing ? nof_eles : std::min(n_presel_ele, nof_eles);
  for(Int_t i = 0; i < nof_ele_iterations; ++i)
  {
    ele_pt[i] = placeholder_value;
    ele_eta[i] = placeholder_value;
    ele_phi[i] = placeholder_value;
    ele_E[i] = placeholder_value;
    ele_charge[i] = placeholder_value;
    ele_miniRelIso[i] = placeholder_value;
    ele_miniIsoCharged[i] = placeholder_value;
    ele_miniIsoNeutral[i] = placeholder_value;
    ele_jetNDauChargedMVASel[i] = placeholder_value;
    ele_jetPtRel[i] = placeholder_value;
    ele_jetPtRatio[i] = placeholder_value;
    ele_jetCSV[i] = placeholder_value;
    ele_sip3D[i] = placeholder_value;
    ele_dxy[i] = placeholder_value;
    ele_dz[i] = placeholder_value;
    ele_ntMVAeleID[i] = placeholder_value;
    ele_leptonMVA[i] = placeholder_value;
    ele_isChargeConsistent[i] = placeholder_value;
    ele_passesConversionVeto[i] = placeholder_value;
    ele_nMissingHits[i] = placeholder_value;
    ele_isfakeablesel[i] = placeholder_value;
    ele_iscutsel[i] = placeholder_value;
    ele_ismvasel[i] = placeholder_value;
  }
  n_presel_ele = placeholder_value;
  n_fakeablesel_ele = placeholder_value;
  n_cutsel_ele = placeholder_value;
  n_mvasel_ele = placeholder_value;

  const Int_t nof_tau_iterations = is_initializing ? nof_taus : std::min(n_presel_tau, nof_taus);
  for(Int_t i = 0; i < nof_tau_iterations; ++i)
  {
    tau_pt[i] = placeholder_value;
    tau_eta[i] = placeholder_value;
    tau_phi[i] = placeholder_value;
    tau_E[i] = placeholder_value;
    tau_charge[i] = placeholder_value;
    tau_dxy[i] = placeholder_value;
    tau_dz[i] = placeholder_value;
    tau_decayModeFindingOldDMs[i] = placeholder_value;
    tau_decayModeFindingNewDMs[i] = placeholder_value;
    tau_byCombinedIsolationDeltaBetaCorr3Hits[i] = placeholder_value;
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits[i] = placeholder_value;
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits[i] = placeholder_value;
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits[i] = placeholder_value;
    tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03[i] = placeholder_value;
    tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03[i] = placeholder_value;
    tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03[i] = placeholder_value;
    tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i] = placeholder_value;
    tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i] = placeholder_value;
    tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i] = placeholder_value;
    tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i] = placeholder_value;
    tau_againstMuonLoose3[i] = placeholder_value;
    tau_againstMuonTight3[i] = placeholder_value;
    tau_againstElectronVLooseMVA6[i] = placeholder_value;
    tau_againstElectronLooseMVA6[i] = placeholder_value;
    tau_againstElectronMediumMVA6[i] = placeholder_value;
    tau_againstElectronTightMVA6[i] = placeholder_value;
  }
  n_presel_tau = placeholder_value;

  const Int_t nof_jet_iterations = is_initializing ? nof_jets : std::min(n_presel_jet, nof_jets);
  for(Int_t i = 0; i < nof_jet_iterations; ++i)
  {
    jet_pt[i] = placeholder_value;
    jet_eta[i] = placeholder_value;
    jet_phi[i] = placeholder_value;
    jet_E[i] = placeholder_value;
    jet_CSV[i] = placeholder_value;
  }
  n_presel_jet = placeholder_value;

  PFMET = placeholder_value;
  PFMETphi = placeholder_value;
  MHT = placeholder_value;
  metLD = placeholder_value;

  lep0_conept = placeholder_value;
  lep1_conePt = placeholder_value;
  mindr_lep0_jet = placeholder_value;
  mindr_lep1_jet = placeholder_value;
  MT_met_lep0 = placeholder_value;
  avg_dr_jet = placeholder_value;
  MVA_2lss_ttV = placeholder_value;
  MVA_2lss_ttbar = placeholder_value;
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
