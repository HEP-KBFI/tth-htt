#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_arithmetic<>

// forward declarations
class TFile;
class RecoMuon;
class RecoElectron;
class RecoHadTau;
class RecoJet;
class hltPath;

enum FloatVariableType
{
//--- MET/MHT
  PFMET,
  PFMETphi,
  MHT,                      ///< vectorial sum of preselected leptons (including taus) + jets
  metLD,
//--- Additional event-level MVA variables
  lep0_conept,              ///< cone pT of leading lepton : if the lepton is fakeable, 0.90*pT(jet) with JECLepAware, else pT(lep)
  lep1_conept,              ///< cone pT of subleading lepton : if the lepton is fakeable, 0.90*pT(jet) with JECLepAware, else pT(lep)
  mindr_lep0_jet,           ///< min dR between leading lepton and preselected jets
  mindr_lep1_jet,           ///< min dR between subleading lepton and preselected jets
  mindr_lep2_jet,           ///< min dR between third lepton and preselected jets
  mindr_tau_jet,            ///< min dR between tau and preselected jets
  MT_met_lep0,              ///< transverse mass of leading lepton and MET (using lep0_conept)
  avg_dr_jet,               ///< average dR between all the pairs of preselected jets
  MVA_2lss_ttV,             ///< ttH vs ttV MVA for 2lss
  MVA_2lss_ttbar,           ///< ttH vs ttbar MVA for 2lss
  tt_deltaR,                ///< deltaR between 2 selected taus
  tt_mvis,                  ///< visible mass of the 2 selected taus
  tt_pt,                    ///< pT of the di-tau pair
  max_dr_jet,               ///< maximum dR between preselected jets
  HT,                       ///< linear sum of preselected leptons (including taus) + jet pT
  MVA_1l2tau_ttbar,         ///< ttH vs ttbar MVA for 1l2tau
  MVA_1l2tau_ttbar_v2,      ///< ttH vs ttbar MVA for 1l2tau v2
  MVA_1l2tau_ttZ_v2,        ///< ttH vs ttZ MVA for 1l2tau v2
  MVA_1l2tau_2Dbin_v2,      ///< 2D bin ttH vs ttbar/ttZ MVA for 1l2tau v2
  mvis_l1tau,               ///< visible mass of subleading lepton and tau
  dR_l0tau,                 ///< deltaR between leading lepton and tau
  dR_l1tau,                 ///< deltaR between subleading lepton and tau
  dR_l2tau,                 ///< deltaR between trailing lepton and tau
  MT_met_lep2,              ///< transverse mass of trailing lepton and MET (using cone pt)
  MVA_3l1tau_ttbar,         ///< ttH vs ttbar MVA for 3l1tau
  MVA_3l1tau_ttV,           ///< ttH vs ttV MVA for 3l1tau
  MVA_3l1tau_2Dbin,         ///< 2D bin ttH vs ttbar/ttZ MVA for 3l1tau
//--- Event weights
  FR_weight,                ///< weight used for fake rate reweighting
  triggerSF_weight,         ///< scale factor for trigger
  leptonSF_weight,          ///< scale factor for lepton ID
  tauSF_weight,             ///< scale factor for tau ID
  bTagSF_weight,            ///< scale factor for b-tagging
  PU_weight,                ///< PU weight
  MC_weight,                ///< MC weight
//--- MEM variables
  Integral_ttH,             ///< ttH weight
  Integral_ttZ,             ///< ttZ (Ztautau) weight
  Integral_ttZ_Zll,         ///< ttZ Z->ll weight
  Integral_ttbar,           ///< ttbar weight
  integration_type,
  MEM_LR,
  dR_leps,                  ///< deltaR between two leading leptons
  mvis_l0tau,               ///< visible mass of leading lepton and tau
  MVA_2lSS1tau_noMEM_ttbar, ///< ttH vs ttbar MVA for 2lSS1tau w/o MEM LR as input
  MVA_2lSS1tau_noMEM_ttV,   ///< ttH vs ttV MVA for 2lSS1tau w/o MEM LR as input
  MVA_2lSS1tau_noMEM_2Dbin, ///< 2D bin ttH vs ttbar/ttZ MVA for 2lSS1tau w/o MEM LR as input
  MVA_2lSS1tau_MEM_ttbar,   ///< ttH vs ttbar MVA for 2lSS1tau w/ MEM LR as input
  MVA_2lSS1tau_MEM_ttV,     ///< ttH vs ttV MVA for 2lSS1tau w/ MEM LR as input
  MVA_2lSS1tau_MEM_2Dbin,   ///< 2D bin ttH vs ttbar/ttZ MVA for 2lSS1tau w/ MEM LR as input
//--- custom additional branches (not necessary in sync)
  lep2_conept,              ///< cone pT of third lepton : if the lepton is fakeable, 0.90*pT(jet) with JECLepAware, else pT(lep)
  lep3_conept,              ///< cone pT of fourth lepton : if the lepton is fakeable, 0.90*pT(jet) with JECLepAware, else pT(lep)
  mindr_lep3_jet,           ///< min dR between fourth lepton and preselected jets
  MT_met_lep1,              ///< transverse mass of subleading lepton and MET (using cone pt)
  MT_met_lep3,              ///< transverse mass of fourth lepton and MET (using cone pt)
  genWeight
};

