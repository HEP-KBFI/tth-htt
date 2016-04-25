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

  jet_pt = new Float_t[nof_jets];
  jet_eta = new Float_t[nof_jets];
  jet_phi = new Float_t[nof_jets];
  jet_mass = new Float_t[nof_jets];
  jet_btagCSV = new Float_t[nof_jets];

  if(outputTree)
  {
    const char * mstr = "mu";
    const char * jstr = "jet";

    outputTree -> Branch(Form("n_presel_%s", mstr), &(n_presel_mu), Form("n_presel_%s/I", mstr));
    outputTree -> Branch(Form("n_presel_%s", jstr), &(n_presel_jet), Form("n_presel_%s/I", jstr));

    for(Int_t i = 0; i < nof_mus; ++i)
    {
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "pt"), &(mu_pt[i]), Form("%s_%d_%s/F", mstr, i, "pt"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "eta"), &(mu_eta[i]), Form("%s_%d_%s/F", mstr, i, "eta"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "phi"), &(mu_phi[i]), Form("%s_%d_%s/F", mstr, i, "phi"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "E"), &(mu_E[i]), Form("%s_%d_%s/F", mstr, i, "E"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "charge"), &(mu_charge[i]), Form("%s_%d_%s/I", mstr, i, "charge"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "miniRelIso"), &(mu_miniRelIso[i]), Form("%s_%d_%s/F", mstr, i, "miniRelIso"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "miniIsoCharged"), &(mu_miniIsoCharged[i]), Form("%s_%d_%s/F", mstr, i, "miniIsoCharged"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "miniIsoNeutral"), &(mu_miniIsoNeutral[i]), Form("%s_%d_%s/F", mstr, i, "miniIsoNeutral"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "jetNDauChargedMVASel"), &(mu_jetNDauChargedMVASel[i]), Form("%s_%d_%s/F", mstr, i, "jetNDauChargedMVASel"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "jetPtRel"), &(mu_jetPtRel[i]), Form("%s_%d_%s/F", mstr, i, "jetPtRel"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "jetPtRatio"), &(mu_jetPtRatio[i]), Form("%s_%d_%s/F", mstr, i, "jetPtRatio"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "jetCSV"), &(mu_jetCSV[i]), Form("%s_%d_%s/F", mstr, i, "jetCSV"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "sip3D"), &(mu_sip3D[i]), Form("%s_%d_%s/F", mstr, i, "sip3D"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "dxy"), &(mu_dxy[i]), Form("%s_%d_%s/F", mstr, i, "dxy"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "dz"), &(mu_dz[i]), Form("%s_%d_%s/F", mstr, i, "dz"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "segmentCompatibility"), &(mu_segmentCompatibility[i]), Form("%s_%d_%s/I", mstr, i, "segmentCompatibility"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "leptonMVA"), &(mu_leptonMVA[i]), Form("%s_%d_%s/F", mstr, i, "leptonMVA"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "mediumID"), &(mu_mediumID[i]), Form("%s_%d_%s/F", mstr, i, "mediumID"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "dpt_div_pt"), &(mu_dpt_div_pt[i]), Form("%s_%d_%s/F", mstr, i, "dpt_div_pt"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "isfakeablesel"), &(mu_isfakeablesel[i]), Form("%s_%d_%s/I", mstr, i, "isfakeablesel"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "iscutsel"), &(mu_iscutsel[i]), Form("%s_%d_%s/I", mstr, i, "iscutsel"));
      outputTree -> Branch(Form("%s_%d_%s", mstr, i, "ismvasel"), &(mu_ismvasel[i]), Form("%s_%d_%s/I", mstr, i, "ismvasel"));
    }

    for(Int_t i = 0; i < nof_jets; ++i)
    {
      outputTree -> Branch(Form("%s_%d_%s", jstr, i, "pt"), &(jet_pt[i]), Form("%s_%d_%s/F", jstr, i, "pt"));
      outputTree -> Branch(Form("%s_%d_%s", jstr, i, "eta"), &(jet_eta[i]), Form("%s_%d_%s/F", jstr, i, "eta"));
      outputTree -> Branch(Form("%s_%d_%s", jstr, i, "phi"), &(jet_phi[i]), Form("%s_%d_%s/F", jstr, i, "phi"));
      outputTree -> Branch(Form("%s_%d_%s", jstr, i, "mass"), &(jet_mass[i]), Form("%s_%d_%s/F", jstr, i, "mass"));
      outputTree -> Branch(Form("%s_%d_%s", jstr, i, "btagCSV"), &(jet_btagCSV[i]), Form("%s_%d_%s/F", jstr, i, "btagCSV"));
    }

    reset();
  }
  else
    std::cerr << "SyncNtuple:WARNING:Should initialize the instance only once!\n";
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
  }
}

void
SyncNtupleManager::reset()
{
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
