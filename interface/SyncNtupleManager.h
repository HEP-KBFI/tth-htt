#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

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
  PFMET,
  PFMETphi,
  MHT,
  metLD,
  mvaOutput_ttV,
  mvaOutput_ttbar,
  MC_weight,
  FR_weight,
  triggerSF_weight,
  leptonSF_weight,
  bTagSF_weight,
  PU_weight,
  hadTauSF_weight,
  genWeight,
  lumiScale
};

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
  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
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
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranches(const std::string & infix,
              int count,
              T * & var,
              const std::string & label,
              Args... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(infix, count, var, label);
    setBranches(infix, count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranches(T & var,
              const std::string & label)
  {
    outputTree -> Branch(label.c_str(), &var, Form("%s/%s", label.c_str(), Traits<T>::TYPE_NAME));
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  setBranches(T & var,
              const std::string & label,
              Args... remainingVars)
  {
    if(! outputTree)
    {
      throw cmsException(this, __func__) << "Input tree uninitialized";
    }
    setBranches(var, label);
    setBranches(remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
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
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  reset(int count,
        T * & var,
        Args... remainingVars)
  {
    reset(count, var);
    reset(count, remainingVars...);
  }

  template<typename T,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  reset(T & var)
  {
    var = placeholder_value;
  }

  template<typename T,
           typename... Args,
           typename = std::enable_if<std::is_arithmetic<T>::value>>
  void
  reset(T & var,
        Args... remainingVars)
  {
    reset(var);
    reset(remainingVars...);
  }

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
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_sip3D;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Float_t * mu_segmentCompatibility;
  Float_t * mu_leptonMVA;
  Float_t * mu_conept;
  Bool_t * mu_mediumID;
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
  Float_t * ele_jetPtRatio;
  Float_t * ele_jetCSV;
  Float_t * ele_sip3D;
  Float_t * ele_dxy;
  Float_t * ele_dz;
  Float_t * ele_ntMVAeleID;
  Float_t * ele_leptonMVA;
  Float_t * ele_conept;
  Int_t * ele_isChargeConsistent;
  Bool_t * ele_passesConversionVeto;
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
  Bool_t * tau_decayModeFindingOldDMs;
  Bool_t * tau_decayModeFindingNewDMs;
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
  Float_t * jet_heppyFlavour;

  std::map<std::string, Int_t> hltMap;

  Float_t lep0_conept;
  Float_t lep1_conept;
  Float_t mindr_lep0_jet;
  Float_t mindr_lep1_jet;
  Float_t MT_met_lep0;
  Float_t avg_dr_jet;
  Float_t n_jet25_recl;

  std::map<FloatVariableType, Float_t> floatMap;
};

#endif // SYNCNTUPLEMANAGER_H
