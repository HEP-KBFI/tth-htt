#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_3l_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <Rtypes.h> // Int_t, Float_t

#include <iostream>

// forward declarations
class RecoLepton;
class RecoHadTau;
enum class MEMsys;

class MEMOutput_3l_1tau
{
public:
  MEMOutput_3l_1tau();
  ~MEMOutput_3l_1tau() {}

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  inline Float_t weight_ttH()           const { return weight_ttH_; }
  inline Float_t weight_ttH_error()     const { return weight_ttH_error_; }
  inline Float_t weight_ttZ()           const { return weight_ttZ_; }
  inline Float_t weight_ttZ_error()     const { return weight_ttZ_error_; }
  inline Float_t weight_ttH_hww()       const { return weight_ttH_hww_; }
  inline Float_t weight_ttH_hww_error() const { return weight_ttH_hww_error_; }
  inline Float_t LR()                   const { return LR_; }
  inline Float_t LR_up()                const { return LR_up_; }
  inline Float_t LR_down()              const { return LR_down_; }
  inline Float_t cpuTime()              const { return cpuTime_; }
  inline Float_t realTime()             const { return realTime_; }
  inline Int_t   isValid()              const { return isValid_; }
  inline Int_t   errorFlag()            const { return errorFlag_; }

  inline bool is_initialized() const { return eventInfo_.is_initialized(); }

  std::map<MEMsys, double>
  get_LR_map() const;

  void
  fillInputs(const RecoLepton * leadLepton,
             const RecoLepton * subleadLepton,
             const RecoLepton * thirdLepton,
             const RecoHadTau * hadTau);

  friend class MEMInterface_3l_1tau;
  friend class MEMOutputReader_3l_1tau;

  EventInfo eventInfo_;
  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t thirdLepton_eta_;
  Float_t thirdLepton_phi_;
  Float_t hadTau_eta_;
  Float_t hadTau_phi_;

protected:
  Float_t weight_ttH_;
  Float_t weight_ttH_error_;
  Float_t weight_ttZ_;
  Float_t weight_ttZ_error_;
  Float_t weight_ttH_hww_;
  Float_t weight_ttH_hww_error_;
  Float_t LR_;
  Float_t LR_up_;
  Float_t LR_down_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
  Int_t errorFlag_;
};

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_3l_1tau& memOutput);

#endif // MEMOutput_3l_1tau_h

