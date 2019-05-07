#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <TTree.h> // TTree

#include <type_traits> // std::enable_if<,>, std::is_arithmetic<>
#include <regex> // std::regex

// forward declarations
class TFile;
class RecoMuon;
class RecoElectron;
class RecoHadTau;
class RecoJet;
class RecoLepton;
class RecoJetAK8;
class RecoJetHTTv2;
class hltPath;

enum class FloatVariableType
{
//--- MET/MHT
  PFMET,
  PFMETphi,
  MHT,                      ///< vectorial sum of preselected leptons (including taus) + jets
  metLD,                    ///< linear discriminator based on MET

//--- Additional event-level MVA input variables
  mindr_lep1_jet,           ///< min dR between leading lepton and preselected jets
  mindr_lep2_jet,           ///< min dR between subleading lepton and preselected jets
  mindr_lep3_jet,           ///< min dR between third lepton and preselected jets
  mindr_lep4_jet,           ///< min dR between fourth lepton and preselected jets

  mindr_tau1_jet,           ///< min dR between leading tau and preselected jets
  mindr_tau2_jet,           ///< min dR between subleading tau and preselected jets

  avg_dr_jet,               ///< average dR between all the pairs of preselected jets
  avr_dr_lep_tau,           ///< average dR between all lepton and tau pairs
  max_dr_jet,               ///< maximum dR between all preselected jet pairs
  max_dr_lep_tau,           ///< maximum dR between all lepton and tau pairs
  min_dr_tau_jet,           ///< min dR between all tau and jets pairs (i.e. min(mindr_tau0_jet, mindr_tau1_jet, ...))
  min_dr_lep_tau,           ///< minimum dR between all lepton and tau pairs
  min_dr_lep_jet,           ///< minimum dR between all lepton and jet pairs

  dr_leps,                  ///< deltaR between two leading leptons
  dr_taus,                  ///< deltaR between two leading taus

  dr_lep_tau_ss,            ///< dR between (leading) lepton and same-sign tau
  dr_lep1_tau1,             ///< dR between leading lepton and leading tau
  dr_lep2_tau1,             ///< dR between leading sublepton and leading tau
  dr_lep3_tau1,             ///< dR between third lepton and (leading) tau
  dr_lep1_tau2,             ///< dR between leading lepton and subleading tau
  dr_lep2_tau2,             ///< dR between leading sublepton and subleading tau

  max_lep_eta,              ///< maximum absolute eta in all selected leptons

  mT_met_lep1,              ///< transverse mass of leading lepton and MET (using reco pt)
  mT_met_lep2,              ///< transverse mass of subleading lepton and MET (using reco pt)
  mT_met_lep3,              ///< transverse mass of trailing lepton and MET (using reco pt)
  mT_met_lep4,              ///< transverse mass of fourth lepton and MET (using reco pt)
  massL,                    ///< transverse mass of highest pT dilepton pair passing loose selection

  mTauTauVis,               ///< visible mass of the two selected taus
  mvis_l1tau,               ///< visible mass of leading lepton and tau (of OS in 3l+1tau)
  mvis_l2tau,               ///< visible mass of subleading lepton and tau (of OS in 3l+1tau)

  mbb,                      ///< mass of two selected medium b-jets
  mbb_loose,                ///< mass of two selected loose b-jets

  cosThetaS_hadTau,         ///< cosine of the angle b/w leading tau and the beam axis in di-tau frame?
  HTT,                      ///< output of hadronic top tagger with kin fit
  HadTop_pt,                ///< pT of the unfitted hadronic top

//--- boosted variables
  HTT_boosted,                    ///<  output of hadronic top tagger for boosted scenario
  HTT_semi_boosted_fromAK8,       ///<  output of hadronic top tagger for semi-boosted scenario
  HadTop_pt_semi_boosted_fromAK8, ///< ...
  Hj_tagger,                      ///< MVA output of Hj-tagger
  HadTop_pt_boosted,              ///< ?
  minDR_HTTv2_Lep,                ///< minimum distance between a tight Lepton (e/mu/tau) and the HTTv2 objet
                                  ///  that is tagged as "HTT_boosted"
  minDR_AK8_Lep,                  ///< minimum distance between a tight Lepton (e/mu/tau) and the AK8 jet
                                  /// that is tagged as part of "HTT_semi_boosted_fromAK8"

//--- Additional event-level MVA output variables
  mvaOutput_plainKin_ttV,   ///< 2l+2tau (BDT1), 3l+1tau (BDT1)
  mvaOutput_plainKin_tt,    ///< 1l+2tau (BDT1), 2l+2tau (BDT2), 3l+1tau (BDT2)

  mvaOutput_HTT_SUM_VT,     ///< 1l+2tau (BDT2)

