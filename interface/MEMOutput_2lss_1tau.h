#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <Rtypes.h> // Int_t, Float_t

#include <iostream>

#define ADDMEM_2LSS1TAU_ERROR                 1
#define ADDMEM_2LSS1TAU_ERROR_JETMULTIPLICITY 2
#define ADDMEM_2LSS1TAU_ERROR_MATRIXINVERSION 3
#define ADDMEM_2LSS1TAU_ERROR_SKIPPED         4
#define ADDMEM_2LSS1TAU_ERROR_SKIPPED_NOPERM  5
#define ADDMEM_2LSS1TAU_ERROR_NOPERM          6

// forward declarations
class RecoLepton;
class RecoHadTau;
enum class MEMsys;

class MEMOutput_2lss_1tau
{
public:
  MEMOutput_2lss_1tau();
  ~MEMOutput_2lss_1tau() {}

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  inline Int_t type()                   const { return type_; }
  inline Float_t weight_ttH()           const { return weight_ttH_; }
  inline Float_t weight_ttH_error()     const { return weight_ttH_error_; }
  inline Float_t weight_ttZ()           const { return weight_ttZ_; }
  inline Float_t weight_ttZ_error()     const { return weight_ttZ_error_; }
  inline Float_t weight_ttZ_Zll()       const { return weight_ttZ_Zll_; }
  inline Float_t weight_ttZ_Zll_error() const { return weight_ttZ_Zll_error_; }
  inline Float_t weight_tt()            const { return weight_tt_; }
  inline Float_t weight_tt_error()      const { return weight_tt_error_; }
  inline Float_t LR()                   const { return LR_; }
  inline Float_t LR_up()                const { return LR_up_; }
  inline Float_t LR_down()              const { return LR_down_; }
  inline Float_t ttZ_LR()               const { return ttZ_LR_; }
  inline Float_t ttZ_LR_up()            const { return ttZ_LR_up_; }
  inline Float_t ttZ_LR_down()          const { return ttZ_LR_down_; }
  inline Float_t ttbar_LR()             const { return ttbar_LR_; }
  inline Float_t ttbar_LR_up()          const { return ttbar_LR_up_; }
  inline Float_t ttbar_LR_down()        const { return ttbar_LR_down_; }
  inline Float_t cpuTime()              const { return cpuTime_; }
  inline Float_t realTime()             const { return realTime_; }
  inline Int_t isValid()                const { return isValid_; }
  inline Int_t errorFlag()              const { return errorFlag_; }
  inline Int_t isValid_ttZ_LR()         const { return isValid_ttZ_LR_; }
  inline Int_t errorFlag_ttZ_LR()       const { return errorFlag_ttZ_LR_; }
  inline Int_t isValid_ttbar_LR()       const { return isValid_ttbar_LR_; }
  inline Int_t errorFlag_ttbar_LR()     const { return errorFlag_ttbar_LR_; }

  inline bool is_initialized() const { return eventInfo_.is_initialized(); }

  std::map<MEMsys, double>
  get_LR_map() const;

  friend class MEMInterface_2lss_1tau;
  friend class MEMOutputReader_2lss_1tau;

  void
  fillInputs(const RecoLepton * leadLepton,
             const RecoLepton * subleadLepton,
             const RecoHadTau * hadTau);

  EventInfo eventInfo_;
  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t hadTau_eta_;
  Float_t hadTau_phi_;
  Int_t errorFlag_;
protected:
  Int_t type_; // either 0 (fully reconstructed W->jj decay) or 1 (one jet from W->jj decay not reconstructed)
  Float_t weight_ttH_;
  Float_t weight_ttH_error_;
  Float_t weight_ttZ_; // ttZ, Z->tautau->lep+tauh
  Float_t weight_ttZ_error_;
  Float_t weight_ttZ_Zll_; // ttZ, Z->ll
  Float_t weight_ttZ_Zll_error_;
  Float_t weight_tt_; // tt+jets (dilepton)
  Float_t weight_tt_error_;
  Float_t LR_;
  Float_t LR_up_;
  Float_t LR_down_;
  Float_t ttZ_LR_;
  Float_t ttZ_LR_up_;
  Float_t ttZ_LR_down_;
  Float_t ttbar_LR_;
  Float_t ttbar_LR_up_;
  Float_t ttbar_LR_down_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
  Int_t isValid_ttZ_LR_;
  Int_t errorFlag_ttZ_LR_;
  Int_t isValid_ttbar_LR_;
  Int_t errorFlag_ttbar_LR_;
};

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_2lss_1tau& memOutput);

#endif // MEMOutput_2lss_1tau_h
