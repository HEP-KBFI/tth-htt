#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<,>

#include <TFile.h> // TFile
#include <TTree.h> // TTree
#include <Rtypes.h> // Float_t, Int_t

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"
#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h"
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath

enum FloatVariableType { PFMET, PFMETphi, MHT, metLD, mvaOutput_ttV, mvaOutput_ttbar, MC_weight, FR_weight, triggerSF_weight, leptonSF_weight, bTagSF_weight, PU_weight, hadTauSF_weight, genWeight, lumiScale };

class SyncNtupleManager
{
public:
  SyncNtupleManager(const std::string & outputFileName,
                    const std::string & outputTreeName);
  ~SyncNtupleManager();

  void initializeBranches();
  void initializeHLTBranches(const std::vector<std::vector<hltPath *>> & hltPaths);
  void readRunLumiEvent(UInt_t run,
                        UInt_t lumi,
                        ULong64_t event);
  void read(std::vector<const RecoMuon *> & muons,
            std::vector<const RecoMuon *> & fakeable_muons,
            std::vector<const RecoMuon *> & cutbased_muons,
            std::vector<const RecoMuon *> & mvabased_muons);
  void read(std::vector<const RecoElectron *> & electrons,
            std::vector<const RecoElectron *> & fakeable_electrons,
            std::vector<const RecoElectron *> & cutbased_electrons,
            std::vector<const RecoElectron *> & mvabased_electrons);
  void read(std::vector<const RecoHadTau *> & hadtaus);
  void read(std::vector<const RecoJet *> & jets);
  void read(const std::map<std::string, Double_t> & mvaInputs);
  void read(Float_t value,
            FloatVariableType type);
  void read(const std::vector<std::vector<hltPath *>> & hltPaths);
  void fill();
  void write();
private:
  void reset(bool is_initializing);
  std::string hltMangle(const std::string & hltBranchName) const;

  TFile * outputFile;
  TTree * outputTree;
  static const Int_t placeholder_value;

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
  Int_t * mu_jetNDauChargedMVASel;
  Float_t * mu_jetPtRel;
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_sip3D;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Float_t * mu_segmentCompatibility;
  Float_t * mu_leptonMVA;
  Float_t * mu_conept;
  Int_t * mu_mediumID;
#ifdef DPT_DIV_PT
  Float_t * mu_dpt_div_pt;
#endif
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
  Int_t * ele_jetNDauChargedMVASel;
  Float_t * ele_jetPtRel;
  Float_t * ele_jetPtRatio;
  Float_t * ele_jetCSV;
  Float_t * ele_sip3D;
  Float_t * ele_dxy;
  Float_t * ele_dz;
  Float_t * ele_ntMVAeleID;
  Float_t * ele_leptonMVA;
  Float_t * ele_conept;
  Int_t * ele_isChargeConsistent;
  Int_t * ele_passesConversionVeto;
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
  Float_t * tau_byCombinedIsolationDeltaBetaCorr3Hits;
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
  Int_t * tau_againstElectronVTightMVA6;

  Int_t n_presel_jet;
  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_E;
  Float_t * jet_CSV;

  Float_t PFMET;
  Float_t PFMETphi;
  Float_t MHT;
  Float_t metLD;

  std::map<std::string, Int_t> hltMap;

  Float_t lep0_conept;
  Float_t lep1_conept;
  Float_t mindr_lep0_jet;
  Float_t mindr_lep1_jet;
  Float_t MT_met_lep0;
  Float_t avg_dr_jet;
  Float_t n_jet25_recl;
  Float_t MVA_2lss_ttV;
  Float_t MVA_2lss_ttbar;
  
  Float_t MC_weight;
  Float_t FR_weight;
  Float_t triggerSF_weight;
  Float_t leptonSF_weight;
  Float_t bTagSF_weight;
  Float_t PU_weight;
  Float_t hadTauSF_weight;
  Float_t genWeight;
  Float_t lumiScale;
};

#endif // SYNCNTUPLEMANAGER_H
