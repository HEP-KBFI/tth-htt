#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_3l_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE

#include <Rtypes.h> // Int_t, Float_t

#include <iostream> 
#include <iomanip> 

class MEMOutput_3l_1tau
{
 public:
  MEMOutput_3l_1tau();
  MEMOutput_3l_1tau(RUN_TYPE run,
		    LUMI_TYPE lumi,
		    EVT_TYPE evt,
		    Float_t leadLepton_eta,
		    Float_t leadLepton_phi,
		    Float_t subleadLepton_eta,
		    Float_t subleadLepton_phi,
		    Float_t thirdLepton_eta,
		    Float_t thirdLepton_phi,
		    Float_t hadTau_eta,
		    Float_t hadTau_phi,
		    Float_t weight_ttH,
		    Float_t weight_ttZ,
		    Float_t weight_ttH_hww,
		    Float_t LR,
		    Float_t cpuTime,
		    Float_t realTime,
		    Int_t isValid,
		    Int_t errorFlag);
  ~MEMOutput_3l_1tau() {}

  void set_run(RUN_TYPE run) { run_ = run; }
  void set_lumi(LUMI_TYPE lumi) { lumi_ = lumi; }
  void set_evt(EVT_TYPE evt) { evt_ = evt; }

  void set_leadLepton_eta(Float_t leadLepton_eta) { leadLepton_eta_ = leadLepton_eta; }
  void set_leadLepton_phi(Float_t leadLepton_phi) { leadLepton_phi_ = leadLepton_phi; }
  void set_subleadLepton_eta(Float_t subleadLepton_eta) { subleadLepton_eta_ = subleadLepton_eta; }
  void set_subleadLepton_phi(Float_t subleadLepton_phi) { subleadLepton_phi_ = subleadLepton_phi; }
  void set_thirdLepton_eta(Float_t thirdLepton_eta) { thirdLepton_eta_ = thirdLepton_eta; }
  void set_thirdLepton_phi(Float_t thirdLepton_phi) { thirdLepton_phi_ = thirdLepton_phi; }
  void set_hadTau_eta(Float_t hadTau_eta) { hadTau_eta_ = hadTau_eta; }
  void set_hadTau_phi(Float_t hadTau_phi) { hadTau_phi_ = hadTau_phi; }

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
  Float_t thirdLepton_eta() const { return thirdLepton_eta_; }
  Float_t thirdLepton_phi() const { return thirdLepton_phi_; }
  Float_t hadTau_eta() const { return hadTau_eta_; }
  Float_t hadTau_phi() const { return hadTau_phi_; }
  Float_t weight_ttH() const { return weight_ttH_; }
  Float_t weight_ttZ() const { return weight_ttZ_; }
  Float_t weight_ttH_hww() const { return weight_ttH_hww_; }
  Float_t LR() const { return LR_; }
  Float_t cpuTime() const { return cpuTime_; }
  Float_t realTime() const { return realTime_; }
  Int_t isValid() const { return isValid_; }
  Int_t errorFlag() const { return errorFlag_; }

  bool is_initialized() { return run_ != 0 && lumi_ != 0 && evt_ != 0; }

  friend class MEMInterface_3l_1tau;

 protected:
  RUN_TYPE run_;
  LUMI_TYPE lumi_;
  EVT_TYPE evt_;
  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t thirdLepton_eta_;
  Float_t thirdLepton_phi_;
  Float_t hadTau_eta_;
  Float_t hadTau_phi_;
  Float_t weight_ttH_;
  Float_t weight_ttZ_;
  Float_t weight_ttH_hww_;
  Float_t LR_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
  Int_t errorFlag_;
};

std::ostream& operator<<(std::ostream& stream, const MEMOutput_3l_1tau& memOutput);

#endif // MEMOutput_3l_1tau_h

