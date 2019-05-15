#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_3l_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_3l_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <Rtypes.h> // Int_t, Float_t

#include <iostream>

// forward declarations
class RecoLepton;

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
  inline Float_t kinfitscore_ttH()  const { return kinfitscore_ttH_; }
  inline Float_t weight_tt()        const { return weight_tt_; }
  inline Float_t kinfitscore_tt()   const { return kinfitscore_tt_; }
  inline Float_t LR()               const { return LR_; }
  inline Float_t cpuTime()          const { return cpuTime_; }
  inline Float_t realTime()         const { return realTime_; }
  inline Int_t isValid()            const { return isValid_; }
  inline Int_t errorFlag()          const { return errorFlag_; }

  inline bool is_initialized() const { return eventInfo_.is_initialized(); }

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
protected:
  Float_t weight_ttH_; 
  Float_t kinfitscore_ttH_; 
  Float_t weight_tt_; 
  Float_t kinfitscore_tt_; 
  Float_t LR_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t isValid_;
  Int_t errorFlag_;
};

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_3l& memOutput);

#endif // MEMOutput_3l_h