  mvaOutput_plainKin_1B_VT,  ///< 2l+2tau (BDT4)
  mvaOutput_plainKin_SUM_VT, ///< 2l+2tau (BDT3)

  mvaOutput_2lss_ttV,                 ///< 2lss+1tau
  mvaOutput_2lss_tt,                  ///< 2lss+1tau
  mvaOutput_2lss_1tau_plainKin_tt,    ///< 2lss+1tau (BDT2)
  mvaOutput_2lss_1tau_plainKin_ttV,   ///< 2lss+1tau (BDT1)
  mvaOutput_2lss_1tau_plainKin_1B_M,  ///< 2lss+1tau (BDT6)
  mvaOutput_2lss_1tau_plainKin_SUM_M, ///< 2lss+1tau (BDT3)
  mvaOutput_2lss_1tau_HTT_SUM_M,      ///< 2lss+1tau (BDT4)
  mvaOutput_2lss_1tau_HTTMEM_SUM_M,   ///< 2lss+1tau (BDT5)

  mvaOutput_3l_ttV,         ///< 3l+1tau
  mvaOutput_3l_ttbar,       ///< 3l+1tau
  mvaOutput_plainKin_SUM_M, ///< 3l+1tau (BDT3)
  mvaOutput_plainKin_1B_M,  ///< 3l+1tau (BDT4)

  mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttH,
  mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_tH,
  mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_ttW,
  mvaOutput_2lss_ttH_tH_4cat_onlyTHQ_v4_rest,

  mvaOutput_3l_ttH_tH_3cat_v8_ttH,
  mvaOutput_3l_ttH_tH_3cat_v8_tH,
  mvaOutput_3l_ttH_tH_3cat_v8_rest,

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
  MEM_LR,                   ///< MEM likelihood ratio (the final score)

//--- custom additional branches (not necessary in sync)
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
  void read(const std::vector<const RecoLepton *> & leptons);
  void read(const std::vector<const RecoMuon *> & muons,
            const std::vector<const RecoMuon *> & fakeable_muons,
            const std::vector<const RecoMuon *> & tight_muons);
  void read(const std::vector<const RecoElectron *> & electrons,
            const std::vector<const RecoElectron *> & fakeable_electrons,
            const std::vector<const RecoElectron *> & tight_electrons);
  void read(const std::vector<const RecoHadTau *> & hadtaus);
  void read(const std::vector<const RecoJet *> & jets,
            bool isFwd = false);
  void read(const std::vector<const RecoJetAK8 *> & jets);
  void read(const std::vector<const RecoJetHTTv2 *> & jets);
  void read(Float_t value,
            FloatVariableType type);
  void read(const std::vector<std::vector<hltPath *>> & hltPaths);
  void read(bool is_genMatched,
            int n_tags,
            int n_tags_loose,
            int n_jets_light,
            int n_jets_cleanedFromAK8 = placeholder_value,
            bool bool_is_tH_like_and_not_ttH_like = false);
  void fill();
  void write();
  void reset();

