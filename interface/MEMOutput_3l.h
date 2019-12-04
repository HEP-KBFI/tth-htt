#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_3l_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_3l_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <Rtypes.h> // Int_t, Float_t

#include <iostream>

#define ADDMEM_3L_ERROR                  1
#define ADDMEM_3L_ERROR_JETMULTIPLICITY  2
#define ADDMEM_3L_ERROR_BJETMULTIPLICITY 3
#define ADDMEM_3L_ERROR_SKIPPED          4
#define ADDMEM_3L_ERROR_SKIPPED_NOPERM   5
#define ADDMEM_3L_ERROR_NOPERM           6

// forward declarations
class RecoLepton;
enum class MEMsys;

class MEMOutput_3l
{
public:
  MEMOutput_3l();
  ~MEMOutput_3l() {}

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  inline Float_t weight_ttH()       const { return weight_ttH_; }
  inline Float_t weight_ttH_error() const { return weight_ttH_error_; }
  inline Float_t kinfitscore_ttH()  const { return kinfitscore_ttH_; }
  inline Float_t weight_tHq()       const { return weight_tHq_; }
  inline Float_t weight_tHq_error() const { return weight_tHq_error_; }
  inline Float_t kinfitscore_tHq()  const { return kinfitscore_tHq_; }
  inline Float_t weight_ttW()       const { return weight_ttW_; }
  inline Float_t weight_ttW_error() const { return weight_ttW_error_; }
  inline Float_t kinfitscore_ttW()  const { return kinfitscore_ttW_; }
  inline Float_t weight_ttZ()       const { return weight_ttZ_; }
  inline Float_t weight_ttZ_error() const { return weight_ttZ_error_; }
  inline Float_t kinfitscore_ttZ()  const { return kinfitscore_ttZ_; }
  inline Float_t weight_tt()        const { return weight_tt_; }
  inline Float_t weight_tt_error()  const { return weight_tt_error_; }
  inline Float_t kinfitscore_tt()   const { return kinfitscore_tt_; }
  inline Float_t LR()               const { return LR_; }
  inline Float_t LR_error()         const { return LR_error_; }
  inline Float_t LR_up()            const { return LR_up_; }
  inline Float_t LR_down()          const { return LR_down_; }
  inline Float_t cpuTime()          const { return cpuTime_; }
  inline Float_t realTime()         const { return realTime_; }
  inline Int_t isValid()            const { return isValid_; }
  inline Int_t errorFlag()          const { return errorFlag_; }

  inline bool is_initialized() const { return eventInfo_.is_initialized(); }

  std::map<MEMsys, double>
  get_LR_map() const;

  friend class MEMInterface_3l;
  friend class MEMOutputReader_3l;

  void
  fillInputs(const RecoLepton * leadLepton,
             const RecoLepton * subleadLepton,
             const RecoLepton * thirdLepton);

  EventInfo eventInfo_;
  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t thirdLepton_eta_;
  Float_t thirdLepton_phi_;
  Int_t errorFlag_;
protected:
  Float_t weight_ttH_; 
  Float_t weight_ttH_error_;
  Float_t kinfitscore_ttH_; 
  Float_t weight_tHq_; 
  Float_t weight_tHq_error_;
  Float_t kinfitscore_tHq_; 
  Float_t weight_ttW_;
  Float_t weight_ttW_error_;
  Float_t kinfitscore_ttW_; 
  Float_t weight_ttZ_; 
  Float_t weight_ttZ_error_;
  Float_t kinfitscore_ttZ_; 
  Float_t weight_tt_;
  Float_t weight_tt_error_;
  Float_t kinfitscore_tt_; 
  Float_t LR_;
  Float_t LR_error_;
  Float_t LR_up_;
  Float_t LR_down_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
};

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_3l& memOutput);

#endif // MEMOutput_3l_h
