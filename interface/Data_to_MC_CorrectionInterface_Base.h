#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_Base_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_Base_h

#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // FRet, FRmt

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

// forward declarations
class TFile;
class TauIDSFTool;
class lutWrapperBase;
enum class TauID;

class Data_to_MC_CorrectionInterface_Base
{
public:
  Data_to_MC_CorrectionInterface_Base(const edm::ParameterSet & cfg);
  virtual ~Data_to_MC_CorrectionInterface_Base();

  //-----------------------------------------------------------------------------
  // overwrite configuration parameters (needed by analyze_jetToTauFakeRate.cc)
  void
  setHadTauSelection(const std::string & hadTauSelection);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // set lepton type, pT and eta
  // (to be called once per event, before calling any of the getSF.. functions)
  void
  setLeptons(int lepton1_type,      double lepton1_pt,      double lepton1_cone_pt,      double lepton1_eta,
             int lepton2_type = -1, double lepton2_pt = 0., double lepton2_cone_pt = 0., double lepton2_eta = 0.,
             int lepton3_type = -1, double lepton3_pt = 0., double lepton3_cone_pt = 0., double lepton3_eta = 0.,
             int lepton4_type = -1, double lepton4_pt = 0., double lepton4_cone_pt = 0., double lepton4_eta = 0.);

  void
  setHadTaus(int hadTau1_genPdgId,      double hadTau1_pt,      double hadTau1_eta,
             int hadTau2_genPdgId = -1, double hadTau2_pt = 0., double hadTau2_eta = 0.,
             int hadTau3_genPdgId = -1, double hadTau3_pt = 0., double hadTau3_eta = 0.,
             int hadTau4_genPdgId = -1, double hadTau4_pt = 0., double hadTau4_eta = 0.);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for electron and muon trigger efficiency
  virtual double
  getSF_leptonTriggerEff(TriggerSFsys central_or_shift) const;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC corrections for electron and muon identification and isolation efficiency,
  // including the cut on the ttH multilepton MVA
  double
  getSF_leptonID_and_Iso_loose() const;

  double
  getSF_leptonID_and_Iso_fakeable_to_loose() const;

  double
  getSF_leptonID_and_Iso_tight_to_loose_woTightCharge(LeptonIDSFsys central_or_shift) const;

  double
  getSF_leptonID_and_Iso_tight_to_loose_wTightCharge(LeptonIDSFsys central_or_shift) const;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC corrections for hadronic tau identification efficiency,
  // and for e->tau and mu->tau misidentification rates
  virtual double
  getSF_hadTauID_and_Iso(TauIDSFsys central_or_shift) const;

  virtual double
  getSF_eToTauFakeRate(FRet central_or_shift) const;

  virtual double
  getSF_muToTauFakeRate(FRmt central_or_shift) const;
  //-----------------------------------------------------------------------------

protected:
  double
  getSF_leptonID_and_Iso(std::size_t numLeptons,
                         const std::vector<double> & lepton_pt,
                         const std::vector<double> & lepton_eta,
                         const std::vector<lutWrapperBase *> & corrections) const;

  void
  initAntiEle_tauIDSFs(const std::string & era_str);

  void
  initAntiMu_tauIDSFs(const std::string & era_str);

  void
  init_tauIDSFs(const std::string & era_str,
                std::map<int, TauIDSFTool *> & tauIDSF_map,
                const std::string & tauID_str,
                int nof_levels);

  //-----------------------------------------------------------------------------
  // data/MC corrections for electron and muon identification and isolation efficiency,
  // including the cut on the ttH multilepton MVA

  // loose electron selection (RecoElectronSelectorLoose)
  std::vector<lutWrapperBase *> sfElectronID_and_Iso_loose_;
  // tight electron selection used in all channels except 2lss_1tau (RecoElectronSelectorTight with tightCharge_cut disabled)
  std::vector<lutWrapperBase *> sfElectronID_and_Iso_tight_to_loose_woTightCharge_;
  // tight electron selection specific to 2lss_1tau channel (RecoElectronSelectorTight with tightCharge_cut enabled)
  std::vector<lutWrapperBase *> sfElectronID_and_Iso_tight_to_loose_wTightCharge_;
  // errors for the above
  std::vector<lutWrapperBase *> sfElectronID_and_Iso_tight_to_loose_errors_up_;
  std::vector<lutWrapperBase *> sfElectronID_and_Iso_tight_to_loose_errors_down_;

  // loose muon selection (RecoMuonSelectorLoose)
  std::vector<lutWrapperBase *> sfMuonID_and_Iso_loose_;
  // tight muon selection used in all channels except 2lss_1tau (RecoMuonSelectorTight with tightCharge_cut disabled)
  std::vector<lutWrapperBase *> sfMuonID_and_Iso_tight_to_loose_woTightCharge_;
  // tight muon selection specific to 2lss_1tau channel (RecoMuonSelectorTight with tightCharge_cut enabled)
  std::vector<lutWrapperBase *> sfMuonID_and_Iso_tight_to_loose_wTightCharge_;
  // errors for the above
  std::vector<lutWrapperBase *> sfMuonID_and_Iso_tight_to_loose_errors_up_;
  std::vector<lutWrapperBase *> sfMuonID_and_Iso_tight_to_loose_errors_down_;
  //-----------------------------------------------------------------------------

  std::map<std::string, TFile *> inputFiles_;

  int hadTauSelection_;
  TauID hadTauId_;
  std::string tauIDSF_str_;
  std::string tauIDSF_level_str_;

  int hadTauSelection_antiElectron_[4];
  int hadTauSelection_antiMuon_[4];

  TauIDSFTool * tauIdSFs_;
  std::map<int, TauIDSFTool *> tauIDSFs_antiEle_;
  std::map<int, TauIDSFTool *> tauIDSFs_antiMu_;
  bool applyHadTauSF_;
  bool isDEBUG_;

  std::size_t numLeptons_;
  std::vector<int> lepton_type_;
  std::vector<double> lepton_pt_;
  std::vector<double> lepton_cone_pt_;
  std::vector<double> lepton_eta_;
  std::size_t numElectrons_;
  std::vector<double> electron_pt_;
  std::vector<double> electron_cone_pt_;
  std::vector<double> electron_eta_;
  std::size_t numMuons_;
  std::vector<double> muon_pt_;
  std::vector<double> muon_cone_pt_;
  std::vector<double> muon_eta_;
  std::size_t numHadTaus_;
  std::vector<int> hadTau_genPdgId_;
  std::vector<double> hadTau_pt_;
  std::vector<double> hadTau_eta_;
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_Base_h
