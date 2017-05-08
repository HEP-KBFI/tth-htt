#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE

#include <Rtypes.h> // Int_t, Float_t

#include <iostream> 
#include <iomanip> 

class MEMOutput_2lss_1tau
{
 public:
  MEMOutput_2lss_1tau();
  MEMOutput_2lss_1tau(RUN_TYPE run,
		      LUMI_TYPE lumi,
		      EVT_TYPE evt,
		      Float_t leadLepton_eta,
		      Float_t leadLepton_phi,
		      Float_t subleadLepton_eta,
		      Float_t subleadLepton_phi,
		      Float_t hadTau_eta,
		      Float_t hadTau_phi,
		      Int_t type,
		      Float_t weight_ttH,
		      Float_t weight_ttZ,
		      Float_t weight_ttZ_Zll,
		      Float_t weight_tt,
		      Float_t LR,
		      Float_t cpuTime,
		      Float_t realTime,
		      Int_t isValid,
		      Int_t errorFlag);
  ~MEMOutput_2lss_1tau() {}

  void set_run(RUN_TYPE run) { run_ = run; }
  void set_lumi(LUMI_TYPE lumi) { lumi_ = lumi; }
  void set_evt(EVT_TYPE evt) { evt_ = evt; }

  void set_leadLepton_eta(Float_t leadLepton_eta) { leadLepton_eta_ = leadLepton_eta; }
  void set_leadLepton_phi(Float_t leadLepton_phi) { leadLepton_phi_ = leadLepton_phi; }
  void set_subleadLepton_eta(Float_t subleadLepton_eta) { subleadLepton_eta_ = subleadLepton_eta; }
  void set_subleadLepton_phi(Float_t subleadLepton_phi) { subleadLepton_phi_ = subleadLepton_phi; }
  void set_hadTau_eta(Float_t hadTau_eta) { hadTau_eta_ = hadTau_eta; }
  void set_hadTau_phi(Float_t hadTau_phi) { hadTau_phi_ = hadTau_phi; }

  bool is_initialized() { return run_ != 0 && lumi_ != 0 && evt_ != 0; }

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  RUN_TYPE run() const { return run_; }
  LUMI_TYPE lumi() const { return lumi_; }
  EVT_TYPE evt() const { return evt_; }
  Float_t leadLepton_eta() const { return leadLepton_eta_; }
  Float_t leadLepton_phi() const { return leadLepton_phi_; }
  Float_t subleadLepton_eta() const { return subleadLepton_eta_; }
  Float_t subleadLepton_phi() const { return subleadLepton_phi_; }
  Float_t hadTau_eta() const { return hadTau_eta_; }
  Float_t hadTau_phi() const { return hadTau_phi_; }
  Int_t type() const { return type_; }
  Float_t weight_ttH() const { return weight_ttH_; }
  Float_t weight_ttZ() const { return weight_ttZ_; }
  Float_t weight_ttZ_Zll() const { return weight_ttZ_Zll_; }
  Float_t weight_tt() const { return weight_tt_; }
  Float_t LR() const { return LR_; }
  Float_t ttZ_LR() const { return ttZ_LR_; }
  Float_t ttbar_LR() const { return ttbar_LR_; }
  Float_t cpuTime() const { return cpuTime_; }
  Float_t realTime() const { return realTime_; }
  Int_t isValid() const { return isValid_; }
  Int_t errorFlag() const { return errorFlag_; }
  Int_t isValid_ttZ_LR() const { return isValid_ttZ_LR_; }
  Int_t errorFlag_ttZ_LR() const { return errorFlag_ttZ_LR_; }
  Int_t isValid_ttbar_LR() const { return isValid_ttbar_LR_; }
  Int_t errorFlag_ttbar_LR() const { return errorFlag_ttbar_LR_; }

  friend class MEMInterface_2lss_1tau;

 protected:
  RUN_TYPE run_;
  LUMI_TYPE lumi_;
  EVT_TYPE evt_;
  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t hadTau_eta_;
  Float_t hadTau_phi_;
  Int_t type_; // either 0 (fully reconstructed W->jj decay) or 1 (one jet from W->jj decay not reconstructed)
  Float_t weight_ttH_;
  Float_t weight_ttZ_; // ttZ, Z->tautau->lep+tauh
  Float_t weight_ttZ_Zll_; // ttZ, Z->ll
  Float_t weight_tt_; // tt+jets (dilepton)
  Float_t LR_;
  Float_t ttZ_LR_;
  Float_t ttbar_LR_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
  Int_t errorFlag_;
  Int_t isValid_ttZ_LR_;
  Int_t errorFlag_ttZ_LR_;
  Int_t isValid_ttbar_LR_;
  Int_t errorFlag_ttbar_LR_;
};

std::ostream& operator<<(std::ostream& stream, const MEMOutput_2lss_1tau& memOutput);

#endif // MEMOutput_2lss_1tau_h
