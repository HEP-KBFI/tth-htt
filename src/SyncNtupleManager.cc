#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManager.h"

#include <algorithm> // std::min()

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
  mu_pt = new Float_t[nof_mus];
  mu_eta = new Float_t[nof_mus];
  mu_phi = new Float_t[nof_mus];
  mu_E = new Float_t[nof_mus];
  mu_charge = new Int_t[nof_mus];
  mu_miniRelIso = new Float_t[nof_mus];
  mu_miniIsoCharged = new Float_t[nof_mus];
  mu_miniIsoNeutral = new Float_t[nof_mus];
  mu_jetNDauChargedMVASel = new Float_t[nof_mus];
  mu_jetPtRel = new Float_t[nof_mus];
  mu_jetPtRatio = new Float_t[nof_mus];
  mu_jetCSV = new Float_t[nof_mus];
  mu_sip3D = new Float_t[nof_mus];
  mu_dxy = new Float_t[nof_mus];
  mu_dz = new Float_t[nof_mus];
  mu_segmentCompatibility = new Int_t[nof_mus];
  mu_leptonMVA = new Float_t[nof_mus];
  mu_mediumID = new Float_t[nof_mus];
  mu_dpt_div_pt = new Float_t[nof_mus];
  mu_isfakeablesel = new Int_t[nof_mus];
  mu_iscutsel = new Int_t[nof_mus];
  mu_ismvasel = new Int_t[nof_mus];

  ele_pt = new Float_t[nof_eles];
  ele_eta = new Float_t[nof_eles];
  ele_phi = new Float_t[nof_eles];
  ele_E = new Float_t[nof_eles];
  ele_charge = new Int_t[nof_eles];
  ele_miniRelIso = new Float_t[nof_eles];
  ele_miniIsoCharged = new Float_t[nof_eles];
  ele_miniIsoNeutral = new Float_t[nof_eles];
  ele_jetNDauChargedMVASel = new Float_t[nof_eles];
  ele_jetPtRel = new Float_t[nof_eles];
  ele_jetPtRatio = new Float_t[nof_eles];
  ele_jetCSV = new Float_t[nof_eles];
  ele_sip3D = new Float_t[nof_eles];
  ele_dxy = new Float_t[nof_eles];
  ele_dz = new Float_t[nof_eles];
  ele_ntMVAeleID = new Float_t[nof_eles];
  ele_leptonMVA = new Float_t[nof_eles];
  ele_isChargeConsistent = new Float_t[nof_eles];
  ele_passesConversionVeto = new Float_t[nof_eles];
  ele_nMissingHits = new Int_t[nof_eles];
  ele_isfakeablesel = new Int_t[nof_eles];
  ele_iscutsel = new Int_t[nof_eles];
  ele_ismvasel = new Int_t[nof_eles];

  tau_pt = new Float_t[nof_eles];
  tau_eta = new Float_t[nof_eles];
  tau_phi = new Float_t[nof_eles];
  tau_E = new Float_t[nof_eles];
  tau_charge = new Int_t[nof_eles];
  tau_dxy = new Float_t[nof_eles];
  tau_dz = new Float_t[nof_eles];
  tau_decayModeFindingOldDMs = new Int_t[nof_eles];
  tau_decayModeFindingNewDMs = new Int_t[nof_eles];
  tau_byCombinedIsolationDeltaBetaCorr3Hits = new Int_t[nof_eles];
  tau_byLooseCombinedIsolationDeltaBetaCorr3Hits = new Int_t[nof_eles];
  tau_byMediumCombinedIsolationDeltaBetaCorr3Hits = new Int_t[nof_eles];
  tau_byTightCombinedIsolationDeltaBetaCorr3Hits = new Int_t[nof_eles];
  tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03 = new Int_t[nof_eles];
  tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03 = new Int_t[nof_eles];
  tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03 = new Int_t[nof_eles];
  tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT = new Int_t[nof_eles];
  tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT = new Int_t[nof_eles];
  tau_byTightIsolationMVArun2v1DBdR03oldDMwLT = new Int_t[nof_eles];
  tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT = new Int_t[nof_eles];
  tau_againstMuonLoose3 = new Int_t[nof_eles];
  tau_againstMuonTight3 = new Int_t[nof_eles];
  tau_againstElectronVLooseMVA6 = new Int_t[nof_eles];
  tau_againstElectronLooseMVA6 = new Int_t[nof_eles];
  tau_againstElectronMediumMVA6 = new Int_t[nof_eles];
  tau_againstElectronTightMVA6 = new Int_t[nof_eles];

  jet_pt = new Float_t[nof_jets];
  jet_eta = new Float_t[nof_jets];
  jet_phi = new Float_t[nof_jets];
  jet_mass = new Float_t[nof_jets];
  jet_btagCSV = new Float_t[nof_jets];

  if(outputTree)
  {
    const char * mstr = "mu";
    const char * estr = "ele";
    const char * tstr = "tau";
    const char * jstr = "jet";

    outputTree -> Branch("nEvent", &(nEvent), "nEvent/l");
    outputTree -> Branch("ls", &(ls), "ls/i");
    outputTree -> Branch("run", &(run), "run/i");

    outputTree -> Branch(Form("n_presel_%s", mstr), &(n_presel_mu), Form("n_presel_%s/I", mstr));
    outputTree -> Branch(Form("n_fakeablesel_%s", mstr), &(n_fakeablesel_mu), Form("n_fakeablesel_%s/I", mstr));
    outputTree -> Branch(Form("n_cutsel_%s", mstr), &(n_cutsel_mu), Form("n_cutsel_%s/I", mstr));
    outputTree -> Branch(Form("n_mvasel_%s", mstr), &(n_mvasel_mu), Form("n_mvasel_%s/I", mstr));

    outputTree -> Branch(Form("n_presel_%s", estr), &(n_presel_ele), Form("n_presel_%s/I", estr));
    outputTree -> Branch(Form("n_fakeablesel_%s", estr), &(n_fakeablesel_ele), Form("n_fakeablesel_%s/I", estr));
    outputTree -> Branch(Form("n_cutsel_%s", estr), &(n_cutsel_ele), Form("n_cutsel_%s/I", estr));
    outputTree -> Branch(Form("n_mvasel_%s", estr), &(n_mvasel_ele), Form("n_mvasel_%s/I", estr));

    outputTree -> Branch(Form("n_presel_%s", tstr), &(n_presel_tau), Form("n_presel_%s/I", tstr));
    outputTree -> Branch(Form("n_presel_%s", jstr), &(n_presel_jet), Form("n_presel_%s/I", jstr));

    for(Int_t i = 0; i < nof_mus; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "pt"), &(mu_pt[i]), Form("%s%d_%s/F", mstr, i, "pt"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "eta"), &(mu_eta[i]), Form("%s%d_%s/F", mstr, i, "eta"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "phi"), &(mu_phi[i]), Form("%s%d_%s/F", mstr, i, "phi"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "E"), &(mu_E[i]), Form("%s%d_%s/F", mstr, i, "E"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "charge"), &(mu_charge[i]), Form("%s%d_%s/I", mstr, i, "charge"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniRelIso"), &(mu_miniRelIso[i]), Form("%s%d_%s/F", mstr, i, "miniRelIso"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniIsoCharged"), &(mu_miniIsoCharged[i]), Form("%s%d_%s/F", mstr, i, "miniIsoCharged"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "miniIsoNeutral"), &(mu_miniIsoNeutral[i]), Form("%s%d_%s/F", mstr, i, "miniIsoNeutral"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetNDauChargedMVASel"), &(mu_jetNDauChargedMVASel[i]), Form("%s%d_%s/F", mstr, i, "jetNDauChargedMVASel"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetPtRel"), &(mu_jetPtRel[i]), Form("%s%d_%s/F", mstr, i, "jetPtRel"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetPtRatio"), &(mu_jetPtRatio[i]), Form("%s%d_%s/F", mstr, i, "jetPtRatio"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "jetCSV"), &(mu_jetCSV[i]), Form("%s%d_%s/F", mstr, i, "jetCSV"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "sip3D"), &(mu_sip3D[i]), Form("%s%d_%s/F", mstr, i, "sip3D"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dxy"), &(mu_dxy[i]), Form("%s%d_%s/F", mstr, i, "dxy"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dz"), &(mu_dz[i]), Form("%s%d_%s/F", mstr, i, "dz"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "segmentCompatibility"), &(mu_segmentCompatibility[i]), Form("%s%d_%s/I", mstr, i, "segmentCompatibility"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "leptonMVA"), &(mu_leptonMVA[i]), Form("%s%d_%s/F", mstr, i, "leptonMVA"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "mediumID"), &(mu_mediumID[i]), Form("%s%d_%s/F", mstr, i, "mediumID"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "dpt_div_pt"), &(mu_dpt_div_pt[i]), Form("%s%d_%s/F", mstr, i, "dpt_div_pt"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "isfakeablesel"), &(mu_isfakeablesel[i]), Form("%s%d_%s/I", mstr, i, "isfakeablesel"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "iscutsel"), &(mu_iscutsel[i]), Form("%s%d_%s/I", mstr, i, "iscutsel"));
      outputTree -> Branch(Form("%s%d_%s", mstr, i, "ismvasel"), &(mu_ismvasel[i]), Form("%s%d_%s/I", mstr, i, "ismvasel"));
    }

    for(Int_t i = 0; i < nof_eles; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", estr, i, "pt"), &(ele_pt[i]), Form("%s%d_%s/F", estr, i, "pt"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "eta"), &(ele_eta[i]), Form("%s%d_%s/F", estr, i, "eta"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "phi"), &(ele_phi[i]), Form("%s%d_%s/F", estr, i, "phi"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "E"), &(ele_E[i]), Form("%s%d_%s/F", estr, i, "E"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "charge"), &(ele_charge[i]), Form("%s%d_%s/I", estr, i, "charge"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniRelIso"), &(ele_miniRelIso[i]), Form("%s%d_%s/F", estr, i, "miniRelIso"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniIsoCharged"), &(ele_miniIsoCharged[i]), Form("%s%d_%s/F", estr, i, "miniIsoCharged"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "miniIsoNeutral"), &(ele_miniIsoNeutral[i]), Form("%s%d_%s/F", estr, i, "miniIsoNeutral"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetNDauChargedMVASel"), &(ele_jetNDauChargedMVASel[i]), Form("%s%d_%s/F", estr, i, "jetNDauChargedMVASel"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetPtRel"), &(ele_jetPtRel[i]), Form("%s%d_%s/F", estr, i, "jetPtRel"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetPtRatio"), &(ele_jetPtRatio[i]), Form("%s%d_%s/F", estr, i, "jetPtRatio"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "jetCSV"), &(ele_jetCSV[i]), Form("%s%d_%s/F", estr, i, "jetCSV"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "sip3D"), &(ele_sip3D[i]), Form("%s%d_%s/F", estr, i, "sip3D"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "dxy"), &(ele_dxy[i]), Form("%s%d_%s/F", estr, i, "dxy"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "dz"), &(ele_dz[i]), Form("%s%d_%s/F", estr, i, "dz"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "ntMVAeleID"), &(ele_ntMVAeleID[i]), Form("%s%d_%s/F", estr, i, "ntMVAeleID"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "leptonMVA"), &(ele_leptonMVA[i]), Form("%s%d_%s/F", estr, i, "leptonMVA"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "isChargeConsistent"), &(ele_isChargeConsistent[i]), Form("%s%d_%s/F", estr, i, "isChargeConsistent"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "passesConversionVeto"), &(ele_passesConversionVeto[i]), Form("%s%d_%s/F", estr, i, "passesConversionVeto"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "nMissingHits"), &(ele_nMissingHits[i]), Form("%s%d_%s/I", estr, i, "nMissingHits"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "isfakeablesel"), &(ele_isfakeablesel[i]), Form("%s%d_%s/I", estr, i, "isfakeablesel"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "iscutsel"), &(ele_iscutsel[i]), Form("%s%d_%s/I", estr, i, "iscutsel"));
      outputTree -> Branch(Form("%s%d_%s", estr, i, "ismvasel"), &(ele_ismvasel[i]), Form("%s%d_%s/I", estr, i, "ismvasel"));
    }

    for(Int_t i = 0; i < nof_taus; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "pt"), &(tau_pt[i]), Form("%s%d_%s/F", tstr, i, "pt"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "eta"), &(tau_eta[i]), Form("%s%d_%s/F", tstr, i, "eta"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "phi"), &(tau_phi[i]), Form("%s%d_%s/F", tstr, i, "phi"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "E"), &(tau_E[i]), Form("%s%d_%s/F", tstr, i, "E"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "charge"), &(tau_charge[i]), Form("%s%d_%s/I", tstr, i, "charge"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "dxy"), &(tau_dxy[i]), Form("%s%d_%s/F", tstr, i, "dxy"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "dz"), &(tau_dz[i]), Form("%s%d_%s/F", tstr, i, "dz"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "decayModeFindingOldDMs"), &(tau_decayModeFindingOldDMs[i]), Form("%s%d_%s/I", tstr, i, "decayModeFindingOldDMs"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "decayModeFindingNewDMs"), &(tau_decayModeFindingNewDMs[i]), Form("%s%d_%s/I", tstr, i, "decayModeFindingNewDMs"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/I", tstr, i, "byCombinedIsolationDeltaBetaCorr3Hits"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byLooseCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/I", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3Hits"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byMediumCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/I", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3Hits"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3Hits"), &(tau_byTightCombinedIsolationDeltaBetaCorr3Hits[i]), Form("%s%d_%s/I", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3Hits"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/I", tstr, i, "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/I", tstr, i, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3HitsdR03"), &(tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03[i]), Form("%s%d_%s/I", tstr, i, "byTightCombinedIsolationDeltaBetaCorr3HitsdR03"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byLooseIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/I", tstr, i, "byLooseIsolationMVArun2v1DBdR03oldDMwLT"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byMediumIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/I", tstr, i, "byMediumIsolationMVArun2v1DBdR03oldDMwLT"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byTightIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byTightIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/I", tstr, i, "byTightIsolationMVArun2v1DBdR03oldDMwLT"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "byVTightIsolationMVArun2v1DBdR03oldDMwLT"), &(tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT[i]), Form("%s%d_%s/I", tstr, i, "byVTightIsolationMVArun2v1DBdR03oldDMwLT"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstMuonLoose3"), &(tau_againstMuonLoose3[i]), Form("%s%d_%s/I", tstr, i, "againstMuonLoose3"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstMuonTight3"), &(tau_againstMuonTight3[i]), Form("%s%d_%s/I", tstr, i, "againstMuonTight3"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronVLooseMVA6"), &(tau_againstElectronVLooseMVA6[i]), Form("%s%d_%s/I", tstr, i, "againstElectronVLooseMVA6"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronLooseMVA6"), &(tau_againstElectronLooseMVA6[i]), Form("%s%d_%s/I", tstr, i, "againstElectronLooseMVA6"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronMediumMVA6"), &(tau_againstElectronMediumMVA6[i]), Form("%s%d_%s/I", tstr, i, "againstElectronMediumMVA6"));
      outputTree -> Branch(Form("%s%d_%s", tstr, i, "againstElectronTightMVA6"), &(tau_againstElectronTightMVA6[i]), Form("%s%d_%s/I", tstr, i, "againstElectronTightMVA6"));
    }

    for(Int_t i = 0; i < nof_jets; ++i)
    {
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "pt"), &(jet_pt[i]), Form("%s%d_%s/F", jstr, i, "pt"));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "eta"), &(jet_eta[i]), Form("%s%d_%s/F", jstr, i, "eta"));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "phi"), &(jet_phi[i]), Form("%s%d_%s/F", jstr, i, "phi"));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "mass"), &(jet_mass[i]), Form("%s%d_%s/F", jstr, i, "mass"));
      outputTree -> Branch(Form("%s%d_%s", jstr, i, "btagCSV"), &(jet_btagCSV[i]), Form("%s%d_%s/F", jstr, i, "btagCSV"));
    }

    outputTree -> Branch("PFMET", &(PFMET), "PFMET/F");
    outputTree -> Branch("PFMETphi", &(PFMETphi), "PFMETphi/F");
    outputTree -> Branch("MHT", &(MHT), "MHT/F");
    outputTree -> Branch("metLD", &(metLD), "metLD/F");

    outputTree -> Branch("lep0_conept", &(lep0_conept), "lep0_conept/F");
    outputTree -> Branch("lep1_conePt", &(lep1_conePt), "lep1_conePt/F");
    outputTree -> Branch("mindr_lep0_jet", &(mindr_lep0_jet), "mindr_lep0_jet/F");
    outputTree -> Branch("mindr_lep1_jet", &(mindr_lep1_jet), "mindr_lep1_jet/F");
    outputTree -> Branch("MT_met_lep0", &(MT_met_lep0), "MT_met_lep0/F");
    outputTree -> Branch("avg_dr_jet", &(avg_dr_jet), "avg_dr_jet/F");
    outputTree -> Branch("MVA_2lss_ttV", &(MVA_2lss_ttV), "MVA_2lss_ttV/F");
    outputTree -> Branch("MVA_2lss_ttbar", &(MVA_2lss_ttbar), "MVA_2lss_ttbar/F");

    reset();
  }
  else
    std::cerr << "SyncNtuple:WARNING:Should initialize the instance only once!\n";
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
    mu_charge[i] = muon -> pdgId_ > 0 ? 1 : -1;
    //
    mu_sip3D[i] = muon -> sip3d_;
    mu_dxy[i] = muon -> dxy_;
    mu_dz[i] = muon -> dz_;
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
    //
    ele_sip3D[i] = electron -> sip3d_;
    ele_dxy[i] = electron -> dxy_;
    ele_dz[i] = electron -> dz_;
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
    //
    tau_dz[i] = hadtau -> dz_;
    //
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
    jet_mass[i] = jet -> mass_;
    jet_btagCSV[i] = jet -> BtagCSV_;
  }
}

void
SyncNtupleManager::reset()
{
  nEvent = 0;
  ls = 0;
  run = 0;

  const Int_t nof_mu_iterations = std::min(n_presel_mu, nof_mus);
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

  const Int_t nof_ele_iterations = std::min(n_presel_ele, nof_eles);
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

  const Int_t nof_tau_iterations = std::min(n_presel_tau, nof_taus);
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

  const Int_t nof_jet_iterations = std::min(n_presel_jet, nof_jets);
  for(Int_t i = 0; i < nof_jet_iterations; ++i)
  {
    jet_pt[i] = placeholder_value;
    jet_eta[i] = placeholder_value;
    jet_phi[i] = placeholder_value;
    jet_mass[i] = placeholder_value;
    jet_btagCSV[i] = placeholder_value;
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
  reset();
}

void
SyncNtupleManager::write()
{
  outputFile -> cd();
  outputTree -> Write();
}