  static const Int_t placeholder_value;
  static const std::regex endsWithNumberRegex;

private:
  static bool
  endsWithNumber(const std::string & infix);

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
      const bool isEndsWithNumber = SyncNtupleManager::endsWithNumber(infix);
      var = new T[count];
      for(int i = 0; i < count; ++i)
      {
        var[i] = placeholder_value;
        const std::string branchName = Form("%s%s%d_%s",
          infix.c_str(), isEndsWithNumber ? "_" : "", i + 1, label.c_str()
        );
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
      if(typeid(T) != typeid(Bool_t))
      {
        var[i] = placeholder_value;
      }
      else
      {
        var[i] = false;
      }
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
    if(typeid(T) != typeid(Bool_t))
    {
      var = placeholder_value;
    }
    else
    {
      var = false;
    }
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

  TFile * outputFile;
  TDirectory * outputDir;
  TTree * outputTree;

  const Int_t nof_leps;
  const Int_t nof_mus;
  const Int_t nof_eles;
  const Int_t nof_taus;
  const Int_t nof_jets;
  const Int_t nof_fwdJets;
  const Int_t nof_jetHTTv2;
  const Int_t nof_jetAK8;

  Long64_t nEvent;
  Int_t ls;
  Int_t run;

  Int_t n_sel_lep;
  Int_t n_presel_mu;
  Int_t n_fakeablesel_mu;
  Int_t n_mvasel_mu;
  Int_t n_presel_ele;
  Int_t n_fakeablesel_ele;
  Int_t n_mvasel_ele;
  Int_t n_presel_tau;
  Int_t n_presel_jet;
  Int_t n_presel_fwdJet;
  Int_t n_presel_jetHTTv2;
  Int_t n_presel_jetAK8;

  Bool_t isGenMatched;        ///< flag to indicate whether lepton(s) + tau(s) are all gen matched
  Bool_t is_tH_like_and_not_ttH_like;
  Int_t ntags;                ///< number of medium b-tagged jets
  Int_t ntags_loose;          ///< number of loose b-tagged jets
  Int_t njets_light;          ///< number of light jets (central jets not passing loose b-tag requirement + forward jets)
  Int_t njets_cleanedFromAK8; ///< number of jets passing the preselection (n_presel_jet),
                              ///  cleaned from the AK8 jet collection with a 0.8 distance deffinition

  Float_t * lep_pt;
  Float_t * lep_conePt;
  Float_t * lep_eta;
  Float_t * lep_phi;
  Int_t * lep_pdgId;
  Int_t * lep_isfakeablesel;
  Int_t * lep_ismvasel;

  Float_t * mu_pt;
  Float_t * mu_conept;
  Float_t * mu_eta;
  Float_t * mu_phi;
  Float_t * mu_E;
  Int_t * mu_charge;
  Float_t * mu_miniRelIso;
  Float_t * mu_miniRelIsoCharged;
  Float_t * mu_miniRelIsoNeutral;
  Float_t * mu_pfRelIso04All;
  Int_t * mu_jetNDauChargedMVASel;
  Float_t * mu_jetPtRel;
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_jetDeepCSV;
  Float_t * mu_jetDeepJet;
  Float_t * mu_sip3D;
  Float_t * mu_dxyAbs;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Float_t * mu_segmentCompatibility;
  Float_t * mu_leptonMVA;
  Int_t * mu_mediumID;
  Float_t * mu_dpt_div_pt;
  Int_t * mu_isfakeablesel;
  Int_t * mu_ismvasel;
  Int_t * mu_isGenMatched;

  Float_t * ele_pt;
  Float_t * ele_conept;
  Float_t * ele_eta;
  Float_t * ele_phi;
  Float_t * ele_E;
  Int_t * ele_charge;
  Float_t * ele_miniRelIso;
  Float_t * ele_miniRelIsoCharged;
  Float_t * ele_miniRelIsoNeutral;
  Float_t * ele_pfRelIso04All;
  Int_t * ele_jetNDauChargedMVASel;
  Float_t * ele_jetPtRel;
  Float_t * ele_jetPtRatio;
  Float_t * ele_jetCSV;
  Float_t * ele_jetDeepCSV;
  Float_t * ele_jetDeepJet;
  Float_t * ele_sip3D;
  Float_t * ele_dxyAbs;
  Float_t * ele_dxy;
  Float_t * ele_dz;
  Float_t * ele_ntMVAeleID;
  Float_t * ele_leptonMVA;
  Int_t * ele_isChargeConsistent;
  Int_t * ele_passesConversionVeto;
  Int_t * ele_nMissingHits;
  Float_t * ele_sigmaEtaEta;
  Float_t * ele_HoE;
  Float_t * ele_deltaEta;
  Float_t * ele_deltaPhi;
  Float_t * ele_OoEminusOoP;
  Int_t * ele_isfakeablesel;
  Int_t * ele_ismvasel;
  Int_t * ele_isGenMatched;

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
  Int_t * tau_byVVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_byVVTightIsolationMVArun2v1DBdR03oldDMwLT;
  Float_t * tau_rawMVArun2v1DBdR03oldDMwLT;
  Int_t * tau_againstMuonLoose3;
  Int_t * tau_againstMuonTight3;
  Int_t * tau_againstElectronVLooseMVA6;
  Int_t * tau_againstElectronLooseMVA6;
  Int_t * tau_againstElectronMediumMVA6;
  Int_t * tau_againstElectronTightMVA6;
  Int_t * tau_againstElectronVTightMVA6;
  Int_t * tau_isGenMatched;

  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_E;
  Float_t * jet_CSV;
  Float_t * jet_DeepCSV;
  Float_t * jet_DeepJet;
  Float_t * jet_QGdiscr;

  Float_t * jetFwd_pt;
  Float_t * jetFwd_eta;
  Float_t * jetFwd_phi;
  Float_t * jetFwd_E;

  Float_t * jetHTTv2_pt;
  Float_t * jetHTTv2_eta;
  Float_t * jetHTTv2_phi;
  Float_t * jetHTTv2_E;

  Float_t * jetAK8_pt;
  Float_t * jetAK8_eta;
  Float_t * jetAK8_phi;
  Float_t * jetAK8_E;

  std::map<std::string, Int_t> hltMap;

  std::map<FloatVariableType, Float_t> floatMap;
};

#endif // SYNCNTUPLEMANAGER_H
