#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include <string> // std::string
#include <vector> // std::vector<>

#include <TFile.h> // TFile
#include <TTree.h> // TTree
#include <Rtypes.h> // Float_t, Int_t

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

class SyncNtupleManager
{
public:
  SyncNtupleManager(const std::string & outputFileName,
                    const std::string & outputTreeName);
  ~SyncNtupleManager();

  void initializeBranches();
  void read(std::vector<const RecoMuon *> & muons);
  void read(std::vector<const RecoElectron *> & electrons);
  void read(std::vector<const RecoHadTau *> & hadtaus);
  void read(std::vector<const RecoJet *> & jets);
  void fill();
  void write();
private:
  void reset();

  TFile * outputFile;
  TTree * outputTree;
  const Int_t placeholder_value;

  const Int_t nof_mus;
  const Int_t nof_eles;
  const Int_t nof_taus;
  const Int_t nof_jets;

  ULong64_t nEvent;
  UInt_t ls;
  UInt_t run;

  Int_t n_presel_mu;
  Int_t n_fakeablesel_mu;
  Int_t n_cutsel_mu;
  Int_t n_mvasel_mu;
  Float_t * mu_pt;
  Float_t * mu_eta;
  Float_t * mu_phi;
  Float_t * mu_E;
  Int_t * mu_charge;
  Float_t * mu_miniRelIso;
  Float_t * mu_miniIsoCharged;
  Float_t * mu_miniIsoNeutral;
  Float_t * mu_jetNDauChargedMVASel;
  Float_t * mu_jetPtRel;
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_sip3D;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Int_t * mu_segmentCompatibility;
  Float_t * mu_leptonMVA;
  Float_t * mu_mediumID;
  Float_t * mu_dpt_div_pt;
  Int_t * mu_isfakeablesel;
  Int_t * mu_iscutsel;
  Int_t * mu_ismvasel;

  Int_t n_presel_ele;
  Int_t n_fakeablesel_ele;
  Int_t n_cutsel_ele;
  Int_t n_mvasel_ele;
  Float_t * ele_pt;
  Float_t * ele_eta;
  Float_t * ele_phi;
  Float_t * ele_E;
  Int_t * ele_charge;
  Float_t * ele_miniRelIso;
  Float_t * ele_miniIsoCharged;
  Float_t * ele_miniIsoNeutral;
  Float_t * ele_jetNDauChargedMVASel;
  Float_t * ele_jetPtRel;
  Float_t * ele_jetPtRatio;
  Float_t * ele_jetCSV;
  Float_t * ele_sip3D;
  Float_t * ele_dxy;
  Float_t * ele_dz;
  Float_t * ele_ntMVAeleID;
  Float_t * ele_leptonMVA;
  Float_t * ele_isChargeConsistent;
  Float_t * ele_passesConversionVeto;
  Int_t * ele_nMissingHits;
  Int_t * ele_isfakeablesel;
  Int_t * ele_iscutsel;
  Int_t * ele_ismvasel;

  Int_t n_presel_tau;
  Float_t * tau_pt;
  Float_t * tau_eta;
  Float_t * tau_phi;
  Float_t * tau_E;
  Int_t * tau_charge;
  Float_t * tau_dxy;
  Float_t * tau_dz;
  Int_t * tau_decayModeFindingOldDMs;
  Int_t * tau_decayModeFindingNewDMs;
  Int_t * tau_byCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byTightCombinedIsolationDeltaBetaCorr3Hits;
  Int_t * tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t * tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_againstMuonLoose3;
  Int_t * tau_againstMuonTight3;
  Int_t * tau_againstElectronVLooseMVA6;
  Int_t * tau_againstElectronLooseMVA6;
  Int_t * tau_againstElectronMediumMVA6;
  Int_t * tau_againstElectronTightMVA6;

  Int_t n_presel_jet;
  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_mass;
  Float_t * jet_btagCSV;

  Float_t PFMET;
  Float_t PFMETphi;
  Float_t MHT;
  Float_t metLD;

  Float_t lep0_conept;
  Float_t lep1_conePt;
  Float_t mindr_lep0_jet;
  Float_t mindr_lep1_jet;
  Float_t MT_met_lep0;
  Float_t avg_dr_jet;
  Float_t MVA_2lss_ttV;
  Float_t MVA_2lss_ttbar;
};

#endif // SYNCNTUPLEMANAGER_H