class SyncNtupleManager
{
public:
  SyncNtupleManager(const std::string & outputFileName,
                    const std::string & outputTreeName);
  ~SyncNtupleManager();

  void initializeBranches();
  void initializeHLTBranches(const std::vector<std::vector<hltPath *>> & hltPaths);
  void read(const EventInfo & eventInfo);
  void read(const std::vector<const RecoMuon *> & muons,
            const std::vector<const RecoMuon *> & fakeable_muons,
            const std::vector<const RecoMuon *> & cutbased_muons,
            const std::vector<const RecoMuon *> & mvabased_muons);
  void read(const std::vector<const RecoElectron *> & electrons,
            const std::vector<const RecoElectron *> & fakeable_electrons,
            const std::vector<const RecoElectron *> & cutbased_electrons,
            const std::vector<const RecoElectron *> & mvabased_electrons);
  void read(const std::vector<const RecoHadTau *> & hadtaus);
  void read(const std::vector<const RecoJet *> & jets);
  void read(Float_t value,
            FloatVariableType type);
  void read(const std::vector<std::vector<hltPath *>> & hltPaths);
  void read(bool is_genMatched, int n_tags, int n_tags_loose);
  void fill();
  void write();

  static const Int_t placeholder_value;

private:
  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(const std::string & infix,
              int count,
              T * & var,
              const std::string & label)
  {
    if(count > 0)
    {
      var = new T[count];
      for(int i = 0; i < count; ++i)
      {
        var[i] = placeholder_value;
        const std::string branchName = Form("%s%d_%s", infix.c_str(), i, label.c_str());
        outputTree -> Branch(branchName.c_str(), &(var[i]), Form("%s/%s", branchName.c_str(), Traits<T>::TYPE_NAME));
      }
    }
    else
    {
      throw cmsException(this, __func__)
        << "Invalid array size = " << count << " for variable " << label << " with infix = " << infix;
    }
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(const std::string & infix,
              int count,
              T * & var,
              const std::string & label,
              Args & ... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(infix, count, var, label);
    setBranches(infix, count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(T & var,
              const std::string & label)
  {
    var = placeholder_value;
    outputTree -> Branch(label.c_str(), &var, Form("%s/%s", label.c_str(), Traits<T>::TYPE_NAME));
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  setBranches(T & var,
              const std::string & label,
              Args & ... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(var, label);
    setBranches(remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(int count,
        T * & var)
  {
    for(int i = 0; i < count; ++i)
    {
      var[i] = placeholder_value;
    }
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(int count,
        T * & var,
        Args & ... remainingVars)
  {
    reset(count, var);
    reset(count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(T & var)
  {
    var = placeholder_value;
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value && ! std::is_pointer<T>::value>>
  void
  reset(T & var,
        Args & ... remainingVars)
  {
    reset(var);
    reset(remainingVars...);
  }

  void reset(bool is_initializing);

  TFile * outputFile;
  TTree * outputTree;

  const Int_t nof_mus;
  const Int_t nof_eles;
  const Int_t nof_taus;
  const Int_t nof_jets;

  Long64_t nEvent;
  Int_t ls;
  Int_t run;

  Int_t n_presel_mu;
  Int_t n_fakeablesel_mu;
  Int_t n_cutsel_mu;
  Int_t n_mvasel_mu;

  Int_t n_presel_ele;
  Int_t n_fakeablesel_ele;
  Int_t n_cutsel_ele;
  Int_t n_mvasel_ele;

  Int_t n_presel_tau;
  Int_t n_presel_jet;

  Bool_t isGenMatched; ///< flag to indicate whether lepton(s) + tau(s) are all gen matched
  Int_t ntags;         ///< number of medium b-tagged jets
  Int_t ntags_loose;   ///< number of loose b-tagged jets

  Float_t * mu_pt;
  Float_t * mu_conept;
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
  Bool_t * mu_mediumID;
  Float_t * mu_dpt_div_pt;
  Bool_t * mu_isfakeablesel;
  Bool_t * mu_iscutsel;
  Bool_t * mu_ismvasel;

  Float_t * ele_pt;
  Float_t * ele_conept;
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
  Bool_t * ele_isChargeConsistent;
  Bool_t * ele_passesConversionVeto;
  Int_t * ele_nMissingHits;
  Bool_t * ele_isfakeablesel;
  Bool_t * ele_iscutsel;
  Bool_t * ele_ismvasel;

  Float_t * tau_pt;
  Float_t * tau_eta;
  Float_t * tau_phi;
  Float_t * tau_E;
  Int_t * tau_charge;
  Float_t * tau_dxy;
  Float_t * tau_dz;
  Int_t * tau_decayMode;
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

  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_E;
  Float_t * jet_CSV;

  std::map<std::string, Int_t> hltMap;

  std::map<FloatVariableType, Float_t> floatMap;
};

#endif // SYNCNTUPLEMANAGER_H
